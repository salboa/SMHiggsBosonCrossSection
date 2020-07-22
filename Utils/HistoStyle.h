#include <TColor.h>
#include <THStack.h>
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TF1.h>
#include <TLatex.h>
#include "Tools.h"

/* Defining processes colors */
Int_t m_sigCol    = TColor::GetColor("#67B2FF");
Int_t m_ZZCol     = TColor::GetColor("#E20D0A");
Int_t m_ZZEWCol   = TColor::GetColor("#B5236F");
Int_t m_redBkgCol = TColor::GetColor("#793FD2");
Int_t m_ttVCol    = TColor::GetColor("#EDE810");
Int_t m_ggFCol    = TColor::GetColor("#67B2FF");
Int_t m_VBFCol    = TColor::GetColor("#99E148");
Int_t m_VHCol     = TColor::GetColor("#EB9B35");
Int_t m_WHCol     = TColor::GetColor("#EB9B35");
Int_t m_ZHCol     = kOrange;
Int_t m_ttHCol    = kBlue;
Int_t m_bbHCol    = kViolet;
Int_t m_dataCol   = kBlack;

/* Defining processes markers */
Int_t m_sigMrk = 20;
Int_t m_ggFMrk = 20;
Int_t m_VBFMrk = 21;
Int_t m_VHMrk  = 33;
Int_t m_WHMrk  = 22;
Int_t m_ZHMrk  = 23;
Int_t m_ttHMrk = 41;
Int_t m_bbHMrk = 47;
  
void SetAtlasStyle(bool useStat=false){
  
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
  atlasStyle->SetPadBottomMargin(0.16);
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
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  /*get rid of X error bars*/
  //atlasStyle->SetErrorX(0.001);
  /*get rid of error bar caps*/
  atlasStyle->SetEndErrorSize(0.);

  /*do not display any of the standard histogram decorations*/
  atlasStyle->SetOptTitle(0);
  if(useStat){
    atlasStyle->SetOptStat(1111);
    atlasStyle->SetOptFit(1111);
  }
  else{
    atlasStyle->SetOptStat(0);
    atlasStyle->SetOptFit(0);
  }

  /*put tick marks on top and RHS of plots*/
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();

}

void DrawAtlasLabel(bool hasRatio=false, bool isConf=false, bool isPaper=false,
		    Double_t Xpos=0.31, Double_t Ypos=0.87, Double_t Tsize=0.04){
  
  Double_t TextSize = Tsize;
  Double_t Pos      = Xpos;
  Double_t AtPos    = Xpos-0.13;
  if(hasRatio){
    TextSize = 0.05;
    Pos      = 0.29;
    AtPos    = Pos-0.11;
  }
  
  TLatex *AT = new TLatex();
  AT->SetNDC();
  AT->SetTextFont(72);
  AT->SetTextSize(TextSize);
  AT->SetTextColor(kBlack);

  TLatex *Lab = new TLatex();
  Lab->SetNDC();
  Lab->SetTextFont(42);
  Lab->SetTextSize(TextSize);
  Lab->SetTextColor(kBlack);

  AT->DrawLatex(AtPos,Ypos,"ATLAS");
  if(isConf)
    Lab->DrawLatex(Pos,Ypos,"Preliminary");
  else if(isPaper)
    Lab->DrawLatex(Pos,Ypos,"");
  else
    Lab->DrawLatex(Pos,Ypos,"Internal");

  AT->Delete();
  Lab->Delete();
  
}

void DrawEnergyLumi(double intlum=36.2, bool addLumi=false, bool hasRatio=false,
		    Double_t Xpos=0.18, Double_t Ypos=0.80, Double_t Tsize=0.04){

  Double_t TextSize = Tsize;
  TLatex *lumi = new TLatex();
  lumi->SetNDC();
  lumi->SetTextFont(42);
  lumi->SetTextSize(TextSize);
  lumi->SetTextColor(kBlack);

  std::string Lumi = ConvertToStringWithPrecision(intlum,3);
  std::string text = "#sqrt{s} = 13 TeV";
  if(addLumi) text += ", "+Lumi+" fb^{-1}";
  lumi->DrawLatex(Xpos,Ypos, text.c_str() );

  lumi->Delete();
  
}

