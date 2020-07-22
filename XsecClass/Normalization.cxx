#include "WorkSpaceMaker.h"

RooFormulaVar* WorkSpaceMaker :: SignalNormFactor(int cat, int ChNum, RooArgList* list, TH1F* h){
  /// TH1 as input to be removed numbers will be read from file?
  
  if( m_debug )
    cout<< "<SignalNormFactor()> :: Making Signal Normalization Factor " << cat << endl;
  
  /// need to define  with-without sys uncertainties condition
  
  /// without sys RooStats::HistFactory::FlexibleInterpVar not needed

  /// define 2 RooFormulaVar -case 1 with sys uncert -case 0 without sys uncert
  
  // common RooRealVar
  int Pos = 0;
  if ( m_Fiducial) Pos =0;
  else Pos = cat*(int(Process::bbH)+1);
  
  RooRealVar *sigma = new RooRealVar("sigma","sigma",1,-1000, 100000 );
  RooRealVar *BRZZ  = NULL;
  if ( m_Fiducial) BRZZ = new RooRealVar(("BR_ZZ_"+m_Category.at(cat)).c_str(), ("BR_ZZ_"+m_Category.at(cat)).c_str(), m_br.at(ChNum).first, 0, 1000 );
  else BRZZ = new RooRealVar("BR_ZZ", "BR_ZZ", m_br.at(ChNum).first, 0, 1000 );

  // specific RooRealVar per cat
  RooRealVar *sigmacat = new RooRealVar( ("sigma_"+m_Category.at(cat)).c_str(),
					 ("sigma_"+m_Category.at(cat)).c_str(), EvalXS(Pos)/m_binwidth.at(cat), -1000, 100000 );

  RooRealVar *Agg  = new RooRealVar( ("Agg_"+m_Category.at(cat)).c_str() , ("Agg_"+m_Category.at(cat)).c_str() , m_acc[ChNum].at(Pos+1).first, 0, 10 );
  RooRealVar *Avbf = new RooRealVar( ("Avbf_"+m_Category.at(cat)).c_str(), ("Avbf_"+m_Category.at(cat)).c_str(), m_acc[ChNum].at(Pos+2).first, 0, 10 );
  RooRealVar *Awh  = new RooRealVar( ("Awh_"+m_Category.at(cat)).c_str() , ("Awh_"+m_Category.at(cat)).c_str() , m_acc[ChNum].at(Pos+3).first, 0, 10 );
  RooRealVar *Azh  = new RooRealVar( ("Azh_"+m_Category.at(cat)).c_str() , ("Azh_"+m_Category.at(cat)).c_str() , m_acc[ChNum].at(Pos+4).first, 0, 10 );
  RooRealVar *Atth = new RooRealVar( ("Atth_"+m_Category.at(cat)).c_str(), ("Atth_"+m_Category.at(cat)).c_str(), m_acc[ChNum].at(Pos+5).first, 0, 10 );
  RooRealVar *Abbh = new RooRealVar( ("Abbh_"+m_Category.at(cat)).c_str(), ("Abbh_"+m_Category.at(cat)).c_str(), m_acc[ChNum].at(Pos+6).first, 0, 10 );
  
  RooRealVar *Cgg  = new RooRealVar( ("Cgg_"+m_Category.at(cat)).c_str() , ("Cgg_"+m_Category.at(cat)).c_str() , m_cf[ChNum].at(Pos+1).first, 0, 10 );
  RooRealVar *Cvbf = new RooRealVar( ("Cvbf_"+m_Category.at(cat)).c_str(), ("Cvbf_"+m_Category.at(cat)).c_str(), m_cf[ChNum].at(Pos+2).first, 0, 10 );
  RooRealVar *Cwh  = new RooRealVar( ("Cwh_"+m_Category.at(cat)).c_str() , ("Cwh_"+m_Category.at(cat)).c_str() , m_cf[ChNum].at(Pos+3).first, 0, 10 );
  RooRealVar *Czh  = new RooRealVar( ("Czh_"+m_Category.at(cat)).c_str() , ("Czh_"+m_Category.at(cat)).c_str() , m_cf[ChNum].at(Pos+4).first, 0, 10 );
  RooRealVar *Ctth = new RooRealVar( ("Ctth_"+m_Category.at(cat)).c_str(), ("Ctth_"+m_Category.at(cat)).c_str(), m_cf[ChNum].at(Pos+5).first, 0, 10 );
  RooRealVar *Cbbh = new RooRealVar( ("Cbbh_"+m_Category.at(cat)).c_str(), ("Cbbh_"+m_Category.at(cat)).c_str(), m_cf[ChNum].at(Pos+6).first, 0, 10 );

  RooRealVar *rgg  = new RooRealVar( ("rgg_"+m_Category.at(cat)).c_str() , ("rgg_"+m_Category.at(cat)).c_str() , m_r[ChNum].at(Pos+1).first, 0, 10 );
  RooRealVar *rvbf = new RooRealVar( ("rvbf_"+m_Category.at(cat)).c_str(), ("rvbf_"+m_Category.at(cat)).c_str(), m_r[ChNum].at(Pos+2).first, 0, 10 );
  RooRealVar *rwh  = new RooRealVar( ("rwh_"+m_Category.at(cat)).c_str() , ("rwh_"+m_Category.at(cat)).c_str() , m_r[ChNum].at(Pos+3).first, 0, 10 );
  RooRealVar *rzh  = new RooRealVar( ("rzh_"+m_Category.at(cat)).c_str() , ("rzh_"+m_Category.at(cat)).c_str() , m_r[ChNum].at(Pos+4).first, 0, 10 );
  RooRealVar *rtth = new RooRealVar( ("rtth_"+m_Category.at(cat)).c_str(), ("rtth_"+m_Category.at(cat)).c_str(), m_r[ChNum].at(Pos+5).first, 0, 10 );
  RooRealVar *rbbh = new RooRealVar( ("rbbh_"+m_Category.at(cat)).c_str(), ("rbbh_"+m_Category.at(cat)).c_str(), m_r[ChNum].at(Pos+6).first, 0, 10 );

  RooArgList rooarglist;
  rooarglist.add(*sigma);    list->add(*sigma); //@0
  rooarglist.add(*m_Lumi);   list->add(*m_Lumi);//@1
  rooarglist.add(*BRZZ);               list->add(*BRZZ);  //@2
  
  rooarglist.add(*sigmacat); list->add(*sigmacat); //@3
  rooarglist.add(*m_binwidthroorealvar.at(cat)); list->add(*m_binwidthroorealvar.at(cat)); //@4
  
  rooarglist.add(*rgg); list->add(*rgg); //@5
  rooarglist.add(*Agg); list->add(*Agg); //@6
  rooarglist.add(*Cgg); list->add(*Cgg); //@7
  
  rooarglist.add(*rvbf); list->add(*rvbf); //@8
  rooarglist.add(*Avbf); list->add(*Avbf); //@9
  rooarglist.add(*Cvbf); list->add(*Cvbf); //@10
  
  rooarglist.add(*rwh); list->add(*rwh); //@11
  rooarglist.add(*Awh); list->add(*Awh); //@12
  rooarglist.add(*Cwh); list->add(*Cwh); //@13
  
  rooarglist.add(*rzh); list->add(*rzh); //@14
  rooarglist.add(*Azh); list->add(*Azh); //@15
  rooarglist.add(*Czh); list->add(*Czh); //@16
  
  rooarglist.add(*rtth); list->add(*rtth); //@17
  rooarglist.add(*Atth); list->add(*Atth); //@18
  rooarglist.add(*Ctth); list->add(*Ctth); //@19
  
  rooarglist.add(*rbbh); list->add(*rbbh); //@20
  rooarglist.add(*Abbh); list->add(*Abbh); //@21
  rooarglist.add(*Cbbh); list->add(*Cbbh); //@22
  
  m_paramOfInterest->add(*sigmacat);
  m_globalObservables.add(rooarglist);
  m_globalObservables.remove(*sigmacat);
  m_Norm = NULL;
  
  if(m_addSys) {

    RooStats::HistFactory::FlexibleInterpVar *sysblock1 = makeSysBlock("block1", ChNum, 0, cat);
    RooStats::HistFactory::FlexibleInterpVar *sysblock2 = makeSysBlock("block2", ChNum, 1, cat);
    RooStats::HistFactory::FlexibleInterpVar *sysblock3 = makeSysBlock("block3", ChNum, 2, cat);
    RooStats::HistFactory::FlexibleInterpVar *sysblock4 = makeSysBlock("block4", ChNum, 3, cat);
    RooStats::HistFactory::FlexibleInterpVar *sysblock5 = makeSysBlock("block5", ChNum, 4, cat);
    RooStats::HistFactory::FlexibleInterpVar *sysblock6 = makeSysBlock("block6", ChNum, 5, cat);
    RooStats::HistFactory::FlexibleInterpVar *sysblock7 = makeSysBlock("block7", ChNum, 6, cat);

    rooarglist.add(*sysblock1); list->add(*sysblock1); //@23
    rooarglist.add(*sysblock2); list->add(*sysblock2); //@24
    rooarglist.add(*sysblock3); list->add(*sysblock3); //@25
    rooarglist.add(*sysblock4); list->add(*sysblock4); //@26
    rooarglist.add(*sysblock5); list->add(*sysblock5); //@27
    rooarglist.add(*sysblock6); list->add(*sysblock6); //@28
    rooarglist.add(*sysblock7); list->add(*sysblock7); //@29
 
    m_Norm = new RooFormulaVar( ("norm_"+m_Category.at(cat)).c_str(),
                               "(@0*@1*@2*@3*@4*@23)*((@5*@6*@7*@24) + (@8*@9*@10*@25) + (@11*@12*@13*@26) + (@14*@15*@16*@27) + (@17*@18*@19*@28) + (@20*@21*@22*@29) )",
                               rooarglist);
  }
  else{
    m_Norm = new RooFormulaVar( ("norm_"+m_Category.at(cat)).c_str(),
				"(@0*@1*@2*@3*@4)*((@5*@6*@7) + (@8*@9*@10) + (@11*@12*@13) + (@14*@15*@16) + (@17*@18*@19) + (@20*@21*@22) )", rooarglist);
  }
  h->Print();
  if( m_Fiducial )
    cout << "Cat = " << cat << " BinContent*BinWidth*Lumi = " << h->Integral() * m_binwidth.at(cat)*m_Lumi->getVal()
	 << " NormWS = " << m_Norm->getVal() << " Ratio: " <<  (h->Integral() * m_binwidth.at(cat)*m_Lumi->getVal())/m_Norm->getVal() << endl;
  else
    cout << "Cat = " << cat << " BinContent*BinWidth*Lumi = " << h->GetBinContent(cat+1) * m_binwidth.at(cat)*m_Lumi->getVal()
	 << " NormWS = " << m_Norm->getVal() << " Ratio: " <<  (h->GetBinContent(cat+1) * m_binwidth.at(cat)*m_Lumi->getVal())/m_Norm->getVal() << endl;
  
  m_xsminitree.push_back(PrintExpXS(ChNum, cat));
  
  if( m_Fiducial ){

    if( TMath::Abs(1-(h->Integral()*m_Lumi->getVal())/m_Norm->getVal())>0.018 ) dumpAllInformation(ChNum, Pos, cat);
    if( TMath::Abs(1-(h->Integral()*m_Lumi->getVal())/m_Norm->getVal())!=0 )
      std::cout << "\033[2;33m WARNING! not perfect matching normalization minitree vs ws  \033[0m" << std::endl;
  }
  else {//if ( m_Variable != "nbjet" ) {
    if( TMath::Abs(1-(h->GetBinContent(cat+1) * m_binwidth.at(cat)*m_Lumi->getVal())/m_Norm->getVal())>0.018) dumpAllInformation(ChNum, Pos, cat);
    if( TMath::Abs(1-(h->GetBinContent(cat+1) * m_binwidth.at(cat)*m_Lumi->getVal())/m_Norm->getVal())!=0 )
      std::cout << "\033[2;33m WARNING! not perfect matching normalization minitree vs ws  \033[0m" << std::endl;
  }
  
  cout << "OK" << endl;
  return m_Norm;
  
}

