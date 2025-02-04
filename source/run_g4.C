void run_g4(int nEvents = 100000, int seed = 0,
	    double energy = 1.3 /*GeV*/,
	    double targThickness = 100 /*cm*/,
	    double targDiameter = 50. /*cm*/,
	    const char *targMaterial = "232Thorium",
	    double coolingThickness = 0.,
	    const char *coolingMaterial = "232Thorium",
	    int pdg = 2212,
            const TString &configMacro = "g4tgeoConfig.C")
{
  gRandom->SetSeed(seed);

  // MC application
  NeutronMCApplication *appl =
      new NeutronMCApplication("neutronMCStudy", "The NeutronMC application");

  appl->SetSeed(seed);

  // beam particle
  appl->SetPdg(pdg); // proton
  appl->SetInitialEnergy(energy);
  appl->SetBeamSize(0. /*cm*/);

  // target parameters
  appl->SetTargetThickness(targThickness);
  appl->SetTargetRadius(targDiameter / 2.);
  appl->SetTargetMaterial(targMaterial);

  // cooling parameters
  appl->SetCoolingThickness(coolingThickness);
  appl->SetCoolingMaterial(coolingMaterial);
    
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
