//--------------------------------------------------------------------------------------------------
// $Id: PublisherMod.h,v 1.4 2008/12/10 17:25:16 loizides Exp $
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

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

namespace mithep 
{
  template<class T>
  class PublisherMod : public BaseMod 
  {
    public:
      PublisherMod(const char *name="PublisherMod", 
                   const char *title="Publisher module");
      ~PublisherMod() {}

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
      const Collection<T>     *fColIn;         //!pointer to collection (in) 
      ObjArray<T>             *fColOut;        //!pointer to collection (out)

      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      ClassDefT(PublisherMod, 1) // Publisher module
  };
}

//--------------------------------------------------------------------------------------------------
template<class T>
mithep::PublisherMod<T>::PublisherMod(const char *name, const char *title) : 
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
template<class T>
void mithep::PublisherMod<T>::Process()
{
  // Load the branch, add pointers to the object array. Publish object array if needed.

  LoadBranch(GetBranchName());
  if (fPubPerEvent)
    fColOut = new mithep::ObjArray<T>(0, GetPublicName());
  else
    fColOut->Reset();

  UInt_t entries = fColIn->GetEntries();
  for(UInt_t i=0; i<entries; ++i)
    fColOut->Add(fColIn->At(i));

  if (fPubPerEvent) 
    AddObjThisEvt(fColOut);
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::PublisherMod<T>::SlaveBegin()
{
  // Request the branch to be published. Depending on the user's decision publish the array.

  ReqBranch(GetBranchName(), fColIn);

  if (fPublicName.IsNull())
    fPublicName = fBranchName;

  if (!GetPubPerEvent()) {
    fColOut = new mithep::ObjArray<T>(0, GetPublicName());
    PublishObj(fColOut);
  }
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::PublisherMod<T>::SlaveTerminate()
{
  // Cleanup in case objects are published only once.

  if (!fPubPerEvent) {
    RetractObj(GetPublicName());
    delete fColOut;
  }
}
#endif
