// $Id: runSimpleExample.C,v 1.10 2009/03/23 14:56:32 loizides Exp $

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
      TestMod() : fSumPt(0), fCount(0) {}
    protected:
      void        Process() { 
        LoadBranch("GsfTracks"); 
        for(UInt_t i=0;i<fCol->Entries();++i) {
          fSumPt+=fCol->At(i)->Pt();
          ++fCount;
        }
      }
      void        SlaveBegin() { 
        ReqBranch("GsfTracks",fCol);
      }
      void        SlaveTerminate() { 
        printf("Avg pt found: %f", fSumPt/fCount);
      }

      const TrackCol *fCol;
      Double_t        fSumPt;
      Int_t           fCount;

    ClassDef(TestMod, 1)
  };
}

//--------------------------------------------------------------------------------------------------
void runGsfTrackTest(const char *files = "mit-gen_000.root")
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  TestMod *tmod = new TestMod;
  
  // set up analysis
  Analysis *ana = new Analysis;
  ana->SetSuperModule(tmod);
  ana->AddFile(files);
  ana->SetUseHLT(0);
  if (gROOT->IsBatch()) 
    ana->SetOutputName("mit-example-hist.root");
  
  // run the analysis after successful initialisation
  ana->Run(!gROOT->IsBatch());
}
