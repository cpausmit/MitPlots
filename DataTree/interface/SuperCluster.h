//--------------------------------------------------------------------------------------------------
// $Id: SuperCluster.h,v 1.28 2013/07/01 20:18:00 paus Exp $
//
// SuperCluster
//
// This class holds the super cluster information.
//
// Authors: C.Paus, J.Bendavid, S.Xie
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_SUPERCLUSTER_H
#define MITANA_DATATREE_SUPERCLUSTER_H

#include <TMath.h>
#include "MitCommon/DataFormats/interface/Vect3C.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/PsCluster.h"
#include "MitAna/DataTree/interface/CaloTower.h"
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"

namespace mithep
{
  class SuperCluster : public DataObject
  {
  public:
    SuperCluster() : fEnergy(0), fEtaWidth(0), fPreshowerEnergy(0),
                     fPhiWidth(0), fRawEnergy(0),
                     fEtaC(-99.), fEtaS(-99.), fEtaM(-99.),
                     fPhiC(-99.), fPhiS(-99.), fPhiM(-99.),
                     fXC(-99.), fXS(-99.), fXM(-99.), fXZ(-99.),
                     fYC(-99.), fYS(-99.), fYM(-99.), fYZ(-99.),
                     fPreshowerEnergyPlane1(0.), fPreshowerEnergyPlane2(0.),
                     fPsEffWidthSigmaXX(-99.), fPsEffWidthSigmaYY(-99.),
                     fRoundness(-99.), fAngle(-99.) {}

    void                   AddCluster(const BasicCluster *c)          { fClusters.Add(c);        }
    void                   AddPsClust(const PsCluster *c)             { fPsClusts.Add(c);        }
    void                   AddTower(const CaloTower *t)               { fCaloTowers.Add(t);      }
    const BasicCluster    *Cluster(UInt_t i)       const { return fClusters.At(i);               }
    UInt_t                 ClusterSize()           const { return fClusters.Entries();           }
    UInt_t                 NClusters()             const { return fClusters.Entries();           }
    UInt_t                 NHits()                 const;
    const PsCluster       *PsClust(UInt_t i)       const { return fPsClusts.At(i);               }    
    UInt_t                 NPsClusts()             const { return fPsClusts.Entries();           }    
    Int_t                  Compare(const TObject *o) const;
    Double_t               Energy()                const { return fEnergy;                       }
    Double_t               Et()                    const;
    Double_t               Eta()                   const { return fPoint.Eta();                  }
    Double_t               AbsEta()                const { return TMath::Abs(Eta());             }
    Double_t               EtaWidth()              const { return fEtaWidth;                     }
    Bool_t                 HasSeed()               const { return fSeedRef.IsValid();            }
    Bool_t                 HasTower(const CaloTower *t) const { return fCaloTowers.HasObject(t); }
    Double_t               HcalDepth1Energy()      const { return fHcalDepth1Energy;             }
    Double_t               HcalDepth2Energy()      const { return fHcalDepth2Energy;             }
    Double_t               HadDepth1OverEm()       const { return fHcalDepth1Energy/fEnergy;     }
    Double_t               HadDepth2OverEm()       const { return fHcalDepth2Energy/fEnergy;     }
    Double_t               HadOverEm()             const { return (fHcalDepth1Energy+
                                                                   fHcalDepth2Energy)/fEnergy;   }
    Bool_t                 IsSortable()            const { return kTRUE;                         }
    EObjType               ObjType()               const { return kSuperCluster;                 }
    UInt_t                 NTowers()               const { return fCaloTowers.Entries();         }
    Double_t               Phi()                   const { return fPoint.Phi();                  }
    Double_t               PhiWidth()              const { return fPhiWidth;                     }
    ThreeVectorC           Point()                 const { return fPoint.V();                    }
    void                   Print(Option_t *opt="") const;
    Double_t               PreshowerEnergy()       const { return fPreshowerEnergy;              }
    Double_t               PreshowerEnergyPlane1() const { return fPreshowerEnergyPlane1;        }
    Double_t               PreshowerEnergyPlane2() const { return fPreshowerEnergyPlane2;        }
    Double_t               RawEnergy()             const { return fRawEnergy;                    }
    Double_t               Rho()                   const { return fPoint.Rho();                  }
    Double_t               R9()                    const { return fSeedRef.Obj()->E3x3()/fRawEnergy; }
    const BasicCluster    *Seed()                  const { return fSeedRef.Obj();                }
    const CaloTower       *Tower(UInt_t i)         const { return fCaloTowers.At(i);             }
    Double_t               EtaC()                  const { return fEtaC;                         }
    Double_t               EtaS()                  const { return fEtaS;                         }
    Double_t               EtaM()                  const { return fEtaM;                         }
    Double_t               PhiC()                  const { return fPhiC;                         }
    Double_t               PhiS()                  const { return fPhiS;                         }
    Double_t               PhiM()                  const { return fPhiM;                         }
    Double_t               XC()                    const { return fXC;                           }
    Double_t               XS()                    const { return fXS;                           }
    Double_t               XM()                    const { return fXM;                           }
    Double_t               XZ()                    const { return fXZ;                           }
    Double_t               YC()                    const { return fYC;                           }
    Double_t               YS()                    const { return fYS;                           }
    Double_t               YM()                    const { return fYM;                           }
    Double_t               YZ()                    const { return fYZ;                           }
    Double_t               Time()                  const { return fTime;                         }
    Double_t               SeedTime()              const { return fSeedTime;                     }
    Double_t               LeadTimeSpan()          const { return fLeadTimeSpan;                 }
    Double_t               SubLeadTimeSpan()       const { return fSubLeadTimeSpan;              }
    Double_t               PsEffWidthSigmaXX()     const { return fPsEffWidthSigmaXX;            }
    Double_t               PsEffWidthSigmaYY()     const { return fPsEffWidthSigmaYY;            }
    Double_t               Roundness()             const { return fRoundness;                    }
    Double_t               Angle()                 const { return fAngle;                        }

