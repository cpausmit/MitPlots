//--------------------------------------------------------------------------------------------------
// $Id: Tau.h,v 1.5 2009/07/13 11:00:32 loizides Exp $
//
// EmebedWeight
//
// Weight for embedded Taus
//
// Authors: P. Harris
//-------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_EMBEDWEIGHT_H
#define MITANA_DATATREE_EMBEDWEIGHT_H
#include <TMath.h>
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Types.h"
 
namespace mithep 
{
  class EmbedWeight : public DataObject
  {
    public:
      EmbedWeight() {}
      EmbedWeight(Double_t weight) {fWeight = weight;}

      Double_t            Weight()                const { return fWeight;        }
      EObjType            ObjType()               const { return kEmbedWeight;   }  
      void                SetWeight(Double_t weight) {fWeight = weight;}
  protected:
      Double32_t          fWeight;
      ClassDef(EmbedWeight,1);
  };
}
#endif
