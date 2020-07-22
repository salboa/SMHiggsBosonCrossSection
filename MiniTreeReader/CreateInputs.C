#define CreateInputs_cxx

/* Class includes */
#include "CreateInputs_Histograms.cxx"
#include "CreateInputs_Utils.cxx"
#include "CreateInputs_RunProcs.cxx"
#include "CreateInputs_ACR.cxx"
#include "CreateInputs_Matrix.cxx"
#include "EventLoop.C"

class Options{
  
public:
  std::string Process        ;
  std::string variable       ;
  std::string ProcXStoScale  ;
  double      ValueToScale   ;
  int         nBins          ;
  int         sysNum         ;
  int         mcType         ;
  int         stage          ;
  double      Min            ;
  double      Max            ;
  bool        doShiftUp      ;
  bool        doShiftDown    ;
  bool        isControlReg   ;
  bool        isCouplings    ;
  bool        doACRfactor    ;
  bool        useMtxMode     ;
  bool        useRootThMtc   ;
  bool        writeEvtList   ;
  bool        debug          ;
  bool        acrDetails     ;
  bool        split_cF       ;
  bool	      restrictJets   ;
  bool        removeLepWeight;
  bool        checkDuplicates;
  
  void SetDefault(){
    Process         = ""   ;
    variable        = ""   ;
    ProcXStoScale   = ""   ;
    ValueToScale    = 0.0  ;
    nBins           = 30   ;
    sysNum          = 0    ;
    mcType          = 0    ;
    stage           = 0    ;
    Min             = 115.0;
    Max             = 130.0;
    doShiftUp       = false;
    doShiftDown     = false;
    isControlReg    = false;
    isCouplings     = false;
    doACRfactor     = false;
    useMtxMode      = false;
    useRootThMtc    = false;
    writeEvtList    = false;
    debug           = false;
    acrDetails      = false;
    split_cF        = false;
    restrictJets    = false;
    removeLepWeight = false;
    checkDuplicates = false;
  }

