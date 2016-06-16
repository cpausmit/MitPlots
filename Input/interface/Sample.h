//--------------------------------------------------------------------------------------------------
// Sample
//
// This class implements Sample which defines all relevant properties of a data sample needed to
// make plots.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITPLOTS_INPUT_SAMPLE_H
#define MITPLOTS_INPUT_SAMPLE_H

#include <TString.h>

namespace mithep 
{
  class Sample
  {
  public:
    Sample() {}
    Sample(const char* name,  const char* file, const char* dir,
	   const double xsec, const double scale);
    virtual ~Sample() {}
    
    const TString           *Name()                           const { return &fName; }
    const TString           *Legend()                         const { return &fLegend; }
    const TString           *File()                           const { return &fFile; }
    const TString           *Dir()                            const { return &fDir; }
    const double            *Xsec()                           const { return &fXsec; }
    const double            *Scale()                          const { return &fScale; }

    void                     SetLegend(const char* legend)          { fLegend = TString(legend); }

    void                     Show()                           const; // show sample properties

  private:
    TString                  fName;     // name of the sample
    TString                  fLegend;   // legend used for this sample
    TString                  fFile;     // file name of the histograms etc.
    TString                  fDir;      // directory with sample file

    double                   fXsec;     // cross section
    double                   fScale;    // k-factor to scale the MC cross section
    
    ClassDef(Sample, 0) // Sample describes all relevant aspects of a sample for plotting
  };
}
#endif
