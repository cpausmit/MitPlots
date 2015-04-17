// $Id: TrackJetColLinkDef.h,v 1.1 2010/02/21 23:42:00 bendavid Exp $

#ifndef MITANA_DATATREE_TRACKJETCOLLINKDEF_H
#define MITANA_DATATREE_TRACKJETCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/TrackJetCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ TrackJetCol
#   define _R__JOIN3_(F,X,Y) _NAME3_(F,X,Y)
#   undef _R__UNIQUE_
#   define _R__UNIQUE_(X) _R__JOIN3_( _R__UNIQUEIDENTIFIER_,X,__LINE__)
#endif

#ifdef __CLING__
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
