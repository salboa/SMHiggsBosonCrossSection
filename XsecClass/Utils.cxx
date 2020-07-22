#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: InitializeIO(){

  if( m_debug )
    cout << "<InitializeIO()>:: Initializing I/O objects/values " << endl;
  
  LoadInputFile();
  DefineInputData();
  LoadObject();
  DefineCategoryMap();
  if ( m_do2D || m_Fiducial ) SetM4lNbins();
  else m_Mbins = 1;
  LoadCorrFact();
  LoadAcceptance();
  LoadProdModeFraction();
  LoadBranchingRatio();
  if(!m_Fiducial)
    LoadXsScaleFraction();
  LoadCrossSection();
  CreateProcList();
  if(m_addSys)
    LoadSystematics();
  
}

void WorkSpaceMaker :: LoadInputFile(){

  if( m_debug )
    cout << "<LoadInputFile()>:: Loading Input File " << endl;

  if( m_FileName=="" )
    m_InFile = new TFile( (m_Dir+"../varsDistro/XsecInputs_15bin.root").c_str() );
  else
    m_InFile = new TFile( (m_Dir+"../varsDistro/"+m_FileName).c_str() );

  if( m_InFile->IsZombie() ){
    cout << "<LoadInputFile()>:: \033[1;31m ERROR, no input file! Exiting \033[0m" << endl;
    exit(0);
  }
  
}

void WorkSpaceMaker :: DefineInputData(){

  if( m_debug )
    cout << "<DefineInputData>:: Defining input CF, Acc, r, xsec data files " << endl;

  if( m_DataPath=="" ) m_DataPath = m_Dir+"../ValReader/Values/";

  m_cfFile = "Fid/CF.dat";
  if( !m_Fiducial ) m_cfFile = "Diff/"+m_Variable+"/CF_"+m_Variable+".dat";
  
  m_accFile = "Fid/Acc.dat";
  if( !m_Fiducial ) m_accFile = "Diff/"+m_Variable+"/Acc_"+m_Variable+".dat";
  
  m_rFile = "Fid/r.dat";
  if( !m_Fiducial ) m_rFile = "Diff/"+m_Variable+"/r_"+m_Variable+".dat";

  m_xsScaleFile = "Fid/xsScale.dat";
  if( !m_Fiducial ) m_xsScaleFile = "Diff/"+m_Variable+"/scaleXsec_"+m_Variable+".dat";

  m_sysFile = "Fid/Sys/";
  if( !m_Fiducial ) m_sysFile = "Diff/"+m_Variable+"/Sys/";

  m_cmSysFile = "Sys.dat";
  if (m_FidTotal)  m_cmSysFile = "SysTOTAL.dat";
  
  m_brFile   = "BR.dat";
  m_xsecFile = "Xsec.dat";
  
}

string WorkSpaceMaker :: GetCurrentWorkingDir( void ) {
  
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  
  return current_working_dir;
  
}

void WorkSpaceMaker :: DefineCategoryMap(){

  if( m_debug )
    cout << "<DefineCategoryMap()>:: filling categories map " << endl;

  if( m_Fiducial ){
    m_Category[ 0 ] = "4mu";
    m_Category[ 1 ] = "4e";
    m_Category[ 2 ] = "2mu2e";
    m_Category[ 3 ] = "2e2mu";
  }
  else{
    m_Htmp = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_incl_AllSig").c_str() );
    int its = m_Htmp->GetNbinsX();
    for(int i=0; i<its; i++){
      m_Category[ i ] = "bin"+to_string(i);
    }
    m_Htmp->Delete();
  }
  
}

void WorkSpaceMaker :: SetM4lNbins(){

  if( m_debug )
    cout << "<SetM4lNbins()>:: setting number of bins for m4l " << endl;
  
  if( m_Fiducial )
    m_Htmp = (TH1F*)m_InFile->Get( "hm_incl_AllSig" );
  else
    m_Htmp = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+m_Category.at(0)+"_incl_AllSig").c_str() );

  m_Mbins =  m_Htmp->GetNbinsX();
  m_Htmp->Delete();

  if( m_verbose )
    cout << "<SetM4lNbins()>:: number of bins for m4l = " << m_Mbins << endl;
    
}

void WorkSpaceMaker :: LoadObject(){
  
  if( m_debug )
    cout << "<LoadObject()>:: Loading Object " << endl;
  
  m_paramOfInterest = new RooArgSet();
  m_Lumi = new RooRealVar("L","L", m_lumi, 0, 100000);
  m_Lumi->Print();
  m_globalObservables.add(*m_Lumi);
  
}

