// $Id: runSkimmingExample.C,v 1.6 2009/08/11 15:32:46 loizides Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TSystem.h>
#include <TRandom.h>
#include <TParameter.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/OutputMod.h"
#endif

//--------------------------------------------------------------------------------------------------
void merge(const char *files, 
           const char *prefix="mergetest", 
           UInt_t nev=0)
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  OutputMod *omod = new OutputMod;
  omod->SetFileName(prefix);
  omod->Keep("*");

  Analysis *ana = new Analysis;
  ana->SetSuperModule(omod);
  if (nev)
    ana->SetProcessNEvents(nev);
  ana->AddFile(files);
  
  // run the analysis after successful initialisation
  ana->Run(0);
}
