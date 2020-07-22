#define DoPlots_cxx

/* Class includes */
#include "doPlots.h"
#include "doPlots_Utils.cxx"
#include "doPlots_Style.cxx"
#include "doPlots_Draw.cxx"
/* C++ includes*/
#include <cassert>
#include <ctime>

/* -------------
   Color numbers 
   RED   = 31
   GREEN = 32
   BLUE  = 34
   ------------ */

class Options{
  
public:
  std::string channel     ;
  std::string filename    ;
  double      lumi        ;
  bool        SigOnly     ;
  bool        useData     ;
  bool        compProdMode;
  bool        doAtlasStyle;
  bool        doLinear    ;
  bool        doMatrix    ;
  bool        useZjets    ;
  bool        useRedBkg   ; 
  bool        useVBS      ;
  bool        drawSyst    ;
  bool        drawM4l     ;
  bool        draw2Dmm    ;
  bool        isConf      ;
  bool        isPaper     ;
  bool        isLowMass   ;
  bool        isHighMass  ;
  std::string GetDateTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%d.%m.%Y_%I.%M.%S",timeinfo);
    std::string str(buffer);
    return str;
  }

  void SetDefault(){
    channel      = "incl";
    filename     = "XsecInputs_15bin.root";
    lumi         = 36.1 ;
    SigOnly      = false;
    useData      = false;
    compProdMode = false;
    doAtlasStyle = false;
    doLinear     = false;
    doMatrix     = false;
    useZjets     = false;
    useRedBkg    = false;
    useVBS       = false;
    drawSyst     = false;
    drawM4l      = false;
    draw2Dmm     = false;
    isConf       = false;
    isPaper      = false;
    isLowMass    = false;
    isHighMass   = false;
  }

  bool checkOpt(char* opt, char* value){
    std::string val = value;
    if( 0==val.find("-") ){
      std::cout << "WARNING:: Option " << opt <<
	" requires value -> skipping " << std::endl;
      return false;
    }
    return true;
  }
  
};


