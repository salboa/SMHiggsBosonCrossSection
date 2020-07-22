#include "WorkSpaceMaker.h"

double WorkSpaceMaker :: EvalXS(int Pos, int ch){

  double m_expXS =0;
  if( m_ProdMode != "AllProd" && m_ProdMode != "MergProd" ){
    if(m_matrix) m_expXS = m_xsec.at(m_process[m_ProdMode]).first *1000;
    else         m_expXS = m_xsec.at(m_process[m_ProdMode]).first* m_r[ch].at(int(Pos+(m_process[m_ProdMode])*(int(m_Category.size()/m_channels.size())) )).first *1000;
  }
  else{
    for( unsigned int i = 1 ; i < Process::bbH+1 ;  ++i ){
      if(m_Fiducial) m_expXS += m_xsec.at(i).first*1000.;
      else            m_expXS += m_xsec.at(i).first* m_r[ch].at(int(Pos+(i)*(int(m_Category.size()/m_channels.size())) )).first *1000;
    }
  }
  return m_expXS;
  
}

double WorkSpaceMaker :: ProcessXS(int Pos, int i, int ch){
  
  double XS =0;
  if(m_Fiducial) XS = m_xsec.at(Pos).first*m_r[ch].at(Pos).first *1000;
  else           XS = m_xsec.at(Pos).first*m_r[ch].at(i+Pos*int(m_Category.size()/m_channels.size() )).first *1000;
  return XS;
  
}

