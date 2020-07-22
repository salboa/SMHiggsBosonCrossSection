#include "WorkSpaceMaker.h"

RooStats::HistFactory::FlexibleInterpVar* WorkSpaceMaker::makeSysBlock(string blockID,
								       int ChNum,
								       int proc,
								       int cat,
								       bool is_aF){
    
  PRINT_DEBUG_FUNCTION(" <makeSysBlock()>:: creating systematic block for cat = "
		       +to_string(cat)+" and proc = "+to_string(proc));
  
  vector< double > syslow;
  vector< double > sysup;
  vector<int> interp;

  map<short int,string> SYSMap;
  if(proc>=Process::Signal && proc<=Process::VH) SYSMap = MakeSysMap(false,Syst::SignalSystematics);
  else if(proc==Process::qqZZ)                   SYSMap = MakeSysMap(false,Syst::qqZZSystematics);
  else if(proc==Process::ggZZ)                   SYSMap = MakeSysMap(false,Syst::ggZZSystematics);
  else if(proc==Process::redBkg)                 SYSMap = MakeSysMap(false,Syst::ZjetsSystematics);

  bool isfNonFid = false;
  if(proc>=Process::Signal && proc<=Process::VH && m_matrix) isfNonFid = true;
  bool isZZ = false;
  std::vector<int> ZZcatbins = getZZCatBins(cat);
  if(proc>=Process::Signal && proc<=Process::VH && m_matrix) isfNonFid = true;
  if(proc==Process::qqZZ || proc==Process::ggZZ) {
		isZZ = true;
		if (!(ZZcatbins.size()>0)) PRINT_FATAL("ZZ systematic with no ZZ bin defined!");
	}	
  
  RooRealVar *tmp_sys = NULL;
  RooArgList v_sys;
  TH1D *hsysup   = NULL;
  TH1D *hsysdown = NULL;
  TH1D *hnom     = NULL;
  TH1D *rsysup   = NULL;
  TH1D *rsysdown = NULL;
  TH1D *rnom     = NULL;
  TH1D *asysup   = NULL;
  TH1D *asysdown = NULL;
  TH1D *anom     = NULL;
  TFile *nomF    = NULL;
  TFile *sysF    = NULL;
  string tmpName = "";
  string hNpfx   = "";
  string hName   = "";
  string rName   = "";
  string aName   = "";
  
  string procName = GetProcessName(proc);
  string chName   = GetChannelName(ChNum);
  string ctg      = m_Category.at(cat);
  if(proc==Process::redBkg) procName = "Zjets";
  string hType = "cF";
  if(is_aF) hType = "aF";

  if(m_chSplit!=0){
    int nChars = 3;
    if(m_chSplit==1) nChars = 4;
    ctg = ctg.substr(0, ctg.size()-nChars)+chName;
  }
  
  string sysBlockName;
  if (m_Fiducial) sysBlockName = blockID+"_proc_"+procName+"_"+chName;
  else 		  sysBlockName = blockID+"_proc_"+procName+"_"+ctg;
 
  if (m_Fiducial) rName = "rF_fid_"+chName+"_"+procName;
  else		  rName = "rF_"+m_Variable+"_"+chName+"_"+procName;

  aName = GetUnfoldParamHistoName("aF",ChNum,proc);

  PRINT_DEBUG(" <makeSysBlock()>:: sysBlockName will be: "+sysBlockName);
  
  for( auto& x: SYSMap ){

    hNpfx = "";
    if ( x.first %2 ==0 ) continue;

    tmpName = GetSysNpName(x.first,x.second);
    if( v_sys.find((tmpName).c_str()) ) PRINT_WARNING(" NP: "+tmpName+" already found in the list.. skipping!" );
    if( v_sys.find((tmpName).c_str()) ) continue;

    PRINT_DEBUG("Processing sys variation = "+tmpName);
    tmp_sys = new RooRealVar(("ATLAS_"+tmpName).c_str(), ("ATLAS_"+tmpName).c_str(), 0, -5, 5);// tmp_sys->setConstant(1);
    
    /* experimental, qqZZ (CKKW and QSF) and Z+jets and systematics */
    if( x.first<=Syst::MUON_SCALE ||
	(x.first>=Syst::VAR_TH_qqZZ_Sherpa_CKKW && x.first<=Syst::VAR_TH_qqZZ_Sherpa_QSF) ||
	(x.first>=Syst::ZJET_stat_2l2e && x.first<=Syst::ZJET_syst_2l2mu)          ){

      if(isfNonFid){
	hName = GetUnfoldParamHistoName("fNonFid_Rel",ChNum,proc);
	nomF  = m_AcInFile;
	sysF  = m_AcSysFile;
      }
      else{
	hName = "h"+m_Variable+"_"+chName+"_"+procName;
	nomF  = m_InFile;
	sysF  = m_SysFile;
      }
      PRINT_DEBUG( hName.c_str() );
      hnom = (TH1D*)nomF->Get( hName.c_str() );
      
      if(hnom==NULL){ PRINT_FATAL(" Histogram: Nominal "+hName+" not found, exit!"); exit(0); }
      
      PRINT_DEBUG( (tmpName+"__1up/h"+hName).c_str() );
      hsysup = (TH1D*)sysF->Get( (tmpName+"__1up/"+hName).c_str() );
      if(hsysup==NULL){ PRINT_WARNING(" Histogram: "+tmpName+"__1up/"+hName+" not found, exit!"); continue; } //TO BE FIXED/REMOVED
      if(hsysup==NULL){ PRINT_FATAL(" Histogram: "+tmpName+"__1up/"+hName+" not found, exit!"); exit(0); }

      PRINT_DEBUG( (tmpName+"__1down/"+hName).c_str() );
      hsysdown = (TH1D*)sysF->Get( (tmpName+"__1down/"+hName).c_str() );
      if(hsysdown==NULL){ PRINT_WARNING(" Histogram: "+ tmpName+"__1down/"+hName+" not found, exit!"); continue; } //TO BE FIXED/REMOVED
      if(hsysdown==NULL){ PRINT_FATAL(" Histogram: "+ tmpName+"__1down/"+hName+" not found, exit!"); exit(0); }

      if (x.first >= Syst::JET_JER_DataVsMC && x.first < Syst::JET_Pileup_OffsetMu) {
	hsysdown = (TH1D*)hnom->Clone( (tmpName+"__1down/"+hName).c_str() ); 
     	hsysdown->Scale(2.0);
     	hsysdown->Add(hsysup, -1);
      }


      if(m_Fiducial){

	if(isfNonFid){
	  sysup.push_back(  hsysup->GetBinContent(1)   / hnom->GetBinContent(1) );
	  syslow.push_back( hsysdown->GetBinContent(1) / hnom->GetBinContent(1) );
	}
	else{
	  sysup.push_back(  hsysup->Integral()   / hnom->Integral() );
	  syslow.push_back( hsysdown->Integral() / hnom->Integral() );
	}
	
      }
      else{
		if( hnom->GetBinContent(cat+1)==0 ){ //assign 100% uncertainty
			syslow.push_back( 2 );
			sysup.push_back(  2 );
		}
		else{
			if( hsysup->GetBinContent(cat+1)==0 || hsysdown->GetBinContent(cat+1)==0 || hnom->GetBinContent(cat+1)==0 ){
				PRINT_FATAL(" Sys "+tmpName+" nominal, variation Up or Down = 0,!"); //TO BE FIXED
				continue;
				exit(0);
			}
			else{
				if (m_floatqqZZ && isZZ) {

					std::vector<int> ZZcat = m_ZZbins[cat];
					double num_up=0, num_down=0;
					double denom=0;
					for (std::vector<int>::iterator it = ZZcat.begin() ; it != ZZcat.end(); ++it) {
						num_up		= num_up + hsysup->GetBinContent(*it+1);
						num_down	= num_down + hsysdown->GetBinContent(*it+1);
						denom		= denom + hnom->GetBinContent(*it+1);
					} 
					sysup.push_back(1 + hsysup->GetBinContent(cat+1) / hnom->GetBinContent(cat+1) - num_up/denom);
					syslow.push_back(1 + hsysdown->GetBinContent(cat+1) / hnom->GetBinContent(cat+1) - num_down/denom);
				} else {
					sysup.push_back(  hsysup->GetBinContent(cat+1)   / hnom->GetBinContent(cat+1) );
					syslow.push_back( hsysdown->GetBinContent(cat+1) / hnom->GetBinContent(cat+1) );
				}
			}
		}
	
	}
      
    }

    /* qqZZ (CSSKIN, QCD, PDF) systematics */
    else if(x.first>=Syst::VAR_TH_qqZZ_Sherpa_CSSKIN && x.first<=Syst::VAR_TH_qqZZ_PDF){

      hName = "h"+m_Variable+"_"+chName+"_"+procName;
      PRINT_DEBUG( (hNpfx+hName).c_str() );
      if(x.first==Syst::VAR_TH_qqZZ_Sherpa_CSSKIN){
	nomF = m_InFile;
      }
      else{
	nomF = m_SysFile; hNpfx = "Theory_qqZZ_MUR1_MUF1_PDF261000/";
      }
      
      hnom = (TH1D*)nomF->Get( (hNpfx+hName).c_str() );
      if(hnom==NULL){ PRINT_FATAL(" Histogram: Nominal "+hNpfx+hName+" not found, exit!"); exit(0); }

      std::pair<double,double> var;
      if(x.first==Syst::VAR_TH_qqZZ_QCD) var = PerformEnvelope(hnom,hnom,ChNum,proc,hName,x.first,cat,isZZ,false);
      else                               var = PerformWeightedSum(hnom,hName,x.first,cat,isZZ);
      sysup.push_back( var.first );
      syslow.push_back( var.second );
      
    }

    /* Var3c and hard Shower Systematics */
    else if(x.first>=Syst::VAR_TH_Var3c && x.first<=Syst::VAR_TH_hard){

      if(isfNonFid){ hName = GetUnfoldParamHistoName("fNonFid_Rel",ChNum,proc); }
      else         { hName = GetUnfoldParamHistoName(hType,ChNum,proc);         }
      nomF  = m_AcInFile;
      sysF  = m_AcSysFile;

      PRINT_DEBUG( (hNpfx+hName).c_str() );
      hnom = (TH1D*)nomF->Get( (hNpfx+hName).c_str() );
      rnom = (TH1D*)nomF->Get( (hNpfx+rName).c_str() );

      if(hnom==NULL){ PRINT_FATAL(" Histogram: Nominal "+hNpfx+hName+" not found, exit!"); exit(0); }

      PRINT_DEBUG( (tmpName+"__1up/"+hName).c_str() );
      hsysup = (TH1D*)sysF->Get( (tmpName+"__1up/"+hName).c_str() );
      rsysup = (TH1D*)sysF->Get( (tmpName+"__1up/"+rName).c_str() );
      asysup = (TH1D*)sysF->Get( (tmpName+"__1up/"+aName).c_str() );
      if(hsysup==NULL){ PRINT_WARNING(" Histogram: "+tmpName+"__1up/"+hName+" not found, exit!"); continue; } // TO BE FIXED/REMOVED
      if(hsysup==NULL){ PRINT_FATAL(" Histogram: "+tmpName+"__1up/"+hName+" not found, exit!"); exit(0); }
	
      PRINT_DEBUG( (tmpName+"__1down/"+hName).c_str() );
      hsysdown = (TH1D*)sysF->Get( (tmpName+"__1down/"+hName).c_str() );
      rsysdown = (TH1D*)sysF->Get( (tmpName+"__1down/"+rName).c_str() );
      asysdown = (TH1D*)sysF->Get( (tmpName+"__1down/"+aName).c_str() );
      if(hsysdown==NULL){ PRINT_WARNING(" Histogram: "+tmpName+"__1down/"+hName+" not found, exit!"); continue; } // TO BE FIXED/REMOVED
      if(hsysdown==NULL){ PRINT_FATAL(" Histogram: "+tmpName+"__1down/"+hName+" not found, exit!"); exit(0); }
      
      if (m_addAsys && !isfNonFid){
      
        double rvarup = 0 ;
        double rvardown = 0 ;
        double avarup = 0 ;
        double avardown = 0 ;
     
        if (rnom->GetBinContent(cat+1) == 0 || anom->GetBinContent(cat+1) == 0) { sysup.push_back( 1 );  syslow.push_back( 1 ); }
        else {
      		//rvarup   = rsysup->GetBinContent(cat+1)/rnom->GetBinContent(cat+1);
      		//rvardown = rsysdown->GetBinContent(cat+1)/rnom->GetBinContent(cat+1);
      		avarup   = asysup->GetBinContent(cat+1)/anom->GetBinContent(cat+1);
      		avardown = asysdown->GetBinContent(cat+1)/anom->GetBinContent(cat+1);
      		double diffup = avarup - (hsysup->GetBinContent(1) / hnom->GetBinContent(1));
      		double diffdown = avardown - (hsysdown->GetBinContent(1) / hnom->GetBinContent(1));
        	sysup.push_back( 1+diffup );  
        	syslow.push_back( 1-diffdown );
        }
      }
      else if(m_Fiducial){
	
        if ( hsysup->GetBinContent(1)==0 || hsysdown->GetBinContent(1)==0){
          PRINT_FATAL(" Sys "+tmpName+" variation Up or Down = 0, exit!");
          exit(0);
        }
        sysup.push_back(  hsysup->GetBinContent(1)   / hnom->GetBinContent(1) );
	syslow.push_back( hsysdown->GetBinContent(1) / hnom->GetBinContent(1) );
      }
      else{
	
        if ( hsysup->GetBinContent(cat+1)==0 || hsysdown->GetBinContent(cat+1)==0){
          PRINT_FATAL(" Sys "+tmpName+" variation Up or Down = 0, exit!");
          exit(0);
        }
	sysup.push_back(  hsysup->GetBinContent(cat+1)  / hnom->GetBinContent(cat+1) );
        syslow.push_back( hsysdown->GetBinContent(cat+1) / hnom->GetBinContent(cat+1) );
	
      }
            
    }
    
    /* QCD scale and Scale Shower systematics */
    else if(x.first==Syst::VAR_TH_QCD_Scale_VBF || x.first==Syst::VAR_TH_QCD_Scale_VH ||
	    x.first==Syst::VAR_TH_QCD_Scale_ttH || x.first==Syst::VAR_TH_Shower_ISRFSR){
      
      if(isfNonFid) hName = GetUnfoldParamHistoName("fNonFid_Rel",ChNum,proc);
      else          hName = GetUnfoldParamHistoName(hType,ChNum,proc);

      if(x.first==Syst::VAR_TH_Shower_ISRFSR){
	nomF = m_AcInFile;
      }
      else{
	nomF = m_AcSysFile;
	if(x.first==Syst::VAR_TH_QCD_Scale_VBF) hNpfx = "Theory_QCD_Scale_Nominal_VBF/";
	if(x.first==Syst::VAR_TH_QCD_Scale_VH)  hNpfx = "Theory_QCD_Scale_Nominal_VH/" ;
	if(x.first==Syst::VAR_TH_QCD_Scale_ttH) hNpfx = "Theory_QCD_Scale_Nominal_ttH/";
      }
            
      PRINT_DEBUG( (hNpfx+hName).c_str() );
      hnom = (TH1D*)nomF->Get( (hNpfx+hName).c_str() );

      if(hnom==NULL){ PRINT_FATAL(" Histogram: Nominal "+hNpfx+hName+" not found, exit!"); exit(0); }
          
      std::pair<double,double> var;
      if(isfNonFid) var = PerformEnvelope(hnom,hnom,ChNum,proc,"fNonFid_Rel",x.first,cat,isZZ,false);
      else          var = PerformEnvelope(hnom,hnom,ChNum,proc,hType,x.first,cat,isZZ,false);

      if (!isfNonFid && m_addAsys && !isZZ) {
	rnom = (TH1D*)nomF->Get( (hNpfx+rName).c_str() );
	anom = (TH1D*)nomF->Get( (hNpfx+aName).c_str() );
	std::pair<double,double> arvar = PerformEnvelope(anom,anom,ChNum,proc,"aF",x.first,cat,isZZ,false);

	double up =  1+(arvar.first-var.first);
        double low = 1+(arvar.second-var.second);
	// symmterize this
	if(x.first==Syst::VAR_TH_Shower_ISRFSR)
	{ 
		if(fabs(1-up) > fabs(1-low)) low = 2 - up;
		else up = 2 - low;
	}

	//std::cout << "up: "  << up << std::endl;
	//std::cout << "dwn: " << low << std::endl;
	sysup.push_back( up );
        syslow.push_back( low );

      }
      else {
        sysup.push_back( var.first );
        syslow.push_back( var.second );
      }

    }

    /* QCD, Herwig Shower, and PDF systematics */
    else if( (x.first>=Syst::VAR_TH_ggF_qcd_2017_pTH120 &&
	      x.first<=Syst::VAR_TH_qcd_wg1_vbf3j)          ||
	     (x.first>=Syst::VAR_TH_Shower_Herwig_ggHbbH &&
	      x.first<=Syst::VAR_TH_Shower_Herwig_ttHtH)    ||
	     (x.first>=Syst::VAR_TH_pdf_90400 &&
	      x.first<=Syst::VAR_TH_pdf_90432)		    ||
	      x.first==Syst::VAR_TH_ggF_QCD_pTH_nJ0         ){

      if (x.first == Syst::VAR_TH_pdf_90432) continue;
      if (x.first == Syst::VAR_TH_pdf_90400) continue;

      if(isfNonFid) hName = GetUnfoldParamHistoName("fNonFid_Rel",ChNum,proc);
      else          hName = GetUnfoldParamHistoName(hType,ChNum,proc);

      if(x.first>=Syst::VAR_TH_pdf_90400 && x.first<=Syst::VAR_TH_pdf_90432){
	nomF =  m_AcSysFile; hNpfx = "Theory_PDF_Nominal/";
      }
      else if(x.first>=Syst::VAR_TH_Shower_Herwig_ggHbbH &&
	      x.first<=Syst::VAR_TH_Shower_Herwig_ttHtH){
	nomF =  m_AcSysFile; hNpfx = "Theory_Shower_Herwig_Nominal/";
      }
	      
      else{ nomF = m_AcInFile; }
      sysF = m_AcSysFile;
      
      PRINT_DEBUG( (hNpfx+hName).c_str() );
      hnom = (TH1D*)nomF->Get( (hNpfx+hName).c_str() );
      if (m_addSys) {
	      rnom = (TH1D*)nomF->Get( (hNpfx+rName).c_str() );
		//std::cout << (hNpfx+aName).c_str() <<std::endl;
	      anom = (TH1D*)nomF->Get( (hNpfx+aName).c_str() );
      }

      if(hnom==NULL){ PRINT_FATAL(" Histogram: Nominal "+hNpfx+hName+" not found, exit!"); exit(0); }

      PRINT_DEBUG( (tmpName+"/"+hName).c_str() );
      hsysup = (TH1D*)m_AcSysFile->Get( (tmpName+"/"+hName).c_str() );
      if (m_addSys) {
	      rsysup = (TH1D*)m_AcSysFile->Get( (tmpName+"/"+rName).c_str() );
	      //std::cout << (tmpName+"/"+aName).c_str() << std::endl;
	      asysup = (TH1D*)m_AcSysFile->Get( (tmpName+"/"+aName).c_str() );
      }
      if(hsysup==NULL){ PRINT_WARNING(" Histogram: "+tmpName+"/"+hName+" not found, exit!"); continue; } //TO BE FIXED/REMOVED
      if(hsysup==NULL){ PRINT_FATAL(" Histogram: "+ tmpName+"/"+hName+" not found, exit!"); exit(0); } //cF
      
      double var = 0 ;

      if(m_Fiducial){
  	  
  	  if( hsysup->GetBinContent(1)==0 ){
  	    PRINT_FATAL(" Sys "+tmpName+" variation = 0, exit!");
  	    exit(0);
  	  }
  	  var = hsysup->GetBinContent(1)/hnom->GetBinContent(1);
  	}
  	else{
  	  
  	  if ( hsysup->GetBinContent(cat+1)==0 ){
  	    PRINT_FATAL(" Sys "+tmpName+" variation = 0, exit!");
  	    exit(0);
  	  }
  	  var = hsysup->GetBinContent(cat+1)/hnom->GetBinContent(cat+1) ;
  	  
  	}

      if (m_addAsys && !isfNonFid){
      
	double rvar = 0 ;
	double avar = 0 ;
     
	if (rnom->GetBinContent(cat+1) == 0 || anom->GetBinContent(cat+1) == 0) { sysup.push_back( 1 );  syslow.push_back( 1 ); }
	else {
		//std::cout << "QCD, Herwig Shower, and PDF systematics" << std::endl;
      		rvar = rsysup->GetBinContent(cat+1)/rnom->GetBinContent(cat+1);
      		avar = asysup->GetBinContent(cat+1)/anom->GetBinContent(cat+1);
      		//double diff = avar*rvar-var;
      		double diff = avar-var;
		//std::cout << "diff: " << diff << std::endl;
		//std::cout << "up: " << 1+diff << ", down: " << 1-diff << std::endl;
    		sysup.push_back( 1+diff );  syslow.push_back( 1-diff );
      	}
      }
      else {
	if(var>1){ sysup.push_back( var );  syslow.push_back( 1-(var-1) ); }
	else     { sysup.push_back( var );  syslow.push_back( 1+(1-var) ); }
      }

    }
    /* Signal Composition systematics */
    else if(x.first>=Syst::SignalComposition_ggHbbH && x.first<=Syst::SignalComposition_ttHtH){

      if (m_addAsys && !isfNonFid) {
      	rnom = (TH1D*)m_AcInFile->Get( (hNpfx+rName).c_str() );
	rsysup = (TH1D*)m_AcSysFile->Get( (tmpName+"__1up/"+rName).c_str() );
	rsysdown = (TH1D*)m_AcSysFile->Get( (tmpName+"__1down/"+rName).c_str() );
      	anom = (TH1D*)m_AcInFile->Get( (hNpfx+aName).c_str() );
	asysup = (TH1D*)m_AcSysFile->Get( (tmpName+"__1up/"+aName).c_str() );
	asysdown = (TH1D*)m_AcSysFile->Get( (tmpName+"__1down/"+aName).c_str() );
      }

      if(isfNonFid){
	hName = GetUnfoldParamHistoName("fNonFid_Rel",ChNum,proc);
	nomF = m_AcInFile;
	sysF = m_AcSysFile;

	PRINT_DEBUG( hName );
	hnom = (TH1D*)nomF->Get( hName.c_str() );
      }
      else{
	if(procName=="AllSig"){
	  hName = GetUnfoldParamHistoName(hType,ChNum,proc);
	  nomF = m_AcInFile;
	  sysF = m_AcSysFile;

	  PRINT_DEBUG( hName );
	  hnom = (TH1D*)nomF->Get( hName.c_str() );
	}
	else{
	  hName = "h"+m_Variable+"_incl_"+procName; //"AllSig"
	  sysF  = m_SysFile;
	  hNpfx = "_"+procName;
	}
      }
      
      PRINT_DEBUG( (tmpName+hNpfx+"__1up/"+hName).c_str() );
      hsysup = (TH1D*)sysF->Get( (tmpName+hNpfx+"__1up/"+hName).c_str() );
      if(hsysup==NULL){ PRINT_WARNING(" Histogram: "+tmpName+hNpfx+"__1up/"+hName+" not found, exit!"); continue; } //TO BE FIXED/REMOVED
      if(hsysup==NULL){ PRINT_FATAL(" Histogram: "+tmpName+hNpfx+"__1up/"+hName+" not found, exit!"); exit(0); }

      PRINT_DEBUG( (tmpName+hNpfx+"__1down/"+hName).c_str() );
      hsysdown = (TH1D*)sysF->Get( (tmpName+hNpfx+"__1down/"+hName).c_str() );
      if(hsysdown==NULL){ PRINT_FATAL(" Histogram: "+tmpName+hNpfx+"__1down/"+hName+" not found, exit!"); continue; } //TO BE FIXED/REMOVED
      if(hsysdown==NULL){ PRINT_FATAL(" Histogram: "+tmpName+hNpfx+"__1up/"+hName+" not found, exit!"); exit(0); }

      if ( hsysup->GetBinContent(cat+1)==0 || hsysdown->GetBinContent(cat+1)==0){
	PRINT_FATAL(" Sys "+tmpName+" variation Up or Down= 0, exit!");
	exit(0);
      }

      if(isfNonFid){
	sysup.push_back(  hsysup->GetBinContent(cat+1)   / hnom->GetBinContent(cat+1) );
	syslow.push_back( hsysdown->GetBinContent(cat+1) / hnom->GetBinContent(cat+1) );
      }
      else{
	if(procName=="AllSig"){
	  if (m_addAsys) {
		
		if (anom->GetBinContent(cat+1) == 0 || rnom->GetBinContent(cat+1) == 0) { sysup.push_back( 1 ); syslow.push_back( 1 ); }
		else {
			//double rvarup = rsysup->GetBinContent(cat+1)/rnom->GetBinContent(cat+1);
		        //double rvardown = rsysdown->GetBinContent(cat+1)/rnom->GetBinContent(cat+1);
			double rvarup = 1.0;
			double rvardown = 1.0;
			double avarup = asysup->GetBinContent(cat+1)/anom->GetBinContent(cat+1);
			double avardown = asysdown->GetBinContent(cat+1)/anom->GetBinContent(cat+1);
			//std::cout << "Signal Composition systematics" << std::endl;
			//std::cout << "rvaru: " << rvarup << std::endl;
			//std::cout << "rvard: " << rvardown << std::endl;
			//std::cout << "avaru: " << avarup << std::endl;
			//std::cout << "avard: " << avardown << std::endl;
			//std::cout << "up: " << 1 + (rvarup*avarup - hsysup->GetBinContent(cat+1)/hnom->GetBinContent(cat+1)) << ", down: " << 1 + (rvardown*avardown - hsysdown->GetBinContent(cat+1)/hnom->GetBinContent(cat+1)) << std::endl;
			sysup.push_back(  1 + (rvarup*avarup - hsysup->GetBinContent(cat+1)/hnom->GetBinContent(cat+1)) );
			syslow.push_back( 1 + (rvardown*avardown - hsysdown->GetBinContent(cat+1)/hnom->GetBinContent(cat+1)) );
		}
		  
	  }
	  else {
		sysup.push_back(  hsysup->GetBinContent(cat+1)   / hnom->GetBinContent(cat+1) );
	  	syslow.push_back( hsysdown->GetBinContent(cat+1) / hnom->GetBinContent(cat+1) );
	  }
	}
	else{
	  sysup.push_back(  hsysup->GetBinContent(cat+1)   );
	  syslow.push_back( hsysdown->GetBinContent(cat+1) );
	}
      }
      
    }

    interp.push_back(4); // 4 is the index of the interpolation for the i-th variable

    if(!m_skipPruning){ if ( Pruning(&syslow, &sysup, &interp) ) { continue;} }

    v_sys.add(*tmp_sys);

    PRINT_DEBUG( " Systematic = " + tmpName + "  DwVal = " + to_string(syslow.at(syslow.size()-1) )  +
		 +"  UpVal = " + to_string(sysup.at(sysup.size()-1) ) );
    makeGaussianConstraint(tmp_sys);
    if ( m_listNP.find((tmpName).c_str()) ) continue; // skip of the NPs is already into the main list


    m_listNP.add(*tmp_sys);
    if (x.first!=Syst::VAR_TH_QCD_Scale_VBF && x.first!=Syst::VAR_TH_QCD_Scale_VH  &&
	x.first!=Syst::VAR_TH_QCD_Scale_ttH && x.first!=Syst::VAR_TH_Shower_ISRFSR &&
	x.first!=Syst::VAR_TH_qqZZ_QCD      && x.first!=Syst::VAR_TH_qqZZ_PDF      &&
	x.first!=Syst::VAR_TH_qqZZ_Sherpa_CSSKIN )
      hsysup->Delete();

    if( x.first<Syst::MUON_SCALE ||
	(x.first>=Syst::VAR_TH_qqZZ_Sherpa_CKKW && x.first<=Syst::VAR_TH_qqZZ_Sherpa_QSF) ||
	(x.first>=Syst::ZJET_stat_2l2e && x.first<=Syst::ZJET_syst_2l2mu)                 ||
	(x.first>=Syst::VAR_TH_Var3c && x.first<=Syst::VAR_TH_hard)                        ){
      hsysdown->Delete();
    }
    
    if( (x.first!=Syst::VAR_TH_pdf_90400 && proc!=Process::ggH && proc!=Process::ggHbbH)   &&
	(x.first<=Syst::SignalComposition_ggHbbH && x.first>=Syst::SignalComposition_ttHtH) ){
      hnom->Delete();
    }
    if(isfNonFid &&
       (x.first>=Syst::SignalComposition_ggHbbH && x.first<=Syst::SignalComposition_ttHtH) )
      hnom->Delete();
    
  }
  
  
  //if(!m_skipPruning) Pruning(&syslow, &sysup, &interp, &v_sys);
  
  m_sysblock = new RooStats::HistFactory::FlexibleInterpVar( sysBlockName.c_str(), sysBlockName.c_str(),  
							     v_sys, 1, syslow, sysup, interp );
  PRINT_DEBUG_OBJECT(m_sysblock,1);
    
  return m_sysblock;
  
}


