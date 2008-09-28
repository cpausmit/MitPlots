//--------------------------------------------------------------------------------------------------
// $Id: HLTExampleMod.h,v 1.10 2008/09/10 03:33:28 loizides Exp $
//
// HLTExampleAnaMod
//
// This TAM module shows how to use the HLTMod module. It produces the pt- and 
// eta- distributions for trigger objects corresponding for a given trigger
// object name.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_HLTEXAMPLEMOD_H
#define MITANA_TREEMOD_HLTEXAMPLEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;

namespace mithep 
{
  class HLTExampleMod : public BaseMod 
  {
    public:
      HLTExampleMod(const char *name="HLTExampleMod", 
                    const char *title="HLT example module");
      ~HLTExampleMod() {}

      void         SetTrigObjsName(const char *n) { fObjsName=n; }

    protected:
      TString      fObjsName;   //name of trigger objects
      TH1D        *fPtHist;     //!pt histogram
      TH1D        *fEtaHist;    //!eta histogram

      void         Process();
      void         SlaveBegin();

      ClassDef(HLTExampleMod,1) // HLT example analysis module
  };
}
#endif
