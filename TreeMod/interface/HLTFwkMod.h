//--------------------------------------------------------------------------------------------------
// $Id: HLTFwkMod.h,v 1.3 2008/12/04 13:48:57 loizides Exp $
//
// HLTFwkMod
//
// This TAM module reads the trigger and trigger objects information whenever it changes
// (ie on run boundaries). It then publishes this in a convenient way so that the real
// user HLTMod modules can make use of it. Note: This module gets automatically integrated
// by the Analysis steering class (unless you have called Analysis::SetUseHLT(kFALSE).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_HLTFWKMOD_H
#define MITANA_TREEMOD_HLTFWKMOD_H

#include <string>
#include <TString.h>
#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

namespace mithep 
{
  class TriggerTable;
  class TriggerObjectsTable;

  class HLTFwkMod : public BaseMod {
    public:
      HLTFwkMod(const char *name="HLTFwkMod", const char *title="HLT framework module");
      ~HLTFwkMod();

      const char                 *HLTTreeName()    const { return fHLTTreeName; }
      const char                 *HLTTabName()     const { return fHLTTabName; }
      const char                 *HLTLabName()     const { return fHLTLabName; }
      const char                 *HLTObjsName()    const { return fObjsName; }
      const char                 *HLTTabNamePub()  const { return fHLTTabNamePub; }
      const char                 *HLTLabNamePub()  const { return fHLTLabNamePub; }
      const char                 *HLTObjsNamePub() const { return fObjsNamePub; }

    protected:
      void                        BeginRun();
      Bool_t                      LoadTriggerTable();
      Bool_t                      Notify();
      void                        Process();
      void                        SlaveBegin();
      void                        SlaveTerminate();

      TString                     fHLTTreeName;   //HLT tree name
      TString                     fHLTTabName;    //HLT trigger names branch name
      TString                     fHLTLabName;    //HLT module labels branch name
      TString                     fObjsName;      //trigger objects branch name
      TString                     fRelsName;      //trigger to objects relation branch name
      TString                     fHLTTabNamePub; //HLT trigger names published name
      TString                     fHLTLabNamePub; //HLT module labels published name
      TString                     fObjsNamePub;   //trigger objects published name
      const UInt_t                fNMaxTriggers;  //maximum number of triggers
      const TriggerObjectBaseArr *fObjs;          //!trigger objects branch
      const TriggerObjectRelArr  *fRels;          //!trigger to objects relation branch
      Bool_t                      fReload;        //!=true then reload/rebuild tables
      TTree                      *fHLTTree;       //!HLT tree in current file
      Vector<std::string>        *fHLTTab;        //!HLT trigger names
      Vector<std::string>        *fHLTLab;        //!HLT module labels
      Int_t                       fCurEnt;        //!current entry in HLT tree (-2 for unset)
      TriggerTable               *fTriggers;      //!exported published HLT trigger table
      TriggerTable               *fLabels;        //!exported published HLT module label table
      TriggerObjectsTable        *fTrigObjs;      //!exported published HLT trigger objects table

      friend class OutputMod;

    ClassDef(HLTFwkMod, 1) // HLT framework TAM module
  };
}
#endif
