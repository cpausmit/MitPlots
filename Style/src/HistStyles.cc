// $Id: HistStyles.cc,v 1.1.2.3 2010/10/12 21:50:11 paus Exp $

#include "MitAna/DataUtil/interface/Debug.h"
#include "MitPlots/Style/interface/HistStyles.h"

ClassImp(mithep::HistStyles)

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
HistStyles::HistStyles() :
  fNStyles  (0),
  fIStyle   (0),
  fDataStyle(0)
{
  // Constructor

  HistStyle *s;
  // add the default Monte Carlo styles
  s = AddStyle();
  s->SetColor      (kBlack);
  s->SetFillStyle  (0);
  s = AddStyle();
  s->SetColor      (kBlue);
  s->SetFillStyle  (3001);
  s = AddStyle();
  s->SetColor      (kRed);
  s->SetFillStyle  (3004);
  s = AddStyle();
  s->SetColor      (kGreen);
  s->SetFillStyle  (3007);
  s = AddStyle();
  s->SetColor      (kCyan);
  s->SetFillStyle  (3010);
  // add the default data style
  s = SetDataStyle ();
  s->SetColor      (kBlack);
  s->SetFillStyle  (0);
  s->SetMarkerStyle(20);
  s->SetMarkerSize (1.0);
}

//--------------------------------------------------------------------------------------------------
void HistStyles::Clear()
{
  // Reset all style and start with a clean slate

  fStyles.clear();
  
  return;
}
//--------------------------------------------------------------------------------------------------
void HistStyles::Show() const
{
  // Show present list of defined samples

  printf("\n ==== Histogram Styles overview ====\n\n");
  printf(" Dataset name                   Legend                Histogram file");
  printf("                                                  Cross Section [pb]\n");
  printf(" -------------------------------------------------------------------");
  printf("--------------------------------------------------------------------\n");
  fDataStyle->Show();
  printf(" -------------------------------------------------------------------");
  printf("--------------------------------------------------------------------\n");
  for (UInt_t i=0; i<fStyles.size(); i++)
    fStyles[i].Show();
  
  return;
}

//--------------------------------------------------------------------------------------------------
const HistStyle *HistStyles::GetStyle(UInt_t iStyle) const
{
  // Get style corresponding to given style index. Return NULL pointer if index out of range.

  if (iStyle >= fNStyles)
    return 0;

  return &fStyles[iStyle];
}

//--------------------------------------------------------------------------------------------------
const HistStyle *HistStyles::GetDataStyle() const
{
  // Get data style. Return NULL pointer if not available.

  return fDataStyle;
}

//--------------------------------------------------------------------------------------------------
HistStyle *HistStyles::AddStyle()
{
  // Adding another style (vector takes care of memory management)

  HistStyle* tmpStyle = new HistStyle();
  fStyles.push_back(*tmpStyle);
  fNStyles++;
  // cleanup after yourself
  delete tmpStyle;

  return &fStyles[fStyles.size()-1];
}

//--------------------------------------------------------------------------------------------------
HistStyle *HistStyles::SetDataStyle()
{
  // Setting the data sample (existing definition is overwritten)

  if (fDataStyle != 0)
    delete fDataStyle;

  fDataStyle = new HistStyle();

  return fDataStyle;
}

//--------------------------------------------------------------------------------------------------
const HistStyle *HistStyles::CurrentStyle() const
{
  // Get sample corresponding to current style index. Return NULL pointer if index out of range.

  if (fIStyle >= fNStyles)
    return 0;

  return &fStyles[fIStyle];
}

//--------------------------------------------------------------------------------------------------
void HistStyles::NextStyle()
{
  // Get sample corresponding to given sample number. Loop back to the beginning
  // if index goes out of range.

  fIStyle++;
  if (fIStyle >= fNStyles)
    fIStyle = 0;

  return;
}

//--------------------------------------------------------------------------------------------------
void HistStyles::PreviousStyle()
{
  // Get previous style

  if (fIStyle == 0)
    fIStyle = fStyles.size() - 1;
  else
    fIStyle--;

  return;
}

//--------------------------------------------------------------------------------------------------
void HistStyles::ResetStyle()
{
  // Get sample corresponding to given sample number. Return NULL pointer if index out of range.

  fIStyle = 0;

  return;
}

//--------------------------------------------------------------------------------------------------
void HistStyles::ApplyCurrentStyle(TH1 *h) const
{
  // Apply the present style to the given histogram

  h->SetMarkerColor(fStyles[fIStyle].Color());
  h->SetLineColor  (fStyles[fIStyle].Color());
  h->SetFillColor  (fStyles[fIStyle].Color());
  h->SetFillStyle  (fStyles[fIStyle].FillStyle());
  h->SetMarkerStyle(fStyles[fIStyle].MarkerStyle());
  h->SetMarkerSize (fStyles[fIStyle].MarkerSize());

  return;
}

//--------------------------------------------------------------------------------------------------
void HistStyles::ApplyDataStyle(TH1 *h) const
{
  // Apply the present style to the given histogram

  h->SetMarkerColor(fDataStyle->Color());
  h->SetLineColor  (fDataStyle->Color());
  h->SetFillColor  (fDataStyle->Color());
  h->SetFillStyle  (fDataStyle->FillStyle());
  h->SetMarkerStyle(fDataStyle->MarkerStyle());
  h->SetMarkerSize (fDataStyle->MarkerSize());

  return;
}
