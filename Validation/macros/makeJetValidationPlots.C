#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <string>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TF1.h>
#include <TH1F.h>
#include <MitStyle.h>
using namespace std;
using namespace mithep;
#endif

#include <vector>

//--------------------------------------------------------------------------------------------------
// Main of the macro
//--------------------------------------------------------------------------------------------------
void makeJetValidationPlots()
{
  //Make Plots for Jet Validation
  gStyle->SetPalette(1);

  bool     doLeg   = true;
  double   legx[2] = { 0.5, 0.75 };
  double   legy[2] = { 0.7, 0.8 };
  double   legTextSize = 0.03;
  TString legTitle = "";

  string sample = "";
  string plotname;
  string filename;

  string filename1 = "mit-JetValidation-hist.root";

  plotname = "CaloJetsPt";
  filename = plotname + ".gif";
  TCanvas *cv = new TCanvas("cv", plotname.c_str() , 800,600); 
  TH1F *tmp1 = getHisto( filename1,"hIC5CaloJetsPt");        
  tmp1->SetAxisRange(0,200);
  tmp1->SetLineColor(4);
  tmp1->SetLineWidth(2);
  tmp1->Draw(); 
  double tmp1Entries = tmp1->GetEntries();
  TH1F* tmp2 = getHisto( filename1,"hSC5CaloJetsPt") ;  
  tmp2->SetAxisRange(0,200);
  tmp2->SetLineColor(2);
  tmp2->SetLineWidth(2);  
  tmp2->Draw("same");
  TLegend *leg=0;
  leg = new TLegend(legx[0],legy[0],legx[1],legy[1]);   
  leg->SetBorderSize(1);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(tmp1, "IC5", "LP"); 
  leg->AddEntry(tmp2, "SC5", "LP"); 
  leg->Draw();
  cv->SaveAs(filename.c_str());
  cv->Delete();

  plotname = "CaloJetEta";
  filename = plotname + ".gif";
  TCanvas *cv = new TCanvas("cv", plotname.c_str() , 800,600); 
  TH1F *tmp1 = getHisto( filename1,"hIC5CaloJetsEta");        
  tmp1->SetLineColor(4);
  tmp1->SetLineWidth(2);
  tmp1->Draw(); 
  double tmp1Entries = tmp1->GetEntries();
  TH1F* tmp2 = getHisto( filename1,"hSC5CaloJetsEta") ;  
  tmp2->SetLineColor(2);
  tmp2->SetLineWidth(2);  
  tmp2->Draw("same");
  TLegend *leg=0;
  leg = new TLegend(legx[0],legy[0],legx[1],legy[1]);   
  leg->SetBorderSize(1);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(tmp1, "IC5", "LP"); 
  leg->AddEntry(tmp2, "SC5", "LP"); 
  leg->Draw();
  cv->SaveAs(filename.c_str());
  cv->Delete();

  plotname = "IC5GenToRecoDeltaR";
  filename = plotname + ".gif";
  TCanvas *cv = new TCanvas("cv", plotname.c_str() , 800,600); 
  TH1F *tmp1 = getHisto( filename1,"hIC5GenJetRecoJetDeltaR");        
  tmp1->SetLineColor(4);
  tmp1->SetLineWidth(2);
  tmp1->Draw(); 
  double tmp1Entries = tmp1->GetEntries();
  TH1F* tmp2 = getHisto( filename1,"hSC5GenJetRecoJetDeltaR") ;  
  tmp2->SetLineColor(2);
  tmp2->SetLineWidth(2);  
  tmp2->DrawNormalized("same",tmp1Entries);
  TLegend *leg=0;
  leg = new TLegend(legx[0],legy[0],legx[1],legy[1]);   
  leg->SetBorderSize(1);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(tmp1, "IC5", "LP"); 
  leg->AddEntry(tmp2, "SC5", "LP"); 
  leg->Draw();
  cv->SaveAs(filename.c_str());
  cv->Delete();



  plotname = "IC5GenToRecoDeltaEta";
  filename = plotname + ".gif";
  TCanvas *cv = new TCanvas("cv", plotname.c_str() , 800,600); 
  TH1F *tmp1 = getHisto( filename1,"hIC5GenJetRecoJetDeltaEta");        
  tmp1->SetLineColor(4);
  tmp1->SetLineWidth(2);
  tmp1->Draw(); 
  double tmp1Entries = tmp1->GetEntries();
  TH1F* tmp2 = getHisto( filename1,"hSC5GenJetRecoJetDeltaEta") ;  
  tmp2->SetLineColor(2);
  tmp2->SetLineWidth(2);  
  tmp2->DrawNormalized("same",tmp1Entries);
  TLegend *leg=0;
  leg = new TLegend(legx[0],legy[0],legx[1],legy[1]);   
  leg->SetBorderSize(1);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(tmp1, "IC5", "LP"); 
  leg->AddEntry(tmp2, "SC5", "LP"); 
  leg->Draw();
  cv->SaveAs(filename.c_str());
  cv->Delete();

  plotname = "IC5GenToRecoDeltaPhi";
  filename = plotname + ".gif";
  TCanvas *cv = new TCanvas("cv", plotname.c_str() , 800,600); 
  TH1F *tmp1 = getHisto( filename1,"hIC5GenJetRecoJetDeltaPhi");        
  tmp1->SetLineColor(4);
  tmp1->SetLineWidth(2);
  tmp1->Draw(); 
  double tmp1Entries = tmp1->GetEntries();
  TH1F* tmp2 = getHisto( filename1,"hSC5GenJetRecoJetDeltaPhi") ;  
  tmp2->SetLineColor(2);
  tmp2->SetLineWidth(2);  
  tmp2->DrawNormalized("same",tmp1Entries);
  TLegend *leg=0;
  leg = new TLegend(legx[0],legy[0],legx[1],legy[1]);   
  leg->SetBorderSize(1);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(tmp1, "IC5", "LP"); 
  leg->AddEntry(tmp2, "SC5", "LP"); 
  leg->Draw();
  cv->SaveAs(filename.c_str());
  cv->Delete();

  plotname = "CentralIC5GenToRecoDeltaR";
  filename = plotname + ".gif";
  TCanvas *cv = new TCanvas("cv", plotname.c_str() , 800,600); 
  TH1F *tmp1 = getHisto( filename1,"hIC5CentralGenJetRecoJetDeltaR");        
  tmp1->SetLineColor(4);
  tmp1->SetLineWidth(2);
  tmp1->Draw(); 
  double tmp1Entries = tmp1->GetEntries();
  TH1F* tmp2 = getHisto( filename1,"hSC5CentralGenJetRecoJetDeltaR") ;  
  tmp2->SetLineColor(2);
  tmp2->SetLineWidth(2);  
  tmp2->DrawNormalized("same",tmp1Entries);
  TLegend *leg=0;
  leg = new TLegend(legx[0],legy[0],legx[1],legy[1]);   
  leg->SetBorderSize(1);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(tmp1, "IC5", "LP"); 
  leg->AddEntry(tmp2, "SC5", "LP"); 
  leg->Draw();
  cv->SaveAs(filename.c_str());
  cv->Delete();

  plotname = "ForwardIC5GenToRecoDeltaR";
  filename = plotname + ".gif";
  TCanvas *cv = new TCanvas("cv", plotname.c_str() , 800,600); 
  TH1F *tmp1 = getHisto( filename1,"hIC5ForwardGenJetRecoJetDeltaR");        
  tmp1->SetLineColor(4);
  tmp1->SetLineWidth(2);
  tmp1->Draw(); 
  double tmp1Entries = tmp1->GetEntries();
  TH1F* tmp2 = getHisto( filename1,"hSC5ForwardGenJetRecoJetDeltaR") ;  
  tmp2->SetLineColor(2);
  tmp2->SetLineWidth(2);  
  tmp2->DrawNormalized("same",tmp1Entries);
  TLegend *leg=0;
  leg = new TLegend(legx[0],legy[0],legx[1],legy[1]);   
  leg->SetBorderSize(1);
  leg->SetTextSize(legTextSize);
  leg->AddEntry(tmp1, "IC5", "LP"); 
  leg->AddEntry(tmp2, "SC5", "LP"); 
  leg->Draw();
  cv->SaveAs(filename.c_str());
  cv->Delete();

//**************************************************************************************************
//
//Make Jet Efficiency Plots
//
//**************************************************************************************************
  vector<string> numerator;
  vector<string> denominator;
  vector<string> jetEffLegendNames;

  plotname = "JetMatchingEfficiencyVsPt";
  numerator.clear();
  denominator.clear();
  jetEffLegendNames.clear();
  numerator.push_back("hIC5NMatchedCaloJetsVsGenJetPt");
  denominator.push_back("hIC5NGenJetsVsGenJetPt");
  jetEffLegendNames.push_back("IC5");
  numerator.push_back("hSC5NMatchedCaloJetsVsGenJetPt");
  denominator.push_back("hSC5NGenJetsVsGenJetPt");
  jetEffLegendNames.push_back("SC5");
  makeJetEfficiencyPlot(filename1, numerator, denominator, jetEffLegendNames, plotname, 10.0,5.0,30);


  plotname = "JetMatchingEfficiencyVsEta";
  numerator.clear();
  denominator.clear();
  jetEffLegendNames.clear();
  numerator.push_back("hIC5NMatchedCaloJetsVsGenJetEta");
  denominator.push_back("hIC5NGenJetsVsGenJetEta");
  jetEffLegendNames.push_back("IC5");
  numerator.push_back("hSC5NMatchedCaloJetsVsGenJetEta");
  denominator.push_back("hSC5NGenJetsVsGenJetEta");
  jetEffLegendNames.push_back("SC5");
  makeJetEfficiencyPlot(filename1, numerator, denominator, jetEffLegendNames, plotname, -5.0,0.25,39);

  plotname = "JetMatchingEfficiencyVsEta_Pt20To30";
  numerator.clear();
  denominator.clear();
  jetEffLegendNames.clear();
  numerator.push_back("hIC5NMatchedCaloJetsVsGenJetEta_Pt20To30");
  denominator.push_back("hIC5NGenJetsVsGenJetEta_Pt20To30");
  jetEffLegendNames.push_back("IC5");
  numerator.push_back("hSC5NMatchedCaloJetsVsGenJetEta_Pt20To30");
  denominator.push_back("hSC5NGenJetsVsGenJetEta_Pt20To30");
  jetEffLegendNames.push_back("SC5");
  makeJetEfficiencyPlot(filename1, numerator, denominator, jetEffLegendNames, plotname, -5.0,0.25,39);

  plotname = "JetMatchingEfficiencyVsEta_Pt30To40";
  numerator.clear();
  denominator.clear();
  jetEffLegendNames.clear();
  numerator.push_back("hIC5NMatchedCaloJetsVsGenJetEta_Pt30To40");
  denominator.push_back("hIC5NGenJetsVsGenJetEta_Pt30To40");
  jetEffLegendNames.push_back("IC5");
  numerator.push_back("hSC5NMatchedCaloJetsVsGenJetEta_Pt30To40");
  denominator.push_back("hSC5NGenJetsVsGenJetEta_Pt30To40");
  jetEffLegendNames.push_back("SC5");
  makeJetEfficiencyPlot(filename1, numerator, denominator, jetEffLegendNames, plotname, -5.0,0.25,39);

  plotname = "JetMatchingEfficiencyVsEta_Pt60To80";
  numerator.clear();
  denominator.clear();
  jetEffLegendNames.clear();
  numerator.push_back("hIC5NMatchedCaloJetsVsGenJetEta_Pt60To80");
  denominator.push_back("hIC5NGenJetsVsGenJetEta_Pt60To80");
  jetEffLegendNames.push_back("IC5");
  numerator.push_back("hSC5NMatchedCaloJetsVsGenJetEta_Pt60To80");
  denominator.push_back("hSC5NGenJetsVsGenJetEta_Pt60To80");
  jetEffLegendNames.push_back("SC5");
  makeJetEfficiencyPlot(filename1, numerator, denominator, jetEffLegendNames, plotname, -5.0,0.25,39);

//**************************************************************************************************
//
//Make Jet Response Plots
//
//**************************************************************************************************
  vector<string> jetResponseHistNames;
  vector<string> jetResponseLegendNames;

  plotname = "JetResponseVsGenJetPtInBarrel";
  jetResponseHistNames.clear();
  jetResponseLegendNames.clear();
  jetResponseHistNames.push_back("hIC5JetResponseVsGenJetPtInBarrel");
  jetResponseHistNames.push_back("hSC5JetResponseVsGenJetPtInBarrel");
  jetResponseLegendNames.push_back("IC5");
  jetResponseLegendNames.push_back("SC5");
 
  makeJetResponsePlot( filename1, jetResponseHistNames,
                       jetResponseLegendNames, 
                       plotname, 15,5,30,false);
  
  plotname = "JetResponseVsGenJetPtInEndcap";
  jetResponseHistNames.clear();
  jetResponseLegendNames.clear();
  jetResponseHistNames.push_back("hIC5JetResponseVsGenJetPtInEndcap");
  jetResponseHistNames.push_back("hSC5JetResponseVsGenJetPtInEndcap");
  jetResponseLegendNames.push_back("IC5");
  jetResponseLegendNames.push_back("SC5");
 
  makeJetResponsePlot( filename1, jetResponseHistNames,
                       jetResponseLegendNames, 
                       plotname, 15,5,20,false);
  
  plotname = "JetResponseVsGenJetPtForward";
  jetResponseHistNames.clear();
  jetResponseLegendNames.clear();
  jetResponseHistNames.push_back("hIC5JetResponseVsGenJetPtForward");
  jetResponseHistNames.push_back("hSC5JetResponseVsGenJetPtForward");
  jetResponseLegendNames.push_back("IC5");
  jetResponseLegendNames.push_back("SC5");
 
  makeJetResponsePlot( filename1, jetResponseHistNames,
                       jetResponseLegendNames, 
                       plotname, 15,5,20,false);


  plotname = "JetResponseVsCaloJetEta";
  jetResponseHistNames.clear();
  jetResponseLegendNames.clear();
  jetResponseHistNames.push_back("hIC5JetResponseVsCaloJetEta");
  jetResponseHistNames.push_back("hSC5JetResponseVsCaloJetEta");
  jetResponseLegendNames.push_back("IC5");
  jetResponseLegendNames.push_back("SC5");
 
  makeJetResponsePlot( filename1, jetResponseHistNames,
                       jetResponseLegendNames, 
                       plotname, 0,5,20,true);

  return;

}

