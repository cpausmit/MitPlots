#!/usr/bin/env python
#---------------------------------------------------------------------------------------------------
# Script to generate code
#
# Author: C.Paus                                                                      (July 1, 2008)
#---------------------------------------------------------------------------------------------------
import os,sys,getopt,re,string

#===================================================================================================
# Main starts here
#===================================================================================================
# Define string to explain usage of the script
usage =  "Usage: submit.py --base=<name>\n"
usage += "                 --namespace=<name>\n"
usage += "                 --dir=<version>\n"
usage += "                 --file=<version>\n"
usage += "                 --help\n"

# Define the valid options which can be specified and check out the command line
valid = ['base=','namespace=','dir=','file=','help']
try:
    opts, args = getopt.getopt(sys.argv[1:], "", valid)
except getopt.GetoptError, ex:
    print usage
    print str(ex)
    sys.exit(1)

# --------------------------------------------------------------------------------------------------
# Get all parameters for the production
# --------------------------------------------------------------------------------------------------
# Set defaults for each option
base       = "MitAna/DataTree"
namespace  = "mitedm"
dir        = "MitEdm/AnalysisDataFormats"
file       = ""

# Read new values from the command line
for opt, arg in opts:
    if opt == "--help":
        print usage
        sys.exit(0)
    if opt == "--base":
        base      = arg
    if opt == "--namespace":
        namespace = arg
    if opt == "--dir":
        dir       = arg
    if opt == "--file":
        oneFile   = arg

ccFiles = []
hFiles  = []

cmd = '/bin/ls -1 ' + os.environ['CMSSW_BASE'] + '/src/' + base + '/interface' + '/' + oneFile + \
      ' | grep -v \~'
print ' CMD: ' + cmd
for line in os.popen(cmd).readlines():   # run command
    file        = line[:-1]              # strip '\n'
    f           = file.split('/');
    file        = f.pop()
    hFiles.append(file)

cmd = '/bin/ls -1 ' + os.environ['CMSSW_BASE'] + '/src/' + base + '/src' + '/' + oneFile + \
      ' | grep -v \~ 2> /dev/null'
print ' CMD: ' + cmd
for line in os.popen(cmd).readlines():   # run command
    file        = line[:-1]              # strip '\n'
    f           = file.split('/');
    file        = f.pop()
    ccFiles.append(file)

# Compile search and replacement sequences
pClassDef  = re.compile('ClassDef')
pClassImp  = re.compile('ClassImp')
pNamespace = re.compile('mithep')
pBase      = re.compile(base)

for file in hFiles:
    print " hFile: " + file
    iFile = os.environ['CMSSW_BASE'] + '/src/' + base + '/interface/' + file
    oFile = pBase.sub(dir,iFile);
    print "Generate: " + oFile + '\n from: ' + iFile
    cmd = 'rm -f ' + oFile
    status = os.system(cmd)
    # Parse template input and write the crab configuration file
    fileI = open(iFile,'r')
    fileO = open(oFile,'w')
    line = fileI.readline()
    while (line != ''):
        line = pNamespace.sub(namespace,line);
        line = pBase     .sub(dir,      line);
        if namespace == "mitedm":
            line = pClassDef.sub("//ClassDef", line);
        fileO.write(line)
        line = fileI.readline()
    fileI.close()
    fileO.close()
    cmd = 'chmod a-w ' + oFile
    status = os.system(cmd)

for file in ccFiles:
    print " ccFile: " + file
    iFile = os.environ['CMSSW_BASE'] + '/src/' + base + '/src/' + file
    oFile = pBase.sub(dir,iFile);
    print "Generate: " + oFile + '\n from: ' + iFile
    cmd = 'rm -f ' + oFile
    status = os.system(cmd)
    # Parse template input and write the crab configuration file
    fileI = open(iFile,'r')
    fileO = open(oFile,'w')
    line = fileI.readline()
    while (line != ''):
        line = pNamespace.sub(namespace,line);
        line = pBase     .sub(dir,      line);
        if namespace == "mitedm":
            line = pClassImp.sub("//ClassImp", line);
        fileO.write(line)
        line = fileI.readline()
    fileI.close()
    fileO.close()
    cmd = 'chmod a-w ' + oFile
    status = os.system(cmd)
