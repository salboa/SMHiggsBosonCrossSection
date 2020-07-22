#include "vector"
#include "iostream"

/***********************************************/
/* Define Needed Bins and Ranges for Couplings */
/***********************************************/

double BDTZZ0j_Rg[] = {-1.0,   -0.875, -0.750, -0.625, -0.500,
		     -0.375, -0.250, -0.125,  0.0,    0.125,
		     0.250,   0.375,  0.500,  0.625,  0.875, 1.0};

double BDT1jpT60_Rg[] = {-1.0, -0.800, -0.600, -0.400, -0.200,
		       0.0,   0.200,  0.400,  0.600,  0.800, 1.0};

double BDT1jpT60_120_Rg[] = {-1.0, -0.800, -0.600, -0.400, -0.200,
			   0.0,   0.200,  0.400,  0.600,  0.800, 1.0};

double BDT1jHpT_Rg[] = {-1.0, -0.800, -0.600, -0.400, -0.200,
		      0.0,   0.200,  0.400,  0.600,  0.800, 1.0};

double BDTVHHad2j_Rg[] = {-1.0, -0.800, -0.600, -0.400, -0.200,
			0.0,   0.200,  0.400,  0.600,  0.800, 1.0};

double BDTVBF2j_Rg[] = {-1.0, -0.800, -0.600, -0.400, -0.200,
		      0.0,   0.200,  0.400,  0.600,  0.800, 1.0};

double NGE200VBF_Rg[] = {0.0, 10.0};

double NttH_Rg[]      = {0.0, 10.0};

Int_t BDTZZ0j_Bn       = ( (sizeof BDTZZ0j_Rg      ) / (sizeof *BDTZZ0j_Rg      ) )-1;
Int_t BDT1jpT60_Bn     = ( (sizeof BDT1jpT60_Rg    ) / (sizeof *BDT1jpT60_Rg    ) )-1;
Int_t BDT1jpT60_120_Bn = ( (sizeof BDT1jpT60_120_Rg) / (sizeof *BDT1jpT60_120_Rg) )-1;
Int_t BDT1jHpT_Bn      = ( (sizeof BDT1jHpT_Rg     ) / (sizeof *BDT1jHpT_Rg     ) )-1;
Int_t BDTVHHad2j_Bn    = ( (sizeof BDTVHHad2j_Rg   ) / (sizeof *BDTVHHad2j_Rg   ) )-1;
Int_t BDTVBF2j_Bn      = ( (sizeof BDTVBF2j_Rg     ) / (sizeof *BDTVBF2j_Rg     ) )-1;
Int_t NGE200VBF_Bn     = ( (sizeof NGE200VBF_Rg    ) / (sizeof *NGE200VBF_Rg    ) )-1;
Int_t NttH_Bn          = ( (sizeof NttH_Rg         ) / (sizeof *NttH_Rg         ) )-1;


/*******************************************/
/*              Categories                 */
/*                                         */
/*     STXS = 0 (STXS Stage 0)             */
/*     STXS = 1 (STXS Stage 1)             */
/*     STXS = 2 (STXS ReducedStage 1)      */
/*******************************************/

std::vector< std::pair<int,std::string> > m_Ctgs;

