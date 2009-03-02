// $Id: Ref.cc,v 1.1 2009/02/17 14:57:29 bendavid Exp $

#include "MitAna/DataCont/interface/RefResolver.h"

#include <TObject.h>
#include <TRefTable.h>
#include <TProcessID.h>
#include <TROOT.h>
#include "MitAna/TAM/interface/TAMSelector.h"

ClassImp(mithep::RefResolver)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
TObject *RefResolver::GetObjectWithID(UInt_t uid, TProcessID *pid)
{
  // Return pointer to object with given uid/pid. 

  static TAMSelector *sel = 0;

#if 0
  if (!sel) {
    TObject *optr = gROOT->GetListOfSpecials()->FindObject("mithep::Selector");
    if (optr)
      sel = dynamic_cast<TAMSelector*>(optr);
  } else {
    if (!gROOT->GetListOfSpecials()->FindObject(sel))
      sel = 0;
  }

  if (sel)
    return sel->GetObjectWithID(uid,pid);
#endif
  // no explicit TAM proxy present, fall back to standard Root calls and check if
  // the reference can be found in the TRefTable
  TRefTable *table = TRefTable::GetRefTable();
  if (table) {
    table->SetUID(uid, pid);
    table->Notify();
  }

  return pid->GetObjectWithID(uid);
}
