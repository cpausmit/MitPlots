#ifndef MITANA_UTILS_CONVERTSTREAMER_H
#define MITANA_UTILS_CONVERTSTREAMER_H

#include "RtypesCore.h"
#include "TString.h"

#include <vector>

class TBuffer;
class TClass;
class TStreamerInfo;

namespace mithep {

  Version_t CheckStreamerVersion(TBuffer&, TClass const*, Version_t);
  void ReplaceStreamerElement(TClass const*, TStreamerInfo*, char const*);
  void ConvertStreamer(TClass*, Version_t, void*, std::vector<TString> const&);
  void ConvertStreamer(TClass*, Version_t, void*, char const*);

}

#endif
