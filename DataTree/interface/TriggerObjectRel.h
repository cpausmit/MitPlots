//--------------------------------------------------------------------------------------------------
// $Id: TriggerObject.h,v 1.11 2009/07/13 06:37:34 loizides Exp $
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
      TriggerObjectRel(UChar_t id, UChar_t type, Short_t obj, Short_t mod, Short_t fil) : 
        fTrgId(id), fType(type), fObjInd(obj), fModInd(mod), fFilterInd(fil) {}

      Short_t               FilterInd() const { return fFilterInd;        }
      Short_t               ModInd()    const { return fModInd;           }
      Short_t               ObjInd()    const { return fObjInd;           }
      EObjType              ObjType()   const { return kTriggerObjectRel; }      
      UChar_t               TrgId()     const { return fTrgId;            }
      UChar_t               Type()      const { return fType;             }

    protected:
      UChar_t               fTrgId;       //trigger id
      Char_t                fType;        //trigger type
      Short_t               fObjInd;      //trigger object index
      Short_t               fModInd;      //module label index
      Short_t               fFilterInd;   //filter label index

    ClassDef(TriggerObjectRel, 2) // Trigger to trigger object relation class
  };
}
#endif
