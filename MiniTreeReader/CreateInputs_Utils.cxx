#include "CreateInputs.h"
#include <TChainElement.h>

void CreateInputs::SetMCtypes(){

  PRINT_DEBUG("<CreateInputs::SetMCtypes()>:: setting MC versions ... ");

  FillMcVersionsMap();
  if(m_mcVers==MCtype::All && m_Process!=Process::Zjets && m_Process!=Process::redBkg){
    for(auto& x: m_mcTypeMap){
      if(m_SystNum==Syst::SignalShowerHerwigSystematics){
	if(x.first==MCtype::mc16e)
	  m_mcType.push_back( x.first );
      }
      else{
	if(x.first!=MCtype::mc15c && x.first!=MCtype::All)
	  m_mcType.push_back( x.first );
      }
    }
  }
  else{
    m_mcType.push_back( m_mcVers );
  }
  
}

void CreateInputs::DetectHostname(){

  PRINT_DEBUG("<CreateInputs::DetectHostName()>:: detecting machine name ... ");

  struct utsname sysinfo;
  uname(&sysinfo);
  std::string hostname = sysinfo.nodename;
  if( hostname.find("lxplus")!=std::string::npos ||
      hostname.find("Dell")  !=std::string::npos ||
      hostname.find("gra")   !=std::string::npos )  m_isLocal = false;
  if( hostname.find("Dell")  !=std::string::npos )  m_isDell  = true;
  if( hostname.find("gra")   !=std::string::npos )  m_isCedar = true;

  PRINT_DEBUG( "                                   hostname = "+hostname+" isLocal = "+
	       std::to_string(m_isLocal)+", m_isDell = "+std::to_string(m_isDell)+
	       ", m_isCedar = "+std::to_string(m_isCedar) );
  
}

void CreateInputs::SetDirPrefix(){

  PRINT_DEBUG("<CreateInputs::SetDirPrefix()>:: setting directories prefix path ... ");

  m_Prefix   = "", m_AltPrefix = "";
  std::string Prod = "Prod_v20Fix/";
  if(m_isLocal){
    m_Prefix    = "../MC_Inputs/";
    m_AltPrefix = "../MC_Inputs/";
  }
  else if(m_isDell){
    m_Prefix    = "/mnt/DataHD/minitree/"+Prod;
    m_AltPrefix = "/mnt/DataHD/minitree/"+Prod;
  }
  else if(m_isCedar){
    m_Prefix    = "/home/sabidi/scratch/"+Prod;
    m_AltPrefix = "/home/sabidi/scratch/"+Prod;
  }
  else{
    m_Prefix    = "/eos/atlas/atlascerngroupdisk/phys-higgs/HSG2/H4l/2018/MiniTrees/"+Prod;
    m_AltPrefix = "/afs/cern.ch/atlas/groups/HSG2/H4l/run2/2016/MiniTrees/Prod_v12/";
    if(m_Process!=Process::data){ m_AltPrefix += "mc";   }
  }
  PRINT_DEBUG("<CreatInputs::SetDirPrefix()>:: Prefix Path = "+m_Prefix);
  
}

