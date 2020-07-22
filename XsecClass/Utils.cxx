#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: InitializeIO(){

  PRINT_DEBUG_FUNCTION(" <InitializeIO()>:: Initializing I/O objects/values ");
  
  if( m_chSplit== 2  || m_Fiducial ) m_channels = {Channel::_4mu  ,Channel::_4e,
						   Channel::_2mu2e,Channel::_2e2mu};
  else if( m_chSplit == 1 )          m_channels = {Channel::_2l2l ,Channel::_4l};
  else                               m_channels = {m_ChNum};

  LoadInputFile();
  DefineInputData();
  LoadObject();
  DefineCategoryMap();
  if ( m_do2D || m_Fiducial ) SetM4lNbins();
  else m_Mbins = 1;
  LoadCorrFact();
  LoadAcceptance();
  LoadNotFid();
  LoadProdModeFraction();
  LoadMinitreeN();
  LoadBranchingRatio();
  LoadCrossSection();
  CreateProcList();

}

void WorkSpaceMaker :: LoadInputFile(){

  PRINT_DEBUG_FUNCTION(" <LoadInputFile()>:: Loading Input File  ");

  m_InFile = new TFile( (m_Dir+m_PathToFile+"/"+m_FileName).c_str() );

  if( m_InFile->IsZombie() ){
    PRINT_FATAL(" <LoadInputFile()>:: \033[1;31m ERROR, no input file! Exiting ");
    exit(0);
  }
  
  if(m_addSys || m_addShapeSys){
    m_SysFile = new TFile( (m_Dir+m_PathToFile+"/"+m_SysFileName).c_str() );
    if( m_SysFile->IsZombie() ){
      PRINT_FATAL(" <LoadInputFile()>:: \033[1;31m ERROR, no input Sys file! Exiting ");
      exit(0);
    }
    m_AcInFile = new TFile( (m_Dir+m_PathToFile+"/"+m_AcFileName).c_str() );
    if( m_AcInFile->IsZombie() ){
      PRINT_FATAL(" <LoadInputFile()>:: \033[1;31m ERROR, no input aF/cF file! Exiting ");
      exit(0);
    }
    m_AcSysFile = new TFile( (m_Dir+m_PathToFile+"/"+m_AcSysFileName).c_str() );
    if( m_AcSysFile->IsZombie() && !m_matrix ){
      PRINT_FATAL(" <LoadInputFile()>:: \033[1;31m ERROR, no input aF/cF Sys file! Exiting ");
      exit(0);
    }

  }
  
}

void WorkSpaceMaker :: DefineInputData(){

  PRINT_DEBUG_FUNCTION(" <DefineInputData>:: Defining input CF, Acc, r, xsec data files ");

  string matrixname = "";
  if(m_matrix)   matrixname = "rspmtx_";
  else           matrixname = "cF_";

  std::string prefixDir = "Fid/"+m_mcTypeMap[m_mcVers]+"/", lepType = "Dressed/";
  if( !m_Fiducial )  prefixDir = "Diff/"+m_Variable+"/"+m_mcTypeMap[m_mcVers]+"/";
  if( m_useBornLep ) lepType = "Born/";

  vector<string> prodModeList = { GetProcessName(Process::Signal), GetProcessName(Process::ggH)   ,
				  GetProcessName(Process::VBF)   , GetProcessName(Process::WH)    ,
				  GetProcessName(Process::ZH)    , GetProcessName(Process::ttH)   ,
				  GetProcessName(Process::bbH)   , GetProcessName(Process::ggHbbH),
				  GetProcessName(Process::VH) };
  
  vector<string> chanList = { GetChannelName(Channel::_incl) , GetChannelName(Channel::_4mu)  ,
			      GetChannelName(Channel::_4e)   , GetChannelName(Channel::_2mu2e),
			      GetChannelName(Channel::_2e2mu), GetChannelName(Channel::_2l2l) ,
			      GetChannelName(Channel::_4l) };
    
  if(!m_matrix){

    for(unsigned int p = 0; p<prodModeList.size(); p++){
      m_cfFile.push_back(     prefixDir+lepType+matrixname+prodModeList.at(p)+"_"+m_Bstr+".dat" );
      m_accFile.push_back(    prefixDir+lepType+"aF_"+prodModeList.at(p)+"_"+m_Bstr+".dat"      );
      m_rFile.push_back(      prefixDir+"rF_"+prodModeList.at(p)+"_"+m_Bstr+".dat"              );
      m_mtFile.push_back(     prefixDir+"Nminitree_"+prodModeList.at(p)+"_"+m_Bstr+".dat"       );
      m_notFidFile.push_back( prefixDir+lepType+"fNonFid_"+prodModeList.at(p)+"_"+m_Bstr+".dat" );
    }
    
  }
  else{

    for(unsigned int c = 0; c<chanList.size(); c++){
      m_cfFile.push_back(  prefixDir+lepType+matrixname+m_ProdMode+"_"+chanList.at(c)+"_"+m_Bstr+".dat"  );
    }
    
    m_accFile.push_back(     prefixDir+lepType+"aF_"+m_ProdMode+"_"+m_Bstr+".dat"                 );
    m_rFile.push_back(       prefixDir+"rF_"+m_ProdMode+"_"+m_Bstr+".dat"                         );
    m_notFidFile.push_back(  prefixDir+lepType+matrixname+"fNonFid_"+m_ProdMode+"_"+m_Bstr+".dat" );
    m_mtFile.push_back(      prefixDir+matrixname+"Nminitree_"+m_ProdMode+"_"+m_Bstr+".dat"       );
    
  }

  m_brFile   = "BR.dat";
  m_xsecFile = "Xsec.dat";
  prodModeList.clear();
  chanList.clear();
  
}