    void                   SetEnergy(Double_t energy)                 { fEnergy = energy;        }
    void                   SetEtaWidth(Double_t etaWidth)             { fEtaWidth = etaWidth;    }
    void                   SetPhiWidth(Double_t phiWidth)             { fPhiWidth = phiWidth;    }
    void                   SetPreshowerEnergy(Double_t e)             { fPreshowerEnergy = e;    }
    void                   SetPreshowerEnergyPlane1(Double_t e)       { fPreshowerEnergyPlane1 = e; }
    void                   SetPreshowerEnergyPlane2(Double_t e)       { fPreshowerEnergyPlane2 = e; }
    void                   SetRawEnergy(Double_t rawEnergy)           { fRawEnergy = rawEnergy;  }
    void                   SetHcalDepth1Energy(Double_t x)            { fHcalDepth1Energy = x;   }
    void                   SetHcalDepth2Energy(Double_t x)            { fHcalDepth2Energy = x;   }
    void                   SetSeed(const BasicCluster *s)             { fSeedRef = s;            }
    void                   SetXYZ(Double_t x, Double_t y, Double_t z) { fPoint.SetXYZ(x,y,z);    }
    void                   SetEtaC(Double_t x)                        { fEtaC = x;               }
    void                   SetEtaS(Double_t x)                        { fEtaS = x;               }
    void                   SetEtaM(Double_t x)                        { fEtaM = x;               }
    void                   SetPhiC(Double_t x)                        { fPhiC = x;               }
    void                   SetPhiS(Double_t x)                        { fPhiS = x;               }
    void                   SetPhiM(Double_t x)                        { fPhiM = x;               }
    void                   SetXC(Double_t x)                          { fXC = x;                 }
    void                   SetXS(Double_t x)                          { fXS = x;                 }
    void                   SetXM(Double_t x)                          { fXM = x;                 }
    void                   SetXZ(Double_t x)                          { fXZ = x;                 }
    void                   SetYC(Double_t x)                          { fYC = x;                 }
    void                   SetYS(Double_t x)                          { fYS = x;                 }
    void                   SetYM(Double_t x)                          { fYM = x;                 }
    void                   SetYZ(Double_t x)                          { fYZ = x;                 }
    void                   SetTime(Double_t x)                        { fTime = x;               }
    void                   SetSeedTime(Double_t x)                    { fSeedTime = x;           }
    void                   SetLeadTimeSpan(Double_t x)                { fLeadTimeSpan = x;       }
    void                   SetSubLeadTimeSpan(Double_t x)             { fSubLeadTimeSpan = x;    }
    void                   SetPsEffWidthSigmaXX(Double_t x)           { fPsEffWidthSigmaXX = x;  }
    void                   SetPsEffWidthSigmaYY(Double_t x)           { fPsEffWidthSigmaYY = x;  }
    void                   SetRoundness(Double_t x)                   { fRoundness = x;          }
    void                   SetAngle(Double_t x)                       { fAngle = x;              }

