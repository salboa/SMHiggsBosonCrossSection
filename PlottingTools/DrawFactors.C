/* program includes */
#include "DrawFactors.h"

int main( int argc, char* argv[] ) {

  std::string var  = "pt"  ;
  std::string chan = "incl";
  m_process        = "";
  m_mcVersion      = 0 ;
  m_nBins          = 30;
  m_lumi           = GetDefaultIntLumi();
  bool useGUI      = false;
  bool printHelp   = false;
  for(int i = 1; i < argc; ++i){
    bool validCmd = false;
    if( !strcmp(argv[i],"--variable")       ){ var         = argv[i+1];            validCmd = true; }
    else if( !strcmp(argv[i],"--channel")   ){ chan        = argv[i+1];            validCmd = true; }
    else if( !strcmp(argv[i],"--isConf")    ){ m_isConf    = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--isPaper")   ){ m_isPaper   = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--mrgProd")   ){ m_mrgProd   = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--addAllSig") ){ m_allSig    = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--useBorn")   ){ m_isBorn    = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--process")   ){ m_process   = argv[i+1];            validCmd = true; }
    else if( !strcmp(argv[i],"--mcVersion") ){ m_mcVersion = std::stoi(argv[i+1]); validCmd = true; }
    else if( !strcmp(argv[i],"--nBins")     ){ m_nBins     = std::stoi(argv[i+1]); validCmd = true; }
    else if( !strcmp(argv[i],"--doMatrix")  ){ m_doMatrix  = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--useGUI")    ){ useGUI      = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--debug")     ){ m_debug     = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp   = true;                 validCmd = true; }
    else{
      if( !validCmd && std::string(argv[i]).find("--")!=std::string::npos ){
	PRINT_ERROR( "Option "+std::string(argv[i])+" not valid! exiting!" );
	exit(0);
      }
    }
  }
  if(printHelp){
    std::cout << "DrawFactors: make A, C, R factors and mig/rps matrices plots! "   << std::endl;
    std::cout << " usage : ./DrawFactors [--help] [--variable pt4l]"                << std::endl;
    std::cout << "                           [--channel incl] [--mrgProd]"          << std::endl;
    std::cout << "                           [--useBorn] [--process] [--isConf]"    << std::endl;
    std::cout << "                           [--isPaper] [--mcVersion] [--nBins]"   << std::endl;
    std::cout << "                           [--doMigMtx] [--doRpsMtx] [--useGUI]"  << std::endl;
    std::cout << "                           [--addAllSig] [--debug] [--verbose]"   << std::endl;
    std::cout << "                                                               "  << std::endl;
    std::cout << " Optional arguments (default value): "                            << std::endl;
    std::cout << " --help      print this help and exit"                            << std::endl;
    std::cout << " --variable  choose variables ('pt4l'). Options are: "            << std::endl;
    std::cout << "             'pt4l', 'pt0j', 'pt1j', 'pt2j', 'm12', 'm34',"       << std::endl;
    std::cout << "             'y4l', 'njet', 'njetv2', 'njetv3', 'njetv4', "       << std::endl;
    std::cout << "             'nbjet', 'cts', 'ljpt', 'mjj', 'etajj', "            << std::endl;
    std::cout << "             'phijj', 'm12m34', 'm4l' "                           << std::endl;
    std::cout << " --channel   choose 4l decay mode ('incl'). Options are: "        << std::endl;
    std::cout << "             'incl', '4mu', '4e', '2mu2e', '2e2mu', "             << std::endl;
    std::cout << "             '2l2l', '4l' "                                       << std::endl;
    std::cout << " --mrgProd   enable merging Higgs Production mode (false) "       << std::endl;
    std::cout << " --useBorn   enable Born leptons instead of Dressed (false) "     << std::endl;
    std::cout << " --process   define signal Production mode ("") "                 << std::endl;
    std::cout << " --isConf    enable Conference note labels (false) "              << std::endl;
    std::cout << " --isPaper   enable Paper labels (false) "                        << std::endl;
    std::cout << " --mcVersion define mc Version ('0' = mc16). Options are:"        << std::endl;
    std::cout << "             0 (mc16), 1 (mc15c), 2 (mc16a), 3 (mc16d) "          << std::endl;
    std::cout << " --nBins     define number of bins ('30' = mass range[115-130])"  << std::endl;
    std::cout << " --doMatrix  enable plotting Migration/Response Matrices (false)" << std::endl;
    std::cout << " --addAllSig enable plotting A/C/R for AllSig (false)"            << std::endl;
    std::cout << " --useGUI    enable GUI (false) "                                 << std::endl;
    std::cout << " --debug     enable debug mode (false) "                          << std::endl;
    exit(0);
  }
  FillMcVersionsMap();
  if(m_process!="" && !m_doMatrix){
    PRINT_INFO("<DrawFactors()>:: process "+m_process+" specified: enabling release comparison mode");
    m_procNum   = GetProcessNumber(m_process);
    m_doRelComp = true;
  }
  if(m_doRelComp && m_mcVersion!=0){
    PRINT_WARNING("<DrawFactors()>:: release comparison mode enabled and mc Version = "+
		  std::to_string(m_mcVersion)+" ("+m_mcTypeMap[m_mcVersion]+")!");
    PRINT_WARNING("                      setting mc Version to 0 (mc16)");
    m_mcVersion = 0;
  }
  if(m_doMatrix && var=="m4l"){
    PRINT_WARNING("<DrawFactors()>:: matrix mode enabled but variable is "+var+
		  " -> no matrix available!");
    PRINT_WARNING("                      switching matrix mode off!");
    m_doMatrix = false;
  }
  if(m_doMatrix && m_process==""){
    PRINT_WARNING("<DrawFactors()>:: matrix mode enabled but process not defined!");
    PRINT_WARNING("                      switching using AllSig!");
    m_process = "AllSig";
  }
  
  SetDebugLevel(m_debug);
  
  if(m_debug){
    std::cout << "<DrawFactors()>:: Options set: "                   << std::endl;
    std::cout << "                      variable  = " << var         << std::endl;
    std::cout << "                      channel   = " << chan        << std::endl;
    std::cout << "                      mrgProd   = " << m_mrgProd   << std::endl;
    std::cout << "                      addAllSig = " << m_allSig    << std::endl;
    std::cout << "                      isConf    = " << m_isConf    << std::endl;
    std::cout << "                      isPaper   = " << m_isPaper   << std::endl;
    std::cout << "                      isBorn    = " << m_isBorn    << std::endl;
    std::cout << "                      process   = " << m_process   << std::endl;
    std::cout << "                      mcVersion = " << m_mcVersion << std::endl;
    std::cout << "                      nBins     = " << m_nBins     << std::endl;
    std::cout << "                      doMatrix  = " << m_doMatrix  << std::endl;
    std::cout << "                      doRelComp = " << m_doRelComp << std::endl;
    std::cout << "                      useGUI    = " << useGUI      << std::endl;
    std::cout << "                      debug     = " << m_debug     << std::endl;
  }
    
  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  DrawFactors( GetVariableID(var), GetChannelID(chan) );
  if(useGUI){
    std::cout << "<DrawFactors()>:: using Rint -> ROOT will remain "
	      << "opened ... " << std::endl;
    myApp->Run();
  }

  myApp->Delete();
  return 0;
  
}

