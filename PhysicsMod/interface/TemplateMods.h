#ifndef MITANA_PHYSICSMOD_TEMPLATEMODS_H
#define MITANA_PHYSICSMOD_TEMPLATEMODS_H

#include "MitAna/PhysicsMod/interface/FilterMod.h"
#include "MitAna/PhysicsMod/interface/MergerMod.h"
#include "MitAna/PhysicsMod/interface/PlotKineMod.h"
#include "MitAna/PhysicsMod/interface/PublisherMod.h"
#include "MitAna/PhysicsMod/interface/SkimMod.h"

#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/CaloJet.h"
#include "MitAna/DataTree/interface/CaloMet.h"
#include "MitAna/DataTree/interface/CaloTower.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/CompoundParticle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/GenJet.h"
#include "MitAna/DataTree/interface/GenericParticle.h"
#include "MitAna/DataTree/interface/JPTJet.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/PFJet.h"
#include "MitAna/DataTree/interface/PFMet.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/PFTau.h"
#include "MitAna/DataTree/interface/Tau.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/Vertex.h"

namespace mithep {

  typedef FilterMod<CaloJet, Jet> CaloJetToJetFilterMod;
  typedef FilterMod<CaloJet> CaloJetFilterMod;
  typedef FilterMod<CaloMet, Met> CaloMetToMetFilterMod;
  typedef FilterMod<CaloMet> CaloMetFilterMod;
  typedef FilterMod<CaloTower> CaloTowerFilterMod;
  typedef FilterMod<CompositeParticle> CompositeParticleFilterMod;
  typedef FilterMod<CompoundParticle> CompoundParticleFilterMod;
  typedef FilterMod<Conversion> ConversionFilterMod;
  typedef FilterMod<Electron> ElectronFilterMod;
  typedef FilterMod<GenJet> GenJetFilterMod;
  typedef FilterMod<Jet> JetFilterMod;
  typedef FilterMod<MCParticle> MCParticleFilterMod;
  typedef FilterMod<Met> MetFilterMod;
  typedef FilterMod<Muon> MuonFilterMod;
  typedef FilterMod<PFJet> PFJetFilterMod;
  typedef FilterMod<Photon> PhotonFilterMod;
  typedef FilterMod<Track> TrackFilterMod;
  typedef FilterMod<TriggerObject> TriggerObjectFilterMod;

  typedef MergerMod<TObject> TObjectMergerMod;
  typedef MergerMod<BasicCluster> BasicClusterMergerMod;
  typedef MergerMod<DataBase> DataBaseMergerMod;
  typedef MergerMod<DataObject> DataObjectMergerMod;
  typedef MergerMod<GenericParticle> GenericParticleMergerMod;
  typedef MergerMod<Particle> ParticleMergerMod;
  typedef MergerMod<SuperCluster> SuperClusterMergerMod;

  typedef PlotKineMod<CaloJet> CaloJetPlotKineMod;
  typedef PlotKineMod<CaloMet> CaloMetPlotKineMod;
  typedef PlotKineMod<CompositeParticle> CompositeParticlePlotKineMod;
  typedef PlotKineMod<CompoundParticle> CompoundParticlePlotKineMod;
  typedef PlotKineMod<Conversion> ConversionPlotKineMod;
  typedef PlotKineMod<Electron> ElectronPlotKineMod;
  typedef PlotKineMod<GenJet> GenJetPlotKineMod;
  typedef PlotKineMod<Jet> JetPlotKineMod;
  typedef PlotKineMod<MCParticle> MCParticlePlotKineMod;
  typedef PlotKineMod<Met> MetPlotKineMod;
  typedef PlotKineMod<Muon> MuonPlotKineMod;
  typedef PlotKineMod<PFJet> PFJetPlotKineMod;
  typedef PlotKineMod<Particle> ParticlePlotKineMod;
  typedef PlotKineMod<Photon> PhotonPlotKineMod;
  typedef PlotKineMod<Track> TrackPlotKineMod;
  typedef PlotKineMod<TriggerObject> TriggerObjectPlotKineMod;

  typedef PublisherMod<BasicCluster> BasicClusterPublisherMod;
  typedef PublisherMod<CaloJet, Jet> CaloJetToJetPublisherMod;
  typedef PublisherMod<CaloJet> CaloJetPublisherMod;
  typedef PublisherMod<CaloMet, Met> CaloMetToMetPublisherMod;
  typedef PublisherMod<CaloMet> CaloMetPublisherMod;
  typedef PublisherMod<CaloTower> CaloTowerPublisherMod;
  typedef PublisherMod<CompositeParticle> CompositeParticlePublisherMod;
  typedef PublisherMod<CompoundParticle> CompoundParticlePublisherMod;
  typedef PublisherMod<Conversion> ConversionPublisherMod;
  typedef PublisherMod<Electron> ElectronPublisherMod;
  typedef PublisherMod<Muon> MuonPublisherMod;
  typedef PublisherMod<GenJet> GenJetPublisherMod;
  typedef PublisherMod<Jet> JetPublisherMod;
  typedef PublisherMod<MCParticle> MCParticlePublisherMod;
  typedef PublisherMod<Met> MetPublisherMod;
  typedef PublisherMod<PFMet, Met> PFMetToMetPublisherMod;
  typedef PublisherMod<PFMet> PFMetPublisherMod;
  typedef PublisherMod<PFJet, Jet> PFJetToJetPublisherMod;
  typedef PublisherMod<PFJet> PFJetPublisherMod;
  typedef PublisherMod<Photon> PhotonPublisherMod;
  typedef PublisherMod<SuperCluster> SuperClusterPublisherMod;
  typedef PublisherMod<Track> TrackPublisherMod;
  typedef PublisherMod<TriggerObject> TriggerObjectPublisherMod;
  typedef PublisherMod<JPTJet, Jet> JPTJetToJetPublisherMod;

  typedef SkimMod<BasicCluster> BasicClusterSkimMod;
  typedef SkimMod<CaloJet> CaloJetSkimMod;
  typedef SkimMod<CaloMet> CaloMetSkimMod;
  typedef SkimMod<CaloTower> CaloTowerSkimMod;
  typedef SkimMod<CompositeParticle> CompositeParticleSkimMod;
  typedef SkimMod<Conversion> ConversionSkimMod;
  typedef SkimMod<Electron> ElectronSkimMod;
  typedef SkimMod<GenJet> GenJetSkimMod;
  typedef SkimMod<Jet> JetSkimMod;
  typedef SkimMod<MCParticle> MCParticleSkimMod;
  typedef SkimMod<Met> MetSkimMod;
  typedef SkimMod<CaloMet> CaloMetSkimMod;
  typedef SkimMod<PFMet> PFMetSkimMod;
  typedef SkimMod<Muon> MuonSkimMod;
  typedef SkimMod<PFCandidate> PFCandidateSkimMod;
  typedef SkimMod<PFJet> PFJetSkimMod;
  typedef SkimMod<Tau> TauSkimMod;
  typedef SkimMod<PFTau> PFTauSkimMod;
  typedef SkimMod<Photon> PhotonSkimMod;
  typedef SkimMod<SuperCluster> SuperClusterSkimMod;
  typedef SkimMod<Track> TrackSkimMod;
  typedef SkimMod<TriggerObject> TriggerObjectSkimMod;
  typedef SkimMod<Vertex> VertexSkimMod;

}

#endif
