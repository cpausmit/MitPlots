//--------------------------------------------------------------------------------------------------
// $Id: BaseMod.h,v 1.2 2008/06/18 19:08:14 loizides Exp $
//
// Selector
//
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

#ifndef TREEMOD_SELECTOR_H
#define TREEMOD_SELECTOR_H

#include "MitAna/TAM/interface/TAModule.h" 
#include "MitAna/TAM/interface/TAMSelector.h" 

namespace mithep {
  class Selector : public TAMSelector
  {
    public:
      Selector();
      ~Selector();
   
      //void              Init(TTree* tree);
      //Bool_t            Notify();
      //Bool_t            Process(Long64_t entry);
      //void              SlaveBegin(TTree* tree);
      //void              SlaveTerminate();
      // void              Terminate();
   
      ClassDef(Selector,1)
  };
}
#endif