void CreateInputs::SetChains(int systNum){
  
  PRINT_DEBUG("<CreateInputs::SetChain()>:: setting chains for Process "+m_ProcStr+" ... ");
  
  std::string rcDir   = "";
  std::string thDir   = "";
  std::string sysPath = "";
  std::string thName  = "mc15";
  std::string rcName  = "mc15";
  if(systNum==Syst::NOMINAL)                            sysPath = "Nominal/";
  else if( (systNum>=Syst::SignalComposition_ggHbbH &&
	    systNum<=Syst::SignalComposition_ttHtH+1)
	   || systNum==Syst::SignalMassShift
	   || systNum==Syst::SignalMassShift+1
	   || (systNum>=Syst::VAR_TH_Shower_Herwig_Nominal &&
	       systNum<=Syst::VAR_TH_Shower_Herwig_ttHtH)
	   || (systNum>=Syst::ZJET_stat_2l2e &&
	       systNum<=Syst::ZJET_syst_2l2mu+1)  )     sysPath = "Nominal/";
  else                                                  sysPath = "Systematics/";
  
  if( (systNum>Syst::NOMINAL && systNum<=Syst::PRW_DATASF+1)                                        ||
      (systNum>=Syst::VAR_TH_muR0p5_muF0p5_VBF && systNum<=Syst::VAR_TH_PDF_Nominal)                ||
      (systNum>=Syst::VAR_TH_Var3c && systNum<=Syst::VAR_TH_isrmuRfac_2p0_fsrmuRfac_2p0)            ||
      (systNum>=Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261000 && systNum<=Syst::VAR_TH_qqZZ_Sherpa_CSSKIN)  ){
    sysPath += "NormSystematic";
  }
  else if(systNum>=Syst::EG_RESOLUTION_ALL && systNum<=Syst:: MUON_SCALE+1){
    if(systNum>=Syst::JET_Flavor_Composition_ggHbbH && systNum<=Syst::JET_Flavor_Composition_ZZ+1){
      if(systNum%2==0) sysPath += "JET_Flavor_Composition__1up";
      else             sysPath += "JET_Flavor_Composition__1down";
    }
    else if(systNum>=Syst::JET_Flavor_Response_ggHbbH && systNum<=Syst::JET_Flavor_Response_ZZ+1){
      if(systNum%2==0) sysPath += "JET_Flavor_Response__1up";
      else             sysPath += "JET_Flavor_Response__1down";
    }
    else
      sysPath += m_SysMap[systNum];
  }
  
  for(uint m=0; m<m_mcType.size(); m++){

    if(m_mcType[m]==MCtype::mc15c){
      rcDir = m_AltPrefix;
      if(m_isLocal || m_isDell) rcDir += m_mcTypeMap[MCtype::mc15c];
      rcDir += "/"+sysPath;
      thDir = m_Prefix+m_mcTypeMap[MCtype::mc16a]+"/FidTheory";
    }
    else{
      rcDir = m_Prefix+m_mcTypeMap[m_mcType[m]]+"/"+sysPath;
      thDir = m_Prefix+m_mcTypeMap[m_mcType[m]]+"/FidTheory";
    }
    if(m_mcType[m]>MCtype::mc15c){
      rcName = "mc16"; thName = "mc16";
    }
    
    PRINT_DEBUG("                             mcVersion = "+std::to_string(m_mcType[m])+
		" ("+m_mcTypeMap[m_mcType[m]]+")");
    PRINT_DEBUG("                             rcDir = "+rcDir);
    PRINT_DEBUG("                             thDir = "+thDir);

    switch(m_Process){
    case Process::ggHbbH:
      AddFilesToChain( Process::ggH,GetRecoDir(Process::ggH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::ggH,systNum) );
      AddFilesToChain( Process::bbH,GetRecoDir(Process::bbH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::bbH,systNum) );
      break;
    case Process::VH:
      AddFilesToChain( Process::WH,GetRecoDir(Process::WH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::WH,systNum) );
      AddFilesToChain( Process::ZH,GetRecoDir(Process::ZH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::ZH,systNum) );
      break;
    case Process::ttH:
      AddFilesToChain( Process::ttH ,GetRecoDir(Process::ttH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::ttH,systNum) );
      AddFilesToChain( Process::tHqb,GetRecoDir(Process::tHqb,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::tHqb,systNum) );
      AddFilesToChain( Process::tWH ,GetRecoDir(Process::tWH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::tWH,systNum) );
      break;
    case Process::Signal:
      AddFilesToChain( Process::ggH ,GetRecoDir(Process::ggH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::ggH,systNum) );
      AddFilesToChain( Process::VBF ,GetRecoDir(Process::VBF,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::VBF,systNum) );
      AddFilesToChain( Process::WH  ,GetRecoDir(Process::WH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::WH,systNum) );
      AddFilesToChain( Process::ZH  ,GetRecoDir(Process::ZH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::ZH,systNum) );
      AddFilesToChain( Process::ttH ,GetRecoDir(Process::ttH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::ttH,systNum) );
      AddFilesToChain( Process::tHqb,GetRecoDir(Process::tHqb,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::tHqb,systNum) );
      AddFilesToChain( Process::tWH ,GetRecoDir(Process::tWH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::tWH,systNum) );
      AddFilesToChain( Process::bbH ,GetRecoDir(Process::bbH,systNum,rcDir),
		       rcName,m_mcType[m],thDir,thName,
		       UseHerwig(Process::bbH,systNum) );
      break;
    case Process::AllZZ:
      AddFilesToChain(Process::qqZZ,GetRecoDir(Process::qqZZ,systNum,rcDir),
		      rcName,m_mcType[m],thDir,thName);
      AddFilesToChain(Process::ggZZ,GetRecoDir(Process::ggZZ,systNum,rcDir),
		      rcName,m_mcType[m],thDir,thName);
      break;
    case Process::MultiBoson:
      AddFilesToChain(Process::MB  ,GetRecoDir(Process::MB,systNum,rcDir),
		      rcName,m_mcType[m],thDir,thName);
      AddFilesToChain(Process::ZZEW,GetRecoDir(Process::ZZEW,systNum,rcDir),
		      rcName,m_mcType[m],thDir,thName);
      break;
    default:
      bool isPw = false;
      if(systNum==Syst::VAR_TH_qqZZ_Generator_Powheg) isPw = true;
      AddFilesToChain(m_Process,GetRecoDir(m_Process,systNum,rcDir),
		      rcName,m_mcType[m],thDir,thName,false,isPw);
    }
    
  }
  
  if(m_debug){
    PrintChainContent("reco", m_chain);
    if(m_useTruth)
      PrintChainContent("truth", m_thchain);
  }
  
}

