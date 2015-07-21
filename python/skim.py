from MitAna.TreeMod.bambu import mithep, analysis
from MitPlots.Tools.Skimmer import skimmer

tree0p0 = mithep.TreeContainer()
tree0p0.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_0p0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_105505/150719_085520/0000/")

skimmer0p0 = skimmer
skimmer0p0.SetInputTree(tree0p0.ReturnTree())
skimmer0p0.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim0p0.root")
skimmer0p0.DoSkim()

tree1p0 = mithep.TreeContainer()
tree1p0.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_1p0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_110544/150719_090555/0000")

skimmer1p0 = skimmer
skimmer1p0.SetInputTree(tree1p0.ReturnTree())
skimmer1p0.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim1p0.root")
skimmer1p0.DoSkim()

tree1p5 = mithep.TreeContainer()
tree1p5.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_1p5/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_110620/150719_090630/0000")

skimmer1p5 = skimmer
skimmer1p5.SetInputTree(tree1p5.ReturnTree())
skimmer1p5.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim1p5.root")
skimmer1p5.DoSkim()

tree2p0 = mithep.TreeContainer()
tree2p0.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_2p0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_110748/150719_090800/0000")

skimmer2p0 = skimmer
skimmer2p0.SetInputTree(tree2p0.ReturnTree())
skimmer2p0.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim2p0.root")
skimmer2p0.DoSkim()

tree2p5 = mithep.TreeContainer()
tree2p5.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_2p5/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_110900/150719_090911/0000")

skimmer2p5 = skimmer
skimmer2p5.SetInputTree(tree2p5.ReturnTree())
skimmer2p5.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim2p5.root")
skimmer2p5.DoSkim()

tree3p0 = mithep.TreeContainer()
tree3p0.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_3p0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_110955/150719_091007/0000")

skimmer3p0 = skimmer
skimmer3p0.SetInputTree(tree3p0.ReturnTree())
skimmer3p0.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim3p0.root")
skimmer3p0.DoSkim()

tree3p5 = mithep.TreeContainer()
tree3p5.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_3p5/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_111024/150719_091036/0000")

skimmer3p5 = skimmer
skimmer3p5.SetInputTree(tree3p5.ReturnTree())
skimmer3p5.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim3p5.root")
skimmer3p5.DoSkim()

tree4p0 = mithep.TreeContainer()
tree4p0.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_4p0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_111907/150719_091919/0000")

skimmer4p0 = skimmer
skimmer4p0.SetInputTree(tree4p0.ReturnTree())
skimmer4p0.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim4p0.root")
skimmer4p0.DoSkim()

tree5p0 = mithep.TreeContainer()
tree5p0.AddDirectory("root://eoscms.cern.ch//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalMIBI/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_noMuon_JEC_ptFw_5p0/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_20150719_111119/150719_091129/0000")

skimmer5p0 = skimmer
skimmer5p0.SetInputTree(tree5p0.ReturnTree())
skimmer5p0.SetOutputFileName("/scratch/dabercro/PUPPETSkims/skim5p0.root")
skimmer5p0.DoSkim()

del tree5p0
del tree4p0
del tree3p5
del tree3p0
del tree2p5
del tree2p0
del tree1p5
del tree1p0
del tree0p0

del skimmer5p0
del skimmer4p0
del skimmer3p5
del skimmer3p0
del skimmer2p5
del skimmer2p0
del skimmer1p5
del skimmer1p0
del skimmer0p0
