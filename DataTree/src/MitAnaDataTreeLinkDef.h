// $Id: MitAnaDataTreeLinkDef.h,v 1.16 2008/07/07 16:02:25 loizides Exp $

#ifndef DATATREE_LINKDEF_H
#define DATATREE_LINKDEF_H

#include <vector>
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/Array.h"
#include "MitAna/DataTree/interface/ObjArray.h"
#include "MitAna/DataTree/interface/RefArray.h"
#include "MitAna/DataTree/interface/Vector.h"
#include "MitAna/DataTree/interface/Collections.h"

#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/LAHeader.h"
#include "MitAna/DataTree/interface/RunInfo.h"

#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/FitVertex.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Lepton.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataTree/interface/Met.h"
#include "MitAna/DataTree/interface/GenParticle.h"
#include "MitAna/DataTree/interface/SimParticle.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/DecayParticle.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/Conversion.h"
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
#pragma link C++ class mithep::Lepton+;
#pragma link C++ class mithep::Muon+;
#pragma link C++ class mithep::Electron+;
#pragma link C++ class mithep::Jet+;
#pragma link C++ class mithep::Met+;
#pragma link C++ class mithep::GenParticle+;
#pragma link C++ class mithep::SimParticle+;

#pragma link C++ class mithep::BaseCollection+;
#pragma link C++ class mithep::Collection<mithep::DataObject>+;
#pragma link C++ class mithep::Collection<mithep::Track>+;
#pragma link C++ class mithep::Collection<mithep::Particle>+;
#pragma link C++ class mithep::Collection<mithep::Lepton>+;
#pragma link C++ class mithep::Collection<mithep::Muon>+;
#pragma link C++ class mithep::Collection<mithep::Electron>+;
#pragma link C++ class mithep::Collection<mithep::Jet>+;
#pragma link C++ class mithep::Collection<mithep::Met>+;
#pragma link C++ class mithep::Collection<mithep::GenParticle>+;
#pragma link C++ class mithep::Collection<mithep::SimParticle>+;
#pragma link C++ class mithep::Collection<mithep::Conversion>+;
#pragma link C++ class mithep::Array<mithep::DataObject>+;
#pragma link C++ class mithep::Array<mithep::Track>+;
#pragma link C++ class mithep::Array<mithep::GenParticle>+;
#pragma link C++ class mithep::Array<mithep::Muon>+;
#pragma link C++ class mithep::Array<mithep::Electron>+;
#pragma link C++ class mithep::Array<mithep::Jet>+;
#pragma link C++ class mithep::Array<mithep::Met>+;
#pragma link C++ class mithep::Array<mithep::SimParticle>+;
#pragma link C++ class mithep::Array<mithep::Conversion>+;
#pragma link C++ class mithep::ObjArray<mithep::DataObject>+;
#pragma link C++ class mithep::ObjArray<mithep::Track>+;
#pragma link C++ class mithep::ObjArray<mithep::GenParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::Lepton>+;
#pragma link C++ class mithep::ObjArray<mithep::Muon>+;
#pragma link C++ class mithep::ObjArray<mithep::Electron>+;
#pragma link C++ class mithep::ObjArray<mithep::Jet>+;
#pragma link C++ class mithep::ObjArray<mithep::Met>+;
#pragma link C++ class mithep::ObjArray<mithep::SimParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::Conversion>+;

#pragma link C++ class mithep::Collection<TRef>+;
#pragma link C++ class mithep::RefArray<mithep::Particle>+;
#pragma link C++ class mithep::RefArray<mithep::Conversion>+;

#pragma link C++ class mithep::CompositeParticle+;
#pragma link C++ class mithep::DecayParticle+;
#pragma link C++ class mithep::Photon+;
#pragma link C++ class mithep::Conversion+;

#pragma link C++ class mithep::Collection<mithep::CompositeParticle>+;
#pragma link C++ class mithep::Collection<mithep::DecayParticle>+;
#pragma link C++ class mithep::Collection<mithep::Photon>+;
#pragma link C++ class mithep::Array<mithep::CompositeParticle>+;
#pragma link C++ class mithep::Array<mithep::DecayParticle>+;
#pragma link C++ class mithep::Array<mithep::Photon>+;
#pragma link C++ class mithep::ObjArray<mithep::CompositeParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::DecayParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::Photon>+;

#pragma link C++ typedef mithep::DataObjectCol;
#pragma link C++ typedef mithep::TrackCol;
#pragma link C++ typedef mithep::ParticleCol;
#pragma link C++ typedef mithep::LeptonCol;
#pragma link C++ typedef mithep::MuonCol;
#pragma link C++ typedef mithep::ElectronCol;
#pragma link C++ typedef mithep::JetCol;
#pragma link C++ typedef mithep::MetCol;
#pragma link C++ typedef mithep::CompositeParticleCol;
#pragma link C++ typedef mithep::GenParticleCol;
#pragma link C++ typedef mithep::SimParticleCol;
#pragma link C++ typedef mithep::DecayParticleCol;
#pragma link C++ typedef mithep::PhotonCol;
#pragma link C++ typedef mithep::ConversionCol;

#pragma link C++ typedef mithep::DataObjectArr;
#pragma link C++ typedef mithep::TrackArr;
#pragma link C++ typedef mithep::MuonArr;
#pragma link C++ typedef mithep::ElectronArr;
#pragma link C++ typedef mithep::JetArr;
#pragma link C++ typedef mithep::MetArr;
#pragma link C++ typedef mithep::GenParticleArr;
#pragma link C++ typedef mithep::SimParticleArr;
#pragma link C++ typedef mithep::PhotonArr;
#pragma link C++ typedef mithep::ConversionArr;

#endif
