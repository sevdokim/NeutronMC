
//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file Ex01MCApplication.cxx
/// \brief Implementation of the Ex01MCApplication class
///
/// Geant4 ExampleN01 adapted to Virtual Monte Carlo \n
///
/// \date 05/04/2002
/// \author I. Hrivnacova; IPN, Orsay

#include "Ex01MCApplication.h"
#include "Ex01DetectorConstructionOld.h"
#include "Ex01MCStack.h"

#include <Riostream.h>
#include <TArrayD.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TGeant4.h>
#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMatrix.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TInterpreter.h>
#include <TLorentzVector.h>
#include <TPad.h>
#include <TROOT.h>
#include <TRandom2.h>
#include <TSystem.h>
#include <TThread.h>
#include <TVirtualGeoTrack.h>
#include <TVirtualMC.h>

using namespace std;

/// \cond CLASSIMP
ClassImp(Ex01MCApplication)
    /// \endcond

    //_____________________________________________________________________________
    Ex01MCApplication::Ex01MCApplication(const char *name, const char *title)
    : TVirtualMCApplication(name, title), fStack(0), fMagField(0), fImedAr(0),
      fImedAir(0), fImedAl(0), fImedPb(0), fImedBe(0), fImedC(0), fImedCu(0),
      fImedSn(0), fImedCH2(0), fImedBronze(0), fImedWolfram(0),
      fOldGeometry(kFALSE), fPdg(0), fSeed(0) {
  /// Standard constructor
  /// \param name   The MC application name
  /// \param title  The MC application description

  // create a user stack
  fStack = new Ex01MCStack(1000000);

  // create magnetic field (with zero value)
  fMagField = new TGeoUniformMagField();
}

//_____________________________________________________________________________
void Ex01MCApplication::SetCollectTracks(bool collectTracks) {
  fIsCollectTracks = collectTracks;
  if (collectTracks) {
    gMC->SetCollectTracks(fIsCollectTracks);
  }
}

//_____________________________________________________________________________
Ex01MCApplication::Ex01MCApplication()
    : TVirtualMCApplication(), fStack(0), fMagField(0), fImedAr(0), fImedAir(0),
      fImedAl(0), fImedPb(0), fImedBe(0), fImedC(0), fImedCu(0), fImedSn(0),
      fImedCH2(0), fImedBronze(0), fImedWolfram(0), fOldGeometry(kFALSE),
      fPdg(0), fSeed(0) {
  /// Default constructor
  // create a user stack
  fStack = new Ex01MCStack(1000000);

  // create magnetic field (with zero value)
  fMagField = new TGeoUniformMagField();
}

//_____________________________________________________________________________
Ex01MCApplication::~Ex01MCApplication() {
  /// Destructor

  delete fStack;
  delete fMagField;
  delete gMC;
}

//
// private methods
//

