#include "WorkSpaceMaker.h"

void  WorkSpaceMaker :: DoQuickTest(){

  PRINT_BEGIN_FUNCTION(" <DoQuickTest()>:: doing a Quick Test");
  
  int NumberOfSteps = 100;
  
  string dataname;
  dataname = "asimovDataFullModel";
  if ( m_useMCData ) dataname = "asimovDataFullModel_MC";
  if ( m_WithData )  dataname = "obsData";
  
  string what = "expected";
  if ( m_WithData ) what = "data";
  
  string sysname = "";
  if(m_addSys) sysname = "_wsys";
  if (m_fixSys!="NO") sysname= sysname+"_fixing_"+m_fixSys;
  string unfoldingmethod = "";
  if (!m_matrix) unfoldingmethod = "_binbybin_";
  
  OpenTableFile(unfoldingmethod,sysname,what);
  OpenResultsFile(unfoldingmethod,sysname,what);
  
  //// set to 1 all acceptances for fiducial measurements
  if ( !m_Fiducial ) setAcceptance(); 
  if ( !m_FidTotal ) m_ws->saveSnapshot("fiducial",m_ws->allVars());  // for fiducial inclusive XS acceptances fixed before
  if ( m_FidTotal ) m_ws->saveSnapshot("total",m_ws->allVars());

  RooRealVar *tmp;
  RooRealVar *tmpReset;
  TIterator *iteratorPOI      = m_modelConfig->GetParametersOfInterest()->createIterator();
  TIterator *iteratorPOIReset = m_modelConfig->GetParametersOfInterest()->createIterator();

  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) )  { 
   m_preFitVal.push_back(tmp->getVal());
    tmp->setConstant(0);
  }

  if (m_bkgOption != "none") {
    
    if (m_floatqqZZ){
      for (unsigned int i =0; i < GetVarBinRange(m_VariableId).size(); ++i){
        m_ws->var(("MuqqZZ"+to_string(i)).c_str())->setConstant(0);
      }
    }
    else{
      for (unsigned int i =0; i < GetVarBinRange(m_VariableId).size(); ++i){
        m_ws->var(("MuqqZZ"+to_string(i)).c_str())->setConstant(1);
      }
    } 
  }

  
  iteratorPOI->Reset(); if (!m_WithData && !m_FidTotal && !m_FidComb) while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) tmp->setRange(0,10000);
  iteratorPOI->Reset(); if (m_WithData && (!m_FidTotal && !m_FidComb) ) while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) tmp->setRange(0,100);
  
  RooAbsData * p_data = m_ws->data(dataname.c_str()); p_data->Print();
  
  m_simPdf = (RooSimultaneous*) m_ws->pdf("simPdf");
  
  RooAbsReal *nll=m_simPdf->createNLL(*p_data,RooFit::Constrain(*m_modelConfig->GetNuisanceParameters()),
                                      RooFit::Offset(kTRUE), RooFit::GlobalObservables(*m_modelConfig->GetGlobalObservables()), RooFit::Verbose(kFALSE), RooFit::NumCPU(1, RooFit::Hybrid) );
  
  RooFIter iter = m_ws->components().fwdIterator();
  RooAbsArg* arg;
  while ((arg = iter.next())) {
    if (arg->IsA() == RooStarMomentMorph::Class()) {
      ((RooStarMomentMorph*)arg)->fixCache();
      arg->Print();
    }
  }
  
  RooMinimizer *minim = new RooMinimizer(*nll);
  minim->setEps(0.01);
  minim->setStrategy(2);
  minim->setPrintLevel(1);
  if (m_debug) minim->setPrintLevel(2);
  
  int fit = minim->minimize("Minuit2");

  RooArgSet params;
  params.add(m_ws->allVars());
  PRINT_DEBUG_OBJECT(&params,1);
  
  //if (m_do2D && m_addSys && m_fixSys =="NO") PlotM4l();

  if (m_FidChan && m_fixSys =="NO") PlotM4l();
  m_ws->saveSnapshot("postfit",params);  
  m_ws->writeToFile( (m_wsname+".root").c_str() );

  
  iteratorPOI->Reset();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) {
    m_postFitVal.push_back(tmp->getVal());
  }
  if (m_skipScan) return;
  PRINT_INFO(" <DoQuickTest()>:: input-output ");
  /*
    for ( unsigned int i = 0 ; i < m_postFitVal.size(); ++i )
    cout << "<DoQuickTest()>:: prefit: " << m_preFitVal.at(i)
    << " postfit: " << m_postFitVal.at(i)
    << " minitree: " << m_xsminitree.at(i) << endl;
  */
  cout << fit << "        =<! " << endl;
  
  iteratorPOI->Reset();
  TCanvas *c        = CreateCanvas( "All_"+m_Variable   , 800, 800 );
  TCanvas *c_single = CreateCanvas( "Single_"+m_Variable, 800, 800 );
  
  if ( m_preFitVal.size()>1 && !( m_FidSum || m_Fid4l || m_Fid2l2l || m_FidTotal || m_BRDiff ) )
    c->Divide( int(m_preFitVal.size()/2. + 0.5),2) ;
  
  int ii=0;
  
  TLatex *t = NULL;
  TGraph *m_scan_plot = NULL;
  TF1 *sigma1 = DefineFunction("sigma1", "1", -10,210000);
  TF1 *sigma2 = DefineFunction("sigma2", "4", -10,210000);
  TF1 *sigma3 = DefineFunction("sigma3", "9", -10,210000);
  TF1 *sigma4 = DefineFunction("sigma4", "16",-10,210000);
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
      m_ws->var(tmpReset->GetName())->setVal(m_preFitVal.at(kk));
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
    
    PRINT_INFO(" <DoQuickTest()>::  doScan for :  Var = "+  m_Variable + "  fixSys = " +
	       m_fixSys +"  ->  \033[0m \033[1;32m " + (string) tmp->GetName() + " !");
    ++ii;
    
    //float fixrange = -0.1; if (m_WithData) if (m_postFitVal.at(ii-1)<0 || m_postFitVal.at(ii-1)< m_preFitVal.at(ii-1)) fixrange =-2;
    
    float fixrangeup = 3;
    if (m_WithData) if (m_postFitVal.at(ii-1)<0 || m_postFitVal.at(ii-1)< m_preFitVal.at(ii-1) ) fixrangeup =-4;
    
    float negative_protection = 0;
    
    //if ( fixrange*abs(m__postFitVal.at(ii-1)) < 0 ) negative_protection= -1*(m_ws->var(("expperfb_"+m_Category.at(ii-1)+"qqZZ").c_str())->getVal()+m_ws->var(("expperfb_"+m_Category.at(ii-1)+"ggZZ").c_str())->getVal()+m_ws->var(("expperfb_"+m_Category.at(ii-1)+"redBkg").c_str())->getVal())/TMath::Max(m_ws->var(("Cgg_"+m_Category.at(ii-1)).c_str())->getVal(), m_ws->var(("Cvbf_"+m_Category.at(ii-1)).c_str())->getVal());
    //else negative_protection = fixrange*abs(m_postFitVal.at(ii-1));
    
    if ( m_WithData && m_Variable== "m12" && (string)tmp->GetName() == "sigma_bin5") fixrangeup = 200;
    if ( m_WithData && m_Variable== "m34" && (string)tmp->GetName() == "sigma_bin6") negative_protection = -0.001;
    if ( m_WithData && (m_Variable== "ptnjet"||m_Variable=="pt0j") && (string)tmp->GetName() == "sigma_bin3") { negative_protection = 2*negative_protection; fixrangeup = 200;}
    
    if ( m_FidSum || m_Fid4l || m_Fid2l2l || m_FidTotal  || m_FidChan || m_FidComb || m_BRDiff ){
      if (m_FidSum)
        ScanNLL( (m_OutDir+"/output.root").c_str(), "myWS", NumberOfSteps,
		 tmp->GetName(), 0.5*m_postFitVal.at(ii-1),2.*m_postFitVal.at(ii-1),
		 dataname, m_scan_plot, m_postFitVal, ii-1);
      else if ( m_BRDiff )
        ScanNLL( (m_OutDir+"/output.root").c_str(), "myWS", NumberOfSteps,
		 tmp->GetName(), -2.*m_postFitVal.at(ii-1),4.*m_postFitVal.at(ii-1),
		 dataname, m_scan_plot, m_postFitVal, ii-1);
      else
        ScanNLL( (m_OutDir+"/output.root").c_str(), "myWS", NumberOfSteps,
		 tmp->GetName(), 0.5*m_postFitVal.at(ii-1), 2.*m_postFitVal.at(ii-1),
		 dataname, m_scan_plot, m_postFitVal, ii-1);

      c->cd(ii);
      m_scan_plot->SetMaximum(5);
      if ( !m_BRDiff )
	m_scan_plot->GetXaxis()->SetLimits(0,2*m_postFitVal.at(ii-1));
      m_scan_plot->Draw("apl");

      c_single->cd();
      m_scan_plot->SetMaximum(5);
      if ( !m_BRDiff )
	m_scan_plot->GetXaxis()->SetLimits(0,2*m_postFitVal.at(ii-1));
      m_scan_plot->Draw("apl");

      yxs.at(0)= 3.; yxs.at(1)= 2.6; yxs.at(2)= 2.4; yxs.at(3)= 2.2;
      if (!m_FidChan) exitLoop = true;
    }
    else{
      PRINT(" Scan range: "+ to_string(negative_protection) + " - " +  to_string(TMath::Abs(fixrangeup*m_postFitVal.at(ii-1)) ));

      ScanNLL( (m_OutDir+"/output.root").c_str(), "myWS", NumberOfSteps,
	       tmp->GetName(), /*-0.1,//*/negative_protection,  //to be checked
	       TMath::Abs(fixrangeup*m_postFitVal.at(ii-1)),//tmp->getVal(),
	       dataname, m_scan_plot, m_postFitVal, ii-1);
      
      c->cd(ii);
      m_scan_plot->SetMaximum(5);
      m_scan_plot->GetXaxis()->SetLimits( negative_protection,
					  fixrangeup*GetPostFitXsecVal(ii-1) );
      m_scan_plot->Draw("apl");

      c_single->cd();
      m_scan_plot->SetMaximum(5);
      m_scan_plot->GetXaxis()->SetLimits( negative_protection,
					  abs(fixrangeup*GetPostFitXsecVal(ii-1)) );
      m_scan_plot->Draw("apl");
      
    }
    
    if( m_debug ) m_scan_plot->Print();
    m_scan_plot->GetYaxis()->SetTitleOffset(1.5);
    c->Update();
    c_single->Update();
  
    errorLeft = new TLine (m_LeftRightErrors.first, 0,
                           m_LeftRightErrors.first, 1);
    errorLeft->SetLineColor(kBlue);
    c->cd(ii); errorLeft->Draw();
    c_single->cd(); errorLeft->Draw();
    
    errorRight = new TLine (m_LeftRightErrors.second, 0,
                            m_LeftRightErrors.second, 1);
    errorRight->SetLineColor(kBlue);
    c->cd(ii); errorRight->Draw();
    c_single->cd(); errorRight->Draw();
    
    c->cd(ii);
    sigma1->Draw("same"); sigma2->Draw("same");
    sigma3->Draw("same"); sigma4->Draw("same");
    c_single->cd();
    sigma1->Draw("same"); sigma2->Draw("same");
    sigma3->Draw("same"); sigma4->Draw("same");
    
    t = CreateText( .5*GetPostFitXsecVal(ii-1), yxs.at(0),
		    ("xs_{inj} = "+
		     ConvertToStringWithPrecision(GetPreFitXsecVal(ii-1), 3)+" fb") );
    c->cd(ii);
    t->Draw();
    c_single->cd();
    t->Draw();
    
    // fit results with errors:
    t = CreateText( .5*GetPostFitXsecVal(ii-1), yxs.at(1),
		    ("xs_{fit} = "+ConvertToStringWithPrecision(GetPostFitXsecVal(ii-1), 3)+
		     "^{+"+ConvertToStringWithPrecision(GetPostFitXsecUpErr(ii-1), 3)      +
		     "}_{-"+ConvertToStringWithPrecision(GetPostFitXsecDownErr(ii-1), 3)   +
		     "} fb") );
    c->cd(ii);
    t->Draw();
    c_single->cd();
    t->Draw();

    double error_up=0; double error_down = 0;
    if( GetPostFitXsecUpErr(ii-1)>0   ) error_up   = GetPostFitXsecUpErr(ii-1);
    if( GetPostFitXsecDownErr(ii-1)>0 ) error_down = GetPostFitXsecDownErr(ii-1);
    
    if( !m_Fiducial ){
      
      double xpos=m_binlowerlimit.at(0);
      for ( int j =0; j< ii-1; ++j ) xpos+=m_binwidth.at(j);
      
      xpos+=(m_binwidth.at(ii-1)/2.) ;
      exp_xs.SetPoint( ii-1, xpos,  m_preFitVal.at(ii-1) );
      exp_xs.SetPointError( ii-1,
			    m_binwidth.at(ii-1)/2., m_binwidth.at(ii-1)/2.,
			    m_preFitVal.at(ii-1)*0.05, m_preFitVal.at(ii-1)*0.05);
      exp2_xs.SetPoint( ii-1, xpos,  m_preFitVal.at(ii-1) );
      exp2_xs.SetPointError( ii-1, m_binwidth.at(ii-1)/2., m_binwidth.at(ii-1)/2., 0, 0 );
      
      obs_xs.SetPoint( ii-1, xpos,  m_postFitVal.at(ii-1) );
      obs_xs.SetPointError( ii-1,
			    m_binwidth.at(ii-1)/2., m_binwidth.at(ii-1)/2.,
			    error_down, error_up );
    }
    if( m_Fiducial ){
      obs_xs.SetPoint( ii-1, ii-1,  m_postFitVal.at(ii-1) );
      obs_xs.SetPointError( ii-1, 0., 0, error_down, error_up );
    }
    
    tmp->setConstant(false);
    c->cd(ii); DrawAtlasLabel();
    c_single->cd(); DrawAtlasLabel();
    if ( !m_Fiducial )
      c->SaveAs( (m_OutDir+"/fit_"+m_Variable+unfoldingmethod+
		  "_"+conference+sysname+".eps").c_str() );
    c_single->SaveAs( (m_OutDir+"/fit_"+tmp->GetName()+"_"+m_Variable+
		       unfoldingmethod+"_"+conference+sysname+what+".eps").c_str() );
    
    m_scan_plot->SaveAs( (m_OutDir+"/scan_"+m_Variable+unfoldingmethod+
			  "_"+conference+"_"+tmp->GetName()+sysname+what+".root").c_str() );
    TString namePOI = (string)tmp->GetName();
    namePOI.ReplaceAll("_","_{");
    namePOI.ReplaceAll("sigma","\\sigma");
    namePOI.ReplaceAll("mu","\\mu");
    WriteTableFile("  $"+(string)namePOI.Data()+"}}$ [\\si{\\femto\\barn}] & ", ii-1);
    WriteResultsFile(ii-1);
    if ( exitLoop ) break;
  }

  CloseTableFile(unfoldingmethod,sysname,what);
  CloseResultsFile();
  
  if( !m_Fiducial ){
    c_single->cd();
    TPad *pad1 = CreateTopPad(m_Variable);
    pad1->SetBottomMargin(0);
    pad1->Draw();
    pad1->cd();
    TLegend *leg = CreateLegend(0.60,0.75,0.90,0.90);
    leg->ConvertNDCtoPad();
    exp_xs.SetFillStyle(3004);
    exp_xs.GetYaxis()->SetTitleOffset(1.6);
    exp_xs.GetXaxis()->SetTitle( GetVariableXaxisLabel(m_VariableId).c_str()       );
    exp_xs.GetYaxis()->SetTitle( GetVariableUnfoldYaxisLabel(m_VariableId).c_str() );
    exp_xs.SetFillColor(kBlue);
    exp_xs.SetMarkerSize(0);
    exp2_xs.SetMarkerSize(0);
    exp2_xs.SetLineColor(kBlue);
    
    double maxObs = obs_xs.GetHistogram()->GetMaximum();
    //double maxExp = exp_xs.GetHistogram()->GetMaximum();
    
    exp_xs.GetYaxis()->SetRangeUser( 0, maxObs );
    exp_xs.GetXaxis()->SetRangeUser( m_binlowerlimit.at(0),
				     accumulate(m_binwidth.begin(), m_binwidth.end(), 0.0) );
    exp_xs.Draw("a2");
    exp2_xs.Draw("p,same");
    obs_xs.Draw("p,same");
    DrawAtlasLabel(true);
    DrawEnergyLumi(m_lumi,true,true);
    DrawChannel(m_ChNum,true);
    leg->AddEntry(&exp_xs, "Higgs SM @125 GeV", "f");
    if(m_WithData)
      leg->AddEntry(&obs_xs, "Data", "p");
    else
      leg->AddEntry(&obs_xs, "Asimov Data", "pel");
    
    leg->Draw("same");
    c_single->cd();
    TPad *pad2 = CreateBottomPad(m_Variable);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->Draw();
    pad2->cd();
    
    for(Int_t ii=0; ii<exp_xs.GetN(); ii++) {
      double x; double y;
      double yobs;
      exp_xs.GetPoint( ii, x, y);
      exp_ratio_xs.SetPoint( ii, x,  1 );
      exp_ratio_xs.SetPointError( ii,
				  exp_xs.GetErrorXlow(ii), exp_xs.GetErrorXhigh(ii),
				  exp_xs.GetErrorYlow(ii)/y, exp_xs.GetErrorYhigh(ii)/y );
      exp2_ratio_xs.SetPoint( ii, x,  1 );
      exp2_ratio_xs.SetPointError(ii,
				  exp2_xs.GetErrorXlow(ii), exp2_xs.GetErrorXhigh(ii), 0, 0);
      obs_xs.GetPoint( ii, x, yobs );
      obs_ratio_xs.SetPoint( ii, x,  yobs/yobs );  // it was y expected not ready yet
      obs_ratio_xs.SetPointError( ii,
				  obs_xs.GetErrorXlow(ii), obs_xs.GetErrorXhigh(ii),
				  obs_xs.GetErrorYlow(ii)/yobs, obs_xs.GetErrorYhigh(ii)/yobs); // it was y expected not ready yet
    }
    
    exp_ratio_xs.SetFillStyle(3004);
    exp_ratio_xs.GetYaxis()->SetTitleOffset(1.6);
    exp_ratio_xs.GetXaxis()->SetTitle(  GetVariableXaxisLabel(m_VariableId).c_str() );
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
    
    exp_ratio_xs.GetXaxis()->SetRangeUser(0,
					  accumulate(m_binwidth.begin(), m_binwidth.end(), 0.0));
    
    exp_ratio_xs.GetYaxis()->SetRangeUser(0., 2);
    
    exp_ratio_xs.GetXaxis()->SetRangeUser(m_binlowerlimit.at(0),
					  accumulate(m_binwidth.begin(), m_binwidth.end(), 0.0));
    //obs_xs.Draw("ap");
    exp_ratio_xs.Draw("a2");
    
    exp2_ratio_xs.Draw("p,same");
    obs_ratio_xs.Draw("p,same");
    obs_xs.SetNameTitle(m_Variable.c_str(),m_Variable.c_str());
    obs_xs.SaveAs( (m_OutDir+"/fit_"+m_Variable+unfoldingmethod+
		    "_"+conference+sysname+what+"_TGunfolded.root").c_str() );
    c_single->SaveAs( (m_OutDir+"/fit_"+m_Variable+unfoldingmethod+
		      "_"+conference+sysname+what+"_unfolded.eps").c_str() );
    c_single->SaveAs( (m_OutDir+"/fit_"+m_Variable+unfoldingmethod+
		       "_"+conference+sysname+what+"_unfolded.root").c_str() );
  }
  if ( m_Fiducial ) {
    obs_xs.SetNameTitle(m_Variable.c_str(),m_Variable.c_str());
    obs_xs.SaveAs( (m_OutDir+"/fit_"+m_Variable+unfoldingmethod+"_"+
		    conference+sysname+what+"_TGunfolded.root").c_str() );
  }
  m_preFitVal.clear();
  m_postFitVal.clear();
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
  delete c;
  delete c_single;
  
}
