#!/usr/bin/env python

import sys
import os
import re
import time
import subprocess
import glob
import shutil
from argparse import ArgumentParser

argParser = ArgumentParser(description = 'Submit BAMBU analysis to cluster')
argParser.add_argument('analysisCfg', metavar = 'ANALYSIS')
argParser.add_argument('--cfg', '-c', metavar = 'FILE', dest = 'configFileName')
argParser.add_argument('--book', '-b', metavar = 'BOOK', dest = 'book')
argParser.add_argument('--dataset', '-d', metavar = 'DATASET', dest = 'dataset')
argParser.add_argument('--filesets', '-s', metavar = 'FILESETS', dest = 'filesets', nargs = '*')

argParser.add_argument('--name', '-n', metavar = 'NAME', dest = 'taskName')
argParser.add_argument('--overwrite', '-R', action = 'store_true', dest = 'overwrite')

argParser.add_argument('--condor-template', '-t', metavar = 'FILE', dest = 'condorTemplateName', default = os.environ['CMSSW_BASE'] + '/src/MitAna/config/condor_template.jdl')
argParser.add_argument('--stageout-dir', '-o', metavar = 'DIR', dest = 'stageoutDirName')
argParser.add_argument('--no-hierarchy', '-a', action = 'store_true', dest = 'anarchy')

args = argParser.parse_args()
sys.argv = []

if not os.path.exists(args.analysisCfg):
    raise RuntimeError('Analysis configuration file ' + args.analysisCfg + ' does not exist')

if args.configFileName and not os.path.exists(args.configFileName):
    raise RuntimeError('Task configuration file ' + args.configFileName + ' does not exist')

if args.stageoutDirName and not os.path.isdir(args.stageoutDirName):
    raise RuntimeError('Cannot write to stageout directory ' + args.stageoutDirName)