void DrawChannel(int chan, bool hasRatio=false,
		 Double_t Xpos=0.18, Double_t Ypos=0.73, Double_t Tsize=0.04){

  Double_t TextSize = Tsize;
  Double_t Pos      = Ypos;
  if(hasRatio){
    TextSize = 0.05;
    Pos      = 0.70;
  }

  TLatex *Chan = new TLatex();
  Chan->SetNDC();
  Chan->SetTextFont(42);
  Chan->SetTextSize(TextSize);
  Chan->SetTextColor(kBlack);
  
  std::string chStr = "";
  if(chan==Channel::_incl)      chStr = "4l";
  else if(chan==Channel::_2l2l) chStr = "2#mu2e / 2e2#mu";
  else if(chan==Channel::_2l2l) chStr = "4#m / 4eu";
  else                          chStr = GetChannelName(chan);
  Chan->DrawLatex(Xpos,Pos, ("H #rightarrow ZZ* #rightarrow "+chStr).c_str() );

  Chan->Delete();
  
}

void DrawProductionMode(std::string process, bool hasRatio=false){

  Double_t TextSize = 0.04;
  Double_t Pos = 0.67;
  if(hasRatio){
    TextSize = 0.05;
    Pos = 0.64;
  }

  TLatex Prod;
  Prod.SetNDC();
  Prod.SetTextFont(42);
  Prod.SetTextSize(TextSize);
  Prod.SetTextColor(kBlack);
  
  Prod.DrawLatex(0.18,Pos, process.c_str() );
  
}

void SetHistoStyle(TH1F* h, int line, int color, double Xmin, double Xmax){

  Double_t yMin = 0, yMax = 1;
  h->SetLineWidth(2);
  h->SetLineStyle(line);
  h->SetLineColor(color);
  h->GetYaxis()->SetTitleOffset(1.50);
  h->GetYaxis()->SetTitle("Events");
  //h->GetYaxis()->CenterTitle(kTRUE);
  h->GetYaxis()->SetRangeUser(yMin,yMax);
  //h->GetXaxis()->SetMoreLogLabels(kTRUE);
  //h->GetXaxis()->SetNoExponent(kTRUE);
  h->GetXaxis()->SetRangeUser(Xmin,Xmax);
  
}

void SetRatioPlots(TH1F *ratio, int line, int color, double Xmin, double Xmax){

  ratio->GetYaxis()->SetTitle("Ratio");
  ratio->GetXaxis()->SetTitleOffset(1.20);
  //ratio->GetYaxis()->CenterTitle(kTRUE);
  ratio->GetYaxis()->SetNdivisions(507);
  //ratio->GetXaxis()->SetMoreLogLabels(kTRUE);
  //ratio->GetXaxis()->SetNoExponent(kTRUE);
  ratio->SetLineStyle(line);
  ratio->SetLineColor(color);
  //ratio->GetXaxis()->SetLabelSize(0.08);
  //ratio->GetYaxis()->SetLabelSize(0.07);
  //ratio->GetXaxis()->SetTitleSize(0.10);
  //ratio->GetYaxis()->SetTitleSize(0.08);
  //ratio->GetYaxis()->SetTitleOffset(0.55);
  ratio->GetYaxis()->SetRangeUser(0.5,1.5);
  ratio->GetXaxis()->SetRangeUser(Xmin,Xmax);
  
}

TCanvas *CreateCanvas(std::string name, double hSize=600,
		      double vSize=600, bool isMatrix=false){

  if(isMatrix){ hSize = 1000; vSize = 1000; }
  TCanvas *cs = new TCanvas( ("cs_"+name).c_str(), ("cs_"+name).c_str(),
			     0, 0, hSize, vSize );
  if(isMatrix){
    cs->SetGridx(kTRUE);
    cs->SetGridy(kTRUE);
    cs->SetRightMargin(0.11);
    cs->SetLeftMargin(0.15);
    cs->SetTopMargin(0.10);
    cs->SetBottomMargin(0.14);
  }
  return cs;
  
}

