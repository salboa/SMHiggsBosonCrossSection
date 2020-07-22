#include "MakeUnfoldPlots.h"
#include "MU_Style.cxx"
#include "MU_Utils.cxx"
#include "MU_Remap.cxx"
#include "MU_Graph.cxx"
#include <fstream>

class Options{
  
public:
  std::string Variable  ;
  std::string VarFitFile;
  std::string Mg5File   ;
  std::string Mg5File2  ;
  std::string ExpFile   ;
  std::string HresFile  ;
  std::string SysFile   ;
  bool        doFiducial;
  bool        Draw      ;
  bool        Normalized;
  bool        doN3LO    ;
  bool        debug     ;
  bool        doError   ;
  bool        isConf    ;
  bool        isPaper   ;
  void SetDefault(){
    Variable   = "pt";
    VarFitFile = "fit_y__wsysdata_TGunfolded.root";
    Mg5File    = "fxfx_1D_diffxsec_pdf_uncerts.root";
    Mg5File2   = "fxfx_1D_diffxsec_scale_uncerts.root";
    ExpFile    = "standard.root";
    HresFile   = "hres_pred.root";
    SysFile    = "fit_y__wsys_fixing_alldata_TGunfolded.root"; 
    doFiducial = false;
    debug      = false;
    Draw       = false;
    Normalized = false;
    doN3LO     = false;
    doError    = false;
    isConf     = false;
    isPaper    = false;
  }

  bool checkOpt(char* opt, char* value){
    std::string val = value;
    if( 0==val.find("-") ){
      std::cout << "WARNING:: Option " << opt <<
	" requires value -> skipping " << std::endl;
      return false;
    }
    return true;
  }
  
};

int main( int argc, char* argv[] ) {

  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
  RooMsgService::instance().getStream(1).removeTopic(Generation);
  RooMsgService::instance().getStream(1).removeTopic(Minimization);
  RooMsgService::instance().getStream(1).removeTopic(Plotting);
  RooMsgService::instance().getStream(1).removeTopic(Fitting);
  RooMsgService::instance().getStream(1).removeTopic(Integration);
  RooMsgService::instance().getStream(1).removeTopic(LinkStateMgmt);
  RooMsgService::instance().getStream(1).removeTopic(Eval);
  RooMsgService::instance().getStream(1).removeTopic(Caching);
  RooMsgService::instance().getStream(1).removeTopic(Optimization);
  RooMsgService::instance().getStream(1).removeTopic( ObjectHandling);
  RooMsgService::instance().getStream(1).removeTopic(InputArguments);
  RooMsgService::instance().getStream(1).removeTopic(Tracing);
  RooMsgService::instance().getStream(1).removeTopic(Contents);
  RooMsgService::instance().getStream(1).removeTopic(DataHandling);
  RooMsgService::instance().getStream(1).removeTopic(NumIntegration);
  gErrorIgnoreLevel = 1001;

  assert(argc>1);
  Options opt;
  opt.SetDefault();
  bool printHelp = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--Variable")        ){
      if( opt.checkOpt(argv[i],argv[i+1]) )     opt.Variable   = argv[i+1]; }
    else if( !strcmp(argv[i],"--VarFitFile") ){
      if( opt.checkOpt(argv[i],argv[i+1]) )     opt.VarFitFile = argv[i+1]; }
    else if( !strcmp(argv[i],"--Mg5File")    ){
      if( opt.checkOpt(argv[i],argv[i+1]) )     opt.Mg5File    = argv[i+1]; }
    else if( !strcmp(argv[i],"--Mg5File2")   ){
      if( opt.checkOpt(argv[i],argv[i+1]) )     opt.Mg5File2   = argv[i+1]; }
    else if( !strcmp(argv[i],"--ExpFile")    ){
      if( opt.checkOpt(argv[i],argv[i+1]) )     opt.ExpFile    = argv[i+1]; }
    else if( !strcmp(argv[i],"--HresFile")    ){
      if( opt.checkOpt(argv[i],argv[i+1]) )     opt.ExpFile    = argv[i+1]; }
    else if( !strcmp(argv[i],"--doFiducial") ){ opt.doFiducial = true;      }
    else if( !strcmp(argv[i],"--Draw")       ){ opt.Draw       = true;      }
    else if( !strcmp(argv[i],"--Normalized") ){ opt.Normalized = true;      }
    else if( !strcmp(argv[i],"--doN3LO") ){ opt.doN3LO = true;      }
    else if( !strcmp(argv[i],"--doError")    ){ opt.doError    = true;      }
    else if( !strcmp(argv[i],"--isConf")     ){ opt.isConf     = true;      }
    else if( !strcmp(argv[i],"--isPaper")    ){ opt.isPaper    = true;      }
    else if( !strcmp(argv[i],"--debug")      ){ opt.debug      = true;      }
    else if( !strcmp(argv[i],"--help")       ){ printHelp      = true;      }
  }
  if( printHelp ){
    std::cout << "<MakeUnfoldPlots()>:: make unfolded plots !!"                            << std::endl;
    std::cout << "  Usage  :  UnfoldPlots [Options]"                                       << std::endl;
    std::cout << "             --doFiducial [Run for Fiducial case: default is 'false']"   << std::endl;
    std::cout << "             --Variable   [define variable to plot: default 'y']"        << std::endl;
    std::cout << "             --VarFitFile [define variable fit file: default for 'y']"   << std::endl;
    std::cout << "             --Mg5File    [define MG5 input file: default set]"          << std::endl;
    std::cout << "             --Mg5File2   [define MG5 input file2: default set]"         << std::endl;
    std::cout << "             --ExpFile    [define Expected values file: default set]"    << std::endl;
    std::cout << "             --HresFile   [define HRes input file: default set]"         << std::endl;
    std::cout << "             --SysFile    [define Sys file: default for 'y'] "           << std::endl;
    std::cout << "             --Draw       [Enable Canvas on Screen: default is 'false']" << std::endl;
    std::cout << "             --Normalized [Normalized at same area: default is 'false']" << std::endl;
    std::cout << "             --doN3LO [Normalized at N3LO: default is 'false']" << std::endl;
    std::cout << "             --doError    [Derive r_bbH error: default is 'false']"      << std::endl;
    std::cout << "             --debug      [Set debug mode: default is 'false']"          << std::endl;
    std::cout << "             --help       [Print this help]"                             << std::endl;
    exit(0);
  }

  opt.VarFitFile = opt.Variable+"/fit_"+opt.Variable+"_binbybin___wsysdata_TGunfolded.root";
  opt.SysFile    = opt.Variable+"/fit_"+opt.Variable+"_binbybin___wsys_fixing_alldata_TGunfolded.root";
  m_Conf  = opt.isConf;
  m_Paper = opt.isPaper;

  std::cout << " <MakeUnfoldPlots()> :: Running with Options: "     << std::endl;
  std::cout << "                         doFiducial = " << opt.doFiducial << std::endl;
  std::cout << "                         Variable   = " << opt.Variable   << std::endl;
  std::cout << "                         VarFitFile = " << opt.VarFitFile << std::endl;
  std::cout << "                         Mg5File    = " << opt.Mg5File    << std::endl;
  std::cout << "                         Mg5File2   = " << opt.Mg5File2   << std::endl;
  std::cout << "                         ExpFile    = " << opt.ExpFile    << std::endl;
  std::cout << "                         HresFile   = " << opt.HresFile   << std::endl;
  std::cout << "                         SysFile    = " << opt.SysFile    << std::endl;
  std::cout << "                         Draw       = " << opt.Draw       << std::endl;
  std::cout << "                         Normalized = " << opt.Normalized << std::endl;
  std::cout << "                         doN3LO = " << opt.doN3LO << std::endl;
  std::cout << "                         doError    = " << opt.doError    << std::endl;
  std::cout << "                         debug      = " << opt.debug      << std::endl;

#ifdef WITHRINT
  TRint *myApp = new TRint("RootSession",&argc,argv,NULL,0);
  std::cout<<" Using Rint: Opening ROOT ..." << std::endl;
#else
  TApplication *myApp = new TApplication("myApp",0,0);
  std::cout<<" Using TApplication: Gui will be used ... " << std::endl;
#endif

  CheckOutDir();
  m_debug = opt.debug;

  if(opt.doFiducial)
    MakeFidUnfoldPlots(opt.ExpFile, opt.Draw);
  else if(opt.doError)
    DeriveError();
  else if(opt.Variable=="njetExt")
    MakeNjetExtended(opt.ExpFile, opt.Mg5File, opt.Mg5File2,
		     opt.Draw, opt.doN3LO);
  else
    MakeDiffUnfoldPlots(opt.Variable, opt.VarFitFile, opt.Mg5File,
			opt.Mg5File2, opt.ExpFile, opt.HresFile,
			opt.SysFile, opt.Draw, opt.Normalized, opt.debug,
			opt.doN3LO);
  
  /*Running GUI*/
  if(opt.Draw)
    myApp->Run();
  
  return 0;
  
}

