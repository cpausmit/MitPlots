//--------------------------------------------------------------------------------------------------
// $Id: Analysis.h,v 1.17 2008/12/11 15:29:09 loizides Exp $
//
// Analysis
//
// This is the top-level analysis class used to hide the (little) differences between TAM standalone
// and TAM with PROOF.  In addition it provides an almost transparent interface in the case you want
// to do mixing of different events.
// 
// The class can operate in following modes:
//  a) Add single files to be analyzed using Analysis::AddFile
//  b) Use a text file to point to files to be analyzed using Analysis::AddFiles
//  c) Add files using a catalog using Analysis::AddDataset
//  d) Use of environment variables (only will be attempted if none of a-c is provided)
//     MIT_CATALOG  (eg. export MIT_CATALOG=/home/mitprod/catalog)
//     MIT_BOOK     (eg. export MIT_BOOK=mit/filler/006)
//     MIT_DATASET  (eg. export MIT_DATASET=s8-ttbar-id9)
//     MIT_FILESETS (eg. export MIT_FILESETS=0000;0001;0002)
//   or   
//     MIT_FILES    (eg. export MIT_FILES=file1;file2;file3)
//
// See $CMSSW_BASE/src/MitAna/macros/examples/runSimpleExample.C
// for an example of how to use this class.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATAUTIL_ANALYSIS_H
#define MITANA_DATAUTIL_ANALYSIS_H

#include <TObject.h>
#include <TString.h>

class TList;
class TChain;
class TDSet;
class TString;
class TAModule;
class TAMSelector;
class TAMVirtualLoader;
class TObjArray;
class TProof;

namespace mithep 
{
  class Dataset;
  class Analysis : public TObject 
  {
    public:
      Analysis(Bool_t useproof=kFALSE);
      ~Analysis();

      Bool_t                    AddDataset(const Dataset *dataset);
      Bool_t                    AddFile(const char *pname);
      Bool_t                    AddFiles(const char *pname, Int_t nmax=-1);
      void                      AddLoader(TAMVirtualLoader *l);
      void                      AddPackage(const char *name);
      void                      AddPackages(TList *list);
      void                      AddSuperModule(TAModule *mod);
      const char               *GetAnaOutputName()            const { return fAnaOutput;          }
      const TList              *GetOutput()                   const { return fOutput;             }
      Bool_t                    GetUseProof()                 const { return fUseProof;           }
      Bool_t                    Init();
      Bool_t                    IsInit()                      const { return fState==kInit;       }
      Bool_t                    IsRun()                       const { return fState==kRun;        }
      Bool_t                    IsTerminated()                const { return fState==kTerminate;  }
      void                      Run();
      Bool_t                    Run(Bool_t browse);
      void                      SetProcessNEvents(Long64_t n)       { fDoNEvents  = n;            }
      void                      SetCompressionLevel(Int_t level)    { fCompLevel  = level;        }
      void                      SetConfigName(const char* name)     { fConfig     = name;         }
      void                      SetAutoBranchLoad(Bool_t b)         { fDoProxy    = b;            }
      void                      SetKeepHierarchy(Bool_t b)          { fHierarchy  = b;            }
      void                      SetMasterName(const char* name)     { fMaster     = name;         }
      void                      SetOutputName(const char *name)     { fAnaOutput  = name;         }
      void                      SetSuperModule(TAModule *mod);
      void                      SetTreeName(const char *name)       { fTreeName   = name;         }
      void                      SetUseHLT(Bool_t hlt)               { fUseHLT     = hlt;          }
      void                      SetUseProof(Bool_t up)              { fUseProof   = up;           }
      void                      Terminate();

    protected:
      void                      AddFile(const char *pname, Int_t eventlist);
      void                      AddFile(const TObject *oname, Int_t eventlist);
      void                      AddList(TList *list, Int_t eventlist);
      void                      FileInputFromEnv();
      Bool_t                    IsValidName(const char */*name*/) { return kTRUE; }
      Bool_t                    InitProof();
      Bool_t                    UploadPackages(TList *packages);

      enum EState {  kPristine,  //after constructor
                     kInit,      //after init
                     kRun,       //after run
                     kTerminate  //after terminate
                  };

      Bool_t                    fUseProof;        //=true if PROOF is to be used (def=0)
      Bool_t                    fUseHLT;          //=true if HLT module is to be used (def=1)
      Bool_t                    fHierarchy;       //=true if module hierachy to be stored (def=1)
      Bool_t                    fDoProxy;         //=true if branch autoload is used (def=1)
      EState                    fState;           //status of analysis
      Int_t                     fNFriends;        //number of friend trees
      TList                    *fList;            //list of lists of path names
      TList                    *fOutput;          //output as obtained from TAM (not owned)
      TList                    *fPackages;        //list of package names for PROOF upload
      TList                    *fLoaders;         //list of loaders
      TList                    *fSuperMods;       //top level TAM module(s) (not owned)
      TAMSelector              *fSelector;        //selector for non-PROOF usage
      TChain                   *fChain;           //trees or friend trees for non-PROOF usage
      TDSet                    *fSet;             //set of trees or friend trees for PROOF usage
      TList                    *fDeleteList;      //list of objects to be deleted on Terminate()
      TString                   fTreeName;        //name of trees or friend trees
      TString                   fAnaOutput;       //path name of output file
      TString                   fMaster;          //hostname of PROOF master
      TString                   fConfig;          //config file name for PROOF
      Int_t                     fCompLevel;       //compression level for output file (def=2)
      TProof                   *fProof;           //pointer to the PROOF session
      Long64_t                  fDoNEvents;       //events to process (def=TChain::kBigNumber)

    ClassDef(Analysis, 0) // Top-level analysis class 
  };
}
#endif