TPad *CreateTopPad(std::string name, Double_t leftMarg=0.14){

  TPad *p1 = new TPad( ("p1_"+name).c_str(),
		       ("p1_"+name).c_str(),
		       0.01,0.35,0.99,0.99 );

  p1->SetBottomMargin(0.02);
  p1->SetLeftMargin(leftMarg);
  return p1;
  
}

TPad *CreateBottomPad(std::string name, Double_t leftMarg=0.14){

  TPad *p2 = new TPad( ("p2_"+name).c_str(),
		       ("p2_"+name).c_str(),
		       0.01,0.01,0.99,0.35 );

  p2->SetTopMargin(0.01);
  p2->SetLeftMargin(leftMarg);
  p2->SetBottomMargin(0.30);
  return p2;
  
}

TLegend *CreateLegend(Double_t v1=0.56, Double_t v2=0.59,
		      Double_t v3=0.91, Double_t v4=0.90){
  
  TLegend *leg = new TLegend(v1,v2,v3,v4);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  return leg;

}

void AdjustRemappedXaxis(TH1D* h, int varId, bool hasRatio=false, bool isRatio=false){

  Double_t Xmin = h->GetXaxis()->GetXmin();
  Double_t Xmax = h->GetXaxis()->GetXmax();
  Double_t lbSize = 0.04, lbOffset = 0.009;

  h->GetXaxis()->SetRangeUser(Xmin,Xmax);
  h->GetXaxis()->SetTitle(GetVariableXaxisLabel(varId).c_str());
  
  if(varId==Variable::pt4l){
    lbSize = 0.04;
    if(hasRatio) lbSize = 0.00;
    if(isRatio)  {lbSize = 0.10; lbOffset = 0.03; }
    h->GetXaxis()->SetNdivisions(0015);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"10");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"20");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"45");
    h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"60");
    h->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"80");
    h->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(9,-1,-1,-1,-1,-1,"200");
    h->GetXaxis()->ChangeLabel(10,-1,-1,-1,-1,-1,"350");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");
  }
  else if(varId==Variable::njet){
    lbSize = 0.06; lbOffset = 0.009;
    if(hasRatio){ lbSize = 0.14; lbOffset = 0.03; }
    if(isRatio){  lbSize = 0.15; lbOffset = 0.03; }
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"1");
    h->GetXaxis()->SetBinLabel(3,"2");
    h->GetXaxis()->SetBinLabel(4,"#geq3");
  }
  else if(varId==Variable::njetv2){
    lbSize = 0.06; lbOffset = 0.009;
    if(hasRatio){ lbSize = 0.14; lbOffset = 0.02; }
    if(isRatio){  lbSize = 0.15; lbOffset = 0.03; }
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"#geq1");
  }
  else if(varId==Variable::njetv3){
    lbSize = 0.06; lbOffset = 0.009;
    if(hasRatio){ lbSize = 0.14; lbOffset = 0.02; }
    if(isRatio){  lbSize = 0.15; lbOffset = 0.03; }
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"1");
    h->GetXaxis()->SetBinLabel(3,"#geq2");
  }
  else if(varId==Variable::njetv4){
    lbSize = 0.06; lbOffset = 0.009;
    if(hasRatio){ lbSize = 0.14; lbOffset = 0.02; }
    if(isRatio){  lbSize = 0.15; lbOffset = 0.03; }
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"1");
    h->GetXaxis()->SetBinLabel(3,"2");
    h->GetXaxis()->SetBinLabel(4,"3");
    h->GetXaxis()->SetBinLabel(5,"#geq4");
  }
  else if(varId==Variable::nbjet){
    lbSize = 0.06; lbOffset = 0.009;
    if(hasRatio){ lbSize = 0.14; lbOffset = 0.02; }
    if(isRatio){  lbSize = 0.15; lbOffset = 0.03; }
    h->GetXaxis()->SetBinLabel(1,"0");
    h->GetXaxis()->SetBinLabel(2,"#geq1");
  }
  else if(varId==Variable::m12m34){
    lbSize = 0.06; lbOffset = 0.009;
    if(hasRatio){ lbSize = 0.14; lbOffset = 0.02; }
    if(isRatio){  lbSize = 0.15; lbOffset = 0.03; }
    h->GetXaxis()->SetBinLabel(1,"bin 0");
    h->GetXaxis()->SetBinLabel(2,"bin 1");
    h->GetXaxis()->SetBinLabel(3,"bin 2");
    h->GetXaxis()->SetBinLabel(4,"bin 3");
    h->GetXaxis()->SetBinLabel(5,"bin 4");
  }
  else if(varId==Variable::mjj){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(004);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"                 #font[12]{N}_{jets}<2");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"450");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"3000");
  }
  else if(varId==Variable::etajj){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(004);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"                 #font[12]{N}_{jets}<2");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"1.0");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"2.5");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"9.0");
  }
  else if(varId==Variable::phijj){
    lbSize = 0.04;  lbOffset = 0.017;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(005);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"              #font[12]{N}_{jets}<2");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"#frac{1}{2} #pi");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"#pi");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"#frac{3}{2} #pi");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"2 #pi");
  }
  else if(varId==Variable::pt0j){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0005);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"15");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"120");
    //h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
  }
  else if(varId==Variable::pt1j){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0006);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"60");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"80");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"120");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
    //h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"350");
    //h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");
  }
  else if(varId==Variable::pt2j){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0002);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"120");
    //h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"350");
    //h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
  }
  else if(varId==Variable::pt3j){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0002);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"120");
    //h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"350");
    //h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
  }
  else if(varId==Variable::pt0y || varId==Variable::pt1y ||
	  varId==Variable::pt1y || varId==Variable::pt3y  ){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0002);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"45");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"120");
    //h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"350");
    //h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
  }
  else if(varId==Variable::ljpt){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0006);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"            #font[12]{N}_{jets}=0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"60");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"120");
    //h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"350");
    //h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
  }
  else if(varId==Variable::sjpt){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0006);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"            #font[12]{N}_{jets}<2");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"30");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"60");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"120");
    //h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"350");
    //h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1000");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"350");
  }
  else if(varId==Variable::cts){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0011);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"0.125");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"0.25");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"0.375");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"0.5");
    h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"0.625");
    h->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"0.75");
    h->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"0.875");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1");
  }
  else if(varId==Variable::ct1 || varId==Variable::ct2){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0011);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"-1");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"-0.75");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"-0.5");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"-0.25");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"0.25");
    h->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"0.5");
    h->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"0.75");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1");
  }
  else if(varId==Variable::phi || varId==Variable::phi1){
    lbSize = 0.04;  lbOffset = 0.017;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0011);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"-#pi");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"- #frac{3}{4} #pi");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"- #frac{1}{2} #pi");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"- #frac{1}{4} #pi");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"#frac{1}{4} #pi");
    h->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"#frac{1}{2} #pi");
    h->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"#frac{3}{4} #pi");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"#pi");
  }
  else if(varId==Variable::y4l){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0015);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"0.15");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"0.3");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"0.45");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"0.6");
    h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"0.75");
    h->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"0.9");
    h->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"1.2");
    h->GetXaxis()->ChangeLabel(9,-1,-1,-1,-1,-1,"1.6");
    h->GetXaxis()->ChangeLabel(10,-1,-1,-1,-1,-1,"2.0");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"2.5");
  }
  else if(varId==Variable::m12){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0007);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"50");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"64");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"73");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"85");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"106");
  }
  else if(varId==Variable::m34){
    lbSize = 0.04;
    if(hasRatio){ lbSize = 0.09; }
    h->GetXaxis()->SetNdivisions(0015);
    h->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"12");
    h->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"20");
    h->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"24");
    h->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"28");
    h->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"32");
    h->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"40");
    h->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"55");
    h->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"65");
    h->GetXaxis()->SetLabelSize(lbSize);
  }
  else if(varId==Variable::m4l){
    lbSize = 0.06; lbOffset = 0.009;
    if(hasRatio){ lbSize = 0.14; lbOffset = 0.03; }
    if(isRatio){  lbSize = 0.15; lbOffset = 0.03; }
    h->GetXaxis()->SetBinLabel(1,"4#mu");
    h->GetXaxis()->SetBinLabel(2,"4e");
    h->GetXaxis()->SetBinLabel(3,"2#mu2e");
    h->GetXaxis()->SetBinLabel(4,"2e2#mu");
  }
  else if(varId==Variable::ptnjet || varId==Variable::pty4l){
    lbSize = 0.04; lbOffset = 0.009;
    if(hasRatio){ lbSize = 0.14; lbOffset = 0.03; }
    if(isRatio){  lbSize = 0.15; lbOffset = 0.03; }
    for(int i=0; i<h->GetNbinsX(); i++){
      h->GetXaxis()->SetBinLabel(i+1, ("bin"+std::to_string(i)).c_str() );
    }
  }
  //else if(varId==Variable::njetFull){
  //  h->GetXaxis()->SetBinLabel( 1 , "0"     );
  //  h->GetXaxis()->SetBinLabel( 2 , "1"     );
  //  h->GetXaxis()->SetBinLabel( 3 , "2"     );
  //  h->GetXaxis()->SetBinLabel( 4 , "3"     );
  //  h->GetXaxis()->SetBinLabel( 4 , "#geq1" );
  //  h->GetXaxis()->SetBinLabel( 5 , "#geq2" );
  //  h->GetXaxis()->SetBinLabel( 6 , "#geq3" );
  //  h->GetXaxis()->SetBinLabel( 7 , "#geq4" );
  //}

  h->GetXaxis()->SetLabelSize(lbSize);
  h->GetXaxis()->SetLabelOffset(lbOffset);
  
  if(hasRatio){
    h->GetYaxis()->SetLabelSize(0.05);
    h->GetYaxis()->SetTitleSize(0.06);
    h->GetYaxis()->SetTitleOffset(1.15);
  }

  if(isRatio){
    h->GetXaxis()->SetTitleSize(0.11);
    h->GetXaxis()->SetTitleOffset(1.35);
    h->GetYaxis()->SetLabelSize(0.09);
    h->GetYaxis()->SetTitleOffset(0.60);
    h->GetYaxis()->SetTitleSize(0.11);
  }
  
}