RooFormulaVar* WorkSpaceMaker :: SignalNormFactorMatrix(int cat, int ChNum, RooArgList* list){
  
  PRINT_DEBUG_FUNCTION ("<SignalNormFactorMatrix()> :: Making Signal Normalization Factor using matrix method for category:"+ to_string(cat));
  
  int Pos = 0;
  if(!m_Fiducial) Pos = cat*( int(m_Category.size()/m_channels.size()) );
  
  RooRealVar *sigma = new RooRealVar("sigma","sigma",1,-1000, 100000 );
  RooRealVar *BRZZ  = NULL;
  if (m_Fiducial){
    BRZZ = new RooRealVar( ("BR_ZZ_"+m_Category.at(ChNum-1)).c_str(),
			   ("BR_ZZ_"+m_Category.at(ChNum-1)).c_str(),
			   m_br.at(ChNum).first, 0, 1000        );
  }
  else{
    BRZZ = new RooRealVar( ("BR_ZZ_"+GetChannelName(ChNum)).c_str(),
			   ("BR_ZZ_"+GetChannelName(ChNum)).c_str(),
			   m_br.at(ChNum).first, 0, 1000          );
  }
  
  // specific RooRealVar per cat
  RooRealVar *sigmacat = NULL ;
  RooRealVar *A = NULL;
  RooRealVar *eff  = NULL;
  RooRealVar *r  = NULL;
  RooRealVar *notFid  = NULL;
  RooRealVar *minitree = NULL;  

  vector <RooRealVar *> v_sigma;
  vector <RooRealVar *> v_A;
  vector <RooRealVar *> v_eff;
  vector <RooRealVar *> v_r;
  vector <RooRealVar *> v_notFid;

  PRINT_DEBUG(" values used for normalization ");

  int MAX = m_Category.size()/m_channels.size();
  if(m_Fiducial) MAX = 1;
  int chPos = 0;
  int chCatPos = ChNum-1;
  if(m_channels.size()==1) chCatPos = 0;
  if(m_chSplit==1)         chCatPos = ChNum-5;
  
  for (int i=0; i < MAX; ++i ){

    chPos = i+(chCatPos)*int(m_Category.size()/m_channels.size());

    sigmacat = new RooRealVar( ("sigma_"+m_Category.at(chPos)).c_str(),
			       ("sigma_"+m_Category.at(chPos)).c_str(),
			       EvalXS(m_process[m_ProdMode], ChNum)/*/m_binwidth.at(i)*/,
			       -10000, 1000000 );
    sigmacat->setConstant(0);
    m_paramOfInterest->add(*sigmacat);
    
    A   = new RooRealVar( ("A_"+m_Category.at(chPos)).c_str() ,
			  ("A_"+m_Category.at(chPos)).c_str() ,
			  m_acc[ChNum].at(i).first, 0, 10 );
    
    string effName = "eff_"+m_Category.at(cat)+m_Category.at(chPos);
    if(m_Fiducial) effName = "eff_"+m_Category.at(chPos);
    
    eff = new RooRealVar( effName.c_str() ,
			  effName.c_str() ,
			  m_cf[ChNum].at(Pos+i).first, 0, 10 );
        
    r   = new RooRealVar( ("r_"+m_Category.at(chPos)).c_str() ,
			  ("r_"+m_Category.at(chPos)).c_str() ,
			  m_r[ChNum].at(i).first, 0, 10 );         
    
    v_sigma.push_back(sigmacat);
    v_A.push_back(A);
    v_eff.push_back(eff);
    v_r.push_back(r);
    
    PRINT_DEBUG( " sigma Acc r eff : cat " + to_string(cat) + " bin " + to_string(cat) +
		 " element " + to_string(cat) + "-" + to_string(i) +
		 " channel: " + to_string(ChNum) + " " + GetChannelName(ChNum) );
    PRINT_DEBUG( " sigma: " + to_string(EvalXS(m_process[m_ProdMode], ChNum) ) );
    PRINT_DEBUG( " Acc: " + to_string(m_acc[ChNum].at(i).first) );
    PRINT_DEBUG( " r:   " + to_string(m_r[ChNum].at(i).first) );
    PRINT_DEBUG( " Eff: " + to_string(m_cf[ChNum].at(Pos+i).first) );
    PRINT_DEBUG( " -------------" );
  }

  int vCat = cat;
  if(m_Fiducial) vCat = chPos;
  else           vCat = chCatPos*int(m_Category.size()/m_channels.size())+cat;//chCatPos*(int)m_channels.size()+cat;
  
  notFid   = new RooRealVar( ("notFid_"+m_Category.at(vCat)).c_str() , //cat
			     ("notFid_"+m_Category.at(vCat)).c_str() , //cat
			     m_notFid[ChNum].at(cat).second, 0, 1 );

  minitree = new RooRealVar( ("Nminitree_"+m_Category.at(vCat)).c_str() , //cat
			     ("Nminitree_"+m_Category.at(vCat)).c_str() , //cat
			     m_MinitreeN[ChNum].at(cat).first, 0, 100 );          /// 1 scaling per bin
  
  v_notFid.push_back(notFid);

  RooRealVar *dummy = new RooRealVar("dummy","dummy",1);
  RooArgList rooarglist;
  rooarglist.add(*sigma);                         list->add(*sigma); //@0
  rooarglist.add(*m_Lumi);                        list->add(*m_Lumi);//@1
  rooarglist.add(*BRZZ);                          list->add(*BRZZ);  //@2
  rooarglist.add(*dummy);                         list->add(*dummy); //@3
  m_globalObservables.add(*sigma);
  m_globalObservables.add(*m_Lumi);
  m_globalObservables.add(*BRZZ);
  m_globalObservables.add(*dummy);

  RooStats::HistFactory::FlexibleInterpVar *sysblockglobal = NULL;
  RooStats::HistFactory::FlexibleInterpVar *sysblockbin    = NULL;
  RooStats::HistFactory::FlexibleInterpVar *sysblockfid    = NULL;
  
  if(m_addSys){
    sysblockglobal = makeSysGlobal("global", ChNum, 0, cat, true, false);
    rooarglist.add(*sysblockglobal);
    list->add(*sysblockglobal);    
  }
  
  double threshold = 0.0;  // threshold for the diagonal elements of the response matrix
  for (int i=0; i < MAX; ++i ){

    if( ! (v_eff.at(i)->getVal() > threshold) ) continue; 
    rooarglist.add(*v_sigma.at(i));               list->add(*v_sigma.at(i));              //@4
    rooarglist.add(*v_A.at(i));                   list->add(*v_A.at(i));                  //@5
    rooarglist.add(*v_eff.at(i));                 list->add(*v_eff.at(i));                //@6
    rooarglist.add(*v_r.at(i));                   list->add(*v_r.at(i));                  //@7
    rooarglist.add(*m_binwidthroorealvar.at(i));  list->add(*m_binwidthroorealvar.at(i)); //@8
    m_globalObservables.add(*v_A.at(i));
    m_globalObservables.add(*v_eff.at(i));
    m_globalObservables.add(*v_r.at(i));
    
    if(m_addSys){
      sysblockbin = makeSysBlockMtx(ChNum, GetProcessNumber(m_ProdMode), cat, i, v_sigma, v_eff, v_A, v_r);
      rooarglist.add(*sysblockbin);
      list->add(*sysblockbin);
    }
  }
  
  rooarglist.add(*v_notFid.at(0));             list->add(*v_notFid.at(0)); //@9
  m_globalObservables.add(*v_notFid.at(0));

  if(m_addSys){
    sysblockfid = makeSysBlock("sigFnonFidSysBlock", ChNum, GetProcessNumber(m_ProdMode), cat);
    rooarglist.add(*sysblockfid);
    list->add(*sysblockfid);
  }
  
  m_Norm = NULL;
  int notFidindex = 0;
  string formula = "(@0*@1*@2)*(";
  int shiftsys = 0;
  if(m_addSys){
    formula ="(@0*@1*@2*@4)*(";
    shiftsys = 1;
  }
  for ( int i=0; i < (rooarglist.getSize()-4-shiftsys-1)/(5+shiftsys) /*m_Category.size()*/; ++i ){  
    string tmp;
    tmp  = "(@"+ to_string(4+shiftsys+(5+shiftsys)*i) + "*@";
    tmp += to_string(5+shiftsys+(5+shiftsys)*i) + "*@";
    tmp += to_string(6+shiftsys+(5+shiftsys)*i) + "*@";
    tmp += to_string(7+shiftsys+(5+shiftsys)*i) ;//+ "*@";
    //tmp += to_string(8+shiftsys+(5+shiftsys)*i);
    string tmpsys = (m_addSys == true) ? "*@"+ to_string(9+shiftsys+(5+shiftsys)*i)+")+" : ")+";
    tmp += tmpsys;
    formula = formula+tmp;
    if (i+1>=(rooarglist.getSize()-4-shiftsys)/(5+shiftsys) /*m_Category.size()*/ ) {
      formula.resize(formula.size()-1);
      formula = formula+")";
      notFidindex = 8+2*shiftsys+(5+shiftsys)*i+1;
    }
  }

  formula += "*(1+@"+to_string(notFidindex);
  if(m_addSys) formula += "*@"+to_string(rooarglist.getSize()-1);
  formula += ")";
  
  PRINT_DEBUG (" Norm Formula: " + formula);
  
  m_Norm = new RooFormulaVar( ("norm_"+m_Category.at(vCat)).c_str(),
                               formula.c_str(), rooarglist);
  
  PRINT_DEBUG ("category: " + to_string(cat) );
  PRINT_DEBUG_OBJECT(m_Norm);
  PRINT_DEBUG("Normalization from input: "+to_string(minitree->getVal())+
	      ", Normalization from histograms: "+
	      to_string(m_hremapped->GetBinContent(cat+1)*m_binwidth.at(cat))+
	      ", Normalization from Formula: " +to_string(m_Norm->getVal()/m_lumi));
  if ( TMath::Abs(1-((m_Norm->getVal()/m_lumi)/(minitree->getVal()))) > 0.008) {
    dumpAllInformation(cat, m_Norm, minitree, rooarglist);
  }
  
  PRINT_DEBUG ("<SignalNormFactorMatrix()>");

  return m_Norm;
  
}

