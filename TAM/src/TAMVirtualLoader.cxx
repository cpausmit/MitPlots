//
// $Id: TAMVirtualLoader.cxx 2272 2006-01-08 17:16:44Z loizides $
//

#include "TAMVirtualLoader.h"


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
