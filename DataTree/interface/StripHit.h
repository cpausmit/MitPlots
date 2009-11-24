//--------------------------------------------------------------------------------------------------
// $Id: StripHit.h,v 1.4 2009/11/17 21:14:33 loizides Exp $
//
// StripHit
//
// StripHit class implemented as a point in space holding fit error and additional information.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_PIXELHIT_H
#define MITANA_DATATREE_PIXELHIT_H
 
#include "MitCommon/DataFormats/interface/Vect3.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include <TMath.h>

namespace mithep 
{
  class StripHit : public DataObject
  {
    public:
      enum EType {
        kUnknown=0,
        kTIB,
        kTOB,
        kTID,
        kTEC
      };
 
      StripHit() : fType(0), fGeoType(0), fCharge(0), fSizeX(0), fSizeY(0) {}
      StripHit(Double_t x, Double_t y, Double_t z) : 
        fPosition(x,y,z), fType(0), fGeoType(0), fCharge(0), fSizeX(0), fSizeY(0) {}
      StripHit(const ThreeVector &pos) : 
        fPosition(pos),  fType(0), fGeoType(0), fCharge(0), fSizeX(0), fSizeY(0) {}

      UInt_t              Charge()              const          { return fCharge;           }
      Int_t               GeoType()             const          { return fGeoType;          }
      EObjType            ObjType()             const          { return kStripHit;         }
      const ThreeVector   Position()            const          { return fPosition.V();     }
      void                SetCharge(UInt_t u)                  { fCharge           = u;    }
      void                SetGeoType(Int_t u)                  { fGeoType          = u;    }
      void                SetPosition(const ThreeVector &pos)  { fPosition         = pos;  }
      void                SetPosition(Double_t x, Double_t y, Double_t z); 
      void                SetSizeX(UInt_t u)                   { fSizeX   = u;             }
      void                SetSizeY(UInt_t u)                   { fSizeY   = u;             }
      void                SetType(Char_t t)                    { fType    = t;             }
      UInt_t              SizeX()               const          { return fSizeX;            }
      UInt_t              SizeY()               const          { return fSizeY;            }
      EType               Type()                const 
                            { return static_cast<EType>(fType); }
      Double_t            X()                   const          { return fPosition.X();     }
      Double_t            Y()                   const          { return fPosition.Y();     }
      Double_t            Z()                   const          { return fPosition.Z();     }
            
    protected:
      Vect3	          fPosition;          //point in space
      Char_t              fType;              //strip type
      Int_t               fGeoType;           //geometrical characteristics  (layer, disk, side)
      UInt_t              fCharge;            //charge of assigned cluster
      UInt_t              fSizeX;             //size in local x of assigned cluster
      UInt_t              fSizeY;             //size in local y of assigned cluster

    ClassDef(StripHit, 1) // StripHit class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::StripHit::SetPosition(Double_t x, Double_t y, Double_t z)
{ 
  // Set pixel hit position.

  fPosition.SetXYZ(x,y,z);
}
#endif
