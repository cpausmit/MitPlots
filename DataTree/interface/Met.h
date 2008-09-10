//--------------------------------------------------------------------------------------------------
// $Id: Met.h,v 1.4 2008/09/10 03:33:27 loizides Exp $
//
// Met
//
// Details to be worked out...
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MET_H
#define MITANA_DATATREE_MET_H
 
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Track.h"

namespace mithep 
{
  class Met : public Particle
  {
    public:
      Met() : fMex(0), fMey(0) {}
      Met(Double_t mex, Double_t mey) : fMex(mex), fMey(mey) {}
      ~Met() {}

      virtual Double_t          Charge()             const { return 0; }
      virtual Double_t		E()                  const { return Pt();}
      virtual Double_t		Eta()                const { return Mom().Eta();}
      virtual Double_t	 	Mass()               const { return TMath::Sqrt(Mom().M2()); }
      virtual FourVector	Mom()                const { return FourVector(fMex,fMey,0,Pt()); }
      virtual Double_t		Phi()                const { return TMath::ATan2(fMey,fMex); }
      virtual Double_t		Pt()                 const { return TMath::Sqrt(fMex*fMex+fMey*fMey);}
      virtual Double_t	 	Px()                 const { return fMex;}
      virtual Double_t		Py()                 const { return fMey;}
      virtual Double_t		Pz()                 const { return 0; }
      virtual Double_t		P()                  const { return Pt(); }

      virtual Double_t          SumEt()              const { return fSumEt; } 
      virtual Double_t          MetSig()             const { return fMetSig; }    
      virtual Double_t          E_longitudinal()     const { return fElongit; }
      
      virtual const std::vector<Double_t>  Dmex()    const { return fDmex; }
      virtual const std::vector<Double_t>  Dmey()    const { return fDmey; }
      virtual const std::vector<Double_t>  DSumEt()  const { return fDSumEt; }
      
      virtual void              SetSumEt(Double_t x)             { fSumEt = x; }
      virtual void              SetE_longitudinal(Double_t x)    { fElongit = x; }
      virtual void              SetMetSig(Double_t x)            { fMetSig = x; }
      virtual void              PushCorrectionX(Double_t x)      { fDmex.push_back(x); }
      virtual void              PushCorrectionY(Double_t x)      { fDmey.push_back(x); }
      virtual void              PushCorrectionSumEt(Double_t x)  { fDSumEt.push_back(x); }
      
    protected:
      Double_t                  fMex;              // x-component
      Double_t                  fMey;              // y-component              
      Double_t                  fSumEt;            // scalar sum of ET over all objects
      Double_t                  fMetSig;           // MET Significance = MET / sqrt(SumET)            
      Double_t                  fElongit;          // z-comp. of vector E sum over all inputs
      std::vector<Double_t>     fDmex;             // vector of all corr. applied to MEx
      std::vector<Double_t>     fDmey;             // vector of all corr. applied to MEy
      std::vector<Double_t>     fDSumEt;           // vector of all corr. applied to SumET

    ClassDef(Met, 1) // Missing Et class
  };
}
#endif
