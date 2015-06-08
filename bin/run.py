#!/usr/bin/env python

import sys
import os
import subprocess
from argparse import ArgumentParser

argParser = ArgumentParser(description = 'Run BAMBU analysis')
argParser.add_argument('analysisCfg', metavar = 'ANALYSIS')
argParser.add_argument('--book', '-b', metavar = 'BOOK', dest = 'book')
argParser.add_argument('--dataset', '-d', metavar = 'DATASET', dest = 'dataset')
argParser.add_argument('--fileset', '-s', metavar = 'FILESET', dest = 'fileset')

args = argParser.parse_args()
sys.argv = []

workdir = os.path.dirname(os.path.realpath(__file__))

from taskenv import SCRAM_ARCH, CMSSW_RELEASE

os.environ['SCRAM_ARCH'] = SCRAM_ARCH

proc = subprocess.Popen('source /cvmfs/cms.cern.ch/cmsset_default.sh; scram project CMSSW ' + CMSSW_RELEASE, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
out, err = proc.communicate()
print out
if err.strip():
    sys.stderr.write(err)
    sys.stderr.flush()

if proc.returncode != 0:
    sys.exit(proc.returncode)

proc = subprocess.Popen(['tar', 'xzf', 'libraries.tar.gz'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
out, err = proc.communicate()
print out
if err.strip():
    sys.stderr.write(err)
    sys.stderr.flush()

os.mkdir('catalog')
proc = subprocess.Popen(['tar', 'xzf', '-C', 'catalog', 'catalogs.tar.gz'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
out, err = proc.communicate()
print out
if err.strip():
    sys.stderr.write(err)
    sys.stderr.flush()

sys.path = os.environ['PYTHONPATH'].split(':')

import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gSystem.AddDynamicPath(CMSSW_RELEASE + '/lib/' + SCRAM_ARCH)

ROOT.gSystem.Load('libMitAnaTreeMod.so')

mithep = ROOT.mithep

analysis = mithep.Analysis()

catalog = mithep.Catalog('catalog')
dataset = catalog.FindDataset(args.book, args.dataset, args.fileset, 1)
analysis.AddDataset(dataset)
analysis.SetOutputName(dataset + '_' + fileset + '.root')
analysis.SetUseCacher(1)
analysis.SetKeepHierarchy(True)

execfile(args.analysisCfg)

analysis.Run(False)
