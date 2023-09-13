
#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fAtmosphereLogical(nullptr)
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Define Materials
    G4NistManager* nist = G4NistManager::Instance();
//    G4Material* air_nist = nist->FindOrBuildMaterial("G4_AIR");//("G4_AIR");
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic"); // New material for the world

    // Define elements
    G4Element* N  = nist->FindOrBuildElement("N");
    G4Element* O  = nist->FindOrBuildElement("O");

    // Define Air
    G4Material* air = new G4Material("Air", 1.290*mg/cm3, 2, kStateGas, 293.15*kelvin, 1.0*atmosphere);

    air->AddElement(N, 75.5*perCent);
    air->AddElement(O, 24.5*perCent);



    // Define volumes
    G4double size = 50*cm/2;  // Size of the box is 1m x 1m x 1m

    // World
    G4Box* worldBox = new G4Box("World", size, size, size);
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, world_mat, "World"); // Use new material
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "World", 0, false, 0);

//    // Atmosphere cube
//    G4double atmosphereSize = size / 2.0; // Change this to suit the size of the atmosphere cube you want
//    G4Box* atmosphereBox = new G4Box("Atmosphere", atmosphereSize, atmosphereSize, atmosphereSize);
//    fAtmosphereLogical = new G4LogicalVolume(atmosphereBox, air, "Atmosphere");
//    new G4PVPlacement(0, G4ThreeVector(), fAtmosphereLogical, "Atmosphere", worldLog, false, 0);

    // Atmosphere cylinder
    G4double cylinderRadius = 3.5*cm / 2.0; // The radius of the cylinder is half the diameter
    G4double cylinderLength = 50*cm; // Length of the cylinder

    G4Tubs* atmosphereCylinder = new G4Tubs("Atmosphere", 0, cylinderRadius, cylinderLength / 2.0, 0.*deg, 360.*deg); // Cylinder dimensions and angles
    fAtmosphereLogical = new G4LogicalVolume(atmosphereCylinder, air, "Atmosphere");
    new G4PVPlacement(0, G4ThreeVector(), fAtmosphereLogical, "Atmosphere", worldLog, false, 0);


    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    return worldPhys;
}
