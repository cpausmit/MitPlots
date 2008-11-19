// $Id: GeneratorMod.cc,v 1.4 2008/11/11 21:22:54 ceballos Exp $

#include "MitAna/TreeMod/interface/AnaFwkMod.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include <TH1D.h>
#include <TStopwatch.h>

using namespace mithep;

ClassImp(mithep::AnaFwkMod)

//--------------------------------------------------------------------------------------------------
AnaFwkMod::AnaFwkMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fNEventsProcessed(0),
  hDEvents(0),
  fSWtotal(0),
  fSWevent(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::Process()
{
  // Do event counting and print out timing information.

  // counting events
  fNEventsProcessed++;

  // check if printout should be done
  Bool_t doPrint = 0;

  MDB(kAnalysis, 4) {
    if (fNEventsProcessed % 1000  == 0) 
      doPrint = 1;
  } else {
    MDB(kAnalysis, 3) {
      if (fNEventsProcessed % 10000  == 0) 
        doPrint = 1;
    } else {
      MDB(kAnalysis, 2) {
        if (fNEventsProcessed % 50000  == 0) 
          doPrint = 1;
      } else {
        MDB(kAnalysis, 1) {
          if (fNEventsProcessed % 250000 == 0) 
            doPrint = 1;
        } 
      }
    }
  }

  if (doPrint) {
    fSWevent->Stop();
    Info("Process", "Events %d -> %.2gs real, %.2gs cpu (%.2g real, %.2g cpu per event)", 
         fNEventsProcessed, fSWevent->RealTime(), fSWevent->CpuTime(),
         fSWevent->RealTime()/fNEventsProcessed, fSWevent->CpuTime()/fNEventsProcessed);
    fSWevent->Start();
  }  
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::SlaveBegin()
{
  // Book our histogram and start the stop watches.

  hDEvents = new TH1D("hDEvents","hDEvents for overall event count",1,-0.5,0.5);
  AddOutput(hDEvents);

  fSWtotal = new TStopwatch;
  fSWevent = new TStopwatch;
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::SlaveTerminate()
{
  // Fill event histogram and printout timing information.

  hDEvents->Fill(0.0,fNEventsProcessed);
  hDEvents->SetEntries(fNEventsProcessed);

  fSWtotal->Stop();
  fSWevent->Stop();

  MDB(kAnalysis, 1)
    Info("SlaveTerminate", "Events %d -> %.2gs real, %.2gs cpu (%.2gs real, %.2gs cpu per event)", 
         fNEventsProcessed, fSWtotal->RealTime(), fSWtotal->CpuTime(),
         fSWtotal->RealTime()/fNEventsProcessed, fSWtotal->CpuTime()/fNEventsProcessed);

  delete fSWtotal;
  delete fSWevent;
}
