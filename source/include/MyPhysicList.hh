// MyPhysicList.hh
#include "G4VModularPhysicsList.hh"
#include "G4EmLivermorePhysics.hh"

class MyPhysicList : public G4VModularPhysicsList {
public:
  MyPhysicList();
  virtual ~MyPhysicList();
};