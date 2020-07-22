#include "EventLoop.h"

void EventLoop:: FillHistograms(){

  PRINT_VERBOSE("<EventLoop::FillHistograms()>:: filling histograms ...");

  if(m_isCouplings)
    FillCouplingsHistos();
  else
    FillXsecHistos();

}

void EventLoop::FillCouplingsHistos(){

  PRINT_VERBOSE( "<EventLoop::FillCouplingsHistos()>:: filling couplings ",
		 "analysis histograms ...");

  /* BDTZZ0j */
  if( prod_type==0 ){
    m_HistosBins["BDTZZ0j"][Cats::all].at(Channel::_incl)->Fill(BDT_discriminant,mFinWgt);
    FillHistoCategories("BDTZZ0j");
  }

  /* BDT1jpT60 */
  if( prod_type==1 && pt4l_fsr<60 ){
    m_HistosBins["BDT1jpT60"][Cats::all].at(Channel::_incl)->Fill(BDT_1Jet_pt4l_60,mFinWgt);
    FillHistoCategories("BDT1jpT60");
  }
  
  /* BDT1jpT60_120 */
  if( prod_type==1 && (pt4l_fsr>60 && pt4l_fsr<120) ){
    m_HistosBins["BDT1jpT60_120"][Cats::all].at(Channel::_incl)->Fill(BDT_1Jet_pt4l_60_120,mFinWgt);
    FillHistoCategories("BDT1jpT60_120");
  }
  
  /* BDT1jHpT */
  if( prod_type==1 && pt4l_fsr>120 ){
    m_HistosBins["BDT1jHpT"][Cats::all].at(Channel::_incl)->Fill(BDT_OneJet_jptetadR_discriminant,mFinWgt);
    FillHistoCategories("BDT1jHpT");
  }
  
  /* BDTVHHad2j */
  if( prod_type==2 ){
    m_HistosBins["BDTVHHad2j"][Cats::all].at(Channel::_incl)->Fill(BDT_VH_noptHjj_discriminant,mFinWgt);
    FillHistoCategories("BDTVHHad2j");
  }
  /* BDTVBF2j */
  if( prod_type==3 && jet_pt->at(0)<200 ){
    m_HistosBins["BDTVBF2j"][Cats::all].at(Channel::_incl)->Fill(BDT_TwoJet_discriminant,mFinWgt);
    FillHistoCategories("BDTVBF2j");
  }

  /* NGE200VBF */
  if( prod_type==3 && jet_pt->at(0)>200 ){
    m_HistosBins["NGE200VBF"][Cats::all].at(Channel::_incl)->Fill(prod_type,mFinWgt);
    FillHistoCategories("NGE200VBF");
  }
  
  /* m4l */
  if( prod_type==4 ){
    m_HistosBins["m4l"][Cats::all].at(Channel::_incl)->Fill(mFourLep,mFinWgt);
    FillHistoCategories("m4l");
  }
  
  /* NttH */
  if( prod_type==5 ){
    m_HistosBins["NttH"][Cats::all].at(Channel::_incl)->Fill(event_type,mFinWgt);
    FillHistoCategories("NttH");
  }
  
}

