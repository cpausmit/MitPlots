// $Id:$

#ifndef MITANA_DATATREE_COMPOSITEPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_COMPOSITEPARTICLECOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/CompoundParticleCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::CompoundParticle+;
#pragma link C++ class mithep::Collection<mithep::CompoundParticle>+;
#pragma link C++ class mithep::Array<mithep::CompoundParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::CompoundParticle>+;
#pragma link C++ class mithep::Ref<mithep::CompoundParticle>+;
#pragma link C++ typedef mithep::CompoundParticleCol;
#pragma link C++ typedef mithep::CompoundParticleArr;
#pragma link C++ typedef mithep::CompoundParticleOArr;
#endif
