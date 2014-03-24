#include <TSystem.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/DataUtil/interface/Cacher.h"

using namespace std;
using namespace mithep;

ClassImp(mithep::Cacher)

//--------------------------------------------------------------------------------------------------
Cacher::Cacher(const TList *list) :
  fInputList(list), 
  fCurrentFileIdx(-1),
  fCachedFileIdx(-1),
  fNFilesAhead(2)
{
  // Constructor

  //create the synchronized cache status vector
  for (Int_t i=0; i<fInputList->GetEntries(); i++) {
    int status = 0;
    fCacheStatus.push_back(status);
  }
}

//--------------------------------------------------------------------------------------------------
Bool_t Cacher::InitialCaching()
{
  // Caching to get the job going. This needs to be done before Run (maybe in SlaveBegin?)

  Bool_t status = kTRUE;
  for (Int_t i=0; i<fInputList->GetEntries(); i++) {
    MDB(kTreeIO, 1)
      Info("Cacher::InitialCaching","cache file: %s",fInputList->At(i)->GetName());
    // here we need to submit the caching request
    status = (status && SubmitSmartCacheRequest(fInputList->At(i)->GetName()));
    // keep track of the book keeping
    fCachedFileIdx++;
    fCacheStatus[i] = 1;
    if (i>=fNFilesAhead-1)
      break;
  }

  // Need to wait for download completion of first two files to get going
  Bool_t complete = kFALSE;
  while (! complete) {                                  // potential deadlock - needs exist strategy
    complete = kTRUE;
    for (Int_t i=0; i<min(2,fInputList->GetEntries()); i++) {
      if (Exists(fInputList->At(i)->GetName()))
	fCacheStatus[i] = 2;
      else
	complete = kFALSE;
    }
    if (complete) {
      MDB(kTreeIO, 1)
	Info("Cacher::InitialCaching","completed initial caching\n");
      break;
    }
    sleep(10); // wait 10 seconds
  }

  return status;
}

//--------------------------------------------------------------------------------------------------
Bool_t Cacher::NextCaching()
{
  // Caching to be triggered after the job already started, checks and waits for completion of the
  // next-to-next file needed and submits the next caching request.

  Bool_t status = kTRUE;

  // Submit the next caching request first
  fCachedFileIdx++;
  if (fCachedFileIdx<fInputList->GetEntries()) {
    MDB(kTreeIO, 1)
      Info("Cacher::NextCaching","cache file: %s",fInputList->At(fCachedFileIdx)->GetName());
    status = SubmitSmartCacheRequest(fInputList->At(fCachedFileIdx)->GetName());
    fCacheStatus[fCachedFileIdx] = 1;
  }
  else {
    MDB(kTreeIO, 2)
      Info("Cacher::NextCaching","no more files to cache");
    return status;
  }

  // Next: wait for download completion of last requested file (needs to be available to the job)
  Bool_t complete = kFALSE;
  while (! complete) {                                  // potential deadlock - needs exist strategy
    complete = kTRUE;

    if (Exists(fInputList->At(fCachedFileIdx-1)->GetName())) {
      fCacheStatus[fCachedFileIdx-1] = 2;
      MDB(kTreeIO, 2)
	Info("Cacher::NextCaching","completed");
      break;
    }
    else
      complete = kFALSE;

    MDB(kTreeIO, 2)
      Info("Cacher::NextCaching","waiting for completion (10 sec)");
    sleep(10); // wait 10 seconds
  }

  return status;
}

//--------------------------------------------------------------------------------------------------
Bool_t Cacher::SubmitSmartCacheRequest(const char* file)
{
  // Submit a SmartCache request for the specified file

  MDB(kTreeIO, 1)
    Info("Cacher::SubmitSmartCacheRequest","request file: %s",file);

  TString cmd = TString(gSystem->Getenv("CMSSW_BASE"))+TString("/src/MitAna/bin/requestFile.sh ")
               +TString(file);

  // Execute the system command
  int rc = gSystem->Exec(cmd.Data());
  
  return (rc == 0);
}

//--------------------------------------------------------------------------------------------------
Bool_t Cacher::Exists(const char* file)
{
  // Check if the specified file exists

  Long_t *id=0,*size=0,*flags=0,*mt=0;

  MDB(kTreeIO, 2)
    Info("Cacher::Exists","test file: %s (test returns %d)",file,
	 gSystem->GetPathInfo(file,id,size,flags,mt));

  return (gSystem->GetPathInfo(file,id,size,flags,mt) == 0);
}
