//==================================================================================================
//
// Plot the IntelROCCS data usage.
//
// - input file are text based with the follwoing fields
//     nSites  (number of sites, with copy)
//     size    (size of dataset) [GB]
//     nFiles  (per dataset)
//     nAccess (filebased accesses all sites)
//
// - key performance plots:
//     h->Fill(value = nAccess/nFiles,        weight = size);
//     h->Fill(value = nAccess/nFiles/nSites, weight = size);
//
//==================================================================================================
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

void overlayFrame(TString text);

//--------------------------------------------------------------------------------------------------
void plotIntelRoccs()
{
  TString text     = "since July/2013";
  TString fileName = "IntelRoccsAll";
  //TString text     = "before 90 days";
  //TString fileName = "IntelRoccsOver90Days";
  //TString text     = "last 90 days";
  //TString fileName = "IntelRoccsLess90Days";

  TString pngFileName = fileName + TString(".png");
  TString inputFile = fileName + TString(".txt");

  // Make sure we have the right styles
  MitStyle::Init();
  //gStyle->SetPadTopMargin(0.055); // to make sure the exponent is on the picture

  // will execute a shell command to get the data

  // Now open our database output
  ifstream input;
  input.open(inputFile.Data());

  Int_t    nLines=0;
  Double_t totalSize=0;

  Int_t    nSites=0, nFiles=0, nAccesses=0;
  Double_t size=0;

  Double_t xMin=0, xMax=40;

  // book our histogram
  TH1D *h = new TH1D("dataUsage","Data Usage",int(xMax-xMin),xMin,xMax);
  MitStyle::InitHist(h,"","",kBlack);  
  TString titles = TString("; Accesses ") + text + TString(";Data Size [TB]");
  h->SetTitle(titles.Data());

  // Loop over the file
  //-------------------
  while (1) {

    // read in 
    input >> nSites >> size >> nFiles >> nAccesses;

    // check it worked
    if (! input.good())
      break;
    
    // show what we are reading
    if (nLines < 5)
      printf(" nSites=%d, size=%8f nFiles=%d  nAccesses=%d\n",nSites, size, nFiles, nAccesses);

    Double_t value = double(nAccesses)/double(nFiles*nSites), weight = double(nSites)*size/1024.;

    totalSize += double(nSites)*size/1024.;

    // truncate at maximum (overflow in last bin) 
    if (value>=xMax)
      value = xMax-0.0001;
    
    h->Fill(value,weight);
    
    nLines++;
  }
  input.close();

  printf(" \n");
  printf(" Found %d entries.\n",nLines);
  printf(" Found %.3f [PB] total volume.\n",totalSize/1024.);
  printf(" \n");

  // Open a canvas
  TCanvas *cv = new TCanvas();
  cv->Draw();
  h->Draw("hist");

  overlayFrame(TString("Overflow in last bin."));

  cv->SaveAs(pngFileName.Data());
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
