#include <vector>
#include <cstring>
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
#include <TTree.h>
#include "MitCommon/Utils/interface/Utils.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitPlots/Style/interface/MitStyle.h"
#include "MitPlots/Plot/interface/PlotTask.h"

ClassImp(mithep::PlotTask)

using namespace std;
using namespace mithep;

TPad *transPad = 0;
const TH1D *PlotTask::sPuWeights = 0;

//--------------------------------------------------------------------------------------------------
PlotTask::PlotTask(TaskSamples *taskSamples, const double lumi) :
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
  fAxisUnitX   (""),
  fLogy        (false),
  fXLegend     (65.),
  fYLegend     (94.),
  fNBins       (100),
  fImageFileName("mitPlotTask.png"),
  fCanvas      (0),
  fPuTarget    (0)
{
  // Constructor

  // If the task samples samples not yet already defined, do it now
  if (!fTask) {

    // read all environment variables
    TString home     = Utils::GetEnv("HOME");
    TString mitMyAna = Utils::GetEnv("MIT_USER_DIR");
    TString hstDir   = Utils::GetEnv("MIT_ANA_HIST");
    TString anaCfg   = Utils::GetEnv("MIT_ANA_CFG");
    TString prdCfg   = Utils::GetEnv("MIT_PROD_CFG");
    
    // define sample
    fTask = new TaskSamples(prdCfg.Data(),hstDir.Data());
    fTask->SetNameTxt(anaCfg.Data());
    fTask->ReadFile((mitMyAna + TString("/config")).Data());
  }
}

//--------------------------------------------------------------------------------------------------
PlotTask::~PlotTask()
{
  // Destructor

  delete fTask;
  delete fHistStyles;
  delete fEmptyHist;
  delete fDataHist;
  delete fCanvas;

  // I do not understand why when deleting the histograms I get a crash but I do, so I just clear
  // which will leave me all the histograms dangeling around

  //for (unsigned int i=0; i<fHists.size(); ++i) {
  //  delete fHists[i];
  //}
  fHists.clear();
  //for (unsigned int i=0; i<fStackedHists.size(); ++i) {
  //  delete fStackedHists[i];
  //}
  fStackedHists.clear();
  //for (unsigned int i=0; i<fHistsToPlot.size(); ++i) {
  //  delete fHistsToPlot[i];
  //}
  fHistsToPlot.clear();
}

