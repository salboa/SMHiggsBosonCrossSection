#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include  <iostream>
#include  <string>
#include  <fstream>

using namespace std;

void getVector(string file, vector <double> *v);
void getVectorPrediction(string file, vector <double> *v);

void makeRatio(string MatxName= "pt_fit__expected_ggH_ggH.dat", string BinByBinname="pt_binbybin__fit__expected_ggH_ggH.dat", string Prediction="pt_fit__expected_ggH_ggH.dat", string output="ggH_ggH"){

  vector <double> mtx;
  vector <double> binbybin;
  vector <double> expected;
  getVector(MatxName, &mtx);
  getVector(BinByBinname, &binbybin);
  getVectorPrediction(Prediction, &expected);
  TGraphAsymmErrors g_mtx;
  TGraphAsymmErrors g_binbybin;

  for (unsigned int i =0; i < mtx.size()/3  ; ++i ){
    cout << expected.at(3*i) << " " << expected.at(3*i+1) << " " << expected.at(3*i+2) << endl;

    g_mtx.SetPoint(i, 1.+i - 0.1, mtx.at(3*i)/expected.at(3*i));
    g_binbybin.SetPoint(i,1.+ i + 0.1, binbybin.at(3*i)/expected.at(3*i));
    g_mtx.SetPointError(i, 0, 0, mtx.at(3*i+2)/expected.at(3*i), mtx.at(3*i+1)/expected.at(3*i));
    g_binbybin.SetPointError(i, 0, 0, binbybin.at(3*i+2)/expected.at(3*i), binbybin.at(3*i+1)/expected.at(3*i));


  }
  TCanvas c("c","c", 800, 800);
  g_mtx.GetYaxis()->SetLimits(0,2.5);
  g_mtx.SetLineColor(kRed); g_mtx.SetMarkerColor(kRed);g_mtx.SetLineWidth(3); g_mtx.SetMarkerStyle(24); g_mtx.SetMarkerSize(1.2);
  g_binbybin.SetLineColor(kBlue); g_binbybin.SetMarkerColor(kBlue);g_binbybin.SetLineWidth(3);  g_binbybin.SetMarkerStyle(26); g_binbybin.SetMarkerSize(1.2);
  
  g_mtx.Draw("ap");
  g_binbybin.Draw("p,same");
  g_mtx.GetYaxis()->SetRangeUser(0,2.5);
  g_mtx.GetYaxis()->SetTitle("Fit/prediction");
  g_mtx.GetXaxis()->SetTitle("Bin number");
  TLegend *leg  = new TLegend(0.6,0.8,0.9,0.9);
  leg->AddEntry(&g_mtx, "Response Matrix (NNLOPS)", "lp");
  leg->AddEntry(&g_binbybin, "Bin-By-Bin (NNLOPS)", "lp");

  leg->Draw();
  TLine prediction (g_mtx.GetXaxis()->GetXmin() ,1,g_mtx.GetXaxis()->GetXmax(),1);
  prediction.SetLineColor(kGray+1);
  prediction.SetLineWidth(2);
  prediction.SetLineStyle(2);

  prediction.Draw();
  

  c.SaveAs(("../ws_output/"+output+".pdf").c_str());
  
}



void getVector(string file, vector <double> *v){
  
  ifstream inFile ("../ws_output/"+file);
  
  if (!inFile) {
    cout << "file " << file << " NOT FOUND! exit" << endl;
    exit(0);
  }

  string dummy;
  int bin = 0;
  double val, up, down;
  
  while (true){
    if (bin ==0 ) inFile >> dummy >> dummy  >> dummy;
    else{
      inFile >> val >> up >> down;
      if( inFile.eof()) break;

      v->push_back(val);
      v->push_back(up);
      v->push_back(down);

 //     cout << val << "  " << up << " " <<  down << endl;
    }
    bin ++;
  }

}


void getVectorPrediction(string file, vector <double> *v){
 
  ifstream inFile ("../ws_output/"+file);
 
  if (!inFile) {
    cout << "file " << file << " NOT FOUND! exit" << endl;
    exit(0);
  }

  string dummy;
  int bin = 0;
  double val, up, down;
  cout << " ********** " << endl;
  while (true){
    if (bin ==0 ) inFile >>dummy >> dummy  ;
    else{  
      inFile >> val >> up ;
      if( inFile.eof()) break;
      v->push_back(val);
      v->push_back(0);
      v->push_back(0);
//      cout << val << "  " << up <<  endl;
      }
    bin ++;
  }

}
