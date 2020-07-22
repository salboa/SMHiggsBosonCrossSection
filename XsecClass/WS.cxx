#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: DoWS(){
  
  cout << "\033[1;32m <DoWS()>:: build workspace \033[0m" << endl;
  cout << "\033[1;33m <DoWS()>:: define Simultaneus PDF \033[0m" << endl;

  CreateOutDir();
  DoSimPdf();
  DefineWS();

  cout << "\033[1;32m <DoWS()>:: define ModelConfig \033[0m" << endl;
  DefineModelConfig();
  
  RooDataSet *combData = (RooDataSet*)RooStats::AsymptoticCalculator::MakeAsimovData(*m_modelConfig,  m_list /* it should be all variables */, m_list);
  
  combData->SetNameTitle("asimovDataFullModel","asimovDataFullModel");
  m_ws->import(*combData);
  combData->Print();
  if ( m_WithData ) ImportData();
  if (m_Variable=="m12m34") MakeMGDataset();
  
  
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle( 0 );

  if ( !m_WithData && m_Fiducial ) PlotPdfFiducial(m_simPdf, combData, combData);
  if ( m_WithData && m_Fiducial ) PlotPdfFiducial(m_simPdf, combData, (RooDataSet*) m_obsdata);
  if ( !m_WithData && !m_Fiducial ) PlotPdf(m_simPdf, combData, combData);
  if ( m_WithData && !m_Fiducial ) PlotPdf(m_simPdf, combData, (RooDataSet*) m_obsdata);
  
  if ( m_FidSum )   doFiducialSumChannels();
  if ( m_Fid4l )    doFiducial4l();
  if ( m_Fid2l2l )  doFiducial2l2l();
  if ( m_FidTotal ) doFiducialTotal();
  if ( m_FidComb )  doFiducialComb();
  if ( m_FidChan )  doFiducialSingleChannel();
  
  if( m_debug ){
    cout << "\033[1;32m <DoWS()>:: print WS and DataSet \033[0m" << endl;
    m_ws->Print("v");
    m_modelConfig->Print();
    combData->Print();
  }
  
  if(m_addSys && m_sysBands) PlotSysBands();

  CleanUp();

  if(!m_skipScan)  m_ws->writeToFile( (m_OutDir+"/ws_"+m_Variable+".root").c_str() );
  
  if( m_dofit ){
    cout << "\033[1;32m <DoWS()>:: calling DoQuickTest() \033[0m" << endl;
    DoQuickTest();
    Closing();
  }
  if(m_skipScan) m_ws->writeToFile( (m_OutDir+"/ws_"+m_Variable+".root").c_str() );

  
  if (m_parallel) Parallel();
}

void WorkSpaceMaker :: DoSimPdf(){

  if( m_debug )
    cout << "<DoSimPdf()>:: making expected PDF" << endl;

  DoAddPdf();

  DefineCategories();
  RooProdPdf* tmp_prodPdf = NULL;
  
  m_simPdf = new RooSimultaneous("simPdf", "simPdf", *m_sample);
  for (unsigned int i = 0; i< m_pdfcategory.size(); ++i){

    if( m_debug ){
      cout << "<DoSimPdf()>:: PdfAddList" << endl;
      m_v_pdfaddlist.at(i).Print();
    }
    if(m_addSys){
      tmp_prodPdf = ApplySys(&m_v_pdfaddlist.at(i));
      m_simPdf->addPdf(*tmp_prodPdf, (m_Category.at(i)).c_str());
    }
    else
      m_simPdf->addPdf(m_v_pdfaddlist.at(i), (m_Category.at(i)).c_str());
  }
  
  if( m_debug ){
    cout << "<DoSimPdf()>:: RooSimPdf" << endl;
    m_simPdf->Print();
  }
  
}

void WorkSpaceMaker :: DefineCategories(){
  
  cout << "\033[2;33m <DefineCategories()>:: PDF \033[0m" << endl;
  
  string incl = "incl";
  m_sample = new RooCategory("channelCat", "channelCat");
  
  if ( m_Channel.compare(incl)==0 )
    for (unsigned int i = 0; i< m_pdfcategory.size(); ++i){
      m_sample->defineType((m_Category.at(i)).c_str(),i); // to be optimized for 4 separate channels
    }

}

void WorkSpaceMaker :: DoAddPdf(){
  
  cout << "\033[2;33m <DoAddPdf()>:: PDF \033[0m" << endl;
  
  m_listpdf.Print();
  RooAddPdf* addPdf = NULL;
  
  for (unsigned int i = 0; i< m_pdfcategory.size(); ++i){
    addPdf = new RooAddPdf( ("model_"+m_Channel+"_nosys_"+m_Category.at(i)).c_str(),
                            ("model_"+m_Channel+"_nosys_"+m_Category.at(i)).c_str(),
                             m_pdfcategory.at(i) );
    if( m_debug )
      addPdf->Print();
    
    m_v_pdfaddlist.push_back(*addPdf);
    m_pdfaddlist.add(*addPdf);
  
  }
  
  delete addPdf;
}

RooProdPdf* WorkSpaceMaker :: ApplySys(RooAddPdf* addPdf){

  cout << "\033[2;33m <ApplySys()>:: PDF \033[0m" << endl;

  //if( m_verbose )
    cout << m_listpdf_np << endl;
  m_listpdf_np.Print();
  
  RooArgList listpdf;
  listpdf.add(*addPdf);
  listpdf.add(m_listpdf_np);
  if (m_addShapeSys)   listpdf.add(m_listpdf_npshapes);


  
  RooProdPdf* prodPdf = new RooProdPdf ( TString(addPdf->GetName()).ReplaceAll("nosys","sys"),
					 TString(addPdf->GetName()).ReplaceAll("nosys","sys"),
					 listpdf );
  if( m_debug )
    prodPdf->Print();
  
  cout << "<ApplySys>:: prodPdf exp: " << prodPdf->expectedEvents(m_list) << endl ;
  
  return prodPdf;
  
}

void WorkSpaceMaker :: DefineWS(){
  
  cout << "\033[1;39m <DefineWS()>:: defining the WS \033[0m" << endl;
  
  m_ws = new RooWorkspace("myWS");
  
  RooRealVar* tmp = NULL;
  TIterator *iteratorGlobalObs= m_list.createIterator();
  while ( (tmp = (RooRealVar*)iteratorGlobalObs->Next()) ) {
    if (string(tmp->GetName())!="dummyvar")tmp->setConstant(1);
  }
  TIterator *iteratorPOI= m_paramOfInterest->createIterator();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) tmp->setConstant(0);
  
  m_ws->import(*m_simPdf);
  m_ws->Print("v");
  
  cout << "<DefineWS()>:: ws simPdf exp: "
       << m_ws->pdf("simPdf")->expectedEvents(m_list) << endl ;
  
  cout << "<DefineWS()>:: simPdf exp: "
       << m_simPdf->expectedEvents(m_list) << endl ;

}

