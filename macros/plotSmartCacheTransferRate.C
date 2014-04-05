#include <iostream>
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

void plot(long int xStart = 0, long int xEnd = 0,
	  TString text = "", TString pngFileName = "transferRate.png");
void plotFrame(Double_t xMin, Double_t xMax, Double_t maxRate = 0.95);

//--------------------------------------------------------------------------------------------------
void plotSmartCacheTransferRate()
{
  TDatime date;
  TString dateTime = date.AsSQLString();
  TString text;
  long int durationHour  =               3600;
  long int durationDay   =          24 * 3600;
  long int durationWeek  =      7 * 24 * 3600;
  long int durationMonth = 28 * 7 * 24 * 3600;
  long int xStart, xEnd;

  // Plot SmartCache tranfers during the last 24 hours
  time_t t;
  time(&t);   

  long int time = (long int) t;

  // hour
  text = TString("Last Hour at ") + dateTime; 
  xStart = time-durationHour;  xEnd = time; plot(xStart,xEnd,text,"transferRateLastHour.png");
  // day
  text = TString("Last Day at ") + dateTime; 
  xStart = time-durationDay;   xEnd = time; plot(xStart,xEnd,text,"transferRateLastDay.png");
  // week
  text = TString("Last Week at ") + dateTime; 
  xStart = time-durationWeek;  xEnd = time; plot(xStart,xEnd,text,"transferRateLastWeek.png");
  // week
  text = TString("Last Month at ") + dateTime; 
  xStart = time-durationMonth; xEnd = time; plot(xStart,xEnd,text,"transferRateLastMonth.png");
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
  TString timeSeriesFile("timeSeriesOfRates.txt");
  TString dbAccess("/home/cmsprod/DynamicData/SmartCache/Client/snapshotSmartCacheHistoryDb.py");

  // remove potentially existing old file
  TString rmDbInfo = TString(".! rm -f ")+timeSeriesFile;
  gROOT->ProcessLine(rmDbInfo.Data());

  // create fresh input file
  TString getDbInfo = TString(".! ") + dbAccess + TString(" -q");
  gROOT->ProcessLine(getDbInfo.Data());

  // Now open our database output
  ifstream input;
  input.open(timeSeriesFile.Data());

  Int_t time=0, nConn=0, nLines=0;
  Double_t rate=0, xMin=double(xStart), xMax=double(xEnd), maxRate=1.0;

  // First loop to determine the boundaries (could be done in one round, dynamically)
  //---------------------------------------------------------------------------------
  while (1) {
    // read in 
    input >> time >> rate >> nConn;
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
      printf(" time=%d, rate=%8f nConnections=%d\n",time, rate, nConn);

    // Determine plot maximum
    if (rate > maxRate)
      maxRate = rate;
    if (nConn > maxRate)
      maxRate = double(nConn);

    nLines++;
  }
  input.close();

  printf(" \n");
  printf(" Found %d measurements.\n",nLines);
  printf(" Maximum tranfer rate at: %6.2f MB/sec\n",maxRate);
  printf(" \n");

  // Open a canvas
  TCanvas *cv = new TCanvas();
  cv->Draw();

  if (nLines<1) {
    printf(" WARNING - no measurements selected.\n");
    plotFrame(double(xStart),double(xEnd));
    double dX = double(xEnd)-double(xStart);
    TText *plotText = new TText(xMin-dX*0.14,0.-(maxRate*1.2*0.14),text.Data());
    printf("Text size: %f\n",plotText->GetTextSize());
    plotText->SetTextSize(0.04);
    plotText->SetTextColor(kBlue);
    plotText->Draw();
    cv->SaveAs(pngFileName.Data());
    return;
  }

  const int numVals = nLines;
  double xVals[numVals];
  double y1Vals[numVals];
  double y2Vals[numVals];

  input.open(timeSeriesFile.Data());

  // Second loop to register the measured values
  //--------------------------------------------
  Int_t i = 0;
  while (1) {
    // read in 
    input >> time >> rate >> nConn;
    // check it worked
    if (!input.good())
      break;

    // check whether in our requested time window
    if (xStart>0 && xStart>time)
      continue;
    if (xEnd>0 && xEnd<time)
      continue;

    xVals[i] = time;
    y1Vals[i] = rate;
    y2Vals[i] = nConn;

    i++;
  }
  input.close();

  // Make a good frame
  plotFrame(xMin,xMax,maxRate);
  double dX = double(xEnd)-double(xStart);
  TText *plotText = new TText(xMin-dX*0.14,0.-(maxRate*1.2*0.14),text.Data());
  plotText->SetTextSize(0.04);
  plotText->SetTextColor(kBlue);
  plotText->Draw();

  // Prepare our graphs
  TGraph* graph1 = new TGraph(numVals, xVals, y1Vals);
  graph1->SetLineColor(2);
  graph1->SetLineWidth(2);
  graph1->SetMarkerColor(4);
  graph1->SetMarkerStyle(21);
  graph1->SetMarkerSize(0.4);
  TGraph* graph2 = new TGraph(numVals, xVals, y2Vals);
  graph2->SetLineColor(3);
  graph2->SetLineWidth(2);
  graph2->SetMarkerColor(4);
  graph2->SetMarkerStyle(20);
  graph2->SetMarkerSize(0.4);

  // Through them into the multigraph
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(graph1,"lp");
  mg->Add(graph2,"lp");

  // Draw the graphs
  mg->Draw("CP");

  // Add a nice legend to the picture
  TLegend *leg = new TLegend(0.4,0.6,0.89,0.89);
  //leg->SetTextSize(0.036);
  leg->SetX1(0.15);
  leg->SetX2(0.30);
  leg->SetY1(0.95);
  leg->SetY2(0.85);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(graph2,"number of tranfers","lp");
  leg->AddEntry(graph1,"data tranfer rate","lp");
  leg->Draw();

  cv->SaveAs(pngFileName);
}

//--------------------------------------------------------------------------------------------------
void plotFrame(Double_t xMin, Double_t xMax, Double_t maxRate)
{
  // Make a good frame
  TH1D * h = new TH1D("tmp","Time Series of Rates",1,xMin,xMax);
  MitStyle::InitHistWide(h,"","",kBlack);  
  h->SetTitle("; Epoch Time [sec]; SmartCache transfer rate [MB/sec]");
  h->SetMaximum(maxRate*1.2);
  h->Draw("hist");
}
