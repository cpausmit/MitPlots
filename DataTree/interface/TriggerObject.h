//--------------------------------------------------------------------------------------------------
// $Id: TriggerObject.h,v 1.10 2009/07/10 13:49:39 loizides Exp $
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
      TriggerObjectBase() : fId(0), fType(0), fNameInd(-1) {}
      TriggerObjectBase(Int_t id, Char_t type, const FourVectorM32 &mom) : 
        fId(id), fMom(mom), fType(type), fNameInd(-1) {}
      TriggerObjectBase(Int_t id, Char_t type, 
                        Double_t pt, Double_t eta, Double_t phi, Double_t mass) : 
        fId(id), fMom(pt,eta,phi,mass), fType(type), fNameInd(-1) {}

      Int_t                 Id()            const { return fId;                }
      Bool_t                IsHLT()               { return fType>0;            }
      Bool_t                IsL1()                { return fType<0;            }
      EObjType              ObjType()       const { return kTriggerObjectBase; }      
      Short_t               NameInd()       const { return fNameInd;           }
      Int_t                 Type()          const { return fType;              }
      void                  SetType(Char_t t)     { fType = t;                 }
      void                  SetNameInd(Short_t i) { fNameInd = i;              }
   
    protected:
      void                  GetMom()        const;

      Int_t                 fId;          //id or physics type (similar to pdgId)
      Vect4M                fMom;         //object momentum
      Char_t                fType;        //trigger type
      Short_t               fNameInd;     //name index of original input tag

    ClassDef(TriggerObjectBase, 2) // Trigger object base class
  };

  class TriggerObjectRel : public DataObject
  {
    public:
      TriggerObjectRel() : fTrgId(0), fType(0), fObjInd(-1), fModInd(-1), fFilterInd(-1) {}
      TriggerObjectRel(UChar_t id, UChar_t type, Short_t obj, Short_t mod, Short_t fil) : 
        fTrgId(id), fType(type), fObjInd(obj), fModInd(mod), fFilterInd(fil) {}

      Short_t               FilterInd() const { return fFilterInd;        }
      Short_t               ModInd()    const { return fModInd;           }
      Short_t               ObjInd()    const { return fObjInd;           }
      EObjType              ObjType()   const { return kTriggerObjectRel; }      
      UChar_t               TrgId()     const { return fTrgId;            }
      UChar_t               Type()      const { return fType;             }

    protected:
      UChar_t               fTrgId;       //trigger id
      Char_t                fType;        //trigger type
      Short_t               fObjInd;      //trigger object index
      Short_t               fModInd;      //module label index
      Short_t               fFilterInd;   //filter label index

    ClassDef(TriggerObjectRel, 2) // Trigger to trigger object relation class
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

      TriggerObject() : fTrgId(0), fTrigName(0), fModName(0), fFilName(0) {}
      TriggerObject(UChar_t tid, Char_t type, Int_t id, const FourVectorM32 &mom) : 
        TriggerObjectBase(id,type,mom), fTrgId(tid), 
        fTrigName(0), fModName(0), fFilName(0) {}
      TriggerObject(UChar_t tid, Char_t type, Int_t id, 
                    Double_t pt, Double_t eta, Double_t phi, Double_t mass) : 
        TriggerObjectBase(id,type,pt,eta,phi,mass), 
        fTrgId(tid), fTrigName(0), fModName(0), fFilName(0) {}

      const char           *FilterName()            const { return fFilName;       }
      ULong_t               Hash()                  const { return fTrgId;         }
      const char           *ModuleName()            const { return fModName;       }
      EObjType              ObjType()               const { return kTriggerObject; }      
      void                  Print(Option_t *opt="") const;
      const char           *TrigName()              const { return fTrigName;      }
      UChar_t               TrgId()                 const { return fTrgId;         }
      ETriggerObject        TriggerType()           const 
                              { return static_cast<ETriggerObject>(Type());         }
      void                  SetTrigName(const char *n)    { fTrigName = n; }
      void                  SetModuleName(const char *n)  { fModName  = n; }
      void                  SetFilterName(const char *n)  { fFilName  = n; }

    protected:
      UChar_t               fTrgId;       //trigger id
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
