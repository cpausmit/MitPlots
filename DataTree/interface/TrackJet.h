//--------------------------------------------------------------------------------------------------
// $Id: TrackJet.h,v 1.2 2012/03/28 12:15:34 paus Exp $
//
// TrackJet
//
// This class holds information about reconstructed jet based on tracks.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRACKJET_H
#define MITANA_DATATREE_TRACKJET_H
 
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/Vertex.h"

namespace mithep 
{
  class TrackJet : public Jet
  {
    public:
      TrackJet() {}
      TrackJet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                Jet(px,py,pz,e) {}

      void                  AddTrack(const Track *t)              { fTracks.Add(t); ClearCharge(); }
      Bool_t                HasTrack(const Track *t)        const { return fTracks.HasObject(t);   }
      Jet                  *MakeCopy()                      const { return new TrackJet(*this);    }
      UInt_t                NConstituents()                 const { return NTracks();              }
      UInt_t                NTracks()                       const { return fTracks.Entries();      }
      EObjType              ObjType()                       const { return kTrackJet;              } 
      const Track          *Trk(UInt_t i)                   const { return fTracks.At(i);          }
      const Vertex         *Vtx()                           const { return fVertex.Obj();          }
      void                  SetVertex(const Vertex *v)            { fVertex = v;                   }

      // Some structural tools
      void                  Mark(UInt_t i=1)                const;

    protected:
      Double_t              GetCharge()                     const;
   
      RefArray<Track>       fTracks;               //tracks in the jet
      Ref<Vertex>           fVertex;               //associated primary vertex

    ClassDef(TrackJet, 1) // TrackJet class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::TrackJet::Mark(UInt_t ib) const
{
  // mark myself
  mithep::DataObject::Mark(ib);
  // mark my dependencies if they are there
  if (fVertex.IsValid())
    fVertex.Obj()->Mark(ib);
  fTracks.Mark(ib);
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::TrackJet::GetCharge() const 
{
  // Return sum of charge of constituent tracks.

  Double_t charge = 0;
  for (UInt_t i=0; i<NTracks(); ++i)
    charge += Trk(i)->Charge();
  
  return charge;
}
#endif
