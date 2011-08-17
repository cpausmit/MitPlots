//--------------------------------------------------------------------------------------------------
// $Id: TriggerObjectRel.h,v 1.1 2009/07/13 09:42:15 loizides Exp $
//
// TriggerObjectRel
//
// This class holds the relation between HLT trigger bit and objects, as well
// as final assignment of the trigger type.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGEROBJECTREL_H
#define MITANA_DATATREE_TRIGGEROBJECTREL_H

#include <THashTable.h>
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerTable.h"

namespace mithep 
{
  class TriggerObjectRel : public DataObject
  {
    public:
      TriggerObjectRel() : fTrgId(0), fType(0), fObjInd(-1), fModInd(-1), fFilterInd(-1) {}
      TriggerObjectRel(UShort_t id, Char_t type, Int_t obj, Int_t mod, Int_t fil) : 
        fTrgId(id), fType(type), fObjInd(obj), fModInd(mod), fFilterInd(fil) {}

      Int_t               FilterInd() const { return fFilterInd;        }
      Int_t               ModInd()    const { return fModInd;           }
      Int_t               ObjInd()    const { return fObjInd;           }
      EObjType            ObjType()   const { return kTriggerObjectRel; }      
      UShort_t            TrgId()     const { return fTrgId;            }
      Char_t              Type()      const { return fType;             }

    protected:
      UShort_t            fTrgId;       //trigger id
      Char_t              fType;        //trigger type
      Int_t               fObjInd;      //trigger object index
      Int_t               fModInd;      //module label index
      Int_t               fFilterInd;   //filter label index

    ClassDef(TriggerObjectRel, 3) // Trigger to trigger object relation class
  };
}
#endif
