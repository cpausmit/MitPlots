// $Id: PileupEnergyDensityColLinkDef.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_PILEUPENERGYDENSITYCOLLINKDEF_H
#define MITANA_DATATREE_PILEUPENERGYDENSITYCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PileupEnergyDensityCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::PileupEnergyDensity+;
#pragma link C++ class mithep::Collection<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::Array<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::ObjArray<mithep::PileupEnergyDensity>+;
#pragma link C++ class mithep::Ref<mithep::PileupEnergyDensity>+;
#pragma link C++ typedef mithep::PileupEnergyDensityCol;
#pragma link C++ typedef mithep::PileupEnergyDensityArr;
#endif
