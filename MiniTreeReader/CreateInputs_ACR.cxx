#include "CreateInputs.h"

void CreateInputs::RunACRfactors(int sysNum){

  PRINT_DEBUG("<CreateInputs::RunACRfactors()>:: Calling Loop on events ... ");

  bool isFirstPass = false;

  evt = new EventLoop( m_Process       , sysNum         , m_Process         ,
		       m_mcVers        , m_Min          , m_Max             ,
		       m_doShiftUp     , m_doShiftDown  , m_isContReg       ,
		       m_isCouplings   , m_doACRfactor  , m_Stage           ,
		       m_useMatrix     , m_useRootThMtc , m_EvtList         ,
		       m_split_cF      , m_restrictJets , m_checkDuplicates ,
		       m_procXStoScale , m_valXStoScale , m_debug );
  
  evt->SetCmaps( m_recoBornVal    , m_recoDresVal    ,
		 m_recoBornRaw    , m_recoDresRaw    ,
		 m_recoBornValInt , m_recoDresValInt ,
		 m_recoBornRawInt , m_recoDresRawInt );

  if(!m_keepTruth){
    evt->SetARmaps( m_fidBornVal    , m_fidBornRaw    ,
		    m_fidBornValInt , m_fidBornRawInt ,
		    m_fidDresVal    , m_fidDresRaw    ,
		    m_fidDresValInt , m_fidDresRawInt ,
		    m_truthVal      , m_truthRaw      ,
		    m_truthValInt   , m_truthRawInt   ,
		    m_truthInt      , m_truthIntRaw );
  }
  
  evt->SetRecoChain(m_chain);
  if(!m_keepTruth){
    evt->SetTruthChain(m_thchain);
    if(m_split_cF && !m_useRootThMtc) evt->Loop(!m_useRootThMtc,!m_useRootThMtc);
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
  if(m_keepTruth){
    evt->Loop(!isFirstPass,false,m_keepTruth);
  }
  else{
    if(m_split_cF) evt->Loop(m_useRootThMtc);
    else           evt->Loop(m_doACRfactor);
  }

  if(m_keepTruth && isFirstPass){
    m_ThMtc_Born = evt->GetTruthMatchingMap(mcType::Born);
    m_ThMtc_Dres = evt->GetTruthMatchingMap(mcType::Dres);
  }
  delete evt;
  
}

void CreateInputs::DefineValuesMaps(){

  PRINT_DEBUG("<CreateInputs::DefineValuesMaps()>:: defining maps for A/C/R evaluation ... ");

  m_truthInt    = new std::vector<double>();
  m_truthIntRaw = new std::vector<double>();

  for(uint ch=0; ch<m_ChMap.size(); ch++){
    
    m_truthInt->push_back(0);
    m_truthIntRaw->push_back(0);
    
  }
  
  for(uint v=0; v<m_diffVars.size(); v++){

    int vNum  = GetVariableID( m_diffVars[v] );
    int nbins = GetNumberOfBins(vNum);

    if(!m_useMatrix){
      m_recoBornValInt[m_diffVars[v]] = new std::vector<std::pair<double,double> >();
      m_recoDresValInt[m_diffVars[v]] = new std::vector<std::pair<double,double> >();
      m_recoBornRawInt[m_diffVars[v]] = new std::vector<std::pair<double,double> >();
      m_recoDresRawInt[m_diffVars[v]] = new std::vector<std::pair<double,double> >();
    }

    if(!m_keepTruth){
      m_fidBornValInt[m_diffVars[v]] = new std::vector<double>();
      m_fidDresValInt[m_diffVars[v]] = new std::vector<double>();
      m_truthValInt  [m_diffVars[v]] = new std::vector<double>();
      m_fidBornRawInt[m_diffVars[v]] = new std::vector<double>();
      m_fidDresRawInt[m_diffVars[v]] = new std::vector<double>();
      m_truthRawInt  [m_diffVars[v]] = new std::vector<double>();
    }
    
    for(auto& x: m_ChMap){

      int ch = x.first;

      if(!m_useMatrix){
	m_recoBornVal   [m_diffVars[v]][ch] = new std::vector<std::pair<double,double> >();
	m_recoDresVal   [m_diffVars[v]][ch] = new std::vector<std::pair<double,double> >();
	m_recoBornRaw   [m_diffVars[v]][ch] = new std::vector<std::pair<double,double> >();
	m_recoDresRaw   [m_diffVars[v]][ch] = new std::vector<std::pair<double,double> >();
	m_recoBornValInt[m_diffVars[v]]     -> push_back(std::make_pair(0,0));
	m_recoDresValInt[m_diffVars[v]]     -> push_back(std::make_pair(0,0));
	m_recoBornRawInt[m_diffVars[v]]     -> push_back(std::make_pair(0,0));
	m_recoDresRawInt[m_diffVars[v]]     -> push_back(std::make_pair(0,0));
      }
      
      if(!m_keepTruth){
	m_fidBornVal[m_diffVars[v]][ch] = new std::vector<double>();
	m_fidDresVal[m_diffVars[v]][ch] = new std::vector<double>();
	m_truthVal  [m_diffVars[v]][ch] = new std::vector<double>();
	m_fidBornRaw[m_diffVars[v]][ch] = new std::vector<double>();
	m_fidDresRaw[m_diffVars[v]][ch] = new std::vector<double>();
	m_truthRaw  [m_diffVars[v]][ch] = new std::vector<double>();
	
	m_fidBornValInt[m_diffVars[v]]  -> push_back(0);
	m_fidDresValInt[m_diffVars[v]]  -> push_back(0);
	m_truthValInt  [m_diffVars[v]]  -> push_back(0);
	m_fidBornRawInt[m_diffVars[v]]  -> push_back(0);
	m_fidDresRawInt[m_diffVars[v]]  -> push_back(0);
	m_truthRawInt  [m_diffVars[v]]  -> push_back(0);
      }
      
      for(int b=0; b<nbins; b++){

	if(!m_useMatrix){
	  m_recoBornVal[m_diffVars[v]][ch] -> push_back(std::make_pair(0,0));
	  m_recoDresVal[m_diffVars[v]][ch] -> push_back(std::make_pair(0,0));
	  m_recoBornRaw[m_diffVars[v]][ch] -> push_back(std::make_pair(0,0));
	  m_recoDresRaw[m_diffVars[v]][ch] -> push_back(std::make_pair(0,0));
	}
	
	if(!m_keepTruth){
	  m_fidBornVal[m_diffVars[v]][ch] -> push_back(0);
	  m_fidDresVal[m_diffVars[v]][ch] -> push_back(0);
	  m_truthVal  [m_diffVars[v]][ch] -> push_back(0);
	  m_fidBornRaw[m_diffVars[v]][ch] -> push_back(0);
	  m_fidDresRaw[m_diffVars[v]][ch] -> push_back(0);
	  m_truthRaw  [m_diffVars[v]][ch] -> push_back(0);
	}
	
      }

    }
    
  }
  
}

void CreateInputs::EvaluateACRfactors(){

  PRINT("<CreateInputs::EvaluateACRfactors()>:: Processing Sample = "+m_ProcStr+" ... ");
  
  for(auto &mp: m_SysMap){
    
    PRINT("                                       Systematic = "+
	  std::to_string(mp.first)+" ("+mp.second+")");
    
    DefineOutFile(mp.first);
    SetChains(mp.first);
    DefineHistograms(mp.first);
    DefineValuesMaps();
    RunACRfactors(mp.first);

    for(uint v=0; v<m_diffVars.size(); v++){
      WriteACRfactors(m_diffVars[v]);
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
    m_HcFBornMap.clear();
    m_HcFDresMap.clear();
    m_HfNFabsBornMap.clear();
    m_HfNFabsDresMap.clear();
    m_HfNFrelBornMap.clear();
    m_HfNFrelDresMap.clear();
    m_HaFBornMap.clear();
    m_HaFDresMap.clear();
    m_HrFmap.clear();
    m_recoBornVal.clear();
    m_recoDresVal.clear();
    m_recoBornRaw.clear();
    m_recoDresRaw.clear();
    m_recoBornValInt.clear();
    m_recoDresValInt.clear();
    m_recoBornRawInt.clear();
    m_recoDresRawInt.clear();
    if(!m_keepTruth){
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

void CreateInputs::WriteACRfactors(std::string var){
  
  SetInfoLevel(m_acrDetails);

  PRINT_DEBUG("CreateInputs::WriteACRfactor()>:: Writing A, C, R values for variable "+
		var);
  
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
 
  WriteCFvalues(Bins,OutDir+"Born/",var);
  WriteCFvalues(Bins,OutDir+"Dressed/",var);
  WriteFnonFidValues(Bins,OutDir+"Born/",var);
  WriteFnonFidValues(Bins,OutDir+"Dressed/",var);
  WriteACCvalues(Bins,OutDir+"Born/",var);
  WriteACCvalues(Bins,OutDir+"Dressed/",var);
  WriteRvalues(Bins,OutDir,var);
  WriteNvalues(Bins,OutDir,var);
  
}

void CreateInputs::WriteFirstLine(){

  PRINT_VERBOSE("<CreateInputs::WriteFirstLine()>:: writing first line to file ... ");

  m_OutF.width(3);  m_OutF << std::left << "Bin";
  m_OutF.width(28); m_OutF << std::right << m_ChMap[Channel::_incl];
  m_OutF.width(28); m_OutF << std::right << m_ChMap[Channel::_4mu];
  m_OutF.width(28); m_OutF << std::right << m_ChMap[Channel::_4e];
  m_OutF.width(28); m_OutF << std::right << m_ChMap[Channel::_2mu2e];
  m_OutF.width(28); m_OutF << std::right << m_ChMap[Channel::_2e2mu];
  m_OutF.width(28); m_OutF << std::right << m_ChMap[Channel::_2l2l];
  m_OutF.width(28); m_OutF << std::right << m_ChMap[Channel::_4l] << std::endl;
  
}

void CreateInputs::WriteCFvalues(int Bins, std::string OutDir, std::string var){

  PRINT_VALUES("<CreateInputs::WriteCFvalues()>:: writing cF values to file ... ");

  bool isBorn = OutDir.find("Born")!=std::string::npos;
  if(!m_doSystematics){
    m_OutF.open( OutDir+"cF_"+m_ProcStr+"_"+std::to_string(m_Nbins)+"bin.dat");
    WriteFirstLine();
  }
  for(int i=0; i<Bins; i++){

    m_OutF.width(3); m_OutF << std::left << i;

    for(auto& x: m_ChMap){
      
      PRINT_VALUES("                                  channel = "+x.second+" , bin = "+std::to_string(i));
      int ch = x.first;
      m_OutF.width(14);
      double cF = 0, err = 0;
      if(isBorn){
	PRINT_VALUES("                                    Born -> num (reco) = ("+
		     std::to_string(m_recoBornVal[var][ch]->at(i).first)+","+
		     std::to_string(m_recoBornRaw[var][ch]->at(i).first)+
		     "),  den (truth sel) = ("+
		     std::to_string(m_fidBornVal[var][ch]->at(i))+","+
		     std::to_string(m_fidBornRaw[var][ch]->at(i))+")");

	cF  = m_recoBornVal[var][ch]->at(i).first/m_fidBornVal[var][ch]->at(i);
	err = DeriveValueError( GetNumberOfEvents(m_recoBornVal[var][ch]->at(i).first,
						  m_recoBornRaw[var][ch]->at(i).first,
						  m_recoBornValInt[var]->at(ch).first,
						  m_recoBornRawInt[var]->at(ch).first),
				m_recoBornVal[var][ch]->at(i).first/m_fidBornVal[var][ch]->at(i) );

	if( !std::isfinite(cF)  ) cF  = 0.0;
	if( !std::isfinite(err) ) err = 0.0;
	m_OutF << std::right << cF;
	m_OutF.width(14);
	m_OutF << std::right << err;

	m_HcFBornMap[var].at(ch)->SetBinContent(i+1,cF);
	m_HcFBornMap[var].at(ch)->SetBinError(i+1,err);
      }
      else{
	PRINT_VALUES("                                    Dres -> num (reco) = ("+
		     std::to_string(m_recoDresVal[var][ch]->at(i).first)+","+
		     std::to_string(m_recoDresRaw[var][ch]->at(i).first)+
		     "),  den (truth sel) = ("+
		     std::to_string(m_fidDresVal[var][ch]->at(i))+","+
		     std::to_string(m_fidDresRaw[var][ch]->at(i))+")");

	cF  = m_recoDresVal[var][ch]->at(i).first/m_fidDresVal[var][ch]->at(i);
	err = DeriveValueError( GetNumberOfEvents(m_recoDresVal[var][ch]->at(i).first,
						  m_recoDresRaw[var][ch]->at(i).first,
						  m_recoDresValInt[var]->at(ch).first,
						  m_recoDresRawInt[var]->at(ch).first),
				m_recoDresVal[var][ch]->at(i).first/m_fidDresVal[var][ch]->at(i) );

	if( !std::isfinite(cF)  ) cF  = 0.0;
	if( !std::isfinite(err) ) err = 0.0;
	m_OutF << std::right << cF;
	m_OutF.width(14);
	m_OutF << std::right << err;

	m_HcFDresMap[var].at(ch)->SetBinContent(i+1,cF);
	m_HcFDresMap[var].at(ch)->SetBinError(i+1,err);
      }
      PRINT_VALUES("                                             cF = "+std::to_string(cF)+
		   " +- "+std::to_string(err));
      
    }
    if(i!=Bins-1)
      m_OutF << std::endl;
    
  }
  if(!m_doSystematics)
    m_OutF.close();
  
}

void CreateInputs::WriteFnonFidValues(int Bins, std::string OutDir, std::string var){
  
  PRINT_VALUES("<CreateInputs::WriteFnonFidValues()>:: writing fnonFid values to file ... ");
  bool isBorn = OutDir.find("Born")!=std::string::npos;
  if(!m_doSystematics){
    m_OutF.open( OutDir+"fNonFid_"+m_ProcStr+"_"+std::to_string(m_Nbins)+"bin.dat");
    WriteFirstLine();
  }
  for(int i=0; i<Bins; i++){
    
    m_OutF.width(3); m_OutF << std::left << i;
    
    for(auto& x: m_ChMap){
      
      PRINT_VALUES("                                  channel = "+x.second+" , bin = "+std::to_string(i));
      int ch = x.first;
      double absV = 0, relV=0;
      m_OutF.width(14);
      if(isBorn){
	PRINT_VALUES("                                    Born leptons");
	absV = m_recoBornVal[var][ch]->at(i).second;
	relV = m_recoBornVal[var][ch]->at(i).second/(m_recoBornVal[var][ch]->at(i).first+m_recoBornVal[var][ch]->at(i).second);
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
	absV = m_recoDresVal[var][ch]->at(i).second;
	relV = m_recoDresVal[var][ch]->at(i).second/(m_recoDresVal[var][ch]->at(i).first+m_recoDresVal[var][ch]->at(i).second);
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

void CreateInputs::WriteACCvalues(int Bins, std::string OutDir, std::string var){

  PRINT_VALUES("<CreateInputs::WriteACCvalues()>:: writing aF values to file ... ");

  bool isBorn = OutDir.find("Born")!=std::string::npos;
  if(!m_doSystematics){
    m_OutF.open( OutDir+"aF_"+m_ProcStr+"_"+std::to_string(m_Nbins)+"bin.dat");
    WriteFirstLine();
  }
  for(int i=0; i<Bins; i++){
    
    m_OutF.width(3); m_OutF << std::left << i;
    
    for(auto& x: m_ChMap){
      
      PRINT_VALUES("                                  channel = "+x.second+" , bin = "+std::to_string(i));
      int ch = x.first;
      m_OutF.width(14);
      double aF = 0, err = 0;
      if(isBorn){
	PRINT_VALUES("                                    Born -> num (truth sel) = "+
		     std::to_string(m_fidBornVal[var][ch]->at(i))+"  den (truth) = "+
		     std::to_string(m_truthVal[var][ch]->at(i)) );
	aF  = m_fidBornVal[var][ch]->at(i)/m_truthVal[var][ch]->at(i);
	err = DeriveValueError( GetNumberOfEvents(m_fidBornVal[var][ch]->at(i),
						  m_fidBornRaw[var][ch]->at(i),
						  m_fidBornValInt[var]->at(ch),
						  m_fidBornRawInt[var]->at(ch)),
				m_fidBornVal[var][ch]->at(i)/m_truthVal[var][ch]->at(i) );

	if( !std::isfinite(aF)  ) aF  = 0.0;
	if( !std::isfinite(err) ) err = 0.0;
	m_OutF << std::right << aF;
	m_OutF.width(14);
	m_OutF << std::right << err;

	m_HaFBornMap[var].at(ch)->SetBinContent(i+1,aF);
	m_HaFBornMap[var].at(ch)->SetBinError(i+1,err);
      }
      else{
	PRINT_VALUES("                                    Dres -> num (truth sel) = "+
                      std::to_string(m_fidDresVal[var][ch]->at(i))+"  den (truth) = "+
		      std::to_string(m_truthVal[var][ch]->at(i)) );
	aF  = m_fidDresVal[var][ch]->at(i)/m_truthVal[var][ch]->at(i);
	err = DeriveValueError( GetNumberOfEvents(m_fidDresVal[var][ch]->at(i),
						  m_fidDresRaw[var][ch]->at(i),
						  m_fidDresValInt[var]->at(ch),
						  m_fidDresRawInt[var]->at(ch)),
				m_fidDresVal[var][ch]->at(i)/m_truthVal[var][ch]->at(i) );

	if( !std::isfinite(aF)  ) aF  = 0.0;
	if( !std::isfinite(err) ) err = 0.0;
	m_OutF << std::right << aF;
	m_OutF.width(14);
	m_OutF << std::right << err;

	m_HaFDresMap[var].at(ch)->SetBinContent(i+1,aF);
	m_HaFDresMap[var].at(ch)->SetBinError(i+1,err);
      }
      PRINT_VALUES("                                             aF = "+std::to_string(aF)+
                   " +- "+std::to_string(err));
      
    }
    if(i!=Bins-1)
      m_OutF << std::endl;
    
  }
  if(!m_doSystematics)
    m_OutF.close();
  
}

void CreateInputs::WriteRvalues(int Bins, std::string OutDir, std::string var){

  PRINT_VALUES("<CreateInputs::WriteRvalues()>:: writing R values to file ... ");

  if(!m_doSystematics){
    m_OutF.open( OutDir+"rF_"+m_ProcStr+"_"+std::to_string(m_Nbins)+"bin.dat");
    WriteFirstLine();
  }
  for(int i=0; i<Bins; i++){
    
    m_OutF.width(3); m_OutF << std::left << i;
    
    for(auto& x: m_ChMap){
      
      PRINT_VALUES("                                  channel = "+x.second+" , bin = "+std::to_string(i));
      int ch = x.first;
      m_OutF.width(14);
      double rF = 0, err = 0;
      rF  = m_truthVal[var][ch]->at(i)/m_truthInt->at(ch);
      err = DeriveValueError( GetNumberOfEvents(m_truthVal[var][ch]->at(i),
						m_truthRaw[var][ch]->at(i),
						m_truthValInt[var]->at(ch),
						m_truthRawInt[var]->at(ch)),
			      m_truthVal[var][ch]->at(i)/m_truthInt->at(ch) );
      if( !std::isfinite(rF)  ) rF  = 0.0;
      if( !std::isfinite(err) ) err = 0.0;
      m_OutF << std::right << rF;
      m_OutF.width(14); 
      m_OutF << std::right << err;
      m_HrFmap[var].at(ch)->SetBinContent(i+1,rF);
      m_HrFmap[var].at(ch)->SetBinError(i+1,err);
      PRINT_VALUES("                                    R = "+std::to_string(rF)+
		   " +- "+std::to_string(err));

    }
    if(i!=Bins-1)
      m_OutF << std::endl;
    
  }
  if(!m_doSystematics)
    m_OutF.close();
  
}

void CreateInputs::WriteNvalues(int Bins, std::string OutDir, std::string var){

  PRINT_VALUES("<CreateInputs::WriteNvalues()>:: writing N values to file ... ");

  if(!m_doSystematics){
    m_OutF.open( OutDir+"Nminitree_"+m_ProcStr+"_"+std::to_string(m_Nbins)+"bin.dat");
    WriteFirstLine();
  }
  for(int i=0; i<Bins; i++){
    m_OutF.width(3); m_OutF << std::left << i;
    for(auto& x: m_ChMap){
      PRINT_VALUES("                                  channel = "+x.second+" , bin = "+std::to_string(i));
      int ch = x.first;
      /* first element (from Born) should be equal to second one (from Dressed) */
      m_OutF.width(14);
      m_OutF << std::right << (m_recoBornVal[var][ch]->at(i).first+m_recoBornVal[var][ch]->at(i).second);
      m_OutF.width(14);
      m_OutF << std::right << (m_recoDresVal[var][ch]->at(i).first+m_recoDresVal[var][ch]->at(i).second);
      PRINT_VALUES("                                      nBorn = "+
		   std::to_string(m_recoBornVal[var][ch]->at(i).first+m_recoBornVal[var][ch]->at(i).second)+
		   " , nDres = "+std::to_string(m_recoDresVal[var][ch]->at(i).first+m_recoDresVal[var][ch]->at(i).second) );
    }
    if(i!=Bins-1)
      m_OutF << std::endl;
  }
  if(!m_doSystematics)
    m_OutF.close();
  
}

double CreateInputs::DeriveValueError(double nEvt, double eff){

  PRINT_VALUES("<CreateInputs::DeriveValueError()>:: deriving error for value ... ");
  PRINT_VALUES("                                     nEvt = "+std::to_string(nEvt)+
		" , eff = "+std::to_string(eff));
  double m_err = sqrt(nEvt*(1-eff)*eff)/nEvt;
  if(eff>1) m_err = eff;
  return m_err;
  
}

double CreateInputs::GetNumberOfEvents(double nEvtWgt, double nEvtRaw, double integral, double nRawTot){

  PRINT_VALUES("<CreateInputs::GetNumberOfEvents()>:: evaluating number of events ... ");
  PRINT_VALUES("                                      nEvtWgt = "+std::to_string(nEvtWgt)+
		" , nEvtRaw = "+std::to_string(nEvtRaw)+" , integral = "+std::to_string(integral)+
		" , nRawTot = "+std::to_string(nRawTot) );
  double m_nEvt = (nEvtWgt/integral)*nRawTot;
  PRINT_VALUES("                                      nEvt = "+std::to_string(m_nEvt)+" , nEvtRaw = "+
		std::to_string(nEvtRaw));
  return m_nEvt;
  
}
