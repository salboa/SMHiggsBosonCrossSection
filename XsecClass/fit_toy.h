#include "TFile.h"
#include "TF1.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH2.h"
#include "TF1.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TCut.h"
#include "TRandom3.h"
#include "Math/Interpolator.h"
#include "RooWorkspace.h"
#include "RooAbsData.h"
#include "RooRandom.h"
#include "RooRealSumPdf.h"

#include "RooStats/ModelConfig.h"
#include "RooStats/ToyMCImportanceSampler.h"
#include "RooStats/SamplingDistribution.h"
#include "RooStats/RatioOfProfiledLikelihoodsTestStat.h"
#include "RooStats/AsymptoticCalculator.h"

#include "RooStats/FrequentistCalculator.h"

#include <vector>

#include "RooNLLVar.h"
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooSimultaneous.h"
#include "RooMinimizer.h"
#include "RooProfileLL.h"
#include "RooPlot.h"
#include "RooStats/RooStatsUtils.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <TMath.h>

int ToyNumber;
int Seed;

std::vector <int> counter;
std::vector <int> max_size;

TTree *ToyTree;


double  m_event, m_event4mu, m_event4e, m_event2e2mu, m_event2mu2e, status_comb,status_4mu, status_4e, status_2e2mu, status_2mu2e;
double sigma_comb, sigma_4mu, sigma_4e, sigma_2e2mu, sigma_2mu2e;
int n_to_extract = -1;
double Timetoy;
int event_index=-1;


//Random generator
TRandom3 rand_gen(0);
vector<double> poi;

vector<double> v_low;
vector<double> v_up;
vector<double> v_nominal;


int mbutoFit (RooWorkspace*, RooDataSet*, TString, TString);
void SetNtupla(RooWorkspace*);
void initializevar(RooWorkspace*, RooStats::ModelConfig*);
void fit_toy(  int, TString, TString, int, int);
void evalranges (RooWorkspace* w, RooStats::ModelConfig* mc);
