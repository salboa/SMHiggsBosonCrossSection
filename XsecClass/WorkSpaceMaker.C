#define WorkSpaceMaker_cxx

/* Class includes */
#include "WorkSpaceMaker.h"
#include "Systematics.cxx"
#include "Utils.cxx"
#include "BuildPdf.cxx"
#include "WS.cxx"
#include "ScanNLL.cxx"
#include "InputValues.cxx"
#include "Normalization.cxx"
#include "Fiducial.cxx"

/* C++ includes*/
#include <cassert>
#include <ctime>

class Options{
  
public:
  string FileName ;
  string DataPath ;
  string Variable ;
  string Channel  ;
  bool Fiducial   ;
  bool FidChan    ;
  bool FidComb    ;
  bool FidTotal   ;
  bool Fid4l      ;
  bool Fid2l2l    ;
  bool FidSum     ;
  bool debug      ;
  bool verbose    ;
  bool addSys     ;
  bool addShapeSys;
  bool sysBands   ;
  bool do2D       ;
  bool WithData   ;
  double Lumi     ;
  string fixSys   ;
  double doFit    ;
  double parallel ;
  bool skipScan   ;
  bool useMG      ;
  string DataSet  ;
  string GetDateTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%d.%m.%Y_%I.%M.%S",timeinfo);
    string str(buffer);
    return str;
  }
  
  void SetDefault(){
    FileName    = ""    ;
    DataPath    = ""    ;
    Variable    = ""    ;
    Channel     = "incl";
    Fiducial    = false ;
    FidChan     = false ;
    FidComb     = false ;
    FidTotal    = false ;
    Fid4l       = false ;
    Fid2l2l     = false ;
    FidSum      = false ;
    debug       = false ;
    verbose     = false ;
    addSys      = false ;
    addShapeSys = false ;
    sysBands    = false ;
    do2D        = false ;
    WithData    = false ;
    Lumi        = 36.1  ;
    fixSys      = "NO"  ;
    doFit       = false ;
    parallel    = false ;
    skipScan    = false ;
    useMG       = false ;
    DataSet     = ""    ;
  }

  bool checkOpt(char* opt, char* value){
    string val = value;
    if( 0==val.find("-") ){
      cout << "WARNING:: Option " << opt <<
	" requires value -> skipping " << endl;
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
    if( !strcmp(argv[i],"--FileName")         ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.FileName    = argv[i+1]; }
    if( !strcmp(argv[i],"--DataPath")         ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.DataPath    = argv[i+1]; }
    if( !strcmp(argv[i],"--Variable")         ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.Variable    = argv[i+1]; }
    if( !strcmp(argv[i],"--Channel")          ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.Channel     = argv[i+1]; }
    if( !strcmp(argv[i],"--lumi")             ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.Lumi        = stod(argv[i+1]); }
    if( !strcmp(argv[i],"--fixSys")             ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.fixSys      = argv[i+1]; }
    else if( !strcmp(argv[i],"--DataSet")     ){
      if( opt.checkOpt(argv[i],argv[i+1]) )      opt.DataSet     = argv[i+1]; }
    else if( !strcmp(argv[i],"--FidChan")     ){ opt.FidChan     = true; }
    else if( !strcmp(argv[i],"--FidComb")     ){ opt.FidComb     = true; }
    else if( !strcmp(argv[i],"--FidTotal")    ){ opt.FidTotal    = true; }
    else if( !strcmp(argv[i],"--Fid4l")       ){ opt.Fid4l       = true; }
    else if( !strcmp(argv[i],"--Fid2l2l")     ){ opt.Fid2l2l     = true; }
    else if( !strcmp(argv[i],"--FidSum")      ){ opt.FidSum      = true; }
    else if( !strcmp(argv[i],"--addSys")      ){ opt.addSys      = true; }
    else if( !strcmp(argv[i],"--addShapeSys") ){ opt.addShapeSys = true; }
    else if( !strcmp(argv[i],"--sysBands")    ){ opt.sysBands    = true; }
    else if( !strcmp(argv[i],"--do2D")        ){ opt.do2D        = true; }
    else if( !strcmp(argv[i],"--debug")       ){ opt.debug       = true; }
    else if( !strcmp(argv[i],"--verbose")     ){ opt.verbose     = true; }
    else if( !strcmp(argv[i],"--doFit")       ){ opt.doFit       = true; }
    else if( !strcmp(argv[i],"--WithData")    ){ opt.WithData    = true; }
    else if( !strcmp(argv[i],"--parallel")    ){ opt.parallel    = true; }
    else if( !strcmp(argv[i],"--skipScan")    ){ opt.skipScan    = true; }
    else if( !strcmp(argv[i],"--useMG")    ){ opt.useMG    = true; }
    else if( !strcmp(argv[i],"--help")        ){ printHelp       = true; }
  }
  if( printHelp ){
    cout << "WorkSpaceMaker: Make WorkSpace for HZZ4l xsec measurement!!"                      << endl;
    cout << "  Usage  :  WorkSpaceMaker [Options]"                                             << endl;
    cout << "             --Variable    [Define variable to be used -> possible choices:"      << endl;
    cout << "                            'pt', 'pt0j', 'pt1j', 'pt2j', 'm12', 'm34', 'y'"      << endl;
    cout << "                            'cts', 'njet', 'nbjet', 'ljpt', 'mjj', 'etajj',"      << endl;
    cout << "                            'phijj', 'm12m34', 'ptpt']"                           << endl;
    cout << "             --Channel     [Define channel to be used -> possible choices:"       << endl;
    cout << "                            'incl', '4mu', '4e', '2mu2e', '2e2mu']"               << endl;
    cout << "             --FileName    [Set ROOT filename to be used: default is ' ']"        << endl;
    cout << "             --DataPath    [Specify path to CF, A, xsec, r files: default is '']" << endl;
    cout << "             --FidChan     [Enable Fiducial single channel xsec measurement:"     << endl;
    cout << "                            default is 'false']"                                  << endl;
    cout << "             --FidComb     [Enable Fiducial comb xsec measurement:"     << endl;
    cout << "                            default is 'false']"                                  << endl;
    cout << "             --FidTotal    [Enable Fiducial total xsec measurement:"              << endl;
    cout << "                            default is 'false']"                                  << endl;
    cout << "             --Fid4l       [Enable Fiducial total xsec measurement for 4l case"   << endl;
    cout << "                            (4e+4mu): default is 'false']"                        << endl;
    cout << "             --Fid2l2l     [Enable Fiducial total xsec measurement for 2l2l"      << endl;
    cout << "                           case (2e2mu+2mu2e): default is 'false']"               << endl;
    cout << "             --FidSum      [Enable Fiducial xsec measurement summing all"         << endl;
    cout << "                            channels (4e+4mu+2e2mu+2mu2e): default is 'false']"   << endl;
    cout << "             --do2D        [Enable 2D: default is 'false']"                       << endl;
    cout << "             --addSys      [Use Systematics: default is 'false']"                 << endl;
    cout << "             --addShapeSys [Use m4l shape Systematics: default is 'false']"       << endl;
    cout << "             --sysBands    [Create systematic bands: defaults is 'false']"        << endl;
    cout << "             --lumi        [Set luminosity: default is '36.1' 1/fb]"              << endl;
    cout << "             --skipScan    [Skip NLL scan: default is 'false']"                   << endl;
    cout << "             --useMG       [use MG for expected: default is 'false']"             << endl;
    cout << "             --doFit       [Enable fit at the end of ws creation]"                << endl;
    cout << "             --WithData    [Include Real Data]"                                   << endl;    
    cout << "             --parallel    [Enable fit in parallel mode preliminary]"             << endl;
    cout << "             --debug       [Set debug mode: default is 'false']"                  << endl;
    cout << "             --verbose     [Set verbose mode: default is 'false']"                << endl;
    cout << "             --DataSet     [Set dataSetName mode: do not use ]"                   << endl;
    cout << "             --fixSys      [Select sys to fix profiled to data: default is 'NO' " << endl;
    cout << "                            -> possible values: 'all', 'muon', 'electron', "      << endl;
    cout << "                                                'jet', 'qqZZ', 'sig']"            << endl;
    cout << "             --help        [Print this help]"                                     << endl;
    cout << "  "                                                                               << endl;
    cout << "          -------------------   REMARKS -----------------"                        << endl;
    cout << "             --Variable option is needed when none of fiducial"                   << endl;
    cout << "                        measurement flag is enabled."                             << endl;
    cout << "             --Channel option is needed when none of fiducial"                    << endl;
    cout << "                        measurement flag is enabled, but for now 'incl'"          << endl;
    cout << "                        is used as default"                                       << endl;
    exit(0);
  }

  if( opt.FidChan || opt.FidTotal || opt.Fid4l || opt.Fid2l2l || opt.FidSum || opt.FidComb )
    opt.Fiducial = true;
  
  if( opt.Fiducial && opt.do2D ){
    cout << "\033[1;31m ERROR:: Doing Fiducial measurement but do2D enabled: " << endl;
    cout << "                   2D must be disabled! Exiting ...  \033[0m "    << endl;
    return -1;
  }

  if( opt.Variable=="" && !opt.Fiducial ){
    cout << "\033[1;31m ERROR:: Variable not set! Exiting ... \033[0m " << endl;
    return -1;
  }
  
  if( opt.verbose ){
    cout << "\033[1;33m INFO:: verbose ON! enabling debug ... \033[0m " << endl;
    opt.debug = true;
    opt.doFit = true;
  }
  if( opt.Fiducial ){
    cout << "\033[1;33m INFO:: Setting Channel and variable for "
	 << "fiducial xsec measurement ... \033[0m " << endl;
    opt.Channel = "incl";
    opt.Variable = "m";
  }

  cout << "Calling WorkSpaceMaker Class with options: " << endl;
  cout << "  FidChan     = " << opt.FidChan             << endl;
  cout << "  FidComb     = " << opt.FidComb             << endl;
  cout << "  FidTotal    = " << opt.FidTotal            << endl;
  cout << "  Fid4l       = " << opt.Fid4l               << endl;
  cout << "  Fid2l2l     = " << opt.Fid2l2l             << endl;
  cout << "  FidSum      = " << opt.FidSum              << endl;
  cout << "  Variable    = " << opt.Variable            << endl;
  cout << "  Channel     = " << opt.Channel             << endl;
  cout << "  FileName    = " << opt.FileName            << endl;
  cout << "  DataPath    = " << opt.DataPath            << endl;
  cout << "  addSys      = " << opt.addSys              << endl;
  cout << "  addShapeSys = " << opt.addShapeSys         << endl;
  cout << "  sysBands    = " << opt.sysBands            << endl;
  cout << "  debug       = " << opt.debug               << endl;
  cout << "  verbose     = " << opt.verbose             << endl;
  cout << "  do2D        = " << opt.do2D                << endl;
  cout << "  Lumi        = " << opt.Lumi                << endl;
  cout << "  fixSys      = " << opt.fixSys              << endl;
  cout << "  doFit       = " << opt.doFit               << endl;
  cout << "  WithData    = " << opt.WithData            << endl;  
  cout << "  parallel    = " << opt.parallel            << endl;
  cout << "  skipScan    = " << opt.skipScan            << endl;
  cout << "  useMG       = " << opt.useMG               << endl;
  cout << "  DataSet     = " << opt.DataSet             << endl;
  
  WorkSpaceMaker *wp = new WorkSpaceMaker(opt.Variable, opt.Channel,
					  opt.FileName, opt.DataPath,
					  opt.Lumi,     opt.FidChan, opt.FidComb,
					  opt.FidTotal, opt.Fid4l,
					  opt.Fid2l2l,  opt.FidSum,
					  opt.debug,    opt.verbose,
					  opt.addSys,   opt.addShapeSys,
					  opt.do2D,     opt.doFit,
					  opt.WithData, opt.parallel,
					  opt.DataSet,  opt.sysBands,
					  opt.skipScan, opt.useMG, opt.fixSys);
  wp->RunClass();
  return 0;
  
}

