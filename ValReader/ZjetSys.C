/* 
   script to translate the shit that red bkg people provide
   it's clear that they need a psychoanalyst
 */

/* program includes */
#include "ZjetSys.h"

int main( int argc, char* argv[] ) {

  bool printHelp = false;
  bool Fiducial  = false;
  bool debug     = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--Fiducial")   ){ Fiducial  = true; }
    else if( !strcmp(argv[i],"--debug") ){ debug     = true; }
    else if( !strcmp(argv[i],"--help")  ){ printHelp = true; }
  }
  if( printHelp ){
    std::cout << "ZjetSys: make systematics Z+jets inputs !!" << std::endl;
    std::cout << "  Usage  :  ZjetSys [Options]"         << std::endl;
    std::cout << "             --Fiducial [Fiducial measurement: default 'false']"  << std::endl;
    std::cout << "             --debug    [Set debug mode: default is 'false']"     << std::endl;
    std::cout << "             --help     [Print this help]"                        << std::endl;
    exit(0);
  }
  if( debug ){
    std::cout << " <ZjetSys()> :: Running with Options: "   << std::endl;
    std::cout << "                 Fiducial = " << Fiducial << std::endl;
    std::cout << "                 debug    = " << debug    << std::endl;
  }
  
  redBkgSys(Fiducial, debug);
  
}

void redBkgSys(bool Fiducial, bool debug){

  m_isFid = Fiducial;
  m_debug = debug;
  
  Y4mu   = 1.25 / 36.1;
  Y4e    = 1.24 / 36.1;
  Y2e2mu = 1.04 / 36.1;
  Y2mu2e = 1.33 / 36.1;
  Ytotal = 4.80 / 36.1;

  m_In =  new TFile( "../MC_Inputs/mc15c/shapes_SignalRegion.root" );

  if(m_isFid)
    doFiducial();
  else
    doDifferential();

  /* Cleaning */
  m_In->Close();
  
  
}

void doDifferential(){

  if(m_debug)
    std::cout << "<ZjetSys()> :: Evaluating Z+jets Sys for Differential" << std::endl;
  
  std::vector<std::string> var = {"pt4l", "njets", "pt4l", "pt4l", "pt4l",
				  "m34", "m12", "cts","nbjets","jet1pt", "y4l",
				  "m12m34", "mjj","detajj","dphijj"};
  
  std::vector<std::string> folder = {"pt", "njet", "pt0j", "pt1j", "pt2j",
				     "m34", "m12", "cts","nbjet","ljpt", "y",
				     "m12m34", "mjj","etajj","phijj"};

  std::vector <std::string> idiots = {"incl", "incl", "0Jet", "1Jet", "ge2Jet",
				      "incl", "incl", "incl", "incl", "ge1Jet",
				      "incl", "incl", "ge2Jet", "ge2Jet",
				      "ge2Jet"};
  
  
  for(uint i=0; i<var.size(); ++i){
    evalSys( var.at(i),folder.at(i),idiots.at(i) );
  }
  
  gSystem->Exec("cp Values/Diff/pt0j/Sys/redBkg* Values/Diff/ptpt/Sys/");
  gSystem->Exec("cp Values/Diff/pt1j/Sys/redBkg_bin0.dat Values/Diff/ptpt/Sys/redBkg_bin4.dat");
  gSystem->Exec("cp Values/Diff/pt1j/Sys/redBkg_bin1.dat Values/Diff/ptpt/Sys/redBkg_bin5.dat");
  gSystem->Exec("cp Values/Diff/pt1j/Sys/redBkg_bin2.dat Values/Diff/ptpt/Sys/redBkg_bin6.dat");
  gSystem->Exec("cp Values/Diff/pt1j/Sys/redBkg_bin3.dat Values/Diff/ptpt/Sys/redBkg_bin7.dat");
  gSystem->Exec("cp Values/Diff/pt1j/Sys/redBkg_bin4.dat Values/Diff/ptpt/Sys/redBkg_bin8.dat");
  gSystem->Exec("cp Values/Diff/pt2j/Sys/redBkg_bin0.dat Values/Diff/ptpt/Sys/redBkg_bin9.dat");
  gSystem->Exec("cp Values/Diff/pt2j/Sys/redBkg_bin1.dat Values/Diff/ptpt/Sys/redBkg_bin10.dat");

}

void doFiducial(){

  if(m_debug)
    std::cout << "<ZjetSys()> :: Evaluating Z+jets Sys for Fiducial" << std::endl;

  std::vector<std::string> chans = {"4mu", "4e", "2mu2e", "2e2mu", "incl"};
  
  for(uint i=0; i<chans.size(); i++){
    evalSys( "m4l", chans.at(i), "incl" );
  }
  
}

