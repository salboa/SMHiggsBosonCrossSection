#include "EventLoop.h"

void EventLoop::FillRecoValues(bool keepTruth){

  PRINT_VERBOSE("<EventLoop::FillRecoValues()>:: filling reco values ... ");
  
  for(uint v=0; v<m_diffVars.size(); v++){
    
    int vNum = GetVariableID( m_diffVars[v] );
    int bin  = GetVariableBin( vNum,mcType::Reco );

    if( PassCondition( vNum,bin,mcType::Reco ) ){
      
      bool m_isNonFidBorn = false, m_isNonFidDres = false;

      if(m_doTruthMatch){

	int binBo = -1, binDr = -1;

	/* ROOT Truth Matching */
	if(m_useRootTruthMatch){
	  Int_t treeEntry = PerformTruthMatching(event,run);
	  if(treeEntry>-1){
	    m_ThChain->GetEntry(treeEntry);
	    
	    /* overwrite jet variables if restricted phase space is enabled */
	    EvaluateJetVariables(mcType::Born);
	    EvaluateJetVariables(mcType::Dres);
	    
	    int binBo = GetVariableBin( vNum,mcType::Born );
	    int binDr = GetVariableBin( vNum,mcType::Dres );
	    
	    if( bin!=binBo      || !PassCondition( vNum,bin,mcType::Born ) ||
		thevtType_truth>3 || !PassMassChanFidCondition(mcType::Born) ||
		!PassTruthMassCut() ||
		event_type!=GetVariableValue(Variable::evtype,mcType::Born) )
	      m_isNonFidBorn = true;
	    if( bin!=binDr      || !PassCondition( vNum,bin,mcType::Dres ) ||
		thevtType_truth>3 || !PassMassChanFidCondition(mcType::Dres) ||
		!PassTruthMassCut() ||
                event_type!=GetVariableValue(Variable::evtype,mcType::Dres) )
	      m_isNonFidDres = true;
	  }
	}
	
	/* Alternative Truth Matching */
	else{
	  short int pos = vNum;
	  short int evtTypeBo = -1;
	  short int evtTypeDr = -1;
	  if(m_diffVars.size()==1) pos=1;
	  if(m_thMtc_Born[run].find(event)!=m_thMtc_Born[run].end() ){
	    binBo     = m_thMtc_Born[run][event].at(pos);
	    evtTypeBo = m_thMtc_Born[run][event].at(0);
	  }
	  
	  if(m_thMtc_Dres[run].find(event)!=m_thMtc_Dres[run].end() ){
	    binDr     = m_thMtc_Dres[run][event].at(pos);
	    evtTypeDr = m_thMtc_Dres[run][event].at(0);
	  }
	  
	  if( bin!=binBo || event_type!=evtTypeBo ) m_isNonFidBorn = true;
	  if( bin!=binDr || event_type!=evtTypeDr ) m_isNonFidDres = true;
	}
	
      }

      PRINT_VERBOSE("                                isNonFidBorn = "+
		    std::to_string(m_isNonFidBorn)+" , isNonFidDres = "+
		    std::to_string(m_isNonFidDres));

      if(m_isNonFidBorn){
	
	m_RecoBornVal[m_diffVars[v]][Channel::_incl]->at( bin ).second += mFinWgt;
	m_RecoBornVal[m_diffVars[v]][event_type+1]  ->at( bin ).second += mFinWgt;
	m_RecoBornVal[m_diffVars[v]][m_mrgChan]     ->at( bin ).second += mFinWgt;

	m_RecoBornRaw[m_diffVars[v]][Channel::_incl]->at( bin ).second += 1;
	m_RecoBornRaw[m_diffVars[v]][event_type+1]  ->at( bin ).second += 1;
	m_RecoBornRaw[m_diffVars[v]][m_mrgChan]     ->at( bin ).second += 1;

	m_RecoBornValInt[m_diffVars[v]]->at( Channel::_incl ).second += mFinWgt;
	m_RecoBornValInt[m_diffVars[v]]->at( event_type+1   ).second += mFinWgt;
	m_RecoBornValInt[m_diffVars[v]]->at( m_mrgChan      ).second += mFinWgt;

	m_RecoBornRawInt[m_diffVars[v]]->at( Channel::_incl ).second += 1;
	m_RecoBornRawInt[m_diffVars[v]]->at( event_type+1   ).second += 1;
	m_RecoBornRawInt[m_diffVars[v]]->at( m_mrgChan      ).second += 1;
	
      }
      else{
	
	m_RecoBornVal[m_diffVars[v]][Channel::_incl]->at( bin ).first += mFinWgt;
	m_RecoBornVal[m_diffVars[v]][event_type+1]  ->at( bin ).first += mFinWgt;
	m_RecoBornVal[m_diffVars[v]][m_mrgChan]     ->at( bin ).first += mFinWgt;
	
	m_RecoBornRaw[m_diffVars[v]][Channel::_incl]->at( bin ).first += 1;
	m_RecoBornRaw[m_diffVars[v]][event_type+1]  ->at( bin ).first += 1;
	m_RecoBornRaw[m_diffVars[v]][m_mrgChan]     ->at( bin ).first += 1;
	
	m_RecoBornValInt[m_diffVars[v]]->at( Channel::_incl ).first += mFinWgt;
	m_RecoBornValInt[m_diffVars[v]]->at( event_type+1   ).first += mFinWgt;
	m_RecoBornValInt[m_diffVars[v]]->at( m_mrgChan      ).first += mFinWgt;
	
	m_RecoBornRawInt[m_diffVars[v]]->at( Channel::_incl ).first += 1;
	m_RecoBornRawInt[m_diffVars[v]]->at( event_type+1   ).first += 1;
	m_RecoBornRawInt[m_diffVars[v]]->at( m_mrgChan      ).first += 1;
	
      }
      if(m_isNonFidDres){
	
	m_RecoDresVal[m_diffVars[v]][Channel::_incl]->at( bin ).second += mFinWgt;
	m_RecoDresVal[m_diffVars[v]][event_type+1]  ->at( bin ).second += mFinWgt;
	m_RecoDresVal[m_diffVars[v]][m_mrgChan]     ->at( bin ).second += mFinWgt;
	
	m_RecoDresRaw[m_diffVars[v]][Channel::_incl]->at( bin ).second += 1;
	m_RecoDresRaw[m_diffVars[v]][event_type+1]  ->at( bin ).second += 1;
	m_RecoDresRaw[m_diffVars[v]][m_mrgChan]     ->at( bin ).second += 1;
	
	m_RecoDresValInt[m_diffVars[v]]->at( Channel::_incl ).second += mFinWgt;
	m_RecoDresValInt[m_diffVars[v]]->at( event_type+1   ).second += mFinWgt;
	m_RecoDresValInt[m_diffVars[v]]->at( m_mrgChan      ).second += mFinWgt;
	
	m_RecoDresRawInt[m_diffVars[v]]->at( Channel::_incl ).second += 1;
	m_RecoDresRawInt[m_diffVars[v]]->at( event_type+1   ).second += 1;
	m_RecoDresRawInt[m_diffVars[v]]->at( m_mrgChan      ).second += 1;
	
      }
      else{
	
	m_RecoDresVal[m_diffVars[v]][Channel::_incl]->at( bin ).first += mFinWgt;
	m_RecoDresVal[m_diffVars[v]][event_type+1]  ->at( bin ).first += mFinWgt;
	m_RecoDresVal[m_diffVars[v]][m_mrgChan]     ->at( bin ).first += mFinWgt;
	
	m_RecoDresRaw[m_diffVars[v]][Channel::_incl]->at( bin ).first += 1;
	m_RecoDresRaw[m_diffVars[v]][event_type+1]  ->at( bin ).first += 1;
	m_RecoDresRaw[m_diffVars[v]][m_mrgChan]     ->at( bin ).first += 1;
	
	m_RecoDresValInt[m_diffVars[v]]->at( Channel::_incl ).first += mFinWgt;
	m_RecoDresValInt[m_diffVars[v]]->at( event_type+1   ).first += mFinWgt;
	m_RecoDresValInt[m_diffVars[v]]->at( m_mrgChan      ).first += mFinWgt;
	
	m_RecoDresRawInt[m_diffVars[v]]->at( Channel::_incl ).first += 1;
	m_RecoDresRawInt[m_diffVars[v]]->at( event_type+1   ).first += 1;
	m_RecoDresRawInt[m_diffVars[v]]->at( m_mrgChan      ).first += 1;
	
      }
      
    } 
    
  }
  if(m_doTruthMatch && !m_useRootTruthMatch && !keepTruth){
    
    if(m_thMtc_Born[run].find(event)!=m_thMtc_Born[run].end() ) m_thMtc_Born[run].erase(event);
    if(m_thMtc_Dres[run].find(event)!=m_thMtc_Dres[run].end() ) m_thMtc_Dres[run].erase(event);
    
  }
  
}

