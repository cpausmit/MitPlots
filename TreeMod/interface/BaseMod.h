//--------------------------------------------------------------------------------------------------
// $Id: BaseMod.h,v 1.20 2009/06/11 08:59:32 loizides Exp $
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

#include <TObjString.h>
#include "MitAna/TAM/interface/TAModule.h" 
#include "MitAna/TreeMod/interface/Selector.h"
#include "MitAna/DataTree/interface/TriggerObjectFwd.h" 

namespace mithep 
{
  class HLTFwkMod;
  class TriggerObjectsTable;
  class TriggerTable;

  class BaseMod : public TAModule {
    public:
      BaseMod(const char *name="BaseMod", const char *title="Base analysis module");

    private:
      class ObjType : public TObjString {
        public:
          ObjType(const char *name="", Bool_t br=kTRUE) : TObjString(name), fBr(br) {}
          ~ObjType() {}
          Bool_t  IsBranch() const { return fBr; }
        protected:
          Bool_t  fBr; //=true then object is from branch
      };

    protected:
      void                        AddEventObject(const char *name, Bool_t fromBr=kTRUE);
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
      Bool_t                      GetFillHist()         const { return fFillHist;                  }
      const HLTFwkMod            *GetHltFwkMod()        const { return fHltFwkMod;                 }
      const TriggerObjectCol     *GetHLTObjects(const char *name) const;
      const TriggerObjectsTable  *GetHLTObjectsTable()            const;
      const TriggerTable         *GetHLTTable()                   const;
      Int_t                       GetNEventsProcessed()           const { return fNEventsProc;     }
      template <class T> const T *GetObjThisEvt(const char *name, Bool_t warn=1) const;
      template <class T> T       *GetObjThisEvt(const char *name, Bool_t warn=1);
      template <class T> const T *GetPublicObj(const char *name, Bool_t warn=1)  const;
      template <class T> T       *GetPublicObj(const char *name, Bool_t warn=1);
      const RunInfo              *GetRunInfo()          const { return GetSel()->GetRunInfo();     }
      const Selector             *GetSel()              const;
      Bool_t                      HasHLTInfo()          const;
      void                        IncNEventsProcessed()       { ++fNEventsProc;                    }
      template <class T> Bool_t   LoadEventObject(const char *name, const T *&addr, Bool_t warn=1);
      template <class T> void     ReqBranch(const char *bname, const T *&addr);
      template <class T> void     ReqEventObject(const char *name, const T *&addr);
      template <class T> void     ReqEventObject(const char *name, const T *&addr, Bool_t fromBr);
      void                        SaveNEventsProcessed(const char *name="hDEvents");
      void                        SetFillHist(Bool_t b)       { fFillHist = b;                     }
      Bool_t                      ValidRunInfo()        const { return GetSel()->ValidRunInfo();   } 

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
    SendError(kWarning, "AddEventObject", 
              "Can not add event object with name %s and type %d",
              name, fromBr);
    return;
  }

  fEvtObjBrNames.Add(new ObjType(name,fromBr));
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
inline const mithep::TriggerObjectCol *mithep::BaseMod::GetHLTObjects(const char *name) const
{
  // Get pointer to HLT TriggerObjects collection with given name for the current event.

  return (dynamic_cast<const TriggerObjectCol *>(FindObjThisEvt(name)));
}

//--------------------------------------------------------------------------------------------------
template <class T> 
inline const T *mithep::BaseMod::GetObjThisEvt(const char *name, Bool_t warn) const
{
  // Get published object for the current event.

  T *ret = dynamic_cast<T*>(FindObjThisEvt(name));
  if (!ret && warn) {
    SendError(kWarning, "GetObjThisEvent", 
              "Could not obtain object with name %s and type %s for current event!",
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
    SendError(kWarning, "GetObjThisEvent", 
              "Could not obtain object with name %s and type %s for current event!",
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
    SendError(kWarning, "GetPublicObject", 
              "Could not obtain public object with name %s and type %s!",
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

//--------------------------------------------------------------------------------------------------
template <class T>
inline Bool_t mithep::BaseMod::LoadEventObject(const char *name, const T *&addr, Bool_t warn)
{
  // Obtain the object with the specified name that has been requested during processing. 
  // In case name is found in fEvtObjBrNames it will be read from a branch to the 
  // address specified in ReqEventObject.

  TString type("event");
  ObjType *o = static_cast<ObjType*>(fEvtObjBrNames.FindObject(name));
  if (o && o->IsBranch()) {
    type = "branch";
    LoadBranch(name);
  } else {
    addr = GetObjThisEvt<T>(name);
  }

  Bool_t ret = (addr!=0); 
  if (!ret && warn) {
    SendError(kWarning, "LoadEventObject", 
              "Could not obtain object with name %s and type %s from %s!",
              name, T::Class_Name(), type.Data());
  }

  return ret;
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void mithep::BaseMod::ReqBranch(const char *bname, const T *&addr)
{
  // Requests that the branch with the specified name is made available
  // during processing and that it be read in to the address specified.

  TAModule::ReqBranch(bname, const_cast<T*&>(addr));
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void mithep::BaseMod::ReqEventObject(const char *name, const T *&addr)
{
  // Requests that the object with the specified name is made available
  // during processing. In case name is found in fEvtObjBrNames it 
  // will be read from a branch to the address specified.

  ObjType *o = static_cast<ObjType*>(fEvtObjBrNames.FindObject(name));
  if (!o || !o->IsBranch())
    return;

  ReqBranch(name, addr);
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void mithep::BaseMod::ReqEventObject(const char *name, const T *&addr, Bool_t fromBr)
{
  // Requests that the object with the specified name is made available
  // during processing. In case name is found in fEvtObjBrNames it 
  // will be read from a branch to the address specified.

  ObjType *o = static_cast<ObjType*>(fEvtObjBrNames.FindObject(name));
  if (!o && fromBr)
    AddEventObject(name, fromBr);

  ReqEventObject(name, addr);
}
#endif
