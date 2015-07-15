from MitAna.TreeMod.bambu import mithep, analysis
import ROOT
ROOT.gROOT.SetBatch(True)

ROOT.gSystem.Load('libMitPlotsContainer.so')
ROOT.gSystem.Load('libMitPlotsPlot.so')

leg = mithep.LegendContainer()

trees = mithep.TreeContainer()
trees.SetPrinting(True)
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEtaAll_NoPtCut.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEtaAll_PtCut.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEtaAll_bin2p2_NoPtCut.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEtaAll_bin2p2_PtCut.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEta2p5_0p3.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEta2p5_0p5.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEta2p5_0p6.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEta2p5_0p3_noCharge.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEta2p5_0p4_noCharge.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEta2p5_0p5_noCharge.root")
trees.AddFile("root://eoscms.cern.ch//store/user/rgerosa/PUPPETAnalysis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Asympt50ns_MCRUN2_74_V9A_puppiEta2p5_0p6_noCharge.root")

plotter = mithep.PlotResolution()
plotter.SetExprX("NVertex")
plotter.SetDefaultWeight("Boson_daughter==13 && Boson_Pt>30")
plotter.SetDefaultExprRes("recoilPFPuppiMet_LongZ+Boson_Pt")

plotter.SetTreeList(trees.ReturnTreeList("PUPPET/t"))

leg.AddEntry("#eta = All, no p_{T} cut",1)
leg.AddEntry("#eta = All, p_{T} cut",2)
leg.AddEntry("#eta = All, bin 2.2, no p_{T} cut",1)
leg.AddEntry("#eta = All, bin 2.2, p_{T} cut",1)
leg.AddEntry("#eta = 2.5, cone = 0.3",1)
leg.AddEntry("#eta = 2.5, cone = 0.5",1)
leg.AddEntry("#eta = 2.5, cone = 0.6",1)
leg.AddEntry("#eta = 2.5, cone = 0.3, #alpha_{F}",1)
leg.AddEntry("#eta = 2.5, cone = 0.4, #alpha_{F}",1)
leg.AddEntry("#eta = 2.5, cone = 0.5, #alpha_{F}",1)
leg.AddEntry("#eta = 2.5, cone = 0.6, #alpha_{F}",1)

print "Making resolution plot."
ResolutionCanvas = plotter.MakeCanvas(leg,"NPV","Resolution [GeV]",
                                      20,5,25,50,-100,100,2,10.,20.,False)

plotter.SetDefaultExprRes("recoilPFPuppiMet_LongZ/-Boson_Pt")
print "Making response plot."
ResponseCanvas = plotter.MakeCanvas(leg,"NPV","Response",
                                    20,5,25,50,-100,100,1,0.5,1.5,False)

ResolutionCanvas.SaveAs("testResolution.png")
ResponseCanvas.SaveAs("testResponse.png")

del trees
del plotter
del leg
