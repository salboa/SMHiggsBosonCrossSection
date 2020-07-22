#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: LoadCorrFact(){

  if( m_debug )
    cout << "<LoadCorrFact()>:: loading correction factors values " << endl;

  m_cf.clear();
  m_InStream.open( (m_DataPath+m_cfFile).c_str() );
  
  if( m_Fiducial ) LoadFidValues(m_cf);
  else LoadDiffValues(m_cf);

  m_InStream.close();

  if( m_verbose ){
    cout << "<LoadCorrFact()>:: Printing loaded values " << endl;
    PrintValues(m_cf);
  }
  
}

void WorkSpaceMaker :: LoadAcceptance(){

  if( m_debug )
    cout << "<LoadAcceptance()>:: loading acceptance values "  << endl;

  m_acc.clear();
  m_InStream.open( (m_DataPath+m_accFile).c_str() );
  
  if( m_Fiducial ) LoadFidValues(m_acc);
  else LoadDiffValues(m_acc);

  m_InStream.close();

  if( m_verbose ){
    cout << "<LoadAcceptance>:: Printing loaded values " << endl;
    PrintValues(m_acc);
  }
      
}

void WorkSpaceMaker :: LoadProdModeFraction(){

  if( m_debug )
    cout << "<LoadProdModeFraction()>:: loading prodution mode ratio values "  << endl;

  m_r.clear();
  m_InStream.open( (m_DataPath+m_rFile).c_str() );

  if( m_Fiducial ) LoadFidValues(m_r);
  else LoadDiffValues(m_r);
  
  m_InStream.close();

  if( m_verbose ){
    cout << "<LoadProdModeFraction>:: Printing loaded values " << endl;
    PrintValues(m_r);
  }
}

void WorkSpaceMaker :: LoadXsScaleFraction(){
  
  if( m_debug )
    cout << "<LoadXsScaleFraction()>:: loading XS scale fraction "  << endl;
  
  m_xsScale.clear();
  m_InStream.open( (m_DataPath+m_xsScaleFile).c_str() );
  LoadValues(m_xsScale,true);
  m_InStream.close();
  
  if( m_verbose ){
    cout << "<LoadXsScaleFraction>:: Printing loaded values " << endl;
    PrintValues(m_xsScale);
  }
}

void WorkSpaceMaker :: LoadCrossSection(){

  if( m_debug )
    cout << "<LoadCrossSection()>:: loading cross section values: " << endl;

  m_xsec.clear();
  m_InStream.open( (m_DataPath+m_xsecFile).c_str() );
  LoadValues(m_xsec);
  m_InStream.close();
  
  if( m_verbose ){
    cout << "<LoadCrossSection()>:: printing loaded values " << endl;
    PrintValues(m_xsec,false,true);
  }
  
}

void WorkSpaceMaker :: LoadBranchingRatio(){

  if( m_debug )
    cout << "<LoadBranchingRatio()>:: loading branching ratio values: " << endl;

  m_br.clear();
  m_InStream.open( (m_DataPath+m_brFile).c_str() );
  LoadValues(m_br);
  m_InStream.close();
  
  if( m_verbose ){
    cout << "<LoadBranchingRatio()>:: printing loaded values " << endl;
    PrintValues(m_br,true,false);
  }
  
}

void WorkSpaceMaker :: LoadSystematics(){

  if( m_debug )
    cout << "<LoadSystematics()>:: loading systematic variations: " << endl;

  m_procSys.clear();

  if( m_Fiducial ){
    for(auto& x: m_process){
      int p = x.second;
      for(auto& c: m_Category){
	string ch = c.second;
	m_InStream.open( (m_DataPath+m_sysFile+GetProcess(p)+"_"+ch+".dat").c_str() );
	LoadValues(p,0,m_procSys,c.first);
	m_InStream.close();
      }
    }
  }
  else{
    int its = m_Category.size();
    for(auto& x: m_process){
      int p = x.second;
      for(int i=0; i<its; i++){
        m_InStream.open( (m_DataPath+m_sysFile+GetProcess(p)+"_bin"+to_string(i)+".dat").c_str() );
        LoadValues(p,i,m_procSys,m_ChNum);
        m_InStream.close();
      }
    }
  }

  m_comSys.clear();
  m_InStream.open( (m_DataPath+m_cmSysFile).c_str() );
  LoadValues(m_comSys);
  m_InStream.close();
  
  if( m_verbose ){
    cout << "<LoadSystematics()>:: printing loaded values " << endl;
    PrintProcessSystematicValues();
    PrintCommonSystematicValues();
  }
  
}

