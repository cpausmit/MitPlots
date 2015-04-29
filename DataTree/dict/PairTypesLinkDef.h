// $Id: PairTypesLinkDef.h,v 1.3 2011/03/11 04:03:00 bendavid Exp $

#ifndef MITANA_DATATREE_PAIRLINKDEF_H
#define MITANA_DATATREE_PAIRLINKDEF_H

#include "MitAna/DataCont/interface/Collection.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/DataTree/interface/Pair.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ PairTypes
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

#pragma link C++ class mithep::Pair<mithep::Particle>+;
#pragma link C++ class mithep::Collection<mithep::Pair<mithep::Particle> >+;
#pragma link C++ class mithep::ObjArray<mithep::Pair<mithep::Particle> >+;

#pragma link C++ class mithep::Pair<mithep::Particle,mithep::TriggerObject>+;
#pragma link C++ class mithep::Collection<mithep::Pair<mithep::Particle,mithep::TriggerObject> >+;
#pragma link C++ class mithep::ObjArray<mithep::Pair<mithep::Particle,mithep::TriggerObject> >+;

#pragma link C++ class mithep::Pair<mithep::Electron,mithep::TriggerObject>+;
#pragma link C++ class mithep::Collection<mithep::Pair<mithep::Electron,mithep::TriggerObject> >+;
#pragma link C++ class mithep::ObjArray<mithep::Pair<mithep::Electron,mithep::TriggerObject> >+;

#pragma link C++ class mithep::Pair<mithep::Muon,mithep::TriggerObject>+;
#pragma link C++ class mithep::Collection<mithep::Pair<mithep::Muon,mithep::TriggerObject> >+;
#pragma link C++ class mithep::ObjArray<mithep::Pair<mithep::Muon,mithep::TriggerObject> >+;
#endif
