// $Id: make_doc.C,v 1.1 2009/07/16 13:13:55 loizides Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include <fstream>
#include <TError.h>
#include <THashList.h>
#include <THtml.h>
#include <TList.h>
#include <TNamed.h>
#include <TRegexp.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TDirectory.h>
#include <TString.h>
#include <TPRegexp.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TEnv.h>
#include <THtml.h>
#endif

class MyHtml : public THtml
{
  public:
    MyHtml() {} 
    void SetIncludePath(const char *p) { fPathInfo.fIncludePath=p; }

  ClassDef(MyHtml, 0);
};

void load_libs(const char *ln)
{
  TDirectory::TContext context(0); // automatically restore gDirectory
  TRegexp re(Form("lib%s*.so", ln), true);
  TString lpath(gSystem->ExpandPathName("$CMSSW_BASE/lib/$SCRAM_ARCH"));
  void *dir = gSystem->OpenDirectory(lpath);
  if(!dir) return;
  while(const char *file = gSystem->GetDirEntry(dir)) {
    TString s(file);
    if (s.Index(re) == kNPOS)
      continue;
    ::Info("make_doc","Loading %s", file);
    gSystem->Load(file);
  }
  gSystem->FreeDirectory(dir);
}

void make_doc()
{
  MyHtml h;
  h.SetProductName("MitRoot");

  // load our libraries
  load_libs("MitCommon");
  load_libs("MitAna");
  load_libs("MitPhysics");

  h.SetInputDir("$CMSSW_BASE/src") ;
  h.SetIncludePath(Form("%s/src/",gSystem->ExpandPathName("$CMSSW_BASE")));
  h.SetClassDocTag("//------------------------------------------------------------");
  h.SetViewCVS("http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/");
  h.MakeAll(1,"mithep::Particle");
}

