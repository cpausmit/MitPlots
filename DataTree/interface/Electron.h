//--------------------------------------------------------------------------------------------------
// Electron
//
// This class holds information about reconstructed electrons from CMSSW.
//
// Authors: C.Paus, G.Ceballos, C.Loizides, J.Bendavid, S.Xie, Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_ELECTRON_H
#define MITANA_DATATREE_ELECTRON_H
 
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/ChargedParticle.h"
#include "MitAna/DataCont/interface/Ref.h"

namespace mithep 
{
  class Electron : public ChargedParticle
  {
  public:
    Electron() {}

    const Track         *BestTrk()                     const;
    Double_t             D0PV()                        const { return fD0PV; }
    Double_t             D0PVErr()                     const { return fD0PVErr; }
    Double_t             D0PVSignificance()            const { return fD0PV/fD0PVErr; }
    Double_t             Ip3dPV()                      const { return fIp3dPV; }
    Double_t             Ip3dPVErr()                   const { return fIp3dPVErr; }
    Double_t             Ip3dPVSignificance()          const { return fIp3dPV/fIp3dPVErr; }
    Double_t             D0PVBS()                      const { return fD0PVBS; }
    Double_t             D0PVBSErr()                   const { return fD0PVBSErr; }
    Double_t             D0PVBSSignificance()          const { return fD0PVBS/fD0PVBSErr; }
    Double_t             Ip3dPVBS()                    const { return fIp3dPVBS; }
    Double_t             Ip3dPVBSErr()                 const { return fIp3dPVBSErr; }
    Double_t             Ip3dPVBSSignificance()        const { return fIp3dPVBS/fIp3dPVBSErr; }
    Double_t             D0PVCkf()                     const { return fD0PVCkf; }
    Double_t             D0PVCkfErr()                  const { return fD0PVCkfErr; }
    Double_t             D0PVCkfSignificance()         const { return fD0PVCkf/fD0PVCkfErr; }
    Double_t             Ip3dPVCkf()                   const { return fIp3dPVCkf; }
    Double_t             Ip3dPVCkfErr()                const { return fIp3dPVCkfErr; }
    Double_t             Ip3dPVCkfSignificance()       const { return fIp3dPVCkf/fIp3dPVCkfErr; }
    Double_t             D0PVBSCkf()                   const { return fD0PVBSCkf; }
    Double_t             D0PVBSCkfErr()                const { return fD0PVBSCkfErr; }
    Double_t             D0PVBSCkfSignificance()       const { return fD0PVBSCkf/fD0PVBSCkfErr; }
    Double_t             Ip3dPVBSCkf()                 const { return fIp3dPVBSCkf; }
    Double_t             Ip3dPVBSCkfErr()              const { return fIp3dPVBSCkfErr; }
    Double_t             Ip3dPVBSCkfSignificance()     const { return fIp3dPVBSCkf/fIp3dPVBSCkfErr; }
    Double_t             D0PVUB()                      const { return fD0PVUB; }
    Double_t             D0PVUBErr()                   const { return fD0PVUBErr; }
    Double_t             D0PVUBSignificance()          const { return fD0PVUB/fD0PVUBErr; }
    Double_t             Ip3dPVUB()                    const { return fIp3dPVUB; }
    Double_t             Ip3dPVUBErr()                 const { return fIp3dPVUBErr; }
    Double_t             Ip3dPVUBSignificance()        const { return fIp3dPVUB/fIp3dPVUBErr; }
    Double_t             D0PVUBBS()                    const { return fD0PVUBBS; }
    Double_t             D0PVUBBSErr()                 const { return fD0PVUBBSErr; }
    Double_t             D0PVUBBSSignificance()        const { return fD0PVUBBS/fD0PVUBBSErr; }
    Double_t             Ip3dPVUBBS()                  const { return fIp3dPVUBBS; }
    Double_t             Ip3dPVUBBSErr()               const { return fIp3dPVUBBSErr; }
    Double_t             Ip3dPVUBBSSignificance()      const { return fIp3dPVUBBS/fIp3dPVUBBSErr; }
    Double_t             D0PVUBCkf()                   const { return fD0PVUBCkf; }
    Double_t             D0PVUBCkfErr()                const { return fD0PVUBCkfErr; }
    Double_t             D0PVUBCkfSignificance()       const { return fD0PVUBCkf/fD0PVUBCkfErr; }
    Double_t             Ip3dPVUBCkf()                 const { return fIp3dPVUBCkf; }
    Double_t             Ip3dPVUBCkfErr()              const { return fIp3dPVUBCkfErr; }
    Double_t             Ip3dPVUBCkfSignificance()     const { return fIp3dPVUBCkf/fIp3dPVUBCkfErr; }
    Double_t             D0PVUBBSCkf()                 const { return fD0PVUBBSCkf; }
    Double_t             D0PVUBBSCkfErr()              const { return fD0PVUBBSCkfErr; }
    Double_t             D0PVUBBSCkfSignificance()     const { return fD0PVUBBSCkf/fD0PVUBBSCkfErr; }
    Double_t             Ip3dPVUBBSCkf()               const { return fIp3dPVUBBSCkf; }
    Double_t             Ip3dPVUBBSCkfErr()            const { return fIp3dPVUBBSCkfErr; }
    Double_t             Ip3dPVUBBSCkfSignificance()   const { return fIp3dPVUBBSCkf/fIp3dPVUBBSCkfErr; }
    Double_t             GsfPVCompatibility()          const { return fGsfPVCompatibility; }
    Double_t             GsfPVBSCompatibility()        const { return fGsfPVBSCompatibility; }
    Double_t             GsfPVCompatibilityMatched()   const { return fGsfPVCompatibilityMatched; }
    Double_t             GsfPVBSCompatibilityMatched() const { return fGsfPVBSCompatibilityMatched; }
    Double_t             ConvPartnerDCotTheta()        const { return fConvPartnerDCotTheta; }
    Double_t             ConvPartnerDist()             const { return fConvPartnerDist; }
    Double_t             ConvPartnerRadius()           const { return fConvPartnerRadius; }
    Int_t                ConvFlag()                    const { return fConvFlag; }
    Int_t                Classification()              const { return fClassification; }
    Double_t             CovEtaEta()                   const { return fCovEtaEta; }
    Double_t             CoviEtaiEta(Bool_t force = kFALSE) const
    { return force || fCoviEtaiEta5x5 < 0. ? fCoviEtaiEta : fCoviEtaiEta5x5; }
    Double_t             CoviEtaiEta5x5()              const { return fCoviEtaiEta5x5; }
    Double_t             DeltaEtaSuperClusterTrackAtVtx() const { return fDeltaEtaSuperClTrkAtVtx; }
    Double_t             DeltaEtaSeedClusterTrackAtCalo() const { return fDeltaEtaSeedClTrkAtCalo; }
    Double_t             DeltaPhiSuperClusterTrackAtVtx() const { return fDeltaPhiSuperClTrkAtVtx; }
    Double_t             DeltaPhiSeedClusterTrackAtCalo() const { return fDeltaPhiSeedClTrkAtCalo; }
    Double_t             E15()                            const { return fE15; }
    Double_t             E25Max()                         const { return fE25Max; }
    Double_t             E55()                            const { return fE55; }
    Double_t             ESuperClusterOverP()             const { return fESuperClusterOverP; }
    Double_t             ESeedClusterOverPout()           const { return fESeedClusterOverPout; }
    Double_t             EEleClusterOverPout()            const { return fEEleClusterOverPout; }
    Double_t             ESeedClusterOverPIn()            const;
    Double_t             FBrem()                          const { return fFBrem; }
    Double_t             FBremOld()                       const { return (PIn() - POut())/PIn(); }
    Double_t             FracSharedHits()                 const { return fFracSharedHits; }
    const Track         *GsfTrk()                         const { return fGsfTrackRef.Obj(); }
    Double_t             HadronicOverEm()                 const { return fHadronicOverEm; }
    Double_t             HcalDepth1OverEcal()             const { return fHcalDepth1OverEcal; }
    Double_t             HcalDepth2OverEcal()             const { return fHcalDepth2OverEcal; }
    Bool_t               HasGsfTrk()                      const { return fGsfTrackRef.IsValid(); }
    Bool_t               HasTrackerTrk()                  const { return fTrackerTrackRef.IsValid(); }
    Bool_t               HasSuperCluster()                const { return fSuperClusterRef.IsValid(); }
    Double_t             IDLikelihood()                   const { return fIDLikelihood; }
    Bool_t               IsEnergyScaleCorrected()         const { return fIsEnergyScaleCorrected; }
    Bool_t               IsMomentumCorrected()            const { return fIsMomentumCorrected; }
    Bool_t               IsEB()                           const { return fIsEB; }
    Bool_t               IsEE()                           const { return fIsEE; }
    Bool_t               IsEBEEGap()                      const { return fIsEBEEGap; }
    Bool_t               IsEBEtaGap()                     const { return fIsEBEtaGap; }
    Bool_t               IsEBPhiGap()                     const { return fIsEBPhiGap; }
    Bool_t               IsEEDeeGap()                     const { return fIsEEDeeGap; }
    Bool_t               IsEERingGap()                    const { return fIsEERingGap; }
    Bool_t               IsEcalDriven()                   const { return fIsEcalDriven; }
    Bool_t               IsTrackerDriven()                const { return fIsTrackerDriven; }
    Double_t             Mva()                            const { return fMva; }
    Double_t             NumberOfClusters()               const { return fNumberOfClusters; }
    EObjType             ObjType()                        const { return kElectron; }
    Double_t             PassLooseID()                    const { return fPassLooseID; }
    Double_t             PassTightID()                    const { return fPassTightID; }
    Double_t             PIn()                            const { return fPIn; }
    Double_t             POut()                           const { return fPOut; }
    const SuperCluster  *SCluster()                       const { return fSuperClusterRef.Obj(); }
    const SuperCluster  *ECALOnlySCluster()               const { return fPFSuperClusterRef.Obj(); }
    const SuperCluster  *PFSCluster()                     const { return ECALOnlySCluster(); } // backward compatibility
    Double_t             ScPixCharge()                    const { return fScPixCharge; }
    Double_t             EcalRecHitIsoDr04()              const { return fEcalJurassicIsolation; }
    Double_t             HcalTowerSumEtDr04()             const
    { return HcalDepth1TowerSumEtDr04() + HcalDepth2TowerSumEtDr04(); }
    Double_t             HcalDepth1TowerSumEtDr04()       const { return fHcalDepth1TowerSumEtDr04; }
    Double_t             HcalDepth2TowerSumEtDr04()       const { return fHcalDepth2TowerSumEtDr04; }
    Double_t             TrackIsolationDr04()             const { return fTrackIsolationDr04; }
    Double_t             EcalRecHitIsoDr03()              const { return fEcalRecHitSumEtDr03; }
    Double_t             HcalTowerSumEtDr03()             const { return fCaloTowerIsolation; }
    Double_t             HcalDepth1TowerSumEtDr03()       const { return fHcalDepth1TowerSumEtDr03; }
    Double_t             HcalDepth2TowerSumEtDr03()       const { return fHcalDepth2TowerSumEtDr03; }
    Double_t             TrackIsolationDr03()             const { return fTrackIsolation; }
    Double_t             PFChargedHadronIso()             const { return fPFChargedHadronIso; }
    Double_t             PFNeutralHadronIso()             const { return fPFNeutralHadronIso; }
    Double_t             PFPhotonIso()                    const { return fPFPhotonIso; }
    Bool_t               MatchesVertexConversion()        const { return fMatchesVertexConversion; }
    UInt_t               NAmbiguousGsfTracks()            const { return fAmbiguousGsfTracks.Entries(); }
    Bool_t               HasAmbiguousGsfTrack(const Track *t) const { return fAmbiguousGsfTracks.HasObject(t); }
    const Track         *AmbiguousGsfTrack(UInt_t i)      const { return fAmbiguousGsfTracks.At(i); }
    Int_t                CTFTrkNLayersWithMeasurement()   const { return fCTFTrkNLayersWithMeasurement; }
    Double_t             HadOverEmTow()                   const { return fHadOverEmTow;       }
    Double_t             HcalIsoTowDr03()                 const { return fHCalIsoTowDr03;    }
    Double_t             HcalIsoTowDr04()                 const { return fHCalIsoTowDr04;    } 
    Double_t             EcalEnergy()                     const { return fEcalEnergy;      }
    Double_t             EcalEnergyError()                const { return fEcalEnergyError; }
    Double_t             TrackMomentumError()             const { return fTrackMomentumError; }

