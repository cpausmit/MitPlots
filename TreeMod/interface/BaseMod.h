// $Id: THIAnaBaseMod.h 4980 2008-01-25 12:03:31Z loizides $

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
