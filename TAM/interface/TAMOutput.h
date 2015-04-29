//
// $Id: TAMOutput.h,v 1.4 2009/07/17 19:18:04 loizides Exp $
//

#ifndef ROOT_TAMOutput
#define ROOT_TAMOutput

// keep this for compatibility 
#define TAM_TAMOutput


#include <vector>
using std::vector;


#ifndef ROOT_TList
#include "TList.h"
#endif
#ifndef ROOT_TObject
#include "TObject.h"
#endif
#ifndef ROOT_TMemberInspector
#include "TMemberInspector.h"
#endif
#ifndef ROOT_TNamed
#include "TNamed.h"
#endif
#ifndef ROOT_THashTable
#include "THashTable.h"
#endif
#ifndef ROOT_TClass
#include "TClass.h"
#endif


class TBrowser;
class TAModule;


class TAMOutput : public TList {
private:
   static const UInt_t kParentStrLen = 1028;

public:   
   struct TAMModInspector : public TMemberInspector {
      struct TAMModMember : public TNamed {
         // name  = name of output object itself (in the output list)
         // title = name of member storing the output object
         void    *fAddr;   //!address of member
         TClass  *fMClass; //module class
         
         TAMModMember(const Char_t* objectname=0,
                      const Char_t* membername=0,
                      void*  addr=0,
                      TClass* cl=0) :
            TNamed(objectname, membername),
            fAddr(addr),
            fMClass(cl) {}
         virtual ~TAMModMember() {}
         ClassDef(TAMModMember,1) // TAM module member class
      };
      
      THashTable     fOutputMembers; //stores members pointing to output objects
      
      TAMModInspector();
      virtual ~TAMModInspector();

      void           AddOutput(TObject* obj, const void* adr);
      using TMemberInspector::Inspect;
      virtual void   Inspect(TClass* cl, const Char_t* parent,
                             const Char_t* name, const void* addr) override;
      TAMModMember  *FindModMemberWithAddr(const void* addr);
      TAMModMember  *FindModMemberWithMemberName(const Char_t* mn);
      void           RemoveOutput(TObject* obj);
      void           SetMemberAddrFor(TObject* obj, const UInt_t verbose);

      ClassDef(TAMModInspector,1) // TAM inspector class
   };
   
private:
   TAMModInspector   fInspector; //stores info about module's output members
   TList             fOutput;    //list of this module's output (NOT owner)
   mutable TList     fCurOutput; //list of this module's output objects 
                                 // moved to fOutput after Merge (NOT owner)
   TAModule         *fMod;       //!pointer to the module whose output this is

   void              CallMerge(TObject* obj, TList& list);
   void              DeleteIterators(vector<TIterator*>& iters);
   TList            *GetCurOutputList()       { return &fCurOutput; }
   using      TList::FindObject;
   Long64_t          MergeOutput(TCollection* list);
   void              NullObjInAddOutput() const;
   void              NullClassFor(void* adr, const Char_t* tid) const;
   void              WarnNameDuplicate(const TObject* obj) const;
   
public:
   TAMOutput();
   TAMOutput(TAModule* mod);
   virtual ~TAMOutput();
   
   template <class OC>
   void              AddOutput(OC* const & obj);
   virtual void      Browse(TBrowser* b) override;
   static void       CheckHistDir(TObject* obj);
   TAMOutput        *FindModOutput(const TAModule* mod);
   TAMOutput        *FindModOutput(const Char_t* name);
   TObject          *FindOutput(const Char_t* obj);
   TObject          *FindOutput(const TObject* obj);
   TObject          *FindOutput(const Char_t* module, const Char_t* obj);
   const TAModule   *GetMod() const { return fMod; }
   TAModule         *GetMod()       { return fMod; }
   const TList      *GetOutputList() const { return &fOutput; }
   TList            *GetOutputList()       { return &fOutput; }
   Long64_t          Merge(TCollection* list);
   virtual void      ls(Option_t* option="") const override;
   using             TCollection::Print;
   virtual void      Print(Option_t* wildcard="") const override;
   void              RemoveOutput(TObject* obj);
   void              SetAllOutputMembers(const Bool_t setAddresses);
   void              SetMod(TAModule* mod) { fMod = mod; }
   void              SetOutputMembers(const Bool_t setAddresses);
   void              StoreAllOutputObjs();
   void              StoreOutputObjs();
   virtual Int_t     Write(const char* name=0, Int_t option=0, Int_t bsize=0) override;
   virtual Int_t     Write(const char* name=0, Int_t option=0, 
                           Int_t bsize=0) const override;
   Int_t             WriteCol(const TCollection *col, const char* name=0, 
                              Int_t option=0, Int_t bsize=0) const;

   ClassDef(TAMOutput, 2) // Tree analysis module output class
};


//______________________________________________________________________________
template <class OC>
inline void TAMOutput::AddOutput(OC* const & obj) 
{
   // Adds the object to the list of output objects of this module.
   // Stores the address of the pointer, for automatic module member pointer
   // setting.

   if (obj!=0) {
      TClass* cl = TClass::GetClass(typeid(OC));
      if (cl!=0) {
         if (cl->InheritsFrom(TObject::Class())) {
            TObject* o = dynamic_cast<TObject*>(obj);
            CheckHistDir(o);
            fInspector.AddOutput(o, &obj);
            if (fCurOutput.FindObject(o->GetName())!=0) WarnNameDuplicate(o);
            fCurOutput.Add(o);
         }
      } else NullClassFor(obj, typeid(OC).name());
   } else NullObjInAddOutput();
}

#endif //ROOT_TAMOutput
