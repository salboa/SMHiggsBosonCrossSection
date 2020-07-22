#include "MakeInput.h"

void MakeInput::SetInitValues(std::string Process, std::string MCtype,
			      int SysType, int Nbins, double Min,
			      double Max, bool doMatrix, bool debug){
  
  m_Process = Process;
  m_MCtype  = MCtype;
  m_SystNum = SysType;
  m_Nbins   = Nbins;
  m_Min     = Min;
  m_Max     = Max;
  m_doMtx   = doMatrix;
  m_debug   = debug;
  if(m_Process=="data") m_SystNum=Syst::NOMINAL;
  MakeSysMap();

  SanityCheck();
  
}

void MakeInput::SetChain(){

  std::string Dir="../MC_Inputs/"+m_MCtype;
  if(m_SystNum>Syst::NOMINAL && m_SystNum<Syst::PRW_DATASF__1up+1)
    Dir += "/NormSystematic";
  else if(m_SystNum>Syst::PRW_DATASF__1up)
    Dir += m_SysMap[m_SystNum];
      
  if(m_Process=="ggH"){
    //m_chain->Add( (Dir+"/mc15_13TeV.341505.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_ZZ4lep_noTau.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root").c_str() );
  }
  if(m_Process=="ggH_Powheg"){
    m_chain->Add( (Dir+"/mc15_13TeV.341505.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_ZZ4lep_noTau.root").c_str() );
  }
  else if(m_Process=="VBF"){
    //m_chain->Add( (Dir+"/mc15_13TeV.341518.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_ZZ4lep_noTau.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root").c_str() );
  }
  else if(m_Process=="WH"){
    //m_chain->Add( (Dir+"/mc15_13TeV.341964.Pythia8EvtGen_A14NNPDF23LO_WH125_ZZ4l.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root").c_str() );
  }
  else if(m_Process=="ZH"){
    //m_chain->Add( (Dir+"/mc15_13TeV.341947.Pythia8EvtGen_A14NNPDF23LO_ZH125_ZZ4l.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root").c_str() );
  }
  else if(m_Process=="ttH"){
    m_chain->Add( (Dir+"/mc15_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l.root").c_str() );
  }
  else if(m_Process=="bbH"){
    m_chain->Add( (Dir+"/mc15_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau.root").c_str() );
  }
  else if(m_Process=="AllSig"){
    //m_chain->Add( (Dir+"/mc15_13TeV.341505.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_ZZ4lep_noTau.root").c_str() );
    //m_chain->Add( (Dir+"/mc15_13TeV.341518.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_ZZ4lep_noTau.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root").c_str() );
    //m_chain->Add( (Dir+"/mc15_13TeV.341964.Pythia8EvtGen_A14NNPDF23LO_WH125_ZZ4l.root").c_str() );
    //m_chain->Add( (Dir+"/mc15_13TeV.341947.Pythia8EvtGen_A14NNPDF23LO_ZH125_ZZ4l.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau.root").c_str() );
  }
  else if(m_Process=="qqZZ"){
    if(m_powhegZZ){
      m_chain->Add( (Dir+"/mc15_13TeV.361603.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.342556.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_100_150.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.343232.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_500_13000.root").c_str() );
    }
    else{
      m_chain->Add( (Dir+"/mc15_13TeV.345107.Sherpa_221_NNPDF30NNLO_llll_m4l100_300_filt100_150.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.345108.Sherpa_221_NNPDF30NNLO_llll_m4l300.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.363490.Sherpa_221_NNPDF30NNLO_llll.root").c_str() );
    }
  }
  else if(m_Process=="ggZZ"){
    m_chain->Add( (Dir+"/mc15_13TeV.343212.Powheggg2vvPythia8EvtGen_gg_ZZ_bkg_2e2mu_13TeV.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.343213.Powheggg2vvPythia8EvtGen_gg_ZZ_bkg_4l_noTau_13TeV.root").c_str() );
  }
  else if(m_Process=="AllZZ"){
    if(m_powhegZZ){
      m_chain->Add( (Dir+"/mc15_13TeV.361603.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.342556.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_100_150.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.343232.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_500_13000.root").c_str() );
    }
    else{
      m_chain->Add( (Dir+"/mc15_13TeV.345107.Sherpa_221_NNPDF30NNLO_llll_m4l100_300_filt100_150.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.345108.Sherpa_221_NNPDF30NNLO_llll_m4l300.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.363490.Sherpa_221_NNPDF30NNLO_llll.root").c_str() );
    }
    m_chain->Add( (Dir+"/mc15_13TeV.343212.Powheggg2vvPythia8EvtGen_gg_ZZ_bkg_2e2mu_13TeV.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.343213.Powheggg2vvPythia8EvtGen_gg_ZZ_bkg_4l_noTau_13TeV.root").c_str() );
  }
  else if(m_Process=="ZZEW"){
    m_chain->Add( (Dir+"/mc15_13TeV.361072.Sherpa_CT10_lllljj_EW6.root").c_str() );
  }
  else if(m_Process=="MultiBoson"){
    m_chain->Add( (Dir+"/mc15_13TeV.361621.Sherpa_CT10_WWZ_4l2v.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.361623.Sherpa_CT10_WZZ_5l1v.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.361625.Sherpa_CT10_ZZZ_6l0v.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.361626.Sherpa_CT10_ZZZ_4l2v.root").c_str() );
    //m_chain->Add( (Dir+"/mc15_13TeV.410069.MadGraphPythia8EvtGen_A14NNPDF23LO_ttZllonshell_Np0.root").c_str() );
    //m_chain->Add( (Dir+"/mc15_13TeV.410070.MadGraphPythia8EvtGen_A14NNPDF23LO_ttZllonshell_Np1.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.410142.Sherpa_NNPDF30NNLO_ttll_mll5.root").c_str() );
    m_chain->Add( (Dir+"/mc15_13TeV.410144.Sherpa_NNPDF30NNLO_ttW.root").c_str() );
  }
  else if(m_Process=="Zjets"){
    if(m_Min==115.0 && m_Max==130.0){
      m_In = new TFile( (Dir+"/shapes_SignalRegion.root").c_str() );
    }
    else{
      m_chain->Add( (Dir+"/mc15_13TeV.344295.Sherpa_NNPDF30NNLO_Zee_4lMassFilter40GeV8GeV.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.344296.Sherpa_NNPDF30NNLO_Zmumu_4lMassFilter40GeV8GeV.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.344297.Sherpa_NNPDF30NNLO_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.344298.Sherpa_NNPDF30NNLO_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.root").c_str() );
      m_chain->Add( (Dir+"/mc15_13TeV.410009.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_dil.root").c_str() );
    }
  }
  else if(m_Process=="data"){
    m_chain->Add( (Dir+"/data_13TeV.root").c_str() );
  }
  else if(m_Process=="MG5"){
    m_chain->Add( (Dir+"/mc15_13TeV.344158.aMcAtNloPythia8EvtGen_A14NNPDF23LO_ppx0_FxFx_Np012_SM.root").c_str() );
  }
  else if(m_Process=="MG5KHvv"){
    m_chain->Add( (Dir+"/mc15_13TeV.344160.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kHvv6_cosa1p0.root").c_str() );
  }
  else if(m_Process=="MG5KAvv"){
    m_chain->Add( (Dir+"/mc15_13TeV.344163.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAvv6_cosa0p707.root").c_str() );
  }
  else if(m_Process=="MG5KAgg"){
    m_chain->Add( (Dir+"/mc15_13TeV.344167.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAgg0p5_cosa0p707.root").c_str() );
  }
  else if(m_Process=="redBkg"){
    m_In = new TFile( m_Out->GetName() );
  }
  
}