    void                 AddAmbiguousGsfTrack(const Track *t)          { fAmbiguousGsfTracks.Add(t); }
    void                 SetCharge(Char_t x)                           { fCharge = x; ClearCharge(); }
    void                 SetScPixCharge(Char_t x)                      { fScPixCharge = x; }
    void                 SetD0PV(Double_t x)                           { fD0PV = x; }
    void                 SetD0PVErr(Double_t x)                        { fD0PVErr = x; }
    void                 SetIp3dPV(Double_t x)                         { fIp3dPV = x; }
    void                 SetIp3dPVErr(Double_t x)                      { fIp3dPVErr = x; }
    void                 SetD0PVBS(Double_t x)                         { fD0PVBS = x; }
    void                 SetD0PVBSErr(Double_t x)                      { fD0PVBSErr = x; }
    void                 SetIp3dPVBS(Double_t x)                       { fIp3dPVBS = x; }
    void                 SetIp3dPVBSErr(Double_t x)                    { fIp3dPVBSErr = x; }
    void                 SetD0PVCkf(Double_t x)                        { fD0PVCkf = x; }
    void                 SetD0PVCkfErr(Double_t x)                     { fD0PVCkfErr = x; }
    void                 SetIp3dPVCkf(Double_t x)                      { fIp3dPVCkf = x; }
    void                 SetIp3dPVCkfErr(Double_t x)                   { fIp3dPVCkfErr = x; }
    void                 SetD0PVBSCkf(Double_t x)                      { fD0PVBSCkf = x; }
    void                 SetD0PVBSCkfErr(Double_t x)                   { fD0PVBSCkfErr = x; }
    void                 SetIp3dPVBSCkf(Double_t x)                    { fIp3dPVBSCkf = x; }
    void                 SetIp3dPVBSCkfErr(Double_t x)                 { fIp3dPVBSCkfErr = x; }
    void                 SetD0PVUB(Double_t x)                         { fD0PVUB = x; }
    void                 SetD0PVUBErr(Double_t x)                      { fD0PVUBErr = x; }
    void                 SetIp3dPVUB(Double_t x)                       { fIp3dPVUB = x; }
    void                 SetIp3dPVUBErr(Double_t x)                    { fIp3dPVUBErr = x; }
    void                 SetD0PVUBBS(Double_t x)                       { fD0PVUBBS = x; }
    void                 SetD0PVUBBSErr(Double_t x)                    { fD0PVUBBSErr = x; }
    void                 SetIp3dPVUBBS(Double_t x)                     { fIp3dPVUBBS = x; }
    void                 SetIp3dPVUBBSErr(Double_t x)                  { fIp3dPVUBBSErr = x; }
    void                 SetD0PVUBCkf(Double_t x)                      { fD0PVUBCkf = x; }
    void                 SetD0PVUBCkfErr(Double_t x)                   { fD0PVUBCkfErr = x; }
    void                 SetIp3dPVUBCkf(Double_t x)                    { fIp3dPVUBCkf = x; }
    void                 SetIp3dPVUBCkfErr(Double_t x)                 { fIp3dPVUBCkfErr = x; }
    void                 SetD0PVUBBSCkf(Double_t x)                    { fD0PVUBBSCkf = x; }
    void                 SetD0PVUBBSCkfErr(Double_t x)                 { fD0PVUBBSCkfErr = x; }
    void                 SetIp3dPVUBBSCkf(Double_t x)                  { fIp3dPVUBBSCkf = x; }
    void                 SetIp3dPVUBBSCkfErr(Double_t x)               { fIp3dPVUBBSCkfErr = x; }
    void                 SetGsfPVCompatibility(Double_t x)             { fGsfPVCompatibility = x; }
    void                 SetGsfPVBSCompatibility(Double_t x)           { fGsfPVBSCompatibility = x; }
    void                 SetGsfPVCompatibilityMatched(Double_t x)      { fGsfPVCompatibilityMatched = x; }
    void                 SetGsfPVBSCompatibilityMatched(Double_t x)    { fGsfPVBSCompatibilityMatched = x; }
    void                 SetConvPartnerDCotTheta(Double_t x)           { fConvPartnerDCotTheta = x; }
    void                 SetConvPartnerDist(Double_t x)                { fConvPartnerDist = x; }
    void                 SetConvPartnerRadius(Double_t x)              { fConvPartnerRadius = x; }
    void                 SetConvFlag(Int_t n)                          { fConvFlag = n; }
    void                 SetClassification(Int_t x)                    { fClassification = x; }
    void                 SetCovEtaEta(Double_t x)                      { fCovEtaEta = x; }
    void                 SetCoviEtaiEta(Double_t x)                    { fCoviEtaiEta = x; }
    void                 SetCoviEtaiEta5x5(Double_t x)                 { fCoviEtaiEta5x5 = x; }
    void                 SetDeltaEtaSuperClusterTrackAtVtx(Double_t x)  
    { fDeltaEtaSuperClTrkAtVtx = x; }
    void                 SetDeltaEtaSeedClusterTrackAtCalo(Double_t x)  
    { fDeltaEtaSeedClTrkAtCalo = x; }
    void                 SetDeltaPhiSuperClusterTrackAtVtx(Double_t x)  
    { fDeltaPhiSuperClTrkAtVtx = x; }
    void                 SetDeltaPhiSeedClusterTrackAtCalo(Double_t x)  
    { fDeltaPhiSeedClTrkAtCalo = x; }
    void                 SetE15(Double_t x)                     { fE15 = x; }
    void                 SetE25Max(Double_t x)                  { fE25Max = x; }
    void                 SetE55(Double_t x)                     { fE55 = x; }
    void                 SetESeedClusterOverPout(Double_t x)    { fESeedClusterOverPout = x; }
    void                 SetEEleClusterOverPout(Double_t x)     { fEEleClusterOverPout = x; }
    void                 SetESuperClusterOverP(Double_t x)      { fESuperClusterOverP = x; }
    void                 SetFBrem(Double_t x)                   { fFBrem = x; }
    void                 SetFracSharedHits(Double_t x)          { fFracSharedHits = x; }
    void	         SetGsfTrk(const Track* t)                     
    { fGsfTrackRef = t; ClearCharge(); }
    void                 SetHadronicOverEm(Double_t x)          { fHadronicOverEm = x; }
    void                 SetHcalDepth1OverEcal(Double_t x)      { fHcalDepth1OverEcal = x; }
    void                 SetHcalDepth2OverEcal(Double_t x)      { fHcalDepth2OverEcal = x; }
    void                 SetIDLikelihood(Double_t x)            { fIDLikelihood = x; }
    void                 SetIsEnergyScaleCorrected(Bool_t x)    { fIsEnergyScaleCorrected = x; }
    void                 SetIsMomentumCorrected(Bool_t x)       { fIsMomentumCorrected = x; }
    void                 SetNumberOfClusters(Double_t x)        { fNumberOfClusters = x; }
    void                 SetPIn(Double_t pIn)                   { fPIn = pIn; }
    void                 SetPOut(Double_t pOut)                 { fPOut = pOut; }
    void                 SetPassLooseID(Double_t passLooseID)   { fPassLooseID = passLooseID; }
    void                 SetPassTightID(Double_t passTightID)   { fPassTightID = passTightID; }
    void                 SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi);
    void	         SetSuperCluster(const SuperCluster* sc) 
    { fSuperClusterRef = sc; }
    void	         SetECALOnlySuperCluster(const SuperCluster* sc) 
    { fPFSuperClusterRef = sc; }                             
    void	         SetTrackerTrk(const Track* t)                 
    { fTrackerTrackRef = t; ClearCharge(); }
    void                 SetConvPartnerTrk(const Track *t)
    { fConvPartnerTrackRef = t; }
    void                 SetEcalRecHitIsoDr04(Double_t x)        { fEcalJurassicIsolation = x; }
    void                 SetHcalDepth1TowerSumEtDr04(Double_t x) { fHcalDepth1TowerSumEtDr04 = x; }
    void                 SetHcalDepth2TowerSumEtDr04(Double_t x) { fHcalDepth2TowerSumEtDr04 = x; }
    void                 SetTrackIsolationDr04(Double_t x)       { fTrackIsolationDr04 = x; }
    void                 SetEcalRecHitIsoDr03(Double_t x)        { fEcalRecHitSumEtDr03 = x; }
    void                 SetHcalTowerSumEtDr03(Double_t x)       { fCaloTowerIsolation = x; }
    void                 SetHcalDepth1TowerSumEtDr03(Double_t x) { fHcalDepth1TowerSumEtDr03 = x; }
    void                 SetHcalDepth2TowerSumEtDr03(Double_t x) { fHcalDepth2TowerSumEtDr03 = x; }
    void                 SetTrackIsolationDr03(Double_t x)       { fTrackIsolation = x; }
    void                 SetPFChargedHadronIso(Double_t x)       { fPFChargedHadronIso = x; }
    void                 SetPFNeutralHadronIso(Double_t x)       { fPFNeutralHadronIso = x; }
    void                 SetPFPhotonIso(Double_t x)              { fPFPhotonIso = x; }
    void                 SetMva(Double_t x)                      { fMva = x; }
    void                 SetIsEB(Bool_t b)                       { fIsEB = b; }
    void                 SetIsEE(Bool_t b)                       { fIsEE = b; }
    void                 SetIsEBEEGap(Bool_t b)                  { fIsEBEEGap = b; }
    void                 SetIsEBEtaGap(Bool_t b)                 { fIsEBEtaGap = b; }
    void                 SetIsEBPhiGap(Bool_t b)                 { fIsEBPhiGap = b; }
    void                 SetIsEEDeeGap(Bool_t b)                 { fIsEEDeeGap = b; }
    void                 SetIsEERingGap(Bool_t b)                { fIsEERingGap = b; }
    void                 SetIsEcalDriven(Bool_t b)               { fIsEcalDriven = b; }
    void                 SetIsTrackerDriven(Bool_t b)            { fIsTrackerDriven = b; }
    void                 SetMatchesVertexConversion(Bool_t b)    { fMatchesVertexConversion = b; }
    void                 SetConversionXYZ(Double_t x, Double_t y, Double_t z)
    { fConvPosition.SetXYZ(x,y,z); }
    void                 SetCTFTrkNLayersWithMeasurement(Int_t x){ fCTFTrkNLayersWithMeasurement = x; }
    void                 SetHadOverEmTow(Double_t x)             { fHadOverEmTow = x; }
    void                 SetHCalIsoTowDr03(Double_t x)           { fHCalIsoTowDr03 = x; }
    void                 SetHCalIsoTowDr04(Double_t x)           { fHCalIsoTowDr04 = x; } 
    void                 SetEcalEnergy(Double_t e)               { fEcalEnergy = e; }
    void                 SetEcalEnergyError(Double_t e)          { fEcalEnergyError = e; }
    void                 SetTrackMomentumError(Double_t e)       { fTrackMomentumError = e; }
     
