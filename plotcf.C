Double_t calculateNormalizationFactor(TH1D *num,TH1D *den, Double_t qlo=0.3,Double_t qhi=0.4)
{
  Double_t binlo = num->GetXaxis()->FindFixBin(qlo);
  Double_t binhi = num->GetXaxis()->FindFixBin(qhi);
  Double_t integralNum = num->Integral(binlo, binhi);
  Double_t integralDen = den->Integral(binlo, binhi);
  return integralDen / integralNum;
}

void plotcf(const char* sys="PP", const char* kT="kT1", const char* proj="Out", int mult=2, TString dir = "../train_results_central_dcaptdep", int period=11, int numofpsibins = 6) {

  int seppsi = 0; // indicates if draw in separate psi bins
  int psibins = 0; // indicates if one uses psi binning
  int fname = 1; // indicates if the file name is specified
  int plotinpsibins = 0;
  int rb = 1; // flag to rebinning

  if (mult<2)
    const char* centrality = "central";
  else
    const char* centrality = "semicentral";

  if (period == 11) {

    const int Nruns = 64;
    // const int Nruns = 66;

    int runs[Nruns] = {
      167915, 168115, 168460, 169035, 169238, 169859, 170228  , 167920 // , 168310
      , 168464, 169091, 169411, 169923, 170230, 167985, 168311, 169094, 169415, 170027, 170268, 167987, 168322, 168511, 169138, 169417, 170081, 170269, 167988, 168325, 168512, 169144, 169835, 170155, 170270, 168069,  168341, 168514, 169145, 169837, 170159, 170306// , 168076
      , 168342, 168777,  169148,      169838, 170163, 170308, 168105, 168361, 168826, 169156, 169846, 170193, 170309, 168107 // ,168362
      , 168988,       169160,      169855, 170203, 168108 , 168458,  168992,      169167, 169858, 170204
    };


    // const int Nruns = 62;
    // int runs[Nruns] = {
    //   167915, 168115, 168460, 169035, 169238, 169859, 170228  ,  // 167920 ,
    //   168310, 168464, 169091, 169411, 169923, 170230, 167985, 168311, 169094, 169415, 170027, 170268, 167987, 168322, 168511, 169138, 169417, 170081, 170269, 167988, 168325, 168512, 169144, 169835, 170155, 170270, 168069, // 168341,
    //   168514, 169145, 169837, 170159, 170306, 168076, 168342, 168777, // 169148,
    //   169838, 170163, 170308, 168105, 168361, 168826, 169156, 169846, 170193, 170309, 168107, 168362, // 168988,
    //   // 169160,
    //   169855, 170203, 168108 , 168458,  168992,
    //   169167, 169858, 170204
    // };

  }
  else if (period == 10) {
    const int Nruns = 89;
    int runs[Nruns] = {
      139510, 139507, 139505, 139503, 139465, 139438, 139437, 139360, 139329, 139328, 139314, 139310, 139309, 139173, 139107, 139105, 139038, 139037, 139036, 139029, 139028, 138872, 138871, 138870, 138837, 138732, 138730, 138666, 138662, 138653, 138652, 138638, 138624, 138621, 138583, 138582, 138579, 138578, 138534, 138469, 138442, 138439, 138438, 138396, 138364, 138275, 138225, 138201, 138197, 138192, 138190, 137848, 137844, 137752, 137751, 137724, 137722, 137718, 137704, 137693, 137692, 137691, 137686, 137685, 137639, 137638, 137608, 137595, 137549, 137544, 137541, 137539, 137443, 137441, 137440, 137439, 137434, 137432, 137431, 137430, 137366, 137243, 137236, 137235, 137232, 137231, 137230, 137162, 137161};
  }


  TFile* ifile_[Nruns+1];

  if (plotinpsibins) {
    for (int jf = 0 ; jf < Nruns; ++jf ) {
      ifile_[jf] = new TFile(Form("%s/%d.mergedbinsdir.root",dir.Data(),runs[jf]), "read");
    }
  }
  if (fname)
    ifile_[Nruns] = new TFile(Form("%s",dir.Data()), "read");
  else
    ifile_[Nruns] = new TFile(Form("%s/allrunsmergedbins.root",dir.Data()), "read");


  TH1D* numpp[13][3][Nruns+1];
  TH1D* denpp[13][3][Nruns+1];

  TH1D* numpapoutp[13][3];
  TH1D* numpapoutn[13][3];
  TH1D* numpaplongp[13][3];
  TH1D* numpaplongn[13][3];
  TH1D* numpapsidep[13][3];
  TH1D* numpapsiden[13][3];

  TH1D* denpapoutp[13][3];
  TH1D* denpapoutn[13][3];
  TH1D* denpaplongp[13][3];
  TH1D* denpaplongn[13][3];
  TH1D* denpapsidep[13][3];
  TH1D* denpapsiden[13][3];

  TH1D* numsum;
  TH1D* densum;

	TCanvas *myCan = new TCanvas("asd","asd");
	myCan->Draw();
	myCan->cd();

	TPad *myPad = new TPad("myPad", "The pad",0,0,1,1);
	myPadSetUp(myPad,0.15,0.04,0.04,0.15);
	myPad->Draw();
	myPad->cd();

  TGraph* grnument[13];
  TH2D* hnument = new TH2D("hipsiif","hipsiif",numofpsibins,-0.5,numofpsibins,Nruns,-0.5,Nruns);

  TFile* grofile = new TFile("grofile.root","recreate");

  if (plotinpsibins) {

// _________________________________________________
// // Psi binning.....
// _________________________________________________

// each numerator and denominator from different run
    for (int iPsi = 0; iPsi < numofpsibins; ++iPsi) {

      grnument[iPsi] = new TGraph();

      for (int iif = 0; iif < Nruns; ++iif ) {


        // cout << Form("NumcqinvPPtpcM3Psi%d%s",iPsi,kT) << endl;
        // cout << Form("Numcqinv%stpcM%dPsi%d%s",sys,mult,iPsi,kT) << endl;
        // cout << "iPsi = " << iPsi << endl;
        // // cout << "ikT = " << ikT << endl;
        // cout << "iif = " << iif << endl << endl;

        bool exi = false;

        if (iPsi == 0) {

          if (strcmp(sys,"PAP") != 0) {


            if ( ifile_[iif]->GetListOfKeys()->Contains(Form("Numcqinv%stpcM%dPsi%d%s",sys,mult,iPsi,kT)) ) {
              exi = true;

              numsum = (TH1D*)ifile_[iif]->Get(Form("Numcqinv%stpcM%dPsi%d%s",sys,mult,iPsi,kT));
              densum = (TH1D*)ifile_[iif]->Get(Form("Dencqinv%stpcM%dPsi%d%s",sys,mult,iPsi,kT));

              grnument[iPsi]->SetPoint(grnument[iPsi]->GetN(), iif, numsum->GetEntries());
              hnument->SetBinContent(iPsi+1, iif, numsum->GetEntries());

              if (densum->GetEntries()==0) {
                cout << "iPsi = " << iPsi << endl;
                cout << "iif = " << iif << endl << endl;
              }
            }
          }
          else {
            exi = true;
            numsum = (TH1D*)ifile_[iif]->Get(Form("Num%sPckstarPAPtpcM%dPsi%d%s",proj,mult,iPsi,kT));
            densum = (TH1D*)ifile_[iif]->Get(Form("Den%sPckstarPAPtpcM%dPsi%d%s",proj,mult,iPsi,kT));
            numsumN = (TH1D*)ifile_[iif]->Get(Form("Num%sNckstarPAPtpcM%dPsi%d%s",proj,mult,iPsi,kT));
            densumN = (TH1D*)ifile_[iif]->Get(Form("Den%sNckstarPAPtpcM%dPsi%d%s",proj,mult,iPsi,kT));

            grnument[iPsi]->SetPoint(grnument[iPsi]->GetN(), iif, numsum->GetEntries());
            hnument->SetBinContent(iPsi+1, iif, numsum->GetEntries());

            // numsum->SetBit(TH1::kIsAverage);
            // densum->SetBit(TH1::kIsAverage);
            // numsumN->SetBit(TH1::kIsAverage);
            // densumN->SetBit(TH1::kIsAverage);

          }
          if (exi)
            if (!seppsi) {
              densum->Scale(numsum->GetEntries()/densum->GetEntries());
            }
          if (strcmp(sys,"PAP") == 0) {
            densumN->Scale(numsumN->GetEntries()/densumN->GetEntries());
          }
        }
        else {
          if (strcmp(sys,"PAP") != 0) {
            if ( ifile_[iif]->GetListOfKeys()->Contains(Form("Numcqinv%stpcM%dPsi%d%s",sys,mult,iPsi,kT)) ) {
              exi = true;
              numpp[iPsi][2][iif] = (TH1D*)ifile_[iif]->Get(Form("Numcqinv%stpcM%dPsi%d%s",sys,mult,iPsi,kT));
              denpp[iPsi][2][iif] = (TH1D*)ifile_[iif]->Get(Form("Dencqinv%stpcM%dPsi%d%s",sys,mult,iPsi,kT));

              grnument[iPsi]->SetPoint(grnument[iPsi]->GetN(), iif, numpp[iPsi][2][iif]->GetEntries());
              hnument->SetBinContent(iPsi+1, iif, numpp[iPsi][2][iif]->GetEntries());

              // cout << iPsi << endl;
              // cout << numpp[iPsi][2][iif]->GetEntries() << endl;
              // // cout << denpp[iPsi][2][iif]->GetEntries() << endl;
              // cout << endl;

              if (denpp[iPsi][2][iif]->GetEntries()==0) {
                cout << denpp[iPsi][2][iif]->GetEntries() << endl;
                cout << "iPsi = " << iPsi << endl;
                cout << "iif = " << iif << endl;
              }
            }
          }
          else {
            exi = true;
            numpp[iPsi][2][iif] = (TH1D*)ifile_[iif]->Get(Form("Num%sPckstarPAPtpcM%dPsi%d%s",proj,mult,iPsi,kT));
            denpp[iPsi][2][iif] = (TH1D*)ifile_[iif]->Get(Form("Den%sPckstarPAPtpcM%dPsi%d%s",proj,mult,iPsi,kT));
            numpp[iPsi][0][iif] = (TH1D*)ifile_[iif]->Get(Form("Num%sNckstarPAPtpcM%dPsi%d%s",proj,mult,iPsi,kT));
            denpp[iPsi][0][iif] = (TH1D*)ifile_[iif]->Get(Form("Den%sNckstarPAPtpcM%dPsi%d%s",proj,mult,iPsi,kT));
            // numpp[iPsi][2][iif]->SetBit(TH1::kIsAverage);
            // denpp[iPsi][2][iif]->SetBit(TH1::kIsAverage);
            // numpp[iPsi][0][iif]->SetBit(TH1::kIsAverage);
            // denpp[iPsi][0][iif]->SetBit(TH1::kIsAverage);
            grnument[iPsi]->SetPoint(grnument[iPsi]->GetN(), iif, numpp[iPsi][2][iif]->GetEntries());
            hnument->SetBinContent(iPsi+1, iif, numpp[iPsi][2][iif]->GetEntries());

          }

          if (exi) {
            numsum->Add(numpp[iPsi][2][iif]);
            if (!seppsi)
              denpp[iPsi][2][iif]->Scale(numpp[iPsi][2][iif]->GetEntries()/denpp[iPsi][2][iif]->GetEntries());
            densum->Add(denpp[iPsi][2][iif]);
            if (strcmp(sys,"PAP") == 0) {
              numsumN->Add(numpp[iPsi][0][iif]);
              denpp[iPsi][0][iif]->Scale(numpp[iPsi][0][iif]->GetEntries()/denpp[iPsi][0][iif]->GetEntries());
              densumN->Add(denpp[iPsi][0][iif]);
            }
          }

        }


        // int rb = 2;
        // if (exi) {
        //     cout << "exi" << endl;
        //     numsum->Rebin(rb);
        // }
        // densum->Rebin(rb);
        // numsum->Divide(densum);
        // numsum->SetMarkerColor(1+iPsi);
        // numsum->SetMarkerStyle(20);
        // numsum->SetMarkerSize(1.0);

        // if (iPsi == 0)
        //     numsum->Draw("p");
        // else
        // numsum->Draw("psame");

      }

      if (seppsi) {
        double norm = numsum->GetEntries()/densum->GetEntries();
        cout << iPsi << " " << norm << endl;
        TH1F *hnew = (TH1F*)densum->Clone("hnew");
        hnew->Scale(norm);

        numsum->SetMarkerColor(iPsi+1);
        numsum->SetMarkerStyle(20);
        numsum->SetMarkerSize(1.0);

        int rb = 1;

        numsum->Rebin(rb);
        // densum->Rebin(rb);
        // numsum->Divide(densum);

        hnew->Rebin(rb);
        numsum->Divide(hnew);
        if (iPsi == 0) {
          numsum->DrawCopy("p");
        }
        else {
          numsum->DrawCopy("psame");
        }

        // hnument[iPsi][iif]->Write();

      }
      // cout <<"write ipsi = " << iPsi << endl;
      // grnument[iPsi]->SetName(Form("gr%d",iPsi));
      // grnument[iPsi]->Write();
    }
    // hnument->Write();

    // numpp[6][2]->Draw("p");


    if (!seppsi) {


      if (strcmp(sys,"PAP")==0) {
        numsum->SetBit(TH1::kIsAverage);
        densum->SetBit(TH1::kIsAverage);
        numsumN->SetBit(TH1::kIsAverage);
        densumN->SetBit(TH1::kIsAverage);

        numsum->Add(numsumN);
        densum->Add(densumN);

        numsum->ResetBit(TH1::kIsAverage);
        densum->ResetBit(TH1::kIsAverage);
      }

      numsum->SetMarkerColor(kBlue);
      numsum->SetMarkerStyle(20);
      numsum->SetMarkerSize(1.0);

      int rb = 1;

      numsum->Rebin(rb);
      densum->Rebin(rb);
      numsum->Divide(densum);



      if (psibins)
        numsum->Draw("p");

      // densum->Draw("psame");
    }
  }

// _________________________________________________
// // bez Psi binningu.....
// _________________________________________________


  if (strcmp(sys,"PAP") != 0) {
    numpp[0][2][Nruns] = (TH1D*)ifile_[Nruns]->Get(Form("Numcqinv%stpcM%dPsi%d%s",sys,mult,numofpsibins,kT));
    denpp[0][2][Nruns] = (TH1D*)ifile_[Nruns]->Get(Form("Dencqinv%stpcM%dPsi%d%s",sys,mult,numofpsibins,kT));

    numpp[0][2][Nruns]->SetXTitle("#it{q}_{inv} (GeV/#it{c})");
    numpp[0][2][Nruns]->SetYTitle("C(#it{q}_{inv})");

    // numsum->SetXTitle("#it{q}_{inv} (GeV/#it{c})");
    // numsum->SetYTitle("C(#it{q}_{inv})");

  }
  else {
    numpp[0][2][Nruns] = (TH1D*)ifile_[Nruns]->Get(Form("Num%sPckstarPAPtpcM%dPsi%d%s",proj,mult,numofpsibins,kT));
    denpp[0][2][Nruns] = (TH1D*)ifile_[Nruns]->Get(Form("Den%sPckstarPAPtpcM%dPsi%d%s",proj,mult,numofpsibins,kT));

    numpp[0][0][Nruns] = (TH1D*)ifile_[Nruns]->Get(Form("Num%sNckstarPAPtpcM%dPsi%d%s",proj,mult,numofpsibins,kT));
    denpp[0][0][Nruns] = (TH1D*)ifile_[Nruns]->Get(Form("Den%sNckstarPAPtpcM%dPsi%d%s",proj,mult,numofpsibins,kT));

    numpp[0][2][Nruns]->SetBit(TH1::kIsAverage);
    denpp[0][2][Nruns]->SetBit(TH1::kIsAverage);

    numpp[0][0][Nruns]->SetBit(TH1::kIsAverage);
    denpp[0][0][Nruns]->SetBit(TH1::kIsAverage);

    numpp[0][2][Nruns]->Add(numpp[0][0][Nruns]);
    denpp[0][2][Nruns]->Add(denpp[0][0][Nruns]);

    numpp[0][2][Nruns]->ResetBit(TH1::kIsAverage);
    denpp[0][2][Nruns]->ResetBit(TH1::kIsAverage);

    numpp[0][2][Nruns]->SetXTitle("#it{k*} (GeV/#it{c})");
    numpp[0][2][Nruns]->SetYTitle("C(#it{k*})");

    // numsum->SetXTitle("#it{k*} (GeV/#it{c})");
    // numsum->SetYTitle("C(#it{k*})");

  }

  gStyle->SetOptStat(0);
  numpp[0][2][Nruns]->GetXaxis()->SetTitleSize(0.06);
  numpp[0][2][Nruns]->GetYaxis()->SetTitleSize(0.06);
  numpp[0][2][Nruns]->SetTitle("");

  numpp[0][2][Nruns]->Rebin(rb);
  denpp[0][2][Nruns]->Rebin(rb);

  numpp[0][2][Nruns]->SetMarkerColor(kRed);
  numpp[0][2][Nruns]->SetMarkerStyle(20);
  numpp[0][2][Nruns]->SetMarkerSize(1.0);

  // numsum->GetXaxis()->SetTitleSize(0.06);
  // numsum->GetYaxis()->SetTitleSize(0.06);
  // numsum->SetTitle("");

  // numsum->Rebin(rb);
  // densum->Rebin(rb);


  double norm = denpp[0][2][Nruns]->GetEntries()/numpp[0][2][Nruns]->GetEntries();
  //double norm = calculateNormalizationFactor(numpp[0][2][Nruns],denpp[0][2][Nruns],0.4,0.45 );
  //double norm = calculateNormalizationFactor(numpp[0][2][Nruns],denpp[0][2][Nruns],0.3,0.4 );

  numpp[0][2][Nruns]->Divide(denpp[0][2][Nruns]);
  numpp[0][2][Nruns]->Scale(norm);

  if (strcmp(sys,"PAP") == 0) {
    numpp[0][2][Nruns]->SetMaximum(1.5);
    numpp[0][2][Nruns]->SetMinimum(0.9);
    // numpp[0][2][Nruns]->GetXaxis()->SetRangeUser(0,0.46);
    // numpp[0][2][Nruns]->GetXaxis()->SetRangeUser(0,0.5);

    // numsum->GetXaxis()->SetRangeUser(0,0.6);

    // numsum->SetMaximum(1.058);
    // numsum->SetMinimum(0.912);
    // numsum->SetTitle("");
  }
  else {
    numpp[0][2][Nruns]->SetMaximum(1.5);
    numpp[0][2][Nruns]->SetMinimum(0.9);
    // numsum->SetMaximum(2.2);
    // numsum->SetMinimum(0.5);
    // numpp[0][2][Nruns]->GetXaxis()->SetRangeUser(0,0.26);
    numpp[0][2][Nruns]->GetXaxis()->SetRangeUser(0,0.5);
    // numsum->GetXaxis()->SetRangeUser(0,0.26);
    // numsum->GetXaxis()->SetRangeUser(0,0.3);
  }


// uncomment this to compare
  // if (!psibins)
  numpp[0][2][Nruns]->Draw("p");
  // else
  //   numpp[0][2][Nruns]->Draw("same");






  //numpp[0][2][Nruns]->Write();

  // if (strcmp(sys,"PAP") ==0 ) {
  //   numpp[0][0][Nruns]->Rebin(rb);
  //   denpp[0][0][Nruns]->Rebin(rb);

  //   numpp[0][0][Nruns]->SetMarkerColor(kBlack);
  //   numpp[0][0][Nruns]->SetMarkerStyle(20);
  //   numpp[0][0][Nruns]->SetMarkerSize(1.0);

  //   double norm = denpp[0][0][Nruns]->GetEntries()/numpp[0][0][Nruns]->GetEntries();
  //   numpp[0][0][Nruns]->Divide(denpp[0][0][Nruns]);
  //   numpp[0][0][Nruns]->Scale(norm);
  //   // numpp[0][0][Nruns]->Draw("same");

  //   numsumN->SetMarkerColor(kGreen+2);
  //   numsumN->SetMarkerStyle(20);
  //   numsumN->SetMarkerSize(1.0);

  //   numsumN->Rebin(rb);
  //   densumN->Rebin(rb);
  //   numsumN->Divide(densumN);

  //   // numsumN->Draw("same");
  // }


  // if (psibins) {
  //   TLegend *leg = new TLegend (0.5,0.2,0.7,0.3);
  //   leg->SetFillColor(kWhite);
  //   leg->SetBorderSize(0);
  //   leg->SetTextSize(0.07);
  //   leg->AddEntry(numsum,"w/ #Psi bins","p");
  //   leg->AddEntry(numpp[0][2][Nruns],"w/o EP cut","p");
  //   leg->Draw("same");
  // }


  // TString namef( dir(16,dir.Length()) );
  // cout << namef << endl;

  dir.ReplaceAll("/","_");
  myCan->SaveAs(Form("figs/cf%s%s%sc%d.png",sys,dir.Data(),kT,mult));

  TFile* ofile = new TFile(Form("figs/cfmb%s%s%sc%d.root",sys,dir.Data(),kT,mult),"recreate");
  numpp[0][2][Nruns]->Write();
  //numsum->Write();


}

void myPadSetUp(TPad *currentPad, float currentLeft=0.11, float currentTop=0.04, float currentRight=0.04, float currentBottom=0.15)
{
	currentPad->SetLeftMargin(currentLeft);
	currentPad->SetTopMargin(currentTop);
	currentPad->SetRightMargin(currentRight);
	currentPad->SetBottomMargin(currentBottom);
	return;
}