void WorkSpaceMaker :: LoadFidValues(map<int, vector< pair<double,double> > > &data){
  
  if( m_debug )
    cout << "<LoadFidValues()>:: loading values for Fid. xsec measurement: " << endl;

  double val=0, err=0;
  std::string tmp="";
  int line=0;
  while(m_InStream.good()){
    val=0, err=0;
    if( line==0 )
      getline(m_InStream,tmp);
    
    m_InStream>>tmp;
    m_InStream>>val; m_InStream>>err;
    data[line].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[line].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[line].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[line].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[line].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[line].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[line].push_back( make_pair(val,err) );
    line++;
  }
  
}

void WorkSpaceMaker :: LoadDiffValues(map<int, vector< pair<double,double> > > &data){
  
  if( m_debug )
    cout << "<LoadDiffValues()>:: loading values for Diff. xsec measurement: "
	 << m_Variable << " var " << endl;

  double val=0, err=0;
  std::string tmp="";
  int line=0;
  while(m_InStream.good()){
    val=0, err=0;
    if( line==0 )
      getline(m_InStream,tmp);
    
    m_InStream>>tmp;
    m_InStream>>val; m_InStream>>err;
    data[m_ChNum].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[m_ChNum].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[m_ChNum].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[m_ChNum].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[m_ChNum].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[m_ChNum].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[m_ChNum].push_back( make_pair(val,err) );
    line++;
  }
  
}

void WorkSpaceMaker :: LoadValues(int p, int b, map<int, map<int, map<int, map<string,vector<double> > > > > &data, int ch){
  
  if( m_debug ){
    cout << "<LoadValues()>:: loading systematic values for xsec measurement: "
	 << "var " << m_Variable;
    if( m_Fiducial ) cout<<endl;
    else cout <<" , bin " << b << endl;
  }
  
  double val=0;
  string id="";
  string tmp="";
  int line=0;
  while(m_InStream.good()){
    val=0, id="";
    if( line==0 )
      getline(m_InStream,tmp);
    
    m_InStream>>id; m_InStream>>val;
    data[ch][p][b][id].push_back(val);
    m_InStream>>val;
    data[ch][p][b][id].push_back(val);
    m_InStream>>val;
    data[ch][p][b][id].push_back(val);
    m_InStream>>val;
    data[ch][p][b][id].push_back(val);
    line++;
  }
  
}

void WorkSpaceMaker :: LoadValues(vector< pair<double,double> > &data,
				  bool isPRF){

  if( m_debug )
    cout << "<LoadValues()>:: loading values for xsec measurement " << endl;

  double val=0, err=0;
  std::string tmp="";
  int line=0;
  while(m_InStream.good()){
    val=0, err=0;
    if( line==0 )
      getline(m_InStream,tmp);

    if( isPRF ){
      m_InStream>>tmp;
      m_InStream>>val; m_InStream>>err;
      data.push_back( make_pair(val,err) );
      m_InStream>>val; m_InStream>>err;
      data.push_back( make_pair(val,err) );
      m_InStream>>val; m_InStream>>err;
      data.push_back( make_pair(val,err) );
      m_InStream>>val; m_InStream>>err;
      data.push_back( make_pair(val,err) );
      m_InStream>>val; m_InStream>>err;
      data.push_back( make_pair(val,err) );
      m_InStream>>val; m_InStream>>err;
      data.push_back( make_pair(val,err) );
      m_InStream>>val; m_InStream>>err;
      data.push_back( make_pair(val,err) );
    }
    else{
      m_InStream>>tmp;
      m_InStream>>val; m_InStream>>err;
      data.push_back( make_pair(val,err) );
    }
    line++;
  }
  
}

