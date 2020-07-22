#include "EventLoop.h"

void EventLoop::Loop(bool setChain, bool isPreTruthMatch, bool keepTruth){

  PRINT_DEBUG("<EventLoop::Loop()>:: Starting loop on reco events ... ");
  
  m_procEvts.clear();
  if(setChain){
    m_Chain->SetBranchStatus("*",0);
    SetChainBranches();
  }
  
  Int_t Nentries = (Int_t)m_Chain->GetEntries();

  /* opening EventList file */
  if(m_EvtList)
    m_OutF.open( "../varsDistro/"+GetProcessName(m_Process)+"_"+ m_mcTypeMap[m_mcType]+
		 "_eventList.dat");
  
  mFinWgt = 1;
  for(Int_t en=0; en<Nentries; en++){
    m_Chain->GetEntry(en);

    if( en % 100000 == 0 )
      PRINT_DEBUG("<EventLoop::Loop()>:: processed "+std::to_string(en)+" events ... ");
    
    std::string curFile = m_Chain->GetCurrentFile()->GetName();
    PRINT_VERBOSE("<Loop()>:: Processing file: "+curFile);
    m_IntProdMode = CheckInternalProdMode(curFile);

    /* Sanity check on jet vector size vs Njets value */
    if( (int)jet_pt->size()!=njets ){
      PRINT_WARNING("<EventLoop::Loop()>:: Found n_jets/jet_var.size mis-match in process "+GetProcessName(m_Process)+
                    " -> (Run = "+std::to_string(run)+", Event = "+std::to_string(event)+
                    ", File = "+curFile+")");
    }
    
    /* defining event weight */
    mFinWgt = GetWeight();
    mLumi   = GetLuminosity();
    if(m_Process!=Process::data) mFinWgt = mFinWgt/mLumi;

    /* scale process cross-section if sys/bias */
    mFinWgt = mFinWgt*DetectCrossSectionScale();
    
    if(m_Process==Process::MG5     || m_Process==Process::MG5KHvv ||
       m_Process==Process::MG5KAvv || m_Process==Process::MG5KAgg  ){
      
      if(event_type == Channel::_4mu || event_type == Channel::_4e)
	mFinWgt      = (GetWeight()/w_xs)*48600*0.00013/mLumi;
      if(event_type == Channel::_2mu2e || event_type == Channel::_2e2mu)
	mFinWgt      = (GetWeight()/w_xs)*48600*0.0001180/mLumi;
      
    }
    
    /* check for duplicates */
    double mcw = w_MCw; 
    if(m_Process==Process::data) mcw = 1;
    if(m_checkDuplicates){
      const std::tuple<Int_t,ULong64_t,double> RunEvt = std::make_tuple(run,event,mcw);
      if( m_procEvts.insert(RunEvt).second == false ){
	PRINT_WARNING("<EventLoop::Loop()>:: Found Possible Duplicate in process "+GetProcessName(m_Process)+
		      " -> Skipping! (Run = "+std::to_string(run)+", Event = "+std::to_string(event)+
		      ", wgt = "+std::to_string(weight)+", FinWgt = "+std::to_string(mFinWgt)+
		      ", evt_type = "+std::to_string(event_type)+", MCw = "+std::to_string(mcw)+
		      ", File = "+curFile+")");
	continue;
      }
    }
    
    PRINT_VERBOSE( "<Loop()>:: Processing sample "+std::to_string(m_Process)+
		   " --> Run "+std::to_string(run)+" Event "+
		   std::to_string(event)+" weight "+
		   std::to_string(GetWeight()) );
    
    /* -------------------------------------------*/
    /*               Event Type                   */
    /*  4mu = 0 , 4e = 1 , 2mu2e = 2 , 2e2mu = 3  */
    /* ------------------------------------------ */

    mFourLep = m4l_fsr;
    if(m_SystNum==Syst::SignalMassShift+1 || m_doShiftUp)     { mFourLep = mFourLep+m_hmShift; }
    else if(m_SystNum==Syst::SignalMassShift || m_doShiftDown){ mFourLep = mFourLep-m_hmShift; }
    
    /* Check mass window */
    if(m_isContReg){
      if( mFourLep>m_Min || mFourLep<m_Max ) continue;
    }
    else{
      if( mFourLep<m_Min || mFourLep>m_Max ) continue;
    }

    PRINT_VERBOSE( "<Loop()>:: entry (evtNumber) "+std::to_string(en)+" ("+
		   std::to_string(event)+") m4l "+std::to_string(mFourLep)+
		   " type "+std::to_string(event_type)+" weight "+
		   std::to_string(mFinWgt) );

    /* set 2l2l/4l category number */
    m_mrgChan = -1;
    if(event_type<2) m_mrgChan = Channel::_4l;
    else             m_mrgChan = Channel::_2l2l;

    /* Write event details to EventList file */
    if(m_EvtList){
      m_OutF.width(10);  m_OutF << std::right << run;
      m_OutF.width(14);  m_OutF << std::right << event;
      m_OutF.width(4);   m_OutF << std::right << event_type;
      m_OutF << std::endl;
    }

    /* overwrite jet variables if restricted phase space is enabled */
    if(!isPreTruthMatch){ EvaluateJetVariables(mcType::Reco); }

    /* Filling event map to be used for truth matching */
    if(isPreTruthMatch){ FillRecoEventsMap(); }
    
    /* Fill Values/Histograms */
    else{
      if(m_doACRfactor){
	if(m_useMatrix){ FillRecoValues4Mtx(keepTruth); }
	else           { FillRecoValues(keepTruth);     }
      }
      else{ FillHistograms(); }
    }
    
  }
  /* clean event duplication map */
  m_procEvts.clear();
  
  if(m_EvtList)       m_OutF.close();
  
}

