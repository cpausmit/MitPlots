//--------------------------------------------------------------------------------------------------
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

#include <TObjString.h>
#include "MitAna/TAM/interface/TAModule.h" 
#include "MitAna/TreeMod/interface/Selector.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h" 
#include "MitAna/DataCont/interface/ObjArray.h"

namespace mithep 
{
  class HLTFwkMod;
  class TriggerObjectsTable;
  class TriggerTable;

  class BaseMod : public TAModule {
  public:
    enum ETrigType { kHLT, kL1A, kL1T };
    BaseMod(const char *name="BaseMod", const char *title="Base analysis module");

    Bool_t GetFillHist()         const { return fFillHist;    }
    void   SetFillHist(Bool_t b)       { fFillHist = b;       }
    Int_t  GetNEventsProcessed() const { return fNEventsProc; }

  protected:
    void                        AddEventObject(const char *name, Bool_t fromBr = kTRUE);
    template <class T> void     AddTH1(T *&ptr, const char *name, const char *title, 
                                       Int_t nbins, Double_t xmin, Double_t xmax);
    template <class T> void     AddTH2(T *&ptr, const char *name, const char *title, 
                                       Int_t nbinsx, Double_t xmin, Double_t xmax,
                                       Int_t nbinsy, Double_t ymin, Double_t ymax);
    template <class T> void     AddTH3(T *&ptr, const char *name, const char *title, 
                                       Int_t nbinsx, Double_t xmin, Double_t xmax,
                                       Int_t nbinsy, Double_t ymin, Double_t ymax,
                                       Int_t nbinsz, Double_t zmin, Double_t zmax);
    void                        AddToTrash(TObject *obj);
    const EventHeader          *GetEventHeader()      const { return GetSel()->GetEventHeader(); }
    const HLTFwkMod            *GetHltFwkMod()        const { return fHltFwkMod;                 }
    const TriggerObjectCol     *GetHLTObjects(const char *name) const;
    const TriggerObjectsTable  *GetHLTObjectsTable()            const;
    const TriggerTable         *GetHLTTable()                   const;
    const TriggerTable         *GetL1AlgoTable()                const;
    const TriggerTable         *GetL1TechTable()                const;
    template <class T> const T *GetColThisEvt(const char *name, Bool_t warn=1);
    template <class T> const T *GetObjThisEvt(const char *name, Bool_t warn=1) const;
    template <class T> T       *GetObjThisEvt(const char *name, Bool_t warn=1);
    template <class T> const T *GetPublicObj(const char *name, Bool_t warn=1)  const;
    template <class T> T       *GetPublicObj(const char *name, Bool_t warn=1);
    const RunInfo              *GetRunInfo()          const { return GetSel()->GetRunInfo();     }
    const MCRunInfo            *GetMCRunInfo()        const { return GetSel()->GetMCRunInfo();   }
    const TriggerTable         *GetTriggerTable(ETrigType t)    const;
    const Selector             *GetSel()              const;
    Bool_t                      HasHLTInfo()          const;
    void                        IncNEventsProcessed()       { ++fNEventsProc;                    }
    template <class T> T*       GetObject(char const* name, Bool_t warn = kTRUE);
    template <class T> Bool_t   LoadEventObject(char const* name, T const*&, Bool_t warn = kTRUE);
    template <class T> void     ReqBranch(char const* bname, const T *&addr);
    template <class T> void     ReqEventObject(char const* name, T const*&);
    template <class T> void     ReqEventObject(char const* name, T const*&, Bool_t fromBr);
    void                        SaveNEventsProcessed(const char *name="hDEvents");
    Bool_t                      ValidRunInfo()        const { return GetSel()->ValidRunInfo();   }
    Bool_t                      ValidMCRunInfo()      const { return GetSel()->ValidMCRunInfo(); }

  private:
    Bool_t                      fFillHist;            //=true then fill histos (def=0)
    THashTable                  fEvtObjBrNames;       //names of per-event objects
    mutable const HLTFwkMod    *fHltFwkMod;           //!pointer to HLTFwdMod
    const TString               fHltFwkModName;       //!name of HLTFwkMod
    Int_t                       fNEventsProc;         //!number of events

