#include "CreateInputs.h"

void CreateInputs::RunMatrix(int sysNum){
  
  PRINT_DEBUG("<CreateInputs::RunMatrix()>:: Calling Loop on events ... ");
  
  bool isFirstPass = false;
  
  evt = new EventLoop( m_Process       , sysNum         , m_Process         ,
		       m_mcVers        , m_Min          , m_Max             ,
		       m_doShiftUp     , m_doShiftDown  , m_isContReg       ,
		       m_isCouplings   , m_doACRfactor  , m_Stage           ,
		       m_useMatrix     , m_useRootThMtc , m_EvtList         ,
		       m_split_cF      , m_restrictJets , m_checkDuplicates ,
		       m_procXStoScale , m_valXStoScale , m_debug );

  evt->SetMtxRecoMaps( m_rspMtxBorn_Num , m_rspMtxDres_Num ,
		       m_nonFidBorn     , m_nonFidDres );

  if(!m_keepTruth){
    evt->SetMtxTruthMaps( m_rspMtxBorn_Denom, m_rspMtxDres_Denom );
    evt->SetARmaps( m_fidBornVal    , m_fidBornRaw    ,
		    m_fidBornValInt , m_fidBornRawInt ,
		    m_fidDresVal    , m_fidDresRaw    ,
		    m_fidDresValInt , m_fidDresRawInt ,
		    m_truthVal      , m_truthRaw      ,
		    m_truthValInt   , m_truthRawInt   ,
		    m_truthInt      , m_truthIntRaw );
  }
  else{
    evt->SetTruthMatchingMaps( m_ThMtc_Born, m_ThMtc_Dres );
  }
  
  evt->SetRecoChain(m_chain);
  if(!m_keepTruth){
    evt->SetTruthChain(m_thchain);
    if(!m_useRootThMtc) evt->Loop(!m_useRootThMtc,!m_useRootThMtc);
    evt->TruthLoop();
  }
  if(!m_keepTruth){

    if(m_SystNum==Syst::NormPart1Systematics  || m_SystNum==Syst::NormPart2Systematics  ||
       m_SystNum==Syst::ShapePart1Systematics || m_SystNum==Syst::ShapePart2Systematics ||
       m_SystNum==Syst::ShapePart3Systematics )
      m_keepTruth = true;
    
    if(sysNum==Syst::EL_EFF_ID_CorrUncertaintyNP0               ||
       sysNum==Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16 ||
       sysNum==Syst::EG_RESOLUTION_ALL                          ||
       sysNum==Syst::JET_JER_DataVsMC                           ||
       sysNum==Syst::JET_Flavor_Composition_ggHbbH               )
      isFirstPass = true;
    
  }
  if(m_keepTruth) evt->Loop(!isFirstPass,false,m_keepTruth);
  else evt->Loop(m_useRootThMtc);
    
  if(m_keepTruth && isFirstPass){
    m_ThMtc_Born = evt->GetTruthMatchingMap(mcType::Born);
    m_ThMtc_Dres = evt->GetTruthMatchingMap(mcType::Dres);
  }
  delete evt;
  
}

void CreateInputs::DefineMatrixMaps(){

  PRINT_DEBUG("<CreateInputs::DefineMatrixMaps()>:: defining maps for matrix evaluation ... ");
  
  for(auto& x: m_ChMap){
    
    int ch = x.first;

    for(uint v=0; v<m_diffVars.size(); v++){
      
      int nBins = GetNumberOfBins( m_diffVars[v] );

      m_nonFidBorn[m_diffVars[v]][ch] = new std::vector <double>();
      m_nonFidDres[m_diffVars[v]][ch] = new std::vector <double>();
      if(!m_keepTruth){
	m_rspMtxBorn_Denom[m_diffVars[v]][ch] = new std::vector <double>();
	m_rspMtxDres_Denom[m_diffVars[v]][ch] = new std::vector <double>();
      }

      for (int i=0; i<nBins; i++) {
	m_rspMtxBorn_Num[m_diffVars[v]][ch][i] = new std::vector <double>();
	m_rspMtxDres_Num[m_diffVars[v]][ch][i] = new std::vector <double>();
	
	for (int j=0; j<nBins; j++) {
	  m_rspMtxBorn_Num[m_diffVars[v]][ch][i] -> push_back(0);
	  m_rspMtxDres_Num[m_diffVars[v]][ch][i] -> push_back(0);
	}
	
	m_nonFidBorn[m_diffVars[v]][ch] -> push_back(0);
	m_nonFidDres[m_diffVars[v]][ch] -> push_back(0);

	if(!m_keepTruth){
	  m_rspMtxBorn_Denom[m_diffVars[v]][ch] -> push_back(0);
	  m_rspMtxDres_Denom[m_diffVars[v]][ch] -> push_back(0);
	}
	
      }
      
    }
    
  }

}

