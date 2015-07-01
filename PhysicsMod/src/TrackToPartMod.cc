#include "MitAna/PhysicsMod/interface/TrackToPartMod.h"
#include "MitAna/DataTree/interface/StableParticleCol.h"
#include "MitAna/DataTree/interface/TrackCol.h"

using namespace mithep;

//--------------------------------------------------------------------------------------------------
TrackToPartMod::TrackToPartMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fBranchName("SetMe"),
  fPublicName(""),
  fPubPerEvent(kTRUE),
  fAbsPdgId(22),
  fColOut(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void TrackToPartMod::Process()
{
  // Load the branch, add pointers to the object array. Publish object array if needed.

  auto* colIn = GetObject<mithep::TrackCol>(GetBranchName());

  if (!colIn) {
    SendError(kAbortModule, "Process", "Could not load data!");
    return;
  }

  const UInt_t entries = colIn->GetEntries();

  if (fPubPerEvent) {
    fColOut = new StableParticleOArr(entries, GetPublicName());
    fColOut->SetOwner(kTRUE);
  }
  else
    fColOut->Reset();

  for(UInt_t i=0; i<entries; ++i)
    fColOut->AddOwned(new StableParticle(fAbsPdgId,colIn->At(i)));

  if (fPubPerEvent) 
    AddObjThisEvt(fColOut);
}

//--------------------------------------------------------------------------------------------------
void TrackToPartMod::SlaveBegin()
{
  if (fPublicName.IsNull())
    fPublicName = GetBranchName();

  if (!GetPubPerEvent()) {
    fColOut = new StableParticleOArr(0, GetPublicName());
    fColOut->SetOwner(kTRUE);
    PublishObj(fColOut);
  }
}

//--------------------------------------------------------------------------------------------------
void TrackToPartMod::SlaveTerminate()
{
  // Cleanup in case objects are published only once.

  if (!fPubPerEvent) {
    RetractObj(GetPublicName());
    delete fColOut;
  }
}
