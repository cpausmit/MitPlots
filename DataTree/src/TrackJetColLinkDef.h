// $Id: TrackJetColLinkDef.h,v 1.1 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_TRACKJETCOLLINKDEF_H
#define MITANA_DATATREE_TRACKJETCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/TrackJetCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::TrackJet+;
#pragma link C++ class mithep::Collection<mithep::TrackJet>+;
#pragma link C++ class mithep::Array<mithep::TrackJet>+;
#pragma link C++ class mithep::ObjArray<mithep::TrackJet>+;
#pragma link C++ class mithep::Ref<mithep::TrackJet>+;
#pragma link C++ typedef mithep::TrackJetCol;
#pragma link C++ typedef mithep::TrackJetArr;
#pragma link C++ typedef mithep::TrackJetOArr;
#endif
