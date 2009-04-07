// $Id: runGsfTracksTest.C,v 1.1 2009/04/07 11:06:03 loizides Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/DataTree/interface/CaloMet.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/PhysicsMod/interface/SimpleExampleMod.h"
#endif

namespace mithep 
{
  class TestMod : public BaseMod
  {
    public:
      TestMod(const char *n="GsfTracks") : fCol(0), fName(n), fSumPt(0), fCount(0) {}
    protected:
      void        Process() { 
        LoadBranch(fName); 
        for(UInt_t i=0;i<fCol->GetEntries();++i) {
          fSumPt+=fCol->At(i)->Pt();
          ++fCount;
        }
      }
      void        SlaveBegin() { 
        ReqBranch(fName,fCol);
      }
      void        SlaveTerminate() { 
        printf("TestMod: %s -> Avg pt found: %f (%f/%d)\n", fName.Data(), fSumPt/fCount, fSumPt, fCount);
      }

      const TrackCol *fCol;
      TString         fName;
      Double_t        fSumPt;
      Int_t           fCount;

    ClassDef(TestMod, 1)
  };
}

//--------------------------------------------------------------------------------------------------
void runGsfTrackTest(const char *files, UInt_t nev=0)
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  TestMod *tmod1 = new TestMod("GsfTracks");
  TestMod *tmod2 = new TestMod("Tracks");
  
  // set up analysis
  Analysis *ana = new Analysis;
  ana->AddSuperModule(tmod1);
  ana->AddSuperModule(tmod2);
  ana->AddFile(files);
  ana->SetUseHLT(0);
  if (nev)
    ana->SetProcessNEvents(nev);

  if (gROOT->IsBatch()) 
    ana->SetOutputName("mit-example-hist.root");
  
  // run the analysis after successful initialisation
  ana->Run(!gROOT->IsBatch());
}
