// $Id: rootlogon.C,v 1.1 2009/07/16 13:13:55 loizides Exp $
{ 
  if (gSystem->Getenv("CMSSW_VERSION")) {
    TString str = gSystem->GetMakeSharedLib();
    if (str.Contains("-m32")==0 && str.Contains("-m64")==0) {
      str.ReplaceAll("g++", "g++ -m32");
      gSystem->SetMakeSharedLib(str);
    }
  }

  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/MitAna/TreeMod/inc");
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/MitAna/macros");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+
			       "/src/MitAna/TreeMod/interface");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/MitAna/macros");
  gROOT->SetMacroPath(TString(gROOT->GetMacroPath())
                      +TString(gSystem->Getenv("CMSSW_BASE"))+"/src/MitAna/macros");

  gROOT->ProcessLine(".L $CMSSW_BASE/src/MitAna/macros/doc/make_doc.C+");

  // load our libraries
  load_libs("MitCommon");
  load_libs("MitAna");
  load_libs("MitPhysics");

  gROOT->ProcessLine(".x $CMSSW_BASE/src/MitAna/macros/doc/make_doc.C+");
}