void EventLoop::TruthLoop(){

  PRINT_DEBUG("<EventLoop::TruthLoop()>:: Starting loop on truth events ... ");
  
  m_procEvts.clear();
  
  m_ThChain->SetBranchStatus("*",0);
  SetTruthChainBranches();
  
  Int_t Nentries = (Int_t)m_ThChain->GetEntries();

  for(Int_t en=0; en<Nentries; en++){
    m_ThChain->GetEntry(en);

    if( en % 100000 == 0 )
      PRINT_DEBUG("<EventLoop::TruthLoop()>:: processed "+std::to_string(en)+" events ... ");
    
    std::string curFile = m_ThChain->GetCurrentFile()->GetName();
    PRINT_VERBOSE("<TruthLoop()>:: Processing file: "+curFile);
    m_IntProdMode = CheckInternalProdMode(curFile);
    
    mThFinWgt = GetTruthWeight()/GetLuminosity(true);

    /* scale process cross-section if sys/bias */
    mThFinWgt = mThFinWgt*DetectCrossSectionScale();

    if(m_Process==Process::MG5     || m_Process==Process::MG5KHvv ||
       m_Process==Process::MG5KAvv || m_Process==Process::MG5KAgg  ){

      if(thevtType_truth == Channel::_4mu || thevtType_truth == Channel::_4e)
        mThFinWgt = (GetTruthWeight()/w_thxs)*48600*0.00013/GetLuminosity(true);
      if(thevtType_truth == Channel::_2mu2e || thevtType_truth == Channel::_2e2mu)
        mThFinWgt = (GetTruthWeight()/w_thxs)*48600*0.0001180/GetLuminosity(true);

    }

    /* Check for duplicates */
    if(m_checkDuplicates){
      const std::tuple<Int_t,ULong64_t,double> RunEvt = std::make_tuple(thrun,thevent,w_thMCw);
      if( m_procEvts.insert(RunEvt).second == false ){
	PRINT_WARNING("<EventLoop::TruthLoop()>:: Found Duplicate in process "+GetProcessName(m_Process)+
		      " -> Skipping! (Run = "+std::to_string(thrun)+" , Event = "+std::to_string(thevent)+
		      ", wgt = "+std::to_string(thweight)+", ThFinWgt = "+std::to_string(mThFinWgt)+
		      ", evt_type = "+std::to_string(thevtType_truth)+", MCw = "+std::to_string(w_thMCw)+
		      ", File = "+curFile+")");
	continue;
      }
    }
    PRINT_VERBOSE("<TruthLoop()>:: entry (evtNumber) "+std::to_string(en)+
		  " ("+std::to_string(thevent)+") wgt "+
		  std::to_string(mThFinWgt) );

    /* set 2l2l/4l category number */
    m_mrgThChanFidBorn = -1, m_mrgThChanFidDres = -1, m_mrgThChanTruth = -1;
    if(thevtType_fidBorn<2) m_mrgThChanFidBorn = Channel::_4l;
    else                    m_mrgThChanFidBorn = Channel::_2l2l;
    if(thevtType_fidDres<2) m_mrgThChanFidDres = Channel::_4l;
    else                    m_mrgThChanFidDres = Channel::_2l2l;
    if(thevtType_truth<2)   m_mrgThChanTruth   = Channel::_4l;
    else                    m_mrgThChanTruth   = Channel::_2l2l;

    /* overwrite jet variables if restricted phase space is enabled */
    EvaluateJetVariables(mcType::Born);
    EvaluateJetVariables(mcType::Dres);
    EvaluateJetVariables(mcType::Truth);
    
    if(m_doACRfactor){
      SetGlobalTruthConditions(); 
      if(m_doTruthMatch && !m_useRootTruthMatch) FillTruthMatchingMaps(); 
      FillTruthValues(); 
    }        
  }
  /* clean event duplication map */
  m_procEvts.clear();
  
}

