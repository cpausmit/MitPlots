#!/usr/bin/env python

import sys
import os
import re
import time
import subprocess
from argparse import ArgumentParser

argParser = ArgumentParser(description = 'Submit BAMBU analysis to cluster')
argParser.add_argument('analysisCfg', metavar = 'ANALYSIS')
argParser.add_argument('--cfg', '-c', metavar = 'FILE', dest = 'configFileName')
argParser.add_argument('--book', '-b', metavar = 'BOOK', dest = 'book')
argParser.add_argument('--dataset', '-d', metavar = 'DATASET', dest = 'dataset')
argParser.add_argument('--filesets', '-s', metavar = 'FILESETS', dest = 'filesets', nargs = '*')

argParser.add_argument('--name', '-n', metavar = 'NAME', dest = 'taskName')

argParser.add_argument('--condor-template', '-t', metavar = 'FILE', dest = 'condorTemplateName', default = os.environ['CMSSW_BASE'] + '/src/MitAna/config/condor_template.jdl')
argParser.add_argument('--no-hierarchy', '-a', action = 'store_true', dest = 'anarchy')

args = argParser.parse_args()
sys.argv = []

if not os.path.exists(args.analysisCfg):
    raise RuntimeError('Analysis configuration file ' + args.analysisCfg + ' does not exist')

if args.configFileName and not os.path.exists(args.configFileName):
    raise RuntimeError('Task configuration file ' + args.configFileName + ' does not exist')

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
        response = sys.stdin.readline()
        if response.strip() == 'y':
            break
        elif response.strip() == 'n':
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

print 'Creating task', taskName

logDirName = os.environ['MIT_PROD_LOGS'] + '/' + taskName
os.mkdir(logDirName)

taskDirName = os.environ['MIT_PROD_HIST'] + '/' + taskName
os.mkdir(taskDirName)

envFileName = taskDirName + '/taskenv.sh'
with open(envFileName, 'w') as envFile:
    envFile.write('export SCRAM_ARCH="' + os.environ['SCRAM_ARCH'] + '"\n')
    envFile.write('export CMSSW_RELEASE="' + os.path.basename(os.environ['CMSSW_RELEASE_BASE']) + '"\n')

analysisCfgName = taskDirName + '/analysis.py'
with open(analysisCfgName, 'w') as analysisCfg:
    with open(args.analysisCfg) as source:
        for line in source:
            if not re.search('MitAna.TreeMod.bambu', line.strip()):
                analysisCfg.write(line)

catalogPackName = taskDirName + '/catalogs.tar.gz'
proc = subprocess.Popen(['tar', 'czf', catalogPackName, '-C', catalogDirName] + catalogs, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
out, err = proc.communicate()
print out
if err.strip():
    sys.stderr.write(err)
    sys.stderr.flush()

cmsswbase = os.environ['CMSSW_BASE']
libTarballName = os.path.dirname(cmsswbase) + '/libraries.tar.gz'
remakeTarball = True
if os.path.exists(libTarballName):
    tarballLastUpdate = os.path.getmtime(libTarballName)
    libDirName = cmsswbase + '/lib/' + os.environ['SCRAM_ARCH']
    for lib in os.listdir(libDirName):
        if os.path.getmtime(libDirName) > tarballLastUpdate:
            break
    else:
        remakeTarball = False
        
if remakeTarball:
    proc = subprocess.Popen(['tar', 'czf', libTarballName, '-C', os.path.dirname(cmsswbase), os.path.basename(cmsswbase) + '/lib/' + os.environ['SCRAM_ARCH']], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    out, err = proc.communicate()
    print out
    if err.strip():
        sys.stderr.write(err)
        sys.stderr.flush()

condorStr = ''
with open(args.condorTemplateName) as condorTemplate:
    for line in condorTemplate:
        if not re.match('#', line.strip()):
            condorStr += line

proc = subprocess.Popen(['condor_q', '-submitter', os.environ['USER'], '-autoformat', 'Iwd', 'Args'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
out, err = proc.communicate()

running = []

for line in out.split('\n'):
    matches = re.match('Iwd = (.*) +Args = ([^ ]+) ([^ ]+) ([^ ]+)')
    running.append((os.path.basename(matches.group(1)), matches.group(2), matches.group(3), matches.group(4)))

for book, dataset, filesetId in filesets:
    if (taskName, book, dataset, filesetId) in running:
        continue

    jobDirName = taskDirName + '/' + book + '/' + dataset

    try:
        os.makedirs(jobDirName)
    except:
        pass

    jdlFileName = jobDirName + '/' + filesetId + '.jdl'
    with open(jdlFileName, 'w') as jdlFile:
        jdlFile.write(condorStr + '\n')
        
        line = 'Arguments = ' + book + ' ' + dataset + ' ' + filesetId
        jdlFile.write(line + '\n')

        line = 'Output = ' + logDirName + '/' + filesetId + '.out'
        jdlFile.write(line + '\n')

        line = 'Error = ' + logDirName + '/' + filesetId + '.err'
        jdlFile.write(line + '\n')

        line = 'Log = ' + logDirName + '/' + filesetId + '.log'
        jdlFile.write(line + '\n')

        line = 'transfer_input_files = run.py,'
        if x509File:
            line += ' ' + x509File + ','
        line += ' ' + analysisCfgName + ','
        line += ' ' + envFileName + ','
        line += ' ' + libTarballName + ','
        line += ' ' + catalogPackName
        jdlFile.write(line + '\n')

        line = 'transfer_output_files = ' + dataset + '_' + filesetId + '.root'
        jdlFile.write(line + '\n')

        line = 'Initialdir = ' + jobDirName
        jdlFile.write(line + '\n')

        jdlFile.write('Queue\n')

    proc = subprocess.Popen(['condor_submit', jdlFileName], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    out, err = proc.communicate()
    print out
    if err.strip():
        sys.stderr.write(err)
        sys.stderr.flush()
