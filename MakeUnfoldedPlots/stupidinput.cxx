
void makeTH1F(TH1F* output, TFile* f, std::string prodMode, std::string what);
void   makeTGraphFit(std::string which);
void stupidinput();
void makeMGhisto(TH1F* , TH1F*, TH1F*);
void makeMGinputs();

void stupidinput(){
  
  TH1F *hgg = NULL;
  TH1F *hvbf= NULL;
  TH1F *hwh= NULL;
  TH1F *hzh= NULL;
  TH1F *htth= NULL;
  TH1F *hbbh= NULL;
  
  TFile *_file0 = TFile::Open("expected/standard.root");
  TFile *_file1 = new TFile ("expected/standard_njet.root", "RECREATE");
  
  
  std::vector<std::string> stocazzo ={"","_ScaleTheoryup","_ScaleTheorydown","_PdfTheoryup","_PdfTheorydown"};
  
  for (unsigned int i =0; i < stocazzo.size(); ++i ){
    hgg = new TH1F (("njetv4_ggHNNLOPS"+stocazzo.at(i)).c_str(),("njetv4_ggHNNLOPS"+stocazzo.at(i)).c_str(),6,0,6);
    makeTH1F(hgg, _file0, "ggHNNLOPS", stocazzo.at(i));
    
    hvbf = new TH1F (("njetv4_VBF"+stocazzo.at(i)).c_str(),("njetv4_VBF"+stocazzo.at(i)).c_str(),6,0,6);
    makeTH1F(hvbf, _file0, "VBF", stocazzo.at(i));
    
    hwh = new TH1F (("njetv4_WH"+stocazzo.at(i)).c_str(),("njetv4_WH"+stocazzo.at(i)).c_str(),6,0,6);
    makeTH1F(hwh, _file0, "WH", stocazzo.at(i));
    
    hzh = new TH1F (("njetv4_ZH"+stocazzo.at(i)).c_str(),("njetv4_ZH"+stocazzo.at(i)).c_str(),6,0,6);
    makeTH1F(hzh, _file0, "ZH", stocazzo.at(i));
    
    htth = new TH1F (("njetv4_ttH"+stocazzo.at(i)).c_str(),("njetv4_ttH"+stocazzo.at(i)).c_str(),6,0,6);
    makeTH1F(htth, _file0, "ttH", stocazzo.at(i));
    
    hbbh = new TH1F (("njetv4_bbH"+stocazzo.at(i)).c_str(),("njetv4_bbH"+stocazzo.at(i)).c_str(),6,0,6);
    makeTH1F(hbbh, _file0, "bbH", stocazzo.at(i));


    
    _file1->cd();
    hgg->Write(); hvbf->Write(); hwh->Write(); hzh->Write(); htth->Write();hbbh->Write();
    
  }
  
  TFile *_gosamfile = new TFile ("./expected/WG1_predictions.root");

  TH1F *gosame_ggh = (TH1F*) _gosamfile->Get("GoSamSherpa_Njets_incl");
  TH1F *gosame_gghUp = (TH1F*) _gosamfile->Get("GoSamSherpa_Njets_incl_up");
  TH1F *gosame_gghDown = (TH1F*) _gosamfile->Get("GoSamSherpa_Njets_incl_down");
  
  int Nbins = 6;
  TH1F *Nom_gosam    = new TH1F("Nom_gosam"   , "Nom_gosam"   , Nbins, 0, Nbins);
  TH1F *Up_gosam     = new TH1F("Up_gosam"    , "Up_gosam"    , Nbins, 0, Nbins);
  TH1F *Down_gosam   = new TH1F("Down_gosam"  , "Down_gosam"  , Nbins, 0, Nbins);
  
  
  
  Nom_gosam->SetBinContent(4, gosame_ggh->Integral(2,4)*0.437394/0.437394 ); Nom_gosam->SetBinContent(5, gosame_ggh->Integral(3,4)*0.447365 ); Nom_gosam->SetBinContent(6, gosame_ggh->Integral(4,4) *0.449617);
  Up_gosam->SetBinContent(4, gosame_gghUp->Integral(2,4)*0.437394 ); Up_gosam->SetBinContent(5, gosame_gghUp->Integral(3,4)*0.447365 ); Up_gosam->SetBinContent(6, gosame_gghUp->Integral(4,4) *0.449617);
  Down_gosam->SetBinContent(4, gosame_gghDown->Integral(2,4)*0.437394 ); Down_gosam->SetBinContent(5, gosame_gghDown->Integral(3,4)*0.447365 ); Down_gosam->SetBinContent(6, gosame_gghDown->Integral(4,4) *0.449617);
  
  double ANNLOPS=1.240E-04/2.270E-03	;
  Nom_gosam->Scale(ANNLOPS);
  Up_gosam->Scale(ANNLOPS);
  Down_gosam->Scale(ANNLOPS);
  
  _file1->cd();
  Nom_gosam->Write(); Up_gosam->Write(); Down_gosam->Write();
  
  _file0->Close();
  _file1->Close();
  
  
  makeTGraphFit("__wsysdata_");
  makeTGraphFit("__wsys_fixing_alldata_");
  
  
  makeMGinputs();
  
}



