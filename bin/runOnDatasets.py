#!/usr/bin/env python

import sys
import os
import re
import time
import subprocess
import glob
import shutil
import socket
from argparse import ArgumentParser

if 'CMSSW_BASE' not in os.environ:
    print 'CMSSW_BASE not set.'
    sys.exit(1)

argParser = ArgumentParser(description = 'Submit BAMBU analysis to cluster')
argParser.add_argument('--cfg', '-c', metavar = 'FILE', dest = 'configFileName')

argParser.add_argument('--book', '-b', metavar = 'BOOK', dest = 'book', default = 't2mit/filefi/040')
argParser.add_argument('--dataset', '-d', metavar = 'DATASET', dest = 'dataset')
argParser.add_argument('--filesets', '-s', metavar = 'FILESETS', dest = 'filesets', nargs = '*', default = [])

argParser.add_argument('--goodlumi', '-j', metavar = 'FILE', dest = 'goodlumiFiles', nargs = '+')

argParser.add_argument('--analysis', '-a', metavar = 'ANALYSIS', dest = 'analysisCfg')

argParser.add_argument('--name', '-n', metavar = 'NAME', dest = 'taskName')
argParser.add_argument('--overwrite', '-R', action = 'store_true', dest = 'overwrite')

argParser.add_argument('--condor-template', '-t', metavar = 'FILE', dest = 'condorTemplateName', default = os.environ['CMSSW_BASE'] + '/src/MitAna/config/condor_template.jdl')
argParser.add_argument('--stageout-dir', '-o', metavar = 'DIR', dest = 'stageoutDirName')

args = argParser.parse_args()
sys.argv = []

if args.analysisCfg and not os.path.exists(args.analysisCfg):
    print 'Analysis configuration file ' + args.analysisCfg + ' does not exist'
    sys.exit(1)

if args.configFileName and not os.path.exists(args.configFileName):
    print 'Task configuration file ' + args.configFileName + ' does not exist'
    sys.exit(1)

if args.stageoutDirName and not os.path.isdir(args.stageoutDirName):
    print 'Cannot write to stageout directory ' + args.stageoutDirName
    sys.exit(1)

def runSubproc(*args, **kwargs):
    proc = subprocess.Popen(list(args), stdout = subprocess.PIPE, stderr = subprocess.PIPE, stdin = subprocess.PIPE)

    if 'stdin' in kwargs and type(kwargs['stdin']) is str:
        stdin = kwargs['stdin']
    else:
        stdin = None
            
    out, err = proc.communicate(stdin)

    if out.strip():
        print out

    if err.strip():
        sys.stderr.write(err)
        sys.stderr.flush()

try:
    catalogDirName = os.environ['MIT_CATALOG']
except KeyError:
    print 'MIT_CATALOG environment not set.'
    sys.exit(1)

# list of pairs (book, dataset)
datasets = []

# json is usually a single file per dataset, but handling as a list since the filter module can
# accept multiple
jsonLists = {}

if args.configFileName:
    with open(args.configFileName) as configFile:
        for line in configFile:
            matches = re.match('([^ ]+) +([^ ]+)( +[^ ]+)*', line.strip())
            if not matches:
                continue

            book = matches.group(1)
            dataset = matches.group(2)
            datasets.append((book, dataset))

            # third paren captures the last column, which is currently assigned to JSON
            if matches.group(3):
                jsonLists[(book, dataset)] = [matches.group(3).strip()]

elif args.book and args.dataset:
    datasets.append((args.book, args.dataset))
    if args.goodlumiFiles:
        jsonLists[(args.book, args.dataset)] = args.goodlumiFiles

if len(datasets) == 0:
    print 'No valid dataset found.'
    sys.exit(1)

allFilesets = {}

for book, dataset in datasets:
    filesets = []
    with open(catalogDirName + '/' + book + '/' + dataset + '/Filesets') as catalog:
        for line in catalog:
            filesetId = line.strip().split()[0]
            if len(args.filesets) and filesetId not in args.filesets:
                continue

            filesets.append(filesetId)

    if len(filesets) != 0:
        allFilesets[(book, dataset)] = filesets

