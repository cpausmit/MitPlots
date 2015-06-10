#ifndef MITANA_DATATREE_LINKDEF_H
#define MITANA_DATATREE_LINKDEF_H

#include "MitAna/DataTree/interface/BranchName.h"
#include "MitAna/DataTree/interface/BranchTable.h"
#include "MitAna/DataTree/interface/EvtSelData.h"
#include "MitAna/DataTree/interface/LAHeader.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/RunInfo.h"
#include "MitAna/DataTree/interface/MCRunInfo.h"
#include "MitAna/DataTree/interface/MCRunInfoFull.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerTable.h"
#include "MitAna/DataTree/interface/TriggerObjectsTable.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ MitAnaDataTree
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

#pragma link C++ class mithep::BranchName+;
#pragma link C++ class mithep::BranchTable+;
#pragma link C++ class mithep::EvtSelData+;
#pragma link C++ class mithep::LAHeader+;
#pragma link C++ class mithep::MCEventInfo+;
#pragma link C++ class mithep::Names+;
#pragma link C++ class mithep::RunInfo+;
#pragma link C++ class mithep::MCRunInfo-;
#pragma link C++ class mithep::MCRunInfoFull-;
#pragma link C++ class mithep::TriggerName+;
#pragma link C++ class mithep::TriggerObjectsTable+;
#pragma link C++ class mithep::TriggerTable+;
#pragma link C++ class std::vector<std::pair<TString, TString> >+;
#endif
