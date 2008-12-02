// $Id: BaseMod.cc,v 1.3 2008/11/25 15:57:49 loizides Exp $

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/TreeMod/interface/HLTFwkMod.h"
#include <TH1D.h>

using namespace mithep;

ClassImp(mithep::BaseMod)

//--------------------------------------------------------------------------------------------------
const TriggerObjectsTable *BaseMod::GetHLTObjectsTable(const char *hltfwk) const
{ 
  // Get pointer to HLT objects table obtained by module with given name. (Note: normally
  // you want to stick to the default argument.)

  if (!HasHLTInfo()) 
    return 0;

  const TList *tasks = GetSelector()->GetTopModule()->GetSubModules();
  const HLTFwkMod *mod = static_cast<const HLTFwkMod*>(tasks->FindObject(hltfwk));
  return (dynamic_cast<const TriggerObjectsTable *>(FindPublicObj(mod->HLTObjsNamePub())));
}

//--------------------------------------------------------------------------------------------------
const TriggerTable *BaseMod::GetHLTTable(const char *hltfwk) const 
{ 
  // Get pointer to HLT trigger table obtained by module with given name. (Note: normally
  // you want to stick to the default argument.)
  
  if (!HasHLTInfo(hltfwk)) 
    return 0;

  const TList *tasks = GetSelector()->GetTopModule()->GetSubModules();
  const HLTFwkMod *mod = static_cast<const HLTFwkMod*>(tasks->FindObject(hltfwk));
  return (dynamic_cast<const TriggerTable *>(FindPublicObj(mod->HLTTabNamePub())));
}

//--------------------------------------------------------------------------------------------------
Bool_t BaseMod::HasHLTInfo(const char *hltfwk) const
{ 
  // Check if HLT framework module is in list of modules. (Note: normally
  // you want to stick to the default argument.)

  if (!GetSelector() || !GetSelector()->GetTopModule()) 
    return kFALSE;

  const TList *tasks = GetSelector()->GetTopModule()->GetSubModules();
  if (!tasks)
    return kFALSE;

  const HLTFwkMod *mod = dynamic_cast<const HLTFwkMod*>(tasks->FindObject(hltfwk));
  if (mod)
    return kTRUE;
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
void BaseMod::SaveNEventsProcessed(const char *name) 
{
  // Save the number of processed events in a one-bin histogram. 

  TH1D *hDEvents = new TH1D(name,"Total number of processed events",1,-0.5,0.5);
  hDEvents->Fill(0.0,fNEventsProcessed);
  hDEvents->SetEntries(fNEventsProcessed);
  AddOutput(hDEvents);
}
