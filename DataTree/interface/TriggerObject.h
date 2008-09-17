//--------------------------------------------------------------------------------------------------
// $Id: TriggerName.h,v 1.2 2008/07/08 14:41:01 loizides Exp $
//
// TriggerObject
//
// Todo
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGEROBJECT_H
#define MITANA_DATATREE_TRIGGEROBJECT_H

#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class TriggerObjectBase : public Particle
  {
    public:
      TriggerObjectBase() {}
      TriggerObjectBase(const FourVectorM32 &mom) : fMom(mom) {}
      TriggerObjectBase(Double_t pt, Double_t eta, Double_t phi, Double_t mass) : 
        fMom(pt,eta,phi,mass) {}
      ~TriggerObjectBase() {}

      Double_t 		    Charge()  const { return 0.; }
      FourVector            Mom()     const { return FourVector(fMom.Px(),fMom.Py(),
                                                                fMom.Pz(),fMom.E()); }

    protected:
      FourVectorM32         fMom;         //object momentum

    ClassDef(TriggerObjectBase, 1) // Trigger object base class
  };

  class TriggerObjectRel : public DataObject
  {
    public:
      TriggerObjectRel() : fId(0), fType(0), fModInd(0), fFilterInd(0) {}
      TriggerObjectRel(UChar_t id, UChar_t type, Short_t mod, Short_t fil) : 
        fId(id), fType(type), fModInd(mod), fFilterInd(fil) {}
      ~TriggerObjectRel() {}

      UChar_t               Id()        const { return fId; }
      UChar_t               Type()      const { return fType; }
      UShort_t              ModInd()    const { return fModInd; }
      UShort_t              FilterInd() const { return fFilterInd; }

    protected:
      UChar_t               fId;          //trigger id
      UChar_t               fType;        //object type
      Short_t               fModInd;      //module label index
      Short_t               fFilterInd;   //filter label index

    ClassDef(TriggerObjectRel, 1) // Trigger to trigger object relation class
  };

  class TriggerObject : public TriggerObjectBase
  {
    public:
      enum ETriggerObject { // see DataFormats/HLTReco/interface/TriggerTypeDefs.h
        None               =  0,
        TriggerL1Mu        =  81,
        TriggerL1NoIsoEG   =  82,
        TriggerL1IsoEG     =  83,
        TriggerL1CenJet    =  84,
        TriggerL1ForJet    =  85,
        TriggerL1TauJet    =  86,
        TriggerL1ETM       =  87,
        TriggerL1ETT       =  88,
        TriggerL1HTT       =  89,
        TriggerL1JetCounts =  90,
        TriggerPhoton      =  91,
        TriggerElectron    =  92,
        TriggerMuon        =  93,
        TriggerTau         =  94,
        TriggerJet         =  95,
        TriggerBJet        =  96,
        TriggerMET         =  97,
        TriggerHT          =  98,
        TriggerTrack       =  99,
        TriggerCluster     = 100
      };

      TriggerObject() : fId(0), fType(None) {}
      TriggerObject(UShort_t id, ETriggerObject type, const FourVectorM32 &mom) : 
        TriggerObjectBase(mom), fId(id), fType(type) {}
      TriggerObject(UShort_t id, ETriggerObject type, 
                    Double_t pt, Double_t eta, Double_t phi, Double_t mass) : 
        TriggerObjectBase(pt,eta,phi,mass), fId(id), fType(type)  {}
      
      ~TriggerObject() {}

      UShort_t              Id()      const { return fId; }
      ETriggerObject        Type()    const { return fType; }

    protected:
      UChar_t               fId;          //trigger id
      ETriggerObject        fType;        //object type

    ClassDef(TriggerObject, 1) // Trigger object class
  };
}
#endif
