//--------------------------------------------------------------------------------------------------
// $Id: $
//
// DCA Significance
//
// This class holds information about the significance of the DCA for various particle assumptions.
//
// Authors: ?.?, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_DCASIG_H
#define MITANA_DATATREE_DCASIG_H

#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/PFTau.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class DCASig : public DataObject
  {
  public:
    DCASig() {}
    enum EDCAType {
      eETau,     //ETau
      eMuTau,    //MuTau
      eEMu,      //EMu
      eEE ,      //EE
      eMuMu,     //Mu Mu
      eTauTau    //Tau Tau
    };
    
    Double_t        DCASig3D()          const {return fDCA3D    /fDCA3DErr; }
    Double_t        DCASig2D()          const {return fDCA2D    /fDCA2DErr; }
    Double_t        DCASig3DRPhi()      const {return fDCA3DRPhi/fDCA3DRPhiErr; }
    Double_t        DCASig2DRPhi()      const {return fDCA2DRPhi/fDCA2DRPhiErr; }

    Double_t        DCA3D()             const {return fDCA3D; }
    Double_t        DCA2D()             const {return fDCA2D; }
    Double_t        DCA3DRPhi()         const {return fDCA3DRPhi; }
    Double_t        DCA2DRPhi()         const {return fDCA2DRPhi; }

    Double_t        DCA3DErr()          const {return fDCA3DErr; }
    Double_t        DCA2DErr()          const {return fDCA2DErr; }
    Double_t        DCA3DRPhiErr()      const {return fDCA3DRPhiErr; }
    Double_t        DCA2DRPhiErr()      const {return fDCA2DRPhiErr; }

    const PFTau    *GetTau()            const {return fTauRef.Obj();}
    const Electron *GetElectron()       const {return fElectronRef.Obj();}
    const Muon     *GetMuon()           const {return fMuonRef.Obj();}
    const PFTau    *Get2ndTau()         const {return f2ndTauRef.Obj();}
    const Electron *Get2ndElectron()    const {return f2ndElectronRef.Obj();}
    const Muon     *Get2ndMuon()        const {return f2ndMuonRef.Obj();}
    EDCAType        Type()              const {return fDCAType;}

    void            SetDCA2D       (Double_t  v)           { fDCA2D        = v; }
    void            SetDCA3D       (Double_t  v)           { fDCA3D        = v; }
    void            SetDCA2DRPhi   (Double_t  v)           { fDCA2DRPhi    = v; }
    void            SetDCA3DRPhi   (Double_t  v)           { fDCA3DRPhi    = v; }
    void            SetDCA2DErr    (Double_t  v)           { fDCA2DErr     = v; }
    void            SetDCA3DErr    (Double_t  v)           { fDCA3DErr     = v; }
    void            SetDCA2DRPhiErr(Double_t  v)           { fDCA2DRPhiErr = v; }
    void            SetDCA3DRPhiErr(Double_t  v)           { fDCA3DRPhiErr = v; }
    void            SetTau         (const mithep::PFTau*iTau, Bool_t i2nd=false)
                                                      { i2nd ? f2ndTauRef = iTau : fTauRef = iTau; }
    void            SetElectron    (const mithep::Electron *iElectron, Bool_t i2nd=false)
                                  { i2nd ? f2ndElectronRef = iElectron : fElectronRef = iElectron; }
    void            SetMuon        (const mithep::Muon *iMuon, Bool_t i2nd=false)
                                                  { i2nd ? f2ndMuonRef = iMuon : fMuonRef = iMuon; }
    void            SetType         (EDCAType v)           { fDCAType      = v; }

    // Some structural tools
    void            Mark() const;

  protected:
 
    EDCAType      fDCAType;         // Lepton pair type
    Double_t      fDCA3D;           // 3D xy   Distance of closest approach Unc
    Double_t      fDCA2D;           // 2D xy   Distance of closest approach Unc
    Double_t      fDCA3DRPhi;       // 3D RPhi Distance of closest approach Unc
    Double_t      fDCA2DRPhi;       // 2D RPhi Distance of closest approach Unc
	     				 
    Double_t      fDCA3DErr;        // 3D xy   Distance of closest approach Unc
    Double_t      fDCA2DErr;        // 2D xy   Distance of closest approach Unc
    Double_t      fDCA3DRPhiErr;    // 3D RPhi Distance of closest approach Unc
    Double_t      fDCA2DRPhiErr;    // 2D RPhi Distance of closest approach Unc

    Ref<PFTau>    fTauRef;          // Tau reference
    Ref<Electron> fElectronRef;     // Electron reference
    Ref<Muon>     fMuonRef;         // Muon reference
    Ref<PFTau>    f2ndTauRef;       // Tau reference
    Ref<Electron> f2ndElectronRef;  // Electron reference
    Ref<Muon>     f2ndMuonRef;      // Muon reference

    ClassDef(DCASig,1) // DCA Significance reference
  };
}

//--------------------------------------------------------------------------------------------------
inline void mithep::DCASig::Mark() const
{
  // mark myself
  mithep::DataObject::Mark();
  // mark my dependencies if they are there
  GetTau()->Mark();
  GetElectron()->Mark();
  GetMuon()->Mark();
  Get2ndTau()->Mark();
  Get2ndElectron()->Mark();
  Get2ndMuon()->Mark();
}
#endif
