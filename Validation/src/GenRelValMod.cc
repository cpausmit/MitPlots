// $Id: GenRelValMod.cc,v 1.1 2008/07/10 14:56:27 loizides Exp $

#include "MitAna/Validation/interface/GenRelValMod.h"
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::GenRelValMod)

//--------------------------------------------------------------------------------------------------
GenRelValMod::GenRelValMod(const char *name, const char *title) :
  BaseMod(name,title),
  fGenPartName(Names::gkGenPartBrn),
  fParticles(0),
  ofile(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void GenRelValMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual analysis. Here, we typically
  // initialize histograms and other analysis objects and request branches. For this module, we
  // request a branch of the MitTree and open a text file for writing.

  ReqBranch(fGenPartName,fParticles);

  ofile = new std::ofstream("macro_output.txt");
  if (ofile->bad()) {
    SendError(kAbortAnalysis, "SlaveBegin", "Can not open output file.");
  }
}

//--------------------------------------------------------------------------------------------------
void GenRelValMod::Process()
{
  // Process entries of the tree. For this module, we just load the branch and fill the histograms.

  LoadBranch(fGenPartName);

  for (UInt_t i=0; i<fParticles->GetEntries(); ++i) {
    GenParticle* p = fParticles->At(i);
    int I     = i+1;                                         // Particle index (starts at 1)
    int KF    = p->GetPdgId();                               // Pdg code
    double p_x = p->Px(); if (fabs(p_x)<0.0005) p_x = 0.;    // Momenta.  We only compare the
    double p_y = p->Py(); if (fabs(p_y)<0.0005) p_y = 0.;    //  first 3 digits after the
    double p_z = p->Pz(); if (fabs(p_z)<0.0005) p_z = 0.;    //  decimal.
    double E   = p->E();  if (fabs(E  )<0.0005) E   = 0.;    // Energy
    int mind=0;
    if(p->HasMother()) {
      const GenParticle *mother = p->GetMother();
      if(mother) {
        for (UInt_t j=0; j<fParticles->GetEntries(); ++j) {
          const  GenParticle *test = fParticles->At(j);
          if(test==mother) {
            mind=j+1;
            // hack to overcome ambiguity
            if(mind==5 && I==7 || I==8) mind=0;
            break;
          }
        }
      }
    }
    char buf[1024];
    sprintf(buf,"%5i%5i%5i%9.3f%9.3f%9.3f%9.3f\n",I,KF,mind,p_x,p_y,p_z,E);
    *ofile<<buf;
  }
}

//--------------------------------------------------------------------------------------------------
void GenRelValMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the analysis. For this module, we close
  // the text file.

  ofile->close();
  delete ofile; 
  ofile=0;
}
