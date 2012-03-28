//--------------------------------------------------------------------------------------------------
// $Id: BaseMetaData.h,v 1.4 2009/03/12 18:36:06 loizides Exp $
//
// BaseMetaData
//
// This class implements a minimal description of a bunch of data. In fact this is a just the
// MetaData for any type of collection of data (e.g file, filesets, datasets) and some convenient
// tools to juggle the metadata.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_CATALOG_BASEMETADATA_H
#define MITANA_CATALOG_BASEMETADATA_H

#include <Rtypes.h>

namespace mithep 
{
  class BaseMetaData
  {
    public:
      BaseMetaData();
      BaseMetaData(UInt_t nAllEvts, UInt_t nEvts,      UInt_t nLs,
		   UInt_t nMinR,    UInt_t nMinLsMinR, UInt_t nMaxR, UInt_t nMaxLsMaxR);
      virtual ~BaseMetaData() {}

      void                     Add               (const BaseMetaData *b);
      void                     AddAllEvent       () { fNAllEvents++; }
      void                     AddEvent          () { fNEvents++; }
      void                     AddLumiSec        (UInt_t nR, UInt_t nLs);
      void                     AddRun            (UInt_t nR, UInt_t nLs);
      UInt_t                   NAllEvents        () const { return fNAllEvents        ; }
      UInt_t                   NEvents           () const { return fNEvents           ; }
      UInt_t                   NLumiSecs         () const { return fNLumiSecs         ; }
      UInt_t                   MaxRun            () const { return fMaxRun            ; }  
      UInt_t                   MaxLumiSecInMaxRun() const { return fMaxLumiSecInMaxRun; }  
      UInt_t                   MinRun            () const { return fMinRun            ; }  
      UInt_t                   MinLumiSecInMinRun() const { return fMinLumiSecInMinRun; }  
      virtual void             Print             () const;

    protected:
      UInt_t                   fNAllEvents;          // number of all events analyzed
      UInt_t                   fNEvents;             // number of events analyzed
      UInt_t                   fNLumiSecs;           // number of lumi sections analyzed
      UInt_t                   fMinRun;              // smallest run number encountered
      UInt_t                   fMinLumiSecInMinRun;  // smallest lumi section in that run
      UInt_t                   fMaxRun;              // largest run nnumber encountered
      UInt_t                   fMaxLumiSecInMaxRun;  // largest lumi section in that run

    ClassDef(BaseMetaData, 1) // Base class for collections of data
  };
}
#endif
