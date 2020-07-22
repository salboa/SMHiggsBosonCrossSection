#ifndef WorkSpaceMaker_H
#define WorkSpaceMaker_H

/* C++ includes */
#include "iostream"
#include "set"
#include "map"
#include <string>
#include <sstream>
#include <numeric>
#include <unistd.h>
#include <sys/stat.h>
#define GetCurrentDir getcwd

/* ROOT includes */
#include <TH1.h>
#include <TH2.h>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
#include <TF1.h>
#include <TLine.h>
#include <TGraphAsymmErrors.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TColor.h>
#include <TGraph.h>
#include <TMath.h>
#include <TChain.h>
#include <TLatex.h>
#include <TIterator.h>
#include <TLegend.h>

/* ROOSTAT includes */
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooFormulaVar.h"
#include "RooExtendPdf.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooArgList.h"
#include "RooDataHist.h"
#include "RooMinimizer.h"
#include "RooAbsReal.h"
#include "RooArgSet.h"
#include "RooStats/HistFactory/FlexibleInterpVar.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooStats/ModelConfig.h"
#include "RooProdPdf.h"
#include "RooMinimizer.h"
#include "RooAbsReal.h"
#include "RooMinuit.h"
#include "RooMsgService.h"
#include "RooStats/AsymptoticCalculator.h"
#include "RooStarMomentMorph.h"
#include "RooMomentMorph.h"

/* others */
#include "Enum.h"

/* parallel fitting */
#include "TThread.h"

using namespace RooFit;
using namespace std;

class WorkSpaceMaker {

 public:
  
  /****************/
  /* Constructors */
  /****************/
  WorkSpaceMaker(string Variable, string Channel, string FileName,
		 string DataPath, double lumi, bool FidChan, bool FidComb, bool FidTotal,
		 bool Fid4l, bool Fid2l2l, bool FidSum, bool debug,
		 bool verbose, bool addSys,bool addShapeSys, bool do2D,
		 bool dofit, bool WithData, bool parallel, string DataSet,
		 bool sysBands, bool skipscan, bool useMG, string fixsys);
    
  /****************/
  /*   Methods    */
  /****************/

  /* Initialize Input/Output */
  void InitializeIO();
  void DefineInputData();
  void CreateOutDir();

  /* Load Input File */
  void LoadInputFile();

  /* Load Objects */
  void LoadObject();

  /* Load Input Values */
  void LoadCorrFact();
  void LoadAcceptance();
  void LoadProdModeFraction();
  void LoadBranchingRatio();
  void LoadCrossSection();
  void LoadXsScaleFraction();
  void LoadSystematics();
  
  void LoadFidValues(map<int, vector< pair<double,double> > > &data);
  void LoadDiffValues(map<int, vector< pair<double,double> > > &data);
  void LoadValues(vector< pair<double,double> > &data, bool isPRF=false);
  void LoadValues(int p, int b, map<int, map<int, map<int,map<string,vector<double> > > > > &data, int ch);
  void LoadValues(map<string,vector<double> > &data);

  /* Print Loaded values */
  void PrintValues(map<int, vector< pair<double,double> > > data);
  void PrintValues(vector< pair<double,double> > data, bool isBR=false, bool isXsec=false);
  void PrintProcessSystematicValues();
  void PrintCommonSystematicValues();

  /* Get A*CF*R value */
  Double_t PrintACRProduct(int ChNum, int cat);
  
  /* Get Expected Cross Section */
  Double_t PrintExpXS(int ChNum, int cat);

  /* Retrieve Systematic Map */
  map<string,vector<double> > GetSysMap(int chnum, int proc, int bin);
  
  /* Define lists */
  void DefineCategoryMap();
  void CreateProcList();

  /* Set M4l number of bins */ 
  void SetM4lNbins();
  
  /* Cleaning */
  void CleanUp();

  /* Evaluate Input XS */
  double EvalXS(int Pos);
  
  /* Check vector size against hist bins */
  void CheckVectorSize(TH1F *h, int chnum);
  
  string ConvertToStringWithPrecision(double value, int n=2);
  void drawlatex(TLatex *t);
  void DrawSigmaLines (TF1 *sigma);
  void dumpAllInformation(int ChNum, int Pos, int cat);