void WorkSpaceMaker :: CreateOutDir(){

  struct stat st;
  m_OutDir = m_Dir+"../ws_output";
  if(stat(m_OutDir.c_str(),&st) == 0){
    cout << "\033[1;39m <CreateOutDir()>:: \033[0m"
	 << "\033[1;32m Out Directory " << m_OutDir << " already present!\033[0m" << endl;
  }
  else{
    cout << "\033[1;39m <CreateOutDir()>:: \033[0m"
	 << "\033[1;34m Creating Directory " << m_OutDir << " ... \033[0m" << endl;
    int outD = system( ("mkdir "+m_OutDir).c_str() );
    if(outD!=0)
      cout << "\033[1;39m <CreateOutDir()>:: \033[0m"
	   << "\033[1;31m Directory " << m_OutDir << " could not be created!\033[0m" << endl;
  }
  
}


inline const char* WorkSpaceMaker :: GetChannel(int n){

  switch(n){
  case Channel::AllChannels: return "incl";
  case Channel::FourMu     : return "4mu";
  case Channel::FourEl     : return "4e";
  case Channel::TwoMuTwoEl : return "2mu2e";
  case Channel::TwoElTwoMu : return "2e2mu";
  default                  : return "";
  }
  
}

inline const char* WorkSpaceMaker :: GetProcess(int p){

  switch(p){
  case Process::Signal: return "AllSig";
  case Process::ggH   : return "ggH";
  case Process::VBF   : return "VBF";
  case Process::WH    : return "WH";
  case Process::ZH    : return "ZH";
  case Process::ttH   : return "ttH";
  case Process::bbH   : return "bbH";
  case Process::ggZZ  : return "ggZZ";
  case Process::qqZZ  : return "qqZZ";
  case Process::redBkg: return "redBkg";
  default             : return "";
  }
  
}

string WorkSpaceMaker :: GetVariable(int v){

  switch(v){
  case Variable::pt          : return "pt";
  case Variable::pt_0jet     : return "pt0j";
  case Variable::pt_1jet     : return "pt1j";
  case Variable::pt_2jet     : return "pt2j";
  case Variable::m12         : return "m12";
  case Variable::m34         : return "m34";
  case Variable::m12m34      : return "m12m34";
  case Variable::y           : return "y";
  case Variable::njet        : return "njet";
  case Variable::njetv2      : return "njetv2";
  case Variable::njetv3      : return "njetv3";
  case Variable::nbjet       : return "nbjet";
  case Variable::costhetastar: return "cts";
  case Variable::LeadJetPt   : return "ljpt";
  case Variable::mjj         : return "mjj";
  case Variable::deltaetajj  : return "etajj";
  case Variable::deltaphijj  : return "phijj";
  default                    : return "";
  }
  
}

int WorkSpaceMaker :: GetChannelId(string ch){

  if( m_debug )
    cout << "<GetChannelId>:: retrieving channel Id" << endl;

  int m_Id=-1;
  if(      ch=="incl"  ) m_Id = Channel::AllChannels;
  else if( ch=="4mu"   ) m_Id = Channel::FourMu     ;
  else if( ch=="4e"    ) m_Id = Channel::FourEl     ;
  else if( ch=="2mu2e" ) m_Id = Channel::TwoMuTwoEl ;
  else if( ch=="2e2mu" ) m_Id = Channel::TwoElTwoMu ;

  return m_Id;
  
}

void WorkSpaceMaker :: CheckVectorSize(TH1F *h, int chnum){

  int Nbins = h->GetNbinsX();

  if( Nbins != (int)m_acc[chnum].size()/(int(Process::bbH)+1) ){
    cout << "<DoSinglePdf()>:: \033[1;31m ERROR: ACC vector size ("
	 << m_acc[chnum].size()/(int(Process::bbH)+1) << ")" << " != Number of bins ("
	 << Nbins << ")!! Exiting \033[0m " << endl;
    exit(0);
  }
  if( Nbins != (int)m_cf[chnum].size()/(int(Process::bbH)+1) ){
    cout << "<DoSinglePdf()>:: \033[1;31m ERROR: CF vector size ("
	 << m_cf[chnum].size()/(int(Process::bbH)+1) << ")" << " != Number of bins ("
	 << Nbins << ")!! Exiting \033[0m " << endl;
    exit(0);
  }
  if( Nbins != (int)m_r[chnum].size()/(int(Process::bbH)+1) ){
    cout << "<DoSinglePdf()>:: \033[1;31m ERROR: R vector size ("
	 << m_r[chnum].size()/(int(Process::bbH)+1) << ")" << " != Number of bins ("
	 << Nbins << ")!! Exiting \033[0m " << endl;
    exit(0);
  }
  
}


