#include "doPlots.h"

void doPlots :: drawHistoSignal(TH1F *t){

  std::cout << " <doPlots::doHistoSignal()> making signal only plots" << std::endl;
				
  cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();
  
  TString name = (TString) t->GetName();

  h_ggh  = (TH1F*) m_f->Get( ((TString) t->GetName()).ReplaceAll("AllSig", "ggH")  );
  h_vbf  = (TH1F*) m_f->Get( ((TString) t->GetName()).ReplaceAll("AllSig", "VBF")  );
  h_wh   = (TH1F*) m_f->Get( ((TString) t->GetName()).ReplaceAll("AllSig", "WH")   );
  h_zh   = (TH1F*) m_f->Get( ((TString) t->GetName()).ReplaceAll("AllSig", "ZH")   );
  h_tth  = (TH1F*) m_f->Get( ((TString) t->GetName()).ReplaceAll("AllSig", "ttH")  );
  h_bbh  = (TH1F*) m_f->Get( ((TString) t->GetName()).ReplaceAll("AllSig", "bbH")  );
  h_data = (TH1F*) m_f->Get( ((TString) t->GetName()).ReplaceAll("AllSig", "data") );
  dummy  = (TH1F*)h_data->Clone( "dummy" ); dummy->Reset();
  
  v_prodmode.push_back( "incl");  list_histo.push_back( t     );
  v_prodmode.push_back( "ggH" );  list_histo.push_back( h_ggh );
  v_prodmode.push_back( "VBF ");  list_histo.push_back( h_vbf );
  v_prodmode.push_back( "WH"  );  list_histo.push_back( h_wh  ); 
  v_prodmode.push_back( "ZH"  );  list_histo.push_back( h_zh  ); 
  v_prodmode.push_back( "ttH" );  list_histo.push_back( h_tth );
  v_prodmode.push_back( "bbH" );  list_histo.push_back( h_bbh );

  /* Creating legend */
  leg  = new TLegend(0.5,0.7,0.90,0.93);
  leg1 = new TLegend(0.57,0.7,0.90,0.93);
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);
  leg1->ConvertNDCtoPad();
  leg1->SetTextFont(42);

  /* Defining ranges */
  double LogYscl = GetYlogScaleCoeff(name);
  double LinYscl = GetYlinScaleCoeff(name);
  Double_t Min   = GetYaxisMin(name);
  Double_t Max   = GetYaxisMax(name,h_data);
  Double_t XMin  = h_data->GetXaxis()->GetXmin();
  Double_t XMax  = h_data->GetXaxis()->GetXmax();

  /* setting axis labels */
  double wd = list_histo.at(0)->GetBinWidth(1);
  dummy->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
  dummy->GetXaxis()->SetTitle( GetAxisLabel(name).c_str() );

  if(m_compProdMode && name.Contains("hm_pt") ){
    for (unsigned int i =1; i< list_histo.size(); ++i){
      setStyleAndLumi( list_histo.at(i), true );
      if(i>0) leg1->AddEntry(list_histo.at(i),(v_prodmode.at(i)), "l");
      list_histo.at(i)->DrawNormalized("same");
    }
    leg1->Draw("same");
    TString name2 = ((TString)t->GetName()).ReplaceAll( "AllSig", "SigComp");
    if(m_doLinear){
      for(uint i=0; i<list_histo.size(); ++i){
	list_histo.at(i)->GetYaxis()->SetRangeUser(0,10);
      }
      cs->SaveAs(m_OutDir+"/"+name2+".pdf");
      cs->SaveAs(m_OutDir+"/"+name2+".eps");
    }
    for(uint i=0; i<list_histo.size(); ++i){
      list_histo.at(i)->GetYaxis()->SetRangeUser(Min,100);
    }
    cs->SetLogy();
    cs->SaveAs(m_OutDir+"/"+name2+"_log.pdf");
    cs->SaveAs(m_OutDir+"/"+name2+"_log.eps");
  }
  
  /* set style and ranges */
  setStyleAndLumi( dummy );
  dummy->GetYaxis()->SetRangeUser(Min,Max);
  dummy->GetXaxis()->SetRangeUser(XMin,XMax);
  for(unsigned int i =0; i<list_histo.size(); ++i){
    setStyleAndLumi( list_histo.at(i) );
    if(i>0)
      leg->AddEntry(list_histo.at(i),(v_prodmode.at(i)), "f");
    list_histo.at(i)->GetYaxis()->SetRangeUser(Min,Max);
    list_histo.at(i)->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
    list_histo.at(i)->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
    list_histo.at(i)->GetXaxis()->SetTitle( GetAxisLabel(name).c_str() );
  }
  
  cs->SetLogy(false);
  h_prodmode = new THStack("h_prodmode","");
  for (unsigned int i = list_histo.size() -1 ; i>0; --i)
    h_prodmode->Add(list_histo.at(i));

  cs->cd();
  TAxis* a = NULL;
  if( name.Contains("hmjjrm_") ){
    a = dummy->GetXaxis();
    a->SetNdivisions(504);
    a->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    a->ChangeLabel(2,-1,-1,-1,-1,-1,"120");
    a->ChangeLabel(3,-1,-1,-1,-1,-1," ");
    a->ChangeLabel(4,-1,-1,-1,-1,-1," ");
    a->ChangeLabel(-1,-1,-1,-1,-1,-1,"3000");
    
  }
  dummy->Draw();
  
  if( name.Contains("hmjjrm_") ){
    dummy->GetXaxis()->SetTickSize(0);
    for(UShort_t bin = 0; bin < dummy->GetNbinsX() ; bin++ ){
      TGaxis *ax = new TGaxis(dummy->GetBinLowEdge(bin+1), 0, dummy->GetBinLowEdge(bin+1)+dummy->GetBinWidth(bin+1), 0, dummy->GetBinLowEdge(bin+1), dummy->GetBinLowEdge(bin+1)+dummy->GetBinWidth(bin+1), 1 ,"US");
      ax->SetTickSize( 0.05 );
      ax->SetLabelOffset(0.02);
      ax->Draw();
    }
  }
  
  
  h_prodmode->Draw("histsame");
    
  gPad->RedrawAxis();
    
  DrawLabels();
  leg->Draw("same");

  /* doing linear plot */
  if(m_doLinear){
    for (uint i=0; i<list_histo.size(); ++i){
      dummy->GetYaxis()->SetRangeUser(0,Max*LinYscl);
      list_histo.at(i)->GetYaxis()->SetRangeUser(0,Max*LinYscl);
    }
    cs->SaveAs(m_OutDir+"/"+name+".pdf");
    cs->SaveAs(m_OutDir+"/"+name+".eps");
  }

  /* doing log plot */
  for (uint i=0; i<list_histo.size(); ++i){
    dummy->GetYaxis()->SetRangeUser(Min,Max*LogYscl);
    list_histo.at(i)->GetYaxis()->SetRangeUser(Min,Max*LogYscl);
  }
  cs->SetLogy();
  cs->SaveAs(m_OutDir+"/"+name+"_log.pdf");
  cs->SaveAs(m_OutDir+"/"+name+"_log.eps");

  ///* drawing all info pad 2 */
  //if ( (name.Contains("pt") || name.Contains("m34") || name.Contains("m12") ||
  //	name.Contains("njet") || name.Contains("y") || name.Contains("cts") ||
  //	name.Contains("nbjet")|| name.Contains("jj") )                       ){
  //  /* pave for number of events */
  //  cs->cd(2);
  //  TPaveText *pt = new TPaveText(0.,.05,1.,.95);
  //  setPave(pt);
  //  TString title = "Values for " + m_LumiStr + "/fb";
  //  pt->AddText(title);
  //  for (int i =0; i <t->GetNbinsX() ; ++i){
  //    TString text = "Exp Bin ";
  //    std::ostringstream val;
  //    val << std::setprecision(3)
  //	  << (t->GetBinContent(i+1)*t->GetBinWidth(i+1));
  //    text += std::to_string(i) + ": " + val.str() + " evts   ";
  //    for (unsigned int j =1; j< list_histo.size(); ++j){
  //      val.str(""); val.clear();  //reset buffer
  //      val << std::setprecision(3) << 100*(list_histo.at(j)->GetBinContent(i+1)*list_histo.at(j)->GetBinWidth(i+1))/(t->GetBinContent(i+1)*t->GetBinWidth(i+1));
  //      text += v_prodmode.at(j) + ": " + val.str() + "\% ";
  //	//cout<< v_prodmode.at(j-1) + ": " <<"bin" <<i << " "<< val.str() << " " <<(list_histo.at(j)->GetBinContent(i+1)*list_histo.at(j)->GetBinWidth(i+1))/(t->GetBinContent(i+1)*t->GetBinWidth(i+1))<< " " << list_histo.at(j)->GetBinContent(i+1) << endl;
  //    }
  //    pt->AddText(text);
  //    pt->SetTextAlign(11);
  //    
  //  }
  //  cs->cd(2);
  //  pt->Draw();
  //}
  //
  //if(m_doLinear){
  //  cs->cd(1)->SetLogy(false);
  //  cs->SaveAs(m_OutDir+"/"+name+"_wtable.eps");
  //  cs->SaveAs(m_OutDir+"/"+name+"_wtable.pdf");
  //}
  //cs->cd(1)->SetLogy();
  //cs->SaveAs(m_OutDir+"/"+name+"_log_wtable.pdf");
  //cs->SaveAs(m_OutDir+"/"+name+"_log_wtable.eps");
  
  t->Print();

  /* Cleaning */
  h_ggh  ->Delete();
  h_vbf  ->Delete();
  h_wh   ->Delete();
  h_zh   ->Delete();
  h_tth  ->Delete();
  h_bbh  ->Delete();
  h_data ->Delete();
  if(a!=NULL) a->Delete();
  dummy->Delete();
  leg->Delete();
  leg1->Delete();
  list_histo.clear();
  v_prodmode.clear();
  delete cs;
  
}