    // Some structural tools
    void                   Mark(UInt_t i=1)  const;

  protected:
    Vect3C                  fPoint;                //centroid Position
    Double32_t              fEnergy;               //[0,0,14]super cluster energy
    Double32_t              fEtaWidth;             //[0,0,14]width in Phi
    Double32_t              fPreshowerEnergy;      //[0,0,14]energy in the preshower
    Double32_t              fPhiWidth;             //[0,0,14]width in Phi
    Double32_t              fRawEnergy;            //[0,0,14]super cluster raw energy
    Double32_t              fHcalDepth1Energy;     //[0,0,14] hcal depth1 over ECAL energy
    Double32_t              fHcalDepth2Energy;     //[0,0,14] hcal depth2 over ECAL energy
    RefArray<BasicCluster>  fClusters;             //assigned basic clusters
    Ref<BasicCluster>       fSeedRef;              //seed cluster
    RefArray<CaloTower>     fCaloTowers;           //calo towers (matched by detid)
    Double32_t              fEtaC;                 //local coordinates
    Double32_t              fEtaS;                 //local coordinates
    Double32_t              fEtaM;                 //local coordinates
    Double32_t              fPhiC;                 //local coordinates
    Double32_t              fPhiS;                 //local coordinates
    Double32_t              fPhiM;                 //local coordinates
    Double32_t              fXC;                   //local coordinates
    Double32_t              fXS;                   //local coordinates
    Double32_t              fXM;                   //local coordinates
    Double32_t              fXZ;                   //local coordinates
    Double32_t              fYC;                   //local coordinates
    Double32_t              fYS;                   //local coordinates
    Double32_t              fYM;                   //local coordinates
    Double32_t              fYZ;                   //local coordinates
    Double32_t              fTime;                 //ecal timing (weighted average)
    Double32_t              fSeedTime;             //ecal timing (seed crystal)
    Double32_t              fLeadTimeSpan;         //ecal supercluster max timespan (seed vs. any other xtal)
    Double32_t              fSubLeadTimeSpan;      //ecal supercluster next-to-max timespan (seed vs. any other xtal)
    Double32_t              fPreshowerEnergyPlane1;//local coordinates
    Double32_t              fPreshowerEnergyPlane2;//local coordinates
    Double32_t              fPsEffWidthSigmaXX;    //preshower cluster width in x plane
    Double32_t              fPsEffWidthSigmaYY;    //preshower cluster width in y plane
    RefArray<PsCluster>     fPsClusts;             //assigned preshower clusters
    Double32_t              fRoundness;            //smaller_SCaxis/larger_SCaxis: barrel only
    Double32_t              fAngle;                //angle between SC axis and beam axis: barrel only

    ClassDef(SuperCluster, 7) // Super cluster class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::SuperCluster::Mark(UInt_t ib) const
{
  // mark myself
  mithep::DataObject::Mark(ib);
  // mark my dependencies if they are there
  if (fSeedRef.IsValid())
    fSeedRef.Obj()->Mark(ib);
  fClusters  .Mark(ib);
  fPsClusts  .Mark(ib);
  fCaloTowers.Mark(ib);
}


//--------------------------------------------------------------------------------------------------
inline UInt_t mithep::SuperCluster::NHits() const
{
  // Return transverse energy.

  UInt_t nhits = 0;
  for (UInt_t i=0; i<fClusters.GetEntries(); ++i) {
    nhits += fClusters.At(i)->NHits();
  }
  return nhits;
}


//--------------------------------------------------------------------------------------------------
inline Double_t mithep::SuperCluster::Et() const
{
  // Return transverse energy.

  return fEnergy*fPoint.Rho()/fPoint.V().R();
}

//--------------------------------------------------------------------------------------------------
inline Int_t mithep::SuperCluster::Compare(const TObject *o) const
{
  // Default compare function for sorting according to transverse momentum.
  // Returns -1 if this object is smaller than given object, 0 if objects are
  // equal and 1 if this is larger than given object.

  const mithep::SuperCluster *s = dynamic_cast<const mithep::SuperCluster *>(o);
  if (!s)
    return 1;

  Double_t mye = Energy();
  Double_t e   = s->Energy();
  if (mye>e)
    return -1;
  else if (e>mye)
    return +1;
  return 0;
}
#endif
