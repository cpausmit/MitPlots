// $Id: DecayParticleColLinkDef.h,v 1.2 2011/03/11 04:03:00 bendavid Exp $

#ifndef MITANA_DATATREE_DECAYPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_DECAYPARTICLECOLLINKDEF_H

#include "MitAna/DataTree/interface/DecayParticleCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ DecayParticleCol
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

#pragma link C++ class mithep::DecayParticle+;
#pragma link C++ class mithep::Collection<mithep::DecayParticle>+;
#pragma link C++ class mithep::Array<mithep::DecayParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::DecayParticle>+;
#pragma link C++ class mithep::Ref<mithep::DecayParticle>+;
#pragma link C++ class mithep::RefArray<mithep::DecayParticle>+;
#pragma link C++ typedef mithep::DecayParticleCol;
#pragma link C++ typedef mithep::DecayParticleArr;
#pragma link C++ typedef mithep::DecayParticleOArr;
#endif
