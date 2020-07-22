/* C++ includes */
#include "iostream"
/* program includes */
#include "ShapeSysVar.h"

int main( int argc, char* argv[] ){

  bool doFiducial = false;
  bool debug      = false;
  bool printHelp  = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--doFiducial") ){
      doFiducial = true;
    }
    if( !strcmp(argv[i],"--debug") ){
      debug = true;
    }
    if( !strcmp(argv[i],"--help") ){
      printHelp=true;
    }
  }

  if(printHelp){
    std::cout << "./ShapeSysVar:  make m4l Sys shapes! " <<std::endl;
    std::cout << "             Options:                            " << std::endl;
    std::cout << "             --doFiducial [Enable fiducial case]" << std::endl;
    std::cout << "             --debug      [Enable debug mode]"    << std::endl;
    exit(0);
  }

  std::cout << "< ShapeSysVar() >:: OPTIONS: " <<std::endl;
  std::cout << "                    doFiducial = " << doFiducial << std::endl;
  std::cout << "                    debug      = " << debug      << std::endl;
  
  ShapeSysVar(doFiducial,debug);
  
  return 0;

}

void ShapeSysVar(bool doFiducial, bool debug){

  TH1::SetDefaultSumw2(kTRUE);

  m_debug = debug;
  
  m_Dir = "../MC_Inputs/systs/";
  if(doFiducial) m_Dir += "Fiducial/";
  else           m_Dir += "Differential/";
  
  std::string OutDir = "../varsDistro/";

  m_Out = NULL;
  if(doFiducial)
    m_Out = new TFile( (OutDir+"XsecInputs_15bin_Sys.root").c_str(), "RECREATE" );
  else
    m_Out = new TFile( (OutDir+"XsecInputs_15bin_Sys.root").c_str(), "UPDATE" );
  /* define production modes */
  m_prodMode.push_back( "ggH" );
  m_prodMode.push_back( "VBF" );
  m_prodMode.push_back( "WH"  );
  m_prodMode.push_back( "ZH"  );
  m_prodMode.push_back( "ttH" );
  m_prodMode.push_back( "bbH" );

  /* define mass shifts */
  m_shifts.push_back( std::make_pair( "ShiftUp"  ,"Up"  ) );
  m_shifts.push_back( std::make_pair( "ShiftDown","Down") );

  /* define histograms */
  DefineHistograms();

  /* define categories */
  DefineCategories(doFiducial);
  
  if(doFiducial){
    ProcessFiducial();
    AddFidMassShifts();
  }
  else{
    ProcessDifferential();
    AddDiffMassShifts();
  }

  m_Out->Close();
  
}

void DefineHistograms(){

   if(m_debug)
     std::cout << "<ShapeSysVar()>:: Defining Histograms" << std::endl;

  ElSclUp1_pm = NULL, ElSclDw1_pm = NULL;
  ElSclUp2_pm = NULL, ElSclDw2_pm = NULL;
  ElSclUp3_pm = NULL, ElSclDw3_pm = NULL;
  ElResoUp_pm = NULL, ElResoDw_pm = NULL;
  MuIdUp_pm   = NULL, MuIdDw_pm   = NULL;
  MuMsUp_pm   = NULL, MuMsDw_pm   = NULL;
  MuSclUp_pm  = NULL, MuSclDw_pm  = NULL;

  ElSclUp1 = new TH1F("ElSclUp1","ElSclUp1",15,115,130);
  ElSclUp2 = new TH1F("ElSclUp2","ElSclUp2",15,115,130);
  ElSclUp3 = new TH1F("ElSclUp3","ElSclUp3",15,115,130);
  ElResoUp = new TH1F("ElResoUp","ElResoUp",15,115,130);
  MuIdUp   = new TH1F("MuIdUp"  ,"MuIdUp"  ,15,115,130);
  MuMsUp   = new TH1F("MuMsUp"  ,"MuMsUp"  ,15,115,130);
  MuSclUp  = new TH1F("MuSclUp" ,"MuSclUp" ,15,115,130);

  ElSclDw1 = new TH1F("ElSclDw1","ElSclDw1",15,115,130);
  ElSclDw2 = new TH1F("ElSclDw2","ElSclDw2",15,115,130);
  ElSclDw3 = new TH1F("ElSclDw3","ElSclDw3",15,115,130);
  ElResoDw = new TH1F("ElResoDw","ElResoDw",15,115,130);
  MuIdDw   = new TH1F("MuIdDw"  ,"MuIdDw"  ,15,115,130);
  MuMsDw   = new TH1F("MuMsDw"  ,"MuMsDw"  ,15,115,130);
  MuSclDw  = new TH1F("MuSclDw" ,"MuSclDw" ,15,115,130);

}

