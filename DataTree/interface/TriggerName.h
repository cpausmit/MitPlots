//--------------------------------------------------------------------------------------------------
// $Id: TriggerName.h,v 1.2 2008/07/08 14:41:01 loizides Exp $
//
// TriggerName
//
// Todo
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGERNAME_H
#define MITANA_DATATREE_TRIGGERNAME_H

#include <TObject.h> 
#include <TString.h>
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class TriggerName : public TObject
  {
    public:
      TriggerName() : fId(0) {}
      TriggerName(const char *name, UShort_t id) : fName(name), fId(id) {}
      ~TriggerName() {}

      UShort_t              Id()      const { return fId; }
      const char           *GetName() const { return fName; }
      ULong_t               Hash()    const { return fName.Hash(); }
      const char           *Name()    const { return fName; }
      void                  Print(Option_t *opt="") const;

    protected:
      TString               fName;        //name
      UShort_t              fId;          //id
      
    ClassDef(TriggerName, 1) // Trigger name class
  };
}
#endif
