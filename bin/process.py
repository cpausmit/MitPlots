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
argParser.add_argument('--fileset', '-s', metavar = 'FILESET', dest = 'fileset')

argParser.add_argument('--name', '-n', metavar = 'NAME', dest = 'taskName')

argParser.add_argument('--condor-template', '-t', metavar = 'FILE', dest = 'condorTemplateName', default = os.path.dirname(os.path.realpath(__file__)) + '/condor_template.jdl')
argParser.add_argument('--no-hierarchy', '-a', action = 'store_true', dest = 'anarchy')

args = argParser.parse_args()
sys.argv = []

if not os.path.exists(args.analysisCfg):
    raise RuntimeError('Analysis configuration ' + args.analysisCfg + ' does not exist')

taskName = args.taskName
if not taskName:
    if args.configFileName:
        taskName = args.configFileName[:args.configFileName.find('.')]
    else:
        taskName = str(int(time.time()))

catalogDirName = os.environ['MIT_CATALOG']
logDirName = os.environ['MIT_PROD_LOGS'] + '/' + taskName

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

filesets = []
catalogs = []

for book, dataset in datasets:
    with open(catalogDirName + '/' + book + '/' + dataset + '/Filesets') as catalog:
        for line in catalog:
            filesetId = line.strip().split()[0]
            if args.fileset and filesetId != args.fileset:
                continue

            filesets.append((book, dataset, filesetId))

    catalogs.append(book + '/' + dataset)

x509File = '/tmp/x509up_u' + str(os.getuid())

taskDirName = os.environ['MIT_PROD_HIST'] + '/' + taskName

envFileName = taskDirName + '/taskenv.py'
with open(envFileName, 'w') as envFile:
    envFile.write('SCRAM_ARCH = "' + os.environ['SCRAM_ARCH'] + '"\n')
    envFile.write('CMSSW_RELEASE = "' + os.path.basename(os.environ['CMSSW_RELEASE_BASE']) + '"\n')
    envFile.write('PYTHONPATH = "' + os.path.basename(os.environ['PYTHONPATH']) + '"\n')

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
    for lib in os.listdir(cmsswbase + '/lib/' + os.environ['SCRAM_ARCH']):
        if os.path.getmtime(lib) > tarballLastUpdate:
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

for book, dataset, filesetId in filesets:
    jobDirName = taskDirName + '/' + book + '/' + dataset

    jdlFileName = jobDirName + '/' + filesetId + '.jdl'
    with open(jdlFileName, 'w') as jdlFile:
        jdlFile.write(condorStr + '\n')
        
        line = 'Arguments ='
        line += ' --book=' + book
        line += ' --dataset=' + dataset
        line += ' --fileset=' + filesetId
        line += ' ' + os.path.basename(args.analysisCfg)
        jdlFile.write(line + '\n')

        line = 'Output = ' + logDirName + '/' + filesetId + '.out'
        jdlFile.write(line + '\n')

        line = 'Error = ' + logDirName + '/' + filesetId + '.err'
        jdlFile.write(line + '\n')

        line = 'Log = ' + logDirName + '/' + filesetId + '.log'
        jdlFile.write(line + '\n')

        line = 'transfer_input_files ='
        line += ' ' + x509File + ','
        line += ' ' + args.analysisCfg + ','
        line += ' ' + envFileName + ','
        line += ' ' + libTarballName + ','
        line += ' ' + catalogPackName
        jdlFile.write(line + '\n')

        line = 'transfer_output_files ='
        line += dataset + '_' + fileset + '.root'
        jdlFile.write(line + '\n')

        jdlFile.write('Queue\n')

#    proc = subprocess.Popen(['condor_submit', jdlFileName], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#    out, err = proc.communicate()
#    print out
#    if err.strip():
#        sys.stderr.write(err)
#        sys.stderr.flush()

    