void DrawFactors(int varId, int chanId){

  PRINT_DEBUG("<DrawFactors::DrawFactors()>:: starting ACR plotting tools ");

  SetAtlasStyle();
  TH1::SetDefaultSumw2(kTRUE);

  m_filePrefix  = "../varsDistro/XsecInputs_"+std::to_string(m_nBins)+"bin_";
  if(m_doMatrix) m_filePrefix += "MatrixARfactors";
  else           m_filePrefix += "ACRfactors";

  /*if(!m_doMatrix)*/ DefineStyle();
  m_varName = "";
  if(varId==Variable::m4l){
    chanId   = Channel::_incl; m_varName  = "fid";
  }
  else{
    m_varName = GetVariableName(varId);
  }
  m_chanName = GetChannelName(chanId);
  m_nBins_string = std::to_string(m_nBins);

  DefineInputFiles();
  RetrieveHistograms();
  if(m_doMatrix) DrawMatrices(varId,chanId);
  else           DrawACR(varId,chanId);
  
}

void DrawMatrices(int varId, int chanId){

  PRINT_DEBUG("<DrawFactors::DrawMatrices()>:: drawing migration and response matrices ");

  SetPalette(false,false);
  gStyle->SetPaintTextFormat("2.2f");
  FillVarsRanges();

  /* Draw Migration Matrix*/
  c = CreateCanvas("MigMtx",1000,1000,true);
  ScaleMatrixValues(m_migMtx);
  SetMatrixPlotStyle(m_migMtx,true);
  AdjustMatrixAxes(m_migMtx,varId);
  //m_migMtx->SetMarkerColor(kGray+2);
  m_migMtx->Draw("ZCOLTEXT");
  DrawAtlasLabel(false,m_isConf,m_isPaper,0.28,0.92,0.035);
  DrawEnergyLumi(m_lumi,false,false,0.45,0.92,0.035);
  DrawChannel(chanId,false,0.69,0.92,0.035);
  c->Print("mtx/"+m_varName+"_migmtx_"+m_process+"_"+m_chanName+"_"+m_nBins_string+".pdf");
  
  /* Draw Response Matrix*/
  c = CreateCanvas("RpsMtx",1000,1000,true);
  SetMatrixPlotStyle(m_rpsMtx);
  AdjustMatrixAxes(m_rpsMtx,varId);
  //m_rpsMtx->SetMarkerColor(kGray+2);
  m_rpsMtx->Draw("ZCOLTEXT");
  DrawAtlasLabel(false,m_isConf,m_isPaper,0.28,0.92,0.035);
  DrawEnergyLumi(m_lumi,false,false,0.45,0.92,0.035);
  DrawChannel(chanId,false,0.69,0.92,0.035);
  c->Print("mtx/"+m_varName+"_rspmtx_"+m_process+"_"+m_chanName+"_"+m_nBins_string+".pdf");

  /* Draw fnonFid*/
  c = CreateCanvas("fnonFid");
  //if(m_doRelComp){
  //  p1 = CreateTopPad("fnonFid");  p2 = CreateBottomPad("fnonFid");
  //  p1->Draw();               p2->Draw();
  //}
  leg = CreateLegend();
  DrawfnonFidPlots(m_fnonFid,leg,chanId,varId);
  c->Update(); 
  c->Print("");
  c->Print("acr/"+m_varName+"_fnonFid_"+m_process+"_"+m_chanName+"_"+m_nBins_string+".pdf");
  
}

