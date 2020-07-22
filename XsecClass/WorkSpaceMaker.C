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
#include "PlotPdf.cxx"
#include "QuickTest.cxx"

class Options{
  
public:
  string FileName     ;
  string SysFileName  ;
  string AcFileName   ;
  string AcSysFileName;
  string binStr       ;
  string PathToFile   ;
  string DataPath     ;
  string Variable     ;
  string Channel      ;
  bool Fiducial       ;
  bool FidChan        ;
  bool FidComb        ;
  bool FidTotal       ;
  bool Fid4l          ;
  bool Fid2l2l        ;
  bool FidSum         ;
  bool BRDiff         ;
  bool debug          ;
  bool verbose        ;
  bool addSys         ;
  bool addShapeSys    ;
  bool sysBands       ;
  bool do2D           ;
  bool WithData       ;
  bool useBornLep     ;
  double Lumi         ;
  string fixSys       ;
  double doFit        ;
  double parallel     ;
  bool skipScan       ;
  bool useMCData      ;
  string DataSet      ;
  bool matrix         ;
  bool cfsplit        ;
  string ProdMode     ;
  string ProdHist     ;
  string BkgHist      ;
  string InputMtx     ;
  int chSplit         ;
  int mcVersion       ;
  bool reduceM4lBins  ;
  bool floatqqZZ      ;
  string bkgOption    ;
  bool skipPruning    ;
  bool addAsys        ;
  
