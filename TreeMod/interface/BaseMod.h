//--------------------------------------------------------------------------------------------------
// $Id: BaseMod.h,v 1.1 2008/06/12 08:47:57 loizides Exp $
//
// BaseMod
//
// This TAM module is the base module for all our TAM modules.
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------


#ifndef TREEMOD_BASEMOD_H
#define TREEMOD_BASEMOD_H

#include "MitAna/TAM/interface/TAModule.h" 

namespace mithep 
{
  class BaseMod : public TAModule {
    public:
      BaseMod(const char *name="BaseMod", const char *title="Base analysis module") 
        : TAModule(name,title) {}
      ~BaseMod() {};

      ClassDef(BaseMod,1) // Base TAM module
  };
}
#endif
