//--------------------------------------------------------------------------------------------------
// $Id: TrackingParticle.h,v 1.3 2010/01/18 14:33:02 bendavid Exp $
//
// TrackingParticle
//
// Stores additional MC information for tracking truth.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRACKINGPARTICLE_H
#define MITANA_DATATREE_TRACKINGPARTICLE_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataCont/interface/RefArray.h"


namespace mithep 
{ 
  class TrackingParticle : public Particle
  {
    public:

      TrackingParticle() {}
      
      void                 AddMCPart(const MCParticle *p) 
                             { fMCParts.Add(p); ClearCharge(); ClearMom(); }      
      const MCParticle    *DistinctMother()         const;
      const MCParticle    *FinalMCPart()            const;
      Bool_t               HasMCPart(const MCParticle *p) const { return fMCParts.HasObject(p); }
      Bool_t               Hit(Track::EHitLayer l)  const { return fHits.TestBit(l);    }
      const BitMask48     &Hits()                   const { return fHits;               }
      const MCParticle    *InitialMCPart()          const;
      const MCParticle    *MCPart(UInt_t i)         const { return fMCParts.At(i);      }
      UInt_t               NMCParts()               const { return fMCParts.Entries();  }
      UInt_t               NHits()                  const { return fHits.NBitsSet();    }
      EObjType             ObjType()                const { return kTrackingParticle;   }      
      void                 SetHit(Track::EHitLayer l)     { fHits.SetBit(l);            }
      void                 SetHits(const BitMask48 &hits) { fHits = hits;               }
      
      // Some structural tools
      void                 Mark()                   const;

    protected:
      Double_t             GetCharge()              const;
      void                 GetMom()                 const;
      BitMask48            fHits;          //storage for sim hit information
      RefArray<MCParticle> fMCParts;       //reference to corresponding MCParticles

    ClassDef(TrackingParticle,1) // Generated particle class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::TrackingParticle::Mark() const
{
  // mark myself
  mithep::DataObject::Mark();
  // mark my dependencies if they are there
  for (UInt_t i=0; i<fMCParts.Entries(); i++)
    fMCParts.At(i)->Mark();
}

//--------------------------------------------------------------------------------------------------
inline const mithep::MCParticle *mithep::TrackingParticle::DistinctMother() const 
{ 
  // Return mother, walking up the tree until a particle with a different pdg from this one
  // is found.

  const mithep::MCParticle *mcPart = FinalMCPart();
  
  if (mcPart) 
    return mcPart->DistinctMother();
  
  return 0;

}

//--------------------------------------------------------------------------------------------------
inline const mithep::MCParticle *mithep::TrackingParticle::FinalMCPart() const 
{ 
  // Return last MCParticle in the chain

  if (NMCParts()) {
    return MCPart(NMCParts() - 1);
  }
  else {
    return 0;
  }
     
}

//--------------------------------------------------------------------------------------------------
inline const mithep::MCParticle *mithep::TrackingParticle::InitialMCPart() const 
{ 
  // Return first MCParticle in the chain

  if (NMCParts()) {
    return MCPart(0);
  }
  else {
    return 0;
  }
     
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::TrackingParticle::GetCharge() const
{
  // Get charge from first MC particle.

  const MCParticle *firstMCPart = InitialMCPart();

  if (firstMCPart) {
    return firstMCPart->Charge();
  }
  else {
    return 0.0;
  }

}

//--------------------------------------------------------------------------------------------------
inline void mithep::TrackingParticle::GetMom() const
{
  // Get momentum from first MC particle.

  const MCParticle *firstMCPart = InitialMCPart();

  if (firstMCPart) {
    fCachedMom = firstMCPart->Mom();
  }
  else {
    fCachedMom = FourVectorM();
  }
  
}

#endif