  void SetDefault(){
    FileName      = ""                    ;
    SysFileName   = ""                    ;
    AcFileName    = ""                    ;
    AcSysFileName = ""                    ;
    binStr        = ""                    ;
    PathToFile    = "../varsDistro/"      ;
    DataPath      = "../ValReader/Values/";
    Variable      = ""                    ;
    Channel       = "incl"                ;
    Fiducial      = false                 ;
    FidChan       = false                 ;
    FidComb       = false                 ;
    FidTotal      = false                 ;
    Fid4l         = false                 ;
    Fid2l2l       = false                 ;
    FidSum        = false                 ;
    BRDiff        = false                 ;
    debug         = false                 ;
    verbose       = false                 ;
    addSys        = false                 ;
    addShapeSys   = false                 ;
    sysBands      = false                 ;
    do2D          = false                 ;
    WithData      = false                 ;
    useBornLep    = false                 ;
    Lumi          = GetDefaultIntLumi()   ;
    fixSys        = "NO"                  ;
    doFit         = false                 ;
    parallel      = false                 ;
    skipScan      = false                 ;
    useMCData     = false                 ;
    DataSet       = ""                    ;
    matrix        = false                 ;
    cfsplit       = false                 ;
    ProdMode      = "MergProd"            ;
    ProdHist      = "AllSig"              ;
    BkgHist       = "AllZZ"               ;
    InputMtx      = ""                    ;
    chSplit       = 0                     ;
    mcVersion     = 0                     ;
    reduceM4lBins = false                 ;
    floatqqZZ	  = false                 ;
    bkgOption	  = "all"                 ;
    skipPruning	  = false                 ;
    addAsys	  = false                 ;
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
    bool validCmd = false;
    string cmd = argv[i];
    if( !strcmp(argv[i],"--variable")           ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.Variable      = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--channel")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.Channel       = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--fileName")      ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.FileName      = argv[i+1];       }  validCmd = true; }
    if( !strcmp(argv[i],"--sysFileName")        ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.SysFileName   = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--acFileName")    ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.AcFileName    = argv[i+1];       }  validCmd = true; }
    if( !strcmp(argv[i],"--acSysFileName")      ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.AcSysFileName = argv[i+1];       }  validCmd = true; }
    if( !strcmp(argv[i],"--nBins")              ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.binStr        = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--pathToFile")    ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.PathToFile    = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--dataPath")      ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.DataPath      = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--lumi")          ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.Lumi          = stod(argv[i+1]); }  validCmd = true; }
    else if( !strcmp(argv[i],"--fixSys")        ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.fixSys        = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--dataSet")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.DataSet       = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--prodMode")      ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.ProdMode      = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--prodHist")      ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.ProdHist      = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--bkgHist")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.BkgHist       = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--inputMtx")      ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.InputMtx      = argv[i+1];       }  validCmd = true; }
    else if( !strcmp(argv[i],"--chSplit")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.chSplit       = stoi(argv[i+1]); }  validCmd = true; }
    else if( !strcmp(argv[i],"--mcVersion")     ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.mcVersion     = stoi(argv[i+1]); }  validCmd = true; }
    else if( !strcmp(argv[i],"--bkgOption")     ){
      if( opt.checkOpt(argv[i],argv[i+1]) ) { opt.bkgOption      = argv[i+1];      }  validCmd = true; }
    else if( !strcmp(argv[i],"--fidChan")       ){ opt.FidChan       = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--fidComb")       ){ opt.FidComb       = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--fidTotal")      ){ opt.FidTotal      = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--fid4l")         ){ opt.Fid4l         = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--fid2l2l")       ){ opt.Fid2l2l       = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--fidSum")        ){ opt.FidSum        = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--BRdiff")        ){ opt.BRDiff        = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--addSys")        ){ opt.addSys        = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--addShapeSys")   ){ opt.addShapeSys   = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--addAsys")       ){ opt.addAsys       = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--skipPruning")   ){ opt.skipPruning   = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--sysBands")      ){ opt.sysBands      = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--do2D")          ){ opt.do2D          = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--doFit")         ){ opt.doFit         = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--withData")      ){ opt.WithData      = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--useBornLep")    ){ opt.useBornLep    = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--parallel")      ){ opt.parallel      = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--skipScan")      ){ opt.skipScan      = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--useMCData")     ){ opt.useMCData     = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--doMatrix")      ){ opt.matrix        = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--doCFsplit")     ){ opt.cfsplit       = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--reduceM4lBins") ){ opt.reduceM4lBins = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--floatqqZZ")	){ opt.floatqqZZ     = true;	      validCmd = true; }
    else if( !strcmp(argv[i],"--debug")         ){ opt.debug         = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--verbose")       ){ opt.verbose       = true;          validCmd = true; }
    else if( !strcmp(argv[i],"--help")          ){ printHelp         = true;          validCmd = true; }
    if( !validCmd  && cmd.find("--")!=string::npos ){
      cout << "\033[1;31m Command: " << cmd << " not valid. "
	   << "Type ./WorkSpaceMaker --help and check the available "
	   << "options, exit!\033[0m" << endl;
      exit(0);
    }
  }
  if( printHelp ){
    cout << "WorkSpaceMaker: Make WorkSpace for HZZ4l xsec measurement!!"                       << endl;
    cout << "  usage: ./WorkspaceMaker [--help] [--variable] [--channel] [--fileName]        "  << endl;
    cout << "                          [--sysFileName] [--acFileName] [--acSysFilename]      "  << endl;
    cout << "                          [--nBins] [--pathToFile] [--dataPath] [--fidChan]     "  << endl;
    cout << "                          [--fidComb] [--fidTotal] [--fid4l] [--fid2l2l]        "  << endl;
    cout << "                          [--fidSum] [--BRdiff] [--doFit] [--do2D] [--addSys]   "  << endl;
    cout << "                          [--addShapeSys] [--sysBands] [--lumi] [--skipScan]    "  << endl;
    cout << "                          [--useMCdata] [--withData] [--useBornLep] [--parallel]"  << endl;
    cout << "                          [--chSplit] [--dataSet] [--mcVersion] [--fixSys]      "  << endl;
    cout << "                          [--prodMode] [--prodHist] [--bkgHist] [--doMatrix]    "  << endl;
    cout << "                          [--inputMtx] [--doCFsplit] [--reduceM4lBins]          "  << endl;
    cout << "                          [--floatqqZZ] [--bkgOption] [--skipPruning] [--addAsys]" << endl;
    cout << "                          [--debug] [--verbose]                                 "  << endl;
    
    cout << " Optional arguments (default value):                                            "  << endl;
    cout << " --help          print this help and exit"                                         << endl;
    cout << " --variable      specify variable to be used (' '). Options are:"                  << endl;
    cout << "                 'pt4l', 'pt0j', 'pt1j', 'pt2j', 'm12', 'm34', 'y', 'cts', 'njet',"<< endl;
    cout << "                 'njetv2', 'njetv3', 'njetv4', 'nbjet', 'ljpt', 'mjj', 'etajj', "  << endl;
    cout << "                 'phijj', 'm12m34', 'ptpt'"                                        << endl;
    cout << " --channel       specify channel to be used ('incl'). Options are:"                << endl;
    cout << "                 'incl', '4mu', '4e', '2mu2e', '2e2mu', '4l', '2l2l'"              << endl;
    cout << " --fileName      Set ROOT filename for Histos to be used (''). If blank, it is"    << endl;
    cout << "                 defined by mcVersion setting as 'XsecInputs_30bin_mc16.root'"     << endl;
    cout << " --sysFilename   Set ROOT filename for systematics to be used (''). If blank, it"  << endl;
    cout << "                 is defined by mcVersion setting as "                              << endl;
    cout << "                 'XsecInputs_30bin_Systematics.root'"                              << endl;
    cout << " --acFileName    Set ROOT filename for aF/cF Nominal values (''). If blank, it is" << endl;
    cout << "                 defined by mcVersion setting as "                                 << endl;
    cout << "                 'XsecInputs_30bin_ACRfactors_mc16.root'"                          << endl;
    cout << " --acSysFilename Set ROOT filename for aF/cF systematics to be used (''). "        << endl;
    cout << "                 If blank, it is defined by mcVersion setting as "                 << endl;
    cout << "                 'XsecInputs_ACRfactors_mc16_Systematics.root'"                    << endl;
    cout << " --nBins         Set number of bins to be used (''). If blank, it is set to "      << endl;
    cout << "                 '30bin' ('110bin') without (with) floatqqZZ option."              << endl;
    cout << " --pathToFile    specify path to root files ('../varsDistro/')"                    << endl;
    cout << " --dataPath      specify path to A, C, R, xsec files ('../ValReader/Values/')"     << endl;
    cout << " --fidChan       enable Fiducial single channel xsec measurement ('false')"        << endl;
    cout << " --fidComb       enable Fiducial comb xsec measurement ('false')"                  << endl;
    cout << " --fidTotal      enable Fiducial total xsec measurement ('false')"                 << endl;
    cout << " --fid4l         enable Fiducial total xsec measurement for 4e+4mu ('false')"      << endl;
    cout << " --fid2l2l       enable Fiducial total xsec measurement for 2e2mu+2mu2e ('false')" << endl;
    cout << " --fidSum        enable Fiducial xsec measurement summing all channels ('false')"  << endl;
    cout << " --BRdiff        fit the BR difference 4mu/4e vs 2e2mu/2mu2e ('false')"            << endl;
    cout << " --doFit         enable fit at the end of workspace creation ('false')"            << endl;
    cout << " --do2D          enable 2D mode, fitting m4l in each variable bin ('false')"       << endl;
    cout << " --addSys        use systematics uncertainties ('false')"                          << endl;
    cout << " --addShapeSys   use m4l shape systematics ('false')"                              << endl;
    cout << " --addAsys       add A factor systematics ('false')"                               << endl;
    cout << " --skipPruning   skip pruning sys uncertainties ('false')"                         << endl;
    cout << " --sysBands      create systematic bands ('false')"                                << endl;
    cout << " --lumi          set integrated luminosity ('145.0' 1/fb)"                         << endl;
    cout << " --skipScan      skip NLL scan ('false')"                                          << endl;
    cout << " --useMCData     use MCData for expected ('false')"                                << endl;
    cout << " --withData      include real Data ('false')"                                      << endl;
    cout << " --useBornLep    use Born leptons instead of Dressed leptons ('false')"            << endl;
    cout << " --parallel      enable parallel mode for fit ('false'). Not suggested for now"    << endl;
    cout << " --chSplit       set final state splitting mode for inclusive case ('0' = incl)"   << endl;
    cout << "                 Options are: 0=incl, 1=2l2l+2l2l, 2=all channels"                 << endl;
    cout << " --dataSet       set dataSetName mode (' '). Do not use it"                        << endl;
    cout << " --mcVersion     set MC version ('0' = all mc16). Options are:"                    << endl;
    cout << "                  0 (mc16), 1 (mc15c), 2 (mc16a), 3 (mc16d)"                       << endl;
    cout << " --fixSys        select sys to fix profiled to data ('NO'). Options are:"          << endl;
    cout << "                 'all', 'muon', 'electron', 'jet', 'qqZZ', 'sig', 'NO'"            << endl;
    cout << " --prodMode      select prod mode to be studied ('MergProd'). Options are:"        << endl;
    cout << "                 'AllSig', 'ggH', 'VBF', 'WH', 'ZH', 'ttH', 'bbH', 'ggHbbH',"      << endl;
    cout << "                 'VH', 'MergProd'"                                                 << endl;
    cout << " --prodHist      select prod mode histograms to be used ('AllSig'). Options are:"  << endl;
    cout << "                 'AllSig', 'ggH', 'VBF', 'WH', 'ZH', 'ttH', 'ggHbbH', 'VH'"        << endl;
    cout << " --bkgHist       select bkg hist to be used ('allZZ'). Options are:"               << endl;
    cout << "                 'allZZ', 'redbkg', 'multiboson'"  	                        << endl;
    cout << " --doMatrix      enable using matrix unfolding ('false' = bin-by-bin)"             << endl;
    cout << " --inputMtx      set input MC for unfolding (''). If blank, it matches prodMode."  << endl;
    cout << "                 Options are: 'ggH', 'MG5', 'VBF', 'WH', 'ZH', 'ttH'"              << endl;
    cout << " --doCFsplit     enable using cF with truth matching ('false' = bin-by-bin)"       << endl;
    cout << " --reduceM4lBins enable reducing m4l binning ('false')"                            << endl;
    cout << " --floatqqZZ     enable floating qqZZ normalization and mass window 105-160 GeV"   << endl;
    cout << "                 (default set to 'false')"			                        << endl;
    cout << " --bkgOption     choose which backgrounds to include (default 'all')"		<< endl;
    cout << "                 Options are: 'all', 'ZZ', or 'none'"				<< endl; 
    cout << " --debug         set debug mode ('false')"                                         << endl;
    cout << " --verbose       set verbose mode ('false')"                                       << endl;
    cout << "                                                                              "    << endl;
    cout << " -------------------------------- REMARKS ----------------------------------- "    << endl;
    cout << "                                                                              "    << endl;
    cout << "   option --variable is needed when none of Fiducial flag is enabled."             << endl;
    cout << "   option --channel  is needed when none of Fiducial flag is enabled,"             << endl;
    cout << "                     but for now 'incl' is used as default"                        << endl;
    exit(0);
  }

  FillMcVersionsMap();
  if( opt.binStr=="" ){
    opt.binStr = "30bin";
    if( opt.floatqqZZ ) {opt.binStr = "110bin"; opt.do2D = true; }
  }
  else
    cout << "\033[0;35m WARNING:: using user defined binStr! \033[0m" << endl;
  
  if( opt.FileName=="" ) 
    opt.FileName = "XsecInputs_"+opt.binStr+"_"+m_mcTypeMap[opt.mcVersion]+".root";
  else
    cout << "\033[0;35m WARNING:: using user defined FileName! \033[0m" << endl;
 
  if( opt.SysFileName=="" )
    opt.SysFileName = "XsecInputs_"+opt.binStr+"_"+m_mcTypeMap[opt.mcVersion]+"_Systematics.root";
  else
    cout << "\033[0;35m WARNING:: using user defined SysFileName! \033[0m" << endl;
  
  if( opt.AcFileName=="" )
    if ( opt.matrix ) opt.AcFileName = "XsecInputs_"+opt.binStr+"_MatrixARfactors_"+m_mcTypeMap[opt.mcVersion]+".root";
    else              opt.AcFileName = "XsecInputs_"+opt.binStr+"_ACRfactors_"+m_mcTypeMap[opt.mcVersion]+".root";
  else
    cout << "\033[0;35m WARNING:: using user defined AcFileName! \033[0m" << endl;
  
  if( opt.AcSysFileName=="" )
    if ( opt.matrix ) opt.AcSysFileName = "XsecInputs_"+opt.binStr+"_MatrixARfactors_"+m_mcTypeMap[opt.mcVersion]+"_Systematics.root";
    else              opt.AcSysFileName = "XsecInputs_"+opt.binStr+"_ACRfactors_"+m_mcTypeMap[opt.mcVersion]+"_Systematics.root";
  else
    cout << "\033[0;35m WARNING:: using user defined AcSysFileName! \033[0m" << endl;

  if( opt.FidChan || opt.FidTotal || opt.Fid4l || opt.Fid2l2l || opt.FidSum || opt.FidComb || opt.BRDiff )
    opt.Fiducial = true;
  
  if( opt.Fiducial && opt.do2D ){
    cout << "\033[1;35m WARNING:: Doing Fiducial measurement but do2D enabled: " << endl;
    cout << "                     2D must be disabled! Disabling ... \033[0m "   << endl;
    opt.do2D = false;
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
    opt.Channel  = "incl";
    opt.Variable = "m4l";
    if(opt.chSplit==1){
      cout << "\033[1;35m WARNING:: Doing Fiducial measurement, but chSplit = 1: "     << endl;
      cout << "                     value not allowed, resetting default ... \033[0m " << endl;
      opt.chSplit = 0;
    }
  }

  if(opt.matrix && opt.ProdMode=="MergProd"){
    cout << "\033[1;35m WARNING:: Using Inversion Matrix mode, but " << opt.ProdMode << " set: " << endl;
    cout << "                     switching to AllSig ... \033[0m "   << endl;
    opt.ProdMode = "AllSig";
  }

  string MtxChoice      = ( (opt.InputMtx=="") ? opt.ProdMode : opt.InputMtx );
  string ProdHistChoice = ( (opt.ProdHist=="") ? opt.ProdMode : opt.ProdHist );
  
  cout << "Calling WorkSpaceMaker Class with options: " << endl;
  cout << "     fidChan       = " << opt.FidChan          << endl;
  cout << "     fidComb       = " << opt.FidComb          << endl;
  cout << "     fidTotal      = " << opt.FidTotal         << endl;
  cout << "     fid4l         = " << opt.Fid4l            << endl;
  cout << "     fid2l2l       = " << opt.Fid2l2l          << endl;
  cout << "     fidSum        = " << opt.FidSum           << endl;
  cout << "     BRdiff        = " << opt.BRDiff           << endl;
  cout << "     variable      = " << opt.Variable         << endl;
  cout << "     channel       = " << opt.Channel          << endl;
  cout << "     fileName      = " << opt.FileName         << endl;
  cout << "     sysFileName   = " << opt.SysFileName      << endl;
  cout << "     acfileName    = " << opt.AcFileName       << endl;
  cout << "     acsysFileName = " << opt.AcSysFileName    << endl;
  cout << "     pathToFile    = " << opt.PathToFile       << endl;
  cout << "     dataPath      = " << opt.DataPath         << endl;
  cout << "     addSys        = " << opt.addSys           << endl;
  cout << "     addShapeSys   = " << opt.addShapeSys      << endl;
  cout << "     addAsys       = " << opt.addAsys          << endl;
  cout << "     skipPruning   = " << opt.skipPruning      << endl;
  cout << "     sysBands      = " << opt.sysBands         << endl;
  cout << "     debug         = " << opt.debug            << endl;
  cout << "     verbose       = " << opt.verbose          << endl;
  cout << "     do2D          = " << opt.do2D             << endl;
  cout << "     lumi          = " << opt.Lumi             << endl;
  cout << "     chSplit       = " << opt.chSplit          << endl;
  cout << "     mcVersion     = " << opt.mcVersion        << endl;
  cout << "     fixSys        = " << opt.fixSys           << endl;
  cout << "     doFit         = " << opt.doFit            << endl;
  cout << "     withData      = " << opt.WithData         << endl;
  cout << "     useBornLep    = " << opt.useBornLep       << endl;
  cout << "     parallel      = " << opt.parallel         << endl;
  cout << "     skipScan      = " << opt.skipScan         << endl;
  cout << "     useMCData     = " << opt.useMCData        << endl;
  cout << "     dataSet       = " << opt.DataSet          << endl;
  cout << "     doMatrix      = " << opt.matrix           << endl;
  cout << "     doCFsplit     = " << opt.cfsplit          << endl;
  cout << "     prodMode      = " << opt.ProdMode         << endl;
  cout << "     prodHist      = " << ProdHistChoice       << endl;
  cout << "     bkgHist       = " << opt.BkgHist	  << endl;
  cout << "     inputMtx      = " << MtxChoice            << endl;
  cout << "     reduceM4lBins = " << opt.reduceM4lBins    << endl;
  cout << "     floatqqZZ     = " << opt.floatqqZZ	  << endl;
  cout << "     bkgOption     = " << opt.bkgOption        << endl;
  cout << "     binStr        = " << opt.binStr           << endl;
  
  WorkSpaceMaker *wp = new WorkSpaceMaker(opt.Variable,      opt.Channel,
					  opt.FileName,      opt.SysFileName,
					  opt.AcFileName,    opt.AcSysFileName,
					  opt.PathToFile,    opt.DataPath,
					  opt.Lumi,          opt.FidChan,
					  opt.FidComb,       opt.FidTotal,
					  opt.Fid4l,         opt.Fid2l2l,
					  opt.FidSum,	     opt.BRDiff,
					  opt.debug,         opt.verbose,
					  opt.addSys, 	     opt.addShapeSys,
					  opt.do2D,          opt.doFit,
					  opt.WithData,      opt.useBornLep,
					  opt.parallel,      opt.DataSet,
					  opt.sysBands,      opt.skipScan,
					  opt.useMCData,     opt.fixSys,
					  opt.matrix,        opt.cfsplit,
					  opt.ProdMode,      opt.ProdHist,
					  opt.BkgHist,	     opt.InputMtx,
					  opt.chSplit,       opt.mcVersion,
					  opt.reduceM4lBins, opt.floatqqZZ,
					  opt.bkgOption,     opt.binStr,
					  opt.skipPruning,   opt.addAsys);
  wp->RunClass();
  return 0;
  
}

