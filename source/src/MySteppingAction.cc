#include "MySteppingAction.hh" // Include the header file for this class
#include "G4SystemOfUnits.hh"
#include "G4Track.hh" // Include Geant4 track class
#include "G4ParticleDefinition.hh" // Include Geant4 particle definition class
#include "G4Electron.hh" // Include Geant4 electron class
#include "G4MuonMinus.hh" // Include Geant4 muon minus class
#include "G4MuonPlus.hh" // Include Geant4 muon plus class
#include <fstream> // Include standard file stream for file operations

MySteppingAction::MySteppingAction()
: G4UserSteppingAction(),
  fSecondaryElectrons(0), // Initialize secondary electrons counter to 0
  fIonizations(0), // Initialize ionizations counter to 0
  fMuonCounter(0) // Initialize muon counter to 0
{}

MySteppingAction::~MySteppingAction() // Destructor
{
  WriteSummaryToFile(); // Write summary to file at the end of the simulation
}

void MySteppingAction::UserSteppingAction(const G4Step* step) // Main function called at every step
{
  G4Track* track = step->GetTrack(); // Get the current track
  G4ParticleDefinition* particle = track->GetDefinition(); // Get the particle definition
  G4int trackID = track->GetTrackID(); // Get the track ID

  // Check if the current particle is a muon
  if (particle == G4MuonMinus::Definition() || particle == G4MuonPlus::Definition())
  {
    if (track->GetCurrentStepNumber() == 1) // If this is the first step of the muon
    {
      fMuonCounter++; // Increment muon counter
      fSecondaryElectronsPerMuon[trackID] = 0; // Initialize secondary electrons counter for this muon
      fIonizationsPerMuon[trackID] = 0; // Initialize ionizations counter for this muon
    }
    WriteMuonToFile(track); // Write muon information to file
  }

  // Check if the current particle is a secondary electron
  if(track->GetParentID() > 0 && particle == G4Electron::Definition())
  {
    fSecondaryElectronsPerMuon[track->GetParentID()]++; // Increment secondary electrons counter for the parent muon
    fIonizationsPerMuon[track->GetParentID()]++; // Increment ionizations counter for the parent muon
    fIonizations++; // Increment total ionizations counter
    WriteSecondaryElectronToFile(track, fIonizations); // Write secondary electron information to file
  }

  // Write ionizations to file
  WriteIonizationToFile(fIonizations);

  // Write muon summary to file at the end of the muon's track
  if (track->GetTrackStatus() == fStopAndKill && (particle == G4MuonMinus::Definition() || particle == G4MuonPlus::Definition()))
  {
    WriteMuonSummaryToFile(trackID, fSecondaryElectronsPerMuon[trackID], fIonizationsPerMuon[trackID]);
  }

  // Write muon details to file at the end of the muon's track
  if (track->GetTrackStatus() == fStopAndKill && (particle == G4MuonMinus::Definition() || particle == G4MuonPlus::Definition()))
  {
    std::ofstream csvFile;
    csvFile.open("muon_details.csv", std::ios::app);

    if (!muonDetailsHeaderWritten) {
      csvFile << "Muon Number,Charge,Kinetic Energy (MeV),Ionizations,Secondary Electrons\n";
      muonDetailsHeaderWritten = true;
    }

    csvFile << fMuonCounter << ","
            << track->GetDynamicParticle()->GetCharge() << ","
            << track->GetKineticEnergy()/MeV << ","
            << fIonizationsPerMuon[track->GetTrackID()] << ","
            << fSecondaryElectronsPerMuon[track->GetTrackID()] << "\n";

    csvFile.close();
  }

}

void MySteppingAction::WriteMuonSummaryToFile(G4int trackID, G4int secondaryElectrons, G4int ionizations)
{
  std::ofstream csvFile; // Declare output file stream
  csvFile.open("muon_summary.csv", std::ios::app); // Open file in append mode

  if (!muonSummaryHeaderWritten) { // Write header if not already written
    csvFile << "Muon Number,Secondary Electrons,Ionizations\n";
    muonSummaryHeaderWritten = true;
  }

  csvFile << fMuonCounter << "," // Write muon number
          << secondaryElectrons << "," // Write secondary electrons for this muon
          << ionizations << "\n"; // Write ionizations for this muon

  csvFile.close(); // Close file
}

void MySteppingAction::WriteMuonToFile(const G4Track* track) // Function to write muon information to file
{
  std::ofstream csvFile; // Declare output file stream
  csvFile.open("muons.csv", std::ios::app); // Open file in append mode

  if (!muonHeaderWritten) { // Write header if not already written
    csvFile << "Muon Number,Track ID,Kinetic Energy (MeV),Position X (mm),Position Y (mm),Position Z (mm)\n";
    muonHeaderWritten = true;
  }

  // Write muon information to file
  csvFile << fMuonCounter << "," // Write muon number
          << track->GetTrackID() << ","
          << track->GetKineticEnergy()/MeV << ","
          << track->GetPosition().x() << ","
          << track->GetPosition().y() << ","
          << track->GetPosition().z() << "\n";

  csvFile.close(); // Close file
}

void MySteppingAction::WriteSecondaryElectronToFile(const G4Track* track, G4int ionizations) // Function to write secondary electron information to file
{
  std::ofstream csvFile; // Declare output file stream
  csvFile.open("secondary_electrons.csv", std::ios::app); // Open file in append mode

  if (!electronHeaderWritten) { // Write header if not already written
    csvFile << "Track ID,Parent ID,Kinetic Energy (MeV),Ionizations\n";
    electronHeaderWritten = true;
  }

  // Write secondary electron information to file
  csvFile << track->GetTrackID() << ","
          << track->GetParentID() << ","
          << track->GetKineticEnergy()/MeV << ","
          << ionizations << "\n";

  csvFile.close(); // Close file
}

void MySteppingAction::WriteIonizationToFile(G4int ionizations) // Function to write ionizations to file
{
  std::ofstream csvFile; // Declare output file stream
  csvFile.open("ionizations.csv", std::ios::app); // Open file in append mode

  if (!ionizationHeaderWritten) { // Write header if not already written
    csvFile << "Ionizations\n";

    ionizationHeaderWritten = true;
  }

  csvFile << fIonizations << "\n"; // Write ionizations to file

  csvFile.close(); // Close file
}

void MySteppingAction::WriteSummaryToFile()
{
  std::ofstream csvFile;
  csvFile.open("summary.csv");

  csvFile << "Muons," << fMuonCounter << "\n"
          << "Secondary Electrons," << fSecondaryElectrons << "\n"
          << "Ionizations," << fIonizations << "\n";

  csvFile.close();
}