void AdjustMatrixAxes(TH2D* h, int varId){

  std::string prefix   = "";
  std::string suffix   = "";
  std::string binLabel = "";
  h->GetXaxis()->SetTitleOffset(1.90);
  h->GetYaxis()->SetTitleOffset(2.40);
  h->GetZaxis()->SetLabelSize(0.030);
  h->SetMarkerSize(1.0);
  
  if(varId==Variable::m12m34){
    for(int i=0; i<GetNumberOfBins(varId); i++){
      h->GetXaxis()->SetBinLabel(i+1,("bin"+std::to_string(i)).c_str());
      h->GetYaxis()->SetBinLabel(i+1,("bin"+std::to_string(i)).c_str());
    }
    h->GetXaxis()->SetTitle( (GetVariableXaxisLabel(varId)+" (reco)").c_str()  );
    h->GetYaxis()->SetTitle( (GetVariableXaxisLabel(varId)+" (truth)").c_str() );
    return;
  }

  std::vector<double> ranges = GetVariableRanges(varId);
  int Start   = 0;
  int sndPre  = 3;
  int shift   = 0;
  double diff = 0;
  int s1 = 0, s2 = 0, s3 = 0;
  if(varId==Variable::ljpt){
    h->GetXaxis()->SetBinLabel(1,"N_{jets}=0");
    h->GetYaxis()->SetBinLabel(1,"N_{jets}=0");
    Start = 1;
  }
  else if(varId==Variable::sjpt){
    h->GetXaxis()->SetBinLabel(1,"N_{jets}<2");
    h->GetYaxis()->SetBinLabel(1,"N_{jets}<2");
    Start = 1;
  }
  else if(varId==Variable::mjj  || varId==Variable::etajj || varId==Variable::phijj){
    h->GetXaxis()->SetBinLabel(1,"N_{jets}<2");
    h->GetYaxis()->SetBinLabel(1,"N_{jets}<2");
  }
  else if(varId==Variable::ptnjet){
    s1 = GetNumberOfBins(Variable::pt0j);
    s2 = GetNumberOfBins(Variable::pt1j);
    s3 = GetNumberOfBins(Variable::pt2j);
    sndPre = 4;
    h->GetXaxis()->SetLabelSize(0.025);
    h->GetYaxis()->SetLabelSize(0.025);
    h->GetXaxis()->SetTitleOffset(2.45);
  }
  else if(varId==Variable::pty4l){
    s1 = GetNumberOfBins(Variable::pt0y);
    s2 = GetNumberOfBins(Variable::pt1y);
    s3 = GetNumberOfBins(Variable::pt2y);
    sndPre = 4;
    h->GetXaxis()->SetLabelSize(0.025);
    h->GetYaxis()->SetLabelSize(0.025);
    h->GetXaxis()->SetTitleOffset(2.45);
  }
  
  for(int i=Start; i<(int)ranges.size()-1; i++){
    if(varId==Variable::njet   || varId==Variable::njetv2 ||
       varId==Variable::njetv3 || varId==Variable::njetv4 ||
       varId==Variable::nbjet ){
      prefix = "N_{";
      if(varId==Variable::nbjet) prefix += "b-";
      prefix += "jets}";
      if(i==(int)ranges.size()-2) prefix += ">=";
      else                        prefix += "=";
      binLabel = prefix+ConvertToStringWithPrecision(ranges.at(i),2)+suffix;
    }
    else if(varId==Variable::ptnjet){
      prefix = "#splitline{N_{jets}";
      if(i<s1)            { prefix += "=0}{pT: ";                 }
      else if(i<s1+s2)    { prefix += "=1}{pT: ";  diff =  350.0; }
      else if(i<s1+s2+s3) { prefix += "=2}{pT: ";  diff =  700.0; }
      else                { prefix += ">=3}{pT: "; diff = 1050.0; }
      binLabel = prefix+(ConvertToStringWithPrecision(ranges.at(i)-diff,3)+"-"+
			 ConvertToStringWithPrecision(ranges.at(i+1)-diff,sndPre))+"}";
    }
    else if(varId==Variable::pty4l){
      prefix = "#splitline{";
      if(i<s1)            { prefix += "|y|: 0-0.5}{pT: ";                  }
      else if(i<s1+s2)    { prefix += "|y|: 0.5-1.0}{pT: "; diff =  350.0; }
      else if(i<s1+s2+s3) { prefix += "|y|: 1.0-1.5}{pT: "; diff =  700.0; }
      else                { prefix += "|y|: 1.5-2.5}{pT: "; diff = 1050.0; }
      binLabel = prefix+(ConvertToStringWithPrecision(ranges.at(i)-diff,3)+"-"+
			 ConvertToStringWithPrecision(ranges.at(i+1)-diff,sndPre))+"}";
    }
    else{
      if(varId==Variable::mjj || varId==Variable::etajj || varId==Variable::phijj) shift=1;
      if(varId==Variable::mjj || varId==Variable::ljpt  || varId==Variable::sjpt ||
	 varId==Variable::pt4l) sndPre = 4; 
      prefix = "", suffix = "";
      if(ranges.at(i)<0 && ranges.at(i+1)<0){
	prefix = "-("; suffix = ")"; 
	binLabel = prefix+(ConvertToStringWithPrecision(fabs(ranges.at(i)),3)+"-"+
			   ConvertToStringWithPrecision(fabs(ranges.at(i+1)),sndPre))+suffix;
      }
      else{
	binLabel = prefix+(ConvertToStringWithPrecision(ranges.at(i),3)+"-"+
			   ConvertToStringWithPrecision(ranges.at(i+1),sndPre))+suffix;
      }
    }
    h->GetXaxis()->SetBinLabel( i+1+shift, binLabel.c_str() );
    h->GetYaxis()->SetBinLabel( i+1+shift, binLabel.c_str() );
    if(varId==Variable::ptnjet || varId==Variable::pty4l) h->GetXaxis()->LabelsOption("v");
  }
  h->GetXaxis()->SetTitle( (GetVariableXaxisLabel(varId)+" (reco)").c_str()  );
  h->GetYaxis()->SetTitle( (GetVariableXaxisLabel(varId)+" (truth)").c_str() );
  ranges.clear();
  
}