    const Track         *TrackerTrk()            const { return fTrackerTrackRef.Obj(); }
    const Track         *Trk()                   const { return BestTrk(); }
    const Track         *ConvPartnerTrk()        const { return fConvPartnerTrackRef.Obj(); }

    // Some structural tools
    void                 Mark(UInt_t i=1)        const;

  protected:
    Double_t          GetCharge()             const;
    Double_t          GetMass()               const { return 0.51099892e-3; }
    void              GetMom()                const;

    Vect3C            fMom;                          //stored three-momentum
    Char_t            fCharge = -99;                 //stored charge - filled with -99 when reading old files
    Char_t            fScPixCharge;                  //charge from supercluster-pixel matching
    Ref<Track>        fGsfTrackRef;                  //gsf track reference
    Ref<Track>        fTrackerTrackRef;              //tracker track reference
    Ref<Track>        fConvPartnerTrackRef;          //conversion partner track reference
    Ref<SuperCluster> fSuperClusterRef;              //reference to SuperCluster (refined unbiased PF supercluster in >= 7XY)
    Double32_t        fESuperClusterOverP;           //[0,0,14]super cluster e over p ratio
    Double32_t        fESeedClusterOverPout;         //[0,0,14]seed cluster e over p mom
    Double32_t        fDeltaEtaSuperClTrkAtVtx;      //[0,0,14]delta eta of super cluster with trk
    Double32_t        fDeltaEtaSeedClTrkAtCalo;      //[0,0,14]delta eta of seeed cluster with trk
    Double32_t        fDeltaPhiSuperClTrkAtVtx;      //[0,0,14]delta phi of super cluster with trk
    Double32_t        fDeltaPhiSeedClTrkAtCalo;      //[0,0,14]delta phi of seeed cluster with trk
    Double32_t        fFBrem;                        //[0,0,14]brem fraction
    Double32_t        fHadronicOverEm;               //[0,0,14]hadronic over em fraction
    Double32_t        fHcalDepth1OverEcal;           //[0,0,14]hadronic over em fraction depth1
    Double32_t        fHcalDepth2OverEcal;           //[0,0,14]hadronic over em fraction depth2
    Double32_t        fNumberOfClusters;             //[0,0,14]number of associated clusters
    Double32_t        fE15;                          //[0,0,14]1x5 crystal energy
    Double32_t        fE25Max;                       //[0,0,14]2x5 crystal energy (max of two possible sums)
    Double32_t        fE55;                          //[0,0,14]5x5 crystal energy
    Double32_t        fCovEtaEta;                    //[0,0,14]variance eta-eta
    Double32_t        fCoviEtaiEta;                  //[0,0,14]covariance eta-eta (in crystals)
    Double32_t        fCoviEtaiEta5x5 = -1.;         //[0,0,14]covariance eta-eta (in crystals, full5x5)
    Double32_t        fHcalDepth1TowerSumEtDr04;     //[0,0,14]hcal depth1 tower based isolation dR 0.4
    Double32_t        fHcalDepth2TowerSumEtDr04;     //[0,0,14]hcal depth2 tower based isolation dR 0.4
    Double32_t        fEcalJurassicIsolation;        //[0,0,14]ecal jura iso dR 0.4 *RENAMING*
    Double32_t        fTrackIsolationDr04;           //[0,0,14]isolation based on tracks dR 0.4
    Double32_t        fCaloTowerIsolation;           //[0,0,14]hcal tower based isolation dR 0.3
    Double32_t        fHcalDepth1TowerSumEtDr03;     //[0,0,14]hcal depth1 tower based isolation dR 0.3
    Double32_t        fHcalDepth2TowerSumEtDr03;     //[0,0,14]hcal depth2 tower based isolation dR 0.3
    Double32_t        fEcalRecHitSumEtDr03;          //[0,0,14]ecal jura iso dR 0.3
    Double32_t        fTrackIsolation;               //[0,0,14]isolation based on tracks dR 0.3 *RENAMING*
    Double32_t        fPassLooseID;                  //[0,0,14]pass loose id
    Double32_t        fPassTightID;                  //[0,0,14]pass tight id
    Double32_t        fIDLikelihood;                 //[0,0,14]likelihood value
    Double32_t        fPIn;                          //[0,0,14]momentum at vtx
    Double32_t        fPOut;                         //[0,0,14]momentum at ecal surface
    Double32_t        fFracSharedHits;               //[0,0,14]fraction of shared hits btw gsf and std. track
    Double32_t        fMva;                          //[0,0,14] pflow mva output
    Double32_t        fD0PV;                         //[0,0,14]transverse impact parameter to signal PV (gsf track)
    Double32_t        fD0PVErr;                      //[0,0,14]transverse impact parameter uncertainty to signal PV (gsf track)
    Double32_t        fIp3dPV;                       //[0,0,14]3d impact parameter to signal PV (gsf track)
    Double32_t        fIp3dPVErr;                    //[0,0,14]3d impact parameter uncertainty to signal PV (gsf track)
    Double32_t        fD0PVBS;                       //[0,0,14]transverse impact parameter to signal PV w/ bs constraint (gsf track)
    Double32_t        fD0PVBSErr;                    //[0,0,14]transverse impact parameter uncertainty to signal PV w/ bs constraint (gsf track)
    Double32_t        fIp3dPVBS;                     //[0,0,14]3d impact parameter to signal PV w/ bs constraint (gsf track)
    Double32_t        fIp3dPVBSErr;                  //[0,0,14]3d impact parameter uncertainty to signal PV w/ bs constraint (gsf track)
    Double32_t        fD0PVCkf;                      //[0,0,14]transverse impact parameter to signal PV (ckf track)
    Double32_t        fD0PVCkfErr;                   //[0,0,14]transverse impact parameter uncertainty to signal PV (ckf track)
    Double32_t        fIp3dPVCkf;                    //[0,0,14]3d impact parameter to signal PV (ckf track)
    Double32_t        fIp3dPVCkfErr;                 //[0,0,14]3d impact parameter uncertainty to signal PV (ckf track)
    Double32_t        fD0PVBSCkf;                    //[0,0,14]transverse impact parameter to signal PV w/ bs constraint (ckf track)
    Double32_t        fD0PVBSCkfErr;                 //[0,0,14]transverse impact parameter uncertainty to signal PV w/ bs constraint (ckf track)
    Double32_t        fIp3dPVBSCkf;                  //[0,0,14]3d impact parameter to signal PV w/ bs constraint (ckf track)
    Double32_t        fIp3dPVBSCkfErr;               //[0,0,14]3d impact parameter uncertainty to signal PV w/ bs constraint (ckf track)
    Double32_t        fD0PVUB;                       //[0,0,14]transverse impact parameter to signal PVUB (gsf track)
    Double32_t        fD0PVUBErr;                    //[0,0,14]transverse impact parameter uncertainty to signal PVUB (gsf track)
    Double32_t        fIp3dPVUB;                     //[0,0,14]3d impact parameter to signal PVUB (gsf track)
    Double32_t        fIp3dPVUBErr;                  //[0,0,14]3d impact parameter uncertainty to signal PVUB (gsf track)
    Double32_t        fD0PVUBBS;                     //[0,0,14]transverse impact parameter to signal PVUB w/ bs constraint (gsf track)
    Double32_t        fD0PVUBBSErr;                  //[0,0,14]transverse impact parameter uncertainty to signal PVUB w/ bs constraint (gsf track)
    Double32_t        fIp3dPVUBBS;                   //[0,0,14]3d impact parameter to signal PVUB w/ bs constraint (gsf track)
    Double32_t        fIp3dPVUBBSErr;                //[0,0,14]3d impact parameter uncertainty to signal PVUB w/ bs constraint (gsf track)
    Double32_t        fD0PVUBCkf;                    //[0,0,14]transverse impact parameter to signal PVUB (ckf track)
    Double32_t        fD0PVUBCkfErr;                 //[0,0,14]transverse impact parameter uncertainty to signal PVUB (ckf track)
    Double32_t        fIp3dPVUBCkf;                  //[0,0,14]3d impact parameter to signal PVUB (ckf track)
    Double32_t        fIp3dPVUBCkfErr;               //[0,0,14]3d impact parameter uncertainty to signal PVUB (ckf track)
    Double32_t        fD0PVUBBSCkf;                  //[0,0,14]transverse impact parameter to signal PVUB w/ bs constraint (ckf track)
    Double32_t        fD0PVUBBSCkfErr;               //[0,0,14]transverse impact parameter uncertainty to signal PVUB w/ bs constraint (ckf track)
    Double32_t        fIp3dPVUBBSCkf;                //[0,0,14]3d impact parameter to signal PVUB w/ bs constraint (ckf track)
    Double32_t        fIp3dPVUBBSCkfErr;             //[0,0,14]3d impact parameter uncertainty to signal PVUB w/ bs constraint (ckf track)
    Double32_t        fGsfPVCompatibility;           //[0,0,14]gsf compatibility with signal PV
    Double32_t        fGsfPVBSCompatibility;         //[0,0,14]gsf compatibility with signal PV w/ bs constraint
    Double32_t        fGsfPVCompatibilityMatched;    //[0,0,14]gsf compatibility with signal PV (matching ckf track excluded from vertex)
    Double32_t        fGsfPVBSCompatibilityMatched;  //[0,0,14]gsf compatibility with signal PV w/ bs constraint (matching ckf track excluded from vertex)
    Double32_t        fConvPartnerDCotTheta;         //[0,0,14]delta cot theta to nearest conversion partner track
    Double32_t        fConvPartnerDist;              //[0,0,14]distance in x-y plane to nearest conversion partner track
    Double32_t        fConvPartnerRadius;            //[0,0,14]radius of helix intersection with conversion partner track
    Double32_t        fPFChargedHadronIso;           //[0,0,14]pf isolation, charged hadrons
    Double32_t        fPFNeutralHadronIso;           //[0,0,14]pf isolation, neutral hadrons
    Double32_t        fPFPhotonIso;                  //[0,0,14]pf isolation, photons
    Int_t             fConvFlag;                     //conversion flag indicating which track combination was used
    Vect3C            fConvPosition;
    Bool_t            fIsEnergyScaleCorrected = kFALSE; //class dependent escale correction
    Bool_t            fIsMomentumCorrected = kFALSE;    //class dependent E-p combination 
    Int_t             fClassification;               //classification (see GsfElectron.h)
    Bool_t            fIsEB = kFALSE;                         //is ECAL barrel
    Bool_t            fIsEE = kFALSE;                         //is ECAL Endcap
    Bool_t            fIsEBEEGap = kFALSE;                    //is in barrel-endcap gap
    Bool_t            fIsEBEtaGap = kFALSE;                   //is in EB eta module gap
    Bool_t            fIsEBPhiGap = kFALSE;                   //is in EB phi module gap
    Bool_t            fIsEEDeeGap = kFALSE;                   //is in EE dee gap
    Bool_t            fIsEERingGap = kFALSE;                  //is in EE ring gap
    Bool_t            fIsEcalDriven = kFALSE;                 //is std. egamma electron
    Bool_t            fIsTrackerDriven = kFALSE;              //is pflow track-seeded electron
    Bool_t            fMatchesVertexConversion = kFALSE;      
    RefArray<Track>   fAmbiguousGsfTracks;           //ambiguous gsf tracks for this electron
    Double_t          fEEleClusterOverPout;          //energy of the electron cluster
    Int_t             fCTFTrkNLayersWithMeasurement; //number of tracker layers from associated ctf trk
    Double32_t        fHadOverEmTow;                 //[0,0,14]per-tower definition of hadronic/em energy fraction
    Double32_t        fHCalIsoTowDr03;               //[0,0,14]hcal isolation matched to per tower h/e definition
    Double32_t        fHCalIsoTowDr04;               //[0,0,14]hcal isolation matched to per tower h/e definition
    Double32_t        fEcalEnergy;                   //[0,0,14]corrected Ecal energy
    Double32_t        fEcalEnergyError;              //[0,0,14]corrected Ecal energy error
    Double32_t        fTrackMomentumError;           //track momentum error
    Ref<SuperCluster> fPFSuperClusterRef;            //reference to ECAL-only SuperCluster

