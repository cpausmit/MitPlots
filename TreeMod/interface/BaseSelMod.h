//--------------------------------------------------------------------------------------------------
// $Id: BaseMod.h,v 1.14 2008/12/09 10:16:24 loizides Exp $
//
// BaseSelMod
//
// This TAM module is the base selection module for all our selection modules. 
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_BASESELMOD_H
#define MITANA_TREEMOD_BASESELMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h"

namespace mithep 
{
  class BaseSelMod : public BaseMod {
    public:
      BaseSelMod(const char *name="BaseSelMod", const char *title="Base selection module");
      ~BaseSelMod() {}

    ClassDef(BaseSelMod, 1) // Base TAM module
  };
}
#endif