void DrawACR(int varId, int chanId){

  PRINT_DEBUG("<DrawFactors::DrawMatrices()>:: drawing A, C and R ");
  
  /* Draw cF*/
  c = CreateCanvas("cF");
  if(m_doRelComp){
    p1 = CreateTopPad("cF");  p2 = CreateBottomPad("cF");
    p1->Draw();               p2->Draw();
  }
  leg = CreateLegend();
  DrawPlots(m_Cfac,m_Crat,factor::cF,leg,chanId,varId);
  c->Update(); 
  c->Print("");
  c->Print("acr/"+m_varName+"_cF_"+m_process+"_"+m_chanName+"_"+m_nBins_string+".pdf");

  /* Draw aF*/
  c = CreateCanvas("aF");
  if(m_doRelComp){
    p1 = CreateTopPad("aF");  p2 = CreateBottomPad("aF");
    p1->Draw();               p2->Draw();
  }
  leg = CreateLegend();
  DrawPlots(m_Afac,m_Arat,factor::aF,leg,chanId,varId);
  c->Update(); 
  c->Print("acr/"+m_varName+"_aF_"+m_process+"_"+m_chanName+"_"+m_nBins_string+".pdf");
    
  /* Draw rF*/
  c = CreateCanvas("rF");
  if(m_doRelComp){
    p1 = CreateTopPad("rF");  p2 = CreateBottomPad("rF");
    p1->Draw();               p2->Draw();
  }
  leg = CreateLegend();
  DrawPlots(m_Rfac,m_Rrat,factor::rF,leg,chanId,varId);
  c->Update(); 
  c->Print("acr/"+m_varName+"_rF_"+m_process+"_"+m_chanName+"_"+m_nBins_string+".pdf");
    
}

