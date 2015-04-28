#ifndef MITANA_UTILS_CONVERTSTREAMER_H
#define MITANA_UTILS_CONVERTSTREAMER_H

#include "RtypesCore.h"
#include "TString.h"

#include <vector>

class TBuffer;
class TClass;
class TStreamerInfo;
class TFile;

namespace mithep {

  class StreamerConverter {
  public:
    static Version_t CheckStreamerVersion(TBuffer&, TClass const*, Version_t);
    static void ReplaceStreamerElement(TClass const*, TStreamerInfo*, char const*);
    static void ConvertStreamer(TClass*, Version_t, void*, std::vector<TString> const&);
    static void ConvertStreamer(TClass*, Version_t, void*, char const*);
    static void CorrectStreamerInfo(TFile*);
  };

}

#endif