void evalSys(std::string var, std::string folder, std::string idiots){

  if(m_debug)
    std::cout << "<ZjetSys()> :: Loading histograms" << std::endl;
  
  h4mu = (TH1F*)m_In->Get( (var+"/"+idiots+"/2l2mu/h_shape_"+var+"_"+idiots+"_2l2mu").c_str() );
  h4mu->SetNameTitle( ("h"+var+"_4mu_redBkg").c_str() , ("h"+var+"_4mu_redBkg").c_str() );
  h4mu->Scale( Y4mu/h4mu->Integral() );

  h4e = (TH1F*)m_In->Get( (var+"/"+idiots+"/2l2e/h_shape_"+var+"_"+idiots+"_2l2e").c_str() );
  h4e->SetNameTitle( ("h"+var+"_4e_redBkg").c_str() , ("h"+var+"_4e_redBkg").c_str() );
  h4e->Scale( Y4e / h4e->Integral() );

  h2mu2e = (TH1F*)m_In->Get( (var+"/"+idiots+"/2l2e/h_shape_"+var+"_"+idiots+"_2l2e").c_str() );
  h2mu2e->SetNameTitle( ("h"+var+"_2mu2e_redBkg").c_str() , ("h"+var+"_2mu2e_redBkg").c_str() );
  h2mu2e->Scale( Y2mu2e / h2mu2e->Integral() );

  h2e2mu = (TH1F*)m_In->Get( (var+"/"+idiots+"/2l2mu/h_shape_"+var+"_"+idiots+"_2l2mu").c_str() );
  h2e2mu->SetNameTitle( ("h"+var+"_2e2mu_redBkg").c_str() , ("h"+var+"_2e2mu_redBkg").c_str() );
  h2e2mu->Scale( Y2e2mu / h2e2mu->Integral() );

  h2l2mu_stat = (TH1F*)m_In->Get( (var+"/"+idiots+"/2l2mu/h_stat_"+var+"_"+idiots+"_2l2mu" ).c_str() );
  h2l2mu_syst = (TH1F*)m_In->Get( (var+"/"+idiots+"/2l2mu/h_syst_"+var+"_"+idiots+"_2l2mu" ).c_str() );

  h2l2e_stat=(TH1F*)m_In->Get( (var+"/"+idiots+"/2l2e/h_stat_"+var+"_"+idiots+"_2l2e" ).c_str() );
  h2l2e_syst=(TH1F*)m_In->Get( (var+"/"+idiots+"/2l2e/h_syst_"+var+"_"+idiots+"_2l2e" ).c_str() );

  if(m_isFid){
    RebinHistos();
    evalFidSys(folder);
  }
  else
    evalDiffSys(folder);

  /* Cleaning */
  h4mu->Delete();
  h4e->Delete();
  h2e2mu->Delete();
  h2mu2e->Delete();
  h2l2mu_stat->Delete();
  h2l2mu_syst->Delete();
  h2l2e_stat->Delete();
  h2l2e_syst->Delete();
  
} 