void doPlots :: drawHistoSigBkgData(TH1F *t){

  std::cout << " <doPlots::doHistoSigBkgData()>: "
	    << "making signal+backgound plots" << std::endl;

  cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();
  
  std::string Rep = "MC";
  if(m_useData) Rep = "Data";
  TString name     = ((TString)t->GetName()).ReplaceAll( "AllSig", Rep.c_str() );
  TString nameHm4l = ((TString)t->GetName()).ReplaceAll( "AllSig", Rep.c_str() );

  TString nameMass = nameHm4l;
  nameMass.ReplaceAll("_incl_MC", "");
  nameMass.ReplaceAll("_incl_Data", "");
  nameMass.ReplaceAll("hm_", "hm_h");
  std::string nameM4lFile = (std::string) nameMass;
  nameM4lFile = nameM4lFile.substr( 0, nameM4lFile.find("bin", 0) );

  bool isFid=false;
  if( name.Contains("hm_4mu")   || name.Contains("hm_4e")  ||
      name.Contains("hm_2mu2e") || name.Contains("hm_2e2mu") ){
    nameM4lFile = "hm_hm_fidchannel";
    if( name.Contains("hm_4mu")   ) { nameHm4l = "hm_m_fidchannel4mu";   }
    if( name.Contains("hm_4e")    ) { nameHm4l = "hm_m_fidchannel4e";    }
    if( name.Contains("hm_2mu2e") ) { nameHm4l = "hm_m_fidchannel2mu2e"; }
    if( name.Contains("hm_2e2mu") ) { nameHm4l = "hm_m_fidchannel2e2mu"; }
    isFid = true;
  }
  else{
    nameHm4l.ReplaceAll("_incl_MC", "");
    nameHm4l.ReplaceAll("_incl_Data", "");
  }
  
  bool m4lfound = false;
  if(m_drawM4l && nameHm4l.Contains("hm_")){
    m4lhistos = new TFile( ("../ws_output/"+nameM4lFile+"_data.root").c_str() );
  }
  if( m4lhistos!=NULL ) m4lfound=true;
  
  h_ZZ    = (TH1F*)m_f->Get( ((TString)t->GetName()).ReplaceAll("AllSig", "AllZZ") );
  h_ZZEW  = (TH1F*)m_f->Get( ((TString)t->GetName()).ReplaceAll("AllSig", "ZZEW") );
  h_Zjets = (TH1F*)m_f->Get( ((TString)t->GetName()).ReplaceAll("AllSig", "Zjets") );
  h_Mbos  = (TH1F*)m_f->Get( ((TString)t->GetName()).ReplaceAll("AllSig", "MultiBoson") );
  h_Red   = (TH1F*)m_f->Get( ((TString)t->GetName()).ReplaceAll("AllSig", "redBkg") );
  h_data  = (TH1F*)m_f->Get( ((TString)t->GetName()).ReplaceAll("AllSig", "data") );
  dummy   = (TH1F*)h_data->Clone( "dummy" ); dummy->Reset();
  if ( ((TString)t->GetName()).Contains("njet") )  dummy->SetNameTitle("dummynjet","dummynjet");
  if ( ((TString)t->GetName()).Contains("nbjet") ) dummy->SetNameTitle("dummynjet","dummynbjet");

  bool useRedBkg = m_useRedBkg;
  if(name.Contains("ptpt")) useRedBkg = false;
    
  h_m4lfit = NULL;
  tgdata   = NULL;
  SysBand  = NULL;
  
  if(m_drawM4l && m4lfound){
    if(isFid){
      h_m4lfit = GetMassPlot(m4lhistos,nameHm4l);
    }
    else{
      h_m4lfit = (TH1F*)m4lhistos->Get( nameHm4l );
    }
  }
  if(m_drawM4l && m4lfound && (h_m4lfit!=NULL) ) m4lfound =true;
  else m4lfound = false;

  v_chan.push_back( "data"   );                  list_histo.push_back( h_data );
  v_chan.push_back( "Signal (m_{H}=125 GeV)" );  list_histo.push_back( t      );
  v_chan.push_back( "Background ZZ*"    );       list_histo.push_back( h_ZZ   );

  if(m_useVBS){
    v_chan.push_back( "ZZ* EW" );  list_histo.push_back( h_ZZEW );
  }
  if(useRedBkg){
    v_chan.push_back( "Background Z+jets, t#bar{t}, t#bar{t}+V, VVV" );  list_histo.push_back( h_Red );
  }
  else{
    v_chan.push_back( "Background t#bar{t}+V, VVV" );  list_histo.push_back( h_Mbos );
  
    if(m_useZjets){
      v_chan.push_back( "Background Z+jets, t#bar{t}" );  list_histo.push_back( h_Zjets );
    }
  }
  
/*  if(m4lfound){
    v_chan.push_back( "Z+jets, t#bar{t}" );  list_histo.push_back( h_m4lfit );
  }
*/
  /* Creating legend */
  leg = new TLegend(0.5,0.7,0.90,0.93);
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);

  /* Defining ranges */
  double LogYscl = GetYlogScaleCoeff(name);
  double LinYscl = GetYlinScaleCoeff(name);
  Double_t Min   = GetYaxisMin(name);
  Double_t Max   = GetYaxisMax(name,h_data);
  Double_t XMin  = h_data->GetXaxis()->GetXmin();
  Double_t XMax  = h_data->GetXaxis()->GetXmax();
  
  /* Creating data graph */
  if(m_useData)
    tgdata = RetrieveData(list_histo.at(0));

  /* setting axis label */
  double wd = list_histo.at(0)->GetBinWidth(1);
  dummy->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
  dummy->GetXaxis()->SetTitle( GetAxisLabel(name).c_str() );
  if(m_useData){
    tgdata->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
    tgdata->GetXaxis()->SetTitle( GetAxisLabel(name).c_str() );
  }
  
  /* set style and ranges */
  setStyleAndLumi( dummy );
  dummy->GetYaxis()->SetRangeUser(Min,Max);
  dummy->GetXaxis()->SetRangeUser(XMin,XMax);
  for (uint i=0; i<list_histo.size(); ++i){
    setStyleAndLumi( list_histo.at(i) );
    if(m_useData && i==0)
      leg->AddEntry(list_histo.at(i),"Data", "pe");
    if(i>0)
      leg->AddEntry(list_histo.at(i),(v_chan.at(i)), "f");
    list_histo.at(i)->GetYaxis()->SetRangeUser(Min,Max);
    list_histo.at(i)->GetXaxis()->SetRangeUser(XMin,XMax);
    list_histo.at(i)->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
    list_histo.at(i)->GetXaxis()->SetTitle( GetAxisLabel(name).c_str() );
    if(m4lfound) list_histo.at(i)->GetXaxis()->SetTitle( "m_{4l}" );

  }
  if(m_useData){
    tgdata->GetYaxis()->SetRangeUser(Min,Max);
    tgdata->GetXaxis()->SetRangeUser(XMin,XMax);
  }
  if(m4lfound) leg->AddEntry(h_m4lfit,"m_{4l} fitted", "l");
  
  h_chan = new THStack("h_chan","");
  for (uint i = list_histo.size()-1 ; i>0; --i)
    h_chan->Add(list_histo.at(i));
    
  cs->cd();
  TAxis* a = NULL;
  if( name.Contains("hmjjrm_") ){
    a = dummy->GetXaxis();
    a->SetNdivisions(504);
    a->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    a->ChangeLabel(2,-1,-1,-1,-1,-1,"120");
    a->ChangeLabel(3,-1,-1,-1,-1,-1," ");
    a->ChangeLabel(4,-1,-1,-1,-1,-1," ");
    a->ChangeLabel(-1,-1,-1,-1,-1,-1,"3000");

  }
  dummy->Draw();

  if( name.Contains("hmjjrm_") ){
    dummy->GetXaxis()->SetTickSize(0);
    for(UShort_t bin = 0; bin < dummy->GetNbinsX() ; bin++ ){
      TGaxis *ax = new TGaxis( dummy->GetBinLowEdge(bin+1), 0,
			       dummy->GetBinLowEdge(bin+1)+dummy->GetBinWidth(bin+1), 0,
			       dummy->GetBinLowEdge(bin+1), dummy->GetBinLowEdge(bin+1)+dummy->GetBinWidth(bin+1), 1 ,"US" );
      ax->SetTickSize( 0.05 );
      ax->SetLabelOffset(0.02);
      ax->Draw();
    }
  }

  h_chan->Draw("histsame");
  if(m_useData)
    tgdata->Draw("pesame");

  if(m4lfound){
    cs->cd();
    h_m4lfit->SetLineColor(kGreen+2);
    h_m4lfit->SetLineStyle(2);
    h_m4lfit->SetLineWidth(3);
    h_m4lfit ->Draw("same");
    DrawVarBinEdges(name);
  }
  if(m_useData)
    tgdata->Draw("pesame");


  if( useSystematicBand(name) ){
    if( isDiffVar(name) )
      SysBand = CreateVarSysBand(list_histo.at(0),h_chan);
    else if( isDiffVarMass(name) )
      SysBand = CreateVarMassSysBand(list_histo.at(0),h_chan);
    else if( isMass(name) )
      SysBand = CreateMassSysBand(list_histo.at(0),h_chan);
    
    SysBand->SetMarkerStyle( 0);
    SysBand->SetLineColor( 0);
    SysBand->SetFillColor(1);
    SysBand->SetFillStyle(3254);
    SysBand->GetXaxis()->SetRangeUser(XMin,XMax);
    leg->AddEntry(SysBand,"Uncertainty","f");
    SysBand->Draw("same2");
  }
  
  gPad->RedrawAxis();

  DrawLabels();
  leg->Draw("same");

  if(m4lfound)
    name = name+"_mPDF";
  
  /* doing linear plot */
  if(m_doLinear){
    dummy->GetYaxis()->SetRangeUser(0,Max*LinYscl);
    if(m_useData) tgdata->GetYaxis()->SetRangeUser(0,Max*LinYscl);
    cs->SaveAs(m_OutDir+"/"+name+".pdf");
    cs->SaveAs(m_OutDir+"/"+name+".eps");
  }

  /* doing log plot */
  dummy->GetYaxis()->SetRangeUser(Min,Max*LogYscl);
  if(m_useData) tgdata->GetYaxis()->SetRangeUser(Min,Max*LogYscl);
  cs->SetLogy();
  cs->SaveAs(m_OutDir+"/"+name+"_log.pdf");
  cs->SaveAs(m_OutDir+"/"+name+"_log.eps");
  
  /* making yield table */
  if ( (name.Contains("pt") || name.Contains("m34") || name.Contains("m12") ||
	name.Contains("njet") || name.Contains("y") || name.Contains("cts") ||
	name.Contains("nbjet")|| name.Contains("jj")) ){
    std::vector<double> SigBkg;

    m_tableFile.clear();
    m_tableFile.open( (m_OutDir+"/"+(std::string)name+"_table.tex").c_str() );
    CreateTableHeader();
    
    for (int i =0; i<t->GetNbinsX() ; ++i){
      std::ostringstream val;
      val << std::setprecision(3)
	  << (h_data->GetBinContent(i+1)*h_data->GetBinWidth(i+1));

      FillTableBin(i);
      
      for (unsigned int j =1; j<list_histo.size(); ++j){
	val.str(""); val.clear();  //reset buffer
	val << std::setprecision(3)
	    << (list_histo.at(j)->GetBinContent(i+1)*list_histo.at(j)->GetBinWidth(i+1));
	SigBkg.push_back( list_histo.at(j)->GetBinContent(i+1)*list_histo.at(j)->GetBinWidth(i+1) );
      }
      val.str(""); val.clear();
      val << std::setprecision(3) << SigBkg.at(0)/getBkgTot(SigBkg);

      val.str(""); val.clear();
      val.str(""); val.clear();
      val << std::setprecision(3) << getSignificance(SigBkg,true);
      
      FillTableRow(list_histo,SigBkg,i);
      SigBkg.clear();
      
    }
    
    m_tableFile << " \\end{tabular}";
    m_tableFile << ("  %\\caption {mortacci tua. }\\label{tab:mortaccitua"+(std::string)name+"_fit_asimov}\n").c_str();
    m_tableFile.close();
    
  }
  
  t->Print();

  /* Cleaning */
  if(h_m4lfit!=NULL)  h_m4lfit->Delete();
  //if(m4lhistos!=NULL) m4lhistos->Close();
  if(tgdata!=NULL)    tgdata->Delete();
  if(SysBand!=NULL)   SysBand->Delete();
  delete cs;
  h_ZZ   ->Delete();
  h_ZZEW ->Delete();
  h_Zjets->Delete();
  h_Mbos ->Delete();
  h_data ->Delete();
  if(a!=NULL) a->Delete();
  dummy  ->Delete();
  leg->Delete();
  list_histo.clear();
  v_chan.clear();

  
}