//_____________________________________________________________________________
void Ex01MCApplication::ConstructMaterials() {
  /// Construct materials using TGeo modeller

  // Create Root geometry manager
  new TGeoManager("E01_geometry", "E01 VMC example geometry");

  Double_t a;       // Mass of a mole in g/mole
  int z;            // Atomic number
  int n;            // Nucleons number
  Double_t density; // Material density in g/cm3

  TGeoElement *elN = new TGeoElement("Nitrogen", "N", z = 7, a = 14.01);
  TGeoElement *elO = new TGeoElement("Oxygen", "O", z = 8, a = 16.00);
  TGeoElement *elH = new TGeoElement("Hydrogen", "H", z = 1, a = 1.01);
  TGeoElement *elC = new TGeoElement("Carbon", "C", z = 6, a = 12.01);
  TGeoElement *elNa = new TGeoElement("Sodium", "Na", z = 11, a = 22.99);
  TGeoElement *elI = new TGeoElement("Iodine", "I", z = 53, a = 126.90447);
  TGeoElement *elBi = new TGeoElement("Bismut", "Bi", z = 83, a = 208.98);
  TGeoElement *elGe = new TGeoElement("Germanium", "Ge", z = 32, a = 72.63);
  TGeoElement *elCu = new TGeoElement("Cuprum", "Cu", z = 29, a = 63.546);
  TGeoElement *elSn = new TGeoElement("Stanum", "Sn", z = 50, a = 118.71);
  TGeoElement *elW = new TGeoElement("Wolfram", "W", z = 74, a = 183.84);
  TGeoElement *elBe = new TGeoElement("Beryllium", "Be", z = 4, a = 9.012182);
  TGeoElement *elLi = new TGeoElement("Lithium", "Li", z = 3, a = 6.95);
  TGeoElement *elF = new TGeoElement("Fluorum", "F", z = 9, a = 18.998403163);

  TGeoIsotope *isot7Li = new TGeoIsotope("7Li", 3, 7, 7.016003434);
  TGeoElement *el7Li = new TGeoElement("Lithium7", "7Li", 1);
  el7Li->AddIsotope(isot7Li, 1.);

  TGeoIsotope *isot6Li = new TGeoIsotope("6Li", 3, 6, 6.0151228874);
  TGeoElement *el6Li = new TGeoElement("Lithium6", "6Li", 1);
  el6Li->AddIsotope(isot6Li, 1.);

  TGeoIsotope *isot2H = new TGeoIsotope("2H", 1, 2, 2.0141017778);
  TGeoElement *el2H = new TGeoElement("Deuterium", "2H", 1);
  el2H->AddIsotope(isot2H, 1.);

  TGeoIsotope *isot106Cd = new TGeoIsotope("106Cd", 48, 106, 105.906459);
  TGeoIsotope *isot108Cd = new TGeoIsotope("108Cd", 48, 108, 107.904184);
  TGeoIsotope *isot110Cd = new TGeoIsotope("110Cd", 48, 110, 109.9030021);
  TGeoIsotope *isot111Cd = new TGeoIsotope("111Cd", 48, 111, 110.9041781);
  TGeoIsotope *isot112Cd = new TGeoIsotope("112Cd", 48, 112, 111.9027578);
  TGeoIsotope *isot113Cd = new TGeoIsotope("113Cd", 48, 113, 112.9044017);
  TGeoIsotope *isot114Cd = new TGeoIsotope("114Cd", 48, 114, 113.9033585);
  TGeoIsotope *isot116Cd = new TGeoIsotope("116Cd", 48, 116, 115.904756);

  TGeoElement *elCd = new TGeoElement("Cadmium", "natCd", 8);
  elCd->AddIsotope(isot106Cd, 0.0125);
  elCd->AddIsotope(isot108Cd, 0.0089);
  elCd->AddIsotope(isot110Cd, 0.1249);
  elCd->AddIsotope(isot111Cd, 0.1280);
  elCd->AddIsotope(isot112Cd, 0.2413);
  elCd->AddIsotope(isot113Cd, 0.1222);
  elCd->AddIsotope(isot114Cd, 0.2873);
  elCd->AddIsotope(isot116Cd, 0.0749);

  //____Ar____
  a = 39.95;
  z = 18.;
  density = 1.782e-03;
  TGeoMaterial *matAr = new TGeoMaterial("ArgonGas", a, z, density);

  //____Air____
  TGeoMixture *matAir = new TGeoMixture("Air", 2, density = 1.29e-03);
  matAir->AddElement(elN, 0.761);
  matAir->AddElement(elO, 0.239);

  //____CH2_____
  TGeoMixture *matPoly = new TGeoMixture("CH2", 2, density = 0.95);
  matPoly->AddElement(elC, 0.8571);
  matPoly->AddElement(elH, 0.1429);

  //____Water____
  TGeoMixture *matWater = new TGeoMixture("Water", 2, density = 1.0);
  matWater->AddElement(elO, int(1));
  matWater->AddElement(elH, int(2));
  matWater->SetState(TGeoMaterial::kMatStateLiquid);

  //____Heavy water____
  TGeoMixture *matD2O = new TGeoMixture("D2O", 2, density = 1.1042);
  matD2O->AddElement(elO, int(1));
  matD2O->AddElement(el2H, int(2));
  matD2O->SetState(TGeoMaterial::kMatStateLiquid);

  //____BeO______
  TGeoMixture *matBeO = new TGeoMixture("BeO", 2, density = 3.01);
  matBeO->AddElement(elBe, int(1));
  matBeO->AddElement(elO, int(1));

  //____Be2C______
  TGeoMixture *matBe2C = new TGeoMixture("Be2C", 2, density = 2.24);
  matBe2C->AddElement(elBe, int(2));
  matBe2C->AddElement(elC, int(1));

  //____7Li2O______
  TGeoMixture *mat7Li2O = new TGeoMixture("7Li2O", 2, density = 2.019725693);
  mat7Li2O->AddElement(el7Li, int(2));
  mat7Li2O->AddElement(elO, int(1));

  //____6Li2O______
  TGeoMixture *mat6Li2O = new TGeoMixture("6Li2O", 2, density = 1.885211828);
  mat6Li2O->AddElement(el6Li, int(2));
  mat6Li2O->AddElement(elO, int(1));

  //____LiF______
  TGeoMixture *matLiF = new TGeoMixture("LiF", 2, density = 2.640);
  matLiF->AddElement(elLi, int(1));
  matLiF->AddElement(elF, int(1));

  //____7LiF______
  TGeoMixture *mat7LiF = new TGeoMixture("7LiF", 2, density = 2.630);
  mat7LiF->AddElement(el7Li, int(1));
  mat7LiF->AddElement(elF, int(1));

  //_____Cd______
  TGeoMixture *matCd = new TGeoMixture("Cd", 1, density = 8.65);
  matCd->AddElement(elCd, int(1));

  //____Al____
  TGeoMaterial *matAl =
      new TGeoMaterial("Al", a = 26.98, z = 13., density = 2.7);
  //____Pb____
  TGeoMaterial *matLead =
      new TGeoMaterial("Pb", a = 207.19, z = 82., density = 11.35);
  //____C_____
  TGeoMaterial *matC = new TGeoMaterial("C", a = 12., z = 6., density = 1.742);
  //____Be____
  TGeoMaterial *matBe =
      new TGeoMaterial("Be", a = 9.01, z = 4., density = 1.848);
  //____Cu____
  TGeoMaterial *matCu =
      new TGeoMaterial("Cu", a = 63.546, z = 29., density = 8.96);
  //____Sn____
  TGeoMaterial *matSn =
      new TGeoMaterial("Sn", a = 118.71, z = 50., density = 7.31);

  //____Wolfram____
  TGeoMaterial *matWolfram =
      new TGeoMaterial("W", a = 183.84, z = 74., density = 19.25);

  //____Bronze_____
  TGeoMixture *matBronze = new TGeoMixture("Bronze", 2, density = 8.6);
  matBronze->AddElement(elCu, 0.8);
  matBronze->AddElement(elSn, 0.2);

  //____NaI____
  TGeoMixture *matNaI = new TGeoMixture("NaI", 2, density = 3.67);
  matNaI->AddElement(elNa, int(1));
  matNaI->AddElement(elI, int(1));

  //____BGO____
  TGeoMixture *matBGO = new TGeoMixture("BGO", 3, density = 7.13);
  matBGO->AddElement(elBi, int(4));
  matBGO->AddElement(elGe, int(3));
  matBGO->AddElement(elO, int(12));

  //____Scintillator____
  TGeoMixture *matSci = new TGeoMixture("Scintillator", 2, density = 1.032);
  matSci->AddElement(elC, 9);
  matSci->AddElement(elH, 10);

  //____Plastic____
  TGeoMixture *matPlastic = new TGeoMixture("POMPlastic", 3, density = 1.42);
  matPlastic->AddElement(elC, 1);
  matPlastic->AddElement(elH, 2);
  matPlastic->AddElement(elO, 1);

  //____Polysteren___
  TGeoMixture *matPolysteren = new TGeoMixture("Polysteren", 2, density = 1.1);
  matPolysteren->AddElement(elC, 1);
  matPolysteren->AddElement(elH, 1);

  //____Vacuum_____
  TGeoMaterial *matVac =
      new TGeoMaterial("Vacuum", a = 1., z = 1., density = 10e-10);

  //
  // Tracking medias
  //

  Double_t param[20];
  param[0] = 0;     // isvol  - Not used
  param[1] = 0;     // ifield - Zero magnetic field
  param[2] = 10.;   // fieldm - Maximum field value (in kiloGauss)
  param[3] = -20.;  // tmaxfd - Maximum angle due to field deflection
  param[4] = -0.01; // stemax - Maximum displacement for multiple scat
  param[5] = -.3;   // deemax - Maximum fractional energy loss, DLS
  param[6] = .001;  // epsil - Tracking precision
  param[7] = -.8;   // stmin
  for (Int_t i = 8; i < 20; ++i)
    param[i] = 0.;

  // target material
  fImedAl = 3;
  new TGeoMedium("Aluminium", fImedAl, matAl, param);

  fImedPb = 6;
  new TGeoMedium("Lead", fImedPb, matLead, param);

  fImedBe = 1;
  new TGeoMedium("Be", fImedBe, matBe, param);

  fImedSn = 5;
  new TGeoMedium("Tin", fImedSn, matSn, param);

  fImedCu = 4;
  new TGeoMedium("Cuprum", fImedCu, matCu, param);

  fImedC = 2;
  new TGeoMedium("Carbon", fImedC, matC, param);

  fImedCH2 = 7;
  new TGeoMedium("Polyethylene", fImedCH2, matPoly, param);

  // all other material
  fImedAr = 10;
  new TGeoMedium("ArgonGas", fImedAr, matAr, param);

  fImedAir = 11;
  new TGeoMedium("Air", fImedAir, matAir, param);

  fImedNaI = 12;
  new TGeoMedium("NaI", fImedNaI, matNaI, param);

  fImedBGO = 13;
  new TGeoMedium("BGOcrystall", fImedBGO, matBGO, param);

  fImedPlastic = 14;
  new TGeoMedium("Plastic", fImedPlastic, matPlastic, param);

  fImedSci = 15;
  new TGeoMedium("Scintillator", fImedSci, matSci, param);

  fImedVac = 16;
  new TGeoMedium("Vacuum", fImedVac, matVac, param);

  fImedBronze = 17;
  new TGeoMedium("Bronze", fImedBronze, matBronze, param);

  fImedWolfram = 18;
  new TGeoMedium("Wolfram", fImedWolfram, matWolfram, param);

  fImedWater = 19;
  new TGeoMedium("Water", fImedWater, matWater, param);

  fImedBeO = 20;
  new TGeoMedium("BeO", fImedBeO, matBeO, param);

  fImed7Li2O = 21;
  new TGeoMedium("7Li2O", fImed7Li2O, mat7Li2O, param);

  fImed6Li2O = 22;
  new TGeoMedium("6Li2O", fImed6Li2O, mat6Li2O, param);

  fImedLiF = 23;
  new TGeoMedium("LiF", fImedLiF, matLiF, param);

  fImedD2O = 24;
  new TGeoMedium("D2O", fImedD2O, matD2O, param);

  fImedBe2C = 25;
  new TGeoMedium("Be2C", fImedBe2C, matBe2C, param);

  fImedLiF = 26;
  new TGeoMedium("7LiF", fImed7LiF, mat7LiF, param);

  fImedCd = 27;
  new TGeoMedium("Cd", fImedCd, matCd, param);

  fImedPolysteren = 28;
  new TGeoMedium("Polysteren", fImedPolysteren, matPolysteren, param);
}
//____________________________________________________________________________
//_____________________________________________________________________________
void Ex01MCApplication::ConstructVolumes() {
  /// Contruct volumes using TGeo modeller

  //------------------------------ experimental hall (world volume)
  //------------------------------ beam line along z axis

  Double_t *ubuf = 0;

  int iMedWorld = -1;
  if (fWorldMaterial == "Air") {
    iMedWorld = fImedAir;
  } else if (fWorldMaterial == "Vacuum") {
    iMedWorld = fImedVac;
  }
  if (iMedWorld != -1) {
    std::cout << "World material " << fWorldMaterial << " is set correctly"
              << std::endl;
  } else {
    std::cout << "World material " << fWorldMaterial
              << " is incorrect. Using air instead!" << std::endl;
    iMedWorld = fImedAir;
  }
  double expHallSize = 1000.;
  if (expHallSize < fSenseSphereRadius) {
    expHallSize = fSenseSphereRadius + 20.;
  }
  Double_t expHall[3];
  expHall[0] = expHallSize;
  expHall[1] = expHallSize;
  expHall[2] = expHallSize;
  TGeoVolume *top = gGeoManager->Volume("EXPH", "BOX", iMedWorld, expHall, 3);
  gGeoManager->SetTopVolume(top);

  // target
  gGeoManager->GetMedium(fImedTarget)
      ->GetMaterial()
      ->SetTemperature(fTargetTemperature);
  TGeoVolume *target;
  if (!fIsSimulatingSphere) {
    target =
        gGeoManager->MakeTube("TARGET", gGeoManager->GetMedium(fImedTarget), 0.,
                              fTargetRadius, fTargetThickness / 2.);
  } else {
    target = gGeoManager->MakeSphere(
        "TARGET", gGeoManager->GetMedium(fImedTarget), 0., fTargetRadius);
  }
  top->AddNode(target, 1, new TGeoTranslation(0., 0., 0.));
  // cooling
  if (fCoolingThickness > 0.) {
    int coolingMediumId = -1;
    if (fCoolingMaterial == "Carbon") {
      coolingMediumId = fImedC;
    } else if (fCoolingMaterial == "Water") {
      coolingMediumId = fImedWater;
    } else if (fCoolingMaterial == "Polyethylene") {
      coolingMediumId = fImedCH2;
    } else if (fCoolingMaterial == "BeO") {
      coolingMediumId = fImedBeO;
    } else if (fCoolingMaterial == "7Li2O") {
      coolingMediumId = fImed7Li2O;
    } else if (fCoolingMaterial == "6Li2O") {
      coolingMediumId = fImed6Li2O;
    } else if (fCoolingMaterial == "LiF") {
      coolingMediumId = fImedLiF;
    } else if (fCoolingMaterial == "D2O") {
      coolingMediumId = fImedD2O;
    } else if (fCoolingMaterial == "Be2C") {
      coolingMediumId = fImedBe2C;
    } else if (fCoolingMaterial == "7LiF") {
      coolingMediumId = fImed7LiF;
    } else if (fCoolingMaterial == "Cd") {
      coolingMediumId = fImedCd;
    } else if (fCoolingMaterial == "Polysteren") {
      coolingMediumId = fImedPolysteren;
    }
    if (coolingMediumId != -1) {
      std::cout << "Cooling material " << fCoolingMaterial
                << " is set correctly." << std::endl;
    } else {
      std::cout << "Cooling material " << fCoolingMaterial
                << " is incorrect. Using Air instead!" << std::endl;
      coolingMediumId = fImedAir;
    }
    gGeoManager->GetMedium(coolingMediumId)
        ->GetMaterial()
        ->SetTemperature(fCoolingTemperature);
    TGeoVolume *cooling;
    if (!fIsSimulatingSphere) {
      cooling = gGeoManager->MakeTube(
          "COOLING", gGeoManager->GetMedium(coolingMediumId), fTargetRadius,
          fTargetRadius + fCoolingThickness,
          fTargetThickness / 2. + fCoolingThickness);
    } else {
      cooling = gGeoManager->MakeSphere(
          "COOLING", gGeoManager->GetMedium(coolingMediumId), fTargetRadius,
          fTargetRadius + fCoolingThickness);
    }
    top->AddNode(cooling, 1, new TGeoTranslation(0., 0., 0.));

    // forward "cork"
    TGeoVolume *coolingCork = gGeoManager->MakeTube(
        "COOLING_CORK", gGeoManager->GetMedium(coolingMediumId), 0.,
        fTargetRadius, fCoolingThickness / 2.);
    if (!fIsSimulatingSphere) {
      top->AddNode(coolingCork, 1,
                   new TGeoTranslation(
                       0., 0., (fTargetThickness + fCoolingThickness) / 2.));
    }
  } // if (fCoolingThickness > 0.) {...

  if (fSenseSphereRadius < TMath::Sqrt(TMath::Power(fTargetThickness / 2., 2) +
                                       TMath::Power(fTargetRadius, 2)) +
                               fCoolingThickness) {
    std::cout << "Sense sphere is smaller than target station! Exiting!"
              << std::endl;
    std::cerr << "Sense sphere is smaller than target station! Exiting!"
              << std::endl;
    gROOT->ProcessLine(".q");
  }
  TGeoVolume *sensSphere =
      gGeoManager->MakeSphere("SENS_SPHERE", gGeoManager->GetMedium(iMedWorld),
                              fSenseSphereRadius, fSenseSphereRadius + 0.01);
  top->AddNode(sensSphere, 1, new TGeoTranslation(0., 0., 0.));

  // close geometry
  gGeoManager->CloseGeometry();

  // notify VMC about Root geometry
  gMC->SetRootGeometry();
}

