// $Id: TrackingParticleColLinkDef.h,v 1.1 2010/01/07 11:03:42 bendavid Exp $

#ifndef MITANA_DATATREE_TRACKINGPARTICLECOLLINKDEF_H
#define MITANA_DATATREE_TRACKINGPARTICLECOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/TrackingParticleCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ TrackingParticleCol
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

#pragma link C++ class mithep::Ref<mithep::TrackingParticle>+;
#pragma link C++ class mithep::TrackingParticle+;
#pragma link C++ class mithep::Collection<mithep::TrackingParticle>+;
#pragma link C++ class mithep::Array<mithep::TrackingParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::TrackingParticle>+;
#pragma link C++ typedef mithep::TrackingParticleCol;
#pragma link C++ typedef mithep::TrackingParticleArr;
#pragma link C++ typedef mithep::TrackingParticleOArr;
#endif