void makeTH1F(TH1F* output, TFile* f, std::string prodMode, std::string what){
  
  
  TH1F* njet = (TH1F*)f->Get(("njet_"+prodMode+what).c_str());
  TH1F* njetv2 = (TH1F*)f->Get(("njetv2_"+prodMode+what).c_str());
  TH1F* njetv3 = (TH1F*)f->Get(("njetv3_"+prodMode+what).c_str());
  
  output->SetBinContent(1, njet->GetBinContent(1));
  output->SetBinContent(2, njet->GetBinContent(2));
  output->SetBinContent(3, njet->GetBinContent(3));
  output->SetBinContent(4, njetv2->GetBinContent(2));
  output->SetBinContent(5, njetv3->GetBinContent(3));
  output->SetBinContent(6, njet->GetBinContent(4));
  
}


void   makeTGraphFit(std::string which){
  
  TFile *_filenj = TFile::Open(("../ws_output/fit_njet"+which+"TGunfolded.root").c_str());
  TFile *_filenjv2 = TFile::Open(("../ws_output/fit_njetv2"+which+"TGunfolded.root").c_str());
  TFile *_filenjv3 = TFile::Open(("../ws_output/fit_njetv3"+which+"TGunfolded.root").c_str());

  TFile *_filenjv4 = new TFile (("../ws_output/fit_njetv4"+which+"TGunfolded.root").c_str(), "RECREATE");
  
  
  TGraphAsymmErrors *g0= (TGraphAsymmErrors*)_filenj->Get("njet");
  TGraphAsymmErrors *g1= (TGraphAsymmErrors*)_filenjv2->Get("njetv2");
  TGraphAsymmErrors *g2= (TGraphAsymmErrors*)_filenjv3->Get("njetv3");
  
  
  TGraphAsymmErrors g;
  g.SetNameTitle("njetv4","njetv4");
  
  
  double x,y;
  g0->GetPoint(0, x,y);
  std::cout << x << "  " << y << std::endl;
  g.SetPoint(0,0.5,y);
  g.SetPointError(0, g0->GetErrorXlow(0),g0->GetErrorXhigh(0),g0->GetErrorYlow(0),g0->GetErrorYhigh(0));
  
  g0->GetPoint(1, x,y);
  std::cout << x << "  " << y << std::endl;
  g.SetPoint(1,1.5,y);
  g.SetPointError(1, g0->GetErrorXlow(1),g0->GetErrorXhigh(1),g0->GetErrorYlow(1),g0->GetErrorYhigh(1));

  
  g0->GetPoint(2, x,y);
  std::cout << x << "  " << y << std::endl;
  g.SetPoint(2,2.5,y);
  g.SetPointError(2, g0->GetErrorXlow(2),g0->GetErrorXhigh(2),g0->GetErrorYlow(2),g0->GetErrorYhigh(2));

  
  g1->GetPoint(1, x,y);
  std::cout << x << "  " << y << std::endl;
  g.SetPoint(3,3.5,y);
  g.SetPointError(3, g1->GetErrorXlow(1),g1->GetErrorXhigh(1),g1->GetErrorYlow(1),g1->GetErrorYhigh(1));

  
  g2->GetPoint(2, x,y);
  std::cout << x << "  " << y << std::endl;
  g.SetPoint(4,4.5,y);
  g.SetPointError(4, g2->GetErrorXlow(2),g2->GetErrorXhigh(2),g2->GetErrorYlow(2),g2->GetErrorYhigh(2));

  
  g0->GetPoint(3, x,y);
  std::cout << x << "  " << y << std::endl;
  g.SetPoint(5,5.5,y);
  g.SetPointError(5, g0->GetErrorXlow(3),g0->GetErrorXhigh(3),g0->GetErrorYlow(3),g0->GetErrorYhigh(3));

  
  g.Print();
  _filenjv4->cd();
  g.Write();
  
  _filenj->Close();
  _filenjv2->Close();
  _filenjv3->Close();
  _filenjv4->Close();
  
}