if len(allFilesets) == 0:
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

try:
    taskDirName = os.environ['HOME'] + '/cms/condor/' + taskName
    outDirName = os.environ['MIT_PROD_HIST'] + '/' + taskName
    logDirName = os.environ['MIT_PROD_LOGS'] + '/' + taskName
    
    scramArch = os.environ['SCRAM_ARCH']
    cmsswbase = os.environ['CMSSW_BASE']
    release = os.path.basename(os.environ['CMSSW_RELEASE_BASE'])
except KeyError, err:
    print 'Environment', err.args[0], ' not set'
    sys.exit(1)

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
        shutil.rmtree(outDirName)
        shutil.rmtree(logDirName)

    else:
        newTask = False

else:
    newTask = True

analysisCfgName = taskDirName + '/analysisCfg.py' # shipping the actual python script until module export works
envFileName = taskDirName + '/taskenv.sh'
libPackName = cmsswbase + '.lib.tar.gz'
incPackName = cmsswbase + '.inc.tar.gz'
pyPackName = cmsswbase + '.python.tar.gz'
binPackName = cmsswbase + '.MitAna-bin.tar.gz'

if newTask:
    if not args.analysisCfg:
        print 'No analysis configuration specified. Set by --analysis=config_path'
        sys.exit(1)

    print 'Creating task', taskName
    os.makedirs(taskDirName)
    os.mkdir(outDirName)
    os.mkdir(logDirName)

    with open(envFileName, 'w') as envFile:
        envFile.write('export SCRAM_ARCH="' + scramArch + '"\n')
        envFile.write('export CMSSW_RELEASE="' + release + '"\n')

    ### TEMPORARY
    # NOT COOL BUT NECESSARY UNTIL INTRA-PYTHON MODULE PACKING IS FIGURED OUT
    shutil.copy(args.analysisCfg, analysisCfgName)

    remakePyPack = not os.path.exists(pyPackName)

    if os.path.exists(pyPackName):
        packLastUpdate = os.path.getmtime(pyPackName)
    else:
        packLastUpdate = 0
    
    for package in os.listdir(cmsswbase + '/python'):
        if not os.path.isdir(cmsswbase + '/python/' + package):
            continue

        for module in os.listdir(cmsswbase + '/python/' + package):
            if not os.path.isdir(cmsswbase + '/python/' + package + '/' + module):
                continue

            for path in glob.glob(cmsswbase + '/python/' + package + '/' + module + '/*'):
                if os.path.islink(path):
                    path = os.readlink(path)

                if os.path.getmtime(path) > packLastUpdate:
                    remakePyPack = True
                    break
            else:
                continue

            break
        else:
            continue

        break
    
    if remakePyPack:
        print 'Creating python tarball.'
        runSubproc('tar', 'chzf', pyPackName, '-C', cmsswbase, 'python')
    ### TEMPORARY
  
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
        runSubproc('tar', 'czf', libPackName, '-C', cmsswbase, 'lib')

    # Include files needed until ROOT 6 libraries become position independent
    remakeIncPack = not os.path.exists(incPackName)

    headerPaths = []
    if os.path.exists(incPackName):
        packLastUpdate = os.path.getmtime(incPackName)
    else:
        packLastUpdate = 0
    
    for package in os.listdir(cmsswbase + '/src'):
        if not os.path.isdir(cmsswbase + '/src/' + package):
            continue

        for module in os.listdir(cmsswbase + '/src/' + package):
            if not os.path.isdir(cmsswbase + '/src/' + package + '/' + module + '/interface'):
                continue

            for header in glob.glob(cmsswbase + '/src/' + package + '/' + module + '/interface/*'):
                if os.path.getmtime(header) > packLastUpdate:
                    remakeIncPack = True
                    break

            headerPaths.append('src/' + package + '/' + module + '/interface')
    
    if remakeIncPack:
        print 'Creating headers tarball.'
        runSubproc('tar', 'czf', incPackName, '-C', cmsswbase, *tuple(headerPaths))

    remakeBinPack = not os.path.exists(binPackName)

    if os.path.exists(binPackName):
        packLastUpdate = os.path.getmtime(binPackName)
    else:
        packLastUpdate = 0

    for fileName in glob.glob(cmsswbase + '/src/MitAna/bin/*'):
        if os.path.getmtime(fileName) > packLastUpdate:
            remakeBinPack = True
            break

    if remakeBinPack:
        runSubproc('tar', 'czf', binPackName, '-C', cmsswbase, 'src/MitAna/bin')

