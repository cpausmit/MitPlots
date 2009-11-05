//--------------------------------------------------------------------------------------------------
// $Id: PixelHit.h,v 1.2 2009/09/28 14:15:34 loizides Exp $
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
#include <TMath.h>

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
 
      class Packing { //adapted from SiPixelRecHitQuality
        public:
          Packing();
          typedef UInt_t QualWordType;

          inline Bool_t   IsOnEdge(QualWordType qualWord)      const {
            return (qualWord >> fEdge_shift) & fEdge_mask;
          }
          inline Bool_t   HasBadPixels(QualWordType qualWord)  const {
            return (qualWord >> fBad_shift) & fBad_mask;
          }
          inline Bool_t   HasFilledProb(QualWordType qualWord) const {
            return (qualWord >> fHasFilledProb_shift) & fHasFilledProb_mask;
          }
          inline Float_t  ProbabilityX(QualWordType qualWord)  const {
            Int_t raw = (qualWord >> fProbX_shift) & fProbX_mask;
            assert(raw>=0 && raw <=2047);
            Float_t prob = 0;
            if   (raw==2047) prob = 0;
            else             prob = TMath::Power(fProbX_units,-raw) ;
            return prob;
          }
          inline Float_t  ProbabilityY(QualWordType qualWord)  const {
            Int_t raw = (qualWord >> fProbY_shift) & fProbY_mask;
            assert(raw>=0 && raw <=2047);
            Float_t prob = 0;
            if   (raw==2047) prob = 0;
            else             prob = TMath::Power(fProbY_units,-raw) ;
            return prob;
          }
          inline Int_t    QBin(QualWordType qualWord)          const {
            Int_t qbin = (qualWord >> fQBin_shift) & fQBin_mask;
            assert(qbin>=0 && qbin <=7);
            return qbin;
          }
          inline Bool_t   SpansTwoROCs(QualWordType qualWord)  const {
            return (qualWord >> fTwoROC_shift) & fTwoROC_mask;
          }
        protected:
          QualWordType    fProbX_mask;
          Int_t           fProbX_shift;
          Float_t         fProbX_units;
          Double_t        fProbX_1_over_log_units;
          Char_t          fProbX_width;
          QualWordType    fProbY_mask;
          Int_t           fProbY_shift;
          Float_t         fProbY_units;
          Double_t        fProbY_1_over_log_units;
          Char_t          fProbY_width;
          QualWordType    fQBin_mask;
          Int_t           fQBin_shift;
          Char_t          fQBin_width;
          QualWordType    fEdge_mask;
          Int_t           fEdge_shift;
          Char_t          fEdge_width;
          QualWordType    fBad_mask;
          Int_t           fBad_shift;
          Char_t          fBad_width;
          QualWordType    fTwoROC_mask;
          Int_t           fTwoROC_shift;
          Char_t          fTwoROC_width;
          QualWordType    fHasFilledProb_mask;
          Int_t           fHasFilledProb_shift;
          Char_t          fHasFilledProb_width;
          Char_t          fSpare_width;
      };

      PixelHit() : fType(0), fQuality(0), fCharge(0), fSize(0) {}
      PixelHit(Double_t x, Double_t y, Double_t z) : 
        fPosition(x,y,z), fType(0), fQuality(0), fCharge(0), fSize(0) {}
      PixelHit(const ThreeVector &pos) : 
        fPosition(pos),  fType(0), fQuality(0), fCharge(0), fSize(0) {}

      UInt_t              Charge()             const          { return fCharge;       }
      Bool_t              IsOnEdge()           const;
      Bool_t              HasBadPixels()       const;
      EObjType            ObjType()            const          { return kPixelHit;     }
      const ThreeVector   Position()           const          { return fPosition.V(); }
      UInt_t              Quality()            const          { return fQuality;      }
      void                SetCharge(UInt_t u)                 { fCharge = u;          }
      void                SetPosition(const ThreeVector &pos) { fPosition = pos;      }
      void                SetPosition(Double_t x, Double_t y, Double_t z); 
      void                SetQuality(UInt_t u)                { fQuality = u;         }
      void                SetType(Char_t t)                   { fType = t;            }
      void                SetSize(UInt_t u)                   { fSize = u;            }
      UInt_t              Size()               const          { return fSize;         }
      Bool_t              SpansTwoROCs()       const;
      EType               Type()               const 
                            { return static_cast<EType>(fType); }
      Double_t            X()                  const          { return fPosition.X(); }
      Double_t            Y()                  const          { return fPosition.Y(); }
      Double_t            Z()                  const          { return fPosition.Z(); }
            
    protected:
      Vect3	          fPosition;   //point in space
      Char_t              fType;       //pixel type
      UInt_t              fQuality;    //quality word as defined by SiPixelRecHitQuality
      UInt_t              fCharge;     //charge of assigned cluster
      UInt_t              fSize;       //size of assigned cluster
      static Packing      fPacking;    //!the (un)packing helper class 

    ClassDef(PixelHit, 1) // PixelHit class
  };
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::PixelHit::IsOnEdge() const
{
  // Return true if pixel hit is on edge.

  return fPacking.IsOnEdge(fQuality);
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::PixelHit::HasBadPixels() const
{
  // Return true if pixel hit contains bad pixels.

  return fPacking.HasBadPixels(fQuality);
}

//--------------------------------------------------------------------------------------------------
inline void mithep::PixelHit::SetPosition(Double_t x, Double_t y, Double_t z)
{ 
  // Set pixel hit position.

  fPosition.SetXYZ(x,y,z);
}

//--------------------------------------------------------------------------------------------------
inline Bool_t mithep::PixelHit::SpansTwoROCs() const
{
  // Return true if pixel hit spans two rocs (ie is large).

  return fPacking.SpansTwoROCs(fQuality);
}
#endif