TH1D *MakeRatio(TH1D* h1, TH1D* h2, std::string name){

  TH1D* m_ratio = (TH1D*)h1->Clone( ("ratio"+name).c_str() );
  m_ratio->Reset();
  m_ratio->Divide(h2,h1);
  return m_ratio;
  
}

TLine *MakeHorLine(Double_t Xmin, Double_t Xmax, Double_t Yval=1){

  TLine *m_line = new TLine(Xmin,Yval,Xmax,Yval);
  m_line->SetLineStyle(2);
  
  return m_line;
  
}

void SetPalette(bool m12m34, bool use1MColors){

  if(m12m34){
    const int Number = 4;
    const Int_t NCont = 255;
    Double_t Green[Number]  = {0.95, 0.90, 0.79, 0.60};
    Double_t Blue[Number]   = {0.95, 0.90, 0.79, 0.50};
    Double_t Red[Number]    = {0.98, 0.93, 0.96, 0.99};
    //Double_t Red[Number]    = {0.99, 0.99, 0.99, 0.99};
    Double_t Length[Number] = {0.00, 0.30, 0.60, 1.00};

    Int_t nb = 100;
    TColor::CreateGradientColorTable(Number, Length, Red, Green, Blue, nb);
    gStyle->SetNumberContours(NCont);
  }
  else if(use1MColors){
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;
    
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
  }
  
}

