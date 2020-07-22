//#include "MakeUnfoldPlots.h"

std::vector<float> totalXS(std::string mc){
  
  std::vector<TH1F*> *totalvector     = new std::vector<TH1F*>();
  std::vector<TH1F*> *totalupvector   = new std::vector<TH1F*>();
  std::vector<TH1F*> *totaldownvector = new std::vector<TH1F*>();
  
  
  std::vector<float> nominal;
  std::vector<float> scaleup;
  std::vector<float> pdfup;
  std::vector<float> scaledown;
  std::vector<float> pdfdown;
  
  std::vector<std::string> prodmode = {"ggh", "vbf", "wh", "zh", "tth", "bbh"} ;
  
  if(mc == "N3LO"){
    nominal = {48.58,3.782,1.373,0.8839,0.5071,0.488}; // ggF N3LO, vbf, wh, zh, tth, bbh
    scaleup = {3.9, 0.4, 0.5, 3.8, 5.8, 20.2};
    scaledown = {-3.9, -0.3, -0.7, -3.1, -9.2, -23.9};
    pdfup = {3.2, 2.1, 1.9, 1.7, 3.6, 0};
    pdfdown = {-3.2, -2.1, -1.9, -1.7, -3.6, 0};
  }
  else if (mc == "N2LO") {
    nominal = { 42.3,3.782,1.373,0.8839,0.5071,0.488}; // ggF NNLO+NNLL, vbf, wh, zh, tth, bbh
    scaleup = {11.5, 0.4, 0.5, 3.8, 5.8, 20.2};
    scaledown = {-11.5, -0.3, -0.7, -3.1, -9.2, -23.9};
    pdfup = {0, 2.1, 1.9, 1.7, 3.6, 0};
    pdfdown = {0, -2.1, -1.9, -1.7, -3.6, 0};
  }
  else if (mc == "MG5") {
    nominal = {32.75,3.782,1.373,0.8839,0.5071,0.488}; // ggF NNLO+NNLL, vbf, wh, zh, tth, bbh
    scaleup = {16.8, 0.4, 0.5, 3.8, 5.8, 20.2};
    scaledown = {-14.1, -0.3, -0.7, -3.1, -9.2, -23.9};
    pdfup = {1.7, 2.1, 1.9, 1.7, 3.6, 0};
    pdfdown = {-1.7, -2.1, -1.9, -1.7, -3.6, 0};
  }
  else if (mc == "NNLOPS") {
    nominal = {43.98,3.782,1.373,0.8839,0.5071,0.488}; // ggF NNLO+NNLL, vbf, wh, zh, tth, bbh
    scaleup = {9.5, 0.4, 0.5, 3.8, 5.8, 20.2};
    scaledown = {-9.5, -0.3, -0.7, -3.1, -9.2, -23.9};
    pdfup = {3.1, 2.1, 1.9, 1.7, 3.6, 0};
    pdfdown = {-3.1, -2.1, -1.9, -1.7, -3.6, 0};
  }
  
  TH1F *tmpnominal   = NULL;
  TH1F *tmpscaleup   = NULL;
  TH1F *tmppdfup     = NULL;
  TH1F *tmpscaledown = NULL;
  TH1F *tmppdfdown   = NULL;
  
  
  TH1F* hnominal = new TH1F("nominal", "nominal", 1, 0, 1);
  TH1F* hup      = new TH1F("up"     , "up"     , 1, 0, 1);
  TH1F* hdown    = new TH1F("down"   , "down"   , 1, 0, 1);
  
  for(unsigned int i =0 ; i< prodmode.size(); ++i ){
    
    tmpnominal   = new TH1F(prodmode.at(i).c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    tmpscaleup   = new TH1F((prodmode.at(i)+"scaleup").c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    tmppdfup     = new TH1F((prodmode.at(i)+"pdfup").c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    tmpscaledown = new TH1F((prodmode.at(i)+"scaledown").c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    tmppdfdown   = new TH1F((prodmode.at(i)+"pdfdown").c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    
    tmpnominal->SetBinContent(1, nominal.at(i));
    tmpscaleup->SetBinContent(1, nominal.at(i)*(1+std::abs(scaleup.at(i)/100.)));
    tmppdfup->SetBinContent(1, nominal.at(i)*(1+std::abs(pdfup.at(i)/100.)));
    tmpscaledown->SetBinContent(1, nominal.at(i)*(1-std::abs(scaledown.at(i)/100.)));
    tmppdfdown->SetBinContent(1, nominal.at(i)*(1-std::abs(pdfdown.at(i)/100.)));
    
    totalvector->push_back(tmpnominal);
    totalupvector->push_back(tmpscaleup); totalupvector->push_back(tmppdfup);
    totaldownvector->push_back(tmpscaledown); totaldownvector->push_back(tmppdfdown);
    
  }

  makeSys(totalvector, totalupvector, totaldownvector, hnominal, hup, hdown, true);
  
  std::vector<float> values;
  values.push_back( (float)hnominal->GetBinContent(1) );
  values.push_back( (float)hup->GetBinContent(1)      );
  values.push_back( (float)hdown->GetBinContent(1)    );

  /* Cleaning */
  hnominal->Delete();
  hup->Delete();
  hdown->Delete();
  for(uint h=0; h<totalvector->size(); h++){
    totalvector->at(h)->Delete();
  }
  for(uint h=0; h<totalupvector->size(); h++){
    totalupvector->at(h)->Delete();
    totaldownvector->at(h)->Delete();
  }
  totalvector->clear();
  totalupvector->clear();
  totaldownvector->clear();

  return values;

}

std::vector<float> totalXS(bool N3LO, std::string ProdMode){
  
  std::vector<TH1F*> *totalvector     = new std::vector<TH1F*>();
  std::vector<TH1F*> *totalupvector   = new std::vector<TH1F*>();
  std::vector<TH1F*> *totaldownvector = new std::vector<TH1F*>();
  

  std::map<std::string,float> nominal;
  std::map<std::string,float> scaleup;
  std::map<std::string,float> pdfup;
  std::map<std::string,float> scaledown;
  std::map<std::string,float> pdfdown;
  
  std::vector<std::string> prodmode;
  if(ProdMode=="all")
    prodmode = {"ggh", "vbf", "wh", "zh", "tth", "bbh"};
  else
    prodmode = {ProdMode};
  
  if(N3LO){
    nominal   ["ggh"] = 48.58;
    scaleup   ["ggh"] = 3.9;
    scaledown ["ggh"] = -3.9;
    pdfup     ["ggh"] = 3.2;
    pdfdown   ["ggh"] = -3.2;
  }
  else{
    nominal   ["ggh"] = 44.14;
    scaleup   ["ggh"] = 4.7;
    scaledown ["ggh"] = -4.7;
  }
  nominal ["vbf"] = 3.782;
  nominal ["wh"]  = 1.373;
  nominal ["zh"]  = 0.8839;
  nominal ["tth"] = 0.5071;
  nominal ["bbh"] = 0.488;
  
  scaleup ["vbf"] = 0.4;
  scaleup ["wh"]  = 0.5;
  scaleup ["zh"]  = 3.8;
  scaleup ["tth"] = 5.8;
  scaleup ["bbh"] = 20.2;

  scaledown ["vbf"] = -0.3;
  scaledown ["wh"]  = -0.7;
  scaledown ["zh"]  = -3.1;
  scaledown ["tth"] = -9.2;
  scaledown ["bbh"] = -23.9;

  pdfup ["vbf"] = 2.1;
  pdfup ["wh"]  = 1.9;
  pdfup ["zh"]  = 1.7;
  pdfup ["tth"] = 3.6;
  pdfup ["bbh"] = 0;

  pdfdown ["vbf"] = -2.1;
  pdfdown ["wh"]  = -1.9;
  pdfdown ["zh"]  = -1.7;
  pdfdown ["tth"] = -3.6;
  pdfdown ["bbh"] = 0;

  TH1F *tmpnominal   = NULL;
  TH1F *tmpscaleup   = NULL;
  TH1F *tmppdfup     = NULL;
  TH1F *tmpscaledown = NULL;
  TH1F *tmppdfdown   = NULL;
  
  
  TH1F* hnominal = new TH1F("nominal", "nominal", 1, 0, 1);
  TH1F* hup      = new TH1F("up"     , "up"     , 1, 0, 1);
  TH1F* hdown    = new TH1F("down"   , "down"   , 1, 0, 1);
  
  for(unsigned int i =0 ; i< prodmode.size(); ++i ){
    
    tmpnominal   = new TH1F(prodmode.at(i).c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    tmpscaleup   = new TH1F((prodmode.at(i)+"scaleup").c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    tmppdfup     = new TH1F((prodmode.at(i)+"pdfup").c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    tmpscaledown = new TH1F((prodmode.at(i)+"scaledown").c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    tmppdfdown   = new TH1F((prodmode.at(i)+"pdfdown").c_str(),prodmode.at(i).c_str(), 1, 0, 1);
    
    tmpnominal->SetBinContent(1, nominal[prodmode.at(i)]);
    tmpscaleup->SetBinContent(1, nominal[prodmode.at(i)]*(1+std::abs(scaleup[prodmode.at(i)]/100.)));
    tmppdfup->SetBinContent(1, nominal[prodmode.at(i)]*(1+std::abs(pdfup[prodmode.at(i)]/100.)));
    tmpscaledown->SetBinContent(1, nominal[prodmode.at(i)]*(1-std::abs(scaledown[prodmode.at(i)]/100.)));
    tmppdfdown->SetBinContent(1, nominal[prodmode.at(i)]*(1-std::abs(pdfdown[prodmode.at(i)]/100.)));
    
    totalvector->push_back(tmpnominal);
    totalupvector->push_back(tmpscaleup); totalupvector->push_back(tmppdfup);
    totaldownvector->push_back(tmpscaledown); totaldownvector->push_back(tmppdfdown);
    
  }
  
  makeSys(totalvector, totalupvector, totaldownvector, hnominal, hup, hdown, true);
  
  std::vector<float> values;
  values.push_back( (float)hnominal->GetBinContent(1) );
  values.push_back( (float)hup->GetBinContent(1)      );
  values.push_back( (float)hdown->GetBinContent(1)    );

  /* Cleaning */
  hnominal->Delete();
  hup->Delete();
  hdown->Delete();
  for(uint h=0; h<totalvector->size(); h++){
    totalvector->at(h)->Delete();
  }
  for(uint h=0; h<totalupvector->size(); h++){
    totalupvector->at(h)->Delete();
    totaldownvector->at(h)->Delete();
  }
  totalvector->clear();
  totalupvector->clear();
  totaldownvector->clear();

  return values;

}

double evalPValue(TH1F* h, std::string MC, std::string var, bool normalized){
  
  int offsetbin=0; 
  if(var=="pt0j") {offsetbin=0;}
  if(var=="pt1j") {offsetbin=4;}
  if(var=="pt2j") {offsetbin=9;}
  
  if(var=="pt0j"||var=="pt1j"||var=="pt2j") var = "ptpt";
  std::string scanname;
  std::string scanfilename;
  double NLL =0.;
  for(int i=1; i<h->GetNbinsX()+1; ++i){
    scanname = "sigma_bin"+std::to_string(i+offsetbin-1);
    scanfilename = "scan_"+var+"__"+ scanname+"_wsysdata.root";
    TFile scanfile( ("../ws_output/"+scanfilename).c_str()  );
    TGraph* scan = (TGraph*)scanfile.Get(scanname.c_str());
    NLL+=scan->Eval(h->GetBinContent(i)*m_integralobs);
  }
  
  
  int dof = h->GetNbinsX();
  if (normalized) dof = dof -1;
  std::cout  << MC << " " << var << "       "
	     <<  ROOT::Math::chisquared_cdf_c(NLL, dof) << std::endl;
  return ROOT::Math::chisquared_cdf_c(NLL, dof) ;
  
}

double evalPValuePtPt(std::string MC, bool normalized){
  
  std::vector<std::string> prodmode = {"VBF","WH", "ZH", "ttH", "bbH"};
  if (MC=="nnlops") prodmode.push_back("ggHNNLOPS");
  
  TFile *_fileStandard = TFile::Open("expected/standard.root");
  TFile *_fileMG = TFile::Open("expected/fxfx_2D_diffxsec_scale_uncerts_merged.root");
  TFile *_fileobs = TFile::Open("../ws_output/fit_ptpt__wsysdata_TGunfolded.root");

  
  TH1F *tmp0j = NULL;
  TH1F *tmp1j = NULL;
  TH1F *tmp2j = NULL;
  
  double Pt0jPt1jRange[] = {  0.0,  15.0,  30.0, 120.0, 350.0,
    380.0, 410.0, 430.0, 470.0, 700.0,
    820.0, 1050.0};
  
  Int_t Pt0jPt1jBins = ( (sizeof Pt0jPt1jRange) / (sizeof *Pt0jPt1jRange) )-1;
  
  TH1F *hptpt = new TH1F ("hptpt", "hptpt", Pt0jPt1jBins, Pt0jPt1jRange);
  
  for (unsigned int i =0; i < prodmode.size(); ++i){
    
    tmp0j = (TH1F*)_fileStandard->Get(("pt0j_"+prodmode.at(i)).c_str());
    tmp1j = (TH1F*)_fileStandard->Get(("pt1j_"+prodmode.at(i)).c_str());
    tmp2j = (TH1F*)_fileStandard->Get(("pt2j_"+prodmode.at(i)).c_str());
    int counter =0;
    
    for (int j=0; j<tmp0j->GetNbinsX();++j){
      counter++;
      hptpt->AddBinContent(counter, tmp0j->GetBinContent(j+1)/hptpt->GetBinWidth(counter));
    }
    for (int j=0; j<tmp1j->GetNbinsX();++j){
      counter++;
      hptpt->AddBinContent(counter, tmp1j->GetBinContent(j+1)/hptpt->GetBinWidth(counter));
    }
    for (int j=0; j<tmp2j->GetNbinsX();++j){
      counter++;
      hptpt->AddBinContent(counter, tmp2j->GetBinContent(j+1)/hptpt->GetBinWidth(counter));
    }
    
  }
  
  if (MC=="mg5"){
    tmp0j = (TH1F*)_fileMG->Get("n_jets_fidDres_4lsel_higgs_pt_fidDres_4lsel_nj_0_nom");
    tmp1j = (TH1F*)_fileMG->Get("n_jets_fidDres_4lsel_higgs_pt_fidDres_4lsel_nj_1_nom");
    tmp2j = (TH1F*)_fileMG->Get("n_jets_fidDres_4lsel_higgs_pt_fidDres_4lsel_nj_geq2_nom");
    
    
    if (m_doN3LO){
      double scaleMG= 48600/(4.1138/1.25e-04);
      tmp0j->Scale(scaleMG);
      tmp1j->Scale(scaleMG);
      tmp2j->Scale(scaleMG);
    }
    
    int counter =0;
    
    for (int j=0; j<tmp0j->GetNbinsX();++j){
      counter++;
      hptpt->AddBinContent(counter, tmp0j->GetBinContent(j+1));
    }
    for (int j=0; j<tmp1j->GetNbinsX();++j){
      counter++;
      hptpt->AddBinContent(counter, tmp1j->GetBinContent(j+1));
    }
    for (int j=0; j<tmp2j->GetNbinsX();++j){
      counter++;
      hptpt->AddBinContent(counter, tmp2j->GetBinContent(j+1));
    }
    
    
  }
  

  if (normalized){
    TH1F *obsh = (TH1F *)hptpt->Clone("obshptpt");// obsh->Reset();
    TGraphAsymmErrors* obs1 = (TGraphAsymmErrors*)_fileobs->Get("ptpt");

    for (int i = 0; i < obs1->GetN(); ++i){
      double x; double y;
      obs1->GetPoint(i, x, y);
      obsh->SetBinContent(i+1,y);
    }
    hptpt->Scale(1./hptpt->Integral());
    m_integralobs =obsh->Integral();
    delete obsh;
  }
  std::string scanname;
  std::string scanfilename;
  double NLL =0.;
  for(int i=1; i<hptpt->GetNbinsX()+1; ++i){
    scanname = "sigma_bin"+std::to_string(i-1);
    scanfilename = "scan_ptpt__"+ scanname+"_wsysdata.root";
    TFile scanfile( ("../ws_output/"+scanfilename).c_str()  );
    TGraph* scan = (TGraph*)scanfile.Get(scanname.c_str());
    NLL+=scan->Eval(hptpt->GetBinContent(i)*m_integralobs);
  }
  
  //_fileStandard->Close();
  //_fileMG->Close();
  std::cout  << MC << " ptpt       "
  <<  ROOT::Math::chisquared_cdf_c(NLL, hptpt->GetNbinsX()) << std::endl;
  return ROOT::Math::chisquared_cdf_c(NLL, hptpt->GetNbinsX()) ;
  
}

void CheckOutDir(){

  struct stat st;
  m_OutDir = "../varsDistro/unfold/";
  if(stat(m_OutDir.c_str(),&st) == 0){
    std::cout << "\033[1;39m <MakeUnfoldPlots()> \033[0m"
	      << "\033[1;32m Out Directory " << m_OutDir
	      << " already present!\033[0m" << std::endl;
  }
  else{
    std::cout << "\033[1;39m <MakeUnfoldPlots()> \033[0m"
	      << "\033[1;34m Creating Directory " << m_OutDir
	      << " ... \033[0m" << std::endl;
    int outD = system( ("mkdir "+m_OutDir).c_str() );
    if(outD!=0)
    std::cout << "\033[1;39m <MakeUnfoldPlots()> \033[0m"
	      << "\033[1;31m Directory " << m_OutDir
	      << " could not be created!\033[0m" << std::endl;
  }
  
}

TH1F* CreateDummyPlot(TH1F* In, std::string name, std::string var){

  TH1F*dummy = NULL;
  if(var!="mjj") dummy = (TH1F*)In->Clone( name.c_str() );
  else{
    double MjjrmRange[] = {0.0, 1.0, 4.0};
    Int_t MjjrmBins = ( (sizeof MjjrmRange)  / (sizeof *MjjrmRange)  )-1;
    dummy = new TH1F( name.c_str(),name.c_str(),MjjrmBins,MjjrmRange );
  }
  dummy->Reset();
  dummy->SetLineColor(0);
  return dummy;
  
}

std::pair<double,double> GetBarSize(std::string var){

  std::pair<double,double> m_val;
  if( var=="m12m34" || var=="pt0j"  || var=="pt1j" || var=="mjj" ||
      var=="ljpt"   || var=="njet"  || var=="pt"   || var=="njetv4" )
    m_val = std::make_pair(0.05,0.05); //1.00
  else if(var=="nbjet" || var=="pt2j")
    m_val = std::make_pair(0.025,0.025); //1.00
  else if(var=="y")
    m_val = std::make_pair(0.01,0.01); //0.3
  else if(var=="cts")
    m_val = std::make_pair(0.006,0.006); //0.125;
  else if(var=="m12")
    m_val = std::make_pair(0.5,0.4); //6.00;
  else if(var=="m34")
    m_val = std::make_pair(0.3,0.2); //4.00;
  else if(var=="etajj")
    m_val = std::make_pair(0.1,0.1); //2.00;
  else if(var=="phijj")
    m_val = std::make_pair(0.07,0.07); //3.14

  return m_val;
}


double GetBarSpacing(std::string var){

  double m_val = 0;
  if( var=="m12m34" || var=="pt0j"  || var=="pt1j" || var=="pt2j" ||
      var=="mjj"    || var=="ljpt"  || var=="njet" || var=="pt"   ||
      var=="njetv4" )
    m_val = 0.15;
  else if(var=="nbjet" )
    m_val = 0.10;
  else if(var=="y")
    m_val = 0.05;
  else if(var=="cts")
    m_val = 0.02;
  else if(var=="m12")
    m_val = 1.20;
  else if(var=="m34")
    m_val = 0.90;
  else if(var=="etajj")
    m_val = 0.40;
  else if(var=="phijj")
    m_val = 0.30;

  return m_val;
  
}

double evalIntegral(TH1F* h){
  
  
  double area =0;
  
  for (int i =1; i < h->GetNbinsX()+1; ++i){
    
    area+= h->GetBinContent(i)*h->GetBinWidth(i);
  }
  
  return area;
  
}

void evalPValueFid (std::vector<double> v){
  
  std::vector<std::string> scanname     = { "_4mu", "_4e", "_2mu2e", "_2e2mu",
					    "_4l", "_2l2l", "_sum", "", "" };
  std::vector<std::string> scanfilename = { "fidchannel__sigma_4mu", "fidchannel__sigma_4e",
					    "fidchannel__sigma_2mu2e", "fidchannel__sigma_2e2mu",
					    "fid4l__sigma_4l", "fid2l2l__sigma_2l2l",
					    "fidsum__sigma_sum","comb__sigma","total__sigma"};
  
  std::vector<std::string> channels = {"4mu  ","4e   ", "2mu2e","2e2mu","4l   ","2l2l ","sum  ","comb ","total"};
  for(uint i=0; i<v.size(); ++i){
    
    //scanname = "sigma_bin"+std::to_string(i+offsetbin-1);
    TFile scanfile( ("../ws_output/""scan_m_"+scanfilename.at(i)+"_wsysdata.root").c_str()  );
    TGraph* scan = (TGraph*)scanfile.Get(("sigma"+scanname.at(i)).c_str());

    std::cout  <<  "sigma "<<channels.at(i) << "    p-value  : "<<  100*RooStats::SignificanceToPValue(sqrt(scan->Eval(v.at(i))))*2<<"%"  << std::endl;
    //NLL+=scan->Eval(h->GetBinContent(i)*m_integralobs);
  }
  
  //std::cout  << MC << " " << var << "       "
  //<<  ROOT::Math::chisquared_cdf_c(NLL, h->GetNbinsX()) << std::endl;
  //return ROOT::Math::chisquared_cdf_c(NLL, h->GetNbinsX()) ;

}
