#include "MitAna/Utils/interface/ConvertStreamer.h"

#include "TClass.h"
#include "TStreamerInfo.h"
#include "TStreamerElement.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace mithep {

  bool
  ConvertStreamer(TClass const* _class, TStreamerInfo* _onfileInfo, char const* _elemName)
  {
    TStreamerInfo* currentInfo(static_cast<TStreamerInfo*>(_class->GetStreamerInfo()));
    TObjArrayIter curItr(currentInfo->GetElements());

    TStreamerElement* currentElem(0);
    while(currentElem = static_cast<TStreamerElement*>(curItr()))
      if(std::strcmp(currentElem->GetName(), _elemName) == 0) break;

    if(!currentElem)
      throw std::logic_error(TString::Format("Current class %s has no member named %s", _class->GetName(), _elemName).Data());

    TObjArrayIter onfItr(_onfileInfo->GetElements());

    TStreamerElement* onfileElem(0);
    while(onfileElem = static_cast<TStreamerElement*>(onfItr()))
      if(std::strcmp(onfileElem->GetName(), _elemName) == 0) break;

    if(!onfileElem)
      throw std::logic_error(TString::Format("On-file class %s has no member named %s", _class->GetName(), _elemName).Data());

    onfileElem->SetTypeName(currentElem->GetTypeName());
    onfileElem->SetNewType(currentElem->GetNewType());
    onfileElem->SetOffset(currentElem->GetOffset());
    onfileElem->Init();

    return true;
  }

}
