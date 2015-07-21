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

    void                   AddFile             ( TString fileName );
    void                   AddDirectory        ( TString directoryName, TString searchFor = ".root" );
    void                   SetTreeName         ( TString TreeName )         { fTreeName = TreeName; }
    TTree*                 ReturnTree          ( TString Name = "", Bool_t inFile = false );
    std::vector<TTree*>    ReturnTreeList      ( TString Name = "" );
    void                   SetPrinting         ( Bool_t printing )          { fPrinting = printing; }

    void                   AddKeepBranch       ( TString name )             { fKeepBranches.push_back(name); }
    void                   SetOutputFileName   ( TString name )             { fOutputFileName = name;        }
    void                   SetSkimmingTrees    ( Bool_t skim )              { fSkimmingTrees = skim;         }

    void                   MakeFile            ( TString fileName = "", TString treeName = "");

  private:

    TTree*                 SkimTree            ( TTree *tree, Bool_t inFile );

    Bool_t                 fPrinting;                               // Printer for debugging
    TFile*                 tempFile;                                // Pointer to File
    TTree*                 tempTree;                                // Pointer to Tree
    TString                fTreeName;                               // Name of Trees looking for
    std::vector<TFile*>    fFileList;                               // List of files
    std::vector<TTree*>    fTreeList;                               // List of trees
    TTree*                 fTree;                                   // Merged Tree gets merged during GetTree

    std::vector<TString>   fKeepBranches;                           // Branches kept in the event of skimming
    TString                fOutputFileName;                         // Potential output file name of skim
    Bool_t                 fSkimmingTrees;                          // Bool to determine if skimming is happening
    
    ClassDef(TreeContainer,1)
  };
}

#endif
