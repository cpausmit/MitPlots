//--------------------------------------------------------------------------------------------------
// $Id: BaseMod.h,v 1.17 2009/04/07 15:56:37 phedex Exp $
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
  class HLTFwkMod;

  class BaseMod : public TAModule {
    public:
      BaseMod(const char *name="BaseMod", const char *title="Base analysis module");

    protected:
      template <class T> void     AddTH1(T *&ptr, const char *name, const char *title, 
                                         Int_t nbins, Double_t xmin, Double_t xmax);
      template <class T> void     AddTH2(T *&ptr, const char *name, const char *title, 
                                         Int_t nbinsx, Double_t xmin, Double_t xmax,
                                         Int_t nbinsy, Double_t ymin, Double_t ymax);
      template <class T> void     AddTH3(T *&ptr, const char *name, const char *title, 
                                         Int_t nbinsx, Double_t xmin, Double_t xmax,
                                         Int_t nbinsy, Double_t ymin, Double_t ymax,
                                         Int_t nbinsz, Double_t zmin, Double_t zmax);
      void                        IncNEventsProcessed()       { ++fNEventsProc; }
      const EventHeader          *GetEventHeader()      const { return GetSel()->GetEventHeader(); }
      Bool_t                      GetFillHist()         const { return fFillHist; }
      const HLTFwkMod            *GetHltFwkMod()        const { return fHltFwkMod; }
      const TriggerObjectCol     *GetHLTObjects(const char *name) const;
      const TriggerObjectsTable  *GetHLTObjectsTable()            const;
      const TriggerTable         *GetHLTTable()                   const;
      Int_t                       GetNEventsProcessed()           const { return fNEventsProc; }
      template <class T> const T *GetObjThisEvt(const char *name, Bool_t warn=1) const;
      template <class T> T       *GetObjThisEvt(const char *name, Bool_t warn=1);
      template <class T> const T *GetPublicObj(const char *name, Bool_t warn=1)  const;
      template <class T> T       *GetPublicObj(const char *name, Bool_t warn=1);
      const RunInfo              *GetRunInfo()          const { return GetSel()->GetRunInfo(); }
      const Selector             *GetSel()              const;
      Bool_t                      HasHLTInfo()          const;
      template <class T> void     ReqBranch(const char *bname, const T *&address);
      Bool_t                      ValidRunInfo()        const { return GetSel()->ValidRunInfo(); } 
      void                        SaveNEventsProcessed(const char *name="hDEvents");
      void                        SetFillHist(Bool_t b)       { fFillHist = b; }

    private:
      Bool_t                      fFillHist;            //=true then fill histos (def=0)
      mutable const HLTFwkMod    *fHltFwkMod;           //!pointer to HLTFwdMod
      const TString               fHltFwkModName;       //!name of HLTFwkMod
      Int_t                       fNEventsProc;         //!number of events

    ClassDef(BaseMod, 1) // Base TAM module
  };
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
inline void mithep::BaseMod::ReqBranch(const char *bname, const T *&address)
{
  // Requests that the branch with the specified name be made available
  // during processing and that it be read in to the address specified.

  TAModule::ReqBranch(bname, const_cast<T*&>(address));
}
#endif
