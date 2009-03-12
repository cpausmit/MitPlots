//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.10 2009/03/02 14:58:17 loizides Exp $
//
// PFMet
//
// Class to hold PFMet specific information
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PFMET_H
#define MITANA_DATATREE_PFMET_H
 
#include "MitAna/DataTree/interface/Met.h"

namespace mithep 
{
  class PFMet : public Met
  {
    public:
      PFMet() :
        fNeutralEMFraction(0), fNeutralHadFraction(0), fChargedEMFraction(0),
        fChargedHadFraction(0), fMuonFraction(0) {}
      PFMet(Double_t mex, Double_t mey) : 
        Met(mex,mey),
        fNeutralEMFraction(0), fNeutralHadFraction(0), fChargedEMFraction(0),
        fChargedHadFraction(0), fMuonFraction(0) {}

      EObjType                     ObjType()             const       { return kPFMet;              }      
      Double_t                     NeutralEMFraction()   const       { return fNeutralEMFraction;  }
      Double_t                     NeutralHadFraction()  const       { return fNeutralHadFraction; }
      Double_t                     ChargedEMFraction()   const       { return fChargedEMFraction;  }
      Double_t                     ChargedHadFraction()  const       { return fChargedHadFraction; }
      Double_t                     MuonFraction()        const       { return fMuonFraction;       }
      
      void                         SetNeutralEMFraction(Double_t x)  { fNeutralEMFraction = x;     }
      void                         SetNeutralHadFraction(Double_t x) { fNeutralHadFraction = x;    }
      void                         SetChargedEMFraction(Double_t x)  { fChargedEMFraction = x;     }
      void                         SetChargedHadFraction(Double_t x) { fChargedHadFraction = x;    } 
      void                         SetMuonFraction(Double_t x)       { fMuonFraction = x;          }
      
      
    protected:

      Double32_t                   fNeutralEMFraction;
      Double32_t                   fNeutralHadFraction;
      Double32_t                   fChargedEMFraction;
      Double32_t                   fChargedHadFraction;
      Double32_t                   fMuonFraction;
    
    ClassDef(PFMet, 1) // Missing transverse energy class
  };
}
#endif