void EventLoop::FillHistoCategories(std::string type){

  PRINT_VERBOSE("<EventLoop::FillHistoCategories()>:: filling categories plots for var "+
		type+" ... ");
  
  double fvar = 0;
  if(type=="NttH")              { fvar = event_type;                       }
  else if(type=="NGE200VBF")    { fvar = prod_type;                        }
  else if(type=="BDTZZ0j")      { fvar = BDT_discriminant;                 }
  else if(type=="BDT1jpT60")    { fvar = BDT_1Jet_pt4l_60;                 }
  else if(type=="BDT1jpT60_120"){ fvar = BDT_1Jet_pt4l_60_120;             }
  else if(type=="BDT1jHpT")     { fvar = BDT_OneJet_jptetadR_discriminant; }
  else if(type=="BDTVHHad2j")   { fvar = BDT_VH_noptHjj_discriminant;      }
  else if(type=="BDTVBF2j")     { fvar = BDT_TwoJet_discriminant;          }
  else if(type=="m4l")          { fvar = mFourLep;                         }
  else{
    PRINT_ERROR("                                  variable "+type+
		" not defined -> exiting ... ");
    exit(0);
  }

  /* filling Stage 0 signal categories */
  if(m_StxsStage==StxsStage::Stage0){

    /* ggH categories */
    if( HTXS_Stage1_Category_pTjet30 != 100 )
      m_HistosBins[type][Cats::gg2H].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* VBF categories */
    if( HTXS_Stage1_Category_pTjet30 != 200 )
      m_HistosBins[type][Cats::VBF].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* WH categories */
    if( HTXS_Stage1_Category_pTjet30 != 200 &&
	HTXS_Stage1_Category_pTjet30 != 300  )
      m_HistosBins[type][Cats::WH].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* ZH categories */
    if( HTXS_Stage1_Category_pTjet30 != 200 &&
	HTXS_Stage1_Category_pTjet30 != 400  )
      m_HistosBins[type][Cats::ZH].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* ggZH categories */
    if( HTXS_Stage1_Category_pTjet30 != 100 &&
	HTXS_Stage1_Category_pTjet30 != 500  )
      m_HistosBins[type][Cats::ggZH].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* VH categories */
    if( HTXS_Stage1_Category_pTjet30 != 200 &&
	HTXS_Stage1_Category_pTjet30 != 300 &&
	HTXS_Stage1_Category_pTjet30 != 400 &&
	HTXS_Stage1_Category_pTjet30 != 100 &&
	HTXS_Stage1_Category_pTjet30 != 500  )
      m_HistosBins[type][Cats::VH].at(Channel::_incl)->Fill(fvar,mFinWgt);

  }

  /* filling Stage 1 signal categories */
  else if(m_StxsStage==StxsStage::Stage1){

    /* ggH categories */
    if( HTXS_Stage1_Category_pTjet30 == 101 )
      m_HistosBins[type][Cats::gg2H_VBFtopo_jet3veto].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 102 )
      m_HistosBins[type][Cats::gg2H_VBFtopo_jet3].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 103 )
      m_HistosBins[type][Cats::gg2H_0J].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 104 )
      m_HistosBins[type][Cats::gg2H_1J_ptH_0_60].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 105 )
      m_HistosBins[type][Cats::gg2H_1J_ptH_60_120].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 106 )
      m_HistosBins[type][Cats::gg2H_1J_ptH_120_200].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 107 )
      m_HistosBins[type][Cats::gg2H_1J_ptH_gt200].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 108 )
      m_HistosBins[type][Cats::gg2H_ge2J_ptH_0_60].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 109 )
      m_HistosBins[type][Cats::gg2H_ge2J_ptH_60_120].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 110 )
      m_HistosBins[type][Cats::gg2H_ge2J_ptH_120_200].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 111 )
      m_HistosBins[type][Cats::gg2H_ge2J_ptH_gt200].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 201 )
      m_HistosBins[type][Cats::VBF_qq2Hqq_VBFtopo_jet3veto].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* VBF categories */
    if( HTXS_Stage1_Category_pTjet30 == 202 )
       m_HistosBins[type][Cats::VBF_qq2Hqq_VBFtopo_jet3].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 203 )
       m_HistosBins[type][Cats::VBF_qq2Hqq_VH2jet].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 204 )
       m_HistosBins[type][Cats::VBF_qq2Hqq_rest].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 205 )
      m_HistosBins[type][Cats::VBF_qq2Hqq_pTjet1_gt200].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    /* WH categories */
    if( HTXS_Stage1_Category_pTjet30 == 301 )
      m_HistosBins[type][Cats::qq2Hlnu_pTV_0_150].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 302 )
      m_HistosBins[type][Cats::qq2Hlnu_pTV_150_250_0J].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 303 )
      m_HistosBins[type][Cats::qq2Hlnu_pTV_150_250_ge1J].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 304 )
      m_HistosBins[type][Cats::qq2Hlnu_pTV_gt250].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 201 )
      m_HistosBins[type][Cats::WH_qq2Hqq_VBFtopo_jet3veto].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 202 )
      m_HistosBins[type][Cats::WH_qq2Hqq_VBFtopo_jet3].at(Channel::_incl)->Fill(fvar,mFinWgt);
	
    if( HTXS_Stage1_Category_pTjet30 == 203 )
      m_HistosBins[type][Cats::WH_qq2Hqq_VH2jet].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 204 )
      m_HistosBins[type][Cats::WH_qq2Hqq_rest].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 205 )
      m_HistosBins[type][Cats::WH_qq2Hqq_pTjet1_gt200].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* ZH categories */
    if( HTXS_Stage1_Category_pTjet30 == 401 )
      m_HistosBins[type][Cats::qq2Hll_pTV_0_150].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 402 )
      m_HistosBins[type][Cats::qq2Hll_pTV_150_250_0J].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 403 )
      m_HistosBins[type][Cats::qq2Hll_pTV_150_250_ge1J].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 404 )
      m_HistosBins[type][Cats::qq2Hll_pTV_gt250].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 201 )
      m_HistosBins[type][Cats::ZH_qq2Hqq_VBFtopo_jet3veto].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 202 )
      m_HistosBins[type][Cats::ZH_qq2Hqq_VBFtopo_jet3].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 203 )
      m_HistosBins[type][Cats::ZH_qq2Hqq_VH2jet].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 204 )
      m_HistosBins[type][Cats::ZH_qq2Hqq_rest].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 205 )
      m_HistosBins[type][Cats::ZH_qq2Hqq_pTjet1_gt200].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* ggZH categories */
    if( HTXS_Stage1_Category_pTjet30 == 501 )
      m_HistosBins[type][Cats::gg2Hll_pTV_0_150].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 502 )
      m_HistosBins[type][Cats::gg2Hll_pTV_gt150_0J].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 503 )
      m_HistosBins[type][Cats::gg2Hll_pTV_gt150_ge1J].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 101 )
      m_HistosBins[type][Cats::ggZH_VBFtopo_jet3veto].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 102 )
      m_HistosBins[type][Cats::ggZH_VBFtopo_jet3].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 103 )
      m_HistosBins[type][Cats::ggZH_0J].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 104 )
      m_HistosBins[type][Cats::ggZH_1J_ptH_0_60].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 105 )
      m_HistosBins[type][Cats::ggZH_1J_ptH_60_120].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 106 )
      m_HistosBins[type][Cats::ggZH_1J_ptH_120_200].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 107 )
      m_HistosBins[type][Cats::ggZH_1J_ptH_gt200].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 108 )
      m_HistosBins[type][Cats::ggZH_ge2J_ptH_0_60].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 109 )
      m_HistosBins[type][Cats::ggZH_ge2J_ptH_60_120].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 110 )
      m_HistosBins[type][Cats::ggZH_ge2J_ptH_120_200].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 111 )
      m_HistosBins[type][Cats::ggZH_ge2J_ptH_gt200].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* VH categories */
    if( HTXS_Stage1_Category_pTjet30 == 401 )
      m_HistosBins[type][Cats::VH_qq2Hll_PTV_0_150].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 402 )
      m_HistosBins[type][Cats::VH_qq2Hll_PTV_150_250_0J].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 403 )
      m_HistosBins[type][Cats::VH_qq2Hll_PTV_150_250_GE1J].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 404 )
      m_HistosBins[type][Cats::VH_qq2Hll_GT250].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 201 )
      m_HistosBins[type][Cats::VH_VBF_Topo_3JetVeto].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 202 )
      m_HistosBins[type][Cats::VH_VBF_Topo_3Jet].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 203 )
      m_HistosBins[type][Cats::VH_VH2JET].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 204 )
      m_HistosBins[type][Cats::VH_qq2qq_REST].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 205 )
      m_HistosBins[type][Cats::VH_qq2qq_PTJET1_GT200].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
  }

  /* filling Reduced Stage 1 signal categories */
  else if(m_StxsStage==StxsStage::RedStage1){

    /* ggH categories */
    if( HTXS_Stage1_Category_pTjet30 == 103 )
      m_HistosBins[type][Cats::gg2H_0J].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 104 )
      m_HistosBins[type][Cats::gg2H_1J_ptH_0_60].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 105 )
      m_HistosBins[type][Cats::gg2H_1J_ptH_60_120].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 106 ||
	HTXS_Stage1_Category_pTjet30 == 107  )
      m_HistosBins[type][Cats::gg2H_1J_ptH_gt120].at(Channel::_incl)->Fill(fvar,mFinWgt);
      
    if( HTXS_Stage1_Category_pTjet30 == 101 ||
	HTXS_Stage1_Category_pTjet30 == 102 ||
	HTXS_Stage1_Category_pTjet30 == 108 ||
	HTXS_Stage1_Category_pTjet30 == 109 ||
	HTXS_Stage1_Category_pTjet30 == 110 ||
	HTXS_Stage1_Category_pTjet30 == 111  )
      m_HistosBins[type][Cats::gg2H_ge2J].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* VBF categories */
    if( HTXS_Stage1_Category_pTjet30 != 205 &&
	HTXS_Stage1_Category_pTjet30 != 200   )
      m_HistosBins[type][Cats::VBF_qq2qq_pTjet1_le200].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 205 )
      m_HistosBins[type][Cats::VBF_qq2qq_pTjet1_gt200].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* WH categories */
    if( HTXS_Stage1_Category_pTjet30 == 401 ||
	HTXS_Stage1_Category_pTjet30 == 402 ||
	HTXS_Stage1_Category_pTjet30 == 403 ||
	HTXS_Stage1_Category_pTjet30 == 404 ||
	HTXS_Stage1_Category_pTjet30 == 301 ||
	HTXS_Stage1_Category_pTjet30 == 302 ||
	HTXS_Stage1_Category_pTjet30 == 303 ||
	HTXS_Stage1_Category_pTjet30 == 304  )
      m_HistosBins[type][Cats::WH_Lep].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 201 ||
	HTXS_Stage1_Category_pTjet30 == 202 ||
	HTXS_Stage1_Category_pTjet30 == 203 ||
	HTXS_Stage1_Category_pTjet30 == 204 ||
	HTXS_Stage1_Category_pTjet30 == 205  )
      m_HistosBins[type][Cats::WH_Had].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* ZH categories */
    if( HTXS_Stage1_Category_pTjet30 == 401 ||
	HTXS_Stage1_Category_pTjet30 == 402 ||
	HTXS_Stage1_Category_pTjet30 == 403 ||
	HTXS_Stage1_Category_pTjet30 == 404 ||
	HTXS_Stage1_Category_pTjet30 == 301 ||
	HTXS_Stage1_Category_pTjet30 == 302 ||
	HTXS_Stage1_Category_pTjet30 == 303 ||
	HTXS_Stage1_Category_pTjet30 == 304  )
      m_HistosBins[type][Cats::ZH_Lep].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
    if( HTXS_Stage1_Category_pTjet30 == 201 ||
	HTXS_Stage1_Category_pTjet30 == 202 ||
	HTXS_Stage1_Category_pTjet30 == 203 ||
	HTXS_Stage1_Category_pTjet30 == 204 ||
	HTXS_Stage1_Category_pTjet30 == 205  )
      m_HistosBins[type][Cats::ZH_Had].at(Channel::_incl)->Fill(fvar,mFinWgt);

    /* VH categories */
    if( HTXS_Stage1_Category_pTjet30 == 401 ||
	HTXS_Stage1_Category_pTjet30 == 402 ||
	HTXS_Stage1_Category_pTjet30 == 403 ||
	HTXS_Stage1_Category_pTjet30 == 404 ||
	HTXS_Stage1_Category_pTjet30 == 301 ||
	HTXS_Stage1_Category_pTjet30 == 302 ||
	HTXS_Stage1_Category_pTjet30 == 303 ||
	HTXS_Stage1_Category_pTjet30 == 304 ||
	HTXS_Stage1_Category_pTjet30 == 501 ||
	HTXS_Stage1_Category_pTjet30 == 502 ||
	HTXS_Stage1_Category_pTjet30 == 503  )
      m_HistosBins[type][Cats::VH_Lep].at(Channel::_incl)->Fill(fvar,mFinWgt);

    if( HTXS_Stage1_Category_pTjet30 == 201 ||
	HTXS_Stage1_Category_pTjet30 == 202 ||
	HTXS_Stage1_Category_pTjet30 == 203 ||
	HTXS_Stage1_Category_pTjet30 == 204 ||
	HTXS_Stage1_Category_pTjet30 == 205 ||
	(HTXS_Stage1_Category_pTjet30 < 200 &&
	 HTXS_Stage1_Category_pTjet30 != 100) )
      m_HistosBins[type][Cats::VH_Had].at(Channel::_incl)->Fill(fvar,mFinWgt);
    
  }

  /* common categories for all stages */
  if( HTXS_Stage1_Category_pTjet30 == 601 )
    m_HistosBins[type][Cats::ttH].at(Channel::_incl)->Fill(fvar,mFinWgt);
  
  if( HTXS_Stage1_Category_pTjet30 == 701 )
    m_HistosBins[type][Cats::bbH].at(Channel::_incl)->Fill(fvar,mFinWgt);
  
  if( HTXS_Stage1_Category_pTjet30 == 801 )
    m_HistosBins[type][Cats::tHW].at(Channel::_incl)->Fill(fvar,mFinWgt);
  
  if( HTXS_Stage1_Category_pTjet30 == 801 )
    m_HistosBins[type][Cats::tHqb].at(Channel::_incl)->Fill(fvar,mFinWgt);
  
}

