#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: DoSinglePdf( std::string process, int chnum, bool isSignal, int cat ){

  int i = cat;
  if( m_debug )
    cout << "<DoSinglePdf()>:: Making " << GetChannel(chnum) << " " << process << " Pdf" << endl;
 

  setupRemappedHistoAndVariables(process, chnum, cat);
  
  RooArgSet m_listSubpdftmp;
  RooArgList *listtmp = new RooArgList();
  
  
  if( isSignal ){
    m_observables.add(*m_x);
    m_norm_pdf = SignalNormFactor(i, chnum, listtmp, m_h_remapped);
  }
  else
    m_norm_pdf = BackgroundNormFactor(i, chnum, listtmp, m_h_remapped, process);
  
  if ( m_Fiducial ) {
    m_x_hdata = new RooDataHist( ("pdf_h"+m_Category.at(cat)+process).c_str(),               //
                                 ("pdf_h"+m_Category.at(cat)+process).c_str(),               //  for fiducial XS the entire m4l histogram is needed 
                                  RooArgList(*m_x), m_h_remapped );                          //
  }
  else {
    m_tmp = new TH1F (("thx"+to_string(i)+"_"+process).c_str(),("thx"+to_string(i)+"_"+process).c_str(),1, 0, 1) ; ;
    m_tmp->Reset();                                                                             
    m_tmp->SetBinContent( 1, m_h_remapped->GetBinContent(i+1) );                             //
    m_x_hdata = new RooDataHist( ("pdf_h"+m_Category.at(cat)+process).c_str(),               //  for diff XS histogram with 1 bin is needed 
                                 ("pdf_h"+m_Category.at(cat)+process).c_str(),               //  equivalent to 1 bin of the distribution
                                  RooArgList(*m_x), m_tmp );                                 //  the histogram can be an external input -> next improvement! 
  }

  m_x_hpdf = new RooHistPdf( ("pdf_"+m_Category.at(cat)+process).c_str(),
                 ("pdf_"+m_Category.at(cat)+process).c_str(),
                 *m_x, *m_x_hdata );
  
  if (m_do2D && !m_Fiducial){ /// pt condition
    TH1F *m_h_m4l = NULL;
    
    if ( process == "redBkg" ) m_h_m4l = (TH1F*)m_InFile->Get( ("hm_"+(string)GetChannel(chnum)+"_"+process).c_str() );
    else m_h_m4l = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+m_Category.at(cat)+"_"+GetChannel(chnum)+"_"+process).c_str() );
    m_h_m4l->Print();
    m_x_hdata  = new RooDataHist( ("pdf_m4l_h"+m_Category.at(cat)+process).c_str(),
                  ("pdfh_m4l_h"+m_Category.at(cat)+process).c_str(),
                  RooArgList(*m_m4l), m_h_m4l );
    
    m_m4l_hpdf = new RooHistPdf( ("pdf_m4l_"+m_Category.at(cat)+process).c_str(),
                 ("pdf_m4l_"+m_Category.at(cat)+process).c_str(),
                 *m_m4l, *m_x_hdata );

    if (m_addShapeSys && isSignal ){

		  RooProdPdf *prodPdf = RetreiveRooStar(cat, m_m4l_hpdf, m_m4l);		 
      m_x_m4l    = new RooProdPdf( ("pdf_m4l"+m_Variable+"_"+m_Category.at(cat)+process).c_str(),
                 ("pdf_ext_"+m_Category.at(cat)+process).c_str(),
                 RooArgList(*m_x_hpdf, *prodPdf) );             
    } 
    else m_x_m4l    = new RooProdPdf( ("pdf_m4l"+m_Variable+"_"+m_Category.at(cat)+process).c_str(),
                 ("pdf_ext_"+m_Category.at(cat)+process).c_str(),
                 RooArgList(*m_x_hpdf, *m_m4l_hpdf) );
    
    m_hpdf_ext = new RooExtendPdf( ("pdf_ext_"+m_Category.at(cat)+process).c_str(),
                   ("pdf_m4l_"+m_Category.at(cat)+process).c_str(),
                   *m_x_m4l, *m_norm_pdf );
    
    m_listSubpdf.add(*m_hpdf_ext);
    m_listSubpdftmp.add(*m_hpdf_ext);

  }
  else {

    if (m_addShapeSys && m_Fiducial && isSignal ){

		  RooProdPdf *prodPdf = RetreiveRooStar(cat, m_x_hpdf, m_x);		 
      m_hpdf_ext = new RooExtendPdf( ("pdf_ext_"+m_Category.at(cat)+process).c_str(),
                   ("pdf_m4lpt_"+m_Category.at(cat)+process).c_str(),
                   *prodPdf, *m_norm_pdf );
    } 
    else m_hpdf_ext = new RooExtendPdf( ("pdf_ext_"+m_Category.at(cat)+process).c_str(),
                   ("pdf_m4lpt_"+m_Category.at(cat)+process).c_str(),
                   *m_x_hpdf, *m_norm_pdf );
    
    m_listSubpdf.add(*m_hpdf_ext);
    m_listSubpdftmp.add(*m_hpdf_ext);


    
  }



  m_spectrum = new RooAddPdf( ("spectrum"+m_Variable+"_"+GetChannel(chnum)+"_"+process+"_"+m_Category.at(cat)).c_str(),
  			      ("spectrum"+m_Variable+"_"+GetChannel(chnum)+"_"+process+"_"+m_Category.at(cat)).c_str(),
  			      m_listSubpdftmp );
  
  if (isSignal) m_pdfcategory.push_back(m_listSubpdftmp);
  else m_pdfcategory.at(cat).add(m_listSubpdftmp);

  m_listpdf.add(*m_spectrum);
  //m_listpdf.add(m_listSubpdftmp);
  m_list.add(*listtmp);
  
}

