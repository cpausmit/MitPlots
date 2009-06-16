// $Id:$

#ifndef MITANA_DATATREE_PAIRLINKDEF_H
#define MITANA_DATATREE_PAIRLINKDEF_H

#include "MitAna/DataTree/interface/Pair.h"
#include "MitAna/DataTree/interface/Particle.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Pair<mithep::Particle>+;
#endif
