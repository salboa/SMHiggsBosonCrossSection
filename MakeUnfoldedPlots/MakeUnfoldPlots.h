/* ROOT includes */
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TRint.h"
#include "TGaxis.h"
#include "TLine.h"
#include "TArrow.h"
#include "Math/ProbFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"
#include "RooStats/RooStatsUtils.h"
/* C++ includes */
#include <map>
#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
#include <utility>



bool m_debug;
bool m_Conf;
bool m_Paper;
bool m_doN3LO;
std::string m_OutDir;
std::string m_Var;
std::vector<float> m_YR4error;
float m_integralobs;
TH1F* m_hremapped;
std::vector<TArrow*> m_Arrows;

void MjjAxis(TH1F *h, TPad *p, float offset);

void evalPValueFid (std::vector<double> v);

void remapHisto(TGraphAsymmErrors* a , std::string MC);

TArrow* MakeArrows(double u, double y, std::string MC);

void remapMjjHisto(TGraphAsymmErrors* a , std::string MC);

double evalIntegral(TH1F* h);

TH1F* remapHisto(TH1F* hIn, bool isMjj=false);//int bin );

TH1F* CreateDummyPlot(TH1F* In, std::string name, std::string var);
  
void setStyle(std::string sample, TH1F *h);

void setStyle(std::string sample, TGraphAsymmErrors *h, bool isPoint=false);

void MakeFidUnfoldPlots(std::string expFile, bool keepCanvas);

void MakeDiffUnfoldPlots(std::string var, std::string varFile,
			 std::string mgFile, std::string mgFile2,
			 std::string expFile, std::string HresFile,
			 std::string sysFile, bool keepCanvas,
			 bool normalized, bool debug, bool doN3LO);

void MakeNjetExtended(std::string expFile, std::string mgFile,
		      std::string mgFile2, bool keepCanvas, bool doN3LO);

void SetAtlasStyle();

TGraphAsymmErrors* makeTGraph(TH1F *nominal, TH1F *up, TH1F *down,
			      std::string MCname, bool reduceXerr=false,
			      bool NoYerr=false);

TGraphAsymmErrors* makeGraph(std::vector<TGraphAsymmErrors*> obs,
			     std::string Name, std::vector<double> xVal,
			     bool scale=false);

TGraphAsymmErrors* makeSysGraph(std::vector<TGraphAsymmErrors*> obs,
				std::vector<TGraphAsymmErrors*> obsSys,
				std::string Name, std::vector<double> xVal,
				bool scale=false);

TGraphAsymmErrors* makeGraphNjet(std::vector<TGraphAsymmErrors*> obs,
				 std::string Name, std::vector<double> xVal);

TGraphAsymmErrors* makeSysGraphNjet(std::vector<TGraphAsymmErrors*> obs,
				    std::vector<TGraphAsymmErrors*> obsSys,
				    std::string Name, std::vector<double> xVal);

TGraphAsymmErrors* makeObs(TGraphAsymmErrors *obs, std::string var);

TGraphAsymmErrors* makeObsSys(TGraphAsymmErrors *obs,
			      TGraphAsymmErrors *sys,
			      std::string var);

TGraphAsymmErrors* makeRatio(TGraphAsymmErrors *inGr,
			     TGraphAsymmErrors *obs,
			     TH1F * dummy, std::string var, std::string MC);

void drawLabels(bool isFiducial=false);

void setAxisLabels(TH1F *g, std::string var, bool ratio);

void makeSys(std::vector<TH1F*> *nominalall, std::vector<TH1F*> *sysupall,
	     std::vector<TH1F*> *sysdownall, TH1F *nominal,
	     TH1F *sysup, TH1F *sysdown, bool istotal= false);

void makehisto(std::vector<TH1F*> *nominalall, std::vector<TH1F*> *sysupall,
	       std::vector<TH1F*> *sysdownall, TFile *_file2, bool rest,
	       std::string var, TH1F *reference);

std::vector<float> totalXS(std::string);

std::vector<float> totalXS(bool N3LO, std::string ProdMode);

double evalPValue(TH1F* h, std::string MC, std::string var, bool normalized);

double evalPValuePtPt(std::string MC, bool normalized);

TLine* DefineVertLine(Double_t Xval, Double_t YvalMin,Double_t Yval);

void CheckOutDir();

void AdjustXaxis(TH1F* h, std::string var);

TLine* MakeHorLine(TH1F*h, std::string var);

TLegend* CreateLegend(std::string var="", bool isFid=false);

std::pair<double,double> GetBarSize(std::string var);

double GetBarSpacing(std::string var);

void DeriveError();
