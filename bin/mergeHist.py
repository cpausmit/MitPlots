#!/usr/bin/env python
#===================================================================================================
import sys, getopt, os, fnmatch, commands
import string

# declare
setupCmsswCommand = \
  'cd /home/$USER/cms/cmssw/017/CMSSW_3_9_5_patch1/src;eval `scram runtime -sh`;cd - >& /dev/null;'

#===================================================================================================
def usage():
    print "possible options are: --help, --InputPath=<myInputPath>, --OutputPath=<myOutputPath>," \
          + " --FilenameHeader=<myFileHeader>, --DatasetListFile=<datasetListFile>"

#===================================================================================================
def filesExist(path,filenameExpression):
    exists = False
    for fileName in os.listdir(path):
        if fnmatch.fnmatch (fileName,filenameExpression):
            exists = True
    return exists

#===================================================================================================
# Merge Filesets
#===================================================================================================
def MergeFilesets(versionList,datasetNameList,skimNameList,inputPath,outputPath,filenameHeader):
    n = 0
    for dataset in datasetNameList:
        #print "================================================================"
        print " Merging files for dataset: " + dataset

        # create the output directory in case it is not yet there
        command              = 'mkdir -p ' + outputPath
        os.system(command)

        outputMergedFilename = filenameHeader + '_' + dataset + '_' + skimNameList[n] + '.root'
        inputFilenameRegExp  = filenameHeader + '_' + dataset + '_' + skimNameList[n] + '_????.root'
        command              = setupCmsswCommand + 'hadd -f ' + outputPath + outputMergedFilename \
                               + ' ' + inputPath + '/' + versionList[n] + '/' + dataset + '/' \
                               + inputFilenameRegExp + ' >& ./merging.tmp'
#        command              = 'hadd -f ' + outputPath + \
#                               outputMergedFilename + ' ' + inputPath + inputFilenameRegExp + \
#                               ' >& ./merging.tmp'

        if (filesExist(inputPath+'/'+versionList[n]+'/'+dataset,inputFilenameRegExp) == True):
            if (os.path.exists(outputPath+outputMergedFilename)):
                print " Warning: merged file already exists. It will be deleted.\n " + \
                      outputPath+outputMergedFilename
                os.system('rm ' + outputPath+outputMergedFilename)
            #print ' merging: ' + command
            os.system(command)
            #print ''
        else:
            print " Warning: No files for dataset " + dataset + "\n at the location: " + inputPath \
                  + '/' + versionList[n] + '/' + dataset + '/' + inputFilenameRegExp
        #print ''
        n += 1

#===================================================================================================
# Main Program
#===================================================================================================
datasetListFile = ''
inputPath = ''
outputPath = ''
filenameHeader = ''
versionList = list()
datasetNameList = list()
skimNameList = list()

if len(sys.argv[1:]) < 1:
    print "Error: not enough parameters specified"
    usage()
    sys.exit()

try:
    opts, args = getopt.getopt(sys.argv[1:], "hi:o:f:d:",
                               ["help","InputPath=","OutputPath=",
                                "FilenameHeader=","DatasetListFile="])
    for o, a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("-i", "--InputPath"):
            inputPath = a + "/"
        elif o in ("-o", "--OutputPath"):
            outputPath = a + "/"
        elif o in ("-f", "--FilenameHeader"):
            filenameHeader = a
        elif o in ("-d", "--DatasetListFile"):
            datasetListFile = a
        else:
            usage()
            sys.exit()
except getopt.GetoptError:
    usage()
    sys.exit(2)

if (inputPath == ''):
    print "Error: No InputPath specified."
    sys.exit()

if (outputPath == ''):
    print "Error: No OutputPath specified."
    sys.exit()

if (filenameHeader == ''):
    print "Error: No FilenameHeader specified."
    sys.exit()

if (datasetListFile == ''):
    print "Error: No dataset list file specified."
    sys.exit()

try:
    inputFile = open(datasetListFile,"r")
except IOError:
    print "Error: The specified dataset list file " + datasetListFile + " could not be opened."
    sys.exit()

#===================================================================================================
# Read in list of datasets and skim names
#===================================================================================================
lineNumber = 1
templine = inputFile.readline()
while len(templine.split()) > 0:

    # ignore commented lines
    if (templine[0] == '#'):
        templine = inputFile.readline()
        lineNumber += 1
        continue;

    # check what type of list was provided and assume 'noskim' as default
    if (len(templine.split()) == 7) :
        tempInputList = templine.split()
        versionList    .append(tempInputList[0])
        datasetNameList.append(tempInputList[1])
        skimNameList   .append('noskim')
        lineNumber += 1
    else:
        print " ERROR: incorrect format for cross section file. Check line %s" % lineNumber
        sys.exit()

    # read the next line
    templine = inputFile.readline()

inputFile.close()

# Check the list of variables
count = 0
for l in datasetNameList:
    count += 1

MergeFilesets(versionList,datasetNameList,skimNameList,inputPath,outputPath,filenameHeader)
