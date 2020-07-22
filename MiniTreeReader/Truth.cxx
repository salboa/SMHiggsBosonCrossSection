#include "MakeInput.h"

void MakeInput::SetTruthChain(){

  std::string Dir="../MC_Inputs/truth";
        
  if(m_Process=="ggH"){
    //m_thchain->Add( (Dir+"/mc15_13TeV.341505.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_ZZ4lep_noTau.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root").c_str() );

  }
  else if(m_Process=="VBF"){
    //m_thchain->Add( (Dir+"/mc15_13TeV.341518.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_ZZ4lep_noTau.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root").c_str() );
  }
  else if(m_Process=="WH"){
    //m_thchain->Add( (Dir+"/mc15_13TeV.341964.Pythia8EvtGen_A14NNPDF23LO_WH125_ZZ4l.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root").c_str() );
  }
  else if(m_Process=="ZH"){
    //m_thchain->Add( (Dir+"/mc15_13TeV.341947.Pythia8EvtGen_A14NNPDF23LO_ZH125_ZZ4l.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root").c_str() );
  }
  else if(m_Process=="ttH"){
    //m_thchain->Add( (Dir+"/mc15_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l.root").c_str() );
  }
  else if(m_Process=="bbH"){
    //m_thchain->Add( (Dir+"/mc15_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau.root").c_str() );
  }
  else if(m_Process=="AllSig"){
    //m_thchain->Add( (Dir+"/mc15_13TeV.341505.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_ZZ4lep_noTau.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.341518.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_ZZ4lep_noTau.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.341964.Pythia8EvtGen_A14NNPDF23LO_WH125_ZZ4l.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.341947.Pythia8EvtGen_A14NNPDF23LO_ZH125_ZZ4l.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root").c_str() );
    //m_thchain->Add( (Dir+"/mc15_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.344235.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau.root").c_str() );
    m_thchain->Add( (Dir+"/mc15_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau.root").c_str() );
  }
		  
}

void MakeInput::SetTruthChainBranches(){

  m_thchain->SetBranchStatus( "event"                        , 1 );
  m_thchain->SetBranchStatus( "run"                          , 1 );
  m_thchain->SetBranchStatus( "Z1_m_fidDres_4lsel"           , 1 );
  m_thchain->SetBranchStatus( "Z2_m_fidDres_4lsel"           , 1 );
  m_thchain->SetBranchStatus( "n_jets_fidDres_truth"         , 1 );
  m_thchain->SetBranchStatus( "cthstr_fidDres_4lsel"         , 1 );
  m_thchain->SetBranchStatus( "leading_jet_pt_fidDres_4lsel" , 1 );
  m_thchain->SetBranchStatus( "higgs_pt_fidDres_4lsel"       , 1 );
  m_thchain->SetBranchStatus( "higgs_y_fidDres_4lsel"        , 1 );
  m_thchain->SetBranchStatus( "weight"                       , 1 );
  m_thchain->SetBranchStatus( "w_MCw"                        , 1 );
  m_thchain->SetBranchStatus( "w_lumi"                       , 1 );
  m_thchain->SetBranchStatus( "pass_fidDres_cut"             , 1 );
  m_thchain->SetBranchStatus( "dijet_deltaeta_fidDres_4lsel" , 1 );
  m_thchain->SetBranchStatus( "dijet_deltaphi_fidDres_4lsel" , 1 );
  m_thchain->SetBranchStatus( "dijet_m_fidDres_4lsel"        , 1 );
  m_thchain->SetBranchStatus( "jet_phi_fidDres_4lsel"        , 1 );
  m_thchain->SetBranchStatus( "jet_eta_fidDres_4lsel"        , 1 );
  m_thchain->SetBranchStatus( "n_bjets_fidDres_4lsel"        , 1 );
  

  m_thchain->SetBranchAddress("event"                        , &thevent             , &b_thevent            );
  m_thchain->SetBranchAddress("run"                          , &thrun               , &b_thrun              );
  m_thchain->SetBranchAddress("Z1_m_fidDres_4lsel"           , &Z1_m_fid            , &b_Z1_m_fid           );
  m_thchain->SetBranchAddress("Z2_m_fidDres_4lsel"           , &Z2_m_fid            , &b_Z2_m_fid           );
  m_thchain->SetBranchAddress("n_jets_fidDres_truth"         , &njets_fid           , &b_njets_fid          );
  m_thchain->SetBranchAddress("cthstr_fidDres_4lsel"         , &cthstr_fid          , &b_cthstr_fid         );
  m_thchain->SetBranchAddress("leading_jet_pt_fidDres_4lsel" , &leading_jet_pt_fid  , &b_leading_jet_pt_fid );
  m_thchain->SetBranchAddress("higgs_pt_fidDres_4lsel"       , &higgs_pt_fid        , &b_higgs_pt_fid       );
  m_thchain->SetBranchAddress("higgs_y_fidDres_4lsel"        , &higgs_y_fid         , &b_higgs_y_fid        );
  m_thchain->SetBranchAddress("weight"                       , &thweight            , &b_thweight           );
  m_thchain->SetBranchAddress("w_MCw"                        , &mcweight            , &b_mcweight           );
  m_thchain->SetBranchAddress("w_lumi"                       , &thlumi              , &b_thlumi             );
  m_thchain->SetBranchAddress("pass_fidDres_cut"             , &pass_fid_cut        , &b_pass_fid_cut       );
  m_thchain->SetBranchAddress("dijet_deltaeta_fidDres_4lsel" , &dijet_deltaeta_fid  , &b_dijet_deltaeta_fid );
  m_thchain->SetBranchAddress("dijet_deltaphi_fidDres_4lsel" , &dijet_deltaphi_fid  , &b_dijet_deltaphi_fid );
  m_thchain->SetBranchAddress("dijet_m_fidDres_4lsel"        , &dijet_invmass_fid   , &b_dijet_invmass_fid  );
  m_thchain->SetBranchAddress("jet_phi_fidDres_4lsel"        , &jet_phi_truth       , &b_jet_phi_truth      );
  m_thchain->SetBranchAddress("jet_eta_fidDres_4lsel"        , &jet_eta_truth       , &b_jet_eta_truth      );
  m_thchain->SetBranchAddress("n_bjets_fidDres_4lsel"        , &nbjets_fid          , &b_nbjets_fid         );
  
  if(!m_doScale)  
    m_thchain->BuildIndex("run","event");
  
}

