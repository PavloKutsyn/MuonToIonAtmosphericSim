/*The overall purpose of this class is to customize the actions taken at the beginning and end of
 *  a simulation run, allowing users to track and respond to events within the simulation in
 *  a flexible way. For example, one might use this class to accumulate certain statistics over
 *  the course of many simulation steps, and then summarize or output these statistics at the
 *  end of the run.*/

#ifndef RunAction_h  // Ensure that the header file is included only once in a single compilation
#define RunAction_h 1  // Define a macro

#include "G4UserRunAction.hh"  // Include Geant4 User Run Action header file
#include "MySteppingAction.hh"  // Include the custom MySteppingAction header file
#include "globals.hh"  // Include the global variables header file

// Declare the RunAction class that inherits from the G4UserRunAction class
class RunAction : public G4UserRunAction
{
  public:
    // Declare the constructor that takes a pointer to MySteppingAction object as argument
    RunAction(MySteppingAction* steppingAction);

    // Declare the destructor
    virtual ~RunAction();

    // Declare the BeginOfRunAction method which is called at the beginning of each run
    // It takes a constant pointer to a G4Run object as argument
    virtual void BeginOfRunAction(const G4Run*);

    // Declare the EndOfRunAction method which is called at the end of each run
    // It also takes a constant pointer to a G4Run object as argument
    virtual void EndOfRunAction(const G4Run*);

  private:
    // Declare a private member variable for total ionization
    G4double fTotalIonization;

    // Declare a private member variable for the stepping action
    MySteppingAction* fSteppingAction;
};

#endif
