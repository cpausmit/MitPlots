// $Id: TreeWriter.cxx 4071 2007-06-06 08:39:13Z loizides $

#include "MitAna/DataUtil/interface/TreeWriter.h"

#include <Riostream.h>
#include <TObject.h>
#include <TSystem.h>
#include <TProcessID.h>

using namespace mithep;

ClassImp(mithep::TreeWriter)

//__________________________________________________________________________________________________
TreeWriter::TreeWriter(const char *tname, Bool_t doreset)
  : TNamed(tname,Form("%s written by mithep::TreeWriter", tname)),
    fBaseURL("."), 
    fPrefix("mithep"), 
    fFileNumber(0),
    fCompressLevel(9),
    fDefBrSize(64*1024),
    fDefSL(99),
    fMaxSize((Long64_t)(0.99 * TTree::GetMaxTreeSize())),
    fkMinFreeSpace(1024*1024), 
    fkMinAvgSize(10*1024), 
    fEvtObjNum(-1), 
    fIsInit(kFALSE), 
    fDoObjNumReset(doreset), 
    fFile(0), 
    fTree(0)
{
  // Constructor.

  TDirectory::TContext context(0); 
  fTree = new TTree(GetName(), GetTitle());
  fTree->SetDirectory(0);
}

//__________________________________________________________________________________________________
TreeWriter::~TreeWriter()
{
  // Destructor.
   
  if(fIsInit) {
    CloseFile();
  }

  TDirectory::TContext context(0); 
  delete fTree;
}

//__________________________________________________________________________________________________
void TreeWriter::AddBranch(const char *name, const char *cname, void *obj, Int_t bsize, Int_t level)
{
  // Add branch with name "name" into tree and set its address to object pointer 
  // for class name "cname" using a given buffer size and splitlevel.

  fTree->Bronch(name, cname, obj, bsize, level);
}

//__________________________________________________________________________________________________
void TreeWriter::AddBranch(const char *name, const char *cname, void *obj, Int_t bsize)
{
  // Add branch with name "name" into tree and set its address to object pointer 
  // for class name "cname" using a given buffer size and default splitlevel.

  fTree->Bronch(name, cname, obj, bsize, fDefSL);
}

//__________________________________________________________________________________________________
void TreeWriter::AddBranch(const char *name, const char *cname, void *obj)
{
  // Add branch with name "name" into tree and set its address to object pointer 
  // for class name "cname" using a given buffer size and default splitlevel.

  fTree->Bronch(name, cname, obj, fDefBrSize, fDefSL);
}

//__________________________________________________________________________________________________
Bool_t TreeWriter::BeginEvent(Bool_t doreset)
{
  // Prepare for the next event. If doreset or fDoObjNumReset is kTRUE
  // store the current object number to be reset in FillEvent().

  if (!fIsInit) {
    OpenFile();
  }

  if(doreset || fDoObjNumReset) {
    fEvtObjNum = TProcessID::GetObjectCount();
  }

  return kTRUE;
}

//__________________________________________________________________________________________________
void TreeWriter::CloseFile()
{
  // Write tree and close file.

  if (!fIsInit) {
    Fatal("CloseFile", "File was not opened, call OpenFile() first!");
    return;
  }

  TDirectory::TContext context(fFile); // cd fFile && 
                                       // automatically restore gDirectory

  fTree->Write(fTree->GetName(),TObject::kOverwrite);
  fTree->Reset();
  fTree->SetDirectory(0);   

  fFile->Close();
  delete fFile; 
  fFile = 0;

  fIsInit = kFALSE; 
  fFileNumber++;  
}

//__________________________________________________________________________________________________
Bool_t TreeWriter::EndEvent(Bool_t doreset)
{
  // Store the event in the tree. If doreset or fDoObjNumReset is kTRUE
  // restore the stored object number at the time BeginEvent(kTRUE) 
  // was called.
   
  if (!fIsInit) {
    Fatal("EndEvent", "File is not open, did you call BeginEvent?");
    return kFALSE;
  }

  //TDirectory::TContext context(fFile);
  Int_t r = fTree->Fill();

  if(IsFull())
    CloseFile();

  if (doreset || fDoObjNumReset) {
    if (fEvtObjNum<0) {
      Error("EndEvent", "Object counter is zero. Did you call BeginEvent(kTRUE)?");
    } else {
      // Reset the TRef table. keep it from growing with each event (see doc)
      TProcessID::SetObjectCount(fEvtObjNum);
    }
  }

  return (r >= 0);
}

//__________________________________________________________________________________________________
Bool_t TreeWriter::IsFull() const
{
  // Check if the maximum file size has been reached.

  Long64_t entries = GetEntries();
   
  if (entries < 1) return kFALSE;
   
  Long64_t avgSize = GetFileSize() / entries;
   
  if (avgSize < fkMinAvgSize)
    avgSize = fkMinAvgSize;

  return (GetFileSize() + avgSize + fkMinFreeSpace) > fMaxSize;
}

//__________________________________________________________________________________________________
void TreeWriter::OpenFile()
{
  // Open the file and attach the tree.

  if (fIsInit) {
    Fatal("OpenFile", "File is already open, call CloseFile first!");
    return;
  }

  TDirectory::TContext context(0);
   
  TString pathname=GetFullName();
  gSystem->ExpandPathName(pathname);

  fFile = TFile::Open(pathname, "RECREATE");
  if (fFile == 0) {
    Fatal("OpenFile", "Could not open file %s", pathname.Data());
    return;
  }

  fFile->SetCompressionLevel(fCompressLevel);
  fTree->SetDirectory(fFile);
  fIsInit = kTRUE;
}

//__________________________________________________________________________________________________
void TreeWriter::Print(Option_t *option) const
{
  // Print the contents of the tree writer.

  if(option) {
    cout << ClassName() << " with members " << endl;
    cout << "   fBaseURL:       " << fBaseURL << endl; 
    cout << "   fPreFix:        " << fPrefix << endl; 
    cout << "   fFileNumber:    " << fFileNumber << endl; 
    cout << "   fCompressLevel: " << fCompressLevel << endl; 
    cout << "   fDefBrSize:     " << fDefBrSize << endl; 
    cout << "   fDefSL:         " << fDefSL << endl; 
    cout << "   fMaxSize:       " << fMaxSize << endl; 
    cout << "   fDoObjNumReset: " << fDoObjNumReset << endl;
    return;
  }

  cout << ClassName() << ": " << GetEntries() 
       << (GetEntries() == 1 ? " event" : " events") << endl;
}

//__________________________________________________________________________________________________
void TreeWriter::StoreObject(const TObject *obj)
{
  // Store object next to tree in file. Used to store the
  // settings of how the tree was created.

  if (!fIsInit) {
    Fatal("StoreObject", "Tree is not created, call create first!");
    return;
  }

  if (!obj) {
    Fatal("StoreObject", "Ptr to TObject is null!");
    return;
  }

  fFile->WriteTObject(obj,obj->GetName(),"WriteDelete");
}