void DefineCategories(bool doFiducial){

  if(doFiducial){
    m_chans.push_back( "4mu"   );
    m_chans.push_back( "4e"    );
    m_chans.push_back( "2mu2e" );
    m_chans.push_back( "2e2mu" );
    m_chans.push_back( "4l"    );
  }
  else{
    m_vars.push_back( std::make_pair("pt"    , 10)  );
    m_vars.push_back( std::make_pair("y"     , 7)   );
    m_vars.push_back( std::make_pair("cts"   , 8)   );
    m_vars.push_back( std::make_pair("ljpt"  , 5)   );
    m_vars.push_back( std::make_pair("mjj"   , 2)   );
    m_vars.push_back( std::make_pair("etajj" , 2)   );
    m_vars.push_back( std::make_pair("phijj" , 2)   );
    m_vars.push_back( std::make_pair("njet"  , 4)   );
    m_vars.push_back( std::make_pair("njetv2", 2)   );
    m_vars.push_back( std::make_pair("njetv3", 3)   );
    m_vars.push_back( std::make_pair("nbjet" , 2)   );
    m_vars.push_back( std::make_pair("ptpt"  , 11)  );
  }
  
}

void ProcessFiducial(){

  if(m_debug)
    std::cout << "<ShapeSysVar()>:: Processing Fiducial case" << std::endl;
  
  m_In = NULL;
  /* loop on channels */
  for(uint v=0; v<m_chans.size(); v++){

    if(m_debug)
      std::cout << "<ShapeSysVar()>:: Processing Channel = "
		<< m_chans.at(v) << std::endl;

    /* loop on production modes */
    for(uint i=0; i<m_prodMode.size(); i++){
      
      if(m_prodMode.at(i)=="ggH")
	m_In = new TFile( (m_Dir+"/outputs_ggF.root").c_str() );
      else
	m_In = new TFile( (m_Dir+"/outputs_"+m_prodMode.at(i)+".root").c_str() );

      ElSclUp1_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_ALLCORR-"+m_chans.at(v)+"_13TeV-up").c_str() );
      ElSclUp2_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_E4SCINTILLATOR-"+m_chans.at(v)+"_13TeV-up").c_str() );
      ElSclUp3_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE-"+m_chans.at(v)+"_13TeV-up").c_str() );
      ElResoUp_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_RESOLUTION_ALL-"+m_chans.at(v)+"_13TeV-up").c_str() );
      MuMsUp_pm   = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_MS-"+m_chans.at(v)+"_13TeV-up").c_str() );
      MuIdUp_pm   = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_ID-"+m_chans.at(v)+"_13TeV-up").c_str() );
      MuSclUp_pm  = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_SCALE-"+m_chans.at(v)+"_13TeV-up").c_str() );
      
      ElSclDw1_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_ALLCORR-"+m_chans.at(v)+"_13TeV-down").c_str() );
      ElSclDw2_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_E4SCINTILLATOR-"+m_chans.at(v)+"_13TeV-down").c_str() );
      ElSclDw3_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE-"+m_chans.at(v)+"_13TeV-down").c_str() );
      ElResoDw_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_RESOLUTION_ALL-"+m_chans.at(v)+"_13TeV-down").c_str() );
      MuMsDw_pm   = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_MS-"+m_chans.at(v)+"_13TeV-down").c_str() );
      MuIdDw_pm   = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_ID-"+m_chans.at(v)+"_13TeV-down").c_str() );
      MuSclDw_pm  = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_SCALE-"+m_chans.at(v)+"_13TeV-down").c_str() );
      
      RebinHistos();
      MergeHistos();

      if(m_debug)
	std::cout << "<ShapeSysVar>:: Cleaning objs for prodMode = "
		  << m_prodMode.at(i) << std::endl;

      /* clean histograms and file */
      CleanProdModeHistos();
    }
    
    m_Out->cd();
    std::string chName = "";
    if(m_chans.at(v)=="4l") chName = "incl";
    else                    chName = m_chans.at(v);
    
    ElSclUp1 ->Write( ("hm_"+chName+"_AllSig_ATLAS_EG_SCALE_ALLCORR_Up").c_str() );
    ElSclUp2 ->Write( ("hm_"+chName+"_AllSig_ATLAS_EG_SCALE_E4SCINTILLATOR_Up").c_str() );
    ElSclUp3 ->Write( ("hm_"+chName+"_AllSig_ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE_Up").c_str() );
    ElResoUp ->Write( ("hm_"+chName+"_AllSig_ATLAS_EG_RESOLUTION_ALL_Up").c_str() );
    MuMsUp   ->Write( ("hm_"+chName+"_AllSig_ATLAS_MUON_MS_Up").c_str() );
    MuIdUp   ->Write( ("hm_"+chName+"_AllSig_ATLAS_MUON_ID_Up").c_str() );
    MuSclUp  ->Write( ("hm_"+chName+"_AllSig_ATLAS_MUON_SCALE_Up").c_str() );
    
    ElSclDw1 ->Write( ("hm_"+chName+"_AllSig_ATLAS_EG_SCALE_ALLCORR_Down").c_str() );
    ElSclDw2 ->Write( ("hm_"+chName+"_AllSig_ATLAS_EG_SCALE_E4SCINTILLATOR_Down").c_str() );
    ElSclDw3 ->Write( ("hm_"+chName+"_AllSig_ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE_Down").c_str() );
    ElResoDw ->Write( ("hm_"+chName+"_AllSig_ATLAS_EG_RESOLUTION_ALL_Down").c_str() );
    MuMsDw   ->Write( ("hm_"+chName+"_AllSig_ATLAS_MUON_MS_Down").c_str() );
    MuIdDw   ->Write( ("hm_"+chName+"_AllSig_ATLAS_MUON_ID_Down").c_str() );
    MuSclDw  ->Write( ("hm_"+chName+"_AllSig_ATLAS_MUON_SCALE_Down").c_str() );
    
    CleanMergedHistos();
  }
  if(m_debug) std::cout << " " << std::endl;
  
}

