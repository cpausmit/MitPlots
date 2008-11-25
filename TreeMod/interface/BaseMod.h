//--------------------------------------------------------------------------------------------------
// $Id: BaseMod.h,v 1.8 2008/09/28 02:34:14 loizides Exp $
//
// BaseMod
//
// This TAM module is the base module for all our TAM modules. It defines a couple of useful
// getters to retrieve information from the underlying framework code, such as the EventHeader,
// RunInfo or Trigger information.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_BASEMOD_H
#define MITANA_TREEMOD_BASEMOD_H

#include "MitAna/TAM/interface/TAModule.h" 
#include "MitAna/TreeMod/interface/Selector.h"
#include "MitAna/DataTree/interface/Collections.h"  
#include "MitAna/DataTree/interface/TriggerName.h" 
#include "MitAna/DataTree/interface/TriggerObject.h" 

namespace mithep 
{
  class Selector;

  class BaseMod : public TAModule {
    public:
      BaseMod(const char *name="BaseMod", const char *title="Base analysis module") 
        : TAModule(name,title), fNEventsProcessed(0) {}
      ~BaseMod() {}

    protected:
      void                        IncNEventsProcessed()       { ++fNEventsProcessed; }
      Int_t                       GetNEventsProcessed() const { return fNEventsProcessed; }

      const EventHeader          *GetEventHeader()      const { return GetSel()->GetEventHeader(); }
      const TriggerObjectCol     *GetHLTObjects(const char *name)                    const;
      const TriggerObjectsTable  *GetHLTObjectsTable(const char *hltfwk="HLTFwkMod") const;
      const TriggerTable         *GetHLTTable(const char *hltfwk="HLTFwkMod")        const;
      const RunInfo              *GetRunInfo()          const { return GetSel()->GetRunInfo(); }
      const Selector             *GetSel()              const;
      Bool_t                      HasHLTInfo(const char *hltfwk="HLTFwkMod")         const;
      Bool_t                      ValidRunInfo()        const { return GetSel()->ValidRunInfo(); } 
      void                        SaveNEventsProcessed(const char *name="hDEvents");

    private:
      Int_t                       fNEventsProcessed; 	//number of events

    ClassDef(BaseMod,1) // Base TAM module
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::TriggerObjectCol *mithep::BaseMod::GetHLTObjects(const char *name) const
{
  // Get pointer to HLT TriggerObjects collection with given name for the current event.

  return (dynamic_cast<const TriggerObjectCol *>(FindObjThisEvt(name)));
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Selector *mithep::BaseMod::GetSel() const 
{ 
  // Get pointer to selector.

  return static_cast<const Selector*>(GetSelector()); 
}
#endif
