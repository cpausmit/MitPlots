//--------------------------------------------------------------------------------------------------
// $Id: $
//
// SkimMod
//
// This module simply publishes an ObjArray and copies all marked data objects from the mother
// branch into this published ObjArray. It assumes that all marking is completed and the references
// will thus all resolve properly.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_SKIMMOD_H
#define MITANA_PHYSICSMOD_SKIMMOD_H

#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/TreeMod/interface/BaseMod.h" 

namespace mithep 
{
  template<class T>
  class SkimMod : public BaseMod 
  {
    public:
      SkimMod(const char *name  = "SkimMod", 
	      const char *title = "Skim module");
      ~SkimMod();

      const char              *GetBranchName()              const { return fBranchName; }
      void                     SetBranchName(const char *n)       { fBranchName = n;    }

    protected:
      TString                  fBranchName;    //name of collection
      
      const Collection<T>     *fCol;           //!pointer to collection (in - branch) 
      ObjArray<T>             *fColSkm;        //!pointer to collection (skm - published object)

      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      ClassDef(SkimMod, 1) // Skim module
  };
}

//--------------------------------------------------------------------------------------------------
template<class T>
mithep::SkimMod<T>::SkimMod(const char *name, const char *title) : 
  BaseMod    (name,title),
  fBranchName("SkmSetMe"),
  fCol       (0),
  fColSkm    (0)
{
  // Constructor.
}

template<class T>
mithep::SkimMod<T>::~SkimMod() 
{
  // Destructor.
  if (fColSkm)
    delete fColSkm;
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::SkimMod<T>::Process()
{
  // make sure the collection is empty before starting
  fColSkm->Reset();

  // load the branch with the properly marked objects
  LoadBranch(GetBranchName());
  const UInt_t entries = fCol->GetEntries();

  for (UInt_t i=0; i<entries; ++i) {
    if (fCol->At(i)->IsMarked()) {
      // Make sure the mark is not written to file
      //fCol->At(i)->Unmark();
      fColSkm->Add(fCol->At(i));
      if (fCol->At(i)->GetUniqueID() == 0)
        printf(" SkimMod -- WARNING -- UID ZERO: %d %d %s\n",
      	 fCol->At(i)->GetUniqueID(),
      	 fCol->At(i)->GetUniqueID()&0xfffff,
      	 fCol->GetName());
    }
  }
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::SkimMod<T>::SlaveBegin()
{
  // Request the marked input branch
  ReqBranch(GetBranchName(), fCol);
  // Request the branch to be published
  fColSkm = new mithep::ObjArray<T>(0,TString("Skm")+GetBranchName());
  PublishObj(fColSkm);
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::SkimMod<T>::SlaveTerminate()
{
}
#endif
