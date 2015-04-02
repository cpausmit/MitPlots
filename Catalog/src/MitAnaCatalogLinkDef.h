// $Id: MitAnaCatalogLinkDef.h,v 1.2 2008/07/08 05:50:57 loizides Exp $

#ifndef MITANA_CATALOG_LINKDEF_H
#define MITANA_CATALOG_LINKDEF_H
#include "MitAna/Catalog/interface/BaseMetaData.h"
#include "MitAna/Catalog/interface/FilesetMetaData.h"
#include "MitAna/Catalog/interface/FileMetaData.h"
#include "MitAna/Catalog/interface/Dataset.h"
#include "MitAna/Catalog/interface/Catalog.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::BaseMetaData+;
#pragma link C++ class mithep::FileMetaData+;
#pragma link C++ class std::vector<mithep::FileMetaData>+;
#pragma link C++ class mithep::FilesetMetaData+;
#pragma link C++ class std::vector<mithep::FilesetMetaData>+;
#pragma link C++ class mithep::Dataset+;
#pragma link C++ ioctortype mithep::Dataset;
#pragma link C++ class mithep::Catalog;
#endif
