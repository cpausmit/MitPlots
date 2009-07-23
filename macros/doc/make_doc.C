// $Id: make_doc.C,v 1.7 2009/07/20 13:49:27 loizides Exp $

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
#include <TDocInfo.h>
#endif

class MyHtml : public THtml
{
  public:
    class MyModDef: public TModuleDefinition {
    public:
      bool GetModule(TClass* cl, TString& out_modulename) const {
        TString cn(cl->GetName());
        if (!cn.BeginsWith("mithep") && !cn.BeginsWith("TAM")) {
          return 0;
          //return TModuleDefinition::GetModule(cl, out_modulename);
        }
        TString tmp(cl->GetDeclFileName());
        Ssiz_t fst = tmp.Index("/Mit")+1;
        Ssiz_t snd = tmp.Index("/",tmp.Index("/",fst)+1);
        out_modulename = tmp(fst,snd-fst);
        return 1;
      }

      ClassDef(MyModDef, 0) // MyModDef class for BAMBU module definition
    };

    MyHtml() 
    {
      MyModDef m;
      SetModuleDefinition(m);
    }
    void SetIncludePath(const char *p) { fPathInfo.fIncludePath=p; }
    void GetModuleNameForClass(TString& module, TClass* cl) const
    {
      module = "NOTUSED";
        TString cn(cl->GetName());
      if (!cn.BeginsWith("mithep") && !cn.BeginsWith("TAM")) {
        return;
      }
      TString tmp(cl->GetDeclFileName());
      Ssiz_t fst = tmp.Index("/Mit")+1;
      Ssiz_t snd = tmp.Index("/",tmp.Index("/",fst)+1);
      module = tmp(fst,snd-fst);
      return;
    }

    void RunAll(Bool_t force, const char *filter) 
    {
      CreateListOfClasses(filter);
      TModuleDocInfo* module = 
        dynamic_cast<TModuleDocInfo*>(GetListOfModules()->FindObject("MitCommon"));
      if (module)
        module->SetSelected();
      THtml::MakeAll(force,filter);
    }

  ClassDef(MyHtml, 0) // MyHtml class for BAMBU docu
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

  TString cb(gSystem->ExpandPathName("$CMSSW_BASE"));
  h.SetInputDir("$CMSSW_BASE/src:$ROOTSYS/include");
  h.SetIncludePath(Form("%s/src/",cb.Data()));
  h.SetClassDocTag("//------------------------------------------------------------");
  h.SetViewCVS("http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/");
  h.SetRootURL("http://root.cern.ch/root/html522");
  h.RunAll(0,"(mithep::|TAM)");
}
