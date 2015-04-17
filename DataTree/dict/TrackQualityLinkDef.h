// $Id: TrackQualityLinkDef.h,v 1.1 2010/01/18 14:35:10 bendavid Exp $

#ifndef MITANA_DATATREE_TRACKQUALITYLINKDEF_H
#define MITANA_DATATREE_TRACKQUALITYLINKDEF_H

#include "MitAna/DataTree/interface/TrackQuality.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ TrackQuality
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

#pragma link C++ class mithep::TrackQuality+;
#pragma link C++ enum mithep::TrackQuality::EQuality;
#endif
