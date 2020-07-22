#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: LoadCorrFact(){

  PRINT_DEBUG_FUNCTION(" <LoadCorrFact()>:: loading correction factors values for input: " +m_InputMtx);

  m_cf.clear();
  for(uint f=0; f<m_cfFile.size(); f++){
    m_InStream.open( (m_Dir+m_DataPath+m_cfFile.at(f)).c_str() );
    if (!m_InStream) {
      PRINT_FATAL(" <LoadCorrFact()>:: File "+(m_Dir+m_DataPath+m_cfFile.at(f))+" does not exist! exit(0)" );
      exit(0);
    }
    if( !m_matrix ) LoadValues(m_cf,m_cfFile.at(f));
    else LoadMatrixValues(m_cf,m_cfFile.at(f));
    m_InStream.close();
  }

  if( m_verbose ){
    PRINT_DEBUG_FUNCTION(" <LoadCorrFact()>:: Printing loaded values");
    PrintValues(m_cf,m_matrix);
  }

}

void WorkSpaceMaker :: LoadAcceptance(){

  PRINT_DEBUG_FUNCTION(" <LoadAcceptance()>:: loading acceptance values");

  m_acc.clear();
  for(uint f=0; f<m_accFile.size(); f++){
    m_InStream.open( (m_Dir+m_DataPath+m_accFile.at(f)).c_str() );
    if (!m_InStream) {
      PRINT_FATAL(" <LoadAcceptance()>:: File"+(m_Dir+m_DataPath+m_accFile.at(f))+" does not exist! exit(0)" );
      exit(0);
    }
    LoadValues(m_acc,m_accFile.at(f));
    m_InStream.close();
  }
  
  if( m_verbose ){
    PRINT_DEBUG_FUNCTION(" <LoadAcceptance>:: Printing loaded values");
    PrintValues(m_acc);
  }
  
}

void WorkSpaceMaker :: LoadNotFid(){
  
  PRINT_DEBUG_FUNCTION(" <LoadNotFid()>:: loading not fid values");
  
  m_notFid.clear();
  for(uint f=0; f<m_notFidFile.size(); f++){
    m_InStream.open( (m_Dir+m_DataPath+m_notFidFile.at(f)).c_str() );
    if (!m_InStream) {
      PRINT_FATAL(" <LoadNotFid()>:: File"+(m_Dir+m_DataPath+m_notFidFile.at(f))+" does not exist! exit(0)" );
      exit(0);
    }
    LoadValues(m_notFid,m_notFidFile.at(f));
    m_InStream.close();
  }
  
  if( m_verbose ){
    PRINT_DEBUG_FUNCTION(" <LoadNotFid>:: Printing loaded values");
    PrintValues(m_notFid);
  }
  
}

void WorkSpaceMaker :: LoadProdModeFraction(){

  PRINT_DEBUG_FUNCTION(" <LoadProdModeFraction()>:: loading prodution mode ratio values ");

  m_r.clear();
  for(uint f=0; f<m_rFile.size(); f++){
    m_InStream.open( (m_Dir+m_DataPath+m_rFile.at(f)).c_str() );
    if (!m_InStream) {
      PRINT_FATAL("  <LoadProdModeFraction()>:: File"+(m_Dir+m_DataPath+m_rFile.at(f))+" does not exist! exit(0)" );
      exit(0);
    }
    LoadValues(m_r,m_rFile.at(f));
    m_InStream.close();
  }

  if( m_verbose ){
    PRINT_DEBUG_FUNCTION(" <LoadProdModeFraction>:: Printing loaded values ");
    PrintValues(m_r);
  }  
}

