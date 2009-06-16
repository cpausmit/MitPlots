// $Id: PairTypesLinkDef.h,v 1.1 2009/06/16 15:56:22 loizides Exp $

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

#ifdef __CINT__
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
