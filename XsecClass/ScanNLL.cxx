/*  simple macro for NNL scan
    authors: A. Gabrielli , R. Di Nardo */

#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: ScanNLL(TString wsPath, TString wsName, int nSteps,
			       TString constPOI, double low, double up,
			       TString dataType, TGraph *scan_plot,
			       vector<double> vector_postfit, int bin){
            
  defineCoutDetails();

  RooAbsArg* arg3;

  RooFIter iter3 = m_ws->components().fwdIterator();
  
  while ((arg3 = iter3.next())) {
    if (arg3->IsA() == RooStarMomentMorph::Class()) {
      ((RooStarMomentMorph*)arg3)->fixCache();
    }
  }

  vector<double> tmp_twonll;
  vector<double> tmp_sigma;

  RooAbsData *p_data =  m_ws->data(dataType);

  RooRealVar *firstPOI = m_ws->var(constPOI);
  firstPOI->setConstant(true);
  //double val = m_ws->var(constPOI)->getVal();
  firstPOI->setRange(low, up);
  double delta = (up-low)/nSteps;
  double val_to_set =-1.;
  
  TStopwatch stopwatch;
  TStopwatch stopwatchinterval;
  vector <double> time;
  cout << "***************" << endl;
  
  SetNtupla(m_ws);
  for (int ii =0; ii<nSteps; ++ii){
    if (!m_Fiducial)m_ws->loadSnapshot("postfit");
    if (m_fixSys!= "NO") FixSysForFit ( m_fixSys );
/*
    if (constPOI != "sigma") for ( unsigned int i =0 ; i< vector_postfit.size(); ++i)
m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setVal(vector_postfit.at(i));
else m_ws->var("sigma")->setVal(vector_postfit.at(0));
*/
    RooMinimizer *minim=NULL;
    RooAbsReal *nll=NULL;
    val_to_set = low+(double)ii*delta;
    
    stopwatch.Start();
    firstPOI->setVal(val_to_set);
    firstPOI->setConstant(true);
         
    RooSimultaneous *simPdf = (RooSimultaneous*) m_ws->pdf("simPdf");

    nll=simPdf->createNLL( *p_data, RooFit::CloneData(kFALSE),
			   RooFit::Constrain(*m_modelConfig->GetNuisanceParameters()),
			   RooFit::Offset(kTRUE),
			   RooFit::GlobalObservables(*m_modelConfig->GetGlobalObservables()),
			   RooFit::Verbose(kFALSE), RooFit::NumCPU(1, RooFit::Hybrid) );
    
    RooFIter iter = m_ws->components().fwdIterator();

    // need only if using RooStarMomentMorph
    RooAbsArg* arg;
    while ((arg = iter.next())) {
      if (arg->IsA() == RooStarMomentMorph::Class()) {
        ((RooStarMomentMorph*)arg)->fixCache();
      }
    }

    minim = new RooMinimizer(*nll);              ////OffSet true default
    minim->setPrintLevel(-1);
    minim->setEps(0.01);
    minim->optimizeConst(2);
    //minim->setStrategy(2);
    m_status= minim->minimize("Minuit2");
    
    if(m_status != 0  && m_status != -1) {
      if (!m_Fiducial)m_ws->loadSnapshot("postfit");
      minim->setStrategy(1);
      minim->minimize("Minuit2");
    }
    if(m_status != 0  && m_status != -1) {
      minim->setStrategy(2);
      minim->minimize("Minuit2");
    }
    
    m_Twonll = 2*nll->getVal();
    PRINT_DEBUG( to_string(val_to_set) + " " + to_string(m_Twonll) + "  " + to_string( m_status) );
    PRINT_DEBUG_OBJECT(firstPOI);

    m_sigma = firstPOI->getVal();
        
    if (m_Twonll==m_Twonll) if ( (m_status ==0||m_status ==-1 ) || ( vector_postfit.size() == 1 && !m_addSys) || m_fixSys=="all"   ){
      tmp_twonll.push_back(m_Twonll);                                                                    /// vector_postfit.size() == 1 && !m_addSys
      scan_plot->SetPoint(tmp_twonll.size()-1, m_sigma, m_Twonll);                                       /// check if there is only 1 poi and no sys
      tmp_sigma.push_back(m_sigma);
    }
    
    delete nll;
    minim->cleanup ();
    delete minim;
    
    stopwatch.Stop();
    /// progress bar
    if (ii%2==0){
      cout << "\033[0;31m [";
      int pos = ii*50/nSteps;
      for (int i = 0; i < 50; ++i) {
        if (i < pos) cout << "==";
        else if (i == pos) cout << ">";
        else cout << "  ";
      }
    
      time.push_back(stopwatch.RealTime());
    
      cout << "] " << int((ii+1) * 100.0 / nSteps) << " % ETA: " << (accumulate(time.begin(), time.end(), 0.0)/time.size())*(nSteps-ii-1) << " seconds \033[0m \r";
      cout.flush();
    }
    stopwatch.Reset();
  }
  
   /*
  TFile *file = new TFile( (m_OutDir+"/Scan_"+constPOI.Data()+".root").c_str(),"RECREATE");
  file->cd();
  m_ScanTree->Write();
  file->Close();
  */
  double minNLL = tmp_twonll.at( distance(begin(tmp_twonll), min_element( begin(tmp_twonll) , end(tmp_twonll) )) );
  
  for (unsigned int ii =0; ii<tmp_twonll.size(); ++ii ) tmp_twonll.at(ii) = tmp_twonll.at(ii)-minNLL;


  m_LeftRightErrors = EvalErrors(tmp_twonll, tmp_sigma, vector_postfit.at(0));
  
  for (unsigned int ii =0; ii<tmp_twonll.size(); ++ii){
    double x, y;
    scan_plot->GetPoint(ii, x, y);
    scan_plot->SetPoint(ii, x, y-minNLL);
   }
  scan_plot->SetTitle("-2 ln #Lambda vs "+constPOI);
  scan_plot->GetYaxis()->SetTitle("-2 ln #Lambda");
  TString namepoi = constPOI;
  namepoi.ReplaceAll("sigma_","sigma_{");
  if (m_FidTotal) namepoi = "sigma_{tot";
  if (m_FidComb) namepoi = "sigma_{comb";
  scan_plot->GetXaxis()->SetTitle(("#"+(string)namepoi.Data()+"}").c_str());
  if (m_BRDiff) scan_plot->GetXaxis()->SetTitle("BRDiff");
  tmp_twonll.clear();
  time.clear();
  cout << endl<< endl << "GOOD =<<<<<<<<" << endl << endl;

  firstPOI->setConstant(false);
}

