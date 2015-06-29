#ifndef MITANA_TREEMOD_SELECTOR_GETOBJECT
#define MITANA_TREEMOD_SELECTOR_GETOBJECT

#include "MitAna/DataCont/interface/Collection.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include <stdexcept>

namespace mithep {
  // partial template specialization for Collection<O> request, where O derives from TObject
  template<class O>
  class mithep::Selector::GetObjectHelper<mithep::Collection<O>> {
  public:
    typedef O ArrayElement;
    typedef mithep::Collection<O> ReturnType;

    static ReturnType* Get(mithep::Selector&, char const* name, Bool_t warn);
  };
}

/*static*/
template<class T>
T*
mithep::Selector::GetObjectHelper<T>::Get(mithep::Selector& selector, char const* name, Bool_t warn)
{
  // Find object of the given name from the list of event objects,
  // public objects, and branches in this order.

  auto* info = static_cast<ObjInfo*>(selector.fObjInfoStore.FindObject(name));

  if (info) {
    if (info->IsEvtObject()) {
      auto* obj = dynamic_cast<T*>(selector.FindObjThisEvt(name));

      if (warn && !obj)
        selector.Warning("GetObject", "Object %s of type %s is registered as an event object but was not found in the current event.", name, T::Class()->GetName());

      return obj;
    }

    if (info->IsPublic() || info->IsBranch()) {
      if (!info->fObjType->InheritsFrom(T::Class())) {
        if (warn)
          selector.Warning("GetObject", "Type mismatch (%s != %s) for requested object %s.", T::Class()->GetName(), info->fObjType->GetName(), name);

        return 0;
      }

      if (info->IsBranch())
        selector.LoadBranch(info->fBranchInfo);

      return reinterpret_cast<T*>(info->fAddr);
    }

    selector.Error("GetObject", "Uninitialized object info");
    throw std::logic_error("");
  }

  info = new ObjInfo(name);

  auto* obj = dynamic_cast<T*>(selector.FindObjThisEvt(name));

  if (obj) {
    info->fSourceType = ObjInfo::kEvtObject;
  }
  else {
    obj = dynamic_cast<T*>(selector.FindPublicObj(name));
    if (obj) {
      info->fSourceType = ObjInfo::kPublic;
      info->fAddr = reinterpret_cast<BranchAddr_t>(obj);
    }
    else {
      auto* branchInfo = static_cast<TAMBranchInfo*>(selector.fBranchTable.FindObject(name));
      bool newBranchInfo = false;
      if (!branchInfo) {
        branchInfo = new TAMBranchInfo(name);
        newBranchInfo = true;
      }

      if (!branchInfo->GetLoader() && (!selector.FindLoader(branchInfo) || !branchInfo->Notify(selector.fTree))) {
        // warning already issued by FindLoader
        delete info;
        if (newBranchInfo)
          delete branchInfo;
        return 0;
      }

      info->fSourceType = ObjInfo::kBranch;

      if (newBranchInfo)
        selector.fBranchTable.Add(branchInfo);

      info->fBranchInfo = branchInfo;
      branchInfo->AddPtr(reinterpret_cast<T*&>(info->fAddr));
      if (branchInfo->IsLoaded())
        info->fAddr = branchInfo->GetLoader()->GetAddress();
      else
        selector.LoadBranch(branchInfo);

      obj = reinterpret_cast<T*>(info->fAddr);
    }
  }

  info->fObjType = obj->IsA();
  selector.fObjInfoStore.Add(info);

  return obj;
}

