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
      virtual ~CaloTower() {}
     
      void	       SetEmEnergy(Double_t EmEnergy)       { fEmEnergy    = EmEnergy;       }
      void	       SetHadEnergy(Double_t HadEnergy)     { fHadEnergy   = HadEnergy;      }
      void	       SetOuterEnergy(Double_t OuterEnergy) { fOuterEnergy = OuterEnergy;    }  
      void	       SetEmLvl1(Int_t EmLvl1)              { fEmLvl1      = EmLvl1;         }
      void	       SetHadLvl1(Int_t HadLvl1)            { fHadLvl1     = HadLvl1;        }      
      void	       SetMomentum(Double_t X, Double_t Y, Double_t Z, Double_t E) 
                                                            { fMomentum.SetPxPyPzE(X,Y,Z,E); }      

      FourVector       Mom()         const { return fMomentum;                            }
      Double_t         Eta()         const { return fMomentum.Eta();                      }
      Double_t         Phi()         const { return fMomentum.Phi();                      }
      Double_t         Energy()      const { return fMomentum.E();                        }
      Double_t         Et()          const { return fMomentum.E()*sin(fMomentum.Theta()); }
      Double_t         EmEnergy()    const { return fEmEnergy;                            }
      Double_t         HadEnergy()   const { return fHadEnergy;                           }
      Double_t         OuterEnergy() const { return fOuterEnergy;                         }
      Double_t         EmEt()        const { return fEmEnergy*sin(fMomentum.Theta());     }
      Double_t         HadEt()       const { return fHadEnergy*sin(fMomentum.Theta());    }
      Double_t         OuterEt()     const { return fOuterEnergy*sin(fMomentum.Theta());  }      
      Double_t         EmLvl1()      const { return fEmLvl1;                              }
      Double_t         HadLvl1()     const { return fHadLvl1;                             }      

    protected:

      FourVector       fMomentum;          
      Double_t         fEmEnergy;
      Double_t         fHadEnergy;
      Double_t         fOuterEnergy;
      Int_t            fEmLvl1;
      Int_t            fHadLvl1;

    ClassDef(CaloTower, 1) // Generic particle class
  };
}
#endif
