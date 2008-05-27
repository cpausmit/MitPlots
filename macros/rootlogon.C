// $Id: rootlogon.C 2637 2006-03-06 23:53:38Z loizides $

{
  if(1) {
    if(gSystem->Getenv("CMSSW_VERSION")) {
      if(gSystem->Load("libFWCoreFWLite.so")==0) {
        AutoLibraryLoader::enable();
        //AutoLibraryLoader::loadAll();

        ::Info("rootlogon.C", 
               "Setting up for %s", gSystem->Getenv("CMSSW_VERSION"));
      } 

      if(1) {
        TString str = gSystem->GetMakeSharedLib();
        if(str.Contains("-m32")==0 && str.Contains("-m64")==0) {
          str.ReplaceAll("g++", "g++ -m32");
          gSystem->SetMakeSharedLib(str);
        }
      }
    }
  }

  gROOT->Macro("$CMSSW_BASE/src/MitAna/macros/setRootEnv.C+");
}
