#!/usr/bin/env python
#===================================================================================================
#
# Merge root files from a given datasets together.
#
#===================================================================================================
import sys, os, re
import time
import subprocess
import shutil

#===================================================================================================
# Merge Filesets
#===================================================================================================
def MergeFilesets(inputPath, outputPath, filenameHeader, datasets = [], skim = '', overwrite = False, debug = False):

    proc = subprocess.Popen(['which', 'hadd'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    out, err = proc.communicate()
    if proc.returncode != 0:
        print "Cannot use merge command `hadd'. Please make sure ROOT environment is set."
        sys.exit(1)

    # create the output directory in case it is not yet there
    outputPath = os.path.realpath(outputPath)
    if not os.path.exists(outputPath):
        os.makedirs(outputPath)

    # check if the output path is in the local file system
    # if not, will create a temp path in /tmp and copy the final product over
    local = True
    for line in open('/proc/mounts'):
        fs = line.strip().split()[0]
        mount = line.strip().split()[1]
        if outputPath.startswith(mount):
            if not fs.startswith('/dev'):
                local = False
            
    if local:
        writePath = outputPath
    else:
        try:
            writePath = '/tmp/' + str(int(time.time()))
            os.makedirs(writePath)
        except OSError:
            time.sleep(1)

    # if no datasets were given, pick up all that are in the input directory
    if len(datasets) == 0:
        for dirName in os.listdir(inputPath):
            if os.path.isdir(inputPath + '/' + dirName):
                datasets.append(dirName)

    # merge input for each dataset
    for dataset in datasets:
        # output name
        if skim:
            outputMergedFilename = writePath + '/' + filenameHeader + '_' + dataset + '_' + skim + '.root'
        else:
            outputMergedFilename = writePath + '/' + filenameHeader + '_' + dataset + '.root'

        if os.path.exists(outputMergedFilename):
            delete = False
            if overwrite:
                print " Overwriting existing output "
                print " " + outputMergedFilename
                delete = True
            else:
                print " Output file "
                print " " + outputMergedFilename
                print " already exists. Do you wish to overwrite? [y/N]:"
                while True:
                    response = sys.stdin.readline()
                    if response.strip() == 'y':
                        delete = True
                    elif response.strip() == 'N':
                        break
                    else:
                        print '[y/N]:'
                        continue

                if delete:
                    os.remove(outputMergedFilename)
                else:
                    print 'Skipping dataset ' + dataset
                    continue
    
        # find all files that have some contents
        inputPaths = []
        inputFiles = []
        for fileName in os.listdir(inputPath + '/' + dataset):
            if not fileName.endswith('.root'):
                continue
    
            fullPath = inputPath + '/' + dataset + '/' + fileName
            if os.path.getsize(inputPath + '/' + dataset + '/' + fileName) > 4:
                inputPaths.append(fullPath)
                inputFiles.append(fileName)
            else:
                print ' WARNING -- empty root file skipped: ' + fullPath

        print 'Merging files from dataset ' + dataset
        if debug:
            print ' Files:'
            print '  ' + ' '.join(sorted(inputFiles))

        proc = subprocess.Popen(['hadd', '-f7', outputMergedFilename] + inputPaths, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
        out, err = proc.communicate()

        if debug and out.strip():
            print out
        if err.strip():
            sys.stderr.write(err)
            sys.stderr.flush()

        if not os.path.exists(outputMergedFilename):
            print 'Failed to create ' + outputMergedFilename
            continue

        if not local:
            shutil.copy(outputMergedFilename, outputMergedFilename.replace(writePath, outputPath, 1))

if __name__ == '__main__':
    #===================================================================================================
    # Main Program
    #===================================================================================================
    from argparse import ArgumentParser
    
    argParser = ArgumentParser(description = 'Merge output files of given datasets')
    argParser.add_argument('--InputPath', '-i', metavar = 'PATH', dest = 'inputPath', required = True, help = 'Path of dataset directories')
    argParser.add_argument('--OutputPath', '-o', metavar = 'PATH', dest = 'outputPath', required = True, help = 'Output directory')
    argParser.add_argument('--Dataset', '-d', metavar = 'DATASET', dest = 'dataset', nargs = '+', default = [], help = 'Space-delimited list of datasets')
    argParser.add_argument('--Skim', '-s', metavar = '<skim|noskim>', dest = 'skim', nargs = '?', default = '', help = 'Skim suffix if present')
    argParser.add_argument('--FilenameHeader', '-f', metavar = 'PREFIX', dest = 'filenameHeader', required = True, help = 'Prefix of the output files')

    argParser.add_argument('--overwrite', '-R', action = 'store_true', dest = 'overwrite', help = 'Overwrite existing output files')
    argParser.add_argument('--debug', '-D', action = 'store_true', dest = 'debug')
    
    args = argParser.parse_args()
    sys.argv = []
    
    # Here is where it all happens
    MergeFilesets(args.inputPath, args.outputPath, args.filenameHeader, args.dataset, skim = args.skim, overwrite = args.overwrite, debug = args.debug)
