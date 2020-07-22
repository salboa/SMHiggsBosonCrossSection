#include "doPlots.h"

void doPlots :: LoadInputFile(){
  
  m_f = new TFile( (m_OutDirPrefix+m_filename).c_str() );
  if( m_f->IsZombie() ){
    std::cout << "\033[1;39m <doPlots::LoadInputFile()>  \033[0m"
	      << "\033[1;31m Input file " << m_filename << " missing \033[0m"
	      << std::endl;
    exit(0);
  }
  
}

void doPlots :: CheckOutDir(){

  struct stat st;
  m_OutDir = m_OutDirPrefix+"plots";
  if(stat(m_OutDir.c_str(),&st) == 0){
    std::cout << "\033[1;39m <doPlots::CheckOutDir()>  \033[0m"
	      << "\033[1;32m Out Directory " << m_OutDir
	      << " already present!\033[0m" << std::endl;
  }
  else{
    std::cout << "\033[1;39m  <doPlots::CheckOutDir()>  \033[0m"
	      << "\033[1;34m Creating Directory " << m_OutDir
	      << " ... \033[0m" << std::endl;
    int outD = system( ("mkdir "+m_OutDir).c_str() );
    if(outD!=0)
    std::cout << "\033[1;39m  <doPlots::CheckOutDir()>  \033[0m"
	      << "\033[1;31m Directory " << m_OutDir
	      << " could not be created!\033[0m" << std::endl;
  }
  
}

double doPlots :: getSignificance(std::vector<double> val,
				  bool Asyntotic){

  double m_val=1;
  double s = val.at(0);
  double b = getBkgTot(val); //val.at(1);
  if(Asyntotic)
    m_val = sqrt( 2*( (s+b)*log(1+s/b)-s ) );
  else
    m_val = s/sqrt(s+b);
  return m_val;
  
}

double doPlots :: getBkgTot(std::vector<double> val){

  double b=0;
  for(uint i=1; i<val.size(); i++){
    b += val.at(i);
  }
  return b;
  
}

std::vector<std::string> doPlots :: GetBinsName(TH2F* t){

  std::vector<std::string> m_names;
  std::string edge = "0";
  for (int i=1; i <t->GetNbinsX()+2; ++i) {
    if( GetLabel( t->GetName() ) == "mjj" && i>2){
      edge = ConvertToStringWithPrecision( t->GetXaxis()->GetBinLowEdge(i),4 );
    }
    else{
      edge = ConvertToStringWithPrecision( t->GetXaxis()->GetBinLowEdge(i),3 );
    }
    m_names.push_back(edge);
  }
  return m_names;
  
}

std::string doPlots :: GetLabel(TString name){

  std::string m_lb = "";
  if ( name.Contains("m12vsm34") )   m_lb = "m12vsm34";
  else if( name.Contains("m12") )    m_lb = "m12";
  else if( name.Contains("m34") )    m_lb = "m34";
  else if( name.Contains("pt2j") )   m_lb = "pt2j";
  else if( name.Contains("pt1j") )   m_lb = "pt1j";
  else if( name.Contains("pt0j") )   m_lb = "pt0j";
  else if( name.Contains("pt") )     m_lb = "pt";
  else if( name.Contains("cts") )    m_lb = "cts";
  else if( name.Contains("y") )      m_lb = "y";
  else if( name.Contains("njetv2") ) m_lb = "njetv2";
  else if( name.Contains("njetv3") ) m_lb = "njetv3";
  else if( name.Contains("njet") )   m_lb = "njet";
  else if( name.Contains("ljet") )   m_lb = "ljpt";
  else if( name.Contains("mjj") )    m_lb = "mjj";
  else if( name.Contains("etajj") )  m_lb = "etajj";
  else if( name.Contains("phijj") )  m_lb = "phijj";

  return m_lb;
  
}

