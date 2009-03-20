//--------------------------------------------------------------------------------------------------
// $Id: Tau.h,v 1.1 2009/03/19 23:09:36 bendavid Exp $
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
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Jet.h"

namespace mithep 
{
  class Tau : public Particle
  {
    public:
      Tau() {}
      Tau(Double_t px, Double_t py, Double_t pz, Double_t e) :    
        fMom(FourVector(px,py,pz,e)) {}

      const FourVectorM   MomAlt()                const { return fMomAlt.V(); }
      EObjType            ObjType()               const { return kTau;        }  
      void                SetMom(Double_t px, Double_t py, Double_t pz, Double_t e);
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

  fCachedMom.SetXYZT(fMom.Pt(), fMom.Eta(), fMom.Phi(), fMom.M()); 
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Tau::SetMom(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set momentum vector.

  fMom.SetXYZT(px, py, pz, e);
  ClearMom();
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Tau::SetMomAlt(Double_t px, Double_t py, Double_t pz, Double_t e)
{ 
  // Set momentum vector.

  fMomAlt.SetXYZT(px, py, pz, e);
}
#endif