  /* Run the Class */
  void RunClass();

  /* Run xsec category */
  void doFiducial();
  void doFiducialComb();
  void doFiducialSingleChannel();
  void doFiducialTotal();
  void doFiducial4l();
  void doFiducial2l2l();
  void doFiducialSumChannels();
  void doDifferential();

  /*Get Channel/Process and Variable Name/Identifier */
  inline const char* GetChannel(int n);
  inline const char* GetProcess(int p);
  string GetVariable(int v);
  int GetChannelId(string ch);

  /* Make Systematic Block */
  RooStats::HistFactory::FlexibleInterpVar* makeSysBlock(std::string blockID, int ChNum, int proc, int cat);
  
  /* Make Gaussian Constraint */
  void makeGaussianConstraint(RooRealVar* v_sys);

  /* Remap Histogram */
  TH1F* remapHisto(TH1F* hIn, int cat);
  void setupRemappedHistoAndVariables(std::string process, int chnum, int cat);
  
  /* Define Signal Normalisation Factor */
  RooFormulaVar* SignalNormFactor(int cat, int chnum, RooArgList* list, TH1F* h);
  RooFormulaVar* BackgroundNormFactor(int cat, int chnum, RooArgList* list, TH1F* h, string process);
  RooHistPdf* RetreiveSysShape (string sys, int cat, string direction, RooRealVar *m_x);
  RooProdPdf* RetreiveRooStar (int cat, RooHistPdf* m_x_hpdf, RooRealVar *m_x);
  void  AddComponentRooStar (RooRealVar *tmp_sys, vector<int> *nn, vector<double> *nref, RooArgList *paramRooStar, RooArgList *variationRooStar, int cat  );
  
  /* Making Signal/Background Pdf */
  void DoSignalPdf(string process, int chnum, int cat);
  void DoBackgroundPdf(int chnum, bool qqZZ, bool ggZZ, bool redBkg, int cat);
  void DoSinglePdf(string process, int chnum, bool isSignal, int cat);
  void DoWS();
  void DoQuickTest();
  RooWorkspace *m_ws;
  void PlotPdf (RooSimultaneous *pdf, RooDataSet *Asimov, RooDataSet *combData);
  void PlotPdfFiducial (RooSimultaneous *pdf, RooDataSet *Asimov, RooDataSet *combData);
  void PlotSysBands ();
  void PlotM4l ();
  void SetCanvasSize(int *cw, int *ch);
  
  /*  WS tools  */
  RooSimultaneous* m_simPdf;
  void DoAddPdf();
  RooProdPdf* ApplySys( RooAddPdf* addPdf );
  void DefineCategories();
  void DoSimPdf();
  RooCategory *m_sample;
  void DefineWS();
  RooArgSet paramOfInterest;
  void DefineModelConfig();
  void setAcceptance();
  RooStats::ModelConfig *m_modelConfig;
  RooArgSet *m_paramOfInterest;
  RooArgSet m_globalObservables;
  vector<RooArgSet> m_pdfcategory;
  RooArgSet m_pdfaddlist;
  vector<RooAddPdf> m_v_pdfaddlist;
  RooDataHist* m_obsdata;
  RooHistPdf *down;
  RooHistPdf *up;
  
  void ImportData();
  void MakeMGDataset();

  /* Fit Tools */
  void SetNtupla(RooWorkspace*);
  void ScanNLL(TString wsPath, TString wsName, int nSteps, TString constPOI,
	       double low, double up, TString dataType, TGraph *scan_plot,
	       vector<double>);
  pair<double,double> EvalErrors(vector<double> twonll, vector<double> sigma, double min);
  double EvalOneSigma(double y1, double y2, double x1, double x2);
  pair<double,double> m_LeftRightErrors;
    
  double  m_sigma, m_sigma_unc;
  int m_status, m_status_unc;
  double m_Twonll, m_Twonll_unc;
  vector<double> m_xsminitree;
  vector<double> m_np;
  vector<double> m_poi;
  vector<double> m_poiunc;
  vector<double> m_npunc;
  
  TTree *m_ScanTree;

