//--------------------------------------------------------------------------------------------------
// $Id: JPTJet.h,v 1.2 2012/03/28 12:15:34 paus Exp $
//
// JPTJet
//
// This class holds information about reconstructed jet based on jpt corrections.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------
 
#ifndef MITANA_DATATREE_JPTJET_H
#define MITANA_DATATREE_JPTJET_H
 
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataCont/interface/Ref.h"

namespace mithep 
{
  class JPTJet : public Jet
  {
    public:
      JPTJet() : Jet(), fZSPCor(0), fChargedHadronEnergy(0), fNeutralHadronEnergy(0),
                fChargedEmEnergy(0), fNeutralEmEnergy(0), fResponseOfChargedWithEff(0),
                fResponseOfChargedWithoutEff(0), fSumPtOfChargedWithEff(0),
                fSumPtOfChargedWithoutEff(0), fSumEnergyOfChargedWithEff(0),
                fSumEnergyOfChargedWithoutEff(0), fR2momtr(0), fEta2momtr(0),
                fPhi2momtr(0), fPout(0), fZch(0), fChargedMultiplicity(0), fMuonMultiplicity(0),
                fElectronMultiplicity(0) {}

      Double_t              ZSPCor()                        const { return fZSPCor;                       }
      Double_t              ChargedHadronEnergy()           const { return fChargedHadronEnergy;          }
      Double_t              NeutralHadronEnergy()           const { return fNeutralHadronEnergy;          }
      Double_t              ChargedEmEnergy()               const { return fChargedEmEnergy;              }
      Double_t              NeutralEmEnergy()               const { return fNeutralEmEnergy;              }
      Double_t              ResponseOfChargedWithEff()      const { return fResponseOfChargedWithEff;     }
      Double_t              ResponseOfChargedWithoutEff()   const { return fResponseOfChargedWithoutEff;  }
      Double_t              SumPtOfChargedWithEff()         const { return fSumPtOfChargedWithEff;        }
      Double_t              SumPtOfChargedWithoutEff()      const { return fSumPtOfChargedWithoutEff;     }
      Double_t              SumEnergyOfChargedWithEff()     const { return fSumEnergyOfChargedWithEff;    }
      Double_t              SumEnergyOfChargedWithoutEff()  const { return fSumEnergyOfChargedWithoutEff; }
      Double_t              R2momtr()                       const { return fR2momtr;                      }
      Double_t              Eta2momtr()                     const { return fEta2momtr;                    }
      Double_t              Phi2momtr()                     const { return fPhi2momtr;                    }
      Double_t              Pout()                          const { return fPout;                         }
      Double_t              Zch()                           const { return fZch;                          }
      UInt_t                ChargedMultiplicity()           const { return fChargedMultiplicity;   }
      UInt_t                MuonMultiplicity()              const { return fMuonMultiplicity;      }
      UInt_t                ElectronMultiplicity()          const { return fElectronMultiplicity;  }
      Jet                  *MakeCopy()                      const { return new JPTJet(*this);      }
      EObjType              ObjType()                       const { return kJPTJet;                } 
      const Jet            *OriginalJet()                   const { return fOriginalJet.Obj();  }
      void                  SetZSPCor(Double_t x)                        { fZSPCor = x;                       }
      void                  SetChargedHadronEnergy(Double_t x)           { fChargedHadronEnergy = x;          }
      void                  SetNeutralHadronEnergy(Double_t x)           { fNeutralHadronEnergy = x;          }
      void                  SetChargedEmEnergy(Double_t x)               { fChargedEmEnergy = x;              }
      void                  SetNeutralEmEnergy(Double_t x)               { fNeutralEmEnergy = x;              }
      void                  SetResponseOfChargedWithEff(Double_t x)      { fResponseOfChargedWithEff = x;     }
      void                  SetResponseOfChargedWithoutEff(Double_t x)   { fResponseOfChargedWithoutEff = x;  }
      void                  SetSumPtOfChargedWithEff(Double_t x)         { fSumPtOfChargedWithEff = x;        }
      void                  SetSumPtOfChargedWithoutEff(Double_t x)      { fSumPtOfChargedWithoutEff = x;     }
      void                  SetSumEnergyOfChargedWithEff(Double_t x)     { fSumEnergyOfChargedWithEff = x;    }
      void                  SetSumEnergyOfChargedWithoutEff(Double_t x)  { fSumEnergyOfChargedWithoutEff = x; }
      void                  SetR2momtr(Double_t x)                       { fR2momtr = x;                      }
      void                  SetEta2momtr(Double_t x)                     { fEta2momtr = x;                    }
      void                  SetPhi2momtr(Double_t x)                     { fPhi2momtr = x;                    }
      void                  SetPout(Double_t x)                          { fPout = x;                         }
      void                  SetZch(Double_t x)                           { fZch = x;                          }
      void                  SetChargedMultiplicity(UInt_t n)             { fChargedMultiplicity = n;          }
      void                  SetMuonMultiplicity(UInt_t n)                { fMuonMultiplicity    = n;          }
      void                  SetElectronMultiplicity(UInt_t n)            { fElectronMultiplicity = n;         }
      void                  SetOriginalJet(const Jet *j)                 { fOriginalJet = j;                  }

      // Some structural tools
      void                  Mark(UInt_t i=1) const;

    protected:
      Double32_t            fZSPCor;               //[0,0,14]ZSP correction
      Double32_t            fChargedHadronEnergy;  //[0,0,14]charged hadron energy
      Double32_t            fNeutralHadronEnergy;  //[0,0,14]neutral hadron energy
      Double32_t            fChargedEmEnergy;      //[0,0,14]charged em energy
      Double32_t            fNeutralEmEnergy;      //[0,0,14]neutral em energy
      Double32_t            fResponseOfChargedWithEff; //[0,0,14]
      Double32_t            fResponseOfChargedWithoutEff; //[0,0,14]
      Double32_t            fSumPtOfChargedWithEff; //[0,0,14]
      Double32_t            fSumPtOfChargedWithoutEff; //[0,0,14]
      Double32_t            fSumEnergyOfChargedWithEff; //[0,0,14]
      Double32_t            fSumEnergyOfChargedWithoutEff; //[0,0,14]
      Double32_t            fR2momtr; //[0,0,14]
      Double32_t            fEta2momtr; //[0,0,14]
      Double32_t            fPhi2momtr; //[0,0,14]
      Double32_t            fPout; //[0,0,14]
      Double32_t            fZch; //[0,0,14]
      UInt_t                fChargedMultiplicity;  //number of charged constituents
      UInt_t                fMuonMultiplicity;     //number of muon constituents
      UInt_t                fElectronMultiplicity; //number of muon constituents
      Ref<Jet>              fOriginalJet;              //reference to original CaloJet

    ClassDef(JPTJet, 1) // JPTJet class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::JPTJet::Mark(UInt_t ib) const
{
  // mark myself
  mithep::DataObject::Mark(ib);
  // mark my dependencies if they are there
  if (fOriginalJet.IsValid())
    fOriginalJet.Obj()->Mark(ib);
}
#endif