WorkSpaceMaker :: WorkSpaceMaker(string Variable,    string Channel,
				 string FileName,    string SysFileName,
				 string AcFileName,  string AcSysFileName,
				 string PathToFile,  string DataPath,
				 double lumi,	     bool FidChan,
				 bool FidComb,	     bool FidTotal,
				 bool Fid4l,	     bool Fid2l2l,
				 bool FidSum,	     bool BRDiff,
				 bool debug,  	     bool verbose,
				 bool addSys,        bool addShapeSys,
				 bool do2D,          bool dofit,
				 bool WithData,      bool useBornLep,
				 bool parallel,	     string DataSet,
				 bool sysBands,      bool skipScan,
				 bool useMCData,     string fixSys,
				 bool matrix,        bool cfsplit,
				 string ProdMode,    string ProdHist,
				 string BkgHist,     string InputMtx,
				 int chSplit,        int mcVersion,
				 bool reduceM4lBins, bool floatqqZZ,
				 string bkgOption,   string binStr,
				 bool skipPruning,   bool addAsys){
  
  TH1::SetDefaultSumw2(kTRUE);
  
  m_FileName      = FileName;
  m_SysFileName   = SysFileName;
  m_AcFileName    = AcFileName;
  m_AcSysFileName = AcSysFileName;
  m_PathToFile    = PathToFile;
  m_DataPath      = DataPath;
  m_VariableId    = GetVariableID(Variable);
  m_Channel       = Channel;
  m_FidChan       = FidChan;
  m_FidComb       = FidComb;
  m_FidTotal      = FidTotal;
  m_Fid4l         = Fid4l;
  m_Fid2l2l       = Fid2l2l;
  m_FidSum        = FidSum;
  m_BRDiff        = BRDiff;
  m_debug         = debug;
  m_verbose       = verbose;
  m_addSys        = addSys;
  m_addShapeSys   = addShapeSys;
  m_addAsys       = addAsys;
  m_skipPruning   = skipPruning;
  m_sysBands      = sysBands;
  m_do2D          = do2D;
  m_ChNum         = GetChannelID(m_Channel);
  m_lumi          = lumi;
  m_chSplit       = chSplit;
  m_mcVers        = mcVersion;
  m_dofit         = dofit;
  m_WithData      = WithData;
  m_useBornLep    = useBornLep;
  m_parallel      = parallel;
  m_DataSet       = DataSet;
  m_skipScan      = skipScan;
  m_useMCData     = useMCData;
  m_fixSys        = fixSys;
  m_ProdMode      = ProdMode;
  m_ProdHist	  = (ProdHist!= "") ? ProdHist : ProdMode ;
  m_BkgHist	  = BkgHist;
  m_InputMtx	  = (InputMtx!= "") ? InputMtx : ProdMode ;
  m_matrix        = matrix;
  m_cfsplit       = cfsplit;
  m_Dir           = "";//GetCurrentWorkingDir()+"/";
  m_multProd      = (m_ProdMode=="AllProd" || m_ProdMode=="MergProd") ? true : false;
  m_redM4lBins    = reduceM4lBins;
  m_floatqqZZ	  = floatqqZZ;
  m_bkgOption     = bkgOption;
  m_Bstr          = binStr;
  
  if( m_FidChan || m_FidTotal || m_Fid4l || m_Fid2l2l || m_FidSum  || m_FidComb || m_BRDiff )
    m_Fiducial=true;
  else
    m_Fiducial=false;

  if(m_Fiducial)  m_Variable = "m";
  else            m_Variable = GetVariableName(m_VariableId);

  SetDebugLevel(m_debug);
  SetAtlasStyle();
  
}

