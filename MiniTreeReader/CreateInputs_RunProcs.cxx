#include "CreateInputs.h"
#include <numeric>

void CreateInputs::MakeRedBkg(int sysNum){

  PRINT_DEBUG("<CreateInputs::MakeRedBkg()>:: making redBkg (Z+jets) histograms ... ");

  Double_t Lumi = 0;
  if(m_mcVers==MCtype::All)        Lumi = 36.207705+44.307223+58.450261;
  else if(m_mcVers==MCtype::mc15c) Lumi = 36.1;
  else if(m_mcVers==MCtype::mc16a) Lumi = 36.207705;
  else if(m_mcVers==MCtype::mc16d) Lumi = 44.307223;
  else if(m_mcVers==MCtype::mc16e) Lumi = 58.450261;
  
  m_zjetNameSuffix = "";
  m_zjetYields.clear();
  if(m_Min==105.0 && m_Max==160){          // v19.5    v19_1    v18
    m_zjetYields.push_back( 7.66 / Lumi ); // 6.30445  6.48021  5.03708  //4mu
    m_zjetYields.push_back( 7.76 / Lumi ); // 9.74184 10.1447   8.27707  //4e
    m_zjetYields.push_back( 9.74 / Lumi ); //10.6668  11.10390  8.59477  //2mu2e
    m_zjetYields.push_back( 8.61 / Lumi ); // 7.08536  7.2812   4.12125  //2e2mu
    m_zjetNameSuffix = "_wide";
  }
  else{
    m_zjetYields.push_back( 2.29 / Lumi ); //1.7827    1.85469  1.54449  //4mu
    m_zjetYields.push_back( 2.54 / Lumi ); //3.03351   2.96893  2.5476   //4e
    m_zjetYields.push_back( 3.19 / Lumi ); //3.31717   3.24966  2.64538  //2mu2e
    m_zjetYields.push_back( 2.57 / Lumi ); //2.00383   2.08396  1.26367  //2e2mu
  }

  double yTot = std::accumulate( m_zjetYields.begin(), m_zjetYields.end(), 0.0);
  m_zjetYields.insert(    m_zjetYields.begin(), yTot       ); //incl
  m_zjetYields.push_back( m_zjetYields.at(Channel::_4mu)+
			  m_zjetYields.at(Channel::_4e)    ); //4l
  m_zjetYields.push_back( m_zjetYields.at(Channel::_2e2mu)+
			  m_zjetYields.at(Channel::_2mu2e) ); //2l2l

  Handle2DZjetsPlotsInfo();
  
  for(uint v=0; v<m_diffVars.size(); v++){
    
    int vNum          = GetVariableID( m_diffVars[v] );
    std::string vName = m_diffVars[v];
    
    if(vNum==Variable::ptnjet || vNum==Variable::pty4l){
      Fill2DZjetsPlots( vName );
    }
    else{
      m_llmumu = (TH1D*)m_In->Get( ("h_"+FindZjetVarName(vName)+
				    "_2l2mu"+m_zjetNameSuffix).c_str() );
      
      m_llee   = (TH1D*)m_In->Get( ("h_"+FindZjetVarName(vName)+
				    "_2l2e"+m_zjetNameSuffix).c_str() );

      if(vNum==Variable::m4l){
	FillZjetsPlots( vName );
	if(m_addFineM4l){
	  FillZjetsPlots( vName+"_Ext" );
	}
      }
      else{
	FillZjetsPlots( vName );
      }
      
    }
    MergeAndNormalizeZjetsPlots( vName );
    if(vNum==Variable::m4l && m_addFineM4l) MergeAndNormalizeZjetsPlots( vName+"_Ext" );
    
    if(vNum==Variable::pt0j || vNum==Variable::pt1j || vNum==Variable::pt2j ||
       vNum==Variable::pt3j || vNum==Variable::pt0y || vNum==Variable::pt1y ||
       vNum==Variable::pt2y || vNum==Variable::pt3y  ){
      Normalize2DZjetsPlots( vNum,vName );
    }
    
    if(m_HmapBins.size()!=0 && vNum!=Variable::m4l){

      for(int i=0; i<GetNumberOfBins( vName ); i++){
	
	for(auto& x: m_ChMap){
	  int ch = x.first;
	  m_HmapBins[vName][i].at(ch)->Add( m_Hmap["m4l"].at(ch) );
	  m_HmapBins[vName][i].at(ch)->Scale( m_Hmap[vName].at(ch)->GetBinContent(i+1) /
					      m_HmapBins[vName][i].at(ch)->Integral() );
	}
	
      }
      
    }

    if(m_HmapBinsFine.size()!=0 && vNum!=Variable::m4l){

      for(int i=0; i<GetNumberOfBins( vName ); i++){
	
	for(auto& x: m_ChMap){
	  int ch = x.first;
	  m_HmapBinsFine[vName][i].at(ch)->Add( m_Hmap["m4l_Ext"].at(ch) );
	  m_HmapBinsFine[vName][i].at(ch)->Scale( m_Hmap[vName].at(ch)->GetBinContent(i+1) /
						  m_HmapBinsFine[vName][i].at(ch)->Integral() );
	}
	
      }
      
    }
    
    
    if(m_doSystematics){
      
      for(auto& ch: m_ChMap){
	
	if(ch.first==Channel::_incl || ch.first>Channel::_2e2mu) continue;
	if(vNum==Variable::m4l){
	  m_Hmap[vName].at(ch.first)->Scale( GetZjetsSysImpact(vName,sysNum,ch.first) );
	  if(m_addFineM4l){
	    m_Hmap[vName+"_Ext"].at(ch.first)->Scale( GetZjetsSysImpact(vName,sysNum,ch.first) );
	  }
	}
	else{
	  for(int i=0; i<GetNumberOfBins( vName ); i++){
	    m_Hmap[vName].at(ch.first)->SetBinContent( i+1, (m_Hmap[vName].at(ch.first)->GetBinContent(i+1)*
							     GetZjetsSysImpact(vName,sysNum,ch.first,i+1))  );
	  }
	}
	
      }
      MergeAndNormalizeZjetsPlots(vName,false);
      
    }
    
  }
  m_zjetNames.clear();
  m_zjetStat.clear();
  m_zjetSys.clear();
  
}

