#include <TROOT.h>
void compile(const char* macro) {

  TString macroP = TString(macro)+TString("+");
  printf("   Compiling: %s\n",macroP.Data());

  gROOT->LoadMacro(macroP);
}
  