void RetrieveHistograms(){

  PRINT_DEBUG("<DrawFactors::RetrieveHistograms()>:: retrieving needed histograms ");

  if(m_doMatrix) RetrieveMatrices();
  else           RetrieveACR();
  
}

void RetrieveMatrices(){

  PRINT_DEBUG("<DrawFactors::RetrieveMatrices()>:: retrieving migration and responce matrices ");

  std::string Prefix = "";
  if(m_isBorn){ Prefix += "Born_"; }
  else        { Prefix += "Dres_"; }
  std::string name = m_varName+"_"+m_chanName+"_";

  m_migMtx = (TH2D*)m_fMap[GetMCreleaseName(m_mcVersion)]->Get( ("MigMtx_"+Prefix+name+m_process).c_str() );
  m_rpsMtx = (TH2D*)m_fMap[GetMCreleaseName(m_mcVersion)]->Get( ("Mtx_"+Prefix+name+m_process).c_str()    );
  
  PRINT_DEBUG("                                          running in single MC release mode");
  
  std::string mctype = GetMCreleaseName(m_mcVersion);
  for( auto& x: m_ProcColor){
    PRINT_VERBOSE("                                          getting "+x.first+" histograms ... ");
    if(m_varName.find("fid")!=std::string::npos){
      m_fnonFid[x.first][mctype] = GetFiducialPlot( "fNonFid_Rel_"+Prefix, x.first, mctype );
    }
    else{
      m_fnonFid[x.first][mctype] = (TH1D*)m_fMap[mctype]->Get( ("fNonFid_Rel_"+Prefix+name+x.first).c_str() );
    }
  }  
  
#ifdef DEBUG
  for( auto& x: m_Afac){
    PRINT_VERBOSE( "                                          process = "+
		   x.first+" map-size fnonFid = "+std::to_string(m_fnonFid[x.first].size()) );
  }
#endif
  
}

void RetrieveACR(){

  PRINT_DEBUG("<DrawFactors::RetrieveACR()>:: retrieving A, C and R ");

  std::string Prefix = "";
  if(m_isBorn){ Prefix += "Born_"; }
  else        { Prefix += "Dres_"; }
  std::string name = m_varName+"_"+m_chanName+"_";

  if(m_doRelComp){

    PRINT_VERBOSE("                                          running in MC release comparison mode");
    PRINT_VERBOSE("                                          getting "+m_process+" histograms ... ");
    for(auto &x: m_mcRelColor){

      if(m_varName.find("fid")!=std::string::npos){
	m_Afac[m_process][x.first] = GetFiducialPlot( "aF_"+Prefix, m_process, x.first);
	m_Cfac[m_process][x.first] = GetFiducialPlot( "cF_"+Prefix, m_process, x.first);
	m_Rfac[m_process][x.first] = GetFiducialPlot( "rF_"       , m_process, x.first);
      }
      else{
	m_Afac[m_process][x.first] = (TH1D*)m_fMap[x.first]->Get( ("aF_"+Prefix+name+m_process).c_str() );
	m_Cfac[m_process][x.first] = (TH1D*)m_fMap[x.first]->Get( ("cF_"+Prefix+name+m_process).c_str() );
	m_Rfac[m_process][x.first] = (TH1D*)m_fMap[x.first]->Get( ("rF_"+name+m_process).c_str()        );
      }
    }
  }
  else{

    PRINT_VERBOSE("                                          running in single MC release mode");

    std::string mctype = GetMCreleaseName(MCtype::All);
    for( auto& x: m_ProcColor){
      PRINT_VERBOSE("                                          getting "+x.first+" histograms ... ");
      if(m_varName.find("fid")!=std::string::npos){
	m_Afac[x.first][mctype] = GetFiducialPlot( "aF_"+Prefix, x.first, mctype );
	m_Cfac[x.first][mctype] = GetFiducialPlot( "cF_"+Prefix, x.first, mctype );
	m_Rfac[x.first][mctype] = GetFiducialPlot( "rF_"       , x.first, mctype );
      }
      else{
	m_Afac[x.first][mctype] = (TH1D*)m_fMap[mctype]->Get( ("aF_"+Prefix+name+x.first).c_str() );
	m_Cfac[x.first][mctype] = (TH1D*)m_fMap[mctype]->Get( ("cF_"+Prefix+name+x.first).c_str() );
	m_Rfac[x.first][mctype] = (TH1D*)m_fMap[mctype]->Get( ("rF_"+name+x.first).c_str()        );
      }
    }
    
  }

  if(m_doRelComp){
    PRINT_VERBOSE("                                          getting "+m_process+" ratio histograms ... ");

    std::string NomMcType = GetMCreleaseName(MCtype::All);//mc15c);
    for(auto &x: m_mcRelColor){
      
      m_Arat[m_process][x.first] = MakeRatio( m_Afac[m_process][NomMcType],
					      m_Afac[m_process][x.first],
					      "A_"+NomMcType+"_"+x.first );
      
      m_Crat[m_process][x.first] = MakeRatio( m_Cfac[m_process][NomMcType],
					      m_Cfac[m_process][x.first],
					      "C_"+NomMcType+"_"+x.first );
      m_Rrat[m_process][x.first] = MakeRatio( m_Rfac[m_process][NomMcType],
					      m_Rfac[m_process][x.first],
					      "R_"+NomMcType+"_"+x.first );
      
    }
  }

#ifdef DEBUG
  for( auto& x: m_Afac){
    PRINT_VERBOSE( "                                          process = "+
		   x.first+" map-size A = "+std::to_string(m_Afac[x.first].size()) );
    PRINT_VERBOSE( "                                          process = "+
		   x.first+" map-size C = "+std::to_string(m_Cfac[x.first].size()) );
    PRINT_VERBOSE( "                                          process = "+
		   x.first+" map-size R = "+std::to_string(m_Rfac[x.first].size()) );
    
    if(m_doRelComp){
      PRINT_VERBOSE( "                                          process = "+
		     x.first+" map-size A ratio = "+std::to_string(m_Arat[x.first].size()) );
      PRINT_VERBOSE( "                                          process = "+
		     x.first+" map-size C ratio = "+std::to_string(m_Crat[x.first].size()) );
      PRINT_VERBOSE( "                                          process = "+
		     x.first+" map-size R ratio = "+std::to_string(m_Rrat[x.first].size()) );
    }
  }
#endif
  
}