void WorkSpaceMaker :: DefineModelConfig(){

  if( m_debug )
    cout << "\033[1;39m <DefineModelConfig()>:: \033[0m" << endl;
  
  m_modelConfig = new RooStats::ModelConfig(m_ws);
  m_modelConfig->SetPdf(*m_simPdf);
  m_paramOfInterest->Print();
  m_modelConfig->SetParametersOfInterest(*m_paramOfInterest);

  RooRealVar weightVar("weightVar", "weightVar", 1, 0.,2.);
  if (m_do2D) m_observables.add(*m_m4l);
  m_observables.add(*m_sample);
  m_observables.add(weightVar);
  m_modelConfig->SetObservables(m_observables);

  m_modelConfig->SetGlobalObservables( m_globalObservables);

  if (m_addShapeSys)   m_listNP.add(m_listNPshapes);
  if(m_addSys) m_modelConfig->SetNuisanceParameters( m_listNP );
  m_modelConfig->SetName("ModelConfig");
  m_ws->import(*m_modelConfig);
  m_modelConfig->Print("v");
  RooArgSet params;
  params.add(*m_paramOfInterest); params.add(m_listNP);
  //m_ws->saveSnapshot("nominal",params);
  
}


void WorkSpaceMaker :: ImportData(){
  
  cout << "\033[2;33m <ImportData()>:: PDF \033[0m" << endl;
  
  TH2F *m_tmp2d = NULL;
  RooDataHist *m_tmp2d_data=NULL;
  map<string,TH1*> hmapd;
  map<string,RooDataHist*> hmapd2d;
  
  bool ZZd = false;
  if ( m_DataSet != "" ) ZZd = true;

  if ( !m_Fiducial ){
    if ( !ZZd ) m_h = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_"+GetChannel(0)+"_data").c_str() );
    else m_h = (TH1F*)m_InFile->Get( m_DataSet.c_str() );

    
    m_h_remapped = remapHisto ( m_h, (int)m_Category.size() ) ;
    
    //for(int i = 0; i < m_h_remapped->GetNbinsX(); ++i ) if (m_h_remapped->GetBinContent(i+1) == 0) { m_h_remapped->SetBinContent(i+1, 0.001/m_binwidth.at(i)); }
    
    for(int i = 0; i < m_h_remapped->GetNbinsX(); ++i )
      m_h_remapped->SetBinContent(i+1, m_h_remapped->GetBinContent(i+1)* m_binwidth.at(i) );

    if( !m_do2D ){
      for( int i=0; i < (int)m_Category.size(); i++ ){
        m_tmp = new TH1F (("data_"+to_string(i)).c_str(),("data_"+to_string(i)).c_str(),1, 0, 1) ; ;
        m_tmp->Reset();
        m_tmp->SetBinContent( 1, m_h_remapped->GetBinContent(i+1) );
        hmapd[m_Category.at(i).c_str()] = m_tmp;
      }
    }

    if( m_do2D ){
      for( int i=0; i < (int)m_Category.size(); i++ ){
        m_h = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+"bin"+to_string(i)+"_"+GetChannel(0)+"_data").c_str() );
        m_tmp2d = new TH2F (("data_"+to_string(i)).c_str(),("data_"+to_string(i)).c_str(),1, 0, 1, 15, 115, 130) ; ;
        m_tmp2d->Reset();
        for (int j=0; j < m_h->GetNbinsX(); ++j ) m_tmp2d->SetBinContent( 1, j+1, m_h->GetBinContent(j+1) );
        m_tmp2d_data = new RooDataHist (("datah_"+to_string(i)).c_str(),("datah_"+to_string(i)).c_str(), RooArgList(RooArgSet(*m_x, *m_m4l)),m_tmp2d);
        hmapd2d[m_Category.at(i).c_str()] = m_tmp2d_data;
      }
    }
  
    if( m_do2D )
      m_obsdata = new RooDataHist ("obsData","obsData",
				   RooArgList(RooArgSet(*m_x, *m_m4l)),
				   *m_sample, hmapd2d);
    else
      m_obsdata = new RooDataHist ("obsData","obsData", *m_x, *m_sample,
				   hmapd, 1.);
    
  }
  
  if ( m_Fiducial ){

    for( int i=0; i < (int)m_Category.size(); i++ ){
      /// start from 1 needed see enum associated
      m_h = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_"+GetChannel(i+1)+"_data").c_str() );
      m_h_remapped = remapHisto ( m_h, m_h->GetNbinsX() ) ;
      hmapd[m_Category.at(i).c_str()] = m_h_remapped;
    }
    
    m_obsdata = new RooDataHist ("obsData","obsData", *m_x, *m_sample,
				 hmapd, 1.); 
  }
  m_ws->import(*m_obsdata);

}