void SetStackOptions(THStack *st, TH1D *h){

  st->GetXaxis()->SetTitle( h->GetXaxis()->GetTitle() );
  st->GetYaxis()->SetTitle( h->GetYaxis()->GetTitle() );
  st->GetXaxis()->SetTitleOffset(1.30);
  st->GetYaxis()->SetTitleOffset(1.65);
  
}

void SetMatrixPlotStyle(TH2D* h, bool isScaled=false){

  h->GetXaxis()->SetTitleOffset(1.30);
  h->GetYaxis()->SetTitleOffset(1.90);
  h->GetYaxis()->SetTitleSize(0.03);
  h->GetXaxis()->SetTitleSize(0.03);
  h->GetYaxis()->SetLabelSize(0.03);
  h->GetXaxis()->SetLabelSize(0.03);
  if(isScaled)
    h->GetZaxis()->SetRangeUser(0.1,100);
  else
    h->GetZaxis()->SetRangeUser(0,1);
}

void ScaleMatrixValues(TH2D* h){

  for (int r=0; r<h->GetNbinsX(); r++){
    for (int t=0; t<h->GetNbinsX(); t++){
      h->SetBinContent(r+1,t+1, h->GetBinContent(r+1,t+1)*100);
    }
  }
  
}

TF1* DefineFunction(std::string objName, std::string funString,
		    Double_t Vmin, Double_t Vmax, Int_t color=kRed){

  TF1 *tf = new TF1(objName.c_str(), funString.c_str(), Vmin, Vmax);
  tf->SetLineStyle(2);
  tf->SetLineWidth(1);
  tf->SetLineColor(color);
  return tf;
  
}

TLatex* CreateText(Double_t xPos, Double_t yPos, std::string text,
		   Int_t color=kRed+2, Int_t font=43, Int_t tSize=22){

  TLatex *t = new TLatex(xPos, yPos, text.c_str() );
  t->SetTextColor(color);
  t->SetTextFont(font);
  t->SetTextSize(tSize);
  return t;
  
}
