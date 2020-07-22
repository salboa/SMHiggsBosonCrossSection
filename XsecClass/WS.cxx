#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: DoWS(){

  PRINT_BEGIN_FUNCTION("<DoWS()>:: build workspace");
  CreateOutDir();
  DoSimPdf();
  DefineWS();
  DefineModelConfig();
  RooDataSet *combData = (RooDataSet*)RooStats::AsymptoticCalculator::MakeAsimovData(*m_modelConfig,  m_list /* it should be all variables */, m_list);
  combData->SetNameTitle("asimovDataFullModel","asimovDataFullModel");
  m_ws->import(*combData);
  if ( m_WithData ) ImportData();
  if ( m_useMCData ) MakeMCDataset();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle( 0 );

  if(!m_WithData && m_Fiducial)                  PlotPdfFiducial(m_simPdf,combData,combData);
  if(m_WithData && m_Fiducial)                   PlotPdfFiducial(m_simPdf,combData,(RooDataSet*)m_obsdata);
  if(!m_WithData && !m_Fiducial && !m_useMCData) PlotPdf(m_simPdf,combData);
  if(!m_WithData && !m_Fiducial && m_useMCData)  PlotPdf(m_simPdf,(RooDataSet*)m_ws->data("asimovDataFullModel_MC"));
  if(m_WithData && !m_Fiducial)                  PlotPdf(m_simPdf,(RooDataSet*)m_obsdata);

  if(m_FidSum)   doFiducialSumChannels();
  if(m_Fid4l)    doFiducial4l();
  if(m_Fid2l2l)  doFiducial2l2l();
  if(m_FidTotal) doFiducialTotal();
  if(m_FidComb)  doFiducialComb();
  if(m_FidChan)  doFiducialSingleChannel();
  if(m_BRDiff)   doFiducialBRDifference();

  PRINT_DEBUG("<DoWS()>:: DataSet");
  PRINT_DEBUG_OBJECT(m_modelConfig);
  PRINT_DEBUG_OBJECT(combData);
  
  if(m_addSys && m_sysBands) PlotSysBands();
  CleanUp();

  m_wsname = m_OutDir+"/ws_"+m_Variable;
  if(m_ProdMode!="AllSig") m_wsname += "_"+m_ProdMode;
  if(m_addSys)             m_wsname += "_wsys";
  if(m_fixSys!="NO")       m_wsname += "_fixing_"+m_fixSys;
  if(m_WithData)           m_wsname += "_data";
  else                     m_wsname += "_expected";
  if(!m_floatqqZZ)	   m_wsname += "_ZZfixed";
  if(m_matrix)             m_wsname += "_mtx";
  else                     m_wsname += "_cf";
                           m_wsname += "_v20v2";
  if(m_addAsys)            m_wsname += "_asys";


  if(m_dofit){
    PRINT_INFO(" <DoWS()>:: calling DoQuickTest() ");
    DoQuickTest();
    if(m_skipScan && m_chSplit!=1){ //for now this doesn't work for 4l+2l2l fit
      if(m_WithData && !m_Fiducial)                  PlotPdf(m_simPdf,(RooDataSet*)m_obsdata,true);
      if(m_WithData && !m_Fiducial)                  PlotPdfSplitXS(m_simPdf,(RooDataSet*)m_obsdata,true);
      //if(!m_WithData && !m_Fiducial)                 PlotPdfSplitXS(m_simPdf,(RooDataSet*)combData,true); uncomment here to observe the splitting BUT in conflict with PlotPdf
      if(!m_WithData && !m_Fiducial && !m_useMCData) PlotPdf(m_simPdf,combData,true);
    }
    Closing();
  }

  else m_ws->writeToFile( (m_wsname+".root").c_str() );
  if (m_parallel) Parallel();
  PRINT_END_FUNCTION("<DoWS()>");

}