void   makeMGinputs(){
  
  TFile *_filenjpdf = TFile::Open("expected/fxfx_1D_diffxsec_pdf_uncerts.root");
  TFile *_filenjscale = TFile::Open("expected/fxfx_1D_diffxsec_scale_uncerts.root");
  
  
  TFile *_filenjv4scale = new TFile ("expected/fxfx_1D_diffxsec_scale_njetincl_uncerts.root", "RECREATE");
  TFile *_filenjv4pdf = new TFile ("expected/fxfx_1D_diffxsec_pdf_njetincl_uncerts.root", "RECREATE");

  TH1F* njv4pdf_nom = new TH1F ("n_jetsv4_fidDres_4lsel_nominal","n_jetsv4_fidDres_4lsel_nominal",6,0,6);
  TH1F* njv4pdf_up = new TH1F ("n_jetsv4_fidDres_4lsel_pdf_up","n_jetsv4_fidDres_4lsel_pdf_up",6,0,6);
  TH1F* njv4pdf_dw = new TH1F ("n_jetsv4_fidDres_4lsel_pdf_down","n_jetsv4_fidDres_4lsel_pdf_down",6,0,6);
  
  TH1F* njv4scale_up = new TH1F ("n_jetsv4_fidDres_4lsel_scale_up","n_jetsv4_fidDres_4lsel_scale_up",6,0,6);
  TH1F* njv4scale_dw = new TH1F ("n_jetsv4_fidDres_4lsel_scale_down","n_jetsv4_fidDres_4lsel_scale_down",6,0,6);
  
  
  
  TH1F*mgnj= (TH1F*)_filenjpdf->Get("n_jets_fidDres_4lsel_nominal");
  TH1F*mgnjincl=(TH1F*)_filenjpdf->Get("n_jets_fidDres_4lsel_inclus_nominal");
  TH1F*mgnjpdfup=(TH1F*)_filenjpdf->Get("n_jets_fidDres_4lsel_pdf_up");
  TH1F*mgnjinclpdfup=(TH1F*)_filenjpdf->Get("n_jets_fidDres_4lsel_inclus_pdf_up");
  TH1F*mgnjpdfdw=(TH1F*)_filenjpdf->Get("n_jets_fidDres_4lsel_pdf_down");
  TH1F*mgnjinclpdfdw=(TH1F*)_filenjpdf->Get("n_jets_fidDres_4lsel_inclus_pdf_down");
  TH1F*mgnjscaleup=(TH1F*)_filenjscale->Get("n_jets_fidDres_4lsel_scale_up");
  TH1F*mgnjinclscaleup=(TH1F*)_filenjscale->Get("n_jets_fidDres_4lsel_inclus_scale_up");
  TH1F*mgnjscaledw=(TH1F*)_filenjscale->Get("n_jets_fidDres_4lsel_scale_down");
  TH1F*mgnjinclscaledw=(TH1F*)_filenjscale->Get("n_jets_fidDres_4lsel_inclus_scale_down");
  
  
  makeMGhisto(njv4pdf_nom, mgnj, mgnjincl);
  makeMGhisto(njv4pdf_up, mgnjpdfup, mgnjinclpdfup);
  makeMGhisto(njv4pdf_dw, mgnjpdfdw, mgnjinclpdfdw);
  makeMGhisto(njv4scale_up, mgnjscaleup, mgnjinclscaleup);
  makeMGhisto(njv4scale_dw, mgnjscaledw, mgnjinclscaledw);
  
  _filenjv4pdf->cd();
  
  njv4pdf_nom->Write();
  njv4pdf_up->Write();
  njv4pdf_dw->Write();
  
  _filenjv4scale->cd();
  
  njv4pdf_nom->Write();
  njv4scale_up->Write();
  njv4scale_dw->Write();
}

void makeMGhisto(TH1F* output, TH1F* excl, TH1F* incl){
  
  
  for (int i =0; i < 6; ++i){
    
    if (i<3){
      cout << i << "  " <<excl->GetBinContent(i+1) <<endl;
      output->SetBinContent(i+1, excl->GetBinContent(i+1));
    }
    if (i>=3){
      cout << i+1-2 << "  " << incl->GetBinContent(i+1-2) << endl;
      incl->Print();
      output->SetBinContent(i+1, incl->GetBinContent(i+1-2));
    }
    
    
  }
  
  
  
  
}

