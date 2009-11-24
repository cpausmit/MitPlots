// $Id: BaseMod.cc,v 1.9 2009/07/13 10:39:20 loizides Exp $

#include "MitAna/TreeMod/interface/HLTFwkMod.h"
#include "MitAna/DataTree/interface/TriggerObjectsTable.h"
#include <TH1D.h>

using namespace mithep;

ClassImp(mithep::BaseMod)

//--------------------------------------------------------------------------------------------------
BaseMod::BaseMod(const char *name, const char *title) : 
  TAModule(name,title),
  fFillHist(kFALSE),
  fEvtObjBrNames(0),
  fHltFwkMod(0),
  fHltFwkModName("HLTFwkMod"),
  fNEventsProc(0)
{
  // Constructor.

  fEvtObjBrNames.SetOwner(kTRUE);
}

//--------------------------------------------------------------------------------------------------
const TriggerObjectsTable *BaseMod::GetHLTObjectsTable() const
{ 
  // Get pointer to HLT objects table obtained by module with given name. (Note: normally
  // you want to stick to the default argument.)

  if (!HasHLTInfo()) 
    return 0;

  return (dynamic_cast<const TriggerObjectsTable *>(FindPublicObj(fHltFwkMod->HLTObjsNamePub())));
}

//--------------------------------------------------------------------------------------------------
const TriggerTable *BaseMod::GetHLTTable() const 
{ 
  // Get pointer to HLT trigger table obtained by module with given name.
  
  if (!HasHLTInfo()) 
    return 0;

  return (dynamic_cast<const TriggerTable *>(FindPublicObj(fHltFwkMod->HLTTabNamePub())));
}

//--------------------------------------------------------------------------------------------------
const TriggerTable *BaseMod::GetL1AlgoTable() const 
{ 
  // Get pointer to L1 algorithm trigger table obtained by module with given name.
  
  if (!HasHLTInfo()) 
    return 0;

  return (dynamic_cast<const TriggerTable *>(FindPublicObj(fHltFwkMod->L1ATabNamePub())));
}

//--------------------------------------------------------------------------------------------------
const TriggerTable *BaseMod::GetL1TechTable() const 
{ 
  // Get pointer to L1 technical trigger table obtained by module with given name.
  
  if (!HasHLTInfo()) 
    return 0;

  return (dynamic_cast<const TriggerTable *>(FindPublicObj(fHltFwkMod->L1TTabNamePub())));
}

//--------------------------------------------------------------------------------------------------
Bool_t BaseMod::HasHLTInfo() const
{ 
  // Check if HLT framework module is in list of modules. 

  if (fHltFwkMod) 
    return kTRUE;

  if (!GetSelector() || !GetSelector()->GetTopModule()) 
    return kFALSE;

  const TList *tasks = GetSelector()->GetTopModule()->GetSubModules();
  if (!tasks)
    return kFALSE;

  fHltFwkMod = dynamic_cast<const HLTFwkMod*>(tasks->FindObject(fHltFwkModName));
  if (fHltFwkMod)
    return kTRUE;
  return kFALSE;
}

//--------------------------------------------------------------------------------------------------
void BaseMod::SaveNEventsProcessed(const char *name) 
{
  // Save the number of processed events in a one-bin histogram. 

  TH1D *hDEvents = new TH1D(name,"Total number of processed events",1,-0.5,0.5);
  hDEvents->Fill(0.0,fNEventsProc);
  hDEvents->SetEntries(fNEventsProc);
  AddOutput(hDEvents);
}
