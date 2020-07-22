#include "EventLoop.h"
#include "TLorentzVector.h"

bool EventLoop::PassTruthMassCut(){

  PRINT_VERBOSE("<EventLoop::PassTruthMassCut()>:: checking truth level mass cut ... ");

  bool m_cut = m4l_truth>124.9 && m4l_truth<125.1;
  if(m_ProdMode==Process::MG5 || m_IntProdMode==Process::VBF || m_IntProdMode==Process::MG5 ){
    m_cut = m4l_truth>124.0 && m4l_truth<126.0;
  }
  else if(m_IntProdMode==Process::ZH || m_IntProdMode==Process::WH){
    m_cut = m4l_truth>124.95 && m4l_truth<125.05;
  }
  else if(m_IntProdMode==Process::ttH){
    m_cut = m4l_truth>124.70 && m4l_truth<125.30;
  }
  else if(m_IntProdMode==Process::tWH){
    m_cut = m4l_truth>124.60 && m4l_truth<125.40;
  }
  else if(m_IntProdMode==Process::tHqb){
    m_cut = m4l_truth>15.0 && m4l_truth<235.0;
  }
  
  return m_cut;
  
}

void EventLoop::SetGlobalTruthConditions(){

  PRINT_VERBOSE("<EventLoop::SetGlobalTruthConditions()>:: setting global truth conditions ...");

  m_passThMassCut    = false;
  m_passBornMassChan = false;
  m_passDresMassChan = false;

  if( PassTruthMassCut() )                     m_passThMassCut    = true;
  if( PassMassChanFidCondition(mcType::Born) ) m_passBornMassChan = true;
  if( PassMassChanFidCondition(mcType::Dres) ) m_passDresMassChan = true;
  
}

bool EventLoop::PassCondition(int vNum, int bin, int type){

  PRINT_VERBOSE("<EventLoop::PassCondition()>:: checking condition for variableId "+
		std::to_string(vNum)+" and mc level type "+
		std::to_string(type)+" ... ");
  
  if(type==mcType::Truth && vNum==Variable::m4l){
    double var = GetVariableValue( Variable::m4l,type );
    if(var<m_Min || var>m_Max) return false;
  }
  if(vNum==Variable::pt0j   || vNum==Variable::pt1j ||
     vNum==Variable::pt2j   || vNum==Variable::pt3j ||
     vNum==Variable::pt0y   || vNum==Variable::pt1y ||
     vNum==Variable::pt2y   || vNum==Variable::pt3y ||
     vNum==Variable::ptnjet || vNum==Variable::pty4l ){
    double var = GetVariableValue( Variable::pt4l,type );
    if(var>350.0) return false;
  }
  if(vNum==Variable::pt0j){
    double var = GetVariableValue( Variable::njet,type );
    if(var>0) return false;
  }
  if(vNum==Variable::pt1j){
    double var = GetVariableValue( Variable::njet,type );
    if(var!=1) return false;
  }
  if(vNum==Variable::pt2j){
    double var = GetVariableValue( Variable::njet,type );
    if(var!=2) return false;
  }
  if(vNum==Variable::pt3j){
    double var = GetVariableValue( Variable::njet,type );
    if(var<3) return false;
  }
  if(vNum==Variable::pt0y){
    double var = GetVariableValue( Variable::y4l,type );
    if(var>0.5) return false;
  }
  if(vNum==Variable::pt1y){
    double var = GetVariableValue( Variable::y4l,type );
    if(var<0.5 || var>1.0) return false;
  }
  if(vNum==Variable::pt2y){
    double var = GetVariableValue( Variable::y4l,type );
    if(var<1.0 || var>1.5) return false;
  }
  if(vNum==Variable::pt3y){
    double var = GetVariableValue( Variable::y4l,type );
    if(var<1.5 || var>2.5) return false;
  }
  if(bin==-1) return false;

  return true;
  
}

