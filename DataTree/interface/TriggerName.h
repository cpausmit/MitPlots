//--------------------------------------------------------------------------------------------------
// $Id: TriggerName.h,v 1.5 2009/02/18 15:38:55 loizides Exp $
//
// TriggerName
//
// A class to hold a name and a number, ie the trigger name and trigger bit.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGERNAME_H
#define MITANA_DATATREE_TRIGGERNAME_H

#include <string>
#include <TObject.h> 
#include <TString.h>
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class TriggerName : public DataBase
  {
    public:
      TriggerName() : fId(0), fHash(0) {}
      TriggerName(const char *name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}
      TriggerName(const std::string &name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}
      TriggerName(const TString &name, UShort_t id) : 
        fName(name), fId(id), fHash(fName.Hash()) {}

      UShort_t              Id()      const { return fId; }
      const char           *GetName() const { return fName; }
      ULong_t               Hash()    const { return fHash; }
      const char           *Name()    const { return fName; }
      EObjType              ObjType() const { return kTriggerName; }      
      void                  Print(Option_t *opt="") const;

    protected:
      TString               fName;        //name
      UShort_t              fId;          //id
      UInt_t                fHash;        //hash

    ClassDef(TriggerName, 1) // Trigger name class
  };
}
#endif