void doPlots :: drawHisto2Dm12m34(TH1F *t){

  std::cout << " <doPlots::doHisto2Dm12m34()>: "
	    << "making m12m34 plots with 2D pad" << std::endl;

  cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();

  h_Sig   = (TH1F*)m_f->Get( ("hm12m34_"+m_channel+"_AllSig").c_str()      );
  h_ZZ    = (TH1F*)m_f->Get( ("hm12m34_"+m_channel+"_AllZZ").c_str()       );
  h_Zjets = (TH1F*)m_f->Get( ("hm12m34_"+m_channel+"_Zjets").c_str()       );
  h_Mbos  = (TH1F*)m_f->Get( ("hm12m34_"+m_channel+"_MultiBoson").c_str()  );
  h_Red   = (TH1F*)m_f->Get( ("hm12m34_"+m_channel+"_redBkg").c_str()      );
  h_data  = (TH1F*)m_f->Get( ("hm12m34_"+m_channel+"_data").c_str()        );
  dummy   = (TH1F*)h_data->Clone( "dummym12m34" ); dummy->Reset();

  v_chan.push_back( "data"   );                        list_histo.push_back( h_data );
  v_chan.push_back( "Signal (m_{H}=125 GeV)" );        list_histo.push_back( h_Sig  );
  v_chan.push_back( "Background ZZ*"    );             list_histo.push_back( h_ZZ   );
  if(m_useRedBkg){
    v_chan.push_back( "Background Z+jets, t#bar{t}, t#bar{t}+V, VVV" );  list_histo.push_back( h_Red );
  }
  else{
    v_chan.push_back( "Background t#bar{t}+V, VVV" );    list_histo.push_back( h_Mbos );
    if(m_useZjets){
      v_chan.push_back( "Background Z+jets, t#bar{t}" );  list_histo.push_back( h_Zjets );
    }
  }
  
  std::string Rep = "MC";
  if(m_useData) Rep = "Data";
  TString name = ((TString)h_ZZ->GetName()).ReplaceAll( "AllZZ", ("w2D_"+Rep).c_str() );

  /* Creating legend */
  leg = new TLegend(0.61,0.7,0.92,0.93);
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);

  /* Defining ranges */
  double LinYscl = GetYlinScaleCoeff(name);
  //Double_t Min   = GetYaxisMin(name);
  Double_t Max   = GetYaxisMax(name,h_data);
  Double_t XMin  = h_data->GetXaxis()->GetXmin();
  Double_t XMax  = h_data->GetXaxis()->GetXmax();
  
  /* Creating data graph */
  if(m_useData)
    tgdata = RetrieveData(list_histo.at(0));

  /* setting axis label */
  double wd = list_histo.at(0)->GetBinWidth(1);
  dummy->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
  dummy->GetXaxis()->SetTitle( GetAxisLabel(name).c_str() );
  if(m_useData){
    tgdata->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
    tgdata->GetXaxis()->SetTitle( GetAxisLabel(name).c_str() );
  }

  /* set style and ranges */
  setStyleAndLumi( dummy );
  dummy->GetYaxis()->SetRangeUser(0,Max);
  dummy->GetXaxis()->SetRangeUser(XMin,XMax);
  for (uint i=0; i<list_histo.size(); ++i){
    setStyleAndLumi( list_histo.at(i) );
    if(m_useData && i==0)
      leg->AddEntry(list_histo.at(i),"Data", "pe"); //leg->AddEntry(list_histo.at(i),(v_chan.at(i)), "ple")
    if(i>0)
      leg->AddEntry(list_histo.at(i),(v_chan.at(i)), "f");
    list_histo.at(i)->GetYaxis()->SetRangeUser(0,Max);
    list_histo.at(i)->GetXaxis()->SetRangeUser(XMin,XMax);
    list_histo.at(i)->GetYaxis()->SetTitle( GetYaxisName(name,wd).c_str() );
    list_histo.at(i)->GetXaxis()->SetTitle( GetAxisLabel(name).c_str() );
  }
  if(m_useData){
    tgdata->GetYaxis()->SetRangeUser(0,Max);
    tgdata->GetXaxis()->SetRangeUser(XMin,XMax);
  }

  h_chan = new THStack("h_chan","");
  for (uint i = list_histo.size()-1 ; i>0; --i)
    h_chan->Add(list_histo.at(i));

  cs->cd();
  dummy->Draw();
  h_chan->Draw("histsame");
  if(m_useData)
    tgdata->Draw("pesame");

  if( useSystematicBand(name) ){
    if( isDiffVar(name) )
      SysBand = CreateVarSysBand(list_histo.at(0),h_chan);
    else if( isDiffVarMass(name) )
      SysBand = CreateVarMassSysBand(list_histo.at(0),h_chan);
    else if( isMass(name) )
      SysBand = CreateMassSysBand(list_histo.at(0),h_chan);
    
    SysBand->SetMarkerStyle( 0);
    SysBand->SetLineColor( 0);
    SysBand->SetFillColor(1);
    SysBand->SetFillStyle(3254);
    SysBand->GetXaxis()->SetRangeUser(XMin,XMax);
    leg->AddEntry(SysBand,"Uncertainty","f");
    SysBand->Draw("same2");
  }
  
  gPad->RedrawAxis();

  DrawLabels();
  leg->Draw("same");

  /* doing linear plot */
  dummy->GetYaxis()->SetRangeUser(0,Max*LinYscl*1.2);
  if(m_useData) tgdata->GetYaxis()->SetRangeUser(0,Max*LinYscl*1.2);

  /* creating pad */
  TPad *np = new TPad ("m12m34_2D", "m12m34_2D", 0.16, 0.34, 0.62, 0.80);
  np->Draw();
  np->cd();
  SetPalette(true);
  
  leg1 = new TLegend(0.63,0.68,0.89,0.94);
  leg1->ConvertNDCtoPad();
  leg1->SetTextFont(42);
  leg1->SetFillStyle(0);
  leg1->SetShadowColor(0);
  leg1->SetLineColor(0);
  leg1->SetBorderSize(0);
  
  TH1F *tZZ   = (TH1F*)m_f->Get( ("hm12vsm34_"+m_channel+"_AllZZ").c_str() );
  TH1F *tMbos = (TH1F*)m_f->Get( ("hm12vsm34_"+m_channel+"_MultiBoson").c_str() );
  TH1F *tdata = NULL;
  if(m_useData)
    tdata = (TH1F*)m_f->Get( ("hm12vsm34_"+m_channel+"_data").c_str() );
  
  tZZ->Add(tMbos);
  
  t->Scale(5);
  tZZ->Scale(m_lumi);
  
  t->SetFillColor(sigCol);
  t->SetLineWidth(1);
  t->SetLineColor(1);
  for(int i=1; i<t->GetNbinsX(); i++){
    for(int j=1; j<t->GetNbinsY(); j++){

      if(t->GetBinContent(i,j)<0.003)
	t->SetBinContent(i,j,0);

      //if(tZZ->GetBinContent(i,j)<0)
      //tZZ->SetBinContent(i,j,0);
    }
  }
  tZZ->SetFillColor(kRed-9);
  tZZ->SetLineWidth(1);
  tZZ->SetLineColor(1);
  
  if(m_useData)
    leg1->AddEntry(tdata,"Data","p");
  leg1->AddEntry(t,"Signal","f");
  leg1->AddEntry(tZZ,"Background","f");

  tZZ->GetXaxis()->SetTitleOffset(1.10);
  tZZ->GetXaxis()->SetTitleSize(0.06);
  tZZ->GetXaxis()->SetLabelSize(0.06);
  tZZ->GetYaxis()->SetTitleOffset(1.10);
  tZZ->GetYaxis()->SetTitleSize(0.06);
  tZZ->GetYaxis()->SetLabelSize(0.06);
  tZZ->Draw("COL1");
  t->Draw("BOXsame");
  if(m_useData){
    tdata->SetMarkerSize(0.5);
    tdata->Draw("psame");
  }
  drawLinesBins();
  leg1->Draw();
  
  cs->SaveAs(m_OutDir+"/"+name+".pdf");
  cs->SaveAs(m_OutDir+"/"+name+".eps");
  
  /* Cleaning */
  if(tgdata!=NULL)    tgdata->Delete();
  if(SysBand!=NULL)   SysBand->Delete();
  delete cs;
  h_Sig  ->Delete();
  h_ZZ   ->Delete();
  h_Zjets->Delete();
  h_Mbos ->Delete();
  h_data ->Delete();
  dummy  ->Delete();
  leg->Delete();
  list_histo.clear();
  v_chan.clear();
  if(tdata!=NULL) tdata->Delete();
  tZZ->Delete();
  tMbos->Delete();
  leg1->Delete();
  
}