void MakeInput::SetChainBranches(){
  
  m_chain->SetBranchAddress("event_type"          , &event_type           , &b_event_type           );
  m_chain->SetBranchAddress("event"               , &event                , &b_event                );
  m_chain->SetBranchAddress("run"                 , &run                  , &b_run                  );
  m_chain->SetBranchAddress("lbn"                 , &lbn                  , &b_lbn                  );
  m_chain->SetBranchAddress("m4l_constrained"     , &m4l_constrained      , &b_m4l_constrained      );
  m_chain->SetBranchAddress("jet_pt"              , &jet_pt               , &b_jet_pt               );
  m_chain->SetBranchAddress("jet_phi"             , &jet_phi              , &b_jet_phi              );
  m_chain->SetBranchAddress("jet_eta"             , &jet_eta              , &b_jet_eta              );
  m_chain->SetBranchAddress("weight"              , &weight               , &b_weight               );
  m_chain->SetBranchAddress("pass_vtx4lCut"       , &pass_vtx4lCut        , &b_pass_vtx4lCut        );
  m_chain->SetBranchAddress("n_jets"              , &n_jets               , &b_n_jets               );
  m_chain->SetBranchAddress("n_jets_btag70"       , &n_jets_btag70        , &b_n_jets_btag70        );
  m_chain->SetBranchAddress("cand_index"          , &cand_index           , &b_cand_index           );
  m_chain->SetBranchAddress("dijet_deltaeta"      , &dijet_deltaeta       , &b_dijet_deltaeta       );
  m_chain->SetBranchAddress("dijet_invmass"       , &dijet_invmass        , &b_dijet_invmass        );
  m_chain->SetBranchAddress("dijet_deltaphi"      , &dijet_deltaphi       , &b_dijet_deltaphi       );
  /* Uncostrained variables */
  m_chain->SetBranchAddress("pt4l_unconstrained"  , &pt4l_unconstrained   , &b_pt4l_unconstrained   );
  m_chain->SetBranchAddress("mZ1_unconstrained"   , &mZ1_unconstrained    , &b_mZ1_unconstrained    );
  m_chain->SetBranchAddress("mZ2_unconstrained"   , &mZ2_unconstrained    , &b_mZ2_unconstrained    );
  m_chain->SetBranchAddress("y4l_unconstrained"   , &y4l_unconstrained    , &b_y4l_unconstrained    );
  m_chain->SetBranchAddress("cthstr"              , &cthstr_unconstrained , &b_cthstr_unconstrained );
  /* FSR variables */
  m_chain->SetBranchAddress("m4l_fsr"             , &m4l_Fsr              , &b_m4l_Fsr              );
  m_chain->SetBranchAddress("pt4l_fsr"            , &pt4l_fsr             , &b_pt4l_fsr             );
  m_chain->SetBranchAddress("mZ1_fsr"             , &mZ1_fsr              , &b_mZ1_fsr              );
  m_chain->SetBranchAddress("mZ2_fsr"             , &mZ2_fsr              , &b_mZ2_fsr              );
  m_chain->SetBranchAddress("y4l_fsr"             , &y4l_fsr              , &b_y4l_fsr              );
  m_chain->SetBranchAddress("cthstr_fsr"          , &cthstr_fsr           , &b_cthstr_fsr           );
  if(m_Process!="data"){
    m_chain->SetBranchAddress("w_lumi"            , &lumi          , &b_lumi  );
    m_chain->SetBranchAddress("w_xs"              , &w_xs          , &b_w_xs  );
  }
  
  if(m_SystNum>Syst::NOMINAL && m_SystNum<Syst::PRW_DATASF__1up+1){
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP0__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP0__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP0__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP0__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP0__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP0__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP1__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP1__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP1__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP1__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP1__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP1__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP10__1down",
			      &weight_EL_EFF_ID_CorrUncertaintyNP10__1down , &b_weight_EL_EFF_ID_CorrUncertaintyNP10__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP10__1up"  ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP10__1up   , &b_weight_EL_EFF_ID_CorrUncertaintyNP10__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP11__1down",
			      &weight_EL_EFF_ID_CorrUncertaintyNP11__1down , &b_weight_EL_EFF_ID_CorrUncertaintyNP11__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP11__1up"  ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP11__1up   , &b_weight_EL_EFF_ID_CorrUncertaintyNP11__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP12__1down",
			      &weight_EL_EFF_ID_CorrUncertaintyNP12__1down , &b_weight_EL_EFF_ID_CorrUncertaintyNP12__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP12__1up"  ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP12__1up   , &b_weight_EL_EFF_ID_CorrUncertaintyNP12__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP13__1down",
			      &weight_EL_EFF_ID_CorrUncertaintyNP13__1down , &b_weight_EL_EFF_ID_CorrUncertaintyNP13__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP13__1up"  ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP13__1up   , &b_weight_EL_EFF_ID_CorrUncertaintyNP13__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP14__1down",
			      &weight_EL_EFF_ID_CorrUncertaintyNP14__1down , &b_weight_EL_EFF_ID_CorrUncertaintyNP14__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP14__1up"  ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP14__1up   , &b_weight_EL_EFF_ID_CorrUncertaintyNP14__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP2__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP2__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP2__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP2__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP2__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP2__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP3__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP3__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP3__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP3__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP3__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP3__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP4__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP4__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP4__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP4__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP4__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP4__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP5__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP5__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP5__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP5__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP5__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP5__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP6__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP6__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP6__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP6__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP6__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP6__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP7__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP7__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP7__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP7__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP7__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP7__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP8__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP8__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP8__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP8__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP8__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP8__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP9__1down" ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP9__1down  , &b_weight_EL_EFF_ID_CorrUncertaintyNP9__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_CorrUncertaintyNP9__1up"   ,
			      &weight_EL_EFF_ID_CorrUncertaintyNP9__1up    , &b_weight_EL_EFF_ID_CorrUncertaintyNP9__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down",
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up"  ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up   , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down",
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up"  ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up   , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down",
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up"  ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up   , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down",
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up"  ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up   , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down",
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up"  ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up   , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down",
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down);
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up"  ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up   , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up  );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down" ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down  , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up"   ,
			      &weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up    , &b_weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up   );
    m_chain->SetBranchAddress("weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down"  ,
			      &weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down   , &b_weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down  );
    m_chain->SetBranchAddress("weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"    ,
			      &weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up     , &b_weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up    );
    m_chain->SetBranchAddress("weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down" ,
			      &weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down  , &b_weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down );
    m_chain->SetBranchAddress("weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up"   ,
			      &weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up    , &b_weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up   );
    m_chain->SetBranchAddress("weight_HOEW_QCD_syst__1down"       , &weight_HOEW_QCD_syst__1down       , &b_weight_HOEW_QCD_syst__1down       );
    m_chain->SetBranchAddress("weight_HOEW_QCD_syst__1up"         , &weight_HOEW_QCD_syst__1up         , &b_weight_HOEW_QCD_syst__1up         );
    m_chain->SetBranchAddress("weight_HOEW_syst__1down"           , &weight_HOEW_syst__1down           , &b_weight_HOEW_syst__1down           );
    m_chain->SetBranchAddress("weight_HOEW_syst__1up"             , &weight_HOEW_syst__1up             , &b_weight_HOEW_syst__1up             );
    m_chain->SetBranchAddress("weight_HOQCD_scale_syst__1down"    , &weight_HOQCD_scale_syst__1down    , &b_weight_HOQCD_scale_syst__1down    );
    m_chain->SetBranchAddress("weight_HOQCD_scale_syst__1up"      , &weight_HOQCD_scale_syst__1up      , &b_weight_HOQCD_scale_syst__1up      );
    m_chain->SetBranchAddress("weight_JvtEfficiencyDown"          , &weight_JvtEfficiencyDown          , &b_weight_JvtEfficiencyDown          );
    m_chain->SetBranchAddress("weight_JvtEfficiencyUp"            , &weight_JvtEfficiencyUp            , &b_weight_JvtEfficiencyUp            );
    m_chain->SetBranchAddress("weight_MUON_EFF_STAT__1down"       , &weight_MUON_EFF_STAT__1down       , &b_weight_MUON_EFF_STAT__1down       );
    m_chain->SetBranchAddress("weight_MUON_EFF_STAT__1up"         , &weight_MUON_EFF_STAT__1up         , &b_weight_MUON_EFF_STAT__1up         );
    m_chain->SetBranchAddress("weight_MUON_EFF_STAT_LOWPT__1down" , &weight_MUON_EFF_STAT_LOWPT__1down , &b_weight_MUON_EFF_STAT_LOWPT__1down );
    m_chain->SetBranchAddress("weight_MUON_EFF_STAT_LOWPT__1up"   , &weight_MUON_EFF_STAT_LOWPT__1up   , &b_weight_MUON_EFF_STAT_LOWPT__1up   );
    m_chain->SetBranchAddress("weight_MUON_EFF_SYS__1down"        , &weight_MUON_EFF_SYS__1down        , &b_weight_MUON_EFF_SYS__1down        );
    m_chain->SetBranchAddress("weight_MUON_EFF_SYS__1up"          , &weight_MUON_EFF_SYS__1up          , &b_weight_MUON_EFF_SYS__1up          );
    m_chain->SetBranchAddress("weight_MUON_EFF_SYS_LOWPT__1down"  , &weight_MUON_EFF_SYS_LOWPT__1down  , &b_weight_MUON_EFF_SYS_LOWPT__1down  );
    m_chain->SetBranchAddress("weight_MUON_EFF_SYS_LOWPT__1up"    , &weight_MUON_EFF_SYS_LOWPT__1up    , &b_weight_MUON_EFF_SYS_LOWPT__1up    );
    m_chain->SetBranchAddress("weight_MUON_ISO_STAT__1down"       , &weight_MUON_ISO_STAT__1down       , &b_weight_MUON_ISO_STAT__1down       );
    m_chain->SetBranchAddress("weight_MUON_ISO_STAT__1up"         , &weight_MUON_ISO_STAT__1up         , &b_weight_MUON_ISO_STAT__1up         );
    m_chain->SetBranchAddress("weight_MUON_ISO_SYS__1down"        , &weight_MUON_ISO_SYS__1down        , &b_weight_MUON_ISO_SYS__1down        );
    m_chain->SetBranchAddress("weight_MUON_ISO_SYS__1up"          , &weight_MUON_ISO_SYS__1up          , &b_weight_MUON_ISO_SYS__1up          );
    m_chain->SetBranchAddress("weight_MUON_TTVA_STAT__1down"      , &weight_MUON_TTVA_STAT__1down      , &b_weight_MUON_TTVA_STAT__1down      );
    m_chain->SetBranchAddress("weight_MUON_TTVA_STAT__1up"        , &weight_MUON_TTVA_STAT__1up        , &b_weight_MUON_TTVA_STAT__1up        );
    m_chain->SetBranchAddress("weight_MUON_TTVA_SYS__1down"       , &weight_MUON_TTVA_SYS__1down       , &b_weight_MUON_TTVA_SYS__1down       );
    m_chain->SetBranchAddress("weight_MUON_TTVA_SYS__1up"         , &weight_MUON_TTVA_SYS__1up         , &b_weight_MUON_TTVA_SYS__1up         );
    m_chain->SetBranchAddress("weight_PRW_DATASF__1down"          , &weight_PRW_DATASF__1down          , &b_weight_PRW_DATASF__1down          );
    m_chain->SetBranchAddress("weight_PRW_DATASF__1up"            , &weight_PRW_DATASF__1up            , &b_weight_PRW_DATASF__1up            );
  }
  
}

