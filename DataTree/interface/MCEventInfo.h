//--------------------------------------------------------------------------------------------------
// $Id: MCEventInfo.h,v 1.9 2009/07/03 06:13:36 phedex Exp $
//
// MCEventInfo
//
// This class holds monte-carle generation specific information, as for example stored
// in HepMC::PdfInfo and HepMC::GenEvent.
// 
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MCEVENTINFO_H
#define MITANA_DATATREE_MCEVENTINFO_H
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class MCEventInfo : public DataBase
  {
    public:
      MCEventInfo() : fProcessId(0), fScale(0), fWeight(0), fId1(0), fId2(0), 
                      fX1(0), fX2(0), fScalePdf(0), fPdf1(0), fPdf2(0), fFlavorHistoryPath(0) {}

      Char_t              Id1()                      const { return fId1;                 }
      Char_t              Id2()                      const { return fId2;                 }
      EObjType            ObjType()                  const { return kMCEventInfo;         }      
      Double_t            Pdf1()                     const { return fPdf1;                }
      Double_t            Pdf2()                     const { return fPdf2;                }
      Int_t               ProcessId()                const { return fProcessId;           }
      Double_t            Scale()                    const { return fScale;               }
      Double_t            ScalePdf()                 const { return fScalePdf;            }
      Double_t            X1()                       const { return fX1;                  }
      Double_t            X2()                       const { return fX2;                  }
      Double_t            Weight()                   const { return fWeight;              }
      Int_t               FlavorHistoryPath()        const { return fFlavorHistoryPath;   }
      void                SetId1(Char_t id)                   { fId1       = id;          }
      void                SetId2(Char_t id)                   { fId2       = id;          }
      void                SetPdf1(Double_t p)                 { fPdf1      = p;           }
      void                SetPdf2(Double_t p)                 { fPdf2      = p;           }
      void                SetProcessId(Int_t id)              { fProcessId = id;          }
      void                SetScale(Double_t s)                { fScale     = s;           }
      void                SetScalePdf(Double_t s)             { fScalePdf  = s;           }
      void                SetWeight(Double_t w)               { fWeight    = w;           }
      void                SetX1(Double_t x)                   { fX1        = x;           }
      void                SetX2(Double_t x)                   { fX2        = x;           }
      void                SetFlavorHistoryPath(Int_t p)       { fFlavorHistoryPath = p;   }

    protected:
      Int_t         fProcessId;           //process id
      Double32_t    fScale;               //scale
      Double32_t    fWeight;              //weight
      Char_t        fId1;                 //pdg of first parton
      Char_t        fId2;                 //pdg of second parton
      Double32_t    fX1;                  //bjorken x1
      Double32_t    fX2;                  //bjorken x2
      Double32_t    fScalePdf;            //scale (Q^2)
      Double32_t    fPdf1;                //pdf1/x1
      Double32_t    fPdf2;                //pdf2/x2
      Int_t         fFlavorHistoryPath;   //Number indicating flavor history

    ClassDef(MCEventInfo, 2) // Monte-Carlo event info class
  };
}
#endif
