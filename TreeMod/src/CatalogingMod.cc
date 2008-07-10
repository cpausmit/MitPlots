// $Id: CatalogingMod.cc,v 1.1 2008/07/07 16:41:54 paus Exp $

#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/CatalogingMod.h"

using namespace mithep;

ClassImp(mithep::CatalogingMod)

//--------------------------------------------------------------------------------------------------
CatalogingMod::CatalogingMod(const char *name, const char *title) : 
  BaseMod        (name,title),
  fMetaDataString("==MetaData=="),
  fNFileSet      (0),
  fLastLumiSec   (999999999),
  fMetaData      (0,0,999999999,0,0,0)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::SlaveBegin()
{
  // Print out cataloging module message.

  if (gDebugLevel > 0)
    cout << " ============================\n"
	 << " CatalogingMod::SlaveBegin -- Creating MetaInformation for the coming events\n"
	 << " ============================\n";
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::BeginRun()
{
  // Reset the last luminosity section.

  fLastLumiSec = 999999999;
  fMetaData.AddRun(GetEventHeader()->RunNum(),GetEventHeader()->LumiSec());
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::Process()
{
  // Add new event and update luminosity section counter.

  // count all events
  fMetaData.AddEvent();
  // count luminosity sections
  if (fLastLumiSec != GetEventHeader()->LumiSec())
    fMetaData.AddLumiSec(GetEventHeader()->RunNum(),GetEventHeader()->LumiSec());
}

//--------------------------------------------------------------------------------------------------
void CatalogingMod::SlaveTerminate()
{
  // Print cataloging module message.

  if (gDebugLevel > 0)
    cout << "\n"
	 << " ============================----\n"
	 << " CatalogingMod::SlaveTerminate -- MetaInformation for analyzed events\n"
	 << " ================================\n"
	 << " Number of lumi sections: " << fMetaData.NLumiSecs() << endl
	 << " Number of events       : " << fMetaData.NEvents()   << endl
	 << " min(Run,LumiSec)       : ("
	 << fMetaData.MinRun() << "," << fMetaData.MinLumiSecInMinRun() << ")\n"
	 << " max(Run,LumiSec)       : ("
	 << fMetaData.MaxRun() << "," << fMetaData.MaxLumiSecInMaxRun() << ")\n\n";
  
  printf("%04d %-60s %9d %9d %9d %6d %9d %6d\n",
	 fNFileSet                     ,
	 fMetaDataString.Data        (),
	 fMetaData.NLumiSecs         (),
	 fMetaData.NEvents           (),
	 fMetaData.MinRun            (),
	 fMetaData.MinLumiSecInMinRun(),
	 fMetaData.MaxRun            (),
	 fMetaData.MaxLumiSecInMaxRun() );

  if (gDebugLevel > 0)
    cout << "\n";
}
