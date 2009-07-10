//--------------------------------------------------------------------------------------------------
// $Id: TriggerObject.h,v 1.9 2009/05/18 06:29:14 loizides Exp $
//
// TriggerObject
//
// This class holds the HLT trigger object information, ie
// mainly the kinematics and type of trigger. 
// The other classes TriggerObjectBase, and TriggerObjectRel are only used for 
// efficient tree storage and should not used in analysis.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGEROBJECT_H
#define MITANA_DATATREE_TRIGGEROBJECT_H

#include <THashTable.h>
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerTable.h"

namespace mithep 
{
  class TriggerObjectBase : public Particle
  {
    public:
      TriggerObjectBase() : fId(0) {}
      TriggerObjectBase(Int_t id, const FourVectorM32 &mom) : fId(id), fMom(mom) {}
      TriggerObjectBase(Int_t id, Double_t pt, Double_t eta, Double_t phi, Double_t mass) : 
        fId(id), fMom(pt,eta,phi,mass) {}

      Int_t                 Id()      const { return fId;                }
      EObjType              ObjType() const { return kTriggerObjectBase; }      

    protected:
      void                  GetMom()  const;

      Int_t                 fId;          //id or physics type (similar to pdgId)
      Vect4M                fMom;         //object momentum

    ClassDef(TriggerObjectBase, 1) // Trigger object base class
  };

  class TriggerObjectRel : public DataObject
  {
    public:
      TriggerObjectRel() : fTrgId(0), fType(0), fObjInd(0), fModInd(0), fFilterInd(0) {}
      TriggerObjectRel(UChar_t id, UChar_t type, Short_t obj, Short_t mod, Short_t fil) : 
        fTrgId(id), fType(type), fObjInd(obj), fModInd(mod), fFilterInd(fil) {}

      UShort_t              FilterInd() const { return fFilterInd;        }
      UShort_t              ModInd()    const { return fModInd;           }
      UShort_t              ObjInd()    const { return fObjInd;           }
      EObjType              ObjType()   const { return kTriggerObjectRef; }      
      UChar_t               TrgId()     const { return fTrgId;            }
      UChar_t               Type()      const { return fType;             }

    protected:
      UChar_t               fTrgId;       //trigger id
      UChar_t               fType;        //object type
      Short_t               fObjInd;      //trigger object index
      Short_t               fModInd;      //module label index
      Short_t               fFilterInd;   //filter label index

    ClassDef(TriggerObjectRel, 1) // Trigger to trigger object relation class
  };

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

      TriggerObject() : fTrgId(0), fType(None), fTrigName(0), fModName(0), fFilName(0) {}
      TriggerObject(UChar_t tid, UChar_t type, Int_t id, const FourVectorM32 &mom) : 
        TriggerObjectBase(id,mom), fTrgId(tid), fType(static_cast<ETriggerObject>(type)) {}
      TriggerObject(UChar_t tid, UChar_t type, Int_t id, 
                    Double_t pt, Double_t eta, Double_t phi, Double_t mass) : 
        TriggerObjectBase(id,pt,eta,phi,mass), fTrgId(tid), 
        fType(static_cast<ETriggerObject>(type)) {}

      const char           *FilterName()            const { return fFilName;       }
      ULong_t               Hash()                  const { return fTrgId;         }
      Bool_t                IsHLT()                 const { return fType>0;        }
      Bool_t                IsL1()                  const { return fType<0;        }
      const char           *ModuleName()            const { return fModName;       }
      EObjType              ObjType()               const { return kTriggerObject; }      
      void                  Print(Option_t *opt="") const;
      const char           *TrigName()              const { return fTrigName;      }
      UShort_t              TrgId()                 const { return fTrgId;         }
      ETriggerObject        Type()                  const { return fType;          }
      void                  SetTrigName(const char *n)    { fTrigName = n; }
      void                  SetModuleName(const char *n)  { fModName  = n; }
      void                  SetFilterName(const char *n)  { fFilName  = n; }

    protected:
      UChar_t               fTrgId;       //trigger id
      ETriggerObject        fType;        //object type
      const char           *fTrigName;    //!trigger name
      const char           *fModName;     //!L3 module name
      const char           *fFilName;     //!L3 filter name

    ClassDef(TriggerObject, 2) // Trigger object class
  };

//--------------------------------------------------------------------------------------------------
// TriggerObjectsTable
//
// A convenient THashTable for storage of TriggerObjects (not streamable).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------
  class TriggerObjectsTable : public THashTable
  {
    private:
      class MyKey : public TObject
      { 
        public:
          MyKey(ULong_t hash) : fHash(hash) {}
          ULong_t Hash() const { return fHash; }
        protected:
          ULong_t fHash; //hash value
      };

    public:
      TriggerObjectsTable(const TriggerTable *table, 
                          Int_t capacity = TCollection::kInitHashTableCapacity, Int_t rehash = 0) :
        THashTable(capacity,rehash), fTriggers(table) {}

      const TList         *GetList(const char *name) const;
      const TList         *GetList(ULong_t id)       const;
      using TCollection::Print;
      void                 Print(Option_t *opt="")   const;
 
    protected:
      const TriggerTable  *fTriggers; //trigger table
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::TriggerObjectBase::GetMom() const
{
  // Get momentum values from stored values.

  fCachedMom.SetCoordinates(fMom.Pt(),fMom.Eta(),fMom.Phi(),fMom.M()); 
}

//--------------------------------------------------------------------------------------------------
inline const TList *mithep::TriggerObjectsTable::GetList(const char *name) const
{ 
  // Return list of trigger objects for given trigger name.

  ULong_t id = fTriggers->GetId(name);
  return GetList(id);
}

//--------------------------------------------------------------------------------------------------
inline const TList *mithep::TriggerObjectsTable::GetList(ULong_t id) const
{ 
  // Return list of trigger objects for given trigger id (bit).

  MyKey key(id); 
  return const_cast<const TList*>(GetListForObject(&key)); 
}
#endif