std::string doPlots :: DetectHisto(TString name){

  std::string m_lb = "";
  if ( name.Contains("hm12m34_") )     m_lb = "m12m34";
  else if( name.Contains("hm12_") )    m_lb = "m12";
  else if( name.Contains("hm34_") )    m_lb = "m34";
  else if( name.Contains("hm34b_") )   m_lb = "m34";
  else if( name.Contains("hmjj_") )    m_lb = "mjj";
  else if( name.Contains("hmjjrm_") )  m_lb = "mjj";
  else if( name.Contains("hm") )       m_lb = "m";
  else if( name.Contains("hy") )       m_lb = "y";
  else if( name.Contains("hcts_") )    m_lb = "cts";
  else if( name.Contains("hpt2j_") )   m_lb = "ptpt";
  else if( name.Contains("hpt1j_") )   m_lb = "ptpt";
  else if( name.Contains("hpt0j_") )   m_lb = "ptpt";
  else if( name.Contains("hpt_") )     m_lb = "pt";
  else if( name.Contains("hnjet_") )   m_lb = "njet";
  else if( name.Contains("hnjetv2_") ) m_lb = "njetv2";
  else if( name.Contains("hnjetv3_") ) m_lb = "njetv3";
  else if( name.Contains("hljpt_") )   m_lb = "ljpt";
  else if( name.Contains("hetajj_") )  m_lb = "etajj";
  else if( name.Contains("hphijj_") )  m_lb = "phijj";
  else if( name.Contains("hnbjet_") )  m_lb = "nbjet";

  return m_lb;
  
}

std::string doPlots :: DetectMassHisto(TString name){

  std::string m_lb = "";
  if ( name.Contains("hm_ptbin") )          m_lb = "pt";
  else if( name.Contains("hm_pt0jbin") )    m_lb = "ptpt";
  else if( name.Contains("hm_pt1jbin") )    m_lb = "ptpt";
  else if( name.Contains("hm_pt2jbin") )    m_lb = "ptpt";
  else if( name.Contains("hm_ctsbin") )     m_lb = "cts";
  else if( name.Contains("hm_ybin") )       m_lb = "y";
  else if( name.Contains("hm_m12bin") )     m_lb = "m12";
  else if( name.Contains("hm_m34bin") )     m_lb = "m34";
  else if( name.Contains("hm_njetbin") )    m_lb = "njet";
  else if( name.Contains("hm_nbjetbin") )   m_lb = "nbjet";
  else if( name.Contains("hm_ljptbin") )    m_lb = "ljpt";
  else if( name.Contains("hm_mjjbin") )     m_lb = "mjj";
  else if( name.Contains("hm_etajjbin") )   m_lb = "etajj";
  else if( name.Contains("hm_phijjbin") )   m_lb = "phijj";
  else if( name.Contains("hm_"+m_channel) ) m_lb = "m";
  
  return m_lb;
  
}

