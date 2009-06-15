// $Id:$

#ifndef MITANA_DATATREE_STABLEPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_STABLEPARTICLECOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/StableParticleCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::StableParticle+;
#pragma link C++ class mithep::Collection<mithep::StableParticle>+;
#pragma link C++ class mithep::Array<mithep::StableParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::StableParticle>+;
#pragma link C++ class mithep::Ref<mithep::StableParticle>+;
#pragma link C++ typedef mithep::StableParticleCol;
#pragma link C++ typedef mithep::StableParticleArr;
#pragma link C++ typedef mithep::StableParticleOArr;
#endif