def runSubproc(*args):
    proc = subprocess.Popen(*args, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    out, err = proc.communicate()
    print out
    if err.strip():
        sys.stderr.write(err)
        sys.stderr.flush()

catalogDirName = os.environ['MIT_CATALOG']

datasets = []

if args.configFileName:
    with open(args.configFileName) as configFile:
        for line in configFile:
            matches = re.match('([ ^]+) +([ ^]+) +', line.strip())
            if not matches:
                continue

            datasets.append((matches.group(1), matches.group(2)))

elif args.book and args.dataset:
    datasets.append((args.book, args.dataset))

if len(datasets) == 0:
    print 'No valid dataset found.'
    sys.exit(1)

filesets = []
catalogs = []

for book, dataset in datasets:
    with open(catalogDirName + '/' + book + '/' + dataset + '/Filesets') as catalog:
        for line in catalog:
            filesetId = line.strip().split()[0]
            if len(args.filesets) and filesetId not in args.filesets:
                continue

            filesets.append((book, dataset, filesetId))

    catalogs.append(book + '/' + dataset)

if len(filesets) == 0:
    print 'No valid fileset found.'
    sys.exit(1)

x509File = '/tmp/x509up_u' + str(os.getuid())
if not os.path.exists(x509File):
    print 'x509 proxy missing. You will not be able to download files from T2 in case T3 cache does not exist.'
    print 'Continue? [y/n]:'
    while True:
        response = sys.stdin.readline().strip()
        if response == 'y':
            break
        elif response == 'n':
            sys.exit(0)
        else:
            print '[y/n]:'
            
    x509File = ''

taskName = args.taskName
if not taskName:
    if args.configFileName:
        taskName = args.configFileName[:args.configFileName.find('.')]
    else:
        taskName = str(int(time.time()))

taskDirName = os.environ['MIT_PROD_HIST'] + '/' + taskName
logDirName = os.environ['MIT_PROD_LOGS'] + '/' + taskName

scramArch = os.environ['SCRAM_ARCH']
cmsswbase = os.environ['CMSSW_BASE']
release = os.path.basename(os.environ['CMSSW_RELEASE_BASE'])

if os.path.isdir(taskDirName):
    if args.overwrite:
        print ' Task ' + taskName + ' already exists.'
        print ' You are requesting this to be a new production task. All existing files will be cleared.'
        print ' Wanna save existing task? Do like:  moveOutput.sh', taskName, taskName + '-last.'
        print ' Do you wish to continue? [N/y]'
        while True:
            response = sys.stdin.readline().strip()
            if response == 'y':
                newTask = True
                break
            elif response == 'N':
                print ' Nothing done. EXIT.'
                sys.exit(0)
            else:
                print '[N/y]'

        shutil.rmtree(taskDirName)
        shutil.rmtree(logDirName)

    else:
        newTask = False

else:
    newTask = True

analysisCfgName = taskDirName + '/analysis.py'
envFileName = taskDirName + '/taskenv.sh'
catalogPackName = taskDirName + '/catalog.tar.gz'
libPackName = cmsswbase + '.lib.tar.gz'
incPackName = cmsswbase + '.inc.tar.gz'

if newTask:
    print 'Creating task', taskName
    os.mkdir(taskDirName)
    os.mkdir(logDirName)

    with open(envFileName, 'w') as envFile:
        envFile.write('export SCRAM_ARCH="' + scramArch + '"\n')
        envFile.write('export CMSSW_RELEASE="' + release + '"\n')
    
    with open(analysisCfgName, 'w') as analysisCfg:
        with open(args.analysisCfg) as source:
            for line in source:
                if not re.search('MitAna.TreeMod.bambu', line.strip()):
                    analysisCfg.write(line)
    
    runSubproc(['tar', 'czf', catalogPackName, '-C', catalogDirName] + catalogs)
    
    remakeLibPack = not os.path.exists(libPackName)
    if os.path.exists(libPackName):
        packLastUpdate = os.path.getmtime(libPackName)
    else:
        packLastUpdate = 0
    
    for lib in glob.glob(cmsswbase + '/lib/' + scramArch + '/*'):
        if os.path.getmtime(lib) > packLastUpdate:
            remakeLibPack = True
            break
    
    if remakeLibPack:
        print 'Creating library tarball.'
        runSubproc(['tar', 'czf', libPackName, '-C', cmsswbase, 'lib'])

    # Include files needed until ROOT 6 libraries become position independent
    remakeIncPack = not os.path.exists(incPackName)
    headerPaths = []
    if os.path.exists(incPackName):
        packLastUpdate = os.path.getmtime(incPackName)
    else:
        packLastUpdate = 0
    
    for package in os.listdir(cmsswbase + '/src'):
        for module in os.listdir(cmsswbase + '/src/' + package):
            if os.path.isdir(cmsswbase + '/src/' + package + '/' + module + '/interface'):
                for header in glob.glob(cmsswbase + '/src/' + package + '/' + module + '/interface/*'):
                    if os.path.getmtime(header) > packLastUpdate:
                        remakeIncPack = True
    
                headerPaths.append('src/' + package + '/' + module + '/interface')
    
    if remakeIncPack:
        print 'Creating headers tarball.'
        runSubproc(['tar', 'czf', incPackName, '-C', cmsswbase] + headerPaths)

print 'Checking running jobs..'

proc = subprocess.Popen(['condor_q', '-submitter', os.environ['USER'], '-autoformat', 'Iwd', 'Args'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
out, err = proc.communicate()

running = []

for line in out.split('\n'):
    matches = re.match('Iwd = (.*) +Args = ([^ ]+) ([^ ]+) ([^ ]+)', line.strip())
    if matches and os.path.basename(matches.group(1)) == taskName:
        running.append((matches.group(2), matches.group(3), matches.group(4)))

if newTask and len(running) != 0:
    print 'New task was requested but some jobs are running.'
    print 'Job kill is not implemented yet.'
    sys.exit(1)

condorConfig = {}
with open(args.condorTemplateName) as condorTemplate:
    for line in condorTemplate:
        if not re.match('#', line.strip()):
            key, eq, value = line.partition('=')
            condorConfig[key.strip().lower()] = value.strip()

inputFilesList = cmsswbase + '/src/MitAna/bin/run.py,'
if x509File:
    inputFilesList += ' ' + x509File + ','
inputFilesList += ' ' + analysisCfgName + ','
inputFilesList += ' ' + envFileName + ','
inputFilesList += ' ' + libPackName + ','
inputFilesList += ' ' + incPackName + ','
inputFilesList += ' ' + catalogPackName

for book, dataset, filesetId in filesets:
    if (book, dataset, filesetId) in running:
        print 'Running: ', book, dataset, filesetId
        continue

    jobDirName = taskDirName + '/' + book + '/' + dataset
    outputName = filesetId + '.root'

    if not os.path.exists(jobDirName):
        os.makedirs(jobDirName)

    if args.stageoutDirName:
        dest = args.stageoutDirName + '/' + taskName + '/' + book + '/' + dataset
        if not os.path.exists(dest):
            os.makedirs(dest)
        outputPath = dest + '/' + outputName
    else:
        outputPath = jobDirName + '/' + outputName

    if os.path.exists(outputPath):
        print 'Output exists: ', book, dataset, filesetId
        continue

    if 'arguments' not in condorConfig:
        condorConfig['arguments'] = '"' + book + ' ' + dataset + ' ' + filesetId + '"'

    if 'transfer_input_files' not in condorConfig:
        condorConfig['transfer_input_files'] = inputFilesList

    if 'transfer_output_files' not in condorConfig:
        condorConfig['transfer_output_files'] = outputName

    if args.stageoutDirName:
        condorConfig['transfer_output_remaps'] = '"' + outputName + ' = ' + dest + '/' + outputName

    condorConfig['output'] = logDirName + '/' + filesetId + '.out'
    condorConfig['error'] = logDirName + '/' + filesetId + '.err'
    condorConfig['log'] = logDirName + '/' + filesetId + '.log'
    condorConfig['initialdir'] = jobDirName

    jdlFileName = jobDirName + '/' + filesetId + '.jdl'
    with open(jdlFileName, 'w') as jdlFile:
        for key, value in condorConfig.items():
            jdlFile.write(key + ' = ' + value + '\n')

        jdlFile.write('Queue\n')

    runSubproc(['condor_submit', jdlFileName])