void WorkSpaceMaker :: SetNtupla(RooWorkspace *w){
  m_ScanTree = new TTree ("ScanTree","ScanTree");
  /*
  ModelConfig* mc = (ModelConfig*) m_ws->obj("ModelConfig");
  RooRealVar *tmp;
  int i =0;
  */
  m_ScanTree->Branch("Twonll",&m_Twonll);
  m_ScanTree->Branch("Twonll_unc",&m_Twonll_unc);
  m_ScanTree->Branch("status_m", &m_status);
  m_ScanTree->Branch("status_m_unc", &m_status_unc);
  m_ScanTree->Branch("sigma", &m_sigma);
  m_ScanTree->Branch("sigma_unc", &m_sigma_unc);
}

pair<double,double> WorkSpaceMaker :: EvalErrors(vector<double> twonll, vector<double> sigma, double  min){
  PRINT_DEBUG_FUNCTION (" <EvalErrors()>");
  if ( twonll.size() != sigma.size()){
    PRINT_FATAL(" impossible to evaluate the errors -> EXIT!");
    PRINT_ERROR(" <EvalErrors()>:: twonll size != sigma size !");
    exit(0);
  }
  pair<double,double> out_pair;
  double err_left = 0; double err_right = 0;
  vector<double> y = {99,-99,99,-99};
  vector<double> x = {99,-99,99,-99};
  bool increase = false ;
  for ( unsigned int i = 0 ; i < twonll.size(); i++){
    if ( twonll.at(i) ==0 ) increase = true ;
    if ( twonll.at(i) > 1 && twonll.at(i) < y.at(0) &&  !increase ){ y.at(0) = twonll.at(i); x.at(0) =  sigma.at(i); }
    if ( twonll.at(i) < 1 && twonll.at(i) > y.at(1) &&  !increase ){ y.at(1) = twonll.at(i); x.at(1) =  sigma.at(i); }
    if ( twonll.at(i) > 1 && twonll.at(i) < y.at(2) &&  increase  ){ y.at(2) = twonll.at(i); x.at(2) =  sigma.at(i); }
    if ( twonll.at(i) < 1 && twonll.at(i) > y.at(3) &&  increase  ){ y.at(3) = twonll.at(i); x.at(3) =  sigma.at(i); }
  }
  PRINT_DEBUG ("<EvalErrors()>:");
  PRINT_DEBUG (to_string(min) + " " + to_string( EvalOneSigma( y.at(0), y.at(1), x.at(0), x.at(1) )));
  PRINT_DEBUG (to_string(min) + " " + to_string( EvalOneSigma( y.at(2), y.at(3), x.at(2), x.at(3) )));
  PRINT_DEBUG (to_string(min  - TMath::Abs( EvalOneSigma( y.at(0), y.at(1), x.at(0), y.at(1)) )));
  
  err_right = EvalOneSigma( y.at(2), y.at(3), x.at(2), x.at(3));
  err_left = EvalOneSigma( y.at(0), y.at(1), x.at(0), x.at(1) );
  out_pair=make_pair(err_left,err_right);
  return out_pair;
  
}

double WorkSpaceMaker :: EvalOneSigma(double y1, double y2, double x1, double x2){

  double x = -999.;
  /// formula from:      (y(=1sigma) - y1)/(y2-y1) = (x-x1)/(x2-x1)
  x = (((1.-y1)/(y2-y1))*(x2-x1)) + x1;
  return x;
  
}