void CreateInputs::AddFilesToChain(int proc  , std::string rcDir, std::string rcName,
				   int mcType, std::string thDir, std::string thName,
				   bool isHw, bool isPw){
  
  switch(proc){

  case Process::ggH:
    if(isHw)
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346446.PhH7EG_H7UE_NNLOPS_nnlo_30_ggH125_ZZ4l_noTau.root").c_str() );
    else
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root").c_str() );
    
    if(m_useTruth){
      if(isHw)
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.346446.PhH7EG_H7UE_NNLOPS_nnlo_30_ggH125_ZZ4l_noTau.root").c_str() );
      else
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l.root").c_str() );
    }
    break;
  case Process::VBF:
    if(isHw)
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346447.PhH7EG_H7UE_NNPDF30_VBFH125_ZZ4lep_noTau.root").c_str() );
    else
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346228.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root").c_str() );
    
    if(m_useTruth){
      if(isHw)
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.346447.PhH7EG_H7UE_NNPDF30_VBFH125_ZZ4lep_noTau.root").c_str() );
      else
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.346228.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau.root").c_str() );
    }
    break;
  case Process::WH:
    if(isHw){
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346449.PhH7EG_H7UE_NNPDF30_WpH125J_Wincl_MINLO.root").c_str() );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346450.PhH7EG_H7UE_NNPDF30_WmH125J_Wincl_MINLO.root").c_str() );
    }
    else{
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root").c_str() );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root").c_str() );
    }
    
    if(m_useTruth){
      if(isHw){
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.346449.PhH7EG_H7UE_NNPDF30_WpH125J_Wincl_MINLO.root").c_str() );
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.346450.PhH7EG_H7UE_NNPDF30_WmH125J_Wincl_MINLO.root").c_str() );
      }
      else{
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO.root").c_str() );
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO.root").c_str() );
      }
    }
    break;
  case Process::ZH:
    if(isHw){
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346448.PhH7EG_H7UE_NNPDF30_ZH125J_Zincl_MINLO.root").c_str() );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346451.PhH7EG_H7UE_NNPDF3_ggZH125_ZZ4lepZinc.root").c_str() );
    }
    else{
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root").c_str() );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345066.PowhegPythia8EvtGen_NNPDF3_AZNLO_ggZH125_ZZ4lepZinc.root").c_str()  );
    }
    
    if(m_useTruth){
      if(isHw){
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.346448.PhH7EG_H7UE_NNPDF30_ZH125J_Zincl_MINLO.root").c_str() );
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.346451.PhH7EG_H7UE_NNPDF3_ggZH125_ZZ4lepZinc.root").c_str() );
      }
      else{
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO.root").c_str() );
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.345066.PowhegPythia8EvtGen_NNPDF3_AZNLO_ggZH125_ZZ4lepZinc.root").c_str()  );
      }
    }
    break;
  case Process::ttH:
    if(mcType==MCtype::mc15c){
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l.root").c_str() );
    }
    else{
      if(isHw){
	m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346452.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_allhad_noTau.root").c_str()  );
	m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346453.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_semilep_noTau.root").c_str() );
	m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346454.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_dilep_noTau.root").c_str()   );
      }
      else{
	m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad.root").c_str()     );
	m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep.root").c_str()    );
	m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep.root").c_str()      );
      }
    }
    
    if(m_useTruth){
      if(mcType==MCtype::mc15c){
	m_thchain->Add( (thDir+"/"+thName+"_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l.root").c_str() );
      }
      else{
	if(isHw){
	  m_thchain->Add( (thDir+"/"+thName+"_13TeV.346452.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_allhad_noTau.root").c_str()  );
	  m_thchain->Add( (thDir+"/"+thName+"_13TeV.346453.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_semilep_noTau.root").c_str() );
	  m_thchain->Add( (thDir+"/"+thName+"_13TeV.346454.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_dilep_noTau.root").c_str()   );
	}
	else{
	  m_thchain->Add( (thDir+"/"+thName+"_13TeV.346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad.root").c_str()     );
	  m_thchain->Add( (thDir+"/"+thName+"_13TeV.346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep.root").c_str()    );
	  m_thchain->Add( (thDir+"/"+thName+"_13TeV.346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep.root").c_str()      );
	}
      }
    }
    break;
  case Process::bbH:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau.root").c_str()  );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau.root").c_str() );
    if(m_useTruth){
      m_thchain->Add( (thDir+"/"+thName+"_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau.root").c_str()  );
      m_thchain->Add( (thDir+"/"+thName+"_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau.root").c_str() );
    }
    break;
  case Process::tHqb:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346414.aMcAtNloPythia8EvtGen_tHjb125_4fl_ZZ4l.root").c_str()  );
    if(m_useTruth)
      m_thchain->Add( (thDir+"/"+thName+"_13TeV.346414.aMcAtNloPythia8EvtGen_tHjb125_4fl_ZZ4l.root").c_str() );
    break;
  case Process::tWH:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.346511.aMcAtNloPythia8EvtGen_tWH125_ZZ4l.root").c_str() );
    if(m_useTruth)
      m_thchain->Add( (thDir+"/"+thName+"_13TeV.346511.aMcAtNloPythia8EvtGen_tWH125_ZZ4l.root").c_str() );
    break;
  case Process::qqZZ:
    if(isPw){
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.343232.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_500_13000.root").c_str() );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.342556.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_100_150.root").c_str()   );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.361603.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4.root").c_str()               );
      
    }
    else{
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.364251.Sherpa_222_NNPDF30NNLO_llll_m4l100_300_filt100_150.root").c_str() );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.364252.Sherpa_222_NNPDF30NNLO_llll_m4l300.root").c_str()                 );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.364250.Sherpa_222_NNPDF30NNLO_llll.root").c_str()                        );
    }
    break;
  case Process::ggZZ:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345708.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_0M4l130.root").c_str() );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345709.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_130M4l.root").c_str()  );
    break;
  case Process::ZZEW:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs_AFii_.root").c_str() );
    break;
  case Process::MB:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6.root").c_str()                    );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.364245.Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6.root").c_str()                    );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.364247.Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6.root").c_str()                    );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.364248.Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6.root").c_str()                    );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345937.aMcAtNloPy8EG_MEN30NLO_A14N23LO_ttee_m4l100_150_mll_3l.root").c_str() );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee.root").c_str()           );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345938.aMcAtNloPy8EG_MEN30NLO_A14N23LO_ttmm_m4l100_150_mll_3l.root").c_str() );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu.root").c_str()         );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.345939.aMcAtNloPy8EG_MEN30NLO_A14N23LO_ttW_m4l100_150_mll_3l.root").c_str()  );
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.410155.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW.root").c_str()            );
    break;
  case Process::MG5:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344158.aMcAtNloPythia8EvtGen_A14NNPDF23LO_ppx0_FxFx_Np012_SM.root").c_str() );
    if(m_useTruth)
       m_thchain->Add( (thDir+"/"+thName+"_13TeV.344158.aMcAtNloPythia8EvtGen_A14NNPDF23LO_ppx0_FxFx_Np012_SM.root").c_str() );
    break;
  case Process::MG5KHvv:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344160.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kHvv6_cosa1p0.root").c_str() );
    break;
  case Process::MG5KAvv:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344163.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAvv6_cosa0p707.root").c_str() );
    break;
  case Process::MG5KAgg:
    m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344167.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAgg0p5_cosa0p707.root").c_str() );
    break;
  case Process::Zjets:
    if( (m_Min==115.0 && m_Max==130.0) || (m_Min==105.0 && m_Max==160.0) ){
      m_In = new TFile( (m_Prefix+"/backgroundResults/allShapes.root").c_str() );
    }
    else{
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344295.Sherpa_NNPDF30NNLO_Zee_4lMassFilter40GeV8GeV.root").c_str()                );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344296.Sherpa_NNPDF30NNLO_Zmumu_4lMassFilter40GeV8GeV.root").c_str()              );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344297.Sherpa_NNPDF30NNLO_Zee_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root").c_str()   );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.344298.Sherpa_NNPDF30NNLO_Zmumu_3lPtFilter4GeV_4lMassVeto40GeV8GeV.root").c_str() );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.root").c_str()         );
      m_chain->Add( (rcDir+"/"+rcName+"_13TeV.410009.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_dil.root").c_str()               );
    }
    break;
  case Process::redBkg:
    m_In = new TFile( m_Out->GetName() );
    break;
  case Process::data:
    if(mcType==MCtype::mc15c)      m_chain->Add( (m_AltPrefix+"data/Nominal/data_13TeV.root").c_str()  ); 
    else if(mcType==MCtype::mc16a) m_chain->Add( (m_Prefix+"data/Nominal/data1516_13TeV.root").c_str() );
    else if(mcType==MCtype::mc16d) m_chain->Add( (m_Prefix+"data/Nominal/data17_13TeV.root").c_str()   );
    else if(mcType==MCtype::mc16e) m_chain->Add( (m_Prefix+"data/Nominal/data18_13TeV.root").c_str()   );
    break;
  default:
    PRINT_FATAL("<CreateInputs::AddFilesToChain()>:: wrong process selected "+std::to_string(proc)+
		" -> exiting ... ");
    exit(0);
  }
  
}


