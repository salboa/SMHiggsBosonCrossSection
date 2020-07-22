#define EventLoop_cxx

/* Class includes */
#include "EventLoop.h"
#include "EvtLoop_Core.cxx"
#include "EvtLoop_Utils.cxx"
#include "EvtLoop_Weights.cxx"
#include "EvtLoop_Fill.cxx"
#include "EvtLoop_MatrixACR.cxx"
#include "EvtLoop_Cond.cxx"

EventLoop::EventLoop(){

  PRINT_DEBUG("<EventLoop()>:: Initializing EventLoop ...");
  TH1::SetDefaultSumw2(kTRUE);
  m_Chain           = NULL;
  m_ThChain         = NULL;
  m_removeLepWeight = false;
  m_cutJetEta       = 2.5 ;
  m_cutJetPt        = 60. ;
  m_hmShift         = 0.20;
  m_Lumi            = 36.207705+44.307223+58.450261;
  
}

EventLoop::EventLoop( int Process      , int SysType       , int prodMode         ,
		      int mcType       , double Min        , double Max           ,
		      bool ShiftUp     , bool ShiftDown    , bool isContReg       ,
		      bool isCouplings , bool doACRfact    , int StxsStage        ,
		      bool useMatrix   , bool useRootThMtc , bool writeEvtList    ,
		      bool split_cF    , bool restrictJets , bool checkDuplicates ,
		      int procScale    , double valScale   , bool debug ){
  
  TH1::SetDefaultSumw2(kTRUE);
  m_debug             = debug;
  SetDebugLevel(m_debug);
  PRINT_DEBUG("<EventLoop()>:: Initializing EventLoop and setting options ...");
  m_Process           = Process;
  m_SystNum           = SysType;
  m_StxsStage         = StxsStage;
  m_ProdMode          = prodMode;
  m_mcType            = mcType;
  m_Min               = Min;
  m_Max               = Max;
  m_doShiftUp         = ShiftUp;
  m_doShiftDown       = ShiftDown;
  m_isContReg         = isContReg;
  m_isCouplings       = isCouplings;
  m_doACRfactor       = doACRfact;
  m_useMatrix         = useMatrix;
  m_restrictJets      = restrictJets;
  m_removeLepWeight   = false;
  m_checkDuplicates   = checkDuplicates;
  m_EvtList           = writeEvtList;
  m_useRootTruthMatch = useRootThMtc;
  m_ProcXStoScale     = procScale;
  m_ValXStoScale      = valScale;
  m_cutJetEta         = 2.5;
  m_cutJetPt          = 60.;
  m_hmShift           = 0.20;
  m_Lumi              = 36.207705+44.307223+58.450261;
  
  if(split_cF || m_useMatrix) m_doTruthMatch = true;
  else                        m_doTruthMatch = false;
  
  if(m_mcType==MCtype::All)
    PRINT_WARNING("<EventLoop()>:: class set with MC version = mc16: luminosity value ("+
		  std::to_string(m_Lumi)+") NOT read from minitrees ...");

  if(!m_checkDuplicates)
    PRINT_WARNING("<EventLoop()>:: check for events duplicates disabled!");

  if(m_Process==Process::MultiBoson){
    m_checkDuplicates = false;
    PRINT_WARNING("<EventLoop()>:: check for events duplicates on MultiBoson disabled!");
  }
  
}

void EventLoop::SetInitValues(int Process       , int SysType          ,
			      int prodMode      , int mcType           ,
			      double Min        , double Max           ,
			      bool ShiftUp      , bool ShiftDown       ,
			      bool isContReg    , bool isCouplings     ,
			      bool doACRfact    , int StxsStage        ,
			      bool useMatrix    , bool useRootThMtc    ,
			      bool writeEvtList , bool split_cF        ,
			      bool restrictJets , bool checkDuplicates ,
			      int procScale     , double valScale      ,
			      bool debug){
  
  m_debug = debug;
  SetDebugLevel(m_debug);
  PRINT_DEBUG("<EventLoop::SetInitValues()>:: Setting EventLoop options ...");
  
  m_Process           = Process;
  m_SystNum           = SysType;
  m_StxsStage         = StxsStage;
  m_ProdMode          = prodMode;
  m_mcType            = mcType;
  m_Min               = Min;
  m_Max               = Max;
  m_doShiftUp         = ShiftUp;
  m_doShiftDown       = ShiftDown;
  m_isCouplings       = isCouplings;
  m_isContReg         = isContReg;
  m_doACRfactor       = doACRfact;
  m_useMatrix         = useMatrix;
  m_restrictJets      = restrictJets;
  m_checkDuplicates   = checkDuplicates;
  m_EvtList           = writeEvtList;
  m_useRootTruthMatch = useRootThMtc;
  m_ProcXStoScale     = procScale;
  m_ValXStoScale      = valScale;

  if(split_cF || m_useMatrix) m_doTruthMatch = true;
  else                        m_doTruthMatch = false;
  
  if(m_mcType==MCtype::All)
    PRINT_WARNING("<EventLoop()>:: class set with MC version = mc16: luminosity value ("+
		  std::to_string(m_Lumi)+") NOT read from minitrees ...");

  if(!m_checkDuplicates)
    PRINT_WARNING("<EventLoop()>:: check for events duplicates disabled!");

  if(m_Process==Process::MultiBoson){
    m_checkDuplicates = false;
    PRINT_WARNING("<EventLoop()>:: check for events duplicates on MultiBoson disabled!");
  }
  
}

void EventLoop::SetRecoChain(TChain *rc_chain){

  PRINT_DEBUG("<EventLoop::SetRecoChain()>:: Setting reco chain ...");
  m_Chain = rc_chain;
  
}

void EventLoop::SetTruthChain(TChain *th_chain){

  PRINT_DEBUG("<EventLoop::SetTruthChain()>:: Setting truth chain ...");
  m_ThChain = th_chain;
  
}

void EventLoop::SetLepWeightUsage(bool choice){

  PRINT_DEBUG("<EventLoop::SetLepWeightUsage()> Setting lepton SF weight usage ...");
  m_removeLepWeight = choice;
  
}
