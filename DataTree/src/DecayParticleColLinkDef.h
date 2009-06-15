// $Id:$

#ifndef MITANA_DATATREE_DECAYPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_DECAYPARTICLECOLLINKDEF_H

#include "MitAna/DataTree/interface/DecayParticleCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::DecayParticle+;
#pragma link C++ class mithep::Collection<mithep::DecayParticle>+;
#pragma link C++ class mithep::Array<mithep::DecayParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::DecayParticle>+;
#pragma link C++ typedef mithep::DecayParticleCol;
#pragma link C++ typedef mithep::DecayParticleArr;
#pragma link C++ typedef mithep::DecayParticleOArr;
#endif
