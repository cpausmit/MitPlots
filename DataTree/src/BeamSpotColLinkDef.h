// $Id:$

#ifndef MITANA_DATATREE_BEAMSPOTCOLLINKDEF_H
#define MITANA_DATATREE_BEAMSPOTCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/BeamSpotCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::BeamSpot+;
#pragma link C++ class mithep::Collection<mithep::BeamSpot>+;
#pragma link C++ class mithep::Array<mithep::BeamSpot>+;
#pragma link C++ class mithep::ObjArray<mithep::BeamSpot>+;
#pragma link C++ class mithep::Ref<mithep::BeamSpot>+;
#pragma link C++ typedef mithep::BeamSpotCol;
#pragma link C++ typedef mithep::BeamSpotArr;
#endif
