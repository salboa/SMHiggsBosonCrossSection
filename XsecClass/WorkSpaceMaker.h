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
#include <iomanip>
#include <limits>
#include <cassert>

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
#include "RooUniform.h"
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
#include "../Utils/PrintHelpers.h"
#include "../Utils/VarHandler.h"
#include "../Utils/Enum.h"
#include "../Utils/SysMapHandler.h"
#include "../Utils/HistoStyle.h"

/* parallel fitting */
#include "TThread.h"

using namespace RooFit;
using namespace std;

class WorkSpaceMaker {

 public:
  
  /****************/
  /* Constructors */
  /****************/
  WorkSpaceMaker(string Variable,    string Channel,    string FileName,
		 string SysFilename, string AcFileName, string AcSysFilename,
		 string PathToFile,  string DataPath,   double lumi,
		 bool FidChan,       bool FidComb,      bool FidTotal,
		 bool Fid4l,         bool Fid2l2l,      bool FidSum,
		 bool BRDiff,        bool debug,        bool verbose,
		 bool addSys,        bool addShapeSys,  bool do2D,
		 bool dofit,         bool WithData,     bool useBornLep,
		 bool parallel,      string DataSet,    bool sysBands,
		 bool skipscan,      bool useMCData,    string fixsys,
		 bool matrix,        bool cfsplit,      string ProdMode,
		 string ProdHist,    string BkgHist,    string InputMtx,
		 int chSplit,        int mcVersion,     bool reduceM4lBins,
		 bool floatqqZZ,     string bkgOption,  string binStr,
		 bool skipPruning,   bool addAsys);
    
  /****************/
  /*   Methods    */
  /****************/

  void defineCoutDetails();
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
  void LoadNotFid();
  void LoadProdModeFraction();
  void LoadBranchingRatio();
  void LoadCrossSection();
  void LoadMinitreeN();
  
  void LoadMatrixValues(map<int, vector< pair<double,double> > > &data, string file);
  void LoadValues(map<int, vector< pair<double,double> > > &data, string file);
  void LoadValues(vector< pair<double,double> > &data, bool isPRF=false);
  void LoadValues(int p, int b, map<int, map<int, map<int,map<string,vector<double> > > > > &data, int ch);
  void LoadValues(map<string,vector<double> > &data);

  /* Print Loaded values */
  void PrintValues(map<int, vector< pair<double,double> > > data, bool isMtx=false);
  void PrintValues(vector< pair<double,double> > data, bool isBR=false, bool isXsec=false);
  
  ///* Get A*CF*R value */
  //Double_t PrintACRProduct(int ChNum, int cat);
  
  /* Get Expected Cross Section */
  //Double_t PrintExpXS(int ChNum, int cat);

  /* Define lists */
  void DefineCategoryMap();
  void CreateProcList();

  /* Set M4l number of bins */ 
  void SetM4lNbins();
  
  /* Cleaning */
  void CleanUp();

  /* Evaluate Input XS */
  double EvalXS(int Pos, int ch=0);
  double ProcessXS(int Pos, int cat, int ch);

  /* Check vector size against hist bins */
  void CheckVectorSize(TH1F *h, int chnum); //see what can be done here
  
  /* Dump information when normalization is wrong */
  void dumpAllInformation(int, RooFormulaVar*, RooRealVar*, RooArgList);

  /* Run the Class */
  void RunClass();

  /* Run xsec category */
  void doFiducialComb();
  void doFiducialSingleChannel();
  void doFiducialTotal();
  void doFiducial4l();
  void doFiducial2l2l();
  void doFiducialSumChannels();
  void doFiducialBRDifference();
  void doDifferentialFiducial();

  /* Make Systematic Block */
  RooStats::HistFactory::FlexibleInterpVar* makeSysBlock(string blockID, int ChNum, int proc, int cat, bool is_aF=false);
  RooStats::HistFactory::FlexibleInterpVar* makeSysBlockMtx(int ChNum, int proc, int cati, int catj, vector <RooRealVar *> v_sigma, vector <RooRealVar *> v_eff, vector <RooRealVar *> v_A, vector <RooRealVar *> v_r);
  RooStats::HistFactory::FlexibleInterpVar* makeSysGlobal(string blockID, int ChNum, int proc, int cat, bool isSignal, bool isggZZ);
  string GetSysNpName(int sysNum, string sysName);
  std::vector<int> getZZCatBins(int cat);
  void Pruning(vector< double > *syslow, vector< double > *sysup, vector<int> *interp, RooArgList *v_sys);
  bool Pruning(vector< double > *syslow, vector< double > *sysup, vector<int> *interp, float releff=999);
  /* Get aF/cF/Mtx/fNonFid histo name */
  string GetUnfoldParamHistoName(string type, int channel, int process);