void  WorkSpaceMaker :: DoQuickTest(){

  cout << "<DoQuickTest()>:: doing a Quick Test ... " << endl;

  vector<double> vector_prefit;
  vector<double> vector_postfit;
  
  string dataname;
  dataname = "asimovDataFullModel";
  if ( m_useMG ) dataname = "asimovDataFullModel_MG";
  if ( m_WithData ) dataname = "obsData";
  ofstream tablefile;
  ofstream resultsfile;
  string what = "expected";
  if ( m_useMG ) what = "expected_MG";

  if ( m_WithData ) what = "data";
  
  string sysname = "";
  if(m_addSys) sysname = "_wsys";
  if (m_fixSys!="NO") sysname= sysname+"_fixing_"+m_fixSys;
  
  tablefile.open ((m_OutDir+"/"+m_Variable+"_fit_"+sysname+"_"+what+"_table.tex").c_str());
  
  resultsfile.open ((m_OutDir+"/"+m_Variable+"_fit_"+sysname+"_"+what+".dat").c_str());
  
  tablefile << "  \\begin{tabular}{ c | c | c | c }\n";
  tablefile << "   POI &  XS$_{\\mathrm{inj}}$  & XS$_{\\mathrm{fit}}$ & Rel. Error\\\\\n \\hline \n";

  resultsfile << " value  error_up  error_down \n" ;
  if( m_debug ) m_ws->allVars().Print("v");

  
  //// set to 1 all acceptances for fiducial measurements
  if ( !m_Fiducial ) setAcceptance();
  
  RooRealVar *tmp;
  RooRealVar *tmpReset;
  TIterator *iteratorPOI= m_modelConfig->GetParametersOfInterest()->createIterator();
  TIterator *iteratorPOIReset= m_modelConfig->GetParametersOfInterest()->createIterator();

  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) vector_prefit.push_back(tmp->getVal());
  iteratorPOI->Reset(); if (!m_WithData && !m_FidTotal && !m_FidComb) while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) tmp->setRange(0,5);

  RooAbsData * p_data = m_ws->data(dataname.c_str()); p_data->Print();

  m_simPdf = (RooSimultaneous*) m_ws->pdf("simPdf");

  RooAbsReal *nll=m_simPdf->createNLL(*p_data, RooFit::Constrain(*m_modelConfig->GetNuisanceParameters()),
                                      RooFit::Offset(kFALSE), RooFit::GlobalObservables(*m_modelConfig->GetGlobalObservables()), RooFit::Verbose(kFALSE), RooFit::NumCPU(1, RooFit::Hybrid) );

  RooFIter iter = m_ws->components().fwdIterator();
  RooAbsArg* arg;  
  while ((arg = iter.next())) {  
    if (arg->IsA() == RooStarMomentMorph::Class()) {  
      ((RooStarMomentMorph*)arg)->fixCache();  
      arg->Print();
    }  
  }
  
  //if (m_addShapeSys) m_ws->var("ATLAS_HiggsMassVariation")->setConstant(1);
  //if (m_addShapeSys) m_ws->var("ATLAS_HiggsMassVariation")->setVal(-1);

  RooMinimizer *minim = new RooMinimizer(*nll);
  minim->setEps(0.01);
  minim->optimizeConst(2);

  int fit = minim->minimize("Minuit2");

  RooArgSet params;
  params.add(m_ws->allVars());
  if( m_debug ) params.Print("v");
  
  if (m_do2D && m_addSys && m_fixSys =="NO") PlotM4l();

  if (m_FidChan && m_fixSys =="NO")PlotM4l();
  m_ws->saveSnapshot("postfit",params);  if (m_skipScan) return;


  iteratorPOI->Reset();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) { vector_postfit.push_back(tmp->getVal()); }

  m_ws->allVars().Print("v");
  
