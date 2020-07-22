#include "WorkSpaceMaker.h"

void WorkSpaceMaker :: doFiducialSumChannels(){
  
  cout << "\033[1;32m <doFiducialSumChannels()>:: evaluating fiducial xsec summing all channels \033[0m" << endl;
  
  setAcceptance();
  m_xsminitree.at(0) = m_xsminitree.at(0)+m_xsminitree.at(1)+m_xsminitree.at(2)+m_xsminitree.at(3);

  double val = m_ws->var("sigma_4mu")->getVal()*m_ws->var("BR_ZZ_4mu")->getVal()+
               m_ws->var("sigma_4e")->getVal()*m_ws->var("BR_ZZ_4e")->getVal()+
               m_ws->var("sigma_2e2mu")->getVal()*m_ws->var("BR_ZZ_2e2mu")->getVal()+
               m_ws->var("sigma_2mu2e")->getVal()*m_ws->var("BR_ZZ_2mu2e")->getVal();

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

}

void WorkSpaceMaker :: doFiducialSingleChannel(){
  
  cout << "\033[1;32m <doFiducialSingleChannel()>:: evaluating fiducial xsec single channel \033[0m" << endl;
  setAcceptance();
  m_Variable+="_fidchannel";
  
}

void WorkSpaceMaker :: doFiducial4l(){
  
  cout << "\033[1;32m <doFiducial4l()>:: evaluating fiducial xsec for 4l (4e+4mu) category \033[0m" << endl;
  setAcceptance();
  m_xsminitree.at(0) = m_xsminitree.at(0)+m_xsminitree.at(1);
  double val = m_ws->var("sigma_4mu")->getVal()*m_ws->var("BR_ZZ_4mu")->getVal()+
               m_ws->var("sigma_4e")->getVal()*m_ws->var("BR_ZZ_4e")->getVal();
  
  m_ws->factory("expr::sigma_4mup('@0-@1',sigma_4l[1,0,10], sigma_4e)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_4mu=sigma_4mup)");
  m_ws->var("sigma_4l")->setVal(val);
  
  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma_4l"));
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
  
}

void WorkSpaceMaker :: doFiducial2l2l(){
  
  cout << "\033[1;32m <doFiducial2l2l()>:: evaluating fiducial xsec 2l2l (2e2mu+2mu2e) category \033[0m" << endl;
  
  setAcceptance();
  m_xsminitree.at(0)=m_xsminitree.at(2)+m_xsminitree.at(3);

  double val = m_ws->var("sigma_2e2mu")->getVal()*m_ws->var("BR_ZZ_2e2mu")->getVal()+
               m_ws->var("sigma_2mu2e")->getVal()*m_ws->var("BR_ZZ_2mu2e")->getVal();
  
  m_ws->factory("expr::sigma_2e2mup('@0-@1',sigma_2l2l[1,0,10], sigma_2mu2e)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_2e2mu=sigma_2e2mup)");
  
  m_ws->var("sigma_2l2l")->setVal(val);

  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma_2l2l"));
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

}

void WorkSpaceMaker :: doFiducialTotal(){
  
  
  cout << "\033[1;32m <doFiducialTotal()>:: evaluating fiducial total xsec \033[0m" << endl;
  
  double val = m_ws->var("sigma_4mu")->getVal();
  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma"));
  m_ws->var("sigma")->setVal(val); m_ws->var("sigma")->setConstant(0);
  m_ws->var("sigma")->setRange(0,100000.);
  /*
  m_ws->factory("EDIT::simPdf(simPdf, sigma_2e2mu=sigma_4mu)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_4e=sigma_4mu)");
  m_ws->factory("EDIT::simPdf(simPdf, sigma_2mu2e=sigma_4mu)");
*/
  for ( unsigned int i = 0 ;i < m_Category.size(); ++i){
    m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setConstant(1);
    
  }
  
  m_modelConfig->SetParametersOfInterest(tmp_poi);
  m_ws->import(*m_modelConfig, true);
  
  m_ws->var("sigma")->Print();
  m_Variable+="_total";
  
}

