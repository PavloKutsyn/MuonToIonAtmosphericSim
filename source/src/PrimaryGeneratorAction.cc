// Including the necessary classes for primary generator action, detector construction, event generation, particle definition, etc.
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ios.hh"
#include <iomanip>
#include <random>

// Using the standard namespace.
using namespace std;

// Definition of the constructor, which takes an input file name as an argument.
PrimaryGeneratorAction::PrimaryGeneratorAction(const char *inputfile)
:G4VUserPrimaryGeneratorAction()
{
    // Define a particle gun.
    particleGun = new G4ParticleGun();

    // Open and read the CRY input file.
    std::ifstream inputFile;
    inputFile.open(inputfile,std::ios::in);
    char buffer[1000];

    // If the file fails to open, print an error message and set the input state to -1.
    if (inputFile.fail()) {
      if( *inputfile !=0)
        G4cout << "PrimaryGeneratorAction: Failed to open CRY input file= " << inputfile << G4endl;
      InputState=-1;
    } else {
      // If the file opens successfully, read the file and setup the CRY generator.
      std::string setupString("");
      while ( !inputFile.getline(buffer,1000).eof()) {
        setupString.append(buffer);
        setupString.append(" ");
      }

      // Create the CRY setup and generator.
      CRYSetup *setup=new CRYSetup(setupString,"../data");
      gen = new CRYGenerator(setup);

      // Set the random number generator for the CRY setup.
      RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
      setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
      InputState=0;
    }

    // Create a vector to store the CRY particles.
    vect=new std::vector<CRYParticle*>;

    // Get the particle table from Geant4.
    particleTable = G4ParticleTable::GetParticleTable();

    // Create a messenger for this class.
    gunMessenger = new PrimaryGeneratorMessenger(this);
}

// Method to set the input state to 1, indicating that CRY input is active.
void PrimaryGeneratorAction::InputCRY()
{
  InputState=1;
}

// Method to update the CRY generator based on a new setup string.
void PrimaryGeneratorAction::UpdateCRY(std::string* MessInput)
{
  // Create the new CRY setup and generator.
  CRYSetup *setup=new CRYSetup(*MessInput,"/home/pavlo/GEANT4_ROOT/cry_v1.7/data");
  gen = new CRYGenerator(setup);

  // Set the random number generator for the new CRY setup.
  RNGWrapper<CLHEP::HepRandomEngine>::set(CLHEP::HepRandom::getTheEngine(),&CLHEP::HepRandomEngine::flat);
  setup->setRandomFunction(RNGWrapper<CLHEP::HepRandomEngine>::rng);
  InputState=0;
}

// Definition of the destructor, which currently does nothing.
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
}

// Method to generate primary particles for each event in the Geant4 simulation.
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // If the CRY library was not successfully initialized, abort the run and throw an exception.
  if (InputState != 0) {
    G4String* str = new G4String("CRY library was not successfully initialized");

    G4Exception("PrimaryGeneratorAction", "1",
                RunMustBeAborted, *str);
  }

  // Define a string to hold the particle name.
  G4String particleName;

  // Clear the vector holding the CRY particles.
  vect->clear();

  // Generate the CRY event.
  gen->genEvent(vect);

  // For each particle in the event, set the particle properties in the particle gun and generate a primary vertex.
  for ( unsigned j=0; j<vect->size(); j++) {
    // Get the particle name.
    particleName=CRYUtils::partName((*vect)[j]->id());

    // Print the particle name and charge.
    cout << "  "          << particleName << " "
         << "charge="      << (*vect)[j]->charge() << " "
      << endl;

    // Set the particle definition, energy, position, momentum direction, and time in the particle gun.
    particleGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));
//    particleGun->SetParticleEnergy ((*vect)[j]->ke()*MeV);
    particleGun->SetParticleEnergy(100*MeV);
    particleGun->SetParticlePosition(G4ThreeVector(0.*cm, 0.*cm, 25*cm));
//    particleGun->SetParticleMomentumDirection(G4ThreeVector((*vect)[j]->u(), (*vect)[j]->v(), (*vect)[j]->w()));
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1)); // particle initial momentums
    particleGun->SetParticleTime((*vect)[j]->t());

    // Generate a primary vertex for the event.
    particleGun->GeneratePrimaryVertex(anEvent);

    // Delete the particle.
    delete (*vect)[j];
  }
}



//void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
//{
//    if (InputState != 0) {
//      G4String* str = new G4String("CRY library was not successfully initialized");

//      G4Exception("PrimaryGeneratorAction", "1",
//                  RunMustBeAborted, *str);
//    }
//    G4String particleName;
//    vect->clear();
//    gen->genEvent(vect);

//    for ( unsigned j=0; j<vect->size(); j++) {
//      particleName=CRYUtils::partName((*vect)[j]->id());

//      // applying CRY source values to partical generator
//      particleGun->SetParticleDefinition(particleTable->FindParticle((*vect)[j]->PDGid()));       // particle type
//      particleGun->SetParticleEnergy(1.5*GeV);                                       // particle energy
//      particleGun->SetParticlePosition(G4ThreeVector((*vect)[j]->x()*m, (*vect)[j]->y()*m, (*vect)[j]->z()*m)); // particle initial points 100*cm
//      particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1)); // particle initial momentums
//      particleGun->SetParticleTime((*vect)[j]->t()); // particle time
//      particleGun->GeneratePrimaryVertex(anEvent); //method of primary generator to make primaries
//      delete (*vect)[j];
//    }

//}
