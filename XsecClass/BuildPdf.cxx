#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: DoSinglePdf( string process, int chnum, bool isSignal, int cat ){

  int i = cat;
  int channelCatPos = chnum-1;
  if ( m_chSplit == 1 ) channelCatPos = chnum-5;

  if ( m_channels.size() ==1 ) channelCatPos =0;
  string pdf_name = m_Variable+"_"+m_Category.at(cat+(channelCatPos)*int(m_Category.size()/m_channels.size()))+"_"+process;
  PRINT_DEBUG_FUNCTION(" <DoSinglePdf()>:: Making " + GetChannelName(chnum) + " " + process + " Pdf");
  setupRemappedHistoAndVariables(process, chnum, cat);
  RooArgSet m_listSubpdftmp;
  RooArgSet m_listNormpdftmp;
  RooArgList *listtmp = new RooArgList();
  
  if( isSignal ){
    if (!m_do2D)  m_observables.add(*m_x);
    if (m_matrix) m_norm_pdf = SignalNormFactorMatrix(i, chnum, listtmp);
    else          m_norm_pdf = SignalNormFactor(i, chnum, listtmp);
  }
  else
    m_norm_pdf = BackgroundNormFactor(i, chnum, listtmp, m_h_remapped, process);
  
  if ( m_Fiducial ) {
    m_x_hdata = new RooDataHist( ("pdf_h"+pdf_name).c_str(),       //
                                 ("pdf_h"+pdf_name).c_str(),       //  for fiducial XS the entire m4l histogram is needed
				 RooArgList(*m_x), m_h_remapped ); //
 
    m_x_hpdf = new RooHistPdf( ("pdf_"+pdf_name).c_str(),
			       ("pdf_"+pdf_name).c_str(),
			       *m_x, *m_x_hdata );
  }
  else m_x_updf = new RooUniform( ("pdf_"+pdf_name).c_str(),
				  ("pdf_"+pdf_name).c_str(), *m_x );
  
  
  if (m_do2D && !m_Fiducial){
    TH1F *m_h_m4l = NULL;
    
    if ( process == "redBkg" ) {

      m_h_m4l = (TH1F*)m_InFile->Get( ("hm_"+GetChannelName(chnum)+"_"+process).c_str() );
      if ( m_h_m4l == NULL ) {
        PRINT_FATAL(" Histogram: hm_"+GetChannelName(chnum)+"_"+process + " not found, exit!"); 
        exit(0);
      }
      m_h_m4l = remapHisto(m_h_m4l, cat);
      
    }
    else{

      m_h_m4l = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+"bin"+to_string(cat)+"_"+GetChannelName(chnum)+"_"+process).c_str() );
      if(m_h_m4l->Integral()==0 || m_h_m4l->GetEntries()<100){
	string nonEmptyBin = RetrieveLastNonEmptyBin(m_Variable,chnum,process);
	m_h_m4l = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+"bin"+nonEmptyBin+"_"+GetChannelName(chnum)+"_"+process).c_str() );
	
      }
      if ( m_h_m4l == NULL ) {
        PRINT_FATAL(" Histogram: hm_"+m_Variable+"bin"+to_string(cat)+"_"+GetChannelName(chnum)+"_"+process + " not found, exit!");
        exit(0);
      } 
      m_h_m4l = remapHisto(m_h_m4l, cat);
    }
    if(m_redM4lBins){
      if (m_Bstr=="110bin") m_h->Rebin(5);
      else                  m_h->Rebin(3);
    }
    
    PRINT_DEBUG_OBJECT(m_h_m4l);
    m_x_hdata  = new RooDataHist( ("pdf_m4l_h"+pdf_name).c_str(),
                  ("pdfh_m4l_h"+pdf_name).c_str(),
                  RooArgList(*m_m4l), m_h_m4l );

    m_m4l_hpdf = new RooHistPdf( ("pdf_m4l_"+pdf_name).c_str(),
                 ("pdf_m4l_"+pdf_name).c_str(),
                 *m_m4l, *m_x_hdata );

    if (m_addShapeSys && (isSignal || process =="qqZZ") && !(m_Variable =="pt" && cat >7) ){   /// for pt >8 no sys shape no stat 
      RooStarMomentMorph *prodPdf = RetrieveRooStar(m_Category.at(cat+(channelCatPos)*int(m_Category.size()/m_channels.size())), cat, m_m4l_hpdf, m_m4l, process);
      m_listSubpdftmp.add(*prodPdf);
    } 
    else m_listSubpdftmp.add(*m_m4l_hpdf);
    
    m_listNormpdftmp.add(*m_norm_pdf);

  }
  else {

    if (m_addShapeSys && m_Fiducial && (isSignal || process =="qqZZ")  ){
      RooStarMomentMorph *prodPdf = RetrieveRooStar(m_Category.at(cat+(channelCatPos)*int(m_Category.size()/m_channels.size())), cat, m_x_hpdf, m_x, process);
      m_listSubpdftmp.add(*prodPdf);
    } 
    else if (m_Fiducial) m_listSubpdftmp.add(*m_x_hpdf);
    else  m_listSubpdftmp.add(*m_x_updf);
    
    m_listNormpdftmp.add(*m_norm_pdf);
    
  }
  PRINT_DEBUG_OBJECT(&m_listNormpdftmp);
  PRINT_DEBUG_OBJECT(&m_listSubpdftmp);

  if (isSignal) {
    m_pdfcategory.push_back(m_listSubpdftmp); m_Normpdfcategory.push_back(m_listNormpdftmp);
    
  }
  else {
    m_pdfcategory.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size())).add(m_listSubpdftmp);
    m_Normpdfcategory.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size())).add(m_listNormpdftmp);   
  }
  m_list.add(*listtmp);
}