//--------------------------------------------------------------------------------------------------
void PlotTask::SetAxisTitles(const char* xtit, const char* ytit/* = "Number of Events"*/, const char* xunit/* = ""*/)
{
  fAxisTitleX = TString(xtit);
  fAxisTitleY = TString(ytit);
  fAxisUnitX = TString(xunit);

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::SetDrawExp(const char* draw, const char* sel)
{
  fDrawExp = TString(draw);
  fSelExp  = TString(sel);

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::DrawFrame()
{
  // find the maximum
  double maximum = 0;
  if (fHistMaximum > 0)
    maximum = fHistMaximum;
  else {
    for (unsigned int i=0; i<fHistsToPlot.size(); i++) { 
      TH1D *h = fHistsToPlot[i];
      if (h->GetMaximum() > maximum)
	maximum = h->GetMaximum();
    }
  }

  // draw the frame
  TH1D *hTmp = new TH1D("FRAME","FRAME",fNBins,fHistXMinimum,fHistXMaximum);

  TString xtitle(fAxisTitleX);
  if (fAxisUnitX.Length() != 0)
    xtitle += " [" + fAxisUnitX + "]";

  MitStyle::InitHist(hTmp,xtitle.Data(),fAxisTitleY.Data(),kBlack);
  if (fHistMinimum != 0)
    hTmp->SetMinimum(fHistMinimum);
  hTmp->SetMaximum(maximum*1.1);
  // draw the frame large enough for the largest contribution (+10%)
  hTmp->DrawCopy("hist");

  // delete the temporary histogram
  if (hTmp)
    delete hTmp;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::DrawHistograms()
{
  // here we draw
  fHistStyles->ResetStyle();
  const HistStyle *hStyle = 0;
  for (unsigned int i=0; i<fHistsToPlot.size(); i++) { 
    TH1D *h = fHistsToPlot[i];
    hStyle = fHistStyles->CurrentStyle();
    h->SetLineColor(hStyle->Color());
    h->Draw("same,hist");        // do not use DrawCopy ... it does not display the first histogram
    fHistStyles->NextStyle();
  }
}

//--------------------------------------------------------------------------------------------------
void PlotTask::Plot(PlotType pType, const char* obj,
                    const char* draw/* = ""*/, const char* cuts/* = ""*/,
		    const char* samp/* = ""*/)
{
  // Interface to producing all type of plots

  // define what we draw
  SetDrawExp(draw,cuts);

  // ensure the histogram styles are ready
  if (! fHistStyles)
    fHistStyles = new HistStyles();

  // give overview of what we plot
  printf(" PlotTask::Plot -- Plotting\n\n");
  printf("   source    : %s\n   variable  : %s\n   with cuts : %s\n\n",obj,draw,cuts);
  printf("   MC samples: %d\n",fTask->NSamples());
  printf("   data      : %d\n\n",fTask->NDataSamples());

  // make sure there is something to do
  if (fTask->NSamples() + fTask->NDataSamples() < 1) {
    printf("    ERROR - no samples to plot. EXIT!\n\n");
    return;
  }

  // use logarithmic scale?
  delete fCanvas;
  fCanvas = new TCanvas;
  fCanvas->SetLogy(fLogy);

  // before collection histograms make sure to scale them histograms
  ScaleHistograms(obj);

  // decide which histograms to make
  if      (pType == Stacked) {        // integrating the stackd contribution is for another day
    DrawFrame();            // make a proper frame
    PlotStack(obj);
    OverlayStackFrame();    // overlay a frame to put the text and boxes on
  }
  else {
    if (pType == Contributions)
      CollectContributions(obj);
    else if (pType == Normalized)
      CollectNormalized(obj);

    // Now draw the produced histograms
    DrawFrame();       // make a proper frame
    DrawHistograms();  // draw the core histograms
    OverlayFrame();    // overlay a frame to put the text and boxes on
  }

  // Save all sample histograms
  TString sample = samp;
  if (sample.Sizeof()-1)
    SaveHistos(obj, samp, draw);

  // Store picture in png
  fCanvas->SaveAs(fImageFileName.Data());
}

//--------------------------------------------------------------------------------------------------
void PlotTask::SavePlot(char const* name/* = 0*/)
{
  if (!fCanvas)
    return;

  TString fileName(fImageFileName);
  if (std::strlen(name) != 0)
    fileName = name;

  fCanvas->SaveAs(fileName);
}

//--------------------------------------------------------------------------------------------------
void PlotTask::CollectNormalized(const char* hist)
{
  // Plot the histogram contribution by contribution each normalized to 1
  const Sample *s = 0;

  // say what we are doing
  printf("\n ==== Plotting Normalized Contributions -- %s ====\n\n",fTask->Name()->Data());

  // check x-axis title
  if (fAxisTitleX == TString(""))
    fAxisTitleX = TString(hist);

  // loop through samples and collect all histograms
  TH1D *hTmp = new TH1D("TMP","TMP",fNBins,fHistXMinimum,fHistXMaximum);
  Bool_t first  = kTRUE;
  for (UInt_t i=0; i<fHists.size(); i++) {
    s = fTask->GetSample(i);
    if (*s->Legend() != TString(" ")) {
      if (! first) {
	fHistsToPlot.push_back(new TH1D(1/hTmp->Integral() * (*hTmp)));
  	hTmp->Reset();
      }
      first = kFALSE;
      hTmp->SetName(*s->Legend());
      hTmp->SetTitle(*s->Legend());
    }
    hTmp->Add(fHists[i]);
  }
  // do not forget to push the last one
  fHistsToPlot.push_back(new TH1D(1/hTmp->Integral() * (*hTmp)));

  // cleanup the temporary histogram
  if (hTmp)
    delete hTmp;

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::CollectContributions(const char* hist)
{
  // Collecting all contributing histograms as requested
  const Sample *s = 0;

  // histograms what we are doing
  printf("\n ==== Plotting Contributions -- %s ====\n\n",fTask->Name()->Data());

  // check x-axis title
  if (fAxisTitleX == TString(""))
    fAxisTitleX = TString(hist);

  // prepare a temporary histogram for stacked contributions according to legend
  TH1D *hTmp = new TH1D("TMP","TMP",fNBins,fHistXMinimum,fHistXMaximum);
  // loop through samples and collect all histograms
  Bool_t first  = kTRUE;
  for (UInt_t i=0; i<fHists.size(); i++) {
    s = fTask->GetSample(i);
    // is this a histogram to plot?
    if (*s->Legend() != TString(" ")) {
      if (! first) {
	fHistsToPlot.push_back(new TH1D(*hTmp));
	hTmp->Reset();
      }
      first = kFALSE;
      hTmp->SetName(*s->Legend());
      hTmp->SetTitle(*s->Legend());
    }
    hTmp->Add(fHists[i]);
  }
  // do not forget to collect the last one
  fHistsToPlot.push_back(new TH1D(*hTmp));

  // and cleanup
  if (hTmp)
    delete hTmp;

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::PlotStack(const char* hist, bool rescale)
{
  // Show present list of defined samples
  const Sample *s = 0;

  // scale the histograms
  FindStackHistMaximum();

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
  TString binWStr(TString::Format(" /%7.3f", binW));
  // trim trailing zeros
  while (binWStr[binWStr.Length() - 1] == '0')
    binWStr = binWStr(0, binWStr.Length() - 1);
  // trim if the last character is '.'
  if (binWStr[binWStr.Length() - 1] == '.')
    binWStr = binWStr(0, binWStr.Length() - 1);

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

  TString xtitle(fAxisTitleX);
  if (fAxisUnitX.Length() != 0)
    xtitle += " [" + fAxisUnitX + "]";

  TString ytitle(fAxisTitleY + binWStr);
  if (fAxisUnitX.Length() != 0)
    ytitle += " " + fAxisUnitX;

  MitStyle::InitHist(hFrame,xtitle.Data(),ytitle.Data(),kBlack);
  hFrame->GetXaxis()->SetNdivisions(505);
  if (fHistMinimum != 0)
    hFrame->SetMinimum(fHistMinimum);
  hFrame->SetMaximum(fHistMaximum*1.1);
  hFrame->Draw("");

  Double_t nmctotal = 0.;
  for (UInt_t i=fHists.size(); i>0; i--) {
    nmctotal += fHists[i-1]->GetSumOfWeights();
  }
  
  Double_t ndata = 1.0;
  Double_t scale = 1.0;
  if (dynamic_cast<TH1D*>(fDataHist)) {
    ndata = fDataHist->GetSumOfWeights();
    scale = ndata/nmctotal;
  }
    
//  if (fDataHist) {
    
//  }
  
  printf("nmc = %5f, ndata = %5f, scale = %5f\n",nmctotal,ndata,scale);
  
  // loop through samples and draw all histograms
  fHistStyles->ResetStyle();
  for (UInt_t i=fStackedHists.size(); i>0; i--) {
    s = fTask->GetSample(i);

    TString xtitle(fAxisTitleX);
    if (fAxisUnitX.Length() != 0)
      xtitle += " [" + fAxisUnitX + "]";

    MitStyle::InitHist(fStackedHists[i-1],xtitle.Data(),fAxisTitleY.Data());
    if (rescale)
      fStackedHists[i-1]->Scale(scale);

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

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::ScaleHistograms(const char* hist)
{
  // Scale the histograms according to the cross section and the desired lumi and store them
  // for later use

  const Sample *s = 0;
  TDirectory *dirMcTmp = 0;
  TDirectory *dirDataTmp = 0;

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
  printf("\n Monte Carlo \n");
  printf("    SampleName                                 Skim -        nEvents");
  printf("            nEventsSelected    Cross Section        luminosity      Factor      Scale\n");
  printf(" ===================================================================");
  printf("=======================================================================================\n");
  double nTotRaw = 0.0, nTot = 0.0, nTot2 = 0.0;
  for (UInt_t i=0; i<fTask->NSamples(); i++) {
    s = fTask->GetSample(i);
    // open file belonging to this sample
    TFile *fif = new TFile((*fTask->Dir()+slash+*s->File()).Data());
    // make sure the file exists
    if (fif->IsOpen() == kFALSE) {
      printf(" WARNING -- sample  %s  does not have a histogram file. Continue without!\n",
             s->Name()->Data());
      continue;
    }
    // read and determine general properties of this sample
    dirMcTmp = (TDirectory*) gROOT->FindObject(dirFwk->Data());
    if (dirMcTmp)
      fif->cd(dirFwk->Data());
    TH1D *hAllEvts = (TH1D*) gROOT->FindObject(allEvts->Data());
    if (! hAllEvts) {
      printf(" WARNING -- sample  %s  does not have a framework file. Next sample!\n",
             s->Name()->Data());
      continue;
    }
    
    // set pileup weights -- adding pileup reweigthing
    if (fPuTarget) {
      if (sPuWeights)
        delete sPuWeights;
      TH1D *pusource = (TH1D*) dirMcTmp->Get("hNPU")->Clone();
      pusource->Scale(1.0/pusource->GetSumOfWeights());
      sPuWeights = new TH1D( (*fPuTarget) / (*pusource) );
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

    TDirectory *fid = 0;
    TString histname = hist;
    if (TString(hist).Contains("/")) {
      TObjArray *f = TString(hist).Tokenize("/");
      fid = (TDirectory*) fif->FindObjectAny(((TObjString*)(f->At(0)))->GetString());
      histname = ((TObjString*) f->At(1))->GetString();
      delete f;
    }
    else
      fid = fif;
   
    // First try to find the histogram explicitely (otherwise it is a variable of the tree)
    TH1D *h = dynamic_cast<TH1D*>(fid->FindObjectAny(histname));
    
    //histogram doesn't exist, try to find TTree instead
    if (!h) {
      TTree *htree = dynamic_cast<TTree*>(fid->FindObjectAny(histname));
      if (!htree) {
        printf(" WARNING -- sample  %s  does not have requested histogram. Next sample!\n",
        s->Name()->Data());
        continue;
      }
      
      TString histname("htempmc_");
      histname += *s->Name();
      h = new TH1D(histname,histname,fNBins,fHistXMinimum,fHistXMaximum);
      TString drawexp = fDrawExp + TString(">>") + histname;
      htree->Draw(drawexp,fSelExp);
    }
    
    if (! fEmptyHist) {
      fEmptyHist = new TH1D(factor * scale * (*h));
      fEmptyHist->Rebin(fNRebin);
      fEmptyHist->Reset();
    }

    double nEvtsSelRaw = h->GetSumOfWeights();
    double nEvtsSel    = nEvtsSelRaw * factor * scale;
    double nEvtsSelErr = TMath::Sqrt(nEvtsSelRaw) * factor * scale;

    TString tmp("->");
    if (*s->Legend() == TString(" "))
      tmp = "  ";

    printf(" %s %-40s - %14.0f %13.2f +- %9.2f %16.5f: %16.4f (x %8.3f x %8.3f)\n",
           tmp.Data(),s->Name()->Data(),
	   nEvts,nEvtsSel,nEvtsSelErr,*s->Xsec(),lumi,factor,scale);

    nTotRaw += nEvts;
    nTot    += nEvtsSel;
    nTot2   += nEvtsSelErr*nEvtsSelErr;

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
  // Monte Carlo summary
  printf(" %-40s           - %14.0f %13.2f +- %9.2f %16.5f: %16.4f (x %8.3f x %8.3f)\n",
	 "== Monte Carlo Total ==",nTotRaw,nTot,TMath::Sqrt(nTot2),0.0,0.0,1.0,1.0);


  //------------------------------------------------------------------------------------------------
  // go through the data samples
  //------------------------------------------------------------------------------------------------
  // loop through data samples and add them up, straight away
  if (fTask->NDataSamples() > 0)
    printf("\n Data \n");
  nTotRaw = 0.0;
  nTot    = 0.0;
  nTot2   = 0.0;
  for (UInt_t i=0; i<fTask->NDataSamples(); i++) {
    s = fTask->GetDataSample(i);
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
      dirDataTmp = (TDirectory*) gROOT->FindObject(dirFwk->Data());
      if (dirDataTmp)
        fif->cd(dirFwk->Data());
      TH1D *hAllEvts = (TH1D*) gROOT->FindObject(allEvts->Data());
      if (! hAllEvts) {
        printf(" WARNING -- sample  %s  does not have a framework file. Next sample!\n",
               s->Name()->Data());
	continue;
      }
      else {
        double nEvts = hAllEvts->GetEntries();
        
        TDirectory *fid = 0;
        TString histname = hist;
        if (TString(hist).Contains("/")) {
          TObjArray *f = TString(hist).Tokenize("/");
          fid = (TDirectory*) fif->FindObjectAny(((TObjString*)(f->At(0)))->GetString());
          histname = ((TObjString*)f->At(1))->GetString();
          delete f;
        }
        else
          fid = fif;
            
	TH1D *h = dynamic_cast<TH1D*>(fid->FindObjectAny(histname));
        //histogram doesn't exist, try to find TTree instead
        if (!h) {
          TTree *htree = dynamic_cast<TTree*>(fid->FindObjectAny(histname));
          if (!htree) {
            printf(" WARNING -- sample  %s  does not have requested histogram. Next sample!\n",
            s->Name()->Data());
            continue;
          }
          
          TString histname("htempdata_");
          histname += i;
          h = new TH1D(histname,histname,fNBins,fHistXMinimum,fHistXMaximum);
          TString drawexp = fDrawExp + TString(">>") + histname;
          //printf ("Draw(%s, %s);\n",drawexp.Data(),fSelExp.Data());
          htree->Draw(drawexp,fSelExp);
        }
        else
          // rebin it
          h->Rebin(fNRebin);

	double nEvtsSelRaw = h->GetSumOfWeights();
	double nEvtsSel    = nEvtsSelRaw;
	double nEvtsSelErr = TMath::Sqrt(nEvtsSelRaw);

	printf(" -> %-40s - %14.0f %13.2f +- %9.2f %16.5f: %16.4f (x %8.3f)\n",
	       s->Name()->Data(),
	       nEvts,nEvtsSel,nEvtsSelErr,*s->Xsec(),fTargetLumi,1.0);

	nTotRaw += nEvts;
	nTot    += nEvtsSel;
	nTot2   += nEvtsSelErr*nEvtsSelErr;

        // construct the complete data histogram
        if (! fDataHist)
          fDataHist = new TH1D(1.0 * (*h));
        else
          fDataHist->Add(h);
      }
    }
  }
  // Data summary
  printf(" %-40s           - %14.0f %13.2f +- %9.2f %16.5f: %16.4f (x %8.3f)\n\n",
	 "== Data Total =========",nTotRaw,nTot,TMath::Sqrt(nTot2),0.0,0.0,1.0);

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::FindHistMaximum()
{
  // Find maximum of all histograms
  const Sample *s = 0;

  // first check whether value was overwritten by hand
  if (fHistMaximum>0.)
    return;
  
  // Make sure to prepare a temporary histogram to stack contributions according to legend
  TH1D *hTmp = new TH1D("TMP","TMP",fNBins,fHistXMinimum,fHistXMaximum);

  Bool_t first  = kTRUE;
  for (UInt_t i=0; i<fHists.size(); i++) {
    s = fTask->GetSample(i);
    // is this a histogram to plot
    if (*s->Legend() != TString(" ")) {
      if (! first) {
	if (hTmp->GetMaximum() > fHistMaximum)
	  fHistMaximum = hTmp->GetMaximum();
	hTmp->Reset();
      }
      first = kFALSE;
    }
    hTmp->Add(fHists[i]);
  }
  // check the last histogram
  if (hTmp->GetMaximum() > fHistMaximum)
    fHistMaximum = hTmp->GetMaximum();

  // cleanup
  if (hTmp)
    delete hTmp;

  // check the data histogram if present
  if (fDataHist && fDataHist->GetMaximum() > fHistMaximum) {
    fHistMaximum = fDataHist->GetMaximum();
    fIdxHistMax  = fHists.size();
  }

  printf(" Histogram maximum (idx=%d) is set to be: %f\n",fIdxHistMax,fHistMaximum);

  return;
}

//--------------------------------------------------------------------------------------------------
void PlotTask::FindStackHistMaximum()
{
  // Find maximum of all histograms

  // first check whether value was overwritten by hand
  if (fHistMaximum>0.)
    return;

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

  printf(" Histogram maximum (idx=%d) is set to be: %f\n",fIdxHistMax,fHistMaximum);

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
  const Sample *s = 0;

  // create new transparent pad for the text
  if (transPad)
    delete transPad;
  transPad = new TPad("transPad","Transparent Pad",0,0,1,1);
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
  for (UInt_t i=0; i<fTask->NSamples(); i++) {
    // attach to the specific sample
    s = fTask->GetSample(i);
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
  for (UInt_t i=0; i<fTask->NSamples(); i++) {
  //for (UInt_t i=fTask->NSamples(); i>0; i--) {
    // attach to the specific sample
    s = fTask->GetSample(i); //!!!
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
    s = fTask->GetDataSample(0);
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

//--------------------------------------------------------------------------------------------------
void PlotTask::OverlayStackFrame() const
{
  // Overlay a linear frame from user coordinates (0-100,0-100)
  const Sample *s = 0;

  // create new transparent pad for the text
  transPad = new TPad("transPad","Transparent Pad",0,0,1,1);
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
  for (UInt_t i=fTask->NSamples(); i>0; i--) {
    // attach to the specific sample
    s = fTask->GetSample(i-1);
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
  for (UInt_t i=fTask->NSamples(); i>0; i--) {
    // attach to the specific sample
    s = fTask->GetSample(i-1);
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
    s = fTask->GetDataSample(0);
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
      //m->Draw();
      m->DrawMarker(xCorner+0.5*xIndent,yText);

      // draw text
      char l[1024];
      sprintf(l,"%.1f",fTargetLumi);
      TString dText = *s->Legend() + TString(" (") + TString(l) + TString("/pb)");
      MDB(kGeneral,1)
        printf(" Adding text \"%s\" at: (x,y) = (%6.2f,%6.2f)\n",dText.Data(),xText,yText);
      // set the proper text color
      text->SetTextFont (42);
      text->SetTextAlign(12);
      text->SetTextSize (0.03);
      text->SetTextColor(hStyle->Color());
      // plot the text
      text->SetTextAlign(12);
      text->DrawLatex(xText,yText,dText.Data());
    }
  }

  // Make sure the histogram frame is nice
  box->SetFillStyle(0);
  box->SetLineColor(kBlack);
  box->DrawBox(0,0,100,100);

  transPad->Update();
  
  delete text;
  delete box;

  return;
}

//--------------------------------------------------------------------------------------------------
float PlotTask::PuWeight(Int_t npu)
{
  if (npu<0)
    return 1.0;
  if (!sPuWeights)
    return 1.0;

  return sPuWeights->GetBinContent(sPuWeights->FindFixBin(npu));
}

//--------------------------------------------------------------------------------------------------
void PlotTask::SaveHistos(const char* obj, const char* out, const char* obs)
{
  // Open new rootfile

  TString outName = out;
  TString obsName = obs;
  TFile *tmpOut = new TFile(outName+"_"+obsName+".root", "RECREATE");
  tmpOut->cd();

  // Write data histogram to rootfile
  if (fTask->NDataSamples()) {
    fDataHist->Write();
    printf("Wrote data histogram \n");
  }
  
  // Read and write MC histograms
  if (!fHistsToPlot.size())
    CollectContributions(obj);
  for (unsigned int i = 0; i < fHistsToPlot.size(); i++) {
    fHistsToPlot[i]->Write();
    // printf("Wrote MC histo %i \n", i);
  }
  printf("Wrote all MC histograms \n");
  
  delete tmpOut;
  return;
}
