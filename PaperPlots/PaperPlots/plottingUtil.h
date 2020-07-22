#ifndef _PLOTTINGUTIL_H
#define _PLOTTINGUTIL_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <map>
#include <sys/stat.h>
#include <cstdlib>
#include <regex>


// ROOT include
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <THStack.h>
#include <TH2.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TMatrixDSym.h"
#include <TChain.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TLine.h>
#include <TGaxis.h>



void setStyle(std::string sample, TH1D *h);

void setStyle(std::string sample, TGraphAsymmErrors *h, bool isPoint);

std::pair<double,double> GetBarSize(TString var);

double GetBarSpacing(TString var);

void setAxisLabels(TH1D *g, TString var, bool ratio, double aspectRatio, bool isZZ);

TLegend* CreateLegend(std::string var, bool isFid);

void AdjustXaxis(TH1D* h, TString var);

TLine* MakeHorLine(TH1D* h);

void drawLimit();

void setupFidFrame(TH1D* hist);

TGaxis* getAxis(TString position);

void drawLabels(bool isFiducial, TString unFoldType);

void plotPValue(TString NNLOPSPVal, TString MG5PVal);

void SetAtlasStyle();



#endif
