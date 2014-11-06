// $Id: TaskSamples.cc,v 1.2 2011/01/25 14:24:52 fabstoec Exp $

#include <TSystem.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitPlots/Input/interface/TaskSamples.h"

ClassImp(mithep::TaskSamples)

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
TaskSamples::TaskSamples(const char *name, const char* dir) :
  fName        (name),
  fNameTxt     (name),
  fDir         (dir),
  fNMcSamples  (0),
  fNDataSamples(0)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
void TaskSamples::Show() const
{
  // Show present list of defined samples

  printf("\n ==== Analysis task overview -- %s ====\n\n",fName.Data());
  printf(" Histogram directory: %s\n\n",fDir.Data());
  printf(" Dataset name                   Skim   Legend               Histogram file");
  printf("                                                  Cross Section [pb]   Scale\n");
  printf(" ------------------------------------------------------------------------");
  printf("----------------------------------------------------------------------------\n");
  for (UInt_t i=0; i<fDataSamples.size(); i++)
    fDataSamples[i].Show();
  printf(" ------------------------------------------------------------------------");
  printf("----------------------------------------------------------------------------\n");
  for (UInt_t i=0; i<fMcSamples.size(); i++)
    fMcSamples[i].Show();
  
  return;
}

//--------------------------------------------------------------------------------------------------
const Sample *TaskSamples::GetSample(UInt_t iSample) const
{
  // Get sample corresponding to given sample number. Return NULL pointer if index out of range.

  if (iSample >= fNMcSamples)
    return 0;

  return &fMcSamples[iSample];
}

//--------------------------------------------------------------------------------------------------
const Sample *TaskSamples::GetDataSample(UInt_t iSample) const
{
  // Get data sample. Return NULL pointer if not available.

  if (iSample >= fNDataSamples)
    return 0;

  return &fDataSamples[iSample];
}

//--------------------------------------------------------------------------------------------------
Sample *TaskSamples::AddSample(const char* name,const char* skimName, const char* file,
			       double xsec, double scale)
{
  // Adding another sample (vector takes care of memory management)

  Sample* tmpSample = new Sample(name,skimName,file,fDir,xsec,scale);
  fMcSamples.push_back(*tmpSample);
  fNMcSamples++;
  // cleanup after yourself
  delete tmpSample;

  return &fMcSamples[fMcSamples.size()-1];
}

//--------------------------------------------------------------------------------------------------
Sample *TaskSamples::AddDataSample(const char* name, const char* skimName, const char* file)
{
  // Adding another the data sample (existing definition is overwritten)

  Sample* tmpSample = new Sample(name,skimName,file,fDir,-1.0,1.0);
  fDataSamples.push_back(*tmpSample);
  fNDataSamples++;
  // cleanup after yourself
  delete tmpSample;

  return &fDataSamples[fDataSamples.size()-1];
}

//--------------------------------------------------------------------------------------------------
void TaskSamples::ReadFile(const char* dir)
{
  // Reading the full task setup from a single file

  char    vers[1024], dset[1024], skim[1024], legend[1024], json[1024];
  float   xsec,scale,overlap;

  Long64_t size;
  Long_t   id, flags, modtime;

  // construct name of the config file
  TString txtFile = TString(dir)+TString("/")+fNameTxt+TString(".txt");
  printf("\n Initializing analysis task from  %s\n\n",txtFile.Data());

  // test whether file exists and say something if it does not 
  if (gSystem->GetPathInfo(txtFile.Data(),&id,&size,&flags,&modtime) != 0) {
    printf("\n TaskSamples::ReadFile() - ERROR - file does not exist. EXIT! %s\n\n",txtFile.Data());
    return;
  }

  // open file in a pipe (leaves options for filtering)
  FILE *f = gSystem->OpenPipe((TString("cat ")+txtFile+TString("| grep -v ^#")).Data(),"r");
  MDB(kGeneral,1) {
    printf("           Cross Section [pb]  Dataset name                              ");
    printf("Legend               Skim?  \n");
    printf(" ------------------------------------------------------------------------");
    printf("----------------------------\n");
  }
  while (fscanf(f,"%s %s %s %s %f %f %f %s",vers,dset,skim,legend,&xsec,&scale,&overlap,json)
	 != EOF) {
    // show what was read
    MDB(kGeneral,1)
      printf(" adding: %3s %-40s %-40s %20.7f %7.3f %7.1f %-70s %-8s\n",
	     vers,dset,legend,xsec,scale,overlap,json,skim);
    
    TString histFile = fName + TString("_") + TString(dset) + TString("_")
      +                        TString(skim) + TString("_flatntuple.root");

    Sample *tmpSample = 0;
    if (xsec < 0)                                                        // found 'the data sample'
      tmpSample = AddDataSample(dset,skim,histFile.Data());
    else                                                       // define the new Monte Carlo sample
      tmpSample = AddSample(dset,skim,histFile.Data(), double(xsec), double(scale));

    // Convert '~' -> ' '
    TString tmpLegend = TString(legend);
    tmpLegend.ReplaceAll(TString("~"),TString(" "));
    tmpSample->SetLegend(tmpLegend.Data());
  }
  gSystem->ClosePipe(f);

  return;
}
