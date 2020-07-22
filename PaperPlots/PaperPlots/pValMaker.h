#ifndef _PVAL_H
#define _PVAL_H

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
#include <fstream>


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
#include <TH1D.h>
#include <TArrow.h>


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

// ROOFit include
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooArgSet.h"
#include "RooCategory.h"
#include "RooSimultaneous.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/AsymptoticCalculator.h"
#include "RooMinimizer.h"
#include "RooNLLVar.h"
#include "TStopwatch.h"
#include "RooRandom.h"
#include "RooFitResult.h"
#include "RooNumIntConfig.h"
#include "RooMinuit.h"
#include "RooRealSumPdf.h"
#include "RooStarMomentMorph.h"

// Base class 
class pValMaker 
{
	public:
		pValMaker(std::map<TString, TString>& opts, std::vector<double> binWidth);
		virtual ~pValMaker();

		TString getPVal(TH1D* prediction, TString generator, TString fidSpecial = "");

	protected:
		TString readPVal();

		void openWorkspace();

		void fixRooStarMomentMorphCache();

		RooFitResult* minimize(RooAbsReal* fcn, int& statusOut, RooArgSet* minosSet = NULL);

		RooNLLVar* getNLL();

		void setPOIs(int setPOI);

		int countPOIs();

		int getNDOF();

		void fitPoint(RooFitResult* &fitresult, int &status, RooNLLVar* &nll, RooArgSet* minosSet = NULL);

		void savePValue(int POIName);


		std::map<TString, TString> m_opts;

   		TFile* m_file;
   		RooWorkspace* m_ws;
   		RooStats::ModelConfig* m_mc;
   		RooDataSet*  m_dataSet;
   		const RooArgSet* m_POI;
   		const RooArgSet* m_Sys;
   		const RooArgSet* m_globs;

   		TH1D* m_prediction;
   		TString m_generator;
   		TString m_outDirName;
   		TString m_fidSpecial;
   		std::vector<double> m_binWidth;

   		double m_pValue = -999;
   		TString m_pValString = "FixMe";

};


#endif