//
// public methods
//

//_____________________________________________________________________________
void Ex01MCApplication::InitMC(const char *setup) {
  /// Initialize MC.
  /// The selection of the concrete MC is done in the macro.
  /// \param setup The name of the configuration macro

  if (TString(setup) != "") {
    gROOT->LoadMacro(setup);
    gInterpreter->ProcessLine("Config()");
    if (!gMC) {
      Fatal("InitMC",
            "Processing Config() has failed. (No MC is instantiated.)");
    }
  }

  gMC->SetStack(fStack);
  gMC->SetMagField(fMagField);
  gMC->Init();
  gMC->BuildPhysics();
  gMC->SetCollectTracks(fIsCollectTracks);
  gRandom = new TRandom2(fSeed);
  gRandom->SetSeed(fSeed);
  cout << "I set seed = " << gRandom->GetSeed() << endl;
  // TGeant4::MasterInstance()->SetRandomSeed();
  ((TGeant4 *)TVirtualMC::GetMC())->SetRandomSeed();
  cout << "fSeed = " << fSeed << ", actual random seed = " << gRandom->GetSeed()
       << endl;
  const char *fileName = "histos.root";
  cout << "Opening file " << fileName << " for writing." << endl;

  fFileSave = new TFile("histos.root", "RECREATE");
  hNeutronLogEnergy =
      new TH1F("hNeutronLogEnergy", "Neutron Energy; Log_{10}(E (MeV)); counts",
               200, -15., 5.);
  hNeutronLogEnergyW = new TH1F(
      "hNeutronLogEnergyW",
      "Neutron Energy (weight = E); Log_{10}(E (MeV)); counts", 200, -15., 5.);

  hNeutronEnergy = new TH1F("hNeutronEnergy", "NeutronEnergy; E (MeV); counts",
                            100000, 0., 1000.);
  hNeutronEnergyW =
      new TH1F("hNeutronEnergyW", "NeutronEnergy (weight = E); E (MeV); counts",
               100000, 0., 1000.);

  hNeutronAngular =
      new TH2F("hNeutronAngular",
               "Neutron angular distribution; cos #Theta; #varphi; counts", 100,
               -1., 1., 80, -4., 4.);
  hNeutronCosTh = new TH1F("hNeutronCosTh",
                           "Neutron angular distribution; cos #Theta; counts",
                           100, -1., 1.);
  hNeutronLogEnVsCosTh = new TH2F(
      "hNeutronLogEnVsCosTh",
      "Neutron energy vs cos #Theta; Log_{10}(E (MeV)); cos #Theta; counts",
      150, -10., 5., 100, -1., 1.);
  hNeutronLogEnVsCosThW = new TH2F("hNeutronLogEnVsCosThW",
                                   "Neutron energy vs cos #Theta (weight = E); "
                                   "Log_{10}(E (MeV)); cos #Theta; counts",
                                   2000, -15., 5., 100, -1., 1.);

  hNeutronEnVsCosTh =
      new TH2F("hNeutronEnVsCosTh",
               "Neutron energy vs cos #Theta; E (MeV); cos #Theta; counts", 100,
               0., 1000., 100, -1., 1.);
  hNeutronEnVsCosThW = new TH2F(
      "hNeutronEnVsCosThW",
      "Neutron energy vs cos #Theta (weight = E); E (MeV); cos #Theta; counts",
      100, 0., 1000., 100, -1., 1.);

  hNeutronLogEnVsTheta = new TH2F(
      "hNeutronLogEnVsTheta",
      "Neutron energy vs #Theta; Log_{10}(E (MeV)); #Theta (degrees); counts",
      150, -10., 5., 72, 0., 180.);
  hChargedAngular =
      new TH2F("hChargedAngular",
               "Charged angular distribution; cos #Theta; #varphi; counts", 100,
               -1., 1., 80, -4., 4.);
  hChargedEnVsCosTh =
      new TH2F("hChargedEnVsCosTh",
               "Charged energy vs cos #Theta; E (MeV); cos #Theta; counts", 100,
               0., 1000., 100, -1., 1.);
  hChargedEnVsCosThW = new TH2F("hChargedLogEnVsCosThW",
                                "Charged energy vs cos #Theta (weight = E); "
                                "E (MeV); cos #Theta; counts",
                                100, 0., 1000., 100, -1., 1.);

  hChargedEnergy = new TH1F("hChargedEnergy", "ChargedEnergy; E (MeV); counts",
                            100000, 0., 1000.);
  hChargedEnergyW =
      new TH1F("hChargedEnergyW", "ChargedEnergy (weight = E); E (MeV); counts",
               100000, 0., 1000.);

  hPhotonAngular =
      new TH2F("hPhotonAngular",
               "Photon angular distribution; cos #Theta; #varphi; counts", 100,
               -1., 1., 80, -4., 4.);
  hPhotonEnVsCosTh =
      new TH2F("hPhotonEnVsCosTh",
               "Photon energy vs cos #Theta; E (MeV); cos #Theta; counts", 100,
               0., 1000., 100, -1., 1.);
  hPhotonEnVsCosThZoomed =
      new TH2F("hPhotonEnVsCosThZoomed",
               "Photon energy vs cos #Theta; E (MeV); cos #Theta; counts", 100,
               0., 10., 100, -1., 1.);
  hPhotonEnVsCosThW = new TH2F("hPhotonEnVsCosThW",
                               "Photon energy vs cos #Theta (weight = E); "
                               "E (MeV); cos #Theta; counts",
                               100, 0., 1000., 100, -1., 1.);

  hPhotonEnergy = new TH1F("hPhotonEnergy", "PhotonEnergy; E (MeV); counts",
                           100000, 0., 1000.);
  hPhotonEnergyW =
      new TH1F("hPhotonEnergyW", "PhotonEnergy (weight = E); E (MeV); counts",
               100000, 0., 1000.);

  hNeutronsPerProton =
      new TH1F("hNeutronsPerProton",
               "Number of neutrons per proton; N_{n}; counts", 1000, 0., 1000.);

  fNeutronMass = TDatabasePDG::Instance()->GetParticle(2112)->Mass();
}