TH1F* getHisto(string filename, string histoname) {
  TFile *tmpfile = new TFile(filename.c_str(),"READ"); assert(tmpfile);
  tmpfile->FindObjectAny("TAMTopModule");
  tmpfile->FindObjectAny("JetValidationMod");

  const char* histname = histoname.c_str();
  TH1F* tmpHist = (TH1F*) tmpfile->Get(histoname.c_str());  
  tmpHist->SetDirectory(0);
  tmpfile->Close();
  return tmpHist;
}

TH2F* get2DHisto(string filename, string histoname) {
  TFile *tmpfile = new TFile(filename.c_str(),"READ"); assert(tmpfile);
  tmpfile->FindObjectAny("TAMTopModule");
  tmpfile->FindObjectAny("JetValidationMod");

  const char* histname = histoname.c_str();
  TH2F* tmpHist = (TH2F*) tmpfile->Get(histoname.c_str());
  tmpHist->SetDirectory(0);
  tmpfile->Close();
  return tmpHist;
}

TH3F* get3DHisto(string filename, string histoname) {
  TFile *tmpfile = new TFile(filename.c_str(),"READ"); assert(tmpfile);
  tmpfile->FindObjectAny("TAMTopModule");
  tmpfile->FindObjectAny("JetValidationMod");

  const char* histname = histoname.c_str();
  TH3F* tmpHist = (TH3F*) tmpfile->Get(histoname.c_str());  
  tmpHist->SetDirectory(0);
  tmpfile->Close();
  return tmpHist;
}

