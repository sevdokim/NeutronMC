//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \ingroup E01
/// \file E01/run_g4.C
/// \brief Macro for running Example01 with Geant4.

void run_g4(int nEvents = 100000, int seed = 0,
            const TString &configMacro = "g4tgeoConfig.C") {
  /// Macro function for running Example01 with Geant4 from
  /// Root interactive session.
  /// Note that since Root 6 the libraries have to be loaded first
  /// via load_g4.C.
  /// \param configMacro configuration macro name, default \ref E01/g4Config.C

  gRandom->SetSeed(seed);

  // MC application
  Ex01MCApplication *appl =
      new Ex01MCApplication("Example01", "The example01 MC application");

  appl->SetSeed(seed);

  // beam particle
  appl->SetPdg(2212); // proton
  appl->SetInitialEnergy(1.3 /*GeV*/);
  appl->SetBeamSize(0. /*cm*/);

  // target parameters
  appl->SetTargetThickness(25.0 /*cm*/);
  appl->SetTargetRadius(5.0 /*cm*/);
  appl->SetTargetMaterial(18); // Wolfram medium id
  appl->SetCoolingThickness(35. /*cm*/);
  appl->SetCoolingMaterial("Carbon");
  // appl->SetCoolingMaterial("Water");

  // Initialize MC
  appl->InitMC(configMacro);
  // appl->SetCollectTracks(true);
  appl->SetCollectTracks(false);
  // appl->DrawEachEvent(true);
  appl->DrawEachEvent(false);
  //     Run MC
  appl->RunMC(nEvents);
  // gGeoManager->GetTopVolume()->Draw();
  // gGeoManager->DrawTracks("/*");
  // delete appl;
}
