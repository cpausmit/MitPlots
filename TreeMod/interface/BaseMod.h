//--------------------------------------------------------------------------------------------------
// $Id: BaseMod.h,v 1.9 2008/11/25 15:57:49 loizides Exp $
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
      const EventHeader          *GetEventHeader()      const { return GetSel()->GetEventHeader(); }
      const TriggerObjectCol     *GetHLTObjects(const char *name)                    const;
      const TriggerObjectsTable  *GetHLTObjectsTable(const char *hltfwk="HLTFwkMod") const;
      const TriggerTable         *GetHLTTable(const char *hltfwk="HLTFwkMod")        const;
      Int_t                       GetNEventsProcessed() const { return fNEventsProcessed; }
      template <class T> T       *GetObjThisEvt(const char *name);
      template <class T> T       *GetPublicObj(const char *name);
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
template <class T> 
inline T *mithep::BaseMod::GetObjThisEvt(const char *name)
{
  // Get published object for the current event.

  T *ret = dynamic_cast<T*>(FindObjThisEvt(name));
  if (!ret) {
    SendError(kWarning, "GetObjThisEvent", 
              "Could not obtain object with name %s and type %s for current event!",
              name, T::Class_Name());
  }
  return ret;
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline T *mithep::BaseMod::GetPublicObj(const char *name)
{
  // Get public object.

  T *ret = dynamic_cast<T*>(FindPublicObj(name));
  if (!ret) {
    SendError(kWarning, "GetPublicObject", 
              "Could not obtain public object with name %s and type %s!",
              name, T::Class_Name());
  }
  return ret;
}

//--------------------------------------------------------------------------------------------------
inline const mithep::Selector *mithep::BaseMod::GetSel() const 
{ 
  // Get pointer to selector.

  return static_cast<const Selector*>(GetSelector()); 
}
#endif
