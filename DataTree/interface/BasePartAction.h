//--------------------------------------------------------------------------------------------------
// Description: Class BasePartAction
// ------------
//
// This abstract base class has been created to help people with recursive descent of a Particle
// Decay Graph. Instead of writing a recursive subroutine or member function, define a subclass of
// this class. The subclass should provide a handler for both decay particles and stable particles.
//
// Recursion occurs when a client invokes:
//
//    DecayPart *particle;
//    particle = ....
//    particle->doAction(Action);
//
// Then, the handle functions are called once per particle as the action is passed up or down the
// Particle Decay Graph. A non-recursive action has also been implemented.
//
// Author List: Ch.Paus
//--------------------------------------------------------------------------------------------------

#ifndef _mithep_BASEPARTACTION_H_
#define _mithep_BASEPARTACTION_H_

#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep
{
  class BasePart;
  class DecayPart;
  class StablePart;

  class BasePartAction
  {
  public:
    // Define the type of the action
    enum         ActionType { BottomUp, TopDown, NonRecursive };

    // Constructor
    BasePartAction(ActionType aType);

    // Destructor
    virtual ~BasePartAction();

    // Handle Generic  Particles
    virtual void doAction(const BasePart* part);

    // Handle Decaying Particles
    virtual void doAction(const DecayPart* part) = 0;

    // Handle Stable   Particles
    virtual void doAction(const StablePart* part) = 0;

    // Recursion level
    void         incLevel     ()       { level_++; }
    void         decLevel     ()       { level_--; }
    int          getLevel     () const { return level_; }
    ActionType   getActionType() const { return actionType_; }

  private:
    // What type of action
    ActionType   actionType_;
    // Remember how deep we are in there
    int          level_;
  };
}
#endif
