/* ROOT includes */
#include <TH1.h>
#include <TH2.h>
#include <TObject.h>
#include <TFile.h>
#include <TSystem.h>
/* C++ includes */
#include "iostream"
#include "fstream"
#include "sstream"

/* Methods */
void redBkgSys(bool Fiducial, bool debug);
void doDifferential();
void doFiducial();
void evalSys(std::string var, std::string folder, std::string idiots);
void evalDiffSys(std::string folder);
void evalFidSys(std::string chan);
void RebinHistos();

/* Internal variables */
TFile *m_In;
Double_t Y4mu, Y4e, Y2mu2e, Y2e2mu, Ytotal;
TH1F *h4mu, *h4e, *h2e2mu, *h2mu2e;
TH1F *h2l2mu_stat, *h2l2mu_syst, *h2l2e_stat, *h2l2e_syst;
std::ofstream m_Out;
std::stringstream m_ss;
std::string m_bin;
bool m_debug;
bool m_isFid;