int EventLoop::CheckInternalProdMode(std::string file){

  PRINT_VERBOSE("<EventLoop::CheckInternalProdMode()>:: checking internal production mode ... ");
  
  int m_val = -1;
  if(file.find("ggH")!=std::string::npos)       { m_val = Process::ggH;  }
  else if(file.find("VBF")!=std::string::npos)  { m_val = Process::VBF;  }
  else if(file.find("WpH")!=std::string::npos)  { m_val = Process::WH;   }
  else if(file.find("WmH")!=std::string::npos)  { m_val = Process::WH;   }
  else if(file.find("ggZH")!=std::string::npos) { m_val = Process::ggZH; }
  else if(file.find("ZH")!=std::string::npos)   { m_val = Process::ZH;   }
  else if(file.find("ttH")!=std::string::npos)  { m_val = Process::ttH;  }
  else if(file.find("bbH")!=std::string::npos)  { m_val = Process::bbH;  }
  else if(file.find("tWH")!=std::string::npos)  { m_val = Process::tWH;  }
  else if(file.find("tHjb")!=std::string::npos) { m_val = Process::tHqb; }
  else if(file.find("_llll")!=std::string::npos){ m_val = Process::qqZZ; }
  
  PRINT_VERBOSE("                                       which is "+std::to_string(m_val));
  
  return m_val;
  
}

double EventLoop::GetLuminosity(bool isTruth){

  PRINT_VERBOSE("<EventLoop::GetLuminosity()>:: getting sample luminosity ... ");

  double m_lumi = 1;
  if(isTruth){
    if(m_mcType==MCtype::All) m_lumi = m_Lumi;
    else                      m_lumi = w_thlumi;
  }
  else{
    if(m_mcType==MCtype::All) m_lumi = m_Lumi;
    else                      m_lumi = w_lumi;
  }
  
  PRINT_VERBOSE("                                Luminosity = "+std::to_string(m_lumi));
  
  return m_lumi;
  
}