double CreateInputs::GetZjetsSysImpact(std::string vName, int sysNum, int channel, int bin){

  PRINT_VERBOSE("<CreateInputs::GetZjetSysImpact()>:: getting Z+jets sys impact for var "+
		vName);

  double m_scl = 1.0;
  
  if(vName=="m4l"){
    switch(sysNum){
    case Syst::ZJET_stat_2l2e:
      switch(channel){
      case Channel::_4e:    m_scl = 1-m_zjetStat.at(Channel::_4e-1)   ; break;
      case Channel::_2mu2e: m_scl = 1-m_zjetStat.at(Channel::_2mu2e-1); break;
      } break;
    case Syst::ZJET_stat_2l2e+1:
      switch(channel){
      case Channel::_4e:    m_scl = 1+m_zjetStat.at(Channel::_4e-1)    ; break;
      case Channel::_2mu2e: m_scl = 1+m_zjetStat.at(Channel::_2mu2e-1) ; break;
      } break;
    case Syst::ZJET_stat_2l2mu:
      switch(channel){
      case Channel::_4mu:   m_scl = 1-m_zjetStat.at(Channel::_4mu-1)   ; break;
      case Channel::_2e2mu: m_scl = 1-m_zjetStat.at(Channel::_2e2mu-1) ; break;
      } break;
    case Syst::ZJET_stat_2l2mu+1:
      switch(channel){
      case Channel::_4mu:   m_scl = 1+m_zjetStat.at(Channel::_4mu-1)   ; break;
      case Channel::_2e2mu: m_scl = 1+m_zjetStat.at(Channel::_2e2mu-1) ; break;
      } break;
    case Syst::ZJET_syst_2l2e:
      switch(channel){
      case Channel::_4e:    m_scl = 1-m_zjetSys.at(Channel::_4e-1)    ; break;
      case Channel::_2mu2e: m_scl = 1-m_zjetSys.at(Channel::_2mu2e-1) ; break;
      } break;
    case Syst::ZJET_syst_2l2e+1:
      switch(channel){
      case Channel::_4e:    m_scl = 1+m_zjetSys.at(Channel::_4e-1)    ; break;
      case Channel::_2mu2e: m_scl = 1+m_zjetSys.at(Channel::_2mu2e-1) ; break;
      } break;
    case Syst::ZJET_syst_2l2mu:
      switch(channel){
      case Channel::_4mu:   m_scl = 1-m_zjetSys.at(Channel::_4mu-1)   ; break;
      case Channel::_2e2mu: m_scl = 1-m_zjetSys.at(Channel::_2e2mu-1) ; break;
      } break;
    case Syst::ZJET_syst_2l2mu+1:
      switch(channel){
      case Channel::_4mu:   m_scl = 1+m_zjetSys.at(Channel::_4mu-1)   ; break;
      case Channel::_2e2mu: m_scl = 1+m_zjetSys.at(Channel::_2e2mu-1) ; break;
      } break;
    }
  }
  else{
    
    std::string lab = "stat";
    if(sysNum==Syst::ZJET_syst_2l2e   || sysNum==Syst::ZJET_syst_2l2mu)   lab = "dn";
    if(sysNum==Syst::ZJET_syst_2l2e+1 || sysNum==Syst::ZJET_syst_2l2mu+1) lab = "up";

    int m_bin = bin;
    std::string m_vName = FindZjetVarName(vName);
    if(vName=="ptnjet" || vName=="pty4l"){
      std::string tmp = "j";
      if(vName=="pty4l") tmp = "y";
      if(bin<GetNumberOfBins("pt0"+tmp)){
	m_bin=bin;
	m_vName=FindZjetVarName("pt0"+tmp);
      }
      else if(bin<(GetNumberOfBins("pt0"+tmp)+GetNumberOfBins("pt1"+tmp))){
	m_bin=bin-GetNumberOfBins("pt0"+tmp);
	m_vName=FindZjetVarName("pt1"+tmp);
      }
      else if(bin<(GetNumberOfBins("pt0"+tmp)+GetNumberOfBins("pt1"+tmp)+
		   GetNumberOfBins("pt2"+tmp))){
	m_bin=bin-(GetNumberOfBins("pt0"+tmp)+GetNumberOfBins("pt1"+tmp));
	m_vName=FindZjetVarName("pt2"+tmp);
      }
      else{
	m_bin=bin-(GetNumberOfBins("pt0"+tmp)+GetNumberOfBins("pt1"+tmp)+
		   GetNumberOfBins("pt2"+tmp));
	m_vName=FindZjetVarName("pt3"+tmp);
      }
    }

    m_llmumu = (TH1D*)m_In->Get( ("h_"+lab+"_"+m_vName+"_2l2mu"+m_zjetNameSuffix).c_str() );
    m_llee   = (TH1D*)m_In->Get( ("h_"+lab+"_"+m_vName+"_2l2e" +m_zjetNameSuffix).c_str() );
    
    switch(sysNum){
    case Syst::ZJET_stat_2l2e  :
    case Syst::ZJET_syst_2l2e  :
      switch(channel){
      case Channel::_4e:    
      case Channel::_2mu2e: m_scl = 1-m_llee->GetBinContent(m_bin); break; 
      default:              m_scl = 1.0;
      } break;
    case Syst::ZJET_stat_2l2e+1:
    case Syst::ZJET_syst_2l2e+1:  
      switch(channel){
      case Channel::_4e:    
      case Channel::_2mu2e: m_scl = 1+m_llee->GetBinContent(m_bin); break; 
      default:              m_scl = 1.0;
      } break;
    case Syst::ZJET_stat_2l2mu  :
    case Syst::ZJET_syst_2l2mu  :
      switch(channel){
      case Channel::_4mu:   
      case Channel::_2e2mu: m_scl = 1-m_llmumu->GetBinContent(m_bin) ; break;
      default:              m_scl = 1.0;
      } break;
    case Syst::ZJET_stat_2l2mu+1:
    case Syst::ZJET_syst_2l2mu+1:  
      switch(channel){
      case Channel::_4mu:   
      case Channel::_2e2mu: m_scl = 1+m_llmumu->GetBinContent(m_bin) ; break;
      default:              m_scl = 1.0;
      } break;
    default:
      m_scl = 1.0;
    }
    m_llmumu->Delete();
    m_llee->Delete();
    
  }
  return m_scl;
  
}