void CreateInputs::EvaluateMatrix() {
  
  PRINT("<CreateInputs::EvaluateMatrix()>:: Processing Sample = "+m_ProcStr+" ... ");

  for(auto &mp: m_SysMap){
    
    PRINT("                         Systematic = "+std::to_string(mp.first)+" ("+mp.second+")");
    
    DefineOutFile(mp.first);
    SetChains(mp.first);
    DefineHistograms(mp.first);
    DefineMatrixMaps();
    DefineValuesMaps();
    RunMatrix(mp.first);
    
    for(uint v=0; v<m_diffVars.size(); v++){
      WriteMatrix( m_diffVars[v] ); 
    }
    
    m_Out->cd();
    if(mp.first>Syst::NOMINAL){
      if( m_Out->GetDirectory( m_SysMap[mp.first].c_str() )==0 )
	m_Out->mkdir( m_SysMap[mp.first].c_str() );
      m_Out->cd( m_SysMap[mp.first].c_str() );
    }		
   
    std::vector<TObject*> Plots = ListOfPlotsToWrite();
    for(uint p=0; p<Plots.size(); p++){
      Plots[p]->Write();
    }
    /* cleaning */
    for(uint p=0; p<Plots.size(); p++){
      Plots[p]->Delete();
    }
    m_chain->Reset();
    m_thchain->Reset();
    m_HmtxBornMap.clear();
    m_HmtxDresMap.clear();
    m_HmtxMigBornMap.clear();
    m_HmtxMigDresMap.clear();
    m_HfNFabsBornMap.clear();
    m_HfNFabsDresMap.clear();
    m_HfNFrelBornMap.clear();
    m_HfNFrelDresMap.clear();
    m_HaFBornMap.clear();
    m_HaFDresMap.clear();
    m_HrFmap.clear();
    m_rspMtxBorn_Num.clear(); 
    m_rspMtxDres_Num.clear(); 
    m_nonFidBorn.clear();
    m_nonFidDres.clear();
    if(!m_keepTruth){
      m_rspMtxBorn_Denom.clear();
      m_rspMtxDres_Denom.clear();
      m_fidBornVal.clear();
      m_fidBornValInt.clear();
      m_fidBornRawInt.clear();
      m_fidDresVal.clear();
      m_fidDresValInt.clear();
      m_fidDresRawInt.clear();
      m_truthVal.clear();
      m_truthValInt.clear();
      m_truthRawInt.clear();
      m_truthInt->clear();
      m_truthIntRaw->clear();
    }
    m_Out->Close();
    PRINT("");
  }
  if(m_keepTruth){
    m_rspMtxBorn_Denom.clear();
    m_rspMtxDres_Denom.clear();
    m_fidBornVal.clear();
    m_fidBornValInt.clear();
    m_fidBornRawInt.clear();
    m_fidDresVal.clear();
    m_fidDresValInt.clear();
    m_fidDresRawInt.clear();
    m_truthVal.clear();
    m_truthValInt.clear();
    m_truthRawInt.clear();
    m_truthInt->clear();
    m_truthIntRaw->clear();
    m_ThMtc_Born.clear();
    m_ThMtc_Dres.clear();
  }
  
}

void CreateInputs::WriteMatrix(std::string var) {

  SetInfoLevel(m_acrDetails);
  
  PRINT_DEBUG("CreateInputs::WriteMatrix()>:: Writing response matrix values for variable "+var);
  
  int Bins = GetNumberOfBins(var);
  std::string OutDir = "../ValReader/Values/";
  if(var=="m4l") OutDir += "Fid/";
  else           OutDir += "Diff/"+GetVariableName(var)+"/";
  if(m_mcVers==MCtype::All) OutDir += "mc16/";
  else                      OutDir += m_mcTypeMap[m_mcVers]+"/";
  if(!m_doSystematics){
    CheckOutDir(OutDir+"Born/");
    CheckOutDir(OutDir+"Dressed/");
  }
  
  WriteMatrixValues(Bins,OutDir+"Born/",var);
  WriteMatrixValues(Bins,OutDir+"Dressed/",var);
  WriteNonFidMatrixValues(Bins,OutDir+"Born/",var);
  WriteNonFidMatrixValues(Bins, OutDir+"Dressed/",var);
  WriteACCvalues(Bins,OutDir+"Born/",var);
  WriteACCvalues(Bins,OutDir+"Dressed/",var);
  WriteRvalues(Bins,OutDir,var);
  WriteNmatrixValues(Bins,OutDir,var);
  
}

