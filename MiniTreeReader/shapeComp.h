/* ROOT includes */
#include <TFile.h>
#include <TH1F.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRint.h>

/* C++ includes*/
#include "iomanip"
#include "iostream"
#include "fstream"
#include "vector"
#include "map"
#include "sstream"
#include <sys/stat.h>
#include <utility>

void CompShape(std::string var, std::string chan);

std::string ConvertToStringWithPrecision(double value, int n);

std::string m_File1, m_File2, m_Path;

Double_t getYmax(TH1F *h1, TH1F *h2);
