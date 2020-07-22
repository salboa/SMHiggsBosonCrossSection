//#include "MakeUnfoldPlots.h"

void drawLabels(bool isFiducial){

  Double_t Xval = 0.18;
  Double_t Txt  = 0.033;
  std::string Pub = "Internal";

  if(m_Conf)      {       Pub = "Preliminary"; }
  else if(m_Paper){ Pub = "";            }
    
  if(!isFiducial){
    Xval = 0.22; Txt = 0.045;
  }
  
  TLatex AT;
  AT.SetNDC();
  AT.SetTextFont(72);
  AT.SetTextColor(kBlack);
  if(!isFiducial)
    AT.SetTextSize(Txt);
  AT.DrawLatex( Xval,0.88,"ATLAS" );
    
  TLatex Lab;
  Lab.SetNDC();
  Lab.SetTextFont(42);
  if(!isFiducial)
    Lab.SetTextSize(Txt);
  Lab.SetTextColor(kBlack);
  if(isFiducial)
    Lab.DrawLatex( Xval+0.13,0.88, Pub.c_str() );
  else
    Lab.DrawLatex( Xval+0.10,0.88, Pub.c_str() );
  
  TLatex lumi;
  lumi.SetNDC();
  lumi.SetTextFont(42);
  lumi.SetTextSize(Txt);
  lumi.SetTextColor(kBlack);
  lumi.DrawLatex( Xval,0.76,/*"#sqrt{s} =*/ "13 TeV, 36.1 fb^{-1}" );

  TLatex Chan;
  Chan.SetNDC();
  Chan.SetTextFont(42);
  Chan.SetTextSize(Txt);
  Chan.SetTextColor(kBlack);
  Chan.DrawLatex( Xval,0.82,"H #rightarrow ZZ* #rightarrow 4#font[12]{l}" );
  
}


void setStyle(std::string sample, TH1F *h){
  
  if(sample=="MG5"){
    h->SetLineColor(kBlue);
    h->SetLineWidth(2);
  }
  
  if(sample=="NNLOPSexp"){
    h->SetLineColor(kRed);
    h->SetLineWidth(1);
    h->SetMarkerColor(kRed);
    h->SetMarkerStyle(22);
    h->SetMarkerSize(0);
    h->SetFillColor(kRed);
    h->SetFillStyle(1001);
    
    for(int i=1; i<h->GetNbinsX()+1; ++i)
      h->SetBinError(i, 0.000000001);
    
  }
  
}

void setStyle(std::string sample, TGraphAsymmErrors *h, bool isPoint){
  
  if(sample=="MG5exp"){
    h->SetLineStyle(1);
    h->SetLineColor(kAzure-4);
    h->SetFillColor(kAzure-4);
    h->SetFillStyle(1001);
    h->SetMarkerStyle(33);
    h->SetMarkerColor(kBlue);
    h->SetMarkerSize(0.5);
  }
  
  if(sample=="MG5ratio"){
    h->SetLineColor(kBlue);
    h->SetLineWidth(1);
    h->SetMarkerStyle(33);
    h->SetMarkerSize(0.5);
    h->SetMarkerColor(kBlue);
    h->SetFillColor(kAzure-4);
  }
  
  if(sample=="NNLOPSexp"){
    h->SetLineStyle(1);
    h->SetLineColor(kRed-10);
    h->SetMarkerColor(kRed);
    h->SetMarkerStyle(21);
    h->SetMarkerSize(0.4);
    h->SetFillColor(kRed-10);
    h->SetFillStyle(1001);
  }
  
  if(sample=="NNLOPSratio"){
    h->SetLineColor(kRed);
    h->SetLineWidth(1);
    h->SetMarkerStyle(21);
    h->SetMarkerSize(0.4);
    h->SetMarkerColor(kRed);
    h->SetLineColor(kRed-10);
    h->SetFillColor(kRed-10);
  }
  
  if(sample=="HRESexpected"){
    h->SetLineStyle(1);
    h->SetLineColor(kGreen-8);
    h->SetMarkerStyle(22);
    h->SetMarkerColor(kGreen+3);
    h->SetMarkerSize(0.4);
    h->SetFillColor(kGreen-8);
    h->SetFillStyle(1001);
  }
  
  if(sample=="HRESratio"){
    h->SetLineColor(kGreen+3);
    h->SetLineWidth(1);
    h->SetMarkerStyle(22);
    h->SetMarkerSize(0.4);
    h->SetMarkerColor(kGreen+3);
    h->SetFillColor(kGreen-8);
  }
  
  if(sample=="RESTexpected"){
    h->SetLineStyle(2);
    h->SetLineColor(kBlack);
    h->SetLineWidth(2);
    h->SetMarkerSize(0);
    h->SetFillColor(kBlack);
    h->SetFillStyle(3004);
  }

  if(isPoint)
    h->SetMarkerSize(0.0);
  
}