void ProcessDifferential(){

  if(m_debug)
    std::cout << "<ShapeSysVar()>:: Processing Differential case" << std::endl;
  
  m_In = NULL;
  /* loop on variables */
  for(uint v=0; v<m_vars.size(); v++){

    if(m_debug)
      std::cout << "<ShapeSysVar()>:: Processing Variable = "
		<< m_vars.at(v).first << std::endl;

    /* loop on var bins */
    for(int b=0; b<m_vars.at(v).second; b++){
      if(m_debug)
	std::cout << "<ShapeSysVar()>:: Processing Variable bin = "
		  << b << " -> string = " << std::to_string(b)
		  << " m_vars.at(v).second = " << m_vars.at(v).second << std::endl;
      
      /* loop on production modes */
      for(uint i=0; i<m_prodMode.size(); i++){
	
	if(m_prodMode.at(i)=="ggH")
	  m_In = new TFile( (m_Dir+m_vars.at(v).first+"/outputs_ggF.root").c_str() );
	else
	  m_In = new TFile( (m_Dir+m_vars.at(v).first+"/outputs_"+m_prodMode.at(i)+".root").c_str() );

	ElSclUp1_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_ALLCORR-bin"+std::to_string(b)+"-up").c_str() );
	ElSclUp2_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_E4SCINTILLATOR-bin"+std::to_string(b)+"-up").c_str() );
	ElSclUp3_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE-bin"+std::to_string(b)+"-up").c_str() );
	ElResoUp_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_RESOLUTION_ALL-bin"+std::to_string(b)+"-up").c_str() );
	MuMsUp_pm   = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_MS-bin"+std::to_string(b)+"-up").c_str() );
	MuIdUp_pm   = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_ID-bin"+std::to_string(b)+"-up").c_str() );
	MuSclUp_pm  = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_SCALE-bin"+std::to_string(b)+"-up").c_str() );

	ElSclDw1_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_ALLCORR-bin"+std::to_string(b)+"-down").c_str() );
	ElSclDw2_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_E4SCINTILLATOR-bin"+std::to_string(b)+"-down").c_str() );
	ElSclDw3_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE-bin"+std::to_string(b)+"-down").c_str() );
	ElResoDw_pm = (TH1F*)m_In->Get( ("m4l-ATLAS_EG_RESOLUTION_ALL-bin"+std::to_string(b)+"-down").c_str() );
	MuMsDw_pm   = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_MS-bin"+std::to_string(b)+"-down").c_str() );
	MuIdDw_pm   = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_ID-bin"+std::to_string(b)+"-down").c_str() );
	MuSclDw_pm  = (TH1F*)m_In->Get( ("m4l-ATLAS_MUON_SCALE-bin"+std::to_string(b)+"-down").c_str() );

	RebinHistos();
	MergeHistos();

	if(m_debug)
	  std::cout << "<ShapeSysVar>:: Cleaning objs for prodMode = "
		    << m_prodMode.at(i) << std::endl;
	
	/* clean histograms and file */
	CleanProdModeHistos();
	
      }

      m_Out->cd();
      ElSclUp1 ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_EG_SCALE_ALLCORR_Up").c_str() );
      ElSclUp2 ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_EG_SCALE_E4SCINTILLATOR_Up").c_str() );
      ElSclUp3 ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE_Up").c_str() );
      ElResoUp ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_EG_RESOLUTION_ALL_Up").c_str() );
      MuMsUp   ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_MUON_MS_Up").c_str() );
      MuIdUp   ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_MUON_ID_Up").c_str() );
      MuSclUp  ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_MUON_SCALE_Up").c_str() );
      
      ElSclDw1 ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_EG_SCALE_ALLCORR_Down").c_str() );
      ElSclDw2 ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_EG_SCALE_E4SCINTILLATOR_Down").c_str() );
      ElSclDw3 ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE_Down").c_str() );
      ElResoDw ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_EG_RESOLUTION_ALL_Down").c_str() );
      MuMsDw   ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_MUON_MS_Down").c_str() );
      MuIdDw   ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_MUON_ID_Down").c_str() );
      MuSclDw  ->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_MUON_SCALE_Down").c_str() );
      
      CleanMergedHistos();
      
    }
    if(m_debug) std::cout << " " << std::endl;
  }
  
}

