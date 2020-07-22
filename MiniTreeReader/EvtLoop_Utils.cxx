#include "EventLoop.h"

void EventLoop::SetChainBranches(){

  PRINT_DEBUG("<EventLoop::SetChainBranches()>:: setting branches for reco chain ...");

  jet_pt = 0; jet_phi = 0; jet_eta = 0; jet_m = 0;
  
  m_Chain->SetBranchAddress("event_type"    , &event_type    , &b_event_type );
  m_Chain->SetBranchAddress("event"         , &event         , &b_event      );
  m_Chain->SetBranchAddress("run"           , &run           , &b_run        );
  m_Chain->SetBranchAddress("jet_pt"        , &jet_pt        , &b_jet_pt     );
  m_Chain->SetBranchAddress("jet_phi"       , &jet_phi       , &b_jet_phi    );
  m_Chain->SetBranchAddress("jet_eta"       , &jet_eta       , &b_jet_eta    );
  m_Chain->SetBranchAddress("jet_m"         , &jet_m         , &b_jet_m      );
  m_Chain->SetBranchAddress("weight"        , &weight        , &b_weight     );
  m_Chain->SetBranchAddress("n_jets"        , &njets         , &b_njets      );
  m_Chain->SetBranchAddress("n_jets_btag70" , &nbjets        , &b_nbjets     );
  m_Chain->SetBranchAddress("dijet_deltaeta", &etajj         , &b_etajj      );
  m_Chain->SetBranchAddress("dijet_invmass" , &mjj           , &b_mjj        );
  m_Chain->SetBranchAddress("dijet_deltaphi", &phijj         , &b_phijj);
  /* FSR variables */
  m_Chain->SetBranchAddress("m4l_fsr"       , &m4l_fsr       , &b_m4l_fsr    );
  m_Chain->SetBranchAddress("pt4l_fsr"      , &pt4l_fsr      , &b_pt4l_fsr   );
  m_Chain->SetBranchAddress("mZ1_fsr"       , &mZ1_fsr       , &b_mZ1_fsr    );
  m_Chain->SetBranchAddress("mZ2_fsr"       , &mZ2_fsr       , &b_mZ2_fsr    );
  m_Chain->SetBranchAddress("y4l_fsr"       , &y4l_fsr       , &b_y4l_fsr    );
  m_Chain->SetBranchAddress("cthstr_fsr"    , &cthstr_fsr    , &b_cthstr_fsr );
  m_Chain->SetBranchAddress("cth1_fsr"      , &ct1_fsr       , &b_ct1_fsr    );
  m_Chain->SetBranchAddress("cth2_fsr"      , &ct2_fsr       , &b_ct2_fsr    );
  m_Chain->SetBranchAddress("phi_fsr"       , &phi_fsr       , &b_phi_fsr    );
  m_Chain->SetBranchAddress("phi1_fsr"      , &phi1_fsr      , &b_phi1_fsr   );
  if(m_Process!=Process::data){
    m_Chain->SetBranchAddress("w_lumi"      , &w_lumi        , &b_w_lumi     );
    m_Chain->SetBranchAddress("w_xs"        , &w_xs          , &b_w_xs       );
    m_Chain->SetBranchAddress("w_MCw"       , &w_MCw         , &b_w_MCw      );
    if(m_removeLepWeight)
      m_Chain->SetBranchAddress("w_lepEff"  , &w_lepEff      , &b_w_lepEff   );
  }
    
  if(m_isCouplings){
    m_Chain->SetBranchAddress("prod_type"                       , &prod_type                       , &b_prod_type                       );
    m_Chain->SetBranchAddress("HTXS_Stage1_Category_pTjet30"    , &HTXS_Stage1_Category_pTjet30    , &b_HTXS_Stage1_Category_pTjet30    );
    m_Chain->SetBranchAddress("BDT_discriminant"		, &BDT_discriminant		   , &b_BDT_discriminant                );		
    m_Chain->SetBranchAddress("BDT_1Jet_pt4l_60"		, &BDT_1Jet_pt4l_60		   , &b_BDT_1Jet_pt4l_60                );
    m_Chain->SetBranchAddress("BDT_1Jet_pt4l_60_120"		, &BDT_1Jet_pt4l_60_120		   , &b_BDT_1Jet_pt4l_60_120	        );
    m_Chain->SetBranchAddress("BDT_OneJet_jptetadR_discriminant", &BDT_OneJet_jptetadR_discriminant, &b_BDT_OneJet_jptetadR_discriminant);
    m_Chain->SetBranchAddress("BDT_VH_noptHjj_discriminant"     , &BDT_VH_noptHjj_discriminant     , &b_BDT_VH_noptHjj_discriminant     );
    m_Chain->SetBranchAddress("BDT_TwoJet_discriminant"         , &BDT_TwoJet_discriminant         , &b_BDT_TwoJet_discriminant         );
  }
  
  switch(m_SystNum){
    
  case Syst::EL_EFF_ID_CorrUncertaintyNP0: 
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP0__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP0__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP0__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP0+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP0__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP0__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP0__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP1__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP1__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP1__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP1+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP1__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP1__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP1__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP2:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP2__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP2__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP2__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP2+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP2__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP2__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP2__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP3:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP3__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP3__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP3__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP3+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP3__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP3__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP3__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP4:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP4__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP4__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP4__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP4+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP4__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP4__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP4__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP5:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP5__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP5__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP5__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP5+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP5__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP5__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP5__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP6:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP6__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP6__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP6__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP6+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP6__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP6__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP6__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP7:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP7__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP7__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP7__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP7+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP7__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP7__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP7__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP8:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP8__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP8__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP8__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP8+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP8__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP8__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP8__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP9:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP9__1down" , &wgt_EL_EFF_ID_CorrUncertaintyNP9__1down  , &b_wgt_EL_EFF_ID_CorrUncertaintyNP9__1down ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP9+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP9__1up"   , &wgt_EL_EFF_ID_CorrUncertaintyNP9__1up    , &b_wgt_EL_EFF_ID_CorrUncertaintyNP9__1up   ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP10:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP10__1down", &wgt_EL_EFF_ID_CorrUncertaintyNP10__1down , &b_wgt_EL_EFF_ID_CorrUncertaintyNP10__1down); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP10+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP10__1up"  , &wgt_EL_EFF_ID_CorrUncertaintyNP10__1up   , &b_wgt_EL_EFF_ID_CorrUncertaintyNP10__1up  ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP11:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP11__1down", &wgt_EL_EFF_ID_CorrUncertaintyNP11__1down , &b_wgt_EL_EFF_ID_CorrUncertaintyNP11__1down); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP11+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP11__1up"  , &wgt_EL_EFF_ID_CorrUncertaintyNP11__1up   , &b_wgt_EL_EFF_ID_CorrUncertaintyNP11__1up  ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP12:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP12__1down", &wgt_EL_EFF_ID_CorrUncertaintyNP12__1down , &b_wgt_EL_EFF_ID_CorrUncertaintyNP12__1down); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP12+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP12__1up"  , &wgt_EL_EFF_ID_CorrUncertaintyNP12__1up   , &b_wgt_EL_EFF_ID_CorrUncertaintyNP12__1up  ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP13:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP13__1down", &wgt_EL_EFF_ID_CorrUncertaintyNP13__1down , &b_wgt_EL_EFF_ID_CorrUncertaintyNP13__1down); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP13+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP13__1up"  , &wgt_EL_EFF_ID_CorrUncertaintyNP13__1up   , &b_wgt_EL_EFF_ID_CorrUncertaintyNP13__1up  ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP14:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP14__1down", &wgt_EL_EFF_ID_CorrUncertaintyNP14__1down , &b_wgt_EL_EFF_ID_CorrUncertaintyNP14__1down); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP14+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP14__1up"  , &wgt_EL_EFF_ID_CorrUncertaintyNP14__1up   , &b_wgt_EL_EFF_ID_CorrUncertaintyNP14__1up  ); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP15:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP15__1down", &wgt_EL_EFF_ID_CorrUncertaintyNP15__1down , &b_wgt_EL_EFF_ID_CorrUncertaintyNP15__1down); break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP15+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_CorrUncertaintyNP15__1up"  , &wgt_EL_EFF_ID_CorrUncertaintyNP15__1up   , &b_wgt_EL_EFF_ID_CorrUncertaintyNP15__1up  ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down" , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down  , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up"   , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up    , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up   ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down", &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up"  , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up   , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up  ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down", &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up"  , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up   , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up  ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down", &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up"  , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up   , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up  ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down", &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up"  , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up   , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up  ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down", &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up"  , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up   , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up  ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down", &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up"  , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up   , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up  ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down", &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1down); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up"  , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up   , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16__1up  ); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down", &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1down); break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up"  , &wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up   , &b_wgt_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP17__1up  ); break;
  case Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down"        , &wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down         , &b_wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down        ); break;
  case Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"          , &wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up           , &b_wgt_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up          ); break;
  case Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down"       , &wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down        , &b_wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down       ); break;
  case Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR+1:
    m_Chain->SetBranchAddress("weight_var_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up"         , &wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up          , &b_wgt_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up         ); break;
  case Syst::FT_EFF_Eigen_B_0:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_B_0__1down"               , &wgt_FT_EFF_Eigen_B_0__1down               , &b_wgt_FT_EFF_Eigen_B_0__1down                           ); break;
  case Syst::FT_EFF_Eigen_B_0+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_B_0__1up"                 , &wgt_FT_EFF_Eigen_B_0__1up                 , &b_wgt_FT_EFF_Eigen_B_0__1up                             ); break;
  case Syst::FT_EFF_Eigen_B_1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_B_1__1down"               , &wgt_FT_EFF_Eigen_B_1__1down               , &b_wgt_FT_EFF_Eigen_B_1__1down                           ); break;
  case Syst::FT_EFF_Eigen_B_1+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_B_1__1up"                 , &wgt_FT_EFF_Eigen_B_1__1up                 , &b_wgt_FT_EFF_Eigen_B_1__1up                             ); break;
  case Syst::FT_EFF_Eigen_B_2:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_B_2__1down"               , &wgt_FT_EFF_Eigen_B_2__1down               , &b_wgt_FT_EFF_Eigen_B_2__1down                           ); break;
  case Syst::FT_EFF_Eigen_B_2+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_B_2__1up"                 , &wgt_FT_EFF_Eigen_B_2__1up                 , &b_wgt_FT_EFF_Eigen_B_2__1up                             ); break;
  case Syst::FT_EFF_Eigen_C_0:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_C_0__1down"               , &wgt_FT_EFF_Eigen_C_0__1down               , &b_wgt_FT_EFF_Eigen_C_0__1down                           ); break;
  case Syst::FT_EFF_Eigen_C_0+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_C_0__1up"                 , &wgt_FT_EFF_Eigen_C_0__1up                 , &b_wgt_FT_EFF_Eigen_C_0__1up                             ); break;
  case Syst::FT_EFF_Eigen_C_1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_C_1__1down"               , &wgt_FT_EFF_Eigen_C_1__1down               , &b_wgt_FT_EFF_Eigen_C_1__1down                           ); break;
  case Syst::FT_EFF_Eigen_C_1+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_C_1__1up"                 , &wgt_FT_EFF_Eigen_C_1__1up                 , &b_wgt_FT_EFF_Eigen_C_1__1up                             ); break;
  case Syst::FT_EFF_Eigen_C_2:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_C_2__1down"               , &wgt_FT_EFF_Eigen_C_2__1down               , &b_wgt_FT_EFF_Eigen_C_2__1down                           ); break;
  case Syst::FT_EFF_Eigen_C_2+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_C_2__1up"                 , &wgt_FT_EFF_Eigen_C_2__1up                 , &b_wgt_FT_EFF_Eigen_C_2__1up                             ); break;
  case Syst::FT_EFF_Eigen_C_3:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_C_3__1down"               , &wgt_FT_EFF_Eigen_C_3__1down               , &b_wgt_FT_EFF_Eigen_C_3__1down                           ); break;
  case Syst::FT_EFF_Eigen_C_3+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_C_3__1up"                 , &wgt_FT_EFF_Eigen_C_3__1up                 , &b_wgt_FT_EFF_Eigen_C_3__1up                             ); break;
  case Syst::FT_EFF_Eigen_Light_0:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_0__1down"           , &wgt_FT_EFF_Eigen_Light_0__1down           , &b_wgt_FT_EFF_Eigen_Light_0__1down                       ); break;
  case Syst::FT_EFF_Eigen_Light_0+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_0__1up"             , &wgt_FT_EFF_Eigen_Light_0__1up             , &b_wgt_FT_EFF_Eigen_Light_0__1up                         ); break;
  case Syst::FT_EFF_Eigen_Light_1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_1__1down"           , &wgt_FT_EFF_Eigen_Light_1__1down           , &b_wgt_FT_EFF_Eigen_Light_1__1down                       ); break;
  case Syst::FT_EFF_Eigen_Light_1+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_1__1up"             , &wgt_FT_EFF_Eigen_Light_1__1up             , &b_wgt_FT_EFF_Eigen_Light_1__1up                         ); break;
  case Syst::FT_EFF_Eigen_Light_2:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_2__1down"           , &wgt_FT_EFF_Eigen_Light_2__1down           , &b_wgt_FT_EFF_Eigen_Light_2__1down                       ); break;
  case Syst::FT_EFF_Eigen_Light_2+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_2__1up"             , &wgt_FT_EFF_Eigen_Light_2__1up             , &b_wgt_FT_EFF_Eigen_Light_2__1up                         ); break;
  case Syst::FT_EFF_Eigen_Light_3:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_3__1down"           , &wgt_FT_EFF_Eigen_Light_3__1down           , &b_wgt_FT_EFF_Eigen_Light_3__1down                       ); break;
  case Syst::FT_EFF_Eigen_Light_3+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_3__1up"             , &wgt_FT_EFF_Eigen_Light_3__1up             , &b_wgt_FT_EFF_Eigen_Light_3__1up                         ); break;
  case Syst::FT_EFF_Eigen_Light_4:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_4__1down"           , &wgt_FT_EFF_Eigen_Light_4__1down           , &b_wgt_FT_EFF_Eigen_Light_4__1down                       ); break;
  case Syst::FT_EFF_Eigen_Light_4+1:
    m_Chain->SetBranchAddress("weight_var_FT_EFF_Eigen_Light_4__1up"             , &wgt_FT_EFF_Eigen_Light_4__1up             , &b_wgt_FT_EFF_Eigen_Light_4__1up                         ); break;
  case Syst::JET_JvtEfficiency:
    m_Chain->SetBranchAddress("weight_var_JET_JvtEfficiency__1down"              , &wgt_JET_JvtEfficiency__1down              , &b_wgt_JET_JvtEfficiency__1down                          ); break;
  case Syst::JET_JvtEfficiency+1:
    m_Chain->SetBranchAddress("weight_var_JET_JvtEfficiency__1up"                , &wgt_JET_JvtEfficiency__1up                , &b_wgt_JET_JvtEfficiency__1up                            ); break;
  case Syst::JET_fJvtEfficiency:
    m_Chain->SetBranchAddress("weight_var_JET_fJvtEfficiency__1down"             , &wgt_JET_fJvtEfficiency__1down             , &b_wgt_JET_fJvtEfficiency__1down                         ); break;
  case Syst::JET_fJvtEfficiency+1:
    m_Chain->SetBranchAddress("weight_var_JET_fJvtEfficiency__1up"               , &wgt_JET_fJvtEfficiency__1up               , &b_wgt_JET_fJvtEfficiency__1up                           ); break;
  case Syst::HOEW_QCD_syst:
    m_Chain->SetBranchAddress("weight_var_HOEW_QCD_syst__1down"                  , &wgt_HOEW_QCD_syst__1down                  , &b_wgt_HOEW_QCD_syst__1down                              ); break;
  case Syst::HOEW_QCD_syst+1:
    m_Chain->SetBranchAddress("weight_var_HOEW_QCD_syst__1up"                    , &wgt_HOEW_QCD_syst__1up                    , &b_wgt_HOEW_QCD_syst__1up                                ); break;
  case Syst::HOEW_syst:
    m_Chain->SetBranchAddress("weight_var_HOEW_syst__1down"                      , &wgt_HOEW_syst__1down                      , &b_wgt_HOEW_syst__1down                                  ); break;
  case Syst::HOEW_syst+1:
    m_Chain->SetBranchAddress("weight_var_HOEW_syst__1up"                        , &wgt_HOEW_syst__1up                        , &b_wgt_HOEW_syst__1up                                    ); break;
  case Syst::HOQCD_scale_syst:
    m_Chain->SetBranchAddress("weight_var_HOQCD_scale_syst__1down"               , &wgt_HOQCD_scale_syst__1down               , &b_wgt_HOQCD_scale_syst__1down                           ); break;
  case Syst::HOQCD_scale_syst+1:
    m_Chain->SetBranchAddress("weight_var_HOQCD_scale_syst__1up"                 , &wgt_HOQCD_scale_syst__1up                 , &b_wgt_HOQCD_scale_syst__1up                             ); break;
  case Syst::MUON_EFF_ISO_STAT:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_ISO_STAT__1down"              , &wgt_MUON_EFF_ISO_STAT__1down              , &b_wgt_MUON_EFF_ISO_STAT__1down                          ); break;
  case Syst::MUON_EFF_ISO_STAT+1:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_ISO_STAT__1up"                , &wgt_MUON_EFF_ISO_STAT__1up                , &b_wgt_MUON_EFF_ISO_STAT__1up                            ); break;
  case Syst::MUON_EFF_ISO_SYS:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_ISO_SYS__1down"               , &wgt_MUON_EFF_ISO_SYS__1down               , &b_wgt_MUON_EFF_ISO_SYS__1down                           ); break;
  case Syst::MUON_EFF_ISO_SYS+1:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_ISO_SYS__1up"                 , &wgt_MUON_EFF_ISO_SYS__1up                 , &b_wgt_MUON_EFF_ISO_SYS__1up                             ); break;
  case Syst::MUON_EFF_RECO_STAT_LOWPT:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_RECO_STAT_LOWPT__1down"       , &wgt_MUON_EFF_RECO_STAT_LOWPT__1down       , &b_wgt_MUON_EFF_RECO_STAT_LOWPT__1down                   ); break;
  case Syst::MUON_EFF_RECO_STAT_LOWPT+1:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_RECO_STAT_LOWPT__1up"         , &wgt_MUON_EFF_RECO_STAT_LOWPT__1up         , &b_wgt_MUON_EFF_RECO_STAT_LOWPT__1up                     ); break;
  case Syst::MUON_EFF_RECO_STAT:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_RECO_STAT__1down"             , &wgt_MUON_EFF_RECO_STAT__1down             , &b_wgt_MUON_EFF_RECO_STAT__1down                         ); break;
  case Syst::MUON_EFF_RECO_STAT+1:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_RECO_STAT__1up"               , &wgt_MUON_EFF_RECO_STAT__1up               , &b_wgt_MUON_EFF_RECO_STAT__1up                           ); break;
  case Syst::MUON_EFF_RECO_SYS_LOWPT:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_RECO_SYS_LOWPT__1down"        , &wgt_MUON_EFF_RECO_SYS_LOWPT__1down        , &b_wgt_MUON_EFF_RECO_SYS_LOWPT__1down                    ); break;
  case Syst::MUON_EFF_RECO_SYS_LOWPT+1:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_RECO_SYS_LOWPT__1up"          , &wgt_MUON_EFF_RECO_SYS_LOWPT__1up          , &b_wgt_MUON_EFF_RECO_SYS_LOWPT__1up                      ); break;
  case Syst::MUON_EFF_RECO_SYS:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_RECO_SYS__1down"              , &wgt_MUON_EFF_RECO_SYS__1down              , &b_wgt_MUON_EFF_RECO_SYS__1down                          ); break;
  case Syst::MUON_EFF_RECO_SYS+1:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_RECO_SYS__1up"                , &wgt_MUON_EFF_RECO_SYS__1up                , &b_wgt_MUON_EFF_RECO_SYS__1up                            ); break;
  case Syst::MUON_EFF_TTVA_STAT:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_TTVA_STAT__1down"             , &wgt_MUON_EFF_TTVA_STAT__1down             , &b_wgt_MUON_EFF_TTVA_STAT__1down                         ); break;
  case Syst::MUON_EFF_TTVA_STAT+1:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_TTVA_STAT__1up"               , &wgt_MUON_EFF_TTVA_STAT__1up               , &b_wgt_MUON_EFF_TTVA_STAT__1up                           ); break;
  case Syst::MUON_EFF_TTVA_SYS:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_TTVA_SYS__1down"              , &wgt_MUON_EFF_TTVA_SYS__1down              , &b_wgt_MUON_EFF_TTVA_SYS__1down                          ); break;
  case Syst::MUON_EFF_TTVA_SYS+1:
    m_Chain->SetBranchAddress("weight_var_MUON_EFF_TTVA_SYS__1up"                , &wgt_MUON_EFF_TTVA_SYS__1up                , &b_wgt_MUON_EFF_TTVA_SYS__1up                            ); break;
  case Syst::PRW_DATASF:
    m_Chain->SetBranchAddress("weight_var_PRW_DATASF__1down"                     , &wgt_PRW_DATASF__1down                     , &b_wgt_PRW_DATASF__1down                                 ); break;
  case Syst::PRW_DATASF+1:
    m_Chain->SetBranchAddress("weight_var_PRW_DATASF__1up"                       , &wgt_PRW_DATASF__1up                       , &b_wgt_PRW_DATASF__1up                                   ); break;
  case Syst::VAR_TH_muR0p5_muF0p5_VBF:
  case Syst::VAR_TH_muR0p5_muF0p5_VH :
  case Syst::VAR_TH_muR0p5_muF0p5_ttH:
    m_Chain->SetBranchAddress("weight_var_th_muR0p5_muF0p5"                      , &wgt_var_th_muR0p5_muF0p5                  , &b_wgt_var_th_muR0p5_muF0p5                              ); break;
  case Syst::VAR_TH_muR0p5_muF1p0_VBF:
  case Syst::VAR_TH_muR0p5_muF1p0_VH :
  case Syst::VAR_TH_muR0p5_muF1p0_ttH:
    m_Chain->SetBranchAddress("weight_var_th_muR0p5_muF1p0"                      , &wgt_var_th_muR0p5_muF1p0                  , &b_wgt_var_th_muR0p5_muF1p0                              ); break;
  case Syst::VAR_TH_muR0p5_muF2p0_VBF:
  case Syst::VAR_TH_muR0p5_muF2p0_VH:
  case Syst::VAR_TH_muR0p5_muF2p0_ttH:
    m_Chain->SetBranchAddress("weight_var_th_muR0p5_muF2p0"                      , &wgt_var_th_muR0p5_muF2p0                  , &b_wgt_var_th_muR0p5_muF2p0                              ); break;
  case Syst::VAR_TH_muR1p0_muF0p5_VBF:
  case Syst::VAR_TH_muR1p0_muF0p5_VH :
  case Syst::VAR_TH_muR1p0_muF0p5_ttH:
    m_Chain->SetBranchAddress("weight_var_th_muR1p0_muF0p5"                      , &wgt_var_th_muR1p0_muF0p5                  , &b_wgt_var_th_muR1p0_muF0p5                              ); break;
  case Syst::VAR_TH_muR1p0_muF2p0_VBF:
  case Syst::VAR_TH_muR1p0_muF2p0_VH :
  case Syst::VAR_TH_muR1p0_muF2p0_ttH:
    m_Chain->SetBranchAddress("weight_var_th_muR1p0_muF2p0"                      , &wgt_var_th_muR1p0_muF2p0                  , &b_wgt_var_th_muR1p0_muF2p0                              ); break;
  case Syst::VAR_TH_muR2p0_muF0p5_VBF:
  case Syst::VAR_TH_muR2p0_muF0p5_VH :
  case Syst::VAR_TH_muR2p0_muF0p5_ttH:
    m_Chain->SetBranchAddress("weight_var_th_muR2p0_muF0p5"                      , &wgt_var_th_muR2p0_muF0p5                  , &b_wgt_var_th_muR2p0_muF0p5                              ); break;
  case Syst::VAR_TH_muR2p0_muF1p0_VBF:
  case Syst::VAR_TH_muR2p0_muF1p0_VH :
  case Syst::VAR_TH_muR2p0_muF1p0_ttH:
    m_Chain->SetBranchAddress("weight_var_th_muR2p0_muF1p0"                      , &wgt_var_th_muR2p0_muF1p0                  , &b_wgt_var_th_muR2p0_muF1p0                              ); break;
  case Syst::VAR_TH_muR2p0_muF2p0_VBF:
  case Syst::VAR_TH_muR2p0_muF2p0_VH :
  case Syst::VAR_TH_muR2p0_muF2p0_ttH:
    m_Chain->SetBranchAddress("weight_var_th_muR2p0_muF2p0"                      , &wgt_var_th_muR2p0_muF2p0                  , &b_wgt_var_th_muR2p0_muF2p0                              ); break;
  case Syst::VAR_TH_pdf_90400  :
  case Syst::VAR_TH_PDF_Nominal:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90400"                          , &wgt_var_th_pdf_90400                      , &b_wgt_var_th_pdf_90400                                  ); break;
  case Syst::VAR_TH_pdf_90401:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90401"                          , &wgt_var_th_pdf_90401                      , &b_wgt_var_th_pdf_90401                                  ); break;
  case Syst::VAR_TH_pdf_90402:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90402"                          , &wgt_var_th_pdf_90402                      , &b_wgt_var_th_pdf_90402                                  ); break;
  case Syst::VAR_TH_pdf_90403:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90403"                          , &wgt_var_th_pdf_90403                      , &b_wgt_var_th_pdf_90403                                  ); break;
  case Syst::VAR_TH_pdf_90404:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90404"                          , &wgt_var_th_pdf_90404                      , &b_wgt_var_th_pdf_90404                                  ); break;
  case Syst::VAR_TH_pdf_90405:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90405"                          , &wgt_var_th_pdf_90405                      , &b_wgt_var_th_pdf_90405                                  ); break;
  case Syst::VAR_TH_pdf_90406:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90406"                          , &wgt_var_th_pdf_90406                      , &b_wgt_var_th_pdf_90406                                  ); break;
  case Syst::VAR_TH_pdf_90407:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90407"                          , &wgt_var_th_pdf_90407                      , &b_wgt_var_th_pdf_90407                                  ); break;
  case Syst::VAR_TH_pdf_90408:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90408"                          , &wgt_var_th_pdf_90408                      , &b_wgt_var_th_pdf_90408                                  ); break;
  case Syst::VAR_TH_pdf_90409:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90409"                          , &wgt_var_th_pdf_90409                      , &b_wgt_var_th_pdf_90409                                  ); break;
  case Syst::VAR_TH_pdf_90410:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90410"                          , &wgt_var_th_pdf_90410                      , &b_wgt_var_th_pdf_90410                                  ); break;
  case Syst::VAR_TH_pdf_90411:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90411"                          , &wgt_var_th_pdf_90411                      , &b_wgt_var_th_pdf_90411                                  ); break;
  case Syst::VAR_TH_pdf_90412:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90412"                          , &wgt_var_th_pdf_90412                      , &b_wgt_var_th_pdf_90412                                  ); break;
  case Syst::VAR_TH_pdf_90413:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90413"                          , &wgt_var_th_pdf_90413                      , &b_wgt_var_th_pdf_90413                                  ); break;
  case Syst::VAR_TH_pdf_90414:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90414"                          , &wgt_var_th_pdf_90414                      , &b_wgt_var_th_pdf_90414                                  ); break;
  case Syst::VAR_TH_pdf_90415:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90415"                          , &wgt_var_th_pdf_90415                      , &b_wgt_var_th_pdf_90415                                  ); break;
  case Syst::VAR_TH_pdf_90416:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90416"                          , &wgt_var_th_pdf_90416                      , &b_wgt_var_th_pdf_90416                                  ); break;
  case Syst::VAR_TH_pdf_90417:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90417"                          , &wgt_var_th_pdf_90417                      , &b_wgt_var_th_pdf_90417                                  ); break;
  case Syst::VAR_TH_pdf_90418:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90418"                          , &wgt_var_th_pdf_90418                      , &b_wgt_var_th_pdf_90418                                  ); break;
  case Syst::VAR_TH_pdf_90419:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90419"                          , &wgt_var_th_pdf_90419                      , &b_wgt_var_th_pdf_90419                                  ); break;
  case Syst::VAR_TH_pdf_90420:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90420"                          , &wgt_var_th_pdf_90420                      , &b_wgt_var_th_pdf_90420                                  ); break;
  case Syst::VAR_TH_pdf_90421:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90421"                          , &wgt_var_th_pdf_90421                      , &b_wgt_var_th_pdf_90421                                  ); break;
  case Syst::VAR_TH_pdf_90422:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90422"                          , &wgt_var_th_pdf_90422                      , &b_wgt_var_th_pdf_90422                                  ); break;
  case Syst::VAR_TH_pdf_90423:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90423"                          , &wgt_var_th_pdf_90423                      , &b_wgt_var_th_pdf_90423                                  ); break;
  case Syst::VAR_TH_pdf_90424:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90424"                          , &wgt_var_th_pdf_90424                      , &b_wgt_var_th_pdf_90424                                  ); break;
  case Syst::VAR_TH_pdf_90425:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90425"                          , &wgt_var_th_pdf_90425                      , &b_wgt_var_th_pdf_90425                                  ); break;
  case Syst::VAR_TH_pdf_90426:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90426"                          , &wgt_var_th_pdf_90426                      , &b_wgt_var_th_pdf_90426                                  ); break;
  case Syst::VAR_TH_pdf_90427:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90427"                          , &wgt_var_th_pdf_90427                      , &b_wgt_var_th_pdf_90427                                  ); break;
  case Syst::VAR_TH_pdf_90428:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90428"                          , &wgt_var_th_pdf_90428                      , &b_wgt_var_th_pdf_90428                                  ); break;
  case Syst::VAR_TH_pdf_90429:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90429"                          , &wgt_var_th_pdf_90429                      , &b_wgt_var_th_pdf_90429                                  ); break;
  case Syst::VAR_TH_pdf_90430:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90430"                          , &wgt_var_th_pdf_90430                      , &b_wgt_var_th_pdf_90430                                  ); break;
  case Syst::VAR_TH_pdf_90431:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90431"                          , &wgt_var_th_pdf_90431                      , &b_wgt_var_th_pdf_90431                                  ); break;
  case Syst::VAR_TH_pdf_90432:
    m_Chain->SetBranchAddress("weight_var_th_pdf_90432"                          , &wgt_var_th_pdf_90432                      , &b_wgt_var_th_pdf_90432                                  ); break;
  case Syst::VAR_TH_ggF_qcd_2017_pTH120:				         					      					                         
    m_Chain->SetBranchAddress("weight_var_th_ggF_qcd_2017_pTH120"                , &wgt_var_th_ggF_qcd_2017_pTH120            , &b_wgt_var_th_ggF_qcd_2017_pTH120                        ); break;
  case Syst::VAR_TH_ggF_qcd_2017_pTH60:					         					      					                         
    m_Chain->SetBranchAddress("weight_var_th_ggF_qcd_2017_pTH60"                 , &wgt_var_th_ggF_qcd_2017_pTH60             , &b_wgt_var_th_ggF_qcd_2017_pTH60                         ); break;
  case Syst::VAR_TH_ggF_QCD_pTH_nJ0:
    m_Chain->SetBranchAddress("weight_var_th_qcd_pTH_nJ0"                        , &wgt_var_th_ggF_qcd_nJ0                    , &b_wgt_var_th_ggF_qcd_nJ0                                ); break;
  case Syst::VAR_TH_qcd_wg1_mig01:					         					      					                         
    m_Chain->SetBranchAddress("weight_var_th_qcd_wg1_mig01"                      , &wgt_var_th_qcd_wg1_mig01                  , &b_wgt_var_th_qcd_wg1_mig01                              ); break;
  case Syst::VAR_TH_qcd_wg1_mig12:					         					      					                         
    m_Chain->SetBranchAddress("weight_var_th_qcd_wg1_mig12"                      , &wgt_var_th_qcd_wg1_mig12                  , &b_wgt_var_th_qcd_wg1_mig12                              ); break;
  case Syst::VAR_TH_qcd_wg1_mu:
    m_Chain->SetBranchAddress("weight_var_th_qcd_wg1_mu"                         , &wgt_var_th_qcd_wg1_mu                     , &b_wgt_var_th_qcd_wg1_mu                                 ); break;
  case Syst::VAR_TH_qcd_wg1_qm_t:					         					      					                         
    m_Chain->SetBranchAddress("weight_var_th_qcd_wg1_qm_t"                       , &wgt_var_th_qcd_wg1_qm_t                   , &b_wgt_var_th_qcd_wg1_qm_t                               ); break;
  case Syst::VAR_TH_qcd_wg1_res:					         					      					                         
    m_Chain->SetBranchAddress("weight_var_th_qcd_wg1_res"                        , &wgt_var_th_qcd_wg1_res                    , &b_wgt_var_th_qcd_wg1_res                                ); break;
  case Syst::VAR_TH_qcd_wg1_vbf2j:					         					      					                         
    m_Chain->SetBranchAddress("weight_var_th_qcd_wg1_vbf2j"                      , &wgt_var_th_qcd_wg1_vbf2j                  , &b_wgt_var_th_qcd_wg1_vbf2j                              ); break;
  case Syst::VAR_TH_qcd_wg1_vbf3j:					         					      					                         
    m_Chain->SetBranchAddress("weight_var_th_qcd_wg1_vbf3j"                      , &wgt_var_th_qcd_wg1_vbf3j                  , &b_wgt_var_th_qcd_wg1_vbf3j                              ); break;
  case Syst::VAR_TH_QCD_Scale_Nominal_VBF:
  case Syst::VAR_TH_QCD_Scale_Nominal_VH :
  case Syst::VAR_TH_QCD_Scale_Nominal_ttH:
    m_Chain->SetBranchAddress("weight_var_th_nominal"                            , &wgt_var_th_nominal                        , &b_wgt_var_th_nominal                                    ); break;
    //case Syst::VAR_TH_Shower_Herwig:
    //m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_Herwig__1up"                              , &wgt_var_th_Herwig                       , &b_wgt_var_th_Herwig                       ); break;
  case Syst::VAR_TH_Var3c:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_Var3c__1down"                      , &wgt_var_th_Var3cDown                    , &b_wgt_var_th_Var3cDown                    ); break;
  case Syst::VAR_TH_Var3c+1:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_Var3c__1up"                        , &wgt_var_th_Var3cUp                      , &b_wgt_var_th_Var3cUp                      ); break;
  case Syst::VAR_TH_hard:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_hard__1down"                       , &wgt_var_th_hardLo                       , &b_wgt_var_th_hardLo                       ); break;
  case Syst::VAR_TH_hard+1:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_hard__1up"                         , &wgt_var_th_hardHi                       , &b_wgt_var_th_hardHi                       ); break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_0p5:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p5_fsrmuRfac_0p5__1up"  , &wgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5  , &b_wgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5  ); break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_1p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p5_fsrmuRfac_1p0__1up"  , &wgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0  , &b_wgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0  ); break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_2p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p5_fsrmuRfac_2p0__1up"  , &wgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0  , &b_wgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0  ); break;
  case Syst::VAR_TH_isrmuRfac_0p625_fsrmuRfac_1p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p625_fsrmuRfac_1p0__1up", &wgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0, &b_wgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0); break;
  case Syst::VAR_TH_isrmuRfac_0p75_fsrmuRfac_1p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p75_fsrmuRfac_1p0__1up" , &wgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0 , &b_wgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0 ); break;
  case Syst::VAR_TH_isrmuRfac_0p875_fsrmuRfac_1p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p875_fsrmuRfac_1p0__1up", &wgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0, &b_wgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p5:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_0p5__1up"  , &wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5  , &b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5  ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p625:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_0p625__1up", &wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625, &b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p75:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_0p75__1up" , &wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75 , &b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75 ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p875:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_0p875__1up", &wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875, &b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p25:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_1p25__1up" , &wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25 , &b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25 ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p5:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_1p5__1up"  , &wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5  , &b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5  ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p75:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_1p75__1up" , &wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75 , &b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75 ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_2p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_2p0__1up"  , &wgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0  , &b_wgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0  ); break;
  case Syst::VAR_TH_isrmuRfac_1p25_fsrmuRfac_1p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p25_fsrmuRfac_1p0__1up" , &wgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0 , &b_wgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0 ); break;
  case Syst::VAR_TH_isrmuRfac_1p5_fsrmuRfac_1p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p5_fsrmuRfac_1p0__1up"  , &wgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0  , &b_wgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0  ); break;
  case Syst::VAR_TH_isrmuRfac_1p75_fsrmuRfac_1p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p75_fsrmuRfac_1p0__1up" , &wgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0 , &b_wgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0 ); break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_0p5:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_2p0_fsrmuRfac_0p5__1up"  , &wgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5  , &b_wgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5  ); break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_1p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_2p0_fsrmuRfac_1p0__1up"  , &wgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0  , &b_wgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0  ); break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_2p0:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_2p0_fsrmuRfac_2p0__1up"  , &wgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0  , &b_wgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0  ); break;
  case Syst::VAR_TH_qqZZ_Sherpa_CKKW:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_Sherpa_CKKW__1down", &wgt_var_th_Sherpa_CKKW__1down     , &b_wgt_var_th_Sherpa_CKKW__1down     ); break;
  case Syst::VAR_TH_qqZZ_Sherpa_CKKW+1:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_Sherpa_CKKW__1up"  , &wgt_var_th_Sherpa_CKKW__1up       , &b_wgt_var_th_Sherpa_CKKW__1up       ); break;
  case Syst::VAR_TH_qqZZ_Sherpa_CSSKIN:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_Sherpa_CSSKIN__1up", &wgt_var_th_Sherpa_CSSKIN__1up     , &b_wgt_var_th_Sherpa_CSSKIN__1up     ); break;
  case Syst::VAR_TH_qqZZ_Sherpa_QSF:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_Sherpa_QSF__1down" , &wgt_var_th_Sherpa_QSF__1down      , &b_wgt_var_th_Sherpa_QSF__1down      ); break;
  case Syst::VAR_TH_qqZZ_Sherpa_QSF+1:
    m_Chain->SetBranchAddress("weight_var_H4l_Shower_UEPS_Sherpa_QSF__1up"   , &wgt_var_th_Sherpa_QSF__1up        , &b_wgt_var_th_Sherpa_QSF__1up        ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261000:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261000"            , &wgt_var_th_MUR1_MUF1_PDF261000    , &b_wgt_var_th_MUR1_MUF1_PDF261000    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261001:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261001"            , &wgt_var_th_MUR1_MUF1_PDF261001    , &b_wgt_var_th_MUR1_MUF1_PDF261001    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261002:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261002"            , &wgt_var_th_MUR1_MUF1_PDF261002    , &b_wgt_var_th_MUR1_MUF1_PDF261002    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261003:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261003"            , &wgt_var_th_MUR1_MUF1_PDF261003    , &b_wgt_var_th_MUR1_MUF1_PDF261003    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261004:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261004"            , &wgt_var_th_MUR1_MUF1_PDF261004    , &b_wgt_var_th_MUR1_MUF1_PDF261004    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261005:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261005"            , &wgt_var_th_MUR1_MUF1_PDF261005    , &b_wgt_var_th_MUR1_MUF1_PDF261005    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261006:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261006"            , &wgt_var_th_MUR1_MUF1_PDF261006    , &b_wgt_var_th_MUR1_MUF1_PDF261006    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261007:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261007"            , &wgt_var_th_MUR1_MUF1_PDF261007    , &b_wgt_var_th_MUR1_MUF1_PDF261007    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261008:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261008"            , &wgt_var_th_MUR1_MUF1_PDF261008    , &b_wgt_var_th_MUR1_MUF1_PDF261008    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261009:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261009"            , &wgt_var_th_MUR1_MUF1_PDF261009    , &b_wgt_var_th_MUR1_MUF1_PDF261009    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261010:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261010"            , &wgt_var_th_MUR1_MUF1_PDF261010    , &b_wgt_var_th_MUR1_MUF1_PDF261010    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261011:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261011"            , &wgt_var_th_MUR1_MUF1_PDF261011    , &b_wgt_var_th_MUR1_MUF1_PDF261011    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261012:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261012"            , &wgt_var_th_MUR1_MUF1_PDF261012    , &b_wgt_var_th_MUR1_MUF1_PDF261012    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261013:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261013"            , &wgt_var_th_MUR1_MUF1_PDF261013    , &b_wgt_var_th_MUR1_MUF1_PDF261013    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261014:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261014"            , &wgt_var_th_MUR1_MUF1_PDF261014    , &b_wgt_var_th_MUR1_MUF1_PDF261014    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261015:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261015"            , &wgt_var_th_MUR1_MUF1_PDF261015    , &b_wgt_var_th_MUR1_MUF1_PDF261015    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261016:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261016"            , &wgt_var_th_MUR1_MUF1_PDF261016    , &b_wgt_var_th_MUR1_MUF1_PDF261016    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261017:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261017"            , &wgt_var_th_MUR1_MUF1_PDF261017    , &b_wgt_var_th_MUR1_MUF1_PDF261017    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261018:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261018"            , &wgt_var_th_MUR1_MUF1_PDF261018    , &b_wgt_var_th_MUR1_MUF1_PDF261018    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261019:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261019"            , &wgt_var_th_MUR1_MUF1_PDF261019    , &b_wgt_var_th_MUR1_MUF1_PDF261019    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261020:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261020"            , &wgt_var_th_MUR1_MUF1_PDF261020    , &b_wgt_var_th_MUR1_MUF1_PDF261020    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261021:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261021"            , &wgt_var_th_MUR1_MUF1_PDF261021    , &b_wgt_var_th_MUR1_MUF1_PDF261021    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261022:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261022"            , &wgt_var_th_MUR1_MUF1_PDF261022    , &b_wgt_var_th_MUR1_MUF1_PDF261022    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261023:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261023"            , &wgt_var_th_MUR1_MUF1_PDF261023    , &b_wgt_var_th_MUR1_MUF1_PDF261023    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261024:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261024"            , &wgt_var_th_MUR1_MUF1_PDF261024    , &b_wgt_var_th_MUR1_MUF1_PDF261024    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261025:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261025"            , &wgt_var_th_MUR1_MUF1_PDF261025    , &b_wgt_var_th_MUR1_MUF1_PDF261025    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261026:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261026"            , &wgt_var_th_MUR1_MUF1_PDF261026    , &b_wgt_var_th_MUR1_MUF1_PDF261026    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261027:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261027"            , &wgt_var_th_MUR1_MUF1_PDF261027    , &b_wgt_var_th_MUR1_MUF1_PDF261027    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261028:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261028"            , &wgt_var_th_MUR1_MUF1_PDF261028    , &b_wgt_var_th_MUR1_MUF1_PDF261028    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261029:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261029"            , &wgt_var_th_MUR1_MUF1_PDF261029    , &b_wgt_var_th_MUR1_MUF1_PDF261029    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261030:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261030"            , &wgt_var_th_MUR1_MUF1_PDF261030    , &b_wgt_var_th_MUR1_MUF1_PDF261030    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261031:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261031"            , &wgt_var_th_MUR1_MUF1_PDF261031    , &b_wgt_var_th_MUR1_MUF1_PDF261031    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261032:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261032"            , &wgt_var_th_MUR1_MUF1_PDF261032    , &b_wgt_var_th_MUR1_MUF1_PDF261032    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261033:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261033"            , &wgt_var_th_MUR1_MUF1_PDF261033    , &b_wgt_var_th_MUR1_MUF1_PDF261033    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261034:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261034"            , &wgt_var_th_MUR1_MUF1_PDF261034    , &b_wgt_var_th_MUR1_MUF1_PDF261034    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261035:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261035"            , &wgt_var_th_MUR1_MUF1_PDF261035    , &b_wgt_var_th_MUR1_MUF1_PDF261035    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261036:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261036"            , &wgt_var_th_MUR1_MUF1_PDF261036    , &b_wgt_var_th_MUR1_MUF1_PDF261036    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261037:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261037"            , &wgt_var_th_MUR1_MUF1_PDF261037    , &b_wgt_var_th_MUR1_MUF1_PDF261037    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261038:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261038"            , &wgt_var_th_MUR1_MUF1_PDF261038    , &b_wgt_var_th_MUR1_MUF1_PDF261038    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261039:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261039"            , &wgt_var_th_MUR1_MUF1_PDF261039    , &b_wgt_var_th_MUR1_MUF1_PDF261039    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261040:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261040"            , &wgt_var_th_MUR1_MUF1_PDF261040    , &b_wgt_var_th_MUR1_MUF1_PDF261040    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261041:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261041"            , &wgt_var_th_MUR1_MUF1_PDF261041    , &b_wgt_var_th_MUR1_MUF1_PDF261041    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261042:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261042"            , &wgt_var_th_MUR1_MUF1_PDF261042    , &b_wgt_var_th_MUR1_MUF1_PDF261042    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261043:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261043"            , &wgt_var_th_MUR1_MUF1_PDF261043    , &b_wgt_var_th_MUR1_MUF1_PDF261043    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261044:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261044"            , &wgt_var_th_MUR1_MUF1_PDF261044    , &b_wgt_var_th_MUR1_MUF1_PDF261044    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261045:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261045"            , &wgt_var_th_MUR1_MUF1_PDF261045    , &b_wgt_var_th_MUR1_MUF1_PDF261045    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261046:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261046"            , &wgt_var_th_MUR1_MUF1_PDF261046    , &b_wgt_var_th_MUR1_MUF1_PDF261046    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261047:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261047"            , &wgt_var_th_MUR1_MUF1_PDF261047    , &b_wgt_var_th_MUR1_MUF1_PDF261047    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261048:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261048"            , &wgt_var_th_MUR1_MUF1_PDF261048    , &b_wgt_var_th_MUR1_MUF1_PDF261048    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261049:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261049"            , &wgt_var_th_MUR1_MUF1_PDF261049    , &b_wgt_var_th_MUR1_MUF1_PDF261049    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261050:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261050"            , &wgt_var_th_MUR1_MUF1_PDF261050    , &b_wgt_var_th_MUR1_MUF1_PDF261050    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261051:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261051"            , &wgt_var_th_MUR1_MUF1_PDF261051    , &b_wgt_var_th_MUR1_MUF1_PDF261051    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261052:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261052"            , &wgt_var_th_MUR1_MUF1_PDF261052    , &b_wgt_var_th_MUR1_MUF1_PDF261052    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261053:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261053"            , &wgt_var_th_MUR1_MUF1_PDF261053    , &b_wgt_var_th_MUR1_MUF1_PDF261053    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261054:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261054"            , &wgt_var_th_MUR1_MUF1_PDF261054    , &b_wgt_var_th_MUR1_MUF1_PDF261054    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261055:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261055"            , &wgt_var_th_MUR1_MUF1_PDF261055    , &b_wgt_var_th_MUR1_MUF1_PDF261055    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261056:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261056"            , &wgt_var_th_MUR1_MUF1_PDF261056    , &b_wgt_var_th_MUR1_MUF1_PDF261056    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261057:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261057"            , &wgt_var_th_MUR1_MUF1_PDF261057    , &b_wgt_var_th_MUR1_MUF1_PDF261057    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261058:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261058"            , &wgt_var_th_MUR1_MUF1_PDF261058    , &b_wgt_var_th_MUR1_MUF1_PDF261058    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261059:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261059"            , &wgt_var_th_MUR1_MUF1_PDF261059    , &b_wgt_var_th_MUR1_MUF1_PDF261059    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261060:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261060"            , &wgt_var_th_MUR1_MUF1_PDF261060    , &b_wgt_var_th_MUR1_MUF1_PDF261060    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261061:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261061"            , &wgt_var_th_MUR1_MUF1_PDF261061    , &b_wgt_var_th_MUR1_MUF1_PDF261061    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261062:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261062"            , &wgt_var_th_MUR1_MUF1_PDF261062    , &b_wgt_var_th_MUR1_MUF1_PDF261062    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261063:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261063"            , &wgt_var_th_MUR1_MUF1_PDF261063    , &b_wgt_var_th_MUR1_MUF1_PDF261063    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261064:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261064"            , &wgt_var_th_MUR1_MUF1_PDF261064    , &b_wgt_var_th_MUR1_MUF1_PDF261064    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261065:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261065"            , &wgt_var_th_MUR1_MUF1_PDF261065    , &b_wgt_var_th_MUR1_MUF1_PDF261065    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261066:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261066"            , &wgt_var_th_MUR1_MUF1_PDF261066    , &b_wgt_var_th_MUR1_MUF1_PDF261066    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261067:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261067"            , &wgt_var_th_MUR1_MUF1_PDF261067    , &b_wgt_var_th_MUR1_MUF1_PDF261067    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261068:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261068"            , &wgt_var_th_MUR1_MUF1_PDF261068    , &b_wgt_var_th_MUR1_MUF1_PDF261068    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261069:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261069"            , &wgt_var_th_MUR1_MUF1_PDF261069    , &b_wgt_var_th_MUR1_MUF1_PDF261069    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261070:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261070"            , &wgt_var_th_MUR1_MUF1_PDF261070    , &b_wgt_var_th_MUR1_MUF1_PDF261070    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261071:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261071"            , &wgt_var_th_MUR1_MUF1_PDF261071    , &b_wgt_var_th_MUR1_MUF1_PDF261071    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261072:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261072"            , &wgt_var_th_MUR1_MUF1_PDF261072    , &b_wgt_var_th_MUR1_MUF1_PDF261072    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261073:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261073"            , &wgt_var_th_MUR1_MUF1_PDF261073    , &b_wgt_var_th_MUR1_MUF1_PDF261073    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261074:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261074"            , &wgt_var_th_MUR1_MUF1_PDF261074    , &b_wgt_var_th_MUR1_MUF1_PDF261074    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261075:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261075"            , &wgt_var_th_MUR1_MUF1_PDF261075    , &b_wgt_var_th_MUR1_MUF1_PDF261075    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261076:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261076"            , &wgt_var_th_MUR1_MUF1_PDF261076    , &b_wgt_var_th_MUR1_MUF1_PDF261076    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261077:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261077"            , &wgt_var_th_MUR1_MUF1_PDF261077    , &b_wgt_var_th_MUR1_MUF1_PDF261077    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261078:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261078"            , &wgt_var_th_MUR1_MUF1_PDF261078    , &b_wgt_var_th_MUR1_MUF1_PDF261078    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261079:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261079"            , &wgt_var_th_MUR1_MUF1_PDF261079    , &b_wgt_var_th_MUR1_MUF1_PDF261079    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261080:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261080"            , &wgt_var_th_MUR1_MUF1_PDF261080    , &b_wgt_var_th_MUR1_MUF1_PDF261080    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261081:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261081"            , &wgt_var_th_MUR1_MUF1_PDF261081    , &b_wgt_var_th_MUR1_MUF1_PDF261081    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261082:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261082"            , &wgt_var_th_MUR1_MUF1_PDF261082    , &b_wgt_var_th_MUR1_MUF1_PDF261082    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261083:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261083"            , &wgt_var_th_MUR1_MUF1_PDF261083    , &b_wgt_var_th_MUR1_MUF1_PDF261083    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261084:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261084"            , &wgt_var_th_MUR1_MUF1_PDF261084    , &b_wgt_var_th_MUR1_MUF1_PDF261084    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261085:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261085"            , &wgt_var_th_MUR1_MUF1_PDF261085    , &b_wgt_var_th_MUR1_MUF1_PDF261085    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261086:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261086"            , &wgt_var_th_MUR1_MUF1_PDF261086    , &b_wgt_var_th_MUR1_MUF1_PDF261086    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261087:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261087"            , &wgt_var_th_MUR1_MUF1_PDF261087    , &b_wgt_var_th_MUR1_MUF1_PDF261087    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261088:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261088"            , &wgt_var_th_MUR1_MUF1_PDF261088    , &b_wgt_var_th_MUR1_MUF1_PDF261088    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261089:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261089"            , &wgt_var_th_MUR1_MUF1_PDF261089    , &b_wgt_var_th_MUR1_MUF1_PDF261089    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261090:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261090"            , &wgt_var_th_MUR1_MUF1_PDF261090    , &b_wgt_var_th_MUR1_MUF1_PDF261090    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261091:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261091"            , &wgt_var_th_MUR1_MUF1_PDF261091    , &b_wgt_var_th_MUR1_MUF1_PDF261091    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261092:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261092"            , &wgt_var_th_MUR1_MUF1_PDF261092    , &b_wgt_var_th_MUR1_MUF1_PDF261092    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261093:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261093"            , &wgt_var_th_MUR1_MUF1_PDF261093    , &b_wgt_var_th_MUR1_MUF1_PDF261093    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261094:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261094"            , &wgt_var_th_MUR1_MUF1_PDF261094    , &b_wgt_var_th_MUR1_MUF1_PDF261094    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261095:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261095"            , &wgt_var_th_MUR1_MUF1_PDF261095    , &b_wgt_var_th_MUR1_MUF1_PDF261095    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261096:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261096"            , &wgt_var_th_MUR1_MUF1_PDF261096    , &b_wgt_var_th_MUR1_MUF1_PDF261096    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261097:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261097"            , &wgt_var_th_MUR1_MUF1_PDF261097    , &b_wgt_var_th_MUR1_MUF1_PDF261097    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261098:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261098"            , &wgt_var_th_MUR1_MUF1_PDF261098    , &b_wgt_var_th_MUR1_MUF1_PDF261098    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261099:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261099"            , &wgt_var_th_MUR1_MUF1_PDF261099    , &b_wgt_var_th_MUR1_MUF1_PDF261099    ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261100:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF1_PDF261100"            , &wgt_var_th_MUR1_MUF1_PDF261100    , &b_wgt_var_th_MUR1_MUF1_PDF261100    ); break;
  case Syst::VAR_TH_qqZZ_MUR0p5_MUF0p5_PDF261000:
    m_Chain->SetBranchAddress("weight_var_th_MUR0p5_MUF0p5_PDF261000"        , &wgt_var_th_MUR0p5_MUF0p5_PDF261000, &b_wgt_var_th_MUR0p5_MUF0p5_PDF261000); break;
  case Syst::VAR_TH_qqZZ_MUR0p5_MUF1_PDF261000:
    m_Chain->SetBranchAddress("weight_var_th_MUR0p5_MUF1_PDF261000"          , &wgt_var_th_MUR0p5_MUF1_PDF261000  , &b_wgt_var_th_MUR0p5_MUF1_PDF261000  ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF0p5_PDF261000:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF0p5_PDF261000"          , &wgt_var_th_MUR1_MUF0p5_PDF261000  , &b_wgt_var_th_MUR1_MUF0p5_PDF261000  ); break;
  case Syst::VAR_TH_qqZZ_MUR1_MUF2_PDF261000:
    m_Chain->SetBranchAddress("weight_var_th_MUR1_MUF2_PDF261000"            , &wgt_var_th_MUR1_MUF2_PDF261000    , &b_wgt_var_th_MUR1_MUF2_PDF261000    ); break;
  case Syst::VAR_TH_qqZZ_MUR2_MUF1_PDF261000:
    m_Chain->SetBranchAddress("weight_var_th_MUR2_MUF1_PDF261000"            , &wgt_var_th_MUR2_MUF1_PDF261000    , &b_wgt_var_th_MUR2_MUF1_PDF261000    ); break;
  case Syst::VAR_TH_qqZZ_MUR2_MUF2_PDF261000:
    m_Chain->SetBranchAddress("weight_var_th_MUR2_MUF2_PDF261000"            , &wgt_var_th_MUR2_MUF2_PDF261000    , &b_wgt_var_th_MUR2_MUF2_PDF261000    ); break;
  default:
    PRINT_VERBOSE("<EventLoop::SetRecoChainBranches()>:: no additional weights to load ...");
    
  }
  
}