std::string doPlots :: GetAxisLabel(TString name){

  std::string m_lb = "";
  if ( name.Contains("m12vsm34") )   m_lb = "Bin_{m12vsm34}";
  else if( name.Contains("m12m34") ) m_lb = "#font[12]{m}_{12} vs #font[12]{m}_{34} bins";
  else if( name.Contains("m12") )    m_lb = "#font[12]{m}_{12} [GeV]";
  else if( name.Contains("m34") )    m_lb = "#font[12]{m}_{34} [GeV]";
  else if( name.Contains("hm_") ){
    if(name.Contains("incl") )       m_lb = "#font[12]{m}_{4l} [GeV]";
    else if(name.Contains("4mu") )   m_lb = "#font[12]{m}_{4#mu} [GeV]";
    else if(name.Contains("4e") )    m_lb = "#font[12]{m}_{4e} [GeV]";
    else if(name.Contains("2mu2e") ) m_lb = "#font[12]{m}_{2#mu2e} [GeV]";
    else if(name.Contains("2e2mu") ) m_lb = "#font[12]{m}_{2e2#mu} [GeV]";
  }
  else if( name.Contains("njet") )   m_lb = "#font[12]{N}_{jets}";
  else if( name.Contains("nbjet") )  m_lb = "#font[12]{N}_{b-jets}";
  else if( name.Contains("cts") )    m_lb = "|cos#theta*|";
  else if( name.Contains("y") )      m_lb = "#left|#font[12]{y}_{4#font[12]{l}}#right|"; //|#font[12]{y}_{4l}|";
  else if( name.Contains("ljpt") )   m_lb = "#font[12]{p}_{T}^{lead. jet} [GeV]";
  else if( name.Contains("mjj") )    m_lb = "#font[12]{m}_{jj} [GeV]";
  else if( name.Contains("etajj") )  m_lb = "#Delta#eta_{jj}";
  else if( name.Contains("phijj") )  m_lb = "#Delta#phi_{jj} [rad]";
  else if( name.Contains("pt0j") )   m_lb = "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0} [GeV]";
  else if( name.Contains("pt1j") )   m_lb = "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1} [GeV]";
  else if( name.Contains("pt2j") )   m_lb = "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq2} [GeV]";
  else if( name.Contains("pt") )     m_lb = "#font[12]{p}_{T,4#font[12]{l}} [GeV]";

  return m_lb;
  
}

bool doPlots :: isDiffVar(TString name){

  bool m_reply = true;
  std::string Variable = DetectHisto(name);
  if(Variable!="pt"     && Variable!="m12"    && Variable!="m34"   &&
     Variable!="etajj"  && Variable!="njet"   && Variable!="mjj"   &&
     Variable!="cts"    && Variable!="ljpt"   && Variable!="y"     &&
     Variable!="m12m34" && Variable!="ptpt"   && Variable!="phijj" &&
     Variable!="nbjet"  && Variable!="njetv2" && Variable!="njetv3" ){

    m_reply = false;

  }

  return m_reply;
  
}

bool doPlots :: isDiffVarMass(TString name){

  bool m_reply = true;
  std::string Variable = DetectMassHisto(name);
  if(Variable!="pt"     && Variable!="m12"   && Variable!="m34"  &&
     Variable!="etajj"  && Variable!="phijj" && Variable!="njet" &&
     Variable!="mjj"    && Variable!="cts"   && Variable!="ljpt" &&
     Variable!="y"      && Variable!="ptpt"  && Variable!="nbjet"  ){

    m_reply = false;

  }

  return m_reply;
  
}

bool doPlots :: isMass(TString name){

  bool m_reply = true;
  std::string Variable = DetectMassHisto(name);
  if(Variable!="m") m_reply = false;
  return m_reply;
  
}

bool doPlots :: useSystematicBand(TString name){

  bool m_check = false;
  if(m_drawSyst && ( isDiffVar(name) || isDiffVarMass(name) || isMass(name) ) )
    m_check = true;

  return m_check;
     
}

int doPlots :: GetHistoBin(TString name){

  int bin = -1;
  if( name.Contains("bin0")       ){ bin = 1;  }
  else if( name.Contains("bin1")  ){ bin = 2;  }
  else if( name.Contains("bin2")  ){ bin = 3;  }
  else if( name.Contains("bin3")  ){ bin = 4;  }
  else if( name.Contains("bin4")  ){ bin = 5;  }
  else if( name.Contains("bin5")  ){ bin = 6;  }
  else if( name.Contains("bin6")  ){ bin = 7;  }
  else if( name.Contains("bin7")  ){ bin = 8;  }
  else if( name.Contains("bin8")  ){ bin = 9;  }
  else if( name.Contains("bin9")  ){ bin = 10; }
  else if( name.Contains("bin10") ){ bin = 11; }
  
  return bin;
  
}

std::string doPlots :: ConvertToStringWithPrecision(double value, int n){
  
  std::ostringstream out;
  out << std::setprecision(n) << value;
  return out.str();
  
}