void WorkSpaceMaker :: DoSimPdf(){

  PRINT_DEBUG_FUNCTION(" <DoSimPdf()>:: making sim PDF");
  DoAddPdf();
  DefineCategories();
  RooProdPdf* tmp_prodPdf = NULL;
  m_simPdf = new RooSimultaneous("simPdf", "simPdf", *m_sample);
  for (unsigned int i = 0; i< m_pdfcategory.size(); ++i){
    PRINT_DEBUG ("<DoSimPdf()>:: PdfAddList");
    PRINT_DEBUG_OBJECT(&m_v_pdfaddlist.at(i));
    if(m_addSys || m_addShapeSys){
      tmp_prodPdf = ApplySys(&m_v_pdfaddlist.at(i));
      m_simPdf->addPdf(*tmp_prodPdf, (m_Category.at(i)).c_str());
    }
    else
      m_simPdf->addPdf(m_v_pdfaddlist.at(i), (m_Category.at(i)).c_str());
  }
  PRINT_DEBUG ("DoSimPdf()>:: RooSimPdf");
  PRINT_DEBUG_OBJECT(m_simPdf);
}

void WorkSpaceMaker :: DefineCategories(){

  PRINT_DEBUG_FUNCTION(" <DefineCategories()>:: Categories");
  string incl = GetChannelName(m_ChNum);
  m_sample = new RooCategory("channelCat", "channelCat");
  if ( m_Channel.compare(incl)==0 )
    for (unsigned int i = 0; i< m_pdfcategory.size(); ++i){
      m_sample->defineType((m_Category.at(i)).c_str(),i); // to be optimized for 4 separate channels
    }
  
}

void WorkSpaceMaker :: DoAddPdf(){

  PRINT_DEBUG_FUNCTION(" <DoAddPdf()>:: PDF ");
  RooAddPdf* addPdf = NULL;

  for (unsigned int i = 0; i< m_pdfcategory.size(); ++i){
    addPdf = new RooAddPdf( ("model_"+m_Channel+"_nosys_"+m_Category.at(i)).c_str(),
                            ("model_"+m_Channel+"_nosys_"+m_Category.at(i)).c_str(),
                             m_pdfcategory.at(i), m_Normpdfcategory.at(i) );
    PRINT_DEBUG_OBJECT(addPdf);
    m_v_pdfaddlist.push_back(*addPdf);
    m_pdfaddlist.add(*addPdf);
  }
  delete addPdf;
  
}

RooProdPdf* WorkSpaceMaker :: ApplySys(RooAddPdf* addPdf){

  PRINT_DEBUG_FUNCTION(" <ApplySys()>:: SYS ");
  PRINT_DEBUG_OBJECT(&m_listpdf_np);
  RooArgList listpdf;
  listpdf.add(*addPdf);
  listpdf.add(m_listpdf_np);
  if (m_addShapeSys)   listpdf.add(m_listpdf_npshapes);
  RooProdPdf* prodPdf = new RooProdPdf ( TString(addPdf->GetName()).ReplaceAll("nosys","sys"),
					 TString(addPdf->GetName()).ReplaceAll("nosys","sys"),
					 listpdf );
  PRINT_DEBUG_OBJECT(prodPdf);
  return prodPdf;
  
}

void WorkSpaceMaker :: DefineWS(){

  PRINT_DEBUG_FUNCTION(" <DefineWS()>:: defining the WS ");
  m_ws = new RooWorkspace("myWS");
  RooRealVar* tmp = NULL;
  TIterator *iteratorGlobalObs= m_list.createIterator();
  while ( (tmp = (RooRealVar*)iteratorGlobalObs->Next()) ) {
    if (string(tmp->GetName())!="dummyvar")tmp->setConstant(1);
  }
  TIterator *iteratorPOI= m_paramOfInterest->createIterator();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) tmp->setConstant(0);
  m_ws->import(*m_simPdf);
  PRINT_DEBUG_OBJECT(m_ws,1);
  
}