std::string CreateInputs::DetectSysFamily(){

  PRINT_DEBUG("<CreateInputs::DetectSysFamily()>:: detecting sys family ... ");
  
  std::string name = "";
  switch(m_SystNum){
  case Syst::NormSystematics                  : name = "_NormSystematics"           ; break;
  case Syst::NormPart1Systematics             : name = "_NormPart1Systematics"      ; break;
  case Syst::NormPart2Systematics             : name = "_NormPart2Systematics"      ; break;
  case Syst::ShapeSystematics                 : name = "_ShapeSystematics"          ; break;
  case Syst::ShapePart1Systematics            : name = "_ShapePart1Systematics"     ; break;
  case Syst::ShapePart2Systematics            : name = "_ShapePart2Systematics"     ; break;
  case Syst::ShapePart3Systematics            : name = "_ShapePart3Systematics"     ; break;
  case Syst::ExperimentalSystematics          : name = "_ExpSystematics"            ; break; 
  case Syst::SignalTheorySystematics          : name = "_SigThSystematics"          ; break;
  case Syst::SignalTheoryScaleSystematics     : name = "_SigThScaleSystematics"     ; break;
  case Syst::SignalTheoryScalePart1Systematics: name = "_SigThScalePart1Systematics"; break;
  case Syst::SignalTheoryScalePart2Systematics: name = "_SigThScalePart2Systematics"; break;
  case Syst::SignalTheoryScalePart3Systematics: name = "_SigThScalePart3Systematics"; break;
  case Syst::SignalTheoryPdfPart1Systematics  : name = "_SigThPdfPart1Systematics"  ; break;
  case Syst::SignalTheoryPdfPart2Systematics  : name = "_SigThPdfPart2Systematics"  ; break;
  case Syst::SignalTheoryPdfPart3Systematics  : name = "_SigThPdfPart3Systematics"  ; break;
  case Syst::SignalTheoryPdfPart4Systematics  : name = "_SigThPdfPart4Systematics"  ; break;
  case Syst::SignalTheoryQcdPart1Systematics  : name = "_SigThQcdPart1Systematics"  ; break;
  case Syst::SignalTheoryQcdPart2Systematics  : name = "_SigThQcdPart2Systematics"  ; break;
  case Syst::SignalTheoryQcdPart3Systematics  : name = "_SigThQcdPart3Systematics"  ; break;
  case Syst::ZZTheorySystematics              : name = "_ZZTheorySystematics"       ; break;
  case Syst::ZZTheoryPart1Systematics         : name = "_ZZTheoryPart1Systematics"  ; break;
  case Syst::ZZTheoryPart2Systematics         : name = "_ZZTheoryPart2Systematics"  ; break;
  case Syst::SignalShowerSystematics          : name = "_SigShowerSystematics"      ; break;
  case Syst::SignalShowerPart1Systematics     : name = "_SigShowerPart1Systematics" ; break;
  case Syst::SignalShowerPart2Systematics     : name = "_SigShowerPart2Systematics" ; break;
  case Syst::SignalShowerPart3Systematics     : name = "_SigShowerPart3Systematics" ; break;
  case Syst::SignalShowerHerwigSystematics    : name = "_SigShowerHerwigSystematics"; break;
  case Syst::SignalCompositionSystematics     : name = "_SigCompositionSystematics" ; break;
  case Syst::SignalMassShapeSystematics       : name = "_SigMassShapeSystematics"   ; break;
  case Syst::ZjetsSystematics                 : name = "_ZjetsSystematiscs"         ; break;
  default: name = "_Systematics";
  }
  return name;
  
}

