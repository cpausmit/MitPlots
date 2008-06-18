// $Id: MitAnaDataTreeLinkDef.h,v 1.7 2008/06/17 14:45:22 loizides Exp $

#ifndef DATATREE_LINKDEF_H
#define DATATREE_LINKDEF_H

#include <vector>
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/Collections.h"
#include "MitAna/DataTree/interface/Array.h"
#include "MitAna/DataTree/interface/ObjArray.h"
#include "MitAna/DataTree/interface/Vector.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/GenParticle.h"
#include "MitAna/DataTree/interface/Lepton.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/GlobalMuon.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Names+;

#pragma link C++ class mithep::DataObject+;
#pragma link C++ class mithep::EventHeader+;
#pragma link C++ class mithep::Track+;
#pragma link C++ class mithep::Particle+;
#pragma link C++ class mithep::GenParticle+;
#pragma link C++ class mithep::Lepton+;
#pragma link C++ class mithep::Muon+;
#pragma link C++ class mithep::Electron+;
#pragma link C++ class mithep::GlobalMuon+;
#pragma link C++ class std::vector<mithep::DataObject>+;
#pragma link C++ class std::vector<mithep::Track>+;
#pragma link C++ class std::vector<mithep::Particle>+;
#pragma link C++ class std::vector<mithep::GenParticle>+;
#pragma link C++ class std::vector<mithep::Lepton>+;
#pragma link C++ class std::vector<mithep::Muon>+;
#pragma link C++ class std::vector<mithep::Electron>+;
#pragma link C++ class std::vector<mithep::GlobalMuon>+;
#pragma link C++ class mithep::BaseCollection+;
#pragma link C++ class mithep::Collection<mithep::EventHeader>+;
#pragma link C++ class mithep::Collection<mithep::DataObject>+;
#pragma link C++ class mithep::Collection<mithep::Track>+;
#pragma link C++ class mithep::Collection<mithep::Particle>+;
#pragma link C++ class mithep::Collection<mithep::GenParticle>+;
#pragma link C++ class mithep::Collection<mithep::Lepton>+;
#pragma link C++ class mithep::Collection<mithep::Muon>+;
#pragma link C++ class mithep::Collection<mithep::Electron>+;
#pragma link C++ class mithep::Collection<mithep::GlobalMuon>+;
#pragma link C++ class mithep::Vector<mithep::DataObject>+;
#pragma link C++ class mithep::Vector<mithep::Track>+;
#pragma link C++ class mithep::Vector<mithep::Particle>+;
#pragma link C++ class mithep::Vector<mithep::GenParticle>+;
#pragma link C++ class mithep::Vector<mithep::Lepton>+;
#pragma link C++ class mithep::Vector<mithep::Muon>+;
#pragma link C++ class mithep::Vector<mithep::Electron>+;
#pragma link C++ class mithep::Vector<mithep::GlobalMuon>+;
#pragma link C++ class mithep::Vector<mithep::EventHeader>+;
#pragma link C++ typedef mithep::DataObjectCol;
#pragma link C++ typedef mithep::TrackCol;
#pragma link C++ typedef mithep::ParticleCol;
#pragma link C++ typedef mithep::GenParticleCol;
#pragma link C++ typedef mithep::LeptonCol;
#pragma link C++ typedef mithep::MuonCol;
#pragma link C++ typedef mithep::ElectronCol;
#pragma link C++ typedef mithep::GlobalMuonCol;
#endif
