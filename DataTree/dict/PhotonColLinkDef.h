#ifndef MITANA_DATATREE_PHOTONCOLLINKDEF_H
#define MITANA_DATATREE_PHOTONCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PhotonCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ PhotonCol
#   define _R__JOIN3_(F,X,Y) _NAME3_(F,X,Y)
#   undef _R__UNIQUE_
#   define _R__UNIQUE_(X) _R__JOIN3_( _R__UNIQUEIDENTIFIER_,X,__LINE__)
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma read \
  sourceClass="mithep::Photon" \
  version="[-21]" \
  source="Double32_t fCoviEtaiEta" \
  targetClass="mithep::Photon" \
  target="fCoviEtaiEta5x5" \
  code="{ fCoviEtaiEta5x5 = onfile.fCoviEtaiEta; }" \

#pragma link C++ class mithep::Photon+;
#pragma link C++ class mithep::Collection<mithep::Photon>+;
#pragma link C++ class mithep::Array<mithep::Photon>+;
#pragma link C++ class mithep::ObjArray<mithep::Photon>+;
#pragma link C++ class mithep::Ref<mithep::Photon>+;
#pragma link C++ typedef mithep::PhotonCol;
#pragma link C++ typedef mithep::PhotonArr;
#pragma link C++ typedef mithep::PhotonOArr;
#endif