void SetAtlasStyle(){

  TStyle *atlasStyle= new TStyle("ATLAS","Atlas style");
  
  /*use plain black on white colors*/
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  /*don't use: white fill color for *all* objects*/
  //atlasStyle->SetFillColor(icol); 

  /*set the paper & margin sizes*/
  atlasStyle->SetPaperSize(20,26);

  /*set margin sizes*/
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.05);
  atlasStyle->SetPadBottomMargin(0.16); //ATLAS style 0.16
  atlasStyle->SetPadLeftMargin(0.14);

  /*set title offsets (for axis label)*/
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);

  /*use large fonts*/
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.04; //io=0.04
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");

  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  /*use bold lines and markers*/
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(1.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  /*get rid of X error bars*/
  //atlasStyle->SetErrorX(0.001);
  /*get rid of error bar caps*/
  atlasStyle->SetEndErrorSize(0.00001);

  /*do not display any of the standard histogram decorations*/
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  /*put tick marks on top and RHS of plots*/
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

}

void setAxisLabels(TH1F *g, std::string var, bool ratio){

  std::map< std::string,std::vector<std::string> > name;
  std::map< std::string,float > range;  
  
  name["pt"]     = { "#font[12]{p}_{T,4#font[12]{l}} [GeV]",
		     "d#sigma/d#font[12]{p}_{T,4#font[12]{l}} [fb/GeV]" };
  
  name["m12"]    = { "#font[12]{m}_{12} [GeV]",
		     "d#sigma/d#font[12]{m}_{12} [fb/GeV]" };
  
  name["m34"]    = { "#font[12]{m}_{34} [GeV]",
		     "d#sigma/d#font[12]{m}_{34} [fb/GeV]" };
  
  name["y"]      = { "#left|#font[12]{y}_{4#font[12]{l}}#right|",
		     "d#sigma/d#left|#font[12]{y}_{4#font[12]{l}}#right| [fb]" };
  
  name["njet"]   = { "#font[12]{N}_{jets}",
		     "#sigma [fb]"};
  
  name["njetv4"]   = { "#font[12]{N}_{jets}",
    "#sigma [fb]"};
  
  name["nbjet"]  = { "#font[12]{N}_{b-jets}",
		     "d#sigma/d#font[12]{N}_{b-jets} [fb]"};
  
  name["m12m34"] = { "#font[12]{m}_{12} vs #font[12]{m}_{34}" ,
		     "#sigma [fb]" };
  
  name["cts"]    = { "|cos#theta*|",
		     "d#sigma/d(|cos#theta*|) [fb]" };
  
  name["mjj"]    = { "#font[12]{m}_{jj} [GeV]",
		     "d#sigma/d#font[12]{m}_{jj} [fb/GeV]" };
  
  name["etajj"]  = { "#Delta#eta_{jj}",
		     "d#sigma/d(#Delta#eta_{jj}) [fb]" };
  name["phijj"]  = { "#Delta#phi_{jj} [rad]",
		     "d#sigma/d(#Delta#phi_{jj}) [fb/rad]" };
  
  name["ljpt"]   = { "#font[12]{p}_{T}^{lead. jet} [GeV]",
		     "d#sigma/d#font[12]{p}_{T}^{lead. jet} [fb/GeV]" };
  
  name["pt0j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0} [GeV]" ,
		     "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0} [fb/GeV]" };
  name["pt1j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1} [GeV]",
		     "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1} [fb/GeV]" };
  
  name["pt2j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq2} [GeV]",
		     "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq2} [fb/GeV]" };

  range["pt"]     = 0.15;
  range["m12"]    = 0.65;
  range["m34"]    = 0.38;
  range["y"]      = 5.50;
  range["njet"]   = 3.00;
  range["njetv4"]   = 3.3;
  range["nbjet"]  = 5.50;
  range["m12m34"] = 2.80;
  range["cts"]    = 11.0;
  range["mjj"]    = 0.0025;
  range["etajj"]  = 0.35;
  range["phijj"]  = 0.35;
  range["ljpt"]   = 0.073;
  range["pt0j"]   = 0.08;
  range["pt1j"]   = 0.027;
  range["pt2j"]   = 0.008;

  if (m_integralobs!=1){
    name["pt"]     = { "#font[12]{p}_{T,4#font[12]{l}} [GeV]",
		       "1/#sigma  d#sigma/d#font[12]{p}_{T,4#font[12]{l}} [1/GeV]" };
    
    name["m12"]    = { "#font[12]{m}_{12} [GeV]",
		       "1/#sigma  d#sigma/d#font[12]{m}_{12} [1/GeV]" };
    
    name["m34"]    = { "#font[12]{m}_{34} [GeV]",
		       "1/#sigma  d#sigma/d#font[12]{m}_{34} [1/GeV]" };
    
    name["y"]      = { "|#font[12]{y}_{4#font[12]{l}}|",
		       "1/#sigma  d#sigma/d|#font[12]{y}_{4#font[12]{l}}|" };
    
    name["njet"]   = { "#font[12]{N}_{jets}",
		       "1/#sigma  #sigma" };
    
    name["nbjet"]  = { "#font[12]{N}_{b-jets}",
		       "1/#sigma  d#sigma/d#font[12]{N}_{b-jets}" };
    
    name["m12m34"] = { "#font[12]{m}_{12} vs #font[12]{m}_{34}",
		       "1/#sigma  d^{2}#sigma/d#font[12]{m}_{12}d#font[12]{m}_{34}" };
    
    name["cts"]    = { "|cos#theta*|",
		       "1/#sigma  d#sigma/d(|cos#theta*|)" };
    
    name["mjj"]    = { "#font[12]{m}_{jj} [GeV]",
		       "1/#sigma  d#sigma/d#font[12]{m}_{jj} [1/GeV]" };
    
    name["etajj"]  = { "#Delta#eta_{jj}",
		       "1/#sigma  d#sigma/d(#Delta#eta_{jj})" };
    
    name["phijj"]  = { "#Delta#phi_{jj} [rad]",
		       "1/#sigma  d#sigma/d(#Delta#phi_{jj})" };

    name["ljpt"]   = { "#font[12]{p}_{T}^{lead. jet} [GeV]",
		       "1/#sigma  d#sigma/d#font[12]{p}_{T}^{lead. jet} [1/GeV]" };

    name["pt0j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0} [GeV]",
		       "1/#sigma  d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0} [1/GeV]" };

    name["pt1j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1} [GeV]",
		       "1/#sigma  d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1} [1/GeV]" };

    name["pt2j"]   = { "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq2 [GeV]}",
		       "1/#sigma  d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq2} [1/GeV]" };
    
    range["pt"]     = 0.04 ;
    range["m12"]    = 0.2;
    range["m34"]    = 0.1;
    range["y"]      = 1.3;
    range["njet"]   = 0.8;
    range["njetincl"]   = 3.3;
    range["nbjet"]  = 1.5;
    range["m12m34"] = 0.8;
    range["cts"]    = 3.;
    range["mjj"]    = 0.005;
    range["etajj"]  = 0.45;
    range["phijj"]  = 0.35;
    range["ljpt"]   = 0.04;
    range["ptpt"]   = 1;
    range["pt0j"]   = 0.05;
    range["pt1j"]   = 0.025;
    range["pt2j"]   = 0.01;
  }
  
  g->GetXaxis()->SetTitle(name[var].at(0).c_str());

  if(ratio){
    /* x axis */
    g->GetXaxis()->SetTitleSize(0.12);
    if(var.find("njet")!=std::string::npos)
      g->GetXaxis()->SetTitleOffset(1.1);
    else
      g->GetXaxis()->SetTitleOffset(1.0);
    /* y axis */
    g->GetYaxis()->SetTitleSize(0.11);
    g->GetYaxis()->SetTitle("Data/Theory");
    g->GetYaxis()->SetTitleOffset(0.70);
    g->GetYaxis()->SetRangeUser(0, 2.4);
    g->GetYaxis()->SetLabelSize(0.095);
    g->GetYaxis()->SetNdivisions(8);
    g->GetYaxis()->CenterTitle(kTRUE);
  }
  else{
    g->GetYaxis()->SetTitleSize(0.07);
    g->GetYaxis()->SetLabelSize(0.05);

    g->GetYaxis()->SetTitleOffset(1.13);
    g->GetYaxis()->SetTitle(name[var].at(1).c_str());
    g->GetYaxis()->SetRangeUser(0.,range[var]);
  }
  
}

