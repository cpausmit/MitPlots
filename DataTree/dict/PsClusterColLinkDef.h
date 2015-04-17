// $Id: PsClusterColLinkDef.h,v 1.2 2011/03/11 04:03:00 bendavid Exp $

#ifndef MITANA_DATATREE_PSCLUSTERCOLLINKDEF_H
#define MITANA_DATATREE_PSCLUSTERCOLLINKDEF_H

#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PsClusterCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ PsClusterCol
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

#pragma link C++ class mithep::PsCluster+;
#pragma link C++ class mithep::Collection<mithep::PsCluster>+;
#pragma link C++ class mithep::Array<mithep::PsCluster>+;
#pragma link C++ class mithep::ObjArray<mithep::PsCluster>+;
#pragma link C++ class mithep::Ref<mithep::PsCluster>+;
#pragma link C++ class mithep::RefArray<mithep::PsCluster>+;
#pragma link C++ typedef mithep::PsClusterCol;
#pragma link C++ typedef mithep::PsClusterArr;
#pragma link C++ typedef mithep::PsClusterOArr;
#endif
