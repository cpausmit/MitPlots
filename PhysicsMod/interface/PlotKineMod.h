//--------------------------------------------------------------------------------------------------
// $Id: PlotKineMod.h,v 1.2 2008/12/04 13:52:27 loizides Exp $
//
// PlotKineMod
// 
// This module allows one to quickly plot eta and pt distribution of a given particle.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_PLOTKINEMOD_H
#define MITANA_PHYSICSMOD_PLOTKINEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"
#include <TH1D.h>

namespace mithep 
{
  template<class T>
  class PlotKineMod : public BaseMod 
  {
    public:
      PlotKineMod(const char *name="PlotKineMod", 
                  const char *title="Plot kinematics module");
      ~PlotKineMod() {}

      const char              *GetColName()              const { return fColName; }
      Double_t                 GetEtaMin()               const { return fEtaMin;  }
      Double_t                 GetEtaMax()               const { return fEtaMax;  }
      Double_t                 GetPtMin()                const { return fPtMin;   }
      Double_t                 GetPtMax()                const { return fPtMax;   }
      Bool_t                   GetLoadBranch()           const { return fLoadBr;  }
      void                     SetColName(const char *n)       { fColName=n;      }
      void                     SetEtaMin(Double_t e)           { fEtaMin = e;     }
      void                     SetEtaMax(Double_t e)           { fEtaMax = e;     }
      void                     SetLoadBranch(Bool_t b)         { fLoadBr = b;     }
      void                     SetPtMin(Double_t pt)           { fPtMin = pt;     }
      void                     SetPtMax(Double_t pt)           { fPtMax = pt;     }

    protected:
      Bool_t                   Load();
      void                     Process();
      void                     SlaveBegin();

      TString                  fColName;    //name of collection
      Double_t                 fPtMin;      //minimum pt
      Double_t                 fPtMax;      //maximum pt
      Double_t                 fEtaMin;     //minimum eta
      Double_t                 fEtaMax;     //maximum eta 
      Bool_t                   fLoadBr;     //=true then load branch (def=1)
      const Collection<T>     *fCol;        //!pointer to collection 
      TH1D                    *fPtHist;     //!pt histogram
      TH1D                    *fEtaHist;    //!eta histogram
      TH1D                    *fMassHist;   //!mass histogram
      TH1D                    *fMtHist;     //!mt histogram

      ClassDefT(PlotKineMod,1) // Plot kinematics module
  };
}

//--------------------------------------------------------------------------------------------------
template<class T>
mithep::PlotKineMod<T>::PlotKineMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fColName("SetMe"),
  fPtMin(1),
  fPtMax(5000),
  fEtaMin(-10),
  fEtaMax(10),
  fLoadBr(kTRUE),
  fCol(0),
  fPtHist(0),
  fEtaHist(0)
{
  // Constructor.

  this->SetFillHist(1);
}

//--------------------------------------------------------------------------------------------------
template<class T>
Bool_t mithep::PlotKineMod<T>::Load()
{
  // Load data from branch or get pointer from event.

  if (GetLoadBranch())
    LoadBranch(GetColName());
  else
    fCol = GetObjThisEvt<Collection<T> >(GetColName());

  return (fCol!=0);
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::PlotKineMod<T>::Process()
{
  // Process entries of the tree: Just load the branch and fill the histograms.

  if (!Load()) {
    this->SendError(kAbortModule, "Process", "Could not load data!");
    return;
  }

  if (!GetFillHist())
    return;
    
  UInt_t ents=fCol->GetEntries();
  for(UInt_t i=0;i<ents;++i) {
     const T *p = fCol->At(i);
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
     fPtHist->Fill(pt);
     fEtaHist->Fill(eta);
  }
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::PlotKineMod<T>::SlaveBegin()
{
  // Request a branch and create the histograms.

  if (GetLoadBranch()) 
    ReqBranch(GetColName(), fCol);

  if (GetFillHist()) {
    AddTH1(fPtHist,"hPtHist",";p_{t} [GeV];#",100,0.,250.);
    AddTH1(fEtaHist,"hEtaHist",";#eta;#",160,-8.,8.);
  }
}
#endif