WorkSpaceMaker :: WorkSpaceMaker(string Variable, string Channel,
				 string FileName, string DataPath,
				 double lumi, bool FidChan, bool FidComb, bool FidTotal,
				 bool Fid4l, bool Fid2l2l, bool FidSum,
				 bool debug, bool verbose, bool addSys,
				 bool addShapeSys, bool do2D, bool dofit,
				 bool WithData, bool parallel, string DataSet,
				 bool sysBands, bool skipScan, bool useMG, string fixSys){
  
  TH1::SetDefaultSumw2(kTRUE);
  
  m_FileName    = FileName;
  m_DataPath    = DataPath;
  m_Variable    = Variable;
  m_Channel     = Channel;
  m_FidChan     = FidChan;
  m_FidComb     = FidComb;
  m_FidTotal    = FidTotal;
  m_Fid4l       = Fid4l;
  m_Fid2l2l     = Fid2l2l;
  m_FidSum      = FidSum;
  m_debug       = debug;
  m_verbose     = verbose;
  m_addSys      = addSys;
  m_addShapeSys = addShapeSys;
  m_sysBands    = sysBands;
  m_do2D        = do2D;
  m_ChNum       = GetChannelId(m_Channel);
  m_lumi        = lumi;
  m_dofit       = dofit;
  m_WithData    = WithData;
  m_parallel    = parallel;
  m_DataSet     = DataSet;
  m_skipScan    = skipScan;
  m_useMG       = useMG;
  m_fixSys      = fixSys;
  m_Dir         = GetCurrentWorkingDir()+"/";

  if( m_FidChan || m_FidTotal || m_Fid4l || m_Fid2l2l || m_FidSum  || m_FidComb )
    m_Fiducial=true;
  else
    m_Fiducial=false;

  SetAtlasStyle();
  defineColors();
  defineAxisLabelsMaps();
  
}

void WorkSpaceMaker :: RunClass(){
  
  InitializeIO();
  
  if( m_Fiducial )       doFiducial();
  else                   doDifferential();

  m_listpdf.Print("v");
  m_list.Print("v");
  DoWS();
  
}

void WorkSpaceMaker :: doFiducial(){
  
  cout << "<doFiducial()>:: evaluating xsec for fiducial case " << endl;
  
  for( int i=0; i < (int)m_Category.size(); i++ ){
    DoSignalPdf( GetProcess(Process::Signal), i+1, i );
    DoBackgroundPdf(i+1, true , true, true, i);
  }
}


void WorkSpaceMaker :: doDifferential(){

  if( m_debug )
    cout << "<doDifferential()>:: evaluating differential xsec" << endl;

  for( int i=0; i < (int)m_Category.size(); i++ ){
    DoSignalPdf( GetProcess(Process::Signal), m_ChNum, i );
    DoBackgroundPdf(m_ChNum, true , true, true, i);
  }
  
}

