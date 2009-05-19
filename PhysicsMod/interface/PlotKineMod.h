//--------------------------------------------------------------------------------------------------
// $Id: PlotKineMod.h,v 1.9 2009/05/18 06:30:38 loizides Exp $
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

      const char              *GetColName()              const { return fColName;     }
      Double_t                 GetEtaMin()               const { return fEtaMin;      }
      Double_t                 GetEtaMax()               const { return fEtaMax;      }
      const char              *GetInputName()            const { return GetColName(); }
      Double_t                 GetPtMin()                const { return fPtMin;       }
      Double_t                 GetPtMax()                const { return fPtMax;       }
      void                     SetColName(const char *n)       { fColName=n;          }
      void                     SetEntriesMax(Int_t e)          { fEntriesMax = e;     }
      void                     SetEtaMin(Double_t e)           { fEtaMin = e;         }
      void                     SetEtaMax(Double_t e)           { fEtaMax = e;         }
      void                     SetInputName(const char *n)     { SetColName(n);       }
      void                     SetPtMin(Double_t pt)           { fPtMin = pt;         }
      void                     SetPtMax(Double_t pt)           { fPtMax = pt;         }

    protected:
      Bool_t                   Load();
      void                     Process();
      void                     SlaveBegin();

      TString                  fColName;    //name of collection
      Double_t                 fPtMin;      //minimum pt
      Double_t                 fPtMax;      //maximum pt
      Double_t                 fEtaMin;     //minimum eta
      Double_t                 fEtaMax;     //maximum eta 
      Int_t                    fEntriesMax;  //maximum number of entries
      const Collection<T>     *fCol;        //!pointer to collection 
      TH1D                    *fPtHist;     //!pt histogram
      TH1D                    *fEtaHist;    //!eta histogram
      TH1D                    *fEntHist;    //!entries histogram

      ClassDefT(PlotKineMod, 1) // Plot kinematics module
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
  fEntriesMax(250),
  fCol(0),
  fPtHist(0),
  fEtaHist(0),
  fEntHist(0)
{
  // Constructor.

  SetFillHist(kTRUE);
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::PlotKineMod<T>::Process()
{
  // Process entries of the tree: Just load the branch and fill the histograms.

  if (!LoadEventObject(GetColName(), fCol)) {
    SendError(kAbortModule, "Process", "Could not load data!");
    return;
  }

  if (!GetFillHist())
    return;
    
  UInt_t ents=fCol->GetEntries();
  fEntHist->Fill(ents);
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
  
  ReqEventObject(GetColName(), fCol);

  if (GetFillHist()) {
    Int_t ptbins = (Int_t)((fPtMax-fPtMin)/2.5);
    AddTH1(fPtHist,"hPtHist",";p_{t} [GeV];#",ptbins,fPtMin,fPtMax);
    Int_t etabins = (Int_t)((fEtaMax-fEtaMin)/0.1);
    AddTH1(fEtaHist,"hEtaHist",";#eta;#",etabins,fEtaMin,fEtaMax);
    AddTH1(fEntHist,"hEntriesHist",";#entries;#",fEntriesMax,-0.5,fEntriesMax-0.5);
  }
}
#endif