void evalDiffSys(std::string folder){

  for(int i=1; i<h4mu->GetNbinsX()+1; ++i){
    
    m_ss.str("");
    m_ss << i-1;

    if(m_debug)
      std::cout << "<ZjetSys()> :: Processing Variable = " << folder
		<< " bin = " << m_ss.str() << std::endl;
    
    m_bin = "bin"+ m_ss.str();
    
    if(m_debug){
      std::cout << m_bin << "   " << folder << std::endl;
      std::cout << "opening file "<< "ValReader/Values/Diff/"+folder+"/Sys/redBkg_"+m_bin+".dat" << std::endl;
    }
    m_Out.open( "Values/Diff/"+folder+"/Sys/redBkg_"+m_bin+".dat" );

    double statmu = h4e->GetBinContent(i)+h2mu2e->GetBinContent(i)+(h2e2mu->GetBinContent(i)+h4mu->GetBinContent(i))*(1+h2l2mu_stat->GetBinContent(i));
    double systmu = h4e->GetBinContent(i)+h2mu2e->GetBinContent(i)+(h2e2mu->GetBinContent(i)+h4mu->GetBinContent(i))*(1+h2l2mu_syst->GetBinContent(i));

    double state = h4mu->GetBinContent(i)+h2e2mu->GetBinContent(i)+(h2mu2e->GetBinContent(i)+h4e->GetBinContent(i))*(1+h2l2e_stat->GetBinContent(i));
    double syste = h4mu->GetBinContent(i)+h2e2mu->GetBinContent(i)+(h2mu2e->GetBinContent(i)+h4e->GetBinContent(i))*(1+h2l2e_syst->GetBinContent(i));

    double nominal = h4mu->GetBinContent(i)+h4e->GetBinContent(i)+h2mu2e->GetBinContent(i)+h2e2mu->GetBinContent(i);

    if(m_debug){
      std::cout << "<ZjetSys()> :: nominal = " << nominal << std::endl;
      std::cout << "               statmu = " << statmu << " systmu = " << systmu
		<< " state = " << state << " syste = " << syste << std::endl;
    }

    m_Out.width(55); m_Out << std::left << "SysId";
    m_Out.width(12); m_Out << "DownVal";
    m_Out.width(12); m_Out << "UpVal";
    m_Out.width(12); m_Out << std::right << "SysType";
    m_Out.width(12); m_Out << "Constr"<<std::endl;

    m_Out.width(55); m_Out << std::left << "ATLAS_ZJET_llmumu_stat";
    m_Out.width(12); m_Out << std::max(1-(statmu/nominal-1),0.);
    m_Out.width(12); m_Out << statmu/nominal;
    m_Out.width(12); m_Out << std::right << 1;
    m_Out.width(12); m_Out << 1 << std::endl;

    m_Out.width(55); m_Out << std::left << "ATLAS_ZJET_llee_stat";
    m_Out.width(12); m_Out << std::max(1-(state/nominal-1),0.);
    m_Out.width(12); m_Out << state/nominal;
    m_Out.width(12); m_Out << std::right << 1;
    m_Out.width(12); m_Out << 1 << std::endl;

    m_Out.width(55); m_Out << std::left << "ATLAS_ZJET_llmumu_sys";
    m_Out.width(12); m_Out << std::max(1-(systmu/nominal-1),0.);
    m_Out.width(12); m_Out << systmu/nominal;
    m_Out.width(12); m_Out << std::right << 1;
    m_Out.width(12); m_Out << 1 << std::endl;

    m_Out.width(55); m_Out << std::left << "ATLAS_ZJET_llee_sys";
    m_Out.width(12); m_Out << std::max(1-(syste/nominal-1),0.);
    m_Out.width(12); m_Out << syste/nominal;
    m_Out.width(12); m_Out << std::right << 1;
    m_Out.width(12); m_Out << 1 << std::endl;
    m_Out.close();
    
  }
  
}