void WorkSpaceMaker :: DoSignalPdf(string process, int chnum, int cat){

  PRINT_DEBUG_FUNCTION(" <DoSignalPdf()>:: Making Signal Pdf");
  DoSinglePdf( process, chnum, true, cat );
  
}

void WorkSpaceMaker :: DoBackgroundPdf(int chnum, bool qqZZ, bool ggZZ, bool redBkg, int cat){

  PRINT_DEBUG_FUNCTION(" <DoBackgroundPdf()>:: Making bkg Pdf");
  if (qqZZ) DoSinglePdf( GetProcessName(Process::qqZZ), chnum, false, cat );
  if (ggZZ) DoSinglePdf( GetProcessName(Process::ggZZ), chnum, false, cat );
  if (redBkg) DoSinglePdf( GetProcessName(Process::redBkg), chnum, false, cat );

  if (!qqZZ && !ggZZ && !redBkg) PRINT_INFO("No background selected!");  
}

void WorkSpaceMaker :: setupRemappedHistoAndVariables(string process, int chnum, int cat){
  
  PRINT_DEBUG_FUNCTION(" <setupRemappedHistoAndVariables()>:: " + GetChannelName(chnum) + " " + to_string(cat) + " " + process + " Pdf");

  m_h = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_"+GetChannelName(chnum)+"_"+process).c_str() );
  if(m_VariableId==Variable::m4l && m_redM4lBins){
    if (m_Bstr=="110bin") m_h->Rebin(5);
    else                  m_h->Rebin(3);
  }
  if ( m_h == NULL ) {
    PRINT_FATAL( " Histogram: h"+m_Variable+"_"+GetChannelName(chnum)+"_"+
		 process + " not found, exit!"); 
    exit(0);
  } 
  m_h_remapped = remapHisto ( m_h, cat ) ;
  if ( m_Fiducial ) {
    m_x = new RooRealVar("x","x", 0, m_Mbins);
    m_x->setBins(m_Mbins);
  }
  else {
    CheckVectorSize(m_h,chnum);
    m_x = new RooRealVar("x","x", 0,1);
    m_x->setBins(1);
    //m_m4l = new RooRealVar("m4l","m4l",m_mMin,m_mMax) ;
    m_m4l = new RooRealVar("m4l","m4l",0,m_Mbins) ;
    m_m4l->setBins(m_Mbins);
  }
  
}