void doPlots :: MakeMatrix(TH2F* t){

  names = GetBinsName(t);
  int nbin = t->GetNbinsX();
  std::string lb  = GetLabel( t->GetName() );
  std::string alb = GetAxisLabel( t->GetName() );
  lb = (std::string)t->GetName();
  tfinal = new TH2F( ("responcemtx_"+lb).c_str(), ("responcemtx_"+lb).c_str(),
		     nbin, 0, nbin, nbin, 0, nbin);

  for(int i=1; i<t->GetNbinsY()+1; ++i) {
    float norm = 0;
    tfinal->GetYaxis()->SetBinLabel(i, (names[i-1]+"-"+names[i]).c_str() );
    for (int j=1; j<t->GetNbinsX()+1; j++)
      norm += t->GetBinContent(j,i)*t->GetXaxis()->GetBinWidth(j);
    
    for(int j=1; j<t->GetNbinsX()+1; j++)
      tfinal->SetBinContent(j, i, t->GetBinContent(j,i)*t->GetXaxis()->GetBinWidth(j)/norm);

    for(int j=1; j<t->GetNbinsX()+1; j++)
      tfinal->GetXaxis()->SetBinLabel( j, (names[j-1]+"-"+names[j]).c_str() );
  }
  tfinal->GetXaxis()->SetTitle( (alb+" (reco)").c_str() );
  tfinal->GetYaxis()->SetTitle( (alb+" (truth)").c_str() );
  setStyle(tfinal);

  TString name = ((TString)t->GetName()).ReplaceAll( "AllSig", "Matrix" );
  cs = new TCanvas("cs","cs",0,0,600,600);
  cs->cd();
  gStyle->SetOptStat(000000);
  cs->SetGridx(1);
  cs->SetGridy(1);
  SetPalette();
  tfinal->Draw("ZCOLTEXT");
  DrawLabels();
  cs->SaveAs(m_OutDir+"/"+name+".pdf");
  cs->SaveAs(m_OutDir+"/"+name+".eps");
  
  t->Print();

  /* Cleaning */
  tfinal->Delete();
  names.clear();
  delete cs;
  
}