string WorkSpaceMaker :: GetCurrentWorkingDir( void ) {
  
  char buff[FILENAME_MAX];
  //GetCurrentDir( buff, FILENAME_MAX );
  string current_working_dir(buff);
  
  return current_working_dir;
  
}

void WorkSpaceMaker :: DefineCategoryMap(){

  PRINT_DEBUG_FUNCTION(" <DefineCategoryMap()>:: filling categories map ");

  if( m_Fiducial ){
    m_Category[ Channel::_4mu   - 1 ] = GetChannelName(Channel::_4mu)  ;
    m_Category[ Channel::_4e    - 1 ] = GetChannelName(Channel::_4e)   ;
    m_Category[ Channel::_2mu2e - 1 ] = GetChannelName(Channel::_2mu2e);
    m_Category[ Channel::_2e2mu - 1 ] = GetChannelName(Channel::_2e2mu);
  }
  else{
    if(m_multProd)
      m_Htmp = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_"+GetChannelName(m_ChNum)+"_AllSig").c_str() );
    else
      m_Htmp = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_"+GetChannelName(m_ChNum)+"_"+m_ProdMode).c_str() );
    if ( m_Htmp == NULL ) {
      if(m_multProd)
	PRINT_FATAL(" Histogram: h"+m_Variable+"_"+GetChannelName(m_ChNum)+"_AllSig" + " not found, exit!");
      else
	PRINT_FATAL(" Histogram: h"+m_Variable+"_"+GetChannelName(m_ChNum)+"_"+m_ProdMode + " not found, exit!");
      exit(0);
    }

    int its = m_Htmp->GetNbinsX();
    for (unsigned int J=0; J<m_channels.size(); J++){
      for(int i=0; i<its; i++){
	m_Category[ i + J*its ] = "bin"+to_string(i)+"_"+GetChannelName(m_channels.at(J));
      }
    }
    m_Htmp->Delete();
  }
  
}

void WorkSpaceMaker :: SetM4lNbins(){

  PRINT_DEBUG_FUNCTION(" <SetM4lNbins()>:: setting number of bins for m4l ");

  if( m_Fiducial )
    m_Htmp = (TH1F*)m_InFile->Get( ("hm_"+GetChannelName(m_ChNum)+"_AllSig").c_str() );
  else
    if(m_multProd)
      m_Htmp = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+"bin0_"+GetChannelName(m_ChNum)+"_AllSig").c_str() );
    else
      m_Htmp = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+"bin0_"+GetChannelName(m_ChNum)+"_"+m_ProdMode).c_str() );
  if ( m_Htmp == NULL ) {
    PRINT_FATAL(" Histogram M4l: not found, exit!");
    exit(0);
  }
  if(m_redM4lBins){
    if (m_Bstr=="110bin") m_Htmp->Rebin(5);
    else m_Htmp->Rebin(3);
  }

  m_Mbins = m_Htmp->GetNbinsX();
  m_mMin  = m_Htmp->GetXaxis()->GetXmin();
  m_mMax  = m_Htmp->GetXaxis()->GetXmax();
  m_Htmp->Delete();
  
}

