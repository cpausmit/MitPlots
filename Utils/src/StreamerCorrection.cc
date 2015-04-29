#include "MitAna/Utils/interface/StreamerCorrection.h"

#include "TClass.h"
#include "TStreamerInfo.h"
#include "TStreamerElement.h"
#include "TFile.h"
#include "TList.h"
#include "TObjArray.h"
#include "TPRegexp.h"

#include <cstring>
#include <stdexcept>

namespace mithep {

  void
  StreamerCorrection::ReplaceStreamerElement(TStreamerInfo* _onfileInfo, TStreamerInfo* _inmemoryInfo, char const* _elemName)
  {
    TObjArrayIter inmItr(_inmemoryInfo->GetElements());

    TStreamerElement* inmemoryElem(0);
    while ((inmemoryElem = static_cast<TStreamerElement*>(inmItr()))) {
      if(std::strcmp(inmemoryElem->GetName(), _elemName) == 0)
        break;
    }

    if (!inmemoryElem)
      throw std::logic_error(TString::Format("In-memory class %s has no member named %s", _inmemoryInfo->GetName(), _elemName).Data());

    TObjArrayIter onfItr(_onfileInfo->GetElements());

    TStreamerElement* onfileElem(0);
    while ((onfileElem = static_cast<TStreamerElement*>(onfItr()))) {
      if(std::strcmp(onfileElem->GetName(), _elemName) == 0)
        break;
    }

    if (!onfileElem)
      throw std::logic_error(TString::Format("On-file class %s has no member named %s", _onfileInfo->GetName(), _elemName).Data());

    onfileElem->SetTypeName(inmemoryElem->GetTypeName());
    onfileElem->SetNewType(inmemoryElem->GetNewType());
    onfileElem->SetOffset(inmemoryElem->GetOffset());
    onfileElem->Init();
  }

  void
  StreamerCorrection::CorrectStreamerInfo(TFile* _firstFile)
  {
    // Subroutine to be called immediately after opening a ROOT 5 Bambu file
    // Since each collection is written as a TClonesArray, Streamer functions
    // of the individual classes (where ConvertStreamer functions are called)
    // are skipped.

    TList* infoList(_firstFile->GetStreamerInfoList());

    for (int iI(0); iI != infoList->GetEntries(); ++iI) {
      TObject* obj(infoList->At(iI));
      if (!obj || obj->IsA() != TStreamerInfo::Class())
        continue;

      Version_t onfileVersion(static_cast<TStreamerInfo*>(obj)->GetClassVersion());

      TString className(obj->GetName());
      TClass* cl(TClass::GetClass(className));

      // Info obtained from TFile::GetStreamerInfoList() is simply read off the file
      // The one that is actually used to read the buffers should be taken from TClass.
      TStreamerInfo* onfileInfo(static_cast<TStreamerInfo*>(cl->GetStreamerInfos()->UncheckedAt(onfileVersion)));

      // If the current in-memory version and on-file version coincides, info is NULL (don't ask me why)
      if (!onfileInfo) continue;

      TStreamerInfo* inmemoryInfo(static_cast<TStreamerInfo*>(cl->GetStreamerInfo()));

      TPRegexp re("^" + className + "::(Ref|RefArray|FastArray)<[^>]+>$");

      TObjArray* elements(onfileInfo->GetElements());

      for (int iE(0); iE != elements->GetEntries(); ++iE) {
        TStreamerElement* elem(static_cast<TStreamerElement*>(elements->UncheckedAt(iE)));
        if (re.MatchB(elem->GetTypeName()))
          ReplaceStreamerElement(onfileInfo, inmemoryInfo, elem->GetName());
      }
    }

    delete infoList;
  }

}