RooStats::HistFactory::FlexibleInterpVar* WorkSpaceMaker::makeSysBlockMtx(int ChNum,
									  int proc,
									  int cati,
									  int catj,  vector <RooRealVar *> v_sigma, vector <RooRealVar *> v_eff, vector <RooRealVar *> v_A, vector <RooRealVar *> v_r){
  
  PRINT_DEBUG_FUNCTION(" <makeSysBlockMtx()>:: creating systematic block for cat reco = "
		       +to_string(cati)+", truth = "+to_string(catj)+" and proc = "+to_string(proc));

  vector< double > syslow;
  vector< double > sysup;
  vector<int> interp;

  map<short int,string> SYSMap;
  if(proc>Process::VH)
    PRINT_FATAL(" <makeSysBlockMtx()>:: called makeSysBlockMtx for process "+
		GetProcessName(proc)+"! NOT VALID!! exit!");
  
  SYSMap = MakeSysMap(false,Syst::SignalSystematics);
  
  RooRealVar *tmp_sys = NULL;
  RooArgList v_sys;
  TH2D *hsysup   = NULL;
  TH2D *hsysdown = NULL;
  TH2D *hnom     = NULL;
  TH1D *rsysup   = NULL;
  TH1D *rsysdown = NULL;
  TH1D *rnom     = NULL;
  TH1D *asysup   = NULL;
  TH1D *asysdown = NULL;
  TH1D *anom     = NULL;
  TFile *nomF    = NULL;
  string tmpName = "";
  string hNpfx   = "";
  string hName   = "";
  string rName   = "";
  string aName   = "";

  string procName = GetProcessName(proc);
  string chName   = GetChannelName(ChNum);
  string ctg_i    = m_Category.at(cati);
  string ctg_j    = m_Category.at(catj);
  if(proc==Process::redBkg) procName = "Zjets";
  
  if(m_chSplit!=0){
    int nChars = 3;
    if(m_chSplit==1) nChars = 4;
    ctg_i = ctg_i.substr(0, ctg_i.size()-nChars)+chName;
    ctg_j = ctg_j.substr(0, ctg_j.size()-nChars)+chName;
  }
  
  string sysBlockName = ("sysblock_reco_"+ctg_i+"_truth_"+
			 ctg_j+"_proc_"+procName);
  if(m_Fiducial) sysBlockName = ("sysblock_reco_"+chName+"_truth_"+
				 chName+"_proc_"+procName);
  if(m_addAsys) {
	  if (m_FidTotal) { rName = ("rF_fid_"+chName+"_"+procName).c_str(); }
	  else 	    	  { rName = ("rF_"+m_Variable+"_"+chName+"_"+procName).c_str(); }
	  aName = GetUnfoldParamHistoName("aF",ChNum,proc);
  }

  PRINT_DEBUG( " <makeSysBlockMtx()>:: sysBlockName will be: "+sysBlockName);
  
  for( auto& x: SYSMap ){
    hNpfx = "";
    hName = GetUnfoldParamHistoName("Mtx",ChNum,proc);

    if ( x.first %2 ==0 ) continue;

    tmpName = GetSysNpName(x.first,x.second);
    if( v_sys.find((tmpName).c_str()) ) PRINT_WARNING(" NP: "+tmpName+" already found in the list.. skipping!" );
    if( v_sys.find((tmpName).c_str()) ) continue;

    PRINT_DEBUG( "Processing sys variation = "+tmpName);
    tmp_sys = new RooRealVar(("ATLAS_"+tmpName).c_str(), ("ATLAS_"+tmpName).c_str(), 0, -5, 5);
    
    /* Experimental, Var3c and hard Shower, and Signal Composition systematics */
    if( x.first<=Syst::MUON_SCALE ||
	(x.first>=Syst::VAR_TH_Var3c && x.first<=Syst::VAR_TH_hard) ||
	(x.first>=Syst::SignalComposition_ggHbbH && x.first<=Syst::SignalComposition_ttHtH) ){
      
      PRINT_DEBUG( (hNpfx+hName).c_str() );
      hnom = (TH2D*)m_AcInFile->Get( (hNpfx+hName).c_str() );
      
      if(hnom==NULL){ PRINT_FATAL(" Histogram: Nominal "+hNpfx+hName+" not found, exit!"); exit(0); }
      
      PRINT_DEBUG( (tmpName+"__1up/"+hName).c_str() );
      hsysup = (TH2D*)m_AcSysFile->Get( (tmpName+"__1up/"+hName).c_str() );

      if(hsysup==NULL){ PRINT_WARNING(" Histogram: "+tmpName+"__1up/"+hName+" not found, skip!"); continue; } /// TO BE FIXED/REMOVED
      if(hsysup==NULL){ PRINT_FATAL(" Histogram: "+tmpName+"__1up/"+hName+" not found, exit!"); exit(0); }
      
      PRINT_DEBUG( (tmpName+"__1down/"+hName).c_str() );
      hsysdown = (TH2D*)m_AcSysFile->Get( (tmpName+"__1down/"+hName).c_str() );
      if(hsysdown==NULL){ PRINT_FATAL(" Histogram: "+tmpName+"__1down/"+hName+" not found, exit!"); exit(0); }

      if (x.first >= Syst::JET_JER_DataVsMC && x.first < Syst::JET_Pileup_OffsetMu ) {
	hsysdown = (TH2D*)hnom->Clone( (tmpName+"__1down/"+hName).c_str() );
     	hsysdown->Scale(2.0);
     	hsysdown->Add(hsysup, -1);
        if (cati!=catj) continue; 
      }


      if ( hsysup->GetBinContent(cati+1,catj+1)==0   ||
	   hsysdown->GetBinContent(cati+1,catj+1)==0 ||
	   hnom->GetBinContent(cati+1,catj+1)==0      ){
	PRINT_WARNING(" Sys "+tmpName+"Nominal, variation Up or Down = 0, exit!");
	continue ;
	exit(0);
      }
      if (((x.first>=Syst::SignalComposition_ggHbbH && x.first<=Syst::SignalComposition_ttHtH) || (x.first>=Syst::VAR_TH_Var3c && x.first<=Syst::VAR_TH_hard)) && m_addAsys) {
      	rnom = (TH1D*)m_AcInFile->Get( (hNpfx+rName).c_str() );
      	anom = (TH1D*)m_AcInFile->Get( (hNpfx+aName).c_str() );
	rsysup = (TH1D*)m_AcSysFile->Get( (tmpName+"__1up/"+rName).c_str() );
	asysup = (TH1D*)m_AcSysFile->Get( (tmpName+"__1up/"+aName).c_str() );
	rsysdown = (TH1D*)m_AcSysFile->Get( (tmpName+"__1down/"+rName).c_str() );
	asysdown = (TH1D*)m_AcSysFile->Get( (tmpName+"__1down/"+aName).c_str() );

	if (anom->GetBinContent(catj+1) == 0 || rnom->GetBinContent(catj+1) == 0) {
		sysup.push_back(1);
		syslow.push_back(1);
	}
	else {
		//double rvarup = rsysup->GetBinContent(catj+1)/rnom->GetBinContent(catj+1);
		double avarup = asysup->GetBinContent(catj+1)/anom->GetBinContent(catj+1);
		//double rvardown = rsysdown->GetBinContent(catj+1)/rnom->GetBinContent(catj+1);
		double avardown = asysdown->GetBinContent(catj+1)/anom->GetBinContent(catj+1);
		double rvarup = 1.0;
		double rvardown = 1.0;
			//std::cout << "Signal Composition systematics" << std::endl;
			//std::cout << "rvaru: " << rvarup << std::endl;
			//std::cout << "rvard: " << rvardown << std::endl;
			//std::cout << "avaru: " << avarup << std::endl;
			//std::cout << "avard: " << avardown << std::endl;
			//std::cout << "up: " << (rvarup*avarup - hsysup->GetBinContent(catj+1)/hnom->GetBinContent(cati+1,catj+1)) << ", down: " << (rvardown*avardown - hsysdown->GetBinContent(catj+1)/hnom->GetBinContent(cati+1,catj+1)) << std::endl;
		sysup.push_back(  1+(avarup*rvarup - hsysup->GetBinContent(cati+1,catj+1)/hnom->GetBinContent(cati+1,catj+1)) );
		syslow.push_back( 1+(avardown*rvardown - hsysdown->GetBinContent(cati+1,catj+1)/hnom->GetBinContent(cati+1,catj+1)) );
	}
      }
      else {
	sysup.push_back(  hsysup->GetBinContent(cati+1,catj+1)   / hnom->GetBinContent(cati+1,catj+1) );
	syslow.push_back( hsysdown->GetBinContent(cati+1,catj+1) / hnom->GetBinContent(cati+1,catj+1) );
      }
    }

    /* QCD Scale and Scale Shower systematics */
    else if(x.first==Syst::VAR_TH_QCD_Scale_VBF || x.first==Syst::VAR_TH_QCD_Scale_VH ||
	    x.first==Syst::VAR_TH_QCD_Scale_ttH || x.first==Syst::VAR_TH_Shower_ISRFSR ){

      if(x.first==Syst::VAR_TH_QCD_Scale_VBF) hNpfx = "Theory_QCD_Scale_Nominal_VBF/";
      if(x.first==Syst::VAR_TH_QCD_Scale_VH)  hNpfx = "Theory_QCD_Scale_Nominal_VH/" ;
      if(x.first==Syst::VAR_TH_QCD_Scale_ttH) hNpfx = "Theory_QCD_Scale_Nominal_ttH/";
      
      if(x.first==Syst::VAR_TH_Shower_ISRFSR) nomF = m_AcInFile;
      else                                    nomF = m_AcSysFile;
      
      PRINT_DEBUG( (hNpfx+hName).c_str() );
      hnom = (TH2D*)nomF->Get( (hNpfx+hName).c_str() );

      if(hnom==NULL){ PRINT_FATAL(" Histogram: Nominal "+hNpfx+hName+" not found, exit!"); exit(0); }

      std::pair<double,double> var = PerformEnvelopeMtx(hnom,ChNum,proc,"Mtx",x.first,cati,catj);

      if (m_addAsys) {
	rnom = (TH1D*)nomF->Get( (hNpfx+rName).c_str() );
	anom = (TH1D*)nomF->Get( (hNpfx+aName).c_str() );
	//std::pair<double,double> arvar = PerformEnvelope(rnom,anom,ChNum,proc,"rF",x.first,catj,false,true);
	std::pair<double,double> arvar = PerformEnvelope(anom,anom,ChNum,proc,"aF",x.first,catj,false,false);
	double up =  1+(arvar.first-var.first);
        double low = 1+(arvar.second-var.second);
	// symmterize this
	if(x.first==Syst::VAR_TH_Shower_ISRFSR)
	{ 
		if(fabs(1-up) > fabs(1-low)) low = 2 - up;
		else up = 2 - low;
	}
	sysup.push_back( up );
        syslow.push_back( low );


      }
      else {
        sysup.push_back( var.first );
        syslow.push_back( var.second );
      }
      
    }

    /* QCD, Herwig Shower, and PDF systematics */
    else if( (x.first>=Syst::VAR_TH_ggF_qcd_2017_pTH120  && x.first<=Syst::VAR_TH_qcd_wg1_vbf3j)       ||
	     (x.first>=Syst::VAR_TH_pdf_90400            && x.first<=Syst::VAR_TH_pdf_90432)           ||
	     (x.first>=Syst::VAR_TH_Shower_Herwig_ggHbbH && x.first<=Syst::VAR_TH_Shower_Herwig_ttHtH) ||
	      x.first==Syst::VAR_TH_ggF_QCD_pTH_nJ0						       ){
      
      if (x.first == Syst::VAR_TH_pdf_90432) continue;
      if (x.first == Syst::VAR_TH_pdf_90400) continue;

      if( x.first>=Syst::VAR_TH_pdf_90400 && x.first<=Syst::VAR_TH_pdf_90432 ){
	nomF = m_AcSysFile; hNpfx = "Theory_PDF_Nominal/"; 
      }
      else if(x.first>=Syst::VAR_TH_Shower_Herwig_ggHbbH &&
	      x.first<=Syst::VAR_TH_Shower_Herwig_ttHtH){
	nomF =  m_AcSysFile; hNpfx = "Theory_Shower_Herwig_Nominal/";
      }
      else{ nomF = m_AcInFile; }
      
      PRINT_DEBUG( (hNpfx+hName).c_str() );
      hnom = (TH2D*)nomF->Get( (hNpfx+hName).c_str() );
      
      if(hnom==NULL){ PRINT_FATAL(" Histogram: Nominal "+hNpfx+hName+" not found, exit!"); exit(0); }

      PRINT_DEBUG( (tmpName+"/"+hName).c_str() );
      hsysup = (TH2D*)m_AcSysFile->Get( (tmpName+"/"+hName).c_str() );

      if(hsysup==NULL){ PRINT_WARNING(" Histogram: "+tmpName+"/"+hName+" not found, skip!"); continue; } /// TO BE FIXED/REMOVED
      if(hsysup==NULL){ PRINT_FATAL(" Histogram: "+tmpName+"/"+hName+" not found, exit!"); exit(0); }
      
      double var = 0;
      if(hsysup->GetBinContent(cati+1,catj+1)==0 ){
	PRINT_FATAL(" Sys "+tmpName+" variation = 0, exit! AA");
	continue;
	//exit(0);
      }
      //std::cout << "cati: " << cati << std::endl;
      //std::cout << "catj: " << catj << std::endl;
      //std::cout << "hsysup: " << hsysup->GetBinContent(cati+1,catj+1) << std::endl;
      //std::cout << "hnom: " << hnom->GetBinContent(cati+1,catj+1) << std::endl;
      if (hsysup->GetBinContent(cati+1,catj+1)==0 || hnom->GetBinContent(cati+1,catj+1) ==0) var =1;
      else var = hsysup->GetBinContent(cati+1,catj+1)/hnom->GetBinContent(cati+1,catj+1) ;

      //std::cout << "var: " << var << std::endl;

      if (m_addAsys) {
      	rnom = (TH1D*)nomF->Get( (hNpfx+rName).c_str() );
      	anom = (TH1D*)nomF->Get( (hNpfx+aName).c_str() );
	rsysup = (TH1D*)m_AcSysFile->Get( (tmpName+"/"+rName).c_str() );
	asysup = (TH1D*)m_AcSysFile->Get( (tmpName+"/"+aName).c_str() );
      	if (rnom->GetBinContent(catj+1) == 0 || anom->GetBinContent(catj+1) == 0) { sysup.push_back( 1 );  syslow.push_back( 1 ); }
        else {
		//double rvar = rsysup->GetBinContent(catj+1)/rnom->GetBinContent(catj+1);
		double avar = asysup->GetBinContent(catj+1)/anom->GetBinContent(catj+1);
		double diff = var - avar;
		sysup.push_back( 1+diff );  syslow.push_back( 1-diff );
		//std::cout << "1+diff: " << 1+diff <<  std::endl;
		//std::cout << "1-diff: " << 1-diff <<  std::endl;
	}
      }
      else {
	if(var>1){ sysup.push_back( var );  syslow.push_back( 1-(var-1) ); }
	else     { sysup.push_back( var );  syslow.push_back( 1+(1-var) ); }
      }
    }
    
    interp.push_back(4); // 4 is the index of the interpolation for the i-th variable
    if(!m_skipPruning){
      float releff = v_sigma.at(catj)->getVal()*v_eff.at(catj)->getVal()*v_r.at(catj)->getVal()*v_A.at(catj)->getVal()/(v_sigma.at(cati)->getVal()*v_eff.at(cati)->getVal()*v_r.at(cati)->getVal()*v_A.at(cati)->getVal());
      if ( Pruning(&syslow, &sysup, &interp, releff) ) continue;
    }

    v_sys.add(*tmp_sys);

    PRINT_DEBUG( " Systematic = " + tmpName + "  DwVal = " + to_string(syslow.at(syslow.size()-1) )  +
		 +"  UpVal = " + to_string(sysup.at(sysup.size()-1) ) );
    makeGaussianConstraint(tmp_sys);
    if ( m_listNP.find((tmpName).c_str()) ) continue; // skip of the NPs is already into the main list


    m_listNP.add(*tmp_sys);
    if( x.first!=Syst::VAR_TH_QCD_Scale_VBF && x.first!=Syst::VAR_TH_QCD_Scale_VH &&
	x.first!=Syst::VAR_TH_QCD_Scale_ttH && x.first!=Syst::VAR_TH_Shower_ISRFSR )
      hsysup->Delete();
    
    if( x.first<Syst::MUON_SCALE ||
	(x.first>=Syst::VAR_TH_Var3c && x.first<=Syst::VAR_TH_hard) ){
      hsysdown->Delete();
    }

    if( (x.first!=Syst::VAR_TH_pdf_90400 && proc!=Process::ggH && proc!=Process::ggHbbH) &&
	(x.first<=Syst::SignalComposition_ggHbbH && x.first>=Syst::SignalComposition_ttHtH) ){
      hnom->Delete();
    }
  }
  
  //if(!m_skipPruning) Pruning(&syslow, &sysup, &interp, &v_sys);
  
  m_sysblock = new RooStats::HistFactory::FlexibleInterpVar( sysBlockName.c_str(), sysBlockName.c_str(),
							     v_sys, 1, syslow, sysup, interp );
  PRINT_DEBUG_OBJECT(m_sysblock,1);
  return m_sysblock;
  
}


