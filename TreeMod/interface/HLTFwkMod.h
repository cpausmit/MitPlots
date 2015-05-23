//--------------------------------------------------------------------------------------------------
// $Id: HLTFwkMod.h,v 1.8 2009/08/11 15:24:39 loizides Exp $
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
#include "MitAna/DataTree/interface/TriggerObjectBaseFwd.h"
#include "MitAna/DataTree/interface/TriggerObjectFwd.h"
#include "MitAna/DataTree/interface/TriggerObjectRelFwd.h"

namespace mithep 
{
  class TriggerTable;
  class TriggerObjectsTable;

  class HLTFwkMod : public BaseMod {
    public:
      HLTFwkMod(const char *name="HLTFwkMod", const char *title="HLT framework module");
      ~HLTFwkMod();

      const char                 *L1ATabNamePub()  const { return fL1ATabNamePub; }
      const char                 *L1TTabNamePub()  const { return fL1TTabNamePub; }
      const char                 *HLTLabName()     const { return fHLTLabName;    }
      const char                 *HLTLabNamePub()  const { return fHLTLabNamePub; }
      const char                 *HLTObjsName()    const { return fObjsName;      }
      const char                 *HLTObjsNamePub() const { return fObjsNamePub;   }
      const char                 *HLTTabName()     const { return fHLTTabName;    }
      const char                 *HLTTabNamePub()  const { return fHLTTabNamePub; }
      const char                 *HLTTreeName()    const { return fHLTTreeName;   }
      void                        SetL1ATabName(const char *n)     { fL1ATabNamePub = n; }
      void                        SetL1TTabName(const char *n)     { fL1TTabNamePub = n; }
      void                        SetHLTLabName(const char *n)     { fHLTLabName    = n; }
      void                        SetHLTLabNamePub(const char *n)  { fHLTLabNamePub = n; }
      void                        SetHLTObjsName(const char *n)    { fObjsName      = n; }
      void                        SetHLTObjsNamePub(const char *n) { fObjsNamePub   = n; }
      void                        SetHLTTabName(const char *n)     { fHLTTabName    = n; }
      void                        SetHLTTabNamePub(const char *n)  { fHLTTabNamePub = n; }
      void                        SetHLTTreeName(const char *n)    { fHLTTreeName   = n; }

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
      TString                     fHLTTabNamePub; //HLT trigger names published qname
      TString                     fHLTLabNamePub; //HLT module labels published name
      TString                     fObjsNamePub;   //trigger objects published name
      TString                     fL1ATabNamePub; //L1 algorithm trigger names published name
      TString                     fL1TTabNamePub; //L1 technical trigger names published name
      const UInt_t                fNMaxTriggers;  //maximum number of triggers
      const TriggerObjectBaseArr *fObjs;          //!trigger objects branch
      const TriggerObjectRelArr  *fRels;          //!trigger to objects relation branch
      Bool_t                      fReload;        //!=true then reload/rebuild tables
      TTree                      *fHLTTree;       //!HLT tree in current file
      std::vector<std::string>   *fHLTTab;        //!HLT trigger names
      std::vector<std::string>   *fHLTLab;        //!HLT module labels
      Int_t                       fCurEnt;        //!current entry in HLT tree (-2 for unset)
      TriggerTable               *fTriggers;      //!exported published HLT trigger table
      TriggerTable               *fLabels;        //!exported published HLT module label table
      TriggerObjectArr           *fTrigObjArr;    //!buffer of published HLT trigger objects
      TriggerObjectsTable        *fTrigObjs;      //!exported published HLT trigger objects table
      TriggerTable               *fL1Algos;       //!exported published L1 algorithm triggers table
      TriggerTable               *fL1Techs;       //!exported published L1 technical triggers table

      friend class OutputMod;

    ClassDef(HLTFwkMod, 1) // HLT framework TAM module
  };
}
#endif