void CreateInputs::WriteFirstMatrixLine(int nbins) {
  
  PRINT_VERBOSE("<CreateInputs::WriteFirstMatrixLine()>:: writing first line to file .... ");
  
  m_OutF.width(3);  m_OutF << std::left << "Bin";
  
  for (int i=0;i<nbins;i++){
    m_OutF.width(18); m_OutF << std::right << i;
  }
  m_OutF << std::endl;
  
}

void CreateInputs::WriteMatrixValues(int Bins, std::string OutDir, std::string var) {

  PRINT_VALUES("<CreateInputs::WriteMatrixValues()>:: writing the response matrix to file ..." );
  
  for(auto& x: m_ChMap){

    int ch = x.first;
    bool isBorn = OutDir.find("Born")!=std::string::npos;
    if(!m_doSystematics){
      m_OutF.open( OutDir+"rspmtx_"+m_ProcStr+"_"+x.second+"_"+std::to_string(m_Nbins)+"bin.dat");
      WriteFirstMatrixLine(Bins);
    }
    
    for(int i=0; i<Bins; i++){
      m_OutF.width(3); m_OutF << std::left << i;
      m_OutF.width(14);
      
      PRINT_VALUES("                                  channel = "+x.second+" , bin = "+std::to_string(i));
      double matrix=0, num=0, denom=0, migdenom = 0, migmtx = 0;
      if(isBorn){
	
	for (int j=0; j<Bins; j++) {
	  num       = m_rspMtxBorn_Num[var][ch][i]->at(j);
	  migdenom += m_rspMtxBorn_Num[var][ch][i]->at(j);
	  denom     = m_rspMtxBorn_Denom[var][ch]->at(j);
	  matrix    = num/denom;
	  
	  if( !std::isfinite(matrix) ) matrix = 0.0;
	  m_OutF << std::right << matrix;
	  m_OutF.width(4); m_OutF << std::right << 0;
	  m_HmtxBornMap[var].at(ch)->SetBinContent(i+1, j+1, matrix);
	  PRINT_VALUES("	                                 rspMtx ("+
		       std::to_string(i)+","+std::to_string(j)+") = "+
		       std::to_string(matrix)+" -> Num = "+std::to_string(num)+
		       " , Den = "+std::to_string(denom));
	  m_OutF.width(14);
	}
	
      }
      else{
	
	for (int j=0; j<Bins; j++) {
	  num       = m_rspMtxDres_Num[var][ch][i]->at(j);
	  migdenom += m_rspMtxDres_Num[var][ch][i]->at(j);
	  denom     = m_rspMtxDres_Denom[var][ch]->at(j);
	  matrix    = num/denom;

	  if( !std::isfinite(matrix) ) matrix = 0.0;
	  m_OutF << std::right << matrix;
	  m_OutF.width(4); m_OutF << std::right << 0;
	  m_HmtxDresMap[var].at(ch)->SetBinContent(i+1, j+1, matrix);
	  PRINT_VALUES("	                                 rspMtx ("+
		       std::to_string(i)+","+std::to_string(j)+") = "+
		       std::to_string(matrix)+" -> Num = "+std::to_string(num)+
		       " , Den = "+std::to_string(denom));
	  m_OutF.width(14);
	}
      }
      if(isBorn){
	for (int j=0; j<Bins; j++) {
	  num    = m_rspMtxBorn_Num[var][ch][i]->at(j);
	  migmtx = num/migdenom;
	  if( !std::isfinite(migmtx) ) migmtx = 0.0;
	  PRINT_VALUES("	                                 migMtx ("+
		       std::to_string(i)+","+std::to_string(j)+") = "+
		       std::to_string(num/migdenom)+" -> Num = "+
		       std::to_string(num)+" , Den = "+
		       std::to_string(migdenom));
	  m_HmtxMigBornMap[var].at(ch)->SetBinContent(i+1, j+1, migmtx);
	}
      }
      else{
	for (int j=0; j<Bins; j++) {
      	  num = m_rspMtxDres_Num[var][ch][i]->at(j);
	  migmtx = num/migdenom;
	  if( !std::isfinite(migmtx) ) migmtx = 0.0;
	  PRINT_VALUES("	                                 migMtx ("+
		       std::to_string(i)+","+std::to_string(j)+") = "+
		       std::to_string(num/migdenom)+" -> Num = "+
		       std::to_string(num)+" , Den = "+
		       std::to_string(migdenom));
      	  m_HmtxMigDresMap[var].at(ch)->SetBinContent(i+1, j+1, migmtx);
      	}
      }
      if(i!=Bins-1)
	m_OutF << std::endl;
    }
    if(!m_doSystematics) m_OutF.close();
  }
  
}

