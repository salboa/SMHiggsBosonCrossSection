#define MakeInput_cxx

/* Class includes */
#include "MakeInput.h"
#include "Histograms.cxx"
#include "Util.cxx"
#include "Truth.cxx"
#include "RunProcesses.cxx"
/* C++ includes*/
#include <cassert>
#include <ctime>

class Options{
  
public:
  std::string Process    ;
  std::string MCtype     ;
  int         SysType    ;
  int         Nbins      ;
  double      Min        ;
  double      Max        ;
  bool        debug      ;
  bool        verbose    ;
  bool        doMatrix   ;
  bool        doScale    ;
  bool        doShiftUp  ;
  bool        doShiftDown;
  bool        usePowhegZZ;
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
    Process     = ""     ;
    SysType     = 0      ;
    MCtype      = "mc15c";
    Nbins       = 15     ;
    Min         = 115.0  ;
    Max         = 130.0  ;
    debug       = false  ;
    verbose     = false  ;
    doMatrix    = false  ;
    doScale     = false  ;
    doShiftUp   = false  ;
    doShiftDown = false  ;
    usePowhegZZ = false  ;
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
    if( !strcmp(argv[i],"--Process")          ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.Process = argv[i+1]; }
    else if( !strcmp(argv[i],"--MCtype")      ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.MCtype  = argv[i+1]; }
    else if( !strcmp(argv[i],"--SysType")     ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.SysType = std::stoi(argv[i+1]);  }
    else if( !strcmp(argv[i],"--Nbins")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.Nbins = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--Min")         ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.Min = std::stod(argv[i+1]); }
    else if( !strcmp(argv[i],"--Max")         ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.Max = std::stod(argv[i+1]); }
    else if( !strcmp(argv[i],"--doMatrix")    ){ opt.doMatrix    = true; }
    else if( !strcmp(argv[i],"--doScale")     ){ opt.doScale     = true; }
    else if( !strcmp(argv[i],"--doShiftUp")   ){ opt.doShiftUp   = true; }
    else if( !strcmp(argv[i],"--doShiftDown") ){ opt.doShiftDown = true; }
    else if( !strcmp(argv[i],"--usePowhegZZ") ){ opt.usePowhegZZ = true; }
    else if( !strcmp(argv[i],"--debug")       ){ opt.debug       = true; }
    else if( !strcmp(argv[i],"--verbose")     ){ opt.verbose     = true; }
    else if( !strcmp(argv[i],"--help")        ){ printHelp       = true; }
  }
  if( printHelp ){
    std::cout << "MakeInput: Run HZZ xsec inputs maker !!" << std::endl;
    std::cout << "  Usage  :  MakeInput [Options]"         << std::endl;
    std::cout << "             --Process      [Set physics process to be processed."     << std::endl;
    std::cout << "                             Options are: 'ggH', 'VBF', 'WH', 'ZH',"   << std::endl;
    std::cout << "                             'ttH', 'AllSig', qqZZ', 'ggZZ', 'Zjets']" << std::endl;
    std::cout << "              --MCtype      [Define MC version: default is 'mc15c'."   << std::endl;
    std::cout << "                             Other options are: 'mc15b']"              << std::endl;
    std::cout << "              --SysType     [Specify the Syst Uncert. Number:"         << std::endl;
    std::cout << "                             defauly is 0. Other options are 0-93]"    << std::endl;
    std::cout << "              --Nbins       [Set Number of bins for m4l plots:"        << std::endl;
    std::cout << "                             default is '15']"                         << std::endl;
    std::cout << "              --Min         [Set Lower m4l range: default is '115']"   << std::endl;
    std::cout << "              --Max         [Set Upper m4l range: default is '130']"   << std::endl;
    std::cout << "              --doMatrix    [Enable response matrix making:"           << std::endl;
    std::cout << "                             defaults is 'false']"                     << std::endl;
    std::cout << "              --doScale     [Enable xsec scale derivation:"            << std::endl;
    std::cout << "                             default is 'false' ]"                     << std::endl;
    std::cout << "              --doShiftUp   [Enable m4l+200 MeV shift:"                << std::endl;
    std::cout << "                             default is 'false' ]"                     << std::endl;
    std::cout << "              --doShiftDown [Enable m4l-200 MeV shift:"                << std::endl;
    std::cout << "                             default is 'false' ]"                     << std::endl;
    std::cout << "              --usePowhegZZ [Enable using Powheg qqZZ: "               << std::endl;
    std::cout << "                              default is 'false' ] "                   << std::endl;
    std::cout << "              --debug       [Set debug mode: default is 'false']"      << std::endl;
    std::cout << "              --verbose     [Set verbose mode: default is 'false']"    << std::endl;
    std::cout << "              --help        [Print this help]"                         << std::endl;
    exit(0);
  }

  if(opt.verbose) opt.debug=true;
  
