/*In essence, the PrimaryGeneratorAction class is an essential
 *  component of any Geant4 simulation, responsible for
 *  defining the initial state of each event in the simulation. Its behavior can be customized to meet the specific requirements of the simulation being performed.
*/

// The include guard prevents the header file from being included more than once in the same file.
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

// Including necessary Geant4 classes for primary particle generation and particle guns.
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

// Including necessary global definitions.
#include "globals.hh"

// Including necessary classes and functions from the CRY library for cosmic-ray generation.
#include "CRYSetup.h"
#include "CRYGenerator.h"
#include "CRYParticle.h"
#include "CRYUtils.h"

// Including necessary classes for using vectors and random number generators.
#include "vector"
#include "RNGWrapper.hh"

// Including necessary Geant4 classes for three-dimensional vectors, data vectors, particle tables, and randomization.
#include "G4ThreeVector.hh"
#include "G4DataVector.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

// Including the class that defines the interface for changing primary generator parameters.
#include "PrimaryGeneratorMessenger.hh"

// Forward declaring the classes to resolve dependencies without including the complete header files.
class G4GeneralParticleSource;
class G4Event;
class DetectorConstruction;

// Declaration of the PrimaryGeneratorAction class, which is responsible for defining primary particles in Geant4 simulations.
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    // Declaration of the constructor, which takes a filename as a parameter.
    PrimaryGeneratorAction(const char * filename);
    // Declaration of the destructor.
    ~PrimaryGeneratorAction();

  public:
    // Declaration of the GeneratePrimaries function, which is responsible for generating primary particles for each event.
    virtual void GeneratePrimaries(G4Event* anEvent);
    // Declaration of the InputCRY function, which is responsible for activating input command features in CRY.
    void InputCRY();
    // Declaration of the UpdateCRY function, which takes a message input to update the parameters of the CRY generator.
    void UpdateCRY(std::string* MessInput);


  private:

    // Declaration of a pointer to a DetectorConstruction object, which defines the geometry of the detectors used in the simulation.
    DetectorConstruction* fDetector;
    // Declaration of a vector to store pointers to CRYParticle objects.
    std::vector<CRYParticle*> *vect;
    // Declaration of a pointer to a G4ParticleTable object, which is a table of all known particles that can be used in the simulation.
    G4ParticleTable* particleTable;
    // Declaration of a pointer to a G4ParticleGun object, which is used to generate primary particles.
    G4ParticleGun* particleGun;
    // Declaration of a pointer to a CRYGenerator object, which is used to generate particles based on the CRY library.
    CRYGenerator* gen;
    // Declaration of an integer to store the state of the CRY input.
    G4int InputState;
    // Declaration of a pointer to a PrimaryGeneratorMessenger object, which controls the commands related to the CRY generator.
    PrimaryGeneratorMessenger* gunMessenger;

};

// Closing the include guard.
#endif
