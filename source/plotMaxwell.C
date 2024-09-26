double funMaxwell_LogE(double *x, double *par) {
  double kT = 8.617333262e-5 * par[0]; // eV
  kT *= 1.e-6;                         // eV -> MeV
  double E = TMath::Power(10., x[0]);
  double fE = (2 / TMath::Sqrt(TMath::Pi())) *
              TMath::Sqrt(TMath::Power(E / kT, 3)) * TMath::Exp(-E / kT);
  double fLog10E = fE * E * TMath::Log(10.);
  return fLog10E;
}
void plotMaxwell(double T = 273.15) {
  TF1 *fMaxwell = new TF1("fMaxwell", funMaxwell_LogE, -10., 5., 1);
  fMaxwell->SetParameter(0, T);
  fMaxwell->SetNpx(1000);
  fMaxwell->SetTitle("dF/dlog10E;log_{10}(E(MeV))");
  fMaxwell->Draw();
}