//__________________________________________________________________________
void Ex01MCApplication::RunMC(Int_t nofEvents) {
  /// Run MC.
  /// \param nofEvents Number of events to be processed

  // gRandom = new TRandom2(fSeed);
  // TGeant4::MasterInstance()->SetRandomSeed();
  /*TGeant4::MasterInstance()->ProcessGeantCommand(
      Form("/random/setSeeds %d %d", fSeed, fSeed));
  cout << "fSeed = " << fSeed << ", actual random seed = " << gRandom->GetSeed()
       << endl;*/
  if (fIsCollectTracks) {
    gGeoManager->GetTopVolume()->Draw();
    gGeoManager->DrawTracks("/*");
    gPad->Modified();
    gPad->Update();
    gSystem->ProcessEvents();
    gSystem->ProcessEvents();
  }
  fNEvents = 0;
  gMC->ProcessRun(nofEvents);
  FinishRun();
}
//_____________________________________________________________________________
void Ex01MCApplication::FinishRun() {
  /// Finish MC run.
  fFileSave->Write();
  fFileSave->Close();
  if (fIsCollectTracks) {
    gGeoManager->GetTopVolume()->Draw();
    gGeoManager->DrawTracks("/*");
  }
}

//_____________________________________________________________________________
TVirtualMCApplication *Ex01MCApplication::CloneForWorker() const {
  return new Ex01MCApplication(GetName(), GetTitle());
}