bool CreateInputs::UseSysMassInBins(int systNum){

  PRINT_VERBOSE("<CreateInputs::UseSysMassInBins()>:: checking sys number ... ");
  
  if( (systNum>=Syst::EG_RESOLUTION_ALL               && systNum<=Syst::EG_SCALE_ALL+1)               ||
      (systNum>=Syst::MUON_ID                         && systNum<=Syst::MUON_SCALE+1)                 ||
      (systNum>=Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261000 && systNum<=Syst::VAR_TH_qqZZ_Generator_Powheg) ||
      systNum==Syst::SignalMassShift	              || systNum==Syst::SignalMassShift+1	       )
    return true;
  else
    return false;
  
}

void CreateInputs::DefineOutFile(int systNum){

  PRINT_DEBUG("<CreateInputs::DefineOutFile()>:: defining out root file ... ");

  std::string OutDir = "../varsDistro";
  CheckOutDir(OutDir);
  
  std::string OutName = OutDir+"/";
  if(m_isCouplings){
    OutName += "Couplings";
    if(m_Stage==StxsStage::Stage0)        { OutName += "_Stage0"; }
    else if(m_Stage==StxsStage::Stage1)   { OutName += "_Stage1"; }
    else if(m_Stage==StxsStage::RedStage1){ OutName += "_RedStage1"; }
  }
  else{
    OutName+= "XsecInputs_"+std::to_string(m_Nbins)+"bin";
    if(m_doACRfactor){
      if(m_useMatrix) OutName += "_MatrixARfactors";
      else            OutName += "_ACRfactors";
    }
  }
  if(m_mcVers==MCtype::All) OutName += "_mc16"; 
  else                      OutName += "_"+m_mcTypeMap[m_mcVers]; 
  
  if(m_doSystematics) OutName += DetectSysFamily();
  if(m_doShiftUp)     OutName += "_ShiftUp"    ;
  if(m_doShiftDown)   OutName += "_ShiftDown"  ;
  if(m_isContReg)     OutName += "_ContReg"    ;

  if(m_doSystematics){
    if( m_SystNum==Syst::ZjetsSystematics &&
	(m_Process==Process::MultiBoson || m_Process==Process::redBkg) )
      OutName += "_Zjets";
    else
      OutName += "_"+m_ProcStr;
  }
  OutName += ".root";

  if(m_doSystematics){
    if(systNum==Syst::EL_EFF_ID_CorrUncertaintyNP0               ||
       systNum==Syst::EL_EFF_ID_SIMPLIFIED_UncorrUncertaintyNP16 ||
       systNum==Syst::EG_RESOLUTION_ALL                          ||
       systNum==Syst::JET_JER_DataVsMC                           ||
       systNum==Syst::JET_Flavor_Composition_ggHbbH              ||
       systNum==Syst::VAR_TH_muR0p5_muF0p5_VBF                   ||
       systNum==Syst::VAR_TH_muR0p5_muF0p5_VH                    ||
       systNum==Syst::VAR_TH_muR0p5_muF0p5_ttH                   ||
       systNum==Syst::VAR_TH_pdf_90400                           ||
       systNum==Syst::VAR_TH_pdf_90408                           ||
       systNum==Syst::VAR_TH_pdf_90417                           ||
       systNum==Syst::VAR_TH_pdf_90425                           ||
       systNum==Syst::VAR_TH_ggF_qcd_2017_pTH120                 ||
       systNum==Syst::VAR_TH_qcd_wg1_qm_t                        ||
       systNum==Syst::VAR_TH_QCD_Scale_Nominal_VBF               ||
       systNum==Syst::VAR_TH_Var3c                               ||
       systNum==Syst::VAR_TH_isrmuRfac_0p75_fsrmuRfac_1p0        ||
       systNum==Syst::VAR_TH_isrmuRfac_1p0_fsrmuRfac_1p75        ||
       systNum==Syst::VAR_TH_Shower_Herwig_Nominal               ||
       systNum==Syst::SignalComposition_ggHbbH                   ||
       systNum==Syst::ZJET_stat_2l2e                             ||
       systNum==Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261000            ||
       systNum==Syst::VAR_TH_qqZZ_MUR1_MUF1_PDF261056            ||
       systNum==Syst::SignalMassShift                            ){

      if( m_Process==Process::MultiBoson ||
	  m_Process==Process::redBkg      )
	m_Out = new TFile( OutName.c_str(), "UPDATE" );
      else
	m_Out = new TFile( OutName.c_str(), "RECREATE" );
      
    }
    else{
      m_Out = new TFile( OutName.c_str(), "UPDATE" );
    }
  }
  else{
    if(m_Process==Process::ggH)
      m_Out = new TFile( OutName.c_str(), "RECREATE" );
    else
      m_Out = new TFile( OutName.c_str(), "UPDATE" );
  }
  
  PRINT_DEBUG("                                  OutFile is "+OutName);
  
}

