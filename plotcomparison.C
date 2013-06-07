void plotcomparison(const char* infilename1, const char* infilename2, const char* system, const char* kT) {

  TFile* infile1 = new TFile(infilename1,"read");
  TFile* infile2 = new TFile(infilename2,"read");

  TH1D* cfv1;
  TH1D* cfv2;
  TH1D* cfv3;
  TH1D* cfv4;

  int psibins1 = 3; // 3, 6
  int psibins2 = 3; // 3, 6

  if ( strcmp(system,"PAP") == 0 ) {
    // cfv1 = (TH1D*)infile1->Get(Form("NumLongPckstarPAPtpcM0Psi%d%s",psibins1,kT));
    // cfv2 = (TH1D*)infile2->Get(Form("NumLongPckstarPAPtpcM0Psi%d%s",psibins2,kT));
    cfv3 = (TH1D*)infile1->Get(Form("NumOutPckstarPAPtpcM0Psi3%s",kT));
    cfv4 = (TH1D*)infile2->Get(Form("NumOutPckstarPAPtpcM0Psi3%s",kT));
  }
  else if ( strcmp(system,"PAPq") == 0 ){
    // cfv1 = (TH1D*)infile1->Get(Form("kstar_NumcqinvPAPtpcM0Psi%d%s",psibins1,kT));
    cfv3 = (TH1D*)infile1->Get(Form("kstar_NumcqinvPAPtpcM0Psi3%s",kT));

    // cfv2 = (TH1D*)infile2->Get(Form("NumLongPckstarPAPtpcM0Psi%d%s",psibins2, kT));
    cfv4 = (TH1D*)infile2->Get(Form("NumLongPckstarPAPtpcM0Psi3%s",kT));

  }
  else if ( strcmp(system,"PPAPAP") == 0 ){
    cfv3 = (TH1D*)infile1->Get(Form("NumcqinvPPtpcM0Psi3%s",kT));
    cfv4 = (TH1D*)infile2->Get(Form("NumcqinvAPAPtpcM0Psi3%s",kT));

  }
  else {
    // cfv1 = (TH1D*)infile1->Get(Form("Numcqinv%stpcM0Psi%d%s",system,psibins1,kT));
    // cfv2 = (TH1D*)infile2->Get(Form("Numcqinv%stpcM0Psi%d%s",system,psibins2,kT));
    cfv3 = (TH1D*)infile1->Get(Form("Numcqinv%stpcM0Psi3%s",system,kT));
    cfv4 = (TH1D*)infile2->Get(Form("Numcqinv%stpcM0Psi3%s",system,kT));

    cout << Form("Numcqinv%stpcM0Psi%d%s",system,psibins2,kT) << endl;
  }

  // cfv1->SetMarkerStyle(20);
  // cfv2->SetMarkerStyle(21);

  cfv3->SetName(Form("Numcqinv%stpcM0Psi3%s_1",system,kT));
  cfv4->SetName(Form("Numcqinv%stpcM0Psi3%s_2",system,kT));



  cfv3->SetMarkerStyle(20);
  cfv4->SetMarkerStyle(21);

  // cfv1->SetMarkerColor(kRed);
  // cfv2->SetMarkerColor(kBlack);
  cfv3->SetMarkerColor(kRed);
  cfv4->SetMarkerColor(kBlack);

  // cfv1->SetMaximum(1.9);
  // cfv1->SetMinimum(0.9);
  // cfv1->GetXaxis()->SetRangeUser(0,0.4);

  cfv3->SetMaximum(1.9);
  cfv3->SetMinimum(0.9);
  // cfv3->GetXaxis()->SetRangeUser(0,0.3);

  gStyle->SetOptStat(0);
  TCanvas* can = new TCanvas("asd","asd");
  can->SetMargin(0.15,0.03,0.15,0.03);
  // can->Divide(2,1);
  // can->cd(1);
  //cfv1->Draw();
  //cfv2->Draw("same");
  // can->cd(2);
  cfv3->Draw();
  cfv4->Draw("same");

  can->SaveAs(Form("figs/comparison/%s%s.png",system,kT));

  TFile* ofile = new TFile(Form("figs/comparison/cfmb%s%s.root",system,kT),"recreate");
  cfv3->Write();
  cfv4->Write();

}