void MakeFidUnfoldPlots(std::string expFile, bool keepCanvas){

  SetAtlasStyle();
  
  TFile *_file0 = new TFile( ("./expected/"+expFile).c_str()                           );
  TFile *_file1 = new TFile( "../ws_output/m/fit_m_fidchannel_binbybin___wsysdata_TGunfolded.root" );
  TFile *_file2 = new TFile( "../ws_output/m/fit_m_fidsum_binbybin___wsysdata_TGunfolded.root"     );
  TFile *_file3 = new TFile( "../ws_output/m/fit_m_fid4l_binbybin___wsysdata_TGunfolded.root"      );
  TFile *_file4 = new TFile( "../ws_output/m/fit_m_fid2l2l_binbybin___wsysdata_TGunfolded.root"    );
  TFile *_file5 = new TFile( "../ws_output/m/fit_m_total_binbybin___wsysdata_TGunfolded.root"      );
  TFile *_file6 = new TFile( "../ws_output/m/fit_m_comb_binbybin___wsysdata_TGunfolded.root"       );

  TFile *_file1sys = new TFile( "../ws_output/m/fit_m_fidchannel_binbybin___wsys_fixing_alldata_TGunfolded.root" );
  TFile *_file2sys = new TFile( "../ws_output/m/fit_m_fidsum_binbybin___wsys_fixing_alldata_TGunfolded.root"     );
  TFile *_file3sys = new TFile( "../ws_output/m/fit_m_fid4l_binbybin___wsys_fixing_alldata_TGunfolded.root"      );
  TFile *_file4sys = new TFile( "../ws_output/m/fit_m_fid2l2l_binbybin___wsys_fixing_alldata_TGunfolded.root"    );
  TFile *_file5sys = new TFile( "../ws_output/m/fit_m_total_binbybin___wsys_fixing_alldata_TGunfolded.root"      );
  TFile *_file6sys = new TFile( "../ws_output/m/fit_m_comb_binbybin___wsys_fixing_alldata_TGunfolded.root"       );

  TFile *_expTGfile1 = new TFile( "../ws_output/m/fit_m_fidchannel_binbybin__expected_TGunfolded.root" );
  TFile *_expTGfile2 = new TFile( "../ws_output/m/fit_m_fidsum_binbybin__expected_TGunfolded.root"     );
  TFile *_expTGfile3 = new TFile( "../ws_output/m/fit_m_fid4l_binbybin__expected_TGunfolded.root"      );
  TFile *_expTGfile4 = new TFile( "../ws_output/m/fit_m_fid2l2l_binbybin__expected_TGunfolded.root"    );
  TFile *_expTGfile5 = new TFile( "../ws_output/m/fit_m_total_binbybin__expected_TGunfolded.root"      );
  TFile *_expTGfile6 = new TFile( "../ws_output/m/fit_m_comb_binbybin__expected_TGunfolded.root"       );


  TCanvas *c = new TCanvas( "Fiducial", "Fiducial", 600, 600 );

  std::vector<TGraphAsymmErrors*> Obs, ObsSys;

  TGraphAsymmErrors *obsChan = (TGraphAsymmErrors*)_file1->Get( "m_fidchannel" );
  TGraphAsymmErrors *obsSum  = (TGraphAsymmErrors*)_file2->Get( "m_fidsum"     );
  TGraphAsymmErrors *obs4l   = (TGraphAsymmErrors*)_file3->Get( "m_fid4l"      );
  TGraphAsymmErrors *obs2l2l = (TGraphAsymmErrors*)_file4->Get( "m_fid2l2l"    );
  TGraphAsymmErrors *obsTot  = (TGraphAsymmErrors*)_file5->Get( "m_total"      );
  TGraphAsymmErrors *obsComb = (TGraphAsymmErrors*)_file6->Get( "m_comb"       );

  TGraphAsymmErrors *expTGChan = (TGraphAsymmErrors*)_expTGfile1->Get( "m_fidchannel" );
  TGraphAsymmErrors *expTGSum  = (TGraphAsymmErrors*)_expTGfile2->Get( "m_fidsum"     );
  TGraphAsymmErrors *expTG4l   = (TGraphAsymmErrors*)_expTGfile3->Get( "m_fid4l"      );
  TGraphAsymmErrors *expTG2l2l = (TGraphAsymmErrors*)_expTGfile4->Get( "m_fid2l2l"    );
  TGraphAsymmErrors *expTGTot  = (TGraphAsymmErrors*)_expTGfile5->Get( "m_total"      );
  TGraphAsymmErrors *expTGComb = (TGraphAsymmErrors*)_expTGfile6->Get( "m_comb"       );

  Obs.push_back( obsChan );
  Obs.push_back( obsSum  );
  Obs.push_back( obs4l   );
  Obs.push_back( obs2l2l );
  Obs.push_back( obsTot  );
  Obs.push_back( obsComb );
  
  TGraphAsymmErrors *obsSysChan = (TGraphAsymmErrors*)_file1sys->Get( "m_fidchannel" );
  TGraphAsymmErrors *obsSysSum  = (TGraphAsymmErrors*)_file2sys->Get( "m_fidsum"     );
  TGraphAsymmErrors *obsSys4l   = (TGraphAsymmErrors*)_file3sys->Get( "m_fid4l"      );
  TGraphAsymmErrors *obsSys2l2l = (TGraphAsymmErrors*)_file4sys->Get( "m_fid2l2l"    );
  TGraphAsymmErrors *obsSysTot  = (TGraphAsymmErrors*)_file5sys->Get( "m_total"      );
  TGraphAsymmErrors *obsSysComb = (TGraphAsymmErrors*)_file6sys->Get( "m_comb"       );

  ObsSys.push_back( obsSysChan );
  ObsSys.push_back( obsSysSum  );
  ObsSys.push_back( obsSys4l   );
  ObsSys.push_back( obsSys2l2l );
  ObsSys.push_back( obsSysTot  );
  ObsSys.push_back( obsSysComb );
  
  TH1F *ref = (TH1F*)_file0->Get( "fid_ggHNNLOPS" ); ref->Reset(); ref->SetName( "ref"  );
  TH1F *up  = (TH1F*)_file0->Get( "fid_ggHNNLOPS" );  up->Reset();  up->SetName( "up"   );
  TH1F *dw  = (TH1F*)_file0->Get( "fid_ggHNNLOPS" );  dw->Reset();  dw->SetName( "down" );

  m_YR4error = totalXS("N3LO");

  std::vector<TH1F*> *nnlops   = new std::vector<TH1F*>();
  std::vector<TH1F*> *nnlopsUp = new std::vector<TH1F*>();
  std::vector<TH1F*> *nnlopsDw = new std::vector<TH1F*>();

  makehisto( nnlops, nnlopsUp, nnlopsDw, _file0, false, "fid", ref );
  makeSys( nnlops, nnlopsUp, nnlopsDw, ref, up, dw );

  Double_t Vals[] = { 0.0, 0.3, 1.3, 2.3, 3.3, 4.3,  // bins 1, 2 ,3  4, 5
		      5.8, 6.1, 7.1, 8.1, 9.1,       // bins 6, 7, 8, 9, 10
		      10.1, 11.6, 11.9, 12.9, 15 ,16.2}; // bins 11, 12, 13, 14

  Int_t Nbins = ( (sizeof Vals) / (sizeof *Vals) )-1;
  std::vector<double> xVal;
  for(int i=0; i<Nbins; i++){
    xVal.push_back(Vals[i]);
  }
    
  TH1F* nom   = new TH1F( "nom", "nom", Nbins, Vals );
  TH1F* upV   = new TH1F( "upV", "upV", Nbins, Vals );
  TH1F* dwV   = new TH1F( "dwV", "dwV", Nbins, Vals );

  TH1F* nom_b = new TH1F( "nom_b", "nom_b", Nbins, Vals );
  TH1F* upV_b = new TH1F( "upV_b", "upV_b", Nbins, Vals );
  TH1F* dwV_b = new TH1F( "dwV_b", "dwV_b", Nbins, Vals );

  TH1F* nom_c = new TH1F( "nom_c", "nom_c", Nbins, Vals );
  TH1F* upV_c = new TH1F( "upV_c", "upV_c", Nbins, Vals );
  TH1F* dwV_c = new TH1F( "dwV_c", "dwV_c", Nbins, Vals );
  
  TH1F* nom_d = new TH1F( "nom_d", "nom_d", Nbins, Vals );
  TH1F* upV_d = new TH1F( "upV_d", "upV_d", Nbins, Vals );
  TH1F* dwV_d = new TH1F( "dwV_d", "dwV_d", Nbins, Vals );
  
  
  /* 1 -> 4mu, 2 -> 4e, 3 -> 2mu2e, 4 -> 2e2mu */
  for(int i=0; i<Nbins; i++){

    if(i>0 && i<5){
      nom->SetBinContent( i+1, ref->GetBinContent(i) );
      upV->SetBinContent( i+1, up->GetBinContent(i)  );
      dwV->SetBinContent( i+1, dw->GetBinContent(i)  );
    }
    else if(i==7){
      nom->SetBinContent( i+1, ref->GetBinContent(1)+ref->GetBinContent(2) );
      upV->SetBinContent( i+1, up->GetBinContent(1)+up->GetBinContent(2)   );
      dwV->SetBinContent( i+1, dw->GetBinContent(1)+dw->GetBinContent(2)   );
    }
    else if(i==8){
      nom->SetBinContent( i+1, ref->GetBinContent(3)+ref->GetBinContent(4) );
      upV->SetBinContent( i+1, up->GetBinContent(3)+up->GetBinContent(4)   );
      dwV->SetBinContent( i+1, dw->GetBinContent(3)+dw->GetBinContent(4)   );
    }
    else if(i==9 || i==10){
      nom->SetBinContent( i+1, (ref->GetBinContent(1)+ref->GetBinContent(2)+
				ref->GetBinContent(3)+ref->GetBinContent(4)) );
      upV->SetBinContent( i+1, (up->GetBinContent(1)+up->GetBinContent(2)+
				up->GetBinContent(3)+up->GetBinContent(4))   );
      dwV->SetBinContent( i+1, (dw->GetBinContent(1)+dw->GetBinContent(2)+
				dw->GetBinContent(3)+dw->GetBinContent(4))   );
    }
    else if(i==13){
      std::vector<float> v_totalXS = totalXS("N3LO"); /// true = N3LO, false = NNLO+NNLL
      nom->SetBinContent( i+1,  v_totalXS.at(0)/20.);
      upV->SetBinContent( i+1,  v_totalXS.at(1)/20.);
      dwV->SetBinContent( i+1,  v_totalXS.at(2)/20.);

      v_totalXS.clear();
      v_totalXS = totalXS("N2LO"); /// true = N3LO, false = NNLO+NNLL
      nom_b->SetBinContent( i+1,  v_totalXS.at(0)/20.);
      upV_b->SetBinContent( i+1,  v_totalXS.at(1)/20.);
      dwV_b->SetBinContent( i+1,  v_totalXS.at(2)/20.);
      
      v_totalXS.clear();
      v_totalXS = totalXS("MG5"); /// true = N3LO, false = NNLO+NNLL
      nom_c->SetBinContent( i+1,  v_totalXS.at(0)/20.);
      upV_c->SetBinContent( i+1,  v_totalXS.at(1)/20.);
      dwV_c->SetBinContent( i+1,  v_totalXS.at(2)/20.);
      
      v_totalXS.clear();
      v_totalXS = totalXS("NNLOPS"); /// true = N3LO, false = NNLO+NNLL
      nom_d->SetBinContent( i+1,  v_totalXS.at(0)/20.);
      upV_d->SetBinContent( i+1,  v_totalXS.at(1)/20.);
      dwV_d->SetBinContent( i+1,  v_totalXS.at(2)/20.);
      
    }
    
  }
  
  TGraphAsymmErrors *exp    = makeTGraph(nom,upV,dwV,"ExpectedFid",true);
  TGraphAsymmErrors *exp_b  = makeTGraph(nom_b,upV_b,dwV_b,"ExpectedFid_b",true);
  TGraphAsymmErrors *exp_c  = makeTGraph(nom_c,upV_c,dwV_c,"ExpectedFid_c",true);
  TGraphAsymmErrors *exp_d  = makeTGraph(nom_d,upV_d,dwV_d,"ExpectedFid_d",true);
  TGraphAsymmErrors *obs    = makeGraph(Obs, "Observed", xVal, true);
  
  double xx, yy, tmp, useless, ratioval, yy2;

  exp->GetPoint(13,xx,yy);
  exp->SetPoint(13,xx+0.75,yy); exp->SetPointError(13,0.2, 0.2, exp->GetErrorYlow(13),exp->GetErrorYhigh(13));
  exp->Print();

  exp->GetPoint(1,xx,tmp);
  expTGChan->GetPoint(0,useless,yy);
  expTGChan->GetPoint(1,useless,yy2);
  yy=0.5*(yy+yy2);
  ratioval=tmp/yy; 
  exp->SetPoint(1,xx, yy*2.5);
  exp->SetPointError(1, exp->GetErrorXlow(1), exp->GetErrorXhigh(1), yy*2.5*0.0445, yy*2.5*0.0445);

  exp->GetPoint(2,xx,tmp);
  expTGChan->GetPoint(1,useless,yy);
  expTGChan->GetPoint(0,useless,yy2);
  yy=0.5*(yy+yy2);
  ratioval=tmp/yy; 
  exp->SetPoint(2,xx, yy*2.5);
  exp->SetPointError(2, exp->GetErrorXlow(2), exp->GetErrorXhigh(2), yy*2.5*0.0445, yy*2.5*0.0445);

  exp->GetPoint(3,xx,useless);
  expTGChan->GetPoint(2,useless,yy);
  exp->SetPoint(3,xx, yy*2.5);
  exp->SetPointError(3, exp->GetErrorXlow(2), exp->GetErrorXhigh(2), yy*2.5*0.0445, yy*2.5*0.0445);

  exp->GetPoint(4,xx,useless);
  expTGChan->GetPoint(3,useless,yy);
  exp->SetPoint(4,xx, yy*2.5);
  exp->SetPointError(4, exp->GetErrorXlow(2), exp->GetErrorXhigh(2), yy*2.5*0.0445, yy*2.5*0.0445);

  exp->GetPoint(7,xx,useless);
  expTG4l->GetPoint(0,useless,yy);
  exp->SetPoint(7,xx, yy);
  exp->SetPointError(7, exp->GetErrorXlow(1), exp->GetErrorXhigh(1), yy*0.0445, yy*0.0445);

  exp->GetPoint(8,xx,useless);
  expTG2l2l->GetPoint(0,useless,yy);
  exp->SetPoint(8,xx, yy);
  exp->SetPointError(8, exp->GetErrorXlow(1), exp->GetErrorXhigh(1), yy*0.0445, yy*0.0445);


  exp->GetPoint(9,xx,useless);
  expTGSum->GetPoint(0,useless,yy);
  exp->SetPoint(9,xx, yy);
  exp->SetPointError(9, exp->GetErrorXlow(1), exp->GetErrorXhigh(1), yy*0.0445, yy*0.0445);

  exp->GetPoint(10,xx,useless);
  expTGComb->GetPoint(0,useless,yy);
  exp->SetPoint(10,xx, yy);
  exp->SetPointError(10, exp->GetErrorXlow(1), exp->GetErrorXhigh(1), yy*0.0445, yy*0.0445);





  exp_b->GetPoint(13,xx,yy);
  exp_b->SetPoint(13,xx+3.,yy); exp_b->SetPointError(13,0.2, 0.2, exp_b->GetErrorYlow(13),exp_b->GetErrorYhigh(13));

  exp_c->GetPoint(13,xx,yy);
  exp_c->SetPoint(13,xx+1.5,yy); exp_c->SetPointError(13,0.2, 0.2, exp_c->GetErrorYlow(13),exp_c->GetErrorYhigh(13));
  
  exp_d->GetPoint(13,xx,yy);
  exp_d->SetPoint(13,xx+2.25,yy); exp_d->SetPointError(13,0.2, 0.2, exp_d->GetErrorYlow(13),exp_d->GetErrorYhigh(13));

  TGraphAsymmErrors *obsSys = makeSysGraph(Obs, ObsSys, "Observed", xVal, true);
  std::cout << " ******************* " << std::endl; 
  exp->Print();
  std::cout << " ******************* " << std::endl; 
  exp_b->Print();
  std::cout << " ******************* " << std::endl; 
  exp_c->Print();
  std::cout << " ******************* " << std::endl; 
  exp_d->Print();

  std::cout << " ******************* " << std::endl; 
  TH1F* dummy = (TH1F*)nom->Clone("dummy");
  dummy->Reset();
  dummy->SetLineColor(0);
  dummy->GetXaxis()->SetRangeUser( dummy->GetXaxis()->GetXmin(),
				   dummy->GetXaxis()->GetXmax() );
  dummy->GetYaxis()->SetRangeUser(0.0001, 7.5);
  dummy->GetXaxis()->SetBinLabel( 1 , " "                                   );
  dummy->GetXaxis()->SetBinLabel( 2 , "#scale[0.6]{#sigma_{4#mu}^{fid}}"          );
  dummy->GetXaxis()->SetBinLabel( 3 , "#scale[0.6]{#sigma_{4e}^{fid}}"            );
  dummy->GetXaxis()->SetBinLabel( 4 , "#scale[0.6]{#sigma_{2#mu2e}^{fid}}"        );
  dummy->GetXaxis()->SetBinLabel( 5 , "#scale[0.6]{#sigma_{2e2#mu}^{fid}}"        );
  dummy->GetXaxis()->SetBinLabel( 6 , " "                                   );
  dummy->GetXaxis()->SetBinLabel( 7 , " "                                   );
  dummy->GetXaxis()->SetBinLabel( 8 , "#scale[0.6]{#sigma_{4#mu+4e}^{fid}}"       );
  dummy->GetXaxis()->SetBinLabel( 9 , "#scale[0.6]{#sigma_{2#mu2e+2e2#mu}^{fid}}" );
  dummy->GetXaxis()->SetBinLabel( 10, "#scale[0.6]{#sigma_{4#font[12]{l} (sum)}^{fid}}"           );
  dummy->GetXaxis()->SetBinLabel( 11, "#scale[0.6]{#sigma_{4#font[12]{l} (comb)}^{fid}}"          );
  dummy->GetXaxis()->SetBinLabel( 12, " "                                   );
  dummy->GetXaxis()->SetBinLabel( 13, " "                                   );
  dummy->GetXaxis()->SetBinLabel( 14, " "         );
  dummy->GetXaxis()->SetBinLabel( 15, "#scale[0.6]{#sigma_{H}}"                                   );
  dummy->GetYaxis()->SetTitleOffset(1.4);
  dummy->GetXaxis()->SetLabelSize(0.07);
  dummy->GetXaxis()->SetLabelOffset(0.013);
  dummy->GetXaxis()->SetTickLength(0.);
  dummy->GetYaxis()->CenterTitle(kTRUE);
  dummy->GetYaxis()->SetNdivisions(000);
  //dummy->LabelsOption("v","X");
  c->cd();
  
  TLegend *leg = CreateLegend("",true);
  dummy->Draw();

  TGaxis *LeftAx = new TGaxis(0,0,0,4.8,0,1.92,510,"");
  LeftAx->SetName("leftAx");
  LeftAx->SetLabelSize(0.028);
  LeftAx->SetLabelFont(42);
  LeftAx->SetTitle("Cross section [fb]");
  LeftAx->SetTitleSize(0.035);
  LeftAx->SetTitleOffset(1.1);
  LeftAx->SetTitleFont(42);
  LeftAx->ChangeLabel(1,-1,-1,-1,-1,-1," ");
  LeftAx->Draw();

  TGaxis *CenterAx = new TGaxis(5.8,0,5.8,4.8,0,4.8,510,"");
  CenterAx->SetName("CenterAx");
  CenterAx->SetLabelSize(0.028);
  CenterAx->SetLabelFont(42);
  CenterAx->SetTitle("[fb]");
  CenterAx->SetTitleSize(0.035);
  CenterAx->SetTitleOffset(1.1);
  CenterAx->SetTitleFont(42);
  CenterAx->ChangeLabel(1,-1,-1,-1,-1,-1," ");
  CenterAx->Draw();

  TGaxis *RightAx = new TGaxis(11.6,0,11.6,4.8,0,95,510,"");
  RightAx->SetName("RightAx");
  RightAx->SetLabelSize(0.028);
  RightAx->SetLabelFont(42);
  RightAx->SetTitle("[pb]");
  RightAx->SetTitleSize(0.035);
  RightAx->SetTitleOffset(1.0);
  RightAx->SetTitleFont(42);
  RightAx->ChangeLabel(1,-1,-1,-1,-1,-1," ");
  RightAx->Draw();
  
  exp->SetFillColor(kRed-10);
  exp->SetLineStyle(1);
  exp->SetLineColor(kRed-10);
  exp->SetMarkerColor(kRed);
  exp->SetMarkerSize(0.8);
  exp->SetMarkerStyle(21);
  exp->Draw("2,same");
  exp->Draw("pX,same");
  
  exp_b->SetFillColor(kGreen-8);
  exp_b->SetLineStyle(1);
  exp_b->SetLineColor(kGreen-8);
  exp_b->SetMarkerColor(kGreen+3);
  exp_b->SetMarkerSize(0.8);
  exp_b->SetMarkerStyle(22);
  
  exp_c->SetFillColor(kBlue-10);
  exp_c->SetLineStyle(1);
  exp_c->SetLineColor(kBlue-10);
  exp_c->SetMarkerColor(kBlue);
  exp_c->SetMarkerSize(1.1);
  exp_c->SetMarkerStyle(33);
  
  exp_d->SetFillColor(kOrange-4);
  exp_d->SetLineStyle(1);
  exp_d->SetLineColor(kOrange-4);
  exp_d->SetMarkerColor(kOrange+2);
  exp_d->SetMarkerSize(1.1);
  exp_d->SetMarkerStyle(34);
  
  
  
  exp_b->Draw("2,same");
  exp_b->Draw("pX,same");
  
  exp_c->Draw("2,same");
  exp_c->Draw("pX,same");
  
  exp_d->Draw("2,same");
  exp_d->Draw("pX,same");
  
  
  
  setStyle("NNLOPSexp",nom);
  obs->SetMarkerSize(0.7);
  obsSys->SetLineColor(kBlack);
  obsSys->SetFillColor(kWhite);
  obsSys->SetFillStyle(0);
  obsSys->SetMarkerSize(0.);
  obs->SetMarkerStyle(20);
  obsSys->SetLineWidth(1);
  obs->SetLineWidth(2);
  
  obsSys->Draw("e5");
  obs->Draw("pez");
  leg->AddEntry(obs, "Data", "pez");
  leg->AddEntry(obsSys, "Syst. uncertainties", "f");
  leg->AddEntry(exp, "SM (ggF @N3LO + XH)", "pf");
  leg->AddEntry(exp_c,"MG5 FxFx + XH","pf");
  leg->AddEntry(exp_d,"NNLOPS + XH","pf");
  leg->AddEntry(exp_b,"HRes 2.3, NNLO+NNLL + XH","pf");
  drawLabels(true);
  leg->SetY1(0.72);
  leg->Draw();


  std::vector<double> exp_SM_XS;

  for (int i =0; i < exp->GetN();++i){
    float scale =1;
    if (i<5) scale=2.5;
    if (i>10) scale = 1./20000;
    double x, y;
    exp->GetPoint(i,x,y);
    
    if (y!=0){
      exp_SM_XS.push_back(y/scale);
    }
  }
  
  evalPValueFid(exp_SM_XS);
  
  
  c->SaveAs( (m_OutDir+"fit_fiducial_data_unfolded.pdf").c_str() );
  c->SaveAs( (m_OutDir+"fit_fiducial_data_unfolded.eps").c_str() );
  c->SaveAs( (m_OutDir+"fit_fiducial_data_unfolded.C").c_str() );
  
  /* Cleaning */
  /* if(!keepCanvas) delete c;
     _file0->Close();
     _file1->Close();
     _file2->Close();
     _file3->Close();
     _file4->Close();
     _file5->Close();
     _file6->Close();
     _file1sys->Close();
     _file2sys->Close();
     _file3sys->Close();
     _file4sys->Close();
     _file5sys->Close();
     _file6sys->Close(); 
  */

}

