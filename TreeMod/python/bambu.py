import ROOT
ROOT.gROOT.SetBatch(True)

ROOT.gSystem.Load('libMitAnaTreeMod.so')

mithep = ROOT.mithep

analysis = mithep.Analysis()
