#include <TSystem.h>
#include <TProfile.h>
#include "MitCommon/Utils/interface/Utils.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/Catalog/interface/Catalog.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/OutputMod.h"
#include "MitAna/PhysicsMod/interface/RunLumiSelectionMod.h"
#include "MitAna/PhysicsMod/interface/SkimMod.h"
#include "MitPhysics/Init/interface/ModNames.h"
#include "MitPhysics/Utils/interface/RhoUtilities.h"
#include "MitPhysics/Mods/interface/GeneratorMod.h"
#include "MitPhysics/Mods/interface/GoodPVFilterMod.h"
#include "MitPhysics/Mods/interface/MuonIDMod.h"

//--------------------------------------------------------------------------------------------------
void runBavanti(const char *fileset    = "0000",
		const char *skim       = "noskim",
		const char *dataset    = "r12b-smu-j22-v1",
		const char *book       = "t2mit/filefi/032",
		const char *catalogDir = "/home/cmsprod/catalog",
		const char *outputName = "boostedv",
		int         nEvents    = 1000)
{
  //------------------------------------------------------------------------------------------------
  // some parameters get passed through the environment
  //------------------------------------------------------------------------------------------------
  TString cataDir  = Utils::GetCatalogDir(catalogDir);
  TString mitData  = Utils::GetEnv("MIT_DATA");
  TString json     = Utils::GetEnv("MIT_PROD_JSON");
  TString jsonFile = Utils::GetJsonFile("/home/cmsprod/cms/json");

  Bool_t  isData   = (json.CompareTo("~") != 0);
  printf("\n Initialization worked. Data?: %d\n\n",isData);

  //------------------------------------------------------------------------------------------------
  // some global setups
  //------------------------------------------------------------------------------------------------
  // debugging config
  using namespace mithep;
  gDebugMask  = (Debug::EDebugMask) (Debug::kGeneral | Debug::kTreeIO);
  gDebugLevel = 3;

  // Caching and how
  Int_t local = 1, cacher = 1;

  // local =   0 - as is,
  //           1 - /mt/hadoop  (MIT:SmartCache - preload one-by-one)
  //           2 - /mnt/hadoop (MIT:SmartCache - preload complete fileset)
  //           3 - ./          (xrdcp          - preload one-by-one)
  // cacher =  0 - no file by file caching
  //           1 - file by file caching on

  //------------------------------------------------------------------------------------------------
  // set up information for master module
  //------------------------------------------------------------------------------------------------
  RunLumiSelectionMod *runLumiSel = new RunLumiSelectionMod;
  runLumiSel->SetAcceptMC(kTRUE);                          // Monte Carlo events are always accepted
  
  // only select on run- and lumisection numbers when valid json file present
  if (json.CompareTo("~") != 0 && json.CompareTo("-") != 0) {
    printf(" runBoostedV() - adding jsonFile: %s\n",jsonFile.Data());
    runLumiSel->AddJSONFile(jsonFile.Data());
  }
  if (json.CompareTo("-") == 0) {
    printf("\n WARNING -- Looking at data without JSON file: always accept.\n\n");
    runLumiSel->SetAbortIfNotAccepted(kFALSE);   // accept all events if there is no valid JSON file
  }
  printf("\n Run lumi worked. \n\n");

  //------------------------------------------------------------------------------------------------
  // setup analysis
  //------------------------------------------------------------------------------------------------
  Analysis *ana = new Analysis;
  ana->SetUseCacher(cacher);
  ana->SetUseHLT(kTRUE);
  ana->SetKeepHierarchy(kTRUE);
  ana->SetSuperModule(runLumiSel);
  ana->SetPrintScale(100);
  if (nEvents >= 0)
    ana->SetProcessNEvents(nEvents);

  //------------------------------------------------------------------------------------------------
  // organize input
  //------------------------------------------------------------------------------------------------
  Catalog *c = new Catalog(cataDir.Data());
  TString skimdataset = TString(dataset)+TString("/") +TString(skim);
  Dataset *d = NULL;
  TString bookstr = book;
  if (TString(skim).CompareTo("noskim") == 0)
    d = c->FindDataset(bookstr,dataset,fileset,local);
  else 
    d = c->FindDataset(bookstr,skimdataset.Data(),fileset,local);
  ana->AddDataset(d);

  //------------------------------------------------------------------------------------------------
  // organize output
  //------------------------------------------------------------------------------------------------
  TString rootFile = TString(outputName);
  rootFile += TString("_") + TString(dataset) + TString("_") + TString(skim);
  if (TString(fileset) != TString(""))
    rootFile += TString("_") + TString(fileset);
  ana->SetOutputName(rootFile + TString(".root"));
  ana->SetCacheSize(0);

  //------------------------------------------------------------------------------------------------
  // select events with a good primary vertex
  //------------------------------------------------------------------------------------------------
  GoodPVFilterMod *goodPvFilterMod = new GoodPVFilterMod;
  goodPvFilterMod->SetMinVertexNTracks(0);
  goodPvFilterMod->SetMinNDof(4.0);
  goodPvFilterMod->SetMaxAbsZ(24.0);
  goodPvFilterMod->SetMaxRho(2.0);
  goodPvFilterMod->SetIsMC(!isData);
  goodPvFilterMod->SetVertexesName("PrimaryVertexes");

  //------------------------------------------------------------------------------------------------
  // object id and cleaning sequence
  //------------------------------------------------------------------------------------------------

  MuonIDMod *muonId = new MuonIDMod;
  muonId->SetOutputName("CleanMuons");
  muonId->SetIntRadius(0.0);
  muonId->SetClassType("GlobalTracker");
  muonId->SetIDType("WWMuIdV4");
  muonId->SetIsoType("IsoRingsV0_BDTG_Iso");
  muonId->SetApplyD0Cut(kTRUE);
  muonId->SetApplyDZCut(kTRUE);
  muonId->SetWhichVertex(0);
  muonId->SetRhoType(RhoUtilities::CMS_RHO_RHOKT6PFJETS);
  muonId->SetPtMin(10.);
  muonId->SetEtaCut(2.4);

  //------------------------------------------------------------------------------------------------
  // save the interesting collection using the skim modules and the output module
  //------------------------------------------------------------------------------------------------
  SkimMod<Track> *skmGlobalMuonTracks = new SkimMod<Track>;
  skmGlobalMuonTracks->SetBranchName("GlobalMuonTracks");
  skmGlobalMuonTracks->SetColFromBranch(kTRUE);
  skmGlobalMuonTracks->SetColMarkFilter(kTRUE);
  skmGlobalMuonTracks->SetPublishArray(kFALSE);

  SkimMod<Track> *skmStandaloneMuonTracks = new SkimMod<Track>;
  skmStandaloneMuonTracks->SetBranchName("StandaloneMuonTracks");
  skmStandaloneMuonTracks->SetColFromBranch(kTRUE);
  skmStandaloneMuonTracks->SetColMarkFilter(kTRUE);
  skmStandaloneMuonTracks->SetPublishArray(kFALSE);

  SkimMod<Track> *skmStandaloneMuonTracksWVtxConstraint = new SkimMod<Track>;
  skmStandaloneMuonTracksWVtxConstraint->SetBranchName("StandaloneMuonTracksWVtxConstraint");
  skmStandaloneMuonTracksWVtxConstraint->SetColFromBranch(kTRUE);
  skmStandaloneMuonTracksWVtxConstraint->SetColMarkFilter(kTRUE);
  skmStandaloneMuonTracksWVtxConstraint->SetPublishArray(kFALSE);

  SkimMod<Track> *skmTracks = new SkimMod<Track>;
  skmTracks->SetBranchName("Tracks");
  skmTracks->SetColFromBranch(kTRUE);
  skmTracks->SetColMarkFilter(kTRUE);
  skmTracks->SetPublishArray(kFALSE);

  SkimMod<Muon> *skmMuons = new SkimMod<Muon>;
  skmMuons->SetBranchName("Muons");
  skmMuons->SetColFromBranch(kTRUE);
  skmMuons->SetColMarkFilter(kTRUE);
  skmMuons->SetPublishArray(kTRUE);

  OutputMod *outMod1 = new OutputMod;
  outMod1->Drop("*");
  outMod1->Keep("Muons");
  outMod1->Keep("GlobalMuonTracks");
  outMod1->Keep("StandaloneMuonTracks");
  outMod1->Keep("StandaloneMuonTracksWVtxConstraint");
  outMod1->Keep("Tracks");
  outMod1->SetKeepTamBr(kTRUE);
  outMod1->SetFileName("bambu");

  OutputMod *outMod2 = new OutputMod;
  outMod2->Drop("*");
  outMod2->AddNewBranch(TString("SkmMuons"));
  outMod2->AddNewBranch(TString("SkmGlobalMuonTracks"));
  outMod1->AddNewBranch(TString("SkmStandaloneMuonTracks"));
  outMod1->AddNewBranch(TString("SkmStandaloneMuonTracksWVtxConstraint"));
  outMod2->AddNewBranch(TString("SkmTracks"));
  outMod2->SetKeepTamBr(kFALSE);
  outMod2->SetFileName("bavanti");

  //------------------------------------------------------------------------------------------------
  // making analysis chain
  //------------------------------------------------------------------------------------------------
  runLumiSel                           ->Add(goodPvFilterMod);
  //goodPvFilterMod                      ->Add(skmGlobalMuonTracks);
  goodPvFilterMod                      ->Add(muonId);
  muonId                               ->Add(skmGlobalMuonTracks);
  skmGlobalMuonTracks                  ->Add(skmStandaloneMuonTracks);
  skmStandaloneMuonTracks              ->Add(skmStandaloneMuonTracksWVtxConstraint);
  skmStandaloneMuonTracksWVtxConstraint->Add(skmTracks);
  skmTracks                            ->Add(skmMuons);
  skmMuons                             ->Add(outMod1);
  outMod1                              ->Add(outMod2);
  
  //muonId             ->Add(outMod1);
  //muonId             ->Add(skmMuons);
  //skmMuons           ->Add(outMod1);
  //muonId             ->Add(skmMuons);
  //skmMuons           ->Add(skmGlobalMuonTracks);
  //skmGlobalMuonTracks->Add(outMod1);
  //outMod1            ->Add(outMod2);
  //------------------------------------------------------------------------------------------------
  // Say what we are doing
  //------------------------------------------------------------------------------------------------
  printf("\n==== PARAMETER SUMMARY FOR THIS JOB ====\n");
  printf("\n JSON file: %s\n",jsonFile.Data());
  printf("\n Rely on Catalog: %s\n",cataDir.Data());
  printf("  -> Book: %s  Dataset: %s  Skim: %s  Fileset: %s <-\n",book,dataset,skim,fileset);
  printf("\n Root output:   %s\n",rootFile.Data());  
  printf("\n========================================\n");

  //------------------------------------------------------------------------------------------------
  // run the analysis after successful initialisation
  //------------------------------------------------------------------------------------------------
  ana->Run(!gROOT->IsBatch());

  return;
}
