/*In its role as a messenger, the class contains a key function,
 *  SetNewValue, which updates the CRY definition or
 *  the parameters based on the command issued by the user.
 *  Thus, the PrimaryGeneratorMessenger class plays a pivotal role
 *  in enabling user interactivity and flexibility in controlling
 *  the simulation parameters for the CRY generator in a Geant4 application.
*/

// Inclusion guard to prevent the header from being included more than once
#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

// Includes necessary Geant4 user interface classes and global constants
#include "G4UImessenger.hh"
#include "globals.hh"

// Forward declarations of classes to be used in this file
class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

// Class for setting macro command for CRY generator values
class PrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    // Constructor: accepts a pointer to `PrimaryGeneratorAction`
    PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
    // Destructor
   ~PrimaryGeneratorMessenger();

    // Method for assigning a new value to a UI command
    void SetNewValue(G4UIcommand*, G4String);

  private:
    // Pointer to an instance of `PrimaryGeneratorAction` controlling the particle generation
    PrimaryGeneratorAction*      Action;
    // Pointer to the directory for CRY generator commands
    G4UIdirectory*               CRYDir;
    // Command for entering the CRY settings file name
    G4UIcmdWithAString*          FileCmd;
    // Command for entering CRY parameters via the command line
    G4UIcmdWithAString*          InputCmd;
    // Command to update CRY parameters
    G4UIcmdWithoutParameter*     UpdateCmd;
    // String storing entered parameters until they are updated
    std::string* MessInput;
};

// End of the inclusion guard
#endif
