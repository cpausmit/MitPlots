#include "MitAna/Utils/interface/ConvertStreamer.h"

#include "TBuffer.h"
#include "TClass.h"
#include "TStreamerInfo.h"
#include "TStreamerElement.h"
#include "TInterpreter.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace mithep {

  Version_t
  CheckStreamerVersion(TBuffer& _buf, TClass const* _thisClass, Version_t _rt6Version)
  {
    unsigned start;
    Version_t version(_buf.ReadVersionNoCheckSum(&start));
    _buf.SetBufferOffset(start);

    if(version >= _rt6Version) return 0;

    TStreamerInfo* info(static_cast<TStreamerInfo*>(_thisClass->GetStreamerInfos()->UncheckedAt(version)));

    if(info->IsCompiled()) return 0;

    return version;
  }

  void
  ReplaceStreamerElement(TClass const* _class, TStreamerInfo* _onfileInfo, char const* _elemName)
  {
    TStreamerInfo* currentInfo(static_cast<TStreamerInfo*>(_class->GetStreamerInfo()));
    TObjArrayIter curItr(currentInfo->GetElements());

    TStreamerElement* currentElem(0);
    while((currentElem = static_cast<TStreamerElement*>(curItr())))
      if(std::strcmp(currentElem->GetName(), _elemName) == 0) break;

    if(!currentElem)
      throw std::logic_error(TString::Format("Current class %s has no member named %s", _class->GetName(), _elemName).Data());

    TObjArrayIter onfItr(_onfileInfo->GetElements());

    TStreamerElement* onfileElem(0);
    while((onfileElem = static_cast<TStreamerElement*>(onfItr())))
      if(std::strcmp(onfileElem->GetName(), _elemName) == 0) break;

    if(!onfileElem)
      throw std::logic_error(TString::Format("On-file class %s has no member named %s", _class->GetName(), _elemName).Data());

    onfileElem->SetTypeName(currentElem->GetTypeName());
    onfileElem->SetNewType(currentElem->GetNewType());
    onfileElem->SetOffset(currentElem->GetOffset());
    onfileElem->Init();
  }

  void
  ConvertStreamer(TClass* _thisClass, Version_t _onfileVersion, void* _this, std::vector<TString> const& _elemNames)
  {
    TStreamerInfo* info(static_cast<TStreamerInfo*>(_thisClass->GetStreamerInfos()->UncheckedAt(_onfileVersion)));

    R__LOCKGUARD(gInterpreterMutex);

    if(info->IsCompiled()) return;

    for(unsigned iE(0); iE != _elemNames.size(); ++iE)
      ReplaceStreamerElement(_thisClass, info, _elemNames[iE]);

    _thisClass->BuildRealData(_this);
    info->BuildOld();
  }

  void
  ConvertStreamer(TClass* _thisClass, Version_t _onfileVersion, void* _this, char const* _elemName)
  {
    ConvertStreamer(_thisClass, _onfileVersion, _this, std::vector<TString>{_elemName});
  }

}
