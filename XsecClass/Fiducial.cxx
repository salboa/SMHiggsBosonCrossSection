#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: doFiducialSumChannels(){

  PRINT_BEGIN_FUNCTION(" <doFiducialSumChannels()>:: evaluating fiducial xsec summing all channels");
  
  setAcceptance();
  if (m_floatqqZZ){
    for (unsigned int i =0; i < GetVarBinRange(m_VariableId).size(); ++i){
      m_ws->var(("MuqqZZ"+to_string(i)).c_str())->setConstant(0);
    }
  }

  double val = ( m_ws->var("sigma_4mu")->getVal()*m_ws->var("BR_ZZ_4mu")->getVal()    +
		 m_ws->var("sigma_4e")->getVal()*m_ws->var("BR_ZZ_4e")->getVal()      +
		 m_ws->var("sigma_2e2mu")->getVal()*m_ws->var("BR_ZZ_2e2mu")->getVal()+
		 m_ws->var("sigma_2mu2e")->getVal()*m_ws->var("BR_ZZ_2mu2e")->getVal() );

  m_ws->factory("expr::sigma_4mup('@0-@1-@2-@3',sigma_sum[1,0,10], sigma_4e, sigma_2e2mu, sigma_2mu2e)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_4mu=sigma_4mup)");
  m_ws->var("sigma_sum")->setVal(val);
  
  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma_sum"));
  tmp_poi.add( *m_ws->var("sigma_4e"));
  tmp_poi.add( *m_ws->var("sigma_2e2mu"));
  tmp_poi.add( *m_ws->var("sigma_2mu2e"));

  m_ws->var("sigma_4e")->setVal(m_ws->var("sigma_4e")->getVal()*m_ws->var("BR_ZZ_4e")->getVal());
  m_ws->var("sigma_2e2mu")->setVal(m_ws->var("sigma_2e2mu")->getVal()*m_ws->var("BR_ZZ_2e2mu")->getVal());
  m_ws->var("sigma_2mu2e")->setVal(m_ws->var("sigma_2mu2e")->getVal()*m_ws->var("BR_ZZ_2mu2e")->getVal());
  
  for ( unsigned int i = 0; i < m_Category.size(); ++i){
    m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
  }

  m_modelConfig->SetParametersOfInterest(tmp_poi);
  m_ws->import(*m_modelConfig, true);
  m_ws->var("sigma_sum")->Print();

  m_Variable+="_fidsum";
  PRINT_END_FUNCTION(" <doFiducialSumChannels()>");
  
}

void WorkSpaceMaker :: doFiducialSingleChannel(){
  
  PRINT_BEGIN_FUNCTION(" <doFiducialSingleChannel()>:: evaluating fiducial xsec");

  setAcceptance();
  m_Variable+="_fidchannel";
  PRINT_END_FUNCTION(" <doFiducialSingleChannel()>");
  
}

void WorkSpaceMaker :: doFiducial4l(){
  
  PRINT_BEGIN_FUNCTION(" <doFiducial4l()>:: evaluating fiducial xsec for 4l (4e+4mu) category");
  
  setAcceptance();
  double val = ( m_ws->var("sigma_4mu")->getVal()*m_ws->var("BR_ZZ_4mu")->getVal()+
		 m_ws->var("sigma_4e")->getVal()*m_ws->var("BR_ZZ_4e")->getVal() );
  
  m_ws->factory("expr::sigma_4mup('@0-@1',sigma_4l[1,0,10], sigma_4e)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_4mu=sigma_4mup)");
  m_ws->var("sigma_4l")->setVal(val);
  
  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma_4l"));
  tmp_poi.add( *m_ws->var("sigma_4e"));
  tmp_poi.add( *m_ws->var("sigma_2e2mu"));
  tmp_poi.add( *m_ws->var("sigma_2mu2e"));
  
  m_ws->var("sigma_4e")->setVal(m_ws->var("sigma_4e")->getVal()*m_ws->var("BR_ZZ_4e")->getVal());
  m_ws->var("sigma_2e2mu")->setVal(m_ws->var("sigma_2e2mu")->getVal()*m_ws->var("BR_ZZ_2e2mu")->getVal());
  m_ws->var("sigma_2mu2e")->setVal(m_ws->var("sigma_2mu2e")->getVal()*m_ws->var("BR_ZZ_2mu2e")->getVal());
  
  for ( unsigned int i = 0; i < m_Category.size(); ++i){
    m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
  }
  
  m_modelConfig->SetParametersOfInterest(tmp_poi);
  m_ws->import(*m_modelConfig, true);
  
  m_Variable+="_fid4l";
  PRINT_END_FUNCTION(" <doFiducial4l()>");
  
}

