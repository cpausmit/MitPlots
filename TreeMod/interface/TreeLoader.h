//--------------------------------------------------------------------------------------------------
// $Id: TreeLoader.h,v 1.2 2008/09/10 03:33:28 loizides Exp $
//
// TreeLoader
//
// TAM plugin loader that is plugged into TAM via Selector::AddLoader() 
// transparently load our trees and properly reset the used Collections.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_TREELOADER_H
#define MITANA_TREEMOD_TREELOADER_H

#include "MitAna/TAM/interface/TAMVirtualLoader.h" 

class TTree;
class TAMBranchInfo;

namespace mithep {
  class TreeLoader : public TAMVirtualLoader 
  {
    public:
      TreeLoader();
      ~TreeLoader() {};

      TAMVirtualBranchLoader *CreateBranchLoader(TTree *tree, TAMBranchInfo* brInfo);

    ClassDef(TreeLoader,1)  // Plugin loader to load our tree branch loader into TAM
  };
}
#endif
