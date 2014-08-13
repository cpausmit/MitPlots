#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TH1D.h>
#include <TLegend.h>
#include <TText.h>

#include "MitPlots/Style/interface/MitStyle.h"

using namespace std;
using namespace mithep;

std::vector<std::string> machines;

void appendMachine(TString name);
bool findMachine(TString name);
bool rejectT3btch(TString name);

void plot(long int xStart, long int xStop, TString text, TString save);
void overlayFrame(TString text, bool align);

//--------------------------------------------------------------------------------------------------
void plotSmartCacheRequests()
{
  TDatime  date;
  TString  dateTime = date.AsSQLString();
  TString  text;
  TString  save;
  long int durationHour  =              3600;
  long int durationDay   =         24 * 3600;
  long int durationWeek  =     7 * 24 * 3600;
  long int durationMonth = 4 * 7 * 24 * 3600;
  long int xStart, xStop;

  time_t t;
  time(&t);   
  long int time = (long int) t;

  // Access the database just once
  TString timeSeriesFile("requests.txt");
  TString dbAccess("/home/cmsprod/DynamicData/SmartCache/Client/dumpSmartCacheHistoryDb.py");
  // remove potentially existing old file
  TString rmDbInfo = TString(".! rm -f ")+timeSeriesFile;
  gROOT->ProcessLine(rmDbInfo.Data());
  // create fresh input file
  TString getDbInfo = TString(".! ") + dbAccess + TString(" -q");
  gROOT->ProcessLine(getDbInfo.Data());

  // All time
  xStart = 0;
  xStop  = time;
  plot(xStart, xStop, "All time at "+dateTime, "AllTime");

  // Month
  xStart = time - durationMonth;
  xStop  = time;
  plot(xStart, xStop, "Last month at "+dateTime, "LastMonth");

  // Week
  xStart = time - durationWeek;
  xStop  = time;
  plot(xStart, xStop, "Last week at "+dateTime, "LastWeek");

  // Day
  xStart = time - durationDay;
  xStop  = time;
  plot(xStart, xStop, "Last day at "+dateTime, "LastDay");

  // Hour
  xStart = time - durationHour;
  xStop = time;
  plot(xStart, xStop, "Last hour at "+dateTime, "LastHour");

  return;
}

