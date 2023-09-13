#ifndef MYSTEPPINGACTION_HH
#define MYSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include <map>

class MySteppingAction : public G4UserSteppingAction
{
public:
  MySteppingAction();
  virtual ~MySteppingAction();

  virtual void UserSteppingAction(const G4Step* step);

private:
  void WriteSummaryToFile();
  void WriteMuonToFile(const G4Track* track);
  void WriteSecondaryElectronToFile(const G4Track* track, G4int ionizations);
  void WriteIonizationToFile(G4int ionizations);
  void WriteMuonSummaryToFile(G4int trackID, G4int secondaryElectrons, G4int ionizations);

  G4int fSecondaryElectrons;
  G4int fIonizations;
  G4int fMuonCounter;
  std::map<G4int, G4int> fSecondaryElectronsPerMuon;
  std::map<G4int, G4int> fIonizationsPerMuon;

  bool muonDetailsHeaderWritten = false;
  bool muonHeaderWritten = false;
  bool electronHeaderWritten = false;
  bool ionizationHeaderWritten = false;
  bool muonSummaryHeaderWritten = false;

};

#endif
