// $Id: PFJetColLinkDef.h,v 1.1 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_PFJETCOLLINKDEF_H
#define MITANA_DATATREE_PFJETCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PFJetCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ PFJetCol
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

#pragma link C++ class mithep::PFJet+;
#pragma link C++ class mithep::Collection<mithep::PFJet>+;
#pragma link C++ class mithep::Array<mithep::PFJet>+;
#pragma link C++ class mithep::ObjArray<mithep::PFJet>+;
#pragma link C++ class mithep::Ref<mithep::PFJet>+;
#pragma link C++ typedef mithep::PFJetCol;
#pragma link C++ typedef mithep::PFJetArr;
#pragma link C++ typedef mithep::PFJetOArr;
#endif
