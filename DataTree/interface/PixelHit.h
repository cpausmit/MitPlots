//--------------------------------------------------------------------------------------------------
// $Id: PixelHit.h,v 1.9 2009/03/18 15:44:32 loizides Exp $
//
// PixelHit
//
// PixelHit class implemented as a point in space holding fit error and additional information.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PIXELHIT_H
#define MITANA_DATATREE_PIXELHIT_H
 
#include "MitCommon/DataFormats/interface/Vect3.h"
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class PixelHit : public DataObject
  {
    public:
      enum EType {
        kUnknown=0, 
        kBLayer1=1,
        kBLayer2=2,
        kBLayer3=3,
        kFNegDisk1=-11,
        kFPosDisk1=+11,
        kFNegDisk2=-12,
        kFPosDisk2=+12
      };

      PixelHit() : fType(0), fQuality(0), fCharge(0), fSize(0) {}
      PixelHit(Double_t x, Double_t y, Double_t z) : 
        fPosition(x,y,z), fType(0), fQuality(0), fCharge(0), fSize(0) {}
      PixelHit(const ThreeVector &pos) : 
        fPosition(pos),  fType(0), fQuality(0), fCharge(0), fSize(0) {}

      const ThreeVector   Position()           const          { return fPosition.V(); }
      EObjType            ObjType()            const          { return kPixelHit;     }
      void                SetCharge(UInt_t u)                 { fCharge = u;          }
      void                SetPosition(const ThreeVector &pos) { fPosition = pos;      }
      void                SetPosition(Double_t x, Double_t y, Double_t z); 
      void                SetQuality(UInt_t u)                { fQuality = u;         }
      void                SetType(Char_t t)                   { fType = t;            }
      void                SetSize(UInt_t u)                   { fSize = u;            }
      Double_t            X()                  const          { return fPosition.X(); }
      Double_t            Y()                  const          { return fPosition.Y(); }
      Double_t            Z()                  const          { return fPosition.Z(); }
            
    protected:
      Vect3	          fPosition; //point in space
      Char_t              fType;       //pixel type
      UInt_t              fQuality;    //quality word as defined by SiPixelRecHitQuality
      UInt_t              fCharge;     //charge of assigned cluster
      UInt_t              fSize;       //size of assigned cluster

    ClassDef(PixelHit, 1) // PixelHit class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::PixelHit::SetPosition(Double_t x, Double_t y, Double_t z)
{ 
  // Set pixel hit position.

  fPosition.SetXYZ(x,y,z);
}
#endif
