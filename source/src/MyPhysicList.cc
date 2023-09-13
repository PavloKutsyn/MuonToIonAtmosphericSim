// MyPhysicList.cc
#include "MyPhysicList.hh"

MyPhysicList::MyPhysicList() : G4VModularPhysicsList() {
  RegisterPhysics(new G4EmLivermorePhysics());
}

MyPhysicList::~MyPhysicList() {}