    // The following members are deprecated
    //    Double32_t        fCaloIsolation;                //[0,0,14](non-jura) ecal isolation based on rechits dR 0.3
    //    Double32_t        fHcalJurassicIsolation;        //[0,0,14]hcal jura iso dR 0.4
    // Accessors
    //    Double_t             CaloIsolation()               const { return fCaloIsolation; }
    //    Double_t             HcalIsolation()                  const { return fHcalJurassicIsolation; }
    // fPFSuperClusterRef: member object name is kept the same as <7XY so that old files can be read
    // Should in principle be possible to use schema evolution to convert it to something like fECALOnlySuperClusterRef
    // The problem is that process ID seems to be not set at the point where conversion rules are applied
    // which is strange since process ID is set in ProcIDRef::Streamer..

    ClassDef(Electron, 18)                             // Electron class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Electron::Mark(UInt_t ib) const
{
  // mark myself
  mithep::DataObject::Mark(ib);
  // mark my dependencies if they are there
  if (fGsfTrackRef.IsValid())
    fGsfTrackRef.Obj()->Mark(ib);
  if (fTrackerTrackRef.IsValid())
    fTrackerTrackRef.Obj()->Mark(ib);
  if (fConvPartnerTrackRef.IsValid())
    fConvPartnerTrackRef.Obj()->Mark(ib);
  if (fSuperClusterRef.IsValid())
    fSuperClusterRef.Obj()->Mark(ib);
  if (fPFSuperClusterRef.IsValid())
    fPFSuperClusterRef.Obj()->Mark(ib);

  fAmbiguousGsfTracks.Mark(ib);
}
  
//--------------------------------------------------------------------------------------------------
inline const mithep::Track *mithep::Electron::BestTrk() const
{
  // Return "best" track.

  if (HasGsfTrk())
    return GsfTrk();
  else if (HasTrackerTrk())
    return TrackerTrk();

  return 0;
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::GetCharge() const
{
  // Return stored charge, unless it is set to invalid (-99),
  // in that case get charge from track as before

  if (fCharge==-99)
    return mithep::ChargedParticle::GetCharge();
  else
    return fCharge;

}

//--------------------------------------------------------------------------------------------------
inline void mithep::Electron::GetMom() const
{
  // Get momentum of the electron. We use an explicitly stored three vector, with the pdg mass,
  // since the momentum vector may be computed non-trivially in cmssw

  fCachedMom.SetCoordinates(fMom.Rho(),fMom.Eta(),fMom.Phi(),GetMass());
}

//-------------------------------------------------------------------------------------------------
inline Double_t mithep::Electron::ESeedClusterOverPIn() const
{
  // Return energy of the SuperCluster seed divided by the magnitude 
  // of the track momentum at the vertex.
  
  return SCluster()->Seed()->Energy() / PIn();
}

//-------------------------------------------------------------------------------------------------
inline void mithep::Electron::SetPtEtaPhi(Double_t pt, Double_t eta, Double_t phi)
{
  // Set three-vector
  
  fMom.Set(pt,eta,phi);
  ClearMom();
}
#endif
