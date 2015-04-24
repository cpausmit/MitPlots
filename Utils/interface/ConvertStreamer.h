#ifndef MITANA_UTILS_CONVERTSTREAMER_H
#define MITANA_UTILS_CONVERTSTREAMER_H

class TClass;
class TStreamerInfo;

namespace mithep {

  bool ConvertStreamer(TClass const*, TStreamerInfo*, char const*);

}

#endif
