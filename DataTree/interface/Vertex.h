//--------------------------------------------------------------------------------------------------
// Vertex
//
// Vertex class derived from BaseVertex holding additional fit information.
//
// Authors: J.Bendavid, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_VERTEX_H
#define MITANA_DATATREE_VERTEX_H
 
#include <TMath.h>
#include "MitAna/DataTree/interface/BaseVertex.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Vertex : public BaseVertex
  {
  public:
    Vertex() : fChi2(0), fIsValid(kFALSE), fNdof(0), fAdaptiveNdof(0), fNTracks(0) {}
    Vertex(Double_t x, Double_t y, Double_t z) : 
      BaseVertex(x,y,z), fChi2(0), fIsValid(kFALSE), fNdof(0), fAdaptiveNdof(0), fNTracks(0) {}
    Vertex(Double_t x, Double_t y, Double_t z, Double_t xErr, Double_t yErr, Double_t zErr) :
      BaseVertex(x,y,z,xErr,yErr,zErr), fChi2(0), fIsValid(kFALSE), fNdof(0), fAdaptiveNdof(0),
      fNTracks(0) {}
    Vertex(const ThreeVector &pos) : 
      BaseVertex(pos), fChi2(0), fIsValid(kFALSE), fNdof(0), fAdaptiveNdof(0), fNTracks(0) {}
    
    void                AddTrack(const Track *t,
				 Double32_t wgt = -1)     { fTracks.Add(t);
                                                            fTrkWeights.Add(wgt); }
    Double_t            Chi2()                      const { return fChi2; } 
    Int_t               Compare(const TObject *o)   const;
    Bool_t              HasTrack(const Track *t)    const { return fTracks.HasObject(t); }
    Bool_t              IsSortable()                const { return kTRUE; }
    Bool_t              IsValid()                   const { return fIsValid; }
    Double_t            Ndof()                      const { return (fAdaptiveNdof>0.0 ?
								    fAdaptiveNdof:fNdof); }
    UInt_t              NTracksFit()                const { return fNTracks; }
    UInt_t              NTracks()                   const { return fTracks.Entries(); }
    EObjType            ObjType()                   const { return kVertex; }      
    Double_t            Prob()                      const { return TMath::Prob(fChi2,fNdof); }
    void                SetChi2(Double_t chi2)            { fChi2 = chi2; }
    void                SetIsValid(Bool_t b)              { fIsValid = b; }
    void                SetNdof(Double_t nDof)            { fAdaptiveNdof = nDof; } 
    void                SetNTracksFit(UInt_t n)           { fNTracks = n; }
    const Track        *Trk(UInt_t i)               const { return fTracks.At(i); }
    Double_t            TrackWeight(UInt_t i)       const { return fTrkWeights.At(i); }
    Double_t            TrackWeight(const Track *t) const;
    const FArrDouble32 &GetTrkWeights()             const { return fTrkWeights; }
    
    
    // Some structural tools
    void                Mark(UInt_t i=1)            const;
    
    
  protected:
    Double32_t          fChi2;         //[0,0,12]chi squared of conversion vertex fit
    Bool_t              fIsValid;      //is vertex valid
    UShort_t            fNdof;         //ndeg of freedom of conversion vertex fit
    Double32_t          fAdaptiveNdof; //ndeg of freedom of vtx fit (non-integer for wghted comps)
    UShort_t            fNTracks;      //number of tracks used for the fit
    FArrDouble32        fTrkWeights;   //||array of track weights
    RefArray<Track>     fTracks;       //tracks associated with the PV
    
    ClassDef(Vertex, 5) // Vertex class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Vertex::Mark(UInt_t ib) const
{
  // mark myself
  mithep::DataObject::Mark(ib);
  // mark my dependencies if they are there
  fTracks.Mark(ib);
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::Vertex::Compare(const TObject *o) const
{
  // Default compare function for sorting according to transverse momentum.  Returns -1 if this
  // object is smaller than given object, 0 if objects are equal and 1 if this is larger than given
  // object.
  
  const mithep::Vertex *v = dynamic_cast<const mithep::Vertex *>(o);
  if (!v)
    return 1;
  
  Int_t myn = NTracks();
  Int_t n   = v->NTracks();
  if (myn>n)
    return -1;
  else if (n>myn)
    return +1;

  Double_t myd = Chi2();
  Double_t d   = v->Chi2();
  if (myd<d)
    return -1;
  else if (d<myd)
    return +1;
  
  return 0;
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Vertex::TrackWeight(const Track *t) const
{
  for (UInt_t i = 0; i < fTracks.Entries(); i++) {
    if (t == fTracks.At(i))
      return fTrkWeights.At(i);
  }

  return -1;
}
#endif