void FillggHCategories(int STXS){
  
  if(STXS==0){
    m_Ctgs.push_back( std::make_pair(Cats::gg2H,"gg2H") ); //"(HTXS_Stage1_Category_pTjet30 != 100)";
  }
  else if(STXS==1){
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_VBFtopo_jet3veto,"gg2H_VBFtopo_jet3veto") ); //"(HTXS_Stage1_Category_pTjet30 == 101)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_VBFtopo_jet3    ,"gg2H_VBFtopo_jet3"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 102)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_0J              ,"gg2H_0J"              ) ); //"(HTXS_Stage1_Category_pTjet30 == 103)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_1J_ptH_0_60     ,"gg2H_1J_ptH_0_60"     ) ); //"(HTXS_Stage1_Category_pTjet30 == 104)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_1J_ptH_60_120   ,"gg2H_1J_ptH_60_120"   ) ); //"(HTXS_Stage1_Category_pTjet30 == 105)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_1J_ptH_120_200  ,"gg2H_1J_ptH_120_200"  ) ); //"(HTXS_Stage1_Category_pTjet30 == 106)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_1J_ptH_gt200    ,"gg2H_1J_ptH_gt200"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 107)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_ge2J_ptH_0_60   ,"gg2H_ge2J_ptH_0_60"   ) ); //"(HTXS_Stage1_Category_pTjet30 == 108)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_ge2J_ptH_60_120 ,"gg2H_ge2J_ptH_60_120" ) ); //"(HTXS_Stage1_Category_pTjet30 == 109)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_ge2J_ptH_120_200,"gg2H_ge2J_ptH_120_200") ); //"(HTXS_Stage1_Category_pTjet30 == 110)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_ge2J_ptH_gt200  ,"gg2H_ge2J_ptH_gt200"  ) ); //"(HTXS_Stage1_Category_pTjet30 == 111)";
  }
  else{
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_0J           ,"gg2H_0J"           ) ); //"(HTXS_Stage1_Category_pTjet30 == 103)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_1J_ptH_0_60  ,"gg2H_1J_ptH_0_60"  ) ); //"(HTXS_Stage1_Category_pTjet30 == 104)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_1J_ptH_60_120,"gg2H_1J_ptH_60_120") ); //"(HTXS_Stage1_Category_pTjet30 == 105)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_1J_ptH_gt120 ,"gg2H_1J_ptH_gt120" ) ); //"(HTXS_Stage1_Category_pTjet30 == 106 || HTXS_Stage1_Category_pTjet30 == 107)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2H_ge2J         ,"gg2H_ge2J"         ) ); //"(HTXS_Stage1_Category_pTjet30 == 101 || HTXS_Stage1_Category_pTjet30 == 102 || HTXS_Stage1_Category_pTjet30 == 108 || HTXS_Stage1_Category_pTjet30 == 109 || HTXS_Stage1_Category_pTjet30 == 110 || HTXS_Stage1_Category_pTjet30 == 111)";
  }
  
}

