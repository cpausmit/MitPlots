// $Id: StableParticleColLinkDef.h,v 1.1 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_STABLEPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_STABLEPARTICLECOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/StableParticleCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ StableParticleCol
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

#pragma link C++ class mithep::StableParticle+;
#pragma link C++ class mithep::Collection<mithep::StableParticle>+;
#pragma link C++ class mithep::Array<mithep::StableParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::StableParticle>+;
#pragma link C++ class mithep::Ref<mithep::StableParticle>+;
#pragma link C++ typedef mithep::StableParticleCol;
#pragma link C++ typedef mithep::StableParticleArr;
#pragma link C++ typedef mithep::StableParticleOArr;
#endif