void MakeInput::DefineOutFile(){

  struct stat st;
  std::string OutDir = "../varsDistro";
  if(stat(OutDir.c_str(),&st) == 0){
    std::cout << "\033[1;32m Out Directory " << OutDir << " already present!\033[0m" << std::endl;
  }
  else{
    std::cout << "\033[1;34m Creating Directory " << OutDir << " ... \033[0m" << std::endl;
    int outD = system( ("mkdir "+OutDir).c_str() );
    if(outD!=0)
      std::cout << "\033[1;31m Directory " << OutDir << " could not be created!\033[0m" << std::endl;
  }
  
  std::string OutName = OutDir+"/XsecInputs_"+std::to_string(m_Nbins)+"bin";
  if(m_SystNum>Syst::NOMINAL) OutName += "_Systematics";
  if(m_doShiftUp)   OutName += "_ShiftUp";
  if(m_doShiftDown) OutName += "_ShiftDown";
  if(m_Min==80.0 && m_Max==110.0)  OutName += "_LowMass";
  if(m_Min==150.0 && m_Max==360.0) OutName += "_HighMass";
  
  OutName += ".root";
  if(m_Process=="ggH" && m_SystNum<2)
    m_Out = new TFile( OutName.c_str(), "RECREATE" );
  else
    m_Out = new TFile( OutName.c_str(), "UPDATE" );
  
}

