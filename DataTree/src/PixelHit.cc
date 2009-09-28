// $Id: PixelHit.cc,v 1.1 2009/09/25 08:39:11 loizides Exp $

#include "MitAna/DataTree/interface/PixelHit.h"

ClassImp(mithep::PixelHit)

using namespace mithep;

//  Initialize the packing format singleton
PixelHit::Packing PixelHit::fPacking;

//--------------------------------------------------------------------------------------------------
PixelHit::Packing::Packing()
{
  // Constructor: pre-computes masks and shifts from field widths
  fProbX_width         = 11;
  fProbY_width         = 11;
  fQBin_width          = 3;
  fEdge_width          = 1;
  fBad_width           = 1;
  fTwoROC_width        = 1;
  fHasFilledProb_width = 1;
  fSpare_width         = 3;
  
  fProbX_units    = 1.008;
  fProbY_units    = 1.008;
  fProbX_1_over_log_units = 1.0 / TMath::Log(fProbX_units);
  fProbY_1_over_log_units = 1.0 / TMath::Log(fProbY_units);

  // Fields are counted from right to left!
  fProbX_shift          = 0;
  fProbY_shift          = fProbX_shift  + fProbX_width;
  fQBin_shift           = fProbY_shift  + fProbY_width; 
  fEdge_shift           = fQBin_shift   + fQBin_width; 
  fBad_shift            = fEdge_shift   + fEdge_width; 
  fTwoROC_shift         = fBad_shift    + fBad_width;
  fHasFilledProb_shift  = fTwoROC_shift + fTwoROC_width;
  
  // Ensure the complement of the correct number of bits:
  QualWordType zero32 = 0;  // 32-bit wide set of 0's
  fProbX_mask          = ~(~zero32 << fProbX_width);
  fProbY_mask          = ~(~zero32 << fProbY_width);
  fQBin_mask           = ~(~zero32 << fQBin_width);
  fEdge_mask           = ~(~zero32 << fEdge_width);
  fBad_mask            = ~(~zero32 << fBad_width);
  fTwoROC_mask         = ~(~zero32 << fTwoROC_width);
  fHasFilledProb_mask  = ~(~zero32 << fHasFilledProb_width);
}