bool EventLoop::PassMassChanFidCondition(int type){

  PRINT_VERBOSE("<EventLoop::PassMassChanFidCondition()>:: checking mass/channel condition ",
		"for mcType "+std::to_string(type)+" ... ");

  double var = GetVariableValue(Variable::m4l,type);
  if(var<m_Min || var>m_Max) return false;

  double evt = GetVariableValue(Variable::evtype,type);
  if(evt<0 || evt>3) return false;

  return true;
  
}

double EventLoop::GetVariableValue(int vNum, int type){

  PRINT_VERBOSE("<EventLoop::GetVariableValue()>:: Get value for variableId "+
		std::to_string(vNum)+" and mc level type "+
		std::to_string(type)+"... ");

  double fvar = -999;
  
  switch(vNum){
  case Variable::m4l:
    switch(type){
    case mcType::Reco : fvar = mFourLep   ; break;
    case mcType::Born : fvar = m4l_fidBorn; break;
    case mcType::Dres : fvar = m4l_fidDres; break;
    case mcType::Truth: fvar = m4l_truth  ; break;
    }
    break;
  case Variable::pt4l:
  case Variable::pt0j:
  case Variable::pt1j:
  case Variable::pt2j:
  case Variable::pt3j:
  case Variable::pt0y:
  case Variable::pt1y:
  case Variable::pt2y:
  case Variable::pt3y:
  case Variable::ptnjet:
  case Variable::pty4l:
    switch(type){
    case mcType::Reco : fvar = pt4l_fsr    ; break;
    case mcType::Born : fvar = pt4l_fidBorn; break;
    case mcType::Dres : fvar = pt4l_fidDres; break;
    case mcType::Truth: fvar = pt4l_truth  ; break;
    }
    break;
  case Variable::njet:
  case Variable::njetv2:
  case Variable::njetv3:
  case Variable::njetv4:
    switch(type){
    case mcType::Reco : fvar = m_njetReco ; break;
    case mcType::Born : fvar = m_njetBorn ; break;
    case mcType::Dres : fvar = m_njetDres ; break;
    case mcType::Truth: fvar = m_njetTruth; break;
    }
    break;
  case Variable::nbjet:
    switch(type){
    case mcType::Reco : fvar = nbjets       ; break;
    case mcType::Born : fvar = nbjet_fidBorn; break;
    case mcType::Dres : fvar = nbjet_fidDres; break;
    case mcType::Truth: fvar = nbjet_truth  ; break;
    }
    break;
  case Variable::m12:
    switch(type){
    case mcType::Reco : fvar = mZ1_fsr    ; break;
    case mcType::Born : fvar = m12_fidBorn; break;
    case mcType::Dres : fvar = m12_fidDres; break;
    case mcType::Truth: fvar = m12_truth  ; break;
    }
    break;
  case Variable::m34:
    switch(type){
    case mcType::Reco : fvar = mZ2_fsr    ; break;
    case mcType::Born : fvar = m34_fidBorn; break;
    case mcType::Dres : fvar = m34_fidDres; break;
    case mcType::Truth: fvar = m34_truth  ; break;
    }
    break;
  case Variable::y4l:
    switch(type){
    case mcType::Reco:  fvar = fabs(y4l_fsr)    ; break;
    case mcType::Born:  fvar = fabs(y4l_fidBorn); break;
    case mcType::Dres:  fvar = fabs(y4l_fidDres); break;
    case mcType::Truth: fvar = fabs(y4l_truth)  ; break;
    }
    break;
  case Variable::cts:
    switch(type){
    case mcType::Reco:  fvar = fabs(cthstr_fsr) ; break;
    case mcType::Born:  fvar = fabs(cts_fidBorn); break;
    case mcType::Dres:  fvar = fabs(cts_fidDres); break;
    case mcType::Truth: fvar = fabs(cts_truth)  ; break;
    }
    break;
  case Variable::ct1:
    switch(type){
    case mcType::Reco:  fvar = ct1_fsr    ; break;
    case mcType::Born:  fvar = ct1_fidBorn; break;
    case mcType::Dres:  fvar = ct1_fidDres; break;
    case mcType::Truth: fvar = ct1_truth  ; break;
    }
    break;
  case Variable::ct2:
    switch(type){
    case mcType::Reco:  fvar = ct2_fsr    ; break;
    case mcType::Born:  fvar = ct2_fidBorn; break;
    case mcType::Dres:  fvar = ct2_fidDres; break;
    case mcType::Truth: fvar = ct2_truth  ; break;
    }
    break;
  case Variable::phi:
    switch(type){
    case mcType::Reco:  fvar = phi_fsr    ; break;
    case mcType::Born:  fvar = phi_fidBorn; break;
    case mcType::Dres:  fvar = phi_fidDres; break;
    case mcType::Truth: fvar = phi_truth  ; break;
    }
    break;
  case Variable::phi1:
    switch(type){
    case mcType::Reco:  fvar = phi1_fsr    ; break;
    case mcType::Born:  fvar = phi1_fidBorn; break;
    case mcType::Dres:  fvar = phi1_fidDres; break;
    case mcType::Truth: fvar = phi1_truth  ; break;
    }
    break;
  case Variable::ljpt:
    switch(type){
    case mcType::Reco:  fvar = m_ljptReco ; break; 
    case mcType::Born:  fvar = m_ljptBorn ; break;
    case mcType::Dres:  fvar = m_ljptDres ; break;
    case mcType::Truth: fvar = m_ljptTruth; break;
    }
    break;
  case Variable::sjpt:
    switch(type){
    case mcType::Reco:  fvar = m_sjptReco ; break; 
    case mcType::Born:  fvar = m_sjptBorn ; break;
    case mcType::Dres:  fvar = m_sjptDres ; break;
    case mcType::Truth: fvar = m_sjptTruth; break;
    }
    break;
  case Variable::mjj:
    switch(type){
    case mcType::Reco:  fvar = m_mjjReco ; break;
    case mcType::Born:  fvar = m_mjjBorn ; break;
    case mcType::Dres:  fvar = m_mjjDres ; break;
    case mcType::Truth: fvar = m_mjjTruth; break;
    }
    break;
  case Variable::etajj:
    switch(type){
    case mcType::Reco:  fvar = m_etajjReco ; break;
    case mcType::Born:  fvar = m_etajjBorn ; break;
    case mcType::Dres:  fvar = m_etajjDres ; break;
    case mcType::Truth: fvar = m_etajjTruth; break;
    }
    break;
  case Variable::phijj:
    switch(type){
    case mcType::Reco:  fvar = m_phijjReco ; break;
    case mcType::Born:  fvar = m_phijjBorn ; break;
    case mcType::Dres:  fvar = m_phijjDres ; break;
    case mcType::Truth: fvar = m_phijjTruth; break;
    }
    break;
  case Variable::evtype:
    switch(type){
    case mcType::Reco:  fvar = event_type       ; break;
    case mcType::Born:  fvar = thevtType_fidBorn; break;
    case mcType::Dres:  fvar = thevtType_fidDres; break;
    case mcType::Truth: fvar = thevtType_truth  ; break;
    }
    break;
  case Variable::m12m34:
    fvar = 0; break;
  default:
    PRINT_ERROR("                                  Variable "+GetVariableName(vNum)+
		" not defined -> exiting ... ");
    exit(0);
  }
  
  PRINT_VERBOSE("                                      value = "+std::to_string(fvar));
  return fvar;
  
}

