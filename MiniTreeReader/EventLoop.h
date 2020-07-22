#ifndef EventLoop_H
#define EventLoop_H

/* C++ includes */
#include "iostream"
#include "set"
#include "tuple"
#include "map"
#include "vector"
#include <sys/stat.h>

/* ROOT includes */
#include <TH1.h>
#include <TH2.h>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TColor.h>
#include <TChain.h>

/* Other includes */
#include "../Utils/VarHandler.h"
#include "../Utils/Enum.h"

class EventLoop {

 public:
  
  /****************/
  /* Constructors */
  /****************/
  EventLoop();
  
  EventLoop( int Process      , int SysType       , int prodMode         ,
	     int mcType       , double Min        , double Max           ,
	     bool ShiftUp     , bool ShiftDown    , bool isContReg       ,
	     bool isCouplings , bool doACRfact    , int StxsStage        ,
	     bool useMatrix   , bool useRootThMtc , bool writeEvtList    ,
	     bool split_cF    , bool restrictJets , bool checkDuplicates ,
	     int procScale    , double valScale   , bool debug );
  
  /****************/
  /*   Methods    */
  /****************/

  /* Set Initial Values */
  void SetInitValues( int Process      , int SysType       , int prodMode         ,
		      int mcType       , double Min        , double Max           ,
		      bool ShiftUp     , bool ShiftDown    , bool isContReg       ,
		      bool isCouplings , bool doACRfact    , int StxsStage        ,
		      bool useMatrix   , bool useRootThMtc , bool writeEvtList    ,
		      bool split_cF    , bool restrictJets , bool checkDuplicates ,
		      int procScale    , double valScale   , bool debug );
  
  /* Set Chains */
  void SetRecoChain(TChain *rc_chain);
  void SetTruthChain(TChain *th_chain);
  
  /* Set Chain Branches */
  void SetChainBranches();
  void SetTruthChainBranches();

  /* Perform reco/truth event matching */
  ULong64_t PerformTruthMatching(ULong64_t evt, Int_t run);
  void FillTruthMatchingMaps();
  void FillRecoEventsMap();
  std::map<int, std::map<ULong64_t, std::vector<short int> > > GetTruthMatchingMap(int type);
  
  /* Loop on Events */
  void Loop(bool setChain=false, bool isPreTruthMatch=false, bool keepTruth=false);
  void TruthLoop();
  
  /* Get Event Weight */
  Double_t GetWeight();
  Double_t GetTruthWeight();

  /* Get Luminosity Value */
  double GetLuminosity(bool isTruth=false);

  /* Detect Cross Section Scale */
  double DetectCrossSectionScale();
  
  /* Set Histos Maps */
  void SetHistosMap(std::map< std::string,std::vector<TH1D*> > & Hmap);
  void SetHistos2DMap(std::map< std::string,std::vector<TH2D*> > & Hmap2D);
  void SetHistosM4lBins(std::map< std::string,std::map<short int,std::vector<TH1D*> > > & HmapBins,
			std::map< std::string,std::map<short int,std::vector<TH1D*> > > & HmapBinsFine);

  /* Set Values Maps */
  void SetCmaps( std::map< std::string, std::map< short int, std::vector<std::pair<double,double> > *> > & recoBorn,
		 std::map< std::string, std::map< short int, std::vector<std::pair<double,double> > *> > & recoDres,
		 std::map< std::string, std::map< short int, std::vector<std::pair<double,double> > *> > & recoBornRaw,
		 std::map< std::string, std::map< short int, std::vector<std::pair<double,double> > *> > & recoDresRaw,
		 std::map< std::string, std::vector<std::pair<double,double> > *> & recoBornInt,
		 std::map< std::string, std::vector<std::pair<double,double> > *> & recoDresInt,
		 std::map< std::string, std::vector<std::pair<double,double> > *> & recoBornRawInt,
		 std::map< std::string, std::vector<std::pair<double,double> > *> & recoDresRawInt );
  
  void SetARmaps( std::map< std::string, std::map< short int, std::vector<double> *> > & born,
		  std::map< std::string, std::map< short int, std::vector<double> *> > & bornRaw,
		  std::map< std::string, std::vector<double> *> & bornInt,
		  std::map< std::string, std::vector<double> *> & bornRawInt,
		  std::map< std::string, std::map< short int, std::vector<double> *> > & dres,
		  std::map< std::string, std::map< short int, std::vector<double> *> > & dresRaw,
		  std::map< std::string, std::vector<double> *> & dresInt,
		  std::map< std::string, std::vector<double> *> & dresRawInt,
		  std::map< std::string, std::map< short int, std::vector<double> *> > & truth,
		  std::map< std::string, std::map< short int, std::vector<double> *> > & truthRaw,
		  std::map< std::string, std::vector<double> *> & truthInt,
		  std::map< std::string, std::vector<double> *> & truthRawInt,
		  std::vector<double> * & integral,
		  std::vector<double> * & integralRaw );

  void SetMtxRecoMaps( std::map< std::string, std::map< short int, std::map <short int, std::vector <double> *> > > & rspMtxBorn_Num, 
		       std::map< std::string, std::map< short int, std::map <short int, std::vector <double> *> > > & rspMtxDres_Num, 
		       std::map< std::string, std::map< short int, std::vector< double > *> > & nonFidBorn,
		       std::map< std::string, std::map< short int, std::vector< double > *> > & nonFidDres );

  void SetMtxTruthMaps( std::map< std::string, std::map< short int, std::vector <double> *> > & rspMtxBorn_Denom,
			std::map< std::string, std::map< short int, std::vector <double> *> > & rspMtxDres_Denom );
			

  void SetTruthMatchingMaps(std::map<int, std::map<ULong64_t, std::vector<short int> > > thMtc_Born,
			    std::map<int, std::map<ULong64_t, std::vector<short int> > > thMtc_Dres);
  
  /* Fill Histograms */
  void FillHistograms();
  void FillCouplingsHistos();
  void FillXsecHistos();
  void FillHistoCategories(std::string type);

  /* Check Reco/Truth Conditions */
  bool PassCondition(int vNum, int bin, int type);
  double GetVariableValue(int vNum, int type);
  int GetVariableBin(int vNum, int type);
  bool PassMassChanFidCondition(int type);
  bool PassTruthMassCut();
  int CheckInternalProdMode(std::string file);
  void SetGlobalTruthConditions();
  
