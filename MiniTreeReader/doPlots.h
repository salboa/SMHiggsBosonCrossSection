#ifndef doPlots_H
#define doPlots_H

/* ROOT includes */
#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TF1.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TKey.h>
#include <TPad.h>
#include <TROOT.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TError.h>
#include <TGaxis.h>
#include <TGraphAsymmErrors.h>

/* C++ includes*/
#include "iomanip"
#include "iostream"
#include "fstream"
#include "vector"
#include "map"
#include "sstream"
#include <sys/stat.h>
#include <utility>

class doPlots {

 public:
  /****************/
  /* Constructors */
  /****************/
  doPlots(std::string channel, std::string filename, double lumi, bool SigOnly,
	  bool useData, bool useZjets, bool useVBS, bool useRedBkg,
	  bool compProdMode, bool doAtlasStyle, bool doLinear, bool doMatrix,
	  bool drawSyst, bool drawM4l, bool draw2Dmm, bool isConf,
	  bool isPaper, bool isLowMass, bool isHighMass);
  
  /****************/
  /*   Methods    */
  /****************/

  /* Manage Input/Output */
  void LoadInputFile();
  void CheckOutDir();

  /* Run Drawing */
  void Run();
  void RunMatrix();
  void RunDistro();
  void Make2DmassPlot();

  /* Draw Signal */
  void drawHistoSignal(TH1F *t);
  
  /* Draw Signal, Background and Data */
  void drawHistoSigBkgData(TH1F *t);

  /* Draw m12m34 plots with 2D pad */
  void drawHisto2Dm12m34(TH1F *t);
  void drawLinesBins();

  /* Set Y axis range */
  double GetYaxisMin(TString name);
  double GetYaxisMax(TString name, TH1F* h);
  double GetYlinScaleCoeff(TString name);
  double GetYlogScaleCoeff(TString name);
  
  /* Get Yaxis name */
  std::string GetYaxisName(TString name, double wd);
  
  /* Draw labels on plots */
  void DrawLabels();

  /* Draw Migration Matrix */
  void MakeMatrix(TH2F* t);

  /* Set Atlas Style */
  void SetAtlasStyle();

  /* Set Fancy Palette */
  void SetPalette(bool m12m34=false);

  /* Set Style and Luminosity */
  void setStyleAndLumi(TH1F *t, bool lcolor=false);
  void setStyle(TH2F *t);

  /* Set Stack Options */
  void setStackOptions(THStack *st, TH1F *t);

  /* Set TPave Text options */
  void setPave(TPaveText *pt);

  /* Define Colors */
  void defineColors();

  /* Calculate Significance */
  double getSignificance(std::vector<double> val,
			 bool Asyntotic);

  /* Evaluate total background */
  double getBkgTot(std::vector<double> val);
  
  /* Get Bin edges names */
  std::vector<std::string> GetBinsName(TH2F* t);

  /* Get Labels */
  std::string GetLabel(TString name);
  std::string GetAxisLabel(TString name);

  /* Detect Histogram Type */
  std::string DetectHisto(TString name);

  /* Detect Mass-Variable Histogram Type */
  std::string DetectMassHisto(TString name);

  /* Detect Differential Variable */
  bool isDiffVar(TString name);

  /* Detect Differential Variable Mass */
  bool isDiffVarMass(TString name);

  /* Detect m4l */
  bool isMass(TString name);
  
  /* Detect Mass-Variable bin */
  int GetHistoBin(TString name);

  /* Covert double to string with precision */
  std::string ConvertToStringWithPrecision(double value, int n);
  
  /* Make TGraph for data */
  TGraphAsymmErrors* RetrieveData(TH1F* data);

  /* Create Tex Table */
  void CreateTableHeader();
  void FillTableBin(int i);
  void FillTableRow(std::vector<TH1F*> list_histo, std::vector<double> SigBkg, int i);

  /* Detect if Drawing Sys Band */
  bool useSystematicBand(TString name);

  /* Make Sys Band */
  TGraphAsymmErrors* CreateVarSysBand(TH1F *h, THStack *stack);
  TGraphAsymmErrors* CreateVarMassSysBand(TH1F *h, THStack *stack);
  TGraphAsymmErrors* CreateMassSysBand(TH1F *h, THStack *stack);

  /* Sys Band for m4l inclusive */
  TH1F* GetNominal(TFile *sysFile);
  TH1F* GetVariation(TFile *sysFile, std::string var);
  
  /* Find Histogram range */
  std::pair<double,double> GetXaxisRanges(TH1F* h); //to be removed

  /* Draw var bin edges */
  void DrawVarBinEdges(TString name);

  /* Transform  m4l fit plot */
  TH1F* GetMassPlot(TFile *f, TString Name);
  
 protected:
  std::string m_channel, m_filename, m_OutDir, m_OutDirPrefix;
  std::string m_prodmode, m_LumiStr;
  double m_lumi;
  bool m_SigOnly, m_useData, m_useZjets, m_useVBS, m_useRedBkg;
  bool m_compProdMode, m_drawSyst, m_drawM4l, m_doAtlasStyle, m_doLinear;
  bool m_doMatrix, m_draw2Dmm, m_conf, m_paper, m_lowMass, m_highMass;
  TFile *m_f;

  Int_t sigCol, ZZCol, ZZEWCol, redBkgCol, ttVCol, dataCol;
  Int_t ggFCol, VBFCol, VHCol, WHCol, ZHCol, ttHCol, bbHCol;

  std::ofstream m_tableFile;

  TCanvas *cs;
  TH1F *h_ZZ, *h_ZZEW, *h_Zjets, *h_Mbos, *h_Red, *h_data, *dummy;
  TH1F *h_ggh, *h_vbf, *h_wh, *h_zh, *h_tth, *h_bbh, *h_Sig;
  TH1F *h_m4lfit; 
  TLegend *leg, *leg1;
  THStack *h_chan, *h_prodmode;
  std::vector<TH1F*> list_histo;
  std::vector<TString> v_chan, v_prodmode;
  TFile *m4lhistos, *SysFile;
  TGraphAsymmErrors *tgdata;
  TGraphAsymmErrors *SysBand;
  TH1F *Nom, *Down, *Up;

  TH2F* tfinal;
  std::vector<std::string> names;
  
  };
#endif
