#ifndef MakeInput_H
#define MakeInput_H

/* C++ includes */
#include "iostream"
#include "set"
#include "map"
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
#include <TMath.h>
#include <TChain.h>

/* Other includes */
#include "Enum.h"

class MakeInput {

 public:
  
  /****************/
  /* Constructors */
  /****************/
  MakeInput();
  
  MakeInput(std::string Process, std::string MCtype,
	    int SysType, int Nbins, double Min, double Max, bool doMatrix,
	    bool ShiftUp, bool ShiftDown, bool PowhegZZ, bool debug,
	    bool verbose);
  
  /****************/
  /*   Methods    */
  /****************/

  /* Set Initial Values */
  void SetInitValues(std::string Process, std::string MCtype,
		     int SysType, int Nbins, double Min,
		     double Max, bool doMatrix, bool debug);
  
  /* Sanity check for response matrix */
  void SanityCheck();

  /* Create Systematics map */
  void MakeSysMap();

  /* Define Output File */
  void DefineOutFile();

  /* Set Files Chain */
  void SetChain();
  void SetTruthChain();

  /* Set Chain Branches */
  void SetChainBranches();
  void SetTruthChainBranches();

  /* Find Truth Match */
  ULong64_t FindTruthMatch(ULong64_t evt, Int_t run);
  
  /* Main Processes */
  void Process();
  void ProcessTruth();
  
  /* Make Reducible Background */
  void MakeRedBkg();

  /* Make Other Processes */
  void MakeOtherProcesses();

  /* Merge Reducible Background */
  void MergeRedBkg();

  /* Derive Xsec Scale Factor */
  void DeriveXsecScale();

  /* Set event counters */
  void SetCounters();

  /* Get Event Weight */
  double GetWeight();
  
  /* Define Histograms */
  void DefineHistograms();

  /* Make List of Plots To be Written on File */
  std::vector<TObject*> ListOfPlotsToWrite();

  /* Make List of Plots To be Normalized to Integral */
  std::vector<TH1F*> ListOfPlotsToNormalize();

  /* Make List of 1D Plots To be Normalized to Bin Width */
  std::vector<TH1F*> ListOf1DPlotsToNorm();

  /* Make List of 2D Plots To be Normalized to Bin Width */
  std::vector<TH2F*> ListOf2DPlotsToNorm();

  /* Normalise Histograms to Bin Size */
  void DivideForBinSize(std::vector<TH1F*> &plots);
  void DivideForBinSize(std::vector<TH2F*> &plots);

  /* Fill Z+jets Histograms */
  void FillZjetsPlots(std::vector<TH1F*> &vec, std::string var="");

  /* Merge and Normalize Plots (used for Z+jets) */
  void MergeAndNormalizePlots(std::vector<TH1F*> &vec, double yield);
  
  /* Set Axis Title Offset */
  void SetAxisTitleOffset(TH1F* h);
  void SetAxisTitleOffset(TH2F* h);

  /* Normalize Plots to a Given Integral */
  void NormalizePlots(Float_t qqZZint, Float_t ggZZint);
  
 protected:
  std::vector<double> PtRangeVec, Pt0jRangeVec, Pt1jRangeVec, Pt2jRangeVec;
  std::vector<double> CtsRangeVec, M12RangeVec, M34RangeVec;
  std::vector<double> NjetRangeVec, NjetRangeVecv2, NjetRangeVecv3;
  std::vector<double> RapRangeVec, LjPtRangeVec, NbjetRangeVec;
  std::vector<double> EtajjRangeVec, MjjRangeVec, PhijjRangeVec;

  std::vector<TH1F*> m_pTBins, m_pT0jBins, m_pT1jBins, m_pT2jBins;
  std::vector<TH1F*> m_VecMJJ, m_VecMJJrm, m_VecETAJJ, m_VecPHIJJ;
  std::vector<TH1F*> m_VecM, m_VecM0j, m_VecM1j, m_VecM2j, m_VecJetPt;
  std::vector<TH1F*> m_VecMLpt, m_VecMHpt;
  std::vector<TH1F*> m_VecPT, m_VecPT0j, m_VecPT1j, m_VecPT2j;
  std::vector<TH1F*> m_VecM12, m_VecM34, m_VecM34B, m_VecNbjet;
  std::vector<TH1F*> m_VecNjet, m_VecNjetv2, m_VecNjetv3;
  std::vector<TH1F*> m_VecY, m_VecY0j, m_VecY1j, m_VecYLpt, m_VecYHpt;
  std::vector<TH1F*> m_VecCts,m_VecCts0j, m_VecCts1j, m_VecCtsLpt, m_VecCtsHpt;
  std::vector<TH1F*> m_ctsBins, m_yBins, m_m12Bins, m_m34Bins;
  std::vector<TH1F*> m_njetBins, m_njetBinsv2, m_njetBinsv3;
  std::vector<TH1F*> m_ljptBins, m_nbjetBins, m_pTpTBins;
  std::vector<TH1F*> m_mjjBins, m_etajjBins, m_phijjBins; 
  