void EventLoop::SetTruthChainBranches(){

  PRINT_DEBUG("<EventLoop::SetTruthChainBranches()>:: setting branches for truth chain ...");

  jet_pt_fidBorn = 0; jet_eta_fidBorn = 0; jet_phi_fidBorn = 0; jet_m_fidBorn = 0;
  jet_pt_fidDres = 0; jet_eta_fidDres = 0; jet_phi_fidDres = 0; jet_m_fidDres = 0;
  jet_pt_truth   = 0; jet_eta_truth   = 0; jet_phi_truth   = 0; jet_m_truth   = 0;
  
  m_ThChain->SetBranchAddress("event"			     , &thevent            , &b_thevent          );
  m_ThChain->SetBranchAddress("run"			     , &thrun              , &b_thrun            );
  m_ThChain->SetBranchAddress("weight"		             , &thweight           , &b_thweight         );
  m_ThChain->SetBranchAddress("w_lumi"		             , &w_thlumi           , &b_w_thlumi         );
  m_ThChain->SetBranchAddress("w_MCw"                        , &w_thMCw            , &b_w_thMCw          );
  m_ThChain->SetBranchAddress("w_xs"                         , &w_thxs             , &b_w_thxs           );
  m_ThChain->SetBranchAddress("event_type_fidBorn_4lsel"     , &thevtType_fidBorn  , &b_thevtType_fidBorn);
  m_ThChain->SetBranchAddress("event_type_fidDres_4lsel"     , &thevtType_fidDres  , &b_thevtType_fidDres);
  m_ThChain->SetBranchAddress("event_type_fidBorn_truth"     , &thevtType_truth    , &b_thevtType_truth  );
  m_ThChain->SetBranchAddress("n_jets_fidBorn_4lsel"         , &njet_fidBorn       , &b_njet_fidBorn     );
  m_ThChain->SetBranchAddress("n_jets_fidDres_4lsel"         , &njet_fidDres       , &b_njet_fidDres     );
  m_ThChain->SetBranchAddress("HTXS_nJets"                   , &njet_truth         , &b_njet_truth       );
  m_ThChain->SetBranchAddress("n_bjets_fidBorn_4lsel"        , &nbjet_fidBorn      , &b_nbjet_fidBorn    );
  m_ThChain->SetBranchAddress("n_bjets_fidDres_4lsel"        , &nbjet_fidDres      , &b_nbjet_fidDres    );
  m_ThChain->SetBranchAddress("n_bjets_fidBorn_truth"        , &nbjet_truth        , &b_nbjet_truth      );
  m_ThChain->SetBranchAddress("higgs_pt_fidBorn_4lsel"       , &pt4l_fidBorn       , &b_pt4l_fidBorn     );
  m_ThChain->SetBranchAddress("higgs_pt_fidDres_4lsel"       , &pt4l_fidDres       , &b_pt4l_fidDres     );
  m_ThChain->SetBranchAddress("higgs_pt_fidBorn_truth"       , &pt4l_truth         , &b_pt4l_truth       );
  m_ThChain->SetBranchAddress("higgs_m_fidBorn_4lsel"	     , &m4l_fidBorn        , &b_m4l_fidBorn      );
  m_ThChain->SetBranchAddress("higgs_m_fidDres_4lsel"	     , &m4l_fidDres        , &b_m4l_fidDres      );
  m_ThChain->SetBranchAddress("higgs_m_fidBorn_truth"	     , &m4l_truth          , &b_m4l_truth        );
  m_ThChain->SetBranchAddress("Z1_m_fidBorn_4lsel"	     , &m12_fidBorn        , &b_m12_fidBorn      );
  m_ThChain->SetBranchAddress("Z1_m_fidDres_4lsel"	     , &m12_fidDres        , &b_m12_fidDres      );
  m_ThChain->SetBranchAddress("Z1_m_fidBorn_truth"	     , &m12_truth          , &b_m12_truth        );
  m_ThChain->SetBranchAddress("Z2_m_fidBorn_4lsel"	     , &m34_fidBorn        , &b_m34_fidBorn      );
  m_ThChain->SetBranchAddress("Z2_m_fidDres_4lsel"	     , &m34_fidDres        , &b_m34_fidDres      );
  m_ThChain->SetBranchAddress("Z2_m_fidBorn_truth"	     , &m34_truth          , &b_m34_truth        );
  m_ThChain->SetBranchAddress("higgs_y_fidBorn_4lsel"	     , &y4l_fidBorn        , &b_y4l_fidBorn      );
  m_ThChain->SetBranchAddress("higgs_y_fidDres_4lsel"	     , &y4l_fidDres        , &b_y4l_fidDres      );
  m_ThChain->SetBranchAddress("higgs_y_fidBorn_truth"	     , &y4l_truth          , &b_y4l_truth        );
  m_ThChain->SetBranchAddress("cthstr_fidBorn_4lsel"	     , &cts_fidBorn        , &b_cts_fidBorn      );
  m_ThChain->SetBranchAddress("cthstr_fidDres_4lsel"	     , &cts_fidDres        , &b_cts_fidDres      );
  m_ThChain->SetBranchAddress("cthstr_fidBorn_truth"	     , &cts_truth          , &b_cts_truth        );
  m_ThChain->SetBranchAddress("cth1_fidBorn_4lsel"	     , &ct1_fidBorn	   , &b_ct1_fidBorn	 );
  m_ThChain->SetBranchAddress("cth1_fidDres_4lsel"	     , &ct1_fidDres	   , &b_ct1_fidDres	 );
  m_ThChain->SetBranchAddress("cth1_fidBorn_truth"	     , &ct1_truth          , &b_ct1_truth        );
  m_ThChain->SetBranchAddress("cth2_fidBorn_4lsel"           , &ct2_fidBorn        , &b_ct2_fidBorn      );
  m_ThChain->SetBranchAddress("cth2_fidDres_4lsel"           , &ct2_fidDres        , &b_ct2_fidDres      );
  m_ThChain->SetBranchAddress("cth2_fidBorn_truth"           , &ct2_truth          , &b_ct2_truth        );
  m_ThChain->SetBranchAddress("phi_fidBorn_4lsel"	     , &phi_fidBorn	   , &b_phi_fidBorn	 );
  m_ThChain->SetBranchAddress("phi_fidDres_4lsel"	     , &phi_fidDres	   , &b_phi_fidDres	 );
  m_ThChain->SetBranchAddress("phi_fidBorn_truth"	     , &phi_truth          , &b_phi_truth        );
  m_ThChain->SetBranchAddress("phi1_fidBorn_4lsel"           , &phi1_fidBorn       , &b_phi1_fidBorn     );
  m_ThChain->SetBranchAddress("phi1_fidDres_4lsel"           , &phi1_fidDres       , &b_phi1_fidDres     );
  m_ThChain->SetBranchAddress("phi1_fidBorn_truth"           , &phi1_truth         , &b_phi1_truth       );
  m_ThChain->SetBranchAddress("dijet_m_fidBorn_4lsel"        , &mjj_fidBorn        , &b_mjj_fidBorn      );
  m_ThChain->SetBranchAddress("dijet_m_fidDres_4lsel"        , &mjj_fidDres        , &b_mjj_fidDres      );
  m_ThChain->SetBranchAddress("HTXS_Mjj"                     , &mjj_truth          , &b_mjj_truth        );
  m_ThChain->SetBranchAddress("dijet_deltaeta_fidBorn_4lsel" , &etajj_fidBorn      , &b_etajj_fidBorn    );
  m_ThChain->SetBranchAddress("dijet_deltaeta_fidDres_4lsel" , &etajj_fidDres      , &b_etajj_fidDres    );
  m_ThChain->SetBranchAddress("HTXS_deltaEtajj"              , &etajj_truth        , &b_etajj_truth      );
  m_ThChain->SetBranchAddress("dijet_deltaphi_fidBorn_4lsel" , &phijj_fidBorn      , &b_phijj_fidBorn    );
  m_ThChain->SetBranchAddress("dijet_deltaphi_fidDres_4lsel" , &phijj_fidDres      , &b_phijj_fidDres    );
  m_ThChain->SetBranchAddress("HTXS_phijj"                   , &phijj_truth        , &b_phijj_truth      );
  m_ThChain->SetBranchAddress("jet_pt_fidBorn_4lsel"         , &jet_pt_fidBorn     , &b_jet_pt_fidBorn   );
  m_ThChain->SetBranchAddress("jet_pt_fidDres_4lsel"         , &jet_pt_fidDres     , &b_jet_pt_fidDres   );
  m_ThChain->SetBranchAddress("HTXS_jet_pt"                  , &jet_pt_truth       , &b_jet_pt_truth     );
  m_ThChain->SetBranchAddress("jet_eta_fidBorn_4lsel"        , &jet_eta_fidBorn    , &b_jet_eta_fidBorn  );
  m_ThChain->SetBranchAddress("jet_eta_fidDres_4lsel"        , &jet_eta_fidDres    , &b_jet_eta_fidDres  );
  m_ThChain->SetBranchAddress("HTXS_jet_eta"                 , &jet_eta_truth      , &b_jet_eta_truth    );
  m_ThChain->SetBranchAddress("jet_phi_fidBorn_4lsel"        , &jet_phi_fidBorn    , &b_jet_phi_fidBorn  );
  m_ThChain->SetBranchAddress("jet_phi_fidDres_4lsel"        , &jet_phi_fidDres    , &b_jet_phi_fidDres  );
  m_ThChain->SetBranchAddress("HTXS_jet_phi"                 , &jet_phi_truth      , &b_jet_phi_truth    );
  m_ThChain->SetBranchAddress("jet_m_fidBorn_4lsel"          , &jet_m_fidBorn      , &b_jet_m_fidBorn    );
  m_ThChain->SetBranchAddress("jet_m_fidDres_4lsel"          , &jet_m_fidDres      , &b_jet_m_fidDres    );
  m_ThChain->SetBranchAddress("HTXS_jet_m"                   , &jet_m_truth        , &b_jet_m_truth      );

  switch(m_SystNum){
    
  case Syst::VAR_TH_muR0p5_muF0p5_VBF:
  case Syst::VAR_TH_muR0p5_muF0p5_VH :
  case Syst::VAR_TH_muR0p5_muF0p5_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_muR0p5_muF0p5"                , &thwgt_var_th_muR0p5_muF0p5            , &b_thwgt_var_th_muR0p5_muF0p5            ); break;
  case Syst::VAR_TH_muR0p5_muF1p0_VBF:
  case Syst::VAR_TH_muR0p5_muF1p0_VH :
  case Syst::VAR_TH_muR0p5_muF1p0_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_muR0p5_muF1p0"                , &thwgt_var_th_muR0p5_muF1p0            , &b_thwgt_var_th_muR0p5_muF1p0            ); break;
  case Syst::VAR_TH_muR0p5_muF2p0_VBF:
  case Syst::VAR_TH_muR0p5_muF2p0_VH :
  case Syst::VAR_TH_muR0p5_muF2p0_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_muR0p5_muF2p0"                , &thwgt_var_th_muR0p5_muF2p0            , &b_thwgt_var_th_muR0p5_muF2p0            ); break;
  case Syst::VAR_TH_muR1p0_muF0p5_VBF:
  case Syst::VAR_TH_muR1p0_muF0p5_VH :
  case Syst::VAR_TH_muR1p0_muF0p5_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_muR1p0_muF0p5"                , &thwgt_var_th_muR1p0_muF0p5            , &b_thwgt_var_th_muR1p0_muF0p5            ); break;
  case Syst::VAR_TH_muR1p0_muF2p0_VBF:
  case Syst::VAR_TH_muR1p0_muF2p0_VH :
  case Syst::VAR_TH_muR1p0_muF2p0_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_muR1p0_muF2p0"                , &thwgt_var_th_muR1p0_muF2p0            , &b_thwgt_var_th_muR1p0_muF2p0            ); break;
  case Syst::VAR_TH_muR2p0_muF0p5_VBF:
  case Syst::VAR_TH_muR2p0_muF0p5_VH :
  case Syst::VAR_TH_muR2p0_muF0p5_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_muR2p0_muF0p5"                , &thwgt_var_th_muR2p0_muF0p5            , &b_thwgt_var_th_muR2p0_muF0p5            ); break;
  case Syst::VAR_TH_muR2p0_muF1p0_VBF:
  case Syst::VAR_TH_muR2p0_muF1p0_VH :
  case Syst::VAR_TH_muR2p0_muF1p0_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_muR2p0_muF1p0"                , &thwgt_var_th_muR2p0_muF1p0            , &b_thwgt_var_th_muR2p0_muF1p0            ); break;
  case Syst::VAR_TH_muR2p0_muF2p0_VBF:
  case Syst::VAR_TH_muR2p0_muF2p0_VH :
  case Syst::VAR_TH_muR2p0_muF2p0_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_muR2p0_muF2p0"                , &thwgt_var_th_muR2p0_muF2p0            , &b_thwgt_var_th_muR2p0_muF2p0            ); break;
  case Syst::VAR_TH_pdf_90400:
  case Syst::VAR_TH_PDF_Nominal:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90400"                    , &thwgt_var_th_pdf_90400                , &b_thwgt_var_th_pdf_90400                ); break;
  case Syst::VAR_TH_pdf_90401:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90401"                    , &thwgt_var_th_pdf_90401                , &b_thwgt_var_th_pdf_90401                ); break;
  case Syst::VAR_TH_pdf_90402:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90402"                    , &thwgt_var_th_pdf_90402                , &b_thwgt_var_th_pdf_90402                ); break;
  case Syst::VAR_TH_pdf_90403:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90403"                    , &thwgt_var_th_pdf_90403                , &b_thwgt_var_th_pdf_90403                ); break;
  case Syst::VAR_TH_pdf_90404:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90404"                    , &thwgt_var_th_pdf_90404                , &b_thwgt_var_th_pdf_90404                ); break;
  case Syst::VAR_TH_pdf_90405:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90405"                    , &thwgt_var_th_pdf_90405                , &b_thwgt_var_th_pdf_90405                ); break;
  case Syst::VAR_TH_pdf_90406:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90406"                    , &thwgt_var_th_pdf_90406                , &b_thwgt_var_th_pdf_90406                ); break;
  case Syst::VAR_TH_pdf_90407:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90407"                    , &thwgt_var_th_pdf_90407                , &b_thwgt_var_th_pdf_90407                ); break;
  case Syst::VAR_TH_pdf_90408:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90408"                    , &thwgt_var_th_pdf_90408                , &b_thwgt_var_th_pdf_90408                ); break;
  case Syst::VAR_TH_pdf_90409:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90409"                    , &thwgt_var_th_pdf_90409                , &b_thwgt_var_th_pdf_90409                ); break;
  case Syst::VAR_TH_pdf_90410:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90410"                    , &thwgt_var_th_pdf_90410                , &b_thwgt_var_th_pdf_90410                ); break;
  case Syst::VAR_TH_pdf_90411:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90411"                    , &thwgt_var_th_pdf_90411                , &b_thwgt_var_th_pdf_90411                ); break;
  case Syst::VAR_TH_pdf_90412:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90412"                    , &thwgt_var_th_pdf_90412                , &b_thwgt_var_th_pdf_90412                ); break;
  case Syst::VAR_TH_pdf_90413:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90413"                    , &thwgt_var_th_pdf_90413                , &b_thwgt_var_th_pdf_90413                ); break;
  case Syst::VAR_TH_pdf_90414:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90414"                    , &thwgt_var_th_pdf_90414                , &b_thwgt_var_th_pdf_90414                ); break;
  case Syst::VAR_TH_pdf_90415:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90415"                    , &thwgt_var_th_pdf_90415                , &b_thwgt_var_th_pdf_90415                ); break;
  case Syst::VAR_TH_pdf_90416:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90416"                    , &thwgt_var_th_pdf_90416                , &b_thwgt_var_th_pdf_90416                ); break;
  case Syst::VAR_TH_pdf_90417:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90417"                    , &thwgt_var_th_pdf_90417                , &b_thwgt_var_th_pdf_90417                ); break;
  case Syst::VAR_TH_pdf_90418:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90418"                    , &thwgt_var_th_pdf_90418                , &b_thwgt_var_th_pdf_90418                ); break;
  case Syst::VAR_TH_pdf_90419:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90419"                    , &thwgt_var_th_pdf_90419                , &b_thwgt_var_th_pdf_90419                ); break;
  case Syst::VAR_TH_pdf_90420:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90420"                    , &thwgt_var_th_pdf_90420                , &b_thwgt_var_th_pdf_90420                ); break;
  case Syst::VAR_TH_pdf_90421:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90421"                    , &thwgt_var_th_pdf_90421                , &b_thwgt_var_th_pdf_90421                ); break;
  case Syst::VAR_TH_pdf_90422:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90422"                    , &thwgt_var_th_pdf_90422                , &b_thwgt_var_th_pdf_90422                ); break;
  case Syst::VAR_TH_pdf_90423:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90423"                    , &thwgt_var_th_pdf_90423                , &b_thwgt_var_th_pdf_90423                ); break;
  case Syst::VAR_TH_pdf_90424:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90424"                    , &thwgt_var_th_pdf_90424                , &b_thwgt_var_th_pdf_90424                ); break;
  case Syst::VAR_TH_pdf_90425:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90425"                    , &thwgt_var_th_pdf_90425                , &b_thwgt_var_th_pdf_90425                ); break;
  case Syst::VAR_TH_pdf_90426:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90426"                    , &thwgt_var_th_pdf_90426                , &b_thwgt_var_th_pdf_90426                ); break;
  case Syst::VAR_TH_pdf_90427:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90427"                    , &thwgt_var_th_pdf_90427                , &b_thwgt_var_th_pdf_90427                ); break;
  case Syst::VAR_TH_pdf_90428:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90428"                    , &thwgt_var_th_pdf_90428                , &b_thwgt_var_th_pdf_90428                ); break;
  case Syst::VAR_TH_pdf_90429:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90429"                    , &thwgt_var_th_pdf_90429                , &b_thwgt_var_th_pdf_90429                ); break;
  case Syst::VAR_TH_pdf_90430:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90430"                    , &thwgt_var_th_pdf_90430                , &b_thwgt_var_th_pdf_90430                ); break;
  case Syst::VAR_TH_pdf_90431:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90431"                    , &thwgt_var_th_pdf_90431                , &b_thwgt_var_th_pdf_90431                ); break;
  case Syst::VAR_TH_pdf_90432:
    m_ThChain->SetBranchAddress("weight_var_th_pdf_90432"                    , &thwgt_var_th_pdf_90432                , &b_thwgt_var_th_pdf_90432                ); break;
  case Syst::VAR_TH_ggF_qcd_2017_pTH120:
    m_ThChain->SetBranchAddress("weight_var_th_ggF_qcd_2017_pTH120"          , &thwgt_var_th_ggF_qcd_2017_pTH120      , &b_thwgt_var_th_ggF_qcd_2017_pTH120      ); break;
  case Syst::VAR_TH_ggF_qcd_2017_pTH60:
    m_ThChain->SetBranchAddress("weight_var_th_ggF_qcd_2017_pTH60"           , &thwgt_var_th_ggF_qcd_2017_pTH60       , &b_thwgt_var_th_ggF_qcd_2017_pTH60       ); break;
  case Syst::VAR_TH_ggF_QCD_pTH_nJ0:
    m_ThChain->SetBranchAddress("weight_var_th_qcd_pTH_nJ0"                  , &thwgt_var_th_ggF_qcd_nJ0              , &b_thwgt_var_th_ggF_qcd_nJ0              ); break;
  case Syst::VAR_TH_qcd_wg1_mig01:
    m_ThChain->SetBranchAddress("weight_var_th_qcd_wg1_mig01"                , &thwgt_var_th_qcd_wg1_mig01            , &b_thwgt_var_th_qcd_wg1_mig01            ); break;
  case Syst::VAR_TH_qcd_wg1_mig12:
    m_ThChain->SetBranchAddress("weight_var_th_qcd_wg1_mig12"                , &thwgt_var_th_qcd_wg1_mig12            , &b_thwgt_var_th_qcd_wg1_mig12            ); break;
  case Syst::VAR_TH_qcd_wg1_mu:
    m_ThChain->SetBranchAddress("weight_var_th_qcd_wg1_mu"                   , &thwgt_var_th_qcd_wg1_mu               , &b_thwgt_var_th_qcd_wg1_mu               ); break;
  case Syst::VAR_TH_qcd_wg1_qm_t:
    m_ThChain->SetBranchAddress("weight_var_th_qcd_wg1_qm_t"                 , &thwgt_var_th_qcd_wg1_qm_t             , &b_thwgt_var_th_qcd_wg1_qm_t             ); break;
  case Syst::VAR_TH_qcd_wg1_res:
    m_ThChain->SetBranchAddress("weight_var_th_qcd_wg1_res"                  , &thwgt_var_th_qcd_wg1_res              , &b_thwgt_var_th_qcd_wg1_res              ); break;
  case Syst::VAR_TH_qcd_wg1_vbf2j:
    m_ThChain->SetBranchAddress("weight_var_th_qcd_wg1_vbf2j"                , &thwgt_var_th_qcd_wg1_vbf2j            , &b_thwgt_var_th_qcd_wg1_vbf2j            ); break;
  case Syst::VAR_TH_qcd_wg1_vbf3j:
    m_ThChain->SetBranchAddress("weight_var_th_qcd_wg1_vbf3j"                , &thwgt_var_th_qcd_wg1_vbf3j            , &b_thwgt_var_th_qcd_wg1_vbf3j            ); break;
  case Syst::VAR_TH_QCD_Scale_Nominal_VBF:
  case Syst::VAR_TH_QCD_Scale_Nominal_VH :
  case Syst::VAR_TH_QCD_Scale_Nominal_ttH:
    m_ThChain->SetBranchAddress("weight_var_th_nominal"                      , &thwgt_var_th_nominal                  , &b_thwgt_var_th_nominal                  ); break;
    //case Syst::VAR_TH_Shower_Herwig:
    //m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_Herwig__1up"                              , &thwgt_var_th_Herwig                       , &b_thwgt_var_th_Herwig                       ); break;
  case Syst::VAR_TH_Var3c:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_Var3c__1down"                      , &thwgt_var_th_Var3cDown                    , &b_thwgt_var_th_Var3cDown                    ); break;
  case Syst::VAR_TH_Var3c+1:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_Var3c__1up"                        , &thwgt_var_th_Var3cUp                      , &b_thwgt_var_th_Var3cUp                      ); break;
  case Syst::VAR_TH_hard:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_hard__1down"                       , &thwgt_var_th_hardLo                       , &b_thwgt_var_th_hardLo                       ); break;
  case Syst::VAR_TH_hard+1:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_hard__1up"                         , &thwgt_var_th_hardHi                       , &b_thwgt_var_th_hardHi                       ); break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_0p5:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p5_fsrmuRfac_0p5__1up"  , &thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5  , &b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5  ); break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_1p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p5_fsrmuRfac_1p0__1up"  , &thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0  , &b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0  ); break;
  case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_2p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p5_fsrmuRfac_2p0__1up"  , &thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0  , &b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0  ); break;
  case Syst::VAR_TH_isrmuRfac_0p625_fsrmuRfac_1p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p625_fsrmuRfac_1p0__1up", &thwgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0, &b_thwgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0); break;
  case Syst::VAR_TH_isrmuRfac_0p75_fsrmuRfac_1p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p75_fsrmuRfac_1p0__1up" , &thwgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0 , &b_thwgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0 ); break;
  case Syst::VAR_TH_isrmuRfac_0p875_fsrmuRfac_1p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_0p875_fsrmuRfac_1p0__1up", &thwgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0, &b_thwgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p5:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_0p5__1up"  , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5  , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5  ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p625:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_0p625__1up", &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625, &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p75:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_0p75__1up" , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75 , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75 ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p875:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_0p875__1up", &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875, &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p25:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_1p25__1up" , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25 , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25 ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p5:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_1p5__1up"  , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5  , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5  ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p75:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_1p75__1up" , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75 , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75 ); break;
  case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_2p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p0_fsrmuRfac_2p0__1up"  , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0  , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0  ); break;
  case Syst::VAR_TH_isrmuRfac_1p25_fsrmuRfac_1p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p25_fsrmuRfac_1p0__1up" , &thwgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0 , &b_thwgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0 ); break;
  case Syst::VAR_TH_isrmuRfac_1p5_fsrmuRfac_1p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p5_fsrmuRfac_1p0__1up"  , &thwgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0  , &b_thwgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0  ); break;
  case Syst::VAR_TH_isrmuRfac_1p75_fsrmuRfac_1p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_1p75_fsrmuRfac_1p0__1up" , &thwgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0 , &b_thwgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0 ); break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_0p5:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_2p0_fsrmuRfac_0p5__1up"  , &thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5  , &b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5  ); break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_1p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_2p0_fsrmuRfac_1p0__1up"  , &thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0  , &b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0  ); break;
  case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_2p0:
    m_ThChain->SetBranchAddress("weight_var_H4l_Shower_UEPS_pythia_isrmuRfac_2p0_fsrmuRfac_2p0__1up"  , &thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0  , &b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0  ); break;
    
    //case Syst::VAR_TH_Var3c:
    //  m_ThChain->SetBranchAddress("weight_var_th_Var3cDown"                    , &thwgt_var_th_Var3cDown                    , &b_thwgt_var_th_Var3cDown                    ); break;
    //case Syst::VAR_TH_Var3c+1:
    //  m_ThChain->SetBranchAddress("weight_var_th_Var3cUp"                      , &thwgt_var_th_Var3cUp                      , &b_thwgt_var_th_Var3cUp                      ); break;
    //case Syst::VAR_TH_hard:
    //  m_ThChain->SetBranchAddress("weight_var_th_hardLo"                       , &thwgt_var_th_hardLo                       , &b_thwgt_var_th_hardLo                       ); break;
    //case Syst::VAR_TH_hard+1:
    //  m_ThChain->SetBranchAddress("weight_var_th_hardHi"                       , &thwgt_var_th_hardHi                       , &b_thwgt_var_th_hardHi                       ); break;
    //case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_0p5:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=0p5_fsrmuRfac=0p5"  , &thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5  , &b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_0p5  ); break;
    //case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_1p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=0p5_fsrmuRfac=1p0"  , &thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0  , &b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_1p0  ); break;
    //case Syst::VAR_TH_isrmuRfac_0p5_fsrmuRfac_2p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=0p5_fsrmuRfac=2p0"  , &thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0  , &b_thwgt_var_th_isrmuRfac_0p5_fsrmuRfac_2p0  ); break;
    //case Syst::VAR_TH_isrmuRfac_0p625_fsrmuRfac_1p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=0p625_fsrmuRfac=1p0", &thwgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0, &b_thwgt_var_th_isrmuRfac_0p625_fsrmuRfac_1p0); break;
    //case Syst::VAR_TH_isrmuRfac_0p75_fsrmuRfac_1p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=0p75_fsrmuRfac=1p0" , &thwgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0 , &b_thwgt_var_th_isrmuRfac_0p75_fsrmuRfac_1p0 ); break;
    //case Syst::VAR_TH_isrmuRfac_0p875_fsrmuRfac_1p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=0p875_fsrmuRfac=1p0", &thwgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0, &b_thwgt_var_th_isrmuRfac_0p875_fsrmuRfac_1p0); break;
    //case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p5:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p0_fsrmuRfac=0p5"  , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5  , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p5  ); break;
    //case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p625:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p0_fsrmuRfac=0p625", &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625, &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p625); break;
    //case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p75:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p0_fsrmuRfac=0p75" , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75 , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p75 ); break;
    //case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_0p875:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p0_fsrmuRfac=0p875", &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875, &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_0p875); break;
    //case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p25:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p0_fsrmuRfac=1p25" , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25 , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p25 ); break;
    //case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p5:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p0_fsrmuRfac=1p5"  , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5  , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p5  ); break;
    //case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p75:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p0_fsrmuRfac=1p75" , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75 , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_1p75 ); break;
    //case Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_2p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p0_fsrmuRfac=2p0"  , &thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0  , &b_thwgt_var_th_isrmuRfac_1p0_fsrmuRfac_2p0  ); break;
    //case Syst::VAR_TH_isrmuRfac_1p25_fsrmuRfac_1p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p25_fsrmuRfac=1p0" , &thwgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0 , &b_thwgt_var_th_isrmuRfac_1p25_fsrmuRfac_1p0 ); break;
    //case Syst::VAR_TH_isrmuRfac_1p5_fsrmuRfac_1p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p5_fsrmuRfac=1p0"  , &thwgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0  , &b_thwgt_var_th_isrmuRfac_1p5_fsrmuRfac_1p0  ); break;
    //case Syst::VAR_TH_isrmuRfac_1p75_fsrmuRfac_1p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=1p75_fsrmuRfac=1p0" , &thwgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0 , &b_thwgt_var_th_isrmuRfac_1p75_fsrmuRfac_1p0 ); break;
    //case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_0p5:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=2p0_fsrmuRfac=0p5"  , &thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5  , &b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_0p5  ); break;
    //case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_1p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=2p0_fsrmuRfac=1p0"  , &thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0  , &b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_1p0  ); break;
    //case Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_2p0:
    //  m_ThChain->SetBranchAddress("weight_var_th_isrmuRfac=2p0_fsrmuRfac=2p0"  , &thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0  , &b_thwgt_var_th_isrmuRfac_2p0_fsrmuRfac_2p0  ); break;
  default:
    PRINT_VERBOSE("<EventLoop::SetTruthChainBranches()>:: no additional weights to load ...");
    
  }
  
  if(m_doTruthMatch && m_useRootTruthMatch){
    PRINT_DEBUG("                                       making index for reco/truth matching ...");
    m_ThChain->BuildIndex("run","event");
  }
  
}

