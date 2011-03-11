// $Id: GenericParticleColLinkDef.h,v 1.2 2009/10/26 09:48:39 loizides Exp $

#ifndef MITANA_DATATREE_GENERICPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_GENERICPARTICLECOLLINKDEF_H

#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/GenericParticleCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ GenericParticleCol
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
