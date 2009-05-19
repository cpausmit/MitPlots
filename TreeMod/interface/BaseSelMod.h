//--------------------------------------------------------------------------------------------------
// $Id: BaseSelMod.h,v 1.2 2009/03/23 22:15:13 loizides Exp $
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

    ClassDef(BaseSelMod, 1) // Base selection TAM module
  };
}
#endif