double MakeInput::GetWeight(){

  double m_w = 1.;

  switch (m_SystNum){
  case Syst::NOMINAL                                           : m_w = weight                                                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP0__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP0__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP0__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP0__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP1__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP1__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP1__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP1__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP10__1down              : m_w=weight_EL_EFF_ID_CorrUncertaintyNP10__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP10__1up                : m_w=weight_EL_EFF_ID_CorrUncertaintyNP10__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP11__1down              : m_w=weight_EL_EFF_ID_CorrUncertaintyNP11__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP11__1up                : m_w=weight_EL_EFF_ID_CorrUncertaintyNP11__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP12__1down              : m_w=weight_EL_EFF_ID_CorrUncertaintyNP12__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP12__1up                : m_w=weight_EL_EFF_ID_CorrUncertaintyNP12__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP13__1down              : m_w=weight_EL_EFF_ID_CorrUncertaintyNP13__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP13__1up                : m_w=weight_EL_EFF_ID_CorrUncertaintyNP13__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP14__1down              : m_w=weight_EL_EFF_ID_CorrUncertaintyNP14__1down              ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP14__1up                : m_w=weight_EL_EFF_ID_CorrUncertaintyNP14__1up                ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP2__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP2__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP2__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP2__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP3__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP3__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP3__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP3__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP4__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP4__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP4__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP4__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP5__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP5__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP5__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP5__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP6__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP6__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP6__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP6__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP7__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP7__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP7__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP7__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP8__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP8__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP8__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP8__1up                 ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP9__1down               : m_w=weight_EL_EFF_ID_CorrUncertaintyNP9__1down               ; break;
  case Syst::EL_EFF_ID_CorrUncertaintyNP9__1up                 : m_w=weight_EL_EFF_ID_CorrUncertaintyNP9__1up                 ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up   : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up   : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up   : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up   : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up   : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up   : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up   ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up    ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down  : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down  ; break;
  case Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up    : m_w=weight_EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up    ; break;
  case Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down         : m_w=weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down         ; break;
  case Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up           : m_w=weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up           ; break;
  case Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down        : m_w=weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down        ; break;
  case Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up          : m_w=weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up          ; break;
  case Syst::HOEW_QCD_syst__1down                              : m_w=weight_HOEW_QCD_syst__1down                              ; break;
  case Syst::HOEW_QCD_syst__1up                                : m_w=weight_HOEW_QCD_syst__1up                                ; break;
  case Syst::HOEW_syst__1down                                  : m_w=weight_HOEW_syst__1down                                  ; break;
  case Syst::HOEW_syst__1up                                    : m_w=weight_HOEW_syst__1up                                    ; break;
  case Syst::HOQCD_scale_syst__1down                           : m_w=weight_HOQCD_scale_syst__1down                           ; break;
  case Syst::HOQCD_scale_syst__1up                             : m_w=weight_HOQCD_scale_syst__1up                             ; break;
  case Syst::JvtEfficiencyDown                                 : m_w=weight_JvtEfficiencyDown                                 ; break;
  case Syst::JvtEfficiencyUp                                   : m_w=weight_JvtEfficiencyUp                                   ; break;
  case Syst::MUON_EFF_STAT__1down                              : m_w=weight_MUON_EFF_STAT__1down                              ; break;
  case Syst::MUON_EFF_STAT__1up                                : m_w=weight_MUON_EFF_STAT__1up                                ; break;
  case Syst::MUON_EFF_STAT_LOWPT__1down                        : m_w=weight_MUON_EFF_STAT_LOWPT__1down                        ; break;
  case Syst::MUON_EFF_STAT_LOWPT__1up                          : m_w=weight_MUON_EFF_STAT_LOWPT__1up                          ; break;
  case Syst::MUON_EFF_SYS__1down                               : m_w=weight_MUON_EFF_SYS__1down                               ; break;
  case Syst::MUON_EFF_SYS__1up                                 : m_w=weight_MUON_EFF_SYS__1up                                 ; break;
  case Syst::MUON_EFF_SYS_LOWPT__1down                         : m_w=weight_MUON_EFF_SYS_LOWPT__1down                         ; break;
  case Syst::MUON_EFF_SYS_LOWPT__1up                           : m_w=weight_MUON_EFF_SYS_LOWPT__1up                           ; break;
  case Syst::MUON_ISO_STAT__1down                              : m_w=weight_MUON_ISO_STAT__1down                              ; break;
  case Syst::MUON_ISO_STAT__1up                                : m_w=weight_MUON_ISO_STAT__1up                                ; break;
  case Syst::MUON_ISO_SYS__1down                               : m_w=weight_MUON_ISO_SYS__1down                               ; break;
  case Syst::MUON_ISO_SYS__1up                                 : m_w=weight_MUON_ISO_SYS__1up                                 ; break;
  case Syst::MUON_TTVA_STAT__1down                             : m_w=weight_MUON_TTVA_STAT__1down                             ; break;
  case Syst::MUON_TTVA_STAT__1up                               : m_w=weight_MUON_TTVA_STAT__1up                               ; break;
  case Syst::MUON_TTVA_SYS__1down                              : m_w=weight_MUON_TTVA_SYS__1down                              ; break;
  case Syst::MUON_TTVA_SYS__1up                                : m_w=weight_MUON_TTVA_SYS__1up                                ; break;
  case Syst::PRW_DATASF__1down                                 : m_w=weight_PRW_DATASF__1down                                 ; break;
  case Syst::PRW_DATASF__1up                                   : m_w=weight_PRW_DATASF__1up                                   ; break;
  default: m_w = weight; break;
  }
  return m_w;
  
}