  bool checkOpt(char* opt, char* value){
    std::string val = value;
    if( 0==val.find("--") ){
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
    bool validCmd = false;
    std::string cmd = argv[i];
    if( !strcmp(argv[i],"--Process")              ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.Process         = argv[i+1]; }            validCmd = true; }
    else if( !strcmp(argv[i],"--variable")        ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.variable        = argv[i+1]; }            validCmd = true; }
    else if( !strcmp(argv[i],"--procXStoScale")   ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.ProcXStoScale   = argv[i+1]; }            validCmd = true; }
    else if( !strcmp(argv[i],"--valXStoScale")    ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.ValueToScale    = std::stod(argv[i+1]); } validCmd = true; }
    else if( !strcmp(argv[i],"--nBins")           ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.nBins           = std::stoi(argv[i+1]); } validCmd = true; }
    else if( !strcmp(argv[i],"--sysNumber")       ){	    
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.sysNum          = std::stoi(argv[i+1]); } validCmd = true; }
    else if( !strcmp(argv[i],"--mcType")          ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.mcType          = std::stoi(argv[i+1]); } validCmd = true; }
    else if( !strcmp(argv[i],"--stxsStage")       ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.stage           = std::stoi(argv[i+1]); } validCmd = true; }
    else if( !strcmp(argv[i],"--Min")             ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.Min             = std::stod(argv[i+1]); } validCmd = true; }
    else if( !strcmp(argv[i],"--Max")             ){
      if( opt.checkOpt(argv[i],argv[i+1]) )        { opt.Max             = std::stod(argv[i+1]); } validCmd = true; }
    else if( !strcmp(argv[i],"--doShiftUp")       ){ opt.doShiftUp       = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--doShiftDown")     ){ opt.doShiftDown     = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--isControlReg")    ){ opt.isControlReg    = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--isCouplings")     ){ opt.isCouplings     = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--doACRfactor")     ){ opt.doACRfactor     = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--useMtxMode")      ){ opt.useMtxMode      = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--useRootThMtc")    ){ opt.useRootThMtc    = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--writeEvtList")    ){ opt.writeEvtList    = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--debug")           ){ opt.debug           = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--acrDetails")      ){ opt.acrDetails      = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--split_cF")        ){ opt.split_cF        = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--restrictJets")    ){ opt.restrictJets    = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--removeLeoWeight") ){ opt.removeLepWeight = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--checkDuplicates") ){ opt.checkDuplicates = true;                   validCmd = true; }
    else if( !strcmp(argv[i],"--help")            ){ printHelp           = true;                   validCmd = true; }
    if( !validCmd && cmd.find("--")!=std::string::npos){
      std::cout << "\033[1;31m option " << cmd << " not valid. Type ./CreateInputs"
		<< " --help and check the available options, exit!\033[0m"  << std::endl;
      exit(0);
    }
  }
  if( printHelp ){
    std::cout << "CreateInputs: Run HZZ xsec inputs maker !!"                          << std::endl;
    std::cout << "  usage  :  ./CreateInputs [--help] [--Process] [--nBins]"           << std::endl;
    std::cout << "                           [--sysNumber] [--mcType] [--stxtStage]"   << std::endl;
    std::cout << "                           [--Min] [--Max] [--doShiftUp]"            << std::endl;
    std::cout << "                           [--doShiftDown] [--isControlReg]"         << std::endl;
    std::cout << "                           [--isCouplings] [--doACRfactor]"          << std::endl;
    std::cout << "                           [--useMtxMode] [--writeEvtList]"          << std::endl;
    std::cout << "                           [--acrDetails] [--split_cF]"              << std::endl;
    std::cout << "                           [--useRootThMtc] [--variable]"            << std::endl;
    std::cout << "                           [--restrictJets] [--removeLepWeight]"     << std::endl;
    std::cout << "                           [--checkDuplicates] [--procXStoScale]"    << std::endl;
    std::cout << "                           [--valXStoScale] [--debug]"               << std::endl;
    std::cout << "                                                                 "   << std::endl;
    std::cout << " Optional arguments (default value): "                               << std::endl;
    std::cout << " --help            print this help and exit"                         << std::endl;
    std::cout << " --Process         set physics process. Options are: 'ggH', 'VBF',"  << std::endl;
    std::cout << "                   'WH', 'ZH', 'ttH', 'AllSig', qqZZ', 'ggZZ',"      << std::endl;
    std::cout << "                   'Zjets', 'redBkg'"                                << std::endl;
    std::cout << " --variable        set variable to process ("" = all)"               << std::endl;
    std::cout << " --nBins           set Number of bins for m4l plots (30)"            << std::endl;
    std::cout << " --Min             set Lower m4l range (115)"                        << std::endl;
    std::cout << " --Max             set Upper m4l range (130)"                        << std::endl;
    std::cout << " --sysNumber       specify sy number (0)"                            << std::endl;
    std::cout << " --mcType          set MC releases to be used (0). Options are: "    << std::endl;
    std::cout << "                   0 (mc16), 1 (mc15c), 2 (mc16a), 3 (mc16d)"        << std::endl;
    std::cout << " --stxsStage       set the STXT Stage (0). Options are: 0 (Stage0)," << std::endl;
    std::cout << "                   1 (Stage1), 2 (RedStage1)"                        << std::endl;
    std::cout << " --doShiftUp       enable m4l+200 MeV shift (false)"                 << std::endl;
    std::cout << " --doShiftDown     enable m4l-200 MeV shift (false)"                 << std::endl;
    std::cout << " --isControlReg    enable control region mode (false)"               << std::endl;
    std::cout << " --isCouplings     enable couplings analysis (false)"                << std::endl;
    std::cout << " --doACRfactor     enable calculating A, C, r factors (false)"       << std::endl;
    std::cout << " --useMtxMode      enable Matrix Mode for A, C, r factors (false)"   << std::endl;
    std::cout << " --useRootThMtc    enable ROOT truth matching (false)"               << std::endl;
    std::cout << " --writeEvtList    enable writing list of selected events (false)"   << std::endl;
    std::cout << " --acrDetails      enable printing ACR evaluation details (false)"   << std::endl;
    std::cout << " --split_cF        enable cF splitting into non-Fiducial (false)"    << std::endl;
    std::cout << " --restrictJets    enable restricting jets phase space (false)"      << std::endl;
    std::cout << " --removeLepWeight enable removing lep SF from total weight (false)" << std::endl;
    std::cout << " --checkDuplicates enable check for events duplicates (false)"       << std::endl;
    std::cout << " --procXStoScale   specify the process to which scale the XS ('')"   << std::endl;
    std::cout << " --valXStoScale    specify the XS scaling value (0). N.B: if set to" << std::endl;
    std::cout << "                   -10, the code will decrese XS value by 10%"       << std::endl;
    std::cout << " --debug           set debug mode (false)"                           << std::endl;
    exit(0);
  }

  if(opt.debug){
    std::cout << "Calling CreateInputs Class with options: "   << std::endl;
    std::cout << "  Process         = " << opt.Process         << std::endl;
    std::cout << "  variable        = " << opt.variable        << std::endl;   
    std::cout << "  nBins           = " << opt.nBins           << std::endl;
    std::cout << "  Min             = " << opt.Min             << std::endl;
    std::cout << "  Max             = " << opt.Max             << std::endl;
    std::cout << "  sysNumber       = " << opt.sysNum          << std::endl;
    std::cout << "  mcType          = " << opt.mcType          << std::endl;
    std::cout << "  sxtsStage       = " << opt.stage           << std::endl;
    std::cout << "  doShiftUp       = " << opt.doShiftUp       << std::endl;
    std::cout << "  doShiftDown     = " << opt.doShiftDown     << std::endl;
    std::cout << "  isControlReg    = " << opt.isControlReg    << std::endl;
    std::cout << "  isCouplings     = " << opt.isCouplings     << std::endl;
    std::cout << "  doACRfactor     = " << opt.doACRfactor     << std::endl;
    std::cout << "  useMtxMode      = " << opt.useMtxMode      << std::endl;
    std::cout << "  useRootThMtc    = " << opt.useRootThMtc    << std::endl;
    std::cout << "  writeEvtList    = " << opt.writeEvtList    << std::endl;
    std::cout << "  acrDetails      = " << opt.acrDetails      << std::endl;
    std::cout << "  split_cF        = " << opt.split_cF        << std::endl;
    std::cout << "  restrictJets    = " << opt.restrictJets    << std::endl;
    std::cout << "  removeLepWeight = " << opt.removeLepWeight << std::endl;
    std::cout << "  checkDuplicates = " << opt.checkDuplicates << std::endl;
    std::cout << "  procXStoScale   = " << opt.ProcXStoScale   << std::endl;
    std::cout << "  valXStoScale    = " << opt.ValueToScale    << std::endl;
  }
  
  CreateInputs *mp = new CreateInputs(opt.Process         , opt.nBins           ,
				      opt.Min             , opt.Max             ,
				      opt.doShiftUp       , opt.doShiftDown     ,
				      opt.sysNum          , opt.mcType          ,
				      opt.isControlReg    , opt.isCouplings     ,
				      opt.doACRfactor     , opt.stage           ,
				      opt.useMtxMode      , opt.useRootThMtc    ,
				      opt.writeEvtList    , opt.acrDetails      ,
				      opt.split_cF        , opt.variable        ,
				      opt.restrictJets    , opt.removeLepWeight ,
				      opt.checkDuplicates , opt.ProcXStoScale   ,
				      opt.ValueToScale    , opt.debug);
  
  mp->Process();
  mp->TimeCount();
  
  return 0;
  
}
  
