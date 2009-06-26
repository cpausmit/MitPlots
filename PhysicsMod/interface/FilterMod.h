//--------------------------------------------------------------------------------------------------
// $Id: FilterMod.h,v 1.4 2009/06/17 11:50:27 loizides Exp $
//
// FilterMod
//
// This module simply loads a branch and --dependent on kinematical cuts-- publishes its content 
// into an ObjArray. 
// Using PublisherPerEvent() one can chose whether the array will be published
// globally (ie only in SlaveBegin) or on per-event basis.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_FILTERMOD_H
#define MITANA_PHYSICSMOD_FILTERMOD_H

#include "MitAna/DataCont/interface/Collection.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/TreeMod/interface/BaseMod.h" 
#include <TH1D.h>

namespace mithep 
{
  template<class TIn, class TOut=TIn>
  class FilterMod : public BaseMod 
  {
    public:
      FilterMod(const char *name="FilterMod", 
                const char *title="Filter module");

      const char              *GetColName()              const { return fColName;        }
      Double_t                 GetEtaMin()               const { return fEtaMin;         }
      Double_t                 GetEtaMax()               const { return fEtaMax;         }
      const char              *GetInputName()            const { return GetColName();    }
      const char              *GetOutputName()           const { return GetPublicName(); }
      const char              *GetPublicName()           const { return fPublicName;     }
      Bool_t                   GetPubPerEvent()          const { return fPubPerEvent;    }
      Double_t                 GetPtMin()                const { return fPtMin;          }
      Double_t                 GetPtMax()                const { return fPtMax;          }
      void                     PublishPerEvent(Bool_t b)       { fPubPerEvent = b;       }
      void                     SetColName(const char *n)       { fColName=n;             }
      void                     SetEntriesMax(Int_t e)          { fEntriesMax = e;        }
      void                     SetEtaMax(Double_t e)           { fEtaMax = e;            }
      void                     SetEtaMin(Double_t e)           { fEtaMin = e;            }
      void                     SetInputName(const char *n)     { SetColName(n);          }
      void                     SetOutputName(const char *n)    { SetPublicName(n);       }
      void                     SetPtMax(Double_t pt)           { fPtMax = pt;            }
      void                     SetPtMin(Double_t pt)           { fPtMin = pt;            }
      void                     SetPublicName(const char *n)    { fPublicName=n;          }

    protected:
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      TString                  fColName;     //name of collection
      TString                  fPublicName;  //name of collection
      Bool_t                   fPubPerEvent; //=true then publish per event (def=1)
      Double_t                 fPtMin;       //minimum pt
      Double_t                 fPtMax;       //maximum pt
      Double_t                 fEtaMin;      //minimum eta
      Double_t                 fEtaMax;      //maximum eta 
      Int_t                    fEntriesMax;  //maximum number of entries
      const Collection<TIn>   *fColIn;       //!pointer to collection (in) 
      ObjArray<TOut>          *fColOut;      //!pointer to collection (out)
      TH1D                    *fPtHist;      //!pt histogram
      TH1D                    *fEtaHist;     //!eta histogram
      TH1D                    *fEntHist1;    //!entries histogram
      TH1D                    *fEntHist2;    //!entries histogram

      ClassDef(FilterMod, 1) // Filter module
  };
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
mithep::FilterMod<TIn, TOut>::FilterMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fColName("SetMe"),
  fPublicName(""),
  fPubPerEvent(kTRUE),
  fPtMin(1),
  fPtMax(1000),
  fEtaMin(-10),
  fEtaMax(10),
  fEntriesMax(250),
  fColIn(0),
  fColOut(0),
  fPtHist(0),
  fEtaHist(0),
  fEntHist1(0),
  fEntHist2(0)
{
  // Constructor.

  SetFillHist(kTRUE);
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void mithep::FilterMod<TIn, TOut>::Process()
{
  // Load the branch, add pointers to the object array. Publish object array if needed.

  if (!LoadEventObject(GetColName(), fColIn)) {
    SendError(kAbortModule, "Process", "Could not load data!");
    return;
  }

  const UInt_t ents=fColIn->GetEntries();

  if (fPubPerEvent)
    fColOut = new mithep::ObjArray<TOut>(ents, GetPublicName());
  else
    fColOut->Reset();

  for(UInt_t i=0;i<ents;++i) {
     const TIn *p = fColIn->At(i);
     Double_t pt = p->Pt();
     if (pt<fPtMin) 
       continue;
     if (pt>fPtMax)
       continue;
     Double_t eta = p->Eta();
     if (eta<fEtaMin)
       continue;
     if (eta>fEtaMax)
       continue;
     
     fColOut->Add(p);
     if (GetFillHist()) {
       fPtHist->Fill(pt);
       fEtaHist->Fill(eta);
     }
  }

  if (GetFillHist()) {
    fEntHist1->Fill(ents);
    fEntHist2->Fill(fColOut->GetEntries());
  }

  if (fPubPerEvent) 
    AddObjThisEvt(fColOut);
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void mithep::FilterMod<TIn, TOut>::SlaveBegin()
{
  // Request the branch to be published. Depending on the user's decision publish the array.

  ReqEventObject(GetColName(), fColIn, kTRUE);

  if (fPublicName.IsNull())
    fPublicName = GetColName();

  if (!GetPubPerEvent()) {
    fColOut = new mithep::ObjArray<TOut>(0, GetPublicName());
    PublishObj(fColOut);
  }

  if (GetFillHist()) {
    Int_t ptbins = (Int_t)((fPtMax-fPtMin)/2.5);
    AddTH1(fPtHist,"hPtHist",";p_{t} [GeV];#",ptbins,fPtMin,fPtMax);
    Int_t etabins = (Int_t)((fEtaMax-fEtaMin)/0.1);
    AddTH1(fEtaHist,"hEtaHist",";#eta;#",etabins,fEtaMin,fEtaMax);
    AddTH1(fEntHist1,"hEntriesBeforeCuts",";#entries;#",fEntriesMax,-0.5,fEntriesMax-0.5);
    AddTH1(fEntHist2,"hEntriesAfterCuts",";#entries;#",fEntriesMax,-0.5,fEntriesMax-0.5);
  }
}

//--------------------------------------------------------------------------------------------------
template<class TIn, class TOut>
void mithep::FilterMod<TIn, TOut>::SlaveTerminate()
{
  // Cleanup in case objects are published only once.

  if (!fPubPerEvent) {
    RetractObj(GetPublicName());
    delete fColOut;
  }
}
#endif