void doPlots :: DrawLabels(){

  Double_t Xlum=0.18, Ylum=0.81;
  Double_t Xatl=0.18, Yatl=0.89;
  Double_t Xlab=0.29, Ylab=0.89;
  Double_t Xch =0.18, Ych =0.85;
  
  std::string Ecm_Lumi  = "13 TeV"; //"#sqrt{s} = 13 TeV";
  std::string IntPreSim = "Simulation";
  std::string Channel   = "H #rightarrow ZZ* #rightarrow ";
  if(m_channel=="incl")       Channel += "4l";
  else if(m_channel=="4mu")   Channel += "4#mu";
  else if(m_channel=="4e")    Channel += "4e";
  else if(m_channel=="2e2mu") Channel += "2e2#mu";
  else if(m_channel=="2mu2e") Channel += "2#mu2e";
  if(m_useData){
    IntPreSim = "Internal";
    if(m_conf)   IntPreSim = "Preliminary";
    if(m_paper)  IntPreSim = "";
  }
  if(!m_doMatrix){
    Ecm_Lumi += ", "+m_LumiStr+" fb^{-1}";
  }

  if(m_doMatrix){
    Xlum=0.50, Ylum=0.96;
    Xatl=0.20, Yatl=0.96;
    Xlab=0.31, Ylab=0.96;
  }
  
  TLatex lumi;
  lumi.SetNDC();
  lumi.SetTextFont(42);
  lumi.SetTextSize(0.033);
  lumi.SetTextColor(kBlack);
  lumi.DrawLatex( Xlum,Ylum,(Ecm_Lumi).c_str() );

  TLatex AT;
  AT.SetNDC();
  AT.SetTextFont(72);
  AT.SetTextSize(0.033);
  AT.SetTextColor(kBlack);
  AT.DrawLatex( Xatl,Yatl,"ATLAS" );

  TLatex Chan;
  Chan.SetNDC();
  Chan.SetTextFont(42);
  Chan.SetTextSize(0.033);
  Chan.SetTextColor(kBlack);
  if(!m_doMatrix)
    Chan.DrawLatex( Xch,Ych,Channel.c_str() );
  
  TLatex Lab;
  Lab.SetNDC();
  Lab.SetTextFont(42);
  Lab.SetTextSize(0.033);
  Lab.SetTextColor(kBlack);
  Lab.DrawLatex( Xlab,Ylab,IntPreSim.c_str() );
  
}