//_____________________________________________________________________________
void Ex01MCApplication::InitOnWorker() {
  gMC->SetStack(fStack);
  gMC->SetMagField(fMagField);
}

//_____________________________________________________________________________
void Ex01MCApplication::ConstructGeometry() {
  /// Construct geometry using TGeo functions or
  /// TVirtualMC functions (if oldGeometry is selected)

  // Cannot use Root geometry if not supported with
  // selected MC
  if (!fOldGeometry && !gMC->IsRootGeometrySupported()) {
    cerr << "Selected MC does not support TGeo geometry" << endl;
    cerr << "Exiting program" << endl;
    exit(1);
  }

  if (!fOldGeometry) {
    cout << "Geometry will be defined via TGeo" << endl;
    ConstructMaterials();
    ConstructVolumes();
  } else {
    cout << "Geometry will be defined via VMC" << endl;
    Ex01DetectorConstructionOld detConstructionOld;
    detConstructionOld.ConstructMaterials();
    detConstructionOld.ConstructVolumes();
  }
}

//_____________________________________________________________________________
void Ex01MCApplication::InitGeometry() {
  /// Initialize geometry.
}

//_____________________________________________________________________________
void Ex01MCApplication::GeneratePrimaries() {
  /// Fill the user stack (derived from TVirtualMCStack) with primary particles.

  // Track ID (filled by stack)
  Int_t ntr;

  // Option: to be tracked
  Int_t toBeDone = 1;

  // pdg code
  int pdg = fPdg;

  // Polarization
  Double_t polx = 0.;
  Double_t poly = 0.;
  Double_t polz = 0.;

  // Position
  Double_t vx = 0.;
  Double_t vy = 0.;
  if (fBeamSize > 0.) {
    vx = gRandom->Gaus(0., fBeamSize);
    vy = gRandom->Gaus(0., fBeamSize);
  }
  Double_t vz = -(fTargetThickness / 2. + fCoolingThickness);
  if (fIsSimulatingSphere) {
    vz = 0.;
  }
  Double_t tof = 0.;

  // 4-momentum
  Double_t px(0.), py(0.), pz(0.), e, m, p;
  m = TDatabasePDG::Instance()->GetParticle(pdg)->Mass();
  e = m + fInitialEnergy;
  p = TMath::Sqrt(e * e - m * m);
  pz = p;
  if (fIsSimulatingSphere) {
    double cosTh = (1. - 2. * gRandom->Rndm());
    double sinTh = TMath::Sqrt((1. - cosTh * cosTh));
    double phi = 2. * TMath::Pi() * gRandom->Rndm();
    pz = p * cosTh;
    px = p * sinTh * TMath::Cos(phi);
    py = p * sinTh * TMath::Sin(phi);
  }
  fStack->PushTrack(toBeDone, -1, pdg, px, py, pz, e, vx, vy, vz, tof, polx,
                    poly, polz, kPPrimary, ntr, 1., 0);
}

