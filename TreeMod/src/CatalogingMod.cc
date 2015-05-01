#include <TFile.h>
#include <TTree.h>
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/CatalogingMod.h"

using namespace std;
using namespace mithep;

ClassImp(mithep::CatalogingMod)

//--------------------------------------------------------------------------------------------------
CatalogingMod::CatalogingMod(const char *name, const char *title) : 
  BaseMod           (name,title),
  fAllHeadTreeName  (Names::gkAllEvtTreeName),
  fMyHeadTree       (0),
  fMyEventHeader    (0),
  fMetaDataString   ("==MetaData=="),
  fNFileSet         (0),
  fCurrentFileIsSkim(kFALSE),
  fLastLumiSec      (999999999),
  fMetaData         (0,0,0,999999999,0,0,0)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::SlaveBegin()
{
  // Print out cataloging module message.
  if (gDebugLevel > 0){
    cout << " ============================" << endl;
    cout << " CatalogingMod::SlaveBegin -- Creating MetaInformation for the coming events" << endl;
    cout << " ============================" << endl;
  }
}

//--------------------------------------------------------------------------------------------------
Bool_t CatalogingMod::Notify()
{
  // Make sure to get the new "(All)Events" tree when the file changes.

  fMyHeadTree    = 0;
  fMyEventHeader = 0;

  // get current file
  TFile *file     = GetCurrentFile();
  if (!file) 
    return kFALSE;
  else
    cout << " Cataloging file: " << file->GetName() << endl;
  
  // The question to answer is: is this a fill containing all events or has this been skimmed such
  // that only the AllEvent tree contains all events?

  // get the tree (AllEvent or Event)
  fCurrentFileIsSkim = kFALSE;
  fMyHeadTree = dynamic_cast<TTree*>(file->Get(fAllHeadTreeName)); // try AllEvent tree first
  if (fMyHeadTree) {
    fCurrentFileIsSkim = kTRUE;
    // get all event header branch
    if (fMyHeadTree->GetBranch(Names::gkAllEvtHeaderBrn))
      fMyHeadTree->SetBranchAddress(Names::gkAllEvtHeaderBrn,&fMyEventHeader);
    else {
      SendError(kWarning,"Notify","Tree '%s' present but no branch '%s' -- THIS SHOULD NOT HAPPEN", 
		fAllHeadTreeName.Data(),Names::gkAllEvtHeaderBrn);
      return kFALSE;
    }
  }
  else {
    SendError(kWarning,"Notify","This is not a skim. Tree '%s' not in file '%s'",
	 fAllHeadTreeName.Data(),file->GetName());

    // revert to the standard 'Events' header (file is not result of a skim)
    fMyHeadTree = dynamic_cast<TTree*>(file->Get(Names::gkEvtTreeName));
    // get all event header branch
    if (fMyHeadTree->GetBranch(Names::gkEvtHeaderBrn))
      fMyHeadTree->SetBranchAddress(Names::gkEvtHeaderBrn,&fMyEventHeader);
    else {
      SendError(kWarning,"Notify","Cannot find branch '%s' in tree '%s'", 
		Names::gkEvtHeaderBrn,Names::gkEvtTreeName);
      return kFALSE;
    }
  }

  // This only needs to be done if this is a skimmed file. Access to the tree seems very suboptimal
  // but for a skim the AllEvents tree is very small, only headers.
  if (fCurrentFileIsSkim) {
    // now we have the proper tree and the event headers, do the loop
    int  curEnt  = 0;
    uint lastRun = 999999999;
    const Int_t neMax = fMyHeadTree->GetEntries();
    cout << " Analyzing Skim -- Looping over: " << neMax << " events" << endl;
    while (curEnt < neMax) {
      fMyHeadTree->GetEntry(curEnt++);                  // get all next records attached to branches
      EventHeader *eh = fMyEventHeader;
      if (lastRun != eh->RunNum()) {
	BeginRunAll(eh);
	lastRun = eh->RunNum();
      }
      if (curEnt >= neMax-1)
	cout << " Last event: " << (curEnt-1) << "  RN: " << eh->RunNum()
	     << " EN: " << eh->EvtNum() << endl;
      ProcessAll(eh);
    }
    cout << " Analyzing Skim -- loop complete." << endl;
  }    

  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::Process()
{
  // Add new event (this is only for the fully stored events)

  // count events
  fMetaData.AddEvent();
  if (! fCurrentFileIsSkim)
    fMetaData.AddAllEvent();
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::BeginRun()
{
  cout << " New run number -- RunInfo: " << GetRunInfo()->RunNum()
       << "  EventHeader: " << GetEventHeader()->RunNum() << endl;
  if (! fCurrentFileIsSkim) {
    fLastLumiSec = 999999999;
    fMetaData.AddRun(GetEventHeader()->RunNum(),GetEventHeader()->LumiSec());
  }
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
    cout << " min(Run,LumiSec)       : (" << fMetaData.MinRun() << ","
	 << fMetaData.MinLumiSecInMinRun() << ")" << endl;
    cout << " max(Run,LumiSec)       : (" << fMetaData.MaxRun() << ","
	 << fMetaData.MaxLumiSecInMaxRun() << ")" << endl;
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

  if (gDebugLevel > 0)
    cout << endl;
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