//  if (m_do2D && !m_addSys) PlotM4l();
  
  cout << "\033[1;39m <DoQuickTest()>:: input-output \033[0m" << endl;

  for ( unsigned int i = 0 ; i < vector_postfit.size(); ++i )
    cout << "<DoQuickTest()>:: prefit: " << vector_prefit.at(i)
	 << " postfit: " << vector_postfit.at(i)
	 << " minitree: " << m_xsminitree.at(i) << endl;

  cout << fit << "        =<! " << endl;
  
  iteratorPOI->Reset();
  
  int cw = 800; int ch = 800;
  SetCanvasSize( &cw, &ch );
  TCanvas c(("canvas_"+m_Variable).c_str(), ("canvas_"+m_Variable).c_str(), cw, ch) ;
  TCanvas c_single(("canvas_"+m_Variable).c_str(), ("canvas_"+m_Variable).c_str(), cw, ch) ;
  
  if ( vector_prefit.size()>1 && !( m_FidSum || m_Fid4l || m_Fid2l2l || m_FidTotal) )
    c.Divide( int(vector_prefit.size()/2. + 0.5),2) ;
  
  int ii=0;
  
  TLatex *t = NULL;
  TGraph *m_scan_plot = NULL;
  TF1 *sigma1 = new TF1 ("sigma1","1",0,210000);
  TF1 *sigma2 = new TF1 ("sigma2","4",0,210000);
  TF1 *sigma3 = new TF1 ("sigma3","9",0,210000);
  TF1 *sigma4 = new TF1 ("sigma4","16",0,210000);
  TLine *errorLeft = NULL;
  TLine *errorRight = NULL;
  
  TGraphAsymmErrors exp_xs;
  TGraphAsymmErrors exp2_xs;
  TGraphAsymmErrors obs_xs;
  TGraphAsymmErrors exp_ratio_xs;
  TGraphAsymmErrors exp2_ratio_xs;
  TGraphAsymmErrors obs_ratio_xs;
  
  
  vector<double> yxs = {3.2, 2.8, 2.4, 2};

  bool exitLoop = false;
  string conference = "";

  
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ){
   /// reset POI values
    int kk =0;
    while ( (tmpReset = (RooRealVar*)iteratorPOIReset->Next()) ) {
      m_ws->var(tmpReset->GetName())->setVal(vector_prefit.at(kk));
      kk++;
    }

    m_scan_plot = new TGraph ();
    m_scan_plot->SetLineColor(kBlue);
    m_scan_plot->SetLineWidth(2);
    if ( m_Lumi->getVal() == 14.8 ) {
      m_scan_plot->SetLineStyle(2);
      conference = "ICHEP";
    }
    m_scan_plot->SetNameTitle((tmp->GetName()+conference).c_str(),(tmp->GetName()+conference).c_str());
    
    cout << "\033[1;39m <DoQuickTest()>::  doScan for :  Var = "
	 <<  m_Variable << "  fixSys = " <<  m_fixSys << "  ->  \033[0m"
	 << "\033[1;32m " << tmp->GetName() << " !\033[0m" << endl;
    ++ii;
    
    cout << tmp->GetName() << endl;
    float fixrange = -0.1; if (m_WithData) if (vector_postfit.at(ii-1)<0 || vector_postfit.at(ii-1)< vector_prefit.at(ii-1)) fixrange =-2;

    float fixrangeup = 3;
    if (m_WithData) if (vector_postfit.at(ii-1)<0 || vector_postfit.at(ii-1)< vector_prefit.at(ii-1) ) fixrangeup =-4;


    float negative_protection = 0;

    if ( fixrange*abs(vector_postfit.at(ii-1)) < 0 ) negative_protection= -1*(m_ws->var(("expperfb_"+m_Category.at(ii-1)+"qqZZ").c_str())->getVal()+m_ws->var(("expperfb_"+m_Category.at(ii-1)+"ggZZ").c_str())->getVal()+m_ws->var(("expperfb_"+m_Category.at(ii-1)+"redBkg").c_str())->getVal())/TMath::Max(m_ws->var(("Cgg_"+m_Category.at(ii-1)).c_str())->getVal(), m_ws->var(("Cvbf_"+m_Category.at(ii-1)).c_str())->getVal()); 
    else negative_protection = fixrange*abs(vector_postfit.at(ii-1));

    if ( m_WithData && m_Variable== "m12" && (string)tmp->GetName() == "sigma_bin5") fixrangeup = 200;
    if ( m_WithData && m_Variable== "m34" && (string)tmp->GetName() == "sigma_bin6") negative_protection = -0.001;
    if ( m_WithData && (m_Variable== "ptpt"||m_Variable=="pt0j") && (string)tmp->GetName() == "sigma_bin3") { negative_protection = 2*negative_protection; fixrangeup = 200;}

    if ( m_FidSum || m_Fid4l || m_Fid2l2l || m_FidTotal  || m_FidChan || m_FidComb ){
      if (m_FidSum)
	ScanNLL( (m_OutDir+"/output.root").c_str(), "myWS", 200,
		 tmp->GetName(), 0.5*vector_postfit.at(ii-1),2.*vector_postfit.at(ii-1),
		 dataname, m_scan_plot, vector_postfit);
      else
        ScanNLL( (m_OutDir+"/output.root").c_str(), "myWS", 200,
		 tmp->GetName(), 0.5*vector_postfit.at(ii-1), 2.*vector_postfit.at(ii-1),
		 dataname, m_scan_plot, vector_postfit);
      c.cd(ii);
      m_scan_plot->SetMaximum(5);
      m_scan_plot->GetXaxis()->SetLimits(0,2*vector_postfit.at(ii-1));
      m_scan_plot->Draw("apl");
      c_single.cd();
      m_scan_plot->SetMaximum(5);
      m_scan_plot->GetXaxis()->SetLimits(0,2*vector_postfit.at(ii-1));
      m_scan_plot->Draw("apl");

      yxs.at(0)= 3.; yxs.at(1)= 2.6; yxs.at(2)= 2.4; yxs.at(3)= 2.2;
      if (!m_FidChan) exitLoop = true;
    }
    else{
      cout << " Scan range: "<< negative_protection << " - " <<
      TMath::Abs(fixrangeup*vector_postfit.at(ii-1)) << endl;
      ScanNLL( (m_OutDir+"/output.root").c_str(), "myWS", 200,
	       tmp->GetName(), negative_protection,
	       TMath::Abs(fixrangeup*vector_postfit.at(ii-1)),//tmp->getVal(),
	       dataname, m_scan_plot, vector_prefit/*vector_postfit*/);
      
      c.cd(ii);
      m_scan_plot->SetMaximum(5);
      m_scan_plot->GetXaxis()->SetLimits( negative_protection,
					  fixrangeup*vector_postfit.at(ii-1));
      m_scan_plot->Draw("apl");
      c_single.cd();
      m_scan_plot->SetMaximum(5);
      m_scan_plot->GetXaxis()->SetLimits( negative_protection,abs(fixrangeup*vector_postfit.at(ii-1)));
      m_scan_plot->Draw("apl");
      
    }

    if( m_debug ) m_scan_plot->Print();
    m_scan_plot->GetYaxis()->SetTitleOffset(1.5);
    c.Update();
    c_single.Update();
    
    
    errorLeft = new TLine (m_LeftRightErrors.first, 0,
			   m_LeftRightErrors.first, 1);
    errorLeft->SetLineColor(kBlue);
    c.cd(ii); errorLeft->Draw();
    c_single.cd(); errorLeft->Draw();
    
    errorRight = new TLine (m_LeftRightErrors.second, 0,
			    m_LeftRightErrors.second, 1);
    errorRight->SetLineColor(kBlue);
    c.cd(ii); errorRight->Draw();
    c_single.cd(); errorRight->Draw();
    
    c.cd(ii);
    DrawSigmaLines( sigma1 ); DrawSigmaLines( sigma2 );
    DrawSigmaLines( sigma3 ); DrawSigmaLines( sigma4 );
    c_single.cd();
    DrawSigmaLines( sigma1 ); DrawSigmaLines( sigma2 );
    DrawSigmaLines( sigma3 ); DrawSigmaLines( sigma4 );
    
    t = new TLatex( .5*vector_postfit.at(ii-1),yxs.at(0),
		    ("xs_{inj} = "+ConvertToStringWithPrecision(vector_prefit.at(ii-1), 3)+" fb").c_str()  );
    c.cd(ii);
    drawlatex(t);
    c_single.cd();
    drawlatex(t);
    // fit results with errors:
    t = new TLatex( .5*vector_postfit.at(ii-1),yxs.at(1),
		    ("xs_{fit} = "+ConvertToStringWithPrecision(vector_postfit.at(ii-1), 3)+"^{+"+ConvertToStringWithPrecision(m_LeftRightErrors.second-vector_postfit.at(ii-1), 3)+"}_{-"+ConvertToStringWithPrecision(vector_postfit.at(ii-1)-m_LeftRightErrors.first, 3)+"} fb").c_str() );
    c.cd(ii);
    drawlatex(t);
    c_single.cd();
    drawlatex(t);
    
    if( !m_Fiducial ){
      
      double xpos=m_binlowerlimit.at(0);
      for ( int j =0; j< ii-1; ++j ) xpos+=m_binwidth.at(j);
      
      xpos+=(m_binwidth.at(ii-1)/2.) ;
      exp_xs.SetPoint(ii-1, xpos,  vector_prefit.at(ii-1) );
      exp_xs.SetPointError(ii-1, m_binwidth.at(ii-1)/2., m_binwidth.at(ii-1)/2., vector_prefit.at(ii-1)*0.05, vector_prefit.at(ii-1)*0.05);
      exp2_xs.SetPoint(ii-1, xpos,  vector_prefit.at(ii-1) );
      exp2_xs.SetPointError(ii-1, m_binwidth.at(ii-1)/2., m_binwidth.at(ii-1)/2., 0, 0);
      
      
      double error_up=0; double error_down = 0;
      if ( m_LeftRightErrors.second-vector_postfit.at(ii-1) > 0 ) error_up = m_LeftRightErrors.second-vector_postfit.at(ii-1);
      if ( vector_postfit.at(ii-1)-m_LeftRightErrors.first > 0 ) error_down = vector_postfit.at(ii-1)-m_LeftRightErrors.first;
      
      //if (vector_postfit.at(ii-1)<0) error_up = TMath::Abs((m_LeftRightErrors.second-vector_postfit.at(ii-1)))*2;
      obs_xs.SetPoint(ii-1, xpos,  vector_postfit.at(ii-1) );
      obs_xs.SetPointError(ii-1, m_binwidth.at(ii-1)/2., m_binwidth.at(ii-1)/2., error_down, error_up);

      
    }
    
    if( m_Fiducial ){
      
      
      double error_up=0; double error_down = 0;
      if ( m_LeftRightErrors.second-vector_postfit.at(ii-1) > 0 ) error_up = m_LeftRightErrors.second-vector_postfit.at(ii-1);
      if ( vector_postfit.at(ii-1)-m_LeftRightErrors.first > 0 ) error_down = vector_postfit.at(ii-1)-m_LeftRightErrors.first;
      
      
      obs_xs.SetPoint(ii-1, ii-1,  vector_postfit.at(ii-1) );
      obs_xs.SetPointError(ii-1, 0., 0, error_down, error_up);
    }
    
    
    tmp->setConstant(false);
    c.cd(ii); drawATLASInternal();
    c_single.cd(); drawATLASInternal();
    if ( !m_Fiducial ) c.SaveAs( (m_OutDir+"/fit_"+m_Variable+"_"+conference+sysname+".eps").c_str() );
    c_single.SaveAs( (m_OutDir+"/fit_"+tmp->GetName()+"_"+m_Variable+"_"+conference+sysname+what+".eps").c_str() );

    m_scan_plot->SaveAs( (m_OutDir+"/scan_"+m_Variable+"_"+conference+"_"+tmp->GetName()+sysname+what+".root").c_str() );
    
    TString namePOI = (string)tmp->GetName();
    namePOI.ReplaceAll("_","_{");
    namePOI.ReplaceAll("sigma","\\sigma");
    namePOI.ReplaceAll("mu","\\mu");
    
    tablefile <<  ("  $"+(string)namePOI+"}$ [\\si{\\femto\\barn}] & "
                   +ConvertToStringWithPrecision(vector_prefit.at(ii-1), 3)+" & $"
                   +ConvertToStringWithPrecision(vector_postfit.at(ii-1), 3)+
                   "^{+"+ConvertToStringWithPrecision(m_LeftRightErrors.second-vector_postfit.at(ii-1), 3)+
                   "}_{-"+ConvertToStringWithPrecision(vector_postfit.at(ii-1)-m_LeftRightErrors.first, 3)+"}$ & $^{+"+
                   ConvertToStringWithPrecision(100*(m_LeftRightErrors.second-vector_postfit.at(ii-1))/vector_postfit.at(ii-1), 3)+"\\%}_{"+
                   ConvertToStringWithPrecision(100*(m_LeftRightErrors.first-vector_postfit.at(ii-1))/vector_postfit.at(ii-1), 3)+"\\%}$ \\\\\n").c_str();

    resultsfile <<  (ConvertToStringWithPrecision(vector_postfit.at(ii-1), 5)+"  "+ConvertToStringWithPrecision(m_LeftRightErrors.second-vector_postfit.at(ii-1), 5)+"  "+ConvertToStringWithPrecision(vector_postfit.at(ii-1)-m_LeftRightErrors.first, 5)+"\n").c_str();
    if ( exitLoop ) break;

  }


  tablefile << "  \\end{tabular}";
  tablefile << ("  %\\caption {Expected and fitted cross sections in each category of $"+m_Variable+"$ using Asimov dataset with $\\mathcal{L} = "+
                ConvertToStringWithPrecision(m_Lumi->getVal(), 3)+" \\,\\mathrm{fb}^{-1}$. }\\label{tab:"+m_Variable+"_fit_asimov}\n").c_str();
  
  if ( !m_Fiducial ){
    c_single.cd();
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    pad1->Draw();             // Draw the upper pad: pad1
    pad1->cd();               // pad1 becomes the current pad
    TLegend *leg = new TLegend(0.60,0.75,0.90,0.90);
    leg->ConvertNDCtoPad();
    leg->SetTextFont(42);
    drawEnergyLumi();
    drawChannel();

    exp_xs.SetFillStyle(3004);
    exp_xs.GetYaxis()->SetTitleOffset(1.6);
    exp_xs.GetXaxis()->SetTitle((m_sigUnfLabels[m_Variable].at(0).c_str()));
    exp_xs.GetYaxis()->SetTitle((m_sigUnfLabels[m_Variable].at(1).c_str()));
    exp_xs.SetFillColor(kBlue);
    exp_xs.SetMarkerSize(0);
    exp2_xs.SetMarkerSize(0);
    exp2_xs.SetLineColor(kBlue);
    exp_xs.GetXaxis()->SetRangeUser(0, accumulate(m_binwidth.begin(), m_binwidth.end(), 0.0));
    
    //double maxObs = obs_xs.GetHistogram()->GetMaximum();
    double maxExp = exp_xs.GetHistogram()->GetMaximum();


    exp_xs.GetYaxis()->SetRangeUser(0, maxExp*1.5);
    
    exp_xs.GetXaxis()->SetRangeUser(0, accumulate(m_binwidth.begin(), m_binwidth.end(), 0.0));

    //obs_xs.Draw("ap");

    exp_xs.Draw("a2");

    exp2_xs.Draw("p,same");
    obs_xs.Draw("p,same");
    drawATLASInternal();
    leg->AddEntry(&exp_xs, "Higgs SM @125 GeV", "f");
    if(m_WithData)
      leg->AddEntry(&obs_xs, "Data", "p");
    else
      leg->AddEntry(&obs_xs, "Asimov Data", "pel");

    leg->Draw("same");
    c_single.cd();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->Draw();
    pad2->cd();
    
    for(Int_t ii=0; ii<exp_xs.GetN(); ii++) {
      double x; double y;
      double yobs;
      exp_xs.GetPoint(ii, x, y);
      exp_ratio_xs.SetPoint(ii, x,  1 );
      exp_ratio_xs.SetPointError(ii, exp_xs.GetErrorXlow(ii), exp_xs.GetErrorXhigh(ii), exp_xs.GetErrorYlow(ii)/y, exp_xs.GetErrorYhigh(ii)/y);
      exp2_ratio_xs.SetPoint(ii, x,  1 );
      exp2_ratio_xs.SetPointError(ii, exp2_xs.GetErrorXlow(ii), exp2_xs.GetErrorXhigh(ii), 0, 0);
      obs_xs.GetPoint(ii, x, yobs);
      obs_ratio_xs.SetPoint(ii, x,  yobs/y );
      obs_ratio_xs.SetPointError(ii, obs_xs.GetErrorXlow(ii), obs_xs.GetErrorXhigh(ii), obs_xs.GetErrorYlow(ii)/y, obs_xs.GetErrorYhigh(ii)/y);
    }
    
    exp_ratio_xs.SetFillStyle(3004);
    exp_ratio_xs.GetYaxis()->SetTitleOffset(1.6);
    exp_ratio_xs.GetXaxis()->SetTitle((m_sigUnfLabels[m_Variable].at(0).c_str()));
    exp_ratio_xs.GetYaxis()->SetTitle("Obs/SM");
    exp_ratio_xs.SetFillColor(kBlue);
    exp_ratio_xs.SetMarkerSize(0);
    exp2_ratio_xs.SetMarkerSize(0);
    exp2_ratio_xs.SetLineColor(kBlue);
    
    exp_ratio_xs.GetYaxis()->SetNdivisions(505);
    exp_ratio_xs.GetYaxis()->SetTitleSize(20);
    exp_ratio_xs.GetYaxis()->SetTitleFont(43);
    exp_ratio_xs.GetYaxis()->SetTitleOffset(1.55);
    exp_ratio_xs.GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    exp_ratio_xs.GetYaxis()->SetLabelSize(15);

    exp_ratio_xs.GetXaxis()->SetTitleSize(20);
    exp_ratio_xs.GetXaxis()->SetTitleFont(43);
    exp_ratio_xs.GetXaxis()->SetTitleOffset(3);
    exp_ratio_xs.GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    exp_ratio_xs.GetXaxis()->SetLabelSize(15);
    
    exp_ratio_xs.GetXaxis()->SetRangeUser(0, accumulate(m_binwidth.begin(), m_binwidth.end(), 0.0));
    
    exp_ratio_xs.GetYaxis()->SetRangeUser(0., 2);
    
    exp_ratio_xs.GetXaxis()->SetRangeUser(0, accumulate(m_binwidth.begin(), m_binwidth.end(), 0.0));
    
    //obs_xs.Draw("ap");
    
    exp_ratio_xs.Draw("a2");
    
    exp2_ratio_xs.Draw("p,same");
    obs_ratio_xs.Draw("p,same");
    obs_xs.SetNameTitle(m_Variable.c_str(),m_Variable.c_str());
    obs_xs.SaveAs((m_OutDir+"/fit_"+m_Variable+"_"+conference+sysname+what+"_TGunfolded.root").c_str()); 
    c_single.SaveAs((m_OutDir+"/fit_"+m_Variable+"_"+conference+sysname+what+"_unfolded.eps").c_str());
    c_single.SaveAs((m_OutDir+"/fit_"+m_Variable+"_"+conference+sysname+what+"_unfolded.root").c_str());
    
  }

  if ( m_Fiducial ) {
    obs_xs.SetNameTitle(m_Variable.c_str(),m_Variable.c_str());
    obs_xs.SaveAs((m_OutDir+"/fit_"+m_Variable+"_"+conference+sysname+what+"_TGunfolded.root").c_str());
  }
  tablefile.close();
  resultsfile.close();
  vector_postfit.clear();
  vector_prefit.clear();
  delete t;
  delete tmp;
  delete p_data;
  delete nll;
  delete minim;
  delete iteratorPOI;
  delete m_scan_plot;
  delete sigma1;
  delete sigma2;
  delete sigma3;
  delete sigma4;

}

