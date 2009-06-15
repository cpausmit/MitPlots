// $Id:$

#ifndef MITANA_DATATREE_PARTICLECOLLINKDEF_H
#define MITANA_DATATREE_PARTICLECOLLINKDEF_H

#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/ParticleCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Particle+;
#pragma link C++ class mithep::Collection<mithep::Particle>+;
#pragma link C++ class mithep::RefArray<mithep::Particle>+;
#pragma link C++ class mithep::ObjArray<mithep::Particle>+;
#pragma link C++ class mithep::Ref<mithep::Particle>+;
#pragma link C++ typedef mithep::ParticleCol;
#pragma link C++ typedef mithep::ParticleOArr;
#endif
