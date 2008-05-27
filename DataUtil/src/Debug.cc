// $Id: THIDebug.h 2637 2006-03-06 23:53:38Z loizides $

#include "MitAna/DataUtil/interface/Debug.h"

ClassImp(mithep::Debug)

mithep::Debug::EDebugMask gDebugMask  = mithep::Debug::kNone;
Int_t                     gDebugLevel = 0;