RooHistPdf* WorkSpaceMaker :: RetrieveSysShape (string sys, string catname, int cat, string direction, RooRealVar *m_var, string process_name){

  PRINT_DEBUG_FUNCTION(" <RetrieveSysShape()>:: " + sys + " " + direction);

  //TFile *_file0 = TFile::Open( (m_Dir+"../varsDistro/XsecInputs_15bin_Sys.root").c_str() );
  string dummy="";  

  if (sys.find("ATLAS_Theory_qqZZ_Generator_Powheg")!=std::string::npos) {
    if (m_Fiducial)  dummy = "Theory_qqZZ_Generator_Powheg/h"+m_Variable+"_"+catname+"_"+process_name;
    else  dummy = "Theory_qqZZ_Generator_Powheg/hm_"+m_Variable+catname+"_"+process_name;
  }
  else {
		
    if (m_Fiducial)  dummy = sys+"__1"+direction+"/h"+m_Variable+"_"+catname+"_"+process_name;
    else  dummy = sys+"__1"+direction+"/hm_"+m_Variable+catname+"_"+process_name;
    dummy = dummy.substr(6, dummy.size());
  }


  TH1F *hsys = (TH1F*) m_SysFile->Get((dummy).c_str());
  if ((sys.find("ATLAS_Theory_qqZZ_Generator_Powheg")!=std::string::npos) && direction == "down") {
	TH1F *hnom  = NULL;
	if (m_Fiducial) hnom = (TH1F*) m_InFile->Get(("h"+m_Variable+"_"+catname+"_"+process_name).c_str());  
	else            hnom = (TH1F*) m_InFile->Get(("hm_"+m_Variable+catname+"_"+process_name).c_str());
  		hnom->Scale(2);
  		hsys->Add(hnom,-1);
  		hsys->Scale(-1);
  }


  if (hsys == NULL) {
    PRINT_FATAL(" <RetrieveSysShape()>:: syst " + dummy + " not found. exit(0)!" );
    exit(0);
  }
  hsys->SetNameTitle( (dummy+"_"+direction).c_str(), (dummy+"_"+direction).c_str()  );
  PRINT_DEBUG_OBJECT(hsys);
  PRINT_DEBUG_OBJECT(m_var);

  TH1F* hsys_remapped = NULL; 
  if (m_Fiducial) hsys_remapped = remapHisto ( hsys, cat ) ;
  else hsys_remapped = remapHisto ( hsys, cat ) ;
  
  PRINT_DEBUG_OBJECT(hsys_remapped);

  RooDataHist *m_x_hdata = new RooDataHist( ("sys"+sys+catname+direction+(string)m_var->GetName()).c_str(), //
					    ("sys"+sys+catname+direction+(string)m_var->GetName()).c_str(), // for fiducial XS the entire m4l histogram is needed 
					    RooArgList(*m_var), hsys_remapped );      
  
  RooHistPdf *m_x_hpdf = new RooHistPdf( ("pdfsys_"+sys+catname+direction+(string)m_var->GetName()).c_str(),
					 ("pdfsys_"+sys+catname+direction+(string)m_var->GetName()).c_str(),
					 *m_var, *m_x_hdata );                                   //
  return m_x_hpdf;
  
}

RooStarMomentMorph* WorkSpaceMaker :: RetrieveRooStar (string catname , int cat, RooHistPdf* m_x_hpdf, RooRealVar *m_var,  string process_name){

  PRINT_DEBUG_FUNCTION(" <RetrieveRooStar()>:: RetrieveRooStar");

  RooRealVar *tmp_sys =NULL;
  vector<double> *nref = new vector<double>;
  vector<int> *nn = new vector<int>;

  RooArgList *paramRooStar = new RooArgList();
  RooArgList *variationRooStar  = new RooArgList() ;
  if (process_name!="qqZZ") {
  //if (process_name == "AllSig") {
    tmp_sys = new RooRealVar ("ATLAS_SignalMassShift", "ATLAS_SignalMassShift", 0, -5, 5); //tmp_sys->setConstant(1);
    AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, catname, cat, process_name);
    //tmp_sys->SetNameTitle(("ATLAS_SignalMassShift"+catname).c_str(),("ATLAS_SignalMassShift"+catname).c_str());
    m_listNP.add(*tmp_sys);
    makeGaussianConstraint(tmp_sys);
  }
  if (process_name == "qqZZ") {
    TString tmp_name="";
    std::vector<int> bin_ranges = GetVarBinRange(m_VariableId);
    for (unsigned int i =0; i < bin_ranges.size(); ++i){
    	if ( cat < bin_ranges.at(i) ){
		tmp_name = std::to_string(i);
		break;
    	}
    }
    tmp_sys = new RooRealVar ("ATLAS_Theory_qqZZ_Generator_Powheg_"+tmp_name, "ATLAS_Theory_qqZZ_Generator_Powheg", 0, -5, 5); //tmp_sys->setConstant(1);
    AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, catname, cat, process_name);
    m_listNP.add(*tmp_sys);
    makeGaussianConstraint(tmp_sys);
  }
