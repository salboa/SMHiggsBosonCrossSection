#include "doPlots.h"

void doPlots :: setStyleAndLumi(TH1F *t, bool lcolor){
  
  Int_t color = 1;
  TString name = (TString) t->GetName();
  gStyle->SetOptStat(0);
  if(name.Contains("AllSig")){
    if(m_SigOnly) color = 1; else color = sigCol;
  }
  else if(name.Contains("ggH"))        color = ggFCol;
  else if(name.Contains("VBF"))        color = VBFCol;
  else if(name.Contains("WH"))         color = WHCol;
  else if(name.Contains("ZH"))         color = ZHCol;
  else if(name.Contains("ttH"))        color = ttHCol;
  else if(name.Contains("bbH"))        color = bbHCol;
  else if(name.Contains("ZZEW"))       color = ZZEWCol;
  else if(name.Contains("Zjets"))      color = redBkgCol;
  else if(name.Contains("redBkg"))     color = redBkgCol;
  else if(name.Contains("MultiBoson")) color = ttVCol;
  else if(name.Contains("data"))       color = dataCol;
  else color = ZZCol;
  if(m_SigOnly){
    if (!name.Contains("AllSig")) t->SetFillColor(color);
    if (!name.Contains("AllSig")) t->SetFillStyle(1001);
  }
  else{
    if (!name.Contains("data")){
      t->SetFillColor(color); t->SetFillStyle(1001);
    }
  }
  if(lcolor) t->SetLineColor(color);
  else       t->SetLineColor(kBlack);
  t->SetMarkerColor(color);
  t->SetLineWidth(1);
  t->SetMarkerStyle(20);
  if (!name.Contains("data")) { t->SetMarkerSize(0.01); }
  else{                         t->SetMarkerSize(0.8); }
  if(!name.Contains("data")) t->Scale(m_lumi);
  t->GetXaxis()->SetTitleOffset(1.30);
  t->GetXaxis()->SetTitleSize(0.05);
  t->GetYaxis()->SetTitleOffset(1.4);
  t->GetYaxis()->SetTitleSize(0.05);
  if(name.Contains("njet") || name.Contains("nbjet"))
    t->GetXaxis()->SetLabelSize(0.055);
  if(name.Contains("m12m34"))
    t->GetXaxis()->SetLabelSize(0.06);
  
}

void doPlots :: setStyle(TH2F* t){

  gStyle->SetOptStat(0);
  t->GetXaxis()->SetTitleOffset(1.30);
  t->GetYaxis()->SetTitleOffset(1.90);
  t->GetYaxis()->SetTitleSize(0.03);
  t->GetXaxis()->SetTitleSize(0.03);
  t->GetYaxis()->SetLabelSize(0.03);
  t->GetXaxis()->SetLabelSize(0.03);
  t->GetZaxis()->SetRangeUser(0.001,1);
  
}

void doPlots :: setStackOptions(THStack *st, TH1F *t){
  
  st->GetXaxis()->SetTitle( t->GetXaxis()->GetTitle() );
  st->GetYaxis()->SetTitle( t->GetYaxis()->GetTitle() );
  st->GetXaxis()->SetTitleOffset(1.30);
  st->GetYaxis()->SetTitleOffset(1.65);
  
}

void doPlots :: setPave(TPaveText *pt){
  
  pt->SetTextSize(0.026);
  pt->SetShadowColor(0);
  pt->SetLineColor(0);
  pt->SetFillColor(0);
  pt->ConvertNDCtoPad();
  
}

void doPlots :: defineColors(){

  sigCol    = TColor::GetColor("#67B2FF");
  ZZCol     = TColor::GetColor("#E20D0A");
  ZZEWCol   = TColor::GetColor("#B5236F");
  redBkgCol = TColor::GetColor("#793FD2");
  ttVCol    = TColor::GetColor("#EDE810");
  ggFCol    = TColor::GetColor("#67B2FF");
  VBFCol    = TColor::GetColor("#99E148");
  VHCol     = TColor::GetColor("#EB9B35");
  WHCol     = TColor::GetColor("#EB9B35");
  ZHCol     = kOrange;
  //ttHCol    = TColor::GetColor("#212ADE");
  ttHCol    = TColor::GetColor("#BF408A");
  //bbHCol    = kMagenta-5;
  bbHCol    = TColor::GetColor("#8028AD");
  dataCol   = kBlack;

}

void doPlots :: SetAtlasStyle(){

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

void doPlots :: SetPalette(bool m12m34){

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
  else{
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
