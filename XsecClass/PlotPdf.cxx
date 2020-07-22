#include "WorkSpaceMaker.h"
#include "RooBinning.h"
#include "THStack.h"

void WorkSpaceMaker :: PlotM4l (){

  PRINT_DEBUG_FUNCTION(" <PlotM4l()>:: PlotM4l");

  TH1* hh_pdf = NULL;
  
  RooWorkspace *myWS = (RooWorkspace*) m_ws->Clone();
  string outName = m_OutDir+"/hm_h"+m_Variable;
  if(m_WithData){ outName += "_data";     }
  else{           outName += "_expected"; }
  TFile* _m4loutput = new TFile( (outName+".root").c_str(), "recreate");
  _m4loutput->cd();
  _m4loutput->Print();

  string varws = "m4l";
  for (unsigned int i = 0; i< m_Category.size(); ++i){
    if(m_FidChan) varws = "x";
    if ( m_addSys ) hh_pdf = myWS->pdf(("model_"+GetChannelName(m_ChNum)+"_sys_"+m_Category.at(i)).c_str())->createHistogram(varws.c_str(),m_Mbins, m_mMin, m_mMax);
    else hh_pdf = myWS->pdf(("model_"+GetChannelName(m_ChNum)+"_nosys_"+m_Category.at(i)).c_str())->createHistogram(varws.c_str(),m_Mbins, m_mMin, m_mMax);
    hh_pdf->SetNameTitle(("hm_"+m_Variable+m_Category.at(i)).c_str(),("hm_"+m_Variable+m_Category.at(i)).c_str());
    hh_pdf->Write();
  }
  _m4loutput->Close();
  
}

void WorkSpaceMaker :: PlotPdfFiducial (RooSimultaneous *pdf,
                                        RooDataSet *Asimov,
                                        RooDataSet *combData){

  PRINT_DEBUG_FUNCTION(" <PlotPdfFiducial()>:: PlotPdfFiducial");

  vector<int> color;
  color.push_back(600); //kRed
  color.push_back(600); //kBlue
  color.push_back(600); //kGreen
  color.push_back(600); //kViolet
  
  if ( color.size() != m_Category.size() ){
    PRINT_FATAL(" <PlotPdfFiducial()>:: m_Category size != number of colors !");
    PRINT_FATAL(" exit!!");
    exit(0);
  }
  
  RooPlot* frame = NULL;
  TCanvas* c = CreateCanvas("pdf",1200,1200);
  c->Divide(2,2) ;
  
  for (unsigned int i = 0; i < color.size() ; i ++){
    frame = m_x->frame(Bins(m_Mbins),Title(m_Category.at(i).c_str())) ;
    combData->plotOn(frame,Cut(("channelCat==channelCat::"+m_Category.at(i)).c_str()),
		     MarkerColor(kBlack),LineColor(kBlack),DataError(RooAbsData::Poisson)) ;
 
    if (m_bkgOption == "none") {
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1)) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(m_sigCol)) ;
    }
    if (m_bkgOption == "ZZ") {
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1)) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(m_sigCol)) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(m_ZZCol),
		  Components(("pdf_*"+m_Category.at(i)+"*Z*").c_str())) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1),
		  Components(("pdf_*"+m_Category.at(i)+"*Z*").c_str())) ;
    }
    if (m_bkgOption == "all") { 
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1)) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(m_sigCol)) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(m_ZZCol),
		  Components(("pdf_*"+m_Category.at(i)+"*Z*,pdf_*"+m_Category.at(i)+"*redBkg").c_str() )) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1),
		  Components(("pdf_*"+m_Category.at(i)+"*Z*,pdf_*"+m_Category.at(i)+"*redBkg").c_str() )) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), DrawOption("F"), FillColor(m_redBkgCol),
		  Components(("pdf_*"+m_Category.at(i)+"*redBkg").c_str())) ;
      pdf->plotOn(frame,Slice(*m_sample,(m_Category.at(i)).c_str()),
		  ProjWData(*m_sample,*Asimov), LineColor(kBlack),LineWidth(1),
		  Components(("pdf_*"+m_Category.at(i)+"*redBkg").c_str())) ;
    }
    combData->plotOn(frame,Cut(("channelCat==channelCat::"+m_Category.at(i)).c_str()),
		     MarkerColor(kBlack), LineColor(kBlack),DataError(RooAbsData::Poisson)) ;
    c->cd(i+1) ;
    gPad->SetLeftMargin(0.15) ;
    frame->GetYaxis()->SetTitleOffset(1.4) ;
    frame->Draw() ;
  }
  
  DrawAtlasLabel();
  string what = "expected";
  if ( m_WithData ) what = "data";
  c->SaveAs( (m_OutDir+"/fiducialPdf_"+what+".eps").c_str() );
  delete c;
  delete frame;
}

