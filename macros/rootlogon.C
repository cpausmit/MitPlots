{
  // ------------------------------------------------------------------------------------------------
  //
  // Root logon for MIT analysis
  // 
  // It is important to note that we are not loading any shared library explicitely but we rely on
  // the compiler for the macro you execute to do that for us. In this way the minimum amount of
  // libraries are being loaded and the resulting shared library file has all libraries created such
  // that they are not hardmounted to a directory. This is un-important if you are working on a
  // cluster with common home (ex. NFS) but if you want to transplant the job in another system it
  // becomes crucial.
  //
  // ------------------------------------------------------------------------------------------------
  // To see what is happening behind the scenes use this
  gDebug = kFALSE;

#if defined(__CINT__) && !defined(__MAKECINT__)
  // Loads all default libraries
  gROOT->Macro("$CMSSW_BASE/src/MitAna/macros/setRootEnv.C+");
#endif

  // Maintain the direcories and libraries we need to use for root internal compilation
  TString str = gSystem->GetMakeSharedLib();
  str = str + TString(" -L$CMSSW_BASE/lib/$SCRAM_ARCH");
  str = str + TString(" -L$CMSSW_BASE/external/$SCRAM_ARCH/lib");
  str = str + TString(" -lMitAnaCatalog -lMitAnaDataCont -lMitAnaDataTree -lMitAnaDataUtil");
  str = str + TString(" -lMitAnaPhysicsMod -lMitAnaTAM -lMitAnaTreeMod -lMitAnaUtils");
  str = str + TString(" -lMitAnaValidation");
  str = str + TString(" -lMitPhysicsMods -lMitPhysicsSelMods");
  str = str + TString(" -lMitMonoJetMods -lMitMonoJetSelMods");
  gSystem->SetMakeSharedLib(str);

  // Make sure we have all include files
  gSystem->AddIncludePath("-I/home/paus/cms/external/include");
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  gSystem->AddIncludePath("-I$CMSSW_RELEASE_BASE/src/");
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/MitAna/macros");
  
  gInterpreter->AddIncludePath(TString("/cvmfs/cms.cern.ch/")+TString(gSystem->Getenv("SCRAM_ARCH"))+
			       TString("/lcg/roofit/5.32.00/include"));
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+TString("/src/"));
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_RELEASE_BASE"))+TString("/src/"));
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+
			       TString("/src/MitAna/TreeMod/interface"));
  
  gROOT->SetMacroPath(TString(gROOT->GetMacroPath())+TString(gSystem->Getenv("CMSSW_BASE"))+
		      TString("/src/MitAna/macros"));
}
