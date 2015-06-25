//--------------------------------------------------------------------------------------------------
// $Id: Tau.h,v 1.4 2009/04/08 10:24:33 loizides Exp $
//
// Tau
//
// Basic implementation mirroring the CMSSW class.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TAU_H
#define MITANA_DATATREE_TAU_H
 
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class Jet;

  class Tau : public Particle
  {
    public:
      Tau() {}

      FourVectorM         MomAlt()                const { return fMomAlt.V(); }
      EObjType            ObjType()               const { return kTau;        }
      void                SetPtEtaPhiM(Double_t pt, Double_t eta, Double_t phi, Double_t m);
      void                SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
      void                SetPtEtaPhiMAlt(Double_t pt, Double_t eta, Double_t phi, Double_t m);
      void                SetMomAlt(Double_t px, Double_t py, Double_t pz, Double_t e);
      virtual const Jet  *SourceJet()             const { return 0;           }

    protected:
      void                GetMom()                const;

      Vect4M              fMom;         //four momentum vector
      Vect4M              fMomAlt;      //alternative momentum combining
                                        //(Tracks and neutral ECAL Island BasicClusters
                                        // or charged hadron and gamma PFCandidates)
        
    ClassDef(Tau,1) // Tau class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Tau::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMom.Pt(), fMom.Eta(), fMom.Phi(), fMom.M()); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Tau::SetPtEtaPhiM(Double_t pt, Double_t eta, Double_t phi, Double_t m)
{ 
  // Set momentum vector.

  fMom.Set(pt, eta, phi, m);
  ClearMom();
}

inline void mithep::Tau::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set momentum vector.

  fMom.SetXYZT(px, py, pz, e);
  ClearMom();
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Tau::SetPtEtaPhiMAlt(Double_t pt, Double_t eta, Double_t phi, Double_t m)
{ 
  // Set momentum vector.

  fMomAlt.Set(pt, eta, phi, m);
  ClearMom();
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Tau::SetMomAlt(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set momentum vector.

  fMomAlt.SetXYZT(px, py, pz, e);
}
#endif
