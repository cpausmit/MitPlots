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
      void                SetEmPosition(Double_t x, Double_t y, Double_t z)
                                                            { fEmPosition.SetXYZ(x,y,z);     }
      void	          SetHadEnergy(Double_t HadEnergy)     { fHadEnergy   = HadEnergy;   }
      void                SetHadPosition(Double_t x, Double_t y, Double_t z)
                                                            { fHadPosition.SetXYZ(x,y,z);    }
      void	          SetOuterEnergy(Double_t OuterEnergy) { fOuterEnergy = OuterEnergy; }  
      void	          SetEmLvl1(Int_t EmLvl1)              { fEmLvl1      = EmLvl1;      }
      void	          SetHadLvl1(Int_t HadLvl1)            { fHadLvl1     = HadLvl1;     }
      void                SetMomentum(Double_t x, Double_t y, Double_t z, Double_t e) 
                                                            { fMomentum.SetPxPyPzE(x,y,z,e); }               

      const FourVector   &Mom()         const { return fMomentum;                            }
      Double_t            Eta()         const { return fMomentum.Eta();                      }
      Double_t            Phi()         const { return fMomentum.Phi();                      }
      Double_t            Theta()       const { return fMomentum.Theta();                    }
      Double_t            E()           const { return fMomentum.E();                        }
      Double_t            Et()          const { return E()*sin(Theta());                     }
      Double_t            EmEnergy()    const { return fEmEnergy;                            }
      const ThreeVector  &EmPosition()  const { return fEmPosition;                          } 
      Double_t            HadEnergy()   const { return fHadEnergy;                           }
      const ThreeVector  &HadPosition() const { return fHadPosition;                         } 
      Double_t            OuterEnergy() const { return fOuterEnergy;                         }
      Double_t            EmEt()        const { return fEmEnergy*sin(Theta());               }
      Double_t            HadEt()       const { return fHadEnergy*sin(Theta());              }
      Double_t            OuterEt()     const { return fOuterEnergy*sin(Theta());            }      
      Double_t            EmLvl1()      const { return fEmLvl1;                              }
      Double_t            HadLvl1()     const { return fHadLvl1;                             }      

    protected:
      FourVector          fMomentum;
      ThreeVector         fEmPosition;   //Position of Ecal shower center
      ThreeVector         fHadPosition;  //Position of Hcal shower center
      Double_t            fEmEnergy;     //tower energy in Ecal
      Double_t            fHadEnergy;    //tower energy in Hcal
      Double_t            fOuterEnergy;
      Int_t               fEmLvl1;
      Int_t               fHadLvl1;

    ClassDef(CaloTower, 1) // Generic particle class
  };
}
#endif
