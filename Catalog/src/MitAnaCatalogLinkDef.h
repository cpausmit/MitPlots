// $Id: MitAnaCatalogLinkDef.h,v 1.1 2008/07/07 16:41:52 paus Exp $

#ifndef CATALOG_LINKDEF_H
#define CATALOG_LINKDEF_H
#include "MitAna/Catalog/interface/BaseMetaData.h"
#include "MitAna/Catalog/interface/FilesetMetaData.h"
#include "MitAna/Catalog/interface/FileMetaData.h"
#include "MitAna/Catalog/interface/Dataset.h"
#include "MitAna/Catalog/interface/Catalog.h"
#endif

#ifdef __CINT__
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