int main( int argc, char* argv[] ) {

  assert(argc>1);
  Options opt;
  opt.SetDefault();
  bool printHelp = false;
  
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--channel")        ){
      if( opt.checkOpt(argv[i],argv[i+1]) )   opt.channel = argv[i+1]; }
    if( !strcmp(argv[i],"--filename")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) )   opt.filename = argv[i+1]; }
    else if( !strcmp(argv[i],"--lumi")      ){
      if( opt.checkOpt(argv[i],argv[i+1]) )   opt.lumi = std::stod(argv[i+1]);  }
    else if( !strcmp(argv[i],"--SigOnly")      ){ opt.SigOnly      = true; }
    else if( !strcmp(argv[i],"--useData")      ){ opt.useData      = true; }
    else if( !strcmp(argv[i],"--useZjets")     ){ opt.useZjets     = true; }
    else if( !strcmp(argv[i],"--useRedBkg")    ){ opt.useRedBkg    = true; }
    else if( !strcmp(argv[i],"--useVBS")       ){ opt.useVBS       = true; }
    else if( !strcmp(argv[i],"--comProdMode")  ){ opt.compProdMode = true; }
    else if( !strcmp(argv[i],"--doAtlasStyle") ){ opt.doAtlasStyle = true; }
    else if( !strcmp(argv[i],"--doLinear")     ){ opt.doLinear     = true; }
    else if( !strcmp(argv[i],"--doMatrix")     ){ opt.doMatrix     = true; }
    else if( !strcmp(argv[i],"--drawSyst")     ){ opt.drawSyst     = true; }
    else if( !strcmp(argv[i],"--drawM4l")      ){ opt.drawM4l      = true; }
    else if( !strcmp(argv[i],"--draw2Dmm")     ){ opt.draw2Dmm     = true; }
    else if( !strcmp(argv[i],"--isConf")       ){ opt.isConf       = true; }
    else if( !strcmp(argv[i],"--isPaper")      ){ opt.isPaper      = true; }   
    else if( !strcmp(argv[i],"--isLowMass")    ){ opt.isLowMass    = true; }
    else if( !strcmp(argv[i],"--isHighMass")   ){ opt.isHighMass   = true; }
    else if( !strcmp(argv[i],"--help")         ){ printHelp        = true; }
  }
  if( printHelp ){
    std::cout << "doPlots: HZZ xsec inputs plots maker !!" << std::endl;
    std::cout << "  Usage  :  doPlots [Options]"         << std::endl;
    std::cout << "             --channel      [Define channel to be used: default is 'incl'."  << std::endl;
    std::cout << "                             Options are: '4mu', '4e', '2e2mu', '2mu2e',"    << std::endl;
    std::cout << "             --filename     [Define input filename:"                         << std::endl;
    std::cout << "                             default is 'XsecInputs_15bin.root']"            << std::endl;
    std::cout << "             --lumi         [Define luminosity: deafult is 36.1"             << std::endl;
    std::cout << "             --SigOnly      [Run Signal Only: default is 'false']"           << std::endl;
    std::cout << "             --useData      [Use Data: default is 'false']"                  << std::endl;
    std::cout << "             --useZjets     [Use Z+jets: default is 'false']"                << std::endl;
    std::cout << "             --useRedBkg    [Merge Z+jets + other bkgs: default is 'false']" << std::endl;
    std::cout << "             --useVBS       [Use ZZ* EW: default is 'false']"                << std::endl;
    std::cout << "             --comProdMode  [Compare Higgs prod. mode: default is 'false']"  << std::endl;
    std::cout << "             --doAtlasStyle [Set ATLAS style: default is 'false']"           << std::endl;
    std::cout << "             --doLinear     [Set y axis linear scale: default is 'false']"   << std::endl;
    std::cout << "             --doMatrix     [Make Matrix migration: default is 'false']"     << std::endl;
    std::cout << "             --drawSyst     [Draw Uncertaity Band: default is 'false']"      << std::endl;
    std::cout << "             --drawM4l      [Draw M4l Fit in each bin: default is 'false']"  << std::endl;
    std::cout << "             --draw2Dmm     [Draw m12vsm34 with 2D pad: default is 'false']" << std::endl;
    std::cout << "             --isConf       [Enable ConfNote labels: default is 'false']"    << std::endl;
    std::cout << "             --isPaper      [Enable Paper labels: default is 'false']"       << std::endl;
    std::cout << "             --isLowMass    [Enable low mass option: default is 'false']"    << std::endl;
    std::cout << "             --isHighMass   [Enable high mass option: default is 'false']"   << std::endl;
    std::cout << "             --help         [Print this help]"                               << std::endl;
    exit(0);
  }

  std::cout << "Calling doPlots Class with options: "    << std::endl;
  std::cout << "    channel      = " << opt.channel      << std::endl;
  std::cout << "    filename     = " << opt.filename     << std::endl;
  std::cout << "    lumi         = " << opt.lumi	 << std::endl;
  std::cout << "    SigOnly      = " << opt.SigOnly      << std::endl;
  std::cout << "    useData      = " << opt.useData      << std::endl;
  std::cout << "    useZjets     = " << opt.useZjets     << std::endl;
  std::cout << "    useRedBkg    = " << opt.useRedBkg    << std::endl;
  std::cout << "    useVBS       = " << opt.useVBS       << std::endl;
  std::cout << "    compProdMode = " << opt.compProdMode << std::endl;
  std::cout << "    doAtlasStyle = " << opt.doAtlasStyle << std::endl;
  std::cout << "    doLinear     = " << opt.doLinear     << std::endl;
  std::cout << "    doMatrix     = " << opt.doMatrix     << std::endl;
  std::cout << "    drawSyst     = " << opt.drawSyst     << std::endl;
  std::cout << "    drawM4l      = " << opt.drawM4l      << std::endl;
  std::cout << "    draw2Dmm     = " << opt.draw2Dmm     << std::endl;
  std::cout << "    isConf       = " << opt.isConf       << std::endl;
  std::cout << "    isPaper      = " << opt.isPaper      << std::endl;
  std::cout << "    isLowMass    = " << opt.isLowMass    << std::endl;
  std::cout << "    isHighMass   = " << opt.isHighMass   << std::endl;
  
  
  doPlots *dp = new doPlots(opt.channel, opt.filename, opt.lumi, opt.SigOnly,
			    opt.useData, opt.useZjets, opt.useVBS, opt.useRedBkg,
			    opt.compProdMode, opt.doAtlasStyle, opt.doLinear,
			    opt.doMatrix, opt.drawSyst, opt.drawM4l,
			    opt.draw2Dmm, opt.isConf, opt.isPaper,
			    opt.isLowMass,opt.isHighMass);
  dp->Run();
  return 0;
  
}