void WorkSpaceMaker :: LoadValues(map<string,vector<double> > &data){

  if( m_debug ){
    cout << "<LoadValues()>:: loading common systematic values for xsec measurement: " << endl;
  }
  
  double val=0;
  string id="";
  string tmp="";
  int line=0;
  while(m_InStream.good()){
    val=0, id="";
    if( line==0 )
      getline(m_InStream,tmp);
    
    m_InStream>>id; m_InStream>>val;
    data[id].push_back(val);
    m_InStream>>val;
    data[id].push_back(val);
    m_InStream>>val;
    data[id].push_back(val);
    m_InStream>>val;
    data[id].push_back(val);
    line++;
  }

}

void WorkSpaceMaker :: PrintValues(map<int, vector< pair<double,double> > > data){

  for(uint i=0; i<data.size(); i++){
    cout << "Decay Channel " << GetChannel(i) << endl;
    uint b=0, Index=0;
    for(uint p=0; p<data[i].size(); p++){
      if( (p % (int(Process::bbH)+1)) ==0 ){
	cout << "---------- Bin = " << b << " ---------- " << endl;
	Index = 0;
	b++;
      }
      cout << "ProdMode = "<< GetProcess(Index)  << " " << data[i].at(p).first << " +- " << data[i].at(p).second << endl;
      Index++;
    }
  }
  
}

void WorkSpaceMaker :: PrintValues(vector< pair<double,double> > data, bool isBR, bool isXsec){

  uint b=0, Index=0;
  for(uint i=0; i<data.size(); i++){
    if( isBR )
      cout << "Decay Channel = " << GetChannel(i) << " " << data.at(i).first << " +- " << data.at(i).second << endl;
    else if( isXsec )
      cout << "ProdMode = " << GetProcess(i) << " " << data.at(i).first << " +- " << data.at(i).second << endl;
    else{
      if( (i % (int(Process::bbH)+1)) ==0 ){
	cout << "---------- Bin = " << b << " ---------- " << endl;
	Index = 0;
	b++;
      }
      cout << "ProdMode = "<< GetProcess(Index)  << " " << data.at(i).first << " +- " << data.at(i).second << endl;
      Index++;
    }
  }
  
}

Double_t WorkSpaceMaker :: PrintACRProduct(int ChNum, int cat){

  double m_val=0;
  int Pos = cat*(int(Process::bbH)+1);
  double ggH_ACR = m_acc[ChNum].at(Pos+1).first*m_cf[ChNum].at(Pos+1).first*m_r[ChNum].at(Pos+1).first;
  double VBF_ACR = m_acc[ChNum].at(Pos+2).first*m_cf[ChNum].at(Pos+2).first*m_r[ChNum].at(Pos+2).first;
  double WH_ACR  = m_acc[ChNum].at(Pos+3).first*m_cf[ChNum].at(Pos+3).first*m_r[ChNum].at(Pos+3).first;
  double ZH_ACR  = m_acc[ChNum].at(Pos+4).first*m_cf[ChNum].at(Pos+4).first*m_r[ChNum].at(Pos+4).first;
  double ttH_ACR = m_acc[ChNum].at(Pos+5).first*m_cf[ChNum].at(Pos+5).first*m_r[ChNum].at(Pos+5).first;
  double bbH_ACR = m_acc[ChNum].at(Pos+6).first*m_cf[ChNum].at(Pos+6).first*m_r[ChNum].at(Pos+6).first;

  return m_val = (ggH_ACR+VBF_ACR+WH_ACR+ZH_ACR+ttH_ACR+bbH_ACR)*m_Lumi->getVal()*m_binwidth.at(cat)*EvalXS(Pos)/m_binwidth.at(cat)*m_br.at(ChNum).first;
  
}

