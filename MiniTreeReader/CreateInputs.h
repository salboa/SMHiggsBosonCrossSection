#ifndef CreateInputs_H
#define CreateInputs_H

/* C++ includes */
#include "iostream"
#include "fstream"
#include "map"
#include <sys/utsname.h>
#include <chrono>
#include <cassert>

/* ROOT includes */
#include <TH1.h>
#include <TH2.h>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TColor.h>
#include <TChain.h>

/* Other includes */
#include "../Utils/PrintHelpers.h"
#include "../Utils/Tools.h"
#include "../Utils/Enum.h"
#include "../Utils/SysMapHandler.h"
#include "../Utils/CoupBins.h"
#include "EventLoop.h"

class CreateInputs {

 public:
  
  /****************/
  /* Constructor */
  /****************/
  CreateInputs();
  CreateInputs( std::string Process   , int Nbins            , double Min           ,
		double Max            , bool ShiftUp         , bool ShiftDown       ,
		int sysNum            , int mcType           , bool isContReg       ,
		bool isCouplings      , bool doACRfact       , int Stage            ,
		bool useMtx           , bool useRootThMtc    , bool writeEvtList    ,
		bool ACRdetails       , bool split_cF        , std::string Var      ,
		bool restrictJet      , bool removeLepWeight , bool checkDuplicates ,
		std::string procScale , double valScale      , bool debug           );

  /****************/
  /*  Destructor  */
  /****************/
  ~CreateInputs();
  
  /****************/
  /*   Methods    */
  /****************/

  /* Time Count */
  void TimeCount();
  
  /* Create Systematics and channels maps */
  void LoadSysMap();
  void MakeChanMaps();

  /* Detect Systematics Family */
  std::string DetectSysFamily();

  /* Detect if sys for m4l shape */
  bool UseSysMassInBins(int systNum);
  
  /* Define Output File */
  void DefineOutFile(int systNum);

  /* Set MC versions */
  void SetMCtypes();

  /* Detect Hostname */
  void DetectHostname();
  
  /* Set Directory prefix */
  void SetDirPrefix();

  /* Get Directory for some Reco cases */
  std::string GetRecoDir(int proc, int systNum, std::string baseDir);

  /* Detect if Herwig sample should be used */
  bool UseHerwig(int proc, int systNum);
    
  /* Set Files/Branches Chain */
  void SetChains(int systNum);
  void AddFilesToChain(int proc  , std::string rcDir, std::string rcName,
		       int mcType, std::string thDir, std::string thName,
		       bool isHw=false, bool isPw=false);
  
  /* Main Processes */
  void Process();
  
  /* Make Reducible Background */
  void MakeRedBkg(int sysNum);

  /* Make Other Processes */
  void RunProcesses(int sysNum);

  /* Make A, C, r Factors */
  void RunACRfactors(int sysNum);
  void EvaluateACRfactors();
  void WriteACRfactors(std::string var);
  double DeriveValueError(double nEvt, double eff);
  double GetNumberOfEvents(double nEvtWgt, double nEvtRaw, double integral, double nRawTot);
 
   /* Make the Response Matrix */
  void RunMatrix(int sysNum);
  void EvaluateMatrix();
  void WriteMatrix(std::string var);
  void WriteFirstMatrixLine(int nbins);
  
  /* Write to File */
  void WriteFirstLine();
  void WriteCFvalues(int Bins, std::string OutDir, std::string var);
  void WriteFnonFidValues(int Bins, std::string OutDir, std::string var);
  void WriteACCvalues(int Bins, std::string OutDir, std::string var);
  void WriteRvalues(int Bins, std::string OutDir, std::string var);
  void WriteNvalues(int Bins, std::string OutDir, std::string var);
  void WriteMatrixValues(int Bins, std::string OutDir, std::string var);
  void WriteNonFidMatrixValues(int Bins, std::string OutDir, std::string var);
  void WriteNmatrixValues(int Bins, std::string OutDir, std::string var);

  /* Merge Reducible Background */
  void MergeRedBkg(std::string sysName="Nominal");

