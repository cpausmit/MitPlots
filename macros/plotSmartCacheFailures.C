#include <iostream>
#include <fstream>

#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TH1D.h>
#include <TLegend.h>
#include <TText.h>

#include "MitPlots/Style/interface/MitStyle.h"

using namespace std;
using namespace mithep;

void plot(long int xStart = 0, long int xEnd = 0,
	  TString text = "", TString pngFileName = "failures.png");
void plotFrame(Double_t xMin, Double_t xMax, Double_t max = 0.95);
void overlayFrame(TString text);

//--------------------------------------------------------------------------------------------------
void plotSmartCacheFailures()
{
  TDatime date;
  TString dateTime = date.AsSQLString();
  TString text;
  long int durationHour  =              3600;
  long int durationDay   =         24 * 3600;
  long int durationWeek  =     7 * 24 * 3600;
  long int durationMonth = 4 * 7 * 24 * 3600;
  long int xStart, xEnd;

  // Plot SmartCache tranfers during the last hour, day, week, month
  time_t t;
  time(&t);   

  long int time = (long int) t;

  // Access the database just once
  TString timeSeriesFile("timeSeriesOfFailures.txt");
  TString dbAccess("/home/cmsprod/DynamicData/SmartCache/Client/snapshotSmartCacheFailedHistoryDb.py");
  // remove potentially existing old file
  TString rmDbInfo = TString(".! rm -f ")+timeSeriesFile;
  gROOT->ProcessLine(rmDbInfo.Data());
  // create fresh input file
  TString getDbInfo = TString(".! ") + dbAccess + TString(" -q");
  gROOT->ProcessLine(getDbInfo.Data());

  // hour
  text = TString("Last Hour at ") + dateTime; 
  xStart = time-durationHour;  xEnd = time; plot(xStart,xEnd,text,"failuresLastHour.png");
  // day
  text = TString("Last Day at ") + dateTime; 
  xStart = time-durationDay;   xEnd = time; plot(xStart,xEnd,text,"failuresLastDay.png");
  // week
  text = TString("Last Week at ") + dateTime; 
  xStart = time-durationWeek;  xEnd = time; plot(xStart,xEnd,text,"failuresLastWeek.png");
  // week
  text = TString("Last Month at ") + dateTime; 
  xStart = time-durationMonth; xEnd = time; plot(xStart,xEnd,text,"failuresLastMonth.png");
}

//--------------------------------------------------------------------------------------------------
void plot(long int xStart, long int xEnd, TString text, TString pngFileName)
{
  // This would be the direct access but TMySQL it is not installed with the CMS root version

  //TSQLServer *db = TSQLServer::Connect("mysql://t3btch039.mit.edu/SmartCache","ssluser","MitSmartCache!");
  //TSQLResult *result = db->Query("select * from CompletedDownloads");
  //
  //if (result)
  //  printf(" Query was successful, continue!\n");
  //else
  //  printf(" Query failed, exit!\n");

  // Make sure we have the right styles
  MitStyle::Init();
  MitStyle::SetStyleWide();
  gStyle->SetPadRightMargin(0.07); // to make sure the exponent is on the picture

  // will execute a shell command to get the data
  TString timeSeriesFile("timeSeriesOfFailures.txt");

  // Now open our database output
  ifstream input;
  input.open(timeSeriesFile.Data());

  Int_t time=0, nFail=0, nLines=0;
  Double_t xMin=double(xStart), xMax=double(xEnd), max=1.0;

  // First loop to determine the boundaries (could be done in one round, dynamically)
  //---------------------------------------------------------------------------------
  while (1) {
    // read in 
    input >> time >> nFail;
    // check it worked
    if (! input.good())
      break;

    //printf(" Min / Time / Max: %d %d %d\n",xStart,time,xEnd);

    // check whether in our requested time window
    if (xStart>0 && xStart>time)
      continue;
    if (xEnd>0 && xEnd<time)
      continue;
    
    // Show what we are reading
    if (nLines < 5)
      printf(" time=%d, nFails=%d\n",time, nFail);

    // Determine plot maximum
    if (nFail > max)
      max = nFail;

    nLines++;
  }
  input.close();

  printf(" \n");
  printf(" Found %d measurements.\n",nLines);
  printf(" Maximum failures at: %6.2f in 90 sec\n",max);
  printf(" \n");

  // Open a canvas
  TCanvas *cv = new TCanvas();
  cv->SetLogy(kTRUE);
  cv->Draw();

  if (nLines<1) {
    printf(" WARNING - no measurements selected.\n");
    plotFrame(double(xStart),double(xEnd));
    overlayFrame(text);
    cv->SaveAs(pngFileName.Data());
    return;
  }

  const int numVals = nLines;
  double xVals[numVals];
  double yVals[numVals];


  input.open(timeSeriesFile.Data());

  // Second loop to register the measured values
  //--------------------------------------------
  Int_t i = 0;
  while (1) {
    // read in 
    input >> time >> nFail;
    // check it worked
    if (!input.good())
      break;

    // check whether in our requested time window
    if (xStart>0 && xStart>time)
      continue;
    if (xEnd>0 && xEnd<time)
      continue;

    xVals[i] = time;
    yVals[i] = nFail;

    i++;
  }
  input.close();

  // Make a good frame
  plotFrame(xMin,xMax,max);

  // Prepare our graphs
  TGraph* graph1 = new TGraph(numVals, xVals, yVals);
  graph1->SetLineColor(2);
  graph1->SetLineWidth(2);
  graph1->SetMarkerColor(4);
  graph1->SetMarkerStyle(21);
  graph1->SetMarkerSize(0.4);

  // Through them into the multigraph
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(graph1,"lp");

  // Draw the graphs
  mg->Draw("CP");

  // Add a nice legend to the picture
  TLegend *leg = new TLegend(0.4,0.6,0.89,0.89);
  leg->SetX1(0.15);
  leg->SetX2(0.30);
  leg->SetY1(0.95);
  leg->SetY2(0.85);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(graph1,"number of failures","lp");
  leg->Draw();

  overlayFrame(text);
  cv->SaveAs(pngFileName);
}

//--------------------------------------------------------------------------------------------------
void plotFrame(Double_t xMin, Double_t xMax, Double_t max)
{
  // Make a good frame
  TH1D * h = new TH1D("tmp","Time Series of Failures",1,xMin,xMax);
  MitStyle::InitHistWide(h,"","",kBlack);
  h->SetTitle("; Epoch Time [sec]; SmartCache Failures / 90 sec");
  h->SetMaximum(max*1.2);
  h->Draw("hist");
}

//--------------------------------------------------------------------------------------------------
void overlayFrame(TString text)
{
  // Overlay a linear frame from user coordinates (0 - 1, 0 - 1) and put the frame text

  // create new transparent pad for the text
  TPad *transPad = new TPad("transPad","Transparent Pad",0,0,1,1);
  transPad->SetFillStyle(4000);
  transPad->Draw();
  transPad->cd();

  // overlay the text in a well defined frame
  TText *plotText = new TText(0.01,0.01,text.Data());
  plotText->SetTextSize(0.04);
  plotText->SetTextColor(kBlue);
  plotText->Draw();

  return;
}