CreateInputs::CreateInputs(std::string Process  , int Nbins             ,
			   double Min           , double Max            ,
			   bool ShiftUp         , bool ShiftDown        ,
			   int sysNum           , int mcType            ,
			   bool isContReg       , bool isCouplings      ,
			   bool doACRfact       , int Stage             ,
			   bool useMtx          , bool useRootThMtc     ,
			   bool writeEvtList    , bool acrDetails       ,
			   bool split_cF        , std::string Var       ,
			   bool restrictJets    , bool removeLepWeight  ,
			   bool checkDuplicates , std::string procScale ,
			   double valScale      , bool debug            ){

  m_begin = std::chrono::system_clock::now();
  
  TH1::SetDefaultSumw2(kTRUE);
  m_debug           = debug;
  m_acrDetails      = acrDetails;
  SetDebugLevel(m_debug);
  PRINT_DEBUG("<CreateInputs()>:: Initializing CreateInputs ...");
  m_ProcStr         = Process;
  m_Process         = GetProcessNumber(Process);
  m_SystNum         = sysNum;
  m_mcVers          = mcType;
  m_Stage           = Stage;
  m_Nbins           = Nbins;
  m_Min             = Min;
  m_Max             = Max;
  m_doShiftUp       = ShiftUp;
  m_doShiftDown     = ShiftDown;
  m_isContReg       = isContReg;
  m_isCouplings     = isCouplings;
  m_doACRfactor     = doACRfact;
  m_useMatrix       = useMtx;
  m_useRootThMtc    = useRootThMtc;
  m_EvtList         = writeEvtList;
  m_split_cF        = split_cF;
  m_restrictJets    = restrictJets;
  m_removeLepWeight = removeLepWeight;
  m_checkDuplicates = checkDuplicates;
  if(procScale!="") m_procXStoScale = GetProcessNumber(procScale);
  else              m_procXStoScale = -1;
  m_valXStoScale    = valScale;
  m_keepTruth       = false;
  m_useTruth        = false;
  m_isLocal         = true;
  m_isDell          = false;
  m_isCedar         = false;
  m_In              = NULL;
  m_Out             = NULL;
  m_treename        = "tree_incl_all";
  m_chain           = NULL;
  m_thchain         = NULL;

  if(m_useMatrix && !m_doACRfactor){
    PRINT_INFO("<CreateInputs>:: matrix mode enabled without ACRfactor option! enabling it ...");
    m_doACRfactor = true;
  }
  
  if(m_doACRfactor){
    m_useTruth = true;
  }

  if( m_Process==Process::Zjets && (Var!="" && Var!="m4l") ){
    m_diffVars.push_back("m4l");
  }
  FillDiffVarVector(Var,!m_doACRfactor);
  
  if(m_SystNum!=0 && m_SystNum%2!=0) m_doSystematics = true;
  else                               m_doSystematics = false;
  
  if(m_Process==Process::data  || m_Process==Process::MG5){
    m_doSystematics=false;
    m_SystNum = 0;
  }
  LoadSysMap();
  MakeChanMaps();
  
  if(m_isCouplings && m_Process<=Process::VH) //to be added ggZH
    FillCategories(m_Stage);
  else
    FillVarsRanges();

  SetMCtypes();
  DetectHostname();
  SetDirPrefix();
  
}