TGraphAsymmErrors* doPlots :: RetrieveData(TH1F* data){
  
  TGraphAsymmErrors *tgdata = new TGraphAsymmErrors();
  TString name  = data->GetName();
  std::vector<double> wid;
  wid.push_back(120.);
  wid.push_back(2880.);
  
  for (int i = 0; i<data->GetNbinsX(); ++i){
    if( name.Contains("hmjjrm_") )
      data->SetBinContent(i+1, data->GetBinContent(i+1)*wid.at(i));
    else
      data->SetBinContent(i+1, data->GetBinContent(i+1)*data->GetBinWidth(i+1));
    TH1F *h1  = new TH1F("h1","Poisson",2000,0, 200);
    double dr = data->GetBinContent(i+1);
    
    float down = 0;
    float up= 0;
    TF1 *f1 = new TF1("f1","TMath::Poisson(x,[0])",0,200);
    if(dr>100) {
      //std::cout << "max evaluation for dr = 100 -> break!" << std::endl; 
      down = sqrt(dr);
      up = sqrt(dr);
    }
    else if (dr>0){
      f1->SetParameter(0,dr);
      h1->FillRandom("f1",200000);
      for(int i=1; i < h1->GetNbinsX(); ++i){
	down =  h1->Integral(i, h1->FindBin(dr))/h1->Integral();
	if(down<0.34135){
	  down=dr-h1->GetBinCenter(i+1);
	  break;
	}
      }
      for (int i=h1->GetNbinsX(); i >0; --i){
	up =  h1->Integral(h1->FindBin(dr),i)/h1->Integral();
	if(up<0.34135){
	  up=h1->GetBinCenter(i+1)-dr;
	  break;
	}
      }
    }
    double BinContent = data->GetBinContent(i+1);
    if(BinContent==0) BinContent=-1;
    if( name.Contains("hmjjrm_") ){
      tgdata->SetPoint(i, data->GetBinCenter(i+1), /*data->GetBinContent(i+1)*/BinContent/wid.at(i) );
      //tgdata->SetPointError(i, data->GetBinWidth(i+1)/2., data->GetBinWidth(i+1)/2., down/wid.at(i), up/wid.at(i));
      tgdata->SetPointError(i, 0, 0, down/wid.at(i), up/wid.at(i));
      data->SetBinContent(i+1, data->GetBinContent(i+1)/wid.at(i));
    }
    else{
      tgdata->SetPoint(i, data->GetBinCenter(i+1), /*data->GetBinContent(i+1)*/BinContent/data->GetBinWidth(i+1) );
      //tgdata->SetPointError(i, data->GetBinWidth(i+1)/2., data->GetBinWidth(i+1)/2., down/data->GetBinWidth(i+1), up/data->GetBinWidth(i+1));
      tgdata->SetPointError(i, 0, 0, down/data->GetBinWidth(i+1), up/data->GetBinWidth(i+1));
      data->SetBinContent(i+1, data->GetBinContent(i+1)/data->GetBinWidth(i+1));
    }
    tgdata->GetXaxis()->SetRangeUser(data->GetBinLowEdge(1), data->GetBinLowEdge(data->GetNbinsX())+data->GetBinWidth(data->GetNbinsX()));
    
    delete h1;
  }
  tgdata->SetMarkerStyle(20);
  tgdata->SetMarkerSize(1.2);
  tgdata->SetLineWidth(1.2);
  
  return tgdata;
  
}

std::string doPlots :: GetYaxisName(TString name, double wd){

  std::string m_txt = "";
  if( name.Contains("hpt")  || name.Contains("hm")    ||
      name.Contains("hmjj") || name.Contains("hljpt")  ){
    
    m_txt = "Events / GeV";
    if( name.Contains("hm_") ){
      if(wd==1)
	m_txt = "Events / GeV";
      else
	m_txt = "Events / "+ConvertToStringWithPrecision(wd,2)+" GeV";
    }
    else if( name.Contains("hm12m34") )
      m_txt = "Events";
  }
  else if( name.Contains("hnjet") || name.Contains("hnbjet") ){
    m_txt = "Events";
  }
  else if( name.Contains("hphijj") ){
    m_txt = "Events / rad";
  }
  else{
    m_txt = "Events / Bin Width";
  }  
  
  return m_txt;
  
}

double doPlots :: GetYaxisMin(TString name){

  double m_min = 0;
  if( m_SigOnly){
    if( name.Contains("hpt") ) m_min = 0.00005;
    else if( name.Contains("hnjet") ) m_min = 0.05;
    else if( name.Contains("hnbjet") ) m_min = 0.005;
    else if( name.Contains("hy") || name.Contains("hcts") ) m_min = 0.005;
    else if( name.Contains("hm12") || name.Contains("hm34") ) m_min = 0.0005;
    else if( name.Contains("hetajj") || name.Contains("hphijj") ) m_min = 0.005;
    else m_min = 0.00005;
  }
  else{
    if( name.Contains("hpt") ) m_min = 0.00005;
    else if( name.Contains("hm12") || name.Contains("hnjet") ) m_min = 0.05;
    else if( name.Contains("hy") || name.Contains("hcts") ) m_min = 0.5;
    else if( name.Contains("hm34") ) m_min = 0.0005;
    else if( name.Contains("hnbjet") ) m_min = 0.05;
    else m_min = 0.00005;
  }
  return m_min;
  
}

double doPlots :: GetYaxisMax(TString name, TH1F* h){

  double m_max = h->GetMaximum();
  if(m_max==0) m_max = 10;
  if(m_SigOnly){
    if( name.Contains("hmjj") )        m_max = m_max*2;
    else if( name.Contains("hetajj") ) m_max = m_max*10;
    else if( name.Contains("hphijj") ) m_max = m_max*20;
  }
  else{
    if( name.Contains("jj") ){
      if(m_lowMass){
	if( name.Contains("etajj") )m_max = m_max*2;
	else if( name.Contains("phijj") )m_max = m_max*2.4;
      }
      else{
	if( name.Contains("etajj") )m_max = m_max*1.7;
	else if( name.Contains("phijj") )m_max = m_max*1.5;
      }
      if( name.Contains("mjj") ) m_max = m_max*2.8;
    }
    else if( name.Contains("hljpt") )   m_max = m_max*1.3;
    else if( name.Contains("hpt0j") )   m_max = m_max*1.2;
    else if( name.Contains("hpt1j") )   m_max = m_max*1.3;
    else if( name.Contains("hpt2j") )   m_max = m_max*1.3;
    else if( name.Contains("hpt_") )    m_max = m_max*1.2;
    else if( name.Contains("hm12m34") ) m_max = m_max*1.8;
    else if( name.Contains("hm12_") )   m_max = m_max*1.4;
    else if( name.Contains("hm34") ){
      //if(m_highMass) m_max = m_max*1.8;
      //else
      m_max = m_max*1.3;
    }
    else if( name.Contains("hm_") ){
      if( name.Contains("4mu") )         m_max = m_max*1.4;
      else if( name.Contains("4e") )     m_max = m_max*1.4;
      else if( name.Contains("2mu2e") )  m_max = m_max*1.4;
      else if( name.Contains("2e2mu") )  m_max = m_max*1.4;
      else                               m_max = m_max*1.6;
      if( name.Contains("ptbin0") )      m_max = m_max*1.2;
      else if( name.Contains("ptbin9") ) m_max = m_max*1.6;
    }
    else if( name.Contains("hnbjet") ){
      if(m_lowMass) m_max = m_max*1.5;
      else          m_max = m_max*1.4;
    }
    else if( name.Contains("hnjet") )   m_max = m_max*1.2;
    else if( name.Contains("hcts") )    m_max = m_max*1.5;
    else if( name.Contains("hy") )      m_max = m_max*1.3;
  }
  return m_max;
  
}