void doPlots :: CreateTableHeader(){

  /* first line */
  m_tableFile << " \\begin{tabular}{ c | c | c |";
  if(m_useZjets)
    m_tableFile << " c |";

  m_tableFile << " c | c | c | c";

  if(m_useData)
    m_tableFile << " | c";

  m_tableFile << " }\n";

  /*second line */
  m_tableFile << " Bin & Signal & $ZZ$ & ";

  if(m_useZjets)
    m_tableFile << "$Z$+jets / $t\\bar{t}$ & ";

  m_tableFile << "$t\\bar{t}V$ + $VVV$ & S/B & $\\sigma$ & $Z_{0}$ ";

  if(m_useData)
    m_tableFile << "& Data (obs)";

  m_tableFile << "  \\\\\n \\hline \n";
  
}

void doPlots :: FillTableBin(int i){

  int prec = 0;
  if(i>8) prec = 2;

  m_tableFile << (" "+ConvertToStringWithPrecision((i),prec)+"  & ").c_str();
  
}

void doPlots :: FillTableRow(std::vector<TH1F*> list_histo,
			     std::vector<double> SigBkg,
			     int i){

  m_tableFile << (ConvertToStringWithPrecision((list_histo.at(1)->GetBinContent(i+1)*list_histo.at(1)->GetBinWidth(i+1)), 2)+" & ").c_str();  //signal
  m_tableFile << (ConvertToStringWithPrecision((list_histo.at(2)->GetBinContent(i+1)*list_histo.at(2)->GetBinWidth(i+1)), 2)+" & ").c_str(); //ZZ

  if(m_useZjets){
    int p = list_histo.size()-1;
    m_tableFile << (ConvertToStringWithPrecision((list_histo.at(p)->GetBinContent(i+1)*list_histo.at(p)->GetBinWidth(i+1)), 2)+" & ").c_str(); //Z+jets
  }

  int pMb = -1;
  if(m_useZjets) pMb =  list_histo.size()-2;
  else pMb =  list_histo.size()-1;
  m_tableFile << (ConvertToStringWithPrecision((list_histo.at(pMb)->GetBinContent(i+1)*list_histo.at(pMb)->GetBinWidth(i+1)), 2)+" & ").c_str(); //multiB
    
  m_tableFile << (ConvertToStringWithPrecision(SigBkg.at(0)/getBkgTot(SigBkg),2)+" & ").c_str(); // S/B
  m_tableFile << (ConvertToStringWithPrecision(getSignificance(SigBkg,false),2)+"  & ").c_str(); // sigma
  m_tableFile << (ConvertToStringWithPrecision(getSignificance(SigBkg,true),2)+" ").c_str(); // Z_0

  if(m_useData)
    m_tableFile << (" & "+ConvertToStringWithPrecision( (list_histo.at(0)->GetBinContent(i+1)*list_histo.at(0)->GetBinWidth(i+1)), 2)).c_str(); //data
  
  m_tableFile << " \\\\\n";
      
}

void doPlots :: DrawVarBinEdges(TString name){

  std::string range = "";
  if( name.Contains("pt") ){
    if( name.Contains("bin0") )       range = "0 GeV < #font[12]{p}_{T,4l} < 10 GeV";
    else if( name.Contains("bin9") )  range = "200 GeV < #font[12]{p}_{T,4l} < 350 GeV";
  }
  
  TLatex Range;
  Range.SetNDC();
  Range.SetTextFont(42);
  Range.SetTextSize(0.030);
  Range.SetTextColor(kBlack);
  Range.DrawLatex( 0.18,0.77,range.c_str() );
  
}

TH1F* doPlots :: GetMassPlot(TFile *f, TString Name){

  TH1F *h = (TH1F*)f->Get( Name);
  TH1F *m = new TH1F("m","m",15,115,130);

  for(int i=0; i<h->GetNbinsX(); i++){
    m->SetBinContent(i+1,h->GetBinContent(i+1));
  }
  return m;
  
}
