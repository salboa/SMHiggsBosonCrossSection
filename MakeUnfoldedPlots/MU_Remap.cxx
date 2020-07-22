//#include "MakeUnfoldPlots.h"

void remapHisto( TGraphAsymmErrors* a, std::string MC ){
  
  float offset = 0, width = 0.5;
  if(MC=="mg"){
    offset = -0.15;
    width  = GetBarSize(m_Var).second;//0.06;
  }
  else if(MC=="hres"){
    offset = 0.15;
    width  = GetBarSize(m_Var).second;//0.06;
  }
  else if(MC=="sys"){
    offset = 0.0;
    width  = GetBarSize(m_Var).first;//0.06;
  }
  else if(MC=="obs"){
    offset = 0.0;
    width  = 0.0;
  }
  else if (MC=="nnlops"){
    offset = 0.0;
    width  = GetBarSize(m_Var).second;//0.06;
    if (m_Var!="pt" && m_Var!="y") offset =0.15;
  }
  
  double x; double y;
  for(Int_t i=0; i<a->GetN(); ++i ) {
    a->GetPoint(i,x,y);

    a->SetPoint( i, i+0.5+offset, y);
    a->SetPointError( i, width,width,
                           a->GetErrorYlow(i),
                           a->GetErrorYhigh(i) );
  }
  
}

void remapMjjHisto( TGraphAsymmErrors* a, std::string MC ){
  
  float offset  = 0;
  float width[] = { 0.5, 1.5 };
  float pos[]   = { 0.5, 2.5 };
  if(MC=="mg"){
    offset   = -0.15;
    width[0] = GetBarSize(m_Var).second; //0.05;
    width[1] = GetBarSize(m_Var).second; //0.05;
  }
  else if(MC=="sys" ){
    offset   = 0.0;
    width[0] = GetBarSize(m_Var).first; //0.0;
    width[1] = GetBarSize(m_Var).first; //0.0;
  }
  else if(MC=="obs"){
    offset   = 0.0;
    width[0] = 0.0;
    width[1] = 0.0;
  }
  else if(MC=="nnlops"){
    offset   = 0.15;
    width[0] = GetBarSize(m_Var).second; //0.05;
    width[1] = GetBarSize(m_Var).second; //0.05;
  }

  double x; double y;
  for(Int_t i=0; i<a->GetN(); ++i ) {
    a->GetPoint(i,x,y);

    a->SetPoint( i, pos[i]+offset, y);
    a->SetPointError( i, width[i], width[i],
		      a->GetErrorYlow(i),
		      a->GetErrorYhigh(i) );
  }
  
}

TH1F* remapHisto( TH1F* hIn, bool isMjj){
  
  if( m_debug )
    std::cout<< "<remapHisto()> :: remapping histogram " << hIn->GetName() << std::endl;

  std::string name = std::string(hIn->GetName())+"remapped";

  if(isMjj){
    double MjjrmRange[] = {0.0, 1.0, 4.0};
    Int_t MjjrmBins = ( (sizeof MjjrmRange)  / (sizeof *MjjrmRange)  )-1;
    m_hremapped = new TH1F( name.c_str(), name.c_str(),
			    MjjrmBins, MjjrmRange );
  }
  else
    m_hremapped = new TH1F ( name.c_str(), name.c_str(),
			     hIn->GetNbinsX(), 0, hIn->GetNbinsX() );
  m_hremapped->Print();
  for(Int_t i=1; i<hIn->GetNbinsX()+1; ++i ){
    m_hremapped->SetBinContent( i, hIn->GetBinContent(i) );
    m_hremapped->SetBinError( i, hIn->GetBinError(i) );
  }
  
  m_hremapped->Print();
  
  return m_hremapped;

}
