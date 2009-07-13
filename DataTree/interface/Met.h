//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.16 2009/07/10 14:17:08 loizides Exp $
//
// Met
//
// Class to store missing transverse energy information.
// This is the base class for various specific kinds of missing energy (CaloMet, PFMet, etc.),
// but can also be used directly.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MET_H
#define MITANA_DATATREE_MET_H
 
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class Met : public Particle
  {
    public:
      Met() :
        fMex(0), fMey(0), fSumEt(0), fElongit(0) { }
      Met(Double_t mex, Double_t mey) : 
        fMex(mex), fMey(mey), fSumEt(0), fElongit(0) { }

      const FArrDouble32          &Dmex()               const { return fDmex;                   }
      const FArrDouble32          &Dmey()               const { return fDmey;                   }
      const FArrDouble32          &DSumEt()             const { return fDSumEt;                 }
      Double_t                     Elongitudinal()      const { return fElongit;                }
      Bool_t                       HasCorrections()     const;
      Double_t                     MetSig()             const;
      Double_t                     Mex()                const { return fMex;                    }
      Double_t                     Mey()                const { return fMey;                    }
      EObjType                     ObjType()            const { return kMet;                    }
      Double_t                     SumEt()              const { return fSumEt;                  }
      void                         PushCorrectionX(Double_t x)       { fDmex.Add(x);            }
      void                         PushCorrectionY(Double_t x)       { fDmey.Add(x);            }
      void                         PushCorrectionSumEt(Double_t x)   { fDSumEt.Add(x);          }
      void                         SetElongitudinal(Double_t x)      { fElongit = x;            }
      void                         SetSumEt(Double_t x)              { fSumEt = x;              }
      
    protected:
      void                         Clear(Option_t * /*option*/ ="");
      void	                   GetMom()             const;

      Double32_t                   fMex;                 //[0,0,14]x-component
      Double32_t                   fMey;                 //[0,0,14]y-component              
      Double32_t                   fSumEt;               //[0,0,14]scalar sum of ET over all objects
      Double32_t                   fElongit;             //[0,0,14]z-comp. of vector E sum
      FArrDouble32                 fDmex;                //||array of all corr. applied to MEx
      FArrDouble32                 fDmey;                //||array of all corr. applied to MEy
      FArrDouble32                 fDSumEt;              //||array of all corr. applied to SumET
    
    ClassDef(Met, 2) // Missing transverse energy class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Met::Clear(Option_t *)
{ 
  // Clear by deleting the std::vectors.
  
  fDmex.Clear();
  fDmey.Clear();
  fDSumEt.Clear();
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Met::GetMom() const
{
  // Get momentum values from stored values.

  Double_t pt = TMath::Sqrt(fMex*fMex+fMey*fMey);
  Double_t phi = TMath::ATan2(fMey,fMex);
  fCachedMom.SetCoordinates(pt,0,phi,0);
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Met::MetSig() const
{ 
  // Calculate Met Significance

  if (fSumEt>0.0)
    return (Et()/TMath::Sqrt(fSumEt));
  else
    return -1.0;
}
#endif
