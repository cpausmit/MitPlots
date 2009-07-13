// $Id: MitAnaDataTreeLinkDef.h,v 1.69 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_LINKDEF_H
#define MITANA_DATATREE_LINKDEF_H

#include "MitAna/DataTree/interface/BranchName.h"
#include "MitAna/DataTree/interface/BranchTable.h"
#include "MitAna/DataTree/interface/LAHeader.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/RunInfo.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerTable.h"
#include "MitAna/DataTree/interface/TriggerObjectsTable.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::BranchName+;
#pragma link C++ class mithep::BranchTable+;
#pragma link C++ class mithep::LAHeader+;
#pragma link C++ class mithep::MCEventInfo+;
#pragma link C++ class mithep::Names+;
#pragma link C++ class mithep::RunInfo+;
#pragma link C++ class mithep::TriggerName+;
#pragma link C++ class mithep::TriggerObjectsTable+;
#pragma link C++ class mithep::TriggerTable+;
#endif
