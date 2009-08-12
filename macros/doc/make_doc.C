// $Id: make_doc.C,v 1.9 2009/08/11 23:11:30 loizides Exp $

// Since we do use our own THtml code from MitAna/Utisl, we 
// on purpose do not compile this macro anymore.
void make_doc()
{
  gROOT->ProcessLine(".L $CMSSW_BASE/src/MitAna/macros/setRootEnv.C+");
  loadLibraries("libMitCommon*");
  loadLibraries("libMitAna*");
  loadLibraries("libMitPhysics*");

  MyHtml h;
  h.SetProductName("MitRoot");

  TString cb(gSystem->ExpandPathName("$CMSSW_BASE"));
  h.SetInputDir("$CMSSW_BASE/src:$ROOTSYS/include");
  h.SetIncludePath(Form("%s/src/",cb.Data()));
  h.SetClassDocTag("//------------------------------------------------------------");
  h.SetViewCVS("http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/");
  h.SetRootURL("http://root.cern.ch/root/html522");
  h.RunAll(0,"(mithep::|TAM)");
}