  std::vector<TH1F*> m_VecM12M34rm;
  std::vector<TH2F*> m_VecM12M34, m_VecPTmtx, m_VecPT0jmtx;
  std::vector<TH2F*> m_VecPT1jmtx, m_VecPT2jmtx, m_VecM12mtx, m_VecM34mtx;
  std::vector<TH2F*> m_VecYmtx, m_VecCTSmtx, m_VecNBJETmtx;
  std::vector<TH2F*> m_VecNJETmtx, m_VecNJETmtxv2, m_VecNJETmtxv3;
  std::vector<TH2F*> m_VecLJETmtx, m_VecMJJmtx, m_VecETAJJmtx, m_VecPHIJJmtx;
  std::vector<TH2F*> m_Vechm12vsm34rmmtx;
  std::vector<TH2F*> m_Vechbin1Z1Z2mtx, m_Vechbin2Z1Z2mtx, m_Vechbin3Z1Z2mtx;
  std::vector<TH2F*> m_Vechbin4Z1Z2mtx, m_Vechbin5Z1Z2mtx;
  std::vector<TH1F*> m_VecPTPT;

  std::vector<double> m_pTInt, m_m12Int, m_m34Int, m_yInt, m_njetInt;
  std::vector<double> m_nbjetInt, m_ctsInt, m_ljptInt, m_pT0jInt, m_pT1jInt;
  
  std::string m_Process;
  std::string m_MCtype;
  std::string m_Syst;
  int m_Nbins;
  int m_THbins;
  double m_Min;
  double m_Max;
  bool m_debug;
  bool m_verbose;
  bool m_doMtx;
  bool m_doScale;
  bool m_doShiftUp;
  bool m_doShiftDown;
  bool m_powhegZZ;
  TFile *m_In;
  TFile *m_Out;
  TChain *m_chain;
  TChain *m_thchain;
  std::string m_treename;
  
  TH1F *hm, *hm0j, *hm1j, *hm2j, *hljpt, *hmjj, *hmjjrm, *hetajj, *hphijj;
  TH1F *hmLpt, *hmHpt, *hctsLpt, *hctsHpt, *hyLpt, *hyHpt;
  TH1F *hpt, *hpt0j, *hpt1j, *hpt2j;
  TH1F *hm_ptbin, *hm0j_ptbin, *hm1j_ptbin, *hm2j_ptbin;
  TH1F *hm_ctsbin, *hm_ybin, *hm_m12bin, *hm_m34bin, *hm_njetbin;
  TH1F *hm_ljptbin, *hm_nbjetbin, *hm12, *hm34, *hm_ptptbin;
  TH1F *hm_mjjbin, *hm_etajjbin, *hm_phijjbin;
  TH1F *hnjet, *hy, *hy0j, *hy1j, *hcts, *hcts0j, *hcts1j, *hnbjet;
  TH1F *hm12vsm34rm;
  TH2F *hm12vsm34, *hm12mtx, *hm34mtx, *hymtx, *hctsmtx, *hnjetmtx, *hnbjetmtx, *hljetmtx;
  TH2F *hmjjmtx, *hetajjmtx, *hphijjmtx, *hptmtx, *hpt0jmtx, *hpt1jmtx, *hpt2jmtx;
  TH2F *hm12vsm34rmmtx;
  TH2F *hbin1Z1Z2mtx, *hbin2Z1Z2mtx, *hbin3Z1Z2mtx, *hbin4Z1Z2mtx;
  TH2F *hbin5Z1Z2mtx, *hbin6Z1Z2mtx;

  TH1F *hptpt;

  TH1F *m_llmumu, *m_llee;
  
  int m_SystNum;
  std::map<int,std::string> m_SysMap;