  /* Perfom Evenlope and return up/down values */
  pair<double,double> PerformEnvelopeMtx(TH2D *nom, int ChNum, int proc, string type,
					 int sys, int rcCat, int thCat=-1);
  pair<double,double> PerformEnvelope(TH1D *nom, TH1D *anom, int ChNum, int proc,
				      string type, int sys, int rcCat, bool isZZ, bool doAR);
  pair<double,double> PerformWeightedSum(TH1D *nom, string hName, int sys, int rcCat, bool isZZ);
  
  /* Make Gaussian Constraint */
  void makeGaussianConstraint(RooRealVar* v_sys);

  /* Remap Histogram */
  TH1F* remapHisto(TH1F* hIn, int cat);
  void setupRemappedHistoAndVariables(string process, int chnum, int cat);
  
  /* Define Signal Normalisation Factor */
  RooFormulaVar* SignalNormFactorMatrix(int cat, int chNum, RooArgList* list);
  RooFormulaVar* SignalNormFactor(int cat, int chNum, RooArgList* list);

  RooFormulaVar* BackgroundNormFactor(int cat, int chNum, RooArgList* list, TH1F* h, string process);
  RooHistPdf* RetrieveSysShape (string sys, string  catname , int cat , string direction, RooRealVar *m_x,  string process_name);
  RooStarMomentMorph* RetrieveRooStar ( string catname, int cat , RooHistPdf* m_x_hpdf, RooRealVar *m_x,  string process_name);
  void  AddComponentRooStar (RooRealVar *tmp_sys, vector<int> *nn, vector<double> *nref, RooArgList *paramRooStar, RooArgList *variationRooStar, string catname, int cat,  string process_name  );
  
  /* Making Signal/Background Pdf */
  void DoSignalPdf(string process, int chnum, int cat);
  void DoBackgroundPdf(int chnum, bool qqZZ, bool ggZZ, bool redBkg, int cat);
  void DoSinglePdf(string process, int chnum, bool isSignal, int cat);
  void DoWS();
  void DoQuickTest();
  RooWorkspace *m_ws;
  void PlotPdf (RooSimultaneous *pdf, RooDataSet *combData, bool postFit = false);
  void PlotPdfSplitXS (RooSimultaneous *pdf, RooDataSet *combData, bool postFit = false);
  void PlotPdfFiducial (RooSimultaneous *pdf, RooDataSet *Asimov, RooDataSet *combData);
  void PlotSysBands ();
  void PlotM4l ();
  
  /*  WS tools  */
  RooRealVar* retrieveMuqqZZ(int cat);
  std::string m_wsname ;
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
  vector<RooArgSet> m_Normpdfcategory;
  RooArgSet m_pdfaddlist;
  vector<RooAddPdf> m_v_pdfaddlist;
  RooDataHist* m_obsdata;
  RooHistPdf *down;
  RooHistPdf *up;
  
  void ImportData();
  void MakeMCDataset();

  /* Fit Tools */
  void SetNtupla(RooWorkspace*);
  void ScanNLL(TString wsPath, TString wsName, int nSteps, TString constPOI,
	       double low, double up, TString dataType, TGraph *scan_plot,
	       vector<double> vector_postfit, int bin);
  pair<double,double> EvalErrors(vector<double> twonll, vector<double> sigma, double min);
  double EvalOneSigma(double y1, double y2, double x1, double x2);
  
  double  m_sigma, m_sigma_unc;
  int m_status, m_status_unc;
  double m_Twonll, m_Twonll_unc;
  vector<double> m_xsminitree;
  vector<double> m_np;
  vector<double> m_poi;
  vector<double> m_poiunc;
  vector<double> m_npunc;
  
  TTree *m_ScanTree;