Double_t WorkSpaceMaker :: PrintExpXS(int ChNum, int cat){
  
  double m_val=0;

  int Pos = 0;
  if( m_Fiducial ) Pos= 0;
  else Pos = cat*(int(Process::bbH)+1);
  double ggH_ACR, VBF_ACR, WH_ACR, ZH_ACR,ttH_ACR,bbH_ACR;
  
  if ( !m_FidTotal ){
    ggH_ACR = m_cf[ChNum].at(Pos+1).first*m_r[ChNum].at(Pos+1).first;
    VBF_ACR = m_cf[ChNum].at(Pos+2).first*m_r[ChNum].at(Pos+2).first;
    WH_ACR  = m_cf[ChNum].at(Pos+3).first*m_r[ChNum].at(Pos+3).first;
    ZH_ACR  = m_cf[ChNum].at(Pos+4).first*m_r[ChNum].at(Pos+4).first;
    ttH_ACR = m_cf[ChNum].at(Pos+5).first*m_r[ChNum].at(Pos+5).first;
    bbH_ACR = m_cf[ChNum].at(Pos+6).first*m_r[ChNum].at(Pos+6).first;
  }
  else {
    ggH_ACR = m_acc[ChNum].at(Pos+1).first*m_cf[ChNum].at(Pos+1).first*m_r[ChNum].at(Pos+1).first;
    VBF_ACR = m_acc[ChNum].at(Pos+2).first*m_cf[ChNum].at(Pos+2).first*m_r[ChNum].at(Pos+2).first;
    WH_ACR  = m_acc[ChNum].at(Pos+3).first*m_cf[ChNum].at(Pos+3).first*m_r[ChNum].at(Pos+3).first;
    ZH_ACR  = m_acc[ChNum].at(Pos+4).first*m_cf[ChNum].at(Pos+4).first*m_r[ChNum].at(Pos+4).first;
    ttH_ACR = m_acc[ChNum].at(Pos+5).first*m_cf[ChNum].at(Pos+5).first*m_r[ChNum].at(Pos+5).first;
    bbH_ACR = m_acc[ChNum].at(Pos+6).first*m_cf[ChNum].at(Pos+6).first*m_r[ChNum].at(Pos+6).first;
    
  }
  cout << m_FidTotal << endl;

  if( m_Fiducial && !m_FidTotal) m_val = (m_h_remapped->Integral()*m_Lumi->getVal())/((ggH_ACR+VBF_ACR+WH_ACR+ZH_ACR+ttH_ACR+bbH_ACR)*m_Lumi->getVal());
  if( m_FidTotal ) m_val = (m_h_remapped->Integral()*m_Lumi->getVal())/((ggH_ACR+VBF_ACR+WH_ACR+ZH_ACR+ttH_ACR+bbH_ACR)*m_Lumi->getVal()*m_br.at(ChNum).first);
  if( !m_Fiducial ) m_val = (m_h_remapped->GetBinContent(cat+1)*m_Lumi->getVal())/((ggH_ACR+VBF_ACR+WH_ACR+ZH_ACR+ttH_ACR+bbH_ACR)*m_Lumi->getVal());

  return m_val;
}

void WorkSpaceMaker :: PrintProcessSystematicValues(){

  cout << "<PrintProcessSystematicValues()>:: -------- process dependent systematic values -------- " << endl;

  for(uint i=0; i<m_procSys.size(); i++){
    cout << "******** Decay Channel " << GetChannel(i) << " ******** " << endl;
    for(auto& x: m_process){
      int p = x.second;
      cout <<"     ***** Process " <<  GetProcess(p) << " ***** " << endl;
      for(uint b=0; b<m_procSys[i][p].size(); b++){
	if( !m_Fiducial )
	  cout << "---------- Bin = " << b << " ---------- " << endl;
	for(auto& x1: m_procSys[i][p][b]){
	  cout <<" Systematic = " << x1.first << "  DwVal = " << x1.second.at(0)
	       << "  UpVal = " << x1.second.at(1) << "  Type = " << x1.second.at(2)
	       << "  Constr = " << x1.second.at(3) << endl;
	}
      }
    }
  }
  
}

void WorkSpaceMaker :: PrintCommonSystematicValues(){

  cout << "<PrintCommonSystematicValues()>:: -------- common systematic values -------- " << endl;
  for(auto& x: m_comSys){
    cout << "Systematic =  " << x.first << "  UpVal = " << x.second.at(0)
	 << "  DwVal = " << x.second.at(1) << "  Type = " << x.second.at(2)
	 << "  Constr = " << x.second.at(3) << endl;
  }
  
}

map<string,vector<double> > WorkSpaceMaker :: GetSysMap(int chnum, int proc, int bin){

  return m_procSys[chnum][proc][bin];
    
}