double EventLoop::GetJetVariableValue(int vNum, int type){

  /* function to be used just for pre-assignment of jet variables */

  PRINT_VERBOSE("<EventLoop::GetJetVariableValue()>:: Get value for jet variableId "+
		std::to_string(vNum)+" and mc level type "+
		std::to_string(type)+"... ");

  double fvar = -999;
  switch(vNum){
  case Variable::njet:
    switch(type){
    case mcType::Reco : fvar = njets       ; break;
    case mcType::Born : fvar = njet_fidBorn; break;
    case mcType::Dres : fvar = njet_fidDres; break;
    case mcType::Truth: fvar = njet_truth  ; break;
    }
    break;
  case Variable::ljpt:
    if(GetJetVariableValue(Variable::njet,type)>0){
      switch(type){
      case mcType::Reco:  fvar = jet_pt->at(0)        ; break; 
      case mcType::Born:  fvar = jet_pt_fidBorn->at(0); break;
      case mcType::Dres:  fvar = jet_pt_fidDres->at(0); break;
      case mcType::Truth: fvar = jet_pt_truth->at(0)  ; break;
      }
    }
    else{ fvar = -999; break;}
    break;
  case Variable::sjpt:
    if(GetJetVariableValue(Variable::njet,type)>1){
      switch(type){
      case mcType::Reco:  fvar = jet_pt->at(1)        ; break; 
      case mcType::Born:  fvar = jet_pt_fidBorn->at(1); break;
      case mcType::Dres:  fvar = jet_pt_fidDres->at(1); break;
      case mcType::Truth: fvar = jet_pt_truth->at(1)  ; break;
      }
    }
    else{ fvar = -999; break;}
    break;
  case Variable::mjj:
    if(GetJetVariableValue(Variable::njet,type)>1){
      switch(type){
      case mcType::Reco:  fvar = mjj        ; break;
      case mcType::Born:  fvar = mjj_fidBorn; break;
      case mcType::Dres:  fvar = mjj_fidDres; break;
      case mcType::Truth: fvar = mjj_truth  ; break;
      }
    }
    else{ fvar = -999; break;}
    break;
  case Variable::etajj:
    if(GetJetVariableValue(Variable::njet,type)>1){
      switch(type){
      case mcType::Reco:  fvar = etajj        ; break;
      case mcType::Born:  fvar = etajj_fidBorn; break;
      case mcType::Dres:  fvar = etajj_fidDres; break;
      case mcType::Truth: fvar = etajj_truth  ; break;
      }
    }
    else{ fvar = -999; break;}
    break;
  case Variable::phijj:
    if(GetJetVariableValue(Variable::njet,type)>1){
      switch(type){
      case mcType::Reco:  fvar = phijj        ; break;
      case mcType::Born:  fvar = phijj_fidBorn; break;
      case mcType::Dres:  fvar = phijj_fidDres; break;
      case mcType::Truth: fvar = phijj_truth  ; break;
      }
    }
    else{ fvar = -999; break;}
    break;
  default:
    PRINT_ERROR("                                  Variable "+GetVariableName(vNum)+
		" not in the jet set -> exiting ... ");
    exit(0);
  }
  return fvar;
  
}