void evalFidSys(std::string chan){

  if(m_debug)
    std::cout << "<ZjetSys()> :: Processing Channel = " << chan << std::endl;
  
  if(m_debug)
    std::cout << "opening file "<< "ValReader/Values/Fid/Sys/redBkg_"+chan+".dat" << std::endl;
  
  m_Out.open( "Values/Fid/Sys/redBkg_"+chan+".dat" );
  
  Int_t BinIn  = h4mu->FindBin(115.);
  Int_t BinEnd = h4mu->FindBin(130.)+1;
  
  double statmu=0, systmu=0, state=0, syste=0, nominal=0;
  for(int i=BinIn; i<BinEnd; i++){
    
    if(chan=="4mu"){
      statmu  += h4mu->GetBinContent(i)*(1+h2l2mu_stat->GetBinContent(i));
      systmu  += h4mu->GetBinContent(i)*(1+h2l2mu_syst->GetBinContent(i));
      nominal += h4mu->GetBinContent(i);
    }
    else if(chan=="2e2mu"){
      statmu  += h2e2mu->GetBinContent(i)*(1+h2l2mu_stat->GetBinContent(i));
      systmu  += h2e2mu->GetBinContent(i)*(1+h2l2mu_syst->GetBinContent(i));
      nominal += h2e2mu->GetBinContent(i);
    }
    else if(chan=="2mu2e"){
      state   += h2mu2e->GetBinContent(i)*(1+h2l2e_stat->GetBinContent(i));
      syste   += h2mu2e->GetBinContent(i)*(1+h2l2e_syst->GetBinContent(i));
      nominal += h2mu2e->GetBinContent(i);
    }
    else if(chan=="4e"){
      state   += h4e->GetBinContent(i)*(1+h2l2e_stat->GetBinContent(i));
      syste   += h4e->GetBinContent(i)*(1+h2l2e_syst->GetBinContent(i));
      nominal += h4e->GetBinContent(i);
    }
    else if(chan=="incl"){
      statmu  += h4e->GetBinContent(i)+h2mu2e->GetBinContent(i)+(h2e2mu->GetBinContent(i)+h4mu->GetBinContent(i))*(1+h2l2mu_stat->GetBinContent(i));
      systmu  += h4e->GetBinContent(i)+h2mu2e->GetBinContent(i)+(h2e2mu->GetBinContent(i)+h4mu->GetBinContent(i))*(1+h2l2mu_syst->GetBinContent(i));
      state   += h4mu->GetBinContent(i)+h2e2mu->GetBinContent(i)+(h2mu2e->GetBinContent(i)+h4e->GetBinContent(i))*(1+h2l2e_stat->GetBinContent(i));
      syste   += h4mu->GetBinContent(i)+h2e2mu->GetBinContent(i)+(h2mu2e->GetBinContent(i)+h4e->GetBinContent(i))*(1+h2l2e_syst->GetBinContent(i));
      nominal += h4mu->GetBinContent(i)+h4e->GetBinContent(i)+h2mu2e->GetBinContent(i)+h2e2mu->GetBinContent(i);
    }
    
  }
  if(m_debug){
    std::cout << "<ZjetSys()> :: nominal = " << nominal << std::endl;
    std::cout << "               statmu = " << statmu << " systmu = " << systmu
	      << " state = " << state << " syste = " << syste << std::endl;
  }
  
  double upStat_llmumu=1.0, dwStat_llmumu=1.0, upSys_llmumu=1.0, dwSys_llmumu=1.0;
  double upStat_llee=1.0,   dwStat_llee=1.0,   upSys_llee=1.0,   dwSys_llee=1.0;
  if(chan=="4mu" || chan=="2e2mu"){
    upStat_llmumu = statmu/nominal;
    dwStat_llmumu = std::max(1-(statmu/nominal-1),0.);
    upSys_llmumu  = systmu/nominal;
    dwSys_llmumu  = std::max(1-(systmu/nominal-1),0.);
  }
  else if(chan=="4e" || chan=="2mu2e"){
    upStat_llee = state/nominal;
    dwStat_llee = std::max(1-(state/nominal-1),0.);
    upSys_llee  = syste/nominal;
    dwSys_llee  = std::max(1-(syste/nominal-1),0.);
  }
  else if(chan=="incl"){
    upStat_llmumu = statmu/nominal;
    dwStat_llmumu = std::max(1-(statmu/nominal-1),0.);
    upSys_llmumu  = systmu/nominal;
    dwSys_llmumu  = std::max(1-(systmu/nominal-1),0.);
    upStat_llee   = state/nominal;
    dwStat_llee   = std::max(1-(state/nominal-1),0.);
    upSys_llee    = syste/nominal;
    dwSys_llee    = std::max(1-(syste/nominal-1),0.);
  }
  
  m_Out.width(55); m_Out << std::left << "SysId";
  m_Out.width(12); m_Out << "DownVal";
  m_Out.width(12); m_Out << "UpVal";
  m_Out.width(12); m_Out << std::right << "SysType";
  m_Out.width(12); m_Out << "Constr"<<std::endl;
  
  m_Out.width(55); m_Out << std::left << "ATLAS_ZJET_llmumu_stat";
  m_Out.width(12); m_Out << dwStat_llmumu;
  m_Out.width(12); m_Out << upStat_llmumu;
  m_Out.width(12); m_Out << std::right << 1;
  m_Out.width(12); m_Out << 1 << std::endl;
  
  m_Out.width(55); m_Out << std::left << "ATLAS_ZJET_llee_stat";
  m_Out.width(12); m_Out << dwStat_llee;
  m_Out.width(12); m_Out << upStat_llee;
  m_Out.width(12); m_Out << std::right << 1;
  m_Out.width(12); m_Out << 1 << std::endl;
  
  m_Out.width(55); m_Out << std::left << "ATLAS_ZJET_llmumu_sys";
  m_Out.width(12); m_Out << dwSys_llmumu;
  m_Out.width(12); m_Out << upSys_llmumu;
  m_Out.width(12); m_Out << std::right << 1;
  m_Out.width(12); m_Out << 1 << std::endl;
  
  m_Out.width(55); m_Out << std::left << "ATLAS_ZJET_llee_sys";
  m_Out.width(12); m_Out << dwSys_llee;
  m_Out.width(12); m_Out << upSys_llee;
  m_Out.width(12); m_Out << std::right << 1;
  m_Out.width(12); m_Out << 1 << std::endl;
  m_Out.close();
  
  if(m_debug)
    std::cout << "" << std::endl;
  
}

void RebinHistos(){

   h4mu->Rebin(2);
   h4e->Rebin(2);
   h2e2mu->Rebin(2);
   h2mu2e->Rebin(2);
   h2l2mu_stat->Rebin(2);
   h2l2mu_syst->Rebin(2);
   h2l2e_stat->Rebin(2);
   h2l2e_syst->Rebin(2);
   
}