doPlots :: doPlots(std::string channel, std::string filename, double lumi,
		   bool SigOnly, bool useData, bool useZjets, bool useVBS,
		   bool useRedBkg, bool compProdMode, bool doAtlasStyle,
		   bool doLinear, bool doMatrix, bool drawSyst, bool drawM4l,
		   bool draw2Dmm, bool isConf, bool isPaper, bool isLowMass,
		   bool isHighMass){

  m_channel      = channel     ;
  m_filename     = filename    ;
  m_lumi         = lumi	       ;
  m_SigOnly      = SigOnly     ;
  m_useData      = useData     ;
  m_useZjets     = useZjets    ;
  m_useVBS       = useVBS      ;
  m_useRedBkg    = useRedBkg   ;
  m_compProdMode = compProdMode;
  m_doAtlasStyle = doAtlasStyle;
  m_doLinear     = doLinear    ;
  m_doMatrix     = doMatrix    ;
  m_drawSyst     = drawSyst    ;
  m_drawM4l      = drawM4l     ;
  m_draw2Dmm     = draw2Dmm    ;
  m_conf         = isConf      ;
  m_paper        = isPaper     ;
  m_lowMass      = isLowMass   ;
  m_highMass     = isHighMass  ;
  m_LumiStr      = ConvertToStringWithPrecision(m_lumi,3);

  m_OutDirPrefix = "../varsDistro/";
  
  if( m_doAtlasStyle ) SetAtlasStyle();

  gErrorIgnoreLevel=1001;
  gStyle->SetOptTitle(0);
  gStyle->SetPalette(104);
  gStyle->SetPaintTextFormat("4.4f");

  defineColors();

}

void doPlots :: Run(){

  LoadInputFile();
  CheckOutDir();

  if(m_doMatrix)
    RunMatrix();
  else if(m_draw2Dmm)
    Make2DmassPlot();
  else
    RunDistro();

  m_f->Close();

}

void doPlots :: RunMatrix(){

  TH2F* h_tmp = NULL;
  TKey *key   = NULL;
  m_prodmode = "mtx_"+m_channel+"_ggH";

  TIter next( m_f->GetListOfKeys());
  while ((key = (TKey *) next())) {
    h_tmp = (TH2F*) m_f->Get(key->GetName());
    TString name = key->GetName();
    if (!key->ReadObj()->IsA()->InheritsFrom("TH2F")) continue;
    if (name.Contains("Z1Z2") ) continue;
    if (name.Contains(m_prodmode) ){
      MakeMatrix( h_tmp );
    }
    h_tmp->Delete();
  }
  
}

void doPlots :: RunDistro(){
  
  TH1F* h_tmp = NULL;
  TKey *key   = NULL;
  m_prodmode = "_"+m_channel+"_AllSig";
  TIter next( m_f->GetListOfKeys());
  while ((key = (TKey *) next())) {
    h_tmp = (TH1F*)m_f->Get(key->GetName());
    TString name = key->GetName();
    if (!key->ReadObj()->IsA()->InheritsFrom("TH1F")) continue;
    if (name.Contains(m_prodmode) ){
      if(m_SigOnly)
	drawHistoSignal( h_tmp );
      else
	drawHistoSigBkgData( h_tmp );
    }
    h_tmp->Delete();
  }
  
}

void doPlots :: Make2DmassPlot(){

  TH1F *h_tmp = (TH1F*)m_f->Get( ("hm12vsm34_"+m_channel+"_AllSig").c_str() );
  drawHisto2Dm12m34(h_tmp);
  h_tmp->Delete();
  
}