ULong64_t EventLoop::PerformTruthMatching(ULong64_t evt, Int_t run){

  PRINT_VERBOSE("<EventLoop::PerformTruthMatching()>:: perfoming reco/truth event matching ... ");

  Int_t m_entry = m_ThChain->GetEntryNumberWithIndex(run,evt);
  PRINT_VERBOSE("                                      event found at index = "+
		std::to_string(m_entry));
  
  return m_entry;
  
}

void EventLoop::FillTruthMatchingMaps(){

  PRINT_VERBOSE("<EventLoop::FillTruthMatchingMaps()>:: filling dressed/born maps to be used for truth matching ... ");
  
  if( m_thMtc_Reco[thrun].find(thevent)!=m_thMtc_Reco[thrun].end() ){
    m_thMtc_Reco[thrun].erase(thevent);
  }
  else return;
  
  if( m_passBornMassChan && m_passThMassCut && thevtType_truth<4 ){
    m_thMtc_Born[thrun][thevent].reserve(m_diffVars.size()+1);
    m_thMtc_Born[thrun][thevent].push_back(thevtType_fidBorn);
  }
  
  if( m_passDresMassChan && m_passThMassCut && thevtType_truth<4 ){
    m_thMtc_Dres[thrun][thevent].reserve(m_diffVars.size()+1);
    m_thMtc_Dres[thrun][thevent].push_back(thevtType_fidDres);
  }
  
  for(uint v=0; v<m_diffVars.size(); v++){
    
    int vNum  = GetVariableID( m_diffVars[v] );
    if( m_passBornMassChan && m_passThMassCut && thevtType_truth<4 ){
      
      double varValue = GetVariableValue( vNum,mcType::Born );
      int bin         = -1;
      if(vNum==Variable::m12m34)      bin = FindBin( vNum,GetVariableValue(Variable::m12,mcType::Born),
						     GetVariableValue(Variable::m34,mcType::Born) );
      else if(vNum==Variable::ptnjet) bin = FindBin( vNum,GetVariableValue(Variable::pt4l,mcType::Born),
						     GetVariableValue(Variable::njet,mcType::Born) );
      else if(vNum==Variable::pty4l)  bin = FindBin( vNum,GetVariableValue(Variable::pt4l,mcType::Born),
						     GetVariableValue(Variable::y4l,mcType::Born) );
      else                            bin = FindBin( vNum,varValue );
      
      if(!PassCondition( vNum,bin,mcType::Born )) bin = -1;
      m_thMtc_Born[thrun][thevent].push_back(bin);
    }

    if( m_passDresMassChan && m_passThMassCut && thevtType_truth<4 ){
      
      double varValue = GetVariableValue( vNum,mcType::Dres );
      int bin         = -1;
      if(vNum==Variable::m12m34)      bin = FindBin( vNum,GetVariableValue(Variable::m12,mcType::Dres),
						     GetVariableValue(Variable::m34,mcType::Dres) );
      else if(vNum==Variable::ptnjet) bin = FindBin( vNum,GetVariableValue(Variable::pt4l,mcType::Dres),
						     GetVariableValue(Variable::njet,mcType::Dres) );
      else if(vNum==Variable::pty4l)  bin = FindBin( vNum,GetVariableValue(Variable::pt4l,mcType::Dres),
						     GetVariableValue(Variable::y4l,mcType::Dres) );
      else                            bin = FindBin( vNum,varValue );
      
      if(!PassCondition( vNum,bin,mcType::Dres )) bin = -1;
      m_thMtc_Dres[thrun][thevent].push_back(bin);
    }
    
  }
  
}

void EventLoop::FillRecoEventsMap(){

  PRINT_VERBOSE("<EventLoop::FillRecoEventsMap()>:: filling reco events map for reco/truth event matching ... ");
  m_thMtc_Reco[run][event] = m_IntProdMode;
  
}

