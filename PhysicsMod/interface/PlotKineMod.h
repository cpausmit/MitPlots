//--------------------------------------------------------------------------------------------------
// $Id: PlotKineMod.h,v 1.1 2008/11/25 14:30:53 loizides Exp $
//
// PlotKineMod
// 
// This module 
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
      Double_t                 GSetEtaMax()              const { return fEtaMax;  }
      Double_t                 GetPtMin()                const { return fPtMin;   }
      Double_t                 GetPtMax()                const { return fPtMax;   }
      void                     SetColName(const char *n)       { fColName=n;      }
      void                     SetEtaMin(Double_t e)           { fEtaMin = e;     }
      void                     SetEtaMax(Double_t e)           { fEtaMax = e;     }
      void                     SetPtMin(Double_t pt)           { fPtMin = pt;     }
      void                     SetPtMax(Double_t pt)           { fPtMax = pt;     }

    protected:
      TString                  fColName;    //name of collection
      Double_t                 fPtMin;      //minimum pt
      Double_t                 fPtMax;      //maximum pt
      Double_t                 fEtaMin;     //minimum eta
      Double_t                 fEtaMax;     //maximum eta 
      T                       *fCol;        //!pointer to collection 
      TH1D                    *fPtHist;     //!pt histogram
      TH1D                    *fEtaHist;    //!eta histogram

      void                     Process();
      void                     SlaveBegin();

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
  fCol(0),
  fPtHist(0),
  fEtaHist(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::PlotKineMod<T>::Process()
{
  // Process entries of the tree: Just load the branch and fill the histograms.

  LoadBranch(GetColName());

  Int_t ents=fCol->GetEntries();
  for(Int_t i=0;i<ents;++i) {
     const Particle *p = fCol->At(i);
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

  ReqBranch(GetColName(), fCol);

  fPtHist  = new TH1D("hPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fPtHist);
  fEtaHist = new TH1D("hEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fEtaHist);
}
#endif
