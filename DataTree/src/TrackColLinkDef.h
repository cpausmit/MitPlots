// $Id:$

#ifndef MITANA_DATATREE_TRACKCOLLINKDEF_H
#define MITANA_DATATREE_TRACKCOLLINKDEF_H

#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/TrackCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Track+;
#pragma link C++ class mithep::Collection<mithep::Track>+;
#pragma link C++ class mithep::Array<mithep::Track>+;
#pragma link C++ class mithep::ObjArray<mithep::Track>+;
#pragma link C++ class mithep::Ref<mithep::Track>+;
#pragma link C++ class mithep::RefArray<mithep::Track>+;
#pragma link C++ typedef mithep::TrackCol;
#pragma link C++ typedef mithep::TrackArr;
#pragma link C++ typedef mithep::TrackOArr;
#pragma link C++ enum mithep::Track::EHitLayer;
#endif
