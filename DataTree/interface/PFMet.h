//--------------------------------------------------------------------------------------------------
// $Id: PFMet.h,v 1.1 2009/03/12 15:56:50 bendavid Exp $
//
// PFMet
//
// Class to hold PFMet specific information.
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

      Double_t                     ChargedEMFraction()   const       { return fChargedEMFraction;  }
      Double_t                     ChargedHadFraction()  const       { return fChargedHadFraction; }
      Double_t                     MuonFraction()        const       { return fMuonFraction;       }
      Double_t                     NeutralEMFraction()   const       { return fNeutralEMFraction;  }
      Double_t                     NeutralHadFraction()  const       { return fNeutralHadFraction; }
      EObjType                     ObjType()             const       { return kPFMet;              }
      void                         SetChargedEMFraction(Double_t x)  { fChargedEMFraction = x;     }
      void                         SetChargedHadFraction(Double_t x) { fChargedHadFraction = x;    } 
      void                         SetMuonFraction(Double_t x)       { fMuonFraction = x;          }
      void                         SetNeutralEMFraction(Double_t x)  { fNeutralEMFraction = x;     }
      void                         SetNeutralHadFraction(Double_t x) { fNeutralHadFraction = x;    }
      
    protected:
      Double32_t                   fNeutralEMFraction;   //[0,0,14]neutral em fraction
      Double32_t                   fNeutralHadFraction;  //[0,0,14]neutral had fraction
      Double32_t                   fChargedEMFraction;   //[0,0,14]charged em fraction
      Double32_t                   fChargedHadFraction;  //[0,0,14]charged had fraction
      Double32_t                   fMuonFraction;        //[0,0,14]muon fraction
    
    ClassDef(PFMet, 1) // Missing transverse energy class
  };
}
#endif
