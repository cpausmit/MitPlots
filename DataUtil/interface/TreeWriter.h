//--------------------------------------------------------------------------------------------------
// $Id: TreeWriter.h,v 1.14 2009/03/15 11:17:04 loizides Exp $
//
// TreeWriter
//
// Class implementing a tree writing infrastructure. The class creates and maintaines
// a standard tree with name "tname" as given in the constructor. The tree is stored in 
// a file or in multiple files if needed, where the file path name and maximum size can be
// specified. Using TreeWriter::AddBranch allows to add various branches to the tree.
// The user has to make sure that (s)he calls TreeWriter::BeginEvent and 
// TreeWriter::EndEvent for every event before and after filling of the branch 
// structures. Note that in addition to the standard tree one can create new
// tree(s) in the same file using the TreeWriter::AddBranchToTree member functions.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------
#ifndef MITANA_DATAUTIL_TREEWRITER_H
#define MITANA_DATAUTIL_TREEWRITER_H

#include <string>
#include <TNamed.h>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>

namespace mithep 
{
  using std::string;

  class MyTree : public TTree 
  {
    public:
      MyTree(const char* name, const char* title, Int_t splitlevel = 99) :
	TTree(name,title, splitlevel), fAutoFill(true) {}
	Bool_t GetAutoFill() const   { return fAutoFill; }
	void   SetAutoFill(Bool_t b) { fAutoFill = b; }

    protected:
      Bool_t fAutoFill; //!=true then fill automatically in TreeWriter (def=1)
  };
  
  class TreeWriter : public TNamed 
  {
    public:
      TreeWriter(const char *tname="MitTree", Bool_t doreset = kFALSE);
      ~TreeWriter();