void WorkSpaceMaker :: MakeMGDataset(){
  
  cout << "\033[2;33m <MakeMGDataset()>:: MakeMGDataset \033[0m" << endl;
  if( m_Variable!="m12m34" ){
    cout << "\033[1;31m <MakeMGDataset()>:: MakeMGDataset m12m34 only!!! "
	 << " \033[0m" << endl;
    exit (0);
  }
  
  //TH1F* powheg   = (TH1F*) m_InFile->Get("hpt_incl_ggH");
  TH1F* madgraph = (TH1F*) m_InFile->Get("hm12m34_incl_MG5");
  TH1F* vbfh = (TH1F*) m_InFile->Get("hm12m34_incl_VBF");
  TH1F* whh = (TH1F*) m_InFile->Get("hm12m34_incl_WH");
  TH1F* zhh = (TH1F*) m_InFile->Get("hm12m34_incl_ZH");
  TH1F* tthh = (TH1F*) m_InFile->Get("hm12m34_incl_ttH");
  TH1F* bbhh = (TH1F*) m_InFile->Get("hm12m34_incl_bbH");

  TH1F* allZZh    = (TH1F*) m_InFile->Get("hm12m34_incl_AllZZ");
  TH1F* redbkgh    = (TH1F*) m_InFile->Get("hm12m34_incl_Zjets");
  TH1F* multibosonh    = (TH1F*) m_InFile->Get("hm12m34_incl_MultiBoson");
  
  //madgraph->Scale(powheg->Integral()/madgraph->Integral());
  madgraph->Add(vbfh);
  madgraph->Add(whh);
  madgraph->Add(zhh);
  madgraph->Add(tthh);
  madgraph->Add(bbhh);
  madgraph->Add(allZZh);
  madgraph->Add(redbkgh);
  madgraph->Add(multibosonh);
  madgraph->Scale(m_Lumi->getVal());
  
  std::map< std::string, TH1 * > histMap;
  
  TH1F* binH = NULL;
  for (unsigned int i=0; i < m_Category.size(); ++i){
    
    binH = new TH1F(("bin_"+m_Category.at(i)).c_str(), ("bin_"+m_Category.at(i)).c_str(), 1, 0, 1);
    binH->SetBinContent(1,madgraph->GetBinContent(i+1));
    
    histMap[m_Category.at(i)] = binH;
    
  }
  
  RooDataHist *m_mgdata = new RooDataHist ("asimovDataFullModel_MG","asimovDataFullModel_MG", *m_x, *m_sample,  histMap, 1.);
  
  m_mgdata->Print();
  
  m_ws->import(*m_mgdata);

  
}