void EventLoop::FillRecoValues4Mtx(bool keepTruth){

  PRINT_VERBOSE("<EventLoop::FillRecoValues4Mtx()>:: filling reco values ... ");
  
  for(uint v=0; v<m_diffVars.size(); v++){
    
    int vNum = GetVariableID( m_diffVars[v] );
    int bin  = GetVariableBin(vNum,mcType::Reco);

    if( PassCondition( vNum,bin,mcType::Reco ) ){
      
      bool m_isNonFidBorn = false, m_isNonFidDres = false;
      int binBo = -1, binDr = -1;
      
      /* ROOT Truth Matching */
      if(m_useRootTruthMatch){
	Int_t treeEntry = PerformTruthMatching(event,run);
	if(treeEntry>-1) {
	  m_ThChain->GetEntry(treeEntry);
	  
	  /* overwrite jet variables if restricted phase space is enabled */
	  EvaluateJetVariables(mcType::Born);
	  EvaluateJetVariables(mcType::Dres);
	  
	  int binBo = GetVariableBin( vNum,mcType::Born );
	  int binDr = GetVariableBin( vNum,mcType::Dres );
	  
	  if( binBo==-1           || !PassCondition( vNum,bin,mcType::Born ) ||
	      !PassTruthMassCut() || !PassMassChanFidCondition(mcType::Born) ||
	      thevtType_truth>3   ||
	      event_type!=GetVariableValue(Variable::evtype,mcType::Born)     )
	    m_isNonFidBorn = true;
	  
	  if( binDr==-1           || !PassCondition( vNum,bin,mcType::Dres ) ||
	      !PassTruthMassCut() || !PassMassChanFidCondition(mcType::Dres) ||
	      thevtType_truth>3   ||
	      event_type!=GetVariableValue(Variable::evtype,mcType::Dres)     )
	    m_isNonFidDres = true;
	}
      }
      /* Alternative Truth Matching */
      else{
	
	short int pos       = vNum;
	short int evtTypeBo = -1;
	short int evtTypeDr = -1;
	if(m_diffVars.size()==1) pos=1;
	
	if(m_thMtc_Born[run].find(event)!=m_thMtc_Born[run].end() ){
	  binBo     = m_thMtc_Born[run][event].at(pos);
	  evtTypeBo = m_thMtc_Born[run][event].at(0);
	}
	
	if(m_thMtc_Dres[run].find(event)!=m_thMtc_Dres[run].end() ){
	  binDr     = m_thMtc_Dres[run][event].at(pos);
	  evtTypeDr = m_thMtc_Dres[run][event].at(0);
	}
	
	if( binBo==-1 || event_type!=evtTypeBo ) m_isNonFidBorn = true;
	if( binDr==-1 || event_type!=evtTypeDr ) m_isNonFidDres = true;
	
      }
      
      if( m_isNonFidBorn ){
	
	m_NonFidBorn[m_diffVars[v]][Channel::_incl]->at(bin) += mFinWgt;
	m_NonFidBorn[m_diffVars[v]][event_type+1]->at(bin)   += mFinWgt;
	m_NonFidBorn[m_diffVars[v]][m_mrgChan]->at(bin)      += mFinWgt;
	
      }
      else{
	
	m_RspMtxBorn_Num[m_diffVars[v]][Channel::_incl][bin]->at(binBo) += mFinWgt;
	m_RspMtxBorn_Num[m_diffVars[v]][event_type+1][bin]->at(binBo)   += mFinWgt;
	m_RspMtxBorn_Num[m_diffVars[v]][m_mrgChan][bin]->at(binBo)      += mFinWgt;
	
      }
      
      if(m_isNonFidDres){
	
	m_NonFidDres[m_diffVars[v]][Channel::_incl]->at(bin) += mFinWgt;
	m_NonFidDres[m_diffVars[v]][event_type+1]->at(bin)   += mFinWgt;
	m_NonFidDres[m_diffVars[v]][m_mrgChan]->at(bin)      += mFinWgt;
	
      }
      else{
	
	m_RspMtxDres_Num[m_diffVars[v]][Channel::_incl][bin]->at(binDr) += mFinWgt;
	m_RspMtxDres_Num[m_diffVars[v]][event_type+1][bin]->at(binDr)   += mFinWgt;
	m_RspMtxDres_Num[m_diffVars[v]][m_mrgChan][bin]->at(binDr)      += mFinWgt;
	
      }
      
    }
    
  }
  if(!m_useRootTruthMatch && !keepTruth){
    
    if(m_thMtc_Born[run].find(event)!=m_thMtc_Born[run].end() ) m_thMtc_Born[run].erase(event);
    if(m_thMtc_Dres[run].find(event)!=m_thMtc_Dres[run].end() ) m_thMtc_Dres[run].erase(event);
    
  }
  
}