TH1D* GetFiducialPlot(std::string prefix, std::string prodMode, std::string mc){

  PRINT_DEBUG("<DrawFactors::GetFiducialPlot()>:: retrieving histograms for fiducial case ");

  TH1D *fid = new TH1D( (prefix+"fid_"+prodMode+"_"+mc).c_str(),
			(prefix+"fid_"+prodMode+"_"+mc).c_str(), 4,0,4);
  std::string Prefix = prefix+"fid_";
  fid->SetBinContent( 1,((TH1D*)m_fMap[mc]->Get( (Prefix+"4mu_"+prodMode).c_str()   ))->GetBinContent(1) );
  fid->SetBinError(   1,((TH1D*)m_fMap[mc]->Get( (Prefix+"4mu_"+prodMode).c_str()   ))->GetBinError(1)   );
  fid->SetBinContent( 2,((TH1D*)m_fMap[mc]->Get( (Prefix+"4e_"+prodMode).c_str()    ))->GetBinContent(1) );
  fid->SetBinError(   2,((TH1D*)m_fMap[mc]->Get( (Prefix+"4e_"+prodMode).c_str()    ))->GetBinError(1)   );
  fid->SetBinContent( 3,((TH1D*)m_fMap[mc]->Get( (Prefix+"2mu2e_"+prodMode).c_str() ))->GetBinContent(1) );
  fid->SetBinError(   3,((TH1D*)m_fMap[mc]->Get( (Prefix+"2mu2e_"+prodMode).c_str() ))->GetBinError(1)   );
  fid->SetBinContent( 4,((TH1D*)m_fMap[mc]->Get( (Prefix+"2e2mu_"+prodMode).c_str() ))->GetBinContent(1) );
  fid->SetBinError(   4,((TH1D*)m_fMap[mc]->Get( (Prefix+"2e2mu_"+prodMode).c_str() ))->GetBinError(1)   );
  if(prefix.find("aF")!=std::string::npos)
    fid->GetYaxis()->SetTitle("Acceptance");
  else if(prefix.find("cF")!=std::string::npos)
    fid->GetYaxis()->SetTitle("Correction factor");
  else if(prefix.find("rF")!=std::string::npos)
    fid->GetYaxis()->SetTitle("R factor");
  
  return fid;
  
}

