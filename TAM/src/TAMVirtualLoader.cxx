//
// $Id: TAMVirtualLoader.cxx,v 1.1 2008/05/27 19:13:21 loizides Exp $
//

#include "MitAna/TAM/interface/TAMVirtualLoader.h"


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TAMVirtualLoader                                                     //
//                                                                      //
// Abstract base class for introducing plugins (data loader) into TAM.  //
// Every TAM plugin loader needs to derive from this class.             //
//                                                                      //
// Author : Maarten Ballintijn	   12/06/2005                           //
//	    Constantin Loizides    12/22/2005                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

ClassImp(TAMVirtualLoader)


//______________________________________________________________________________
TAMVirtualLoader::TAMVirtualLoader()
{
   // Default constructor.
}
