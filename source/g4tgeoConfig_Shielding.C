//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \ingroup E01
/// \file E01/g4tgeoConfig.C
/// \brief Configuration macro for Geant4 VMC for Example01
///
/// For geometry defined with Root and selected G4Root navigation

void Config() {
  /// The configuration function for Geant4 VMC for Example01
  /// called during MC application initialization.
  /// For geometry defined with Root and selected RG4Root navigation

  // RunConfiguration for Geant4
  TG4RunConfiguration
      *runConfiguration = // new TG4RunConfiguration("geomRoot");
                          // new TG4RunConfiguration("geomRoot", "FTFP_BERT");
    //    new TG4RunConfiguration("geomRoot", "QGSP_BERT_HP");
   new TG4RunConfiguration("geomRoot", "Shielding");
  //    new TG4RunConfiguration("geomRoot", "ShieldingLEND");
  //  new TG4RunConfiguration("geomRoot", "FTFP_BERT_EMZ+optical");
  runConfiguration->SetMTApplication(0);
  // TGeant4
  TGeant4 *geant4 =
      new TGeant4("TGeant4", "The Geant4 Monte Carlo", runConfiguration);
  geant4->SetRandomSeed();
  geant4->ProcessGeantCommand("/mcPhysics/rangeCuts 10 mm");
  // geant4->ProcessGeantCommand("/mcPhysics/emModel/setEmModel
  // SpecialUrbanMsc");
  geant4->ProcessGeantCommand("/mcDet/setIsMaxStepInLowDensityMaterials true");
  geant4->ProcessGeantCommand("/mcDet/setMaxStepInLowDensityMaterials 10 m");
  // geant4->ProcessGeantCommand("/mcVerbose/composedPhysicsList 2");
  geant4->ProcessGeantCommand("/mcTracking/skipNeutrino true");
  // geant4->ProcessGeantCommand("/mcVerbose/extraPhysicsList 2");
  //
  // geant4->ProcessGeantCommand("/process/optical/verbose 1");
  // geant4->ProcessGeantCommand("/process/optical/processActivation
  // Scintillation true");
  // geant4->ProcessGeantCommand("/process/optical/processActivation Cerenkov
  // false");
  // geant4->ProcessGeantCommand("/process/optical/scintillation/setTrackInfo
  // false");
  // geant4->ProcessGeantCommand("/process/optical/scintillation/setStackPhotons
  // true");
  // geant4->ProcessGeantCommand("/process/optical/scintillation/setStackPhotons
  // false");
  // geant4->ProcessGeantCommand("/process/optical/scintillation/setEnhancedTimeConstants
  // true");
  cout << "Geant4 has been created." << endl;
}