  /* MiniTree Variables */
  Int_t     event_type;
  ULong64_t event;
  Int_t     run;
  Int_t     lbn;
  Int_t     pass_vtx4lCut;
  Float_t   m4l_constrained;
  Float_t   m4l_Fsr;
  Float_t   pt4l_unconstrained;
  Float_t   mZ1_unconstrained;
  Float_t   mZ2_unconstrained;
  Float_t   y4l_unconstrained;
  Float_t   cthstr_unconstrained;
  Float_t   pt4l_fsr;
  Float_t   mZ1_fsr;
  Float_t   mZ2_fsr;
  Float_t   y4l_fsr;
  Float_t   cthstr_fsr;
  Float_t   jet_pt[4];
  Float_t   jet_eta[4];
  Float_t   jet_phi[4];
  Double_t  lumi;
  Int_t     n_jets;
  Int_t     n_jets_btag70;
  Int_t     cand_index;
  Float_t   dijet_invmass;
  Float_t   dijet_deltaeta;
  Float_t   dijet_deltaphi;
  Double_t  weight;
  Double_t  w_xs;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP0__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP0__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP1__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP1__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP10__1down;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP10__1up  ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP11__1down;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP11__1up  ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP12__1down;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP12__1up  ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP13__1down;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP13__1up  ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP14__1down;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP14__1up  ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP2__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP2__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP3__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP3__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP4__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP4__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP5__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP5__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP6__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP6__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP7__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP7__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP8__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP8__1up   ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP9__1down ;
  Double_t   weight_EL_EFF_ID_CorrUncertaintyNP9__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up  ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up  ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up  ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up  ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up  ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up  ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up   ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down ;
  Double_t   weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up   ;
  Double_t   weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down  ;
  Double_t   weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up    ;
  Double_t   weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down ;
  Double_t   weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up   ;
  Double_t   weight_HOEW_QCD_syst__1down       ;
  Double_t   weight_HOEW_QCD_syst__1up         ;
  Double_t   weight_HOEW_syst__1down           ;
  Double_t   weight_HOEW_syst__1up             ;
  Double_t   weight_HOQCD_scale_syst__1down    ;
  Double_t   weight_HOQCD_scale_syst__1up      ;
  Double_t   weight_JvtEfficiencyDown          ;
  Double_t   weight_JvtEfficiencyUp            ;
  Double_t   weight_MUON_EFF_STAT__1down       ;
  Double_t   weight_MUON_EFF_STAT__1up         ;
  Double_t   weight_MUON_EFF_STAT_LOWPT__1down ;
  Double_t   weight_MUON_EFF_STAT_LOWPT__1up   ;
  Double_t   weight_MUON_EFF_SYS__1down        ;
  Double_t   weight_MUON_EFF_SYS__1up          ;
  Double_t   weight_MUON_EFF_SYS_LOWPT__1down  ;
  Double_t   weight_MUON_EFF_SYS_LOWPT__1up    ;
  Double_t   weight_MUON_ISO_STAT__1down       ;
  Double_t   weight_MUON_ISO_STAT__1up         ;
  Double_t   weight_MUON_ISO_SYS__1down        ;
  Double_t   weight_MUON_ISO_SYS__1up          ;
  Double_t   weight_MUON_TTVA_STAT__1down      ;
  Double_t   weight_MUON_TTVA_STAT__1up        ;
  Double_t   weight_MUON_TTVA_SYS__1down       ;
  Double_t   weight_MUON_TTVA_SYS__1up         ;
  Double_t   weight_PRW_DATASF__1down          ;
  Double_t   weight_PRW_DATASF__1up            ;

