// $Id: $

#include <TROOT.h>
#include <TSystem.h>
#include "MitAna/Catalog/interface/BaseMetaData.h"
#include "MitAna/Catalog/interface/Dataset.h"

using namespace mithep;

//--------------------------------------------------------------------------------------------------
BaseMetaData::BaseMetaData() :
  fNEvents           (0),
  fNLumiSecs         (0),
  fMinRun            (999999999),
  fMinLumiSecInMinRun(0),
  fMaxRun            (0),
  fMaxLumiSecInMaxRun(0)
{
  // Constructor
}

BaseMetaData::BaseMetaData(UInt_t nEvts, UInt_t nLs,
                           UInt_t nMinR, UInt_t nMinLsMinR, UInt_t nMaxR, UInt_t nMaxLsMaxR) :
  fNEvents           (nEvts),
  fNLumiSecs         (nLs),
  fMinRun            (nMinR),
  fMinLumiSecInMinRun(nMinLsMinR),
  fMaxRun            (nMaxR),
  fMaxLumiSecInMaxRun(nMaxLsMaxR)
{
  // Constructor
}


//--------------------------------------------------------------------------------------------------
BaseMetaData::BaseMetaData(BaseMetaData *b)
{
  fNEvents            = b->NEvents           ();
  fNLumiSecs          = b->NLumiSecs         ();
  fMinRun             = b->MinRun            ();
  fMinLumiSecInMinRun = b->MinLumiSecInMinRun();
  fMaxRun             = b->MaxRun            ();
  fMaxLumiSecInMaxRun = b->MaxLumiSecInMaxRun();
}

//--------------------------------------------------------------------------------------------------
void BaseMetaData::AddRun(UInt_t nR, UInt_t nLs)
{
  // account for the minimum run number and reset minimum luminosity section within
  if (fMinRun > nR) {
    fMinRun             = nR;
    fMinLumiSecInMinRun = nLs;
  }
  // account for the maximum run number and reset maximum luminosity section within
  if (fMaxRun < nR) {
    fMaxRun             = nR;
    fMaxLumiSecInMaxRun = nLs;
  }
}

//--------------------------------------------------------------------------------------------------
void BaseMetaData::AddLumiSec(UInt_t nR, UInt_t nLs)
{
  fNLumiSecs++;
  // account for the maximum lumi section number in the maximum run
  if (fMaxRun == nR) {
    if (fMaxLumiSecInMaxRun < nLs)
      fMaxLumiSecInMaxRun = nLs;
  }
  // account for the minimum lumi section number in the minimum run
  if (fMinRun == nR) {
    if (fMinLumiSecInMinRun > nLs)
      fMinLumiSecInMinRun = nLs;
  }
}

//--------------------------------------------------------------------------------------------------
void BaseMetaData::Add(BaseMetaData *b)
{
  // Add simple counts (nRun count is incorrect... we are counting the times BeginRun is hit...)
  fNEvents   += b->NEvents  ();
  fNLumiSecs += b->NLumiSecs();
  // Determine the lowest and highest data location in the new data
  if (b->MinRun() < fMinRun ||
      (b->MinRun() == fMinRun && b->MinLumiSecInMinRun() < fMinLumiSecInMinRun)) {
    fMinRun             = b->MinRun            ();
    fMinLumiSecInMinRun = b->MinLumiSecInMinRun();
  }
  if (b->MaxRun() > fMaxRun ||
      (b->MaxRun() == fMaxRun && b->MaxLumiSecInMaxRun() > fMaxLumiSecInMaxRun)) {
    fMaxRun             = b->MaxRun            ();
    fMaxLumiSecInMaxRun = b->MaxLumiSecInMaxRun();
  }
}

//--------------------------------------------------------------------------------------------------
void BaseMetaData::Print() const
{
  printf("%9d %9d %9d %6d %9d %6d\n",
	 fNLumiSecs         ,
	 fNEvents           ,
	 fMinRun            ,
	 fMinLumiSecInMinRun,
	 fMaxRun            ,
	 fMaxLumiSecInMaxRun );
}