void WorkSpaceMaker :: DoSignalPdf(string process, int chnum, int cat){

  DoSinglePdf( process, chnum, true, cat );
  
}

void WorkSpaceMaker :: DoBackgroundPdf(int chnum, bool qqZZ, bool ggZZ, bool redBkg, int cat){
  
  if (qqZZ) DoSinglePdf( GetProcess(Process::qqZZ), chnum, false, cat );
  if (ggZZ) DoSinglePdf( GetProcess(Process::ggZZ), chnum, false, cat );
  if (redBkg) DoSinglePdf( GetProcess(Process::redBkg), chnum, false, cat );
  
}

void WorkSpaceMaker :: setupRemappedHistoAndVariables(std::string process, int chnum, int cat)
{
  m_h = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_"+GetChannel(chnum)+"_"+process).c_str() );
  m_h_remapped = remapHisto ( m_h, cat ) ;
  if ( m_Fiducial ) {
    m_x = new RooRealVar("x","x", 0, m_Mbins);
    m_x->setBins(m_Mbins);
  }
  else {
    CheckVectorSize(m_h,chnum);
    m_x = new RooRealVar("x","x", 0,1);
    m_x->setBins(1);
    m_m4l = new RooRealVar("m4l","m4l",115,130) ;
    m_m4l->setBins(m_Mbins);
  }

}


RooHistPdf* WorkSpaceMaker :: RetreiveSysShape (string sys, int cat, string direction, RooRealVar *m_var){


  TFile *_file0 = TFile::Open( (m_Dir+"../varsDistro/XsecInputs_15bin_Sys.root").c_str() );
   cout << sys << endl;
  TH1F *hsys = (TH1F*) _file0->Get((sys+"_"+direction).c_str());
  hsys->Print(); 
  m_var->Print();
  TH1F* hsys_remapped = NULL; 
  if (m_Fiducial) hsys_remapped = remapHisto ( hsys, cat ) ;
  else hsys_remapped = hsys ;
  m_var->Print();
  hsys_remapped->Print();
  RooDataHist *m_x_hdata = new RooDataHist( ("sys"+sys+m_Category.at(cat)+direction+(string)m_var->GetName()).c_str(), //
					    ("sys"+sys+m_Category.at(cat)+direction+(string)m_var->GetName()).c_str(), // for fiducial XS the entire m4l histogram is needed 
					    RooArgList(*m_var), hsys_remapped );      
  
  RooHistPdf *m_x_hpdf = new RooHistPdf( ("pdfsys_"+sys+m_Category.at(cat)+direction+(string)m_var->GetName()).c_str(),
					 ("pdfsys_"+sys+m_Category.at(cat)+direction+(string)m_var->GetName()).c_str(),
					 *m_var, *m_x_hdata );                                   //
  return m_x_hpdf;     

}