void WorkSpaceMaker :: doFiducial2l2l(){
  
  PRINT_BEGIN_FUNCTION(" <doFiducial2l2l()>:: evaluating fiducial xsec 2l2l (2e2mu+2mu2e) category");
  
  setAcceptance();
  double val = ( m_ws->var("sigma_2e2mu")->getVal()*m_ws->var("BR_ZZ_2e2mu")->getVal()+
		 m_ws->var("sigma_2mu2e")->getVal()*m_ws->var("BR_ZZ_2mu2e")->getVal() );
  
  m_ws->factory("expr::sigma_2e2mup('@0-@1',sigma_2l2l[1,0,10], sigma_2mu2e)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_2e2mu=sigma_2e2mup)");
  
  m_ws->var("sigma_2l2l")->setVal(val);
  
  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma_2l2l"));
  tmp_poi.add( *m_ws->var("sigma_2mu2e"));
  tmp_poi.add( *m_ws->var("sigma_4mu"));
  tmp_poi.add( *m_ws->var("sigma_4e"));
  
  m_ws->var("sigma_4e")->setVal(m_ws->var("sigma_4e")->getVal()*m_ws->var("BR_ZZ_4e")->getVal());
  m_ws->var("sigma_4mu")->setVal(m_ws->var("sigma_4mu")->getVal()*m_ws->var("BR_ZZ_4mu")->getVal());
  m_ws->var("sigma_2mu2e")->setVal(m_ws->var("sigma_2mu2e")->getVal()*m_ws->var("BR_ZZ_2mu2e")->getVal());
  
  for ( unsigned int i = 0; i < m_Category.size(); ++i){
    m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
  }
  
  m_modelConfig->SetParametersOfInterest(tmp_poi);
  m_ws->import(*m_modelConfig, true);
  
  m_Variable+="_fid2l2l";
  PRINT_END_FUNCTION(" <doFiducial2l2l()>");
  
}

void WorkSpaceMaker :: doFiducialTotal(){
  
  PRINT_BEGIN_FUNCTION(" <doFiducialTotal()>:: evaluating fiducial total xsec");

  double val = m_ws->var("sigma_4mu")->getVal();
  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma"));
  m_ws->var("sigma")->setVal(val); m_ws->var("sigma")->setConstant(0);
  m_ws->var("sigma")->setRange(0,100000.);
  if (m_floatqqZZ){
    for (unsigned int i =0; i < GetVarBinRange(m_VariableId).size(); ++i){
      m_ws->var(("MuqqZZ"+to_string(i)).c_str())->setConstant(0);
    }
  }

  /*
  m_ws->factory("EDIT::simPdf(simPdf, sigma_2e2mu=sigma_4mu)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_4e=sigma_4mu)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_2mu2e=sigma_4mu)");
*/
  for ( unsigned int i = 0 ;i < m_Category.size(); ++i){
    m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setVal(1);
    m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setConstant(1);
  }
  
  m_modelConfig->SetParametersOfInterest(tmp_poi);
  m_ws->import(*m_modelConfig, true);
  m_ws->var("sigma")->Print();
  m_Variable+="_total";
  PRINT_END_FUNCTION(" <doFiducialTotal()>");
  
}