void WorkSpaceMaker :: DefineModelConfig(){

  PRINT_DEBUG_FUNCTION(" <DefineModelConfig()>:: ModelConfig");
  m_modelConfig = new RooStats::ModelConfig(m_ws);
  m_modelConfig->SetPdf(*m_simPdf);
  PRINT_DEBUG_OBJECT(m_paramOfInterest);
  m_modelConfig->SetParametersOfInterest(*m_paramOfInterest);
  RooRealVar weightVar("weightVar", "weightVar", 1, 0.,2.);
  if (m_do2D) m_observables.add(*m_m4l);
  m_observables.add(*m_sample);
  m_observables.add(weightVar);
  m_modelConfig->SetObservables(m_observables);
  m_modelConfig->SetGlobalObservables( m_globalObservables);
  if (m_addShapeSys)   m_listNP.add(m_listNPshapes);
  m_modelConfig->SetNuisanceParameters( m_listNP );
  m_modelConfig->SetName("ModelConfig");
  m_ws->import(*m_modelConfig);
  PRINT_DEBUG_OBJECT(m_modelConfig,1);
  
  TIterator *iteratorPOI= m_modelConfig->GetParametersOfInterest()->createIterator();
  RooRealVar *tmp=NULL;
  if (m_matrix){ 
    while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) {
      TString name = tmp->GetName();
      name.ReplaceAll("sigma_","");
    
      TString ch = name;
      if(!m_Fiducial) ch = ch.Replace(0,ch.First("_")+1,"");
      m_ws->var( ("sigma_"+name) )->setVal( m_ws->var(("sigma_"+name))->getVal()*
                                           m_ws->var(("r_"+name))->getVal() );
      m_ws->var( ("r_"+name) )->setVal(1);
    }
  }
  if (!m_FidTotal) m_ws->saveSnapshot("total",m_ws->allVars());

  //RooRealVar *tmp;
  //TIterator *iteratorPOI= m_modelConfig->GetParametersOfInterest()->createIterator();
  iteratorPOI->Reset();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) { 
    tmp->setConstant(0);
  }
  
}

void WorkSpaceMaker :: ImportData(){

  PRINT_DEBUG_FUNCTION(" <ImportData()>:: ImportData ");

  map<string,TH1*> hmapd;
  //map<string,RooDataHist*> hmapd2d;
  map<string,TH1*> hmapd2d;
  
  bool ZZd = false;
  if ( m_DataSet != "" ) ZZd = true;

  if ( !m_Fiducial ){
    if ( !ZZd ) m_h = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_"+GetChannelName(0)+"_data").c_str() );
    else m_h = (TH1F*)m_InFile->Get( m_DataSet.c_str() );

    m_h_remapped = remapHisto ( m_h, (int)m_Category.size() ) ;

    for(int i = 0; i < m_h_remapped->GetNbinsX(); ++i )
      m_h_remapped->SetBinContent(i+1, m_h_remapped->GetBinContent(i+1)* m_binwidth.at(i) );

    if( !m_do2D ){
      for( int i=0; i < (int)m_Category.size(); i++ ){
        m_tmp = new TH1F (("data_"+to_string(i)).c_str(),("data_"+to_string(i)).c_str(),1, 0, 1) ; ;
        m_tmp->Reset();
        m_tmp->SetBinContent( 1, m_h_remapped->GetBinContent(i+1) );
        //if (i ==2) m_tmp->SetBinContent( 1, m_h_remapped->GetBinContent(i+1)*2 );
        hmapd[m_Category.at(i).c_str()] = m_tmp;
      }
    }

    if( m_do2D ){
      for( int i=0; i < (int)m_Category.size(); i++ ){
        m_h = (TH1F*)m_InFile->Get( ("hm_"+m_Variable+"bin"+to_string(i)+"_"+GetChannelName(0)+"_data").c_str() );
	if(m_redM4lBins) m_h->Rebin(3);
        m_h = remapHisto(m_h, m_Mbins);
        hmapd2d[m_Category.at(i).c_str()] = m_h;
      }
    }

    if( m_do2D )
      m_obsdata = new RooDataHist ("obsData","obsData",
                                   RooArgList(RooArgSet(/**m_x,*/ *m_m4l)),
                                   *m_sample, hmapd2d);
                       
    else
      m_obsdata = new RooDataHist ("obsData","obsData", *m_x, *m_sample,
                                   hmapd, 1.);
    m_obsdata->Print();
  }

  if ( m_Fiducial ){

    for( int i=0; i < (int)m_Category.size(); i++ ){
      /// start from 1 needed see enum associated                                                                                                                                                                                     
      m_h = (TH1F*)m_InFile->Get( ("h"+m_Variable+"_"+GetChannelName(i+1)+"_data").c_str() );
      if(m_redM4lBins) m_h->Rebin(3);
      m_h_remapped = remapHisto ( m_h, m_h->GetNbinsX() ) ;
      hmapd[m_Category.at(i).c_str()] = m_h_remapped;
    }

    m_obsdata = new RooDataHist ("obsData","obsData", *m_x, *m_sample,
                                 hmapd, 1.);
  }
  m_ws->import(*m_obsdata);

}

