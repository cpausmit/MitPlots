//--------------------------------------------------------------------------------------------------
// $Id: SimpleTable.h,v 1.1 2009/01/23 07:34:34 loizides Exp $
//
// MyHtml
//
// Simple extension to THtml class. To be able to bugfix THtml a copy of all files from ROOT 
// are added (which obviously are not totally compliant with our coding conventions:
//  TClassDocOutput.h  
//  TDocDirective.h  
//  TDocInfo.h  
//  TDocOutput.h  
//  TDocParser.h  
//  THtml.h
//
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_UTILS_MYHTML_H
#define MITANA_UTILS_MYHTML_H

#include "THtml.h"
#include "TDocInfo.h"

class MyHtml : public THtml
{
  public:
    class MyModDef: public TModuleDefinition {
    public:
      using TModuleDefinition::GetModule;
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

    void GetModuleNameForClass(TString& module, TClass* cl) const override
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
#endif
