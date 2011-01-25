// $Id: PlotTask.cc,v 1.1.2.2 2010/10/12 21:25:03 paus Exp $

#include <vector>
#include <TROOT.h>
#include <TSystem.h>
#include <TMath.h>
#include <TPad.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <TBox.h>
#include <TMarker.h>
#include <TLatex.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitPlots/Style/interface/MitStyle.h"
#include "MitPlots/Plot/interface/PlotTask.h"

ClassImp(mithep::PlotTask)

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
PlotTask::PlotTask(const TaskSamples *taskSamples, const double lumi) :
  fTask        (taskSamples),
  fHistStyles  (0),
  fTargetLumi  (lumi),
  fIdxHistMax  (-1),
  fNRebin      (1),
  fEmptyHist   (0),
  fDataHist    (0),
  fHistMinimum (0),
  fHistMaximum (0),
  fHistXMinimum(0),
  fHistXMaximum(0),
  fAxisTitleX  (""),
  fAxisTitleY  ("Number of Events"),
  fXLegend     (70.),
  fYLegend     (98.)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
PlotTask::~PlotTask()
{
  // Destructor

  if (fEmptyHist)
    delete fEmptyHist;
  if (fDataHist)
    delete fDataHist;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::SetAxisTitles(const char* xtit, const char* ytit)
{
  fAxisTitleX = TString(xtit);
  fAxisTitleY = TString(ytit);

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::PlotContributions(const char* dir, const char* hist)
{
  // Show present list of defined samples

  // scale the histograms
  ScaleHistograms(dir,hist);
  FindHistMaximum();

  // say what we are doing
  printf("\n ==== Plotting Contributions -- %s ====\n\n",fTask->Name()->Data());
  printf("  index of highest histogram %d (0-%d)\n\n",fIdxHistMax,fHists.size()-1);

  // check x-axis title
  if (fAxisTitleX == TString(""))
    fAxisTitleX = TString(hist);

  // initialize the largest histogram properly and draw it
  TH1D* hmax = 0;
  if (fIdxHistMax == fHists.size())
    hmax = fDataHist;
  else
    hmax = fHists[fHists.size()-1];
  MitStyle::InitHist(hmax,fAxisTitleX.Data(),fAxisTitleY.Data(),kBlack);
  hmax->GetXaxis()->SetNdivisions(505);
  if (fHistMinimum != 0)
    hmax->SetMinimum(fHistMinimum);
  if (fIdxHistMax == fHists.size())
    hmax->Draw("E");
  else
    hmax->Draw("hist");

  // loop through samples and draw all histograms
  int iCol  = (EColor) kBlack;
  int iFill = 3001;
  for (UInt_t i=0; i<*fTask->NSamples(); i++) {
    //const Sample *s = fTask->GetSample(i);
    MitStyle::InitHist(fHists[i],hist,"Number of Events",(EColor) iCol);

    fHists[i]->SetLineColor(iCol);
    //fHists[i]->SetFillColor(iCol);
    //fHists[i]->SetFillStyle(iFill);
    fHists[i]->Draw("same;Hist");

    iFill++; iCol++;
  }

  // overlay a frame to put the text and boxes on
  OverlayFrame();

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::PlotStack(const char* dir, const char* hist)
{
  // Show present list of defined samples

  // scale the histograms
  ScaleHistograms(dir,hist);
  FindHistMaximum();

  // ensure the histogram styles are ready
  if (! fHistStyles)
    fHistStyles = new HistStyles();

  // check basics
  if (fStackedHists.size() < 1) {
    printf(" WARNING -- no histograms with name: %s. EXIT!\n",hist);
    return;
  }

  // determine the width of one bin
  double binW = fEmptyHist->GetBinWidth(1);
  char binWStr[7];
  sprintf(binWStr," /%7.3f",binW);

  // say what we are doing
  printf("\n ==== Plotting Stack -- %s ====\n",fTask->Name()->Data());
  printf("\n   bin width: %7.3f  in  xMin: %7.3f  <--> xMax: %7.3f\n\n",
	 binW,fHistXMinimum,fHistXMaximum);

  // check x-axis title
  if (fAxisTitleX == TString(""))
    fAxisTitleX = TString(hist);

  // create the requested frame and initialize the empty histogram properly and draw it
  TH1D *hFrame = 0;
  if (fHistXMinimum != 0. || fHistXMaximum != 0.) {
    hFrame = new TH1D("Frame",fEmptyHist->GetTitle(),1,fHistXMinimum,fHistXMaximum);
  }
  else
    hFrame = fEmptyHist;

  MitStyle::InitHist(hFrame,fAxisTitleX.Data(),(fAxisTitleY+TString(binWStr)).Data(),kBlack);
  hFrame->GetXaxis()->SetNdivisions(505);
  if (fHistMinimum != 0)
    hFrame->SetMinimum(fHistMinimum);
  hFrame->SetMaximum(fHistMaximum*1.1);
  hFrame->Draw("");

  // loop through samples and draw all histograms
  fHistStyles->ResetStyle();
  for (UInt_t i=fStackedHists.size(); i>0; i--) {
    const Sample *s = fTask->GetSample(i);
    MitStyle::InitHist(fStackedHists[i-1],fAxisTitleX.Data(),fAxisTitleY.Data());
    if (i == fStackedHists.size()) {
      fHistStyles->ApplyCurrentStyle(fStackedHists[i-1]);
      fStackedHists[i-1]->Draw("same;Hist");
      fHistStyles->NextStyle();
    }
    else {
      if (*s->Legend() != TString(" ")) {
        // white out the histogram first
        fStackedHists[i-1]->SetFillColor(10);
        fStackedHists[i-1]->SetFillStyle(1001);
        fStackedHists[i-1]->DrawCopy("same;Hist");
        // overlay the histogram with proper hatching
	fHistStyles->ApplyCurrentStyle(fStackedHists[i-1]);
        fStackedHists[i-1]->Draw("same;Hist");
	fHistStyles->NextStyle();
      }
    }
  }

  if (fDataHist) {
    fHistStyles->ApplyDataStyle(fDataHist);
    fDataHist->Draw("same;E");
  }

  // overlay a frame to put the text and boxes on
  OverlayFrame();

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::ScaleHistograms(const char* dir, const char* hist)
{
  // Scale the histograms according to the cross section and the desired lumi and store them
  // for later use

  if (fHists.size() > 0) {
    printf(" WARNING - scaled histograms already exist. EXIT.");
    return;
  }

  fIdxHistMax = -1;

  // some useful definitions
  TString *dirFwk  = new TString("AnaFwkMod");
  TString *allEvts = new TString("hDAllEvents");
  TString  slash  ("/");

  // say what we are doing
  printf("\n ==== Extracting and Scaling Contributions -- %s ====\n\n",fTask->Name()->Data());
  printf("  target luminosity %f 1/fb\n\n",fTargetLumi/1000.);

  //------------------------------------------------------------------------------------------------
  // go through the Monte Carlo samples
  //------------------------------------------------------------------------------------------------
  // loop through samples and determine maximum
  printf("\n monte carlo \n");
  for (UInt_t i=0; i<*fTask->NSamples(); i++) {
    const Sample *s = fTask->GetSample(i);
    // open file belonging to this sample
    TFile *fif = new TFile((*fTask->Dir()+slash+*s->File()).Data());
    // make sure the file exists
    if (fif->IsOpen() == kFALSE) {
      printf(" WARNING -- sample  %s  does not have a histogram file. Continue without!\n",
             s->Name()->Data());
      continue;
    }
    // read and determine general properties of this sample
    TDirectory *dirTmp = (TDirectory*) gROOT->FindObject(dirFwk->Data());
    if (dirTmp)
      fif->cd(dirFwk->Data());
    TH1D *hAllEvts = (TH1D*) gROOT->FindObject(allEvts->Data());
    if (! hAllEvts) {
      printf(" WARNING -- sample  %s  does not have a framework file. Next sample!\n",
             s->Name()->Data());
      continue;
    }
    double nEvts   = hAllEvts->GetEntries();
    double lumi    = nEvts / *s->Xsec();
    double factor,scale = *s->Scale();
    if      (lumi < 0)
      factor = 1.0;
    else if (lumi > 0)
      factor = fTargetLumi/lumi;
    else
      factor = 0;

    TH1D *h    = (TH1D*) fif->FindObjectAny(hist);
    if (! h) {
      printf(" WARNING -- sample  %s  does not have requested histogram. Next sample!\n",
             s->Name()->Data());
      continue;
    }
    if (! fEmptyHist) {
      fEmptyHist = new TH1D(factor * scale * (*h));
      fEmptyHist->Rebin(fNRebin);
      fEmptyHist->Reset();
    }

    double nEvtsSelRaw = h->GetEntries();
    double nEvtsSel    = nEvtsSelRaw * factor * scale;
    double nEvtsSelErr = TMath::Sqrt(nEvtsSelRaw) * factor * scale;

    printf(" -> %-40s - %14.0f %10.3f +- %6.3f %16.7f: %16.4f (x %f x %f - %p)\n",
           s->Name()->Data(),nEvts,nEvtsSel,nEvtsSelErr,*s->Xsec(),lumi,factor,scale,(void*)h);

    // scale it
    TH1D *hTmp = new TH1D(factor * scale * (*h));
    hTmp->Rebin(fNRebin);
    // put it into our collection
    fHists.push_back(hTmp);
    // make a new histogram from the last added one and add the recent
    if (i == 0)
      fStackedHists.push_back(hTmp);
    else {
      TH1D *hStackedTmp = new TH1D(*fStackedHists[fStackedHists.size()-1]);
      // remember the stored histogram is already rebinned
      hStackedTmp->Add(hTmp);
      fStackedHists.push_back(hStackedTmp);
    }
  }

  //------------------------------------------------------------------------------------------------
  // go through the data samples
  //------------------------------------------------------------------------------------------------
  // loop through data samples and add them up, straight away
  if (*fTask->NDataSamples() > 0)
    printf("\n data \n");
  for (UInt_t i=0; i<*fTask->NDataSamples(); i++) {
    const Sample *s = fTask->GetDataSample(i);
    // open file belonging to the data sample
    TFile *fif = new TFile((*fTask->Dir()+slash+*s->File()).Data());
    // make sure the file exists
    if (fif->IsOpen() == kFALSE) {
      printf(" WARNING -- sample  %s  does not have a histogram file. Continue without!\n",
             s->Name()->Data());
      continue;
    }
    else {
      // read and determine general properties of this sample
      TDirectory *dirTmp = (TDirectory*) gROOT->FindObject(dirFwk->Data());
      if (dirTmp)
        fif->cd(dirFwk->Data());
      TH1D *hAllEvts = (TH1D*) gROOT->FindObject(allEvts->Data());
      if (! hAllEvts) {
        printf(" WARNING -- sample  %s  does not have a framework file. Next sample!\n",
               s->Name()->Data());
	continue;
      }
      else {
        double nEvts = hAllEvts->GetEntries();

	TH1D *h = (TH1D*) fif->FindObjectAny(hist);
        if (! h) {
          printf(" WARNING -- sample  %s  does not have requested histogram. Next sample!\n",
                 s->Name()->Data());
	  continue;
	}
        else
          // rebin it
          h->Rebin(fNRebin);

	double nEvtsSelRaw = h->GetEntries();
	double nEvtsSel    = nEvtsSelRaw;
	double nEvtsSelErr = TMath::Sqrt(nEvtsSelRaw);

	printf(" -> %-40s - %14.0f %10.3f +- %6.3f %16.7f: %16.4f (x %f)\n",
	       s->Name()->Data(),nEvts,nEvtsSel,nEvtsSelErr,*s->Xsec(),fTargetLumi,1.0);



        // construct the complete data histogram
        if (! fDataHist)
          fDataHist = new TH1D(1.0 * (*h));
        else
          fDataHist->Add(h);
      }
    }
  }

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::FindHistMaximum()
{
  // Find maximum of all histograms

  // first check whether value was overwritten by hand
  if (fHistMaximum>0.)
    return;
  
  // search through the single histograms
  for (UInt_t i=0; i<fHists.size(); i++) {
    if (fHists[i]->GetMaximum() > fHistMaximum) {
      fHistMaximum = fHists[i]->GetMaximum();
      fIdxHistMax  = i;
    }
  }

  // search through the stacked histograms
  fHistMaximum = 0.;
  for (UInt_t i=0; i<fStackedHists.size(); i++) {
    if (fStackedHists[i]->GetMaximum() > fHistMaximum)
      fHistMaximum = fStackedHists[i]->GetMaximum();
  }
  
  // check the data histogram if present
  if (fDataHist && fDataHist->GetMaximum() > fHistMaximum) {
    fHistMaximum = fDataHist->GetMaximum();
    fIdxHistMax  = fHists.size();
  }

  printf(" Histogram maximum is set to be: %f\n",fHistMaximum);

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::OverlayEmptyHist() const
{
  // Overlay an empty histogram onto the picture
  if (fEmptyHist)
    fEmptyHist->Draw("same");

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::OverlayFrame() const
{
  // Overlay a linear frame from user coordinates (0-100,0-100)

  // create new transparent pad for the text
  TPad *transPad = new TPad("transPad","Transparent Pad",0,0,1,1);
  transPad->SetFillStyle(4000);
  transPad->Draw();
  transPad->cd();
  // find out the right normalization to define the new range (histogram: 0,0 -> 100,100)
  double xtot = 1./(1. - transPad->GetLeftMargin() - transPad->GetRightMargin());
  double ytot = 1./(1. - transPad->GetBottomMargin() - transPad->GetTopMargin());
  transPad->Range((xtot*transPad->GetLeftMargin()  *-100      ),
                  (ytot*transPad->GetBottomMargin()*-100      ),
                  (xtot*transPad->GetRightMargin() * 100 + 100),
                  (ytot*transPad->GetTopMargin()   * 100 + 100));
  MDB(kGeneral,1)
    printf(" Range: %f %f %f %f\n",
           (xtot*transPad->GetLeftMargin()  *-100      ),
           (ytot*transPad->GetBottomMargin()*-100      ),
           (xtot*transPad->GetRightMargin() * 100 + 100),
           (ytot*transPad->GetTopMargin()   * 100 + 100) );

  // define the basic text to be used
  TLatex* text = new TLatex();
  text->SetTextFont (42);
  text->SetTextAlign(12);
  text->SetTextSize (0.03);

  // define the basic box to be used
  TBox *box = new TBox();
  box->SetLineWidth(2);
  // base coordinates for the text/boxes
  double xCorner = fXLegend, yCorner = fYLegend, yDelLine = 4.;
  double xIndent = 1.5*yDelLine;
  // count samples with non empty legend
  int nLegends = 0;
  for (UInt_t i=*fTask->NSamples(); i>0; i--) {
    // attach to the specific sample
    const Sample *s = fTask->GetSample(i-1);
    if (*s->Legend() != TString(" "))
      nLegends++;
  }
  int iDat = 0;
  if (fDataHist) {
    iDat = 1;
    nLegends++;
  }

  // set start values
  fHistStyles->ResetStyle();
  int iLeg  = 0;
  // loop through the sampels
  for (UInt_t i=*fTask->NSamples(); i>0; i--) {
    // attach to the specific sample
    const Sample *s = fTask->GetSample(i-1);
    // calculate corners for the text
    double xText = xCorner+xIndent, yText = yCorner-float((iLeg+iDat)+0.5)*yDelLine;
    // say what goes where
    MDB(kGeneral,1)
      printf(" Adding box at: (x1,y1,x2,y2) = (%6.2f,%6.2f,%6.2f,%6.2f)\n",
             xCorner+0.15*xIndent,yText-0.3*yDelLine,
             xCorner+0.85*xIndent,yText+0.4*yDelLine);
    // plot the box
    if (*s->Legend() != TString(" ")) {
      const HistStyle *hStyle = fHistStyles->CurrentStyle();
      box->SetFillStyle(0);
      box->SetFillColor(hStyle->Color());
      box->SetLineColor(hStyle->Color());
      box->DrawBox(xCorner+0.15*xIndent,yText-0.3*yDelLine,
                   xCorner+0.85*xIndent,yText+0.4*yDelLine);
      box->SetFillStyle(hStyle->FillStyle());
      box->DrawBox(xCorner+0.15*xIndent,yText-0.3*yDelLine,
                   xCorner+0.85*xIndent,yText+0.4*yDelLine);

      TString pText = *s->Legend();
      MDB(kGeneral,1)
        printf(" Adding text \"%s\" at: (x,y) = (%6.2f,%6.2f)\n",pText.Data(),xText,yText);
      // set the proper text color
      text->SetTextColor(hStyle->Color());
      // plot the text
      text->SetTextAlign(12);
      text->DrawLatex(xText,yText,pText.Data());

      fHistStyles->NextStyle();
      // keep track of how many were printed
      iLeg++;
    }
  }

  // attach to the data sample
  if (fDataHist) {
    const Sample *s = fTask->GetDataSample(0);
    // calculate corners for the text
    double xText = xCorner+xIndent, yText = yCorner-float(1-0.7)*yDelLine;
    // say what goes where
    MDB(kGeneral,1)
      printf(" Adding marker at: (x,y) = (%6.2f,%6.2f)\n",
             xCorner+0.5*xIndent,yText);
    // plot the marker
    if (*s->Legend() != TString(" ")) {
      const HistStyle *hStyle = fHistStyles->GetDataStyle();

      // draw marker
      TMarker *m = new TMarker(xCorner+0.5*xIndent,yText,20);
      m->SetMarkerColor(hStyle->Color      ());
      m->SetMarkerSize (hStyle->MarkerSize ());
      m->SetMarkerStyle(hStyle->MarkerStyle());
      m->Draw();
      // draw text
      char l[1024];
      sprintf(l,"%4.2f",fTargetLumi);
      //TString pText = *s->Legend() + TString(" (#int L = ") + TString(l) + TString("/pb)");
      TString pText = *s->Legend() + TString(" (") + TString(l) + TString("/pb)");
      MDB(kGeneral,1)
        printf(" Adding text \"%s\" at: (x,y) = (%6.2f,%6.2f)\n",pText.Data(),xText,yText);
      // set the proper text color
      text->SetTextColor(hStyle->Color());
      // plot the text
      text->SetTextAlign(12);
      text->DrawLatex(xText,yText,pText.Data());
    }
  }

  // Make sure the histogram frame is nice
  box->SetFillStyle(0);
  box->SetLineColor(kBlack);
  box->DrawBox(0,0,100,100);

  delete text;
  delete box;

  return;
}
