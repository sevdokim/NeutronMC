
#ifndef EX01_MC_APPLICATION_H
#define EX01_MC_APPLICATION_H

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file Ex01MCApplication.h
/// \brief Definition of the Ex01MCApplication class
///
/// Geant4 ExampleN01 adapted to Virtual Monte Carlo
///
/// \author I. Hrivnacova; IPN, Orsay

#include "Ex01MCStack.h"
#include <TDatabasePDG.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <TVirtualMCApplication.h>

class TVirtualMagField;
class TH1F;
class TH2F;
class TFile;

/// \ingroup E01
/// \brief Implementation of the TVirtualMCApplication
///
/// \date 05/04/2002
/// \author I. Hrivnacova; IPN, Orsay

class Ex01MCApplication : public TVirtualMCApplication {
public:
  Ex01MCApplication(const char *name, const char *title);
  Ex01MCApplication();
  virtual ~Ex01MCApplication();

  // static access method
  static Ex01MCApplication *Instance();

  // methods
  void InitMC(const char *setup);
  void RunMC(Int_t nofEvents);
  void FinishRun();
  void SetBeamSize(double size) { fBeamSize = size; }
  void SetTargetMaterial(int mat) { fImedTarget = mat; }
  void SetTargetMaterial(const char *mat) { fTargetMaterial = mat; }
  void SetTargetRadius(double rad) { fTargetRadius = rad; }
  void SetTargetThickness(double thic) { fTargetThickness = thic; }
  void SetTargetTemperature(double temp) { fTargetTemperature = temp; }
  void SetTargetHoleRadius(double rad) { fTargetHoleRadius = rad; }
  void SetCoolingThickness(double thic) { fCoolingThickness = thic; }
  void SetCoolingMaterial(const char *mat) { fCoolingMaterial = mat; }
  void SetCoolingTemperature(double temp) { fCoolingTemperature = temp; }
  void SetWorldMaterial(const char *mat) { fWorldMaterial = mat; }
  void SetSenseSphereRadius(double rad) { fSenseSphereRadius = rad; }
  void SetInitialEnergy(double initEn) { fInitialEnergy = initEn; }
  void SetPdg(int pdg) { fPdg = pdg; }
  void SetSeed(int seed) { fSeed = seed; }
  void SetCollectTracks(bool collectTracks);
  void DrawEachEvent(bool draw) { fDrawEachEvent = draw; }
  void SetSimulatingSphere() { fIsSimulatingSphere = true; }
  void SetDebugSuspiciousEvent() { fDebugSuspiciousEvent = true; }

  virtual TVirtualMCApplication *CloneForWorker() const;
  virtual void InitOnWorker();
  virtual void ConstructGeometry();
  virtual void InitGeometry();
  virtual void GeneratePrimaries();
  virtual void BeginEvent();
  virtual void BeginPrimary();
  virtual void PreTrack();
  virtual void Stepping();
  virtual void PostTrack();
  virtual void FinishPrimary();
  virtual void FinishEvent();

  // methods for tests
  void SetOldGeometry(Bool_t oldGeometry = kTRUE);
  void TestVMCGeometryGetters();

private:
  // methods
  void ConstructMaterials();
  void ConstructVolumes();

  // data members
  Ex01MCStack *fStack;         ///< The VMC stack
  TVirtualMagField *fMagField; ///< The magnetic field
  Int_t fImedAr;               ///< The Argon gas medium Id
  Int_t fImedAir;              ///< The air medium Id
  Int_t fImedAl;               ///< The Aluminium medium Id
  Int_t fImedPb;               ///< The Lead medium Id
  int fImedBe;
  int fImedC;
  int fImedCu;
  int fImedSn;
  int fImedCH2;
  int fImedPlastic;
  int fImedSci;
  int fImedBGO;
  int fImedNaI;
  int fImedBronze;
  int fImedVac;
  int fImedWolfram;
  int fImedWater;
  int fImedBeO;
  int fImed7Li2O;
  int fImed6Li2O;
  int fImedLiF;
  int fImedD2O;
  int fImedBe2C;
  int fImed7LiF;
  int fImedCd;
  int fImedPolysteren;
  int fImedLiH;

  bool fIsSimulatingSphere = false;
  int fPdg = 2212;
  int fSeed = 0;
  double fBeamSize = 0.;
  double fInitialEnergy = 1.3;

  int fImedTarget = 18;                // default = Wolfram
  double fTargetTemperature = 273.15;  // [K]
  double fTargetRadius = 5.;           // default = 5 cm
  double fTargetThickness = 25.;       // default = 25 cm
  double fTargetHoleRadius = 0.;       // default = 0 cm (no hole)
  TString fTargetMaterial = "NOT_SET"; // default

  double fCoolingThickness = 2.5;      // default = 2.5 cm
  double fCoolingTemperature = 273.15; // [K]
  TString fCoolingMaterial = "Water";  // default = water

  TString fWorldMaterial = "Air";

  double fSenseSphereRadius = 100.; // [cm]

  int fNNeutrons;
  int fNEvents;

  bool fDrawEvent;
  bool fIsCollectTracks = false;
  bool fDrawEachEvent = false;

  double fNeutronMass;

  Bool_t fOldGeometry; ///< Option for geometry definition
  bool fDebugSuspiciousEvent = false;
  bool fIsSuspiciousEvent = false;
  TFile *fFileSave;
  TH1F *hNeutronLogEnergy;
  TH1F *hNeutronLogEnergyW;
  TH1F *hNeutronEnergy;
  TH1F *hNeutronEnergyW;
  TH1F *hNeutronCosTh;
  TH2F *hNeutronAngular;
  TH2F *hNeutronLogEnVsCosTh;
  TH2F *hNeutronLogEnVsCosThW;
  TH2F *hNeutronEnVsCosTh;
  TH2F *hNeutronEnVsCosThW;
  TH2F *hNeutronLogEnVsTheta;

  TH2F *hChargedAngular;
  TH1F *hChargedEnergy;
  TH1F *hChargedEnergyW;
  TH2F *hChargedEnVsCosTh;
  TH2F *hChargedEnVsCosThW;

  TH2F *hPhotonAngular;
  TH1F *hPhotonEnergy;
  TH1F *hPhotonEnergyW;
  TH2F *hPhotonEnVsCosTh;
  TH2F *hPhotonEnVsCosThZoomed;
  TH2F *hPhotonEnVsCosThW;

  TH1F *hNeutronsPerProton;

  ClassDef(Ex01MCApplication, 1) // Interface to MonteCarlo application
};

// inline functions

inline Ex01MCApplication *Ex01MCApplication::Instance() {
  /// \return The MC application instance
  return (Ex01MCApplication *)(TVirtualMCApplication::Instance());
}

inline void Ex01MCApplication::SetOldGeometry(Bool_t oldGeometry) {
  /// Select old geometry definition (via TVirtualMC)
  fOldGeometry = oldGeometry;
}

#endif // EX01_MC_APPLICATION_H
