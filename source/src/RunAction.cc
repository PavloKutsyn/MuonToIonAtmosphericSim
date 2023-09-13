#include "RunAction.hh"  // Include the RunAction header file
#include "G4Run.hh"      // Include the Geant4 Run header file
#include "G4SystemOfUnits.hh"  // Include the Geant4 system of units header file
#include "G4UnitsTable.hh"     // Include the Geant4 units table header file

// Constructor for the RunAction class
// It takes a pointer to an object of MySteppingAction as input
// This constructor initializes the base G4UserRunAction class, and the private data members fTotalIonization and fSteppingAction
RunAction::RunAction(MySteppingAction* steppingAction)
    : G4UserRunAction(),
    fTotalIonization(0.),
    fSteppingAction(steppingAction) // initialize the new member variable
{}

// Destructor for the RunAction class
RunAction::~RunAction()
{}

// This method is called at the beginning of each run
// It resets the total ionization to zero
void RunAction::BeginOfRunAction(const G4Run*)
{
    // Reset total ionization
    fTotalIonization = 0.;
}

// This method is called at the end of each run
// It prints the total ionization of the run
void RunAction::EndOfRunAction(const G4Run*)
{
    // Print total ionization
    G4cout << "Total Ionization: "
           << G4BestUnit(fTotalIonization, "Energy")
           << G4endl;
}
