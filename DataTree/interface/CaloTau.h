//--------------------------------------------------------------------------------------------------
// $Id: CaloTau.h,v 1.2 2009/03/12 15:55:38 bendavid Exp $
//
// CaloTau
//
// This class holds information about reconstructed tau based on calorimeter towers, ecal basic
// clusters, and tracks
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_CALOTAU_H
#define MITANA_DATATREE_CALOTAU_H
 
#include "MitAna/DataTree/interface/Tau.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/CaloJet.h"

namespace mithep 
{
  class CaloTau : public Tau
  {
    public:
      CaloTau() : fLeadTrackSignedD0Significance(0), fLeadTrack3x3HCalEt(0),
                  fLeadTrack3x3HCalDEta(0), fSignalTracksMass(0),
                  fTracksMass(0), fIsoTrackPtSum(0), fIsoECalEtSum(0),
                  fMaxHCalHitEt(0) {}
      CaloTau(Double_t px, Double_t py, Double_t pz, Double_t e) : 
                  Tau(px,py,pz,e),
                  fLeadTrackSignedD0Significance(0), fLeadTrack3x3HCalEt(0),
                  fLeadTrack3x3HCalDEta(0), fSignalTracksMass(0),
                  fTracksMass(0), fIsoTrackPtSum(0), fIsoECalEtSum(0),
                  fMaxHCalHitEt(0) {}

      void                AddIsoTrack(const Track *t)       { fIsoTracks.Add(t);                 }
      void                AddSignalTrack(const Track *t)    { fSignalTracks.Add(t);              }
      void                AddNeutralBC(const BasicCluster* c) { fNeutralBCs.Add(c);              } 
      void                SetCaloJet(const CaloJet *j)      { fCaloJet = j;                      }
      void                SetLeadTrack(const Track *t)      { fLeadTrack = t;                    }   
                   
      const Track        *LeadTrack()                 const { return fLeadTrack.Obj();           }
      const CaloJet      *SourceCaloJet()             const { return fCaloJet.Obj();             }
      const Jet          *SourceJet()                 const { return SourceCaloJet();            }
 
      UInt_t              NIsoTracks()                const { return fIsoTracks.GetEntries();    }
      UInt_t              NSignalTracks()             const { return fSignalTracks.GetEntries(); }
      UInt_t              NNeutralBCs()               const { return fNeutralBCs.GetEntries();   } 
      const Track        *SignalTrack(UInt_t i)       const { return fSignalTracks.At(i);        }
      const Track        *IsoTrack(UInt_t i)          const { return fIsoTracks.At(i);           }
      const BasicCluster *NeutralBC(UInt_t i)         const { return fNeutralBCs.At(i);          }
                       
      EObjType            ObjType()                   const { return kCaloTau;                   }  
      
      Double_t            LeadTrackSignedD0Significance() const { return fLeadTrackSignedD0Significance; } 
      Double_t            LeadTrack3x3HCalEt()        const { return fLeadTrack3x3HCalEt;        }
      Double_t            LeadTrack3x3HCalDEta()      const { return fLeadTrack3x3HCalDEta;      }
      Double_t            SignalTracksMass()          const { return fSignalTracksMass;          }
      Double_t            TracksMass()                const { return fTracksMass;                }
      Double_t            IsoTrackPtSum()             const { return fIsoTrackPtSum;             }
      Double_t            IsoECalEtSum()              const { return fIsoECalEtSum;              }
      Double_t            MaxHCalHitEt()             const { return fMaxHCalHitEt;              }
      
      void                SetLeadTrackSignedD0Significance(Double_t x) { fLeadTrackSignedD0Significance = x; } 
      void                SetLeadTrack3x3HCalEt(Double_t x)     { fLeadTrack3x3HCalEt = x;        }
      void                SetLeadTrack3x3HCalDEta(Double_t x)   { fLeadTrack3x3HCalDEta = x;      }
      void                SetSignalTracksMass(Double_t x)       { fSignalTracksMass = x;          }
      void                SetTracksMass(Double_t x)             { fTracksMass = x;                }
      void                SetIsoTrackPtSum(Double_t x)          { fIsoTrackPtSum = x;             }
      void                SetIsoECalEtSum(Double_t x)           { fIsoECalEtSum = x;              }
      void                SetMaxHCalHitEt(Double_t x)           { fMaxHCalHitEt = x;              }
        


    protected:

      Double32_t              fLeadTrackSignedD0Significance;  //signed lead track D0 significance
      Double32_t              fLeadTrack3x3HCalEt; //sum HCal et in 3x3 calo tower region around lead track
      Double32_t              fLeadTrack3x3HCalDEta; //abs(delta eta) btw lead track and hottest hcal rec hit in 3x3 region
      Double32_t              fSignalTracksMass;   // invariant mass of signal tracks
      Double32_t              fTracksMass;         // invariant mass of signal and isolation tracks
      Double32_t              fIsoTrackPtSum;     //sum pt of tracks in isolation annulus
      Double32_t              fIsoECalEtSum;      //sum et of ecal rechits in isolation annulus
      Double32_t              fMaxHCalHitEt;      //Et of largest Et HCal rechit
      Ref<Track>              fLeadTrack;         //leading track in signal cone
      Ref<CaloJet>            fCaloJet;           //original reconstructed calo jet
      RefArray<Track>         fSignalTracks;      //tracks in signal cone
      RefArray<Track>         fIsoTracks;         //tracks in isolation annulus
      RefArray<BasicCluster>  fNeutralBCs;        //neutral Ecal basic clusters

    ClassDef(CaloTau, 1) // CaloTau class
  };
}
#endif
