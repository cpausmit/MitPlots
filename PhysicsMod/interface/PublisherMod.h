//--------------------------------------------------------------------------------------------------
// $Id: PublisherMod.h,v 1.9 2009/06/15 15:00:16 loizides Exp $
//
// PublisherMod
//
// This module simply loads a branch and publishes its content into an ObjArray. 
// Using PublisherPerEvent() one can chose whether the array will be published
// globally (ie only in SlaveBegin) or on per-event basis.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_PUBLISHERMOD_H
#define MITANA_PHYSICSMOD_PUBLISHERMOD_H

#include "MitAna/DataCont/interface/Collection.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/TreeMod/interface/BaseMod.h" 

namespace mithep 
{
  template<class TIn, class TOut=TIn>
  class PublisherMod : public BaseMod 
  {
    public:
      PublisherMod(const char *name="PublisherMod", 
                   const char *title="Publisher module");

      const char              *GetBranchName()              const { return fBranchName;     }
      const char              *GetInputName()               const { return GetBranchName(); }
      const char              *GetOutputName()              const { return GetPublicName(); }
      const char              *GetPublicName()              const { return fPublicName;     }
      Bool_t                   GetPubPerEvent()             const { return fPubPerEvent;    }
      void                     SetBranchName(const char *n)       { fBranchName=n;          }
      void                     SetInputName(const char *n)        { SetBranchName(n);       }
      void                     SetOutputName(const char *n)       { SetPublicName(n);       }
      void                     SetPublicName(const char *n)       { fPublicName=n;          }
      void                     PublishPerEvent(Bool_t b)          { fPubPerEvent = b;       }

    protected:
      TString                  fBranchName;    //name of collection
      TString                  fPublicName;    //name of collection
      Bool_t                   fPubPerEvent;   //=true then publish per event (def=1)
      const Collection<TIn>   *fColIn;         //!pointer to collection (in) 
      ObjArray<TOut>          *fColOut;        //!pointer to collection (out)

      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      ClassDef(PublisherMod, 1) // Publisher module
  };
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
mithep::PublisherMod<TIn, TOut>::PublisherMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fBranchName("SetMe"),
  fPublicName(""),
  fPubPerEvent(kTRUE),
  fColIn(0),
  fColOut(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void mithep::PublisherMod<TIn, TOut>::Process()
{
  // Load the branch, add pointers to the object array. Publish object array if needed.

  LoadBranch(GetBranchName());
  if (fPubPerEvent)
    fColOut = new mithep::ObjArray<TOut>(0, GetPublicName());
  else
    fColOut->Reset();

  UInt_t entries = fColIn->GetEntries();
  for(UInt_t i=0; i<entries; ++i)
    fColOut->Add(fColIn->At(i));

  if (fPubPerEvent) 
    AddObjThisEvt(fColOut);
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void mithep::PublisherMod<TIn, TOut>::SlaveBegin()
{
  // Request the branch to be published. Depending on the user's decision publish the array.

  ReqBranch(GetBranchName(), fColIn);

  if (fPublicName.IsNull())
    fPublicName = GetBranchName();

  if (!GetPubPerEvent()) {
    fColOut = new mithep::ObjArray<TOut>(0, GetPublicName());
    PublishObj(fColOut);
  }
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void mithep::PublisherMod<TIn, TOut>::SlaveTerminate()
{
  // Cleanup in case objects are published only once.

  if (!fPubPerEvent) {
    RetractObj(GetPublicName());
    delete fColOut;
  }
}
#endif