void WorkSpaceMaker :: PlotPdf (RooSimultaneous *pdf, RooDataSet *Asimov,
				RooDataSet *combData){

  TCanvas *oneD = new TCanvas("1D","1D",800,800);
  TLegend *leg = new TLegend(0.70,0.73,0.90,0.91);
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);

  TH1F *h_xAll = NULL;
  h_xAll = new TH1F("h_xAll", "h_xAll", m_Category.size(), 0, m_Category.size());

  TH1F *h_xbkg = NULL;
  h_xbkg = new TH1F("h_xbkg", "h_xbkg", m_Category.size(), 0, m_Category.size());
  TH1F *h_xbkgredBkg= NULL;
  h_xbkgredBkg = new TH1F("h_xbkgredBkg", "h_xbkgredBkg", m_Category.size(), 0, m_Category.size());

  TGraphAsymmErrors tgdata;
  TGraphAsymmErrors tgdata_real;
  
  RooPlot* frame = NULL;
  RooPlot* frame_tmp = NULL;
  double x, y;

  for (unsigned int i = 0; i< m_Category.size(); ++i){
    frame = m_x->frame(Title((m_Category.at(i)).c_str())) ;    
    frame_tmp = m_x->frame(Title((m_Category.at(i)+"_tmp").c_str())) ;    

    combData->plotOn(frame_tmp,Cut(("channelCat==channelCat::"+m_Category.at(i)).c_str()), DataError(RooAbsData::Poisson)) ;
    RooHist *data_tmp = (RooHist *) frame_tmp->getObject(0);
    data_tmp->GetPoint(0, x, y);
    tgdata.SetPoint(i, x+i,  y/m_binwidth.at(i) );
    tgdata.SetPointError(i, 0, 0, data_tmp->GetErrorYlow(0)/m_binwidth.at(i), data_tmp->GetErrorYhigh(0)/m_binwidth.at(i));

    Asimov->plotOn(frame,Cut(("channelCat==channelCat::"+m_Category.at(i)).c_str()), DataError(RooAbsData::Poisson)) ;

    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov));
    RooHist *all = (RooHist *) frame->getObject(1);
    all->GetPoint(1, x, y);
    h_xAll->SetBinContent(i+1,y/m_binwidth.at(i));

    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov),Components(("pdf_ext_"+m_Category.at(i)+"*Z*").c_str()));
    RooHist *bkg = (RooHist *) frame->getObject(2);
    bkg->GetPoint(1, x, y);
    h_xbkg->SetBinContent(i+1,y/m_binwidth.at(i));

    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov),Components(("pdf_ext_"+m_Category.at(i)+"*redBkg").c_str())) ;
    RooHist *bkgredBkg = (RooHist *) frame->getObject(3);
    bkgredBkg->GetPoint(1, x, y);
    h_xbkgredBkg->SetBinContent(i+1,y/m_binwidth.at(i));
 
  }

  h_xAll->SetLineColor(kBlack); h_xAll->SetFillColor(kBlue); h_xAll->SetLineWidth(1);
  /*h_xbkg->Add(h_xbkgredBkg);*/ h_xbkg->SetLineColor(kBlack); h_xbkg->SetFillColor(kRed); h_xbkg->SetLineWidth(1);   
  h_xbkgredBkg->SetLineColor(kBlack); h_xbkgredBkg->SetFillColor(kViolet); h_xbkgredBkg->SetLineWidth(1);   

  tgdata.SetMarkerStyle(9); tgdata.SetMarkerColor(kBlack); tgdata.SetLineWidth(kBlack); tgdata.SetLineColor(kBlack);

  for (int j =1; j < h_xAll->GetNbinsX()+1; ++j) {
    stringstream streamlow;
    stringstream streamup;
    streamlow << setprecision(3) << m_binnames.at(j-1);
    string slow = streamlow.str();
    streamup << setprecision(3) << m_binnames.at(j);
    string sup = streamup.str();
    h_xAll->GetXaxis()->SetBinLabel(j,(slow+"-"+sup).c_str());
  }

  h_xAll->Draw("h");
  h_xAll->SetMinimum(0);
  h_xAll->SetMaximum(1.85*h_xAll->GetMaximum());
  h_xAll->GetYaxis()->SetTitle( m_shapeLabels[m_Variable].at(1).c_str() );
  h_xAll->GetYaxis()->SetTitleOffset(1.5);
  h_xAll->GetXaxis()->SetTitle( m_shapeLabels[m_Variable].at(0).c_str() );
  h_xbkg->Draw("same");
  h_xbkgredBkg->Draw("same");
  tgdata.Draw("p,same");

  
  leg->AddEntry(h_xAll, "Signal", "f");
  leg->AddEntry(h_xbkg, "ZZ^{*}", "f");
  leg->AddEntry(h_xbkgredBkg, "Z+jets", "f");
  if (m_WithData) leg->AddEntry(&tgdata, "Data", "pel");
  else  leg->AddEntry(&tgdata, "Asimov Data", "pel");
  leg->Draw("same");
  
  drawEnergyLumi();
  drawChannel();
  std::cout << "porco dio " << std::endl;
  
  string what = "expected";
  if ( m_WithData ) what = "data";

  drawATLASInternal();
  gPad->RedrawAxis();
  oneD->SaveAs( (m_OutDir+"/shape_"+m_Variable+"_"+what+".eps").c_str() );
 
  if( m_do2D ){
    TH2F *h_s2D = new TH2F("h_s2D", "h_s2D", m_v_pdfaddlist.size(), 0, m_pdfcategory.size(), m_Mbins, 115, 130);

    for (unsigned int i = 0; i< m_v_pdfaddlist.size(); ++i){
      TH1* hspectrum = m_v_pdfaddlist.at(i).createHistogram( ("pt vs m4l"+to_string(i)).c_str(),
                                                   *m_x, Binning(1), YVar(*m_m4l,Binning(m_Mbins)) );
      for (int j = 0; j< hspectrum->GetNbinsY(); ++j)
        h_s2D->SetBinContent(i+1,j+1, hspectrum->GetBinContent(1,j+1)/m_binwidth.at(i));
    }
    h_s2D->Draw("COLZ");
    oneD->SaveAs( (m_OutDir+"/shape2D_"+m_Variable+"_"+what+".eps").c_str() );
    h_s2D->Draw("LEGO2");
    oneD->SaveAs((m_OutDir+"/shape3D_"+m_Variable+"_"+what+".eps").c_str() );
    delete h_s2D;

  }
  delete oneD;
}


