from MitAna.TreeMod.bambu import mithep, analysis
import ROOT
ROOT.gROOT.SetBatch(True)

ROOT.gSystem.Load('libMitPlotsContainer.so')

test = mithep.TreeContainer()
test.AddDirectory("/scratch/dabercro","mumugamma")

tree = test.ReturnTree()