    ClassDef(BaseMod, 1) // Base TAM module
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::BaseMod::AddEventObject(const char *name, Bool_t fromBr)
{
  // Add event object to list of objects that should be retrieved from a branch rather
  // than from a pointer given by the event.

  if (fEvtObjBrNames.FindObject(name)) {
    SendError(kWarning, Form("AddEventObject (\"%s\")",GetName()), 
              "Can not add event object with name \"\"%s\"\" and type %d",
              name, fromBr);
    return;
  }

  fEvtObjBrNames.Add(new Selector::ObjInfo(name, Selector::ObjInfo::kBranch));
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline void mithep::BaseMod::AddTH1(T *&ptr, const char *name, const char *title, 
                                    Int_t nbins, Double_t xmin, Double_t xmax)
{
  // Create ROOT histogram and add it to the output list.

  ptr = new T(name, title, nbins, xmin, xmax);
  ptr->Sumw2();
  AddOutput(ptr);
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline void mithep::BaseMod::AddTH2(T *&ptr, const char *name, const char *title, 
                                    Int_t nbinsx, Double_t xmin, Double_t xmax,
                                    Int_t nbinsy, Double_t ymin, Double_t ymax)
{
  // Create ROOT histogram and add it to the output list.

  ptr = new T(name, title, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
  ptr->Sumw2();
  AddOutput(ptr);
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline void mithep::BaseMod::AddTH3(T *&ptr, const char *name, const char *title, 
                                    Int_t nbinsx, Double_t xmin, Double_t xmax,
                                    Int_t nbinsy, Double_t ymin, Double_t ymax,
                                    Int_t nbinsz, Double_t zmin, Double_t zmax)
{
  // Create ROOT histogram and add it to the output list.

  ptr = new T(name, title, nbinsx, xmin, xmax, nbinsy, ymin, ymax, nbinsz, zmin, zmax);
  ptr->Sumw2();
  AddOutput(ptr);
}

//--------------------------------------------------------------------------------------------------
inline void mithep::BaseMod::AddToTrash(TObject *obj)
{
  // Add object to trash. Trash will be emptied after an entry of the tree was processed.

  Selector *sel = const_cast<Selector*>(GetSel()); 
  sel->AddToTrash(obj);
}

//--------------------------------------------------------------------------------------------------
template <class T> 
const T *mithep::BaseMod::GetColThisEvt(const char*, Bool_t)
{
  SendError(kWarning, "GetColThisEvt", "This function is deprecated. Use GetObject instead.");
  return 0;
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline const T *mithep::BaseMod::GetObjThisEvt(const char *name, Bool_t warn) const
{
  // Get published object for the current event.

  T *ret = dynamic_cast<T*>(FindObjThisEvt(name));
  if (!ret && warn) {
    SendError(kWarning, Form("GetObjThisEvt (\"%s\")",GetName()), 
              "Could not obtain object with name \"%s\" and type \"%s\" for current event!",
              name, T::Class_Name());
  }
  return ret;
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline T *mithep::BaseMod::GetObjThisEvt(const char *name, Bool_t warn)
{
  // Get published object for the current event.

  T *ret = dynamic_cast<T*>(FindObjThisEvt(name));
  if (!ret && warn) {
    SendError(kWarning, Form("GetObjThisEvt (\"%s\")",GetName()), 
              "Could not obtain object with name \"%s\" and type \"%s\" for current event!",
              name, T::Class_Name());
  }
  return ret;
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline const T *mithep::BaseMod::GetPublicObj(const char *name, Bool_t warn) const
{
  // Get public object.


  T *ret = dynamic_cast<T*>(FindPublicObj(name));
  if (!ret && warn) {
    SendError(kWarning, Form("GetPublicObject (\"%s\")",GetName()),  
              "Could not obtain public object with name \"%s\" and type \"%s\"!",
              name, T::Class_Name());
  }
  return ret;
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline T *mithep::BaseMod::GetPublicObj(const char *name, Bool_t warn)
{
  // Get public object.

  T *ret = dynamic_cast<T*>(FindPublicObj(name));
  if (!ret && warn) {
    SendError(kWarning, Form("GetPublicObject (\"%s\")",GetName()),
              "Could not obtain public object with name \"%s\" and type \"%s\"!",
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

//--------------------------------------------------------------------------------------------------
inline const mithep::TriggerObjectCol *mithep::BaseMod::GetHLTObjects(const char *name) const
{
  // Get pointer to HLT TriggerObjects collection with given name for the current event.

  return (dynamic_cast<const TriggerObjectCol *>(FindObjThisEvt(name)));
}

template <class T>
inline
T*
mithep::BaseMod::GetObject(char const* name, Bool_t warn/* = kTRUE*/)
{
  if (GetSelector())
    return static_cast<Selector*>(GetSelector())->GetObject<T>(name, warn);

  SendError(kAbortAnalysis, "GetObject", "fSelector is null in module [%s]", GetName());
  return 0;
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline Bool_t mithep::BaseMod::LoadEventObject(const char *name, const T *&addr, Bool_t warn)
{
  // Obtain the object with the specified name that has been requested during processing. 
  // In case name is found in fEvtObjBrNames it will be read from a branch to the 
  // address specified in ReqEventObject.

  TString type("event");
  auto* info = static_cast<Selector::ObjInfo*>(fEvtObjBrNames.FindObject(name));
  if (info && info->fSourceType == Selector::ObjInfo::kBranch) {
    type = "branch";
    LoadBranch(name);
  }
  else {
    addr = GetObjThisEvt<T>(name);
  }

  if (addr)
    return kTRUE;

  if (warn) {
    SendError(kWarning, Form("LoadEventObject (\"%s\")",GetName()), 
              "Could not obtain object with name \"%s\" and type \"%s\" from \"%s\"!",
              name, T::Class_Name(), type.Data());
  }

  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void mithep::BaseMod::ReqBranch(const char *bname, const T *&addr)
{
  // Requests that the branch with the specified name is made available during processing and that
  // it be read in to the address specified.

  TAModule::ReqBranch(bname, const_cast<T*&>(addr));
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void mithep::BaseMod::ReqEventObject(const char *name, const T *&addr)
{
  // Requests that the object with the specified name is made available
  // during processing. In case name is found in fEvtObjBrNames it 
  // will be read from a branch to the address specified.

  auto* info = static_cast<Selector::ObjInfo*>(fEvtObjBrNames.FindObject(name));
  if (!info || info->fSourceType != Selector::ObjInfo::kBranch)
    return;

  ReqBranch(name, addr);
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void mithep::BaseMod::ReqEventObject(const char *name, const T *&addr, Bool_t fromBr)
{
  // Requests that the object with the specified name is made available
  // during processing. In case name is found in fEvtObjBrNames it 
  // will be read from a branch to the address specified. If "fromBr" is
  // kTRUE then add the event to the list of events needed to be retrieved
  // from a branch.

  auto* info = static_cast<Selector::ObjInfo*>(fEvtObjBrNames.FindObject(name));
  if (!info && fromBr)
    AddEventObject(name, fromBr);

  ReqEventObject(name, addr);
}
#endif