double doPlots :: GetYlinScaleCoeff(TString name){

  double m_scale = 1.3;
  if(m_SigOnly){
    m_scale = 1.3;
    if( name.Contains("hm12m34") ) m_scale = 0.9;
  }
  else{
    if( name.Contains("jj") ){
      m_scale = 1.1;
      if( name.Contains("hmjj") ) m_scale = 1.0;
    }
    else if( name.Contains("hnbjet") )  m_scale = 1.1;

    if(m_channel!="incl"){
      if( name.Contains("hm_") )     m_scale = 1.6;
    }
  }
  return m_scale;
  
}

double doPlots :: GetYlogScaleCoeff(TString name){

  double m_scale = 5.0;
  if(m_SigOnly){
    m_scale = 5.0;
    if( name.Contains("hpt2j") )        m_scale = 10.0;
    else if( name.Contains("hm12m34") ) m_scale = 30.0;
    else if( name.Contains("hnbjet") )  m_scale = 12.0;
    
  }
  else{
    if( name.Contains("hm12m34") )      m_scale = 20.0;
    else if( name.Contains("hnbjet") )  m_scale = 10.0;
    else if( name.Contains("hpt_") )    m_scale = 30.0;
    else if( name.Contains("hpt0j") )   m_scale = 30.0;
    else if( name.Contains("hpt1j") )   m_scale = 20.0;
    else if( name.Contains("hpt2j") )   m_scale = 20.0;
    else if( name.Contains("hljpt") )   m_scale = 20.0;
  }
  return m_scale;
  
}

TGraphAsymmErrors* doPlots :: CreateVarSysBand(TH1F *h, THStack *stack){

  std::string Variable = DetectHisto( h->GetName() );
    
  SysFile = new TFile( ("../ws_output/"+Variable+"_totalSysShape.root").c_str() );
  
  Nom  = (TH1F*)SysFile->Get( "nominal_all" );
  Down = (TH1F*)SysFile->Get( "down_all"    );
  Up   = (TH1F*)SysFile->Get( "up_all"      );

  std::vector<double> XVal, YVal, XWid, UpSys, DwSys;
  
  Int_t N = h->GetNbinsX();
  Int_t Offset = 0;
  
  if(Variable=="ptpt"){
    /* bins ptpt -> pt0j = 1-4 , pt1j = 5-9 , pt2j = 10-11 */
    if( ((TString)h->GetName()).Contains("pt1j") ) Offset = 4;
    else if( ((TString)h->GetName()).Contains("pt2j") ) Offset = 9;
  }
  
  for(int b=1; b<N+1; b++){

    double UpVal = 0, DwVal = 0;
    if( Up->GetBinContent(b+Offset) > Down->GetBinContent(b+Offset) ){
      UpVal = Up->GetBinContent(b+Offset);
      DwVal = Down->GetBinContent(b+Offset);
    }
    else{
      DwVal = Up->GetBinContent(b+Offset);
      UpVal = Down->GetBinContent(b+Offset);
    }
    UpSys.push_back( UpVal/Nom->GetBinContent(b+Offset)-1 );
    DwSys.push_back( 1-DwVal/Nom->GetBinContent(b+Offset) );
  }
  
  for(int b=1; b<N+1; b++){
    XVal.push_back( h->GetBinCenter(b) );
    XWid.push_back( h->GetBinWidth(b) );
    YVal.push_back( ((TH1*)(stack->GetStack()->Last()))->GetBinContent(b) );
  }
	
  Double_t xVal[N], yVal[N];
  Double_t xErr[N], yErrU[N], yErrD[N];

  for(int p=1; p<N+1; p++){
    xVal[p-1]  = XVal.at(p-1);
    yVal[p-1]  = YVal.at(p-1);
    xErr[p-1]  = XWid.at(p-1)/2;
    
    yErrU[p-1] =  sqrt( pow(YVal.at(p-1)*UpSys.at(p-1),2)+pow(((TH1*)(stack->GetStack()->Last()))->GetBinError(p),2) ); //syst+stat in quad
    yErrD[p-1] =  sqrt( pow(YVal.at(p-1)*DwSys.at(p-1),2)+pow(((TH1*)(stack->GetStack()->Last()))->GetBinError(p),2) ); //syst+stat in quad

  }
  
  TGraphAsymmErrors *band = new TGraphAsymmErrors(N, xVal, yVal, xErr, xErr, yErrD, yErrU);
  band->GetXaxis()->SetTitle( GetAxisLabel( h->GetName() ).c_str() );

  /* Cleaning */
  Nom->Delete();
  Down->Delete();
  Up->Delete();
  SysFile->Close();
  
  return band;
  
  return band;
  
}

TGraphAsymmErrors* doPlots :: CreateVarMassSysBand(TH1F *h, THStack *stack){

  std::string Variable = DetectMassHisto( h->GetName() );
  Int_t b = GetHistoBin( h->GetName() );
  
  SysFile = new TFile( ("../ws_output/"+Variable+"_totalSysShape.root").c_str() );

  Nom  = (TH1F*)SysFile->Get( "nominal_all" );
  Down = (TH1F*)SysFile->Get( "down_all"    );
  Up   = (TH1F*)SysFile->Get( "up_all"      );

  std::vector<double> XVal, YVal, XWid;
  double UpSys, DwSys;

  Int_t N = h->GetNbinsX();
  Int_t Offset = 0;
  
  if(Variable=="ptpt"){
    /* bins ptpt -> pt0j = 1-4 , pt1j = 5-9 , pt2j = 10-11 */
    if( ((TString)h->GetName()).Contains("pt1j") ) Offset = 4;
    else if( ((TString)h->GetName()).Contains("pt2j") ) Offset = 9;
  }

  double UpVal = 0, DwVal = 0;
  if(Up->GetBinContent(b+Offset) > Down->GetBinContent(b+Offset) ){
    UpVal = Up->GetBinContent(b+Offset);
    DwVal = Down->GetBinContent(b+Offset);
  }
  else{
    DwVal = Up->GetBinContent(b+Offset);
    UpVal = Down->GetBinContent(b+Offset);
  }
  UpSys = UpVal/Nom->GetBinContent(b+Offset)-1 ;
  DwSys = 1-DwVal/Nom->GetBinContent(b+Offset) ;
  
  for(int b=1; b<N+1; b++){
    XVal.push_back( h->GetBinCenter(b) );
    XWid.push_back( h->GetBinWidth(b) );
    YVal.push_back( ((TH1*)(stack->GetStack()->Last()))->GetBinContent(b) );
  }

  Double_t xVal[N], yVal[N];
  Double_t xErr[N], yErrU[N], yErrD[N];
  
  for(int p=1; p<N+1; p++){
    xVal[p-1]  = XVal.at(p-1);
    yVal[p-1]  = YVal.at(p-1);
    xErr[p-1]  = XWid.at(p-1)/2;
    
    yErrU[p-1] =  sqrt( pow(YVal.at(p-1)*UpSys,2)+pow(((TH1*)(stack->GetStack()->Last()))->GetBinError(p),2) ); //syst+stat in quad
    yErrD[p-1] =  sqrt( pow(YVal.at(p-1)*DwSys,2)+pow(((TH1*)(stack->GetStack()->Last()))->GetBinError(p),2) ); //syst+stat in quad

  }
  
  TGraphAsymmErrors *band = new TGraphAsymmErrors(N, xVal, yVal, xErr, xErr, yErrD, yErrU);
  band->GetXaxis()->SetTitle( GetAxisLabel( h->GetName() ).c_str() );

  /* Cleaning */
  Nom->Delete();
  Down->Delete();
  Up->Delete();
  SysFile->Close();
  
  return band;
  
}

