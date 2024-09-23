void drawSizes() {
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
  /*TString size[] = {
    "40x55",
    "60x75",
    "80x95"};*/
  TString size[] = {
    "20x35",
    //"30x45",
    "40x55",
    //"50x65",
    "60x75",
    "80x95"
  };
  TString material = "7LiFx";//"BeO";// "Be2C"; // "C";

  TString *fileName = new TString[nFiles];
  for (int i = 0; i < nFiles; i++) {
    fileName[i] = "ShieldingLEND_W10x25_";
    fileName[i] += material;
    fileName[i] += size[i];
    fileName[i] += ".root";
    cout << fileName[i] << endl;
  }
  const char *legText[] = {
    "5 cm",
    //"10 cm",
    "15 cm",
    //"20 cm",
    "25 cm",
    "35 cm"
  };
  const char *legHeader = "^{7}LiF thickness";//"BeO thickness"; //"Be_{2}C thickness";//"Carbon thickness";
  
  const double xRangeLeft = -10., xRangeRight = 5.; // <----------------------------------- X-axis range
  // ------ if xRangeRight < xRangeLeft then range is not set -------


  gROOT->ForceStyle(kTRUE);
  gStyle->SetHistLineWidth(2);
  gStyle->SetLineWidth(2);
  gStyle->SetOptStat(0);
  
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
  TLegend *leg = new TLegend(0.7, 0.6, 1.0, 0.9);
  leg->SetHeader(legHeader, "C");
  // leg->AddEntry(histo[maxHistoId], legText[maxHistoId], "l");
  for (int i = 0; i < nFiles; i++) {
    leg->AddEntry(histo[i], legText[i], "l");
    if (i == maxHistoId) {
      continue;
    }
    histo[i]->SetLineColor(colors[i]);
    histo[i]->Draw("same");
  }
  leg->Draw();
  c1->Print(material + "_sizes.pdf");
}
