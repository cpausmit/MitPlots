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

  using namespace std;
  
  if (gDebugLevel > 0){
    cout << " ============================" << endl;
    cout << " CatalogingMod::SlaveBegin -- Creating MetaInformation for the coming events" << endl;
    cout << " ============================" << endl;
  }

  fTriggers = GetHLTTable();
  if (! fTriggers) {
    cout << " Has trigger table is: " << HasHLTInfo() << endl;
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
    std::cout << " Cataloging file: " << file->GetName() << std::endl;
  
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
  std::cout << " Looping over: " << neMax << " events" << std::endl;
  while (curEnt < neMax) {
    fMyHeadTree->GetEntry(curEnt++);                   // get all next records attached to branches
    EventHeader *eh = fMyEventHeader;
    if (lastRun != eh->RunNum()) {
      BeginRunAll(eh);
      lastRun = eh->RunNum();
    }
    if (curEnt >= neMax-1)
      std::cout << " Last event: " << (curEnt-1) << "  RN: " << eh->RunNum() << " EN: " << eh->EvtNum() << std::endl;
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
  std::cout << " New run number -- RunInfo: " << GetRunInfo()->RunNum() << "  EventHeader: " << GetEventHeader()->RunNum() << std::endl;
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::SlaveTerminate()
{
  // Print cataloging module message.
  using namespace std;

  if (gDebugLevel > 0){
    cout << endl;
    cout << " ============================----" << endl;
    cout << " CatalogingMod::SlaveTerminate -- MetaInformation for analyzed events" << endl;
    cout << " ================================" << endl;
    cout << " Number of lumi sections: " << fMetaData.NLumiSecs() << endl;
    cout << " Number of events       : " << fMetaData.NEvents() << endl;
    cout << " min(Run,LumiSec)       : (" << fMetaData.MinRun() << "," << fMetaData.MinLumiSecInMinRun() << ")" << endl;
    cout << " max(Run,LumiSec)       : (" << fMetaData.MaxRun() << "," << fMetaData.MaxLumiSecInMaxRun() << ")" << endl;
    cout << endl;
  }
  
  cout << TString::Format("%04d %-60s %9d %9d %9d %6d %9d %6d",
                          fNFileSet                     ,
                          fMetaDataString.Data        (),
                          fMetaData.NAllEvents        (),
                          fMetaData.NEvents           (),
                          fMetaData.MinRun            (),
                          fMetaData.MinLumiSecInMinRun(),
                          fMetaData.MaxRun            (),
                          fMetaData.MaxLumiSecInMaxRun()) << endl;

  if (gDebugLevel > 0) cout << endl;
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