  TBranch *b_event_type;  //!
  TBranch *b_event;  //!
  TBranch *b_run;  //!
  TBranch *b_lbn;  //!
  TBranch *b_pass_vtx4lCut;  //!
  TBranch *b_m4l_constrained;  //!
  TBranch *b_m4l_Fsr;  //!
  TBranch *b_pt4l_unconstrained;  //!
  TBranch *b_y4l_unconstrained;  //!
  TBranch *b_mZ1_unconstrained;  //!
  TBranch *b_mZ2_unconstrained;  //!
  TBranch *b_cthstr_unconstrained;  //!
  TBranch *b_pt4l_fsr;  //!
  TBranch *b_y4l_fsr;  //!
  TBranch *b_mZ1_fsr;  //!
  TBranch *b_mZ2_fsr;  //!
  TBranch *b_cthstr_fsr;  //!
  TBranch *b_jet_pt;  //!
  TBranch *b_jet_phi;  //!
  TBranch *b_jet_eta;  //!
  TBranch *b_weight;  //!
  TBranch *b_w_xs;  //!
  TBranch *b_lumi;  //!
  TBranch *b_dijet_deltaeta;  //!
  TBranch *b_dijet_invmass;  //!
  TBranch *b_dijet_deltaphi;  //!
  TBranch *b_n_jets;  //!
  TBranch *b_n_jets_btag70;  //!
  TBranch *b_cand_index;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP0__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP0__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP1__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP1__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP10__1down;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP10__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP11__1down;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP11__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP12__1down;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP12__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP13__1down;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP13__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP14__1down;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP14__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP2__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP2__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP3__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP3__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP4__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP4__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP5__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP5__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP6__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP6__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP7__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP7__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP8__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP8__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP9__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_CorrUncertaintyNP9__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up  ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up   ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down ;  //!
  TBranch *b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up   ;  //!
  TBranch *b_weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down  ;  //!
  TBranch *b_weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up    ;  //!
  TBranch *b_weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down ;  //!
  TBranch *b_weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up   ;  //!
  TBranch *b_weight_HOEW_QCD_syst__1down       ;  //!
  TBranch *b_weight_HOEW_QCD_syst__1up         ;  //!
  TBranch *b_weight_HOEW_syst__1down           ;  //!
  TBranch *b_weight_HOEW_syst__1up             ;  //!
  TBranch *b_weight_HOQCD_scale_syst__1down    ;  //!
  TBranch *b_weight_HOQCD_scale_syst__1up      ;  //!
  TBranch *b_weight_JvtEfficiencyDown          ;  //!
  TBranch *b_weight_JvtEfficiencyUp            ;  //!
  TBranch *b_weight_MUON_EFF_STAT__1down       ;  //!
  TBranch *b_weight_MUON_EFF_STAT__1up         ;  //!
  TBranch *b_weight_MUON_EFF_STAT_LOWPT__1down ;  //!
  TBranch *b_weight_MUON_EFF_STAT_LOWPT__1up   ;  //!
  TBranch *b_weight_MUON_EFF_SYS__1down        ;  //!
  TBranch *b_weight_MUON_EFF_SYS__1up          ;  //!
  TBranch *b_weight_MUON_EFF_SYS_LOWPT__1down  ;  //!
  TBranch *b_weight_MUON_EFF_SYS_LOWPT__1up    ;  //!
  TBranch *b_weight_MUON_ISO_STAT__1down       ;  //!
  TBranch *b_weight_MUON_ISO_STAT__1up         ;  //!
  TBranch *b_weight_MUON_ISO_SYS__1down        ;  //!
  TBranch *b_weight_MUON_ISO_SYS__1up          ;  //!
  TBranch *b_weight_MUON_TTVA_STAT__1down      ;  //!
  TBranch *b_weight_MUON_TTVA_STAT__1up        ;  //!
  TBranch *b_weight_MUON_TTVA_SYS__1down       ;  //!
  TBranch *b_weight_MUON_TTVA_SYS__1up         ;  //!
  TBranch *b_weight_PRW_DATASF__1down          ;  //!
  TBranch *b_weight_PRW_DATASF__1up            ;  //!

  /* Fiducial Minitrees variables */
  ULong64_t thevent;
  Int_t     thrun;
  Float_t   Z1_m_fid;
  Float_t   Z2_m_fid;
  Int_t     njets_fid;
  Int_t     nbjets_fid;
  Float_t   cthstr_fid;
  Float_t   leading_jet_pt_fid;
  Float_t   higgs_pt_fid;
  Float_t   higgs_y_fid;
  Float_t   thweight;
  Float_t   mcweight;
  Float_t   ptweight;
  Float_t   thlumi;
  Int_t     pass_fid_cut;
  Float_t   dijet_deltaeta_fid;
  Float_t   dijet_deltaphi_fid;
  Float_t   dijet_invmass_fid;
  Float_t   jet_phi_truth[4];
  Float_t   jet_eta_truth[4];
  
  TBranch *b_thevent;  //!
  TBranch *b_thrun;  //!
  TBranch *b_Z1_m_fid;  //!
  TBranch *b_Z2_m_fid;  //!
  TBranch *b_njets_fid;  //!
  TBranch *b_nbjets_fid;  //!
  TBranch *b_cthstr_fid;  //!
  TBranch *b_leading_jet_pt_fid;  //!
  TBranch *b_higgs_pt_fid;  //!
  TBranch *b_higgs_y_fid;  //!
  TBranch *b_thweight;  //!
  TBranch *b_mcweight;  //!
  TBranch *b_ptweight;  //!
  TBranch *b_thlumi;  //! 
  TBranch *b_pass_fid_cut; //!
  TBranch *b_dijet_deltaeta_fid;  //!
  TBranch *b_dijet_deltaphi_fid;  //!
  TBranch *b_dijet_invmass_fid;  //!
  TBranch *b_jet_phi_truth;  //!
  TBranch *b_jet_eta_truth;  //!
};
#endif
