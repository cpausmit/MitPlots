//--------------------------------------------------------------------------------------------------
// $ Id $
//
// Calo Tower
//
// Details to be worked out...
//
// Authors: Si Xie
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_CALOTOWER_H
#define DATATREE_CALOTOWER_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class CaloTower : public DataObject
  {
    public:
      CaloTower() {}
      ~CaloTower() {}
     
      void	          SetEmEnergy(Double_t EmEnergy)       { fEmEnergy    = EmEnergy;    }
      void                SetPosition(Double_t x, Double_t y, Double_t z)
                                                            { fPosition.SetXYZ(x,y,z);     }
      void	          SetHadEnergy(Double_t HadEnergy)     { fHadEnergy   = HadEnergy;   }
      void	          SetOuterEnergy(Double_t OuterEnergy) { fOuterEnergy = OuterEnergy; }              

      const FourVectorM   Mom()         const;
      Double_t            Eta()         const { return fPosition.Eta();                      }
      Double_t            Phi()         const { return fPosition.Phi();                      }
      Double_t            Theta()       const { return fPosition.Theta();                    }
      Double_t            E()           const { return (fEmEnergy + fHadEnergy);             }
      Double_t            Et()          const { return E()*TMath::Sin(Theta());              }
      Double_t            EtWithHO()    const { return EWithHO()*TMath::Sin(Theta());        }
      Double_t            EWithHO()     const { return (fEmEnergy + fHadEnergy + fOuterEnergy); }
      Double_t            EmEnergy()    const { return fEmEnergy;                            }
      const ThreeVectorC  Position()    const { return fPosition;                            } 
      Double_t            HadEnergy()   const { return fHadEnergy;                           } 
      Double_t            OuterEnergy() const { return fOuterEnergy;                         }
      Double_t            EmEt()        const { return fEmEnergy*TMath::Sin(Theta());        }
      Double_t            HadEt()       const { return fHadEnergy*TMath::Sin(Theta());       }
      Double_t            OuterEt()     const { return fOuterEnergy*TMath::Sin(Theta());     }        

    protected:
      ThreeVectorC32      fPosition;     //Position of Tower
      Double32_t          fEmEnergy;     //tower energy in Ecal
      Double32_t          fHadEnergy;    //tower energy in Hcal
      Double32_t          fOuterEnergy;

    ClassDef(CaloTower, 1) // Generic particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::FourVectorM mithep::CaloTower::Mom() const
{
  // Compute and return four momentum

  if ( E() > 0 )
    return mithep::FourVectorM(Et(),Eta(),Phi(),0.0);
  else
    return mithep::FourVectorM();
}
#endif