void WorkSpaceMaker :: setAcceptance(){

  PRINT_BEGIN_FUNCTION(" <setAcceptance()>:: setting Acceptance value");
  RooRealVar *tmp = NULL;

  TIterator *iteratorPOI= m_modelConfig->GetParametersOfInterest()->createIterator();
  while ( (tmp = (RooRealVar*)iteratorPOI->Next()) ) {
    TString name = tmp->GetName();
    name.ReplaceAll("sigma_","");

    if (m_matrix){
      TString ch = name;
      if(!m_Fiducial) ch = ch.Replace(0,ch.First("_")+1,"");
      m_ws->var( ("sigma_"+name) )->setVal( m_ws->var(("sigma_"+name))->getVal()*
					    m_ws->var("BR_ZZ_"+ch)->getVal()    *
					    m_ws->var(("A_"+name))->getVal()    *
					    m_ws->var(("r_"+name))->getVal() );
    }
    else{
      TString ch  = name, chn = name;
      if(!m_Fiducial) ch = ch.Replace(ch.First("_"),ch.Length(),"");
      if(m_Fiducial) chn = to_string(GetChannelID("4mu")-1);
      else           chn = ch;
      
      if (m_ProdMode == "MergProd")
	m_ws->var(("sigma_"+name))->setVal( ( ((RooFormulaVar*) m_ws->obj(("norm_"+name)))->getVal()/
					      ( (m_ws->var(("C_ggHbbH_"+name))->getVal()*m_ws->var(("f_ggHbbH_"+name))->getVal()+
						 m_ws->var(("C_VBF_"+name))->getVal()*m_ws->var(("f_VBF_"+name))->getVal()      +
						 m_ws->var(("C_VH_"+name))->getVal()*m_ws->var(("f_VH_"+name))->getVal()        +
						 m_ws->var(("C_ttH_"+name))->getVal()*m_ws->var(("f_ttH_"+name))->getVal())
						*m_ws->var("L")->getVal() ) ));///m_ws->var("BinWidth_"+chn)->getVal() );
      
      else if (m_ProdMode == "AllProd")
	m_ws->var(("sigma_"+name))->setVal( ( ((RooFormulaVar*) m_ws->obj(("norm_"+name)))->getVal()/
					      ( (m_ws->var(("C_ggH_"+name))->getVal()*m_ws->var(("f_ggH_"+name))->getVal()+
						 m_ws->var(("C_VBF_"+name))->getVal()*m_ws->var(("f_VBF_"+name))->getVal()+
						 m_ws->var(("C_WH_"+name))->getVal()*m_ws->var(("f_WH_"+name))->getVal()  +
						 m_ws->var(("C_ZH_"+name))->getVal()*m_ws->var(("f_ZH_"+name))->getVal()  +
						 m_ws->var(("C_bbH_"+name))->getVal()*m_ws->var(("f_bbH_"+name))->getVal()+
						 m_ws->var(("C_ttH_"+name))->getVal()*m_ws->var(("f_ttH_"+name))->getVal())
						*m_ws->var("L")->getVal() ) ));///m_ws->var("BinWidth_"+chn)->getVal()  );
      
      else  m_ws->var(("sigma_"+name))->setVal( ( ((RooFormulaVar*) m_ws->obj(("norm_"+name)))->getVal()/
						  ( (m_ws->var(("C_"+m_ProdMode+"_"+name))->getVal()  *
						     m_ws->var(("f_"+m_ProdMode+"_"+name))->getVal()) *
						    m_ws->var("L")->getVal() ) ));///m_ws->var("BinWidth_"+chn)->getVal() );
    }
  }
  TIterator *iterator= m_modelConfig->GetGlobalObservables()->createIterator();
  while ( (tmp = (RooRealVar*)iterator->Next()) ) {
    if ( string(tmp->GetName()).find("ATLAS")==string::npos &&
	 ( string(tmp->GetName()).find("BR")!=string::npos   ||
	   string(tmp->GetName()).find("A_")!=string::npos   ||
	   /*string(tmp->GetName()).find("f_")!=string::npos ||*/
	   string(tmp->GetName()).find("r_")!=string::npos    ) &&
	 string(tmp->GetName()).find("eff_")==string::npos ){
      tmp->setVal(1);
      tmp->setConstant(1);
    }
  }

  TIterator *iteratorNP= NULL;
  if (m_addSys){
    iteratorNP =  m_modelConfig->GetNuisanceParameters()->createIterator();
    while ( (tmp = (RooRealVar*)iteratorNP->Next()) ) {
      if ( string(tmp->GetName()).find("_tot")!=string::npos){
        PRINT_DEBUG (" fix " + string(tmp->GetName()) + " to 1: Sys not needed for fiducial measurement!");   
        PRINT_DEBUG_OBJECT(tmp);    
        tmp->setVal(1);
        tmp->setConstant(1);
      }
    }
  }
  

  delete iterator;
  delete iteratorNP;
  delete tmp;
  PRINT_END_FUNCTION(" <setAcceptance()>");
  
}