RooProdPdf* WorkSpaceMaker :: RetreiveRooStar (int cat, RooHistPdf* m_x_hpdf, RooRealVar *m_var){

  RooRealVar *tmp_sys =NULL;
  vector<double> *nref = new vector<double>;
  vector<int> *nn = new vector<int>;

  RooArgList *paramRooStar = new RooArgList();
  RooArgList *variationRooStar  = new RooArgList() ;

  tmp_sys = new RooRealVar ("ATLAS_HiggsMassVariation", "ATLAS_HiggsMassVariation", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);
  
  tmp_sys = new RooRealVar ("ATLAS_EG_SCALE_ALLCORR", "ATLAS_EG_SCALE_ALLCORR", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);

  tmp_sys = new RooRealVar ("ATLAS_EG_SCALE_E4SCINTILLATOR", "ATLAS_EG_SCALE_E4SCINTILLATOR", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);

  tmp_sys = new RooRealVar ("ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE", "ATLAS_EG_SCALE_LARCALIB_EXTRA2015PRE", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);

  tmp_sys = new RooRealVar ("ATLAS_EG_RESOLUTION_ALL", "ATLAS_EG_RESOLUTION_ALL", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);

  tmp_sys = new RooRealVar ("ATLAS_MUON_MS", "ATLAS_MUON_MS", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);
  
  tmp_sys = new RooRealVar ("ATLAS_MUON_ID", "ATLAS_MUON_ID", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);
  
  tmp_sys = new RooRealVar ("ATLAS_MUON_SCALE", "ATLAS_MUON_SCALE", 0, -5, 5); //tmp_sys->setConstant(1);
  AddComponentRooStar(tmp_sys, nn, nref, paramRooStar, variationRooStar, cat);


  paramRooStar->Print("v");
  variationRooStar->add(*m_x_hpdf);
  m_signalmorphiong = new RooStarMomentMorph (("mm"+m_Category.at(cat)).c_str(), ("mm"+m_Category.at(cat)).c_str(), *paramRooStar, RooArgList(*m_var), *variationRooStar, *nn, *nref, RooStarMomentMorph::Linear);

  m_signalmorphiong->useHorizontalMorphing(false);
  RooArgSet observableSet(*m_var, *paramRooStar);
  m_signalmorphiong->setBinIntegrator(observableSet);
  m_signalmorphiong->getVal();
  

  RooProdPdf* prodPdf = new RooProdPdf ( TString(m_signalmorphiong->GetName()).ReplaceAll("mm","mmsys"), TString(m_signalmorphiong->GetName()).ReplaceAll("mm","mmsys"),
                                        RooArgList(*m_signalmorphiong/*, *m_gaus_tmp*/));

  //prodPdf->Print("v"); exit(0);
  return prodPdf;
}  

void WorkSpaceMaker :: AddComponentRooStar (RooRealVar *tmp_sys, vector<int> *nn, vector<double> *nref, RooArgList *paramRooStar, RooArgList *variationRooStar, int cat ){

  string tmpname;  
  string histoname = "hm_";
  if (!m_Fiducial) histoname = histoname+m_Variable;
  
  m_listNPshapes.add(*tmp_sys);
  nn->push_back(2); nref->push_back(-1); nref->push_back(1);
  paramRooStar->add(*tmp_sys);
  if (m_Fiducial)tmpname= histoname+m_Category.at(cat)+"_AllSig_"+(string)tmp_sys->GetName();
  else tmpname= histoname+m_Category.at(cat)+"_incl_AllSig_"+(string)tmp_sys->GetName();
  

  if (m_Fiducial) {down = RetreiveSysShape(tmpname, cat, "Down", m_x);        up = RetreiveSysShape(tmpname, cat, "Up", m_x);}
  else{ down = RetreiveSysShape(tmpname, cat, "Down", m_m4l);        up = RetreiveSysShape(tmpname, cat, "Up", m_m4l);}
  variationRooStar->add(*down);  variationRooStar->add(*up);
}