void CreateInputs::WriteNonFidMatrixValues(int Bins, std::string OutDir, std::string var){

  PRINT_VALUES("<CreateInputs::WriteFnonFidValues()>:: writing fnonFid values to file ... ");

  bool isBorn = OutDir.find("Born")!=std::string::npos;
  if(!m_doSystematics){
    m_OutF.open( OutDir+"rspmtx_fNonFid_"+m_ProcStr+"_"+std::to_string(m_Nbins)+"bin.dat");
    WriteFirstLine();
  }
  
  for(int i=0; i<Bins; i++){
    m_OutF.width(3); m_OutF << std::left << i;

    for(auto& x: m_ChMap){

      PRINT_VALUES("                                  channel = "+x.second+" , bin = "+std::to_string(i));
      int ch = x.first;
      m_OutF.width(14);
      double absV=0, relV = 0, denom=0;
      if(isBorn){
	PRINT_VALUES("                                    Born leptons");
	absV = m_nonFidBorn[var][ch]->at(i);
	for (int j=0; j<Bins; j++) {
	  denom += m_rspMtxBorn_Num[var][ch][i]->at(j);
 	}
	relV = m_nonFidBorn[var][ch]->at(i)/denom;
	if( !std::isfinite(absV) ) absV = 0.0;
	if( !std::isfinite(relV) ) relV = 0.0;
	m_OutF << std::right << absV;
	m_OutF.width(14);
        m_OutF << std::right << relV;
	m_HfNFabsBornMap[var].at(ch)->SetBinContent(i+1, absV);
	m_HfNFrelBornMap[var].at(ch)->SetBinContent(i+1, relV);
      }
      else{
	PRINT_VALUES("                                    Dressed leptons");
	absV = m_nonFidDres[var][ch]->at(i);
	for (int j=0; j<Bins; j++) {
	  denom += m_rspMtxDres_Num[var][ch][i]->at(j);
 	}
	relV = m_nonFidDres[var][ch]->at(i)/denom;
	if( !std::isfinite(absV) ) absV = 0.0;
	if( !std::isfinite(relV) ) relV = 0.0;
	m_OutF << std::right << absV;
	m_OutF.width(14);
	m_OutF << std::right << relV;
	m_HfNFabsDresMap[var].at(ch)->SetBinContent(i+1, absV);
	m_HfNFrelDresMap[var].at(ch)->SetBinContent(i+1, relV);
      }
      PRINT_VALUES("                                    absVal = "+std::to_string(absV)+" , relVal = "+std::to_string(relV));
    }
    
    if(i!=Bins-1)
      m_OutF << std::endl;
  }
  if(!m_doSystematics)
    m_OutF.close();
  
}

void CreateInputs::WriteNmatrixValues(int Bins, std::string OutDir, std::string var){

  PRINT_VALUES("<CreateInputs::WriteNmatrixValues()>:: writing N values to file ... ");

  if(!m_doSystematics){
    m_OutF.open( OutDir+"rspmtx_Nminitree_"+m_ProcStr+"_"+std::to_string(m_Nbins)+"bin.dat");
    WriteFirstLine();
  }

  for(int i=0; i<Bins; i++){
    m_OutF.width(3); m_OutF << std::left << i;
    for(auto& x: m_ChMap){
      PRINT_VALUES("                                  channel = "+x.second+" , bin = "+std::to_string(i));
      int ch = x.first;
      /* first element (from Born) should be equal to second one (from Dressed) */
      double born = 0, dress = 0;
      for (int j=0; j<Bins; j++) {
	born  += m_rspMtxBorn_Num[var][ch][i]->at(j);
	dress += m_rspMtxDres_Num[var][ch][i]->at(j);
      }
      m_OutF.width(14);
      m_OutF << std::right << (born+m_nonFidBorn[var][ch]->at(i));
      m_OutF.width(14);
      m_OutF << std::right << (dress+m_nonFidDres[var][ch]->at(i));
      PRINT_VALUES("                                      nBorn = "+
		   std::to_string(born+m_nonFidBorn[var][ch]->at(i))+
		   " , nDres = "+std::to_string(dress+m_nonFidDres[var][ch]->at(i)));
    }
    if(i!=Bins-1)
      m_OutF << std::endl;
  }
  if(!m_doSystematics)
    m_OutF.close();
  
}