void EventLoop::FillTruthValues(){

  PRINT_VERBOSE("<EventLoop::FillTruthValues()>:: filling truth values ... ");
  
  /* Integral over whole particle level phase space */
  if( m_passThMassCut && thevtType_truth<4 ){
    
    m_TruthInt->at( Channel::_incl    ) += mThFinWgt;
    m_TruthInt->at( thevtType_truth+1 ) += mThFinWgt;
    m_TruthInt->at( m_mrgThChanTruth  ) += mThFinWgt;
    
    m_TruthIntRaw->at( Channel::_incl    ) += 1;
    m_TruthIntRaw->at( thevtType_truth+1 ) += 1;
    m_TruthIntRaw->at( m_mrgThChanTruth  ) += 1;
    

    for(uint v=0; v<m_diffVars.size(); v++){
      
      int vNum = GetVariableID( m_diffVars[v] );
      
      /* born leptons case */
      PRINT_VERBOSE("                                 filling born values ... ");
      if( m_passBornMassChan ){
	
	int bin = GetVariableBin( vNum,mcType::Born );
	
	if( PassCondition( vNum,bin,mcType::Born ) ){
	  
	  m_FidBornVal[m_diffVars[v]][Channel::_incl]     ->at( bin ) += mThFinWgt;
	  m_FidBornVal[m_diffVars[v]][thevtType_fidBorn+1]->at( bin ) += mThFinWgt;
	  m_FidBornVal[m_diffVars[v]][m_mrgThChanFidBorn] ->at( bin ) += mThFinWgt;
	  
	  m_FidBornRaw[m_diffVars[v]][Channel::_incl]     ->at( bin ) += 1;
	  m_FidBornRaw[m_diffVars[v]][thevtType_fidBorn+1]->at( bin ) += 1;
	  m_FidBornRaw[m_diffVars[v]][m_mrgThChanFidBorn] ->at( bin ) += 1;
	  
	  m_FidBornValInt[m_diffVars[v]]->at( Channel::_incl      ) += mThFinWgt;
	  m_FidBornValInt[m_diffVars[v]]->at( thevtType_fidBorn+1 ) += mThFinWgt;
	  m_FidBornValInt[m_diffVars[v]]->at( m_mrgThChanFidBorn  ) += mThFinWgt;
	  
	  m_FidBornRawInt[m_diffVars[v]]->at( Channel::_incl      ) += 1;
	  m_FidBornRawInt[m_diffVars[v]]->at( thevtType_fidBorn+1 ) += 1;
	  m_FidBornRawInt[m_diffVars[v]]->at( m_mrgThChanFidBorn  ) += 1;

          if (m_useMatrix){
  	    m_RspMtxBorn_Denom[m_diffVars[v]][Channel::_incl]->at(bin)      += mThFinWgt;
	    m_RspMtxBorn_Denom[m_diffVars[v]][thevtType_fidBorn+1]->at(bin) += mThFinWgt;
	    m_RspMtxBorn_Denom[m_diffVars[v]][m_mrgThChanFidBorn]->at(bin)  += mThFinWgt;
	  }
	  
	}
	
      }
      
      /* dressed leptons case */
      PRINT_VERBOSE("                                 filling dressed values ... ");
      if( m_passDresMassChan ){
	
	int bin = GetVariableBin( vNum,mcType::Dres );

	if( PassCondition( vNum,bin,mcType::Dres ) ){
	  
	  m_FidDresVal[m_diffVars[v]][Channel::_incl]     ->at( bin ) += mThFinWgt;
	  m_FidDresVal[m_diffVars[v]][thevtType_fidDres+1]->at( bin ) += mThFinWgt;
	  m_FidDresVal[m_diffVars[v]][m_mrgThChanFidDres] ->at( bin ) += mThFinWgt;
	  
	  m_FidDresRaw[m_diffVars[v]][Channel::_incl]     ->at( bin ) += 1;
	  m_FidDresRaw[m_diffVars[v]][thevtType_fidDres+1]->at( bin ) += 1;
	  m_FidDresRaw[m_diffVars[v]][m_mrgThChanFidDres] ->at( bin ) += 1;
	  
	  m_FidDresValInt[m_diffVars[v]]->at( Channel::_incl      ) += mThFinWgt;
	  m_FidDresValInt[m_diffVars[v]]->at( thevtType_fidDres+1 ) += mThFinWgt;
	  m_FidDresValInt[m_diffVars[v]]->at( m_mrgThChanFidDres  ) += mThFinWgt;
	  
	  m_FidDresRawInt[m_diffVars[v]]->at( Channel::_incl      ) += 1;
	  m_FidDresRawInt[m_diffVars[v]]->at( thevtType_fidDres+1 ) += 1;
	  m_FidDresRawInt[m_diffVars[v]]->at( m_mrgThChanFidDres  ) += 1;

          if (m_useMatrix){
	    m_RspMtxDres_Denom[m_diffVars[v]][Channel::_incl]->at(bin)      += mThFinWgt;
	    m_RspMtxDres_Denom[m_diffVars[v]][thevtType_fidDres+1]->at(bin) += mThFinWgt;
	    m_RspMtxDres_Denom[m_diffVars[v]][m_mrgThChanFidDres]->at(bin)  += mThFinWgt;
	  }
	  
	}
	
      }
      
      /* truth particle level */
      PRINT_VERBOSE("                                 filling truth values ... ");
            
      int bin = GetVariableBin( vNum,mcType::Truth );
      
      if( PassCondition( vNum,bin,mcType::Truth ) ){

	m_TruthVal[m_diffVars[v]][Channel::_incl]   ->at( bin ) += mThFinWgt;
	m_TruthVal[m_diffVars[v]][thevtType_truth+1]->at( bin ) += mThFinWgt;
	m_TruthVal[m_diffVars[v]][m_mrgThChanTruth] ->at( bin ) += mThFinWgt;
	
	m_TruthRaw[m_diffVars[v]][Channel::_incl]   ->at( bin ) += 1;
	m_TruthRaw[m_diffVars[v]][thevtType_truth+1]->at( bin ) += 1;
	m_TruthRaw[m_diffVars[v]][m_mrgThChanTruth] ->at( bin ) += 1;
	
	m_TruthValInt[m_diffVars[v]]->at( Channel::_incl    ) += mThFinWgt;
	m_TruthValInt[m_diffVars[v]]->at( thevtType_truth+1 ) += mThFinWgt;
	m_TruthValInt[m_diffVars[v]]->at( m_mrgThChanTruth  ) += mThFinWgt;
	
	m_TruthRawInt[m_diffVars[v]]->at( Channel::_incl    ) += 1;
	m_TruthRawInt[m_diffVars[v]]->at( thevtType_truth+1 ) += 1;
	m_TruthRawInt[m_diffVars[v]]->at( m_mrgThChanTruth  ) += 1;
	
      }

      
    }
    
  }
  
}