void EventLoop::SetHistosMap(std::map< std::string,std::vector<TH1D*> > & Hmap){
  
  PRINT_DEBUG("<EventLoop::SetHistoMap()>:: setting histograms 1D map ...");
  
  m_Histos = Hmap;
  
}

void EventLoop::SetHistos2DMap(std::map< std::string,std::vector<TH2D*> > & Hmap2D){

  PRINT_DEBUG("<EventLoop::SetHisto2DMap()>:: setting histograms 2D map ...");
  
  m_Histos2D = Hmap2D;
  
}

void EventLoop::SetHistosM4lBins(std::map< std::string,std::map<short int,std::vector<TH1D*> > > & HmapBins,
				 std::map< std::string,std::map<short int,std::vector<TH1D*> > > & HmapBinsFine){

  PRINT_DEBUG("<EventLoop::SetHistoM4lMap()>:: setting m4l histograms in ",
	      "variables bins maps ..." );

  m_HistosBins     = HmapBins    ;
  m_HistosBinsFine = HmapBinsFine;
  
}

void EventLoop::SetCmaps( std::map< std::string, std::map< short int, std::vector<std::pair<double,double> > *> > & recoBorn,
			  std::map< std::string, std::map< short int, std::vector<std::pair<double,double> > *> > & recoDres,
			  std::map< std::string, std::map< short int, std::vector<std::pair<double,double> > *> > & recoBornRaw,
			  std::map< std::string, std::map< short int, std::vector<std::pair<double,double> > *> > & recoDresRaw,
			  std::map< std::string, std::vector<std::pair<double,double> > *> & recoBornInt,
			  std::map< std::string, std::vector<std::pair<double,double> > *> & recoDresInt,
			  std::map< std::string, std::vector<std::pair<double,double> > *> & recoBornRawInt,
			  std::map< std::string, std::vector<std::pair<double,double> > *> & recoDresRawInt ){
			 
  PRINT_DEBUG("<EventLoop::SetCmaps()>:: setting C maps ... ");
  
  m_RecoBornVal    = recoBorn;
  m_RecoDresVal    = recoDres;
  m_RecoBornRaw    = recoBornRaw;
  m_RecoDresRaw    = recoDresRaw;
  m_RecoBornValInt = recoBornInt;
  m_RecoDresValInt = recoDresInt;
  m_RecoBornRawInt = recoBornRawInt;
  m_RecoDresRawInt = recoDresRawInt;
  
}