  if(opt.debug){
    std::cout << "Calling MakeInput Class with options: " << std::endl;
    std::cout << "  Process     = " << opt.Process     << std::endl;
    std::cout << "  MCtype      = " << opt.MCtype      << std::endl;
    std::cout << "  SysType     = " << opt.SysType     << std::endl;
    std::cout << "  Nbins       = " << opt.Nbins       << std::endl;
    std::cout << "  Min         = " << opt.Min         << std::endl;
    std::cout << "  Max         = " << opt.Max         << std::endl;
    std::cout << "  doMatrix    = " << opt.doMatrix    << std::endl;
    std::cout << "  doScale     = " << opt.doScale     << std::endl;
    std::cout << "  doShiftUp   = " << opt.doShiftUp   << std::endl;
    std::cout << "  doShiftDown = " << opt.doShiftDown << std::endl;
    std::cout << "  usePowhegZZ = " << opt.usePowhegZZ << std::endl;
  }

  MakeInput *mp = new MakeInput(opt.Process, opt.MCtype, opt.SysType,
				opt.Nbins, opt.Min, opt.Max, opt.doMatrix,
				opt.doShiftUp, opt.doShiftDown, opt.usePowhegZZ,
				opt.debug, opt.verbose);
  
  if(opt.doScale)
    mp->DeriveXsecScale();
  else
    mp->Process();
  
  return 0;
  
}
  
MakeInput::MakeInput(){

  TH1::SetDefaultSumw2(kTRUE);
  
  //gROOT->SetStyle("ATLAS");
  //gROOT->ForceStyle();

  m_In       = NULL;
  m_Out      = NULL;
  m_treename = "tree_incl_all";
  m_chain    = NULL;
  m_thchain  = NULL; 
  
}

MakeInput::MakeInput(std::string Process, std::string MCtype,
		     int SysType, int Nbins, double Min, double Max,
		     bool doMatrix, bool ShiftUp, bool ShiftDown,
		     bool PowhegZZ, bool debug, bool verbose){
  
  TH1::SetDefaultSumw2(kTRUE);
  
  //gROOT->SetStyle("ATLAS");
  //gROOT->ForceStyle();

  m_Process     = Process;
  m_MCtype      = MCtype;
  m_SystNum     = SysType;
  m_Nbins       = Nbins;
  m_Min         = Min;
  m_Max         = Max;
  m_doMtx       = doMatrix;
  m_doShiftUp   = ShiftUp;
  m_doShiftDown = ShiftDown;
  m_powhegZZ    = PowhegZZ;
  m_debug       = debug;
  m_verbose     = verbose;
  m_In          = NULL;
  m_Out         = NULL;
  m_treename    = "tree_incl_all";
  m_chain       = NULL;
  m_thchain     = NULL;
  
  if(m_Process=="data") m_SystNum=Syst::NOMINAL;
  MakeSysMap();

  SanityCheck();
  
}

void MakeInput::Process(){

  if(m_debug){
    std::cout << " Processing Sample = " << m_Process << std::endl;
    std::cout << " String bins "<< std::to_string(m_Nbins) << " (for m4l plots) " << std::endl;
  }
  
  m_chain = new TChain( m_treename.c_str() );
  if(m_doMtx) m_thchain = new TChain( m_treename.c_str() );

  DefineOutFile();

  SetChain();
  if(m_doMtx) SetTruthChain();

  m_THbins = m_Nbins;
  //if(m_Process=="Zjets" && m_Nbins==1){ m_THbins = 30; }

  if(m_Process=="redBkg"){
    MergeRedBkg();
    m_Out->Close();
    m_In->Close();
    return;
  }
  
  DefineHistograms();

  if(m_Process=="Zjets" && m_Min==115.0 && m_Max==130.0)
    MakeRedBkg();
  else
    MakeOtherProcesses();
  
  /* Divide Plots For BinSize*/
  std::vector<TH1F*> Plots1D = ListOf1DPlotsToNorm();
  DivideForBinSize( Plots1D );

  std::vector<TH2F*> Plots2D =  ListOf2DPlotsToNorm();
  DivideForBinSize( Plots2D );
  
  /* Write Plots To File */
  m_Out->cd();
  if(m_SystNum>Syst::NOMINAL){
    m_Out->mkdir( m_SysMap[m_SystNum].c_str() );
    m_Out->cd( m_SysMap[m_SystNum].c_str() );
  }
  std::vector<TObject*> Plots = ListOfPlotsToWrite();
  for(uint p=0; p<Plots.size(); p++){
    Plots.at(p)->Write();
  }
  m_Out->Close();
  if(m_Process=="Zjets" && m_Min==115.0 && m_Max==130.0)
    m_In->Close();
  
}

void MakeInput::DeriveXsecScale(){

  if( m_Process!="ggH" && m_Process!="VBF" && m_Process!="WH"   &&
      m_Process!="ZH"  && m_Process!="ttH" && m_Process!="bbH"   ){
    std::cout << " Process = " << m_Process
	      << " : xsec scale cannot be derived! Exiting " << std::endl;
    return;
  }
  
  if(m_debug){
    std::cout << " Processing Sample = " << m_Process << std::endl;
    std::cout << " String bins "<< std::to_string(m_Nbins)
	      << " (for m4l plots) " << std::endl;
  }
  m_doScale = true;
  m_thchain = new TChain( m_treename.c_str() );
  SetTruthChain();
  m_THbins = m_Nbins;
  DefineHistograms();
  SetCounters();
  ProcessTruth();
  
}
