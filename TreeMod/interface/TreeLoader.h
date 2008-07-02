//--------------------------------------------------------------------------------------------------
// $Id: THITreeLoader.h 2950 2006-06-16 16:26:16Z loizides $
//
// TreeLoader
//
// TAM plugin loader that is plugged into TAM via Selector::AddLoader() 
// transparently load our trees and properly reset the used Collections.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef TREEMOD_TREELOADER_H
#define TREEMOD_TREELOADER_H

#include "MitAna/TAM/interface/TAMVirtualLoader.h" 

class TTree;
class TAMBranchInfo;

namespace mithep {
  class TreeLoader : public TAMVirtualLoader 
  {
    public:
      TreeLoader();
      virtual ~TreeLoader() {};

      TAMVirtualBranchLoader *CreateBranchLoader(TTree *tree, TAMBranchInfo* brInfo);

    ClassDef(TreeLoader,1)  // Plugin loader to load our tree branch loader into TAM
  };
}
#endif
