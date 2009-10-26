// $Id: GenericParticleColLinkDef.h,v 1.1 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_GENERICPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_GENERICPARTICLECOLLINKDEF_H

#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/GenericParticleCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::GenericParticle+;
#pragma link C++ class mithep::Collection<mithep::GenericParticle>+;
#pragma link C++ class mithep::RefArray<mithep::GenericParticle>+;
#pragma link C++ class mithep::Array<mithep::GenericParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::GenericParticle>+;
#pragma link C++ class mithep::Ref<mithep::GenericParticle>+;
#pragma link C++ typedef mithep::GenericParticleCol;
#pragma link C++ typedef mithep::GenericParticleArr;
#pragma link C++ typedef mithep::GenericParticleOArr;
#endif