std::map<int, std::map<ULong64_t, std::vector<short int> > > EventLoop::GetTruthMatchingMap(int type){

  PRINT_VERBOSE("<EventLoop::GetBornTruthMatchingMap()> :: retrieving truth matching map for Born leptons ... ");
  switch(type){
  case mcType::Born: return m_thMtc_Born; break;
  case mcType::Dres: return m_thMtc_Dres; break;
  default:
    PRINT_FATAL("                                           not available truth matching map for "+
		std::to_string(type)+" ! exiting ... ");
    exit(0);
  }
  
}

double EventLoop::DetectCrossSectionScale(){

  PRINT_VERBOSE("EventLoop::DetectCrossSectionScale()>:: apply scale to signal process xsec ...");

  double m_scl = 1.;
  switch(m_SystNum){
    /* sum in quadrature of Theory and Pdf+alpha_s uncertainties */
  case Syst::SignalComposition_ggHbbH  :
    if(m_IntProdMode==Process::ggH)       m_scl = 1-sqrt( pow(0.067,2)+pow(0.032,2) );
    else if(m_IntProdMode==Process::bbH)  m_scl = 1-sqrt( pow(0.239,2) );
    break;
  case Syst::SignalComposition_ggHbbH+1:
    if(m_IntProdMode==Process::ggH)       m_scl = 1+sqrt( pow(0.046,2)+pow(0.032,2) );
    else if(m_IntProdMode==Process::bbH)  m_scl = 1+sqrt( pow(0.202,2) );
    break;
  case Syst::SignalComposition_VBF     :
    if(m_IntProdMode==Process::VBF)       m_scl = 1-sqrt( pow(0.003,2)+pow(0.021,2) );
    break;
  case Syst::SignalComposition_VBF+1   :
    if(m_IntProdMode==Process::VBF)       m_scl = 1+sqrt( pow(0.004,2)+pow(0.021,2) );
    break;
  case Syst::SignalComposition_VH      :
    if(m_IntProdMode==Process::WH)        m_scl = 1-sqrt( pow(0.007,2)+pow(0.019,2) );
    else if(m_IntProdMode==Process::ZH)   m_scl = 1-sqrt( pow(0.031,2)+pow(0.016,2) );
    else if(m_IntProdMode==Process::ggZH) m_scl = 1-sqrt( pow(0.189,2)+pow(0.024,2) );
    break;
  case Syst::SignalComposition_VH+1    :
    if(m_IntProdMode==Process::WH)        m_scl = 1+sqrt( pow(0.005,2)+pow(0.019,2) );
    else if(m_IntProdMode==Process::ZH)   m_scl = 1+sqrt( pow(0.038,2)+pow(0.016,2) );
    else if(m_IntProdMode==Process::ggZH) m_scl = 1+sqrt( pow(0.251,2)+pow(0.024,2) );
    break;
  case Syst::SignalComposition_ttHtH   :
    if(m_IntProdMode==Process::ttH)       m_scl = 1-sqrt( pow(0.092,2)+pow(0.036,2) );
    else if(m_IntProdMode==Process::tWH)  m_scl = 1-sqrt( pow(0.067,2)+pow(0.063,2) );
    else if(m_IntProdMode==Process::tHqb) m_scl = 1-sqrt( pow(0.150,2)+pow(0.043,2) );
    break;
  case Syst::SignalComposition_ttHtH+1 :
    if(m_IntProdMode==Process::ttH)       m_scl = 1+sqrt( pow(0.058,2)+pow(0.036,2) );
    else if(m_IntProdMode==Process::tWH)  m_scl = 1+sqrt( pow(0.049,2)+pow(0.063,2) );
    else if(m_IntProdMode==Process::tHqb) m_scl = 1+sqrt( pow(0.069,2)+pow(0.043,2) );
    break;
  default:
    if(m_ProcXStoScale!=-1 && m_ProcXStoScale==m_IntProdMode){
      m_scl = 1+(m_ValXStoScale/100.);
    }
    else m_scl = 1.;
  }
  return m_scl;
  
}