TH1F* WorkSpaceMaker :: remapHisto( TH1F* hIn, int bin ){

  if( m_debug )
    cout<< "<remapHisto()> :: remapping histogram " << hIn->GetName() << endl;
  
  m_hremapped =  new TH1F ( (string(hIn->GetName())+"remapped"+"_"+to_string(bin)).c_str(),
			    (string(hIn->GetTitle())+"remapped"+"_"+to_string(bin)).c_str(),
			    hIn->GetNbinsX(), 0, hIn->GetNbinsX() ); m_hremapped->Print();
  RooRealVar *BinWidth = NULL;
  float binw = 0;
  for(Int_t i=1; i<hIn->GetNbinsX()+1; ++i ) {
    binw = hIn->GetBinWidth(i);
    m_binnames.push_back(hIn->GetBinLowEdge(i));

    if( m_Fiducial ) {
      binw = 1;
      BinWidth = new RooRealVar( ("BinWidth_"+to_string(i-1)).c_str(),
				 ("BinWidth_"+to_string(i-1)).c_str(), binw);
    }
    else BinWidth = new RooRealVar( ("BinWidth_"+m_Category.at(i-1)).c_str(),
				    ("BinWidth_"+m_Category.at(i-1)).c_str(), binw);

    m_hremapped->SetBinContent(i, hIn->GetBinContent(i));
    m_hremapped->SetBinError(i,hIn->GetBinError(i));
    m_binwidth.push_back(binw);
    m_binlowerlimit.push_back(hIn->GetBinLowEdge(i));
    m_binwidthroorealvar.push_back(BinWidth);

    if( m_verbose ){
      cout << "<remapHisto()> :: Bin "<< i << " " << "Remap = " << m_hremapped->GetBinContent(i)
	   << " Orig = " << hIn->GetBinContent(i) << endl;
      cout << " Bin width saved = " << m_binwidth.at(i-1) << endl;
      cout << " Original Bin Information = " << hIn->GetBinLowEdge(i)
	   << " " << hIn->GetBinLowEdge(i)+hIn->GetBinWidth(i) <<" "<< hIn->GetBinWidth(i)  << endl;
      cout << " remapped Bin Information = " << m_hremapped->GetBinLowEdge(i)
      << " " << m_hremapped->GetBinLowEdge(i)+m_hremapped->GetBinWidth(i) <<" "<< m_hremapped->GetBinWidth(i)  << endl;
      cout << " Original integral = " << hIn->Integral() << endl;
      cout << " remapped integral = " << m_hremapped->Integral() << endl;

    }
  }
  m_binnames.push_back(hIn->GetBinLowEdge(hIn->GetNbinsX())+ hIn->GetBinWidth(hIn->GetNbinsX()));

  return m_hremapped;
  
}

string WorkSpaceMaker :: ConvertToStringWithPrecision(double value, int n){
  
  ostringstream out;
  out << setprecision(n) << value;
  return out.str();
  
}

void WorkSpaceMaker :: drawlatex(TLatex *t){

  t->SetTextColor(kRed+2);
  t->SetTextFont(43);
  t->SetTextSize(22);
  t->Draw();

}

void WorkSpaceMaker :: drawATLASInternal(){

  TLatex AT;
  AT.SetNDC();
  AT.SetTextFont(72);
  AT.SetTextColor(kBlack);
  AT.DrawLatex(0.25,0.89,"ATLAS");

  TLatex Lab;
  Lab.SetNDC();
  Lab.SetTextFont(42);
  Lab.SetTextColor(kBlack);
  Lab.DrawLatex(0.40,0.89, "Internal");
    
}

void WorkSpaceMaker :: drawEnergyLumi(){

  TLatex lumi;
  lumi.SetNDC();
  lumi.SetTextFont(42);
  lumi.SetTextSize(0.033);
  lumi.SetTextColor(kBlack);
  lumi.DrawLatex(0.25,0.77,("#sqrt{s} = 13 TeV, "+ConvertToStringWithPrecision(m_lumi, 3)+" fb^{-1}").c_str());
  
}

void WorkSpaceMaker :: drawChannel(){

  TLatex Chan;
  Chan.SetNDC();
  Chan.SetTextFont(42);
  Chan.SetTextSize(0.033);
  Chan.SetTextColor(kBlack);
  Chan.DrawLatex( 0.25,0.83,"H #rightarrow ZZ* #rightarrow 4l" );

}