void WorkSpaceMaker :: LoadObject(){

  PRINT_DEBUG_FUNCTION(" <LoadObject()>:: Loading Object ");
  
  m_paramOfInterest = new RooArgSet();
  m_Lumi = new RooRealVar("L","L", m_lumi, 0, 100000);
  m_Lumi->Print();
  m_globalObservables.add(*m_Lumi);
  
}

void WorkSpaceMaker :: CreateOutDir(){

  
  m_OutDir = m_Dir+"../ws_output/"+m_Variable+"/";
  CheckOutDir(m_OutDir);
    
  if (m_useBornLep) m_OutDir = m_OutDir+"/Born/";
  else m_OutDir = m_OutDir+"/Dres/";
  CheckOutDir(m_OutDir);

  m_OutDir = m_OutDir+"/"+m_Channel+"/";
  CheckOutDir(m_OutDir);

  if (m_matrix) m_OutDir = m_OutDir+"/matrix/";
  else m_OutDir = m_OutDir+"/cf/";
  CheckOutDir(m_OutDir);

  if (m_floatqqZZ) m_OutDir = m_OutDir+"/floatZZ/";
  else m_OutDir = m_OutDir+"/fixZZ/";
  CheckOutDir(m_OutDir);


}

void WorkSpaceMaker :: CheckVectorSize(TH1F *h, int chnum){

 // int Nbins = h->GetNbinsX();
  // TO BE FIXED
  /*
  if( Nbins != (int)m_acc[chnum].size()/(1) ){
    cout << "<DoSinglePdf()>:: \033[1;31m ERROR: ACC vector size ("
	 << m_acc[chnum].size()/(int(Process::bbH)+1) << ")" << " != Number of bins ("
	 << Nbins << ")!! Exiting \033[0m " << endl;
    exit(0);
  }
  if( Nbins != (int)m_cf[chnum].size()/(int(Process::bbH)+1) ){
    cout << "<DoSinglePdf()>:: \033[1;31m ERROR: CF vector size ("
	 << m_cf[chnum].size()/(int(Process::bbH)+1) << ")" << " != Number of bins ("
	 << Nbins << ")!! Exiting \033[0m " << endl;
    exit(0);
  }
  if( Nbins != (int)m_r[chnum].size()/(1) ){
    cout << "<DoSinglePdf()>:: \033[1;31m ERROR: R vector size ("
	 << m_r[chnum].size()/(int(Process::bbH)+1) << ")" << " != Number of bins ("
	 << Nbins << ")!! Exiting \033[0m " << endl;
    exit(0);
  }
  */
  
}


TH1F* WorkSpaceMaker :: remapHisto( TH1F* hIn, int bin ){

  PRINT_DEBUG_FUNCTION(" <remapHisto()> :: remapping histogram " + (string) hIn->GetName());
  
  m_hremapped =  new TH1F ( (string(hIn->GetName())+"remapped"+"_"+to_string(bin)).c_str(),
			    (string(hIn->GetTitle())+"remapped"+"_"+to_string(bin)).c_str(),
			    hIn->GetNbinsX(), 0, hIn->GetNbinsX() ); 
  RooRealVar *BinWidth = NULL;
  float binw = 0;
  vector<float> mjjWidth;
  mjjWidth.push_back(    0.0 );
  mjjWidth.push_back(    1.0 );
  mjjWidth.push_back(  121.0 );
  mjjWidth.push_back(  451.0 );
  mjjWidth.push_back( 3001.0 );
  for(Int_t i=1; i<hIn->GetNbinsX()+1; ++i ) {
    if( m_VariableId==Variable::mjj ){
      binw = mjjWidth.at(i)-mjjWidth.at(i-1);
      m_binnames.push_back(mjjWidth.at(i-1));
      m_binlowerlimit.push_back(mjjWidth.at(i-1));
    }
    else{
      binw = hIn->GetBinWidth(i);
      m_binnames.push_back(hIn->GetBinLowEdge(i));
      m_binlowerlimit.push_back(hIn->GetBinLowEdge(i));
    }
    
    if( m_Fiducial ) {
      binw = 1;
      BinWidth = new RooRealVar( ("BinWidth_"+to_string(i-1)).c_str(),
				 ("BinWidth_"+to_string(i-1)).c_str(), binw );
    }
    else
      BinWidth = new RooRealVar( ("BinWidth_bin"+to_string(i-1)).c_str(),
				 ("BinWidth_bin"+to_string(i-1)).c_str(), binw );

    m_hremapped->SetBinContent(i, hIn->GetBinContent(i));
    m_hremapped->SetBinError(i,hIn->GetBinError(i));
    m_binwidth.push_back(binw);
    m_binwidthroorealvar.push_back(BinWidth);

    if( m_verbose ){
      cout << "<remapHisto()> :: Bin "<< i << " " << "Remap = "
	   << m_hremapped->GetBinContent(i) << " Orig = "
	   << hIn->GetBinContent(i) << endl;
      cout << " Bin width saved = " << m_binwidth.at(i-1) << endl;
      if(m_Variable=="mjj"){
	cout << " Original Bin Information = " << mjjWidth.at(i-1)
	     << " " << mjjWidth.at(i-1)+m_binwidth.at(i-1)
	     << " " << m_binwidth.at(i-1) << endl;
      }
      else{
	cout << " Original Bin Information = " << hIn->GetBinLowEdge(i)
	     << " " << hIn->GetBinLowEdge(i)+hIn->GetBinWidth(i)
	     << " " << hIn->GetBinWidth(i)  << endl;
      }
      cout << " remapped Bin Information = " << m_hremapped->GetBinLowEdge(i)
	   << " " << m_hremapped->GetBinLowEdge(i)+m_hremapped->GetBinWidth(i)
	   <<" "<< m_hremapped->GetBinWidth(i)  << endl;
      cout << " Original integral = " << hIn->Integral() << endl;
      cout << " remapped integral = " << m_hremapped->Integral() << endl;

    }
  }
  if(m_Variable=="mjj")
    m_binnames.push_back( mjjWidth.at(mjjWidth.size()-1) );
  else
    m_binnames.push_back( hIn->GetBinLowEdge(hIn->GetNbinsX()) +
			  hIn->GetBinWidth(hIn->GetNbinsX()) );

  return m_hremapped;
  
}