void CreateInputs::LoadSysMap(){

  PRINT_DEBUG("<CreateInputs::LoadSysMap()>:: loading systematics map ... ");

  m_SysMap = MakeSysMap(!m_doSystematics,m_SystNum);

  for(auto& mp: m_SysMap){
    PRINT_VERBOSE("                               Sys number = "+
		  std::to_string(mp.first));
  }
  
}

void CreateInputs::MakeChanMaps(){

  PRINT_DEBUG("<CreateInputs::MakeChanMaps()>:: creating channels maps ... ");

  m_ChMap[Channel::_incl ] = "incl" ;
  m_ChMap[Channel::_4mu  ] = "4mu"  ;
  m_ChMap[Channel::_4e   ] = "4e"   ;
  m_ChMap[Channel::_2mu2e] = "2mu2e";
  m_ChMap[Channel::_2e2mu] = "2e2mu";
  m_ChMap[Channel::_2l2l ] = "2l2l" ;
  m_ChMap[Channel::_4l   ] = "4l"   ;

  m_LbMap[Channel::_incl ] = ""      ;
  m_LbMap[Channel::_4mu  ] = "4#mu"  ;
  m_LbMap[Channel::_4e   ] = "4e"    ;
  m_LbMap[Channel::_2mu2e] = "2#mu2e";
  m_LbMap[Channel::_2e2mu] = "2e2#mu";
  m_LbMap[Channel::_2l2l ] = "2l2l"  ;
  m_LbMap[Channel::_4l   ] = "4l"    ;
  
}