void MakeInput::MakeSysMap(){
  
  m_SysMap[ Syst::NOMINAL                                           ] = "Nominal"                                          ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP0__1down               ] = "EL_EFF_ID_CorrUncertaintyNP0__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP0__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP0__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP1__1down               ] = "EL_EFF_ID_CorrUncertaintyNP1__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP1__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP1__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP10__1down              ] = "EL_EFF_ID_CorrUncertaintyNP10__1down"              ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP10__1up                ] = "EL_EFF_ID_CorrUncertaintyNP10__1up"                ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP11__1down              ] = "EL_EFF_ID_CorrUncertaintyNP11__1down"              ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP11__1up                ] = "EL_EFF_ID_CorrUncertaintyNP11__1up"                ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP12__1down              ] = "EL_EFF_ID_CorrUncertaintyNP12__1down"              ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP12__1up                ] = "EL_EFF_ID_CorrUncertaintyNP12__1up"                ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP13__1down              ] = "EL_EFF_ID_CorrUncertaintyNP13__1down"              ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP13__1up                ] = "EL_EFF_ID_CorrUncertaintyNP13__1up"                ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP14__1down              ] = "EL_EFF_ID_CorrUncertaintyNP14__1down"              ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP14__1up                ] = "EL_EFF_ID_CorrUncertaintyNP14__1up"                ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP2__1down               ] = "EL_EFF_ID_CorrUncertaintyNP2__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP2__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP2__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP3__1down               ] = "EL_EFF_ID_CorrUncertaintyNP3__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP3__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP3__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP4__1down               ] = "EL_EFF_ID_CorrUncertaintyNP4__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP4__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP4__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP5__1down               ] = "EL_EFF_ID_CorrUncertaintyNP5__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP5__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP5__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP6__1down               ] = "EL_EFF_ID_CorrUncertaintyNP6__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP6__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP6__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP7__1down               ] = "EL_EFF_ID_CorrUncertaintyNP7__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP7__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP7__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP8__1down               ] = "EL_EFF_ID_CorrUncertaintyNP8__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP8__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP8__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP9__1down               ] = "EL_EFF_ID_CorrUncertaintyNP9__1down"               ;
  m_SysMap[ Syst::EL_EFF_ID_CorrUncertaintyNP9__1up                 ] = "EL_EFF_ID_CorrUncertaintyNP9__1up"                 ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP0__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP1__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1down" ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP10__1up"   ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1down" ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP11__1up"   ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1down" ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP12__1up"   ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1down" ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP13__1up"   ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1down" ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP14__1up"   ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1down" ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up   ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP15__1up"   ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP2__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP3__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP4__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP5__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP6__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP7__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP8__1up"    ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down  ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1down"  ;
  m_SysMap[ Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up    ] = "EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP9__1up"    ;
  m_SysMap[ Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down         ] = "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down"         ;
  m_SysMap[ Syst::EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up           ] = "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up"           ;
  m_SysMap[ Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down        ] = "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down"        ;
  m_SysMap[ Syst::EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up          ] = "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up"          ;
  m_SysMap[ Syst::HOEW_QCD_syst__1down                              ] = "HOEW_QCD_syst__1down"                              ;
  m_SysMap[ Syst::HOEW_QCD_syst__1up                                ] = "HOEW_QCD_syst__1up"                                ;
  m_SysMap[ Syst::HOEW_syst__1down                                  ] = "HOEW_syst__1down"                                  ;
  m_SysMap[ Syst::HOEW_syst__1up                                    ] = "HOEW_syst__1up"                                    ;
  m_SysMap[ Syst::HOQCD_scale_syst__1down                           ] = "HOQCD_scale_syst__1down"                           ;
  m_SysMap[ Syst::HOQCD_scale_syst__1up                             ] = "HOQCD_scale_syst__1up"                             ;
  m_SysMap[ Syst::JvtEfficiencyDown                                 ] = "JvtEfficiencyDown"                                 ;
  m_SysMap[ Syst::JvtEfficiencyUp                                   ] = "JvtEfficiencyUp"                                   ;
  m_SysMap[ Syst::MUON_EFF_STAT__1down                              ] = "MUON_EFF_STAT__1down"                              ;
  m_SysMap[ Syst::MUON_EFF_STAT__1up                                ] = "MUON_EFF_STAT__1up"                                ;
  m_SysMap[ Syst::MUON_EFF_STAT_LOWPT__1down                        ] = "MUON_EFF_STAT_LOWPT__1down"                        ;
  m_SysMap[ Syst::MUON_EFF_STAT_LOWPT__1up                          ] = "MUON_EFF_STAT_LOWPT__1up"                          ;
  m_SysMap[ Syst::MUON_EFF_SYS__1down                               ] = "MUON_EFF_SYS__1down"                               ;
  m_SysMap[ Syst::MUON_EFF_SYS__1up                                 ] = "MUON_EFF_SYS__1up"                                 ;
  m_SysMap[ Syst::MUON_EFF_SYS_LOWPT__1down                         ] = "MUON_EFF_SYS_LOWPT__1down"                         ;
  m_SysMap[ Syst::MUON_EFF_SYS_LOWPT__1up                           ] = "MUON_EFF_SYS_LOWPT__1up"                           ;
  m_SysMap[ Syst::MUON_ISO_STAT__1down                              ] = "MUON_ISO_STAT__1down"                              ;
  m_SysMap[ Syst::MUON_ISO_STAT__1up                                ] = "MUON_ISO_STAT__1up"                                ;
  m_SysMap[ Syst::MUON_ISO_SYS__1down                               ] = "MUON_ISO_SYS__1down"                               ;
  m_SysMap[ Syst::MUON_ISO_SYS__1up                                 ] = "MUON_ISO_SYS__1up"                                 ;
  m_SysMap[ Syst::MUON_TTVA_STAT__1down                             ] = "MUON_TTVA_STAT__1down"                             ;
  m_SysMap[ Syst::MUON_TTVA_STAT__1up                               ] = "MUON_TTVA_STAT__1up"                               ;
  m_SysMap[ Syst::MUON_TTVA_SYS__1down                              ] = "MUON_TTVA_SYS__1down"                              ;
  m_SysMap[ Syst::MUON_TTVA_SYS__1up                                ] = "MUON_TTVA_SYS__1up"                                ;
  m_SysMap[ Syst::PRW_DATASF__1down                                 ] = "PRW_DATASF__1down"                                 ;
  m_SysMap[ Syst::PRW_DATASF__1up                                   ] = "PRW_DATASF__1up"                                   ;
  m_SysMap[ Syst::EG_RESOLUTION_ALL__1down                          ] = "EG_RESOLUTION_ALL__1down"                          ;
  m_SysMap[ Syst::EG_RESOLUTION_ALL__1up			    ] = "EG_RESOLUTION_ALL__1up"			    ;
  m_SysMap[ Syst::EG_SCALE_ALLCORR__1down			    ] = "EG_SCALE_ALLCORR__1down"			    ;
  m_SysMap[ Syst::EG_SCALE_ALLCORR__1up			            ] = "EG_SCALE_ALLCORR__1up"			            ;
  m_SysMap[ Syst::EG_SCALE_E4SCINTILLATOR__1down		    ] = "EG_SCALE_E4SCINTILLATOR__1down"		    ;
  m_SysMap[ Syst::EG_SCALE_E4SCINTILLATOR__1up		            ] = "EG_SCALE_E4SCINTILLATOR__1up"		            ;
  m_SysMap[ Syst::EG_SCALE_LARCALIB_EXTRA2015PRE__1down	            ] = "EG_SCALE_LARCALIB_EXTRA2015PRE__1down"	            ;
  m_SysMap[ Syst::EG_SCALE_LARCALIB_EXTRA2015PRE__1up		    ] = "EG_SCALE_LARCALIB_EXTRA2015PRE__1up"		    ;
  m_SysMap[ Syst::EG_SCALE_LARTEMPERATURE_EXTRA2015PRE__1down	    ] = "EG_SCALE_LARTEMPERATURE_EXTRA2015PRE__1down"	    ;
  m_SysMap[ Syst::EG_SCALE_LARTEMPERATURE_EXTRA2015PRE__1up	    ] = "EG_SCALE_LARTEMPERATURE_EXTRA2015PRE__1up"	    ;
  m_SysMap[ Syst::EG_SCALE_LARTEMPERATURE_EXTRA2016PRE__1down	    ] = "EG_SCALE_LARTEMPERATURE_EXTRA2016PRE__1down"	    ;
  m_SysMap[ Syst::EG_SCALE_LARTEMPERATURE_EXTRA2016PRE__1up	    ] = "EG_SCALE_LARTEMPERATURE_EXTRA2016PRE__1up"	    ;
  m_SysMap[ Syst::JET_BJES_Response__1down			    ] = "JET_BJES_Response__1down"			    ;
  m_SysMap[ Syst::JET_BJES_Response__1up			    ] = "JET_BJES_Response__1up"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_1__1down			    ] = "JET_EffectiveNP_1__1down"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_1__1up			    ] = "JET_EffectiveNP_1__1up"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_2__1down			    ] = "JET_EffectiveNP_2__1down"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_2__1up			    ] = "JET_EffectiveNP_2__1up"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_3__1down			    ] = "JET_EffectiveNP_3__1down"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_3__1up			    ] = "JET_EffectiveNP_3__1up"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_4__1down			    ] = "JET_EffectiveNP_4__1down"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_4__1up			    ] = "JET_EffectiveNP_4__1up"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_5__1down			    ] = "JET_EffectiveNP_5__1down"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_5__1up			    ] = "JET_EffectiveNP_5__1up"			    ;
  m_SysMap[ Syst::JET_EffectiveNP_6restTerm__1down		    ] = "JET_EffectiveNP_6restTerm__1down"		    ;
  m_SysMap[ Syst::JET_EffectiveNP_6restTerm__1up		    ] = "JET_EffectiveNP_6restTerm__1up"		    ;
  m_SysMap[ Syst::JET_EtaIntercalibration_Modelling__1down	    ] = "JET_EtaIntercalibration_Modelling__1down"	    ;
  m_SysMap[ Syst::JET_EtaIntercalibration_Modelling__1up	    ] = "JET_EtaIntercalibration_Modelling__1up"	    ;
  m_SysMap[ Syst::JET_EtaIntercalibration_NonClosure__1down	    ] = "JET_EtaIntercalibration_NonClosure__1down"	    ;
  m_SysMap[ Syst::JET_EtaIntercalibration_NonClosure__1up	    ] = "JET_EtaIntercalibration_NonClosure__1up"	    ;
  m_SysMap[ Syst::JET_EtaIntercalibration_TotalStat__1down	    ] = "JET_EtaIntercalibration_TotalStat__1down"	    ;
  m_SysMap[ Syst::JET_EtaIntercalibration_TotalStat__1up	    ] = "JET_EtaIntercalibration_TotalStat__1up"	    ;
  m_SysMap[ Syst::JET_Flavor_Composition__1down		            ] = "JET_Flavor_Composition__1down"		            ;
  m_SysMap[ Syst::JET_Flavor_Composition__1up			    ] = "JET_Flavor_Composition__1up"			    ;
  m_SysMap[ Syst::JET_Flavor_Response__1down			    ] = "JET_Flavor_Response__1down"			    ;
  m_SysMap[ Syst::JET_Flavor_Response__1up			    ] = "JET_Flavor_Response__1up"			    ;
  m_SysMap[ Syst::JET_JER_SINGLE_NP__1up			    ] = "JET_JER_SINGLE_NP__1up"			    ;
  m_SysMap[ Syst::JET_Pileup_OffsetMu__1down			    ] = "JET_Pileup_OffsetMu__1down"			    ;
  m_SysMap[ Syst::JET_Pileup_OffsetMu__1up			    ] = "JET_Pileup_OffsetMu__1up"			    ;
  m_SysMap[ Syst::JET_Pileup_OffsetNPV__1down			    ] = "JET_Pileup_OffsetNPV__1down"			    ;
  m_SysMap[ Syst::JET_Pileup_OffsetNPV__1up			    ] = "JET_Pileup_OffsetNPV__1up"			    ;
  m_SysMap[ Syst::JET_Pileup_PtTerm__1down			    ] = "JET_Pileup_PtTerm__1down"			    ;
  m_SysMap[ Syst::JET_Pileup_PtTerm__1up			    ] = "JET_Pileup_PtTerm__1up"			    ;
  m_SysMap[ Syst::JET_Pileup_RhoTopology__1down		            ] = "JET_Pileup_RhoTopology__1down"		            ;
  m_SysMap[ Syst::JET_Pileup_RhoTopology__1up			    ] = "JET_Pileup_RhoTopology__1up"			    ;
  m_SysMap[ Syst::JET_PunchThrough_MC15__1down		            ] = "JET_PunchThrough_MC15__1down"		            ;
  m_SysMap[ Syst::JET_PunchThrough_MC15__1up			    ] = "JET_PunchThrough_MC15__1up"			    ;
  m_SysMap[ Syst::JET_SingleParticle_HighPt__1down		    ] = "JET_SingleParticle_HighPt__1down"		    ;
  m_SysMap[ Syst::JET_SingleParticle_HighPt__1up		    ] = "JET_SingleParticle_HighPt__1up"		    ;
  m_SysMap[ Syst::MUONS_ID__1down				    ] = "MUONS_ID__1down"				    ;
  m_SysMap[ Syst::MUONS_ID__1up				            ] = "MUONS_ID__1up"				            ;
  m_SysMap[ Syst::MUONS_MS__1down				    ] = "MUONS_MS__1down"				    ;
  m_SysMap[ Syst::MUONS_MS__1up				            ] = "MUONS_MS__1up"				            ;
  m_SysMap[ Syst::MUONS_SCALE__1down				    ] = "MUONS_SCALE__1down"				    ;
  m_SysMap[ Syst::MUONS_SCALE__1up				    ] = "MUONS_SCALE__1up"				    ;
  m_SysMap[ Syst::MUONS_TTVA__byHand_down			    ] = "MUONS_TTVA__byHand_down"			    ;
  m_SysMap[ Syst::MUONS_TTVA__byHand_up                             ] = "MUONS_TTVA__byHand_up"                             ;
  
}

