// Includes the corresponding header file, other necessary Geant4 classes, and the primary generator action class
#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"

// Constructor: initializes member variables and creates new UI commands and a new directory for them
PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
  :Action(Gun)
{
  // Creates a new directory for CRY commands
  CRYDir = new G4UIdirectory("/CRY/");
  CRYDir->SetGuidance("CRY initialization");

  // Creates a command to enter the CRY settings file name
  FileCmd = new G4UIcmdWithAString("/CRY/file",this);
  FileCmd->SetGuidance("This reads the CRY definition from a file");
  FileCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Creates a command to enter CRY parameters directly
  InputCmd = new G4UIcmdWithAString("/CRY/input",this);
  InputCmd->SetGuidance("CRY input lines");
  InputCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  // Creates a command to update CRY settings
  UpdateCmd = new G4UIcmdWithoutParameter("/CRY/update",this);
  UpdateCmd->SetGuidance("Update CRY definition. This command MUST be applied before \"beamOn\" if you changed the CRY definition.");
  UpdateCmd->AvailableForStates(G4State_Idle);

  // Initializes the string for storing entered parameters
  MessInput = new std::string;
}

// Destructor: deletes created UI commands and the directory
PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete CRYDir;
  delete InputCmd;
  delete UpdateCmd;
  delete FileCmd;
}

// Updates the CRY definition or the parameters according to the command issued
void PrimaryGeneratorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{
  // If input parameters were given, they are added to the existing ones
  if( command == InputCmd )
   {
     Action->InputCRY();
     (*MessInput).append(newValue);
     (*MessInput).append(" ");
   }
  // If an update command was given, the CRY definition is updated
  if( command == UpdateCmd )
   {
     Action->UpdateCRY(MessInput);
     *MessInput = "";
   }
}