void WorkSpaceMaker :: DrawSigmaLines (TF1 *sigma){
  
  sigma->SetLineStyle(2);
  sigma->SetLineWidth(1);
  sigma->SetLineColor(kRed);
  sigma->Draw("same");
  
}

void WorkSpaceMaker :: CreateProcList(){

  m_process["Signal"] = 0;
  m_process["ggH"]    = 1;
  m_process["VBF"]    = 2;
  m_process["WH"]     = 3;
  m_process["ZH"]     = 4;
  m_process["ttH"]    = 5;
  m_process["bbH"]    = 6;
  m_process["ggZZ"]   = 7;
  m_process["qqZZ"]   = 8;
  m_process["redBkg"]  = 9;

  
}

void WorkSpaceMaker :: CleanUp(){

  cout << "\033[1;32m <CleanUp()>:: cleaning memory ... \033[0m" << endl;
  
  m_cf.clear();
  m_acc.clear();
  m_r.clear();
  m_br.clear();
  m_xsec.clear();
  m_xsScale.clear();
  m_procSys.clear();
  m_comSys.clear();
  
}

void WorkSpaceMaker :: SetCanvasSize(int *cw, int *ch){
  
  cout << "\033[1;32m <SetCanvasSize()>\033[0m" << endl;
  
  if( m_Variable == "pt"   ){  cw = (int*) 1200; ch = (int*) 1000; }
  if( m_Variable == "cts"  ){  cw = (int*) 1200; ch = (int*) 1000; }
  if( m_Variable == "njet" ){  cw = (int*) 1200; ch = (int*) 1000; }
  if( m_Variable == "m12"  ){  cw = (int*) 1200; ch = (int*) 1000; }
  if( m_Variable == "m34"  ){  cw = (int*) 1200; ch = (int*) 1000; }
  if( m_Variable == "y"    ){  cw = (int*) 1200; ch = (int*) 1000; }
  if( m_Variable == "ljpt" ){  cw = (int*) 1200; ch = (int*) 1000; }
  if( m_Variable == "ljpt" ){  cw = (int*) 1200; ch = (int*) 1000; }
  if( m_Fid2l2l || m_Fid4l || m_FidSum || m_FidTotal ){
    cw = (int*) 400; ch = (int*) 400;
  }
  else{
    cw = (int*) 1200; ch = (int*) 1200;
  }
  
}

/*
TH1F* WorkSpaceMaker :: GetDoubleDifferentialH( vector<TH1F*> v_h ){
  
  cout << "\033[1;32m <GetDoubleDifferentialH()>\033[0m" << endl;

  int Ncat = 0;
  
  for ( unsigned int =0; i< v_h.size(); ++i ) Ncat = v_h.at(i)->GetNbisX();
  
  m_doubleDiff = new TH1F* ("double_diff"+m_Variable+)
  
}
*/

void WorkSpaceMaker :: SetAtlasStyle(){

  TStyle *atlasStyle= new TStyle("ATLAS","Atlas style");
  
  /*use plain black on white colors*/
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  /*don't use: white fill color for *all* objects*/
  //atlasStyle->SetFillColor(icol); 

  /*set the paper & margin sizes*/
  atlasStyle->SetPaperSize(20,26);

  /*set margin sizes*/
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.14);

  /*set title offsets (for axis label)*/
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);

  /*use large fonts*/
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.04; //io=0.04
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");

  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  /*use bold lines and markers*/
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  /*get rid of X error bars*/
  //atlasStyle->SetErrorX(0.001);
  /*get rid of error bar caps*/
  atlasStyle->SetEndErrorSize(0.);

  /*do not display any of the standard histogram decorations*/
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  /*put tick marks on top and RHS of plots*/
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

}

void WorkSpaceMaker :: defineColors(){
  
  sigCol    = TColor::GetColor("#67B2FF");
  ZZCol     = TColor::GetColor("#E20D0A");
  ZZEWCol   = TColor::GetColor("#B5236F");
  redBkgCol = TColor::GetColor("#793FD2");
  ttVCol    = TColor::GetColor("#EDE810");
  ggFCol    = TColor::GetColor("#67B2FF");
  VBFCol    = TColor::GetColor("#99E148");
  VHCol     = TColor::GetColor("#EB9B35");
  WHCol     = TColor::GetColor("#EB9B35");
  ZHCol     = kOrange;
  ttHCol    = kBlue;
  dataCol   = kBlack;

}

