//--------------------------------------------------------------------------------------------------
// $Id: PublisherMod.h,v 1.1 2008/11/25 14:30:53 loizides Exp $
//
// PublisherMod
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_PUBLISHERMOD_H
#define MITANA_PHYSICSMOD_PUBLISHERMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

namespace mithep 
{
  template<class T>
  class PublisherMod : public BaseMod 
  {
    public:
      PublisherMod(const char *name="PublisherMod", 
                   const char *title="Publisher module");
      ~PublisherMod() {}

      const char              *GetBranchName()              const { return fBranchName; }
      void                     SetBranchName(const char *n)       { fBranchName=n; }
      const char              *GetPublicName()              const { return fPublicName; }
      void                     SetPublicName(const char *n)       { fPublicName=n; }

    protected:
      TString                  fBranchName;    //name of collection
      TString                  fPublicName;    //name of collection
      T                       *fObj;           //!pointer to collection 

      void                     Process();
      void                     SlaveBegin();

      ClassDefT(PublisherMod,1) // Plot kinematics module
  };
}

//--------------------------------------------------------------------------------------------------
template<class T>
mithep::PublisherMod<T>::PublisherMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fBranchName("SetMe"),
  fPublicName(""),
  fObj(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::PublisherMod<T>::Process()
{
  // Process entries of the tree: Just load the branch and fill the histograms.

  LoadBranch(GetBranchName());
  AddObjThisEvt(fObj,GetPublicName());
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::PublisherMod<T>::SlaveBegin()
{
  // Request a branch and create the histograms.

  ReqBranch(GetBranchName(), fObj);

  if (fPublicName.IsNull())
    fPublicName = fBranchName;
}
#endif