void WorkSpaceMaker::makeGaussianConstraint(RooRealVar* v_sys){
  
  PRINT_DEBUG_FUNCTION(" <makeGaussianConstraint()>:: make Gaussian constraint for systematic ");

  m_gaus_tmp = NULL;
  sigma_p = new RooRealVar("sigma_p","sigma_p",1);
  sigma_p->setConstant(1);
  m_mean = new RooRealVar((string(v_sys->GetName())+"_mean").c_str(),(string(v_sys->GetName())+"_mean").c_str(),0);
  m_mean->setConstant(1);
  m_gaus_tmp = new RooGaussian ( (string(v_sys->GetName())+"_Pdf").c_str(),
				 (string(v_sys->GetName())+"_Pdf").c_str(),
				 *v_sys, *m_mean,  *sigma_p );
  
  if (m_listpdf_np.find(m_gaus_tmp->GetName())==0 ){
    m_listpdf_np.add(*m_gaus_tmp);
    m_globalObservables.add(*m_mean);
  }
}

void  WorkSpaceMaker :: FixSysForFit(string which){
  PRINT_DEBUG_FUNCTION(" <FixSysForFit()>:: fixing Systematic category " + which +
                       " when profiling to data");

  m_ws->loadSnapshot("postfit");
  TIterator* it = m_listNP.createIterator();
  
  RooRealVar *var = NULL;
  if( which=="all" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      m_ws->var(var->GetName())->setConstant(true); 
    }
  }      
  else if( which=="electron" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("AS_E") != string::npos )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="muon" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("MUON") != string::npos )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="ZZ" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("qqZZ") != string::npos || string(var->GetName()).find("ggZZ") != string::npos )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="sig" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("sig") != string::npos || string(var->GetName()).find("Sig") != string::npos || string(var->GetName()).find("HiggsMassVariation") != string::npos  )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="jet" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("_J")!=string::npos ||
	  string(var->GetName()).find("_FT")!=string::npos )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  
  else if( which=="lumi" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("Lumi")!=string::npos )
        m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="zjet" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("ZJET")!=string::npos )
        m_ws->var(var->GetName())->setConstant(true);
    }
  }
}


