//--------------------------------------------------------------------------------------------------
// StreamerCorrection
//
// Utility subroutines to be called before reading ROOT 5 Bambu files (tag < 040) from ROOT 6
// software. I could not find a way to make only the simple functions visible to CLING, hence the
// unfortunate implementation as a class with only static members.
//
// Authors: Y.Iiyama
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_UTILS_STREAMERCORRECTION_H
#define MITANA_UTILS_STREAMERCORRECTION_H

class TStreamerInfo;
class TFile;

namespace mithep {

  class StreamerCorrection {
  public:
    static void ReplaceStreamerElement(TStreamerInfo*, TStreamerInfo*, char const*);
    static void CorrectStreamerInfo(TFile*);
  };

}

#endif
