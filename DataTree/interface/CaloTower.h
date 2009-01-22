//--------------------------------------------------------------------------------------------------
// $Id: CaloTower.h,v 1.6 2008/12/09 17:46:59 loizides Exp $
//
// CaloTower
//
// This class holds calo tower information.
//
// Authors: S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_CALOTOWER_H
#define MITANA_DATATREE_CALOTOWER_H
 
#include "MitAna/DataTree/interface/DataObject.h"
#include <TMath.h>

namespace mithep 
{
  class CaloTower : public DataObject
  {
    public:
      CaloTower() {}
      ~CaloTower() {}
     

      Double_t            E()           const { return (fEmEnergy + fHadEnergy);                }
      Double_t            EmEt()        const { return fEmEnergy*TMath::Sin(Theta());           }
      Double_t            Eta()         const { return fPosition.Eta();                         }
      Double_t            Et()          const { return E()*TMath::Sin(Theta());                 }
      Double_t            EtWithHO()    const { return EWithHO()*TMath::Sin(Theta());           }
      Double_t            EWithHO()     const { return (fEmEnergy + fHadEnergy + fOuterEnergy); }
      Double_t            EmEnergy()    const { return fEmEnergy;                               }
      Double_t            HadEnergy()   const { return fHadEnergy;                              } 
      Double_t            HadEt()       const { return fHadEnergy*TMath::Sin(Theta());          }
      const FourVectorM   Mom()         const;
      Double_t            Phi()         const { return fPosition.Phi();                         }
      EObjType            ObjType()     const { return kCaloTower;                              }
      Double_t            OuterEnergy() const { return fOuterEnergy;                            }
      Double_t            OuterEt()     const { return fOuterEnergy*TMath::Sin(Theta());        }
      const ThreeVectorC  Position()    const { return fPosition;                               } 
      Double_t            Theta()       const { return fPosition.Theta();                       }

      void	          SetEmEnergy(Double_t EmEnergy)       { fEmEnergy    = EmEnergy;       }
      void	          SetHadEnergy(Double_t HadEnergy)     { fHadEnergy   = HadEnergy;      }
      void	          SetOuterEnergy(Double_t OuterEnergy) { fOuterEnergy = OuterEnergy;    }
      void                SetPosition(Double_t x, Double_t y, Double_t z)
                                                               { fPosition.SetXYZ(x,y,z);       }

    protected:
      ThreeVectorC32      fPosition;     //position of tower
      Double32_t          fEmEnergy;     //tower energy in Ecal
      Double32_t          fHadEnergy;    //tower energy in Hcal
      Double32_t          fOuterEnergy;  //tower energy in outer Hcal

    ClassDef(CaloTower, 1) // Calo tower class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::FourVectorM mithep::CaloTower::Mom() const
{
  // Compute and return four momentum.

  if ( E() > 0 )
    return mithep::FourVectorM(Et(),Eta(),Phi(),0.0);
  else
    return mithep::FourVectorM();
}
#endif
