// $Id: JPTJetColLinkDef.h,v 1.1 2010/05/04 11:56:06 bendavid Exp $

#ifndef MITANA_DATATREE_JPTJETCOLLINKDEF_H
#define MITANA_DATATREE_JPTJETCOLLINKDEF_H
 
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/JPTJetCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ JPTJetCol
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

#pragma link C++ class mithep::JPTJet+;
#pragma link C++ class mithep::Collection<mithep::JPTJet>+;
#pragma link C++ class mithep::Array<mithep::JPTJet>+;
#pragma link C++ class mithep::ObjArray<mithep::JPTJet>+;
#pragma link C++ class mithep::Ref<mithep::JPTJet>+;
#pragma link C++ typedef mithep::JPTJetCol;
#pragma link C++ typedef mithep::JPTJetArr;
#pragma link C++ typedef mithep::JPTJetOArr;
#endif
