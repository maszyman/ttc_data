void plotavgsep(const char* infilename1, const char* system, const char* kT) {


  TFile* infile1 = new TFile(infilename1,"read");

  TH1D* num;
  TH1D* den;
  int psibins1 = 3; // 3, 6
  int psibins2 = 3; // 3, 6


  num = (TH1D*)infile1->Get(Form("NumcAvgSep%stpcM0Psi3%s",system,kT));
  den = (TH1D*)infile1->Get(Form("DencAvgSep%stpcM0Psi3%s",system,kT));

  num->SetXTitle("average separation (cm)");
  num->SetYTitle("C");
  num->SetTitle("");


  double norm = den->GetEntries()/num->GetEntries();
  num->Divide(den);
  num->Scale(norm);

  num->SetMaximum(1.3);
  num->SetMinimum(0.8);
  num->GetXaxis()->SetRangeUser(0,50);

  // num->SetName(Form("Numcqinv%stpcM0Psi3%s_1",system,kT));



  num->SetMarkerStyle(20);

  num->SetMarkerColor(kRed);


  gStyle->SetOptStat(0);
  TCanvas* can = new TCanvas("asd","asd");
  can->SetMargin(0.15,0.03,0.15,0.03);
  num->Draw();

  int mult = -1;
  TLatex Tl;
  Tl.SetTextAlign(23);
  Tl.SetTextSize(0.045);
  const char* latsys="";
  const char* latkT="";
  if (strcmp("PP",system)==0)
    Tl.DrawLatex(40,1.293,"pp");
  else if (strcmp("PAP",system)==0) {
    Tl.DrawLatex(40,1.2,"p#bar{p}");
    if (strcmp("",kT)==0)
      Tl.DrawLatex(40,1.15,"0.01 < k_{T} < 5 GeV/c ");
    else if (strcmp("kT0",kT)==0)
      Tl.DrawLatex(40,1.15,"0.01 < k_{T} < 1 GeV/c");
    else if (strcmp("kT1",kT)==0)
      Tl.DrawLatex(40,1.15,"1 < k_{T} < 5 GeV/c");
    if (mult==0)
      Tl.DrawLatex(40,1.1,"0-10%");
  }
  // else if (strcmp("APAP",system)==0)
  //   Tl.DrawLatex(0.12,1.293,"#bar{p}#bar{p}");
  if (strcmp("PAP",system)!=0) {
    if (strcmp("",kT)==0)
      Tl.DrawLatex(40,1.23,"0.01 < k_{T} < 5 GeV/c ");
    else if (strcmp("kT0",kT)==0)
      Tl.DrawLatex(40,1.23,"0.01 < k_{T} < 1 GeV/c");
    else if (strcmp("kT1",kT)==0)
      Tl.DrawLatex(40,1.23,"1 < k_{T} < 5 GeV/c");
    if (mult==0)
      Tl.DrawLatex(40,1.17,"0-10%");
  }
  // if (strcmp("PPAPAP",system)==0) {
  //   Tl.DrawLatex(40,1.293,"#Delta #eta < 0.03 #Delta #phi * < 0.04 @ R=1.6m");
  // }

// TLegend *leg = new TLegend (0.3,0.7,0.8,0.8);
//   leg->SetFillColor(kWhite);
//   leg->SetBorderSize(0);
//   leg->SetTextSize(0.05);


  // leg->AddEntry(num,"#Delta #eta < 0.03 #Delta #phi_{min} * < 0.04","p");
  // leg->AddEntry(cfv4,"no cut","p");

  // leg->AddEntry(num,"field-- #Delta #eta < 0.03 #Delta #phi_{min} * < 0.04","p");
  // leg->AddEntry(cfv4,"field++ #Delta #eta < 0.03 #Delta #phi_{min} * < 0.04","p");

  // leg->Draw("same");

  // can->SaveAs(Form("figs/comparison_%s/%s%s.png",cmp,system,kT));
  can->SaveAs(Form("AvgSep%s%s.png",system,kT));

  // TFile* ofile = new TFile(Form("figs/comparison_%s/cfmb%s%s.root",cmp,system,kT),"recreate");
  // num->Write();
  // cfv4->Write();

}
