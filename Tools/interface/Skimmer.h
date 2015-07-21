#ifndef MITPLOTS_TOOLS_SKIMMER_H
#define MITPLOTS_TOOLS_SKIMMER_H

#include "TTree.h"
#include "TString.h"

namespace mithep
{
  class Skimmer
  {
  public:
    Skimmer();
    virtual ~Skimmer();

    void SetInputTree      ( TTree *tree )              { fInputTree = tree;             }
    void SetOutputFileName ( TString name )             { fOutputFileName = name;        }
    void AddBranch         ( TString name )             { fKeepBranches.push_back(name); }

    void DoSkim            ();

  private:

    TTree                 *fInputTree;
    TString                fOutputFileName;
    std::vector<TString>   fKeepBranches;
   
    ClassDef(Skimmer,1)
  };
}

#endif