void WorkSpaceMaker :: RunClass(){
  
  PRINT_INFO(" NOT SYSTEMATIC UNCERTAINTIES IMPLEMENTED FOR NOT FIDUCIAL");
  if(!m_debug)   PRINT_INFO(" DEBUG = 0 MINIMAL SET OF INFO PRINTED");
  if(m_debug)    PRINT_INFO(" DEBUG = 1 INFO PRINTED");
  if(m_verbose)  PRINT_INFO(" VERBOSE = 1 HUGE AMOUNT OF INFO PRINTED");
  if(!m_verbose) defineCoutDetails();
  
  InitializeIO();
  doDifferentialFiducial();
  DoWS();
  
}

void WorkSpaceMaker :: doDifferentialFiducial(){
  
  PRINT_BEGIN_FUNCTION("<doDifferential()>:: evaluating differential xsec");

  if(m_floatqqZZ && m_addSys) m_ZZbins = FillZZBin(m_VariableId);

  for( unsigned ch =0 ; ch < m_channels.size(); ++ch ){

    for( int i=0; i < int(m_Category.size()/m_channels.size()); i++ ){

      if( m_multProd )
        DoSignalPdf( "AllSig", m_channels.at(ch), i );
      else
        DoSignalPdf( m_ProdMode, m_channels.at(ch), i );
      if( m_bkgOption == "none" ) DoBackgroundPdf(m_channels.at(ch), false, false, false, i); //sig only band
      if( m_bkgOption == "ZZ"   ) DoBackgroundPdf(m_channels.at(ch), true , true, false, i);
      if( m_bkgOption == "all"  ) DoBackgroundPdf(m_channels.at(ch), true , true, true, i);
      
    }
    
  }
  PRINT_END_FUNCTION("<doDifferential()>");
  
}

void WorkSpaceMaker :: defineCoutDetails(){
  
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
  RooMsgService::instance().getStream(1).removeTopic(Generation);
  RooMsgService::instance().getStream(1).removeTopic(Minimization);
  RooMsgService::instance().getStream(1).removeTopic(Plotting);
  RooMsgService::instance().getStream(1).removeTopic(Fitting);
  RooMsgService::instance().getStream(1).removeTopic(Integration);
  RooMsgService::instance().getStream(1).removeTopic(LinkStateMgmt);
  RooMsgService::instance().getStream(1).removeTopic(Eval);
  RooMsgService::instance().getStream(1).removeTopic(Caching);
  RooMsgService::instance().getStream(1).removeTopic(Optimization);
  RooMsgService::instance().getStream(1).removeTopic( ObjectHandling);
  RooMsgService::instance().getStream(1).removeTopic(InputArguments);
  RooMsgService::instance().getStream(1).removeTopic(Tracing);
  RooMsgService::instance().getStream(1).removeTopic(Contents);
  RooMsgService::instance().getStream(1).removeTopic(DataHandling);
  RooMsgService::instance().getStream(1).removeTopic(NumIntegration);
  gErrorIgnoreLevel = 1001; /// remove info messages

}