std::vector<float> EventLoop::GetVariableVector(int vNum, int type){
  
  PRINT_VERBOSE("<EventLoop::GetVariableVector()>:: Get vector for variableId "+
                std::to_string(vNum)+" and mc level type "+std::to_string(type)+"... ");

  std::vector<float> m_vec;
  switch(vNum){
  case Variable::jet_pt:
    switch(type) {
    case mcType::Reco:  m_vec = *jet_pt        ; break;
    case mcType::Born:  m_vec = *jet_pt_fidBorn; break;
    case mcType::Dres:  m_vec = *jet_pt_fidDres; break;
    case mcType::Truth:	m_vec = *jet_pt_truth  ; break;
    }
    break;
  case Variable::jet_eta:
    switch(type) {
    case mcType::Reco:  m_vec = *jet_eta        ; break;
    case mcType::Born:  m_vec = *jet_eta_fidBorn; break;
    case mcType::Dres:  m_vec = *jet_eta_fidDres; break;
    case mcType::Truth:	m_vec = *jet_eta_truth  ; break;
    }
    break;
  case Variable::jet_phi:
    switch(type) {
    case mcType::Reco:	m_vec = *jet_phi        ; break;
    case mcType::Born:	m_vec = *jet_phi_fidBorn; break;
    case mcType::Dres:	m_vec = *jet_phi_fidDres; break;
    case mcType::Truth:	m_vec = *jet_phi_truth  ; break;
    }
    break;
  case Variable::jet_m:
    switch(type) {
    case mcType::Reco:	m_vec = *jet_m        ; break;
    case mcType::Born:	m_vec = *jet_m_fidBorn; break;
    case mcType::Dres:	m_vec = *jet_m_fidDres; break;
    case mcType::Truth:	m_vec = *jet_m_truth  ;	break;
    }
    break;
  default:
    PRINT_ERROR("                                  Variable "+GetVariableName(vNum)+
                " not among the jet quantities -> exiting ... ");
    exit(0);
  }

  return m_vec;

}
void EventLoop::EvaluateJetVariables(int type){

  PRINT_VERBOSE("<EventLoop::EvaluateJetVariables()>:: overwrite jet variables for restricted phase space ... ");

  double Vnjet = -999, Vljpt  = -999, Vsjpt  = -999;
  double Vmjj  = -999, Vetajj = -999, Vphijj = -999;

  if(m_restrictJets && type!=mcType::Truth){
    m_tmpJetEta = GetVariableVector(Variable::jet_eta,type);
    m_tmpJetPhi = GetVariableVector(Variable::jet_phi,type);
    m_tmpJetPt  = GetVariableVector(Variable::jet_pt ,type);
    m_tmpJetM   = GetVariableVector(Variable::jet_m  ,type);
    
    for(uint i=0; i<m_tmpJetEta.size(); i++){
      /* remove forward jets (|eta|>2.5) with pT<60 GeV */
      //if( m_tmpJetPt.at(i)<m_cutJetPt && fabs(m_tmpJetEta.at(i))>m_cutJetEta) continue;
      if( m_tmpJetPt[i]<m_cutJetPt && fabs(m_tmpJetEta[i])>m_cutJetEta) continue;
      m_JetEta.push_back( m_tmpJetEta[i] );
      m_JetPhi.push_back( m_tmpJetPhi[i] );
      m_JetPt.push_back( m_tmpJetPt[i] );
      m_JetM.push_back( m_tmpJetM[i] );
    }
    
    Vnjet  = m_JetEta.size();
    Vljpt  = -999;
    Vetajj = -999;
    Vphijj = -999;
    Vmjj   = -999;
    if(m_JetEta.size()>0) Vljpt = m_JetPt[0];
    if(m_JetEta.size()>1){
      Vsjpt = m_JetPt[1];
      Vetajj = fabs(m_JetEta[0]-m_JetEta[1]);
      if( m_JetEta[0]>m_JetEta[1] ) Vphijj = m_JetPhi[0]-m_JetPhi[1];
      if( m_JetEta[0]<m_JetEta[1] ) Vphijj = m_JetPhi[1]-m_JetPhi[0];
      if(Vphijj<0) Vphijj = Vphijj + 2*TMath::Pi();
      Vmjj = EvalDiJetMass();
    }
    /* cleaning */
    m_tmpJetPt.clear(); m_tmpJetEta.clear(); m_tmpJetPhi.clear(); m_tmpJetM.clear();
    m_JetPt.clear();    m_JetEta.clear();    m_JetPhi.clear();    m_JetM.clear();
  }
  else{
    Vnjet  = GetJetVariableValue(Variable::njet ,type);
    Vljpt  = GetJetVariableValue(Variable::ljpt ,type);
    Vsjpt  = GetJetVariableValue(Variable::sjpt ,type);
    Vmjj   = GetJetVariableValue(Variable::mjj  ,type);
    Vetajj = GetJetVariableValue(Variable::etajj,type);
    Vphijj = GetJetVariableValue(Variable::phijj,type);
  }
  FillJetVarValues(Variable::njet , Vnjet , type);
  FillJetVarValues(Variable::ljpt , Vljpt , type);
  FillJetVarValues(Variable::sjpt , Vsjpt , type);
  FillJetVarValues(Variable::mjj  , Vmjj  , type);
  FillJetVarValues(Variable::etajj, Vetajj, type);
  FillJetVarValues(Variable::phijj, Vphijj, type);
  
}

