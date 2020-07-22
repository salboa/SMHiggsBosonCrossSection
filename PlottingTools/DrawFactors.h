#include <TROOT.h>
#include <TH1.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TFile.h>
#include <TApplication.h>
#include <TRint.h>
#include <TLine.h>
/* C++ includes */
#include <iomanip>
#include <iostream>
#include <map>
/* Other includes */
#include "../Utils/PrintHelpers.h"
#include "../Utils/VarHandler.h"
#include "../Utils/HistoStyle.h"

void DrawFactors(int varId, int chanId);
void RetrieveHistograms();
void RetrieveMatrices();
void RetrieveACR();
void DefineInputFiles();
void DefineStyle();
void DrawMatrices(int varId, int chanId);
void DrawACR(int varId, int chanId);
void DrawPlots(std::map<std::string,std::map<std::string,TH1D*> > histos,
	       std::map<std::string,std::map<std::string,TH1D*> > ratios,
	       int type, TLegend *leg, int chanId, int varId);
TH1D* GetFiducialPlot(std::string prefix, std::string prodMode, std::string mc);
void DrawfnonFidPlots(std::map<std::string,std::map<std::string,TH1D*> > histos, TLegend *leg, int chanId, int varId);

/* Global variables */
bool m_debug, m_verbose, m_isConf, m_isPaper, m_mrgProd;
bool m_allSig, m_isBorn, m_doRelComp, m_doMatrix;
std::vector<std::string> m_ProdModes;
std::map<std::string,std::map<std::string,TH1D*> > m_Afac, m_Cfac, m_Rfac;
std::map<std::string,std::map<std::string,TH1D*> > m_Arat, m_Crat, m_Rrat;
std::map<std::string,Int_t> m_ProcColor, m_ProcMarker, m_mcRelColor, m_mcRelMarker;
std::map<std::string,Double_t> m_ProcMrkSz, m_mcRelMrkSz;
std::map<std::string,TFile*> m_fMap;
std::string m_varName, m_chanName, m_process, m_filePrefix;
int m_procNum;
int m_mcVersion;
int m_nBins;
TString m_nBins_string;
double m_lumi;

TCanvas *c;
TPad *p1, *p2;
TLegend *leg;
TLine *hline;
TH2D *m_migMtx, *m_rpsMtx;
std::map<std::string,std::map<std::string,TH1D*> > m_fnonFid;