void WorkSpaceMaker :: PlotPdfFiducial (RooSimultaneous *pdf,
					RooDataSet *Asimov,
					RooDataSet *combData){

  cout << "\033[1;39m <PlotPdfFiducial()> \033[0m" << endl;
  
  vector<int> color;
  color.push_back(600); //kRed
  color.push_back(600); //kBlue
  color.push_back(600); //kGreen
  color.push_back(600); //kViolet
  
  if ( color.size() != m_Category.size() ){
    cout << "\033[1;31m <PlotPdfFiducial()>:: m_Category size != number of colors !\033[0m" << endl;
    cout << "\033[1;31m exit!\033[0m" << endl;
    exit(0);
  }
  RooPlot* frame = NULL;
  TCanvas* c = new TCanvas("pdf","pdf",1200,1200) ;
  c->Divide(2,2) ;

  for (unsigned int i = 0; i < color.size() ; i ++){
    frame = m_x->frame(Bins(m_Mbins),Title(m_Category.at(i).c_str())) ;
    combData->plotOn(frame,Cut(("channelCat==channelCat::"+m_Category.at(i)).c_str()), MarkerColor(kBlack),LineColor(kBlack),DataError(RooAbsData::Poisson)) ;
    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1)) ;
    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(kBlue)) ;
    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(kRed),Components(("pdf_ext_"+m_Category.at(i)+"*Z*").c_str())) ;
    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1),Components(("pdf_ext_"+m_Category.at(i)+"*Z*").c_str())) ;
    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(kViolet),Components(("pdf_ext_"+m_Category.at(i)+"*redBkg").c_str())) ;
    pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1),Components(("pdf_ext_"+m_Category.at(i)+"*redBkg").c_str())) ;

    combData->plotOn(frame,Cut(("channelCat==channelCat::"+m_Category.at(i)).c_str()), MarkerColor(kBlack), LineColor(kBlack),DataError(RooAbsData::Poisson)) ;
    c->cd(i+1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  }
  
  drawATLASInternal();
  string what = "expected";
  if ( m_WithData ) what = "data";
  c->SaveAs( (m_OutDir+"/fiducialPdf_"+what+".eps").c_str() );
  delete c;
  delete frame;
}

