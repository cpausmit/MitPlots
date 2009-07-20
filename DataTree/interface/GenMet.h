//--------------------------------------------------------------------------------------------------
// $Id: GenMet.h,v 1.1 2009/07/14 13:46:11 bendavid Exp $
//
// GenMet
//
// Class to hold GenMet specific information based on MC Truth information.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_GENMET_H
#define MITANA_DATATREE_GENMET_H
 
#include "MitAna/DataTree/interface/Met.h"

namespace mithep 
{
  class GenMet : public Met
  {
    public:
      GenMet() :
        fEmEnergy(0), fHadEnergy(0), fInvisibleEnergy(0), fAuxiliaryEnergy(0) {}
      GenMet(Double_t mex, Double_t mey) : 
        Met(mex,mey),
        fEmEnergy(0), fHadEnergy(0), fInvisibleEnergy(0), fAuxiliaryEnergy(0) {}

      Double_t               AuxiliaryEnergy()              const { return fAuxiliaryEnergy; }
      Double_t               EmEnergy()                     const { return fEmEnergy;        }
      Double_t               HadEnergy()                    const { return fHadEnergy;       }  
      Double_t               InvisibleEnergy()              const { return fInvisibleEnergy; }
      EObjType               ObjType()                      const { return kGenMet;          }
      void                   SetAuxiliaryEnergy(Double_t x)       { fAuxiliaryEnergy = x;    }
      void                   SetEmEnergy(Double_t x)              { fEmEnergy = x;           }
      void                   SetHadEnergy(Double_t x)             { fHadEnergy = x;          }
      void                   SetInvisibleEnergy(Double_t x)       { fInvisibleEnergy = x;    }
      
    protected:

      Double32_t             fEmEnergy;        //[0,0,14]total event energy from EM particles
      Double32_t             fHadEnergy;       //[0,0,14]total event energy from hadronic particles
      Double32_t             fInvisibleEnergy; //[0,0,14]total event energy from neutrinos,etc
      Double32_t             fAuxiliaryEnergy; //[0,0,14]total event energy from undecayed particles
    
    ClassDef(GenMet, 1) // Missing transverse energy class
  };
}
#endif
