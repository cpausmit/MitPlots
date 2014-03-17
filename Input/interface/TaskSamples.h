//--------------------------------------------------------------------------------------------------
// $Id: TaskSamples.h,v 1.2 2011/01/25 14:24:52 fabstoec Exp $
//
// TaskSamples
//
// This class implements TaskSamples which fundamentally is a collection of samples used in a given
// analysis task. The data sample is not part of the list but is stored separately.
//
// This class manages the data and list of Monte Carlo samples for plotting etc.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------
#ifndef MITPLOTS_INPUT_TASKSAMPLES_H
#define MITPLOTS_INPUT_TASKSAMPLES_H

#include <vector>
#include <TString.h>
#include "MitPlots/Input/interface/Sample.h"

namespace mithep
{
  class TaskSamples
  {
  public:
    TaskSamples(const char* name, const char* dir);
    ~TaskSamples() { }

    const TString          *Name      ()            const { return &fName; }
    const TString          *NameTxt   ()            const { return &fNameTxt; }
    void                    SetNameTxt(const char* n)     { fNameTxt = TString(n); }
    const TString          *Dir       ()            const { return &fDir; }
    void                    Show      ()            const; // show list of task samples
    UInt_t                  NSamples  ()            const { return fNMcSamples; }
    UInt_t                  NDataSamples()          const { return fNDataSamples; }
    const Sample           *GetSample(UInt_t i)     const; // return 'i'th Monte Carlo sample
    const Sample           *GetDataSample(UInt_t i) const; // return 'i'th data sample

    void                    ReadFile     (const char* dir);

  private:
    Sample                 *AddDataSample(const char* name, const char* skimName, const char* file);
    Sample                 *AddSample    (const char* name, const char* skimName, const char* file,
                                          double xsec, double scale);

    TString                 fName;         // location of production
    TString                 fNameTxt;      // location of configuration (usually same as prod.)
    TString                 fDir;          // directory with sample files (sample can overwrite)

    UInt_t                  fNMcSamples;   // number of MC samples
    UInt_t                  fNDataSamples; // number of data samples
    std::vector<Sample>     fMcSamples;    // list of files contained in the fileset
    std::vector<Sample>     fDataSamples;  // data sample (not part of the list

    ClassDef(TaskSamples, 0) // TaskSamples manages a list of samples used in an analysis task
  };
}
#endif