ULong64_t MakeInput::FindTruthMatch(ULong64_t evt, Int_t run){

  Int_t m_entry = m_thchain->GetEntryNumberWithIndex(run,evt);
  if(m_verbose){
    if(m_entry>-1)
      std::cout << " Found Truth Index: " << m_entry << std::endl;
    else
      std::cout << " Truth Match not Found " << std::endl;
  }
  return m_entry;
  
}

void MakeInput::ProcessTruth(){

  /* Check for duplicates */
  std::set< std::pair<Int_t,ULong64_t> > EvtProcessed;
  EvtProcessed.clear();

  m_thchain->SetBranchStatus("*",1);
  SetTruthChainBranches();
  Int_t Nentries = (Int_t)m_thchain->GetEntries();

  if(m_debug)
    std::cout << " Starting loop on truth events = " << Nentries << std::endl;

  double total = 0;
  for(Int_t en=0; en<Nentries; en++){
    m_thchain->GetEntry(en);

    const std::pair<Int_t,ULong64_t> RunEvt = std::make_pair(thrun,thevent);
    if( EvtProcessed.insert(RunEvt).second == false ){
      if(m_debug)
	std::cout<< "Found Duplicate in sample " << m_Process
		 <<"   -> Skipping! (Run "<< thrun << " Event "<< thevent
		 <<" weight " << thweight << ")" << std::endl;
      continue;
    }
    thweight = thweight/thlumi;
    total += thweight;
    /* pt inclusive */
    for(uint i=0; i<m_pTBins.size(); i++){
      if(higgs_pt_fid>=PtRangeVec.at(i) && higgs_pt_fid<PtRangeVec.at(i+1))
	m_pTInt[i] += thweight;
    }
    /* m12 */
    for(uint i=0; i<m_m12Bins.size(); i++){
      if(Z1_m_fid>=M12RangeVec.at(i) && Z1_m_fid<M12RangeVec.at(i+1))
	m_m12Int[i] += thweight;
    }
    /* m34 */
    for(uint i=0; i<m_m34Bins.size(); i++){
      if(Z2_m_fid>=M34RangeVec.at(i) && Z2_m_fid<M34RangeVec.at(i+1))
	m_m34Int[i] += thweight;
    }
    /* y */
    for(uint i=0; i<m_yBins.size(); i++){
      if(higgs_y_fid>=RapRangeVec.at(i) && higgs_y_fid<RapRangeVec.at(i+1))
	m_yInt[i] += thweight;
    }
    /* njet */
    for(uint i=0; i<m_njetBins.size(); i++){
      if(i==m_njetBins.size()-1){
	if(njets_fid>=3)
	  m_njetInt[i] += thweight;
      }
      else{
	if(njets_fid>=NjetRangeVec.at(i) && njets_fid<NjetRangeVec.at(i+1))
	  m_njetInt[i] += thweight;
      }
    }
    /* cts */
    for(uint i=0; i<m_ctsBins.size(); i++){
      if(std::abs(cthstr_fid)>=CtsRangeVec.at(i) && std::abs(cthstr_fid)<CtsRangeVec.at(i+1))
	m_ctsInt[i] += thweight;
    }
    /* ljpt */
    for(uint i=0; i<m_ljptBins.size(); i++){
      if(leading_jet_pt_fid>=LjPtRangeVec.at(i) && leading_jet_pt_fid<LjPtRangeVec.at(i+1))
	m_ljptInt[i] += thweight;
    }
    /* pt0j */
    if(njets_fid==0){
      for(uint i=0; i<m_pT0jBins.size(); i++){
	if(higgs_pt_fid>=Pt0jRangeVec.at(i) && higgs_pt_fid<Pt0jRangeVec.at(i+1))
    	  m_pT0jInt[i] += thweight;
      }
    }
    /* pt1j */
    else if(njets_fid>=1){
      for(uint i=0; i<m_pT1jBins.size(); i++){
    	if(higgs_pt_fid>=Pt1jRangeVec.at(i) && higgs_pt_fid<Pt1jRangeVec.at(i+1))
	  m_pT1jInt[i] += thweight;
      }
    }
  }
  std::cout << " Xsec Scale Factor: Process = " << m_Process << std::endl;
  for(uint i=0; i<m_pTInt.size(); i++){
    std::cout << "pt ->  Bin" << i << " xsec SF = " << m_pTInt.at(i)/total << std::endl;
  }
  std::cout << "" << std::endl;
  for(uint i=0; i<m_m12Int.size(); i++){
    std::cout << "m12 ->  Bin" << i << " xsec SF = " << m_m12Int.at(i)/total << std::endl;
  }
  std::cout << "" << std::endl;
  for(uint i=0; i<m_m34Int.size(); i++){
    std::cout << "m34 ->  Bin" << i << " xsec SF = " << m_m34Int.at(i)/total << std::endl;
  }
  std::cout << "" << std::endl;
  for(uint i=0; i<m_yInt.size(); i++){
    std::cout << "y ->  Bin" << i << " xsec SF = " << m_yInt.at(i)/total << std::endl;
  }
  std::cout << "" << std::endl;
  for(uint i=0; i<m_njetInt.size(); i++){
    std::cout << "njet ->  Bin" << i << " xsec SF = " << m_njetInt.at(i)/total << std::endl;
  }
  std::cout << "" << std::endl;
  for(uint i=0; i<m_ctsInt.size(); i++){
    std::cout << "cts ->  Bin" << i << " xsec SF = " << m_ctsInt.at(i)/total << std::endl;
  }
  std::cout << "" << std::endl;
  for(uint i=0; i<m_ljptInt.size(); i++){
    std::cout << "ljpt ->  Bin" << i << " xsec SF = " << m_ljptInt.at(i)/total << std::endl;
  }
  std::cout << "" << std::endl;
  for(uint i=0; i<m_pT0jInt.size(); i++){
    std::cout << "pt0j ->  Bin" << i << " xsec SF = " << m_pT0jInt.at(i)/total << std::endl;
  }
  std::cout << "" << std::endl;
  for(uint i=0; i<m_pT1jInt.size(); i++){
    std::cout << "pt1j ->  Bin" << i << " xsec SF = " << m_pT1jInt.at(i)/total << std::endl;
  }

}