std::string CreateInputs::GetRecoDir(int proc, int systNum, std::string baseDir){

  PRINT_VERBOSE("<CreateInputs::GetRecoDir()>:: defining reco trees directory ... ");

  std::string rcDir = baseDir;
  switch(systNum){
  case Syst::JET_Flavor_Composition_ggHbbH  :
  case Syst::JET_Flavor_Composition_ggHbbH+1:
  case Syst::JET_Flavor_Response_ggHbbH     :
  case Syst::JET_Flavor_Response_ggHbbH+1   :
    if(proc!=Process::ggH && proc!=Process::bbH)
      rcDir += "/../../Nominal";
    break;
  case Syst::JET_Flavor_Composition_VBF  :
  case Syst::JET_Flavor_Composition_VBF+1:
  case Syst::JET_Flavor_Response_VBF     :
  case Syst::JET_Flavor_Response_VBF+1   :
    if(proc!=Process::VBF)
      rcDir += "/../../Nominal";
    break;
  case Syst::JET_Flavor_Composition_VH  :
  case Syst::JET_Flavor_Composition_VH+1:
  case Syst::JET_Flavor_Response_VH     :
  case Syst::JET_Flavor_Response_VH+1   :
    if(proc!=Process::WH && proc!=Process::ZH)
      rcDir += "/../../Nominal";
    break;
  case Syst::JET_Flavor_Composition_ttHtH  :
  case Syst::JET_Flavor_Composition_ttHtH+1:
  case Syst::JET_Flavor_Response_ttHtH     :
  case Syst::JET_Flavor_Response_ttHtH+1   :
    if(proc!=Process::ttH && proc!=Process::tHqb && proc!=Process::tWH)
      rcDir += "/../../Nominal";
    break;
  case Syst::JET_Flavor_Composition_ZZ  :
  case Syst::JET_Flavor_Composition_ZZ+1:
  case Syst::JET_Flavor_Response_ZZ     :
  case Syst::JET_Flavor_Response_ZZ+1   :
    if(proc!=Process::qqZZ && proc!=Process::ggZZ)
      rcDir += "/../../Nominal";
    break;
  case Syst::VAR_TH_qqZZ_Generator_Powheg:
    rcDir += "../Nominal";
    break;
  }

  return rcDir;
  
}

bool CreateInputs::UseHerwig(int proc, int systNum){

  PRINT_VERBOSE("<CreateInputs::UseHerwig()>:: detecting if Herwig has to be used ... ");

  bool isHw = false;
  switch(systNum){
  case Syst::VAR_TH_Shower_Herwig_ggHbbH:
    if(proc==Process::ggH) isHw = true;
    break;
  case Syst::VAR_TH_Shower_Herwig_VBF:
    if(proc==Process::VBF) isHw = true;
    break;
  case Syst::VAR_TH_Shower_Herwig_VH:
    if(proc==Process::WH || proc==Process::ZH) isHw = true;
    break;
  case Syst::VAR_TH_Shower_Herwig_ttHtH:
    if(proc==Process::ttH) isHw = true;
    break;
  }

  return isHw;
  
}
