import sys
from argparse import ArgumentParser

argParser = ArgumentParser(description = 'Run BAMBU analysis')
argParser.add_argument('analysisCfg', metavar = 'ANALYSIS')
argParser.add_argument('--book', '-b', metavar = 'BOOK', dest = 'book')
argParser.add_argument('--dataset', '-d', metavar = 'DATASET', dest = 'dataset')
argParser.add_argument('--fileset', '-s', metavar = 'FILESET', dest = 'fileset')

args = argParser.parse_args()
sys.argv = []

import ROOT
ROOT.gROOT.SetBatch(True)

ROOT.gSystem.Load('libMitAnaTreeMod.so')

mithep = ROOT.mithep

analysis = mithep.Analysis()

catalog = mithep.Catalog('catalog')
dataset = catalog.FindDataset(args.book, args.dataset, args.fileset, 1)
analysis.AddDataset(dataset)
analysis.SetOutputName(args.dataset + '_' + args.fileset + '.root')
analysis.SetUseCacher(1)
analysis.SetKeepHierarchy(True)

execfile(args.analysisCfg)

analysis.Run(False)