void DefineStyle(){

  PRINT_DEBUG("<DrawFactors::DefineStyle()>:: defining global histograms style ");

  if(m_mrgProd){
    m_ProcColor[GetProcessName(Process::ggHbbH)] = m_ggFCol;
    m_ProcColor[GetProcessName(Process::VBF)]    = m_VBFCol;
    m_ProcColor[GetProcessName(Process::VH)]     = m_VHCol;
    m_ProcColor[GetProcessName(Process::ttH)]    = m_ttHCol;
    
    m_ProcMarker[GetProcessName(Process::ggHbbH)] = m_ggFMrk;
    m_ProcMarker[GetProcessName(Process::VBF)]    = m_VBFMrk;
    m_ProcMarker[GetProcessName(Process::VH)]     = m_VHMrk;
    m_ProcMarker[GetProcessName(Process::ttH)]    = m_ZHMrk;

    m_ProcMrkSz[GetProcessName(Process::ggHbbH)] = 1.4;
    m_ProcMrkSz[GetProcessName(Process::VBF)]    = 1.4;
    m_ProcMrkSz[GetProcessName(Process::VH)]     = 2.1;
    m_ProcMrkSz[GetProcessName(Process::ttH)]    = 1.4;
  }
  else{
    m_ProcColor[GetProcessName(Process::ggH)] = m_ggFCol;
    m_ProcColor[GetProcessName(Process::VBF)] = m_VBFCol;
    m_ProcColor[GetProcessName(Process::WH)]  = m_WHCol;
    m_ProcColor[GetProcessName(Process::ZH)]  = m_ZHCol;
    m_ProcColor[GetProcessName(Process::ttH)] = m_ttHCol;
    m_ProcColor[GetProcessName(Process::bbH)] = m_bbHCol;

    m_ProcMarker[GetProcessName(Process::ggH)] = m_ggFMrk;
    m_ProcMarker[GetProcessName(Process::VBF)] = m_VBFMrk;
    m_ProcMarker[GetProcessName(Process::WH)]  = m_WHMrk;
    m_ProcMarker[GetProcessName(Process::ZH)]  = m_ZHMrk;
    m_ProcMarker[GetProcessName(Process::ttH)] = m_ttHMrk;
    m_ProcMarker[GetProcessName(Process::bbH)] = m_bbHMrk;

    m_ProcMrkSz[GetProcessName(Process::ggH)] = 1.4;
    m_ProcMrkSz[GetProcessName(Process::VBF)] = 1.4;
    m_ProcMrkSz[GetProcessName(Process::WH)]  = 2.1;
    m_ProcMrkSz[GetProcessName(Process::ZH)]  = 2.1;
    m_ProcMrkSz[GetProcessName(Process::ttH)] = 1.8;
    m_ProcMrkSz[GetProcessName(Process::bbH)] = 1.8;
  }

  m_mcRelColor[GetMCreleaseName(MCtype::All)]   = m_ggFCol;
  m_mcRelColor[GetMCreleaseName(MCtype::mc15c)] = m_VBFCol;
  m_mcRelColor[GetMCreleaseName(MCtype::mc16a)] = m_VHCol;
  m_mcRelColor[GetMCreleaseName(MCtype::mc16d)] = m_ttHCol;
  
  m_mcRelMarker[GetMCreleaseName(MCtype::All)]   = m_ggFMrk;
  m_mcRelMarker[GetMCreleaseName(MCtype::mc15c)] = m_VBFMrk;
  m_mcRelMarker[GetMCreleaseName(MCtype::mc16a)] = m_WHMrk;
  m_mcRelMarker[GetMCreleaseName(MCtype::mc16d)] = m_ZHMrk;
  
  m_mcRelMrkSz[GetMCreleaseName(MCtype::All)]   = 1.4;
  m_mcRelMrkSz[GetMCreleaseName(MCtype::mc15c)] = 1.4;
  m_mcRelMrkSz[GetMCreleaseName(MCtype::mc16a)] = 2.1;
  m_mcRelMrkSz[GetMCreleaseName(MCtype::mc16d)] = 1.8;

  if(m_allSig){
    m_ProcColor[GetProcessName(Process::Signal)]  = m_bbHCol;
    m_ProcMarker[GetProcessName(Process::Signal)] = m_bbHMrk;
    m_ProcMrkSz[GetProcessName(Process::Signal)]  = 1.8;
  }
  
}