/*
  tmp_sys = new RooRealVar ("ATLAS_HiggsMassVariation", "ATLAS_HiggsMassVariation", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);
  
  tmp_sys = new RooRealVar ("ATLAS_EG_SCALE_ALLCORR", "ATLAS_EG_SCALE_ALLCORR", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);

  tmp_sys = new RooRealVar ("ATLAS_EG_SCALE_E4SCINTILLATOR", "ATLAS_EG_SCALE_E4SCINTILLATOR", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);

  tmp_sys = new RooRealVar ("ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE", "ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);
*/
/*
  tmp_sys = new RooRealVar ("ATLAS_EG_RESOLUTION_ALL", "ATLAS_EG_RESOLUTION_ALL", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, catname, cat, process_name);
*/
/*
  tmp_sys = new RooRealVar ("ATLAS_MUON_MS", "ATLAS_MUON_MS", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);
*/
  //tmp_sys = new RooRealVar ("ATLAS_MUON_ID", "ATLAS_MUON_ID", 0, -5, 5); //tmp_sys->setConstant(1);
  //AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, catname, cat, process_name);
/*
  tmp_sys = new RooRealVar ("ATLAS_MUON_SCALE", "ATLAS_MUON_SCALE", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);
*/
  PRINT_DEBUG_OBJECT(paramRooStar,1);
  variationRooStar->add(*m_x_hpdf);
  m_signalmorphiong = new RooStarMomentMorph (("mm"+catname+"_"+process_name).c_str(), ("mm"+catname+"_"+process_name).c_str(), *paramRooStar, RooArgList(*m_var), *variationRooStar, *nn, *nref, RooStarMomentMorph::Linear);
  m_signalmorphiong->useHorizontalMorphing(false);
  RooArgSet observableSet(*m_var);
  m_signalmorphiong->setBinIntegrator(observableSet);
  m_signalmorphiong->getVal();
  
  return m_signalmorphiong;
  
}  

void WorkSpaceMaker :: AddComponentRooStar (RooRealVar *tmp_sys, vector<int> *nn, vector<double> *nref, RooArgList *paramRooStar, RooArgList *variationRooStar, string catname, int cat, string process_name ){
 
  PRINT_DEBUG_FUNCTION(" <AddComponentRooStar()>:: AddComponentRooStar");
  string tmpname;  
  string histoname = "hm_";
  if (!m_Fiducial) histoname = histoname+m_Variable;
  m_listNPshapes.add(*tmp_sys);
  nn->push_back(2); nref->push_back(-1); nref->push_back(1);
  paramRooStar->add(*tmp_sys);
//  if (m_Fiducial)
  tmpname= tmp_sys->GetName();//_"+(string)tmp_sys->GetName();
//  else tmpname= histoname+m_Category.at(cat)+"_AllSig";//_"+(string)tmp_sys->GetName();
  
  if (m_Fiducial){ down = RetrieveSysShape(tmpname, catname, cat, "down", m_x, process_name);   up = RetrieveSysShape(tmpname, catname, cat, "up", m_x, process_name); }  
  else           { down = RetrieveSysShape(tmpname, catname, cat, "down", m_m4l, process_name); up = RetrieveSysShape(tmpname, catname, cat, "up", m_m4l, process_name); }
  
  variationRooStar->add(*down);  variationRooStar->add(*up);
  
}
