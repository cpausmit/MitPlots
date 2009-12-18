// $Id: Met.cc,v 1.2 2009/04/07 14:59:08 loizides Exp $

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
  
  TList *list = gFile->GetStreamerInfoList();
  if (!list)
    return ret;

  const TStreamerInfo *si = 
    dynamic_cast<const TStreamerInfo*>(list->FindObject("mithep::Met"));

  if (!si) {
    delete list;
    return ret;
  }

  ret = (si->GetClassVersion()>1);
  delete list;
  return ret;
}
