// $Id: Analysis.h,v 1.4 2008/06/05 09:46:40 loizides Exp $

#ifndef DATAUTIL_ANALYSIS_H
#define DATAUTIL_ANALYSIS_H

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

//--------------------------------------------------------------------------------------------------
//
// Analysis
//
// This is the top-level analysis class used to hide the (little)
// differences between TAM standalone and TAM with PROOF.
// In addition it provides an almost transparent interface
// in the case you want to do mixing of different events.
// 
// The class can operate in following modes:
//  a) Add single files to be analyzed using Analysis::AddFile
//  b) Use a text file to point to files to be analyzed using Analysis::AddFiles
//  c) Add files using a catalogue (to be done)
//
// See $CMSSW_BASE/src/MitAna/macros/examples/runSimpleExample.C
// for an example of how to use this class.
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Analysis : public TObject 
  {
    public:
      Analysis(Bool_t useproof=kFALSE);
      ~Analysis();

      void                      AddLoader(TAMVirtualLoader *l);
      Bool_t                    AddFile(const char *pname);
      Bool_t                    AddFiles(const char *pname, Int_t nmax=-1);
      void                      AddPackage(const char* name);
      void                      AddPackages(TList *list);
      const char               *GetAnaOutputName()            const { return fAnaOutput;}
      const TList              *GetOutput()                   const { return fOutput; }
      Bool_t                    GetUseProof()                 const { return fUseProof; }
      Bool_t                    Init();
      Bool_t                    IsInit()                      const { return fState==kInit; }
      Bool_t                    IsRun()                       const { return fState==kRun; }
      Bool_t                    IsTerminated()                const { return fState==kTerminate; }
      void                      Run();
      Bool_t                    Run(Bool_t browse);
      void                      SetProcessNevents(Int_t n)          { fDoNEvents = n; }
      void                      SetCompressionLevel(Int_t level)    { fCompLevel = level; }
      void                      SetConfigName(const char* name)     { fConfig    = name; }
      void                      SetKeepHierachy(Bool_t b)           { fHierachy  = b; }
      void                      SetMasterName(const char* name)     { fMaster    = name; }
      void                      SetOutputName(const char *name)     { fAnaOutput = name; }
      void                      SetSuperModule(TAModule *mod)       { fSuperMod  = mod; }
      void                      SetTreeName(const char *name)       { fTreeName  = name; }
      void                      SetUseProof(Bool_t up)              { fUseProof  = up; }
      void                      Terminate();

    protected:
      enum EState {  kPristine,  //after constructor
                     kInit,      //after init
                     kRun,       //after run
                     kTerminate  //after terminate
                  };

      Bool_t                    fUseProof;        //=true if PROOF is to be used (def=0)
      Bool_t                    fHierachy;        //=true if module hierachy to be stored (def=1)
      EState                    fState;           //status of analysis
      Int_t                     fNFriends;        //number of friend trees
      TList                    *fList;            //list of lists of path names
      TList                    *fOutput;          //output as obtained from TAM (not owned)
      TList                    *fPackages;        //list of package names for PROOF upload
      TList                    *fLoaders;         //list of loaders
      TAModule                 *fSuperMod;        //top level TAM module (not owned)
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
      Int_t                     fDoNEvents;       //number of events to process (def=-1)

      void                      AddFile(const char *pname, Int_t eventlist);
      void                      AddFile(const TObject *oname, Int_t eventlist);
      void                      AddList(TList *list, Int_t eventlist);
      Bool_t                    IsValidName(const char */*name*/) { return kTRUE; }
      Bool_t                    InitProof();
      Bool_t                    UploadPackages(TList *packages);

      ClassDef(Analysis,0) // Top-level analysis class 
  };
}
#endif