/*static*/
template<class O>
mithep::Collection<O>*
mithep::Selector::GetObjectHelper<mithep::Collection<O>>::Get(mithep::Selector& selector, char const* name, Bool_t warn)
{
  // Find object of the given name from the list of event objects,
  // public objects, and branches in this order.
  // If the located object is a collection of C whose base class is O,
  // fill ObjInfo::fCollection and return

  auto* info = static_cast<ObjInfo*>(selector.fObjInfoStore.FindObject(name));
  TObject* obj = 0;

  if (info) {
    if (info->fCollection && info->fCollectionCached && info->fCollection->IsA()->InheritsFrom(ReturnType::Class()))
      return static_cast<ReturnType*>(info->fCollection);

    if (info->IsEvtObject()) {
      obj = dynamic_cast<mithep::BaseCollection*>(selector.FindObjThisEvt(name));

      if (!obj) {
        if (warn)
          selector.Warning("GetObject", "Object %s is registered as an collection event object but was not found in the current event.", name);

        return 0;
      }
    }
    else if (info->IsPublic() || info->IsBranch()) {
      if (!info->fObjType->InheritsFrom(mithep::BaseCollection::Class())) {
        if (warn)
          selector.Warning("GetObject", "%s is not a collection.", name);

        return 0;
      }

      if (info->IsBranch())
        selector.LoadBranch(info->fBranchInfo);

      obj = reinterpret_cast<TObject*>(info->fAddr);
    }

    if (!obj) {
      // Info is registered as public or branch but null -> somehow broken. Delete and create a new one
      selector.fObjInfoStore.Remove(info);
      delete info;
    }
  }

  // lambda for casting obj to ReturnType
  auto CastCollection = [&selector, warn](TObject* obj, mithep::Selector::ObjInfo* info) -> ReturnType* {
    // First try direct cast    
    if (obj->IsA()->InheritsFrom(ReturnType::Class()))
      return static_cast<ReturnType*>(obj);

    // If not a collection, warn and return 0
    if (!obj->IsA()->InheritsFrom(mithep::BaseCollection::Class())) {
      if (warn)
        selector.Warning("GetObject", "Object %s is not a collection", info->GetName());

      return 0;
    }

    // Then check element type
    auto* col = static_cast<mithep::BaseCollection*>(obj);
    if (!col->ElementClass()) {
      if (warn)
        selector.Warning("GetObject", "Object %s is not a collection of objects", info->GetName());

      return 0;
    }

    if (col->ElementClass()->InheritsFrom(ArrayElement::Class())) {
      if (info->fCollection && info->fCollection->ElementClass() != ArrayElement::Class()) {
        if (warn)
          selector.Warning("GetObject", "Replacing the existing cache of ObjArray<%s> with ObjArray<%s>", info->fCollection->ElementClass()->GetName(), col->ElementClass()->GetName());

        delete info->fCollection;
        info->fCollection = 0;
      }
      if (!info->fCollection)
        info->fCollection = new mithep::ObjArray<ArrayElement>(col->GetSize());

      auto* ret = static_cast<mithep::ObjArray<ArrayElement>*>(info->fCollection);

      ret->Reset();
      for (unsigned iE = 0; iE != col->GetEntries(); ++iE)
        ret->Add(static_cast<ArrayElement*>(col->ObjAt(iE)));

      info->fCollectionCached = true;

      return ret;
    }
    else {
      if (warn)
        selector.Warning("GetObject", "Could not cast collection %s of %s to arary of %s", info->GetName(), col->ElementClass()->GetName(), ArrayElement::Class()->GetName());

      return 0;
    }
  };

  ReturnType* ret = 0;

  if (obj) {
    // information of the object exists, but the product is not cached yet as ReturnType
    ret = CastCollection(obj, info);
  }
  else {
    info = new ObjInfo(name);

    obj = selector.FindObjThisEvt(name);

    if (obj) {
      info->fSourceType = ObjInfo::kEvtObject;
      ret = CastCollection(obj, info);
    }
    else {
      obj = selector.FindPublicObj(name);
      if (obj) {
        info->fSourceType = ObjInfo::kPublic;
        info->fAddr = reinterpret_cast<BranchAddr_t>(obj);
        ret = CastCollection(obj, info);
      }
      else {
        auto* branchInfo = static_cast<TAMBranchInfo*>(selector.fBranchTable.FindObject(name));
        bool newBranchInfo = false;
        if (!branchInfo) {
          branchInfo = new TAMBranchInfo(name);
          newBranchInfo = true;
        }

        if (!branchInfo->GetLoader() && (!selector.FindLoader(branchInfo) || !branchInfo->Notify(selector.fTree))) {
          // warning already issued by FindLoader
          delete info;
          if (newBranchInfo)
            delete branchInfo;
          return 0;
        }

        info->fSourceType = ObjInfo::kBranch;

        if (newBranchInfo)
          selector.fBranchTable.Add(branchInfo);

        info->fBranchInfo = branchInfo;
        if (!branchInfo->IsLoaded())
          selector.LoadBranch(branchInfo);

        info->fAddr = branchInfo->GetLoader()->GetAddress();

        ret = CastCollection(reinterpret_cast<TObject*>(info->fAddr), info);

        if (ret)
          branchInfo->AddPtr(reinterpret_cast<mithep::BaseCollection*&>(info->fAddr));
      }
    }

    if (ret) {
      info->fObjType = ret->IsA();
      selector.fObjInfoStore.Add(info);
    }
    else {
      // sufficient number of warning rows must have been printed by now
      delete info;
    }
  }

  return ret;
}

template<class T>
T*
mithep::Selector::GetObject(char const* name, Bool_t warn)
{
  return GetObjectHelper<T>::Get(*this, name, warn);
}

#endif