void WorkSpaceMaker :: MakeMCDataset(){
  
  PRINT_DEBUG_FUNCTION(" <MakeMCDataset()>:: MakeMCDataset");
  TH1F* madgraph = (TH1F*) m_InFile->Get(("h"+m_Variable+"_"+m_Channel+"_"+m_ProdHist).c_str());
  int factor = 1 ;
  if (m_ProdHist == "ggH" || m_ProdHist == "incl") { factor = 1; }
  else if (m_ProdHist == "VBF") { factor = 80; }
  else if (m_ProdHist == "WH" || m_ProdHist == "ZH" || m_ProdHist == "ttH") { factor = 1000; }
  if( factor!= 1) PRINT_WARNING(" Signal("+ m_ProdHist + ") scaled by factor: "+ to_string(factor));
  for (unsigned int i=0; i < m_Category.size(); ++i){
    madgraph->SetBinContent(i+1, madgraph->GetBinContent(i+1)*factor);
  }
  TH1F* hBkg    = (TH1F*) m_InFile->Get(("h"+m_Variable+"_"+m_Channel+"_"+m_BkgHist).c_str());
  madgraph->Add(hBkg);
  madgraph->Scale(m_Lumi->getVal());
  RooDataHist *m_mcdata = NULL;
  map< string, TH1 * > histMap;
  TH1F* binH = NULL;
  TH2F* binH2D = NULL;
  if (!m_do2D) {
   for (unsigned int i=0; i < m_Category.size(); ++i){
     binH = new TH1F(("bin_"+m_Category.at(i)).c_str(), ("bin_"+m_Category.at(i)).c_str(), 1, 0, 1);
     binH->SetBinContent(1,madgraph->GetBinContent(i+1)*m_binwidth.at(i));
     histMap[m_Category.at(i)] = binH;
    }
    m_mcdata = new RooDataHist ("asimovDataFullModel_MC","asimovDataFullModel_MC", *m_x, *m_sample,  histMap, 1.);
  }
  else{
    for (unsigned int i=0; i < m_Category.size(); ++i){
      binH = (TH1F*) m_InFile->Get(("hm_"+m_Variable+m_Category.at(i)+"_"+m_ProdHist).c_str()) ;
      if (binH==NULL){
        string name = "hm_"+m_Variable+m_Category.at(i)+"_"+m_ProdHist;
        PRINT_FATAL("Histogram: " + name + " not found, exit(0)!");
        exit(0);
      }
      binH->Scale(factor); // signal scaled if needed: VBF, VH, ttH
      hBkg = (TH1F*) m_InFile->Get(("hm_"+m_Variable+m_Category.at(i)+"_"+m_Channel+"_"+m_BkgHist).c_str()) ;
      if (binH==NULL){
        string name = "hm_"+m_Variable+m_Category.at(i)+"_"+m_BkgHist;
        PRINT_FATAL("Histogram: " + name + " not found, exit(0)!");
        exit(0);
      }
      binH->Add(hBkg);
      binH->Scale(m_Lumi->getVal());
      binH2D = new TH2F (("h2Dm_"+m_Variable+m_Category.at(i)+"_"+m_Channel+"_"+m_ProdHist).c_str(),("h2Dm_"+m_Variable+m_Category.at(i)+"_"+m_Channel+"_"+m_ProdHist).c_str(), 1, 0., 1., binH->GetNbinsX(), binH->GetXaxis()->GetXmin(),  binH->GetXaxis()->GetXmax());
      for ( int j =0 ; j < binH->GetNbinsX(); ++j ) binH2D->SetBinContent(1,j+1, binH->GetBinContent(j+1));
      histMap[m_Category.at(i)] = (TH1*) binH2D;
      if( m_debug ) histMap[m_Category.at(i)]->Print();
    }
    m_mcdata = new RooDataHist ("asimovDataFullModel_MC","asimovDataFullModel_MC", RooArgList(*m_x, *m_m4l), *m_sample,  histMap, 1.);
  }
  PRINT_DEBUG_OBJECT( m_mcdata );
  m_ws->import(*m_mcdata);
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

  cout << "\033[1;39m WARNING!!! <WorkSpaceMaker::Parallel()>:: parallel fit not working yet... printing memory address of the threads\033[0m" << endl;
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

void WorkSpaceMaker::CallParallelCalibrationThread( void* Address ){

  cout << Address << " " << endl;

}
