/* C++ includes */
#include "iostream"
/* program includes */
#include "PlotsSys.h"

int main( int argc, char* argv[] ){

  std::string variable = "";
  std::string channel = "";
  std::string sysType  = "";
  bool debug          = false;
  bool printHelp      = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--variable") ){
      variable = argv[i+1];
    }
    if( !strcmp(argv[i],"--channel") ){
      channel = argv[i+1];
    }
    if( !strcmp(argv[i],"--sysType") ){
      sysType = argv[i+1];
    }
    if( !strcmp(argv[i],"--debug") ){
      debug = true;
    }
    if( !strcmp(argv[i],"--help") ){
      printHelp=true;
    }
  }

  if(printHelp){
    std::cout << "./PlotSys:  make Sys variation plots! " <<std::endl;
    std::cout << "             Options:                            " << std::endl;
    std::cout << "             --variable [specify variable]"   << std::endl;
    std::cout << "             --channel  [specify channel]"    << std::endl;
    std::cout << "             --sysType  [specify sts type]"   << std::endl;
    std::cout << "             --debug    [Enable debug mode]"  << std::endl;
    exit(0);
  }

  if(debug){
    std::cout << "< PlotSys() >:: OPTIONS: "    << std::endl;
    std::cout << "                 variable = " << variable << std::endl;
    std::cout << "                 channel  = " << channel  << std::endl;
    std::cout << "                 sysType  = " << sysType  << std::endl;
    std::cout << "                 debug    = " << debug    << std::endl;
  }

  if(variable==""){
    std::cout << "variable not set -> please provide it1" << std::endl;
    exit(0);
  }
  if(variable=="m" && channel==""){
    std::cout << "using variable = m but channel not set -> please provide it!"
	      << std::endl;
    exit(0);
  }
  if(sysType==""){
    std::cout << "sysType not set -> please provide it!" << std::endl;
    exit(0);
  }
  
  PlotSys(variable,channel,sysType,debug);
  
  return 0;

}

void PlotSys(std::string variable, std::string channel,
	     std::string sysType, bool debug){

  TH1::SetDefaultSumw2(kTRUE);
  SetAtlasStyle();

  m_debug    = debug;
  m_variable = variable;
  m_channel  = channel;
  m_sysType  = sysType;
  
  m_Dir    = "../ws_output/";
  m_OutDir = "../varsDistro/sysPlots/";
  CheckOutDir();

  std::string name = "";
  if(m_variable=="pt0j" || m_variable=="pt1j" || m_variable=="pt2j")
    name = "ptpt_totalSysShape.root";
  else if(m_variable=="m")
    name = "m_fidchannel_totalSysShape.root";
  else
    name = m_variable+"_totalSysShape.root";
  
  m_InFile = new TFile( (m_Dir+name).c_str() );

  hup = GetHistogram("up");
  hdw = GetHistogram("down");
  if(m_variable=="m")
    hnm = GetHistogram("nom");
  else
    hnm = GetHistogram("nominal");
  
  m_cs = new TCanvas("cs","cs",0,0,600,600);
  m_cs->cd();

  m_leg = CreateLegend();

  if(m_debug)
    std::cout << "< PlotSys() >:: Setting histograms colors and range " << std::endl;
  
  hnm->SetLineColor(kBlack);
  hdw->SetLineColor(kBlue);
  hup->SetLineColor(kRed);
  hup->GetYaxis()->SetRangeUser(0, hup->GetMaximum()*1.7);
  SetAxisLabels(hnm);
  SetAxisLabels(hup);
  SetAxisLabels(hdw);

  if(m_debug)
    std::cout << "< PlotSys() >:: adding entry to the legend " << std::endl;
  
  m_leg->AddEntry( hnm, "Nominal", "l" );
  m_leg->AddEntry( hdw, (m_sysType+" syst. +1#sigma").c_str(), "l" );
  m_leg->AddEntry( hup, (m_sysType+" syst. -1#sigma").c_str(), "l" );
  
  hup->Draw("hist");
  hnm->Draw("histsame");
  hdw->Draw("histsame");
  m_leg->Draw();
  drawLabels();

  std::string OutName = m_OutDir+m_variable;
  if(m_variable=="m")
    OutName += m_channel;
  OutName += "_sys_"+m_sysType;

  if(m_debug)
    std::cout << "< PlotSys() >:: saving plot " << std::endl;

  std::cout << OutName << std::endl;
  m_cs->SaveAs( (OutName+".pdf").c_str() );
  m_cs->SaveAs( (OutName+".eps").c_str() );

  if(m_debug)
    std::cout << "< PlotSys() >:: cleaning " << std::endl;
  /* Cleaning */
  //hup->Delete();
  //hdw->Delete();
  //hnm->Delete();
  //m_InFile->Close();
  //m_cs->Delete();
  //m_leg->Delete();

}

