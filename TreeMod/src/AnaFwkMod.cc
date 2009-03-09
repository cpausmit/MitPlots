// $Id: AnaFwkMod.cc,v 1.3 2008/11/25 15:57:49 loizides Exp $

#include "MitAna/TreeMod/interface/AnaFwkMod.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include <TFile.h>
#include <TH1D.h>
#include <TStopwatch.h>
#include <TTree.h>

using namespace mithep;

ClassImp(mithep::AnaFwkMod)

//--------------------------------------------------------------------------------------------------
AnaFwkMod::AnaFwkMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fSWtotal(0),
  fSWevent(0),
  fAllHeaders(0,"AllEventHeaders"),
  fAllHeadTree(0),
  fAllEventHeader(0),
  fReload(kFALSE),
  fCurEnt(-2)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::BeginRun()
{
  // Get HLT tree and set branches if new file was opened. Read next entry in HLT key
  // depending on entry in RunInfo.

  if (fReload) {

    // reset to be (re-)loaded variables
    fReload         = 0;
    fAllHeadTree    = 0;
    fAllEventHeader = 0;
    fCurEnt         = 0;

    // get current file
    TFile *file = GetCurrentFile();
    if (!file) 
      return;

    // get HLT tree
    fAllHeadTree = dynamic_cast<TTree*>(file->Get(fAllHeadTreeName));
    if (!fAllHeadTree) {
      return;
    }
  }

  // get HLT trigger name branch
  if (fAllHeadTree->GetBranch(fAllHeadBrName)) {
    fAllHeadTree->SetBranchAddress(fAllHeadBrName, &fAllEventHeader);
  } else {
    SendError(kWarning, "BeginRun",
              "Can not find branch with name %s in tree %s", 
              fAllHeadBrName.Data(), fAllHeadTreeName.Data());
    return;
  }
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::CopyAllEventHeaders()
{
  // Deal with the headers from all events if needed.

  fAllHeaders.Reset();

  const EventHeader *curev = GetEventHeader();
  if (!curev) {
    SendError(kWarning, "CopyAllEventHeaders", "Can not obtain current event");
    return;
  }

  if (fAllHeadTree) {
    fAllHeadTree->GetEntry(fCurEnt++);
    while(fAllEventHeader->IsRemoved()) {
      EventHeader *eh = fAllHeaders.AddNew();
      eh->SetRunNum(fAllEventHeader->RunNum());
      eh->SetEvtNum(fAllEventHeader->EvtNum());
      eh->SetLumiSec(fAllEventHeader->LumiSec());
      eh->SetIsRemoved(fAllEventHeader->RunEntry());
      eh->SetRunEntry(fAllEventHeader->IsRemoved());
      fAllHeadTree->GetEntry(fCurEnt++);
    }
    if ((fAllEventHeader->RunNum()!=curev->RunNum())   ||
        (fAllEventHeader->EvtNum()!=curev->EvtNum())   ||
        (fAllEventHeader->LumiSec()!=curev->LumiSec()) ||
        (fAllEventHeader->RunEntry()!=curev->RunEntry())) {
      SendError(kWarning, "CopyAllEventHeaders", 
                "Event header information inconsistent: %d==%d, %d==%d, %d==%d, %d==%d",
                fAllEventHeader->RunNum(),   curev->RunNum(), 
                fAllEventHeader->EvtNum(),   curev->EvtNum(),
                fAllEventHeader->LumiSec(),  curev->LumiSec(),
                fAllEventHeader->RunEntry(), curev->RunEntry());
      return;
    }
  }
}

//--------------------------------------------------------------------------------------------------
Bool_t AnaFwkMod::Notify()
{
  // Make sure to get the new "AllEvents" tree when the file changes.

  fReload = kTRUE;
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::Process()
{
  // Do event counting and print out timing information.

  

  // counting events
  IncNEventsProcessed();

  // check if printout should be done
  Bool_t doPrint = 0;

  MDB(kAnalysis, 4) {
    if (GetNEventsProcessed() % 1000  == 0) 
      doPrint = 1;
  } else {
    MDB(kAnalysis, 3) {
      if (GetNEventsProcessed() % 10000  == 0) 
        doPrint = 1;
    } else {
      MDB(kAnalysis, 2) {
        if (GetNEventsProcessed() % 50000  == 0) 
          doPrint = 1;
      } else {
        MDB(kAnalysis, 1) {
          if (GetNEventsProcessed() % 250000 == 0) 
            doPrint = 1;
        } 
      }
    }
  }

  if (doPrint) {
    fSWevent->Stop();
    Info("Process", "Events %d -> %.2gs real, %.2gs cpu (%.2g real, %.2g cpu per event)", 
         GetNEventsProcessed(), fSWevent->RealTime(), fSWevent->CpuTime(),
         fSWevent->RealTime()/GetNEventsProcessed(), fSWevent->CpuTime()/GetNEventsProcessed());
    fSWevent->Start();
  }  
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::SlaveBegin()
{
  // Book our histogram and start the stop watches.

  fSWtotal = new TStopwatch;
  fSWevent = new TStopwatch;

  if (!PublishObj(&fAllHeaders)) {
    SendError(kAbortAnalysis, "SlaveBegin", 
              "Could not publish all event headers with name %s.", fAllHeaders.GetName());
    return;
  }
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::SlaveTerminate()
{
  // Fill event histogram and printout timing information.

  RetractObj(fAllHeaders.GetName());

  SaveNEventsProcessed();

  fSWtotal->Stop();
  fSWevent->Stop();

  MDB(kAnalysis, 1)
    Info("SlaveTerminate", "Events %d -> %.2gs real, %.2gs cpu (%.2gs real, %.2gs cpu per event)", 
         GetNEventsProcessed(), fSWtotal->RealTime(), fSWtotal->CpuTime(),
         fSWtotal->RealTime()/GetNEventsProcessed(), fSWtotal->CpuTime()/GetNEventsProcessed());

  delete fSWtotal;
  delete fSWevent;
}

