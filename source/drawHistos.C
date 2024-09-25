void drawHistos(const char *fileName = "histos.root") {
  const Int_t colors[] = {kBlack,       kRed + 1,    kBlue + 1, kGreen + 3,
                          kMagenta + 1, kOrange - 1, kCyan + 2, kYellow + 2,
                          kYellow + 4,  kAzure + 2};

  TFile *f = TFile::Open(fileName);
  TString fileSave(fileName);
  if (fileSave.EndsWith(".root")) {
    auto pos = fileSave.Last('.');
    fileSave.Remove(pos);
    fileSave.Append(".pdf");
    cout << fileSave << endl;
  }
  TCanvas *c1 = new TCanvas();
  gROOT->ForceStyle(kTRUE);
  gStyle->SetHistLineWidth(2);
  gStyle->SetLineWidth(2);
  gStyle->SetOptStat(1);
  gPad->SetLogy(1);
  TH1F *hNeutronsPerProton = (TH1F *)f->Get("hNeutronsPerProton");
  hNeutronsPerProton->GetXaxis()->SetRangeUser(0., 100);
  hNeutronsPerProton->Draw();
  c1->Print(fileSave + "(");

  TH1F *hNeutronLogEnergy = (TH1F *)f->Get("hNeutronLogEnergy");
  hNeutronLogEnergy->GetXaxis()->SetRangeUser(-10., 5);
  gPad->SetLogy(0);
  hNeutronLogEnergy->Draw();
  c1->Print(fileSave);
  gPad->SetLogy(1);
  hNeutronLogEnergy->Draw();
  c1->Print(fileSave);

  TH1F *hNeutronEnergy = (TH1F *)f->Get("hNeutronEnergy");
  hNeutronEnergy->Draw();
  gPad->SetLogy(1);
  c1->Print(fileSave);
  gPad->SetLogy(0);

  TH1F *hNeutronCosTh = (TH1F *)f->Get("hNeutronCosTh");
  hNeutronCosTh->Draw();
  c1->Print(fileSave);

  gStyle->SetOptStat(0);
  TH2F *hNeutronAngular = (TH2F *)f->Get("hNeutronAngular");
  hNeutronAngular->Draw("colz");
  c1->Print(fileSave);

  TH2F *hNeutronLogEnVsCosTh = (TH2F *)f->Get("hNeutronLogEnVsCosTh");
  gPad->SetLogz(1);
  hNeutronLogEnVsCosTh->Draw("colz");
  c1->Print(fileSave);
  gPad->SetLogz(0);

  TH2F *hNeutronLogEnVsTheta = (TH2F *)f->Get("hNeutronLogEnVsTheta");
  if (hNeutronLogEnVsTheta) {
    gPad->SetLogz(1);
    hNeutronLogEnVsTheta->Draw("colz");
    c1->Print(fileSave);
    gPad->SetLogz(0);

    double max = -1.;
    TH1 *hPr0;
    TLegend *leg = new TLegend(0.7, 0.5, 1., 1.);
    for (int i = 0; i < 7; i++) {
      int iF, iL;
      const char *drawOpt = "same";
      if (i == 0) {
        iF = 0;
        iL = 3;
        drawOpt = "";
      } else {
        iF = i * 6 - 3;
        iL = 3 + i * 6;
      }
      TH1 *hPr = hNeutronLogEnVsTheta->ProjectionX(
          Form("hNeutronLogEn_Theta%d", i), iF, iL);
      if (i == 0) {
        hPr0 = hPr;
      }
      if (max < hPr->GetMaximum()) {
        max = hPr->GetMaximum();
      }
      hPr->SetLineColor(colors[i]);
      hPr->Draw(drawOpt);
      leg->AddEntry(hPr, Form("#Theta #in [%4.1f, %4.1f]", iF * 2.5, iL * 2.5),
                    "l");
    }
    hPr0->GetYaxis()->SetRangeUser(0., max * 1.2);
    leg->Draw();
    c1->Print(fileSave);

    double max2 = -1.;
    TH1 *hPr02;
    TLegend *leg2 = new TLegend(0.7, 0.5, 1., 1.);
    for (int i = 6; i <= 12; i++) {
      int iF, iL;
      const char *drawOpt = "same";
      if (i == 6) {
        drawOpt = "";
      }
      iF = i * 6 - 3;
      iL = 3 + i * 6;
      if (i == 12) {
        iL = i * 6;
      }
      TH1 *hPr = hNeutronLogEnVsTheta->ProjectionX(
          Form("hNeutronLogEn_Theta%d", i), iF, iL);
      if (i == 6) {
        hPr02 = hPr;
      }
      if (max2 < hPr->GetMaximum()) {
        max2 = hPr->GetMaximum();
      }
      hPr->SetLineColor(colors[i - 6]);
      hPr->Draw(drawOpt);
      leg2->AddEntry(hPr, Form("#Theta #in [%4.1f, %4.1f]", iF * 2.5, iL * 2.5),
                     "l");
    }
    hPr02->GetYaxis()->SetRangeUser(0., max2 * 1.2);
    leg2->Draw();
    c1->Print(fileSave);
  }

  TH2F *hNeutronEnVsCosTh = (TH2F *)f->Get("hNeutronEnVsCosTh");
  hNeutronEnVsCosTh->Draw("colz");
  c1->Print(fileSave);

  TH2F *hChargedAngular = (TH2F *)f->Get("hChargedAngular");
  hChargedAngular->Draw("colz");
  c1->Print(fileSave);

  gStyle->SetOptStat(1);
  TH1F *hChargedEnergy = (TH1F *)f->Get("hChargedEnergy");
  hChargedEnergy->Rebin(5);
  hChargedEnergy->Draw();
  gPad->SetLogy(1);
  c1->Print(fileSave);
  gPad->SetLogy(0);

  gStyle->SetOptStat(0);
  TH2F *hChargedEnVsCosTh = (TH2F *)f->Get("hChargedEnVsCosTh");
  hChargedEnVsCosTh->Draw("colz");
  c1->Print(fileSave);

  TH2F *hPhotonAngular = (TH2F *)f->Get("hPhotonAngular");
  hPhotonAngular->Draw("colz");
  c1->Print(fileSave);

  gStyle->SetOptStat(1);
  TH1F *hPhotonEnergy = (TH1F *)f->Get("hPhotonEnergy");
  hPhotonEnergy->GetXaxis()->SetRangeUser(0., 100.);
  hPhotonEnergy->Draw();
  gPad->SetLogy(1);
  c1->Print(fileSave);

  hPhotonEnergy->GetXaxis()->SetRangeUser(0., 10.);
  hPhotonEnergy->Draw();
  c1->Print(fileSave);
  gPad->SetLogy(0);

  gStyle->SetOptStat(0);
  TH2F *hPhotonEnVsCosTh = (TH2F *)f->Get("hPhotonEnVsCosTh");
  hPhotonEnVsCosTh->Draw("colz");
  c1->Print(fileSave);

  TH2F *hPhotonEnVsCosThZoomed = (TH2F *)f->Get("hPhotonEnVsCosThZoomed");
  if (hPhotonEnVsCosThZoomed) {
    hPhotonEnVsCosThZoomed->Draw("colz");
  }
  c1->Print(fileSave + ")");
}