void MakeInput::SanityCheck(){
  
  if( m_Process!="ggH" && m_Process!="VBF" && m_Process!="WH"  &&
      m_Process!="ZH"  && m_Process!="ttH" && m_Process!="bbH" && m_Process!="AllSig"  ){
    m_doMtx = false;
    std::cout << "\033[1;32m Disabled DoMatrix: running on Not signal Process!!! \033[0m" << std::endl;
  }
  
}

void MakeInput::SetCounters(){

  for(uint i=0; i<m_pTBins.size(); i++)
    m_pTInt.push_back(0);

  for(uint i=0; i<m_m12Bins.size(); i++)
    m_m12Int.push_back(0);

  for(uint i=0; i<m_m34Bins.size(); i++)
    m_m34Int.push_back(0);

  for(uint i=0; i<m_yBins.size(); i++)
    m_yInt.push_back(0);

  for(uint i=0; i<m_njetBins.size(); i++)
    m_njetInt.push_back(0);

  for(uint i=0; i<m_ctsBins.size(); i++)
    m_ctsInt.push_back(0);

  for(uint i=0; i<m_ljptBins.size(); i++)
    m_ljptInt.push_back(0);
    
  for(uint i=0; i<m_pT0jBins.size(); i++)
    m_pT0jInt.push_back(0);
  
  for(uint i=0; i<m_pT1jBins.size(); i++)
    m_pT1jInt.push_back(0);
  
}
