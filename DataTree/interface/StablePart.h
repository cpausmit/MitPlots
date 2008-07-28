//--------------------------------------------------------------------------------------------------
// $ Id: $
//
// Description: Class StablePart
// ------------
//
// Implementation of a stable particle class for use in general analyses in CMS. The contents of a
// stable particle is basically its link to the track it refers to. This will be hopefully at some
// point a useful and good implementation. See the double dispatcher doAction(MyAction).
//
// Author List: Ch.Paus
//--------------------------------------------------------------------------------------------------

#ifndef _mithep_STABLEPART_H_
#define _mithep_STABLEPART_H_

#include <iostream>
#include <cmath>

#include "MitAna/DataTree/interface/BasePart.h"

namespace mithep
{
  class BasePartAction;
  class StablePart : public BasePart
  {
  public:
    // Constructors
    StablePart();
    StablePart(int pid);
    StablePart(int pid, double mass);
    StablePart(const StablePart &);
    // Destructor
    virtual ~StablePart() {}
    
    // Override recursion helper method
    virtual void   doAction   (BasePartAction *Action) const;
    // General printing method
    virtual void   print      (std::ostream &os = std::cout) const;

    //----------------------------------------------------------------------------------------------
    // Acessors
    //----------------------------------------------------------------------------------------------
    // Getting
    int            stat       () const { return stat_; }
    int            hits       () const { return hits_; }
    // Track parameters and errors
    double         phi0       () const { return phi0_; }
    double         phi0Err    () const { return phi0Err_; }
    //double         d0         (TVector3 *vtx) const;
    double         d0Raw      () const { return d0_; }
    double         d0Err      () const { return d0Err_; }
    double         pt         () const { return fabs(pt_); }
    double         ptErr      () const { return ptErr_; }
    //double         z0         (TVector3 *vtx) const;
    double         z0Raw      () const { return z0_; }
    double         z0Err      () const { return z0Err_; }
    double         cotT       () const { return cotT_; }
    double         cotTErr    () const { return cotTErr_; }
    // Setting
    void           setStat    (int   v) { stat_    = v; }
    void           setHits    (int   v) { hits_    = v; }
    void           setPhi0    (float v) { phi0_    = v; }
    void           setPhi0Err (float v) { phi0Err_ = v; }
    void           setD0Raw   (float v) { d0_      = v; }
    void           setD0Err   (float v) { d0Err_   = v; }
    void           setPt      (float v) { pt_      = v; }
    void           setPtErr   (float v) { ptErr_   = v; }
    void           setZ0Raw   (float v) { z0_      = v; }
    void           setZ0Err   (float v) { z0Err_   = v; }
    void           setCotT    (float v) { cotT_    = v; }
    void           setCotTErr (float v) { cotTErr_ = v; }
    
    int            charge     () const { return (pt_>0) ? 1 : -1; }
   
  private:
    // Constant which is store in the file
    int            hits_;                // Mostly Hit informations
    int            stat_;                // Storage for various interesting things
    float          phi0_,phi0Err_;       // Follow track parameters/uncertainties
    float          d0_,  d0Err_;
    float          pt_,  ptErr_;
    float          z0_,  z0Err_;
    float          cotT_,cotTErr_;

    ClassDef(StablePart, 1)
  };
}
#endif