void AdjustXaxis(TH1F* h, std::string var){

  Double_t Xmin = h->GetXaxis()->GetXmin();
  Double_t Xmax = h->GetXaxis()->GetXmax();
  
  if(var=="pt"){
    Xmax=10;
    h->GetXaxis()->SetNdivisions(0015);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"10");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"15");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"20");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"45");
    h->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"60");
    h->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"80");
    h->GetXaxis()->ChangeLabel(9,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(10,-1,-1,-1,-1,-1,"200");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var=="njet"){
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"1");
    h->GetXaxis()->SetBinLabel(3,"2");
    h->GetXaxis()->SetBinLabel(4,"#geq3");
    h->GetXaxis()->SetLabelSize(0.14);
    h->GetXaxis()->SetLabelOffset(0.02);
  }
  else if(var=="m12m34"){
    h->GetXaxis()->SetBinLabel(1,"bin 0");
    h->GetXaxis()->SetBinLabel(2,"bin 1");
    h->GetXaxis()->SetBinLabel(3,"bin 2");
    h->GetXaxis()->SetBinLabel(4,"bin 3");
    h->GetXaxis()->SetBinLabel(5,"bin 4");
    h->GetXaxis()->SetLabelSize(0.14);
    h->GetXaxis()->SetLabelOffset(0.02);
  }
  else if(var=="nbjet"){
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"#geq1");
    h->GetXaxis()->SetLabelSize(0.14);
    h->GetXaxis()->SetLabelOffset(0.02);
  }
  else if(var=="mjj"){
    h->GetXaxis()->SetNdivisions(504);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1," ");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1," ");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"3000");
    h->GetXaxis()->SetLabelSize(0.09);
    h->GetXaxis()->SetTickSize(0);
  }
  else if(var=="pt0j"){
    Xmax=4;
    h->GetXaxis()->SetNdivisions(0005);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"15");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var=="pt1j"){
    Xmax=5;
    h->GetXaxis()->SetNdivisions(0006);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"60");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"80");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var=="pt2j"){
    Xmax=2;
    h->GetXaxis()->SetNdivisions(0002);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var=="ljpt"){
    Xmax=5;
    h->GetXaxis()->SetNdivisions(0006);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"40");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"55");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"75");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->SetLabelSize(0.09);
  }
  else if(var=="njetv4"){
    h->GetXaxis()->SetBinLabel( 1 , "0"     );
    h->GetXaxis()->SetBinLabel( 2 , "1"     );
    h->GetXaxis()->SetBinLabel( 3 , "2"     );
    h->GetXaxis()->SetBinLabel( 4 , "#geq1" );
    h->GetXaxis()->SetBinLabel( 5 , "#geq2" );
    h->GetXaxis()->SetBinLabel( 6 , "#geq3" );
    h->GetXaxis()->SetTitle("#font[12]{N}_{jets}");
    h->GetXaxis()->SetLabelSize(0.14);
    h->GetXaxis()->SetLabelOffset(0.02);
    
  }
  else{
    h->GetXaxis()->SetLabelOffset(0.02);
    h->GetXaxis()->SetLabelSize(0.09);
  }
  h->GetXaxis()->SetRangeUser(Xmin,Xmax);
  
}

