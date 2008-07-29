// $Id: MitAnaDataTreeLinkDef.h,v 1.22 2008/07/28 23:13:42 paus Exp $

#ifndef DATATREE_LINKDEF_H
#define DATATREE_LINKDEF_H

#include <vector>
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/Collections.h"

#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/LAHeader.h"
#include "MitAna/DataTree/interface/RunInfo.h"

#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/FitVertex.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/ChargedParticle.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataTree/interface/Met.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/DecayParticle.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/BasePart.h"
#include "MitAna/DataTree/interface/DecayPart.h"
#include "MitAna/DataTree/interface/StablePart.h"
#include "MitAna/DataTree/interface/StableParticle.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Names+;

#pragma link C++ class mithep::EventHeader+;
#pragma link C++ class mithep::LAHeader+;
#pragma link C++ class mithep::RunInfo+;

#pragma link C++ class mithep::DataObject+;
#pragma link C++ class mithep::Vertex+;
#pragma link C++ class mithep::FitVertex+;
#pragma link C++ class mithep::Track+;
#pragma link C++ class mithep::Particle+;
#pragma link C++ class mithep::ChargedParticle+;
#pragma link C++ class mithep::Muon+;
#pragma link C++ class mithep::Electron+;
#pragma link C++ class mithep::Jet+;
#pragma link C++ class mithep::Met+;
#pragma link C++ class mithep::MCParticle+;
#pragma link C++ class mithep::StableParticle+;

#pragma link C++ class mithep::BaseCollection+;
#pragma link C++ class mithep::Collection<mithep::DataObject>+;
#pragma link C++ class mithep::Collection<mithep::Track>+;
#pragma link C++ class mithep::Collection<mithep::Particle>+;
#pragma link C++ class mithep::Collection<mithep::ChargedParticle>+;
#pragma link C++ class mithep::Collection<mithep::Muon>+;
#pragma link C++ class mithep::Collection<mithep::Electron>+;
#pragma link C++ class mithep::Collection<mithep::Jet>+;
#pragma link C++ class mithep::Collection<mithep::Met>+;
#pragma link C++ class mithep::Collection<mithep::MCParticle>+;
#pragma link C++ class mithep::Collection<mithep::Conversion>+;
#pragma link C++ class mithep::Collection<mithep::StableParticle>+;
#pragma link C++ class mithep::Array<mithep::DataObject>+;
#pragma link C++ class mithep::Array<mithep::Track>+;
#pragma link C++ class mithep::Array<mithep::MCParticle>+;
#pragma link C++ class mithep::Array<mithep::Muon>+;
#pragma link C++ class mithep::Array<mithep::Electron>+;
#pragma link C++ class mithep::Array<mithep::Jet>+;
#pragma link C++ class mithep::Array<mithep::Met>+;
#pragma link C++ class mithep::Array<mithep::Conversion>+;
#pragma link C++ class mithep::Array<mithep::StableParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::DataObject>+;
#pragma link C++ class mithep::ObjArray<mithep::Track>+;
#pragma link C++ class mithep::ObjArray<mithep::MCParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::ChargedParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::Muon>+;
#pragma link C++ class mithep::ObjArray<mithep::Electron>+;
#pragma link C++ class mithep::ObjArray<mithep::Jet>+;
#pragma link C++ class mithep::ObjArray<mithep::Met>+;
#pragma link C++ class mithep::ObjArray<mithep::Conversion>+;
#pragma link C++ class mithep::ObjArray<mithep::StableParticle>+;

#pragma link C++ class mithep::Collection<TRef>+;
#pragma link C++ class mithep::RefArray<mithep::Particle>-;
#pragma link C++ class mithep::RefArray<mithep::Conversion>-;

#pragma link C++ class mithep::CompositeParticle+;
#pragma link C++ class mithep::DecayParticle+;
#pragma link C++ class mithep::Photon+;
#pragma link C++ class mithep::Conversion+;
#pragma link C++ class mithep::BasePart+;
#pragma link C++ class mithep::DecayPart+;
#pragma link C++ class mithep::StablePart+;

#pragma link C++ class mithep::Collection<mithep::CompositeParticle>+;
#pragma link C++ class mithep::Collection<mithep::DecayParticle>+;
#pragma link C++ class mithep::Collection<mithep::Photon>+;
#pragma link C++ class mithep::Collection<mithep::BasePart>+;
#pragma link C++ class mithep::Collection<mithep::DecayPart>+;
#pragma link C++ class mithep::Collection<mithep::StablePart>+;
#pragma link C++ class mithep::Array<mithep::CompositeParticle>+;
#pragma link C++ class mithep::Array<mithep::DecayParticle>+;
#pragma link C++ class mithep::Array<mithep::Photon>+;
#pragma link C++ class mithep::ObjArray<mithep::CompositeParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::DecayParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::Photon>+;
#pragma link C++ class mithep::ObjArray<mithep::BasePart>+;
#pragma link C++ class mithep::ObjArray<mithep::DecayPart>+;
#pragma link C++ class mithep::ObjArray<mithep::StablePart>+;

#pragma link C++ typedef mithep::DataObjectCol;
#pragma link C++ typedef mithep::TrackCol;
#pragma link C++ typedef mithep::ParticleCol;
#pragma link C++ typedef mithep::ChargedParticleCol;
#pragma link C++ typedef mithep::MuonCol;
#pragma link C++ typedef mithep::ElectronCol;
#pragma link C++ typedef mithep::JetCol;
#pragma link C++ typedef mithep::MetCol;
#pragma link C++ typedef mithep::CompositeParticleCol;
#pragma link C++ typedef mithep::MCParticleCol;
#pragma link C++ typedef mithep::DecayParticleCol;
#pragma link C++ typedef mithep::PhotonCol;
#pragma link C++ typedef mithep::ConversionCol;
#pragma link C++ typedef mithep::StableParticleCol;

#pragma link C++ typedef mithep::DataObjectArr;
#pragma link C++ typedef mithep::TrackArr;
#pragma link C++ typedef mithep::MuonArr;
#pragma link C++ typedef mithep::ElectronArr;
#pragma link C++ typedef mithep::JetArr;
#pragma link C++ typedef mithep::MetArr;
#pragma link C++ typedef mithep::MCParticleArr;
#pragma link C++ typedef mithep::PhotonArr;
#pragma link C++ typedef mithep::StableParticleArr;

#pragma link C++ enum mithep::MCParticle::EPartType;

#pragma link C++ typedef mithep::BasePartObjArr;
#pragma link C++ typedef mithep::DecayPartObjArr;
#pragma link C++ typedef mithep::StablePartObjArr;

#endif