RooFormulaVar* WorkSpaceMaker :: BackgroundNormFactor(int cat, int chnum, RooArgList* list, TH1F* h, string process){
  /// TH1 as input to be removed numbers will be read from file?
  
  if( m_debug )
    cout<< "<BackgroundNormFactor()> :: Making Background Normalization Factor" << cat << endl;
  
  /// need to define  with-without sys uncertainties condition
  /// without sys RooStats::HistFactory::FlexibleInterpVar not needed
  /// define 2 RooFormulaVar -case 1 with sys uncert -case 0 without sys uncert
  
  // common RooRealVar
  
  // specific RooRealVar per cat

  RooRealVar *expperfb = new RooRealVar( ("expperfb_"+m_Category.at(cat)+process).c_str(),
					 ("expperfb_"+m_Category.at(cat)+process).c_str(),
					 h->GetBinContent(cat+1)) ;
  
  //expperfb->setVal( h->GetBinContent(cat+1) ) ;
  if( m_Fiducial ) expperfb->setVal( h->Integral() ) ;
  
  RooArgList rooarglist;
  rooarglist.add(*m_Lumi);   //list->add(*m_Lumi);   //@0
  rooarglist.add(*m_binwidthroorealvar.at(cat)); list->add(*m_binwidthroorealvar.at(cat)); //@1
  rooarglist.add(*expperfb); list->add(*expperfb); //@2
  m_globalObservables.add(rooarglist);

  m_Norm = NULL;
  
  if( m_addSys ) {


    if (process=="redBkg"){
      //RooStats::HistFactory::FlexibleInterpVar *sysblock1 = makeSysBlock("block1", chnum, m_process.at(process), cat);  
      RooStats::HistFactory::FlexibleInterpVar *sysblock2 = makeSysBlock("block2", chnum, m_process.at(process), cat);
    
      //rooarglist.add(*sysblock1); list->add(*sysblock1); //@3
      rooarglist.add(*sysblock2); list->add(*sysblock2); //@3
      
      m_Norm = new RooFormulaVar( ("norm_bkg_"+m_Category.at(cat)+process).c_str(),
                               "(@0*@1*@2*@3)", rooarglist);

    }


    else {
      RooStats::HistFactory::FlexibleInterpVar *sysblock1 = makeSysBlock("block1", chnum, m_process.at(process), cat);
      RooStats::HistFactory::FlexibleInterpVar *sysblock2 = makeSysBlock("block2", chnum, m_process.at(process), cat);
    
      rooarglist.add(*sysblock1); list->add(*sysblock1); //@3
      rooarglist.add(*sysblock2); list->add(*sysblock2); //@4
      m_Norm = new RooFormulaVar( ("norm_bkg_"+m_Category.at(cat)+process).c_str(),
                               "(@0*@1*@2*@3*@4)", rooarglist);
    }    


  }
  else  m_Norm = new RooFormulaVar( ("norm_bkg_"+m_Category.at(cat)+process).c_str(),
                               "(@0*@1*@2)",
                               rooarglist);
  if( m_debug ){
    cout << process << endl;
    cout << "<BackgroundNormFactor()> "<< endl;
    cout << "Normalization cat #:" << cat << " " << m_Norm->getVal() << endl;
    cout << "Process ID: "  << m_process.at(process) << endl;
    cout << m_Norm->getVal() << endl;

  }
  
  //exit(0);
  return m_Norm;
  
}

