// $Id: BaseMod.cc,v 1.1 2008/06/12 08:47:57 loizides Exp $

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/TreeMod/interface/HLTFwkMod.h"

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
  const HLTFwkMod *mod = static_cast<const HLTFwkMod *>(tasks->FindObject(hltfwk));
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
  const HLTFwkMod *mod = static_cast<const HLTFwkMod *>(tasks->FindObject(hltfwk));
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

  const HLTFwkMod *mod = dynamic_cast<const HLTFwkMod *>(tasks->FindObject(hltfwk));
  if (mod)
    return kTRUE;
  return kFALSE;
}
