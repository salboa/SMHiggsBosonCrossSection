#ifndef _PLOTMAKER_H
#define _PLOTMAKER_H

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
#include <TArrow.h>


// custom includes
#include "plottingUtil.h"
#include "pValMaker.h"

// Base class 
class plotMaker 
{
   public:
   	plotMaker(std::map<TString, TString>& opts);
   	virtual ~plotMaker();

   	void run();

   protected:
      // for 1D variables
      typedef struct _fileGroup {TFile* fitFile; TFile* sysFitFile; TString unFoldType;} fileGroup;
      typedef struct _tgraphGroup {TGraphAsymmErrors* fitGraph; TGraphAsymmErrors* sysFitGraph;TGraphAsymmErrors* ZZfitGraph; TGraphAsymmErrors* ZZsysFitGraph; TString unFoldType;} tgraphGroup;

      typedef struct _histPred {TH1D* nom; TH1D* up; TH1D* down;} histPred;
      typedef struct _histPredFid {histPred fidPerChan; histPred fid2l2l; histPred fid4l; histPred fidSum; histPred fidComb; histPred fidTotal;} histPredFid;


      // for fiducial variables
      typedef struct _fidResFiles   {TFile* fidPerChan; TFile* fid2l2l; TFile* fid4l; TFile* fidSum; TFile* fidComb; TFile* fidTotal;} fidResFiles;
      typedef struct _fidResTGraphs {TGraphAsymmErrors* fidPerChan; TGraphAsymmErrors* fid2l2l; TGraphAsymmErrors* fid4l; TGraphAsymmErrors* fidSum; TGraphAsymmErrors* fidComb; TGraphAsymmErrors* fidTotal;} fidResTGraphs;

      // get the names of the variables inside all the root files
      void setVariableMap();

      void getFitFiles();

      void getFitTGraphs();
      fidResTGraphs getFidTGraphs(fidResFiles fidFiles);

      void getPredictions();

      // plotting
      void plot1D();

      void plot2D();
      
      void plotFid();


      ////////////////// helper functions ///////////////////
      histPred loadPreditions(TString fileName);
      histPredFid loadFidPreditions(TString fileName, bool onlyTotal);

      void addXH(histPredFid &ggF, histPredFid XH, bool totalOnly);
      void addXH(histPred &prediction, histPred XH);


      TGraphAsymmErrors* makeTGraph(histPred predictions, TString name);


      void rebin(histPred &histPred);
      void scaleHist(histPred &histPred, double scale);
      TH1D* rebin(TH1D* hist);
      void modifyObs(tgraphGroup &fitResults);
      TGraphAsymmErrors* modifyObs(TGraphAsymmErrors* inGraph, TString type);
      std::vector<double> getBinWidth();
      

      TGraphAsymmErrors* makeRatio(TGraphAsymmErrors* input, TGraphAsymmErrors* reference, TH1D* frame, TString compareTo);
      TArrow* MakeArrows(double u, double y, TString compareTo);


      TGraphAsymmErrors* getFidBinning(fidResTGraphs resultTGraphs, bool isSys);
      TGraphAsymmErrors* getFidBinning(histPredFid resultTGraphs, bool totalOnly, TString inName);
      void setFidPoint(TGraphAsymmErrors *newGraph, int newBin, TGraphAsymmErrors *oldGraph, int oldBin, bool isSys, double scaling);
      void saveFidPVal();
      void printFidPredition(plotMaker::histPred hist);

      // vector list to cycle through to decide if something is 1D, 2D, or fiducial
      void getVarPlotType();


      // for fiducial variables
      histPredFid m_NNLOPS_N3LO_Fid;
      histPredFid m_XHFid;
      histPredFid m_MG5FxFxFid;
      histPredFid m_NNLOPS_N2LO_Fid;
      histPredFid m_HRESFid;

      // for 1D variables
      histPred m_NNLOPS;
      histPred m_NNLOPS_XH;
      histPred m_MG5FxFx;
      fidResFiles   m_fidFiles;
      fidResFiles   m_fidSysFiles;
      fidResTGraphs m_fidResults;
      fidResTGraphs m_fidSysResults;

      std::vector<fileGroup>        m_fitFileVect;
      std::vector<tgraphGroup>      m_fitGraphVect;
    
      // common
      std::vector<TArrow*>          m_Arrows;
      std::map<TString, TString>    m_opts;
      std::map<TString, TString>    m_variableMap;
      std::vector<TString>          m_subFolderVect;
      std::vector<double>           m_binWidth;

};


#endif
