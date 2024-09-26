void drawSeveral() {
  const Int_t colors[] = {kBlack,       kRed + 1,    kBlue + 1, kGreen + 3,
                          kMagenta + 1, kOrange - 1, kCyan + 2, kYellow + 2};
  // const char *histoName = "hNeutronsPerProton";
  const char *histoName = "hNeutronLogEnergy"; // <-------------------------------------- HISTO NAME
  // const char *histoName = "hNeutronEnergy";
  // const char *histoName = "hNeutronCosTh";
  // const char *histoName = "hChargedEnergy";
  // const char *histoName = "hPhotonEnergy";
  int nFiles = 4; // <------------------------------------------------------------------- NUMBER OF FILES
  /*const char *fileName[] = {"W10x35_H2O20x45.root", "W15x25_H2O25x35.root",
                            "W10x25_C16x31.root", "W10x25_H2O20x35.root",
                            "W10x25_H2C20x35.root"};*/
  /*const char *fileName[] = {"W10x25_H2O20x35.root", "W10x25_H2C20x35.root",
                            "W10x25_BeO20x35.root"};
  */
  // const char *fileName[] = {"QGSP_BERT_HP_W10x25_H2O20x35.root", "ShieldingLEND_W10x25_H2O20x35.root", "Shielding_W10x25_H2O20x35.root"};
  // const char *fileName[] = {"QGSP_BERT_HP_W10x25_7Li2O20x35.root", "ShieldingLEND_W10x25_7Li2O20x35.root"};
  // const char *fileName[] = {"QGSP_BERT_HP_W10x25_H2O20x35.root", "ShieldingLEND_W10x25_H2O20x35.root"};
  /*const char *fileName[] = { // <--------------------------------------------------------- FILE NAMES
    "ShieldingLEND_W10x25_H2O20x35.root",
    "ShieldingLEND_W10x25_H2C20x35.root",
    "ShieldingLEND_W10x25_C60x75.root"}; */
  const char *fileName[] = {
    // "ShieldingLEND_Sphere_Poly15cm_hole2cm.root",
    "Shielding_Sphere_Poly15cm_hole2cm.root",
    "Shielding_Sphere_D2O15cm_hole2cm.root",
    "Shielding_Sphere_LiH15cm_hole2cm.root",
    "Shielding_Sphere_LiH25cm_hole2cm.root"
  };
    //"QGSP_Sphere_Poly15cm_hole2cm.root"};
  
  const double xRangeLeft = 0., xRangeRight = -1.; // <----------------------------------- X-axis range
  // ------ if xRangeRight < xRangeLeft then range is not set -------


  gROOT->ForceStyle(kTRUE);
  gStyle->SetHistLineWidth(2);
  gStyle->SetLineWidth(2);

  TCanvas *c1 = new TCanvas();
  TH1 **histo = new TH1 *[nFiles];
  float histoMax = 0.;
  int maxHistoId = 0;
  for (int i = 0; i < nFiles; i++) {
    TFile *f = TFile::Open(fileName[i]);
    histo[i] = (TH1 *)f->Get(histoName);
    if (histoMax < histo[i]->GetMaximum()) {
      histoMax = histo[i]->GetMaximum();
      maxHistoId = i;
    }
  }
  histo[maxHistoId]->SetLineColor(colors[maxHistoId]);
  if (xRangeLeft <= xRangeRight) {
    histo[maxHistoId]->GetXaxis()->SetRangeUser(xRangeLeft, xRangeRight);
  }
  histo[maxHistoId]->Draw();
  gPad->SetLogy(1);
  TLegend *leg = new TLegend(0.1, 0.7, 0.48, 0.9);
  leg->AddEntry(histo[maxHistoId], fileName[maxHistoId], "l");
  for (int i = 0; i < nFiles; i++) {
    if (i == maxHistoId) {
      continue;
    }
    histo[i]->SetLineColor(colors[i]);
    histo[i]->Draw("same");
    leg->AddEntry(histo[i], fileName[i], "l");
  }
  leg->Draw();
}