double EventLoop::EvalDiJetMass(){

  PRINT_VERBOSE("EventLoop::EvalDiJetMass()>:: calculating di-jet mass ... ");

  double m = -999;
  if( m_JetPt.size()==0 ){
    PRINT_ERROR("                               jet vector not filled! exiting ...");
    exit(0);
  }
  TLorentzVector jet1, jet2;
  jet1.SetPtEtaPhiM( m_JetPt.at(0), m_JetEta.at(0), m_JetPhi.at(0), m_JetM.at(0) );
  jet2.SetPtEtaPhiM( m_JetPt.at(1), m_JetEta.at(1), m_JetPhi.at(1), m_JetM.at(1) );
  m = (jet1+jet2).M();
  
  PRINT_VERBOSE("                                              value = "+std::to_string(m));
  
  return m;
  
}

void EventLoop::FillJetVarValues(int vNum, double val, int type){

  PRINT_VERBOSE("EventLoop::FillJetVarValues()>:: filling jet variables values for varId = "+
		std::to_string(vNum)+" and mcType = "+std::to_string(type));

  switch(vNum){
  case Variable::njet:
    switch(type) {
    case mcType::Reco:  m_njetReco  = val; break;
    case mcType::Born:  m_njetBorn  = val; break;
    case mcType::Dres:  m_njetDres  = val; break;
    case mcType::Truth:	m_njetTruth = val; break;
    }
    break;
  case Variable::ljpt:
    switch(type) {
    case mcType::Reco:  m_ljptReco  = val; break;
    case mcType::Born:  m_ljptBorn  = val; break;
    case mcType::Dres:  m_ljptDres  = val; break;
    case mcType::Truth:	m_ljptTruth = val; break;
    }
    break;
  case Variable::sjpt:
    switch(type) {
    case mcType::Reco:  m_sjptReco  = val; break;
    case mcType::Born:  m_sjptBorn  = val; break;
    case mcType::Dres:  m_sjptDres  = val; break;
    case mcType::Truth:	m_sjptTruth = val; break;
    }
    break; 
  case Variable::mjj:
    switch(type) {
    case mcType::Reco:  m_mjjReco  = val; break;
    case mcType::Born:  m_mjjBorn  = val; break;
    case mcType::Dres:  m_mjjDres  = val; break;
    case mcType::Truth:	m_mjjTruth = val; break;
    }
    break;
  case Variable::etajj:
    switch(type) {
    case mcType::Reco:  m_etajjReco  = val; break;
    case mcType::Born:  m_etajjBorn  = val; break;
    case mcType::Dres:  m_etajjDres  = val; break;
    case mcType::Truth:	m_etajjTruth = val; break;
    }
    break;
    case Variable::phijj:
    switch(type) {
    case mcType::Reco:  m_phijjReco  = val; break;
    case mcType::Born:  m_phijjBorn  = val; break;
    case mcType::Dres:  m_phijjDres  = val; break;
    case mcType::Truth:	m_phijjTruth = val; break;
    }
    break;
  default:
    PRINT_ERROR("                                  Variable "+GetVariableName(vNum)+
                " not in the jet set -> exiting ... ");
    exit(0);
  }
  
}

int EventLoop::GetVariableBin(int vNum, int mcType){

  int bin = -1;
  switch(vNum){
  case Variable::m12m34: bin = FindBin( vNum,GetVariableValue(Variable::m12,mcType),
					GetVariableValue(Variable::m34,mcType) );     break;
  case Variable::ptnjet: bin = FindBin( vNum,GetVariableValue(Variable::pt4l,mcType),
					GetVariableValue(Variable::njet,mcType) );    break;
  case Variable::pty4l:  bin = FindBin( vNum,GetVariableValue(Variable::pt4l,mcType),
					GetVariableValue(Variable::y4l,mcType) );     break;
  default:               bin = FindBin( vNum,GetVariableValue( vNum,mcType ) );
  }
  
  return bin;
  
}
