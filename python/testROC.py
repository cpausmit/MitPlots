from MitAna.TreeMod.bambu import mithep, analysis

# This is stuff from github.com/dabercro/MitCrombie # # # # # # # # # # # # # # # # # # # # # # # #
SignalTree     = mithep.TreeContainer("/scratch/dabercro/boostedv-v9/skims/BDT_Signal.root")      #
BackgroundTree = mithep.TreeContainer("/scratch/dabercro/boostedv-v9/skims/BDT_Background.root")  #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 

CleanCut = "&& bdt_noMass > -100 && fjet1MassTrimmed > 70"

plotter = mithep.PlotROC(
    SignalTree     = SignalTree.ReturnTree("DMSTree"),          # Any other way to pass a pointer
    BackgroundTree = BackgroundTree.ReturnTree("DMSTree"),      #   to a tree also works
    SignalCut      = "weight*(abs(fjet1PartonId)==23||abs(fjet1PartonId)==24)"+CleanCut,
    BackgroundCut  = "weight*(abs(fjet1PartonId)!=23&&abs(fjet1PartonId)!=24)"+CleanCut,
)

plotter.AddVar("bdt_all")              # Variables over which the ROC curves are made
plotter.AddVar("bdt_noMass")

plotter.AddLegendEntry("All",1)        # Order should match the variable input
plotter.AddLegendEntry("No Mass",2)    #   (Legend Entry, Color, LineSize=2, LineStyle=1) effectively
plotter.SetLegendLimits(0.15,0.85,0.5,0.6)

plotter.MakeCanvas("testROC")  # outputs testROC.C, testROC.png, and testROC.pdf

del plotter
del SignalTree
del BackgroundTree