void AddFidMassShifts(){

  if(m_debug)
    std::cout << "<ShapeSysVar()>:: Adding Mass Shifts for Fiducial case" << std::endl;

  /* loop on shifts */
  for(uint s=0; s<m_shifts.size(); s++){

    if(m_debug)
      std::cout << "<ShapeSysVar()>:: Processing Mass " << m_shifts.at(s).first << std::endl;

    m_In = new TFile( ("../varsDistro/XsecInputs_15bin_"+m_shifts.at(s).first+".root").c_str() );

    /* loop on channels */
    for(uint c=0; c<m_chans.size(); c++){
      
      if(m_debug)
	std::cout << "<ShapeSysVar()>:: Processing Channel = "
		  << m_chans.at(c) << std::endl;
      
      std::string chName = "";
      if(m_chans.at(c)=="4l") chName="incl";
      else                    chName=m_chans.at(c);
      
      MassShift = (TH1F*)m_In->Get( ("hm_"+chName+"_AllSig").c_str() );
      m_Out->cd();
      MassShift->Write( ("hm_"+chName+"_AllSig_ATLAS_HiggsMassVariation_"+m_shifts.at(s).second).c_str() );
      MassShift->Delete();
	
    }
    
    m_In->Close();
  }
  
}

void AddDiffMassShifts(){

  if(m_debug)
    std::cout << "<ShapeSysVar()>:: Adding Mass Shifts for Differential case" << std::endl;

  /* loop on shifts */
  for(uint s=0; s<m_shifts.size(); s++){

     if(m_debug)
      std::cout << "<ShapeSysVar()>:: Processing Mass " << m_shifts.at(s).first << std::endl;

    m_In = new TFile( ("../varsDistro/XsecInputs_15bin_"+m_shifts.at(s).first+".root").c_str() );

    /* loop on variables */
    for(uint v=0; v<m_vars.size(); v++){

      if(m_debug)
	std::cout << "<ShapeSysVar()>:: Processing Variable = "
		  << m_vars.at(v).first << std::endl;

      /* loop on var bins */
      for(int b=0; b<m_vars.at(v).second; b++){

	if(m_debug)
	  std::cout << "<ShapeSysVar()>:: Processing Variable bin = "
		    << b << " -> string = " << std::to_string(b)
		    << " m_vars.at(v).second = " << m_vars.at(v).second << std::endl;

	MassShift = (TH1F*)m_In->Get( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig").c_str() );
	m_Out->cd();
	MassShift->Write( ("hm_"+m_vars.at(v).first+"bin"+std::to_string(b)+"_incl_AllSig_ATLAS_HiggsMassVariation_"+m_shifts.at(s).second).c_str() );
	MassShift->Delete();
	
      }
      
    }
    
    m_In->Close();
  }
  
}

void RebinHistos(){

  ElSclUp1_pm->Rebin(2);
  ElSclUp2_pm->Rebin(2);
  ElSclUp3_pm->Rebin(2);
  ElResoUp_pm->Rebin(2);
  MuMsUp_pm  ->Rebin(2);
  MuIdUp_pm  ->Rebin(2);
  MuSclUp_pm ->Rebin(2);
  
  ElSclDw1_pm->Rebin(2);
  ElSclDw2_pm->Rebin(2);
  ElSclDw3_pm->Rebin(2);
  ElResoDw_pm->Rebin(2);
  MuMsDw_pm  ->Rebin(2);
  MuIdDw_pm  ->Rebin(2);
  MuSclDw_pm ->Rebin(2);
  
}

void MergeHistos(){

  ElSclUp1 ->Add( ElSclUp1_pm );
  ElSclUp2 ->Add( ElSclUp2_pm );
  ElSclUp3 ->Add( ElSclUp3_pm );
  ElResoUp ->Add( ElResoUp_pm );
  MuMsUp   ->Add( MuMsUp_pm   );
  MuIdUp   ->Add( MuIdUp_pm   );
  MuSclUp  ->Add( MuSclUp_pm  );
  
  ElSclDw1 ->Add( ElSclDw1_pm );
  ElSclDw2 ->Add( ElSclDw2_pm );
  ElSclDw3 ->Add( ElSclDw3_pm );
  ElResoDw ->Add( ElResoDw_pm );
  MuMsDw   ->Add( MuMsDw_pm   );
  MuIdDw   ->Add( MuIdDw_pm   );
  MuSclDw  ->Add( MuSclDw_pm  );

}

void CleanProdModeHistos(){

  ElSclUp1_pm->Delete();
  ElSclUp2_pm->Delete();
  ElSclUp3_pm->Delete();
  ElResoUp_pm->Delete();
  MuMsUp_pm  ->Delete();
  MuIdUp_pm  ->Delete();
  MuSclUp_pm ->Delete();
  
  ElSclDw1_pm->Delete();
  ElSclDw2_pm->Delete();
  ElSclDw3_pm->Delete();
  ElResoDw_pm->Delete();
  MuMsDw_pm  ->Delete();
  MuIdDw_pm  ->Delete();
  MuSclDw_pm ->Delete();
  
  m_In->Close();
  
}

void CleanMergedHistos(){

  ElSclUp1->Reset();
  ElSclUp2->Reset();
  ElSclUp3->Reset();
  ElResoUp->Reset();
  MuIdUp  ->Reset();
  MuMsUp  ->Reset();
  MuSclUp ->Reset();
  
  ElSclDw1->Reset();
  ElSclDw2->Reset();
  ElSclDw3->Reset();
  ElResoDw->Reset();
  MuIdDw  ->Reset();
  MuMsDw  ->Reset();
  MuSclDw ->Reset();
  
}
