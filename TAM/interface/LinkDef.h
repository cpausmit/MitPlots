//
// $Id: LinkDef.h 3890 2007-04-25 20:59:27Z loizides $
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

#endif