void WorkSpaceMaker :: PlotSysBands (){
  
  PRINT_DEBUG_FUNCTION(" <PlotSysBands()>:: PlotSysBands");
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
  RooMsgService::instance().getStream(1).removeTopic(Generation);
  RooMsgService::instance().getStream(1).removeTopic(Minimization);
  RooMsgService::instance().getStream(1).removeTopic(Plotting);
  RooMsgService::instance().getStream(1).removeTopic(Fitting);
  RooMsgService::instance().getStream(1).removeTopic(Integration);
  RooMsgService::instance().getStream(1).removeTopic(LinkStateMgmt);
  RooMsgService::instance().getStream(1).removeTopic(Eval);
  RooMsgService::instance().getStream(1).removeTopic(Caching);
  RooMsgService::instance().getStream(1).removeTopic(Optimization);
  RooMsgService::instance().getStream(1).removeTopic( ObjectHandling);
  RooMsgService::instance().getStream(1).removeTopic(InputArguments);
  RooMsgService::instance().getStream(1).removeTopic(Tracing);
  RooMsgService::instance().getStream(1).removeTopic(Contents);
  RooMsgService::instance().getStream(1).removeTopic(DataHandling);
  RooMsgService::instance().getStream(1).removeTopic(NumIntegration);
  gErrorIgnoreLevel = 1001; /// remove info messages
  TFile* _sysoutput = new  TFile((m_OutDir+"/"+m_Variable+"_totalSysShape.root").c_str(),"recreate");

  TH1* hh_pdf = NULL;
  int bin = m_Category.size();
  if(m_Fiducial) bin = m_Mbins;
  
  TH1* hh_pdfnominal = NULL;
  TH1* hh_pdfdown    = NULL;
  TH1* hh_pdfup      = NULL;
  
  /*
   if (!m_Fiducial){
   
   hh_pdfnominal = new TH1F("nominal", "nominal",  bin, 0, bin  );
   hh_pdfdown = new TH1F("down", "down",  bin, 0, bin );
   hh_pdfup = new TH1F("up", "up",  bin, 0, bin );
   
   }*/
  
  TIterator* it = m_listNP.createIterator();
  RooRealVar *var;
  string name;
  RooWorkspace *myWS = (RooWorkspace*) m_ws->Clone();
  vector<double> varup;
  vector<double> vardown;
  varup.clear(); vardown.clear();
  
  vector<string> syssplit     = {"all", "MUON", "_J" , "AS_E"    , "ZZ", "sig", "ZJET", "Lumi"/*, "AS_FT"*/};
  vector<string> syssplitname = {"all", "muon", "jet", "electron", "ZZ", "sig", "zjet", "lumi"/*, "flavourtag"*/};
  
  for (unsigned int i_sys = 0; i_sys< syssplit.size(); ++i_sys){
    
    for (unsigned int i = 0; i< m_Category.size(); ++i){
      PRINT_INFO(" Printing histo sys: \033[0m " + m_Variable + " " + m_Category.at(i) + " "
      + syssplitname.at(i_sys));
      
      if (m_Fiducial){
        hh_pdfnominal = new TH1F( ("nominal"+m_Category.at(i)+"_"+syssplitname.at(i_sys)).c_str(),
                                 ("nominal"+m_Category.at(i)+"_"+syssplitname.at(i_sys)).c_str(),  bin, 0, bin  );
        hh_pdfdown    = new TH1F( ("down"+m_Category.at(i)+"_"+syssplitname.at(i_sys)).c_str(),
                                 ("down"+m_Category.at(i)+"_"+syssplitname.at(i_sys)).c_str(),  bin, 0, bin );
        hh_pdfup      = new TH1F( ("up"+m_Category.at(i)+"_"+syssplitname.at(i_sys)).c_str(),
                                 ("up"+m_Category.at(i)+"_"+syssplitname.at(i_sys)).c_str(),  bin, 0, bin );
      }
      
      if (!m_Fiducial && i==0){
        hh_pdfnominal = new TH1F( ("nominal_"+syssplitname.at(i_sys)).c_str(),
                                 ("nominal_"+syssplitname.at(i_sys)).c_str(),  bin, 0, bin  );
        hh_pdfdown    = new TH1F( ("down_"+syssplitname.at(i_sys)).c_str(),
                                 ("down_"+syssplitname.at(i_sys)).c_str(),  bin, 0, bin );
        hh_pdfup      = new TH1F( ("up_"+syssplitname.at(i_sys)).c_str(),
                                 ("up_"+syssplitname.at(i_sys)).c_str(),  bin, 0, bin );
      }
      varup.clear();
      vardown.clear();
      
      it->Reset();
      while ((var = (RooRealVar*)it->Next())) {
        
        if( syssplit.at(i_sys) != "all" && syssplit.at(i_sys)!="sig" )
          if( string(var->GetName()).find(syssplit.at(i_sys) ) == string::npos ) continue ;
        
        if (syssplit.at(i_sys)=="sig"){
          //if ( string(var->GetName()).find("sig") == string::npos &&
          //    string(var->GetName()).find("Sig") == string::npos &&
          //    string(var->GetName()).find("Mass") == string::npos )
	  if ( string(var->GetName()).find("Theory_pdf") == string::npos &&
	       string(var->GetName()).find("QCDscale") == string::npos &&
	       string(var->GetName()).find("QCDScale") == string::npos &&
	       string(var->GetName()).find("sig") == string::npos )
            continue ;
        }
        PRINT_DEBUG( (string)var->GetName() + "  " + syssplitname.at(i_sys) + "  " +m_Category.at(i));
        myWS->var(var->GetName())->setVal(0);
        
        //myWS->var("ATLAS_ZJET_llmumu_stat")->setVal(0); myWS->var("ATLAS_ZJET_llmumu_sys")->setVal(0); myWS->var("ATLAS_ZJET_llee_stat")->setVal(0); myWS->var("ATLAS_ZJET_llee_sys")->setVal(0);
        
        hh_pdf = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram("x",bin);
	hh_pdf->SetNameTitle(("nom"+m_Category.at(i)+"_"+syssplitname.at(i_sys)).c_str(),("nom"+m_Category.at(i)+"_"+syssplitname.at(i_sys)).c_str());
        if (!m_Fiducial) hh_pdfnominal->SetBinContent(i+1,hh_pdf->GetBinContent(1)/m_binwidth.at(i));
        if (m_Fiducial)  hh_pdfnominal=hh_pdf;
        
        myWS->var(var->GetName());
        myWS->var(var->GetName())->setVal(1);
        hh_pdf = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram("x",bin);
        hh_pdf->SetNameTitle(("up"+m_Category.at(i)+var->GetName()).c_str(),("up"+m_Category.at(i)+var->GetName()).c_str());
        if (!m_Fiducial)
          varup.push_back( ( (hh_pdfnominal->GetBinContent(i+1)) - (hh_pdf->GetBinContent(1)/m_binwidth.at(i)) ) / ( hh_pdfnominal->GetBinContent(i+1) ) );
        if (m_Fiducial)
          varup.push_back( ( (hh_pdfnominal->Integral()) - (hh_pdf->Integral()) )/( hh_pdfnominal->Integral() ) ); //bin 10 = higgs peak
        
        myWS->var(var->GetName());
        myWS->var(var->GetName())->setVal(-1);
        hh_pdf = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram("x",bin);
        hh_pdf->SetNameTitle(("down"+m_Category.at(i)+var->GetName()).c_str(),("down"+m_Category.at(i)+var->GetName()).c_str());
        if (!m_Fiducial)
          vardown.push_back( ( (hh_pdfnominal->GetBinContent(i+1)) - (hh_pdf->GetBinContent(1)/m_binwidth.at(i)) ) / ( hh_pdfnominal->GetBinContent(i+1)) );
        if (m_Fiducial)
          vardown.push_back( ( (hh_pdfnominal->Integral()) - (hh_pdf->Integral()) ) / ( hh_pdfnominal->Integral()) ); //bin 10 = higgs peak
        
        myWS->var(var->GetName())->setVal(0);
      }
      
      double downsys=0;
      double upsys=0;
      
      for (unsigned int kk =0; kk <vardown.size(); ++kk){
        downsys+=(vardown.at(kk) * vardown.at(kk));
        upsys+=( varup.at(kk) * varup.at(kk));
        
      }
      upsys= sqrt(upsys); downsys=sqrt(downsys);
      
      if (!m_Fiducial)  {
        hh_pdfup->SetBinContent(i+1,(hh_pdfnominal->GetBinContent(i+1)*(1+upsys)));
        hh_pdfdown->SetBinContent(i+1,(hh_pdfnominal->GetBinContent(i+1)*(1-downsys)));
      }
      
      if (m_Fiducial){
        hh_pdfup->Reset();
        hh_pdfup->Add(hh_pdfnominal);
        hh_pdfup->Scale( (1+upsys) );
        hh_pdfdown->Reset();
        hh_pdfdown->Add(hh_pdfnominal);
        hh_pdfdown->Scale( (1-downsys) );
        hh_pdfnominal->SetLineColor(kBlack);
        hh_pdfnominal->SetLineWidth(2);
        hh_pdfnominal->GetYaxis()->SetRangeUser(0,hh_pdfnominal->GetMaximum()*1.2);
        hh_pdfnominal->Draw();
        hh_pdfup->SetLineColor(kBlue);
        hh_pdfup->SetLineWidth(2);
        hh_pdfup->Draw("same");
        hh_pdfdown->SetLineColor(kRed);
        hh_pdfdown->SetLineWidth(2);
        hh_pdfdown->Draw("same");
        _sysoutput->cd();
        hh_pdfnominal->Write();
        hh_pdfup->Write();
        hh_pdfdown->Write();
      }
      varup.clear(); vardown.clear();
    }
    if (!m_Fiducial){
      hh_pdfnominal->SetLineColor(kBlack);
      hh_pdfnominal->SetLineWidth(2);
      hh_pdfnominal->GetYaxis()->SetRangeUser(0,hh_pdfnominal->GetMaximum()*1.2);
      hh_pdfnominal->Draw();
      hh_pdfup->SetLineColor(kBlue);
      hh_pdfup->SetLineWidth(2);
      hh_pdfup->Draw("same");
      hh_pdfdown->SetLineColor(kRed);
      hh_pdfdown->SetLineWidth(2);
      hh_pdfdown->Draw("same");
      _sysoutput->cd();
      hh_pdfnominal->Write();
      hh_pdfup->Write();
      hh_pdfdown->Write();
    }
  }
  //_sysoutput->Write();
  _sysoutput->Close();
  
  it->Reset();
  while ((var = (RooRealVar*)it->Next())){
    myWS->var(var->GetName());
    myWS->var(var->GetName())->setVal(0);
  }
  
  if(false && m_addShapeSys && !m_Fiducial)  {
    string varname = "x";
    if (!m_Fiducial) varname = "m4l";
    vector<string> shapesname = {"ATLAS_MUON_SCALE", "ATLAS_MUON_ID", "ATLAS_HiggsMassVariation"};
    int i = 0;
    for (unsigned jj = 0; jj < shapesname.size() ; ++jj){
      myWS->var(shapesname.at(jj).c_str())->setVal(0);
      hh_pdfnominal = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram(varname.c_str(),m_Mbins);
      hh_pdfnominal->SetNameTitle(("nom"+m_Category.at(i)).c_str(),("nom"+m_Category.at(i)).c_str());
      myWS->var(shapesname.at(jj).c_str())->setVal(1);
      hh_pdfup = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram(varname.c_str(),m_Mbins);
      hh_pdfup->SetNameTitle(("up"+m_Category.at(i)).c_str(),("up"+m_Category.at(i)).c_str());
      myWS->var(shapesname.at(jj).c_str())->setVal(-1);
      hh_pdfdown = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram(varname.c_str(),m_Mbins);
      hh_pdfdown->SetNameTitle(("down"+m_Category.at(i)).c_str(),("down"+m_Category.at(i)).c_str());
      TCanvas *ctmp = CreateCanvas( "pdftmp_"+shapesname.at(jj),800,800 );
      hh_pdfnominal->SetLineColor(kBlack);hh_pdfnominal->SetLineWidth(2);
      hh_pdfnominal->GetYaxis()->SetRangeUser(0,hh_pdfnominal->GetMaximum()*1.2);
      hh_pdfnominal->Draw();
      hh_pdfup->SetLineColor(kBlue);hh_pdfup->SetLineWidth(2);
      hh_pdfup->Draw("same");
      hh_pdfdown->SetLineColor(kRed);hh_pdfdown->SetLineWidth(2);
      hh_pdfdown->Draw("same");
      ctmp->SaveAs( ("~/Desktop/sys"+shapesname.at(jj)+".pdf").c_str() );
      myWS->var(shapesname.at(jj).c_str())->setVal(0);
    }

  }
  
  it->Reset();
  while( (var = (RooRealVar*)it->Next()) ){
    myWS->var(var->GetName());
    myWS->var(var->GetName())->setVal(0);
  }
  
}