void WorkSpaceMaker :: LoadMinitreeN(){

  PRINT_DEBUG_FUNCTION(" <LoadMinitreeN()>:: loading N exp from minitree ");

  m_MinitreeN.clear();
  for(uint f=0; f<m_mtFile.size(); f++){
    m_InStream.open( (m_Dir+m_DataPath+m_mtFile.at(f)).c_str() );
    if (!m_InStream) {
      PRINT_FATAL("  <LoadMinitreeN()>:: File"+(m_Dir+m_DataPath+m_mtFile.at(f))+" does not exist! exit(0)" );
    exit(0);
    }
    LoadValues(m_MinitreeN,m_mtFile.at(f));
    m_InStream.close();
  }
    
  if( m_verbose ){
    PRINT_DEBUG_FUNCTION(" <LoadMinitreeN>:: Printing loaded values ");
    PrintValues(m_MinitreeN);
  }
    
}

void WorkSpaceMaker :: LoadCrossSection(){

  PRINT_DEBUG_FUNCTION(" <LoadCrossSection()>:: loading cross section values ");

  m_xsec.clear();
  m_InStream.open( (m_Dir+m_DataPath+m_xsecFile).c_str() );
  if (!m_InStream) {
    PRINT_FATAL(" <LoadCrossSection()>:: File"+(m_Dir+m_DataPath+m_xsecFile)+" does not exist! exit(0)" );
    exit(0);
  }
  LoadValues(m_xsec);
  m_InStream.close();
  
  if( m_verbose ){
    PRINT_DEBUG_FUNCTION(" <LoadCrossSection()>:: printing loaded values ");
    PrintValues(m_xsec,false,true);
  }
  
}

void WorkSpaceMaker :: LoadBranchingRatio(){

  PRINT_DEBUG_FUNCTION(" <LoadBranchingRatio()>:: loading branching ratio values ");

  m_br.clear();
  m_InStream.open( (m_Dir+m_DataPath+m_brFile).c_str() );
  if (!m_InStream) {
    PRINT_FATAL(" <LoadBranchingRatio()>:: File"+(m_Dir+m_DataPath+m_brFile)+" does not exist! exit(0)" );
    exit(0);
  }
  LoadValues(m_br);
  m_InStream.close();
  
  if( m_verbose ){
    PRINT_DEBUG_FUNCTION(" <LoadBranchingRatio()>:: printing loaded values ");
    PrintValues(m_br,true,false);
  }
  
}

void WorkSpaceMaker :: LoadValues(map<int, vector< pair<double,double> > > &data,
				  string file){

  PRINT_DEBUG_FUNCTION(" <LoadValues()>:: loading values for Fid. xsec measurement, file " + file );

  double val=0, err=0;
  string tmp="";
  int line=0;
  while(m_InStream.good()){
    val=0, err=0;
    if( line==0 )
      getline(m_InStream,tmp);
    m_InStream>>tmp;
    m_InStream>>val; m_InStream>>err;
    data[Channel::_incl].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[Channel::_4mu].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[Channel::_4e].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[Channel::_2mu2e].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[Channel::_2e2mu].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[Channel::_2l2l].push_back( make_pair(val,err) );
    m_InStream>>val; m_InStream>>err;
    data[Channel::_4l].push_back( make_pair(val,err) );
    line++;
  }
  
}

void WorkSpaceMaker :: LoadMatrixValues(map<int, vector< pair<double,double> > > &data,
					string file){

  PRINT_DEBUG_FUNCTION(" <LoadMatrixValues()>:: loading values for Diff. xsec measurement: "
                       + m_Variable + " var, file " + file );

  double val=0, err=0;
  string tmp="";
  int line=0;
  int numItems=0;
  int chan = GetDecayChannelId(file);
  while(m_InStream.good()) {
    getline(m_InStream,tmp);
    ++numItems;
  }
  
  PRINT_DEBUG_FUNCTION( " number of row for Matrix = " + to_string(numItems-1) );
  int cols = numItems-1; // # of row found
  line=0;
  
  m_InStream.seekg( m_InStream.beg ); // reset ifstream
  while(m_InStream.good()){
    val=0, err=0;
    if( m_InStream.eof()) break;

    if( line==0 )
      getline(m_InStream,tmp);
    
    m_InStream>>tmp;
    
    for (int ii = 0; ii < cols; ++ii){
      m_InStream>>val; m_InStream>>err;
      PRINT_DEBUG ( " value " + to_string(val) + "   " + to_string(line) + "   "+ to_string(ii));
      data[chan].push_back( make_pair(val,err) );//m_ChNum
    }
    line++;
  }
  
}