void MakeDiffUnfoldPlots(std::string var, std::string varFile,
			 std::string mgFile, std::string mgFile2,
			 std::string expFile, std::string HresFile,
			 std::string sysFile, bool keepCanvas,
			 bool normalized, bool debug, bool doN3LO ){
  m_debug = debug;
  m_Var = var;
  
  
  if(var=="njetv4"){
    expFile="standard_njet.root";
  }
  m_doN3LO = doN3LO;
  
  std::map<std::string, std::string> remapping;
  remapping["pt"]     = "higgs_pt_fidDres_4lsel";
  remapping["y"]      = "higgs_y_fidDres_4lsel";
  remapping["cts"]    = "cthstr_fidDres_4lsel";
  remapping["njet"]   = "n_jets_fidDres_4lsel";
  remapping["nbjet"]  = "n_bjets_fidDres_4lsel";
  remapping["m12"]    = "Z1_m_fidDres_4lsel";
  remapping["m34"]    = "Z2_m_fidDres_4lsel";
  remapping["ljpt"]   = "leading_jet_pt_fidDres_4lsel";
  remapping["mjj"]    = "dijet_m_fidDres_4lsel";
  remapping["etajj"]  = "dijet_deltaeta_fidDres_4lsel";
  remapping["phijj"]  = "dijet_deltaphi_fidDres_4lsel";
  remapping["pt0j"]   = "n_jets_fidDres_4lsel_higgs_pt_fidDres_4lsel_nj_0";  
  remapping["pt1j"]   = "n_jets_fidDres_4lsel_higgs_pt_fidDres_4lsel_nj_1";  
  remapping["pt2j"]   = "n_jets_fidDres_4lsel_higgs_pt_fidDres_4lsel_nj_geq2";
  remapping["m12m34"] = "Z1_m_fidDres_4lsel_Z2_m_fidDres_4lsel";
  remapping["njetv4"] = "n_jetsv4_fidDres_4lsel";
  
  
  std::map<std::string, std::string> remappingHres;
  remappingHres["y"]  = "y_nom";
  remappingHres["yup"]  = "y_up";
  remappingHres["ydown"]  = "y_dw";
  remappingHres["pt"] = "pt_nom";
  remappingHres["ptup"] = "pt_up";
  remappingHres["ptdown"] = "pt_dw";

  SetAtlasStyle();
  
  if (var=="m12m34" || var == "pt0j" || var == "pt1j" || var == "pt2j"){
    mgFile  = "fxfx_2D_diffxsec_pdf_uncerts_merged.root";
    mgFile2 = "fxfx_2D_diffxsec_scale_uncerts_merged.root";
  }
  if(var=="pt0j"||var=="pt1j"||var=="pt2j"){
    varFile = "fit_ptpt__wsysdata_TGunfolded.root";
    sysFile = "fit_ptpt__wsys_fixing_alldata_TGunfolded.root";
  }
  if(var=="njetv4"){
    mgFile  = "fxfx_1D_diffxsec_pdf_njetincl_uncerts.root";
    mgFile2 = "fxfx_1D_diffxsec_scale_njetincl_uncerts.root";
  }
  std::cout << mgFile << std::endl;
  
  std::vector<TH1F*> *mgvector         = new std::vector<TH1F*>();
  std::vector<TH1F*> *mgupvector       = new std::vector<TH1F*>();
  std::vector<TH1F*> *mgdownvector     = new std::vector<TH1F*>();
  std::vector<TH1F*> *nnlopsvector     = new std::vector<TH1F*>();
  std::vector<TH1F*> *nnlopsupvector   = new std::vector<TH1F*>();
  std::vector<TH1F*> *nnlopsdownvector = new std::vector<TH1F*>();
  std::vector<TH1F*> *hresvector       = new std::vector<TH1F*>();
  std::vector<TH1F*> *hresupvector     = new std::vector<TH1F*>();
  std::vector<TH1F*> *hresdownvector   = new std::vector<TH1F*>();
  
  std::vector<TH1F*> *gosamvector         = new std::vector<TH1F*>();
  std::vector<TH1F*> *gosamupvector       = new std::vector<TH1F*>();
  std::vector<TH1F*> *gosamdownvector     = new std::vector<TH1F*>();
  
  std::vector<TH1F*> *restvector       = new std::vector<TH1F*>();
  std::vector<TH1F*> *restupvector     = new std::vector<TH1F*>();
  std::vector<TH1F*> *restdownvector   = new std::vector<TH1F*>();

  TString nameExp = varFile;
  nameExp.ReplaceAll("_wsysdata","expected");
  TFile *_Expfile0        = new TFile( ("../ws_output/"+(std::string)nameExp.Data()).c_str() );
  TGraphAsymmErrors *TGexpected = (TGraphAsymmErrors*)_Expfile0->Get(var.c_str());
  TFile *_file0        = new TFile( ("../ws_output/"+varFile).c_str() );
  TFile *_file0sys     = new TFile( ("../ws_output/"+sysFile).c_str() );
  TFile *_file1        = new TFile( ("./expected/"+mgFile).c_str()    );
  TFile *_file1b       = new TFile( ("./expected/"+mgFile2).c_str()   );
  TFile *_file2        = new TFile( ("./expected/"+expFile).c_str()   );
  TFile *_filehres     = new TFile( ("./expected/"+HresFile).c_str()  );
 
  _Expfile0->Print();
  TCanvas *c = new TCanvas( var.c_str(), var.c_str(), 600, 600 );

  TGraphAsymmErrors *obs = NULL, *obssys = NULL;
  
  m_YR4error = totalXS("N3LO");
  
  std::cout << std::endl << "Variable:  " << var.c_str() << std::endl;
  TGraphAsymmErrors *exp_ratio_xsMG     = new TGraphAsymmErrors();
  TGraphAsymmErrors *exp_ratio_xsNNLOPS = new TGraphAsymmErrors();
  TGraphAsymmErrors *exp_ratio_xsHRES   = new TGraphAsymmErrors();

  TH1F *mgexpected_ggH = NULL;
  if (var=="m12m34" || var == "pt0j" ||
      var == "pt1j" || var == "pt2j"  )
    mgexpected_ggH=(TH1F*)_file1->Get( (remapping[var]+"_nom").c_str() );
//  else
//    mgexpected_ggH=(TH1F*)_file1->Get( (remapping[var]+"_nominal").c_str() );

  if (var=="pt")
	 mgexpected_ggH= new TH1F(var.c_str(), var.c_str(),11,0,11 );

  if (var=="njet")
         mgexpected_ggH= new TH1F(var.c_str(), var.c_str(),5,0,5 );
  TH1F *mgexpected_ggH2 = (TH1F*)mgexpected_ggH->Clone("mg2"); 
  TH1F *mgexpected_ggHUppdf     = (TH1F*)_file1->Get(  (remapping[var]+"_pdf_up").c_str()     );
  TH1F *mgexpected_ggHDownpdf   = (TH1F*)_file1->Get(  (remapping[var]+"_pdf_down").c_str()   );
  TH1F *mgexpected_ggHUpscale   = (TH1F*)_file1b->Get( (remapping[var]+"_scale_up").c_str()   );
  TH1F *mgexpected_ggHDownscale = (TH1F*)_file1b->Get( (remapping[var]+"_scale_down").c_str() );
  
  std::cout << mgexpected_ggH << std::endl;
  if (m_doN3LO){
    double scaleMG= 48580*1.25E-04	/4.1138;
    std::cout << mgexpected_ggH ->Integral() << std::endl;
    mgexpected_ggH->Scale(scaleMG);
    mgexpected_ggHUppdf->Scale(scaleMG);
    mgexpected_ggHDownpdf->Scale(scaleMG);
    mgexpected_ggHUpscale->Scale(scaleMG);
    mgexpected_ggHDownscale->Scale(scaleMG);
  }
  
  mgvector->push_back(mgexpected_ggH);
  mgupvector->push_back(mgexpected_ggHUppdf);	 
  mgdownvector->push_back(mgexpected_ggHDownpdf);
  mgupvector->push_back(mgexpected_ggHUpscale);	
  mgdownvector->push_back(mgexpected_ggHDownscale);


  TH1F *hresexpected_ggH = NULL, *hres = NULL, *hresup = NULL, *hresdown = NULL;
  TH1F *hresexpected_ggHvarup = NULL;
  TH1F *hresexpected_ggHvardown = NULL;
  
  TH1F* gosamexp_ggH= NULL, *hgosam = NULL, *hgosamup = NULL, *hgosamdown = NULL;
  TH1F* gosamexp_ggHup= NULL;
  TH1F* gosamexp_ggHdown= NULL;
  
  if(var=="njetv4"){
    gosamexp_ggH=(TH1F*)_file2->Get("Nom_gosam"); gosamexp_ggH->Print();
    gosamexp_ggHup=(TH1F*)_file2->Get("Up_gosam");
    gosamexp_ggHdown=(TH1F*)_file2->Get("Down_gosam");
    
    gosamvector->push_back(gosamexp_ggH);
    gosamupvector->push_back(gosamexp_ggHup);
    gosamupvector->push_back(gosamexp_ggH);
    gosamdownvector->push_back(gosamexp_ggHdown);
    gosamdownvector->push_back(gosamexp_ggH);
    
    hgosam    = (TH1F*)mgexpected_ggH->Clone("hgosam");      hgosam->Reset();
    hgosamup   = (TH1F*)mgexpected_ggH->Clone("hgosamup");    hgosamup->Reset();
    hgosamdown = (TH1F*)mgexpected_ggH->Clone("hgosamdown");  hgosamdown->Reset();
    
  }
  if (var=="y" || var=="pt") {

    hresexpected_ggH = (TH1F*)_filehres->Get( (remappingHres[var]).c_str()  );
    hresexpected_ggHvarup = (TH1F*)_filehres->Get( (remappingHres[var+"up"]).c_str()  );
    hresexpected_ggHvardown = (TH1F*)_filehres->Get( (remappingHres[var+"down"]).c_str()  );
    
    if (m_doN3LO){
      double scaleHRes=       2.91014/2.74937;
      hresexpected_ggH->Scale(scaleHRes);
      hresexpected_ggHvarup->Scale(scaleHRes);
      hresexpected_ggHvardown->Scale(scaleHRes);
    }

    hresvector->push_back(hresexpected_ggH);
    hresupvector->push_back(hresexpected_ggHvarup);
    hresupvector->push_back(hresexpected_ggH);
    hresdownvector->push_back(hresexpected_ggHvardown);
    hresdownvector->push_back(hresexpected_ggH);
    
    hres     = (TH1F*)mgexpected_ggH->Clone("hres");      hres->Reset();
    hresup   = (TH1F*)mgexpected_ggH->Clone("hresup");    hresup->Reset();
    hresdown = (TH1F*)mgexpected_ggH->Clone("hresdown");  hresdown->Reset();
  }

  TH1F* nnlops     = (TH1F*)mgexpected_ggH->Clone("nnlops");     nnlops->Reset();
  TH1F* nnlopsup   = (TH1F*)mgexpected_ggH->Clone("nnlopsup");   nnlopsup->Reset();
  TH1F* nnlopsdown = (TH1F*)mgexpected_ggH->Clone("nnlopsdown"); nnlopsdown->Reset();

  TH1F* mg     = (TH1F*)mgexpected_ggH->Clone("mg");     mg->Reset();
  TH1F* mgup   = (TH1F*)mgexpected_ggH->Clone("mgup");   mgup->Reset();
  TH1F* mgdown = (TH1F*)mgexpected_ggH->Clone("mgdown"); mgdown->Reset();

  TH1F* rest     = (TH1F*)mgexpected_ggH->Clone("rest");     rest->Reset();
  TH1F* restup   = (TH1F*)mgexpected_ggH->Clone("restup");   restup->Reset();
  TH1F* restdown = (TH1F*)mgexpected_ggH->Clone("restdown"); restdown->Reset();

  m_integralobs = 1;
  if(var=="pt0j" || var=="pt1j" || var=="pt2j"){
    obs    = makeObs( (TGraphAsymmErrors*)_file0->Get("ptpt"), var );
    obssys = makeObsSys( (TGraphAsymmErrors*)_file0->Get("ptpt"),
			 (TGraphAsymmErrors*)_file0sys->Get("ptpt"),
			 var );
  }
  else{
    obs    = makeObs( (TGraphAsymmErrors*)_file0->Get(var.c_str()), var );
    //obssys = makeObsSys( (TGraphAsymmErrors*)_file0->Get(var.c_str()),
    obssys = makeObsSys( obs,
			 (TGraphAsymmErrors*)_file0sys->Get(var.c_str()),
			 var );
  }
  
  obssys->SetFillColor(kGray);
  obssys->SetLineColor(kGray);
  obssys->SetFillStyle(3352);
  
  /* make histograms and vectors */
  makehisto(mgvector, mgupvector, mgdownvector, _file2, true, var, mg);
  makehisto(nnlopsvector, nnlopsupvector, nnlopsdownvector, _file2, false, var, nnlops);

  if (var=="njet4")
    makehisto(gosamvector, gosamupvector, gosamdownvector, _file2, true, var, hgosam);


  if( var=="y" || var=="pt" )
    makehisto(hresvector, hresupvector, hresdownvector, _file2, true, var, hres);
  
  makehisto(restvector, restupvector, restdownvector, _file2, true, var, rest);
  
  /* make sys bands */
  makeSys(mgvector, mgupvector, mgdownvector, mg, mgup, mgdown);
  makeSys(nnlopsvector, nnlopsupvector, nnlopsdownvector, nnlops, nnlopsup, nnlopsdown);
  
  if (var=="njetv4")
    makeSys(gosamvector, gosamupvector, gosamdownvector, hgosam, hgosamup, hgosamdown);// std::cout<<"SS";gosamvector->at(0)->Print();

  if (var=="y" || var=="pt")
    makeSys(hresvector, hresupvector, hresdownvector, hres, hresup, hresdown);
  
  makeSys(restvector, restupvector, restdownvector, rest, restup, restdown);
  
  /* Create skeleton histograms */
  TH1F* dummy1 = CreateDummyPlot(mgexpected_ggH2,"dummy1",var);
  dummy1->GetXaxis()->SetLabelOffset(1.8);
  TH1F* dummy2 = CreateDummyPlot(mgexpected_ggH2,"dummy2",var);
  

  
  if(normalized){

    double integral_tmp = evalIntegral(nnlops);
    restup   ->Scale( 1./integral_tmp );
    restdown ->Scale( 1./integral_tmp );
    rest     ->Scale( 1./integral_tmp );
    
    integral_tmp = evalIntegral(mg);
    mgup   ->Scale( 1./integral_tmp );
    mgdown ->Scale( 1./integral_tmp );
    mg     ->Scale( 1./integral_tmp );
    
    integral_tmp = evalIntegral(nnlops);
    nnlopsup   ->Scale( 1./integral_tmp );
    nnlopsdown ->Scale( 1./integral_tmp );
    nnlops     ->Scale( 1./integral_tmp );

    
    if(hres!=NULL){
      hresup   ->Scale( 1./integral_tmp );
      hresdown ->Scale( 1./integral_tmp );
      hres     ->Scale( 1./integral_tmp );

    }
    
    obs->Print("v");
    TH1F *obsh = (TH1F *)nnlops->Clone("obsh");
    
    for (int i = 0; i < obssys->GetN(); ++i){
      double x; double y;
      obs->GetPoint(i, x, y);
      obsh->SetBinContent(i+1,y);
    }
    
    m_integralobs = evalIntegral(obsh);
      
    if(var=="pt0j" || var=="pt1j" || var=="pt2j"){
      obs    = makeObs( (TGraphAsymmErrors*)_file0->Get("ptpt"), var );
      obssys = makeObsSys( (TGraphAsymmErrors*)_file0->Get("ptpt"),
			   (TGraphAsymmErrors*)_file0sys->Get("ptpt"),
			   var );
    }
    else{
      obs    = makeObs( (TGraphAsymmErrors*)_file0->Get(var.c_str()), var );
      obssys = makeObsSys( (TGraphAsymmErrors*)_file0->Get(var.c_str()),
			   (TGraphAsymmErrors*)_file0sys->Get(var.c_str()),
			   var );
    }
    
  }
  
  /* Create Expected Hisotgrams */
  TGraphAsymmErrors *mgexpected       = makeTGraph(mg, mgup, mgdown, "MG5");
  TGraphAsymmErrors *nnlopsexpected   = makeTGraph(nnlops, nnlopsup, nnlopsdown, "NNLOPS");
  restdown->Reset();
  TGraphAsymmErrors *restexpected     = makeTGraph(rest, restup, restdown, "REST");
  TGraphAsymmErrors *restexpectedL    = makeTGraph(rest, restup, restdown, "REST",false,true);
  TGraphAsymmErrors *hresexpected     = NULL;
  TGraphAsymmErrors *hgosamexpected     = NULL;

  std::vector<double> binwidth;
  std::vector<double> hrest;
  std::vector<double> hresteup;
  std::vector<double> hrestedn;
  std::vector<double> nnlopseup;
  std::vector<double> nnlopsedn;
  std::vector<double> mg5;
  std::vector<double> mg5eup;
  std::vector<double> mg5edn;
  if (var=="pt")  binwidth= {10,5,5,10,15,15,20,40,80,150,650};
  if (var=="njet")  binwidth= {1,1,1,1,1};

  if (var=="pt")  hrest= {0.0084215,0.0096109,0.0122763,0.0281371,0.0486485,0.0507376,0.0633878,0.0963436,0.086345,0.0313941,0.0049818};
  if (var=="njet") hrest= {0.06421094,0.13931988,0.15309773,0.04103201,0.04293282};

  if (var=="pt")    hresteup = {0,0,0,0,0,0,0,0,0,0,0};
  if (var=="njet")  hresteup= {0,0,0,0,0};
  if (var=="pt")    hrestedn = {0,0,0,0,0,0,0,0,0,0,0};
  if (var=="njet")  hrestedn= {0,0,0,0,0};

  if (var=="pt")    nnlopseup = {0.0479009772326,0.0457994875108,0.0462700857505,0.0454166976476,0.0454452500846,0.0453582156614,0.0451191291278,0.0451147222332,0.044859052981,0.0446028481257,0.0445197920544};
  if (var=="njet")  nnlopseup= {0.0455768780864,0.0459641934662,0.0458876759081,0.0459311958504,0.0451255791943};
  if (var=="pt")    nnlopsedn = {0.0459548181614,0.0490296837538,0.0496648127978,0.0456957361469,0.045136283225,0.0449332395742,0.0448177897797,0.0447603965759,0.0446688190041,0.0445598018492,0.0445289440664};
  if (var=="njet")  nnlopsedn= {0.0458955943159,0.0452715198645,0.0454659998434,0.0455614356887,0.0448565256871};

  if (var=="pt")  mg5= {0.399796101,0.284166481,0.260984718,0.433388157,0.4702525,0.315921292,0.260211501,0.253366026,0.169829103,0.065070466,0.014153272};
  if (var=="njet") mg5= {1.66308680003121,0.831907972870721,0.297502711517352,0.0966222150500302,0.038104691251128};

  if (var=="pt")    mg5edn = {0.115,0.115,0.115,0.115,0.115,0.115,0.115,0.115,0.115,0.115,0.115};
  if (var=="njet")  mg5edn= {0.115,0.115,0.115,0.115,0.115};
  if (var=="pt")    mg5eup = {0.115,0.115,0.115,0.115,0.115,0.115,0.115,0.115,0.115,0.115,0.115};
  if (var=="njet")  mg5eup= {0.115,0.115,0.115,0.115,0.115};





  for (unsigned int ii =0; ii< nnlopsexpected->GetN(); ++ii ){
    double xx,yy, dummy;
    double eyu, eyd;
    TGexpected->GetPoint(ii, xx, yy);
    //nnlopsexpected->GetPoint(ii, xx, dummy); 
    nnlopsexpected->SetPoint(ii, xx+0.2, yy/binwidth.at(ii));
    nnlopsexpected->SetPointEYlow(ii,nnlopsedn.at(ii)*yy/binwidth.at(ii));
    nnlopsexpected->SetPointEYhigh(ii,nnlopseup.at(ii)*yy/binwidth.at(ii));
    restexpected->SetPoint(ii, ii+0.5, hrest.at(ii)/binwidth.at(ii));
    restexpectedL->SetPoint(ii, ii+0.5, hrest.at(ii)/binwidth.at(ii));
   /* 
    if (var=="pt" && ii+1==nnlopsexpected->GetN()){
      obs->SetPoint(ii, xx, yy/binwidth.at(ii)*3.75);
      obs->SetPointEYhigh(ii,0.);
      obs->SetPointEYlow (ii,0);
      obs->SetPointEXhigh(ii,0.5);
      obs->SetPointEXlow(ii,0.5);

    }*/
    mgexpected->SetPoint(ii, xx-0.2, (hrest.at(ii)+mg5.at(ii))/binwidth.at(ii));
    mgexpected->SetPointEYhigh(ii,mg5eup.at(ii)*(hrest.at(ii)+mg5.at(ii))/binwidth.at(ii));
    mgexpected->SetPointEYlow (ii,mg5edn.at(ii)*(hrest.at(ii)+mg5.at(ii))/binwidth.at(ii));
    mgexpected->SetPointEXhigh(ii,0.08);
    mgexpected->SetPointEXlow(ii,0.08);
    nnlopsexpected->SetPointEXhigh(ii,0.08);
    nnlopsexpected->SetPointEXlow(ii,0.08);
    //restexpectedL->SetPointError(ii, 0, 0 ,  hrest.at(ii)/binwidth.at(ii), (hrest.at(ii)/binwidth.at(ii))*hresteup.at(ii));i
  }
  
  std::cout <<"$%$%$%$%$%$%$%$%$%$%$ "<< std::endl;
  nnlopsexpected->Print();
  if (hgosam!=NULL)
    hgosamexpected =makeTGraph(hgosam, hgosamup, hgosamdown, "HGOSAM");
  if(hres!=NULL)
    hresexpected   = makeTGraph(hres, hresup, hresdown, "HRES");

  c->Draw();
  TPad* p1 = new TPad("p1","p1",0.01,0.345,0.99,0.99);
  p1->Draw();
  p1->SetBottomMargin(0.02);
  p1->SetLeftMargin(0.18);
  TPad* p2 = new TPad("p2","p2",0.01,0.01,0.99,0.345);
  p2->Draw();
  p2->SetTopMargin(0.);
  p2->SetLeftMargin(0.18);
  p2->SetBottomMargin(0.30);

  p1->cd();
  setStyle("NNLOPSexp",nnlopsexpected);
  setStyle("MG5exp",mgexpected);
  setStyle("RESTexpected",restexpected);
  setStyle("RESTexpected",restexpectedL,true);
  setStyle("NNLOPSexp",nnlops);
  if(hres!=NULL)
    setStyle("HRESexpected",hresexpected);
  
  TLegend *leg = CreateLegend(var);
  leg->AddEntry(obs, "Data","pez");
  leg->AddEntry(obssys, "Syst. uncertainties","f");
  leg->AddEntry(mgexpected, "MG5 FxFx #font[12]{K} = 1.47, +XH", "pf");
  if(normalized)
    leg->AddEntry(nnlopsexpected, "NNLOPS #font[12]{K} = 1.1, +XH", "pf");
  if(!normalized)
    leg->AddEntry(nnlopsexpected, "NNLOPS #font[12]{K} = 1.1, +XH", "pf");
  if(hresexpected_ggH!=NULL)
    //leg->AddEntry(hresexpected, "HRes 2.3 #font[12]{K} = 1.1, +XH", "pf");
  
  leg->AddEntry(restexpected, "XH = VBF+WH+ZH+ttH+bbH", "lf");
  if ( var == "njet") leg->AddEntry(restexpectedL, "XH = VBF+WH+ZH+ttH+bbH", "lf");

  TH1F* nnlops_rm= NULL;
  if (var=="pt"||var=="pt0j"||var=="pt1j"||var=="pt2j"||var=="ljpt"){
    remapHisto(mgexpected, "mg");
    remapHisto(restexpected, "rest");
    remapHisto(restexpectedL, "rest");
    if (var=="pt") remapHisto(hresexpected, "hres");
    nnlops_rm = remapHisto(nnlops);
    remapHisto(nnlopsexpected, "nnlops");
    remapHisto(obssys, "sys");
    remapHisto(obs, "obs");
    setStyle("NNLOPSexp",nnlops_rm);
    dummy1 = remapHisto(dummy1,false);
    dummy2 = remapHisto(dummy2,false);

    dummy1->GetXaxis()->SetRangeUser(0,nnlops_rm->GetNbinsX()+1);

  }
  else if(var=="mjj"){
    remapMjjHisto(mgexpected, "mg");
    remapMjjHisto(restexpected, "rest");
    remapMjjHisto(restexpectedL, "rest");
    nnlops_rm = remapHisto(nnlops,true);
    remapMjjHisto(nnlopsexpected, "nnlops");
    remapMjjHisto(obssys, "sys");
    remapMjjHisto(obs, "obs");
    setStyle("NNLOPSexp",nnlops_rm);
    dummy1->GetXaxis()->SetRangeUser(0,4);
  }
  
  setAxisLabels(dummy1, var, false);
  AdjustXaxis(dummy1, var);
  if(m_debug)
    std::cout << TMath::MaxElement(mgexpected->GetN(),mgexpected->GetX()) << std::endl;
  dummy1->SetLabelOffset(3);
  dummy1->Draw();
  dummy1->Print();
  std::cout << dummy1->GetNbinsX() << std::endl; 
  TH1F *nominal = NULL;
  if (nnlops_rm!=NULL) nominal = (TH1F *)nnlops_rm->Clone("rmm");
  else nominal = (TH1F *)nnlops->Clone("rmm");
  for (int i = 0; i < obssys->GetN(); ++i){
    double x; double y;
    nnlopsexpected->GetPoint(i, x, y);
    nominal->SetBinContent(i+1,y);
    nominal->SetLineColor(kRed+1);
    nominal->SetLineStyle(3);
    nominal->SetFillColor(kWhite);
  }
  nominal->Draw("h,same");  
  nnlopsexpected->Draw("2,same");
  nnlopsexpected->Draw("pX,same");
// DA NON COMMENTARE
  mgexpected->Draw("2,same");
  mgexpected->Draw("pX,same");
  
  if(hres!=NULL){
    //hresexpected->Draw("2,same");
    //hresexpected->Draw("pX,same");
  }
  
  if(hgosam!=NULL){
    //hgosamexpected->Draw("2,same");
    //hgosamexpected->Draw("pX,same");
  }
  
  restexpected->Draw("2,same");
  restexpectedL->Draw("p,same");
  //restexpected->Draw("2,same");

  restexpected->Print();
  restexpectedL->Print();
  if (var=="m34"||var=="pt0j"){
    double x, y;
    nnlops->Print();
    obs->GetPoint(nnlops->GetNbinsX()-1, x,y);
    if(var=="m34"){
      obs->SetPoint(nnlops->GetNbinsX()-1, x, nnlops->GetBinContent(nnlops->GetNbinsX())*4.32);         //uppper limit
      obs->SetPointError(nnlops->GetNbinsX()-1,nnlops->GetBinWidth(nnlops->GetNbinsX())/2,nnlops->GetBinWidth(nnlops->GetNbinsX())/2,0,0);
      obssys->SetPointError(nnlops->GetNbinsX()-1,0,0,0,0);
    }
    if(var=="pt0j"){
      obs->SetPoint(nnlops_rm->GetNbinsX()-1, x, nnlops_rm->GetBinContent(nnlops->GetNbinsX())*41.5);  //upper limit
      obs->SetPointError(nnlops_rm->GetNbinsX()-1,nnlops_rm->GetBinWidth(nnlops_rm->GetNbinsX())/2,nnlops_rm->GetBinWidth(nnlops_rm->GetNbinsX())/2,0,0);
      obssys->SetPointError(nnlops_rm->GetNbinsX()-1,0,0,0,0);
    }
  }
  
  obs->SetMarkerSize(0.7);
  obssys->SetLineColor(kBlack);
  obssys->SetFillColor(kWhite);
  obssys->SetFillStyle(0);
  obssys->SetMarkerSize(0.);
  obs->SetMarkerStyle(20);
  obssys->SetLineWidth(1);
  obs->SetLineWidth(2);
  
  obssys->Draw("e5,SAME");
  obs->Draw("pez");
  obssys->Print();
  drawLabels();
  
  leg->Draw();

  std::ofstream tablefile;
  tablefile.open (("HEP_"+var+"_table.dat").c_str());
  double obsY, obsStatUp, obsStatDown, ObsSysUp, ObsSysDown;
  double NNLOPSY, NNLOPSUp, NNLOPSDown;
  double dummy;
  double binwidthtmp;
  for (unsigned int i = 0 ; i < nnlops->GetNbinsX(); ++i){
    obs->GetPoint(i, dummy,obsY);
    nnlopsexpected->GetPoint(i, dummy,NNLOPSY);
    NNLOPSUp = nnlopsexpected->GetErrorYhigh(i);
    NNLOPSDown = nnlopsexpected->GetErrorYlow(i);
    ObsSysUp = obssys->GetErrorYhigh(i);
    ObsSysDown = obssys->GetErrorYlow(i);
    obsStatUp = sqrt(obs->GetErrorYhigh(i)*obs->GetErrorYhigh(i)-obssys->GetErrorYhigh(i)*obssys->GetErrorYhigh(i));
    obsStatDown = sqrt(obs->GetErrorYlow(i)*obs->GetErrorYlow(i)-obssys->GetErrorYlow(i)*obssys->GetErrorYlow(i));
    
    
    tablefile << nnlops->GetBinLowEdge(i+1)<<"  "<< nnlops->GetBinLowEdge(i+1)+nnlops->GetBinWidth(i+1) << "  " <<obsY << "  " << obsStatUp << " " << -1*obsStatDown << " "<<ObsSysUp << "  "<<-1*ObsSysDown << "  " << NNLOPSY << " "<<NNLOPSUp << "  " << -1*NNLOPSDown;
    if (i < nnlops->GetNbinsX()-1) tablefile << std::endl;
  }

  tablefile.close();
  p2->cd();
  
  TH1F* dummy3;
  if(var=="pt"   || var=="pt0j" || var=="pt1j" ||
     var=="pt2j" || var=="ljpt" || var=="mjj"   )
    dummy3 = nnlops_rm;
  else
    dummy3=nnlops;
  
  /* making ratios */
  TGraphAsymmErrors *obs_ratio     = makeRatio(obs,obs,dummy3,var,"obs");
  exp_ratio_xsMG     = makeRatio(mgexpected,obs,dummy3,var,"mg");
  exp_ratio_xsNNLOPS = makeRatio(nnlopsexpected,obs,dummy3,var,"nnlops");
  //if(hresexpected_ggH!=NULL)
    //exp_ratio_xsHRES = makeRatio(hresexpected,obs,dummy3,var,"hres");
  
  setStyle("obsratio",obs_ratio);
  leg->AddEntry(obs_ratio, "Total stat. #oplus syst. uncertainty", "lf");
  setStyle("MG5ratio",exp_ratio_xsMG);
  setStyle("NNLOPSratio",exp_ratio_xsNNLOPS);
  if(hresexpected_ggH!=NULL)
    setStyle("HRESratio",exp_ratio_xsHRES);

  setAxisLabels(dummy2, var, true);
  AdjustXaxis(dummy2, var);
  dummy2->GetYaxis()->SetRangeUser(0.4,1.85);
  dummy2->GetYaxis()->SetNdivisions(5);
  dummy2->Draw();
  TLine *l = MakeHorLine(dummy2,var);
  l->Draw();
  //DA NON COMMENTARE
  obs_ratio->Draw("2p,same");
  l->Draw();
  exp_ratio_xsMG->Draw("2p,same");
  exp_ratio_xsNNLOPS->Draw("2p,same");
  if(hresexpected_ggH!=NULL)
    //exp_ratio_xsHRES->Draw("2p,same");
  
  std::cout << std::endl;
  if(var=="pt0j"||var=="pt1j"||var=="pt2j"){
    std::cout << "for pt0j/pt1j/pt2j full 2D scan is used to evaluate the p-value" << std::endl;

  }

  for (unsigned int i =0; i<m_Arrows.size(); ++i) m_Arrows.at(i)->Draw();
  
  if (var!="njetv4"){
    
    double pvaluehres =0;
    std::cout << "*******************************" << std::endl;
    std::cout << "Generator   variable      p-value" << std::endl;
    double pvaluennlops;
    //if (var=="pt0j" || var=="pt1j" || var=="pt2j")
     // pvaluennlops = evalPValuePtPt("nnlops",normalized);
   // else
    pvaluennlops  = evalPValue(nnlopsexpected, "NNLOPS        ", var,normalized,obs);
    std::cout << "NNLOPS       "<< var << "   	" << pvaluennlops*100. <<"%"<<std::endl;
    double pvaluemg;
   // if (var=="pt0j" || var=="pt1j" || var=="pt2j")
     // pvaluemg = evalPValuePtPt("mg5",normalized);
    //else
    pvaluemg = evalPValue(mgexpected, "MadGraph     	 ", var,normalized,obs);
    std::cout << "MG            "<< var << "	 " << pvaluemg*100. <<"%"<<std::endl;
    
    if(hresexpected_ggH!=NULL) pvaluehres =0;// evalPValue(hresexpected, "HRes          ", var,normalized,obs);
    std::cout << "*******************************" << std::endl;

    std::cout << std::endl;

    p1->cd();
    TLatex pVal;
    pVal.SetNDC();
    pVal.SetTextFont(42);
    pVal.SetTextSize(0.042);
    pVal.SetTextColor(kBlack);

    Double_t xVal = 0.62;
    Double_t yVal = 0.54;
    if(var=="cts"){
      xVal = 0.21; yVal = 0.66;
    }
    else if(var=="m12m34" || var=="m12"){
      xVal = 0.21; yVal = 0.54;
    }
    
    std::ostringstream out;
    out << std::setprecision(2) << pvaluennlops*100;
    pVal.DrawLatex( xVal,yVal,("#font[12]{p}-value NNLOPS = "+out.str()+"%").c_str() );

    out.str(""); out << std::setprecision(2) << pvaluemg*100;
    pVal.DrawLatex( xVal,yVal-0.07,("#font[12]{p}-value MG5 FxFx = "+out.str()+"%").c_str() );

    out.str(""); out << std::setprecision(2) << pvaluehres*100;
    if(hresexpected_ggH!=NULL)
     // pVal.DrawLatex( xVal,yVal-0.14,("#font[12]{p}-value HRes = "+out.str()+"%").c_str() );

    
    if (var=="m34"||var=="pt"){
      double x,y;
    pVal.SetTextSize(0.035);
      obs->GetPoint(obs->GetN()-1,x,y); pVal.SetTextAngle(90);
      if (var=="m34"){
        pVal.DrawLatex( x/dummy1->GetXaxis()->GetXmax()-0.07 , 0.08 ,"upper limit" );
        pVal.DrawLatex( x/dummy1->GetXaxis()->GetXmax()-0.04 , 0.08 ,"@95% CL_{s}" );
      }
      if (var=="pt"){
        pVal.DrawLatex( x/dummy1->GetXaxis()->GetXmax()-0.035 , 0.08 ,"#sigma <3.75 #times SM 95% CL_{s}" );
        //pVal.DrawLatex( x/dummy1->GetXaxis()->GetXmax()-0.01 , 0.08 ,"@95% CL_{s}" );
      }
    }

  }
  if (var=="njetv4"){
    p1->cd();
    TLine* v1 = DefineVertLine(3,0.,2.2);
    v1->SetLineColor(kGray+2);
    v1->Draw("same");
    p2->cd();
    
    TLine* v2 = DefineVertLine(3,0.05,2.95);
    v2->SetLineColor(kGray+2);
    v2->Draw("same");
  }
  /* Redraw Axis()*/
  p1->cd();  gPad->RedrawAxis(); if(var=="mjj") MjjAxis(dummy1, p1, 0);
  p2->cd();  gPad->RedrawAxis(); if(var=="mjj") MjjAxis(dummy3, p2, 0.05);

  p1->cd(); leg->Draw();
  /* Saving to file */
  
  if (m_doN3LO) var = var+"_N3LO";
  if (!normalized){
    c->SaveAs( (m_OutDir+"fit_"+var+"_data_unfolded.pdf").c_str() );
    c->SaveAs( (m_OutDir+"fit_"+var+"_data_unfolded.eps").c_str() );
  }
  else{
    c->SaveAs( (m_OutDir+"fit_"+var+"_data_unfolded_normalized.pdf").c_str() );
    c->SaveAs( (m_OutDir+"fit_"+var+"_data_unfolded_normalized.eps").c_str() );
  }

  /* Cleaning */
  if(!keepCanvas) delete c;
  _file0->Close();
  _file1->Close();
  _file1b->Close();
  _file2->Close();

}