RooStats::HistFactory::FlexibleInterpVar* WorkSpaceMaker::makeSysGlobal(string blockID, int ChNum,
									int proc, 	int cat,
									bool isSignal, bool isggZZ){
  
  PRINT_DEBUG_FUNCTION(" <makeSysGlobal()>:: creating systematic block");
  string sysBlockName;
  if (m_Fiducial) sysBlockName = "sysblock"+blockID+"_proc_"+to_string(proc)+"_"+GetChannelName(ChNum);
  else            sysBlockName = "sysblock"+blockID+"_proc_"+to_string(proc)+"_"+m_Category.at(cat);
  PRINT_DEBUG( " <makeSysGlobal()>:: sysBlockName will be: "+sysBlockName);
  
  vector< double > syslow;
  vector< double > sysup;
  vector<int> interp;

  vector<string> SYS = {"ATLAS_LUMI"};
  vector<double> SYSvalues = {0.017};

  if(isSignal && m_FidTotal){
    SYS.push_back("ATLAS_BR_ZZ_tot");
    SYSvalues.push_back(0.022);
  }
  
  if (isggZZ) {
  	SYS.push_back("ATLAS_QCDscale_ggZZ");
  	SYSvalues.push_back(0.70);
  }

   if (m_Variable=="njet" && !m_matrix) {
  	if (cat==0 && isSignal){
    		SYS.push_back("ATLAS_bias_0");
    		SYSvalues.push_back(0.01);
  	}
  	if (cat==1 && isSignal){
    		SYS.push_back("ATLAS_bias_1");
    		SYSvalues.push_back(0.05);
  	}
  	if (cat==2 && isSignal){
    		SYS.push_back("ATLAS_bias_2");
    		SYSvalues.push_back(0.075);
  	}
  	if (cat==3 && isSignal){
    		SYS.push_back("ATLAS_bias_3");
    		SYSvalues.push_back(0.10);
  	}
   }

  RooRealVar *tmp_sys =NULL;
  RooArgList v_sys;

  for( unsigned int i = 0; i < SYS.size(); ++i ){
    
    if ( v_sys.find(SYS.at(i).c_str() )) PRINT_WARNING(" NP: "+ SYS.at(i) +" already found in the list.. skip it!" );
    if ( v_sys.find(SYS.at(i).c_str() )) continue;
    
    tmp_sys = new RooRealVar((SYS.at(i)).c_str(), (SYS.at(i)).c_str(), 0, -5, 5);// tmp_sys->setConstant(1);

    syslow.push_back( 1- SYSvalues.at(i) );
    sysup.push_back( 1+ SYSvalues.at(i) );
    interp.push_back(4); // 4 is the index of the interpolation for the i-th variable

    v_sys.add(*tmp_sys);

    PRINT_DEBUG( " Systematic = " + SYS.at(i) + "  DwVal = " + to_string(syslow.at(syslow.size()-1) )  +
                +"  UpVal = " + to_string(sysup.at(sysup.size()-1) ) );
    makeGaussianConstraint(tmp_sys);
    if ( m_listNP.find((SYS.at(i)).c_str()) ) continue; // skip of the NPs is already into the main list

    
    m_listNP.add(*tmp_sys);
  }
  
  //if(!m_skipPruning) Pruning(&syslow, &sysup, &interp, &v_sys);
    
  m_sysblock = new RooStats::HistFactory::FlexibleInterpVar( sysBlockName.c_str(), sysBlockName.c_str(),
							     v_sys, 1, syslow, sysup, interp );
  PRINT_DEBUG_OBJECT(m_sysblock,1);
  return m_sysblock;
  
}

