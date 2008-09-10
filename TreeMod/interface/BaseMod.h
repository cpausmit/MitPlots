//--------------------------------------------------------------------------------------------------
// $Id: BaseMod.h,v 1.6 2008/07/03 08:22:18 loizides Exp $
//
// BaseMod
//
// This TAM module is the base module for all our TAM modules.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_BASEMOD_H
#define MITANA_TREEMOD_BASEMOD_H

#include "MitAna/TAM/interface/TAModule.h" 
#include "MitAna/TreeMod/interface/Selector.h" 

namespace mithep 
{
  class Selector;

  class BaseMod : public TAModule {
    public:
      BaseMod(const char *name="BaseMod", const char *title="Base analysis module") 
        : TAModule(name,title) {}
      ~BaseMod() {}

    protected:
      const EventHeader   *GetEventHeader()    const { return GetSel()->GetEventHeader(); }
      const RunInfo       *GetRunInfo()        const { return GetSel()->GetRunInfo(); }
      const Selector      *GetSel()            const;
      Bool_t               ValidRunInfo()      const { return GetSel()->ValidRunInfo(); } 

    ClassDef(BaseMod,1) // Base TAM module
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Selector *mithep::BaseMod::GetSel() const 
{ 
  return static_cast<const Selector*>(GetSelector()); 
}
#endif
