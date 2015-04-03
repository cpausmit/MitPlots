//
// $Id: LinkDef.h 5395 2009-01-20 12:18:42Z loizides $
//
//

#ifdef __CLING__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclasses;

#pragma link C++ class TAMBranchInfo+;
#pragma link C++ class TAModule+;
#pragma link C++ enum  TAModule::EModResult;
#pragma link C++ class TAMOutput+;
#pragma link C++ class TAMOutput::TAMModInspector-;
#pragma link C++ class TAMOutput::TAMModInspector::TAMModMember+;
#pragma link C++ class TAMSelector+;
#pragma link C++ class TAMTreeLoader+;
#pragma link C++ class TAMTreeBranchLoader+;
#pragma link C++ class TAMVirtualLoader+;
#pragma link C++ class TAMVirtualBranchLoader+;
#pragma link C++ class TAMObjLoader+;
#pragma link C++ class TAMObjBranchLoader+;

#endif
