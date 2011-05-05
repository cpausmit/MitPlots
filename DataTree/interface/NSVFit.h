//--------------------------------------------------------------------------------------------------
// $Id: NSVFit.h,v 1.5 2009/07/13 11:00:32 loizides Exp $
//
// NSVFit
//
// Basic implementation of a class that allows access to the nsv fit information for resonances that 
// decay into tau leptons (subsequenctly decaying into electrons, muons or hadrons).
//
// Authors: R.Wolf
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_NSVFIT_H
#define MITANA_DATATREE_NSVFIT_H
 
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class NSVFit : public DataObject
  {
    public:
      NSVFit() {}
			
      Bool_t       IsValid()         const {return fIsValid;}
	     
      Double_t     Mass()            const {return fMass; }
      Double_t     MassErrUp()       const {return fMassErrUp; }
      Double_t     MassErrDown()     const {return fMassErrDown; }
				     
      Double_t     MassMean()        const {return fMassMean; }
      Double_t     MassMedian()      const {return fMassMedian; }
      Double_t     MassMaximum()     const {return fMassMaximum; }
      Double_t     MassMaxInterpol() const {return fMassMaxInterpol; }

      FourVectorM  Daughter(UInt_t i)  const { return i<fDaughters.size() ? fDaughters.at(i).V() : FourVectorM(); }


      void         AddDaughter(Double_t pt, Double_t eta, Double_t phi, Double_t m);
      void         SetIsValid(Bool_t value)           { fIsValid     = value; }
      void         SetMass(Double_t value)            { fMass        = value; }
      void         SetMassErrUp(Double_t value)       { fMassErrUp   = value; }
      void         SetMassErrDown(Double_t value)     { fMassErrDown = value; }
      void         SetMassMean(Double_t value)        { fMassMean    = value; }
      void         SetMassMedian(Double_t value)      { fMassMaximum = value; }
      void         SetMassMaximum(Double_t value)     { fMassMaximum = value; }
      void         SetMassMaxInterpol(Double_t value) { fMassMaxInterpol = value; }

    protected:

      Bool_t   fIsValid;              // determines whether the fit converged or not

      Double_t fMass;                 // mass from fit
      Double_t fMassErrUp;            // +1 sigma error on mass from fit
      Double_t fMassErrDown;          // -1 sigma error on mass from fit
      	     
      Double_t fMassMean;             // mean of the mass from scan 
      Double_t fMassMedian;           // median of the mass from scan
      Double_t fMassMaximum;          // maximum of the mass from scan
      Double_t fMassMaxInterpol;      // maximum of the mass from scan 

      std::vector<Vect4M> fDaughters; // vector of four momenta of daughters (input values to fit)
      
      ClassDef(NSVFit,1) // NSVFit class
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::NSVFit::AddDaughter(Double_t pt, Double_t eta, Double_t phi, Double_t m)
{
  // Set four momentum of first daughter used in fit (ordering from fit)

  Vect4M buffer; buffer.Set(pt, eta, phi, m);
  fDaughters.push_back(buffer);
}

#endif
