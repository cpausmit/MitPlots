// $Id: CatalogingMod.cc,v 1.2 2008/07/10 21:31:46 loizides Exp $

#include <TFile.h>
#include <TTree.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/CatalogingMod.h"
#include "MitAna/DataTree/interface/TriggerTable.h"

using namespace mithep;

ClassImp(mithep::CatalogingMod)

//--------------------------------------------------------------------------------------------------
CatalogingMod::CatalogingMod(const char *name, const char *title) : 
  BaseMod         (name,title),
  fAllHeadTreeName(Names::gkAllEvtTreeName),
  fMyHeadTree     (0),
  fMyEventHeader  (0),
  fMetaDataString ("==MetaData=="),
  fNFileSet       (0),
  fLastLumiSec    (999999999),
  fMetaData       (0,0,0,999999999,0,0,0),
  fTriggers       (0)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::SlaveBegin()
{
  // Print out cataloging module message.
  
  if (gDebugLevel > 0)
    cout << " ============================\n"
	 << " CatalogingMod::SlaveBegin -- Creating MetaInformation for the coming events\n"
	 << " ============================\n";

  fTriggers = GetHLTTable();
  if (! fTriggers) {
    printf(" Has trigger table is: %d\n",HasHLTInfo());
    SendError(kAbortAnalysis, "SlaveBegin", "Could not get HLT trigger table.");
    return;
  }
}

//--------------------------------------------------------------------------------------------------
Bool_t CatalogingMod::Notify()
{
  // Make sure to get the new "AllEvents" tree when the file changes.

  fMyHeadTree    = 0;
  fMyEventHeader = 0;

  // get current file
  TFile *file     = GetCurrentFile();
  if (!file) 
    return kFALSE;
  else
    printf(" Cataloging file: %s\n",file->GetName());
  
  // get all event header tree / or the Events tree
  fMyHeadTree = dynamic_cast<TTree*>(file->Get(fAllHeadTreeName));
  if (fMyHeadTree) {
    // get all event header branch
    if (fMyHeadTree->GetBranch(Names::gkAllEvtHeaderBrn))
      fMyHeadTree->SetBranchAddress(Names::gkAllEvtHeaderBrn,&fMyEventHeader);
    else {
      SendError(kWarning, "Notify", "Cannot find branch '%s' in tree '%s'", 
		Names::gkAllEvtHeaderBrn, fAllHeadTreeName.Data());
      return kFALSE;
    }
  }
  else {
    SendError(kWarning, "Notify","Cannot find tree '%s' in file '%s'", 
	      fAllHeadTreeName.Data(),file->GetName());
    // revert to the standard 'Events' header (file is not result of a skim)
    fMyHeadTree = dynamic_cast<TTree*>(file->Get(Names::gkEvtTreeName));
    // get all event header branch
    if (fMyHeadTree->GetBranch(Names::gkEvtHeaderBrn)) {
      fMyHeadTree->SetBranchAddress(Names::gkEvtHeaderBrn,&fMyEventHeader);
    } else {
      SendError(kWarning, "Notify", "Cannot find branch '%s' in tree '%s'", 
		Names::gkEvtHeaderBrn, Names::gkEvtTreeName);
      return kFALSE;
    }
  }

  // now we have the proper tree and the event headers, do the loop
  int  curEnt  = 0;
  uint lastRun = 999999999;
  const Int_t neMax = fMyHeadTree->GetEntries();
  printf(" Looping over: %d events\n",neMax);
  while (curEnt < neMax) {
    fMyHeadTree->GetEntry(curEnt++);                   // get all next records attached to branches
    EventHeader *eh = fMyEventHeader;
    if (lastRun != eh->RunNum()) {
      BeginRunAll(eh);
      lastRun = eh->RunNum();
    }
    if (curEnt >= neMax-1)
      printf(" Last event: %d  RN: %d EN: %d\n",curEnt-1,eh->RunNum(),eh->EvtNum());
    ProcessAll(eh);
  }
  
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::Process()
{
  // Add new event (this is only for the fully stored events)

  // count events
  fMetaData.AddEvent();
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::BeginRun()
{
  printf(" New run number -- RunInfo: %d  EventHeader: %d\n",
	 GetRunInfo()->RunNum(),GetEventHeader()->RunNum());
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::SlaveTerminate()
{
  // Print cataloging module message.

  if (gDebugLevel > 0)
    cout << "\n"
	 << " ============================----\n"
	 << " CatalogingMod::SlaveTerminate -- MetaInformation for analyzed events\n"
	 << " ================================\n"
	 << " Number of lumi sections: " << fMetaData.NLumiSecs() << endl
	 << " Number of events       : " << fMetaData.NEvents()   << endl
	 << " min(Run,LumiSec)       : ("
	 << fMetaData.MinRun() << "," << fMetaData.MinLumiSecInMinRun() << ")\n"
	 << " max(Run,LumiSec)       : ("
	 << fMetaData.MaxRun() << "," << fMetaData.MaxLumiSecInMaxRun() << ")\n\n";
  
  printf("%04d %-60s %9d %9d %9d %6d %9d %6d\n",
	 fNFileSet                     ,
	 fMetaDataString.Data        (),
	 fMetaData.NAllEvents        (),
	 fMetaData.NEvents           (),
	 fMetaData.MinRun            (),
	 fMetaData.MinLumiSecInMinRun(),
	 fMetaData.MaxRun            (),
	 fMetaData.MaxLumiSecInMaxRun() );

  if (gDebugLevel > 0)
    cout << "\n";
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::BeginRunAll(EventHeader *eh)
{
  // Reset the last luminosity section and get access to all events

  fLastLumiSec = 999999999;
  fMetaData.AddRun(eh->RunNum(),eh->LumiSec());
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::ProcessAll(EventHeader *eh)
{
  // Add new event and update luminosity section counter.

  // count events
  fMetaData.AddAllEvent();
  // count luminosity sections
  if (fLastLumiSec != eh->LumiSec())
    fMetaData.AddLumiSec(eh->RunNum(),eh->LumiSec());
}
