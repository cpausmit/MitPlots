// $Id: AnaFwkMod.cc,v 1.2 2008/11/19 17:16:10 loizides Exp $

#include "MitAna/TreeMod/interface/AnaFwkMod.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include <TH1D.h>
#include <TStopwatch.h>

using namespace mithep;

ClassImp(mithep::AnaFwkMod)

//--------------------------------------------------------------------------------------------------
AnaFwkMod::AnaFwkMod(const char *name, const char *title) : 
  BaseMod(name,title),
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
}

//--------------------------------------------------------------------------------------------------
void AnaFwkMod::SlaveTerminate()
{
  // Fill event histogram and printout timing information.

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