void CreateInputs::Process(){

  PRINT("<CreateInputs::Process()>:: Processing Sample = "+m_ProcStr+
	", String bins "+std::to_string(m_Nbins)+" (for m4l plots) ");
  
  m_chain = new TChain( m_treename.c_str() );
  if(m_useTruth) m_thchain = new TChain( m_treename.c_str() );
    
  if(m_doACRfactor){
    if(m_useMatrix) EvaluateMatrix();
    else            EvaluateACRfactors();
    return;
  }

  if(m_Min!=115 && m_Max!=130) m_addFineM4l = true;

  if(m_Process==Process::redBkg){
    if(m_SystNum==Syst::ZjetsSystematics){
      for(auto &mp: m_SysMap){
	DefineOutFile(m_SystNum);
	SetChains(Syst::NOMINAL);
	MergeRedBkg(mp.second);
	m_Out->Close();
	m_In->Close();	
      }
    }
    else{
      DefineOutFile(Syst::NOMINAL);
      SetChains(Syst::NOMINAL);
      MergeRedBkg();
      m_Out->Close();
      m_In->Close();
    }
    return;
  }
  
  for(auto &mp: m_SysMap){
    
    PRINT("<CreateInputs::Process()>:: Systematic = "+std::to_string(mp.first)+
	  " ("+mp.second+"), Sample = "+m_ProcStr);
    
    DefineOutFile(mp.first);
    
    SetChains(mp.first);
    
    DefineHistograms(mp.first);
    
    if( m_Process==Process::Zjets &&
	( (m_Min==115.0 && m_Max==130.0) || (m_Min==105.0 && m_Max==160.0) ) )
      MakeRedBkg(mp.first);
    else
      RunProcesses(mp.first);
    
    /* Divide Plots For BinSize*/
    if(!m_isCouplings){
      std::vector<TH1D*> Plots1D = ListOf1DPlotsToNorm();
      DivideForBinSize( Plots1D );
    }
    
    /* Write Plots To File */
    m_Out->cd();
    if(mp.first>Syst::NOMINAL){
      if( m_Out->GetDirectory( mp.second.c_str() )==0 )
    	m_Out->mkdir( mp.second.c_str() );
      m_Out->cd( mp.second.c_str() );
    }
    std::vector<TObject*> Plots = ListOfPlotsToWrite();
    for(uint p=0; p<Plots.size(); p++){
      Plots[p]->Write();
    }
    for(uint p=0; p<Plots.size(); p++){
      Plots[p]->Delete();
    }
    m_chain->Reset();
    m_Hmap.clear();
    m_Hmap2D.clear();
    m_HmapBins.clear();
    m_HmapBinsFine.clear();
    m_Out->Close();
    PRINT("");
  }
  
  if( m_Process==Process::Zjets &&
      ( (m_Min==115.0 && m_Max==130.0) || (m_Min==105.0 && m_Max==160.0) ) )
    m_In->Close();

}

void CreateInputs::TimeCount(){

  m_end         = std::chrono::system_clock::now();
  m_elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(m_end-m_begin).count();
  m_startTime   = std::chrono::system_clock::to_time_t(m_begin);
  m_endTime     = std::chrono::system_clock::to_time_t(m_end);
  
  std::cout << "<CreateInputs:TimeCount()>:: computation started at  "
	    << std::ctime(&m_startTime)
	    << "                             computation finished at "
	    << std::ctime(&m_endTime)
	    << "                             -> elapsed time = "
	    << m_elapsedTime << "s (" << m_elapsedTime/60. << "m)" << std::endl;
  
}