string WorkSpaceMaker::GetUnfoldParamHistoName(std::string type, int channel,  int process){

  string m_name = type+"_";
  if (type != "rF") {
      if(m_useBornLep) m_name += "Born_";
      else             m_name += "Dres_";
  }
  if(m_Fiducial)   m_name += "fid_";
  else             m_name += m_Variable+"_";
  m_name += GetChannelName(channel)+"_"+GetProcessName(process);

  return m_name;
  
}

pair<double,double> WorkSpaceMaker::PerformEnvelopeMtx(TH2D *nom, int ChNum, int proc, string type,
						       int sys  , int rcCat, int thCat){

  PRINT_DEBUG( "<PerformEnvelopeMtx()>:: sys variation "+to_string(sys) );

  vector<TH2D*> vars;
  vector<double> values;
  string hName = GetUnfoldParamHistoName(type,ChNum,proc);

  switch(sys){
  case Syst::VAR_TH_QCD_Scale_VBF:
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_VBF/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_VBF/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_VBF/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_VBF/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_VBF/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_VBF/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_VBF/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_VBF/"+hName).c_str() ) );
    break;
  case Syst::VAR_TH_QCD_Scale_VH:
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_VH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_VH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_VH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_VH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_VH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_VH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_VH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_VH/"+hName).c_str() ) );
    break;
  case Syst::VAR_TH_QCD_Scale_ttH:
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_ttH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_ttH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_ttH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_ttH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_ttH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_ttH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_ttH/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_ttH/"+hName).c_str() ) );
    break;
  case Syst::VAR_TH_Shower_ISRFSR:
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_0p5/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_1p0/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_2p0/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p625_fsrmuRfac_1p0/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p75_fsrmuRfac_1p0/" +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p875_fsrmuRfac_1p0/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p5/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p625/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p75/" +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p875/"+hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p25/" +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p5/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p75/" +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_2p0/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p25_fsrmuRfac_1p0/" +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p5_fsrmuRfac_1p0/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p75_fsrmuRfac_1p0/" +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_0p5/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_1p0/"  +hName).c_str() ) );
    vars.push_back( (TH2D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_2p0/"  +hName).c_str() ) );
    break;
  default:
    return make_pair( 1,1 );
  }
  
  for(uint i=0; i<vars.size(); i++){
    
    values.push_back( vars.at(i)->GetBinContent(rcCat+1,thCat+1)/nom->GetBinContent(rcCat+1,thCat+1) );
    PRINT_DEBUG( "                         "+string(vars.at(i)->GetName())+" var = "+
		 to_string(vars.at(i)->GetBinContent(rcCat+1,thCat+1))+
		 " nom = "+to_string(nom->GetBinContent(rcCat+1,thCat+1))+
		 " ratio = "+to_string(values.at(i)) );
  }

  sort(values.begin(), values.end() );
  
  return make_pair( values.at(values.size()-1), values.at(0) );
  
}

