/* ROOT includes */
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLatex.h>
/* C++ includes */
#include <sys/stat.h>
#include <utility>
#include "iomanip"
#include "iostream"
#include "fstream"
#include "sstream"

void PlotSys(std::string variable, std::string channel,
	     std::string sysType, bool debug);
TH1F* GetHistogram(std::string var);
std::string GetChannel();
void SetAtlasStyle();
void drawLabels();
TLegend* CreateLegend();
void CheckOutDir();
void SetAxisLabels(TH1F* h);
std::string ConvertToStringWithPrecision(double value, int n);
std::string GetYaxisName(TH1F* h);
std::string GetXaxisName();

bool m_debug;
std::string m_Dir;
std::string m_OutDir;
std::string m_variable;
std::string m_channel;
std::string m_sysType;
TFile *m_InFile;
TH1F *hup;
TH1F *hdw;
TH1F *hnm;
TCanvas *m_cs;
TLegend *m_leg;