  /* Reduced Phase Space */
  void EvaluateJetVariables(int type);
  double GetJetVariableValue(int vNum, int type);
  double EvalDiJetMass();
  void FillJetVarValues(int var, double val, int type);
  std::vector<float> GetVariableVector(int vNum, int type);
  
  /* Fill Values */
  void FillRecoValues(bool keepTruth);
  void FillRecoValues4Mtx(bool keepTruth);
  void FillTruthValues();

  /* Set Lepton SF Weight Usage */
  void SetLepWeightUsage(bool choice);
  
 protected:

  /* Class Init Variables */
  int m_Process;
  int m_ProcXStoScale;
  double m_ValXStoScale;
  std::string m_Syst;
  int m_SystNum;
  int m_ProdMode;
  int m_IntProdMode;
  int m_StxsStage;
  int m_mcType;
  double m_Min;
  double m_Max;
  bool m_debug;
  bool m_doShiftUp;
  bool m_doShiftDown;
  bool m_isContReg;
  bool m_isCouplings;
  bool m_doACRfactor;
  bool m_useMatrix;
  bool m_EvtList;
  bool m_doTruthMatch;
  bool m_useRootTruthMatch;
  bool m_restrictJets;
  bool m_removeLepWeight;
  bool m_checkDuplicates;
  double m_cutJetEta;
  double m_cutJetPt;
  double m_hmShift;
  TChain *m_Chain;
  TChain *m_ThChain;

  /* Histograms maps */
  std::map< std::string,std::vector<TH1D*> > m_Histos;
  std::map< std::string,std::vector<TH2D*> > m_Histos2D;
  std::map< std::string,std::map<short int,std::vector<TH1D*> > > m_HistosBins;
  std::map< std::string,std::map<short int,std::vector<TH1D*> > > m_HistosBinsFine;

  /* A, C, r maps */
  std::map< std::string,std::map<short int,std::vector<std::pair<double,double> > *> > m_RecoBornVal;
  std::map< std::string,std::map<short int,std::vector<std::pair<double,double> > *> > m_RecoDresVal;
  std::map< std::string,std::map<short int,std::vector<std::pair<double,double> > *> > m_RecoBornRaw;
  std::map< std::string,std::map<short int,std::vector<std::pair<double,double> > *> > m_RecoDresRaw;
  std::map< std::string,std::vector<std::pair<double,double> > *> m_RecoBornValInt;
  std::map< std::string,std::vector<std::pair<double,double> > *> m_RecoDresValInt;
  std::map< std::string,std::vector<std::pair<double,double> > *> m_RecoBornRawInt;
  std::map< std::string,std::vector<std::pair<double,double> > *> m_RecoDresRawInt;
  std::map< std::string,std::map<short int,std::vector<double> *> > m_FidBornVal;
  std::map< std::string,std::map<short int,std::vector<double> *> > m_FidBornRaw;
  std::map< std::string,std::vector<double> *> m_FidBornValInt;
  std::map< std::string,std::vector<double> *> m_FidBornRawInt;
  std::map< std::string,std::map<short int,std::vector<double> *> > m_FidDresVal;
  std::map< std::string,std::map<short int,std::vector<double> *> > m_FidDresRaw;
  std::map< std::string,std::vector<double> *> m_FidDresValInt;
  std::map< std::string,std::vector<double> *> m_FidDresRawInt;
  std::map< std::string,std::map<short int,std::vector<double> *> > m_TruthVal;
  std::map< std::string,std::map<short int,std::vector<double> *> > m_TruthRaw;
  std::map< std::string,std::vector<double> *> m_TruthValInt;
  std::map< std::string,std::vector<double> *> m_TruthRawInt;
  std::vector<double> *m_TruthInt;
  std::vector<double> *m_TruthIntRaw;
  
  /* Matrix Maps */ 
  std::map< std::string, std::map< short int, std::map <short int, std::vector <double> *> > > m_RspMtxBorn_Num;
  std::map< std::string, std::map< short int, std::vector <double> *> > m_RspMtxBorn_Denom;
  std::map< std::string, std::map< short int, std::map <short int, std::vector <double> *> > > m_RspMtxDres_Num;
  std::map< std::string, std::map< short int, std::vector <double> *> > m_RspMtxDres_Denom;
  std::map< std::string, std::map< short int, std::vector< double > *> > m_NonFidBorn;
  std::map< std::string, std::map< short int, std::vector< double > *> > m_NonFidDres;

  /* Alternative Truth Matching maps */
  std::map<int, std::map<ULong64_t, short int > > m_thMtc_Reco;
  std::map<int, std::map<ULong64_t, std::vector<short int> > > m_thMtc_Born;
  std::map<int, std::map<ULong64_t, std::vector<short int> > > m_thMtc_Dres;
  
  /* Global Variables */ 
  Double_t mFinWgt;
  Double_t mThFinWgt;
  Float_t mFourLep;
  Int_t m_mrgChan;
  Int_t m_mrgThChanFidBorn;
  Int_t m_mrgThChanFidDres;
  Int_t m_mrgThChanTruth;
  Double_t mLumi;
  double m_Lumi;
  std::ofstream m_OutF;
  bool m_passThMassCut;
  bool m_passBornMassChan;
  bool m_passDresMassChan;

  /* Temporary jets variables/vectors */
  std::vector<float> m_tmpJetEta;
  std::vector<float> m_tmpJetPhi;
  std::vector<float> m_tmpJetPt;
  std::vector<float> m_tmpJetM;
  std::vector<float> m_JetEta;
  std::vector<float> m_JetPhi;
  std::vector<float> m_JetPt;
  std::vector<float> m_JetM;
  int    m_njetReco , m_njetBorn , m_njetDres , m_njetTruth ;
  double m_ljptReco , m_ljptBorn , m_ljptDres , m_ljptTruth ;
  double m_sjptReco , m_sjptBorn , m_sjptDres , m_sjptTruth ; 
  double m_etajjReco, m_etajjBorn, m_etajjDres, m_etajjTruth;
  double m_phijjReco, m_phijjBorn, m_phijjDres, m_phijjTruth;
  double m_mjjReco  , m_mjjBorn  , m_mjjDres  , m_mjjTruth  ;
  
  /* List for duplicates check */
  std::set< std::tuple<Int_t,ULong64_t,double> > m_procEvts;
    
