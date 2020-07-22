/* ROOT includes */
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TColor.h>

void ShapeSysVar(bool doFiducial, bool debug);
void DefineHistograms();
void DefineCategories(bool doFiducial);
void ProcessFiducial();
void AddFidMassShifts();
void ProcessDifferential();
void AddDiffMassShifts();
void RebinHistos();
void MergeHistos();
void CleanProdModeHistos();
void CleanMergedHistos();

bool m_debug;
std::string m_Dir;
TFile *m_In;
TFile *m_Out;
std::vector<std::string> m_prodMode;
std::vector<std::string> m_chans;
std::vector< std::pair<std::string,int> > m_vars;
std::vector< std::pair<std::string,std::string> > m_shifts;

TH1F *ElSclUp1_pm, *ElSclDw1_pm;
TH1F *ElSclUp2_pm, *ElSclDw2_pm;
TH1F *ElSclUp3_pm, *ElSclDw3_pm;
TH1F *ElResoUp_pm, *ElResoDw_pm;
TH1F *MuIdUp_pm  , *MuIdDw_pm  ;
TH1F *MuMsUp_pm  , *MuMsDw_pm  ;
TH1F *MuSclUp_pm , *MuSclDw_pm ;

TH1F *ElSclUp1, *ElSclDw1;
TH1F *ElSclUp2,	*ElSclDw2;
TH1F *ElSclUp3,	*ElSclDw3;
TH1F *ElResoUp,	*ElResoDw;
TH1F *MuIdUp  ,	*MuIdDw  ;
TH1F *MuMsUp  ,	*MuMsDw  ;
TH1F *MuSclUp ,	*MuSclDw ;

TH1F *MassShift;