//_____________________________________________________________________________
void Ex01MCApplication::BeginEvent() {
  /// User actions at beginning of event.
  fNNeutrons = 0;
  fDrawEvent = false;
  // std::cin.ignore();
  // Clear TGeo tracks (if filled)
  if (/*TString(gMC->GetName()) == "TGeant3TGeo" &&*/
      fIsCollectTracks && gGeoManager->GetListOfTracks() &&
      gGeoManager->GetTrack(0) &&
      ((TVirtualGeoTrack *)gGeoManager->GetTrack(0))->HasPoints()) {

    gGeoManager->ClearTracks();
    // if (gPad) gPad->Clear();
  }
}

//_____________________________________________________________________________
void Ex01MCApplication::BeginPrimary() {
  /// User actions at beginning of a primary track.
  /// Nothing to be done this example
}

//_____________________________________________________________________________
void Ex01MCApplication::PreTrack() {
  /// User actions at beginning of each track.
  /// Print info message.

  // cout << endl;
  // cout << "Starting new track" << endl;
}

//_____________________________________________________________________________
void Ex01MCApplication::Stepping() {
  /// User actions at each step.
  // cout << gMC->TrackPid() << endl;
  if (strcmp(gMC->CurrentVolName(), "SENS_SPHERE") == 0 &&
      gMC->IsTrackExiting()) {
    gMC->StopTrack(); // stop track if it leaves region of interest
  }
  if (strcmp(gMC->CurrentVolName(), "SENS_SPHERE") == 0 &&
      gMC->IsTrackEntering()) {
    TLorentzVector trackMomentum;
    gMC->TrackMomentum(trackMomentum);
    double eKin = 1000. * trackMomentum.E() -
                  1000. * trackMomentum.M(); // Kin energy (MeV)
    TLorentzVector position;
    gMC->TrackPosition(position);
    if (gMC->TrackPid() == 2112) { // neutron
      fNNeutrons++;
      double w = eKin;
      hNeutronLogEnergy->Fill(TMath::Log10(eKin));
      hNeutronEnergy->Fill(eKin);
      hNeutronLogEnergyW->Fill(TMath::Log10(eKin), eKin);
      hNeutronEnergyW->Fill(eKin, eKin);

      hNeutronAngular->Fill(position.CosTheta(), position.Phi());
      hNeutronCosTh->Fill(position.CosTheta());
      hNeutronEnVsCosTh->Fill(eKin, position.CosTheta());
      hNeutronLogEnVsCosTh->Fill(TMath::Log10(eKin), position.CosTheta());
      hNeutronEnVsCosThW->Fill(eKin, position.CosTheta(), eKin);
      hNeutronLogEnVsCosThW->Fill(TMath::Log10(eKin), position.CosTheta(),
                                  eKin);
      hNeutronLogEnVsTheta->Fill(TMath::Log10(eKin),
                                 180. * position.Theta() / TMath::Pi());
    }
    if (gMC->TrackCharge() != 0.) { // charged particles
      hChargedAngular->Fill(position.CosTheta(), position.Phi());
      hChargedEnVsCosTh->Fill(eKin, position.CosTheta());
      hChargedEnVsCosThW->Fill(eKin, position.CosTheta(), eKin);
      hChargedEnergy->Fill(eKin);
      hChargedEnergyW->Fill(eKin, eKin);
      if (eKin > 600.) {
        fDrawEvent = true;
      }
    }
    if (gMC->TrackPid() == 22) { // photon
      hPhotonAngular->Fill(position.CosTheta(), position.Phi());
      hPhotonEnVsCosTh->Fill(eKin, position.CosTheta());
      hPhotonEnVsCosThZoomed->Fill(eKin, position.CosTheta());
      hPhotonEnVsCosThW->Fill(eKin, position.CosTheta(), eKin);
      hPhotonEnergy->Fill(eKin);
      hPhotonEnergyW->Fill(eKin, eKin);
      if (eKin > 5.) {
      }
    }
  } /// Print track position, the current volume and current medium names.
  /*
  TLorentzVector position;
  gMC->TrackPosition(position);

  cout << "Track " << position.X() << " " << position.Y() << " " << position.Z()
       << "  in " << gMC->CurrentVolName() << "  ";

  if (gMC->CurrentMedium() == fImed) cout << "ArgonGas";
  if (gMC->CurrentMedium() == fImedAl) cout << "Aluminium";
  if (gMC->CurrentMedium() == fImedPb) cout << "Lead";

  cout << endl;
  */
  // // Test other TVirtualMC::TrackPosition() functions

  // Double_t dx, dy, dz;
  // gMC->TrackPosition(dx, dy, dz);

  // Float_t x, y, z;
  // gMC->TrackPosition(x, y, z);

  // cout << "Track position (double): "  << dx << " " << dy << " " << dz
  //      << "  (float): "   << x << " " << y << " " << z << endl;
}