void DeriveError(){

  m_YR4error = totalXS(true,"all");

  /* Formula
     sqrt( (1/pow(sigma,2) * ( pow(DeltaSigGGH,2)+pow(DeltaSigVBF,2)+
           pow(DeltaSigWH,2)+pow(DeltaSigZH,2)+pow(DeltaSigTTH,2) ) +
	   pow( (SigGGH+SigVBF+SigWH+SigZH+SigTTH)/sigma)*DeltaSigma,2) )
   */

  std::vector<float> ggH = totalXS(true,"ggh");
  std::vector<float> VBF = totalXS(true,"vbf");
  std::vector<float> WH  = totalXS(true,"wh");
  std::vector<float> ZH  = totalXS(true,"zh");
  std::vector<float> TTH = totalXS(true,"tth");
  std::vector<float> BBH = totalXS(true,"bbh");
  std::vector<float> All = totalXS(true,"all");

  double XsecSum = ggH.at(0)+VBF.at(0)+WH.at(0)+ZH.at(0)+TTH.at(0);
  double XsecTot = All.at(0);

  
  double UpGGH = (ggH.at(1) - ggH.at(0)) ; // / ggH.at(0) ;
  double UpVBF = (VBF.at(1) - VBF.at(0)) ; // / VBF.at(0) ;
  double UpWH  = (WH.at(1)  - WH.at(0) ) ; // / WH.at(0)  ;
  double UpZH  = (ZH.at(1)  - ZH.at(0) ) ; // / ZH.at(0)  ;
  double UpTTH = (TTH.at(1) - TTH.at(0)) ; // / TTH.at(0) ;
  double UpBBH = (BBH.at(1) - BBH.at(0)) ; // / TTH.at(0) ;
  double UpTot = (All.at(1) - All.at(0)) ; // / All.at(0) ;

  double DwGGH = (ggH.at(0) - ggH.at(2)) ;// / ggH.at(0) ;
  double DwVBF = (VBF.at(0) - VBF.at(2)) ;// / VBF.at(0) ;
  double DwWH  = (WH.at(0)  - WH.at(2) ) ;// / WH.at(0)  ;
  double DwZH  = (ZH.at(0)  - ZH.at(2) ) ;// / ZH.at(0)  ;
  double DwTTH = (TTH.at(0) - TTH.at(2)) ;// / TTH.at(0) ;
  double DwBBH = (BBH.at(0) - BBH.at(2)) ;// / TTH.at(0) ;
  double DwTot = (All.at(0) - All.at(2)) ;// / All.at(0) ;

  std::cout << " xsec TOT " << All.at(0) << " UpTot "<< UpTot << " DwTot "<< DwTot << std::endl;
  std::cout << " xsec TOT " << All.at(0) << " UpTot "<< UpTot << " DwTot "<< DwTot << std::endl;
  std::cout << " xsec GGH " << ggH.at(0) << " UpGGH "<< UpGGH << " DwGGH "<< DwGGH << std::endl;
  std::cout << " xsec VBF " << VBF.at(0) << " UpVBF "<< UpVBF << " DwVBF "<< DwVBF << std::endl;
  std::cout << " xsec WH  " << WH.at(0)  << " UpWH  "<< UpWH  << " DwWH  "<< DwWH  << std::endl;
  std::cout << " xsec ZH  " << ZH.at(0)  << " UpZH  "<< UpZH  << " DwZH  "<< DwZH  << std::endl;
  std::cout << " xsec TTH " << TTH.at(0) << " UpTTH "<< UpTTH << " DwTTH "<< DwTTH << std::endl;
  std::cout << " xsec BBH " << BBH.at(0) << " UpBBH "<< UpBBH << " DwBBH "<< DwBBH << std::endl;
  
  //double ErrUp = sqrt( (1/pow(XsecTot,2)) * ( pow(UpGGH,2)+pow(UpVBF,2)+pow(UpWH,2)+pow(UpZH,2)+pow(UpTTH,2) ) +
  //pow( (XsecSum/XsecTot*XsecTot)*UpTot, 2 ) );

  double ErrUp = 1/XsecTot * sqrt( pow(UpGGH,2)+pow(UpVBF,2)+pow(UpWH,2)+pow(UpZH,2)+pow(UpTTH,2) +
				   pow( (XsecSum/XsecTot)*UpTot, 2 ) );

  double ErrDw = sqrt( (1/pow(XsecTot,2)) * ( pow(DwGGH,2)+pow(DwVBF,2)+pow(DwWH,2)+pow(DwZH,2)+pow(DwTTH,2) ) +
		       pow( (XsecSum/(XsecTot*XsecTot))*DwTot, 2 ) );

  std::cout << "bbH Error ---> Up = " << ErrUp << "  Down = "<< ErrDw << std::endl;
  
}