void WorkSpaceMaker :: CreateProcList(){

  m_process[ GetProcessName(Process::Signal) ] = Process::Signal;
  m_process[ GetProcessName(Process::ggH)    ] = Process::ggH   ;
  m_process[ GetProcessName(Process::VBF)    ] = Process::VBF   ;
  m_process[ GetProcessName(Process::WH)     ] = Process::WH    ;
  m_process[ GetProcessName(Process::ZH)     ] = Process::ZH    ;
  m_process[ GetProcessName(Process::ttH)    ] = Process::ttH   ;
  m_process[ GetProcessName(Process::bbH)    ] = Process::bbH   ;
  m_process[ GetProcessName(Process::ggHbbH) ] = Process::ggHbbH;
  m_process[ GetProcessName(Process::VH)     ] = Process::VH    ;
  m_process[ GetProcessName(Process::ggZZ)   ] = Process::ggZZ  ;
  m_process[ GetProcessName(Process::qqZZ)   ] = Process::qqZZ  ;
  m_process[ GetProcessName(Process::redBkg) ] = Process::redBkg;
  
}

void WorkSpaceMaker :: CleanUp(){

  PRINT_SYS ( " <CleanUp()>:: cleaning memory ... ");
  
  m_cf.clear();
  m_acc.clear();
  m_r.clear();
  m_br.clear();
  m_xsec.clear();
  m_xsScale.clear();
  m_InFile->Close();
  if (m_addSys){
    m_SysFile->Close();
    m_AcInFile->Close();
    m_AcSysFile->Close();
  }

}

/*
TH1F* WorkSpaceMaker :: GetDoubleDifferentialH( vector<TH1F*> v_h ){
  
  cout << "\033[1;32m <GetDoubleDifferentialH()>\033[0m" << endl;

  int Ncat = 0;
  
  for ( unsigned int =0; i< v_h.size(); ++i ) Ncat = v_h.at(i)->GetNbisX();
  
  m_doubleDiff = new TH1F* ("double_diff"+m_Variable+)
  
}
*/

string WorkSpaceMaker :: RetrieveLastNonEmptyBin(string variable, int channel, string process){

  PRINT_DEBUG_FUNCTION("<RetrieveLastNonEmptyBin()>:: detecting last non empty bin for process "+
		       process+" and channel "+to_string(channel));
  int bins = m_h_remapped->GetNbinsX();
  int nEbin = -1;
  for(int h=0; h<bins; h++){
    TH1F *hm4l = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+"bin"+to_string(h)+
					"_"+GetChannelName(channel)+"_"+process).c_str() );
    if(hm4l->Integral()>0 && hm4l->GetEntries()>100) nEbin = h;
  }
  string binStr = to_string(nEbin);
  return binStr;
  
}