TLegend* CreateLegend(std::string var, bool isFid){
  
  TLegend *leg = NULL;
  if(var=="pt" || var=="y")
    leg = new TLegend(0.50,0.58,0.92,0.92);
  else if (var=="njetv4" )
    leg = new TLegend(0.50,0.67,0.92,0.92);
  else{
    if(isFid)
      leg = new TLegend(0.50,0.71,0.91,0.93);
    else
      leg = new TLegend(0.50,0.62,0.93,0.94);
  }
  
  leg->ConvertNDCtoPad();
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->SetShadowColor(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  
  return leg;
  
}

TLine *MakeHorLine(TH1F*h, std::string var){

  Double_t Xmin = h->GetXaxis()->GetXmin();
  Double_t Xmax = h->GetXaxis()->GetXmax();
  if(var=="pt")
    Xmax=10;
  TLine *line = new TLine(Xmin,1,Xmax,1);
  line->SetLineStyle(2);
  
  return line;
  
}

TArrow* MakeArrows(double u, double y, std::string MC){
  
  double v = 0, off1 = 0, off2 = 0;
  if(y>1){
    v = 2.5; off1 = -0.2; off2 = 0.2;
  }
  else{
    v = 0.5; off1 = 0.2; off2 = -0.2; //0.5
  }
  TArrow *ar2 = new TArrow(u,v+off1,u,v+off2,0.005,"|>");
  ar2->SetLineWidth(1);
  if(MC=="mg"){
    ar2->SetLineColor(kBlue);
    ar2->SetFillColor(kBlue);
  }
  else if(MC=="nnlops"){
    ar2->SetLineColor(kRed);
    ar2->SetFillColor(kRed);
  }
  else if(MC=="hres"){
    ar2->SetLineColor(kGreen+3);
    ar2->SetFillColor(kGreen+3);
  }
  
  return ar2;

}

void MjjAxis(TH1F *h, TPad *p, float offset){
  
  p->cd();
  h->GetXaxis()->SetTickSize(0);

  for(UShort_t bin = 0; bin < h->GetNbinsX() ; bin++ ){
    
    TGaxis *ax = new TGaxis(h->GetBinLowEdge(bin+1),
			    offset,
			    h->GetBinLowEdge(bin+1)+h->GetBinWidth(bin+1),
			    offset,
			    h->GetBinLowEdge(bin+1),
			    h->GetBinLowEdge(bin+1)+h->GetBinWidth(bin+1),
			    1,
			    "US");
    ax->SetTickSize( 0.05 );
    ax->SetLabelOffset(0.02);
    ax->Draw();
    
  }
  
}

TLine* DefineVertLine(Double_t Xval,Double_t YvalMin, Double_t Yval){

  TLine *vline = new TLine(Xval,YvalMin,Xval,Yval);
  return vline;
  
}
