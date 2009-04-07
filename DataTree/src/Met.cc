// $Id: Met.cc,v 1.1 2008/07/07 16:02:25 loizides Exp $

#include "MitAna/DataTree/interface/Met.h"
#include <TFile.h>
#include <TStreamerInfo.h>

ClassImp(mithep::Met)

//--------------------------------------------------------------------------------------------------
Bool_t mithep::Met::HasCorrections() const
{
  // Return kTRUE if class version is larger than 1.

  Bool_t ret = (IsA()->GetBaseClass("mithep::Met")->GetClassVersion()>1);

  if (!gFile)
    return ret;
  
  TStreamerInfo *si = 
    dynamic_cast<TStreamerInfo*>(gFile->GetStreamerInfoList()->FindObject("mithep::Met"));
  if (!si)
    return ret;

  ret = (si->GetClassVersion()>1);
  return ret;
}
