#include "MitAna/DataTree/interface/BasePartAction.h"
#include "MitAna/DataTree/interface/BasePart.h"
#include "MitAna/DataTree/interface/DecayPart.h"
#include "MitAna/DataTree/interface/StablePart.h"
#include <iostream>

using namespace mithep;

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
BasePartAction::BasePartAction(ActionType AType) :
  actionType_(AType),
  level_     (0)
{
}

//------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------
BasePartAction::~BasePartAction()
{
}

//------------------------------------------------------------------------------
// Handle Generic Particles
//------------------------------------------------------------------------------
void BasePartAction::doAction(const BasePart *part)
{
  // Just override me
}
