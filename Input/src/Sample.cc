// $Id: Sample.cc,v 1.2 2011/01/25 11:30:30 paus Exp $

#include "MitPlots/Input/interface/Sample.h"

ClassImp(mithep::Sample)

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
Sample::Sample(const char *name, const char *skimName, const char* file, const char* dir,
	       const double xsec, const double scale) :
  fName    (name),
  fSkimName(skimName),
  fLegend  (""),
  fFile    (file),
  fDir     (dir),
  fXsec    (xsec),
  fScale   (scale)
{
  // Constructor
}

void Sample::Show() const
{
  // Show information of this sample
  printf(" %-30s %-6s %-20s %-60s  %20.7f %7.3f\n",fName.Data(),fSkimName.Data(),fLegend.Data(),
	 fFile.Data(),fXsec,fScale);
}
