#include "MitAna/DataTree/interface/MCRunInfoFull.h"

ClassImp(mithep::MCRunInfoFull)

mithep::MCRunInfoFull::MCRunInfoFull() :
  MCRunInfo(),
  fInternalXSec(-1.),
  fInternalXSecErr(0.),
  fExternalXSecLO(-1.),
  fExternalXSecLOErr(0.),
  fExternalXSecNLO(-1.),
  fExternalXSecNLOErr(0.),
  fHasLHEInfo(false),
  fBeamEnergy(0.),
  fPdfGroup(0),
  fPdfId(0),
  fWeightMode(0),
  fNProcesses(0),
  fProcessesSize(16),
  fProcessXSec(new Double_t[fProcessesSize]),
  fProcessXSecError(new Double_t[fProcessesSize]),
  fProcessXSecMax(new Double_t[fProcessesSize]),
  fProcessId(new Int_t[fProcessesSize]),
  fNHeaderBlocks(0),
  fHeaderBlocksSize(16),
  fHeaderBlockTag(new TString[fHeaderBlocksSize]),
  fHeaderBlockContent(new TString[fHeaderBlocksSize]),
  fComments()
{
}

mithep::MCRunInfoFull::~MCRunInfoFull()
{
  delete [] fProcessXSec;
  delete [] fProcessXSecError;
  delete [] fProcessXSecMax;
  delete [] fProcessId;
  delete [] fHeaderBlockTag;
  delete [] fHeaderBlockContent;
}

void
mithep::MCRunInfoFull::SetNProcesses(UInt_t n)
{
  if (n > fProcessesSize) {
    fProcessesSize = n * 2;

    auto tmp1 = new Double_t[fProcessesSize];
    std::copy(fProcessXSec, fProcessXSec + fNProcesses, tmp1);
    delete [] fProcessXSec;
    fProcessXSec = tmp1;

    auto tmp2 = new Double_t[fProcessesSize];
    std::copy(fProcessXSecError, fProcessXSecError + fNProcesses, tmp2);
    delete [] fProcessXSecError;
    fProcessXSecError = tmp2;
    
    auto tmp3 = new Double_t[fProcessesSize];
    std::copy(fProcessXSecMax, fProcessXSecMax + fNProcesses, tmp3);
    delete [] fProcessXSecMax;
    fProcessXSecMax = tmp3;

    auto tmp4 = new Int_t[fProcessesSize];
    std::copy(fProcessId, fProcessId + fNProcesses, tmp4);
    delete [] fProcessId;
    fProcessId = tmp4;
  }

  fNProcesses = n;
}

void
mithep::MCRunInfoFull::SetNHeaderBlocks(UInt_t n)
{
  if (n > fHeaderBlocksSize) {
    fHeaderBlocksSize = n * 2;

    auto tmp1 = new TString[fHeaderBlocksSize];
    std::copy(fHeaderBlockTag, fHeaderBlockTag + fNHeaderBlocks, tmp1);
    delete [] fHeaderBlockTag;
    fHeaderBlockTag = tmp1;
    
    auto tmp2 = new TString[fHeaderBlocksSize];
    std::copy(fHeaderBlockContent, fHeaderBlockContent + fNHeaderBlocks, tmp2);
    delete [] fHeaderBlockContent;
    fHeaderBlockContent = tmp2;
  }

  fNHeaderBlocks = n;
}

void
mithep::MCRunInfoFull::Streamer(TBuffer& buffer)
{
  if (buffer.IsReading()) {
    buffer.ReadClassBuffer(mithep::MCRunInfoFull::Class(), this);

    fProcessesSize = fNProcesses;
    fHeaderBlocksSize = fNHeaderBlocks;
    fWeightGroupsSize = fNWeightGroups;
  }
  else
    buffer.WriteClassBuffer(mithep::MCRunInfoFull::Class(), this);
}