void WorkSpaceMaker :: PlotPdf (RooSimultaneous *pdf, RooDataSet *combData, bool postFit){
  
  PRINT_DEBUG_FUNCTION(" <PlotPdf()>:: PlotPdf");
  TCanvas *oneD = CreateCanvas("1D",800,800);
  TLegend *leg = new TLegend(0.70,0.73,0.90,0.91);
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);

  TH1D *h_xAll = NULL;
  h_xAll = new TH1D("h_xAll", "h_xAll", m_Category.size(), 0, m_Category.size());

  TH1F *h_xbkg = NULL;
  TH1F *h_xbkgredBkg= NULL;
  
  if (m_bkgOption == "ZZ") {
    h_xbkg = new TH1F("h_xbkg", "h_xbkg", m_Category.size(), 0, m_Category.size());
  }
  if (m_bkgOption == "all") {
    h_xbkg = new TH1F("h_xbkg", "h_xbkg", m_Category.size(), 0, m_Category.size());	
    h_xbkgredBkg = new TH1F("h_xbkgredBkg", "h_xbkgredBkg", m_Category.size(), 0, m_Category.size());
  }

  TGraphAsymmErrors tgdata;
  TGraphAsymmErrors tgdata_real;

  RooRealVar *varForIntegral = NULL;
  RooAddPdf *pdf_forIntegral;
      
  if (m_do2D)  varForIntegral = m_m4l;
  else varForIntegral = m_x;

  double y;
  RooDataHist* data_tmp = NULL;
  for (unsigned int i = 0; i< m_Category.size(); ++i){
  
    data_tmp = (RooDataHist*) combData->reduce(	("channelCat==channelCat::"+m_Category.at(i)).c_str() );	     

    y = data_tmp->sumEntries();

    double alpha = 1. - 0.682689492;
    tgdata.SetPoint(i, 0.5+i,  y/m_binwidth.at(i) );
    double eh = ROOT::Math::gamma_quantile_c(alpha/2, int(y)+1, 1)-(y);
    
    double el = (y)-ROOT::Math::gamma_quantile(alpha/2, int(y), 1);

    tgdata.SetPointError(i, 0, 0, el/m_binwidth.at(i), eh/m_binwidth.at(i));

    if (postFit) pdf_forIntegral =  (RooAddPdf*) m_ws->pdf(m_v_pdfaddlist.at(i).GetName());
    else pdf_forIntegral = &m_v_pdfaddlist.at(i);
    
    
    RooArgList listNormCoef = pdf_forIntegral->coefList();
         
    h_xAll->SetBinContent(i+1, pdf_forIntegral->expectedEvents(*varForIntegral) / m_binwidth.at(i));
    
    if (m_bkgOption == "ZZ") {
      RooFormulaVar *bkg1 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"qqZZ").c_str()));
      RooFormulaVar *bkg2 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"ggZZ").c_str()));
      
      if (bkg1==NULL || bkg2 == NULL) { 
	PRINT_FATAL("<PlotPdf()>:: qq or gg bkg normalization factor not found, exit(0)!") ;
	exit(0);
      }
      h_xbkg->SetBinContent(i+1,(bkg1->getVal()+bkg2->getVal())/m_binwidth.at(i));
    }
    
    if (m_bkgOption == "all") {
      
      RooFormulaVar * bkg1 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"qqZZ").c_str()));
      RooFormulaVar * bkg2 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"ggZZ").c_str()));
      RooFormulaVar * bkg3 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"redBkg").c_str()));
      
      if (bkg1==NULL || bkg2 == NULL) { 
	PRINT_FATAL("<PlotPdf()>:: redbkg, qq or gg bkg normalization factor not found, exit(0)!") ;
	exit(0);
      }
      h_xbkg->SetBinContent(i+1,(bkg1->getVal()+bkg2->getVal())/m_binwidth.at(i)); 
      h_xbkgredBkg->SetBinContent(i+1,(bkg3->getVal())/m_binwidth.at(i));

    }

  }


  h_xAll->SetLineColor(kBlack); h_xAll->SetFillColor(m_sigCol); h_xAll->SetLineWidth(1);
  
  if (m_bkgOption == "ZZ") {
    h_xbkg->SetLineColor(kBlack); h_xbkg->SetFillColor(m_ZZCol); h_xbkg->SetLineWidth(1);
  }
  if (m_bkgOption == "all") {
    h_xbkg->Add(h_xbkgredBkg);
    h_xbkg->SetLineColor(kBlack);       h_xbkg->SetFillColor(m_ZZCol);           h_xbkg->SetLineWidth(1);
    h_xbkgredBkg->SetLineColor(kBlack); h_xbkgredBkg->SetFillColor(m_redBkgCol); h_xbkgredBkg->SetLineWidth(1);
  }
  tgdata.SetMarkerStyle(9); tgdata.SetMarkerColor(kBlack); tgdata.SetLineWidth(kBlack); tgdata.SetLineColor(kBlack);

  AdjustRemappedXaxis(h_xAll,m_VariableId);
  h_xAll->Draw("h");
  h_xAll->SetMinimum(0);
  h_xAll->SetMaximum(1.85*h_xAll->GetMaximum());
  if(m_VariableId==Variable::etajj || m_VariableId==Variable::phijj){
    h_xAll->SetMinimum(0.1);
    h_xAll->SetMaximum(100*h_xAll->GetMaximum());
    oneD->SetLogy(kTRUE);
  }
  else if(m_VariableId==Variable::ljpt || m_VariableId==Variable::sjpt ||
	  m_VariableId==Variable::mjj  ){
    if(m_VariableId==Variable::sjpt) h_xAll->SetMinimum(0.00001);
    else                             h_xAll->SetMinimum(0.0001);
    h_xAll->SetMaximum(1000*h_xAll->GetMaximum());
    oneD->SetLogy(kTRUE);
  }
  
  h_xAll->GetYaxis()->SetTitle( GetVariableDistroYaxisLabel(m_VariableId).c_str() );
  h_xAll->GetYaxis()->SetTitleOffset(1.5);
  h_xAll->GetXaxis()->SetTitle( GetVariableXaxisLabel(m_VariableId).c_str() );
  
  if (m_bkgOption == "all") {
    h_xbkg->Draw("same");
    h_xbkgredBkg->Draw("same");

  }
  if (m_bkgOption == "ZZ") {
    h_xbkg->Draw("same");
  }
  
  tgdata.Draw("p,same");
  leg->AddEntry(h_xAll, "Signal", "f");
  
  if (m_bkgOption == "all") {
    leg->AddEntry(h_xbkg, "ZZ*", "f");
    leg->AddEntry(h_xbkgredBkg, "Z+jets, t#bar{t}, t#bar{t}+V, VVV", "f");
  }
  if (m_bkgOption == "ZZ") leg->AddEntry(h_xbkg, "ZZ*", "f");
  
  if (m_WithData) leg->AddEntry(&tgdata, "Data", "pel");
  else  leg->AddEntry(&tgdata, "Asimov Data", "pel");
  leg->Draw("same");
  
  string what = "expected";
  if ( m_WithData ) what = "data";
  
  DrawAtlasLabel();
  DrawEnergyLumi(m_lumi,true);
  DrawChannel(m_ChNum);
  gPad->RedrawAxis();

  if (postFit) what += "_postfit";
  else what += "_prefit";
  oneD->SaveAs( (m_OutDir+"/shape_"+m_Variable+"_"+what+".eps").c_str() );


  delete h_xAll;
  delete h_xbkg;
  delete h_xbkgredBkg;
  delete oneD;
  delete data_tmp;
}




