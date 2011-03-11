// $Id: ConversionQualityLinkDef.h,v 1.1 2010/11/22 16:51:27 bendavid Exp $

#ifndef MITANA_DATATREE_CONVERSIONQUALITYLINKDEF_H
#define MITANA_DATATREE_CONVERSIONQUALITYLINKDEF_H

#include "MitAna/DataTree/interface/ConversionQuality.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ ConversionQuality
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

#pragma link C++ class mithep::ConversionQuality+;
#pragma link C++ enum mithep::ConversionQuality::EQuality;
#endif
