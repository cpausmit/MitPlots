// $Id: TreeWriter.cc,v 1.17 2009/07/13 20:04:13 loizides Exp $

#include "MitAna/DataUtil/interface/TreeWriter.h"
#include <Riostream.h>
#include <TObject.h>
#include <TSystem.h>
#include <TProcessID.h>
#include <TBranchRef.h>
#include "MitAna/DataUtil/interface/Debug.h"

using namespace mithep;

ClassImp(mithep::TreeWriter)

//__________________________________________________________________________________________________
TreeWriter::TreeWriter(const char *tname, Bool_t doreset) : 
  TNamed(tname,Form("%s written by mithep::TreeWriter", tname)),
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
  fDoBranchRef(0), 
  fFile(0), 
  fTrees(0)
{
  // Constructor.

  fTrees.SetOwner();
}

//__________________________________________________________________________________________________
TreeWriter::~TreeWriter()
{
  // Destructor.
   
  Terminate();
}

//__________________________________________________________________________________________________
void TreeWriter::AddBranch(const char *name, const char *cname, 
                           void *obj, Int_t bsize, Int_t level)
{
  // Add branch with name "name" into tree with name "tname" and set its address to object pointer
  // for class name "cname" using a given buffer size and splitlevel.

  MyTree  *t = AddOrGetMyTree(GetName());
  TBranch *b = t->Bronch(name, cname, obj, bsize, level);
  b->SetCompressionLevel(GetCompressLevel());
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranch(const char *name, void *obj, Int_t bsize, Int_t level)
{
  // Add branch with name "name" into tree with name "tname" and set its address to object pointer
  // using a given buffer size and splitlevel.

  AddBranch(name, CName(obj), obj, bsize, level);
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranch(const char *name, const char *cname, 
                           void *obj, Int_t bsize)
{
  // Add branch with name "name" into tree with name "tname" and set its address to object pointer
  // for class name "cname" using a given buffer size and default splitlevel.

  MyTree  *t = AddOrGetMyTree(GetName());
  TBranch *b = t->Bronch(name, cname, obj, bsize, fDefSL);
  b->SetCompressionLevel(GetCompressLevel());
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranch(const char *name, void *obj, Int_t bsize)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer using a given buffer size and default splitlevel.

  AddBranch(name, CName(obj), obj, bsize);
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranch(const char *name, const char *cname, 
                           void *obj)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer for class name "cname" using a default buffer size and splitlevel.

  MyTree  *t = AddOrGetMyTree(GetName());
  TBranch *b = t->Bronch(name, cname, obj, fDefBrSize, fDefSL);
  b->SetCompressionLevel(GetCompressLevel());
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranch(const char *name, void *obj)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer using a default buffer size and splitlevel.

  AddBranch(name, CName(obj), obj);
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranchToTree(const char *tname, const char *name, const char *cname, 
                                 void *obj, Int_t bsize, Int_t level)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer for class name "cname" using a given buffer size and splitlevel.

  MyTree  *t = AddOrGetMyTree(tname);
  TBranch *b = t->Bronch(name, cname, obj, bsize, level);
  b->SetCompressionLevel(GetCompressLevel());
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranchToTree(const char *tname, const char *name, void *obj, 
                                 Int_t bsize, Int_t level)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer using a given buffer size and splitlevel.

  AddBranchToTree(tname, name, CName(obj), obj, bsize, level);
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranchToTree(const char *tname, const char *name, const char *cname, 
                                 void *obj, Int_t bsize)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer for class name "cname" using a given buffer size and default splitlevel.

  MyTree  *t = AddOrGetMyTree(tname);
  TBranch *b = t->Bronch(name, cname, obj, bsize, fDefSL);
  b->SetCompressionLevel(GetCompressLevel());
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranchToTree(const char *tname, const char *name, void *obj,
                                 Int_t bsize)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer using a given buffer size and default splitlevel.

  AddBranchToTree(tname, name, CName(obj), obj, bsize);
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranchToTree(const char *tname, const char *name, const char *cname, 
                                 void *obj)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer for class name "cname" using a default buffer size and splitlevel.

  MyTree  *t = AddOrGetMyTree(tname);
  TBranch *b = t->Bronch(name, cname, obj, fDefBrSize, fDefSL);
  b->SetCompressionLevel(GetCompressLevel());
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddBranchToTree(const char *tname, const char *name, void *obj)
{
  // Add branch with name "name" into tree with name "tname" and set its address 
  // to object pointer for class name "cname" using a default buffer size and splitlevel.

  AddBranchToTree(tname, name, CName(obj), obj);
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::AddTree(const char *tname)
{
  // Add tree with name "name" into tree with name "tname".

  AddOrGetMyTree(tname);
}

//--------------------------------------------------------------------------------------------------
MyTree *TreeWriter::AddOrGetMyTree(const char *tn)
{
  // Add new tree if not present in array of trees or return
  // present tree.

  MyTree *tree = GetMyTree(tn);
  if (tree)
    return tree;

  TDirectory::TContext context(fFile); 
  tree = new MyTree(tn, tn);
  tree->SetDirectory(fFile);
  if (fDoBranchRef)
    tree->BranchRef();
  fTrees.AddLast(tree);  
  return tree;
}

//--------------------------------------------------------------------------------------------------
Bool_t TreeWriter::BeginEvent(Bool_t doreset)
{
  // Prepare for the next event. If doreset or fDoObjNumReset is kTRUE
  // store the current object number to be reset in FillEvent().

  if (!fIsInit) {
    OpenFile();
  }

  if (doreset || fDoObjNumReset) {
    fEvtObjNum = TProcessID::GetObjectCount();
  }

  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::CloseFile()
{
  // Write tree(s) and close file.

  if (!fIsInit) {
    Fatal("CloseFile", "File was not opened, call OpenFile() first!");
    return;
  }

  TDirectory::TContext context(fFile); // cd fFile && 
                                       // automatically restore gDirectory

  for (Int_t i=0;i<fTrees.GetEntries();++i) {
    MyTree *mt = static_cast<MyTree*>(fTrees.At(i));
    mt->FlushBaskets();
    mt->Write(mt->GetName(),TObject::kOverwrite);

    // backup and restore list of branch pointers from TRefTable (needed for autoloading)
    if (mt->GetBranchRef()) {
      TObjArray *parents = mt->GetBranchRef()->GetRefTable()->GetParents();
      TObjArray parentsBak(*parents);
      mt->Reset();
      for (Int_t j=0; j<parentsBak.GetEntries(); ++j)
        parents->Add(parentsBak.At(j));
    }
    else
      mt->Reset();
    mt->SetDirectory(0);   
  }

  fFile->Close();
  delete fFile; 
  fFile = 0;

  fIsInit = kFALSE; 
  fFileNumber++;  
}

//--------------------------------------------------------------------------------------------------
const char *TreeWriter::CName(void *obj) const 
{
  // Dereference void* pointer into TObject* pointer

  TObject **sobj = static_cast<TObject**>(obj);
  TObject *tobj = dynamic_cast<TObject*>(*sobj);
  if (tobj==0) {
    Fatal("CName", "Given void* ptr cannot be dereferenced into TObject*");
  }
  return tobj->ClassName();
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::DoBranchRef(const char *tn)
{
  // Fill BranchRef for given tree.

  if (fTrees.GetEntries()==0) {
    Error("DoBranchRef", "Tree with name %s not found!", tn); 
    return;
  }

  MyTree *mt = GetMyTree(tn);
  if (!mt)
    return;

  mt->BranchRef();
}

//--------------------------------------------------------------------------------------------------
Bool_t TreeWriter::EndEvent(Bool_t doreset)
{
  // Store the event in the tree. If doreset or fDoObjNumReset is kTRUE
  // restore the stored object number at the time BeginEvent(kTRUE) 
  // was called.
   
  if (!fIsInit) {
    Fatal("EndEvent", "File is not open, did you call BeginEvent?");
    return kFALSE;
  }

  Int_t r = 0;
  for (Int_t i=0;i<fTrees.GetEntries();++i) {
    MyTree *mt = static_cast<MyTree*>(fTrees.At(i));
    if (mt->GetAutoFill()==0)
      continue;
    r += mt->Fill();
  }

  if (IsFull())
    CloseFile();

  if (doreset || fDoObjNumReset) {
    if (fEvtObjNum<0) {
      Error("EndEvent", "Object counter is zero. Did you call BeginEvent(kTRUE)?");
    } else {
      // Reset the TRef table. Keep it from growing with each event (see doc)
      TProcessID::SetObjectCount(fEvtObjNum);
    }
  }

  return (r >= 0);
}

//--------------------------------------------------------------------------------------------------
Long64_t TreeWriter::GetEntries(const char *tn) const
{ 
  // Return entries of tree with given name. If no tree is given, return sum of entries
  // of all trees.

   if (fTrees.GetEntries()==0) return -1;

   if (tn) {
     const TTree *mt=GetTree(tn);
     if (mt)
       return mt->GetEntries();
     else
       return -1;
   }

   Long64_t ret = 0;
   for (Int_t i=0;i<fTrees.GetEntries();++i) {
      const MyTree *mt = static_cast<const MyTree*>(fTrees.At(i));
      ret += mt->GetEntries();
   }
   return ret;
}

//--------------------------------------------------------------------------------------------------
MyTree *mithep::TreeWriter::GetMyTree(const char *tn)
{
  // Return MyTree with given name from array.

  if (fTrees.GetEntries()==0) 
    return 0;

  TObject *obj = 0;
  if (tn==0) {
    obj = fTrees.At(0);
  } else {
    obj = fTrees.FindObject(tn);
  }
  
  if (obj)  
    return static_cast<MyTree*>(obj);
  return 0;
}   

//--------------------------------------------------------------------------------------------------
const TTree *mithep::TreeWriter::GetTree(const char *tn) const
{
  // Return TTree with given name from array.

  if (fTrees.GetEntries()==0) 
    return 0;

  TObject *obj = 0;
  if (tn==0) {
    obj = fTrees.At(0);
  } else {
    obj = fTrees.FindObject(tn);
  }
  
  if (obj)  
    return dynamic_cast<const TTree*>(obj);
  return 0;
}   

//--------------------------------------------------------------------------------------------------
TTree *mithep::TreeWriter::GetTree(const char *tn)
{
  // Return TTree with given name from array.

  if (fTrees.GetEntries()==0) 
    return 0;

  TObject *obj = 0;
  if (tn==0) {
    obj = fTrees.At(0);
  } else {
    obj = fTrees.FindObject(tn);
  }
  
  if (obj)  
    return dynamic_cast<TTree*>(obj);
  return 0;
}   

//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
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

  for (Int_t i=0;i<fTrees.GetEntries();++i) {
    MyTree *mt = static_cast<MyTree*>(fTrees.At(i));
    mt->SetDirectory(fFile);
  }

  fIsInit = kTRUE;
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::Print(Option_t *option) const
{
  // Print the contents of the tree writer.

  if (option) {
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

//--------------------------------------------------------------------------------------------------
void TreeWriter::SetAutoFill(const char *tn, Bool_t b)
{
  // Set auto-fill mode of tree with given name.

  if (fTrees.GetEntries()==0)
    return;

  MyTree *mt = GetMyTree(tn);
  if (!mt)
    return;

  mt->SetAutoFill(b);
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::SetMaxSize(Long64_t s) 
{ 
  // Set maximum file size. Check if this exceeds the ROOT file size and if, 
  // print a warning and adjust it.

  if (s>=(Long64_t)(0.99 * TTree::GetMaxTreeSize())) {
    Long64_t news = (Long64_t)(s/0.99);
    Warning("SetMaxSize", "Maximum tree size increased from %lld to %lld",
            TTree::GetMaxTreeSize(), news);
    TTree::SetMaxTreeSize(news);
  }

  fMaxSize=s; 
}

//--------------------------------------------------------------------------------------------------
void TreeWriter::StoreObject(const TObject *obj)
{
  // Store object next to tree in file. Used to store the settings of how the tree was created.

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

//__________________________________________________________________________________________________
void TreeWriter::Terminate()
{
  // Terminate tree file writing.
   
  if (fIsInit) {
    CloseFile();
  }

  TDirectory::TContext context(0); 
  fTrees.Clear();
}
