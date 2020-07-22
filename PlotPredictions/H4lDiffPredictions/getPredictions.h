#ifndef _GETPREDICTIONS_H
#define _GETPREDICTIONS_H

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
#include <THStack.h>
#include <TH2.h>
#include <TMath.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TMatrixDSym.h"
#include <TChain.h>
#include <TLegend.h>
#include <TLatex.h>
#include "TCollection.h"
#include "TKey.h"
#include "TObject.h"
#include "TObjArray.h"


// Base class 
class getPredictions 
{
   public:
   	getPredictions(std::map<TString, TString>& opts);
   	virtual ~getPredictions();

   	// open the file and setup POI and NP ranges
   	void run();

   protected:


      void loadMaps();

      void stupidFill();

      void readFiles();

      void calcFid();

      void cleanHist();

      void quadSys(TString fidWeightName, TString fidVarName);

      TH1D* getPDFSys(TString fidWeightName, TString fidVarName);

      void evelopeSys(TString fidWeightName, TString fidVarName);
      TString getNominalSys();

      TH1D* getHist(TString histName, TString varName, TString weightName);

      void fillSysMap();

      void saveFiles();

      void haddFiles();

      std::vector<TString> tokenizeStr(TString str, TString key);


      std::map<TString, TString> m_opts;
      std::map<TString, TString> m_cutsMap;
      std::map<TString, TString> m_obsMap;
      std::map<TString, std::vector<double>> m_binMap;
      std::map<TString, TString> m_sysMap;

      std::vector<TString> m_fileListVect;
      std::vector<TString> m_haddFileList;

      TChain* m_fileChain;
      TString m_outFolderName;

      TH1D* m_fidHist;
      TH1D* m_incHist;
      
      TH1D* m_nomHist;
      TH1D* m_upHist;
      TH1D* m_downHist;

      TString m_keyName;
      TString m_DSID;

      std::vector<TH1D*> m_nomHistVect;
      std::vector<TH1D*> m_upHistVect;
      std::vector<TH1D*> m_downHistVect;


};


#endif