pair<double,double> WorkSpaceMaker::PerformEnvelope(TH1D *nom, TH1D* anom, int ChNum, int proc,
						    string type, int sys  , int rcCat, bool isZZ, bool doAR){

  PRINT_DEBUG( "<PerformEnvelope()>:: sys variation "+to_string(sys) );

  vector<TH1D*> vars;
  vector<double> values;
  string hName = "";
  string aName = GetUnfoldParamHistoName("aF",ChNum,proc);
  if(sys==Syst::VAR_TH_qqZZ_QCD) hName = type;
  else                           hName = GetUnfoldParamHistoName(type,ChNum,proc);

  switch(sys){
  case Syst::VAR_TH_QCD_Scale_VBF:
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_VBF/"+hName).c_str() )->Clone("h0")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_VBF/"+hName).c_str() )->Clone("h1")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_VBF/"+hName).c_str() )->Clone("h2")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_VBF/"+hName).c_str() )->Clone("h3")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_VBF/"+hName).c_str() )->Clone("h4")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_VBF/"+hName).c_str() )->Clone("h5")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_VBF/"+hName).c_str() )->Clone("h6")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_VBF/"+hName).c_str() )->Clone("h7")) );
    break;
  case Syst::VAR_TH_QCD_Scale_VH:
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_VH/"+hName).c_str() )->Clone("h0")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_VH/"+hName).c_str() )->Clone("h1")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_VH/"+hName).c_str() )->Clone("h2")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_VH/"+hName).c_str() )->Clone("h3")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_VH/"+hName).c_str() )->Clone("h4")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_VH/"+hName).c_str() )->Clone("h5")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_VH/"+hName).c_str() )->Clone("h6")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_VH/"+hName).c_str() )->Clone("h7")) );
    break;
  case Syst::VAR_TH_QCD_Scale_ttH:
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_ttH/"+hName).c_str() )->Clone("h0")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_ttH/"+hName).c_str() )->Clone("h1")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_ttH/"+hName).c_str() )->Clone("h2")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_ttH/"+hName).c_str() )->Clone("h3")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_ttH/"+hName).c_str() )->Clone("h4")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_ttH/"+hName).c_str() )->Clone("h5")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_ttH/"+hName).c_str() )->Clone("h6")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_ttH/"+hName).c_str() )->Clone("h7")) );
    break;
  case Syst::VAR_TH_Shower_ISRFSR:
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_0p5/"  +hName).c_str() )->Clone("h0")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_1p0/"  +hName).c_str() )->Clone("h1")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_2p0/"  +hName).c_str() )->Clone("h2")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p625_fsrmuRfac_1p0/"+hName).c_str() )->Clone("h3")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p75_fsrmuRfac_1p0/" +hName).c_str() )->Clone("h4")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p875_fsrmuRfac_1p0/"+hName).c_str() )->Clone("h5")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p5/"  +hName).c_str() )->Clone("h6")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p625/"+hName).c_str() )->Clone("h7")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p75/" +hName).c_str() )->Clone("h8")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p875/"+hName).c_str() )->Clone("h9")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p25/" +hName).c_str() )->Clone("h10")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p5/"  +hName).c_str() )->Clone("h11")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p75/" +hName).c_str() )->Clone("h12")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_2p0/"  +hName).c_str() )->Clone("h13")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p25_fsrmuRfac_1p0/" +hName).c_str() )->Clone("h14")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p5_fsrmuRfac_1p0/"  +hName).c_str() )->Clone("h15")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p75_fsrmuRfac_1p0/" +hName).c_str() )->Clone("h16")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_0p5/"  +hName).c_str() )->Clone("h17")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_1p0/"  +hName).c_str() )->Clone("h18")) );
    vars.push_back( (TH1D*)(m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_2p0/"  +hName).c_str() )->Clone("h19")) );
    break;
  case Syst::VAR_TH_qqZZ_QCD:
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR0p5_MUF0p5_PDF261000/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR0p5_MUF1_PDF261000/"  +hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF0p5_PDF261000/"  +hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF2_PDF261000/"    +hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR2_MUF1_PDF261000/"    +hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR2_MUF2_PDF261000/"    +hName).c_str() ) );
    break;
  default:
    return make_pair( 1,1 );
  }

  if (doAR) {
  	switch(sys){
  	case Syst::VAR_TH_QCD_Scale_VBF:
  	  vars[0]->Multiply(vars[0], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_VBF/"+aName).c_str() ) );
  	  vars[1]->Multiply(vars[1], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_VBF/"+aName).c_str() ) );
  	  vars[2]->Multiply(vars[2], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_VBF/"+aName).c_str() ) );
  	  vars[3]->Multiply(vars[3], (TH1D*)m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_VBF/"+aName).c_str() ) );
  	  vars[4]->Multiply(vars[4], (TH1D*)m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_VBF/"+aName).c_str() ) );
  	  vars[5]->Multiply(vars[5], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_VBF/"+aName).c_str() ) );
  	  vars[6]->Multiply(vars[6], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_VBF/"+aName).c_str() ) );
  	  vars[7]->Multiply(vars[7], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_VBF/"+aName).c_str() ) );
  	  break;
  	case Syst::VAR_TH_QCD_Scale_VH:
  	  vars[0]->Multiply(vars[0], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_VH/"+aName).c_str() ) );
  	  vars[1]->Multiply(vars[1], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_VH/"+aName).c_str() ) );
  	  vars[2]->Multiply(vars[2], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_VH/"+aName).c_str() ) );
  	  vars[3]->Multiply(vars[3], (TH1D*)m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_VH/"+aName).c_str() ) );
  	  vars[4]->Multiply(vars[4], (TH1D*)m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_VH/"+aName).c_str() ) );
  	  vars[5]->Multiply(vars[5], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_VH/"+aName).c_str() ) );
  	  vars[6]->Multiply(vars[6], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_VH/"+aName).c_str() ) );
  	  vars[7]->Multiply(vars[7], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_VH/"+aName).c_str() ) );
  	  break;
  	case Syst::VAR_TH_QCD_Scale_ttH:
  	  vars[0]->Multiply(vars[0], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF0p5_ttH/"+aName).c_str() ) );
  	  vars[1]->Multiply(vars[1], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF1p0_ttH/"+aName).c_str() ) );
  	  vars[2]->Multiply(vars[2], (TH1D*)m_AcSysFile->Get( ("Theory_muR0p5_muF2p0_ttH/"+aName).c_str() ) );
  	  vars[3]->Multiply(vars[3], (TH1D*)m_AcSysFile->Get( ("Theory_muR1p0_muF0p5_ttH/"+aName).c_str() ) );
  	  vars[4]->Multiply(vars[4], (TH1D*)m_AcSysFile->Get( ("Theory_muR1p0_muF2p0_ttH/"+aName).c_str() ) );
  	  vars[5]->Multiply(vars[5], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF0p5_ttH/"+aName).c_str() ) );
  	  vars[6]->Multiply(vars[6], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF1p0_ttH/"+aName).c_str() ) );
  	  vars[7]->Multiply(vars[7], (TH1D*)m_AcSysFile->Get( ("Theory_muR2p0_muF2p0_ttH/"+aName).c_str() ) );
  	  break;
  	case Syst::VAR_TH_Shower_ISRFSR:
  	  vars[0]->Multiply(vars[0], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_0p5/"  +aName).c_str() ) );
  	  vars[1]->Multiply(vars[1], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_1p0/"  +aName).c_str() ) );
  	  vars[2]->Multiply(vars[2], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p5_fsrmuRfac_2p0/"  +aName).c_str() ) );
  	  vars[3]->Multiply(vars[3], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p625_fsrmuRfac_1p0/"+aName).c_str() ) );
  	  vars[4]->Multiply(vars[4], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p75_fsrmuRfac_1p0/" +aName).c_str() ) );
  	  vars[5]->Multiply(vars[5], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_0p875_fsrmuRfac_1p0/"+aName).c_str() ) );
  	  vars[6]->Multiply(vars[6], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p5/"  +aName).c_str() ) );
  	  vars[7]->Multiply(vars[7], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p625/"+aName).c_str() ) );
  	  vars[8]->Multiply(vars[8], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p75/" +aName).c_str() ) );
  	  vars[9]->Multiply(vars[9], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_0p875/"+aName).c_str() ) );
  	  vars[10]->Multiply(vars[10], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p25/" +aName).c_str() ) );
  	  vars[11]->Multiply(vars[11], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p5/"  +aName).c_str() ) );
  	  vars[12]->Multiply(vars[12], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_1p75/" +aName).c_str() ) );
  	  vars[13]->Multiply(vars[13], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p0_fsrmuRfac_2p0/"  +aName).c_str() ) );
  	  vars[14]->Multiply(vars[14], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p25_fsrmuRfac_1p0/" +aName).c_str() ) );
  	  vars[15]->Multiply(vars[15], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p5_fsrmuRfac_1p0/"  +aName).c_str() ) );
  	  vars[16]->Multiply(vars[16], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_1p75_fsrmuRfac_1p0/" +aName).c_str() ) );
  	  vars[17]->Multiply(vars[17], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_0p5/"  +aName).c_str() ) );
  	  vars[18]->Multiply(vars[18], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_1p0/"  +aName).c_str() ) );
  	  vars[19]->Multiply(vars[19], (TH1D*)m_AcSysFile->Get( ("Theory_Shower_isrmuRfac_2p0_fsrmuRfac_2p0/"  +aName).c_str() ) );
  	  break;
  	case Syst::VAR_TH_qqZZ_QCD:
  	  vars[0]->Multiply(vars[0], (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR0p5_MUF0p5_PDF261000/"+aName).c_str() ) );
  	  vars[1]->Multiply(vars[1], (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR0p5_MUF1_PDF261000/"  +aName).c_str() ) );
  	  vars[2]->Multiply(vars[2], (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF0p5_PDF261000/"  +aName).c_str() ) );
  	  vars[3]->Multiply(vars[3], (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF2_PDF261000/"    +aName).c_str() ) );
  	  vars[4]->Multiply(vars[4], (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR2_MUF1_PDF261000/"    +aName).c_str() ) );
  	  vars[5]->Multiply(vars[5], (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR2_MUF2_PDF261000/"    +aName).c_str() ) );
  	  break;
  	default:
  	  return make_pair( 1,1 );
  	}
  }

  
  for(uint i=0; i<vars.size(); i++){

    if(m_Fiducial) {
	double denom;
	if (doAR) denom = anom->GetBinContent(1)*nom->GetBinContent(1);
        else      denom = nom->GetBinContent(1);	
        values.push_back( vars.at(i)->GetBinContent(1)/denom );
    }
    else {
		if (m_floatqqZZ && isZZ) {
			std::vector<int> ZZcat = m_ZZbins[rcCat];
				double num=0;
				double denom=0;
				for (std::vector<int>::iterator it = ZZcat.begin() ; it != ZZcat.end(); ++it) {
					num   = num + vars.at(i)->GetBinContent(*it+1);
					denom = denom + nom->GetBinContent(*it+1);
				} 
				values.push_back(1 + vars.at(i)->GetBinContent(rcCat+1)/nom->GetBinContent(rcCat+1) - num/denom);
		
		}
		else {
		       if (doAR) {values.push_back( vars.at(i)->GetBinContent(rcCat+1)/(nom->GetBinContent(rcCat+1)*anom->GetBinContent(rcCat+1)) );
			//       std::cout << "num: " << vars.at(i)->GetBinContent(rcCat+1) << std::endl;
			//       std::cout << "bin: " << rcCat << ", rnom: " << nom->GetBinContent(rcCat+1) << std::endl; 
			//       std::cout << "bin: " << rcCat << ", anom: " << anom->GetBinContent(rcCat+1) << std::endl;
		       	//	std::cout << "denom: " << nom->GetBinContent(rcCat+1)*anom->GetBinContent(rcCat+1) << std::endl;
				} 
		       else  {    values.push_back( vars.at(i)->GetBinContent(rcCat+1)/nom->GetBinContent(rcCat+1) );
			      //std::cout << "num: " << vars.at(i)->GetBinContent(rcCat+1) << std::endl;
			     //std::cout << "denom: " << nom->GetBinContent(rcCat+1) << std::endl;
			     } 
		}
    }
    PRINT_DEBUG( "                      "+string(vars.at(i)->GetName())+" var = "+
		 to_string(vars.at(i)->GetBinContent(rcCat+1))+
		 " nom = "+to_string(nom->GetBinContent(rcCat+1))+
		 " ratio = "+to_string(values.at(i)) );
    
  }

  sort(values.begin(), values.end() );
//  for (int i = 0; i < 8; i++) {
//	  std::cout << "i = " << i << ", value: " << values[i] << std::endl;
//  }

  return make_pair( values.at(values.size()-1), values.at(0) );
  
}

 pair<double,double> WorkSpaceMaker::PerformWeightedSum(TH1D *nom, string hName,
							int sys  , int rcCat, bool isZZ){

   PRINT_DEBUG( "<PerformWeightedSum()>:: sys variation "+to_string(sys) );

  vector<TH1D*> vars;
  double diff2 = 0;

  switch(sys){
  case Syst::VAR_TH_qqZZ_Sherpa_CSSKIN:
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_CSSKIN/"+hName).c_str() ) );
    break;
  case Syst::VAR_TH_qqZZ_PDF:
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261001/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261002/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261003/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261004/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261005/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261006/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261007/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261008/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261009/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261010/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261011/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261012/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261013/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261014/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261015/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261016/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261017/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261018/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261019/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261020/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261021/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261022/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261023/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261024/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261025/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261026/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261027/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261028/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261029/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261030/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261031/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261032/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261033/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261034/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261035/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261036/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261037/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261038/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261039/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261040/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261041/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261042/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261043/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261044/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261045/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261046/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261047/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261048/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261049/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261050/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261051/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261052/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261053/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261054/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261055/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261056/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261057/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261058/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261059/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261060/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261061/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261062/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261063/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261064/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261065/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261066/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261067/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261068/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261069/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261070/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261071/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261072/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261073/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261074/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261075/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261076/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261077/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261078/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261079/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261080/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261081/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261082/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261083/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261084/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261085/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261086/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261087/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261088/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261089/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261090/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261091/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261092/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261093/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261094/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261095/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261096/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261097/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261098/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261099/"+hName).c_str() ) );
    vars.push_back( (TH1D*)m_SysFile->Get( ("Theory_qqZZ_MUR1_MUF1_PDF261100/"+hName).c_str() ) );
    break;
  default:
    return make_pair( 1,1 );
  }

  for(uint i=0; i<vars.size(); i++){

    if(m_Fiducial)
      diff2 += pow(nom->Integral()-vars.at(i)->Integral(),2);
    else {
		if (m_floatqqZZ && isZZ) {
			std::vector<int> ZZcat = m_ZZbins[rcCat];
			double num=0;
			double denom=0;
			for (std::vector<int>::iterator it = ZZcat.begin() ; it != ZZcat.end(); ++it) {
				//std::cout << "Bin = " << rcCat << " ZZbin = " << *it << std::endl;
				num		= num + vars.at(i)->GetBinContent(*it+1);
				denom	= denom + nom->GetBinContent(*it+1);
			} 
			
			diff2 += pow(nom->GetBinContent(rcCat+1) - (1 + vars.at(i)->GetBinContent(rcCat+1)/nom->GetBinContent(rcCat+1) - num/denom)*nom->GetBinContent(rcCat+1),2);
		}
		else diff2 += pow(nom->GetBinContent(rcCat+1)-vars.at(i)->GetBinContent(rcCat+1),2);    
    }
  }
  int totVars = vars.size();
  if(sys==Syst::VAR_TH_qqZZ_PDF) totVars = totVars - 1;
    
  return make_pair( 1+sqrt(1/totVars*diff2), 1-sqrt(1/totVars*diff2) );
  
}


string WorkSpaceMaker::GetSysNpName(int sysNum, string sysName){

  std::string m_name = "";
  if( sysNum<=Syst::MUON_SCALE                                                          ||
      (sysNum>=Syst::VAR_TH_qqZZ_Sherpa_CKKW && sysNum<=Syst::VAR_TH_qqZZ_Sherpa_QSF)   ||
      (sysNum>=Syst::VAR_TH_Var3c && sysNum<=Syst::VAR_TH_hard)                         ||
      (sysNum>=Syst::SignalComposition_ggHbbH && sysNum<=Syst::SignalComposition_ttHtH) ||
      (sysNum>=Syst::ZJET_stat_2l2e && sysNum<=Syst::ZJET_syst_2l2mu)                    ){

    m_name = sysName.substr(0, sysName.length()-7);
  }
  else{
    m_name = sysName;
  }
  return m_name;
  
}

void WorkSpaceMaker::Pruning(vector< double > *syslow, vector< double > *sysup,
			     vector<int> *interp     , RooArgList *v_sys){

  RooRealVar *tmp =NULL;
  for (unsigned int i =0; i < syslow->size(); ++i){
    
    if(abs(1-sysup->at(i)) < 0.08|| abs(1-syslow->at(i)) < 0.08 ){

      tmp = (RooRealVar*) v_sys->at(i);
      string namesys = tmp->GetName();

      PRINT_DEBUG(" <makeSysBlock()>:: sys pruning, sys  = "+namesys+" val up = "+
		  to_string(sysup->at(i))+" val down = "+to_string(syslow->at(i)) );

      syslow ->erase(syslow->begin() + i);
      sysup  ->erase(sysup->begin()  + i);
      interp ->erase(interp->begin() + i);
      v_sys  ->remove(*tmp);
      i--;
      
    }
    
  }
  
}



bool WorkSpaceMaker::Pruning(vector< double > *syslow, vector< double > *sysup,
                             vector<int> *interp, float releff ){

  bool pruned = false;
  if( abs(1-sysup->at(sysup->size()-1)) < 0.01|| abs(1-syslow->at(sysup->size()-1)) < 0.01 ){
    sysup->pop_back();
    syslow->pop_back();
    interp->pop_back();
    pruned = true;
  }
  return pruned;
}



std::vector<int> WorkSpaceMaker :: getZZCatBins(int cat) {
	std::vector<int> ZZCatBins;
	std::vector<int> bin_ranges = GetVarBinRange(m_VariableId);
	
	for (unsigned int i =0; i < bin_ranges.size(); ++i){
		if ( cat < bin_ranges.at(i) ){
			ZZCatBins.push_back(i);
			break;
		}
	}
	return ZZCatBins;
}