  /*MiniTree Variables */
  Int_t              event_type                              ;
  ULong64_t          event                                   ;
  Int_t              run                                     ;
  Float_t            m4l_fsr                                 ;
  Float_t            pt4l_fsr                                ;
  Float_t            mZ1_fsr                                 ;
  Float_t            mZ2_fsr                                 ;
  Float_t            y4l_fsr                                 ;
  Float_t            cthstr_fsr                              ;
  Float_t            ct1_fsr                                 ;
  Float_t            ct2_fsr                                 ;
  Float_t            phi_fsr                                 ;
  Float_t            phi1_fsr                                ;
  std::vector<float> *jet_pt                                 ;
  std::vector<float> *jet_eta                                ;
  std::vector<float> *jet_phi                                ;
  std::vector<float> *jet_m                                  ;
  Int_t              njets                                   ;
  Int_t              nbjets                                  ;
  Float_t            mjj                                     ;
  Float_t            etajj                                   ;
  Float_t            phijj                                   ;
  Double_t           weight                                  ;
  Double_t           w_xs                                    ;
  Double_t           w_MCw                                   ;
  Double_t           w_lumi                                  ;
  Double_t           w_lepEff                                ;
  /* Norm Sys Weights */
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP0__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP0__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP1__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP1__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP2__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP2__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP3__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP3__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP4__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP4__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP5__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP5__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP6__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP6__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP7__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP7__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP8__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP8__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP9__1down ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP9__1up   ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP10__1down;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP10__1up  ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP11__1down;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP11__1up  ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP12__1down;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP12__1up  ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP13__1down;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP13__1up  ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP14__1down;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP14__1up  ;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP15__1down;
  Double_t           wgt_EL_EFF_ID_CorrUncertaintyNP15__1up  ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up   ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up  ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up  ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up  ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up  ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up  ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up  ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up  ;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down;
  Double_t           wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up  ;
  Double_t           wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down        ;
  Double_t           wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up          ;
  Double_t           wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down       ;
  Double_t           wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up         ;
  Double_t           wgt_FT_EFF_Eigen_B_0__1down                          ;
  Double_t           wgt_FT_EFF_Eigen_B_0__1up                            ;
  Double_t           wgt_FT_EFF_Eigen_B_1__1down                          ;
  Double_t           wgt_FT_EFF_Eigen_B_1__1up                            ;
  Double_t           wgt_FT_EFF_Eigen_B_2__1down                          ;
  Double_t           wgt_FT_EFF_Eigen_B_2__1up                            ;
  Double_t           wgt_FT_EFF_Eigen_C_0__1down                          ;
  Double_t           wgt_FT_EFF_Eigen_C_0__1up                            ;
  Double_t           wgt_FT_EFF_Eigen_C_1__1down                          ;
  Double_t           wgt_FT_EFF_Eigen_C_1__1up                            ;
  Double_t           wgt_FT_EFF_Eigen_C_2__1down                          ;
  Double_t           wgt_FT_EFF_Eigen_C_2__1up                            ;
  Double_t           wgt_FT_EFF_Eigen_C_3__1down                          ;
  Double_t           wgt_FT_EFF_Eigen_C_3__1up                            ;
  Double_t           wgt_FT_EFF_Eigen_Light_0__1down                      ;
  Double_t           wgt_FT_EFF_Eigen_Light_0__1up                        ;
  Double_t           wgt_FT_EFF_Eigen_Light_1__1down                      ;
  Double_t           wgt_FT_EFF_Eigen_Light_1__1up                        ;
  Double_t           wgt_FT_EFF_Eigen_Light_2__1down                      ;
  Double_t           wgt_FT_EFF_Eigen_Light_2__1up                        ;
  Double_t           wgt_FT_EFF_Eigen_Light_3__1down                      ;
  Double_t           wgt_FT_EFF_Eigen_Light_3__1up                        ;
  Double_t           wgt_FT_EFF_Eigen_Light_4__1down                      ;
  Double_t           wgt_FT_EFF_Eigen_Light_4__1up                        ;
  Double_t           wgt_FT_EFF_extrapolation__1down                      ;
  Double_t           wgt_FT_EFF_extrapolation__1up                        ;
  Double_t           wgt_FT_EFF_extrapolation_from_charm__1down           ;
  Double_t           wgt_FT_EFF_extrapolation_from_charm__1up             ;
  Double_t           wgt_JET_JvtEfficiency__1down                         ;
  Double_t           wgt_JET_JvtEfficiency__1up                           ;
  Double_t           wgt_JET_fJvtEfficiency__1down                        ;
  Double_t           wgt_JET_fJvtEfficiency__1up                          ;
  Double_t           wgt_HOEW_QCD_syst__1down                             ;
  Double_t           wgt_HOEW_QCD_syst__1up                               ;
  Double_t           wgt_HOEW_syst__1down                                 ;
  Double_t           wgt_HOEW_syst__1up                                   ;
  Double_t           wgt_HOQCD_scale_syst__1down                          ;
  Double_t           wgt_HOQCD_scale_syst__1up                            ;
  Double_t           wgt_MUON_EFF_ISO_STAT__1down                         ;
  Double_t           wgt_MUON_EFF_ISO_STAT__1up                           ;
  Double_t           wgt_MUON_EFF_ISO_SYS__1down                          ;
  Double_t           wgt_MUON_EFF_ISO_SYS__1up                            ;
  Double_t           wgt_MUON_EFF_RECO_STAT_LOWPT__1down                  ;
  Double_t           wgt_MUON_EFF_RECO_STAT_LOWPT__1up                    ;
  Double_t           wgt_MUON_EFF_RECO_STAT__1down                        ;
  Double_t           wgt_MUON_EFF_RECO_STAT__1up                          ;
  Double_t           wgt_MUON_EFF_RECO_SYS_LOWPT__1down                   ;
  Double_t           wgt_MUON_EFF_RECO_SYS_LOWPT__1up                     ;
  Double_t           wgt_MUON_EFF_RECO_SYS__1down                         ;
  Double_t           wgt_MUON_EFF_RECO_SYS__1up                           ;
  Double_t           wgt_MUON_EFF_TTVA_STAT__1down                        ;
  Double_t           wgt_MUON_EFF_TTVA_STAT__1up                          ;
  Double_t           wgt_MUON_EFF_TTVA_SYS__1down                         ;
  Double_t           wgt_MUON_EFF_TTVA_SYS__1up                           ;
  Double_t           wgt_PRW_DATASF__1down                                ;
  Double_t           wgt_PRW_DATASF__1up                                  ;
  /* Signal Theory Weights */
  Double_t           wgt_var_th_muR0p5_muF0p5                             ;
  Double_t           wgt_var_th_muR0p5_muF1p0                             ;
  Double_t           wgt_var_th_muR0p5_muF2p0                             ;
  Double_t           wgt_var_th_muR1p0_muF0p5                             ;
  Double_t           wgt_var_th_muR1p0_muF2p0                             ;
  Double_t           wgt_var_th_muR2p0_muF0p5                             ;
  Double_t           wgt_var_th_muR2p0_muF1p0                             ;
  Double_t           wgt_var_th_muR2p0_muF2p0                             ;
  Double_t           wgt_var_th_pdf_90400                                 ;
  Double_t           wgt_var_th_pdf_90401                                 ;
  Double_t           wgt_var_th_pdf_90402                                 ;
  Double_t           wgt_var_th_pdf_90403                                 ;
  Double_t           wgt_var_th_pdf_90404                                 ;
  Double_t           wgt_var_th_pdf_90405                                 ;
  Double_t           wgt_var_th_pdf_90406                                 ;
  Double_t           wgt_var_th_pdf_90407                                 ;
  Double_t           wgt_var_th_pdf_90408                                 ;
  Double_t           wgt_var_th_pdf_90409                                 ;
  Double_t           wgt_var_th_pdf_90410                                 ;
  Double_t           wgt_var_th_pdf_90411                                 ;
  Double_t           wgt_var_th_pdf_90412                                 ;
  Double_t           wgt_var_th_pdf_90413                                 ;
  Double_t           wgt_var_th_pdf_90414                                 ;
  Double_t           wgt_var_th_pdf_90415                                 ;
  Double_t           wgt_var_th_pdf_90416                                 ;
  Double_t           wgt_var_th_pdf_90417                                 ;
  Double_t           wgt_var_th_pdf_90418                                 ;
  Double_t           wgt_var_th_pdf_90419                                 ;
  Double_t           wgt_var_th_pdf_90420                                 ;
  Double_t           wgt_var_th_pdf_90421                                 ;
  Double_t           wgt_var_th_pdf_90422                                 ;
  Double_t           wgt_var_th_pdf_90423                                 ;
  Double_t           wgt_var_th_pdf_90424                                 ;
  Double_t           wgt_var_th_pdf_90425                                 ;
  Double_t           wgt_var_th_pdf_90426                                 ;
  Double_t           wgt_var_th_pdf_90427                                 ;
  Double_t           wgt_var_th_pdf_90428                                 ;
  Double_t           wgt_var_th_pdf_90429                                 ;
  Double_t           wgt_var_th_pdf_90430                                 ;
  Double_t           wgt_var_th_pdf_90431                                 ;
  Double_t           wgt_var_th_pdf_90432                                 ;
  Double_t           wgt_var_th_ggF_qcd_2017_pTH120                       ;
  Double_t           wgt_var_th_ggF_qcd_2017_pTH60                        ;
  Double_t           wgt_var_th_ggF_qcd_nJ0                               ;
  Double_t           wgt_var_th_qcd_wg1_mig01                             ;
  Double_t           wgt_var_th_qcd_wg1_mig12                             ;
  Double_t           wgt_var_th_qcd_wg1_mu                                ;
  Double_t           wgt_var_th_qcd_wg1_qm_t                              ;
  Double_t           wgt_var_th_qcd_wg1_res                               ;
  Double_t           wgt_var_th_qcd_wg1_vbf2j                             ;
  Double_t           wgt_var_th_qcd_wg1_vbf3j                             ;
  Double_t           wgt_var_th_nominal                                   ;
  /* Signal Shower Weights */
  Double_t           wgt_var_th_Var3cDown                                 ;
  Double_t           wgt_var_th_Var3cUp                                   ;
  Double_t           wgt_var_th_hardLo                                    ;
  Double_t           wgt_var_th_hardHi                                    ;
  Double_t           wgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5               ;
  Double_t           wgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0               ;
  Double_t           wgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0               ;
  Double_t           wgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0             ;
  Double_t           wgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0              ;
  Double_t           wgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0             ;
  Double_t           wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5               ;
  Double_t           wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625             ;
  Double_t           wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75              ;
  Double_t           wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875             ;
  Double_t           wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25              ;
  Double_t           wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5               ;
  Double_t           wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75              ;
  Double_t           wgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0               ;
  Double_t           wgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0              ;
  Double_t           wgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0               ;
  Double_t           wgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0              ;
  Double_t           wgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5               ;
  Double_t           wgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0               ;
  Double_t           wgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0               ;
  Double_t           wgt_var_th_Herwig                                    ;
  /* qqZZ Theory/Shower Weights */
  Double_t           wgt_var_th_Sherpa_CKKW__1down                        ;
  Double_t           wgt_var_th_Sherpa_CKKW__1up                          ;
  Double_t           wgt_var_th_Sherpa_CSSKIN__1up                        ;
  Double_t           wgt_var_th_Sherpa_QSF__1down                         ;
  Double_t           wgt_var_th_Sherpa_QSF__1up                           ;
  Double_t           wgt_var_th_MUR0p5_MUF0p5_PDF261000                   ;
  Double_t           wgt_var_th_MUR0p5_MUF1_PDF261000                     ;
  Double_t           wgt_var_th_MUR1_MUF0p5_PDF261000                     ;
  Double_t           wgt_var_th_MUR1_MUF2_PDF261000                       ;
  Double_t           wgt_var_th_MUR2_MUF1_PDF261000                       ;
  Double_t           wgt_var_th_MUR2_MUF2_PDF261000                       ; 
  Double_t           wgt_var_th_MUR1_MUF1_PDF261000                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261001                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261002                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261003                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261004                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261005                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261006                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261007                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261008                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261009                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261010                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261011                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261012                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261013                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261014                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261015                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261016                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261017                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261018                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261019                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261020                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261021                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261022                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261023                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261024                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261025                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261026                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261027                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261028                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261029                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261030                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261031                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261032                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261033                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261034                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261035                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261036                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261037                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261038                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261039                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261040                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261041                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261042                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261043                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261044                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261045                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261046                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261047                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261048                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261049                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261050                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261051                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261052                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261053                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261054                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261055                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261056                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261057                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261058                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261059                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261060                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261061                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261062                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261063                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261064                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261065                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261066                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261067                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261068                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261069                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261070                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261071                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261072                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261073                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261074                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261075                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261076                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261077                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261078                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261079                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261080                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261081                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261082                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261083                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261084                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261085                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261086                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261087                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261088                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261089                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261090                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261091                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261092                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261093                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261094                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261095                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261096                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261097                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261098                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261099                       ;
  Double_t           wgt_var_th_MUR1_MUF1_PDF261100                       ;

  
  TBranch *b_event_type                                           ;  //!
  TBranch *b_event                                                ;  //!
  TBranch *b_run                                                  ;  //!
  TBranch *b_m4l_fsr                                              ;  //!
  TBranch *b_pt4l_fsr                                             ;  //!
  TBranch *b_y4l_fsr                                              ;  //!
  TBranch *b_mZ1_fsr                                              ;  //!
  TBranch *b_mZ2_fsr                                              ;  //!
  TBranch *b_cthstr_fsr                                           ;  //!
  TBranch *b_ct1_fsr                                              ;  //!
  TBranch *b_ct2_fsr                                              ;  //!
  TBranch *b_phi_fsr                                              ;  //!
  TBranch *b_phi1_fsr                                             ;  //!
  TBranch *b_jet_pt                                               ;  //!
  TBranch *b_jet_phi                                              ;  //!
  TBranch *b_jet_eta                                              ;  //!
  TBranch *b_jet_m                                                ;  //!
  TBranch *b_weight                                               ;  //!
  TBranch *b_w_xs                                                 ;  //!
  TBranch *b_w_MCw                                                ;  //!
  TBranch *b_w_lumi                                               ;  //!
  TBranch *b_w_lepEff                                             ;  //!
  TBranch *b_etajj                                                ;  //!
  TBranch *b_mjj                                                  ;  //!
  TBranch *b_phijj                                                ;  //!
  TBranch *b_njets                                                ;  //!
  TBranch *b_nbjets                                               ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP0__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP0__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP1__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP1__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP2__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP2__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP3__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP3__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP4__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP4__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP5__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP5__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP6__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP6__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP7__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP7__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP8__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP8__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP9__1down              ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP9__1up                ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP10__1down             ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP10__1up               ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP11__1down             ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP11__1up               ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP12__1down             ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP12__1up               ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP13__1down             ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP13__1up               ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP14__1down             ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP14__1up               ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP15__1down             ;  //!
  TBranch *b_wgt_EL_EFF_ID_CorrUncertaintyNP15__1up               ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up   ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up  ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up  ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up  ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up  ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up  ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up  ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up  ;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down;  //!
  TBranch *b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up  ;  //!
  TBranch *b_wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down        ;  //!
  TBranch *b_wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up          ;  //!
  TBranch *b_wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down       ;  //!
  TBranch *b_wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up         ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_B_0__1down                          ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_B_0__1up                            ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_B_1__1down                          ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_B_1__1up                            ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_B_2__1down                          ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_B_2__1up                            ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_C_0__1down                          ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_C_0__1up                            ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_C_1__1down                          ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_C_1__1up                            ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_C_2__1down                          ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_C_2__1up                            ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_C_3__1down                          ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_C_3__1up                            ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_0__1down                      ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_0__1up                        ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_1__1down                      ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_1__1up                        ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_2__1down                      ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_2__1up                        ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_3__1down                      ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_3__1up                        ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_4__1down                      ;  //!
  TBranch *b_wgt_FT_EFF_Eigen_Light_4__1up                        ;  //!
  TBranch *b_wgt_FT_EFF_extrapolation__1down                      ;  //!
  TBranch *b_wgt_FT_EFF_extrapolation__1up                        ;  //!
  TBranch *b_wgt_FT_EFF_extrapolation_from_charm__1down           ;  //!
  TBranch *b_wgt_FT_EFF_extrapolation_from_charm__1up             ;  //!
  TBranch *b_wgt_JET_JvtEfficiency__1down                         ;  //!
  TBranch *b_wgt_JET_JvtEfficiency__1up                           ;  //!
  TBranch *b_wgt_JET_fJvtEfficiency__1down                        ;  //!
  TBranch *b_wgt_JET_fJvtEfficiency__1up                          ;  //!
  TBranch *b_wgt_HOEW_QCD_syst__1down                             ;  //!
  TBranch *b_wgt_HOEW_QCD_syst__1up                               ;  //!
  TBranch *b_wgt_HOEW_syst__1down                                 ;  //!
  TBranch *b_wgt_HOEW_syst__1up                                   ;  //!
  TBranch *b_wgt_HOQCD_scale_syst__1down                          ;  //!
  TBranch *b_wgt_HOQCD_scale_syst__1up                            ;  //!
  TBranch *b_wgt_MUON_EFF_ISO_STAT__1down                         ;  //!
  TBranch *b_wgt_MUON_EFF_ISO_STAT__1up                           ;  //!
  TBranch *b_wgt_MUON_EFF_ISO_SYS__1down                          ;  //!
  TBranch *b_wgt_MUON_EFF_ISO_SYS__1up                            ;  //!
  TBranch *b_wgt_MUON_EFF_RECO_STAT_LOWPT__1down                  ;  //!
  TBranch *b_wgt_MUON_EFF_RECO_STAT_LOWPT__1up                    ;  //!
  TBranch *b_wgt_MUON_EFF_RECO_STAT__1down                        ;  //!
  TBranch *b_wgt_MUON_EFF_RECO_STAT__1up                          ;  //!
  TBranch *b_wgt_MUON_EFF_RECO_SYS_LOWPT__1down                   ;  //!
  TBranch *b_wgt_MUON_EFF_RECO_SYS_LOWPT__1up                     ;  //!
  TBranch *b_wgt_MUON_EFF_RECO_SYS__1down                         ;  //!
  TBranch *b_wgt_MUON_EFF_RECO_SYS__1up                           ;  //!
  TBranch *b_wgt_MUON_EFF_TTVA_STAT__1down                        ;  //!
  TBranch *b_wgt_MUON_EFF_TTVA_STAT__1up                          ;  //!
  TBranch *b_wgt_MUON_EFF_TTVA_SYS__1down                         ;  //!
  TBranch *b_wgt_MUON_EFF_TTVA_SYS__1up                           ;  //!
  TBranch *b_wgt_PRW_DATASF__1down                                ;  //!
  TBranch *b_wgt_PRW_DATASF__1up                                  ;  //!
  TBranch *b_wgt_var_th_muR0p5_muF0p5                             ;  //!
  TBranch *b_wgt_var_th_muR0p5_muF1p0                             ;  //!
  TBranch *b_wgt_var_th_muR0p5_muF2p0                             ;  //!
  TBranch *b_wgt_var_th_muR1p0_muF0p5                             ;  //!
  TBranch *b_wgt_var_th_muR1p0_muF2p0                             ;  //!
  TBranch *b_wgt_var_th_muR2p0_muF0p5                             ;  //!
  TBranch *b_wgt_var_th_muR2p0_muF1p0                             ;  //!
  TBranch *b_wgt_var_th_muR2p0_muF2p0                             ;  //!
  TBranch *b_wgt_var_th_pdf_90400                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90401                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90402                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90403                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90404                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90405                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90406                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90407                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90408                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90409                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90410                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90411                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90412                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90413                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90414                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90415                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90416                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90417                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90418                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90419                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90420                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90421                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90422                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90423                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90424                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90425                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90426                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90427                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90428                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90429                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90430                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90431                                 ;  //!
  TBranch *b_wgt_var_th_pdf_90432                                 ;  //!
  TBranch *b_wgt_var_th_ggF_qcd_2017_pTH120                       ;  //!
  TBranch *b_wgt_var_th_ggF_qcd_2017_pTH60                        ;  //!
  TBranch *b_wgt_var_th_ggF_qcd_nJ0                               ;  //!
  TBranch *b_wgt_var_th_qcd_wg1_mig01                             ;  //!
  TBranch *b_wgt_var_th_qcd_wg1_mig12                             ;  //!
  TBranch *b_wgt_var_th_qcd_wg1_mu                                ;  //!
  TBranch *b_wgt_var_th_qcd_wg1_qm_t                              ;  //!
  TBranch *b_wgt_var_th_qcd_wg1_res                               ;  //!
  TBranch *b_wgt_var_th_qcd_wg1_vbf2j                             ;  //!
  TBranch *b_wgt_var_th_qcd_wg1_vbf3j                             ;  //!
  TBranch *b_wgt_var_th_nominal                                   ;  //!
  TBranch *b_wgt_var_th_Var3cDown                                 ;  //!
  TBranch *b_wgt_var_th_Var3cUp                                   ;  //!
  TBranch *b_wgt_var_th_hardLo                                    ;  //!
  TBranch *b_wgt_var_th_hardHi                                    ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0             ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0              ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0             ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625             ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75              ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875             ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25              ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75              ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0              ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0              ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0               ;  //!
  TBranch *b_wgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0               ;  //!
  TBranch *b_wgt_var_th_Herwig                                    ;  //!
  TBranch *b_wgt_var_th_Sherpa_CKKW__1down                        ;  //!
  TBranch *b_wgt_var_th_Sherpa_CKKW__1up                          ;  //!
  TBranch *b_wgt_var_th_Sherpa_CSSKIN__1up                        ;  //!
  TBranch *b_wgt_var_th_Sherpa_QSF__1down                         ;  //!
  TBranch *b_wgt_var_th_Sherpa_QSF__1up                           ;  //!
  TBranch *b_wgt_var_th_MUR0p5_MUF0p5_PDF261000                   ;  //!
  TBranch *b_wgt_var_th_MUR0p5_MUF1_PDF261000                     ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF0p5_PDF261000                     ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF2_PDF261000                       ;  //!
  TBranch *b_wgt_var_th_MUR2_MUF1_PDF261000                       ;  //!
  TBranch *b_wgt_var_th_MUR2_MUF2_PDF261000                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261000                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261001                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261002                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261003                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261004                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261005                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261006                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261007                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261008                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261009                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261010                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261011                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261012                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261013                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261014                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261015                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261016                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261017                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261018                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261019                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261020                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261021                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261022                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261023                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261024                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261025                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261026                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261027                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261028                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261029                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261030                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261031                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261032                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261033                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261034                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261035                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261036                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261037                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261038                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261039                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261040                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261041                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261042                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261043                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261044                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261045                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261046                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261047                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261048                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261049                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261050                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261051                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261052                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261053                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261054                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261055                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261056                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261057                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261058                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261059                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261060                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261061                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261062                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261063                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261064                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261065                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261066                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261067                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261068                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261069                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261070                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261071                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261072                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261073                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261074                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261075                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261076                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261077                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261078                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261079                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261080                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261081                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261082                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261083                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261084                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261085                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261086                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261087                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261088                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261089                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261090                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261091                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261092                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261093                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261094                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261095                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261096                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261097                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261098                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261099                       ;  //!
  TBranch *b_wgt_var_th_MUR1_MUF1_PDF261100                       ;  //!