void WorkSpaceMaker :: Closing(){
  
  cout << endl;
  cout << "|                      " << "           / l+        " << endl;
  cout << "|   *                  " << "          /            " << endl;
  cout << "|     *                " << "         /\\           " << endl;
  cout << "|  *   *               " << "     Z  /  \\ l-       " << endl;
  cout << "|        *             " << " H_____/               " << endl;
  cout << "| *        *           " << "       \\              " << endl;
  cout << "|             *        " << "     Z* \\  / l+       " << endl;
  cout << "|*                 *   " << "         \\/           " << endl;
  cout << "|______________________" << "          \\           " << endl;
  cout << "                       " << "           \\ l-       " << endl;
  cout << "                                                    " << endl;
  cout << "                MEASUREMENT DONE !                  " << endl;
  
}


void WorkSpaceMaker :: Parallel() {

  cout << "\033[1;39m WARNING!!! <DoWS>:: Parallel() fit not working yet... printing memory address of the threads\033[0m" << endl;
  cout << "\033[1;39m this is just a preliminary implementation it will be available soon                         \033[0m" << endl;
  m_NThreads = 8;
  m_ThreadNextItem = 0;
  m_Threads.resize(m_NThreads);
  m_ThreadIsInitialized.resize(m_NThreads);
  m_ThreadIsFinished.resize(m_NThreads);

  if (m_NThreads > 1) {
    
    // Start threads
    for (unsigned int t = 0; t < m_NThreads; ++t) {
      TString Name = "Calibration thread #";
      Name += t;
      cout<<"Creating thread: "<<Name<<endl;
      //TThread* Thread = new TThread(Name, (void(*) (void *)) &CallParallelCalibrationThread, (void*) 0);
      TThread* Thread = new TThread("t0", (void(*) (void *)) &WorkSpaceMaker::CallParallelCalibrationThread, (void*) 1, TThread::EPriority::kNormalPriority);
      m_Threads[t] = Thread;
      Thread->Run();
    }    

  }     
    cout<<"All threads have finished"<<endl;
  
}

void WorkSpaceMaker::CallParallelCalibrationThread( void* Address )
{

  cout << Address << " " << endl;

}

void WorkSpaceMaker :: PlotSysBands (){

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
  TCanvas c("pdf","pdf", 800,800);

  TH1* hh_pdf = NULL;
  int bin = m_Category.size();
  if(m_Fiducial) bin = 15;
  
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
      
      cout << "\033[1;32m Printing histo sys: \033[0m " 
	   << m_Variable << " " << m_Category.at(i) << " "
	   << syssplitname.at(i_sys)  << endl;

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
	  if( string(var->GetName()).find(syssplit.at(i_sys) ) == std::string::npos ) continue ;
	
	if (syssplit.at(i_sys)=="sig"){
	  if ( string(var->GetName()).find("sig") == std::string::npos &&
	       string(var->GetName()).find("Sig") == std::string::npos &&
	       string(var->GetName()).find("Mass") == std::string::npos )
	    continue ;
	}
	
	if (m_debug)
	  cout <<    var->GetName() << "  " << syssplitname.at(i_sys) << "  " <<m_Category.at(i)  << endl;
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
      hh_pdfnominal = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram(varname.c_str(),15);
      hh_pdfnominal->SetNameTitle(("nom"+m_Category.at(i)).c_str(),("nom"+m_Category.at(i)).c_str());
      
      myWS->var(shapesname.at(jj).c_str())->setVal(1);
      hh_pdfup = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram(varname.c_str(),15);
      hh_pdfup->SetNameTitle(("up"+m_Category.at(i)).c_str(),("up"+m_Category.at(i)).c_str());
      
      myWS->var(shapesname.at(jj).c_str())->setVal(-1);
      hh_pdfdown = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram(varname.c_str(),15);
      hh_pdfdown->SetNameTitle(("down"+m_Category.at(i)).c_str(),("down"+m_Category.at(i)).c_str());

      TCanvas ctmp("pdftmp","pdftmp", 800,800);
      
      hh_pdfnominal->SetLineColor(kBlack);hh_pdfnominal->SetLineWidth(2);
      hh_pdfnominal->GetYaxis()->SetRangeUser(0,hh_pdfnominal->GetMaximum()*1.2);
      hh_pdfnominal->Draw();
      hh_pdfup->SetLineColor(kBlue);hh_pdfup->SetLineWidth(2);
      hh_pdfup->Draw("same");
      hh_pdfdown->SetLineColor(kRed);hh_pdfdown->SetLineWidth(2);
      hh_pdfdown->Draw("same");
      
      ctmp.SaveAs( ("~/Desktop/sys"+shapesname.at(jj)+".pdf").c_str() );

      myWS->var(shapesname.at(jj).c_str())->setVal(0);
      
    }
    //exit(0);
  }
  
  it->Reset();
  while( (var = (RooRealVar*)it->Next()) ){
    myWS->var(var->GetName());
    myWS->var(var->GetName())->setVal(0);
  }
  
}

void WorkSpaceMaker :: PlotM4l (){
  
  TH1* hh_pdf = NULL;
  
  RooWorkspace *myWS = (RooWorkspace*) m_ws->Clone();
  string outName = m_OutDir+"/hm_h"+m_Variable;
  if(m_WithData){ outName += "_data";     }
  else{           outName += "_expected"; } 
  TFile* _m4loutput = new  TFile( (outName+".root").c_str(), "recreate");
  _m4loutput->cd();
  _m4loutput->Print();
  
  std::string varws = "m4l";
  for (unsigned int i = 0; i< m_Category.size(); ++i){
    
    if(m_FidChan) varws = "x";
    
    if ( m_addSys ) hh_pdf = myWS->pdf(("model_incl_sys_"+m_Category.at(i)).c_str())->createHistogram(varws.c_str(),15, 115, 130);
    else hh_pdf = myWS->pdf(("model_incl_nosys_"+m_Category.at(i)).c_str())->createHistogram(varws.c_str(),15, 115, 130);
    hh_pdf->SetNameTitle(("hm_"+m_Variable+m_Category.at(i)).c_str(),("hm_"+m_Variable+m_Category.at(i)).c_str());
    hh_pdf->Write();
  }
  _m4loutput->Close();
  
}


