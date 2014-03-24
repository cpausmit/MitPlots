//--------------------------------------------------------------------------------------------------
// Cacher
//
// Class implementing a utility to keep track of the files needed by the analysis and caching them
// in advance and in parallel using SmartCache infrastructure or the AAA system.
//
// WARNING - bambu supports reading several files in parallel which we do not support here. We will
//           pretend that there is only one filelist. In principle this can be added.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------
#ifndef MITANA_DATAUTIL_CACHER_H
#define MITANA_DATAUTIL_CACHER_H

#include <vector>
#include <TList.h>

namespace mithep 
{
  class Cacher
  {
  public:
    Cacher(const TList *list);
    ~Cacher() {}
    
    Bool_t               InitialCaching();
    Bool_t               NextCaching();
    Bool_t               SubmitSmartCacheRequest(const char* file);
    Bool_t               Exists(const char* file);
    
  protected:
    
  private:
    const TList         *fInputList;          //in bambu several input files can be handled in
                                              //parallel we do not (yet) implement this here
    Int_t                fCurrentFileIdx;     //index of currently processing file
    Int_t                fCachedFileIdx;      //index of last cached file
    Int_t                fNFilesAhead;        //number of files to cache ahead of running job
    std::vector<int>     fCacheStatus;        //0-nothing, 1-submitted, 2-complete

  ClassDef(Cacher, 0) // Cacher class
  };
}
#endif
