// $Id: DataBaseColLinkDef.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_DATABASECOLLINKDEF_H
#define MITANA_DATATREE_DATABASECOLLINKDEF_H

#include "MitAna/DataTree/interface/DataBaseCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ DataBaseCol
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

#pragma link C++ class mithep::DataBase+;
#pragma link C++ class mithep::Collection<mithep::DataBase>+;
#pragma link C++ class mithep::Array<mithep::DataBase>+;
#pragma link C++ class mithep::ObjArray<mithep::DataBase>+;
#endif
