// $Id: runGenRelVal.C,v 1.1 2008/11/25 13:58:52 loizides Exp $

void runGenRelVal(const char *files = "mit-gen_000.root")
{
  gROOT->Macro("$CMSSW_BASE/src/MitAna/macros/setRootEnv.C+");
  gSystem->Load("$CMSSW_BASE/lib/slc4_ia32_gcc345/libMitAnaValidation.so");

  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 0;

  // set up the modules
  GenRelValMod *mod = new GenRelValMod;
  mod->SetWrite(1);
  mod->SetPrint(0);

  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(mod);
  ana->SetUseHLT(0);
  ana->AddFile(files);

  // run the analysis after successful initialisation
  ana->Run(0);
}