//_____________________________________________________________________________
void Ex01MCApplication::PostTrack() {
  /// User actions after finishing of each track
  /// Nothing to be done this example
}

//_____________________________________________________________________________
void Ex01MCApplication::FinishPrimary() {
  /// User actions after finishing of a primary track.
  /// Nothing to be done this example
}

//_____________________________________________________________________________
void Ex01MCApplication::FinishEvent() {
  fNEvents++;
  hNeutronsPerProton->Fill(fNNeutrons);
  if ((fDrawEvent || fDrawEachEvent) && fIsCollectTracks) {
    gGeoManager->GetTopVolume()->Draw();
    gGeoManager->DrawTracks("/*");
    gPad->Modified();
    gPad->Update();
    gSystem->ProcessEvents();
    gSystem->ProcessEvents();
    // gMC->StopRun();
    gSystem->Sleep(500);
  }
  fStack->Reset();
}

//_____________________________________________________________________________
void Ex01MCApplication::TestVMCGeometryGetters() {
  /// Test (new) TVirtualMC functions:
  /// GetTransform(), GetShape(), GetMaterial(), GetMedium()

  // Get transformation of 10th layer
  //
  TString volPath = "/EXPH_1/CALB_1/LAYB_9";
  TGeoHMatrix matrix;
  Bool_t result = gMC->GetTransformation(volPath, matrix);
  if (result) {
    cout << "Transformation for " << volPath.Data() << ": " << endl;
    matrix.Print();
  } else {
    cerr << "Volume path " << volPath.Data() << " not found" << endl;
  }
  cout << endl;

  volPath = "/EXPH_1/CALB_1/LAYB_100";
  result = gMC->GetTransformation(volPath, matrix);
  if (result) {
    cout << "Transformation for " << volPath.Data() << ": " << endl;
    matrix.Print();
  } else {
    cerr << "Volume path " << volPath.Data() << " not found" << endl;
  }
  cout << endl;

  volPath = "/EXPH_1/CALB_1/LAYB_9";
  result = gMC->GetTransformation(volPath, matrix);
  if (result) {
    cout << "Transformation for " << volPath.Data() << ": " << endl;
    matrix.Print();
  } else {
    cerr << "Volume path " << volPath.Data() << " not found" << endl;
  }
  cout << endl;

  // Get shape
  //
  volPath = "/EXPH_1/CALB_1/LAYB_9";
  TString shapeType;
  TArrayD par;
  result = gMC->GetShape(volPath, shapeType, par);
  if (result) {
    cout << "Shape for " << volPath.Data() << ": " << endl;
    cout << shapeType.Data() << "  parameters: ";
    for (Int_t ipar = 0; ipar < par.GetSize(); ipar++)
      cout << par.At(ipar) << ",  ";
    cout << endl;
  } else {
    cerr << "Volume path " << volPath.Data() << " not found" << endl;
  }
  cout << endl;

  // Get material by material ID
  //
  TString matName;
  Int_t imat = 2;
  Double_t a, z, density, radl, inter;
  TArrayD mpar;
#if ROOT_VERSION_CODE >= ROOT_VERSION(5, 30, 0)
  result = gMC->GetMaterial(imat, matName, a, z, density, radl, inter, mpar);
  if (result) {
    cout << "Material with ID " << imat << ": " << endl;
    cout << matName.Data() << "  Aeff = " << a << "  Zeff = " << z
         << "  density = " << density << "  radl = " << radl
         << "  inter = " << inter << endl;
    if (mpar.GetSize() > 0) {
      cout << " User defined parameters: ";
      for (Int_t ipar = 0; ipar < par.GetSize(); ipar++)
        cout << mpar.At(ipar) << ",  ";
      cout << endl;
    }
  } else {
    cerr << "Material with ID " << imat << " not found" << endl;
  }
  cout << endl;
#endif

  // Get material by volume name
  //
  TString volName = "LAYB";
  mpar.Set(0);
  result = gMC->GetMaterial(volName, matName, imat, a, z, density, radl, inter,
                            mpar);
  if (result) {
    cout << "Material for " << volName.Data() << " volume: " << endl;
    cout << matName.Data() << "  " << imat << "  Aeff = " << a
         << "  Zeff = " << z << "  density = " << density << "  radl = " << radl
         << "  inter = " << inter << endl;
    if (mpar.GetSize() > 0) {
      cout << " User defined parameters: ";
      for (Int_t ipar = 0; ipar < par.GetSize(); ipar++)
        cout << mpar.At(ipar) << ",  ";
      cout << endl;
    }
  } else {
    cerr << "Volume " << volName.Data() << " not found" << endl;
  }
  cout << endl;

  // Get medium
  //
  TString medName;
  Int_t imed, nmat, isvol, ifield;
  Double_t fieldm, tmaxfd, stemax, deemax, epsil, stmin;
  result = gMC->GetMedium(volName, medName, imed, nmat, isvol, ifield, fieldm,
                          tmaxfd, stemax, deemax, epsil, stmin, mpar);
  if (result) {
    cout << "Medium for " << volName.Data() << " volume: " << endl;
    cout << medName.Data() << "  " << imed << "  nmat = " << nmat
         << "  isvol = " << isvol << "  ifield = " << ifield
         << "  fieldm = " << fieldm << "  tmaxfd = " << tmaxfd
         << "  stemax = " << stemax << "  deemax = " << deemax
         << "  epsil = " << epsil << "  stmin = " << stmin << endl;
    if (mpar.GetSize() > 0) {
      cout << " User defined parameters: ";
      for (Int_t ipar = 0; ipar < par.GetSize(); ipar++)
        cout << mpar.At(ipar) << ",  ";
      cout << endl;
    }
  } else {
    cerr << "Volume " << volName.Data() << " not found" << endl;
  }
  cout << endl;

  // Test getters non-existing position/volume
  //

  // Transformation
  volPath = "/EXPH_1/CALB_1/LAYB_100";
  result = gMC->GetTransformation(volPath, matrix);
  cout << "GetTransformation: Volume path " << volPath.Data();
  if (!result)
    cout << " not found" << endl;
  else
    cout << " found" << endl;

  // Shape
  result = gMC->GetShape(volPath, shapeType, par);
  cout << "GetShape: Volume path " << volPath.Data();
  if (!result)
    cout << " not found" << endl;
  else
    cout << " found" << endl;

  // Material
  volName = "XYZ";
  result = gMC->GetMaterial(volName, matName, imat, a, z, density, radl, inter,
                            mpar);
  cout << "GetMaterial: Volume name " << volName.Data();
  if (!result)
    cout << " not found" << endl;
  else
    cout << " found" << endl;

  // Medium
  result = gMC->GetMedium(volName, medName, imed, nmat, isvol, ifield, fieldm,
                          tmaxfd, stemax, deemax, epsil, stmin, mpar);
  cout << "GetMedium: Volume name " << volName.Data();
  if (!result)
    cout << " not found" << endl;
  else
    cout << " found" << endl;
}