void WorkSpaceMaker :: defineAxisLabelsMaps(){

  /* Shape plots */
  m_shapeLabels["pt"]     = { "p_{T} [GeV]"            , "Events / GeV"       };
  m_shapeLabels["m12"]    = { "m_{12} [GeV]"           , "Events / GeV"       };
  m_shapeLabels["m34"]    = { "m_{34} [GeV]"           , "Events / GeV"       };
  m_shapeLabels["y"]      = { "|y|"                    , "Events / Bin Width" };
  m_shapeLabels["njet"]   = { "N_{jets}"               , "Events"             };
  m_shapeLabels["njetv2"] = { "N_{jets}"               , "Events"             };
  m_shapeLabels["njetv3"] = { "N_{jets}"               , "Events"             };
  m_shapeLabels["nbjet"]  = { "N_{jets}"               , "Events"             };
  m_shapeLabels["m12m34"] = { "m_{12} vs m_{34}"       , "Events"             };
  m_shapeLabels["cts"]    = { "|cos#theta^{*}|"        , "Events / Bin Width" };
  m_shapeLabels["mjj"]    = { "m_{jj} [GeV]"           , "Events / GeV"       };
  m_shapeLabels["etajj"]  = { "#Delta#eta_{jj}"        , "Events / Bin Width" };
  m_shapeLabels["phijj"]  = { "#Delta#phi_{jj}"        , "Events / #pi"       };
  m_shapeLabels["ljpt"]   = { "p_{T}^{lead. jet} [GeV]", "Events / GeV"       };
  m_shapeLabels["ptpt"]   = { "p_{T} [GeV]"            , "Events / GeV"       };
  m_shapeLabels["pt0j"]   = { "p_{T}^{0 jet} [GeV]"    , "Events / GeV"       };
  m_shapeLabels["pt1j"]   = { "p_{T}^{1 jet} [GeV]"    , "Events / GeV"       };
  m_shapeLabels["pt2j"]   = { "p_{T}^{>=2 jet} [GeV]"  , "Events / GeV"       };
  
  /* Sigma Unfolded plots */
  m_sigUnfLabels["pt"]     = { "p_{T} [GeV]"             , "#sigma / Bin Width [fb/GeV]" };
  m_sigUnfLabels["m12"]    = { "m_{12} [GeV]"            , "#sigma / Bin Width [fb/GeV]" };
  m_sigUnfLabels["m34"]    = { "m_{34} [GeV]"            , "#sigma / Bin Width [fb/GeV]" };
  m_sigUnfLabels["y"]      = { "|y|"                     , "#sigma / Bin Width [fb]"     };
  m_sigUnfLabels["njet"]   = { "N_{jets}"                , "#sigma [fb]"                 };
  m_sigUnfLabels["njetv2"] = { "N_{jets}"                , "#sigma [fb]"                 };
  m_sigUnfLabels["njetv3"] = { "N_{jets}"                , "#sigma [fb]"                 };
  m_sigUnfLabels["nbjet"]  = { "N_{b-jets}"              , "#sigma [fb]"                 };
  m_sigUnfLabels["m12m34"] = { "m_{12} vs m_{34}"        , "#sigma [fb]"                 };
  m_sigUnfLabels["cts"]    = { "|cos#theta^{*}|"         , "#sigma / Bin Width [fb]"     };
  m_sigUnfLabels["mjj"]    = { "m_{jj} [GeV]"            , "#sigma / Bin Width [fb/GeV]" };
  m_sigUnfLabels["etajj"]  = { "#Delta#eta_{jj}"         , "#sigma / Bin Width [fb]"     };
  m_sigUnfLabels["phijj"]  = { "#Delta#phi_{jj}"         , "#sigma / #pi [fb]"           };
  m_sigUnfLabels["ljpt"]   = { "p_{T}^{lead. jet} [GeV]" , "#sigma / Bin Width [fb/GeV]" };
  m_sigUnfLabels["ptpt"]   = { "p_{T} [GeV]"             , "#sigma / Bin Width [fb/GeV]" };
  m_sigUnfLabels["pt0j"]   = { "p_{T, 0 jet} [GeV]"      , "#sigma / Bin Width [fb/GeV]" };
  m_sigUnfLabels["pt1j"]   = { "p_{T, 1 jet} [GeV]"      , "#sigma / Bin Width [fb/GeV]" };
  m_sigUnfLabels["pt2j"]   = { "p_{T, >=2 jets} [GeV]"   , "#sigma / Bin Width [fb/GeV]" };
  
}