void WorkSpaceMaker :: PlotPdfSplitXS (RooSimultaneous *pdf, RooDataSet *combData, bool postFit){
  
  PRINT_DEBUG_FUNCTION(" <PPlotPdfSplitXS>:: PlotPdfSplitXS");
  TCanvas *oneD = CreateCanvas("1Dsplit",800,800);
  TLegend *leg = new TLegend(0.70,0.73,0.90,0.91);
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);
  
  vector<unsigned int> color= {EColor::kGreen,EColor::kMagenta,EColor::kBlue,EColor::kOrange,EColor::kAzure+10,EColor::kGray,EColor::kPink,EColor::kBlack,EColor::kTeal,
  			       EColor::kGreen+2,EColor::kMagenta+2,EColor::kBlue+2,EColor::kOrange+2,EColor::kAzure+2,EColor::kGray+2,EColor::kPink+2,EColor::kBlack+2,EColor::kTeal+2,
  			       EColor::kGreen+4,EColor::kMagenta+4,EColor::kBlue+4,EColor::kOrange+4,EColor::kAzure+4,EColor::kGray+4,EColor::kPink+4,EColor::kBlack+4,EColor::kTeal+4,
  			       EColor::kGreen+6,EColor::kMagenta+6,EColor::kBlue+6,EColor::kOrange+6,EColor::kAzure+6,EColor::kGray+6,EColor::kPink+6,EColor::kBlack+6,EColor::kTeal+6}; 
  			       
  if (m_Category.size() > color.size()){
    PRINT_WARNING("<PlotPdfSplitXS()>: # categories > # color available, skip split XS plot");
    return;
  }
  TH1D *h_xAll = NULL;
  h_xAll = new TH1D("h_xAll", "h_xAll", m_Category.size(), 0, m_Category.size());

  TH1F *h_xbkg = NULL;
  TH1F *h_xbkgredBkg= NULL;
  
  if (m_bkgOption == "ZZ") {
    h_xbkg = new TH1F("h_xbkg", "h_xbkg", m_Category.size(), 0, m_Category.size());
  }
  if (m_bkgOption == "all") { 
    h_xbkg = new TH1F("h_xbkg", "h_xbkg", m_Category.size(), 0, m_Category.size());	
    h_xbkgredBkg = new TH1F("h_xbkgredBkg", "h_xbkgredBkg", m_Category.size(), 0, m_Category.size());
  }

  TGraphAsymmErrors tgdata;
  TGraphAsymmErrors tgdata_real;

  RooRealVar *varForIntegral = NULL;
  RooAddPdf *pdf_forIntegral;
      
  if (m_do2D)  varForIntegral = m_m4l;
  else varForIntegral = m_x;


  TH1F *sigma = NULL;
  vector<TH1F*> v_sigma;
  for (unsigned int i =0 ; i < m_Category.size(); ++i){
  
    sigma = new TH1F (m_Category.at(i).c_str(), m_Category.at(i).c_str(),  m_Category.size(), 0,  m_Category.size());
    v_sigma.push_back(sigma);
  }

  double y;
  RooDataHist* data_tmp = NULL;

  for (unsigned int i = 0; i< m_Category.size(); ++i){
  
    data_tmp = (RooDataHist*) combData->reduce(	("channelCat==channelCat::"+m_Category.at(i)).c_str() );	     

    y = data_tmp->sumEntries();

    double alpha = 1. - 0.682689492;
    tgdata.SetPoint(i, 0.5+i,  y/m_binwidth.at(i) );
    double eh = ROOT::Math::gamma_quantile_c(alpha/2, int(y)+1, 1)-(y);
    
    double el = (y)-ROOT::Math::gamma_quantile(alpha/2, int(y), 1);

    tgdata.SetPointError(i, 0, 0, el/m_binwidth.at(i), eh/m_binwidth.at(i));

    if (postFit) pdf_forIntegral =  (RooAddPdf*) m_ws->pdf(m_v_pdfaddlist.at(i).GetName());
    else pdf_forIntegral = &m_v_pdfaddlist.at(i);
    
    h_xAll->SetBinContent(i+1, pdf_forIntegral->expectedEvents(*varForIntegral) / m_binwidth.at(i));
    
    RooArgList listNormCoef = pdf_forIntegral->coefList();
           
    if (m_bkgOption == "ZZ") {
      RooFormulaVar *bkg1 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"qqZZ").c_str()));
      RooFormulaVar *bkg2 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"ggZZ").c_str()));
      
      if (bkg1==NULL || bkg2 == NULL) { 
	PRINT_FATAL("<PlotPdf()>:: qq or gg bkg normalization factor not found, exit(0)!") ;
	exit(0);
      }
      h_xbkg->SetBinContent(i+1,(bkg1->getVal()+bkg2->getVal())/m_binwidth.at(i)); 

    }
    
    if (m_bkgOption == "all") {
      
      RooFormulaVar * bkg1 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"qqZZ").c_str()));
      RooFormulaVar * bkg2 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"ggZZ").c_str()));
      RooFormulaVar * bkg3 = (RooFormulaVar*) listNormCoef.at(listNormCoef.index(("norm_bkg_"+m_Category.at(i)+"redBkg").c_str()));
      
      if (bkg1==NULL || bkg2 == NULL) { 
	PRINT_FATAL("<PlotPdf()>:: redbkg, qq or gg bkg normalization factor not found, exit(0)!") ;
	exit(0);
      }
      h_xbkg->SetBinContent(i+1,(bkg1->getVal()+bkg2->getVal())/m_binwidth.at(i)); 
      h_xbkgredBkg->SetBinContent(i+1,(bkg3->getVal())/m_binwidth.at(i));

    }

  }


  
  THStack *xsSplit = new THStack ("xsSplit","xsSplit");
  if (m_bkgOption == "all")  xsSplit->Add(h_xbkgredBkg);
  xsSplit->Add(h_xbkg);
  
  for ( unsigned int i = 0; i< m_Category.size(); ++i){ 
  
    for ( unsigned int k = 0; k< m_Category.size(); ++k){
      m_ws->var(("sigma_"+m_Category.at(k)).c_str() )->setVal(0);
    }
  
    m_ws->var(("sigma_"+m_Category.at(i)).c_str() )->setVal(m_postFitVal.at(i));
    
    for ( unsigned int j = 0; j< m_Category.size(); ++j){     
       v_sigma.at(i)->SetBinContent(j+1, ((RooFormulaVar*) m_ws->obj(("norm_"+m_Category.at(j)).c_str() ))->getVal()/m_binwidth.at(j));
    } 
    v_sigma.at(i)->SetFillColor(color.at(i));
    xsSplit->Add(v_sigma.at(i));
    leg->AddEntry(v_sigma.at(i), m_Category.at(i).c_str(), "f");

  }

  
  if (m_bkgOption == "ZZ") {
    h_xbkg->SetLineColor(kBlack); h_xbkg->SetFillColor(m_ZZCol); h_xbkg->SetLineWidth(1);
  }
  if (m_bkgOption == "all") {
    //h_xbkg->Add(h_xbkgredBkg);
    h_xbkg->SetLineColor(kBlack); h_xbkg->SetFillColor(m_ZZCol); h_xbkg->SetLineWidth(1);
    h_xbkgredBkg->SetLineColor(kBlack); h_xbkgredBkg->SetFillColor(m_redBkgCol); h_xbkgredBkg->SetLineWidth(1);
  }
  tgdata.SetMarkerStyle(9); tgdata.SetMarkerColor(kBlack); tgdata.SetLineWidth(kBlack); tgdata.SetLineColor(kBlack);
  
  AdjustRemappedXaxis(h_xAll,m_VariableId);

  h_xAll->Draw("h");
  h_xAll->SetMinimum(0);
  h_xAll->SetMaximum(1.85*h_xAll->GetMaximum());
  if(m_VariableId==Variable::etajj || m_VariableId==Variable::phijj){
    h_xAll->SetMinimum(0.1);
    h_xAll->SetMaximum(100*h_xAll->GetMaximum());
    oneD->SetLogy(kTRUE);
  }
  else if(m_VariableId==Variable::ljpt || m_VariableId==Variable::sjpt ||
	  m_VariableId==Variable::mjj  ){
    if(m_VariableId==Variable::sjpt) h_xAll->SetMinimum(0.00001);
    else                             h_xAll->SetMinimum(0.0001);
    h_xAll->SetMaximum(1000*h_xAll->GetMaximum());
    oneD->SetLogy(kTRUE);
  }
  
  h_xAll->GetYaxis()->SetTitle( GetVariableDistroYaxisLabel(m_VariableId).c_str() );
  h_xAll->GetYaxis()->SetTitleOffset(1.5);
  h_xAll->GetXaxis()->SetTitle( GetVariableXaxisLabel(m_VariableId).c_str() );
  
  xsSplit->Draw("same");
  tgdata.Draw("p,same");
  //leg->AddEntry(h_xAll, "Signal", "f");
  
  if (m_bkgOption == "all") {
    leg->AddEntry(h_xbkg, "ZZ*", "f");
    leg->AddEntry(h_xbkgredBkg, "Z+jets", "f");
  }
  if (m_bkgOption == "ZZ") leg->AddEntry(h_xbkg, "ZZ*", "f");
  
  if (m_WithData) leg->AddEntry(&tgdata, "Data", "pel");
  else  leg->AddEntry(&tgdata, "Asimov Data", "pel");
  leg->Draw("same");
  
  string what = "expected";
  if ( m_WithData ) what = "data";
  
  DrawAtlasLabel();
  DrawEnergyLumi(m_lumi,true);
  DrawChannel(m_ChNum);
  gPad->RedrawAxis();

  if (postFit) what += "_postfit";
  else what += "_prefit";
  oneD->SaveAs( (m_OutDir+"/shape_splitXS_"+m_Variable+"_"+what+".eps").c_str() );
  oneD->SaveAs( (m_OutDir+"/shape_splitXS_"+m_Variable+"_"+what+".png").c_str() );
  oneD->SaveAs( (m_OutDir+"/shape_splitXS_"+m_Variable+"_"+what+".pdf").c_str() );

 
  delete xsSplit;
  delete leg;
  delete h_xAll;
  delete h_xbkg;
  delete h_xbkgredBkg;
  delete oneD;
  delete data_tmp;
}





