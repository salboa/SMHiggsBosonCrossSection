#include "MakeInput.h"

void MakeInput::MakeRedBkg(){

  Double_t Y4mu   = 1.25 / 36.1; //1.95090*0.55 / 36.5 ;  // 4mu 55% 2e2mu 45%
  Double_t Y4e    = 1.24 / 36.1; //1.27838      / 36.5 ;  // 4e  50% 2mu2e 50%
  Double_t Y2e2mu = 1.04 / 36.1; //1.95090*0.45 / 36.5 ;
  Double_t Y2mu2e = 1.33 / 36.1; //1.27838      / 36.5 ;
  Double_t Ytotal = 4.80 / 36.1; //4.50766      / 36.5 ;
  
  /* m4l */
  m_llmumu = (TH1F*)m_In->Get( "m4l/incl/2l2mu/h_shape_m4l_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "m4l/incl/2l2e/h_shape_m4l_incl_2l2e"   );
  m_llmumu->Rebin(2);  m_llee->Rebin(2);

  Int_t Bin115 = m_llmumu->FindBin(115);
  for(int i=0; i<15; i++){
    m_VecM[1]->SetBinContent( i+1,m_llmumu->GetBinContent(i+Bin115) );
    m_VecM[2]->SetBinContent( i+1,m_llee->GetBinContent(i+Bin115)   );
    m_VecM[3]->SetBinContent( i+1,m_llee->GetBinContent(i+Bin115)   );
    m_VecM[4]->SetBinContent( i+1,m_llmumu->GetBinContent(i+Bin115) );
  }
  m_llmumu->Delete(); m_llee->Delete();

  MergeAndNormalizePlots(m_VecM,Ytotal);
  m_VecM[1]->Scale( Y4mu   / m_VecM[1]->Integral() );
  m_VecM[2]->Scale( Y4e    / m_VecM[2]->Integral() );
  m_VecM[3]->Scale( Y2e2mu / m_VecM[3]->Integral() );
  m_VecM[4]->Scale( Y2mu2e / m_VecM[4]->Integral() );
  
  /* pt */
  m_llmumu = (TH1F*)m_In->Get( "pt4l/incl/2l2mu/h_shape_pt4l_incl_2l2mu" );;
  m_llee   = (TH1F*)m_In->Get( "pt4l/incl/2l2e/h_shape_pt4l_incl_2l2e"   );
  FillZjetsPlots(m_VecPT);
  MergeAndNormalizePlots(m_VecPT,Ytotal);
  
  /* njet */
  m_llmumu = (TH1F*)m_In->Get( "njets/incl/2l2mu/h_shape_njets_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "njets/incl/2l2e/h_shape_njets_incl_2l2e"   );
  FillZjetsPlots(m_VecNjet);
  MergeAndNormalizePlots(m_VecNjet,Ytotal);

  /* njetv2 */
  m_llmumu = (TH1F*)m_In->Get( "njets/incl/2l2mu/h_shape_njets_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "njets/incl/2l2e/h_shape_njets_incl_2l2e"   );
  FillZjetsPlots(m_VecNjetv2,"njetv2");
  MergeAndNormalizePlots(m_VecNjetv2,Ytotal);

  /* njetv3 */
  m_llmumu = (TH1F*)m_In->Get( "njets/incl/2l2mu/h_shape_njets_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "njets/incl/2l2e/h_shape_njets_incl_2l2e"   );
  FillZjetsPlots(m_VecNjetv3,"njetv3");
  MergeAndNormalizePlots(m_VecNjetv3,Ytotal);
  
  /* pt0j */
  m_llmumu = (TH1F*)m_In->Get( "pt4l/0Jet/2l2mu/h_shape_pt4l_0Jet_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "pt4l/0Jet/2l2e/h_shape_pt4l_0Jet_2l2e"   );
  FillZjetsPlots(m_VecPT0j);
  MergeAndNormalizePlots(m_VecPT0j,m_VecNjet[0]->GetBinContent(1));
  
  /* pt1j */
  m_llmumu = (TH1F*)m_In->Get( "pt4l/1Jet/2l2mu/h_shape_pt4l_1Jet_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "pt4l/1Jet/2l2e/h_shape_pt4l_1Jet_2l2e"   );
  FillZjetsPlots(m_VecPT1j);
  MergeAndNormalizePlots(m_VecPT1j,m_VecNjet[0]->GetBinContent(2));
  
  /* pt2j */
  m_llmumu = (TH1F*)m_In->Get( "pt4l/ge2Jet/2l2mu/h_shape_pt4l_ge2Jet_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "pt4l/ge2Jet/2l2e/h_shape_pt4l_ge2Jet_2l2e"   );
  FillZjetsPlots(m_VecPT2j);
  MergeAndNormalizePlots(m_VecPT2j,m_VecNjet[0]->GetBinContent(3)+m_VecNjet[0]->GetBinContent(4));
  
  /* ptpt */
  int pt0jBin = m_VecPT0j[1]->GetNbinsX();
  int pt1jBin = m_VecPT1j[1]->GetNbinsX();
  int pt2jBin = m_VecPT2j[1]->GetNbinsX();
  for(int i=0; i<pt0jBin; i++){
    m_VecPTPT[0]->SetBinContent( i+1,m_VecPT0j[0]->GetBinContent(i+1) );
    m_VecPTPT[1]->SetBinContent( i+1,m_VecPT0j[1]->GetBinContent(i+1) );
    m_VecPTPT[2]->SetBinContent( i+1,m_VecPT0j[2]->GetBinContent(i+1) );
    m_VecPTPT[3]->SetBinContent( i+1,m_VecPT0j[3]->GetBinContent(i+1) );
    m_VecPTPT[4]->SetBinContent( i+1,m_VecPT0j[4]->GetBinContent(i+1) );
  }
  for(int i=0; i<pt1jBin; i++){
    m_VecPTPT[0]->SetBinContent( pt0jBin+i+1,m_VecPT1j[0]->GetBinContent(i+1) );
    m_VecPTPT[1]->SetBinContent( pt0jBin+i+1,m_VecPT1j[1]->GetBinContent(i+1) );
    m_VecPTPT[2]->SetBinContent( pt0jBin+i+1,m_VecPT1j[2]->GetBinContent(i+1) );
    m_VecPTPT[3]->SetBinContent( pt0jBin+i+1,m_VecPT1j[3]->GetBinContent(i+1) );
    m_VecPTPT[4]->SetBinContent( pt0jBin+i+1,m_VecPT1j[4]->GetBinContent(i+1) );
  }
  for(int i=0; i<pt2jBin; i++){
    m_VecPTPT[0]->SetBinContent( pt0jBin+pt1jBin+i+1,m_VecPT1j[0]->GetBinContent(i+1) );
    m_VecPTPT[1]->SetBinContent( pt0jBin+pt1jBin+i+1,m_VecPT1j[1]->GetBinContent(i+1) );
    m_VecPTPT[2]->SetBinContent( pt0jBin+pt1jBin+i+1,m_VecPT1j[2]->GetBinContent(i+1) );
    m_VecPTPT[3]->SetBinContent( pt0jBin+pt1jBin+i+1,m_VecPT1j[3]->GetBinContent(i+1) );
    m_VecPTPT[4]->SetBinContent( pt0jBin+pt1jBin+i+1,m_VecPT1j[4]->GetBinContent(i+1) );
  }
  
  /* m34 */
  m_llmumu = (TH1F*)m_In->Get( "m34/incl/2l2mu/h_shape_m34_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "m34/incl/2l2e/h_shape_m34_incl_2l2e"   );
  FillZjetsPlots(m_VecM34);
  MergeAndNormalizePlots(m_VecM34,Ytotal);
  
  /* m12 */
  m_llmumu = (TH1F*)m_In->Get( "m12/incl/2l2mu/h_shape_m12_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "m12/incl/2l2e/h_shape_m12_incl_2l2e"   );
  FillZjetsPlots(m_VecM12);
  MergeAndNormalizePlots(m_VecM12,Ytotal);
  
  /* cts */
  m_llmumu = (TH1F*)m_In->Get( "cts/incl/2l2mu/h_shape_cts_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "cts/incl/2l2e/h_shape_cts_incl_2l2e"   );
  FillZjetsPlots(m_VecCts);
  MergeAndNormalizePlots(m_VecCts,Ytotal);
  
  
  /* nbjet */
  m_llmumu = (TH1F*)m_In->Get( "nbjets/incl/2l2mu/h_shape_nbjets_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "nbjets/incl/2l2e/h_shape_nbjets_incl_2l2e"   );
  FillZjetsPlots(m_VecNbjet);
  MergeAndNormalizePlots(m_VecNbjet,Ytotal);
  
  /* ljpt */
  m_llmumu = (TH1F*)m_In->Get( "jet1pt/ge1Jet/2l2mu/h_shape_jet1pt_ge1Jet_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "jet1pt/ge1Jet/2l2e/h_shape_jet1pt_ge1Jet_2l2e"   );
  FillZjetsPlots(m_VecJetPt);
  MergeAndNormalizePlots(m_VecJetPt,m_VecNjet[0]->GetBinContent(2)+m_VecNjet[0]->GetBinContent(3)+m_VecNjet[0]->GetBinContent(4));
  
  /* y4l */
  m_llmumu = (TH1F*)m_In->Get( "y4l/incl/2l2mu/h_shape_y4l_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "y4l/incl/2l2e/h_shape_y4l_incl_2l2e"   );
  FillZjetsPlots(m_VecY);
  MergeAndNormalizePlots(m_VecY,Ytotal);
  
  /* m12m34 */
  m_llmumu = (TH1F*)m_In->Get( "m12m34/incl/2l2mu/h_shape_m12m34_incl_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "m12m34/incl/2l2e/h_shape_m12m34_incl_2l2e"   );
  FillZjetsPlots(m_VecM12M34rm);
  MergeAndNormalizePlots(m_VecM12M34rm,Ytotal);
  
  /* mjj */
  m_llmumu = (TH1F*)m_In->Get( "mjj/ge2Jet/2l2mu/h_shape_mjj_ge2Jet_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "mjj/ge2Jet/2l2e/h_shape_mjj_ge2Jet_2l2e"   );
  FillZjetsPlots(m_VecMJJ);
  MergeAndNormalizePlots(m_VecMJJ,m_VecNjet[0]->GetBinContent(3)+m_VecNjet[0]->GetBinContent(4));

  m_llmumu = (TH1F*)m_In->Get( "mjj/ge2Jet/2l2mu/h_shape_mjj_ge2Jet_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "mjj/ge2Jet/2l2e/h_shape_mjj_ge2Jet_2l2e"   );
  FillZjetsPlots(m_VecMJJrm);
  MergeAndNormalizePlots(m_VecMJJrm,m_VecNjet[0]->GetBinContent(3)+m_VecNjet[0]->GetBinContent(4));
  
  /*etajj*/
  m_llmumu = (TH1F*)m_In->Get( "detajj/ge2Jet/2l2mu/h_shape_detajj_ge2Jet_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "detajj/ge2Jet/2l2e/h_shape_detajj_ge2Jet_2l2e"   );
  FillZjetsPlots(m_VecETAJJ);
  MergeAndNormalizePlots(m_VecETAJJ,m_VecNjet[0]->GetBinContent(3)+m_VecNjet[0]->GetBinContent(4));
  
  /* phijj */
  m_llmumu = (TH1F*)m_In->Get( "dphijj/ge2Jet/2l2mu/h_shape_dphijj_ge2Jet_2l2mu" );
  m_llee   = (TH1F*)m_In->Get( "dphijj/ge2Jet/2l2e/h_shape_dphijj_ge2Jet_2l2e"   );
  FillZjetsPlots(m_VecPHIJJ);
  MergeAndNormalizePlots(m_VecPHIJJ,m_VecNjet[0]->GetBinContent(3)+m_VecNjet[0]->GetBinContent(4));
  
  
  for(uint i=0; i<m_pTBins.size(); i++){
    m_pTBins.at(i)->Add(m_VecM[0]); m_pTBins.at(i)->Scale( m_VecPT[0]->GetBinContent(i+1)/m_pTBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_njetBins.size(); i++){
    m_njetBins.at(i)->Add(m_VecM[0]); m_njetBins.at(i)->Scale( m_VecNjet[0]->GetBinContent(i+1)/m_njetBins.at(i)->Integral());
  }

  for(uint i=0; i<m_njetBinsv2.size(); i++){
    m_njetBinsv2.at(i)->Add(m_VecM[0]); m_njetBinsv2.at(i)->Scale( m_VecNjetv2[0]->GetBinContent(i+1)/m_njetBinsv2.at(i)->Integral());
  }

  for(uint i=0; i<m_njetBinsv3.size(); i++){
    m_njetBinsv3.at(i)->Add(m_VecM[0]); m_njetBinsv3.at(i)->Scale( m_VecNjetv3[0]->GetBinContent(i+1)/m_njetBinsv3.at(i)->Integral());
  }
  
  for(uint i=0; i<m_nbjetBins.size(); i++){
    m_nbjetBins.at(i)->Add(m_VecM[0]); m_nbjetBins.at(i)->Scale( m_VecNbjet[0]->GetBinContent(i+1)/m_nbjetBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_ctsBins.size(); i++){
    m_ctsBins.at(i)->Add(m_VecM[0]); m_ctsBins.at(i)->Scale( m_VecCts[0]->GetBinContent(i+1)/m_ctsBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_ljptBins.size(); i++){
    m_ljptBins.at(i)->Add(m_VecM[0]); m_ljptBins.at(i)->Scale( m_VecJetPt[0]->GetBinContent(i+1)/m_ljptBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_pT0jBins.size(); i++){
    m_pT0jBins.at(i)->Add(m_VecM[0]); m_pT0jBins.at(i)->Scale( m_VecPT0j[0]->GetBinContent(i+1)/m_pT0jBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_pT1jBins.size(); i++){
    m_pT1jBins.at(i)->Add(m_VecM[0]); m_pT1jBins.at(i)->Scale( m_VecPT1j[0]->GetBinContent(i+1)/m_pT1jBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_pT2jBins.size(); i++){
    m_pT2jBins.at(i)->Add(m_VecM[0]); m_pT2jBins.at(i)->Scale( m_VecPT2j[0]->GetBinContent(i+1)/m_pT2jBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_pTpTBins.size(); i++){
    m_pTpTBins.at(i)->Add(m_VecM[0]); m_pTpTBins.at(i)->Scale( m_VecPTPT[0]->GetBinContent(i+1)/m_pTpTBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_mjjBins.size(); i++){
    m_mjjBins.at(i)->Add(m_VecM[0]); m_mjjBins.at(i)->Scale( m_VecMJJ[0]->GetBinContent(i+1)/m_mjjBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_etajjBins.size(); i++){
    m_etajjBins.at(i)->Add(m_VecM[0]); m_etajjBins.at(i)->Scale( m_VecETAJJ[0]->GetBinContent(i+1)/m_etajjBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_phijjBins.size(); i++){
    m_phijjBins.at(i)->Add(m_VecM[0]); m_phijjBins.at(i)->Scale( m_VecPHIJJ[0]->GetBinContent(i+1)/m_phijjBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_yBins.size(); i++){
    m_yBins.at(i)->Add(m_VecM[0]); m_yBins.at(i)->Scale( m_VecY[0]->GetBinContent(i+1)/m_yBins.at(i)->Integral());
  }
  
  for(uint i=0; i<m_yBins.size(); i++){
    m_yBins.at(i)->Add(m_VecM[0]); m_yBins.at(i)->Scale( m_VecY[0]->GetBinContent(i+1)/m_yBins.at(i)->Integral());
  }
  
}

void MakeInput::MergeRedBkg(){

  std::string names[]  = {"hm_4mu_","hpt_4mu_", "hpt0j_4mu_", "hpt1j_4mu_", "hpt2j_4mu_", "hptpt_4mu_", "hm12_4mu_", "hm34_4mu_", "hm34b_4mu_",
			  "hnjet_4mu_", "hnjetv2_4mu_", "hnjetv3_4mu_", "hnbjet_4mu_", "hy_4mu_", "hcts_4mu_", "hljpt_4mu_", "hmjj_4mu_",
			  "hmjjrm_4mu_", "hetajj_4mu_", "hphijj_4mu_", "hm12m34_4mu_",
			  
			  "hm_4e_", "hpt_4e_", "hpt0j_4e_", "hpt1j_4e_", "hpt2j_4e_", "hptpt_4e_", "hm12_4e_", "hm34_4e_", "hm34b_4e_", "hnjet_4e_",
			  "hnjetv2_4e_", "hnjetv3_4e_", "hnbjet_4e_", "hy_4e_", "hcts_4e_", "hljpt_4e_", "hmjj_4e_", "hmjjrm_4e_", "hetajj_4e_",
			  "hphijj_4e_", "hm12m34_4e_",
			  
			  "hm_2mu2e_", "hpt_2mu2e_", "hpt0j_2mu2e_", "hpt1j_2mu2e_", "hpt2j_2mu2e_", "hptpt_2mu2e_", "hm12_2mu2e_", "hm34_2mu2e_",
			  "hm34b_2mu2e_", "hnjet_2mu2e_", "hnjetv2_2mu2e_", "hnjetv3_2mu2e_", "hnbjet_2mu2e_", "hy_2mu2e_", "hcts_2mu2e_",
			  "hljpt_2mu2e_", "hmjj_2mu2e_", "hmjjrm_2mu2e_", "hetajj_2mu2e_", "hphijj_2mu2e_", "hm12m34_2mu2e_",
			  
			  "hm_2e2mu_", "hpt_2e2mu_", "hpt0j_2e2mu_", "hpt1j_2e2mu_", "hpt2j_2e2mu_", "hptpt_2e2mu_", "hm12_2e2mu_", "hm34_2e2mu_",
			  "hm34b_2e2mu_", "hnjet_2e2mu_", "hnjetv2_2e2mu_", "hnjetv3_2e2mu_", "hnbjet_2e2mu_", "hy_2e2mu_", "hcts_2e2mu_",
			  "hljpt_2e2mu_", "hmjj_2e2mu_", "hmjjrm_2e2mu_", "hetajj_2e2mu_", "hphijj_2e2mu_", "hm12m34_2e2mu_",
			  
			  "hm_incl_", "hpt_incl_", "hpt0j_incl_", "hpt1j_incl_", "hpt2j_incl_", "hptpt_incl_", "hm12_incl_", "hm34_incl_",
			  "hm34b_incl_", "hnjet_incl_", "hnjetv2_incl_", "hnjetv3_incl_", "hnbjet_incl_", "hy_incl_", "hcts_incl_", "hljpt_incl_",
			  "hmjj_incl_", "hmjjrm_incl_", "hetajj_incl_", "hphijj_incl_", "hm12m34_incl_", "hm_ptbin0_incl_", "hm_ptbin1_incl_",
			  "hm_ptbin2_incl_", "hm_ptbin3_incl_", "hm_ptbin4_incl_", "hm_ptbin5_incl_", "hm_ptbin6_incl_", "hm_ptbin7_incl_",
			  "hm_ptbin8_incl_", "hm_ptbin9_incl_", "hm_pt0jbin0_incl_", "hm_pt0jbin1_incl_", "hm_pt0jbin2_incl_", "hm_pt0jbin3_incl_",
			  "hm_pt1jbin0_incl_", "hm_pt1jbin1_incl_", "hm_pt1jbin2_incl_", "hm_pt1jbin3_incl_", "hm_pt1jbin4_incl_", "hm_pt2jbin0_incl_",
			  "hm_pt2jbin1_incl_", "hm_ctsbin0_incl_", "hm_ctsbin1_incl_", "hm_ctsbin2_incl_", "hm_ctsbin3_incl_", "hm_ctsbin4_incl_",
			  "hm_ctsbin5_incl_", "hm_ctsbin6_incl_", "hm_ctsbin7_incl_", "hm_ybin0_incl_", "hm_ybin1_incl_", "hm_ybin2_incl_",
			  "hm_ybin3_incl_", "hm_ybin4_incl_", "hm_ybin5_incl_", "hm_ybin6_incl_", "hm_m12bin0_incl_", "hm_m12bin1_incl_",
			  "hm_m12bin2_incl_", "hm_m12bin3_incl_", "hm_m12bin4_incl_", "hm_m12bin5_incl_", "hm_m34bin0_incl_", "hm_m34bin1_incl_",
			  "hm_m34bin2_incl_", "hm_m34bin3_incl_", "hm_m34bin4_incl_", "hm_m34bin5_incl_", "hm_m34bin6_incl_", "hm_njetbin0_incl_",
			  "hm_njetbin1_incl_", "hm_njetbin2_incl_", "hm_njetbin3_incl_", "hm_njetv2bin0_incl_", "hm_njetv2bin1_incl_",
			  "hm_njetv3bin0_incl_", "hm_njetv3bin1_incl_", "hm_njetv3bin2_incl_", "hm_nbjetbin0_incl_", "hm_nbjetbin1_incl_",
			  "hm_ljptbin0_incl_", "hm_ljptbin1_incl_", "hm_ljptbin2_incl_", "hm_ljptbin3_incl_", "hm_ljptbin4_incl_",
			  "hm_mjjbin0_incl_", "hm_mjjbin1_incl_", "hm_etajjbin0_incl_", "hm_etajjbin1_incl_", "hm_phijjbin0_incl_",
			  "hm_phijjbin1_incl_", "hm_ptptbin0_incl_", "hm_ptptbin1_incl_", "hm_ptptbin2_incl_", "hm_ptptbin3_incl_",
			  "hm_ptptbin4_incl_", "hm_ptptbin5_incl_", "hm_ptptbin6_incl_", "hm_ptptbin7_incl_", "hm_ptptbin8_incl_",
			  "hm_ptptbin9_incl_", "hm_ptptbin10_incl_"};

  int N = ( (sizeof names)  / (sizeof *names)  )-1;

  TH1F *hInZj=NULL, *hInMb=NULL, *hOut=NULL;
  for(int i=0; i<N; i++){
    hInZj = (TH1F*)m_In->Get( (names[i]+"Zjets").c_str() );
    hInMb = (TH1F*)m_In->Get( (names[i]+"MultiBoson").c_str() );
    hOut  = (TH1F*)hInZj->Clone( (names[i]+"redBkg").c_str() );
    hOut->SetName( (names[i]+"redBkg").c_str() );
    hOut->Add(hInMb);

    m_Out->cd();
    hOut->Write( (names[i]+"redBkg").c_str() );
    hInZj->Delete();
    hInMb->Delete();
    hOut->Delete();
  }
  
}

void MakeInput::MakeOtherProcesses(){

  /* Check for duplicates */
  std::set< std::pair<Int_t,ULong64_t> > EvtProcessed;
  EvtProcessed.clear();
  
  m_chain->SetBranchStatus("*",1);
  SetChainBranches();
  if(m_doMtx){
    m_thchain->SetBranchStatus("*",0);
    SetTruthChainBranches();
  }
    
  
  Int_t Nentries = (Int_t)m_chain->GetEntries();
  Float_t NormFact    = 1.;
  Float_t FinWgt      = 1.;
  Float_t xsec_Scale  = 1.;
  Float_t AddBbh      = 1.;

  Float_t qqZZInt = 0;
  Float_t ggZZInt = 0;

  if(m_debug)
    std::cout << " Starting loop on events = " << Nentries << std::endl;
  
  int Pos=-1;
  for(Int_t en=0; en<Nentries; en++){
    m_chain->GetEntry(en);

    AddBbh     = 1.;
    std::string curFile = m_chain->GetCurrentFile()->GetName();
    if(m_verbose) std::cout << "Processing file: " << curFile << std::endl;

    /* Add bbH to ggF - not Used anymore */
    //if(curFile.find("ggH")!=std::string::npos)
    //AddBbh  = 1.010022671;
    
    /* Check vertex cut and candidate index */
    if(pass_vtx4lCut==0) continue;
    if(cand_index>0) continue;

    const std::pair<Int_t,ULong64_t> RunEvt = std::make_pair(run,event);
    if( EvtProcessed.insert(RunEvt).second == false ){
      if(m_debug)
	std::cout<< "Found Duplicate in sample " << m_Process
		 <<"   -> Skipping! (Run "<< run << " Event "<< event
		 <<" weight " << GetWeight() << ")" << std::endl;
      continue;
    }
    if(m_verbose)
      std::cout<< "Processing sample " << m_Process <<" --> Run "<< run
	       << " Event "<< event  <<" weight " << GetWeight() << std::endl;
    
    /* --------------*/
    /*  Event Type   */
    /*  4mu    =  0  */
    /*  4e     =  1  */
    /*  2mu2e  =  2  */
    /*  2e2mu  =  3  */
    /* --------------*/

    Float_t m4l_fsr = m4l_Fsr;
    if(m_doShiftUp)
      m4l_fsr = m4l_Fsr+0.24;
    else if(m_doShiftDown)
      m4l_fsr = m4l_Fsr-0.24;
    
    /* Check mass window */
    if( m4l_fsr<m_Min || m4l_fsr>m_Max ) continue;
    
    /* Retrieve event weight */
    if(m_Process!="data")
      FinWgt      = GetWeight()*NormFact*AddBbh*xsec_Scale/lumi;
    else
      FinWgt      = 1;
    
    if(m_Process=="MG5"     || m_Process=="MG5KHvv" ||
       m_Process=="MG5KAvv" || m_Process=="MG5KAgg"  ){
      
      if(event_type == 0 || event_type == 1)
	FinWgt      = (GetWeight()*xsec_Scale/w_xs)*48600*0.00013/lumi;
      if(event_type == 2 || event_type == 3)
	FinWgt      = (GetWeight()*xsec_Scale/w_xs)*48600*0.0001180/lumi;
	
    }

    if(m_verbose)
      std::cout<< " Final Wgt = " << FinWgt << std::endl;
    
    /* evaluating qqZZ and ggZZ integrals */
    if( curFile.find("ZZllll_mll4")!=std::string::npos ){
      qqZZInt += FinWgt;
    }
    if( curFile.find("Powheggg2vvPythia")!=std::string::npos){
      ggZZInt += FinWgt;
    }
    
    /* Apply Sherpa/Powheg njet reweighting */ 
    if( curFile.find("ZZllll_mll4")!=std::string::npos ){
      if( n_jets == 0 ) FinWgt = FinWgt*0.949;
      if( n_jets == 1 ) FinWgt = FinWgt*0.977;
      if( n_jets >= 2 ) FinWgt = FinWgt*1.773;
    }

    if(m_verbose){
      std::cout << " event " << en << " m4l " << m4l_Fsr
		<< " type " << event_type << "weight " << FinWgt << std::endl;
    }

    /* evaluating dijet delta_phi */
    float dijet_phi = -99;
    if( n_jets >= 2 ){

      if(jet_eta[0]>jet_eta[1]) dijet_phi= jet_phi[0]-jet_phi[1];
      if(jet_eta[0]<jet_eta[1]) dijet_phi= jet_phi[1]-jet_phi[0];
      
      if(dijet_phi<0) dijet_phi = dijet_phi + 2*TMath::Pi();
      
    }
    
    Pos = event_type+1;
    /* no jet-category */
    m_VecM[0]     ->Fill(m4l_fsr,FinWgt);
    m_VecM12[0]   ->Fill(mZ1_fsr,FinWgt);
    m_VecM34[0]   ->Fill(mZ2_fsr,FinWgt);
    m_VecM34B[0]  ->Fill(mZ2_fsr,FinWgt);
    m_VecM12M34[0]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
    m_VecPT[0]    ->Fill(pt4l_fsr,FinWgt);
    m_VecJetPt[0] ->Fill(jet_pt[0],FinWgt);
    if(n_jets>=2 ){
      m_VecMJJ[0]   ->Fill(dijet_invmass,FinWgt);
      if(dijet_invmass<120)       m_VecMJJrm[0]->Fill(0.5,FinWgt);
      else if(dijet_invmass<3000) m_VecMJJrm[0]->Fill(2.1,FinWgt);
      m_VecETAJJ[0] ->Fill(dijet_deltaeta,FinWgt);
      m_VecPHIJJ[0] ->Fill(dijet_deltaphi,FinWgt); //dijet_phi
    }

    if (n_jets < 3) m_VecNjet[0]  ->Fill(n_jets,FinWgt);
    else m_VecNjet[0]->Fill(3,FinWgt);

    if (n_jets < 1) m_VecNjetv2[0]  ->Fill(n_jets,FinWgt);
    else m_VecNjetv2[0]->Fill(1,FinWgt);

    if (n_jets < 2) m_VecNjetv3[0]  ->Fill(n_jets,FinWgt);
    else m_VecNjetv3[0]->Fill(2,FinWgt);
    
    if (n_jets_btag70 < 1) m_VecNbjet[0]  ->Fill(n_jets_btag70,FinWgt);
    else m_VecNbjet[0]  ->Fill(1,FinWgt);
    
    m_VecY[0]     ->Fill(fabs(y4l_fsr),FinWgt);
    if( n_jets == 0) m_VecY0j[0]     ->Fill(fabs(y4l_fsr),FinWgt);
    if( n_jets >= 1) m_VecY1j[0]     ->Fill(fabs(y4l_fsr),FinWgt);
    
    m_VecCts[0]   ->Fill(fabs(cthstr_fsr),FinWgt);
    if (n_jets == 0) m_VecCts0j[0]   ->Fill(fabs(cthstr_fsr),FinWgt);
    if (n_jets >= 1) m_VecCts1j[0]   ->Fill(fabs(cthstr_fsr),FinWgt);

    if(pt4l_fsr<=60){
      m_VecMLpt[0]   ->Fill(m4l_fsr,FinWgt);
      m_VecYLpt[0]   ->Fill(fabs(y4l_fsr),FinWgt);
      m_VecCtsLpt[0] ->Fill(fabs(cthstr_fsr),FinWgt);
    }
    else{
      m_VecMHpt[0]   ->Fill(m4l_fsr,FinWgt);
      m_VecYHpt[0]   ->Fill(fabs(y4l_fsr),FinWgt);
      m_VecCtsHpt[0] ->Fill(fabs(cthstr_fsr),FinWgt);
    }
    
    m_VecM[Pos]     ->Fill(m4l_fsr,FinWgt);
    m_VecM12[Pos]   ->Fill(mZ1_fsr,FinWgt);
    m_VecM34[Pos]   ->Fill(mZ2_fsr,FinWgt);
    m_VecM34B[Pos]  ->Fill(mZ2_fsr,FinWgt);
    m_VecM12M34[Pos]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
    m_VecPT[Pos]    ->Fill(pt4l_fsr,FinWgt);
    m_VecJetPt[Pos] ->Fill(jet_pt[0],FinWgt);
    
    if (n_jets < 3) m_VecNjet[Pos]->Fill(n_jets,FinWgt);
    else m_VecNjet[Pos]->Fill(3,FinWgt);

    if (n_jets < 1) m_VecNjetv2[Pos]->Fill(n_jets,FinWgt);
    else m_VecNjetv3[Pos]->Fill(1,FinWgt);
    
    if (n_jets < 2) m_VecNjetv3[Pos]->Fill(n_jets,FinWgt);
    else m_VecNjetv3[Pos]->Fill(2,FinWgt);

    if (n_jets_btag70 < 1) m_VecNbjet[Pos]  ->Fill(n_jets_btag70,FinWgt);
    else m_VecNbjet[Pos]  ->Fill(1,FinWgt);

    m_VecY[Pos]     ->Fill(fabs(y4l_fsr),FinWgt);
    if (n_jets == 0) m_VecY0j[Pos]     ->Fill(fabs(y4l_fsr),FinWgt);
    if (n_jets >= 1) m_VecY1j[Pos]     ->Fill(fabs(y4l_fsr),FinWgt);

    m_VecCts[Pos]   ->Fill(fabs(cthstr_fsr),FinWgt);
    if (n_jets == 0) m_VecCts0j[Pos]   ->Fill(fabs(cthstr_fsr),FinWgt);
    if (n_jets >= 1) m_VecCts1j[Pos]   ->Fill(fabs(cthstr_fsr),FinWgt);

    if(pt4l_fsr<=60){
      m_VecMLpt[Pos]   ->Fill(m4l_fsr,FinWgt);
      m_VecYLpt[Pos]   ->Fill(fabs(y4l_fsr),FinWgt);
      m_VecCtsLpt[Pos] ->Fill(fabs(cthstr_fsr),FinWgt);
    }
    else{
      m_VecMHpt[Pos]   ->Fill(m4l_fsr,FinWgt);
      m_VecYHpt[Pos]   ->Fill(fabs(y4l_fsr),FinWgt);
      m_VecCtsHpt[Pos] ->Fill(fabs(cthstr_fsr),FinWgt);
    }
    
    if(n_jets>=2){
      m_VecMJJ[Pos]   ->Fill(dijet_invmass,FinWgt);
      if(dijet_invmass<120)       m_VecMJJrm[Pos]->Fill(0.5,FinWgt);
      else if(dijet_invmass<3000) m_VecMJJrm[Pos]->Fill(2.1,FinWgt);
      m_VecETAJJ[Pos] ->Fill(dijet_deltaeta,FinWgt);
      m_VecPHIJJ[Pos] ->Fill(dijet_deltaphi,FinWgt);
    }

    double val[] = {0.5, 1.5, 2.5, 3.5, 4.5};
    if(mZ2_fsr< 32 && mZ1_fsr < 82){  m_VecM12M34rm[0]->Fill(val[0],FinWgt); } //m_VecM12M34rm[0]->AddBinContent(1,FinWgt); }
    if(mZ2_fsr> 32 && mZ1_fsr < 74){  m_VecM12M34rm[0]->Fill(val[1],FinWgt); } //m_VecM12M34rm[0]->AddBinContent(2,FinWgt); }
    if(mZ2_fsr> 32 && mZ1_fsr > 74){  m_VecM12M34rm[0]->Fill(val[2],FinWgt); } //m_VecM12M34rm[0]->AddBinContent(3,FinWgt); }
    if(mZ2_fsr< 32 && mZ2_fsr > 24 && mZ1_fsr > 82){ m_VecM12M34rm[0]->Fill(val[3],FinWgt); } //m_VecM12M34rm[0]->AddBinContent(4,FinWgt); }
    if(mZ2_fsr< 24 && mZ1_fsr > 82){  m_VecM12M34rm[0]->Fill(val[4],FinWgt); } //m_VecM12M34rm[0]->AddBinContent(5,FinWgt); }
    
    if(mZ2_fsr< 32 && mZ1_fsr < 82){  m_VecM12M34rm[Pos]->Fill(val[0],FinWgt); } //m_VecM12M34rm[Pos]->AddBinContent(1,FinWgt); }
    if(mZ2_fsr> 32 && mZ1_fsr < 74){  m_VecM12M34rm[Pos]->Fill(val[1],FinWgt); } //m_VecM12M34rm[Pos]->AddBinContent(2,FinWgt); }
    if(mZ2_fsr> 32 && mZ1_fsr > 74){  m_VecM12M34rm[Pos]->Fill(val[2],FinWgt); } //m_VecM12M34rm[Pos]->AddBinContent(3,FinWgt); }
    if(mZ2_fsr< 32 && mZ2_fsr > 24 && mZ1_fsr > 82){ m_VecM12M34rm[Pos]->Fill(val[3],FinWgt); } //m_VecM12M34rm[Pos]->AddBinContent(4,FinWgt); }
    if(mZ2_fsr< 24 && mZ1_fsr > 82){  m_VecM12M34rm[Pos]->Fill(val[4],FinWgt); } //m_VecM12M34rm[Pos]->AddBinContent(5,FinWgt); }
    
    
    /* m4l for each variable bin */
    for(uint i=0; i<m_pTBins.size(); i++){
      if( pt4l_fsr>=PtRangeVec.at(i) && pt4l_fsr<PtRangeVec.at(i+1) )
        m_pTBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    for(uint i=0; i<m_ctsBins.size(); i++){
      if( fabs(cthstr_fsr)>=CtsRangeVec.at(i) && fabs(cthstr_fsr)<CtsRangeVec.at(i+1) )
        m_ctsBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    for(uint i=0; i<m_yBins.size(); i++){
      if( fabs(y4l_fsr)>=RapRangeVec.at(i) && fabs(y4l_fsr)<RapRangeVec.at(i+1) )
        m_yBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    for(uint i=0; i<m_m12Bins.size(); i++){
      if( mZ1_fsr>=M12RangeVec.at(i) && mZ1_fsr<M12RangeVec.at(i+1) )
        m_m12Bins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    for(uint i=0; i<m_m34Bins.size(); i++){
      if( mZ2_fsr>=M34RangeVec.at(i) && mZ2_fsr<M34RangeVec.at(i+1) )
        m_m34Bins.at(i)->Fill(m4l_fsr,FinWgt);
    }

    for(uint i=0; i<m_njetBins.size(); i++){
      if( n_jets>=NjetRangeVec.at(i) && n_jets<NjetRangeVec.at(i+1) )
        m_njetBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    if( n_jets >= (int)m_njetBins.size() ) m_njetBins.at(m_njetBins.size()-1)->Fill(m4l_fsr,FinWgt);  ///// needed for overflow

    for(uint i=0; i<m_njetBinsv2.size(); i++){
      if( n_jets>=NjetRangeVecv2.at(i) && n_jets<NjetRangeVecv2.at(i+1) )
        m_njetBinsv2.at(i)->Fill(m4l_fsr,FinWgt);
    }
    if( n_jets >= (int)m_njetBinsv2.size() ) m_njetBinsv2.at(m_njetBinsv2.size()-1)->Fill(m4l_fsr,FinWgt);  ///// needed for overflow

    for(uint i=0; i<m_njetBinsv3.size(); i++){
      if( n_jets>=NjetRangeVecv3.at(i) && n_jets<NjetRangeVecv3.at(i+1) )
        m_njetBinsv3.at(i)->Fill(m4l_fsr,FinWgt);
    }
    if( n_jets >= (int)m_njetBinsv3.size() ) m_njetBinsv3.at(m_njetBinsv3.size()-1)->Fill(m4l_fsr,FinWgt);  ///// needed for overflow

    for(uint i=0; i<m_nbjetBins.size(); i++){
      if( n_jets_btag70>=NbjetRangeVec.at(i) && n_jets_btag70<NbjetRangeVec.at(i+1) )
        m_nbjetBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    if( n_jets_btag70 >= (int)m_nbjetBins.size() ) m_nbjetBins.at(m_nbjetBins.size()-1)->Fill(m4l_fsr,FinWgt); ///// needed for overflow
        
    for(uint i=0; i<m_ljptBins.size(); i++){
      if( jet_pt[0]>=LjPtRangeVec.at(i) && jet_pt[0]<LjPtRangeVec.at(i+1) )
        m_ljptBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    for(uint i=0; i<m_mjjBins.size(); i++){
      if( n_jets>1 && dijet_invmass>=MjjRangeVec.at(i) && dijet_invmass<MjjRangeVec.at(i+1) )
        m_mjjBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    for(uint i=0; i<m_etajjBins.size(); i++){
      if( n_jets>1 && dijet_deltaeta>=EtajjRangeVec.at(i) && dijet_deltaeta<EtajjRangeVec.at(i+1) )
        m_etajjBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    for(uint i=0; i<m_phijjBins.size(); i++){
      if( n_jets>1 && dijet_phi>=PhijjRangeVec.at(i) && dijet_phi<PhijjRangeVec.at(i+1) )
        m_phijjBins.at(i)->Fill(m4l_fsr,FinWgt);
    }
    
    
    /* jet-category */
    if(n_jets==0){
      m_VecPT0j[0]  ->Fill(pt4l_fsr,FinWgt);
      m_VecM0j[0]   ->Fill(m4l_fsr,FinWgt);
      m_VecPT0j[Pos]->Fill(pt4l_fsr,FinWgt);
      m_VecM0j[Pos] ->Fill(m4l_fsr,FinWgt);
      if(pt4l_fsr<m_VecPT0j[0]->GetXaxis()->GetXmax() ){
	m_VecPTPT[0]->Fill(pt4l_fsr,FinWgt);
	//m_VecPTPT[0]->Fill(pt4l_fsr+m_VecPT0j[0]->GetXaxis()->GetXmax(),FinWgt);  /// it's like second histogram
      }

      for(uint i=0; i<m_pT0jBins.size(); i++){
    	if(pt4l_fsr>=Pt0jRangeVec.at(i) && pt4l_fsr<Pt0jRangeVec.at(i+1)){
    	  m_pT0jBins.at(i)->Fill(m4l_fsr,FinWgt);
	  m_pTpTBins.at(i)->Fill(m4l_fsr,FinWgt);
	}
      }
    }
    else if(n_jets==1){ //>=1
      m_VecPT1j[0]->Fill(pt4l_fsr,FinWgt);
      m_VecM1j[0]->Fill(m4l_fsr,FinWgt);
      m_VecPT1j[Pos]->Fill(pt4l_fsr,FinWgt);
      m_VecM1j[Pos]->Fill(m4l_fsr,FinWgt);

      if(pt4l_fsr<m_VecPT0j[0]->GetXaxis()->GetXmax() ){
	m_VecPTPT[0]->Fill(pt4l_fsr+m_VecPT0j[0]->GetXaxis()->GetXmax(),FinWgt);  /// it's like second histogram
      }

      for(uint i=0; i<m_pT1jBins.size(); i++){
    	if(pt4l_fsr>=Pt1jRangeVec.at(i) && pt4l_fsr<Pt1jRangeVec.at(i+1)){
    	  m_pT1jBins.at(i)->Fill(m4l_fsr,FinWgt);
	  m_pTpTBins.at(m_pT0jBins.size()+i)->Fill(m4l_fsr,FinWgt);
	}
      }
    }
    else{
      m_VecPT2j[0]->Fill(pt4l_fsr,FinWgt);
      m_VecM2j[0]->Fill(m4l_fsr,FinWgt);
      m_VecPT2j[Pos]->Fill(pt4l_fsr,FinWgt);
      m_VecM2j[Pos]->Fill(m4l_fsr,FinWgt);
      if(pt4l_fsr<m_VecPT0j[0]->GetXaxis()->GetXmax() ){
        m_VecPTPT[0]->Fill(pt4l_fsr+2*m_VecPT0j[0]->GetXaxis()->GetXmax(),FinWgt);  /// it's like second histogram
      }
      for(uint i=0; i<m_pT2jBins.size(); i++){
    	if(pt4l_fsr>=Pt2jRangeVec.at(i) && pt4l_fsr<Pt2jRangeVec.at(i+1)){
    	  m_pT2jBins.at(i)->Fill(m4l_fsr,FinWgt);
	  m_pTpTBins.at(m_pT0jBins.size()+m_pT1jBins.size()+i)->Fill(m4l_fsr,FinWgt);
	}
      }
    }
    if(m_doMtx){
      m_thchain->GetEntry(FindTruthMatch(event, run));
      float dijet_phi_truth = -99;
      if( njets_fid >= 2 ){
	
	if(jet_eta_truth[0]>jet_eta_truth[1]) dijet_phi_truth= jet_phi_truth[0]-jet_phi_truth[1];
	if(jet_eta_truth[0]<jet_eta_truth[1]) dijet_phi_truth= jet_phi_truth[1]-jet_phi_truth[0];
	
	if(dijet_phi_truth<0) dijet_phi_truth = dijet_phi_truth + 2*TMath::Pi();
	
      }
      
      if(Z1_m_fid<0) continue;
      if(Z1_m_fid<0) std::cout << "this event should not be included" << std::endl;
      
      m_VecPTmtx[0]   ->Fill(pt4l_fsr,higgs_pt_fid,FinWgt);
      m_VecPTmtx[Pos] ->Fill(pt4l_fsr,higgs_pt_fid,FinWgt);
      m_VecM12mtx[0]  ->Fill(mZ1_fsr,Z1_m_fid,FinWgt);
      m_VecM12mtx[Pos]->Fill(mZ1_fsr,Z1_m_fid,FinWgt);
      m_VecM34mtx[0]  ->Fill(mZ2_fsr,Z2_m_fid,FinWgt);
      m_VecM34mtx[Pos]->Fill(mZ2_fsr,Z2_m_fid,FinWgt);
      m_VecYmtx[0]    ->Fill(fabs(y4l_fsr),fabs(higgs_y_fid),FinWgt);
      m_VecYmtx[Pos]  ->Fill(fabs(y4l_fsr),fabs(higgs_y_fid),FinWgt);
      m_VecCTSmtx[0]  ->Fill(fabs(cthstr_fsr),fabs(cthstr_fid),FinWgt);
      m_VecCTSmtx[Pos]->Fill(fabs(cthstr_fsr),fabs(cthstr_fid),FinWgt);


      if(n_jets_btag70<2 && nbjets_fid<2){	
	m_VecNBJETmtx[0]  ->Fill(n_jets_btag70, nbjets_fid,FinWgt);
	m_VecNBJETmtx[Pos]->Fill(n_jets_btag70, nbjets_fid,FinWgt);
      }
      else if(n_jets_btag70>=2 && nbjets_fid<2){
	m_VecNBJETmtx[0]  ->SetBinContent(2,nbjets_fid+1,m_VecNBJETmtx[0]->GetBinContent(2,nbjets_fid+1)+FinWgt);
	m_VecNBJETmtx[Pos]->SetBinContent(2,nbjets_fid+1,m_VecNBJETmtx[Pos]->GetBinContent(2,nbjets_fid+1)+FinWgt);
      }
      else if(n_jets_btag70<2 && nbjets_fid>=2){
	m_VecNBJETmtx[0]  ->SetBinContent(n_jets_btag70+1,2,m_VecNBJETmtx[0]->GetBinContent(n_jets_btag70+1,2)+FinWgt);
	m_VecNBJETmtx[Pos]->SetBinContent(n_jets_btag70+1,2,m_VecNBJETmtx[Pos]->GetBinContent(n_jets_btag70+1,2)+FinWgt);
      }
      else if(n_jets_btag70>=2 && nbjets_fid>=2){
	m_VecNBJETmtx[0]  ->SetBinContent(2,2,m_VecNBJETmtx[0]->GetBinContent(2,2)+FinWgt);
	m_VecNBJETmtx[Pos]->SetBinContent(2,2,m_VecNBJETmtx[Pos]->GetBinContent(2,2)+FinWgt);
      }

      if(n_jets<3 && njets_fid<3){
        m_VecNJETmtx[0]  ->Fill(n_jets,njets_fid,FinWgt);
        m_VecNJETmtx[Pos]->Fill(n_jets,njets_fid,FinWgt);
      }
      else if(n_jets>=3 && njets_fid<3){
        m_VecNJETmtx[0]  ->SetBinContent(4,njets_fid+1,m_VecNJETmtx[0]->GetBinContent(4,njets_fid+1)+FinWgt);
        m_VecNJETmtx[Pos]->SetBinContent(4,njets_fid+1,m_VecNJETmtx[Pos]->GetBinContent(4,njets_fid+1)+FinWgt);
      }
      else if(n_jets<3 && njets_fid>=3){
	m_VecNJETmtx[0]  ->SetBinContent(n_jets+1,4,m_VecNJETmtx[0]->GetBinContent(n_jets+1,4)+FinWgt);
        m_VecNJETmtx[Pos]->SetBinContent(n_jets+1,4,m_VecNJETmtx[Pos]->GetBinContent(n_jets+1,4)+FinWgt);
      }
      else if(n_jets>=3 && njets_fid>=3){
        m_VecNJETmtx[0]  ->SetBinContent(4,4,m_VecNJETmtx[0]->GetBinContent(4,4)+FinWgt);
        m_VecNJETmtx[Pos]->SetBinContent(4,4,m_VecNJETmtx[Pos]->GetBinContent(4,4)+FinWgt);
      }

      if(n_jets<1 && njets_fid<1){
        m_VecNJETmtxv2[0]  ->Fill(n_jets,njets_fid,FinWgt);
        m_VecNJETmtxv2[Pos]->Fill(n_jets,njets_fid,FinWgt);
      }
      else if(n_jets>=1 && njets_fid<1){
        m_VecNJETmtxv2[0]  ->SetBinContent(2,njets_fid+1,m_VecNJETmtxv2[0]->GetBinContent(2,njets_fid+1)+FinWgt);
        m_VecNJETmtxv2[Pos]->SetBinContent(2,njets_fid+1,m_VecNJETmtxv2[Pos]->GetBinContent(2,njets_fid+1)+FinWgt);
      }
      else if(n_jets<1 && njets_fid>=1){
	m_VecNJETmtxv2[0]  ->SetBinContent(n_jets+1,2,m_VecNJETmtxv2[0]->GetBinContent(n_jets+1,2)+FinWgt);
        m_VecNJETmtxv2[Pos]->SetBinContent(n_jets+1,2,m_VecNJETmtxv2[Pos]->GetBinContent(n_jets+1,2)+FinWgt);
      }
      else if(n_jets>=1 && njets_fid>=1){
        m_VecNJETmtxv2[0]  ->SetBinContent(2,2,m_VecNJETmtxv2[0]->GetBinContent(2,2)+FinWgt);
        m_VecNJETmtxv2[Pos]->SetBinContent(2,2,m_VecNJETmtxv2[Pos]->GetBinContent(2,2)+FinWgt);
      }

      if(n_jets<2 && njets_fid<2){
        m_VecNJETmtxv3[0]  ->Fill(n_jets,njets_fid,FinWgt);
        m_VecNJETmtxv3[Pos]->Fill(n_jets,njets_fid,FinWgt);
      }
      else if(n_jets>=2 && njets_fid<2){
        m_VecNJETmtxv3[0]  ->SetBinContent(3,njets_fid+1,m_VecNJETmtxv3[0]->GetBinContent(3,njets_fid+1)+FinWgt);
        m_VecNJETmtxv3[Pos]->SetBinContent(3,njets_fid+1,m_VecNJETmtxv3[Pos]->GetBinContent(3,njets_fid+1)+FinWgt);
      }
      else if(n_jets<2 && njets_fid>=2){
	m_VecNJETmtxv3[0]  ->SetBinContent(n_jets+1,3,m_VecNJETmtxv3[0]->GetBinContent(n_jets+1,3)+FinWgt);
        m_VecNJETmtxv3[Pos]->SetBinContent(n_jets+1,3,m_VecNJETmtxv3[Pos]->GetBinContent(n_jets+1,3)+FinWgt);
      }
      else if(n_jets>=2 && njets_fid>=2){
        m_VecNJETmtxv3[0]  ->SetBinContent(3,3,m_VecNJETmtxv3[0]->GetBinContent(3,3)+FinWgt);
        m_VecNJETmtxv3[Pos]->SetBinContent(3,3,m_VecNJETmtxv3[Pos]->GetBinContent(3,3)+FinWgt);
      }
            
      m_VecLJETmtx[0]  ->Fill(jet_pt[0],leading_jet_pt_fid,FinWgt);
      m_VecLJETmtx[Pos]->Fill(jet_pt[0],leading_jet_pt_fid,FinWgt);
      
      if(n_jets==0){
        m_VecPT0jmtx[0]  ->Fill(pt4l_fsr,higgs_pt_fid,FinWgt);
        m_VecPT0jmtx[Pos]->Fill(pt4l_fsr,higgs_pt_fid,FinWgt);
      }
      else if(n_jets==1){
        m_VecPT1jmtx[0]  ->Fill(pt4l_fsr,higgs_pt_fid,FinWgt);
        m_VecPT1jmtx[Pos]->Fill(pt4l_fsr,higgs_pt_fid,FinWgt);
      }
      else{
	m_VecPT2jmtx[0]  ->Fill(pt4l_fsr,higgs_pt_fid,FinWgt);
	m_VecPT2jmtx[Pos]->Fill(pt4l_fsr,higgs_pt_fid,FinWgt);
      }

      if(n_jets>= 2){
	m_VecMJJmtx[0]    ->Fill(dijet_invmass,dijet_invmass_fid,FinWgt);
	m_VecETAJJmtx[0]  ->Fill(dijet_deltaeta,dijet_deltaeta_fid,FinWgt);
	m_VecPHIJJmtx[0]  ->Fill(dijet_phi,dijet_deltaphi_fid,FinWgt); //dijet_phi_truth,FinWgt);
	m_VecMJJmtx[Pos]  ->Fill(dijet_invmass,dijet_invmass_fid,FinWgt);
	m_VecETAJJmtx[Pos]->Fill(dijet_deltaeta,dijet_deltaeta_fid,FinWgt);
	m_VecPHIJJmtx[Pos]->Fill(dijet_phi,dijet_deltaphi_fid,FinWgt); //dijet_phi_truth,FinWgt);
      }
     
      int truthb=0;
      if (Z2_m_fid< 32 && Z1_m_fid < 82) truthb=1;
      if (Z2_m_fid> 32 && Z1_m_fid < 74) truthb=2;
      if (Z2_m_fid> 32 && Z1_m_fid > 74) truthb=3;
      if (Z2_m_fid< 32 && Z2_m_fid > 24 && Z1_m_fid > 82) truthb=4;
      if (Z2_m_fid< 24 && Z1_m_fid > 82) truthb=5;

      if (mZ2_fsr< 32 && mZ1_fsr < 82) m_Vechm12vsm34rmmtx[0]->SetBinContent(1,truthb, m_Vechm12vsm34rmmtx[0]->GetBinContent(1,truthb)+FinWgt);
      if (mZ2_fsr> 32 && mZ1_fsr < 74) m_Vechm12vsm34rmmtx[0]->SetBinContent(2,truthb, m_Vechm12vsm34rmmtx[0]->GetBinContent(2,truthb,2)+FinWgt);
      if (mZ2_fsr> 32 && mZ1_fsr > 74) m_Vechm12vsm34rmmtx[0]->SetBinContent(3,truthb, m_Vechm12vsm34rmmtx[0]->GetBinContent(3,truthb)+FinWgt);
      if (mZ2_fsr< 32 && mZ2_fsr > 24 && mZ1_fsr > 82) m_Vechm12vsm34rmmtx[0]->SetBinContent(4,truthb, m_Vechm12vsm34rmmtx[0]->GetBinContent(4,truthb)+FinWgt);
      if (mZ2_fsr< 24 && mZ1_fsr > 82) m_Vechm12vsm34rmmtx[0]->SetBinContent(5,truthb, m_Vechm12vsm34rmmtx[0]->GetBinContent(5,truthb)+FinWgt);
      
      if (mZ2_fsr< 32 && mZ1_fsr < 82) m_Vechm12vsm34rmmtx[Pos]->SetBinContent(1,truthb, m_Vechm12vsm34rmmtx[Pos]->GetBinContent(1,truthb)+FinWgt);
      if (mZ2_fsr> 32 && mZ1_fsr < 74) m_Vechm12vsm34rmmtx[Pos]->SetBinContent(2,truthb, m_Vechm12vsm34rmmtx[Pos]->GetBinContent(2,truthb)+FinWgt);
      if (mZ2_fsr> 32 && mZ1_fsr > 74) m_Vechm12vsm34rmmtx[Pos]->SetBinContent(3,truthb, m_Vechm12vsm34rmmtx[Pos]->GetBinContent(3,truthb)+FinWgt);
      if (mZ2_fsr< 32 && mZ2_fsr > 24 && mZ1_fsr > 82) m_Vechm12vsm34rmmtx[Pos]->SetBinContent(4,truthb, m_Vechm12vsm34rmmtx[Pos]->GetBinContent(4,truthb)+FinWgt);
      if (mZ2_fsr< 24 && mZ1_fsr > 82) m_Vechm12vsm34rmmtx[Pos]->SetBinContent(5,truthb, m_Vechm12vsm34rmmtx[Pos]->GetBinContent(5,truthb)+FinWgt);
      //// truth info for m12 vs m34
      
      if (Z2_m_fid< 32 && Z1_m_fid < 82 ) m_Vechbin1Z1Z2mtx[0]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      if (Z2_m_fid> 32 && Z1_m_fid < 74) m_Vechbin2Z1Z2mtx[0]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      if (Z2_m_fid> 32 && Z1_m_fid > 74) m_Vechbin3Z1Z2mtx[0]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      if (Z2_m_fid< 32 && Z2_m_fid > 24 && Z1_m_fid > 82) m_Vechbin4Z1Z2mtx[0]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      if (Z2_m_fid< 24 && Z1_m_fid > 82) m_Vechbin5Z1Z2mtx[0]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      
      if (Z2_m_fid< 32 && Z1_m_fid < 82 ) m_Vechbin1Z1Z2mtx[Pos]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      if (Z2_m_fid> 32 && Z1_m_fid < 74) m_Vechbin2Z1Z2mtx[Pos]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      if (Z2_m_fid> 32 && Z1_m_fid > 74) m_Vechbin3Z1Z2mtx[Pos]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      if (Z2_m_fid< 32 && Z2_m_fid > 24 && Z1_m_fid > 82) m_Vechbin4Z1Z2mtx[Pos]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      if (Z2_m_fid< 24 && Z1_m_fid > 82) m_Vechbin5Z1Z2mtx[Pos]->Fill(mZ1_fsr,mZ2_fsr,FinWgt);
      
    }
    
  }
  //if(m_Process=="qqZZ"){
  //  NormalizePlots(qqZZInt,0);
  //}
  //if(m_Process=="AllZZ"){
  //  NormalizePlots(qqZZInt,ggZZInt);
  //}
  
}