void MakeNjetExtended(std::string expFile, std::string mgFile,
		      std::string mgFile2, bool keepCanvas, bool doN3LO){

  SetAtlasStyle();
  m_doN3LO = doN3LO;
  m_Var    = "njetExt";
  
  TFile *_file0 = new TFile( ("./expected/"+expFile).c_str()                     );
  TFile *_file1 = new TFile( "../ws_output/fit_njet__wsysdata_TGunfolded.root"   );
  TFile *_file2 = new TFile( "../ws_output/fit_njetv2__wsysdata_TGunfolded.root" );
  TFile *_file3 = new TFile( "../ws_output/fit_njetv3__wsysdata_TGunfolded.root" );

  TFile *_file1sys = new TFile( "../ws_output/fit_njet__wsys_fixing_alldata_TGunfolded.root"   );
  TFile *_file2sys = new TFile( "../ws_output/fit_njetv2__wsys_fixing_alldata_TGunfolded.root" );
  TFile *_file3sys = new TFile( "../ws_output/fit_njetv3__wsys_fixing_alldata_TGunfolded.root" );

  TFile *_mgfile  = new TFile( ("./expected/"+mgFile).c_str()  );
  TFile *_mgfile2 = new TFile( ("./expected/"+mgFile2).c_str() );
  
  TFile *_gosamfile = new TFile ("./expected/WG1_predictions.root");

  std::vector<TGraphAsymmErrors*> Obs, ObsSys;

  TGraphAsymmErrors *obsnjet   = (TGraphAsymmErrors*)_file1->Get( "njet"   );
  TGraphAsymmErrors *obsnjetv2 = (TGraphAsymmErrors*)_file2->Get( "njetv2" );
  TGraphAsymmErrors *obsnjetv3 = (TGraphAsymmErrors*)_file3->Get( "njetv3" );

  Obs.push_back( obsnjet   );
  Obs.push_back( obsnjetv2 );
  Obs.push_back( obsnjetv3 );
  
  TGraphAsymmErrors *obsSysnjet   = (TGraphAsymmErrors*)_file1sys->Get( "njet"   );
  TGraphAsymmErrors *obsSysnjetv2 = (TGraphAsymmErrors*)_file2sys->Get( "njetv2" );
  TGraphAsymmErrors *obsSysnjetv3 = (TGraphAsymmErrors*)_file3sys->Get( "njetv3" );

  ObsSys.push_back( obsSysnjet   );
  ObsSys.push_back( obsSysnjetv2 );
  ObsSys.push_back( obsSysnjetv3 );

  m_YR4error = totalXS("N3LO");

  TH1F *mgexp_ggH          = (TH1F*)_mgfile->Get(  "n_jets_fidDres_4lsel_nominal"    );
  TH1F *mgexp_ggHUppdf     = (TH1F*)_mgfile->Get(  "n_jets_fidDres_4lsel_pdf_up"     );
  TH1F *mgexp_ggHDownpdf   = (TH1F*)_mgfile->Get(  "n_jets_fidDres_4lsel_pdf_down"   );
  TH1F *mgexp_ggHUpscale   = (TH1F*)_mgfile2->Get(  "n_jets_fidDres_4lsel_scale_up"   );
  TH1F *mgexp_ggHDownscale = (TH1F*)_mgfile2->Get(  "n_jets_fidDres_4lsel_scale_down" );

  TH1F *mgexp_ggH2          = (TH1F*)_mgfile->Get( "n_jets_fidDres_4lsel_inclus_nominal"    );
  TH1F *mgexp_ggHUppdf2     = (TH1F*)_mgfile->Get( "n_jets_fidDres_4lsel_inclus_pdf_up"     );
  TH1F *mgexp_ggHDownpdf2   = (TH1F*)_mgfile->Get( "n_jets_fidDres_4lsel_inclus_pdf_down"   );
  TH1F *mgexp_ggHUpscale2   = (TH1F*)_mgfile2->Get( "n_jets_fidDres_4lsel_inclus_scale_up"   );
  TH1F *mgexp_ggHDownscale2 = (TH1F*)_mgfile2->Get( "n_jets_fidDres_4lsel_inclus_scale_down" );
  
  TH1F *gosame_ggh = (TH1F*) _gosamfile->Get("GoSamSherpa_Njets_incl");
  TH1F *gosame_gghUp = (TH1F*) _gosamfile->Get("GoSamSherpa_Njets_incl_up");
  TH1F *gosame_gghDown = (TH1F*) _gosamfile->Get("GoSamSherpa_Njets_incl_down");

  double ANNLOPS=1.;
  gosame_ggh->Scale(ANNLOPS);
  gosame_gghUp->Scale(ANNLOPS);
  gosame_gghDown->Scale(ANNLOPS);

  if(m_doN3LO){
    double scaleMG= 48580*1.25E-04	/4.1138;
    std::cout << mgexp_ggH ->Integral() << std::endl;
    mgexp_ggH->Scale(scaleMG);
    mgexp_ggHUppdf->Scale(scaleMG);
    mgexp_ggHDownpdf->Scale(scaleMG);
    mgexp_ggHUpscale->Scale(scaleMG);
    mgexp_ggHDownscale->Scale(scaleMG);
    mgexp_ggH2->Scale(scaleMG);
    mgexp_ggHUppdf2->Scale(scaleMG);
    mgexp_ggHDownpdf2->Scale(scaleMG);
    mgexp_ggHUpscale2->Scale(scaleMG);
    mgexp_ggHDownscale2->Scale(scaleMG);
  }
  std::vector<TH1F*> *Vmg      = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vmgup    = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vmgdown  = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vmg2     = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vmgup2   = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vmgdown2 = new std::vector<TH1F*>();
  
  Vmg     ->push_back(mgexp_ggH);
  Vmgup   ->push_back(mgexp_ggHUppdf);	 
  Vmgdown ->push_back(mgexp_ggHDownpdf);
  Vmgup   ->push_back(mgexp_ggHUpscale);	
  Vmgdown ->push_back(mgexp_ggHDownscale);

  Vmg2     ->push_back(mgexp_ggH2);
  Vmgup2   ->push_back(mgexp_ggHUppdf2);
  Vmgdown2 ->push_back(mgexp_ggHDownpdf2);
  Vmgup2   ->push_back(mgexp_ggHUpscale2);
  Vmgdown2 ->push_back(mgexp_ggHDownscale2);

  TH1F *ref  = (TH1F*)_file0->Get( "njet_ggHNNLOPS" );    ref->Reset();   ref->SetName(  "ref"   );
  TH1F *up   = (TH1F*)_file0->Get( "njet_ggHNNLOPS" );    up->Reset();    up->SetName(   "up"    );
  TH1F *dw   = (TH1F*)_file0->Get( "njet_ggHNNLOPS" );    dw->Reset();    dw->SetName(   "down"  );
  TH1F *ref2 = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );  ref2->Reset();  ref2->SetName( "ref2"  );
  TH1F *up2  = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );  up2->Reset();   up2->SetName(  "up2"   );
  TH1F *dw2  = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );  dw2->Reset();   dw2->SetName(  "down2" );
  TH1F *ref3 = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );  ref3->Reset();  ref3->SetName( "ref3"  );
  TH1F *up3  = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );  up3->Reset();   up3->SetName(  "up3"   );
  TH1F *dw3  = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );  dw3->Reset();   dw3->SetName(  "down3" );
  /*
  TH1F *gosam2  = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );    gosam->Reset();   gosam->SetName(  "gosam2"   );
  TH1F *gosamup2   = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );    gosamup->Reset();    gosamup->SetName(   "gosamup2"    );
  TH1F *gosamdw2   = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );    gosamdw->Reset();    gosamdw->SetName(   "gosamdw2"  );
  
  TH1F *gosam3  = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );    gosam->Reset();   gosam->SetName(  "gosam3"   );
  TH1F *gosamup3   = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );    gosamup->Reset();    gosamup->SetName(   "gosamup3"    );
  TH1F *gosamdw3   = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );    gosamdw->Reset();    gosamdw->SetName(   "gosamdw3"  );
  
  
  gosam->SetBinContent(4, gosame_ggh->Integral(2,4) ); gosam->SetBinContent(5, gosame_ggh->Integral(3,4) ); gosam->SetBinContent(6, gosame_ggh->Integral(4,4) );
  gosamup->SetBinContent(4, gosame_gghUp->Integral(2,4) ); gosamup->SetBinContent(5, gosame_gghUp->Integral(3,4) ); gosamup->SetBinContent(6, gosame_gghUp->Integral(4,4) );
  gosamdw->SetBinContent(4, gosame_gghDown->Integral(2,4) ); gosamdw->SetBinContent(5, gosame_gghDown->Integral(3,4) ); gosamdw->SetBinContent(6, gosame_gghDown->Integral(4,4) );
*/
  
  std::vector<TH1F*> *Vnnlops    = new std::vector<TH1F*>();
  std::vector<TH1F*> *VnnlopsUp  = new std::vector<TH1F*>();
  std::vector<TH1F*> *VnnlopsDw  = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vnnlops2   = new std::vector<TH1F*>();
  std::vector<TH1F*> *VnnlopsUp2 = new std::vector<TH1F*>();
  std::vector<TH1F*> *VnnlopsDw2 = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vnnlops3   = new std::vector<TH1F*>();
  std::vector<TH1F*> *VnnlopsUp3 = new std::vector<TH1F*>();
  std::vector<TH1F*> *VnnlopsDw3 = new std::vector<TH1F*>();

  TH1F* mg     = (TH1F*)mgexp_ggH->Clone("mg");     mg->Reset();
  TH1F* mgup   = (TH1F*)mgexp_ggH->Clone("mgup");   mgup->Reset();
  TH1F* mgdown = (TH1F*)mgexp_ggH->Clone("mgdown"); mgdown->Reset();
  
  TH1F* mg2     = (TH1F*)mgexp_ggH2->Clone("mg2");     mg2->Reset();
  TH1F* mgup2   = (TH1F*)mgexp_ggH2->Clone("mgup2");   mgup2->Reset();
  TH1F* mgdown2 = (TH1F*)mgexp_ggH2->Clone("mgdown2"); mgdown2->Reset();

  TH1F *rest    = (TH1F*)_file0->Get( "njet_ggHNNLOPS" );    rest->Reset();     rest->SetName(    "rest"    );
  TH1F *restup  = (TH1F*)_file0->Get( "njet_ggHNNLOPS" );    restup->Reset();   restup->SetName(  "restup"  );
  TH1F *restdw  = (TH1F*)_file0->Get( "njet_ggHNNLOPS" );    restdw->Reset();   restdw->SetName(  "down"    );
  TH1F *rest2   = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );  rest2->Reset();    rest2->SetName(   "rest2"   );
  TH1F *restup2 = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );  restup2->Reset();  restup2->SetName( "restup2" );
  TH1F *restdw2 = (TH1F*)_file0->Get( "njetv2_ggHNNLOPS" );  restdw2->Reset();  restdw2->SetName( "down2"   );
  TH1F *rest3   = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );  rest3->Reset();    rest3->SetName(   "rest3"   );
  TH1F *restup3 = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );  restup3->Reset();  restup3->SetName( "restup3" );
  TH1F *restdw3 = (TH1F*)_file0->Get( "njetv3_ggHNNLOPS" );  restdw3->Reset();  restdw3->SetName( "down3"   );

  std::vector<TH1F*> *Vrest      = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vrestup    = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vrestdown  = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vrest2     = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vrestup2   = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vrestdown2 = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vrest3     = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vrestup3   = new std::vector<TH1F*>();
  std::vector<TH1F*> *Vrestdown3 = new std::vector<TH1F*>();

  /* make histograms */
  makehisto( Vnnlops  , VnnlopsUp  , VnnlopsDw  , _file0 , false , "njet"   , ref   );
  makehisto( Vnnlops2 , VnnlopsUp2 , VnnlopsDw2 , _file0 , false , "njetv2" , ref2  );
  makehisto( Vnnlops3 , VnnlopsUp3 , VnnlopsDw3 , _file0 , false , "njetv3" , ref3  );
  makehisto( Vmg      , Vmgup      , Vmgdown    , _file0 , true  , "njet"   , mg    );
  makehisto( Vmg2     , Vmgup2     , Vmgdown2   , _file0 , true  , "njet"   , mg2   );
  makehisto( Vrest    , Vrestup    , Vrestdown  , _file0 , true  , "njet"   , rest  );
  makehisto( Vrest2   , Vrestup2   , Vrestdown2 , _file0 , true  , "njetv3" , rest2 );
  makehisto( Vrest3   , Vrestup3   , Vrestdown3 , _file0 , true  , "njetv3" , rest3 );

  /* mas sys bands */
  makeSys( Vnnlops  , VnnlopsUp  , VnnlopsDw  , ref   , up      , dw      );
  makeSys( Vnnlops2 , VnnlopsUp2 , VnnlopsDw2 , ref2  , up2     , dw2     );
  makeSys( Vnnlops3 , VnnlopsUp3 , VnnlopsDw3 , ref3  , up3     , dw3     );
  makeSys( Vmg      , Vmgup      , Vmgdown    , mg    , mgup    , mgdown  );
  makeSys( Vmg2     , Vmgup2     , Vmgdown2   , mg2   , mgup2   , mgdown2 );
  makeSys( Vrest    , Vrestup    , Vrestdown  , rest  , restup  , restdw  );
  makeSys( Vrest2   , Vrestup2   , Vrestdown2 , rest2 , restup2 , restdw2 );
  makeSys( Vrest3   , Vrestup3   , Vrestdown3 , rest3 , restup3 , restdw3 );


  /* Create expected Graphs */
  restdw->Reset();   restdw2->Reset();   restdw->Reset();

  Double_t Vals[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  Int_t Nbins = ( (sizeof Vals) / (sizeof *Vals) )-1;
  std::vector<double> xVal;
  for(int i=0; i<Nbins+1; i++){
    xVal.push_back(Vals[i]);
  }
  TH1F *Nom_nnlops  = new TH1F("Nom_nnlops" , "Nom_nnlops" , Nbins, 0, Nbins);
  TH1F *Up_nnlops   = new TH1F("Up_nnlops"  , "Up_nnlops"  , Nbins, 0, Nbins);
  TH1F *Down_nnlops = new TH1F("Down_nnlops", "Down_nnlops", Nbins, 0, Nbins);
  TH1F *Nom_mg5     = new TH1F("Nom_mg5"    , "Nom_mg5"    , Nbins, 0, Nbins);
  TH1F *Up_mg5      = new TH1F("Up_mg5"     , "Up_mg5"     , Nbins, 0, Nbins);
  TH1F *Down_mg5    = new TH1F("Down_mg5"   , "Down_mg5"   , Nbins, 0, Nbins);
  TH1F *Nom_rest    = new TH1F("Nom_rest"   , "Nom_rest"   , Nbins, 0, Nbins);
  TH1F *Up_rest     = new TH1F("Up_rest"    , "Up_rest"    , Nbins, 0, Nbins);
  TH1F *Down_rest   = new TH1F("Down_rest"  , "Down_rest"  , Nbins, 0, Nbins);

  TH1F *Nom_gosam    = new TH1F("Nom_gosam"   , "Nom_gosam"   , Nbins, 0, Nbins);
  TH1F *Up_gosam     = new TH1F("Up_gosam"    , "Up_gosam"    , Nbins, 0, Nbins);
  TH1F *Down_gosam   = new TH1F("Down_gosam"  , "Down_gosam"  , Nbins, 0, Nbins);

  
  for(int i=0; i<Nbins; i++){
    if(i<3){ //0 1 2
      Nom_nnlops ->SetBinContent( i+1, ref->GetBinContent(i+1)    );
      Up_nnlops  ->SetBinContent( i+1, up->GetBinContent(i+1)     );
      Down_nnlops->SetBinContent( i+1, dw->GetBinContent(i+1)     );
      Nom_mg5    ->SetBinContent( i+1, mg->GetBinContent(i+1)     );
      Up_mg5     ->SetBinContent( i+1, mgup->GetBinContent(i+1)   );
      Down_mg5   ->SetBinContent( i+1, mgdown->GetBinContent(i+1) );
      Nom_rest   ->SetBinContent( i+1, rest->GetBinContent(i+1)   );
      Up_rest    ->SetBinContent( i+1, restup->GetBinContent(i+1) );
      Down_rest  ->SetBinContent( i+1, restdw->GetBinContent(i+1) );
    }
    else if(i==3){ //>=1
      Nom_nnlops ->SetBinContent( i+1, ref2->GetBinContent(2)    );
      Up_nnlops  ->SetBinContent( i+1, up2->GetBinContent(2)     );
      Down_nnlops->SetBinContent( i+1, dw2->GetBinContent(2)     );
      Nom_mg5    ->SetBinContent( i+1, mg2->GetBinContent(2)     );
      Up_mg5     ->SetBinContent( i+1, mgup2->GetBinContent(2)   );
      Down_mg5   ->SetBinContent( i+1, mgdown2->GetBinContent(2) );
      Nom_rest   ->SetBinContent( i+1, rest2->GetBinContent(2)   );
      Up_rest    ->SetBinContent( i+1, restup2->GetBinContent(2) );
      Down_rest  ->SetBinContent( i+1, restdw2->GetBinContent(2) );
    }
    else if(i==4){ //>=2
      Nom_nnlops ->SetBinContent( i+1, ref3->GetBinContent(3)    );
      Up_nnlops  ->SetBinContent( i+1, up3->GetBinContent(3)     );
      Down_nnlops->SetBinContent( i+1, dw3->GetBinContent(3)     );
      Nom_mg5    ->SetBinContent( i+1, mg2->GetBinContent(3)     );
      Up_mg5     ->SetBinContent( i+1, mgup2->GetBinContent(3)   );
      Down_mg5   ->SetBinContent( i+1, mgdown2->GetBinContent(3) );
      Nom_rest   ->SetBinContent( i+1, rest3->GetBinContent(3)   );
      Up_rest    ->SetBinContent( i+1, restup3->GetBinContent(3) );
      Down_rest  ->SetBinContent( i+1, restdw3->GetBinContent(3) );
    }
    else if(i==5){ //>=3
      Nom_nnlops ->SetBinContent( i+1, ref->GetBinContent(4)     );
      Up_nnlops  ->SetBinContent( i+1, up->GetBinContent(4)      );
      Down_nnlops->SetBinContent( i+1, dw->GetBinContent(4)      );
      Nom_mg5    ->SetBinContent( i+1, mg2->GetBinContent(4)     );
      Up_mg5     ->SetBinContent( i+1, mgup2->GetBinContent(4)   );
      Down_mg5   ->SetBinContent( i+1, mgdown2->GetBinContent(4) );
      Nom_rest   ->SetBinContent( i+1, rest->GetBinContent(4)    );
      Up_rest    ->SetBinContent( i+1, restup->GetBinContent(4)  );
      Down_rest  ->SetBinContent( i+1, restdw->GetBinContent(4)  );
    }
    
  }
  
  TGraphAsymmErrors *expNNLOPS = makeTGraph(Nom_nnlops,Up_nnlops,Down_nnlops,"NNLOPS");
  TGraphAsymmErrors *expMG5    = makeTGraph(Nom_mg5,Up_mg5,Down_mg5,"MG5");
  Down_rest->Reset();
  TGraphAsymmErrors *expREST   = makeTGraph(Nom_rest,Up_rest,Down_rest,"REST");
  TGraphAsymmErrors *expRESTL  = makeTGraph(Nom_rest,Up_rest,Down_rest,"REST",false,true);
  TGraphAsymmErrors *obs       = makeGraphNjet(Obs, "Observed", xVal);
  TGraphAsymmErrors *obsSys    = makeSysGraphNjet(Obs, ObsSys, "Observed", xVal);

  TCanvas *c = new TCanvas( "njets", "njets", 600, 600 );
  
  c->Draw();
  TPad* p1 = new TPad("p1","p1",0.01,0.345,0.99,0.99);
  p1->Draw();
  p1->SetBottomMargin(0.02);
  p1->SetLeftMargin(0.18);
  TPad* p2 = new TPad("p2","p2",0.01,0.01,0.99,0.345);
  p2->Draw();
  p2->SetTopMargin(0.);
  p2->SetLeftMargin(0.18);
  p2->SetBottomMargin(0.30);
  p1->cd();

  TH1F* dummy = (TH1F*)Nom_nnlops->Clone("dummy");
  dummy->Reset();
  dummy->SetLineColor(0);
  dummy->GetXaxis()->SetRangeUser( dummy->GetXaxis()->GetXmin(),
				   dummy->GetXaxis()->GetXmax() );

  
  setAxisLabels(dummy, "njetincl", false);

  p1->cd();
  
  TLegend *leg = CreateLegend("",false);
  dummy->GetXaxis()->SetLabelOffset(1.8);
  dummy->Draw();
  
  
  setStyle("MG5exp",expMG5);
  setStyle("NNLOPSexp",expNNLOPS);

  setStyle("NNLOPSexp",Nom_nnlops);
  
  setStyle("RESTexpected",expREST);
  setStyle("RESTexpected",expRESTL,true);

  Nom_nnlops->SetFillColor(kWhite);
  Nom_nnlops->SetLineColor(kRed+1);
  Nom_nnlops->SetLineStyle(3);
  
  Nom_nnlops->Draw("h, same");
  expNNLOPS->Draw("2,same");
  expNNLOPS->Draw("pX,same");
  expMG5->Draw("2,same");
  expMG5->Draw("pX,same");
  expREST->Draw("2,same");
  expRESTL->Draw("p,same");

  obs->SetMarkerSize(0.7);
  obsSys->SetLineColor(kBlack);
  obsSys->SetFillColor(kWhite);
  obsSys->SetFillStyle(0);
  obsSys->SetMarkerSize(0.);
  obs->SetMarkerStyle(20);
  obsSys->SetLineWidth(1);
  obs->SetLineWidth(2);
  
  obsSys->Draw("e5");
  obs->Draw("pez");

  leg->AddEntry(obs, "Data", "pez");
  leg->AddEntry(obsSys, "Syst. uncertainties", "f");
  leg->AddEntry(expNNLOPS, "NNLOPS #font[12]{K} = 1.1, +XH", "pf");
  leg->AddEntry(expMG5, "MG5 FxFx #font[12]{K} = 1.47, +XH" ,"pf");
  leg->AddEntry(expREST, "XH = VBF+WH+ZH+ttH+bbH", "lf");
  drawLabels(false);
  leg->SetY1(0.72);
  leg->Draw();
  
  TLine* v1 = DefineVertLine(3,0.,2.35);
  v1->SetLineColor(kGray+2);
  v1->Draw("same");
  p2->cd();
  TH1F* dummy2 = new TH1F ("dummy2","dummy2",6,0,6);
  
  dummy2->GetXaxis()->SetBinLabel( 1 , "0"     );
  dummy2->GetXaxis()->SetBinLabel( 2 , "1"     );
  dummy2->GetXaxis()->SetBinLabel( 3 , "2"     );
  dummy2->GetXaxis()->SetBinLabel( 4 , "#geq1" );
  dummy2->GetXaxis()->SetBinLabel( 5 , "#geq2" );
  dummy2->GetXaxis()->SetBinLabel( 6 , "#geq3" );
  dummy2->GetXaxis()->SetTitle("#font[12]{N}_{jets}");
  dummy2->GetYaxis()->SetTitle("Data/Theory");
  dummy2->GetYaxis()->SetTitleOffset(1.4);
  dummy2->GetXaxis()->SetLabelSize(0.06);
  dummy2->GetXaxis()->SetLabelOffset(0.013);
  dummy2->GetYaxis()->SetRangeUser(0,4);

  
  TGraphAsymmErrors* exp_ratio_xsMG     = makeRatio(expMG5,obs,dummy2,"njet","mg");
  TGraphAsymmErrors* exp_ratio_xsNNLOPS = makeRatio(expNNLOPS,obs,dummy2,"njet","nnlops");
  exp_ratio_xsMG->Print();
  setStyle("MG5ratio",exp_ratio_xsMG);
  setStyle("NNLOPSratio",exp_ratio_xsNNLOPS);
  
  setAxisLabels(dummy2, "njetincl", true);
  AdjustXaxis(dummy2, "njetincl");
  dummy2->GetYaxis()->SetRangeUser(0.05,2.95);
  dummy2->Draw();

  TLine *l = MakeHorLine(dummy2,"");
  l->Draw();
  exp_ratio_xsMG->Draw("2p,same");
  exp_ratio_xsNNLOPS->Draw("2p,same");
  
  TLine* v2 = DefineVertLine(3,0.05,2.95);
  v2->SetLineColor(kGray+2);
  v2->Draw("same");
  
  std::string var = m_Var;
  if(m_doN3LO) var = var+"_N3LO";
  c->SaveAs( (m_OutDir+"fit_"+var+"_data_unfolded.pdf").c_str() );
  c->SaveAs( (m_OutDir+"fit_"+var+"_data_unfolded.eps").c_str() );
  
  
  
  
}
