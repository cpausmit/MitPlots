// $Id: Collections.h,v 1.6 2008/06/09 11:47:03 paus Exp $

#ifndef DATATREE_COLLECTIONS_H
#define DATATREE_COLLECTIONS_H
 
#include "MitAna/DataTree/interface/Collection.h"
#include "MitAna/DataTree/interface/Vector.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/GenParticle.h"
#include "MitAna/DataTree/interface/Lepton.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/Electron.h"

//--------------------------------------------------------------------------------------------------
//
// Collections
//
// This header file defines the standard types for the collections we want to use.
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{

  typedef Collection<DataObject>  DataObjectCol;
  typedef Collection<Track>       TrackCol;
  typedef Collection<Particle>    ParticleCol;
  typedef Collection<GenParticle> GenParticleCol;
  typedef Collection<Lepton>      LeptonCol;
  typedef Collection<Muon>        MuonCol;
  typedef Collection<Electron>    ElectronCol;
}
#endif
