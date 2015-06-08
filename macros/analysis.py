from argparse import ArgumentParser
import sys
import os

argParser = ArgumentParser(description = 'Run BAMBU analysis')
argParser.add_argument('config', metavar = 'CONFIG')
argParser.add_argument('--file', '-f', metavar = 'INPUT', dest = 'inputFile')
argParser.add_argument('--output', '-o', metavar = 'FILENAME', dest = 'outputFile')
argParser.add_argument('--nentries', '-n', metavar = 'N', dest = 'nentries', type = int, default = 0)
argParser.add_argument('--cacher', '-c', action = 'store_true', dest = 'useCacher')
argParser.add_argument('--no-hierarchy', '-a', action = 'store_true', dest = 'anarchy')

args = argParser.parse_args()
sys.argv = []

from MitAna.TreeMod.bambu import mithep, analysis

if args.inputFile:
    analysis.AddFile(args.inputFile)

if args.outputFile:
    analysis.SetOutputName(args.outputFile)

execfile(args.config)

if args.nentries > 0:
    analysis.SetProcessNEvents(args.nentries)

if args.useCacher:
    analysis.SetUseCacher(1)

if args.anarchy:
    analysis.SetKeepHierarchy(False)

analysis.Run(False)
