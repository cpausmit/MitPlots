//--------------------------------------------------------------------------------------------------
// LegendContainer
//
// This class holds all of the trees that are used to make a single plot
//
// Authors: D.Abercrombie
//--------------------------------------------------------------------------------------------------

#ifndef MITPLOTS_CONTAINER_LEGENDCONTAINER_H
#define MITPLOTS_CONTAINER_LEGENDCONTAINER_H

#include <vector>

#include "TString.h"
#include "TColor.h"

namespace mithep 
{
  class LegendContainer
  {
  public:
    LegendContainer();
    virtual ~LegendContainer();

    void                  AddEntry              ( TString LegendEntry, Color_t ColorEntry );
    TString               ReturnLegendEntry     ( Int_t i0 )          { return fLegendEntries[i0]; }
    Color_t               ReturnColor           ( Int_t i0 )          { return fColors[i0];        }
    std::vector<TString>  ReturnLegendEntries   ()                    { return fLegendEntries;     }
    std::vector<Color_t>  ReturnColors          ()                    { return fColors;            }

  private:

    std::vector<TString>   fLegendEntries;
    std::vector<Color_t>   fColors;
    
    ClassDef(LegendContainer,1)
  };
}

#endif
