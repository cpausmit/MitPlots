//--------------------------------------------------------------------------------------------------
// TreeContainer
//
// This class holds all of the trees that are used to make a single plot
//
// Authors: D.Abercrombie
//--------------------------------------------------------------------------------------------------

#ifndef MITPLOTS_CONTAINER_TREECONTAINER_H
#define MITPLOTS_CONTAINER_TREECONTAINER_H

#include <vector>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"

namespace mithep 
{
  class TreeContainer
  {
  public:
    TreeContainer();
    virtual ~TreeContainer();

    void     AddFile        ( TString fileName );
    void     AddDirectory   ( TString directoryName, TString searchFor = ".root" );
    void     SetTreeName    ( TString TreeName )                              { fTreeName = TreeName; }
    TTree*   ReturnTree     ( TString Name = "" );
    void     SetPrinting    ( bool printing )                                 { fPrinting = printing; }

  private:

    Bool_t                 fPrinting;                               // Printer for debugging
    TFile*                 tempFile;                                // Pointer to File
    TTree*                 tempTree;                                // Pointer to Tree
    TString                fTreeName;                               // Name of Trees looking for
    std::vector<TFile*>    fFileList;                               // List of files
    TTree*                 fTree;                                   // Merged Tree gets merged during GetTree
    
    ClassDef(TreeContainer,1)
  };
}

#endif
