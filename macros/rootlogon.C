// $Id: rootlogon.C,v 1.1 2008/05/27 19:59:54 loizides Exp $

{
  if (gSystem->Getenv("CMSSW_VERSION")) {
    TString str = gSystem->GetMakeSharedLib();
    if (str.Contains("-m32")==0 && str.Contains("-m64")==0) {
      str.ReplaceAll("g++", "g++ -m32");
      gSystem->SetMakeSharedLib(str);
    }
  }
  
  gROOT->Macro("$CMSSW_BASE/src/MitAna/macros/setRootEnv.C+");
}
