//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.18 2009/09/09 03:38:26 bendavid Exp $
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
      num_PU_vertices(0) 
    { };    
    
    const UInt_t           GetPU_NumInteractions()    const { return num_PU_vertices;         }
    const FArrDouble32    &GetPU_zPositions()         const { return zPositions;              }
    const FArrDouble32    &GetPU_sumpT_lowpT()        const { return sumpT_lowpT;             }
    const FArrDouble32    &GetPU_sumpT_highpT()       const { return sumpT_highpT;            }
    const FArrUInt        &GetPU_ntrks_lowpT()        const { return ntrks_lowpT;             }
    const FArrUInt        &GetPU_ntrks_highpT()       const { return ntrks_highpT;            }
    
    virtual PileupInfo    *MakeCopy()                 const { return new PileupInfo(*this);   }
    
    void                 SetPU_NumInteractions(UInt_t i)  { num_PU_vertices = i;            }
    void                 PushPU_zPositions(Double32_t x)    { zPositions.Add(x);              }
    void                 PushPU_sumpT_lowpT(Double32_t x)   { sumpT_lowpT.Add(x);             }
    void                 PushPU_sumpT_highpT(Double32_t x)  { sumpT_highpT.Add(x);            }
    void                 PushPU_ntrks_lowpT(UInt_t i)   { ntrks_lowpT.Add(i);             }
    void                 PushPU_ntrks_highpT(UInt_t i)  { ntrks_highpT.Add(i);            }
        
  protected:
    UInt_t                     num_PU_vertices;         //number of PU vertices
    FArrDouble32               zPositions;              //||array positions along z
    FArrDouble32               sumpT_lowpT;             //||array sumpT for lowpT tracks
    FArrDouble32               sumpT_highpT;            //||array sumpT for highT tracks
    FArrUInt                   ntrks_lowpT;             //||array lowpT tracks
    FArrUInt                   ntrks_highpT;            //||array highpT tracks
    
    
    ClassDef(PileupInfo, 1) // Pileup Information class
  };
}

#endif
