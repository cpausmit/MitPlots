//--------------------------------------------------------------------------------------------------
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
      const char               *GetAllEvtTreeName()           const { return fAllEvtTreeName;     }
      const char               *GetAllEvtHdrBrn()             const { return fAllEvtHdrBrn;       }
      const char               *GetAnaOutputName()            const { return fAnaOutput;          }
      const char               *GetEvtHdrName()               const { return fEvtHdrName;         }
      const char               *GetHLTObjsName()              const { return fHLTObjsName;        }
      const char               *GetHLTTreeName()              const { return fHLTTreeName;        }
      const char               *GetLATreeName()               const { return fLATreeName;         }
      const char               *GetLAHdrName()                const { return fLAHdrName;          }
      const char               *GetRunTreeName()              const { return fRunTreeName;        }
      const char               *GetRunInfoName()              const { return fRunInfoName;        }
      const TList              *GetOutput()                   const { return fOutput;             }
      const TList              *GetSuperMods()                const { return fSuperMods;          }
      Bool_t                    GetUseProof()                 const { return fUseProof;           }
      Bool_t                    Init();
      Bool_t                    IsInit()                      const { return fState==kInit;       }
      Bool_t                    IsRun()                       const { return fState==kRun;        }
      Bool_t                    IsTerminated()                const { return fState==kTerminate;  }
      void                      Run();
      Bool_t                    Run(Bool_t browse);
      void                      SetAllEvtHdrBrn(const char *n)      { fAllEvtHdrBrn   = n;        }
      void                      SetAllEvtTreeName(const char *n)    { fAllEvtTreeName = n;        }
      void                      SetCacheSize(Int_t cache)           { fCacheSize      = cache;    }
      void                      SetCompressionLevel(Int_t level)    { fCompLevel      = level;    }
      void                      SetConfigName(const char* name)     { fConfig         = name;     }
      void                      SetDoObjTabClean(Bool_t b)          { fDoObjTabClean  = b;        }
      void                      SetDoParallel(Bool_t b)             { fParallel       = b;        }
      void                      SetDoProxy(Bool_t b)                { fDoProxy        = b;        }
      void                      SetEvtHdrName(const char *n)        { fEvtHdrName     = n;        }
      void                      SetHLTObjsName(const char *n)       { fHLTObjsName    = n;        }
      void                      SetHLTTreeName(const char *n)       { fHLTTreeName    = n;        }
      void                      SetKeepHierarchy(Bool_t b)          { fHierarchy      = b;        }
      void                      SetLAHdrName(const char *n)         { fLAHdrName      = n;        }
      void                      SetLATreeName(const char *n)        { fLATreeName     = n;        }
      void                      SetMasterName(const char* name)     { fMaster         = name;     }
      void                      SetOutputName(const char *name)     { fAnaOutput      = name;     }
      void                      SetPrintScale(UInt_t n)             { fPrintScale     = n;        }
      void                      SetProcessNEvents(Long64_t n)       { fDoNEvents      = n;        }
      void                      SetRunInfoName(const char *n)       { fRunInfoName    = n;        }
      void                      SetRunTreeName(const char *n)       { fRunTreeName    = n;        }
      void                      SetSkipFirstNEvents(Long64_t n)     { fSkipNEvents    = n;        }
      void                      SetSuperModule(TAModule *mod);
      void                      SetTreeName(const char *name)       { fTreeName       = name;     }
      void                      SetUseHLT(Bool_t hlt)               { fUseHLT         = hlt;      }
      void                      SetUseProof(Bool_t up)              { fUseProof       = up;       }
      void                      SetUseCacher(Int_t i)               { fUseCacher      = i;        }
      void                      Terminate();

      void                      PrintModuleTree() const; // for debugging

    protected:
      void                      AddFile(const char *pname, Int_t eventlist);
      void                      AddFile(const TObject *oname, Int_t eventlist);
      void                      AddList(TList *list, Int_t eventlist);
      void                      FileInputFromEnv();
      Bool_t                    IsValidName(const char */*name*/) { return kTRUE; }
      Bool_t                    InitProof();
      Bool_t                    UploadPackages(TList *packages);

      enum EState {  
        kPristine,  //after constructor
        kInit,      //after init
        kRun,       //after run
        kTerminate  //after terminate
      };

      Bool_t                    fUseProof;        //=true if PROOF is to be used (def=0)
      Bool_t                    fUseCacher;       //=1 use file caching (def=0)
      Bool_t                    fUseHLT;          //=true if HLT module is to be used (def=1)
      Bool_t                    fHierarchy;       //=true if module hierachy to be stored (def=1)
      Bool_t                    fDoProxy;         //=true if TRef branch autoload is used (def=0)
      Bool_t                    fDoObjTabClean;   //=true if object table cleaning is used (def=1)
      Bool_t                    fParallel;        //=true if parellel tree unzipping is used (def=0)
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
      TString                   fAnaOutput;       //path name of output file
      TString                   fMaster;          //hostname of PROOF master
      TString                   fConfig;          //config file name for PROOF
      Int_t                     fCompLevel;       //compression level for output file (def=7)
      TProof                   *fProof;           //pointer to the PROOF session
      Long64_t                  fDoNEvents;       //events to process (def=TChain::kBigNumber)
      Long64_t                  fSkipNEvents;     //number of events to skip from beginning (def=0)
      UInt_t                    fPrintScale;      //scale for evt number/timings printouts (def=100)
      Int_t                     fCacheSize;       //size of read cache for events tree
      TString                   fTreeName;        //name of trees or friend trees
      TString                   fEvtHdrName;      //name of event header branch
      TString                   fRunTreeName;     //name of run info tree
      TString                   fRunInfoName;     //name of run info branch
      TString                   fAllEvtHdrBrn;    //name of all-event header branch
      TString                   fLATreeName;      //name of look-ahead tree
      TString                   fLAHdrName;       //name of look-ahead event header branch
      TString                   fHLTTreeName;     //name of HLT tree
      TString                   fAllEvtTreeName;  //name of all-event tree
      TString                   fHLTObjsName;     //trigger objects branch name

    ClassDef(Analysis, 0) // Top-level analysis class 
  };
}
#endif