  /* Couplings related variable */
  Int_t   prod_type;
  Int_t   HTXS_Stage1_Category_pTjet30;
  Float_t BDT_discriminant;
  Float_t BDT_1Jet_pt4l_60;
  Float_t BDT_1Jet_pt4l_60_120;
  Float_t BDT_OneJet_jptetadR_discriminant;
  Float_t BDT_VH_noptHjj_discriminant;
  Float_t BDT_TwoJet_discriminant;

  TBranch *b_prod_type;  //!
  TBranch *b_HTXS_Stage1_Category_pTjet30; //!
  TBranch *b_BDT_discriminant;  //!
  TBranch *b_BDT_1Jet_pt4l_60;  //!
  TBranch *b_BDT_1Jet_pt4l_60_120;  //!
  TBranch *b_BDT_OneJet_jptetadR_discriminant;  //!
  TBranch *b_BDT_VH_noptHjj_discriminant;  //!
  TBranch *b_BDT_TwoJet_discriminant;  //!

  /* Fiducial Minitrees variables */
  ULong64_t          thevent;
  Int_t              thrun;
  Double_t           thweight;
  Double_t           w_thlumi;
  Double_t           w_thMCw;
  Double_t           w_thxs;
  Int_t              thevtType_fidBorn;
  Int_t              thevtType_fidDres;
  Int_t              thevtType_truth;
  Int_t              njet_fidBorn;
  Int_t              njet_fidDres;
  Int_t              njet_truth;
  Int_t              nbjet_fidBorn;
  Int_t              nbjet_fidDres;
  Int_t              nbjet_truth;
  Float_t            pt4l_fidBorn;
  Float_t            pt4l_fidDres;
  Float_t            pt4l_truth;
  Float_t            m4l_fidBorn;
  Float_t            m4l_fidDres;
  Float_t            m4l_truth;
  Float_t            m12_fidBorn;
  Float_t            m12_fidDres;
  Float_t            m12_truth;
  Float_t            m34_fidBorn;
  Float_t            m34_fidDres;
  Float_t            m34_truth;
  Float_t            y4l_fidBorn;
  Float_t            y4l_fidDres;
  Float_t            y4l_truth;
  Float_t            cts_fidBorn;
  Float_t            cts_fidDres;
  Float_t            cts_truth;
  Float_t            ct1_fidBorn;
  Float_t            ct1_fidDres;
  Float_t            ct1_truth;
  Float_t            ct2_fidBorn;
  Float_t            ct2_fidDres;
  Float_t            ct2_truth;
  Float_t            phi_fidBorn;
  Float_t            phi_fidDres;
  Float_t            phi_truth;
  Float_t            phi1_fidBorn;
  Float_t            phi1_fidDres;
  Float_t            phi1_truth;
  Float_t            mjj_fidBorn;
  Float_t            mjj_fidDres;
  Float_t            mjj_truth;
  Float_t            etajj_fidBorn;
  Float_t            etajj_fidDres;
  Float_t            etajj_truth;
  Float_t            phijj_fidBorn;
  Float_t            phijj_fidDres;
  Float_t            phijj_truth;
  std::vector<float> *jet_pt_fidBorn;
  std::vector<float> *jet_pt_fidDres;
  std::vector<float> *jet_pt_truth;
  std::vector<float> *jet_m_fidBorn;
  std::vector<float> *jet_m_fidDres;
  std::vector<float> *jet_m_truth;
  std::vector<float> *jet_eta_fidBorn;
  std::vector<float> *jet_eta_fidDres;
  std::vector<float> *jet_eta_truth;
  std::vector<float> *jet_phi_fidBorn;
  std::vector<float> *jet_phi_fidDres;
  std::vector<float> *jet_phi_truth;
  /* Theory Weights */
  Double_t           thwgt_var_th_muR0p5_muF0p5                ;
  Double_t           thwgt_var_th_muR0p5_muF1p0                ;
  Double_t           thwgt_var_th_muR0p5_muF2p0                ;
  Double_t           thwgt_var_th_muR1p0_muF0p5                ;
  Double_t           thwgt_var_th_muR1p0_muF2p0                ;
  Double_t           thwgt_var_th_muR2p0_muF0p5                ;
  Double_t           thwgt_var_th_muR2p0_muF1p0                ;
  Double_t           thwgt_var_th_muR2p0_muF2p0                ;
  Double_t           thwgt_var_th_pdf_90400                    ;
  Double_t           thwgt_var_th_pdf_90401                    ;
  Double_t           thwgt_var_th_pdf_90402                    ;
  Double_t           thwgt_var_th_pdf_90403                    ;
  Double_t           thwgt_var_th_pdf_90404                    ;
  Double_t           thwgt_var_th_pdf_90405                    ;
  Double_t           thwgt_var_th_pdf_90406                    ;
  Double_t           thwgt_var_th_pdf_90407                    ;
  Double_t           thwgt_var_th_pdf_90408                    ;
  Double_t           thwgt_var_th_pdf_90409                    ;
  Double_t           thwgt_var_th_pdf_90410                    ;
  Double_t           thwgt_var_th_pdf_90411                    ;
  Double_t           thwgt_var_th_pdf_90412                    ;
  Double_t           thwgt_var_th_pdf_90413                    ;
  Double_t           thwgt_var_th_pdf_90414                    ;
  Double_t           thwgt_var_th_pdf_90415                    ;
  Double_t           thwgt_var_th_pdf_90416                    ;
  Double_t           thwgt_var_th_pdf_90417                    ;
  Double_t           thwgt_var_th_pdf_90418                    ;
  Double_t           thwgt_var_th_pdf_90419                    ;
  Double_t           thwgt_var_th_pdf_90420                    ;
  Double_t           thwgt_var_th_pdf_90421                    ;
  Double_t           thwgt_var_th_pdf_90422                    ;
  Double_t           thwgt_var_th_pdf_90423                    ;
  Double_t           thwgt_var_th_pdf_90424                    ;
  Double_t           thwgt_var_th_pdf_90425                    ;
  Double_t           thwgt_var_th_pdf_90426                    ;
  Double_t           thwgt_var_th_pdf_90427                    ;
  Double_t           thwgt_var_th_pdf_90428                    ;
  Double_t           thwgt_var_th_pdf_90429                    ;
  Double_t           thwgt_var_th_pdf_90430                    ;
  Double_t           thwgt_var_th_pdf_90431                    ;
  Double_t           thwgt_var_th_pdf_90432                    ;
  Double_t           thwgt_var_th_ggF_qcd_2017_pTH120          ;
  Double_t           thwgt_var_th_ggF_qcd_2017_pTH60           ;
  Double_t           thwgt_var_th_ggF_qcd_nJ0                  ;
  Double_t           thwgt_var_th_qcd_wg1_mig01                ;
  Double_t           thwgt_var_th_qcd_wg1_mig12                ;
  Double_t           thwgt_var_th_qcd_wg1_mu                   ;
  Double_t           thwgt_var_th_qcd_wg1_qm_t                 ;
  Double_t           thwgt_var_th_qcd_wg1_res                  ;
  Double_t           thwgt_var_th_qcd_wg1_vbf2j                ;
  Double_t           thwgt_var_th_qcd_wg1_vbf3j                ;
  Double_t           thwgt_var_th_nominal                      ;
  Double_t           thwgt_var_th_Var3cDown                    ;
  Double_t           thwgt_var_th_Var3cUp                      ;
  Double_t           thwgt_var_th_hardHi                       ;
  Double_t           thwgt_var_th_hardLo                       ;
  Double_t           thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5  ;
  Double_t           thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0  ;
  Double_t           thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0  ;
  Double_t           thwgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0;
  Double_t           thwgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0 ;
  Double_t           thwgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0;
  Double_t           thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5  ;
  Double_t           thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625;
  Double_t           thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75 ;
  Double_t           thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875;
  Double_t           thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25 ;
  Double_t           thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5  ;
  Double_t           thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75 ;
  Double_t           thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0  ; 
  Double_t           thwgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0 ;
  Double_t           thwgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0  ;
  Double_t           thwgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0 ;
  Double_t           thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5  ;
  Double_t           thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0  ;
  Double_t           thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0  ;
  Double_t           thwgt_var_th_Herwig                       ;
  
