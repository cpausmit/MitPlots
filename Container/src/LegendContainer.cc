
#include "MitPlots/Container/interface/LegendContainer.h"

using namespace mithep;

ClassImp(mithep::LegendContainer)

//--------------------------------------------------------------------
LegendContainer::LegendContainer()
{

  // Constructor
  fLegendEntries.resize(0);
  fColors.resize(0);

}

//--------------------------------------------------------------------
LegendContainer::~LegendContainer()
{ }

//--------------------------------------------------------------------
void
LegendContainer::AddEntry(TString LegendEntry, Color_t ColorEntry ){

  fLegendEntries.push_back(LegendEntry);
  fColors.push_back(ColorEntry);

}
