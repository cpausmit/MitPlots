// $Id: MitAnaUtilsLinkDef.h,v 1.2 2009/08/11 23:09:28 loizides Exp $

#ifndef MITANA_UTILS_LINKDEF_H
#define MITANA_UTILS_LINKDEF_H
#include "MitAna/Utils/interface/MyHtml.h"
#include "MitAna/Utils/interface/SimpleTable.h"
#include "MitAna/Utils/interface/TClassDocOutput.h"
#include "MitAna/Utils/interface/TDocDirective.h"
#include "MitAna/Utils/interface/TDocInfo.h"
#include "MitAna/Utils/interface/TDocOutput.h"
#include "MitAna/Utils/interface/TDocParser.h"
#include "MitAna/Utils/interface/THtml.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class MyHtml+;
#pragma link C++ class MyHtml::MyModDef+;
#pragma link C++ class mithep::SimpleTable+;
#pragma link C++ class mithep::SimpleTable::MyParameter+;
#pragma link C++ class TClassDocInfo;
#pragma link C++ class TClassDocOutput;
#pragma link C++ class TDocDirective;
#pragma link C++ class TDocHtmlDirective;
#pragma link C++ class TDocLatexDirective;
#pragma link C++ class TDocMacroDirective;
#pragma link C++ class TDocOutput;
#pragma link C++ class TDocParser;
#pragma link C++ class THtml;
#pragma link C++ class THtml::TFileDefinition;
#pragma link C++ class THtml::TFileSysDB;
#pragma link C++ class THtml::TFileSysDir;
#pragma link C++ class THtml::TFileSysEntry;
#pragma link C++ class THtml::TFileSysRoot;
#pragma link C++ class THtml::THelperBase;
#pragma link C++ class THtml::TModuleDefinition;
#pragma link C++ class THtml::TPathDefinition;
#pragma link C++ class TLibraryDocInfo;
#pragma link C++ class TModuleDocInfo;
#endif
