//--------------------------------------------------------------------------------------------------
// $Id: TreeBranchLoader.h,v 1.1 2008/07/02 16:34:06 loizides Exp $
//
// TreeBranchLoader
//
// TAM plugin that loads data from single tree branches
// into memory. We use our customed tree data loader in order
// to reset the contents of the collections and cached pointers
// properly on each entry.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_TREEBRANCHLOADER_H
#define MITANA_TREEMOD_TREEBRANCHLOADER_H

#include "MitAna/TAM/interface/TAMTreeBranchLoader.h"

namespace mithep {
  class TreeBranchLoader : public TAMTreeBranchLoader {
    protected:
      Bool_t               fDoReset; //=true if Collection::Reset() must be called

    public:
      TreeBranchLoader(TAMBranchInfo *binfo);
      ~TreeBranchLoader() {};

      void                 Clear(Option_t *option="");
      Bool_t               Notify(TTree *tree);

    ClassDef(TreeBranchLoader,0)  // TAM plugin to load data from a single branch
  };
}
#endif
