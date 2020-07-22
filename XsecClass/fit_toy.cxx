#include "fit_toy.h"
#include <sstream>
#include <iostream>
#include "TH2.h"


using namespace RooFit;
using namespace RooStats;

using namespace std;


void fit_toy(  int ntoy = 10000,
	       TString fileName ="../ws_output/output.root",
	       TString outName = "../ws_output/toys.root",
	       int nbin = 15,
	       int theSeed=1 ) {

  TStopwatch cron;
  //setting seed
  rand_gen.SetSeed(theSeed);
  RooRandom::randomGenerator()->SetSeed(theSeed);

  
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;  
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting) ;
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization) ;   
  RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments) ;
  
  TFile* fcomb = new TFile(fileName);
  TFile *file = new TFile(outName,"RECREATE");

  RooWorkspace* w = (RooWorkspace*) fcomb->Get("myWS");
  SetNtupla(w);

  ModelConfig* mc = (ModelConfig*) w->obj("ModelConfig");
  w->var("m4l")->setBins(nbin);
  evalranges(w,mc);

  ToyMCSampler *toymcs= new ToyMCSampler();
  toymcs->SetPdf( *mc->GetPdf() );
  toymcs->SetObservables( *mc->GetObservables() );
  RooArgSet * allParams= (RooArgSet*) mc->GetObservables();
  RooDataSet * p_data = NULL;

  allParams->Print("v");

  mc->Print("v");
  cron.Start();
  float tmp_time = 0;
  for (int jj = 0;jj< ntoy; ++jj){
    if (jj%100 == 0){
      cout << jj << endl;
      cron.Stop();
      tmp_time += cron.RealTime();
      Timetoy = tmp_time;
      cron.Reset();
      cron.Start();
  
    }
    initializevar(w, mc);
    RooSimultaneous* pdf = (RooSimultaneous*) mc->GetPdf();
    p_data= (RooDataSet*) toymcs->GenerateToyData( *allParams );
    //p_data->Print();
    status_comb = mbutoFit(w, p_data, "sigma", "simPdf");
    m_event =  p_data->numEntries();
    
    //cout << poi.size() << endl;
    //cout << poi.at(0) << " " << poi.at(1) << " " << poi.at(2) << " " << poi.at(3) << " " << poi.at(4) << " " << poi.at(5) << " " << poi.at(6) << " " << poi.at(7) << " " << poi.at(8) << " " << poi.at(9) << " " << endl;

    Seed=theSeed;
    ToyNumber=jj;
    ToyTree->Fill();
  }
    
  cron.Stop();
    //TFile *file = new TFile(outName,"RECREATE");
  file->cd();
  ToyTree->Write();
  file->Close();
  fcomb->Close();
}

int mbutoFit (RooWorkspace *w, RooDataSet * p_data, TString var, TString pdfname){

  poi.clear();
  ModelConfig* mc = (ModelConfig*) w->obj("ModelConfig");
  //initializevar(w, mc);

  RooAbsReal* nll = NULL;
  RooMinimizer* minim= NULL;
  RooSimultaneous* pdf = (RooSimultaneous*) mc->GetPdf();

  nll=pdf->createNLL(*p_data, RooFit::CloneData(kFALSE), RooFit::Constrain(*mc->GetNuisanceParameters()), RooFit::Offset(kTRUE),RooFit::GlobalObservables(*mc->GetGlobalObservables()), RooFit::Verbose(kFALSE), RooFit::NumCPU(2, RooFit::Hybrid));

  minim = new RooMinimizer(*nll);
  //minim->setEps(0.01);
  minim->setPrintLevel(-1);
  minim->optimizeConst(2);
  minim->setStrategy(0);
  int fit = minim->minimize("Minuit2");
  
  RooRealVar *tmp;
  TIterator *iteratorPOI= mc->GetParametersOfInterest()->createIterator();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) poi.push_back(tmp->getVal());

  delete nll;
  delete minim;
  return fit;
}


void SetNtupla(RooWorkspace *w){
    
  ToyTree = new TTree ("ToyTree","ToyTree");
  
  ModelConfig* mc = (ModelConfig*) w->obj("ModelConfig");
  RooRealVar *tmp;
  
  int i =0;
  TIterator *iteratorPOI= mc->GetParametersOfInterest()->createIterator();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) {
    poi.push_back(-99);
    ++i;
  }
  
  i =0;
  iteratorPOI->Reset();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) {
    ToyTree->Branch(tmp->GetTitle(), &poi.at(i));
    ++i;
  }
  
  
  ToyTree->Branch("status_comb", &status_comb);
  ToyTree->Branch("event_comb", &m_event);
  ToyTree->Branch("Seed", &Seed);
  ToyTree->Branch("ToyNumber", &ToyNumber);
  ToyTree->Branch("time", &Timetoy);
  
  return;
}

void initializevar (RooWorkspace *w, RooStats::ModelConfig* mc){

  RooRealVar *tmp;
  int i=0;
  TIterator *iteratorPOI= mc->GetParametersOfInterest()->createIterator();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) {
    tmp->setRange(v_low.at(i),v_up.at(i));
    tmp->setVal(v_nominal.at(i));
    //tmp->Print();
    ++i;
  }

  return;
}

void evalranges (RooWorkspace* w, RooStats::ModelConfig* mc){
  
  RooFormulaVar * qqZZ =  NULL; //(RooFormulaVar*) w->obj("norm_bkg_bin6ggZZ");
  RooFormulaVar * ggZZ =  NULL; //(RooFormulaVar*) w->obj("norm_bkg_bin6ggZZ");

  RooFormulaVar * signal = NULL;
  int i = 0;
  double limitdown = 0;
  double limitup = 0;
  double nominal = 0;

  
  TIterator *iteratorPOI= mc->GetParametersOfInterest()->createIterator();
  while ( ((RooRealVar*)iteratorPOI->Next()) ) {
    qqZZ = (RooFormulaVar*) w->obj(("norm_bkg_bin"+std::to_string(i)+"qqZZ").c_str());
    ggZZ = (RooFormulaVar*) w->obj(("norm_bkg_bin"+std::to_string(i)+"ggZZ").c_str());
  
    limitdown = - ( qqZZ->getVal()+ ggZZ->getVal() - 0.00001 )/ ( (w->var("L")->getVal() * w->var(("BinWidth_bin"+std::to_string(i)+"qqZZ").c_str())->getVal() ) *  w->var("BRZZ")->getVal() *
                                                 (w->var(("rgg_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Agg_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Cgg_bin"+std::to_string(i)).c_str())->getVal()+
                                                  w->var(("rvbf_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Avbf_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Cvbf_bin"+std::to_string(i)).c_str())->getVal()+
                                                  w->var(("rwh_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Awh_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Cwh_bin"+std::to_string(i)).c_str())->getVal()+
                                                  w->var(("rzh_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Azh_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Czh_bin"+std::to_string(i)).c_str())->getVal()+
                                                  w->var(("rtth_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Atth_bin"+std::to_string(i)).c_str())->getVal() * w->var(("Ctth_bin"+std::to_string(i)).c_str())->getVal()) );
    cout << limitdown << endl;

    v_low.push_back( limitdown );
    v_nominal.push_back( w->var(("sigma_bin"+std::to_string(i)).c_str())->getVal() );
    v_up.push_back( w->var(("sigma_bin"+std::to_string(i)).c_str())->getVal()*2 );

    ++i;

  }
  
  
}