double WorkSpaceMaker :: EvalXS(int Pos){
  
  double m_expXS =0;
  for ( unsigned int i = 1 ; i < m_xsec.size() ;  ++i ){

    if (m_Fiducial) m_expXS += m_xsec.at(i).first*1000.;
    //for fiducial m_xsScale not present ---> it will be removed from Differential next step
    else m_expXS += m_xsec.at(i).first*m_xsScale.at(Pos+i).first*1000.;

  }
  return m_expXS;
  
}

void WorkSpaceMaker :: dumpAllInformation(int ChNum, int Pos, int cat){
  
  cout << " \033[1;31m ERROR! bad normalization check all numbers below \033[0m : 1.8% threshold exceeded " << endl;
  
  cout << " \033[1;21m Expected number of events at " << m_Category.at(cat) << " from ws " << cat
  << " " << PrintACRProduct(0, cat) << " vs minitree: "
  << m_h->GetBinContent(cat+1) * m_binwidth.at(cat)*m_Lumi->getVal() << " \033[0m" << endl;
  
  cout << " Scale values for ggF: " << m_xsScale.at(Pos+1).first << " VBF: " << m_xsScale.at(Pos+2).first
  << " WH: " << m_xsScale.at(Pos+3).first << " ZH: " << m_xsScale.at(Pos+4).first
  << " ttH: " << m_xsScale.at(Pos+5).first << " bbH: " << m_xsScale.at(Pos+6).first << endl;
  
  cout << " relative production mode contribution ggF: " << m_r[ChNum].at(Pos+1).first << " VBF: " << m_r[ChNum].at(Pos+2).first
  << " WH: " << m_r[ChNum].at(Pos+3).first << " ZH: " << m_r[ChNum].at(Pos+4).first
  << " ttH: " << m_r[ChNum].at(Pos+5).first << " bbH: " << m_r[ChNum].at(Pos+6).first << endl;
  
  cout << " CF per production mode ggF: " << m_cf[ChNum].at(Pos+1).first << " VBF: " << m_cf[ChNum].at(Pos+2).first
  << " WH: " << m_cf[ChNum].at(Pos+3).first << " ZH: " << m_cf[ChNum].at(Pos+4).first
  << " ttH: " << m_cf[ChNum].at(Pos+5).first << " bbH: " << m_cf[ChNum].at(Pos+6).first << endl;
  
  cout << " Acceptance per production mode ggF: "<< m_acc[ChNum].at(Pos+1).first << " VBF: " << m_acc[ChNum].at(Pos+2).first
  << " WH: "  << m_acc[ChNum].at(Pos+3).first << " ZH: " << m_acc[ChNum].at(Pos+4).first
  << " ttH: " << m_acc[ChNum].at(Pos+5).first << " " << " bbH: " << m_acc[ChNum].at(Pos+6).first << " " << endl;
  
  cout << "Events for ggF from A*C..: "
  <<  (m_acc[ChNum].at(Pos+1).first) * (m_cf[ChNum].at(Pos+1).first) * m_r[ChNum].at(Pos+1).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat) <<
  "   Events from minitree:  " << ((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_ggH").c_str()))->GetBinContent(cat+1)<<
  "   ratio A*C/minitree:  " <<  ((m_acc[ChNum].at(Pos+1).first) * (m_cf[ChNum].at(Pos+1).first) * m_r[ChNum].at(Pos+1).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat))/((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_ggH").c_str()))->GetBinContent(cat+1) << endl;
  
  cout << "Events for VBF from A*C..: "
  <<  (m_acc[ChNum].at(Pos+2).first) * (m_cf[ChNum].at(Pos+2).first) * m_r[ChNum].at(Pos+2).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat) <<
  "   Events from minitree:  " << ((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_VBF").c_str()))->GetBinContent(cat+1)<<
  "   ratio A*C/minitree:  " <<  ((m_acc[ChNum].at(Pos+2).first) * (m_cf[ChNum].at(Pos+1).first) * m_r[ChNum].at(Pos+2).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat))/((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_VBF").c_str()))->GetBinContent(cat+1) << endl;

  
  cout << "Events for WH from A*C..:  "
  <<  (m_acc[ChNum].at(Pos+3).first) * (m_cf[ChNum].at(Pos+3).first) * m_r[ChNum].at(Pos+3).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat) <<
  "   Events from minitree:  " << ((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_WH").c_str()))->GetBinContent(cat+1)<<
  "   ratio A*C/minitree:  " <<  ((m_acc[ChNum].at(Pos+3).first) * (m_cf[ChNum].at(Pos+3).first) * m_r[ChNum].at(Pos+3).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat))/((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_WH").c_str()))->GetBinContent(cat+1) << endl;

  
  cout << "Events for ZH from A*C..:  "
  <<  (m_acc[ChNum].at(Pos+4).first) * (m_cf[ChNum].at(Pos+4).first) * m_r[ChNum].at(Pos+4).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat) <<
  "   Events from minitree:  " << ((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_ZH").c_str()))->GetBinContent(cat+1)<<
  "   ratio A*C/minitree:  " <<  ((m_acc[ChNum].at(Pos+4).first) * (m_cf[ChNum].at(Pos+4).first) * m_r[ChNum].at(Pos+4).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat))/((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_ZH").c_str()))->GetBinContent(cat+1) << endl;

  
  cout << "Events for ttH from A*C..: "
  <<  (m_acc[ChNum].at(Pos+5).first) * (m_cf[ChNum].at(Pos+5).first) * m_r[ChNum].at(Pos+5).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat) <<
  "   Events from minitree:  " << ((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_ttH").c_str()))->GetBinContent(cat+1)<<
  "   ratio A*C/minitree:  " <<  ((m_acc[ChNum].at(Pos+5).first) * (m_cf[ChNum].at(Pos+5).first) * m_r[ChNum].at(Pos+5).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat))/((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_ttH").c_str()))->GetBinContent(cat+1) << endl;
  
  
  cout << "Events for bbH from A*C..: "
  <<  (m_acc[ChNum].at(Pos+6).first) * (m_cf[ChNum].at(Pos+6).first) * m_r[ChNum].at(Pos+6).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat) <<
  "   Events from minitree:  " << ((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_bbH").c_str()))->GetBinContent(cat+1)<<
  "   ratio A*C/minitree:  " <<  ((m_acc[ChNum].at(Pos+6).first) * (m_cf[ChNum].at(Pos+6).first) * m_r[ChNum].at(Pos+6).first * (m_br.at(ChNum).first) *EvalXS(Pos)/m_binwidth.at(cat))/((TH1F*)m_InFile->Get(("h"+m_Variable+"_incl_bbH").c_str()))->GetBinContent(cat+1) << endl;
  
  
  cout << " BinWidth saved: "<< m_binwidth.at(cat) << endl;
  
  cout << " Bin Range original: " <<m_h->GetBinLowEdge(cat+1) << " " << m_h->GetBinLowEdge(cat+1)+m_h->GetBinWidth(cat+1) << endl;
  
  cout << "\033[0;31m Advice 1: check Acceptance definition e.g. truth range vs histogram range \033[0m" << endl;
  cout << "\033[0;31m Advice 2: check type of variable for CF unconstrained vs FSR vs constrained \033[0m" << endl;
  
  
  cout << " \033[1;31m exit \033[0m" << endl;
  
  exit(0);
  
}