void makeJetEfficiencyPlot( string inputFilename, vector<string> numeratorNames, vector<string> denominatorNames,
                            vector<string> legendNames, string plotname, double leftEdge, double binSize, int nBins) {

  assert(numeratorNames.size() == denominatorNames.size());
  assert(numeratorNames.size() == legendNames.size());

  TObjArray JetEfficiency(100);
  string filename = plotname + ".gif";
   
  vector<double> xaxis;
  vector<double> xerrors;
  vector<double> eff;
  vector<double> efferrors;
  for (int i=0; i < numeratorNames.size(); i++) {

    xaxis.clear();
    xerrors.clear();
    eff.clear();
    efferrors.clear();

    TH1F *numerator = getHisto(inputFilename, numeratorNames[i]);
    TH1F *denominator = getHisto(inputFilename, denominatorNames[i]);
    TH1F *effHist = numerator->Clone();

    cerr << "i=" << i << "  " << numerator << " " << denominator << endl;

    for (int j=0;j<=nBins;j++) {
      double lowerEdge = leftEdge + binSize*j;
      double upperEdge = leftEdge + binSize*(j+1);
      double center = (lowerEdge + upperEdge) / 2;
    
      xaxis.push_back(center);
      xerrors.push_back(binSize/2);
    
      cerr << "j=" << j << endl;
      
      numerator->SetAxisRange(lowerEdge,upperEdge);
      denominator->SetAxisRange(lowerEdge,upperEdge);    
    
      if (denominator->Integral() > 0) {
        eff.push_back(numerator->Integral() / denominator->Integral());
        efferrors.push_back(TMath::Sqrt( eff[j]*(1-eff[j])/denominator->Integral() ));
        cerr << "bin " << j << ": " << lowerEdge << " - " << upperEdge << " numerator=" << numerator->Integral() << "  denominator=" <<  denominator->Integral() << "   eff=" << numerator->Integral() / denominator->Integral() << " +- " << efferrors[j] << endl;  
      } else {
        eff.push_back(0.0);
        efferrors.push_back(0.0);
        cerr << "bin " << j << ": " << lowerEdge << " - " << upperEdge << " numerator=" << numerator->Integral() << "  denominator=" <<  denominator->Integral() << "   eff=" << "nan" << " +- " << efferrors[j] << endl;  
      }    
        
    }

    TGraphErrors *EffGraph = new TGraphErrors ( nBins+1,
                                                (Double_t *)&(xaxis[0]),
                                                (Double_t *)&(eff[0]),
                                                (Double_t *)&(xerrors[0]),
                                                (Double_t *)&(efferrors[0]));
    EffGraph->SetMarkerStyle(kFullSquare);
    EffGraph->GetYaxis()->SetTitle("Jet Matching Efficiency");
    EffGraph->GetXaxis()->SetTitle("GenJet Pt (GeV)");
    EffGraph->SetMarkerColor(2+i);
    EffGraph->SetMarkerSize(0.75);
    JetEfficiency.Add(EffGraph);
  }
   
  TCanvas *cv = new TCanvas("cv", filename.c_str() , 800,600); 
  TLegend *leg=0;
  leg = new TLegend(0.70,0.6,0.85,0.7);   
  leg->SetBorderSize(1);
  leg->SetTextSize(0.03);

  for (int i=0; i < numeratorNames.size(); i++) {
    if (i==0) {
      JetEfficiency[i]->Draw("AP");
    } else {
      JetEfficiency[i]->Draw("P");
    }    
    leg->AddEntry(JetEfficiency[i], legendNames[i].c_str(), "LP"); 
  }

  leg->Draw();
  cv->SaveAs(filename.c_str());
  cv->Delete();

  return;
}