void WorkSpaceMaker :: doFiducialComb(){
  
  PRINT_BEGIN_FUNCTION(" <doFiducialComb()>:: evaluating fiducial comb xsec");

  double val = m_ws->var("sigma_4mu")->getVal();
  double br  = ( m_ws->var("BR_ZZ_4mu")->getVal()  +
		 m_ws->var("BR_ZZ_4e")->getVal()   +
		 m_ws->var("BR_ZZ_2e2mu")->getVal()+
		 m_ws->var("BR_ZZ_2mu2e")->getVal() );
  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma"));
  m_ws->var("sigma")->setVal(val*m_acc[0].at(0).first * br);
  m_ws->var("sigma")->setConstant(0);
  if (m_floatqqZZ){
    for (unsigned int i =0; i < GetVarBinRange(m_VariableId).size(); ++i){
      m_ws->var(("MuqqZZ"+to_string(i)).c_str())->setConstant(0);
    }
  }

  for ( unsigned int i = 0 ;i < m_Category.size(); ++i){
    
    m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setVal(1);
    m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setConstant(1);
    
    if (m_ProdMode == "MergProd"){
      m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->getVal()/br); m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_ggHbbH_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_ggHbbH_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_ggHbbH_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_VBF_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_VBF_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_VBF_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_VH_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_VH_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_VH_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_ttH_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_ttH_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_ttH_"+m_Category.at(i)).c_str())->setConstant(1);
    }
    else if (m_ProdMode == "AllProd"){
      m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->getVal()/br); m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_ggH_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_ggH_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_ggH_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_VBF_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_VBF_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_VBF_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_WH_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_WH_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_WH_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_ZH_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_ZH_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_ZH_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_ttH_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_ttH_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_ttH_"+m_Category.at(i)).c_str())->setConstant(1);
      m_ws->var(("A_bbH_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_bbH_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
      m_ws->var(("A_bbH_"+m_Category.at(i)).c_str())->setConstant(1);
    }
    else {
      m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->getVal()/br);
      m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
      if(m_matrix){
	m_ws->var(("A_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
	m_ws->var(("A_"+m_Category.at(i)).c_str())->setConstant(1);
      }
      else{
	m_ws->var(("A_"+m_ProdMode+"_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("A_"+m_ProdMode+"_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first );
	m_ws->var(("A_"+m_ProdMode+"_"+m_Category.at(i)).c_str())->setConstant(1);
      }
    }
    
  }
  
  m_modelConfig->SetParametersOfInterest(tmp_poi);
  m_ws->import(*m_modelConfig, true);
  m_ws->var("sigma")->Print();
  m_Variable+="_comb";
  m_ws->var("sigma")->setRange(0,10);
  PRINT_END_FUNCTION(" <doFiducialComb()>");

}

void WorkSpaceMaker :: doFiducialBRDifference(){
  
  PRINT_BEGIN_FUNCTION(" <doFiducialBRDifference()>:: evaluating fiducial xsec 2l2l (2e2mu+2mu2e) category");
  
  //setAcceptance();

  m_ws->var("sigma_4e")->setVal(m_ws->var("sigma_4e")->getVal()*m_ws->var("BR_ZZ_4e")->getVal());
  m_ws->var("sigma_4mu")->setVal(m_ws->var("sigma_4mu")->getVal()*m_ws->var("BR_ZZ_4mu")->getVal());
  m_ws->var("sigma_2mu2e")->setVal(m_ws->var("sigma_2mu2e")->getVal()*m_ws->var("BR_ZZ_2mu2e")->getVal());
  m_ws->var("sigma_2e2mu")->setVal(m_ws->var("sigma_2e2mu")->getVal()*m_ws->var("BR_ZZ_2e2mu")->getVal());
  
  m_ws->var("sigma_2e2mu")->SetNameTitle("sigma_2l2l","sigma_2l2l");
  m_ws->var("sigma_2mu2e")->SetNameTitle("sigma_2l2l","sigma_2l2l");
  m_ws->var("sigma_4mu")->SetNameTitle("sigma_4l","sigma_4l");
  m_ws->var("sigma_4e")->SetNameTitle("sigma_4l","sigma_4l");
  
  
  
  m_ws->factory("expr::sigma_BRp('@0*@1',BRdiff[1.1036,-3,3], sigma_2l2l)");
  //m_ws->factory("expr::sigma_BRp4mu('@0+@1',BRdiff[0.123,-1,1], sigma_2l2l[1,0,2])");
  //m_ws->factory("expr::sigma_BRp4e('@0+@1',BRdiff[0.123,-1,1], sigma_2l2l)");
  //m_ws->factory("expr::sigma_BRp2mu2e('@0', sigma_2l2l)");
  //m_ws->factory("expr::sigma_BRp2e2mu('@0', sigma_2l2l)");

  //m_ws->factory("EDIT::simPdf(simPdf, sigma_4mu=sigma_BRp4mu, sigma_4e=sigma_BRp4e, sigma_2mu2e=sigma_BRp2mu2e, sigma_2e2mu=sigma_BRp2e2mu)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_4l=sigma_BRp)");

  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("BRdiff"));
  tmp_poi.add( *m_ws->var("sigma_2l2l"));


  for ( unsigned int i = 0; i < m_Category.size(); ++i){
    m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
  }
  
  m_modelConfig->SetParametersOfInterest(tmp_poi);
  m_ws->import(*m_modelConfig, true);
  
  m_Variable+="_fidBR";
  PRINT_END_FUNCTION(" <doFiducialBRDifference()>");
  
}