void CreateInputs::MergeRedBkg(std::string sysName){

  PRINT_DEBUG("<CreateInputs::MergeRedBkg()>:: merging redBkg (Z+jets + MultiBoson) histograms ... ");

  std::vector<std::string> names;
  for(uint v=0; v<m_diffVars.size(); v++){
    
    int vNum  = GetVariableID( m_diffVars[v] );
    if(vNum==Variable::m4l){
      names.push_back("hm");
      if(m_addFineM4l) names.push_back("hmFine");
    }
    else{
      names.push_back("h"+GetVariableName(vNum));
    }
    
  }
  if(sysName=="Nominal"){
    for(uint v=0; v<m_diffVars.size(); v++){
      
      int vNum  = GetVariableID( m_diffVars[v] );
      if(vNum==Variable::m4l) continue;
      for(int b=0; b<GetNumberOfBins(m_diffVars[v]); b++){
	names.push_back("hm_"+GetVariableName(vNum)+"bin"+std::to_string(b));
	if(m_addFineM4l)
	  names.push_back("hmFine_"+GetVariableName(vNum)+"bin"+std::to_string(b));
      }
      
    }
  }
  
  std::string prefix = "";
  if(sysName!="Nominal") prefix = sysName+"/";
  TH1D *hInZj=NULL, *hInMb=NULL, *hOut=NULL;
  for(uint i=0; i<names.size(); i++){
    for(auto& x: m_ChMap){
      hInZj = (TH1D*)m_In->Get( (prefix+names[i]+"_"+x.second+"_Zjets").c_str()      );
      hInMb = (TH1D*)m_In->Get( (prefix+names[i]+"_"+x.second+"_MultiBoson").c_str() );
      hOut  = (TH1D*)hInZj->Clone( (names[i]+"_"+x.second+"_redBkg").c_str()  );
      hOut->SetName( (names[i]+"_"+x.second+"_redBkg").c_str() );
      hOut->Add(hInMb);
      m_Out->cd(prefix.c_str());
      hOut->Write( (names[i]+"_"+x.second+"_redBkg").c_str() );
      hInZj->Delete();
      hInMb->Delete();
      hOut->Delete();
    }
  }
  names.clear();
  
}

void CreateInputs::RunProcesses(int sysNum){

  PRINT_DEBUG("<CreateInputs::RunProcesses()>:: Calling Loop on events ... ");

  evt = new EventLoop( m_Process       , sysNum         , m_Process         ,
		       m_mcVers        , m_Min          , m_Max             ,
		       m_doShiftUp     , m_doShiftDown  , m_isContReg       ,
		       m_isCouplings   , m_doACRfactor  , m_Stage           ,
		       m_useMatrix     , m_useRootThMtc , m_EvtList         ,
		       m_split_cF      , m_restrictJets , m_checkDuplicates ,
		       m_procXStoScale , m_valXStoScale , m_debug );

  evt->SetLepWeightUsage(m_removeLepWeight);

  if(m_isCouplings){
    evt->SetHistosM4lBins(m_HmapBins, m_HmapBinsFine);
  }
  else{
    evt->SetHistosMap(m_Hmap);
    if( !m_doSystematics || UseSysMassInBins(sysNum) ){
      evt->SetHistos2DMap(m_Hmap2D);
      evt->SetHistosM4lBins(m_HmapBins, m_HmapBinsFine);
    }
  }
  evt->SetRecoChain(m_chain);
  evt->Loop(true);
  delete evt;
  
}
