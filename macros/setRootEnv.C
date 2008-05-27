// $Id: setRootEnv.C 4721 2007-11-14 18:01:08Z loizides $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TEnv.h>
#include <TString.h>
#include <TSystem.h>
#include <TRegexp.h>
#include <TROOT.h>
#include <TFile.h>
#include <TClass.h>
#include <TClassTable.h>
#include <TInterpreter.h>
#include <TRandom3.h>
#include <TError.h>
#include <TStyle.h>
#endif

void setRootEnv()
{
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/ -I$CMSSW_BASE/src/MitAna/TreeMod/inc");
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/MitAna/macros");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/MitAna/TreeMod/inc");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/MitAna/macros");
  gROOT->SetMacroPath(TString(gROOT->GetMacroPath())
                       +TString(gSystem->Getenv("CMSSW_BASE"))+"/src/MitAna/macros");

  if (1) { // load libs
    TDirectory::TContext context(0); // automatically restore gDirectory
    if(1) {

      TString libstr(Form("%s/lib/%s",
                          gSystem->Getenv("CMSSW_BASE"),
                          gSystem->Getenv("SCRAM_ARCH")));

      void *dir = gSystem->OpenDirectory(libstr.Data());
      if(1) {
        TRegexp re("libMitAna*.so", kTRUE); 
        TRegexp reignore("libMitAnalysis*.so", kTRUE); 
        while(const char *direntry=gSystem->GetDirEntry(dir) ) {
          TString sdirentry(direntry); 
          if (sdirentry.Index(re) == kNPOS) {
            continue;
          }
          if (sdirentry.Index(reignore) != kNPOS) {
            continue;
          }
          Int_t len=strlen(direntry)-3;
          if(len<=0) continue;
          char *tmpstr = new char[len+1];
          for(Int_t i=0;i<len;i++) tmpstr[i]=direntry[i];
          tmpstr[len]='\0';
          if (gInterpreter->IsLoaded(tmpstr))  {
            if (gDebug) Warning("setRootEnv","Trying to load \"%s\", but it is already loaded", tmpstr);
          } else {
            if(gSystem->Load(tmpstr)<0) {
              gROOT->Error("setRootEnv", "could not load \"%s\" for use in ACLiC", tmpstr);
            } else {
              if(gDebug) Info("setRootEnv","Loaded \"%s\" and its dependencies", tmpstr);
            }
          }
          delete[] tmpstr;
        }
        gSystem->FreeDirectory(dir);
      }
    }

    if(0) { // set some common gStyle settings
      gStyle->SetPalette(1,0);

      gStyle->SetPadColor(0);
      gStyle->SetPadBorderSize(0);
      gStyle->SetPadBorderMode(0);
      gStyle->SetCanvasColor(0);
      gStyle->SetCanvasBorderMode(0);
      gStyle->SetCanvasBorderSize(0);
      gStyle->SetFrameBorderMode(0);
      gStyle->SetFrameLineColor(0);
      gStyle->SetTitleColor(0);
      gStyle->SetTitleBorderSize(0);
    }

    if(1) { // set a better default random generator
      delete gRandom;
      gRandom = new TRandom3;
      gRandom->SetSeed(0);
    }

    if (gClassTable->GetID("mithep::Particle") >= 0) {
      ::Info("setRootEnv", "Welcome to MITROOT!\n");
    }
  }
}
