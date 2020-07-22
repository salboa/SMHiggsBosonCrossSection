#include "WorkSpaceMaker.h"

RooStats::HistFactory::FlexibleInterpVar* WorkSpaceMaker::makeSysBlock(string blockID,
								       int ChNum, int proc, int cat){
  if(m_debug){
    cout<< "<makeSysBlock()>:: creating systematic block" <<endl;
    cout << "blockID: " << blockID << endl;

  }

  vector< double > syslow;
  vector< double > sysup;
  
  RooRealVar *tmp_sys =NULL;
  RooArgList v_sys;
  
  map<string,vector<double> > tmpmap;
  
  
  if (blockID=="block1") tmpmap = m_comSys;
  else if ( m_Fiducial ) tmpmap = (GetSysMap(ChNum-1, proc, 0));
  else tmpmap = (GetSysMap(ChNum, proc, cat));
  
  for( auto& x: tmpmap){
    if ( ( (x.second.at(1) == 1) && (x.second.at(1) == x.second.at(0)) )
        ||
        ( ( abs(x.second.at(1) - 1) < 0.005 ) && ( abs(x.second.at(0) - 1)< 0.005  ) )
        )
      if ( (x.first.find("ATLAS_HiggsMassVariation") ==std::string::npos &&
          x.first.find("ATLAS_EG_SCALE_ALLCORR") ==std::string::npos &&
          x.first.find("ATLAS_EG_SCALE_E4SCINTILLATOR") ==std::string::npos &&
          x.first.find("ATLAS_EG_RESOLUTION_ALL") ==std::string::npos &&
          x.first.find("ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE") ==std::string::npos &&
          x.first.find("ATLAS_MUON_MS") ==std::string::npos &&
          x.first.find("ATLAS_MUON_ID") ==std::string::npos &&
          x.first.find("ATLAS_MUON_SCALE") ==std::string::npos &&
            x.first.find("ATLAS_SignalComposition") ==std::string::npos ) ){
      cout << "\033[1;39m <makeSysBlock()>::  sys up = sys down = 1 skipping sys " << x.first << " cat: "<< cat <<"\033[0m" << endl;
      continue;
    }
    if ( x.first=="" ) continue;


    tmp_sys = new RooRealVar((x.first).c_str(), (x.first).c_str(), 0, -5, 5);// tmp_sys->setConstant(1);
    syslow.push_back( x.second.at(0) );
    sysup.push_back( x.second.at(1) );

    v_sys.add(*tmp_sys);

    cout <<" Systematic = " << x.first << "  DwVal = " << x.second.at(0)
	 << "  UpVal = " << x.second.at(1) << "  Type = " << x.second.at(2)
	 << "  Constr = " << x.second.at(3) << endl;
    if ( x.second.at(3) == 1 ) makeGaussianConstraint(tmp_sys);
    
    if ( m_listNP.find((x.first).c_str()) ) continue;
    m_listNP.add(*tmp_sys);

  }

  m_sysblock = new RooStats::HistFactory::FlexibleInterpVar( ("sysblock"+blockID+"_proc_"+to_string(proc)+"_"+m_Category.at(cat)).c_str(),
							     ("sysblock"+blockID+"_proc_"+to_string(proc)+"_"+m_Category.at(cat)).c_str(),
							     v_sys, 1, syslow, sysup );
  m_sysblock->Print();
  
  return m_sysblock;
  
}

void WorkSpaceMaker::makeGaussianConstraint(RooRealVar* v_sys){
  
  if(m_debug)
    cout << "<makeGaussianConstraint()>:: make Gaussian constraint for systematic " << endl;
  
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
  //m_listpdf_np.Print("v");
  
}

void  WorkSpaceMaker :: FixSysForFit(string which){

  if(m_debug)
    cout << "<FixSysForFit()>:: fixing Systematic category " << which <<
      " when profiling to data" << endl;

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
      if( string(var->GetName()).find("AS_E") != std::string::npos )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="muon" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("MUON") != std::string::npos )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="ZZ" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("qqZZ") != std::string::npos || string(var->GetName()).find("ggZZ") != std::string::npos )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="sig" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("sig") != std::string::npos || string(var->GetName()).find("Sig") != std::string::npos || string(var->GetName()).find("HiggsMassVariation") != std::string::npos  )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="jet" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("_J")!=std::string::npos ||
	  string(var->GetName()).find("_FT")!=std::string::npos )
	m_ws->var(var->GetName())->setConstant(true);
    }
  }
  
  else if( which=="lumi" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("Lumi")!=std::string::npos )
        m_ws->var(var->GetName())->setConstant(true);
    }
  }
  else if( which=="zjet" ){
    it->Reset();
    while( (var = (RooRealVar*)it->Next()) ){
      if( string(var->GetName()).find("ZJET")!=std::string::npos )
        m_ws->var(var->GetName())->setConstant(true);
    }
  }
  
}