void EventLoop::FillXsecHistos(){

  PRINT_VERBOSE("<EventLoop::FillCouplingsHistos()>:: filling xsec ",
		"analysis histograms ...");


  double sht = 0.;
  for(uint v=0; v<m_diffVars.size(); v++){

    int vNum        = GetVariableID( m_diffVars[v] );
    double varValue = GetVariableValue(vNum,mcType::Reco);
    int bin = GetVariableBin( vNum,mcType::Reco);
    
    if( PassCondition( vNum,bin,mcType::Reco) ){

      if(vNum==Variable::mjj){
	double val = -999;
	if(varValue==-999)    { val = 0.5; }
	else if(varValue<120) { val = 1.5; }
	else if(varValue<450) { val = 2.5; }
	else if(varValue<3000){ val = 5.5; }
	m_Histos[m_diffVars[v]].at(Channel::_incl)->Fill(val,mFinWgt);
	m_Histos[m_diffVars[v]].at(event_type+1)  ->Fill(val,mFinWgt);
	m_Histos[m_diffVars[v]].at(m_mrgChan)     ->Fill(val,mFinWgt);
      }
      else if( (vNum>=Variable::njet && vNum<=Variable::njetv4) ||
	       vNum==Variable::nbjet ){
	m_Histos[m_diffVars[v]].at(Channel::_incl)->Fill(bin,mFinWgt);
	m_Histos[m_diffVars[v]].at(event_type+1)  ->Fill(bin,mFinWgt);
	m_Histos[m_diffVars[v]].at(m_mrgChan)     ->Fill(bin,mFinWgt);
      }
      else if(vNum==Variable::m12m34){
	m_Histos[m_diffVars[v]].at(Channel::_incl)->Fill(bin,mFinWgt);
	m_Histos[m_diffVars[v]].at(event_type+1)  ->Fill(bin,mFinWgt);
	m_Histos[m_diffVars[v]].at(m_mrgChan)     ->Fill(bin,mFinWgt);
	if(m_Histos2D.size()!=0){
	  /* m12 vs m34 TH2 */
	  m_Histos2D[m_diffVars[v]].at(Channel::_incl)->Fill(GetVariableValue(Variable::m12,mcType::Reco),
							     GetVariableValue(Variable::m34,mcType::Reco),
							     mFinWgt);
	  m_Histos2D[m_diffVars[v]].at(event_type+1)  ->Fill(GetVariableValue(Variable::m12,mcType::Reco),
							     GetVariableValue(Variable::m34,mcType::Reco),
							     mFinWgt);
	  m_Histos2D[m_diffVars[v]].at(m_mrgChan)     ->Fill(GetVariableValue(Variable::m12,mcType::Reco),
							     GetVariableValue(Variable::m34,mcType::Reco),
							     mFinWgt);
	}
      }
      else{
	sht = 0.;
	if(vNum==Variable::ptnjet){
	  if(GetVariableValue(Variable::njet,mcType::Reco)==0)     { sht = 0.0   ; }
	  else if(GetVariableValue(Variable::njet,mcType::Reco)==1){ sht = 350.0 ; }
	  else if(GetVariableValue(Variable::njet,mcType::Reco)==2){ sht = 700.0 ; }
	  else                                                     { sht = 1050.0; }
	}
	else if(vNum==Variable::pty4l){
	  if(GetVariableValue(Variable::y4l,mcType::Reco)<0.5)     { sht = 0.0   ; }
	  else if(GetVariableValue(Variable::y4l,mcType::Reco)<1.0){ sht = 350.0 ; }
	  else if(GetVariableValue(Variable::y4l,mcType::Reco)<1.5){ sht = 700.0 ; }
	  else if(GetVariableValue(Variable::y4l,mcType::Reco)<2.5){ sht = 1050.0; }
	  else                                                     { sht = 9000.0; }
	}
	else if(vNum==Variable::ljpt || vNum==Variable::sjpt){
	  if(varValue==-999) sht = 999+29.0;
	}
      	else if(vNum==Variable::phijj || vNum==Variable::etajj){
	  if(varValue==-999) sht = 999;
	  else               sht = 1.0;
	}
	m_Histos[m_diffVars[v]].at(Channel::_incl)->Fill(varValue+sht,mFinWgt);
	m_Histos[m_diffVars[v]].at(event_type+1)  ->Fill(varValue+sht,mFinWgt);	
	m_Histos[m_diffVars[v]].at(m_mrgChan)     ->Fill(varValue+sht,mFinWgt);
	if(m_diffVars[v]=="m4l" && m_Min!=115 && m_Max!=130){
	  m_Histos[m_diffVars[v]+"_Ext"].at(Channel::_incl)->Fill(varValue+sht,mFinWgt);
	  m_Histos[m_diffVars[v]+"_Ext"].at(event_type+1)  ->Fill(varValue+sht,mFinWgt);	
	  m_Histos[m_diffVars[v]+"_Ext"].at(m_mrgChan)     ->Fill(varValue+sht,mFinWgt);
	}
      }
      
      if( m_HistosBins.size()!=0 && UseMassInBins(vNum) ){
	m_HistosBins[m_diffVars[v]][bin].at(Channel::_incl)->Fill(GetVariableValue(Variable::m4l,mcType::Reco),mFinWgt);
	m_HistosBins[m_diffVars[v]][bin].at(event_type+1)  ->Fill(GetVariableValue(Variable::m4l,mcType::Reco),mFinWgt);
	m_HistosBins[m_diffVars[v]][bin].at(m_mrgChan)     ->Fill(GetVariableValue(Variable::m4l,mcType::Reco),mFinWgt);
      }
      if( m_HistosBinsFine.size()!=0 && UseMassInBins(vNum) ){
	m_HistosBinsFine[m_diffVars[v]][bin].at(Channel::_incl)->Fill(GetVariableValue(Variable::m4l,mcType::Reco),mFinWgt);
	m_HistosBinsFine[m_diffVars[v]][bin].at(event_type+1)  ->Fill(GetVariableValue(Variable::m4l,mcType::Reco),mFinWgt);
	m_HistosBinsFine[m_diffVars[v]][bin].at(m_mrgChan)     ->Fill(GetVariableValue(Variable::m4l,mcType::Reco),mFinWgt);
      }

    }
    
  }
  
}