void WorkSpaceMaker :: OpenTableFile(string unfold, string sys, string what){


  m_tableFile.open ( (m_OutDir+"/"+m_Variable+unfold+"_fit_"+
		      sys+"_"+what+"_table.tex").c_str() );
  m_tableFile << "  \\begin{tabular}{ c | c | c | c }\n";
  m_tableFile << "   POI &  XS $_{\\mathrm{inj}}$  & XS $_{\\mathrm{fit}}$ & Rel. Error\\\\\n ";
  m_tableFile << " \\hline \n";
  
}

void WorkSpaceMaker :: WriteTableFile(string prefix, int pos){

  double preFit   = GetPreFitXsecVal(pos);
  double postFit  = GetPostFitXsecVal(pos);
  double upErr    = GetPostFitXsecUpErr(pos);
  double dwErr    = GetPostFitXsecDownErr(pos);
  double upErrPer = 100*upErr/postFit;
  double dwErrPer = 100*dwErr/postFit;

  m_tableFile << (prefix+
		  ConvertToStringWithPrecision(preFit, 3)    + " & $"+
		  ConvertToStringWithPrecision(postFit, 3)   + "^{+"+
		  ConvertToStringWithPrecision(upErr, 3)     + "}_{-"+
		  ConvertToStringWithPrecision(dwErr, 3)     + "}$ & $^{+"+
		  ConvertToStringWithPrecision(upErrPer, 3)  + "\\%}_{"+
		  ConvertToStringWithPrecision(dwErrPer, 3) + "\\%}$ \\\\\n");
  
}

void WorkSpaceMaker :: CloseTableFile(string unfold,string sys, string what){

  m_tableFile << "  \\end{tabular}";
  m_tableFile << ("  %\\caption {Expected and fitted cross sections in each category of $"+
		  m_Variable+unfold+"$ using Asimov dataset with $\\mathcal{L} = "+
		  ConvertToStringWithPrecision(m_Lumi->getVal(), 3)+
		  " \\,\\mathrm{fb}^{-1}$. }\\label{tab:"+
		  m_Variable+unfold+"_fit_"+sys+"_"+what+"_asimov}\n");
  m_tableFile.close();
  
}

void WorkSpaceMaker :: OpenResultsFile(string unfold, string sys, string what){

  m_resultsFile.open ( (m_OutDir+"/"+m_Variable+unfold+"_fit_"+sys+"_"+
			what+"_"+m_ProdMode+"_"+m_ProdHist+".dat").c_str() );
  m_resultsFile << "preFitVal  postFitVal  error_up  error_down \n" ;
  
}

void WorkSpaceMaker :: WriteResultsFile(int pos){

  double preFit   = GetPreFitXsecVal(pos);
  double postFit  = GetPostFitXsecVal(pos);
  double upErr    = GetPostFitXsecUpErr(pos);
  double dwErr    = GetPostFitXsecDownErr(pos);
  
  m_resultsFile << (ConvertToStringWithPrecision(preFit, 5)    + "  "+
		    ConvertToStringWithPrecision(postFit, 5)   + "  "+
		    ConvertToStringWithPrecision(upErr, 5)     + "  "+
		    ConvertToStringWithPrecision(dwErr, 5)     + "\n");
  
}

void WorkSpaceMaker :: CloseResultsFile(){

  m_resultsFile.close();
  
}

double WorkSpaceMaker :: GetPreFitXsecVal(int pos){

  return m_preFitVal.at(pos);
  
}

double WorkSpaceMaker :: GetPostFitXsecVal(int pos){

  return m_postFitVal.at(pos);
    
}

double WorkSpaceMaker :: GetPostFitXsecUpErr(int pos){

  return m_LeftRightErrors.second-m_postFitVal.at(pos);
  
}

double WorkSpaceMaker :: GetPostFitXsecDownErr(int pos){
  
  return m_postFitVal.at(pos)-m_LeftRightErrors.first;
  
}

int WorkSpaceMaker :: GetDecayChannelId(string file){

  string tmp = file.substr( (size_t)(file.find(m_ProdMode)+m_ProdMode.length()+1),
			    (size_t)(file.find(m_Bstr)-1) );
  tmp = tmp.substr(0, (size_t)(tmp.find(m_Bstr)-1) );
  return GetChannelID(tmp);
  
}