void DefineInputFiles(){

  if(m_doRelComp){
    m_fMap[GetMCreleaseName(MCtype::All)] = new TFile( (m_filePrefix+"_mc16.root").c_str() );
    for(auto &x: m_mcRelColor){
      if(x.first==GetMCreleaseName(MCtype::All)) continue;
      m_fMap[x.first] = new TFile( (m_filePrefix+"_"+x.first+".root").c_str() );
    }
  }
  else
    m_fMap[GetMCreleaseName(m_mcVersion)] = new TFile( (m_filePrefix+"_"+GetMCreleaseName(m_mcVersion)+".root").c_str() );
  
}

void DrawPlots(std::map<std::string,std::map<std::string,TH1D*> > histos,
	       std::map<std::string,std::map<std::string,TH1D*> > ratios,
	       int type, TLegend *leg, int chanId, int varId){

  PRINT_DEBUG("<DrawFactors::DrawPlots()>:: drawing plots ... ");

  Double_t Ymax = 1.1;
  if(type==factor::aF) Ymax = 1.2;
  if(type==factor::rF) Ymax = 0.5;

  std::string ggHbbH = GetProcessName(Process::ggHbbH);
  std::string VBF    = GetProcessName(Process::VBF);
  std::string AllSig = GetProcessName(Process::Signal);
  std::string ttH    = GetProcessName(Process::ttH);
  if(m_doRelComp)
    hline = MakeHorLine( histos[m_process]["mc16"]->GetXaxis()->GetXmin(),
			 histos[m_process]["mc16"]->GetXaxis()->GetXmax() );
  for(auto& x: histos){
    
    for(auto& y: m_fMap){
      
      PRINT_VERBOSE("                                 drawing "+x.first+
		    " histogram and mc release "+y.first);
      if(m_doRelComp){
	histos[x.first][y.first]->SetLineColor(m_mcRelColor[y.first]);
	histos[x.first][y.first]->SetMarkerColor(m_mcRelColor[y.first]);
	histos[x.first][y.first]->SetMarkerStyle(m_mcRelMarker[y.first]);
	histos[x.first][y.first]->SetMarkerSize(m_mcRelMrkSz[y.first]);
	
	ratios[x.first][y.first]->SetLineColor(m_mcRelColor[y.first]);
	ratios[x.first][y.first]->SetMarkerColor(m_mcRelColor[y.first]);
	ratios[x.first][y.first]->SetMarkerStyle(m_mcRelMarker[y.first]);
	ratios[x.first][y.first]->SetMarkerSize(m_mcRelMrkSz[y.first]);
	ratios[x.first][y.first]->GetYaxis()->SetRangeUser(0.65,1.35);
	ratios[x.first][y.first]->GetYaxis()->SetTitle("mc16x/mc16");
	AdjustRemappedXaxis(ratios[x.first][y.first],varId,m_doRelComp,true);
      }
      else{
	histos[x.first][y.first]->SetLineColor(m_ProcColor[x.first]);
	histos[x.first][y.first]->SetMarkerColor(m_ProcColor[x.first]);
	histos[x.first][y.first]->SetMarkerStyle(m_ProcMarker[x.first]);
	histos[x.first][y.first]->SetMarkerSize(m_ProcMrkSz[x.first]);
      }
      histos[x.first][y.first]->GetYaxis()->SetRangeUser(0,Ymax);
      AdjustRemappedXaxis(histos[x.first][y.first],varId,m_doRelComp);
      if( x.first==ggHbbH ){
	if(m_doRelComp)
	  leg->AddEntry(histos[x.first][y.first],y.first.c_str(),"p");
	else
	  leg->AddEntry(histos[x.first][y.first],"ggH + bbH","p");
      }
      else if( x.first==AllSig ){
	if(m_doRelComp)
	  leg->AddEntry(histos[x.first][y.first],y.first.c_str(),"p");
	else
	  leg->AddEntry(histos[x.first][y.first],"All Prod. Modes","p");
      }
      else if( x.first==ttH ){
	if(m_doRelComp)
	  leg->AddEntry(histos[x.first][y.first],y.first.c_str(),"p");
	else
	  leg->AddEntry(histos[x.first][y.first],"ttH + tH","p");
      }
      else{
	if(m_doRelComp){
	  if(m_process=="ttH"){
	    if(y.first=="mc16a")
	      leg->AddEntry(histos[x.first][y.first],"mc16a (Powheg)","p");
	    else if(y.first=="mc16d")
	      leg->AddEntry(histos[x.first][y.first],"mc16d (Powheg)","p");
	    else if(y.first=="mc15c")
	      leg->AddEntry(histos[x.first][y.first],"mc15c (aMcAtNLO)","p");
	    else if(y.first=="mc16")
	      leg->AddEntry(histos[x.first][y.first],"mc16 (Powheg)","p");
	  }
	  else
	    leg->AddEntry(histos[x.first][y.first],y.first.c_str(),"p");
	}
	else
	  leg->AddEntry(histos[x.first][y.first],x.first.c_str(),"p");
      }
      if(m_doRelComp) p1->cd();
      else            c->cd();
      histos[x.first][y.first]->Draw("pEsame");
      if(m_doRelComp){
	p2->cd();
	if(y.first!="mc15c"){
	  ratios[x.first][y.first]->Draw("pEsame");
	  if(y.first=="mc16"){
	    hline->Draw("same");
	    ratios[x.first][y.first]->Draw("pEsame");
	  }
	}
      }
    }
  }
  if(m_doRelComp) p1->cd();
  else            c->cd();
  leg->Draw();
  DrawAtlasLabel(m_doRelComp,m_isConf,m_isPaper);
  DrawEnergyLumi(m_lumi,false,m_doRelComp);
  DrawChannel(chanId,m_doRelComp);
  if(m_doRelComp)
    DrawProductionMode(m_process,m_doRelComp);
  
}

