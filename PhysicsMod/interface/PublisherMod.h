//--------------------------------------------------------------------------------------------------
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

#include <type_traits>

namespace mithep {

  template<class TIn, class TOut = TIn>
  class PublisherMod : public BaseMod {
  public:
    PublisherMod(const char *name="PublisherMod", const char *title="Publisher module");

    const char* GetInputName()               const { return fInputName;      }
    const char* GetBranchName()              const { return GetInputName();  }
    const char* GetOutputName()              const { return fOutputName;     }
    const char* GetPublicName()              const { return GetOutputName(); }
    Bool_t      GetPubPerEvent()             const { return fPubPerEvent;    }
    void        SetBranchName(const char *n)       { fInputName = n;         }
    void        SetInputName(const char *n)        { SetBranchName(n);       }
    void        SetOutputName(const char *n)       { fOutputName = n;        }
    void        SetPublicName(const char *n)       { SetOutputName(n);       }
    void        SetPublishPerEvent(Bool_t b)       { fPubPerEvent = b;       }
    void        PublishPerEvent(Bool_t b)          { SetPublishPerEvent(b);  }

  protected:
    typedef mithep::Collection<TIn> InputColType;
    // this class is instantiatable only when TOut is a base class of TIn
    typedef std::enable_if<std::is_base_of<TOut, TIn>::value, mithep::ObjArray<TOut>> Instantiable;
    typedef typename Instantiable::type OutputColType;

    TString fInputName;    //name of collection
    TString fOutputName;    //name of collection
    Bool_t  fPubPerEvent;   //=true then publish per event (def=1)

    OutputColType* fColOut;  //!pointer to collection (out)
  
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    ClassDef(PublisherMod, 1) // Publisher module
  };

}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
mithep::PublisherMod<TIn, TOut>::PublisherMod(const char *name, const char *title) : 
  BaseMod(name, title),
  fInputName(""),
  fOutputName(""),
  fPubPerEvent(kTRUE),
  fColOut(0)
{
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void
mithep::PublisherMod<TIn, TOut>::Process()
{
  // Load the branch, add pointers to the object array. Publish object array if needed.
  auto* input = GetObject<InputColType>(fInputName);

  if (fPubPerEvent)
    fColOut = new OutputColType(input->GetEntries(), fOutputName);
  else
    fColOut->Reset();

  for (UInt_t iO = 0; iO != input->GetEntries(); ++iO)
    fColOut->Add(input->At(iO));

  if (fPubPerEvent) 
    AddObjThisEvt(fColOut);
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void
mithep::PublisherMod<TIn, TOut>::SlaveBegin()
{
  if (fInputName.IsNull())
    SendError(kAbortAnalysis, "SlaveBegin", "Input name is null.");

  if (fOutputName.IsNull())
    SendError(kAbortAnalysis, "SlaveBegin", "Output name is null.");

  if (!fPubPerEvent) {
    fColOut = new OutputColType(0, fOutputName);
    PublishObj(fColOut);
  }
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void
mithep::PublisherMod<TIn, TOut>::SlaveTerminate()
{
  // Cleanup in case objects are published only once.

  if (!fPubPerEvent) {
    RetractObj(fOutputName);
    delete fColOut;
  }
}

#endif