TH1F* GetHistogram(std::string var){

  if(m_debug)
    std::cout << "< PlotSys() >:: retrieving " << var << " variation"
	      << " for sysType = " << m_sysType << " and variable "
	      << m_variable << std::endl;

  TH1F* h = NULL;
  if(m_variable=="pt0j" || m_variable=="pt1j" || m_variable=="pt2j"){

    TH1F * tmp = (TH1F*)m_InFile->Get( (var+"_"+m_sysType).c_str() );
    int offset = 0, bins = 4;
    if(m_variable=="pt1j"){      offset=4; bins = 5; }
    else if(m_variable=="pt2j"){ offset=9; bins = 2; }

    h = new TH1F(var.c_str(),var.c_str(),bins,0,bins);
    for(int i=1; i<bins+1; i++){
      if(m_variable=="pt0j" && i==4)
	h->SetBinContent(i, 0);
      else
	h->SetBinContent(i, tmp->GetBinContent(i+offset) );
    }
  }
  else if(m_variable=="m"){
    h = (TH1F*)m_InFile->Get( (var+m_channel+"_"+m_sysType).c_str() );
  }
  else
    h = (TH1F*)m_InFile->Get( (var+"_"+m_sysType).c_str() );
  
  return h;
  
}

TLegend* CreateLegend(){
  
  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->SetShadowColor(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  
  return leg;
  
}

void drawLabels(){

  TLatex AT;
  AT.SetNDC();
  AT.SetTextFont(72);
  AT.SetTextSize(0.033);
  AT.SetTextColor(kBlack);
  AT.DrawLatex(0.20,0.85,"ATLAS");
  
  TLatex Lab;
  Lab.SetNDC();
  Lab.SetTextFont(42);
  Lab.SetTextColor(kBlack);
  Lab.SetTextColor(kBlack);
  Lab.DrawLatex(0.31,0.85, "Internal");
  
  TLatex lumi;
  lumi.SetNDC();
  lumi.SetTextFont(42);
  lumi.SetTextSize(0.033);
  lumi.SetTextColor(kBlack);
  lumi.DrawLatex(0.20,0.74,/*"#sqrt{s} =*/ "13 TeV, 36.1 fb^{-1}");

  TLatex Chan;
  Chan.SetNDC();
  Chan.SetTextFont(42);
  Chan.SetTextSize(0.033);
  Chan.SetTextColor(kBlack);
  std::string chan = "";
  Chan.DrawLatex( 0.20,0.80, ("H #rightarrow ZZ* #rightarrow "+GetChannel()).c_str() );
  
}

std::string GetChannel(){

  std::string chan = "";
  if(m_channel=="")
    chan  = "4#font[12]{l}";
  else if(m_channel=="4mu")
    chan  = "4#mu";
  else if(m_channel=="4e")
    chan  = "4#e";
  else if(m_channel=="2e2mu")
    chan  = "2e2#mu";
  else if(m_channel=="2mu2e")
    chan  = "2#mu2e";

  return chan;
  
}

void SetAtlasStyle(){

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

void CheckOutDir(){

  struct stat st;
  m_OutDir = "../varsDistro/sysPlots/";
  if(stat(m_OutDir.c_str(),&st) == 0){
    if(m_debug)
      std::cout << "\033[1;39m <PlotSys()> \033[0m"
		<< "\033[1;32m Out Directory " << m_OutDir
		<< " already present!\033[0m" << std::endl;
  }
  else{
    if(m_debug)
      std::cout << "\033[1;39m <PlotSys()> \033[0m"
		<< "\033[1;34m Creating Directory " << m_OutDir
		<< " ... \033[0m" << std::endl;
    int outD = system( ("mkdir "+m_OutDir).c_str() );
    if(outD!=0)
      std::cout << "\033[1;39m <PlotsSys()> \033[0m"
		<< "\033[1;31m Directory " << m_OutDir
		<< " could not be created!\033[0m" << std::endl;
  }
  
}

void SetAxisLabels(TH1F* h){

  h->GetXaxis()->SetTitle( GetXaxisName().c_str()  );
  h->GetYaxis()->SetTitle( GetYaxisName(h).c_str() );
  
}

std::string GetXaxisName(){

  std::string m_lb = "";
  if( m_variable == "m12m34" )      m_lb = "#font[12]{m}_{12} vs #font[12]{m}_{34} bins";
  else if( m_variable == "m12" )    m_lb = "#font[12]{m}_{12} [GeV]";
  else if( m_variable == "m34" )    m_lb = "#font[12]{m}_{34} [GeV]";
  else if( m_variable == "m" ){
    if(m_channel == ("incl") ||
       m_channel == ""        )       m_lb = "#font[12]{m}_{4l} [GeV]";
    else if(m_channel == "4mu" )    m_lb = "#font[12]{m}_{4#mu} [GeV]";
    else if(m_channel == "4e" )     m_lb = "#font[12]{m}_{4e} [GeV]";
    else if(m_channel == "2mu2e" )  m_lb = "#font[12]{m}_{2#mu2e} [GeV]";
    else if(m_channel == "2e2mu" )  m_lb = "#font[12]{m}_{2e2#mu} [GeV]";
  }
  else if( m_variable == "njet" )   m_lb = "#font[12]{n}_{jets}";
  else if( m_variable == "nbjet" )  m_lb = "#font[12]{n}_{b-jets}";
  else if( m_variable == "cts" )    m_lb = "cos#theta^{*}";
  else if( m_variable == "y" )      m_lb = "|#font[12]{y}_{4l}|";
  else if( m_variable == "ljpt" )   m_lb = "#font[12]{p}_{T}^{lead. jet} [GeV]";
  else if( m_variable == "mjj" )    m_lb = "#font[12]{m}_{jj} [GeV]";
  else if( m_variable == "etajj" )  m_lb = "#Delta#eta_{jj}";
  else if( m_variable == "phijj" )  m_lb = "#Delta#phi_{jj}";
  else if( m_variable == "pt0j" )   m_lb = "#font[12]{p}_{T,4l}^{#font[12]{n}_{jets}=0} [GeV]";
  else if( m_variable == "pt1j" )   m_lb = "#font[12]{p}_{T,4l}^{#font[12]{n}_{jets}=1} [GeV]";
  else if( m_variable == "pt2j" )   m_lb = "#font[12]{p}_{T,4l}^{#font[12]{n}_{jets}#geq2} [GeV]";
  else if( m_variable == "pt" )     m_lb = "#font[12]{p}_{T,4l} [GeV]";

  return m_lb;
  
}

std::string GetYaxisName(TH1F* h){

  std::string m_txt = "";
  double wd = h->GetBinWidth(1);
  if( m_variable == "pt"  || m_variable == "m"    ||
      m_variable == "mjj" || m_variable == "ljpt"  ){
    
    m_txt = "Events / GeV";
    if( m_variable == "m" ){
      if(wd==1)
	m_txt = "Events / GeV";
      else
	m_txt = "Events / "+ConvertToStringWithPrecision(wd,2)+" GeV";
    }
    else if( m_variable == "m12m34" )
      m_txt = "Events";
  }
  else if( m_variable == "njet" || m_variable == "nbjet" ){
    m_txt = "Events";
  }
  else if( m_variable == "phijj" ){
    m_txt = "Events / #pi";
  }
  else{
    m_txt = "Events / Bin Width";
  }  
  
  return m_txt;
  
}

std::string ConvertToStringWithPrecision(double value, int n){
  
  std::ostringstream out;
  out << std::setprecision(n) << value;
  return out.str();
  
}