RooFormulaVar* WorkSpaceMaker :: BackgroundNormFactor(int cat, int chNum, RooArgList* list,
						      TH1F* h, string process){
  
  PRINT_DEBUG_FUNCTION ("<BackgroundNormFactor()> :: Making Background Normalization Factor" +
			to_string(cat) );
  
  int channelCatPos = chNum-1;
  if( m_channels.size()==1 ) channelCatPos = 0;
  if( m_chSplit == 1 )       channelCatPos = chNum-5;

  double normbin = h->GetBinContent(cat+1);
  if(normbin==0) normbin = 0.000000000001;
  
  RooRealVar *expperfb = new RooRealVar( ("expperfb_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))+process).c_str(),
					 ("expperfb_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))+process).c_str(),
					 /*h->GetBinContent(cat+1)*/ normbin) ;

  //RooRealVar *MuqqZZ = new RooRealVar( "MuqqZZ", "MuqqZZ", 1,0,2 );
  
  RooRealVar *MuqqZZ = NULL;
  MuqqZZ = retrieveMuqqZZ(cat);

  if( m_Fiducial ) expperfb->setVal( h->Integral() ) ;
  RooArgList rooarglist;
  rooarglist.add(*m_Lumi);                       //list->add(*m_Lumi);                     //@0
  rooarglist.add(*m_binwidthroorealvar.at(cat)); list->add(*m_binwidthroorealvar.at(cat)); //@1
  rooarglist.add(*expperfb);                     list->add(*expperfb);                     //@2
  if(process=="qqZZ" || process=="ggZZ") rooarglist.add(*MuqqZZ); //@3
  if(!m_floatqqZZ) MuqqZZ->setConstant(1); 
  if(m_bkgOption != "none"){
    if (m_floatqqZZ) MuqqZZ->setConstant(0); 
    else MuqqZZ->setConstant(1);
  }
  m_globalObservables.add(rooarglist);
  
  m_Norm = NULL;

  if( m_addSys ) {
    
    if (process=="redBkg"){
      RooStats::HistFactory::FlexibleInterpVar *sysblock = makeSysBlock("bkgSysBlock", chNum, m_process.at(process), cat);
      rooarglist.add(*sysblock); list->add(*sysblock); //@3
      m_Norm = new RooFormulaVar( ("norm_bkg_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))+process).c_str(),
				  "(@0*@1*@2*@3)", rooarglist);
    }
    else {
      
      RooStats::HistFactory::FlexibleInterpVar *sysblock1 = makeSysBlock("bkgSysBlock", chNum, m_process.at(process), cat);
      
      bool isggZZ = false;
      if(process=="ggZZ") isggZZ = true; 
      else isggZZ = false;
      
      RooStats::HistFactory::FlexibleInterpVar *sysblock2 = makeSysGlobal("global", chNum, 0, cat, false, isggZZ);
      
      rooarglist.add(*sysblock1); list->add(*sysblock1); //@4
      if(!m_floatqqZZ){ rooarglist.add(*sysblock2); list->add(*sysblock2); } //@5
      
      if(m_floatqqZZ) m_Norm = new RooFormulaVar( ("norm_bkg_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))+process).c_str(),
						  "(@0*@1*@2*@3*@4)", rooarglist );
      else m_Norm = new RooFormulaVar( ("norm_bkg_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))+process).c_str(),
				       "(@0*@1*@2*@4*@5)", rooarglist );
    }
  }
  else {
    
    if(process=="qqZZ" || process=="ggZZ"){
      m_Norm = new RooFormulaVar( ("norm_bkg_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))+process).c_str(),
				  "(@0*@1*@2*@3)",rooarglist );
    }
    else{
      m_Norm = new RooFormulaVar( ("norm_bkg_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))+process).c_str(),
				  "(@0*@1*@2)",rooarglist );
    }
  }
  PRINT_DEBUG ( process );
  PRINT_DEBUG ( " <BackgroundNormFactor()> ");
  PRINT_DEBUG ( " Normalization cat #: " + to_string(cat) + " " + to_string(m_Norm->getVal()));
  PRINT_DEBUG ( " Process ID: "  + to_string(m_process.at(process)));
  return m_Norm;
  
}


void WorkSpaceMaker :: dumpAllInformation(int cat, RooFormulaVar* m_Norm,
					  RooRealVar* minitree, RooArgList rooarglist){
  
  PRINT_FATAL( " bad normalization check all numbers below : 0.8% threshold exceeded" );
  PRINT_ERROR( " Histogram Content: " + to_string(m_h->GetBinContent(cat+1)) +
	       " Minitree norm:  "+ to_string(minitree->getVal()) +
	       " Formula Norm: " + to_string(m_Norm->getVal()/m_lumi) +
	       " ratio: " + to_string((m_Norm->getVal()/m_lumi)/minitree->getVal()) );
  PRINT_DEBUG_OBJECT(&rooarglist,1);
  PRINT_DEBUG_OBJECT(m_h);
  PRINT(" BinWidth saved: "+ to_string(m_binwidth.at(cat)));
  PRINT(" Bin Range original: " + to_string(m_h->GetBinLowEdge(cat+1)) +" "
	+ to_string( m_h->GetBinLowEdge(cat+1)+m_h->GetBinWidth(cat+1) ));
  PRINT_ERROR( " Check all numbers above ");
  PRINT_ERROR( " Advice 1: check Acceptance definition e.g. truth range vs histogram range");
  PRINT_ERROR( " Advice 2: check type: unconstrained vs FSR vs constrained");
  PRINT_ERROR( " Advice 3: check cross section and BR of the sample");
  PRINT_ERROR( " Advice 4: check variables range definition (i.e. sigmacat)");
  PRINT_ERROR( " exit!!!!");
  exit(0);
  
}



RooFormulaVar* WorkSpaceMaker :: SignalNormFactor(int cat, int ChNum, RooArgList* list){

  PRINT_DEBUG_FUNCTION ("<SignalNormFactor()> :: Making Signal Normalization Factor for category: "+ to_string(cat));
  
  int Pos = cat;
  int channelCatPos = ChNum-1;
  if( m_channels.size()==1 ) channelCatPos = 0;
  if( m_chSplit == 1 )       channelCatPos = ChNum-5;

  vector<string> variablesname;
  if(m_ProdMode == "AllProd")        variablesname = {"ggH","VBF","WH","ZH","ttH","bbH"};
  else if(m_ProdMode == "MergProd" ) variablesname = {"ggHbbH","VBF","VH","ttH"};
  else                               variablesname = {m_ProdMode};

  string relativefraction = "AllSig";
  if( m_ProdMode != "AllProd" && m_ProdMode != "MergProd" ) relativefraction = m_ProdMode;
  
  RooRealVar *minitree = NULL;

  double minitreeval = m_MinitreeN[ChNum].at(int(Pos)).first;
  if( m_ProdMode != "AllProd" && m_ProdMode != "MergProd" )
    minitreeval = m_MinitreeN[ChNum].at(int(Pos)+int(m_Category.size()/m_channels.size()*m_process[variablesname.at(0)])).first;
  
  if (m_Fiducial) {
    if ( m_ProdMode != "AllProd" && m_ProdMode != "MergProd" )
      minitreeval = m_MinitreeN[ChNum].at(int(Pos)+int(m_Category.size()/m_channels.size()*m_process[variablesname.at(0)])).first;
    else
      minitreeval = m_MinitreeN[ChNum].at(int(Pos)).first;
  }
  minitree = new RooRealVar( ("Nminitree_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			     ("Nminitree_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			     minitreeval, 0, 100 );          /// 1 scaling per bin
  
  
  RooRealVar *sigma = new RooRealVar( "sigma","sigma",1,-1000, 100000 );
  RooRealVar *BRZZ  = new RooRealVar( ("BR_ZZ_"+GetChannelName(ChNum)).c_str(),
				      ("BR_ZZ_"+GetChannelName(ChNum)).c_str(),
				      m_br.at(ChNum).first, 0, 1000 );
  
  RooRealVar *sigmacat = new RooRealVar( ("sigma_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str(),
					 ("sigma_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str(),
					 EvalXS(Pos, ChNum)/*/m_binwidth.at(Pos)*/, -1000, 100000 );

  RooArgList rooarglist;
  rooarglist.add(*sigma);                        list->add(*sigma);                        //@0
  rooarglist.add(*m_Lumi);                       list->add(*m_Lumi);                       //@1
  rooarglist.add(*BRZZ);                         list->add(*BRZZ);                         //@2
  rooarglist.add(*sigmacat);                     list->add(*sigmacat);                     //@3
  rooarglist.add(*m_binwidthroorealvar.at(cat)); list->add(*m_binwidthroorealvar.at(cat)); //@4
  RooRealVar *A = NULL;
  RooRealVar *C = NULL;
  RooRealVar *r = NULL;
  RooRealVar *f = NULL;
  RooRealVar *notFid  = NULL;
  vector <RooRealVar *> v_notFid;
  
  for (unsigned int i=0; i < variablesname.size(); ++i ){
    int position = 0;
    if (m_Fiducial) position =  m_process[variablesname.at(i)] ;
    else  position = int(Pos + m_process[variablesname.at(i)]*(int(m_Category.size()/m_channels.size())) ) ;
    PRINT_DEBUG( " position map " + to_string(position) ) ;
    
    A       = new RooRealVar( ("A_"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      ("A_"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      m_acc[ChNum].at(position).first, 0, 10 );
    
    C       = new RooRealVar( ("C_"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      ("C_"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      m_cf[ChNum].at(position).first, 0, 10 );
    r       = new RooRealVar( ("dummy"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      ("dummy"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      1/*m_r[ChNum].at(position).first*/, 1, 1 );
    f       = new RooRealVar( ("f_"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      ("f_"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      ProcessXS(m_process[variablesname.at(i)],cat, ChNum) / ProcessXS(m_process[relativefraction],cat, ChNum), 0, 10 );
    
    notFid  = new RooRealVar( ("notFid_"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      ("notFid_"+variablesname.at(i)+"_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str() ,
			      m_Lumi->getVal()*m_notFid[ChNum].at(position).first, 0, 100 );

    rooarglist.add(*r); list->add(*r); //@5
    rooarglist.add(*A); list->add(*A); //@6
    rooarglist.add(*C); list->add(*C); //@7
    rooarglist.add(*f); list->add(*f); //@8
    v_notFid.push_back(notFid);

    string prodname = m_ProdMode;

    if(m_ProdMode == "AllProd" || m_ProdMode == "MergProd" ) prodname = "AllSig";
    PRINT_DEBUG( " sigma Acc r eff : cat " + to_string(cat) + " bin " + to_string(cat) +
		 " channel: " + to_string(ChNum) + " " + GetChannelName(ChNum) );
    PRINT_DEBUG( " sigma: " + to_string(sigmacat->getVal()) );
    PRINT_DEBUG( " Acc: " + to_string(m_acc[ChNum].at(position).first) );
    PRINT_DEBUG( " r:   " + to_string(m_r[ChNum].at(position).first) );
    PRINT_DEBUG( " Eff: " + to_string(m_cf[ChNum].at(position).first) );
    PRINT_DEBUG( " f: " + to_string(f->getVal()));
    PRINT_DEBUG( " notFid: " + to_string(notFid->getVal()));
    PRINT_DEBUG( " -------------" );
  }

  m_paramOfInterest->add(*sigmacat);
  m_globalObservables.add(rooarglist);
  m_globalObservables.remove(*sigmacat);
  m_Norm = NULL;
  string normformula = "";

  if(m_addSys) {
    
    RooStats::HistFactory::FlexibleInterpVar *sysblock1 = makeSysGlobal("global", ChNum, 0, cat, true, false);  // --> to be changed in to m_process[variablesname.at(0)]
    RooStats::HistFactory::FlexibleInterpVar *sysblock2 = makeSysBlock("sigSysBlock1", ChNum, m_process[variablesname.at(0)], cat);
    RooStats::HistFactory::FlexibleInterpVar *sysblock3 = NULL;
    RooStats::HistFactory::FlexibleInterpVar *sysblock4 = NULL;
    RooStats::HistFactory::FlexibleInterpVar *sysblock5 = NULL;
    RooStats::HistFactory::FlexibleInterpVar *sysblock6 = NULL;
    RooStats::HistFactory::FlexibleInterpVar *sysblock7 = NULL;

    if(m_ProdMode == "MergProd" || m_ProdMode == "AllProd"){
      sysblock3 = makeSysBlock("sigSysBlock2", ChNum, m_process[variablesname.at(1)], cat);
      sysblock4 = makeSysBlock("sigSysBlock3", ChNum, m_process[variablesname.at(2)], cat);
      sysblock5 = makeSysBlock("sigSysBlock4", ChNum, m_process[variablesname.at(3)], cat);
    }
    
    if (m_ProdMode == "AllProd"){
      sysblock6 = makeSysBlock("sigSysBlock5", ChNum, m_process[variablesname.at(4)], cat);
      sysblock7 = makeSysBlock("sigSysBlock6", ChNum, m_process[variablesname.at(5)], cat);
      
    }
    rooarglist.add(*sysblock1); list->add(*sysblock1); //@23
    rooarglist.add(*sysblock2); list->add(*sysblock2); //@24
    
    if(m_ProdMode == "MergProd" || m_ProdMode == "AllProd"){
      rooarglist.add(*sysblock3); list->add(*sysblock3); //@25
      rooarglist.add(*sysblock4); list->add(*sysblock4); //@26
      rooarglist.add(*sysblock5); list->add(*sysblock5); //@27
    }
    
    if (m_ProdMode == "AllProd"){
      rooarglist.add(*sysblock6); list->add(*sysblock6); //@28
      rooarglist.add(*sysblock7); list->add(*sysblock7); //@29
    }
    if (m_ProdMode == "AllProd"){
      normformula  = "(@0*@1*@2*@3*@29)*((@5*@6*@7*@8*@30)";
      normformula += " + (@9*@10*@11*@12*@31) + (@13*@14*@15*@16*@32)";
      normformula += " + (@17*@18*@19*@20*@33) + (@21*@22*@23*@24*@34)";
      normformula += " + (@25*@26*@27*@28*@35) )";
    }
    else if (m_ProdMode == "MergProd"){
      normformula  = "(@0*@1*@2*@3*@21)*((@5*@6*@7*@8*@22)";
      normformula += " + (@9*@10*@11*@12*@23) + (@13*@14*@15*@16*@24)";
      normformula += " + (@17*@18*@19*@20*@25) )";
    }
    else{
      normformula = "(@0*@1*@2*@3*@9)*((@5*@6*@7*@8*@10))";
    }
    
    if (m_cfsplit){
      for (unsigned int i=0; i < v_notFid.size(); ++i ) {
        rooarglist.add(*v_notFid.at(i)); list->add(*v_notFid.at(i)); //@30
      }
      
      if (m_ProdMode == "AllProd")       normformula += "+(@36+@37+@38+@39+@40)";
      else if (m_ProdMode == "MergProd") normformula += "+(@26+@27+@28+@29)";
      else                               normformula += "+(@23)";
    }
    
  }
  else{
    if (m_ProdMode == "AllProd"){
      normformula  = "(@0*@1*@2*@3)*((@5*@6*@7*@8)"; 
      normformula += " + (@9*@10*@11*@12) + (@13*@14*@15*@16)";
      normformula += " + (@17*@18*@19*@20)  + (@21*@22*@23*@24)";
      normformula += " + (@25*@26*@27*@28) )";
    }
    else if (m_ProdMode == "MergProd"){
      normformula  = "(@0*@1*@2*@3)*((@5*@6*@7*@8)";
      normformula += " + (@9*@10*@11*@12) + (@13*@14*@15*@16)";
      normformula += " + (@17*@18*@19*@20) )";
    }
    else{
      normformula = "(@0*@1*@2*@3)*((@5*@6*@7*@8))";
    }
    
    if (m_cfsplit){
      for (unsigned int i=0; i < v_notFid.size(); ++i ) {
        rooarglist.add(*v_notFid.at(i)); list->add(*v_notFid.at(i)); //@30
      }
      
      if (m_ProdMode == "AllProd")       normformula += "+(@29+@30+@31+@32+@33)";
      else if (m_ProdMode == "MergProd") normformula += "+(@21+@22+@23+@24)";
      else                               normformula += "+(@9)";
    }
    
  }

  PRINT_DEBUG (" Norm Formula: " + normformula);
  m_Norm = new RooFormulaVar( ("norm_"+m_Category.at(cat+(channelCatPos)* int(m_Category.size()/m_channels.size()))).c_str(),
			      normformula.c_str(), rooarglist);
  
  PRINT_DEBUG ("category: " + to_string(cat) );
  PRINT_DEBUG_OBJECT(m_Norm);
  if (m_Fiducial)
    PRINT_DEBUG("Normalization from input: "+to_string(minitree->getVal())+
		", Normalization from histograms: "+to_string(m_hremapped->Integral())+
		", Normalization from Formula: " +to_string(m_Norm->getVal()/m_lumi));
  else
    PRINT_DEBUG("Normalziation from input: "+to_string(minitree->getVal())+
		", Normalization from histograms: "+
		to_string(m_hremapped->GetBinContent(cat+1)*m_binwidth.at(cat))+
		", Normalization from Formula: " +to_string(m_Norm->getVal()/m_lumi));
  
  if ( TMath::Abs(1-((m_Norm->getVal()/m_lumi)/(minitree->getVal()))) > 0.008) {
    dumpAllInformation(cat, m_Norm, minitree, rooarglist);
  }
  
  PRINT_DEBUG ("<SignalNormFactor()>");
  
  return m_Norm;
  
}

RooRealVar* WorkSpaceMaker :: retrieveMuqqZZ(int cat){

  RooRealVar *mu = NULL;
  
  std::vector<int> bin_ranges = GetVarBinRange(m_VariableId);
  
  for (unsigned int i =0; i < bin_ranges.size(); ++i){
    if ( cat < bin_ranges.at(i) ){
      mu = new RooRealVar(("MuqqZZ"+to_string(i)).c_str(), ("MuqqZZ"+to_string(i)).c_str(), 1,-2,4 );
      break;
    }
  }

  return mu;
}
