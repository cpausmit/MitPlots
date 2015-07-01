//--------------------------------------------------------------------------------------------------
// PlotKineMod
// 
// This module allows one to quickly plot eta and pt distribution of a given particle.
//
// Authors: C.Loizides, Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_PLOTKINEMOD_H
#define MITANA_PHYSICSMOD_PLOTKINEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/ParticleCol.h"

#include <TH1D.h>

namespace mithep {

  class PlotKineMod : public BaseMod {
  public:
    PlotKineMod(char const* name = "PlotKineMod", 
                char const* title = "Plot kinematics module");

    char const* GetColName() const   { return fColName; }
    char const* GetInputName() const { return GetColName(); }

    Double_t GetPtMin() const     { return fPtMin; }
    Double_t GetPtMax() const     { return fPtMax; }
    Double_t GetEtaMin() const    { return fEtaMin; }
    Double_t GetEtaMax() const    { return fEtaMax; }
    Double_t GetAbsEtaMin() const { return fAbsEtaMin; }
    Double_t GetAbsEtaMax() const { return fAbsEtaMax; }

    void SetColName(char const* n)   { fColName = n; }
    void SetInputName(char const* n) { SetColName(n); }

    void SetEtaMin(Double_t e)    { fEtaMin = e; }
    void SetEtaMax(Double_t e)    { fEtaMax = e; }
    void SetPtMin(Double_t pt)    { fPtMin = pt; }
    void SetPtMax(Double_t pt)    { fPtMax = pt; }
    void SetAbsEtaMin(Double_t e) { fAbsEtaMin = e; }
    void SetAbsEtaMax(Double_t e) { fAbsEtaMax = e; }

  protected:
    void Process() override;
    void SlaveBegin() override;

    TString  fColName = "";    //name of collection
    Double_t fPtMin = 0.;      //minimum pt
    Double_t fPtMax = 1000.;      //maximum pt
    Double_t fEtaMin = -5.;     //minimum eta
    Double_t fEtaMax = 5.;     //maximum eta
    Double_t fAbsEtaMin = 0.;
    Double_t fAbsEtaMax = 1000.;

    TH1D* fPtHist = 0;     //!pt histogram
    TH1D* fEtaHist = 0;    //!eta histogram
    TH1D* fPhiHist = 0;    //!phi histogram
    TH1D* fLeadPtHist = 0;  //!pt histogram (leading object)
    TH1D* fLeadEtaHist = 0; //!eta histogram (leading object)
    TH1D* fMultHist = 0;   //!multiplicity histogram

    ClassDef(PlotKineMod, 1) // Plot kinematics module
  };

}

#endif