void FillVBFCategories(int STXS){
  
  if(STXS==0){
    m_Ctgs.push_back( std::make_pair(Cats::VBF,"VBF") ); //"(HTXS_Stage1_Category_pTjet30 != 200)";
  }
  else if(STXS==1){
    m_Ctgs.push_back( std::make_pair(Cats::VBF_qq2Hqq_VBFtopo_jet3veto,"VBF_qq2Hqq_VBFtopo_jet3veto") ); //"(HTXS_Stage1_Category_pTjet30 == 201)";
    m_Ctgs.push_back( std::make_pair(Cats::VBF_qq2Hqq_VBFtopo_jet3    ,"VBF_qq2Hqq_VBFtopo_jet3"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 202)";
    m_Ctgs.push_back( std::make_pair(Cats::VBF_qq2Hqq_VH2jet          ,"VBF_qq2Hqq_VH2jet"          ) ); //"(HTXS_Stage1_Category_pTjet30 == 203)";
    m_Ctgs.push_back( std::make_pair(Cats::VBF_qq2Hqq_rest            ,"VBF_qq2Hqq_rest"            ) ); //"(HTXS_Stage1_Category_pTjet30 == 204)";
    m_Ctgs.push_back( std::make_pair(Cats::VBF_qq2Hqq_pTjet1_gt200    ,"VBF_qq2Hqq_pTjet1_gt200"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 205)";
  }
  else{
    m_Ctgs.push_back( std::make_pair(Cats::VBF_qq2qq_pTjet1_le200,"VBF_qq2qq_pTjet1_le200") ); //"(HTXS_Stage1_Category_pTjet30 != 205 && HTXS_Stage1_Category_pTjet30 != 200 )";
    m_Ctgs.push_back( std::make_pair(Cats::VBF_qq2qq_pTjet1_gt200,"VBF_qq2qq_pTjet1_gt200") ); //"(HTXS_Stage1_Category_pTjet30 == 205)";
  }

}

void FillWHCategories(int STXS){
  
  if(STXS==0){
    m_Ctgs.push_back( std::make_pair(Cats::WH,"WH") ); //"(HTXS_Stage1_Category_pTjet30 != 200 && HTXS_Stage1_Category_pTjet30 != 300)";
  }
  else if(STXS==1){
    m_Ctgs.push_back( std::make_pair(Cats::qq2Hlnu_pTV_0_150         ,"qq2Hlnu_pTV_0_150"         ) ); //"(HTXS_Stage1_Category_pTjet30 == 301)";
    m_Ctgs.push_back( std::make_pair(Cats::qq2Hlnu_pTV_150_250_0J    ,"qq2Hlnu_pTV_150_250_0J"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 302)";
    m_Ctgs.push_back( std::make_pair(Cats::qq2Hlnu_pTV_150_250_ge1J  ,"qq2Hlnu_pTV_150_250_ge1J"  ) ); //"(HTXS_Stage1_Category_pTjet30 == 303)";
    m_Ctgs.push_back( std::make_pair(Cats::qq2Hlnu_pTV_gt250         , "qq2Hlnu_pTV_gt250"        ) ); //"(HTXS_Stage1_Category_pTjet30 == 304)";
    m_Ctgs.push_back( std::make_pair(Cats::WH_qq2Hqq_VBFtopo_jet3veto,"WH_qq2Hqq_VBFtopo_jet3veto") ); //"(HTXS_Stage1_Category_pTjet30 == 201)";
    m_Ctgs.push_back( std::make_pair(Cats::WH_qq2Hqq_VBFtopo_jet3    ,"WH_qq2Hqq_VBFtopo_jet3"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 202)";
    m_Ctgs.push_back( std::make_pair(Cats::WH_qq2Hqq_VH2jet          ,"WH_qq2Hqq_VH2jet"          ) ); //"(HTXS_Stage1_Category_pTjet30 == 203)";
    m_Ctgs.push_back( std::make_pair(Cats::WH_qq2Hqq_rest            ,"WH_qq2Hqq_rest"            ) ); //"(HTXS_Stage1_Category_pTjet30 == 204)";
    m_Ctgs.push_back( std::make_pair(Cats::WH_qq2Hqq_pTjet1_gt200    ,"WH_qq2Hqq_pTjet1_gt200"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 205)";
  }
  else{
    // Reduced stage 1
    TString cut = "((HTXS_Stage1_Category_pTjet30 == 401)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 402)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 403)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 404)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 301)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 302)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 303)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 304))";
    
    m_Ctgs.push_back( std::make_pair(Cats::WH_Lep,"WH_Lep") ); //cut;    
    m_Ctgs.push_back( std::make_pair(Cats::WH_Had,"WH_Had") ); //"(HTXS_Stage1_Category_pTjet30 == 201 ||HTXS_Stage1_Category_pTjet30 == 202 || HTXS_Stage1_Category_pTjet30 == 203 || HTXS_Stage1_Category_pTjet30 == 204 || HTXS_Stage1_Category_pTjet30 == 205)";
  }

}

void FillZHCategories(int STXS){
  
  if(STXS==0){
    m_Ctgs.push_back( std::make_pair(Cats::ZH,"ZH") ); //"(HTXS_Stage1_Category_pTjet30 != 200 && HTXS_Stage1_Category_pTjet30 != 400)";
  }
  else if(STXS==1){
    m_Ctgs.push_back( std::make_pair(Cats::qq2Hll_pTV_0_150          ,"qq2Hll_pTV_0_150"          ) ); //"(HTXS_Stage1_Category_pTjet30 == 401)";
    m_Ctgs.push_back( std::make_pair(Cats::qq2Hll_pTV_150_250_0J     ,"qq2Hll_pTV_150_250_0J"     ) ); //"(HTXS_Stage1_Category_pTjet30 == 402)";
    m_Ctgs.push_back( std::make_pair(Cats::qq2Hll_pTV_150_250_ge1J   ,"qq2Hll_pTV_150_250_ge1J"   ) ); //"(HTXS_Stage1_Category_pTjet30 == 403)";
    m_Ctgs.push_back( std::make_pair(Cats::qq2Hll_pTV_gt250          ,"qq2Hll_pTV_gt250"          ) ); //"(HTXS_Stage1_Category_pTjet30 == 404)";
    m_Ctgs.push_back( std::make_pair(Cats::ZH_qq2Hqq_VBFtopo_jet3veto,"ZH_qq2Hqq_VBFtopo_jet3veto") ); //"(HTXS_Stage1_Category_pTjet30 == 201)";
    m_Ctgs.push_back( std::make_pair(Cats::ZH_qq2Hqq_VBFtopo_jet3    ,"ZH_qq2Hqq_VBFtopo_jet3"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 202)";
    m_Ctgs.push_back( std::make_pair(Cats::ZH_qq2Hqq_VH2jet          ,"ZH_qq2Hqq_VH2jet"          ) ); //"(HTXS_Stage1_Category_pTjet30 == 203)";
    m_Ctgs.push_back( std::make_pair(Cats::ZH_qq2Hqq_rest            ,"ZH_qq2Hqq_rest"            ) ); //"(HTXS_Stage1_Category_pTjet30 == 204)";
    m_Ctgs.push_back( std::make_pair(Cats::ZH_qq2Hqq_pTjet1_gt200    ,"ZH_qq2Hqq_pTjet1_gt200"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 205)";
  }
  else{
    TString cut = "((HTXS_Stage1_Category_pTjet30 == 401)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 402)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 403)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 404)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 301)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 302)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 303)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 304))";
    
    m_Ctgs.push_back( std::make_pair(Cats::ZH_Lep,"ZH_Lep") ); //cut;    
    m_Ctgs.push_back( std::make_pair(Cats::ZH_Had,"ZH_Had") ); //"(HTXS_Stage1_Category_pTjet30 == 201 ||HTXS_Stage1_Category_pTjet30 == 202 || HTXS_Stage1_Category_pTjet30 == 203 || HTXS_Stage1_Category_pTjet30 == 204 || HTXS_Stage1_Category_pTjet30 == 205)";
  }
  
}

void FillggZHCategories(int STXS){
  
  if(STXS==0){
    m_Ctgs.push_back( std::make_pair(Cats::ggZH,"ggZH") ); //"(HTXS_Stage1_Category_pTjet30 != 100 && HTXS_Stage1_Category_pTjet30 != 500)";
  }
  else if(STXS==1){
    m_Ctgs.push_back( std::make_pair(Cats::gg2Hll_pTV_0_150     ,"gg2Hll_pTV_0_150"     ) ); //"(HTXS_Stage1_Category_pTjet30 == 501)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2Hll_pTV_gt150_0J  ,"gg2Hll_pTV_gt150_0J"  ) ); //"(HTXS_Stage1_Category_pTjet30 == 502)";
    m_Ctgs.push_back( std::make_pair(Cats::gg2Hll_pTV_gt150_ge1J,"gg2Hll_pTV_gt150_ge1J") ); //"(HTXS_Stage1_Category_pTjet30 == 503)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_VBFtopo_jet3veto,"ggZH_VBFtopo_jet3veto") ); //"(HTXS_Stage1_Category_pTjet30 == 101)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_VBFtopo_jet3    ,"ggZH_VBFtopo_jet3"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 102)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_0J              ,"ggZH_0J"              ) ); //"(HTXS_Stage1_Category_pTjet30 == 103)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_1J_ptH_0_60     ,"ggZH_1J_ptH_0_60"     ) ); //"(HTXS_Stage1_Category_pTjet30 == 104)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_1J_ptH_60_120   ,"ggZH_1J_ptH_60_120"   ) ); //"(HTXS_Stage1_Category_pTjet30 == 105)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_1J_ptH_120_200  ,"ggZH_1J_ptH_120_200"  ) ); //"(HTXS_Stage1_Category_pTjet30 == 106)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_1J_ptH_gt200    ,"ggZH_1J_ptH_gt200"    ) ); //"(HTXS_Stage1_Category_pTjet30 == 107)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_ge2J_ptH_0_60   ,"ggZH_ge2J_ptH_0_60"   ) ); //"(HTXS_Stage1_Category_pTjet30 == 108)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_ge2J_ptH_60_120 ,"ggZH_ge2J_ptH_60_120" ) ); //"(HTXS_Stage1_Category_pTjet30 == 109)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_ge2J_ptH_120_200,"ggZH_ge2J_ptH_120_200") ); //"(HTXS_Stage1_Category_pTjet30 == 110)";
    m_Ctgs.push_back( std::make_pair(Cats::ggZH_ge2J_ptH_gt200  ,"ggZH_ge2J_ptH_gt200"  ) ); //"(HTXS_Stage1_Category_pTjet30 == 111)";
  }
  //else{
  //  TString cut = "((HTXS_Stage1_Category_pTjet30 == 401)";
  //  cut += "||(HTXS_Stage1_Category_pTjet30 == 402)";
  //  cut += "||(HTXS_Stage1_Category_pTjet30 == 403)";
  //  cut += "||(HTXS_Stage1_Category_pTjet30 == 404)";
  //  cut += "||(HTXS_Stage1_Category_pTjet30 == 301)";
  //  cut += "||(HTXS_Stage1_Category_pTjet30 == 302)";
  //  cut += "||(HTXS_Stage1_Category_pTjet30 == 303)";
  //  cut += "||(HTXS_Stage1_Category_pTjet30 == 304))";
  //  m_Ctgs.push_back( "ZH_Lep" ); //cut;    
  //  m_Ctgs.push_back( "ZH_Had" ); //"(HTXS_Stage1_Category_pTjet30 == 201 ||HTXS_Stage1_Category_pTjet30 == 202 || HTXS_Stage1_Category_pTjet30 == 203 || HTXS_Stage1_Category_pTjet30 == 204 || HTXS_Stage1_Category_pTjet30 == 205)";
  //}
  
}

void FillVHCategories(int STXS){

  if(STXS==0){
    m_Ctgs.push_back( std::make_pair(Cats::VH,"VH") ); //"(HTXS_Stage1_Category_pTjet30 != 200 && HTXS_Stage1_Category_pTjet30 != 300 && HTXS_Stage1_Category_pTjet30 != 400 && HTXS_Stage1_Category_pTjet30 != 100 && HTXS_Stage1_Category_pTjet30 != 500)";
  }
  else if(STXS==1){
    m_Ctgs.push_back( std::make_pair(Cats::VH_qq2Hll_PTV_0_150       ,"VH_qq2Hll_PTV_0_150"       ) ); //"(HTXS_Stage1_Category_pTjet30 == 401)";
    m_Ctgs.push_back( std::make_pair(Cats::VH_qq2Hll_PTV_150_250_0J  ,"VH_qq2Hll_PTV_150_250_0J"  ) ); //"(HTXS_Stage1_Category_pTjet30 == 402)";
    m_Ctgs.push_back( std::make_pair(Cats::VH_qq2Hll_PTV_150_250_GE1J,"VH_qq2Hll_PTV_150_250_GE1J") ); //"(HTXS_Stage1_Category_pTjet30 == 403)";
    m_Ctgs.push_back( std::make_pair(Cats::VH_qq2Hll_GT250           ,"VH_qq2Hll_GT250"           ) ); //"(HTXS_Stage1_Category_pTjet30 == 404)";
    m_Ctgs.push_back( std::make_pair(Cats::VH_VBF_Topo_3JetVeto      ,"VH_VBF_Topo_3JetVeto"      ) ); //"(HTXS_Stage1_Category_pTjet30 == 201)";
    m_Ctgs.push_back( std::make_pair(Cats::VH_VBF_Topo_3Jet          ,"VH_VBF_Topo_3Jet"          ) ); //"(HTXS_Stage1_Category_pTjet30 == 202)";
    m_Ctgs.push_back( std::make_pair(Cats::VH_VH2JET                 ,"VH_VH2JET"                 ) ); //"(HTXS_Stage1_Category_pTjet30 == 203)";
    m_Ctgs.push_back( std::make_pair(Cats::VH_qq2qq_REST             ,"VH_qq2qq_REST"             ) ); //"(HTXS_Stage1_Category_pTjet30 == 204)";
    m_Ctgs.push_back( std::make_pair(Cats::VH_qq2qq_PTJET1_GT200     ,"VH_qq2qq_PTJET1_GT200"     ) ); //"(HTXS_Stage1_Category_pTjet30 == 205)";
  }
  else{
    TString cut = "((HTXS_Stage1_Category_pTjet30 == 401)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 402)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 403)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 404)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 301)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 302)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 303)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 304)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 501)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 502)";
    cut += "||(HTXS_Stage1_Category_pTjet30 == 503)";
    cut += ")";

    m_Ctgs.push_back( std::make_pair(Cats::VH_Lep,"VH_Lep") ); //cut;    
    m_Ctgs.push_back( std::make_pair(Cats::VH_Had,"VH_Had") ); //"(HTXS_Stage1_Category_pTjet30 == 201 ||HTXS_Stage1_Category_pTjet30 == 202 || HTXS_Stage1_Category_pTjet30 == 203 || HTXS_Stage1_Category_pTjet30 == 204 || HTXS_Stage1_Category_pTjet30 == 205 || (HTXS_Stage1_Category_pTjet30 < 200 && HTXS_Stage1_Category_pTjet30 != 100))";
  }
  
}

void FillCategories(int STXS){

  FillggHCategories(STXS);
  FillVBFCategories(STXS);

  FillWHCategories(STXS);
  FillZHCategories(STXS);
  FillggZHCategories(STXS);
  FillVHCategories(STXS);

  m_Ctgs.push_back( std::make_pair(Cats::ttH ,"ttH" ) ); //"(HTXS_Stage1_Category_pTjet30 == 601)";
  m_Ctgs.push_back( std::make_pair(Cats::bbH ,"bbH" ) ); //"(HTXS_Stage1_Category_pTjet30 == 701)";
  m_Ctgs.push_back( std::make_pair(Cats::tHW ,"tHW" ) ); //"(HTXS_Stage1_Category_pTjet30 == 801)";
  m_Ctgs.push_back( std::make_pair(Cats::tHqb,"tHqb") ); //"(HTXS_Stage1_Category_pTjet30 == 801)";
  //last two are the same ....
}