      void                 AddBranch(const char *name, const char *cname, 
                                     void *obj,  Int_t bsize, Int_t level);
      void                 AddBranch(const string &name, const string &cname, 
                                     void *obj,  Int_t bsize, Int_t level)
                             { AddBranch(name.c_str(),cname.c_str(),obj,bsize,level); }
      void                 AddBranch(const char *name, void *obj, Int_t bsize, Int_t level);
      void                 AddBranch(const string &name, void *obj, Int_t bsize, Int_t level)
                             { AddBranch(name.c_str(),obj,bsize,level); }
      void                 AddBranch(const char *name, const char *cname, 
                                     void *obj, Int_t bsize);
      void                 AddBranch(const string &name, const string &cname, 
                                     void *obj, Int_t bsize)
                             { AddBranch(name.c_str(),cname.c_str(),obj,bsize); }
      void                 AddBranch(const char *name, void *obj, Int_t bsize);
      void                 AddBranch(const string &name, void *obj, Int_t bsize)
                             { AddBranch(name.c_str(),obj, bsize); }
      void                 AddBranch(const char *name, const char *cname, void *obj);
      void                 AddBranch(const string &name, const string &cname, void *obj)
                             { AddBranch(name.c_str(),cname.c_str(),obj); }
      void                 AddBranch(const char *name, void *obj);
      void                 AddBranch(const string &name, void *obj) 
                             { AddBranch(name.c_str(),obj); }
      void                 AddBranchToTree(const char *tname, const char *name, const char *cname, 
                                           void *obj,  Int_t bsize, Int_t level);
      void                 AddBranchToTree(const string &tn, const string &n, const string &cn, 
                                           void *obj,  Int_t bsize, Int_t level)
                             { AddBranchToTree(tn.c_str(),n.c_str(),cn.c_str(),obj,bsize,level); }
      void                 AddBranchToTree(const char *tname, const char *name, void *obj,  
                                           Int_t bsize, Int_t level);
      void                 AddBranchToTree(const string &tn, const string &n, void *obj,  
                                           Int_t bsize, Int_t level)
                             { AddBranchToTree(tn.c_str(),n.c_str(),obj,bsize,level); }
      void                 AddBranchToTree(const char *tname, const char *name, const char *cname, 
                                           void *obj, Int_t bsize);
      void                 AddBranchToTree(const string &tn, const string &n, const string &cn, 
                                           void *obj,  Int_t bsize)
                             { AddBranchToTree(tn.c_str(),n.c_str(),cn.c_str(),obj,bsize); }
      void                 AddBranchToTree(const char *tname, const char *name, void *obj, 
                                           Int_t bsize);
      void                 AddBranchToTree(const string &tn, const string &n, void *obj,
                                           Int_t bsize)
                             { AddBranchToTree(tn.c_str(),n.c_str(),obj,bsize); }
      void                 AddBranchToTree(const char *tname, const char *name, const char *cname, 
                                           void *obj);
      void                 AddBranchToTree(const string &tn, const string &n, const string &cn, 
                                           void *obj)
                             { AddBranchToTree(tn.c_str(),n.c_str(),cn.c_str(),obj); }
      void                 AddBranchToTree(const char *tname, const char *name, void *obj);
      void                 AddBranchToTree(const string &tn, const string &n, void *obj)
                             { AddBranchToTree(tn.c_str(),n.c_str(),obj); }
      void                 AddTree(const char *tname);
      void                 AddTree(const string &tname)       { AddTree(tname.c_str()); }
      Bool_t               BeginEvent(Bool_t doreset=kFALSE);
      void                 DoBranchRef(const char *tn);
      Bool_t               EndEvent(Bool_t doreset=kFALSE);
      const char          *GetBaseURL()                 const
                             { return fBaseURL.IsNull()?".":fBaseURL.Data(); }  
      Int_t                GetCompressLevel()           const { return fCompressLevel;  }
      Int_t                GetDefaultBrSize()           const { return fDefBrSize;      }
      Int_t                GetDefaultSL()               const { return fDefSL;          }
      Bool_t               GetDoObjNumReset()           const { return fDoObjNumReset;  }
      Bool_t               GetDoBranchRef()             const { return fDoBranchRef;    }
      Long64_t             GetEntries(const char *tn=0) const;
      Long64_t             GetFileSize()                const 
                             { return fFile!=0?fFile->GetEND():0; }
      const TFile         *GetFile()                    const { return fFile;           }
      const char          *GetFileName()                const {
	                     return Form("%s_%03d.root",GetPrefix(),GetFileNumber());   }
      UShort_t             GetFileNumber()              const { return fFileNumber;     }
      const char          *GetFullName()                const {
	                     return Form("%s/%s",GetBaseURL(),GetFileName());           }
      const char          *GetPrefix()                  const { return fPrefix;         }  
      const TTree         *GetTree(const char *tn=0)    const;
      TTree               *GetTree(const char *tn=0);
      const TTree         *GetTree(const string &tn)    const { return GetTree(tn.c_str()); }
      TTree               *GetTree(const string &tn)          { return GetTree(tn.c_str()); }
      void                 Print(Option_t *option="")   const;
      void                 SetAutoFill(const char *tn, Bool_t b);
      void                 SetAutoFill(const string &tn, Bool_t b)
                             { SetAutoFill(tn.c_str(), b); }
      void                 SetBaseURL(const char *b)          { fBaseURL = b;         }
      void                 SetBaseURL(const string &b)        { fBaseURL = b.c_str(); }
      void                 SetCompressLevel(Int_t l)          { fCompressLevel = l;   }
      void                 SetDefaultBrSize(Int_t s)          { fDefBrSize=s;         }
      void                 SetDefaultSL(Int_t s)              { fDefSL=s;             }
      void                 SetDoObjNumReset(Bool_t b)         { fDoObjNumReset = b;   }
      void                 SetDoBranchRef(Bool_t b)           { fDoBranchRef = b;     }
      void                 SetMaxSize(Long64_t s);
      void                 SetPrefix(const char *p)           { fPrefix = p;          }
      void                 SetPrefix(const string &p)         { fPrefix = p.c_str();  }
      void                 StoreObject(const TObject *obj);
      void                 Terminate();

    protected:
      TString              fBaseURL;            //base url for tree storage
      TString              fPrefix;             //prefix of file name 
      UShort_t             fFileNumber;         //current sequence number
      Int_t                fCompressLevel;      //compression level used for TFile
      Int_t                fDefBrSize;          //default buffer size for branches
      Int_t                fDefSL;              //default split level for branches
      Long64_t             fMaxSize;            //maximum file size for a file [Bytes]
      const Long64_t       fkMinFreeSpace;      //minimum free space required for closing file
      const Long64_t       fkMinAvgSize;        //minimum average entry size 
      Long64_t             fEvtObjNum;          //event object number offset (for TRef)
      Bool_t               fIsInit;             //true if OpenFile() was called
      Bool_t               fDoObjNumReset;      //true if obj. number resets automatically (def=0)
      Bool_t               fDoBranchRef;        //true if BranchRef is called automatically (def=0)
      TFile               *fFile;               //file being written
      TObjArray            fTrees;              //array of tree(s) being filled

      mithep::MyTree      *AddOrGetMyTree(const char *tn);
      mithep::MyTree      *GetMyTree(const char *tn);
      Bool_t               IsInit()                     const { return fIsInit; }
      Bool_t               IsFull()                     const;
      void                 OpenFile();
      void                 CloseFile();

    private:
      const char          *CName(void *obj)             const; 

    ClassDef(TreeWriter, 0) // Tree writer class
  };
}
#endif
