from MitAna.TreeMod.bambu import mithep

skimmer = mithep.Skimmer()
skimmer.AddBranch("recoilPFPuppiMet_Pt");
skimmer.AddBranch("recoilPFPuppiMet_PerpZ");
skimmer.AddBranch("recoilPFPuppiMet_LongZ");
skimmer.AddBranch("Boson_Pt");
skimmer.AddBranch("Boson_daughter");
skimmer.AddBranch("NVertex");
