#include "MitPlots/Input/interface/Sample.h"

ClassImp(mithep::Sample)

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
Sample::Sample(const char *name, const char* file, const char* dir,
	       const double xsec, const double scale) :
  fName    (name),
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
  printf(" %-30s %-20s %-60s  %20.7f %7.3f\n",fName.Data(),fLegend.Data(),
	 fFile.Data(),fXsec,fScale);
}
