void plotcomparison(const char* infilename1, const char* infilename2, const char* system, const char* kT) {


  TFile* infile1 = new TFile(infilename1,"read");
  TFile* infile2 = new TFile(infilename2,"read");

  TH1D* cfv1;
  TH1D* cfv2;
  TH1D* cfv3;
  TH1D* cfv4;

  int psibins1 = 3; // 3, 6
  int psibins2 = 3; // 3, 6

  // const char* ktname;
  // if ( strcmp(kT,"") == 0 ) {
  //   ktname = "< k_{T} > = 1.0 GeV/c";
  // }
  // else if ( strcmp(kT,"kT0") == 0 ) {
  //   ktname = "< k_{T} > = 0.6 GeV/c";
  // }
  // else if ( strcmp(kT,"kT1") == 0 ) {
  //   ktname = "< k_{T} > = 1.4 GeV/c";
  // }

  if ( strcmp(system,"PAP") == 0 ) {
    // cfv1 = (TH1D*)infile1->Get(Form("NumLongPckstarPAPtpcM0Psi%d%s",psibins1,kT));
    // cfv2 = (TH1D*)infile2->Get(Form("NumLongPckstarPAPtpcM0Psi%d%s",psibins2,kT));
    cfv3 = (TH1D*)infile1->Get(Form("NumOutPckstarPAPtpcM0Psi3%s",kT));
    cfv4 = (TH1D*)infile2->Get(Form("NumOutPckstarPAPtpcM0Psi3%s",kT));


    cfv3->SetMaximum(1.05);
    cfv3->SetMinimum(0.95);
    cfv3->GetXaxis()->SetRangeUser(0,0.4);
    // cfv3->SetTitle(Form("%s, %s",system,ktname));

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
    cfv3->SetMaximum(1.9);
    cfv3->SetMinimum(0.9);
    cfv3->GetXaxis()->SetRangeUser(0,0.25);

  }
  else {
    // cfv1 = (TH1D*)infile1->Get(Form("Numcqinv%stpcM0Psi%d%s",system,psibins1,kT));
    // cfv2 = (TH1D*)infile2->Get(Form("Numcqinv%stpcM0Psi%d%s",system,psibins2,kT));
    cfv3 = (TH1D*)infile1->Get(Form("Numcqinv%stpcM0Psi3%s",system,kT));
    cfv4 = (TH1D*)infile2->Get(Form("Numcqinv%stpcM0Psi3%s",system,kT));

    cout << Form("Numcqinv%stpcM0Psi%d%s",system,psibins2,kT) << endl;


    cfv3->SetMaximum(1.9);
    cfv3->SetMinimum(0.9);
    cfv3->GetXaxis()->SetRangeUser(0,0.25);

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

  // cfv3->SetMaximum(1.5);
  // cfv3->SetMinimum(0.9);
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

  // const char* cmp = "ttc16_nottc";
  // const char* cmp = "ttc16_f1_f3";
  // const char* cmp = "nottc_f1_f3";
  // const char* cmp = "ttc16_pp_apap";
  // const char* cmp = "nottc_pp_apap";
  // const char* cmp = "ttc16_ttcmin_f1";
  // const char* cmp = "ttcmin_nottc";
  // const char* cmp = "ttc16_ttcmin";
  // const char* cmp = "ttcmin_f1_f3";
  const char* cmp = "ttc16_ttc16dca24";


  int mult = 0;

  TLatex Tl;
  Tl.SetTextAlign(23);
  Tl.SetTextSize(0.045);
  const char* latsys="";
  const char* latkT="";
  if (strcmp("PP",system)==0)
    Tl.DrawLatex(0.12,1.293,"pp");
  else if (strcmp("PAP",system)==0) {
    Tl.DrawLatex(0.22,0.99,"p#bar{p}");
    if (strcmp("",kT)==0)
      Tl.DrawLatex(0.22,0.98,"0.01 < k_{T} < 5 GeV/c ");
    else if (strcmp("kT0",kT)==0)
      Tl.DrawLatex(0.22,0.98,"0.01 < k_{T} < 1 GeV/c");
    else if (strcmp("kT1",kT)==0)
      Tl.DrawLatex(0.22,0.98,"1 < k_{T} < 5 GeV/c");
    if (mult==0)
      Tl.DrawLatex(0.22,0.97,"0-10%");
  }
  else if (strcmp("APAP",system)==0)
    Tl.DrawLatex(0.12,1.293,"#bar{p}#bar{p}");
  if (strcmp("PAP",system)!=0) {
    if (strcmp("",kT)==0)
      Tl.DrawLatex(0.12,1.23,"0.01 < k_{T} < 5 GeV/c ");
    else if (strcmp("kT0",kT)==0)
      Tl.DrawLatex(0.12,1.23,"0.01 < k_{T} < 1 GeV/c");
    else if (strcmp("kT1",kT)==0)
      Tl.DrawLatex(0.12,1.23,"1 < k_{T} < 5 GeV/c");
    if (mult==0)
      Tl.DrawLatex(0.12,1.17,"0-10%");
  }
  if (strcmp("PPAPAP",system)==0) {
    Tl.DrawLatex(0.12,1.293,"#Delta #eta < 0.03 #Delta #phi * < 0.04 @ R=1.6m");
  }

TLegend *leg = new TLegend (0.3,0.7,0.8,0.8);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);

  // leg->AddEntry(cfv3,"#Delta #eta < 0.03 #Delta #phi * < 0.04 @ R=1.6m","p");
  // leg->AddEntry(cfv4,"no cut","p");

  // leg->AddEntry(cfv3,"field-- #Delta #eta < 0.03 #Delta #phi * < 0.04 @ R=1.6m","p");
  // leg->AddEntry(cfv4,"field++ #Delta #eta < 0.03 #Delta #phi * < 0.04 @ R=1.6m","p");

  // leg->AddEntry(cfv3,"field-- no ttc","p");
  // leg->AddEntry(cfv4,"field++ no ttc","p");

  // leg->AddEntry(cfv3,"pp","p");
  // leg->AddEntry(cfv4,"#bar{p}#bar{p}","p");

  // leg->AddEntry(cfv3,"#Delta #eta < 0.03 #Delta #phi * < 0.04 @ R=1.6m","p");
  // leg->AddEntry(cfv4,"#Delta #eta < 0.03 #Delta #phi_{min} * < 0.04","p");

  leg->AddEntry(cfv3,"DCA pT-dep (strict)","p");
  leg->AddEntry(cfv4,"DCA_{xy} < 2.4 cm","p");
  (strcmp(system,"PAP"))?Tl.DrawLatex(0.12,1.493,"#Delta #eta < 0.03 #Delta #phi * < 0.04 @ R=1.6m"):Tl.DrawLatex(0.2,1.01,"#Delta #eta < 0.03 #Delta #phi * < 0.04 @ R=1.6m");

  // leg->AddEntry(cfv3,"#Delta #eta < 0.03 #Delta #phi_{min} * < 0.04","p");
  // leg->AddEntry(cfv4,"no cut","p");

  // leg->AddEntry(cfv3,"field-- #Delta #eta < 0.03 #Delta #phi_{min} * < 0.04","p");
  // leg->AddEntry(cfv4,"field++ #Delta #eta < 0.03 #Delta #phi_{min} * < 0.04","p");

  leg->Draw("same");

  can->SaveAs(Form("figs/comparison_%s/%s%s.png",cmp,system,kT));

  TFile* ofile = new TFile(Form("figs/comparison_%s/cfmb%s%s.root",cmp,system,kT),"recreate");
  cfv3->Write();
  cfv4->Write();

}
