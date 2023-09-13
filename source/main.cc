#include "G4RunManager.hh"             // Include the Geant4 run manager header
#include "G4UImanager.hh"              // Include the Geant4 user interface manager header
//#include "QGSP_BERT.hh"                // Include the physics list used for the simulation
#include "MyPhysicList.hh"
#include "G4VisExecutive.hh"           // Include the Geant4 visualization manager header
#include "G4UIExecutive.hh"            // Include the Geant4 user interface executive header
#include "DetectorConstruction.hh"     // Include the detector construction header
#include "PrimaryGeneratorAction.hh"   // Include the primary generator action header
#include "RunAction.hh"                // Include the run action header
#include "EventAction.hh"              // Include the event action header
#include "MySteppingAction.hh"         // Include the stepping action header
#include <chrono>                      // Include the standard chrono library for handling time

int main (int argc,char** argv)
{
    // Create and set the random number generation engine
    CLHEP::RanecuEngine * engine = new CLHEP::RanecuEngine();

    // Get the current time in milliseconds since the epoch
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long long seed = value.count();

    // Initialize the random number generator with the current time
    engine->setSeed(seed);

    // Set the random number generation engine for Geant4
    G4Random::setTheEngine(engine);

    // Create the Geant4 run manager
    G4RunManager* theRunManager = new G4RunManager;

    // Set the mandatory initialization classes
    theRunManager->SetUserInitialization(new DetectorConstruction()); // Construct the geometry
//    G4VModularPhysicsList* physicsList = new QGSP_BERT; // Use the QGSP_BERT physics list
    G4VModularPhysicsList* physicsList = new MyPhysicList(); // Use the custom physics list
    theRunManager->SetUserInitialization(physicsList); // Set the physics list
    theRunManager->SetUserAction(new PrimaryGeneratorAction("")); // Set the primary particle generation
    theRunManager->Initialize(); // Initialize the run manager

    // Register the stepping action
    MySteppingAction* steppingAction = new MySteppingAction();

    // Create a new run action and event action
    RunAction* runAction = new RunAction(steppingAction); // Create a new run action
    theRunManager->SetUserAction(runAction); // Set the run action
    EventAction* eventAction = new EventAction(); // Create a new event action
    theRunManager->SetUserAction(eventAction); // Set the event action

    theRunManager->SetUserAction(steppingAction);

    // Create the Geant4 visualization manager and initialize it
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get a pointer to the Geant4 user interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if ( argc == 1 ) { // If no command line arguments, start an interactive session
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute vis.mac"); // Execute the vis.mac macro
        ui->SessionStart(); // Start the UI session
        delete ui;
    }
    else { // If command line arguments are provided, execute a macro
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName); // Execute the macro
    }

    delete visManager; // Delete the visualization manager
    delete theRunManager; // Delete the run manager
    delete steppingAction; // Delete the stepping action pointer
    return 0;
}
