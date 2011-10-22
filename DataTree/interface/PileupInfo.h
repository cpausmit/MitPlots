//--------------------------------------------------------------------------------------------------
// $Id: PileupInfo.h,v 1.3 2011/03/25 16:51:56 bendavid Exp $
//
// Met
//
// Class to store missing transverse energy information.
// This is the base class for various specific kinds of missing energy (CaloMet, PFMet, etc.),
// but can also be used directly.
//
// Authors: M. Zanetti
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PILEUPINFO_H
#define MITANA_DATATREE_PILEUPINFO_H
 
#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class PileupInfo : public DataBase
  {
  public:
    PileupInfo(): 
      bunchCrossing(0),
      num_PU_vertices(0),
      num_PU_mean(0)
    { };    
    
    const Int_t            GetBunchCrossing()         const { return bunchCrossing;           }
    const UInt_t           GetPU_NumInteractions()    const { return num_PU_vertices;         }
    const Float_t          GetPU_NumMean()            const { return num_PU_mean;             }
    const FArrDouble32    &GetPU_zPositions()         const { return zPositions;              }
    const FArrDouble32    &GetPU_sumpT_lowpT()        const { return sumpT_lowpT;             }
    const FArrDouble32    &GetPU_sumpT_highpT()       const { return sumpT_highpT;            }
    const FArrUInt        &GetPU_ntrks_lowpT()        const { return ntrks_lowpT;             }
    const FArrUInt        &GetPU_ntrks_highpT()       const { return ntrks_highpT;            }
    
    virtual PileupInfo    *MakeCopy()                 const { return new PileupInfo(*this);   }

    void                 SetBunchCrossing(Int_t i)        { bunchCrossing = i;                }    
    void                 SetPU_NumInteractions(UInt_t i)  { num_PU_vertices = i;              }
    void                 SetPU_NumMean(Float_t x)         { num_PU_mean = x;                  }    
    void                 PushPU_zPositions(Double32_t x)    { zPositions.Add(x);              }
    void                 PushPU_sumpT_lowpT(Double32_t x)   { sumpT_lowpT.Add(x);             }
    void                 PushPU_sumpT_highpT(Double32_t x)  { sumpT_highpT.Add(x);            }
    void                 PushPU_ntrks_lowpT(UInt_t i)   { ntrks_lowpT.Add(i);                 }
    void                 PushPU_ntrks_highpT(UInt_t i)  { ntrks_highpT.Add(i);                }
        
  protected:
    Int_t                      bunchCrossing;           //bunch crossing
    UInt_t                     num_PU_vertices;         //number of PU vertices
    FArrDouble32               zPositions;              //||array positions along z
    FArrDouble32               sumpT_lowpT;             //||array sumpT for lowpT tracks
    FArrDouble32               sumpT_highpT;            //||array sumpT for highT tracks
    FArrUInt                   ntrks_lowpT;             //||array lowpT tracks
    FArrUInt                   ntrks_highpT;            //||array highpT tracks
    Float_t                    num_PU_mean;             //poisson mean from which npu was thrown
    
    ClassDef(PileupInfo, 3) // Pileup Information class
  };
}

#endif