print 'Checking for running jobs..'

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

condorTemplate = {}
with open(args.condorTemplateName) as condorTemplateFile:
    for line in condorTemplateFile:
        if not re.match('#', line.strip()):
            key, eq, value = line.partition('=')
            condorTemplate[key.strip().lower()] = value.strip()

# loop over datasets to submit

for (book, dataset), filesets in allFilesets.items():
    jobDirName = taskDirName + '/' + book + '/' + dataset
    jobOutDirName = outDirName + '/' + book + '/' + dataset
    jobLogDirName = logDirName + '/' + book + '/' + dataset

    condorTemplate['initialdir'] = jobOutDirName

    if not os.path.exists(jobDirName):
        os.makedirs(jobDirName)

    if not os.path.exists(jobOutDirName):
        os.makedirs(jobOutDirName)

    if not os.path.exists(jobLogDirName):
        os.makedirs(jobLogDirName)

    if args.stageoutDirName:
        stageoutDest = args.stageoutDirName + '/' + taskName + '/' + book + '/' + dataset
        if not os.path.exists(stageoutDest):
            os.makedirs(stageoutDest)

    catalogPackName = jobDirName + '/catalog.tar.gz'
    if not os.path.exists(catalogPackName):
        runSubproc('tar', 'czf', catalogPackName, '-C', catalogDirName, book + '/' + dataset)

    if 'transfer_input_files' not in condorTemplate:
        inputFilesList = cmsswbase + '/src/MitAna/bin/analysis.py,'
        if x509File:
            inputFilesList += ' ' + x509File + ','
        inputFilesList += ' ' + analysisCfgName + ','
        inputFilesList += ' ' + envFileName + ','
        inputFilesList += ' ' + libPackName + ','
        inputFilesList += ' ' + incPackName + ','
        inputFilesList += ' ' + pyPackName + ','
        inputFilesList += ' ' + binPackName + ','
        inputFilesList += ' ' + catalogPackName
    else:
        inputFilesList = condorTemplate['transfer_input_files']

    # loop over filesets and do actual submission   
    for fileset in filesets:
        if (book, dataset, fileset) in running:
            print 'Running: ', book, dataset, fileset
            continue
    
        outputName = fileset + '.root'
   
        if args.stageoutDirName:
            outputPath = stageoutDest + '/' + outputName
        else:
            outputPath = jobOutDirName + '/' + outputName
    
        if os.path.exists(outputPath) and os.stat(outputPath).st_size != 0:
            print 'Output exists: ', book, dataset, fileset
            continue

        print book, dataset, fileset

        condorConfig = {}
        condorConfig.update(condorTemplate)
    
        if 'arguments' not in condorConfig:
            arguments = book + ' ' + dataset + ' ' + fileset
            if (book, dataset) in jsonLists:
                arguments += ' ' + ' '.join(jsonLists[(book, dataset)])

            condorConfig['arguments'] = '"' + arguments + '"'
    
        if 'transfer_output_files' not in condorConfig:
            condorConfig['transfer_output_files'] = outputName
    
        if args.stageoutDirName:
            condorConfig['transfer_output_remaps'] = '"' + outputName + ' = ' + outputPath + '"'
    
        condorConfig['output'] = jobLogDirName + '/' + fileset + '.out'
        condorConfig['error'] = jobLogDirName + '/' + fileset + '.err'
        condorConfig['log'] = jobLogDirName + '/' + fileset + '.log'
        condorConfig['transfer_input_files'] = inputFilesList
    
        jdlCommand = '\n'.join([key + ' = ' + value for key, value in condorConfig.items()]) + '\nqueue\n'

        runSubproc('condor_submit', stdin = jdlCommand)