void DrawfnonFidPlots(std::map<std::string,std::map<std::string,TH1D*> > histos,TLegend *leg, int chanId, int varId) {

  PRINT_DEBUG("<DrawFactors::DrawPlots()>:: drawing plots ... ");

  Double_t Ymax = 0.3;

  std::string ggHbbH = GetProcessName(Process::ggHbbH);
  std::string VBF    = GetProcessName(Process::VBF);
  std::string AllSig = GetProcessName(Process::Signal);
  std::string ttH    = GetProcessName(Process::ttH);

  for(auto& x: histos){
    
    for(auto& y: m_fMap){
      
      PRINT_VERBOSE("                                 drawing "+x.first+
		    " histogram and mc release "+y.first);
	histos[x.first][y.first]->SetLineColor(m_ProcColor[x.first]);
	histos[x.first][y.first]->SetMarkerColor(m_ProcColor[x.first]);
	histos[x.first][y.first]->SetMarkerStyle(m_ProcMarker[x.first]);
	histos[x.first][y.first]->SetMarkerSize(m_ProcMrkSz[x.first]);

    histos[x.first][y.first]->GetYaxis()->SetRangeUser(0,Ymax);
    AdjustRemappedXaxis(histos[x.first][y.first],varId,m_doRelComp);

	if( x.first==ggHbbH )		leg->AddEntry(histos[x.first][y.first],"ggH + bbH","p");
    else if( x.first==AllSig ) 	leg->AddEntry(histos[x.first][y.first],"All Prod. Modes","p");
    else if( x.first==ttH ) 	leg->AddEntry(histos[x.first][y.first],"ttH + tH","p");
    else						leg->AddEntry(histos[x.first][y.first],x.first.c_str(),"p");
	  
	c->cd();
    histos[x.first][y.first]->Draw("pEsame");
  
  	}
  }
  
  c->cd();
  leg->Draw();
  DrawAtlasLabel(m_doRelComp,m_isConf,m_isPaper);
  DrawEnergyLumi(m_lumi,false,m_doRelComp);
  DrawChannel(chanId,m_doRelComp);
  
}