//--------------------------------------------------------------------------------------------------
void plot(long int xStart, long int xStop, TString text, TString save)
{
  // Save names (after machine name)
  TString sc1 = TString("lagTime")       + save + TString(".png");
  TString sc2 = TString("downloadSpeed") + save + TString(".png");
  TString sc  = save + (".png");

  // Rates file, pruned by shell script
  TString inName("./requests.txt");

  // File contents
  TString  file, content, version;
  long int n1, tRequest, n2, tReceived, tComplete;
  Double_t size;
  TString  machine;

  // Variables
  Double_t tLag   = 0, tDown   = 0, rate    = 0;
  Double_t maxLag = 0, maxDown = 0, maxRate = 0;

  Int_t nLines = 0, e = 0;
  bool empty = 0;

  printf("\nPreview of input file (%s) contents:\n",inName.Data());

  ifstream input;
  input.open(inName.Data());

  // First loop to find limits
  while (1) {

    // Read file
    input >> file >> content >> version >> n1 >> tRequest >> n2 >> tReceived >> tComplete
	  >> size >> machine;

    // Good file?
    if (! input.good())
      break;

    // During time interval?
    if (xStart > tReceived)
      continue;
    if (xStop  < tReceived)
      continue;

    // Filter invalid older data
    if (rejectT3btch(machine))
      continue;

    appendMachine(machine);

    tLag  = tReceived - tRequest;
    tDown = tComplete - tReceived;

    rate  = size/double(tDown);

    if (tDown <= 0) {
      e++;
      continue;
    }

    if (size <= 0)
      continue;

    // Preview of input file
    if (nLines < 5)
      printf("%s %s %s %d %d %d %d %d %f %s\n",
	     file.Data(),content.Data(),version.Data(),
	     n1,tRequest,n2,tReceived,tComplete,size,machine.Data());

    // Find limits
    if (tLag > maxLag)
      maxLag = tLag;
    if (tDown > maxDown)
      maxDown = tDown;
    if (rate > maxRate)
      maxRate = rate;

    nLines++;
  }
  input.close();

  printf("\n");
  printf("Found %i good requests in interval",nLines);
  printf("\nMaximum download rate [GB/sec] = %f",maxRate);
  printf("\nMaximum time for request receipt [sec] = %f",maxLag);
  printf("\n");
  printf("\nFound %i files with negative download time",e);
  printf("\n");

  // Prepare histograms
  MitStyle::Init();
  MitStyle::SetStyleWide();
  gStyle->SetPadRightMargin(0.07); // to make sure the exponent is on the picture

  TString hist1("hist1"), hist2("hist2");
  hist1.Prepend(save.Data());
  hist2.Prepend(save.Data());

  TH1D* h1 = new TH1D(hist1.Data(),"Lag time between request and start",100,0,maxLag);
  MitStyle::InitHistWide(h1,"","",kBlack);

  TH1D* h2 = new TH1D(hist2.Data(),"Average download speed",100,0,maxRate);
  MitStyle::InitHistWide(h2,"","",kBlack);

  const Int_t n = Int_t(machines.size());
  Int_t i = 0;
  Double_t null = 0;

  TH1D* h[n];
  for (int i=0; i<machines.size(); i++) {
    TString machineName = TString(machines[i]);
    machineName.Prepend(save.Data());
    h[i] = new TH1D(machineName.Data(),"Average download speed",100,0,maxRate);
    MitStyle::InitHistWide(h[i],"","",kBlack);
  }

  if (nLines < 1) {
    empty   = 1;
    printf("\nFound no good requests in interval :(\n");
    goto go;
  }

  input.open(inName.Data());

  // Second loop to fill histograms
  while (1) {

    // Read file
    input >> file >> content >> version >> n1 >> tRequest >> n2 >> tReceived
	  >> tComplete >> size >> machine;

    // Good file?
    if (! input.good())
      break;

    // During time interval?
    if (xStart > tReceived)
      continue;
    if (xStop 	< tComplete)
      continue;

    // Filter invalid older data
    if (rejectT3btch(machine))
      continue;

    tLag  = tReceived - tRequest;
    tDown = tComplete - tReceived;
    rate  = size/double(tDown);

    if (tDown <= 0)
      continue;

    if (size <= 0)
      continue;

    if (tLag != 0)
      h1->Fill(float(tLag));

    h2->Fill(rate,size);

    for (int i=0; i<machines.size(); i++) {
      TString machineName = TString(machines[i]);
      if (machineName == machine) {
        h[i]->Fill(rate,size);
        break;
      }
    }

    i++;
  }
  input.close();

 go:

  if (empty) {
    h1->Fill(null,null);
    h2->Fill(null,null);
  }

  if (empty) {
    for (int i=0; i<machines.size(); i++) {
      h[i]->Fill(null,null);
    }
  }

  // Draw the histograms, each to its own canvas
  TCanvas *c1 = new TCanvas("c1","Overall lag time between request and receipt");
  TCanvas *c2 = new TCanvas("c2","Overall average download speed");

  c1->cd();
  h1->GetXaxis()->SetTitle("Lag time [sec]");
  h1->GetYaxis()->SetTitle("Number of requests");
  h1->Draw();
  //overlayFrame(TString("t3 cluster"),1);
  overlayFrame(text,0);
  c1->SaveAs(sc1.Data());

  c2->cd();
  h2->GetXaxis()->SetTitle("Speed [GB/sec]");
  h2->GetYaxis()->SetTitle("Data downloaded [GB]");
  h2->Draw();
  overlayFrame(TString("t3 cluster"),1);
  overlayFrame(text,0);
  c2->SaveAs(sc2.Data());

  for (int i=0; i<machines.size(); i++) {
    TString machineName = TString(machines[i]);

    TCanvas *c = new TCanvas("c",machineName.Data());

    TString s = machineName.Append(sc.Data());
    c->cd();
    h[i]->GetXaxis()->SetTitle("Speed [GB/sec]");
    h[i]->GetYaxis()->SetTitle("Data downloaded [GB]");
    h[i]->Draw();
    overlayFrame(TString(machines[i]),1);
    overlayFrame(text,0);
    c->SaveAs(s.Data());
  }

  return;
}

//--------------------------------------------------------------------------------------------------
void appendMachine(TString name)
{
  // Append a machine, but only is it is not yet in the 'global list'
  if (! findMachine(name))
    machines.push_back(string(name.Data()));

  return;
}

//--------------------------------------------------------------------------------------------------
bool findMachine(TString name)
{
  // Find a machine in the 'global list' - true, else - false
  bool result = false;

  for (uint i=0; i<machines.size(); i++) {
    TString machineName = TString(machines[i]);
    
    if (machineName == name) {
      result = true;
      break;
    }
  }
  return result;
}

//--------------------------------------------------------------------------------------------------
bool rejectT3btch(TString name)
{
  // Does machine have this name?
  return (name == TString("t3btch.mit.edu"));
}

//--------------------------------------------------------------------------------------------------
void overlayFrame(TString text, bool align)
{
  // Overlay a linear frame from user coordinates (0 - 1, 0 - 1) and put the frame text

  // Create new transparent pad for the text
  TPad *transPad = new TPad("transPad","Transparent Pad",0,0,1,1);
  transPad->SetFillStyle(4000);
  transPad->Draw();
  transPad->cd();

  // Overlay the text in a well defined frame
  TText *plotText = new TText();
  plotText->SetTextColor(kBlue);
  plotText->SetTextSize(0.04);
  plotText->SetNDC();

  // Draw text at top right
  if (align) {
    plotText->SetTextColor(kBlack);
    plotText->SetTextAlign(33);
    plotText->DrawText(0.92,0.95,text.Data());
  }
  // Draw text at bottom left
  else
    plotText->DrawText(0.01,0.01,text.Data());

  return;
}
