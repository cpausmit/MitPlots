// $Id: PileupEnergyDensityColLinkDef.h,v 1.1 2011/03/01 14:23:28 mzanetti Exp $

#ifndef MITANA_DATATREE_PILEUPENERGYDENSITYCOLLINKDEF_H
#define MITANA_DATATREE_PILEUPENERGYDENSITYCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PileupEnergyDensityCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ PileupEnergyDensityCol
#   define _R__JOIN3_(F,X,Y) _NAME3_(F,X,Y)
#   undef _R__UNIQUE_
#   define _R__UNIQUE_(X) _R__JOIN3_( _R__UNIQUEIDENTIFIER_,X,__LINE__)
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
