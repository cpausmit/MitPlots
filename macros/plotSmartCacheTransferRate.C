#include <iostream>
#include <fstream>

#include <TROOT.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TH1D.h>
#include <TLegend.h>

#include "MitPlots/Style/interface/MitStyle.h"

using namespace std;
using namespace mithep;

void plotSmartCacheTransferRate(Int_t xStart = 0, Int_t xEnd = 0)
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
  TString getDbInfo = TString(".! ") + dbAccess + TString(" > /dev/null");
  gROOT->ProcessLine(getDbInfo.Data());

  // Now open our database output
  ifstream input;
  input.open(timeSeriesFile.Data());

  Int_t time=0, nConn=0, nLines=0;
  Double_t rate=0, xMin=0, xMax=0, maxRate=0;

  // First loop to determine the boundaries (could be done in one round, dynamically)
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

    // Determine maximum
    if (rate > maxRate)
      maxRate = rate;

    if (xMin == 0.)
      xMin = double(time);
    
    xMax = double(time);

    nLines++;
  }
  input.close();

  printf(" \n");
  printf(" Found %d measurements.\n",nLines);
  printf(" Maximum tranfer rate at: %6.2f MB/sec\n",maxRate);
  printf(" \n");

  if (nLines<1) {
    printf(" ERROR - no measurements selected.\n");
    return;
  }
  
  const int numVals = nLines;
  double xVals[numVals];
  double y1Vals[numVals];
  double y2Vals[numVals];

  input.open(timeSeriesFile.Data());

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

  // Open a canvas
  TCanvas *cv = new TCanvas("TimeSeries","TimeSeries");
  cv->Draw();

  // Make a good frame
  TH1D * h = new TH1D("tmp","Time Series of Rates",1,xMin,xMax);
  MitStyle::InitHistWide(h,"","",kBlack);  
  h->SetTitle("; Epoch Time [sec]; SmartCache transfer rate [MB/sec]");
  h->SetMaximum(maxRate*1.1);
  h->Draw("hist");

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
  leg->SetX1(0.15);
  leg->SetX2(0.30);
  leg->SetY1(0.95);
  leg->SetY2(0.85);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(graph2,"number of tranfers","lp");
  leg->AddEntry(graph1,"data tranfer rate","lp");
  leg->Draw();
}