  /* Define Histograms */
  void DefineHistograms(int systNum);
  void DefineCouplingsHistoSet();
  void DefineXsecHistoSet(int systNum);
  void DefineACRHistoSet();
  void DefineACRHistos(std::string fact, std::map< std::string,std::vector<TH1D*> > & hmap);
  void DefineMatrixHistos(std::string, std::map< std::string,std::vector<TH2D*> > & hmap);
  void Create1DHistogram(TH1D* &h1d, std::string Hname, int vNum, bool isFine=false);

  /* Define Values */
  void DefineValuesMaps();
  void DefineMatrixMaps();
  
  /* Make List of Plots To be Written on File */
  std::vector<TObject*> ListOfPlotsToWrite();

  /* Make List of 1D Plots To be Normalized to Bin Width */
  std::vector<TH1D*> ListOf1DPlotsToNorm();

  /* Make List of 2D Plots To be Normalized to Bin Width */
  std::vector<TH2D*> ListOf2DPlotsToNorm();

  /* Normalise Histograms to Bin Size */
  void DivideForBinSize(std::vector<TH1D*> &plots);
  void DivideForBinSize(std::vector<TH2D*> &plots);

  /* Fill and Normalize Z+jets Histograms */
  void Handle2DZjetsPlotsInfo();
  int Get2DZjetsVarShift(int vNum, int pos);
  void FillZjetsPlots(std::string var);
  void FillZjetsFineM4l(int InBin, std::string var);
  void Fill2DZjetsPlots(std::string var);
  void MergeAndNormalizeZjetsPlots(std::string var, bool normalize=true);
  void Normalize2DZjetsPlots(int vNum,std::string var);
  double GetZjetsSysImpact(std::string vName, int sysNum, int channel, int bin=0);
  
 protected:

  /* Class Init Variables */
  int m_Process;
  std::string m_ProcStr;
  std::string m_Syst;
  std::string m_zjetNameSuffix;
  int m_procXStoScale;
  double m_valXStoScale;
  int m_SystNum;
  int m_mcVers;
  int m_Nbins;
  int m_Stage;
  double m_Min;
  double m_Max;
  bool m_debug;
  bool m_acrDetails;
  bool m_doSystematics;
  bool m_doShiftUp;
  bool m_doShiftDown;
  bool m_isContReg;
  bool m_isCouplings;
  bool m_isLocal;
  bool m_isDell;
  bool m_isCedar;
  bool m_doACRfactor;
  bool m_useMatrix;
  bool m_useRootThMtc;
  bool m_EvtList;
  bool m_useTruth;
  bool m_split_cF;
  bool m_restrictJets;
  bool m_removeLepWeight;
  bool m_keepTruth;
  bool m_checkDuplicates;
  std::map< int,std::vector< std::pair<std::string,std::string> > > m_zjetNames;
  std::vector<double> m_zjetStat;
  std::vector<double> m_zjetSys;
  std::vector<double> m_zjetYields;
  std::map< short int,std::string > m_SysMap;
  std::map< short int,std::string > m_ChMap, m_LbMap;
  std::map< std::string,std::vector<TH1D*> > m_Hmap;
  std::map< std::string,std::vector<TH2D*> > m_Hmap2D;
  std::map< std::string,std::map< short int,std::vector<TH1D*> > > m_HmapBins;
  std::map< std::string,std::map< short int,std::vector<TH1D*> > > m_HmapBinsFine;
  std::map< std::string,std::vector<TH1D*> > m_HcFBornMap;
  std::map< std::string,std::vector<TH1D*> > m_HcFDresMap;
  std::map< std::string,std::vector<TH1D*> > m_HfNFabsBornMap;
  std::map< std::string,std::vector<TH1D*> > m_HfNFabsDresMap;
  std::map< std::string,std::vector<TH1D*> > m_HfNFrelBornMap;
  std::map< std::string,std::vector<TH1D*> > m_HfNFrelDresMap;
  std::map< std::string,std::vector<TH1D*> > m_HaFBornMap;
  std::map< std::string,std::vector<TH1D*> > m_HaFDresMap;
  std::map< std::string,std::vector<TH1D*> > m_HrFmap;
  std::map< std::string,std::vector<TH2D*> > m_HmtxBornMap;
  std::map< std::string,std::vector<TH2D*> > m_HmtxDresMap;
  std::map< std::string,std::vector<TH2D*> > m_HmtxMigBornMap;
  std::map< std::string,std::vector<TH2D*> > m_HmtxMigDresMap;
  std::map< std::string,std::map< short int,std::vector<std::pair<double,double> > *> > m_recoBornVal;
  std::map< std::string,std::map< short int,std::vector<std::pair<double,double> > *> > m_recoDresVal;
  std::map< std::string,std::map< short int,std::vector<std::pair<double,double> > *> > m_recoBornRaw;
  std::map< std::string,std::map< short int,std::vector<std::pair<double,double> > *> > m_recoDresRaw;
  std::map< std::string,std::vector<std::pair<double,double> > *> m_recoBornValInt;
  std::map< std::string,std::vector<std::pair<double,double> > *> m_recoDresValInt;
  std::map< std::string,std::vector<std::pair<double,double> > *> m_recoBornRawInt;
  std::map< std::string,std::vector<std::pair<double,double> > *> m_recoDresRawInt;
  std::map< std::string,std::map< short int,std::vector<double> *> > m_fidBornVal;
  std::map< std::string,std::map< short int,std::vector<double> *> > m_fidBornRaw;
  std::map< std::string,std::vector<double> *> m_fidBornValInt;
  std::map< std::string,std::vector<double> *> m_fidBornRawInt;
  std::map< std::string,std::map< short int,std::vector<double> *> > m_fidDresVal;
  std::map< std::string,std::map< short int,std::vector<double> *> > m_fidDresRaw;
  std::map< std::string,std::vector<double> *> m_fidDresValInt;
  std::map< std::string,std::vector<double> *> m_fidDresRawInt;
  std::map< std::string,std::map< short int,std::vector<double> *> > m_truthVal;
  std::map< std::string,std::map< short int,std::vector<double> *> > m_truthRaw;
  std::map< std::string,std::vector<double> *> m_truthValInt;
  std::map< std::string,std::vector<double> *> m_truthRawInt;
  std::vector<double> *m_truthInt;
  std::vector<double> *m_truthIntRaw;
  std::vector<int> m_mcType;
  std::map< std::string, std::map< short int, std::map <short int, std::vector <double> *> > > m_rspMtxBorn_Num;
  std::map< std::string, std::map< short int, std::vector <double> *> > m_rspMtxBorn_Denom;
  std::map< std::string, std::map< short int, std::map <short int, std::vector <double> *> > > m_rspMtxDres_Num;
  std::map< std::string, std::map< short int, std::vector <double> *> > m_rspMtxDres_Denom;
  std::map< std::string, std::map< short int, std::vector< double > *> > m_nonFidBorn;
  std::map< std::string, std::map< short int, std::vector< double > *> > m_nonFidDres;

  std::map<int, std::map<ULong64_t, std::vector<short int> > > m_ThMtc_Born;
  std::map<int, std::map<ULong64_t, std::vector<short int> > > m_ThMtc_Dres;
  
  /* Class internal variables */
  TFile *m_In;
  TFile *m_Out;
  TChain *m_chain;
  TChain *m_thchain;
  std::string m_treename;
  std::ofstream m_OutF;
  TH1D *h1d;
  TH2D *h2d;
  TH1D *m_llmumu, *m_llee;
  std::string m_Prefix;
  //std::string m_fidPrefix;
  std::string m_AltPrefix;
  
  /* Event Loop Class */
  EventLoop *evt;

 private:
  std::chrono::time_point<std::chrono::system_clock> m_begin, m_end;
  int m_elapsedTime;
  std::time_t m_startTime, m_endTime;
  Double_t m_m4lRange[34];
  Int_t m_NbinsFine;
  bool m_addFineM4l;
};
#endif