void WorkSpaceMaker :: setAcceptance(){

  cout << "\033[1;32m <setAcceptance()>:: setting Acceptance value \033[0m" << endl;

  for ( unsigned int i = 0; i < m_Category.size(); ++i){
    
    double xsold =((RooFormulaVar*) m_ws->obj(("norm_"+m_Category.at(i)).c_str()))->getVal();
    
    //// for not differential XS binwidth not present!!!!!!
    
    if( !m_Fiducial )

      m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setVal( xsold/(
								     (m_ws->var(("Cgg_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rgg_"+m_Category.at(i)).c_str())->getVal()+
								      m_ws->var(("Cvbf_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rvbf_"+m_Category.at(i)).c_str())->getVal()+
								      m_ws->var(("Cwh_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rwh_"+m_Category.at(i)).c_str())->getVal()+
								      m_ws->var(("Czh_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rzh_"+m_Category.at(i)).c_str())->getVal()+
								      m_ws->var(("Ctth_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rtth_"+m_Category.at(i)).c_str())->getVal())*
								     m_ws->var(("BinWidth_"+m_Category.at(i)).c_str())->getVal()*m_ws->var("L")->getVal()));
    
    if( m_Fiducial )

      m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setVal( xsold/(
								     (m_ws->var(("Cgg_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rgg_"+m_Category.at(i)).c_str())->getVal()+
								      m_ws->var(("Cvbf_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rvbf_"+m_Category.at(i)).c_str())->getVal()+
								      m_ws->var(("Cwh_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rwh_"+m_Category.at(i)).c_str())->getVal()+
								      m_ws->var(("Czh_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rzh_"+m_Category.at(i)).c_str())->getVal()+
								      m_ws->var(("Ctth_"+m_Category.at(i)).c_str())->getVal()*m_ws->var(("rtth_"+m_Category.at(i)).c_str())->getVal())*
								     m_ws->var("L")->getVal()));
    
    m_ws->var(("Agg_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("Agg_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Avbf_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("Avbf_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Awh_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("Awh_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Azh_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("Azh_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Atth_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("Atth_"+m_Category.at(i)).c_str())->setConstant(1);
    
    
    if( m_Fiducial ) m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setRange(-10,10);
    else {
      float negative_protection= -1*(m_ws->var(("expperfb_"+m_Category.at(i)+"qqZZ").c_str())->getVal()+m_ws->var(("expperfb_"+m_Category.at(i)+"ggZZ").c_str())->getVal()+m_ws->var(("expperfb_"+m_Category.at(i)+"redBkg").c_str())->getVal())/TMath::Max(m_ws->var(("Cgg_"+m_Category.at(i)).c_str())->getVal(), m_ws->var(("Cvbf_"+m_Category.at(i)).c_str())->getVal());
      

      m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setRange(negative_protection,5);


    }
  }
 
  
  
  if( !m_Fiducial ){
    m_ws->var("BR_ZZ")->setVal(1); m_ws->var("BR_ZZ")->setConstant(1);
  }
  else {
    for ( unsigned int i = 0; i < m_Category.size(); ++i){
      m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
      cout <<  m_ws->var(("sigma_"+m_Category.at(i)).c_str())->getVal() << endl;
    }
  }
  
}


void WorkSpaceMaker :: doFiducialComb(){
  
  
  cout << "\033[1;32m <doFiducialComb()>:: evaluating fiducial comb xsec \033[0m" << endl;
  
  double val = m_ws->var("sigma_4mu")->getVal();
  double br = m_ws->var("BR_ZZ_4mu")->getVal()+m_ws->var("BR_ZZ_4e")->getVal()+m_ws->var("BR_ZZ_2e2mu")->getVal()+m_ws->var("BR_ZZ_2mu2e")->getVal();
  RooArgSet tmp_poi;
  tmp_poi.add( *m_ws->var("sigma"));
  m_ws->var("sigma")->setVal(val*m_acc[0].at(0).first * br);
  //m_ws->var("sigma")->setRange(0,6);
  m_ws->var("sigma")->setConstant(0);
  

  for ( unsigned int i = 0 ;i < m_Category.size(); ++i){
    m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setVal(1); m_ws->var(("sigma_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setVal(m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->getVal()/br); m_ws->var(("BR_ZZ_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Agg_"+m_Category.at(i)).c_str())->setVal( m_ws->var(("Agg_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first ); m_ws->var(("Agg_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Avbf_"+m_Category.at(i)).c_str())->setVal(m_ws->var(("Avbf_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first ); m_ws->var(("Avbf_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Awh_"+m_Category.at(i)).c_str())->setVal(m_ws->var(("Awh_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first ); m_ws->var(("Awh_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Azh_"+m_Category.at(i)).c_str())->setVal(m_ws->var(("Azh_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first ); m_ws->var(("Azh_"+m_Category.at(i)).c_str())->setConstant(1);
    m_ws->var(("Atth_"+m_Category.at(i)).c_str())->setVal(m_ws->var(("Atth_"+m_Category.at(i)).c_str())->getVal()/m_acc[0].at(0).first ); m_ws->var(("Atth_"+m_Category.at(i)).c_str())->setConstant(1);

    
  }
  
  m_modelConfig->SetParametersOfInterest(tmp_poi);
  m_ws->import(*m_modelConfig, true);
  
  m_ws->var("sigma")->Print();
  m_Variable+="_comb";
  m_ws->var("sigma")->setRange(0,10);
  
}