void EventLoop::SetARmaps( std::map< std::string, std::map< short int, std::vector<double> *> > & born,
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
			   std::vector<double> * & integralRaw ){

  PRINT_DEBUG("<EventLoop::SetARmaps()>:: setting AR maps ... ");
  
  m_FidBornVal     = born;
  m_FidBornRaw     = bornRaw;
  m_FidBornValInt  = bornInt;
  m_FidBornRawInt  = bornRawInt;
  m_FidDresVal     = dres;
  m_FidDresRaw     = dresRaw;
  m_FidDresValInt  = dresInt;
  m_FidDresRawInt  = dresRawInt;
  m_TruthVal       = truth;
  m_TruthRaw       = truthRaw;
  m_TruthValInt    = truthInt;
  m_TruthRawInt    = truthRawInt;
  m_TruthInt       = integral;
  m_TruthIntRaw    = integralRaw;
  
}

void EventLoop::SetMtxRecoMaps(std::map< std::string, std::map< short int, std::map <short int, std::vector <double> *> > > & rspMtxBorn_Num, 
			       std::map< std::string, std::map< short int, std::map <short int, std::vector <double> *> > > & rspMtxDres_Num, 
			       std::map< std::string, std::map< short int, std::vector< double > *> > & nonFidBorn,
			       std::map< std::string, std::map< short int, std::vector< double > *> > & nonFidDres){
  
  PRINT_DEBUG("<EventLoop::SetMtxMaps()>:: setting Matrix Reco maps ... ");
  
  m_RspMtxBorn_Num   = rspMtxBorn_Num;
  m_RspMtxDres_Num   = rspMtxDres_Num;
  m_NonFidBorn	     = nonFidBorn;
  m_NonFidDres	     = nonFidDres;
  
}

void EventLoop::SetMtxTruthMaps(std::map< std::string, std::map< short int, std::vector <double> *> > & rspMtxBorn_Denom,
				std::map< std::string, std::map< short int, std::vector <double> *> > & rspMtxDres_Denom){
  
  PRINT_DEBUG("<EventLoop::SetMtxMaps()>:: setting Matrix Truth maps ... ");

  m_RspMtxBorn_Denom = rspMtxBorn_Denom;
  m_RspMtxDres_Denom = rspMtxDres_Denom;
  
}

void EventLoop::SetTruthMatchingMaps(std::map<int, std::map<ULong64_t, std::vector<short int> > > thMtc_Born,
				     std::map<int, std::map<ULong64_t, std::vector<short int> > > thMtc_Dres){
  
  PRINT_DEBUG("<EventLoop::SetTruthMatchingMaps()>:: setting truth matching maps ... ");
  
  m_thMtc_Born = thMtc_Born;
  m_thMtc_Dres = thMtc_Dres;

}
