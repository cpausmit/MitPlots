from MitAna.TreeMod.bambu import mithep, analysis
import ROOT
ROOT.gROOT.SetBatch(True)

ROOT.gSystem.Load('libMitPlotsContainer.so')
ROOT.gSystem.Load('libMitPlotsPlot.so')

leg = mithep.LegendContainer()

trees = mithep.TreeContainer()
trees.SetPrinting(True)
trees.AddFile("/scratch/dabercro/puppiEtaAll_NoPtCut.root")
trees.AddFile("/scratch/dabercro/puppiEtaAll_PtCut.root")
trees.AddFile("/scratch/dabercro/puppiEtaAll_bin2p2_NoPtCut.root")
trees.AddFile("/scratch/dabercro/puppiEtaAll_bin2p2_PtCut.root")
trees.AddFile("/scratch/dabercro/puppiEta2p5_0p3.root")
trees.AddFile("/scratch/dabercro/puppiEta2p5_0p5.root")
trees.AddFile("/scratch/dabercro/puppiEta2p5_0p6.root")
trees.AddFile("/scratch/dabercro/puppiEta2p5_0p3_noCharge.root")
trees.AddFile("/scratch/dabercro/puppiEta2p5_0p4_noCharge.root")
trees.AddFile("/scratch/dabercro/puppiEta2p5_0p5_noCharge.root")
trees.AddFile("/scratch/dabercro/puppiEta2p5_0p6_noCharge.root")

plotter = mithep.PlotResolution()
plotter.SetExprX("NVertex")
plotter.SetDefaultWeight("Boson_daughter==13 && Boson_Pt>30")
plotter.SetDefaultExprRes("recoilPFPuppiMet_LongZ+Boson_Pt")

plotter.SetLineWidth(1)
plotter.SetTreeList(trees.ReturnTreeList("t"))

leg.AddEntry("eta = All, no p_{T} cut",1)
leg.AddEntry("eta = All, p_{T} cut",2)
leg.AddEntry("eta = All, bin 2.2, no p_{T} cut",3)
leg.AddEntry("eta = All, bin 2.2, p_{T} cut",4)
leg.AddEntry("eta = 2.5, cone = 0.3",5)
leg.AddEntry("eta = 2.5, cone = 0.5",6)
leg.AddEntry("eta = 2.5, cone = 0.6",7)
leg.AddEntry("eta = 2.5, cone = 0.3, alpha_{F}",8)
leg.AddEntry("eta = 2.5, cone = 0.4, alpha_{F}",9)
leg.AddEntry("eta = 2.5, cone = 0.5, alpha_{F}",11)
leg.AddEntry("eta = 2.5, cone = 0.6, alpha_{F}",25)

print "Making resolution plot."
ResolutionCanvas = plotter.MakeCanvas(leg,"NPV","Resolution [GeV]",
                                      20,5,25,50,-100,100,2,10.,40.,False)

print ResolutionCanvas
ResolutionCanvas.SaveAs("testResolution.C")
ResolutionCanvas.SaveAs("testResolution.pdf")
ResolutionCanvas.SaveAs("testResolution.png")

plotter.SetDefaultExprRes("recoilPFPuppiMet_LongZ/-Boson_Pt")
print "Making response plot."
plotter.SetParameterLimits(1,0.5,1.2)
ResponseCanvas = plotter.MakeCanvas(leg,"NPV","Response",
                                      20,5,25,50,-5,5,1,0.,2.,False)

print ResponseCanvas
ResponseCanvas.SaveAs("testResponse.C")
ResponseCanvas.SaveAs("testResponse.pdf")
ResponseCanvas.SaveAs("testResponse.png")

del trees
del plotter
del leg
