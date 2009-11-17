//--------------------------------------------------------------------------------------------------
// $Id: TriggerObject.h,v 1.13 2009/07/13 13:44:07 loizides Exp $
//
// TriggerObject
//
// This class holds the HLT trigger object information obtained by the HLTFwkMod module from
// TriggerObjectBase and TriggerObjectRel.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGEROBJECT_H
#define MITANA_DATATREE_TRIGGEROBJECT_H

#include "MitAna/DataTree/interface/TriggerObjectBase.h"

namespace mithep 
{
  class TriggerObject : public TriggerObjectBase
  {
    public:
      enum ETriggerObject { // see DataFormats/HLTReco/interface/TriggerTypeDefs.h
        None                  =  0,
        TriggerL1Mu           = -81,
        TriggerL1NoIsoEG      = -82,
        TriggerL1IsoEG        = -83,
        TriggerL1CenJet       = -84,
        TriggerL1ForJet       = -85,
        TriggerL1TauJet       = -86,
        TriggerL1ETM          = -87,
        TriggerL1ETT          = -88,
        TriggerL1HTT          = -89,
        TriggerL1HTM          = -90,
        TriggerL1JetCounts    = -91,
        TriggerL1HfBitCounts  = -92,
        TriggerL1HfRingEtSums = -93,
        TriggerL1TechTrig     = -94,
        TriggerL1Castor       = -95,
        TriggerL1BPTX         = -96,
        TriggerL1GtExternal   = -97,
        TriggerPhoton         = +81,
        TriggerElectron       = +82,
        TriggerMuon           = +83,
        TriggerTau            = +84,
        TriggerJet            = +85,
        TriggerBJet           = +86,
        TriggerMET            = +87,
        TriggerTET            = +88,
        TriggerTHT            = +89,
        TriggerMHT            = +90,
        TriggerTrack          = +91,
        TriggerCluster        = +92,
        TriggerMETSig         = +93,
        TriggerELongit        = +94,
        TriggerMHTSig         = +95,
        TriggerHLongit        = +96
      };

      TriggerObject() : fTrgId(0), fTrigName(0), fModName(0), fFilName(0), fTagName(0) {}
      TriggerObject(UChar_t tid, Char_t type, Int_t id, const FourVectorM32 &mom) : 
        TriggerObjectBase(id,type,mom), fTrgId(tid), 
        fTrigName(0), fModName(0), fFilName(0), fTagName(0) {}
      TriggerObject(UChar_t tid, Char_t type, Int_t id, 
                    Double_t pt, Double_t eta, Double_t phi, Double_t mass) : 
        TriggerObjectBase(id,type,pt,eta,phi,mass), 
        fTrgId(tid), fTrigName(0), fModName(0), fFilName(0), fTagName(0) {}

      const char           *FilterName()            const { return fFilName;       }
      ULong_t               Hash()                  const { return fTrgId;         }
      const char           *ModuleName()            const { return fModName;       }
      EObjType              ObjType()               const { return kTriggerObject; }      
      void                  Print(Option_t *opt="") const;
      const char           *TagName()               const { return fTagName;       }
      UChar_t               TrgId()                 const { return fTrgId;         }
      const char           *TrigName()              const { return fTrigName;      }
      ETriggerObject        TriggerType()           const 
                              { return static_cast<ETriggerObject>(Type());        }
      void                  SetFilterName(const char *n)  { fFilName  = n; }
      void                  SetModuleName(const char *n)  { fModName  = n; }
      void                  SetTagName(const char *n)     { fTagName = n;  }
      void                  SetTrigName(const char *n)    { fTrigName = n; }

    protected:
      UChar_t               fTrgId;       //trigger id
      const char           *fTrigName;    //!trigger name
      const char           *fModName;     //!L3 module name
      const char           *fFilName;     //!L3 filter name
      const char           *fTagName;     //!input tag name

    ClassDef(TriggerObject, 2) // Trigger object class
  };
}
#endif