  /* Set Style */
  void SetAtlasStyle();
  void drawATLASInternal();
  void drawEnergyLumi();
  void drawChannel();
  void defineColors();
  
  /* define axis labels*/
  void defineAxisLabelsMaps();

  /* Close the class */
  void Closing();
  
 protected:
  /* class options */
  string m_FileName;
  string m_DataPath;
  string m_Variable;
  string m_Channel;
  bool m_debug;
  bool m_verbose;
  bool m_addSys;
  bool m_addShapeSys;
  bool m_sysBands;
  bool m_do2D;
  bool m_Fiducial;
  bool m_FidChan;
  bool m_FidComb;
  bool m_FidTotal;
  bool m_Fid4l;
  bool m_Fid2l2l;
  bool m_FidSum;
  double m_lumi;
  bool m_dofit;
  bool m_WithData;
  double m_parallel;
  bool m_skipScan;
  bool m_useMG;
  string m_DataSet;
  string m_fixSys;
  
  /*****************/
  /* class members */
  /*****************/
  
 private:
  string m_OutDir;
  string m_Dir;
  TH1F* m_hremapped; //!
  TFile *m_InFile;   //!
  map<int, vector<pair<double,double> > > m_cf, m_acc, m_r;
  map<int, map<int, map<int,map<string,vector<double> > > > > m_procSys;
  map<string,vector<double> > m_comSys;
  map<int,string> m_Category;
  vector< pair<double,double> > m_br, m_xsec, m_xsScale;
  map<string,int> m_process;
  map<string, vector<string> > m_shapeLabels, m_sigUnfLabels;
  ifstream m_InStream;
  string m_cfFile, m_accFile, m_rFile, m_brFile, m_xsecFile;
  string m_xsScaleFile, m_sysFile, m_cmSysFile;
  int m_ChNum;
  int m_Mbins;

  /* process colors */
  Int_t sigCol, ZZCol, ZZEWCol, redBkgCol, ttVCol, dataCol;
  Int_t ggFCol, VBFCol, VHCol, WHCol, ZHCol, ttHCol;

  /* histograms objects */
  TH1F *m_h;  //!
  TH1F *m_h_remapped;  //!
  TH1F *m_tmp;  // probably not needed
  vector<double> m_binnames;

  TH1F *m_Htmp; //!

  /* RooFit objects */
  RooRealVar *m_Lumi ;
  RooFormulaVar *m_Norm, *m_norm_pdf;
  RooRealVar *m_x, *m_m4l, *m_mean;
  RooRealVar *sigma_p;
  RooProdPdf *m_x_m4l;
  RooAddPdf *m_spectrum;
  RooHistPdf *m_x_hpdf, *m_m4l_hpdf;
  RooExtendPdf *m_hpdf_ext;
  RooDataHist *m_x_hdata;
  RooArgSet m_listpdf, m_listSubpdf;
  RooArgSet m_list;
  RooArgSet m_observables;
  RooGaussian* m_gaus_tmp;
  RooArgSet m_listNP;
  RooArgSet m_listNPshapes;
  RooStats::HistFactory::FlexibleInterpVar *m_sysblock;
  RooArgList m_listpdf_np;
  RooArgList m_listpdf_np2;
  RooArgList m_listpdf_npshapes;
  std::vector<double> m_binwidth;
  std::vector<double> m_binlowerlimit;
  std::vector<RooRealVar*> m_binwidthroorealvar;
  RooStarMomentMorph *m_signalmorphiong;
  /* parallel fitting */
    
  //! Number of threads
  unsigned int m_NThreads;
  //! Storing the threads:
  vector<TThread*> m_Threads;
  //! Storing a flag that the thread is running
  vector<bool> m_ThreadIsInitialized;
  //! Storing a flag that the thread is finished
  vector<bool> m_ThreadIsFinished;
  void SetThreads(unsigned int NThreads) { m_NThreads = NThreads; }
  //! ID of the next item to be processed
  unsigned int m_ThreadNextItem;
  static void CallParallelCalibrationThread( void* Address );
  void Parallel();
  void FixSysForFit(string);
  string GetCurrentWorkingDir(void);

};
#endif
