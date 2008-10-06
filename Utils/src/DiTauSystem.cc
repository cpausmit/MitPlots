// $Id: DiTauSystem.cc,v 1.1 2008/09/30 19:24:22 ceballos Exp $

#include "MitAna/Utils/interface/DiTauSystem.h"

using namespace mithep;

DiTauSystem::DiTauSystem(ChargedParticle *t1, ChargedParticle *t2, Met *met):
  fT1(t1),
  fT2(t2),
  fMet(met) 
{
  init();
}

void DiTauSystem::init()
{
  CompositeParticle *tt = new CompositeParticle();
  tt->AddDaughter(fT1);
  tt->AddDaughter(fT2);
  
  CompositeParticle *higgs = new CompositeParticle();
  higgs->AddDaughter(fT1);
  higgs->AddDaughter(fT2);
  higgs->AddDaughter(fMet);
  
  double xvar[3];
  xvar[0] = higgs->Px()*fT2->Py()-higgs->Py()*fT2->Px();
  xvar[1] = higgs->Py()*fT1->Px()-higgs->Px()*fT1->Py();
  xvar[2] = fT1->Px()*fT2->Py()-fT1->Py()*fT2->Px();
  
  for(int i=0; i<2; ++i)
    xvar[i]==0 ? fXTau[i]=0 : fXTau[i]=xvar[2]/xvar[i];
  
  fVisMass  = tt->Mass();
  if (fXTau[0] > 0 && fXTau[1] > 0)
    fRecoMass = fVisMass / sqrt(fXTau[0]*fXTau[1]);
  else 
    fRecoMass = 0;
  
  fETll = 0;  fETnn = 0; fMT = 0;
  double visMassS = fVisMass*fVisMass;
  double ptll     = tt->Pt();
  double ptmis    = fMet->Pt();
  
  if (visMassS>0)
    {
      fETll    = sqrt( ptll*ptll   + visMassS);
      fETnn    = sqrt( ptmis*ptmis + visMassS);
      fMT      = (fETll+fETnn)*(fETll+fETnn)-(ptll+ptmis)*(ptll+ptmis);
      (fMT > 0) ? fMT=sqrt(fMT) : fMT=0;
    }
}
