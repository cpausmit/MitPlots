// $Id:$

#ifndef MITANA_DATATREE_MCPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_MCPARTICLECOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/MCParticleCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Ref<mithep::MCParticle>+;
#pragma link C++ class mithep::MCParticle+;
#pragma link C++ class mithep::Collection<mithep::MCParticle>+;
#pragma link C++ class mithep::Array<mithep::MCParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::MCParticle>+;
#pragma link C++ typedef mithep::MCParticleCol;
#pragma link C++ typedef mithep::MCParticleArr;
#pragma link C++ typedef mithep::MCParticleOArr;
#pragma link C++ enum mithep::MCParticle::EPartType;
#endif