  TBranch *b_thevent                                   ;  //!
  TBranch *b_thrun                                     ;  //!
  TBranch *b_thweight                                  ;  //!
  TBranch *b_w_thlumi                                  ;  //!
  TBranch *b_w_thMCw                                   ;  //!
  TBranch *b_w_thxs                                    ;  //!
  TBranch *b_thevtType_fidBorn                         ;  //!
  TBranch *b_thevtType_fidDres                         ;  //!
  TBranch *b_thevtType_truth                           ;  //!
  TBranch *b_njet_fidBorn                              ;  //!
  TBranch *b_njet_fidDres                              ;  //!
  TBranch *b_njet_truth                                ;  //!
  TBranch *b_nbjet_fidBorn                             ;  //!
  TBranch *b_nbjet_fidDres                             ;  //!
  TBranch *b_nbjet_truth                               ;  //!
  TBranch *b_pt4l_fidBorn                              ;  //!
  TBranch *b_pt4l_fidDres                              ;  //!
  TBranch *b_pt4l_truth                                ;  //!
  TBranch *b_m4l_fidBorn                               ;  //!
  TBranch *b_m4l_fidDres                               ;  //!
  TBranch *b_m4l_truth                                 ;  //!
  TBranch *b_m12_fidBorn                               ;  //!
  TBranch *b_m12_fidDres                               ;  //!
  TBranch *b_m12_truth                                 ;  //!
  TBranch *b_m34_fidBorn                               ;  //!
  TBranch *b_m34_fidDres                               ;  //!
  TBranch *b_m34_truth                                 ;  //!
  TBranch *b_y4l_fidBorn                               ;  //!
  TBranch *b_y4l_fidDres                               ;  //!
  TBranch *b_y4l_truth                                 ;  //!
  TBranch *b_cts_fidBorn                               ;  //!
  TBranch *b_cts_fidDres                               ;  //!
  TBranch *b_cts_truth                                 ;  //!
  TBranch *b_ct1_fidBorn                               ;  //!
  TBranch *b_ct1_fidDres                               ;  //!
  TBranch *b_ct1_truth                                 ;  //!
  TBranch *b_ct2_fidBorn                               ;  //!
  TBranch *b_ct2_fidDres                               ;  //!
  TBranch *b_ct2_truth                                 ;  //!
  TBranch *b_phi_fidBorn                               ;  //!
  TBranch *b_phi_fidDres                               ;  //!
  TBranch *b_phi_truth                                 ;  //!
  TBranch *b_phi1_fidBorn                              ;  //!
  TBranch *b_phi1_fidDres                              ;  //!
  TBranch *b_phi1_truth                                ;  //!
  TBranch *b_mjj_fidBorn                               ;  //!
  TBranch *b_mjj_fidDres                               ;  //!
  TBranch *b_mjj_truth                                 ;  //!
  TBranch *b_etajj_fidBorn                             ;  //!
  TBranch *b_etajj_fidDres                             ;  //!
  TBranch *b_etajj_truth                               ;  //!
  TBranch *b_phijj_fidBorn                             ;  //!
  TBranch *b_phijj_fidDres                             ;  //!
  TBranch *b_phijj_truth                               ;  //!
  TBranch *b_jet_pt_fidBorn                            ;  //!
  TBranch *b_jet_pt_fidDres                            ;  //!
  TBranch *b_jet_pt_truth                              ;  //!
  TBranch *b_jet_m_fidBorn                             ;  //!
  TBranch *b_jet_m_fidDres                             ;  //!
  TBranch *b_jet_m_truth                               ;  //!
  TBranch *b_jet_eta_fidBorn                           ;  //!
  TBranch *b_jet_eta_fidDres                           ;  //!
  TBranch *b_jet_eta_truth                             ;  //!
  TBranch *b_jet_phi_fidBorn                           ;  //!
  TBranch *b_jet_phi_fidDres                           ;  //!
  TBranch *b_jet_phi_truth                             ;  //!
  TBranch *b_thwgt_var_th_muR0p5_muF0p5                ;  //!
  TBranch *b_thwgt_var_th_muR0p5_muF1p0                ;  //!
  TBranch *b_thwgt_var_th_muR0p5_muF2p0                ;  //!
  TBranch *b_thwgt_var_th_muR1p0_muF0p5                ;  //!
  TBranch *b_thwgt_var_th_muR1p0_muF2p0                ;  //!
  TBranch *b_thwgt_var_th_muR2p0_muF0p5                ;  //!
  TBranch *b_thwgt_var_th_muR2p0_muF1p0                ;  //!
  TBranch *b_thwgt_var_th_muR2p0_muF2p0                ;  //!
  TBranch *b_thwgt_var_th_pdf_90400                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90401                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90402                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90403                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90404                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90405                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90406                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90407                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90408                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90409                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90410                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90411                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90412                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90413                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90414                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90415                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90416                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90417                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90418                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90419                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90420                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90421                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90422                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90423                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90424                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90425                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90426                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90427                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90428                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90429                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90430                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90431                    ;  //!
  TBranch *b_thwgt_var_th_pdf_90432                    ;  //!
  TBranch *b_thwgt_var_th_ggF_qcd_2017_pTH120          ;  //!
  TBranch *b_thwgt_var_th_ggF_qcd_2017_pTH60           ;  //!
  TBranch *b_thwgt_var_th_ggF_qcd_nJ0                  ;  //!
  TBranch *b_thwgt_var_th_qcd_wg1_mig01                ;  //!
  TBranch *b_thwgt_var_th_qcd_wg1_mig12                ;  //!
  TBranch *b_thwgt_var_th_qcd_wg1_mu                   ;  //!
  TBranch *b_thwgt_var_th_qcd_wg1_qm_t                 ;  //!
  TBranch *b_thwgt_var_th_qcd_wg1_res                  ;  //!
  TBranch *b_thwgt_var_th_qcd_wg1_vbf2j                ;  //!
  TBranch *b_thwgt_var_th_qcd_wg1_vbf3j                ;  //!
  TBranch *b_thwgt_var_th_nominal                      ;  //!
  TBranch *b_thwgt_var_th_Var3cDown                    ;  //!
  TBranch *b_thwgt_var_th_Var3cUp                      ;  //!
  TBranch *b_thwgt_var_th_hardHi                       ;  //!
  TBranch *b_thwgt_var_th_hardLo                       ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0 ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75 ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25 ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75 ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0 ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0 ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0  ;  //!
  TBranch *b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0  ;  //!
  TBranch *b_thwgt_var_th_Herwig                       ;  //!
  
};
#endif