  /* Find last non empty bin */
  string RetrieveLastNonEmptyBin(string variable, int channel, string process);

  /* Detect Decay Channel from file */
  int GetDecayChannelId(string file);

  /* Get PreFit and PostFit Xsec values and errors */
  double GetPreFitXsecVal(int pos);
  double GetPostFitXsecVal(int pos);
  double GetPostFitXsecUpErr(int pos);
  double GetPostFitXsecDownErr(int pos);

  /* Write Tables and dat files */
  void OpenTableFile(string unfold, string sys, string what);
  void WriteTableFile(string prefix, int pos);
  void CloseTableFile(string unfold, string sys, string what);
  void OpenResultsFile(string unfold, string sys, string what);
  void WriteResultsFile(int pos);
  void CloseResultsFile();
  
  /* Close the class */
  void Closing();

 protected:
  /* class options */
  string m_FileName;
  string m_SysFileName;
  string m_AcFileName;
  string m_AcSysFileName;
  string m_PathToFile;
  string m_DataPath;
  int    m_VariableId;
  string m_Variable;
  string m_Channel;
  string m_Bstr;
  bool   m_debug;
  bool   m_verbose;
  bool   m_addSys;
  bool   m_addShapeSys;
  bool   m_sysBands;
  bool   m_do2D;
  bool   m_Fiducial;
  bool   m_FidChan;
  bool   m_FidComb;
  bool   m_FidTotal;
  bool   m_Fid4l;
  bool   m_Fid2l2l;
  bool   m_FidSum;
  bool   m_BRDiff;
  double m_lumi;
  bool   m_dofit;
  bool   m_WithData;
  bool   m_useBornLep;
  double m_parallel;
  bool   m_skipScan;
  bool   m_useMCData;
  string m_DataSet;
  string m_fixSys;
  bool   m_matrix;
  bool   m_cfsplit;
  bool   m_multProd;
  string m_ProdMode;
  string m_ProdHist;
  string m_BkgHist;
  string m_InputMtx;
  int    m_chSplit;
  int    m_mcVers;
  bool   m_redM4lBins;
  bool	 m_floatqqZZ;
  string m_bkgOption;
  bool   m_skipPruning;
  bool   m_addAsys;
  
  /*****************/
  /* class members */
  /*****************/
  
 private:
  string m_OutDir;
  string m_Dir;
  TH1F* m_hremapped;   //!
  TFile *m_InFile;     //!
  TFile *m_SysFile;    //!
  TFile *m_AcInFile;   //!
  TFile *m_AcSysFile;  //!
  map<int, vector<pair<double,double> > > m_cf, m_acc, m_r, m_xsScale, m_MinitreeN, m_notFid;
  vector<vector<int> > m_ZZbins;
  map<int,string> m_Category;
  vector<int> m_channels;
  vector< pair<double,double> > m_br, m_xsec;
  map<string,int> m_process;
  map<string, vector<string> > m_shapeLabels, m_sigUnfLabels;
  ifstream m_InStream;
  vector<string> m_cfFile, m_accFile, m_rFile, m_mtFile, m_notFidFile;
  string m_brFile, m_xsecFile;
  int m_ChNum;
  int m_Mbins;
  Double_t m_mMin, m_mMax;

  /* histograms objects */
  TH1F *m_h;  //!
  TH1F *m_h_remapped;  //!
  TH1F *m_tmp;  //!
  TH1F *m_Htmp; //!
  vector<double> m_binnames;

  /* RooFit objects */
  RooRealVar *m_Lumi ;
  RooFormulaVar *m_Norm, *m_norm_pdf;
  RooRealVar *m_x, *m_m4l, *m_mean;
  RooRealVar *sigma_p;
  //
  //RooProdPdf *m_x_m4l;
  RooHistPdf *m_x_hpdf, *m_m4l_hpdf;
  RooUniform *m_x_updf;
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
  vector<double> m_binwidth;
  vector<double> m_binlowerlimit;
  vector<RooRealVar*> m_binwidthroorealvar;
  RooStarMomentMorph *m_signalmorphiong;

  pair<double,double> m_LeftRightErrors;
  vector<double> m_preFitVal, m_postFitVal;

  ofstream m_tableFile, m_resultsFile;

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