void WorkSpaceMaker :: LoadValues(int p, int b, map<int, map<int, map<int, map<string,vector<double> > > > > &data, int ch){
  
  PRINT_DEBUG_FUNCTION(" <LoadValues()>:: loading systematic values for xsec measurement: "
                       + m_Variable + " var ");
  if( m_Fiducial  && !m_multProd )  PRINT_DEBUG_FUNCTION("");
  else PRINT_DEBUG_FUNCTION(" , bin " +to_string(b));
  
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

void WorkSpaceMaker :: LoadValues(vector< pair<double,double> > &data, bool isPRF){
  
  PRINT_DEBUG_FUNCTION(" <LoadValues()>:: loading values for xsec measurement ");
  
  double val=0, err=0;
  string tmp="";
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

  PRINT_DEBUG_FUNCTION(" <LoadValues()>:: loading common systematic values for xsec measurement ");
  
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

void WorkSpaceMaker :: PrintValues(map<int, vector< pair<double,double> > > data, bool isMtx){

  for(uint i=0; i<data.size(); i++){
    cout << "Decay Channel " << GetChannelName(i) << endl;
    uint b=0, Index=0;
    for(uint p=0; p<data[i].size(); p++){
      if( (p % int(m_Category.size()/m_channels.size()) ==0 ) ){
	if(!m_matrix)
	  cout << "---------- Process = " << GetProcessName(b) << " ---------- " << endl;
	else{
	  if(isMtx) cout << "---------- Process = " << m_ProdMode << " row = " << b << " ---------- " << endl;
	  else      cout << "---------- Process = " << m_ProdMode << " ---------- " << endl;
	}
        Index = 0;
        b++;
      }
      if(isMtx)
	cout << "Element = "<< b-1 << "-" << Index << " -> " << data[i].at(p).first << " +- " << data[i].at(p).second << endl;
      else
	cout << "Bin = "<< Index  << " -> " << data[i].at(p).first << " +- " << data[i].at(p).second << endl;
      Index++;
    }
  }
  
}

void WorkSpaceMaker :: PrintValues(vector< pair<double,double> > data, bool isBR, bool isXsec){

  uint b=0, Index=0;
  for(uint i=0; i<data.size(); i++){
    if( isBR )
      cout << "Decay Channel = " << GetChannelName(i) << " " << data.at(i).first << " +- " << data.at(i).second << endl;
    else if( isXsec )
      cout << "ProdMode = " << GetProcessName(i) << " " << data.at(i).first << " +- " << data.at(i).second << endl;
    else{
      if( (i % (int(Process::bbH)+1)) ==0 ){
	cout << "---------- Bin = " << b << " ---------- " << endl;
	Index = 0;
	b++;
      }
      cout << "ProdMode = "<< GetProcessName(Index)  << " " << data.at(i).first << " +- " << data.at(i).second << endl;
      Index++;
    }
  }
  
}

//Double_t WorkSpaceMaker :: PrintACRProduct(int ChNum, int cat){ //unused -> remove?
//
//  double m_val=0;
//  int Pos = cat*(int(Process::bbH)+1);
//  double ggH_ACR = m_acc[ChNum].at(Pos+1).first*m_cf[ChNum].at(Pos+1).first*m_r[ChNum].at(Pos+1).first;
//  double VBF_ACR = m_acc[ChNum].at(Pos+2).first*m_cf[ChNum].at(Pos+2).first*m_r[ChNum].at(Pos+2).first;
//  double WH_ACR  = m_acc[ChNum].at(Pos+3).first*m_cf[ChNum].at(Pos+3).first*m_r[ChNum].at(Pos+3).first;
//  double ZH_ACR  = m_acc[ChNum].at(Pos+4).first*m_cf[ChNum].at(Pos+4).first*m_r[ChNum].at(Pos+4).first;
//  double ttH_ACR = m_acc[ChNum].at(Pos+5).first*m_cf[ChNum].at(Pos+5).first*m_r[ChNum].at(Pos+5).first;
//  double bbH_ACR = m_acc[ChNum].at(Pos+6).first*m_cf[ChNum].at(Pos+6).first*m_r[ChNum].at(Pos+6).first;
//
//  return m_val = (ggH_ACR+VBF_ACR+WH_ACR+ZH_ACR+ttH_ACR+bbH_ACR)*m_Lumi->getVal()*m_binwidth.at(cat)*EvalXS(Pos)/m_binwidth.at(cat)*m_br.at(ChNum).first;
//  
//}

//Double_t WorkSpaceMaker :: PrintExpXS(int ChNum, int cat){
//  
//  double m_val=0;
//
//  int Pos = 0;
//  if( m_Fiducial  && !m_multProd )  Pos= 0;
//  else Pos = cat*(int(Process::bbH)+1);
//  double ggH_ACR, VBF_ACR, WH_ACR, ZH_ACR,ttH_ACR,bbH_ACR;
//  
//  if ( !m_FidTotal ){
//    ggH_ACR = m_cf[ChNum].at(Pos+1).first*m_r[ChNum].at(Pos+1).first;
//    VBF_ACR = m_cf[ChNum].at(Pos+2).first*m_r[ChNum].at(Pos+2).first;
//    WH_ACR  = m_cf[ChNum].at(Pos+3).first*m_r[ChNum].at(Pos+3).first;
//    ZH_ACR  = m_cf[ChNum].at(Pos+4).first*m_r[ChNum].at(Pos+4).first;
//    ttH_ACR = m_cf[ChNum].at(Pos+5).first*m_r[ChNum].at(Pos+5).first;
//    bbH_ACR = m_cf[ChNum].at(Pos+6).first*m_r[ChNum].at(Pos+6).first;
//  }
//  else {
//    ggH_ACR = m_acc[ChNum].at(Pos+1).first*m_cf[ChNum].at(Pos+1).first*m_r[ChNum].at(Pos+1).first;
//    VBF_ACR = m_acc[ChNum].at(Pos+2).first*m_cf[ChNum].at(Pos+2).first*m_r[ChNum].at(Pos+2).first;
//    WH_ACR  = m_acc[ChNum].at(Pos+3).first*m_cf[ChNum].at(Pos+3).first*m_r[ChNum].at(Pos+3).first;
//    ZH_ACR  = m_acc[ChNum].at(Pos+4).first*m_cf[ChNum].at(Pos+4).first*m_r[ChNum].at(Pos+4).first;
//    ttH_ACR = m_acc[ChNum].at(Pos+5).first*m_cf[ChNum].at(Pos+5).first*m_r[ChNum].at(Pos+5).first;
//    bbH_ACR = m_acc[ChNum].at(Pos+6).first*m_cf[ChNum].at(Pos+6).first*m_r[ChNum].at(Pos+6).first;
//    
//  }
//  cout << m_FidTotal << endl;
//
//  if( m_Fiducial && !m_FidTotal) m_val = (m_h_remapped->Integral()*m_Lumi->getVal())/((ggH_ACR+VBF_ACR+WH_ACR+ZH_ACR+ttH_ACR+bbH_ACR)*m_Lumi->getVal());
//  if( m_FidTotal ) m_val = (m_h_remapped->Integral()*m_Lumi->getVal())/((ggH_ACR+VBF_ACR+WH_ACR+ZH_ACR+ttH_ACR+bbH_ACR)*m_Lumi->getVal()*m_br.at(ChNum).first);
//  if( !m_Fiducial ) m_val = (m_h_remapped->GetBinContent(cat+1)*m_Lumi->getVal())/((ggH_ACR+VBF_ACR+WH_ACR+ZH_ACR+ttH_ACR+bbH_ACR)*m_Lumi->getVal());
//
//  return m_val;
//}
