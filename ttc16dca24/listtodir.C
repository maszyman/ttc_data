void listtodir(const char *infile, int usedir=1, const char* listname = "femtolist")
{
  TFile *ifile = new TFile(infile);
  if (usedir)
    ifile->cd("PWG2FEMTO");
  TList *clist1 = (TList *) gDirectory->Get(listname);
//  TList *clist1 = (TList *) gDirectory->Get("clist1");

  char buf[200];
  sprintf(buf, infile);
  buf[strlen(infile)-5] = '\0';
  strcat(buf, ".dir.root");

  TFile *ofile = new TFile(buf, "RECREATE");

  TIter next(clist1);
  TObject *obj;
  while (obj = next())
  {
    ofile->cd();
    obj->Write();
  }
}
