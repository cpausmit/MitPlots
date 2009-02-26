//--------------------------------------------------------------------------------------------------
// $Id: CaloTower.h,v 1.8 2009/02/18 15:38:54 loizides Exp $
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
#include "MitAna/DataTree/interface/CacheFlag.h"
#include <TMath.h>

namespace mithep 
{
  class CaloTower : public DataObject
  {
    public:
      CaloTower() : fEmEnergy(0), fHadEnergy(0), fOuterEnergy(0) {}

      Double_t            E()           const { return (fEmEnergy + fHadEnergy);                }
      Double_t            EmEt()        const { return fEmEnergy*TMath::Sin(Theta());           }
      Double_t            Eta()         const { return fPosition.Eta();                         }
      Double_t            Et()          const { return E()*TMath::Sin(Theta());                 }
      Double_t            EtWithHO()    const { return EWithHO()*TMath::Sin(Theta());           }
      Double_t            EWithHO()     const { return (fEmEnergy + fHadEnergy + fOuterEnergy); }
      Double_t            EmEnergy()    const { return fEmEnergy;                               }
      Double_t            HadEnergy()   const { return fHadEnergy;                              } 
      Double_t            HadEt()       const { return fHadEnergy*TMath::Sin(Theta());          }
      const FourVectorM  &Mom()         const;
      Double_t            Phi()         const { return fPosition.Phi();                         }
      EObjType            ObjType()     const { return kCaloTower;                              }
      Double_t            OuterEnergy() const { return fOuterEnergy;                            }
      Double_t            OuterEt()     const { return fOuterEnergy*TMath::Sin(Theta());        }
      const ThreeVectorC &Position()    const { return fPosition;                               } 
      Double_t            Theta()       const { return fPosition.Theta();                       }
      void	          SetEmEnergy(Double_t EmEnergy)       { fEmEnergy    = EmEnergy; ClearMom(); }
      void	          SetHadEnergy(Double_t HadEnergy)     { fHadEnergy   = HadEnergy; ClearMom(); }
      void	          SetOuterEnergy(Double_t OuterEnergy) { fOuterEnergy = OuterEnergy; ClearMom(); }
      void                SetPosition(Double_t x, Double_t y, Double_t z)
                                                               { fPosition.SetXYZ(x,y,z); ClearMom(); }

    protected:
      void                ClearMom()     const { fCacheMomFlag.ClearCache(); }
      void                GetMom()       const;
    
      ThreeVectorC32      fPosition;     //position of tower
      Double32_t          fEmEnergy;     //tower energy in Ecal
      Double32_t          fHadEnergy;    //tower energy in Hcal
      Double32_t          fOuterEnergy;  //tower energy in outer Hcal
      
      mutable CacheFlag   fCacheMomFlag; //||cache validity flag for momentum
      mutable FourVectorM fCachedMom;    //!cached momentum vector (filled by derived classes)

    ClassDef(CaloTower, 1) // Calo tower class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::CaloTower::GetMom() const
{
  // Compute and return four momentum.

  if (E() > 0)
    fCachedMom.SetCoordinates(Et(),Eta(),Phi(),0.0);
  else
    fCachedMom = mithep::FourVectorM();
}

//--------------------------------------------------------------------------------------------------
inline const mithep::FourVectorM &mithep::CaloTower::Mom() const
{
  // Return cached momentum value.

  if (!fCacheMomFlag.IsValid()) {
    GetMom();
    fCacheMomFlag.SetValid();
  }

  return fCachedMom;
}
#endif