void makeJetResponsePlot( string inputFilename, vector<string> histNames,vector<string> legendNames,
                          string plotname, int firstBin, int regionWidth, int NRegions,  
                          bool makeFitPlots = false) {

  assert(histNames.size() == legendNames.size());
  TObjArray JetResponseVsPt(100);
  vector<double> xaxis;
  vector<double> xerrors;
  vector<double> jetResponse;
  vector<double> jetResponseErrors;
  string filename = plotname + ".gif";

  for (int i=0;i<histNames.size();i++) {
    TH2F *tmp2D = get2DHisto( inputFilename ,histNames[i]);      
    if (tmp2D == NULL) {
      cerr << "cannot get histogram " << histNames[i] << " from file: " << inputFilename << endl;
      return;
    }
    
    if (i==0) {
      binWidth = tmp2D->GetYaxis()->GetBinWidth(1);
      leftEdge = tmp2D->GetYaxis()->GetBinLowEdge(1);
    }

    xaxis.clear();
    xerrors.clear();
    jetResponse.clear();
    jetResponseErrors.clear();
    
    for (int j=0;j<NRegions;j++) {
      Int_t index_lowEdge = firstBin + j*regionWidth;
      Int_t index_upperEdge = firstBin+(j+1)*regionWidth;
      
      xaxis.push_back(leftEdge + (index_lowEdge + index_upperEdge + 0.0) * binWidth / 2);
      xerrors.push_back(( regionWidth + 0.0) * binWidth / 2);
      TH1D *jetResponseBinned = tmp2D->ProjectionX("_px", index_lowEdge,index_upperEdge);
      double tempMean = jetResponseBinned->GetMean();
      double tempRMS = jetResponseBinned->GetRMS();
      
      TF1 *jetResponseFit = new TF1("jetResponseFit","gaus");
      jetResponseBinned->Fit(jetResponseFit,"","",tempMean-1.5*tempRMS,tempMean+1.5*tempRMS);
      
      jetResponse.push_back(jetResponseFit->GetParameter(1));
      jetResponseErrors.push_back(jetResponseFit->GetParError(1));
      if (makeFitPlots) {
        char label [50];
        sprintf(label,"%d",j);
        string canvasName = histNames[i] + "_" + label;
        string plotName = histNames[i] +"_"+label+".gif";
        TCanvas *cv2 = new TCanvas("cv2", canvasName.c_str() , 800,600); 
        jetResponseBinned->Draw();
        jetResponseFit->Draw("same");       
        cv2->SaveAs(plotName.c_str());
        cv2->Delete();
      }
    }

    TGraphErrors *tmpJetReponseVsPtGraph = 
      new TGraphErrors ( NRegions+1,
                         (Double_t *)&(xaxis[0]),
                         (Double_t *)&(jetResponse[0]),
                         (Double_t *)&(xerrors[0]),
                         (Double_t *)&(jetResponseErrors[0]));
    tmpJetReponseVsPtGraph->SetMarkerStyle(kFullSquare);
    tmpJetReponseVsPtGraph->GetYaxis()->SetTitle("CaloJetEt/GenJetEt");
    tmpJetReponseVsPtGraph->GetXaxis()->SetTitle("GenJet Pt (GeV)");
    tmpJetReponseVsPtGraph->SetMarkerColor(2+i);
    tmpJetReponseVsPtGraph->SetMarkerSize(0.75);
    JetResponseVsPt.Add(tmpJetReponseVsPtGraph);
    
    cerr << "done plot" << i << " " << tmpJetReponseVsPtGraph << " " << JetResponseVsPt[i] << endl;
                 
  }  

  TCanvas *cv = new TCanvas("cv", plotname.c_str() , 800,600); 
  TLegend *leg=0;
  leg = new TLegend(0.75,0.45,0.88,0.55);   
  leg->SetBorderSize(1);
  leg->SetTextSize(0.03);
  
  for (int i=0;i<histNames.size();i++) {
    cerr << "plot " << i << " " << JetResponseVsPt[i] << endl;
    if (i==0) {
      ((TGraphErrors*)JetResponseVsPt[i])->GetYaxis()->SetRangeUser(0.0,1.0);
      JetResponseVsPt[i]->Draw("AP");
    } else {
      JetResponseVsPt[i]->Draw("P");
    }
    leg->AddEntry(JetResponseVsPt[i], legendNames[i].c_str() , "LP"); 
  }

  leg->Draw("");
  cv->SaveAs(filename.c_str());
  cv->Delete();
  return;
}
