from MitAna.TreeMod.bambu import mithep, analysis
from MitPlots.Container.PUPPETSkim import puppetSkimTree

tree0p0 = puppetSkimTree
tree0p0.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_0p0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_105505/150719_085520/0000")
tree0p0.MakeFile("/scratch/dabercro/PUPPETSkims/skimPF.root")

del tree0p0