TGraphAsymmErrors* doPlots :: CreateMassSysBand(TH1F *h, THStack *stack){

  std::string Variable = DetectMassHisto( h->GetName() );

  SysFile = new TFile( ("../ws_output/"+Variable+"_fidchannel_totalSysShape.root").c_str() );

  if(m_channel=="incl"){
    Nom  = GetNominal(SysFile);
    Down = GetVariation(SysFile,"down");
    Up   = GetVariation(SysFile,"up");
    
  }
  else{
    Nom  = (TH1F*)SysFile->Get( ("nom"+m_channel+"_all").c_str()  );
    Down = (TH1F*)SysFile->Get( ("down"+m_channel+"_all").c_str() );
    Up   = (TH1F*)SysFile->Get( ("up"+m_channel+"_all").c_str()   );
  }
  std::cout<<" Up Var = "<<Up->Integral()/Nom->Integral()-1
	   <<" Dw Var = "<<1-Down->Integral()/Nom->Integral()<<std::endl;
  
  std::vector<double> XVal, YVal, XWid, UpSys, DwSys;

  Int_t N = h->GetNbinsX();
  for(int b=1; b<N+1; b++){
    
    double UpVal = 0, DwVal = 0;
    if(Up->GetBinContent(b) > Down->GetBinContent(b) ){
      UpVal = Up->GetBinContent(b);
      DwVal = Down->GetBinContent(b);
    }
    else{
      DwVal = Up->GetBinContent(b);
      UpVal = Down->GetBinContent(b);
    }
    UpSys.push_back( UpVal/Nom->GetBinContent(b)-1 );
    DwSys.push_back( 1-DwVal/Nom->GetBinContent(b) );
    
  }
  
  for(int b=1; b<N+1; b++){
    XVal.push_back( h->GetBinCenter(b) );
    XWid.push_back( h->GetBinWidth(b) );
    YVal.push_back( ((TH1*)(stack->GetStack()->Last()))->GetBinContent(b) );
  }

  Double_t xVal[N], yVal[N];
  Double_t xErr[N], yErrU[N], yErrD[N];
  
  for(int p=1; p<N+1; p++){
    
    xVal[p-1]  = XVal.at(p-1);
    yVal[p-1]  = YVal.at(p-1);
    xErr[p-1]  = XWid.at(p-1)/2;
    
    yErrU[p-1] =  sqrt( pow(YVal.at(p-1)*UpSys.at(p-1),2)+pow(((TH1*)(stack->GetStack()->Last()))->GetBinError(p),2) ); //syst+stat in quad
    yErrD[p-1] =  sqrt( pow(YVal.at(p-1)*DwSys.at(p-1),2)+pow(((TH1*)(stack->GetStack()->Last()))->GetBinError(p),2) ); //syst+stat in quad
    
  }
  
  TGraphAsymmErrors *band = new TGraphAsymmErrors(N, xVal, yVal, xErr, xErr, yErrD, yErrU);
  band->GetXaxis()->SetTitle( GetAxisLabel( h->GetName() ).c_str() );

  /* Cleaning */
  Nom->Delete();
  Down->Delete();
  Up->Delete();
  SysFile->Close();
  
  return band;
  
}

std::pair<double,double> doPlots :: GetXaxisRanges(TH1F* h){

  int bins = h->GetNbinsX();
  double min = h->GetBinLowEdge(1);
  double max = h->GetBinLowEdge(bins+1);

  std::pair<double,double> vals;
  vals = std::make_pair(min,max);
  return vals;
  
}

TH1F * doPlots :: GetNominal(TFile *sysFile){

  TH1F *h4mu   = (TH1F*)sysFile->Get( "nom4mu_all"   );
  TH1F *h4e    = (TH1F*)sysFile->Get( "nom4e_all"    );
  TH1F *h2mu2e = (TH1F*)sysFile->Get( "nom2mu2e_all" );
  TH1F *h2e2mu = (TH1F*)sysFile->Get( "nom2e2mu_all" );
  TH1F *tot    = (TH1F*)h4mu->Clone( "incl" );
  tot->Add(h4e);
  tot->Add(h2mu2e);
  tot->Add(h2e2mu);

  return tot;
  
}

TH1F * doPlots :: GetVariation(TFile *sysFile, std::string var){

  TH1F *Var_4mu   = (TH1F*)sysFile->Get( (var+"4mu_all").c_str()   );
  TH1F *Var_4e    = (TH1F*)sysFile->Get( (var+"4e_all").c_str()    );
  TH1F *Var_2mu2e = (TH1F*)sysFile->Get( (var+"2mu2e_all").c_str() );
  TH1F *Var_2e2mu = (TH1F*)sysFile->Get( (var+"2e2mu_all").c_str() );

  TH1F *Var_tot = (TH1F*)Var_4mu->Clone( (var+"incl").c_str() );
  Var_tot->Add(Var_4e);
  Var_tot->Add(Var_2mu2e);
  Var_tot->Add(Var_2e2mu);

  return Var_tot;
  
}

void doPlots :: drawLinesBins(){

  TF1 *constraint1 = new TF1("constraint1", "130-x", 65 , 106);
  TF1 *constraint2 = new TF1("constraint2", "x"    , 50 , 65 );
  TF1 *constrainth = new TF1("constrainth", "32"   , 50 , 98 );
  TLine *constraint3  = new TLine(50 , 12, 50 , 50);
  TLine *constraint4  = new TLine(50 , 12, 106, 12);
  TLine *constraint5  = new TLine(106, 12, 106, 24);
  TLine *constraintv1 = new TLine(74 , 32, 74 , 56);
  TLine *constraintv2 = new TLine(82 , 12, 82 , 32);
  TLine *constrainth1 = new TLine(82 , 24, 106, 24);
  
  constraint1->SetLineColor(kRed);  constraint1->SetLineWidth(2);
  constraint2->SetLineColor(kRed);  constraint2->SetLineWidth(2);
  constraint3->SetLineColor(kRed);  constraint3->SetLineWidth(2);
  constraint4->SetLineColor(kRed);  constraint4->SetLineWidth(2);
  constraint5->SetLineColor(kRed);  constraint5->SetLineWidth(2);
  constraintv1->SetLineColor(kRed); constraintv1->SetLineWidth(2);
  constraintv2->SetLineColor(kRed); constraintv2->SetLineWidth(2);
  constrainth1->SetLineColor(kRed); constrainth1->SetLineWidth(2);
  constrainth->SetLineColor(kRed);  constrainth->SetLineWidth(2);
  constraint1->Draw("same");
  constraint2->Draw("same");
  constraint3->Draw("same");
  constraint4->Draw("same");
  constraint5->Draw("same");
  constrainth->Draw("same");
  constraintv1->Draw("same");
  constraintv2->Draw("same");
  constrainth1->Draw("same");

  TLatex bin;
  bin.SetNDC();
  bin.SetTextFont(42);
  bin.SetTextSize(0.05);
  bin.SetTextColor(kRed+2);

  bin.DrawLatex(0.230,0.420,"bin 0");
  bin.DrawLatex(0.230,0.510,"bin 1");
  bin.DrawLatex(0.555,0.605,"bin 2");
  bin.DrawLatex(0.765,0.390,"bin 3");
  bin.DrawLatex(0.765,0.335,"bin 4");
}
