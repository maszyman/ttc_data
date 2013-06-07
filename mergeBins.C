void mergeBins(int mult, const char* dir, int period) {

  // int mult = 4;

  // if (mult<2)
  //   const char* centrality = "central";
  // else
  //   const char* centrality = "semicentral";

  int psibins = 4; // 4, 7, 13

  if (period == 11) {
    const int Nruns = 1;
    // const int Nruns = 66;

  //   int runs[Nruns] = {
  //     167915, 168115, 168460, 169035, 169238, 169859, 170228  , 167920  // , 168310
  //     , 168464, 169091, 169411, 169923, 170230, 167985, 168311, 169094, 169415, 170027, 170268, 167987, 168322, 168511, 169138, 169417, 170081, 170269, 167988, 168325, 168512, 169144, 169835, 170155, 170270, 168069,  168341, 168514, 169145, 169837, 170159, 170306// , 168076
  //     , 168342, 168777,  169148,      169838, 170163, 170308, 168105, 168361, 168826, 169156, 169846, 170193, 170309, 168107  // ,168362
  //     , 168988,       169160,      169855, 170203, 168108 , 168458,  168992,      169167, 169858, 170204
  //   };
  // }
  // else if (period == 10) {
  //   const int Nruns = 90;
  //   int runs[Nruns] = {
  //     139510, 139507, 139505, 139503, 139465, 139438, 139437, 139360, 139329, 139328, 139314, 139310, 139309, 139173, 139107, 139105, 139038, 139037, 139036, 139029, 139028, 138872, 138871, 138870, 138837, 138732, 138730, 138666, 138662, 138653, 138652, 138638, 138624, 138621, 138583, 138582, 138579, 138578, 138534, 138469, 138442, 138439, 138438, 138396, 138364, 138275, 138225, 138201, 138197, 138192, 138190, 137848, 137844, 137752, 137751, 137724, 137722, 137718, 137704, 137693, 137692, 137691, 137686, 137685, 137639, 137638, 137608, 137595, 137549, 137544, 137541, 137539, 137443, 137441, 137440, 137439, 137434, 137432, 137431, 137430, 137366, 137243, 137236, 137235, 137232, 137231, 137230, 137162, 137161, 137135};
  }

  TFile* ifile_[Nruns+1];
  TFile* ofile_[Nruns+1];

  for (int jf = 0 ; jf < Nruns; ++jf ) {
    ifile_[jf] = new TFile(Form("%s",dir), "read");
    // cout << Form("%s/%d.dir.root",dir,runs[jf]) << endl;
  }
//    ifile_[Nruns] = new TFile(Form("train_results_%s/allruns.root",centrality), "read");

  TH1D* numpp[13][Nruns+1][3][8];
  TH1D* denpp[13][Nruns+1][3][8];

  for (int iif = 0; iif < Nruns; ++iif ) {
    ofile_[iif] = new TFile(Form("%s.mergedbinsdir.root",dir), "update");

    for (int iPsi = 3; iPsi < psibins; ++iPsi) {

      numpp[iPsi][iif][0][0] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvPPtpcM%dPsi%d",mult,iPsi));
      numpp[iPsi][iif][1][0] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvPPtpcM%dPsi%dkT0",mult,iPsi));
      numpp[iPsi][iif][2][0] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvPPtpcM%dPsi%dkT1",mult,iPsi));

      numpp[iPsi][iif][0][1] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvAPAPtpcM%dPsi%d",mult,iPsi));
      numpp[iPsi][iif][1][1] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvAPAPtpcM%dPsi%dkT0",mult,iPsi));
      numpp[iPsi][iif][2][1] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvAPAPtpcM%dPsi%dkT1",mult,iPsi));

      // numpp[iPsi][iif][0][2] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvPAPtpcM%dPsi%d",mult,iPsi));
      // numpp[iPsi][iif][1][2] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvPAPtpcM%dPsi%dkT0",mult,iPsi));
      // numpp[iPsi][iif][2][2] = (TH1D*)ifile_[iif]->Get(Form("NumcqinvPAPtpcM%dPsi%dkT1",mult,iPsi));

      numpp[iPsi][iif][0][2] = (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%d",mult,iPsi));
      numpp[iPsi][iif][1][2] = (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      numpp[iPsi][iif][2][2] = (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      numpp[iPsi][iif][0][3] = (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%d",mult,iPsi));
      numpp[iPsi][iif][1][3] = (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      numpp[iPsi][iif][2][3] = (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      numpp[iPsi][iif][0][4] = (TH1D*)ifile_[iif]->Get(Form("NumSidePckstarPAPtpcM%dPsi%d",mult,iPsi));
      numpp[iPsi][iif][1][4] = (TH1D*)ifile_[iif]->Get(Form("NumSidePckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      numpp[iPsi][iif][2][4] = (TH1D*)ifile_[iif]->Get(Form("NumSidePckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      numpp[iPsi][iif][0][5] = (TH1D*)ifile_[iif]->Get(Form("NumSideNckstarPAPtpcM%dPsi%d",mult,iPsi));
      numpp[iPsi][iif][1][5] = (TH1D*)ifile_[iif]->Get(Form("NumSideNckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      numpp[iPsi][iif][2][5] = (TH1D*)ifile_[iif]->Get(Form("NumSideNckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      numpp[iPsi][iif][0][6] = (TH1D*)ifile_[iif]->Get(Form("NumLongPckstarPAPtpcM%dPsi%d",mult,iPsi));
      numpp[iPsi][iif][1][6] = (TH1D*)ifile_[iif]->Get(Form("NumLongPckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      numpp[iPsi][iif][2][6] = (TH1D*)ifile_[iif]->Get(Form("NumLongPckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      numpp[iPsi][iif][0][7] = (TH1D*)ifile_[iif]->Get(Form("NumLongNckstarPAPtpcM%dPsi%d",mult,iPsi));
      numpp[iPsi][iif][1][7] = (TH1D*)ifile_[iif]->Get(Form("NumLongNckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      numpp[iPsi][iif][2][7] = (TH1D*)ifile_[iif]->Get(Form("NumLongNckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

// //---
      denpp[iPsi][iif][0][0] = (TH1D*)ifile_[iif]->Get(Form("DencqinvPPtpcM%dPsi%d",mult,iPsi));
      denpp[iPsi][iif][1][0] = (TH1D*)ifile_[iif]->Get(Form("DencqinvPPtpcM%dPsi%dkT0",mult,iPsi));
      denpp[iPsi][iif][2][0] = (TH1D*)ifile_[iif]->Get(Form("DencqinvPPtpcM%dPsi%dkT1",mult,iPsi));

      denpp[iPsi][iif][0][1] = (TH1D*)ifile_[iif]->Get(Form("DencqinvAPAPtpcM%dPsi%d",mult,iPsi));
      denpp[iPsi][iif][1][1] = (TH1D*)ifile_[iif]->Get(Form("DencqinvAPAPtpcM%dPsi%dkT0",mult,iPsi));
      denpp[iPsi][iif][2][1] = (TH1D*)ifile_[iif]->Get(Form("DencqinvAPAPtpcM%dPsi%dkT1",mult,iPsi));

      // denpp[iPsi][iif][0][2] = (TH1D*)ifile_[iif]->Get(Form("DencqinvPAPtpcM%dPsi%d",mult,iPsi));
      // denpp[iPsi][iif][1][2] = (TH1D*)ifile_[iif]->Get(Form("DencqinvPAPtpcM%dPsi%dkT0",mult,iPsi));
      // denpp[iPsi][iif][2][2] = (TH1D*)ifile_[iif]->Get(Form("DencqinvPAPtpcM%dPsi%dkT1",mult,iPsi));

      denpp[iPsi][iif][0][2] = (TH1D*)ifile_[iif]->Get(Form("DenOutPckstarPAPtpcM%dPsi%d",mult,iPsi));
      denpp[iPsi][iif][1][2] = (TH1D*)ifile_[iif]->Get(Form("DenOutPckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      denpp[iPsi][iif][2][2] = (TH1D*)ifile_[iif]->Get(Form("DenOutPckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      denpp[iPsi][iif][0][3] = (TH1D*)ifile_[iif]->Get(Form("DenOutNckstarPAPtpcM%dPsi%d",mult,iPsi));
      denpp[iPsi][iif][1][3] = (TH1D*)ifile_[iif]->Get(Form("DenOutNckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      denpp[iPsi][iif][2][3] = (TH1D*)ifile_[iif]->Get(Form("DenOutNckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      denpp[iPsi][iif][0][4] = (TH1D*)ifile_[iif]->Get(Form("DenSidePckstarPAPtpcM%dPsi%d",mult,iPsi));
      denpp[iPsi][iif][1][4] = (TH1D*)ifile_[iif]->Get(Form("DenSidePckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      denpp[iPsi][iif][2][4] = (TH1D*)ifile_[iif]->Get(Form("DenSidePckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      denpp[iPsi][iif][0][5] = (TH1D*)ifile_[iif]->Get(Form("DenSideNckstarPAPtpcM%dPsi%d",mult,iPsi));
      denpp[iPsi][iif][1][5] = (TH1D*)ifile_[iif]->Get(Form("DenSideNckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      denpp[iPsi][iif][2][5] = (TH1D*)ifile_[iif]->Get(Form("DenSideNckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      denpp[iPsi][iif][0][6] = (TH1D*)ifile_[iif]->Get(Form("DenLongPckstarPAPtpcM%dPsi%d",mult,iPsi));
      denpp[iPsi][iif][1][6] = (TH1D*)ifile_[iif]->Get(Form("DenLongPckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      denpp[iPsi][iif][2][6] = (TH1D*)ifile_[iif]->Get(Form("DenLongPckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

      denpp[iPsi][iif][0][7] = (TH1D*)ifile_[iif]->Get(Form("DenLongNckstarPAPtpcM%dPsi%d",mult,iPsi));
      denpp[iPsi][iif][1][7] = (TH1D*)ifile_[iif]->Get(Form("DenLongNckstarPAPtpcM%dPsi%dkT0",mult,iPsi));
      denpp[iPsi][iif][2][7] = (TH1D*)ifile_[iif]->Get(Form("DenLongNckstarPAPtpcM%dPsi%dkT1",mult,iPsi));

// //---
      numpp[iPsi][iif][0][0]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvPPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][0]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvPPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][0]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvPPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][1]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvAPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][1]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvAPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][1]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvAPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      // numpp[iPsi][iif][0][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvPAPtpcM%dPsi%d",mult+1,iPsi)) );
      // numpp[iPsi][iif][1][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      // numpp[iPsi][iif][2][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumcqinvPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][3]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][3]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][3]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][2]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutPckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][3]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][3]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][3]->Add( (TH1D*)ifile_[iif]->Get(Form("NumOutNckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][4]->Add( (TH1D*)ifile_[iif]->Get(Form("NumSidePckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][4]->Add( (TH1D*)ifile_[iif]->Get(Form("NumSidePckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][4]->Add( (TH1D*)ifile_[iif]->Get(Form("NumSidePckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][5]->Add( (TH1D*)ifile_[iif]->Get(Form("NumSideNckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][5]->Add( (TH1D*)ifile_[iif]->Get(Form("NumSideNckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][5]->Add( (TH1D*)ifile_[iif]->Get(Form("NumSideNckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][6]->Add( (TH1D*)ifile_[iif]->Get(Form("NumLongPckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][6]->Add( (TH1D*)ifile_[iif]->Get(Form("NumLongPckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][6]->Add( (TH1D*)ifile_[iif]->Get(Form("NumLongPckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      numpp[iPsi][iif][0][7]->Add( (TH1D*)ifile_[iif]->Get(Form("NumLongNckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      numpp[iPsi][iif][1][7]->Add( (TH1D*)ifile_[iif]->Get(Form("NumLongNckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      numpp[iPsi][iif][2][7]->Add( (TH1D*)ifile_[iif]->Get(Form("NumLongNckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

// //---
      denpp[iPsi][iif][0][0]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvPPtpcM%dPsi%d",mult+1,iPsi)) );
      denpp[iPsi][iif][1][0]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvPPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      denpp[iPsi][iif][2][0]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvPPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      denpp[iPsi][iif][0][1]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvAPAPtpcM%dPsi%d",mult+1,iPsi)) );
      denpp[iPsi][iif][1][1]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvAPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      denpp[iPsi][iif][2][1]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvAPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      // denpp[iPsi][iif][0][2]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvPAPtpcM%dPsi%d",mult+1,iPsi)) );
      // denpp[iPsi][iif][1][2]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      // denpp[iPsi][iif][2][2]->Add( (TH1D*)ifile_[iif]->Get(Form("DencqinvPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      denpp[iPsi][iif][0][2]->Add( (TH1D*)ifile_[iif]->Get(Form("DenOutPckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      denpp[iPsi][iif][1][2]->Add( (TH1D*)ifile_[iif]->Get(Form("DenOutPckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      denpp[iPsi][iif][2][2]->Add( (TH1D*)ifile_[iif]->Get(Form("DenOutPckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      denpp[iPsi][iif][0][3]->Add( (TH1D*)ifile_[iif]->Get(Form("DenOutNckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      denpp[iPsi][iif][1][3]->Add( (TH1D*)ifile_[iif]->Get(Form("DenOutNckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      denpp[iPsi][iif][2][3]->Add( (TH1D*)ifile_[iif]->Get(Form("DenOutNckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      denpp[iPsi][iif][0][4]->Add( (TH1D*)ifile_[iif]->Get(Form("DenSidePckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      denpp[iPsi][iif][1][4]->Add( (TH1D*)ifile_[iif]->Get(Form("DenSidePckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      denpp[iPsi][iif][2][4]->Add( (TH1D*)ifile_[iif]->Get(Form("DenSidePckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      denpp[iPsi][iif][0][5]->Add( (TH1D*)ifile_[iif]->Get(Form("DenSideNckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      denpp[iPsi][iif][1][5]->Add( (TH1D*)ifile_[iif]->Get(Form("DenSideNckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      denpp[iPsi][iif][2][5]->Add( (TH1D*)ifile_[iif]->Get(Form("DenSideNckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      denpp[iPsi][iif][0][6]->Add( (TH1D*)ifile_[iif]->Get(Form("DenLongPckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      denpp[iPsi][iif][1][6]->Add( (TH1D*)ifile_[iif]->Get(Form("DenLongPckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      denpp[iPsi][iif][2][6]->Add( (TH1D*)ifile_[iif]->Get(Form("DenLongPckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );

      denpp[iPsi][iif][0][7]->Add( (TH1D*)ifile_[iif]->Get(Form("DenLongNckstarPAPtpcM%dPsi%d",mult+1,iPsi)) );
      denpp[iPsi][iif][1][7]->Add( (TH1D*)ifile_[iif]->Get(Form("DenLongNckstarPAPtpcM%dPsi%dkT0",mult+1,iPsi)) );
      denpp[iPsi][iif][2][7]->Add( (TH1D*)ifile_[iif]->Get(Form("DenLongNckstarPAPtpcM%dPsi%dkT1",mult+1,iPsi)) );
// // //---

      for (int i = 0; i < 3;++i) {
        for (int j = 0; j < 8;++j) {
          // if (j != 1) {
          numpp[iPsi][iif][i][j]->Write();
          denpp[iPsi][iif][i][j]->Write();
          // }
        }
      }


    }
  }


}
