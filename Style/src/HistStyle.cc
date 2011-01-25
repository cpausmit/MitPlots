// $Id: HistStyle.cc,v 1.1.2.2 2010/10/12 21:25:04 paus Exp $

#include "MitPlots/Style/interface/HistStyle.h"

ClassImp(mithep::HistStyle)

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
HistStyle::HistStyle() :
  fColor      (1),
  fLineWidth  (2.0),
  fFillStyle  (0),
  fMarkerStyle(20),
  fMarkerSize (1.2)
{
  // Constructor
}

void HistStyle::Show() const
{
  // Show information of this histogram style
  printf(" %3d %3.1f  %6d  %6d  %3.1f\n",fColor,fLineWidth,fFillStyle,fMarkerStyle,fMarkerSize);
}
