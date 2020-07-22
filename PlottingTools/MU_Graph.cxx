//#include "MakeUnfoldPlots.h"

TGraphAsymmErrors* makeTGraph(TH1F* nominal,TH1F* up,TH1F* down,
			      std::string MCname, bool reduceXerr,
			      bool NoYerr){
  
  float shift = 0;
  float scale = 1;
  
  if(MCname=="MG5"){
    scale = 0.8;
    shift = -GetBarSpacing(m_Var);//0.15;
  }
  if(MCname=="HRES"){
    scale = 0.1;
    shift = GetBarSpacing(m_Var);//0.15;
  }
  
  if(MCname=="NNLOPS"){
    scale = 0.2;
    shift =0.;
    shift = GetBarSpacing(m_Var);//0.15;
    //if (m_Var=="pt"|| m_Var=="y") shift = 0;
    //else 
  }
  
  double ctr = 0.5;
  if(reduceXerr) ctr = 0.4;
  
  TGraphAsymmErrors *tmp = new TGraphAsymmErrors();
  
  for(Int_t ii=0; ii<nominal->GetNbinsX(); ii++) {

    double mul = 1.0;
    if( MCname=="ExpectedFid" && ii<5 ){
      mul = 2.5;
    }

    if(m_debug)
      std::cout << "MC " <<MCname  << " Value = "
		<< nominal->GetBinContent(ii+1) << " ErrUp = "
		<< (std::abs(nominal->GetBinContent(ii+1)-up->GetBinContent(ii+1)))
		<< " ErrDw = " << (std::abs(nominal->GetBinContent(ii+1)-down->GetBinContent(ii+1))) << std::endl;
    
    tmp->SetPoint( ii, nominal->GetBinCenter(ii+1)+shift,
		   nominal->GetBinContent(ii+1)*mul );

    Double_t eYdw = (std::abs(nominal->GetBinContent(ii+1)-down->GetBinContent(ii+1)))*mul;
    Double_t eYup = (std::abs(nominal->GetBinContent(ii+1)-up->GetBinContent(ii+1)))*mul;
    if(NoYerr){
      eYdw = 0.0; eYup = 0.0;
    }

    if( MCname=="ExpectedFid" || MCname=="REST"){
      if( ii +1 == nominal->GetNbinsX()){
        tmp->SetPointError( ii, ctr*nominal->GetBinWidth(ii+1)*scale,
                          ctr*nominal->GetBinWidth(ii+1)*scale, 0, 0 );
        break;
      }
      
      tmp->SetPointError( ii, ctr*nominal->GetBinWidth(ii+1)*scale,
			  ctr*nominal->GetBinWidth(ii+1)*scale,	eYdw, eYup );
    }
    else{
      tmp->SetPointError( ii, GetBarSize(m_Var).second,
			  GetBarSize(m_Var).second, eYdw, eYup );
    }
    
  }
  
  return tmp;
  
}

TGraphAsymmErrors* makeGraph(std::vector<TGraphAsymmErrors*> obs,
			     std::string Name,
			     std::vector<double> xVal,
			     bool scale){
  
  double mul=1.0;
  if(scale) mul=2.5;

  TGraphAsymmErrors *obsChan = obs.at(0);
  TGraphAsymmErrors *obsSum  = obs.at(1);
  TGraphAsymmErrors *obs4l   = obs.at(2);
  TGraphAsymmErrors *obs2l2l = obs.at(3);
  TGraphAsymmErrors *obsTot  = obs.at(4);
  TGraphAsymmErrors *obsComb = obs.at(5);

  Int_t nChan = obsChan->GetN();
  Double_t xChan[nChan], yChan[nChan], yEuChan[nChan], yEdChan[nChan];
  for(Int_t i=0; i<nChan; i++){
    obsChan->GetPoint(i,xChan[i],yChan[i]);
    yEuChan[i] = obsChan->GetErrorYhigh(i);
    yEdChan[i] = obsChan->GetErrorYlow(i);

    if(m_debug)
      std::cout << "FidChans: x, y = " << xChan[i] << " , " << yChan[i]
		<< " yUp, yDw = " << yEuChan[i] << " , " <<  yEdChan[i]
		<< std::endl;
  }

  Int_t nSum = obsSum->GetN();
  Double_t xSum[nSum], ySum[nSum], yEuSum[nSum], yEdSum[nSum];
  for(Int_t i=0; i<nSum; i++){
    obsSum->GetPoint(i,xSum[i],ySum[i]);
    yEuSum[i] = obsSum->GetErrorYhigh(i);
    yEdSum[i] = obsSum->GetErrorYlow(i);

    if(m_debug)
      std::cout << "FidSum: x, y = " << xSum[i] << " , " << ySum[i]
		<< " yUp, yDw = " << yEuSum[i] << " , " <<  yEdSum[i]
		<< std::endl;
  }
  Int_t nComb = obsComb->GetN();
  Double_t xComb[nComb], yComb[nComb], yEuComb[nComb], yEdComb[nComb];
  for(Int_t i=0; i<nComb; i++){
    obsComb->GetPoint(i,xComb[i],yComb[i]);
    yEuComb[i] = obsComb->GetErrorYhigh(i);
    yEdComb[i] = obsComb->GetErrorYlow(i);
    
    if(m_debug)
      std::cout << "FidSum: x, y = " << xSum[i] << " , " << ySum[i]
		<< " yUp, yDw = " << yEuSum[i] << " , " <<  yEdSum[i]
		<< std::endl;
  }
  

  Int_t n4l = obs4l->GetN();
  Double_t x4l[n4l], y4l[n4l], yEu4l[n4l], yEd4l[n4l];
  for(Int_t i=0; i<n4l; i++){
    obs4l->GetPoint(i,x4l[i],y4l[i]);
    yEu4l[i] = obs4l->GetErrorYhigh(i);
    yEd4l[i] = obs4l->GetErrorYlow(i);

    if(m_debug)
      std::cout << "Fid_4l: x, y = " << x4l[i] << " , " << y4l[i]
		<< " yUp, yDw = " << yEu4l[i] << " , " <<  yEd4l[i]
		<< std::endl;
    
  }

  Int_t n2l2l = obs2l2l->GetN();
  Double_t x2l2l[n2l2l], y2l2l[n2l2l], yEu2l2l[n2l2l], yEd2l2l[n2l2l];
  for(Int_t i=0; i<n2l2l; i++){
    obs2l2l->GetPoint(i,x2l2l[i],y2l2l[i]);
    yEu2l2l[i] = obs2l2l->GetErrorYhigh(i);
    yEd2l2l[i] = obs2l2l->GetErrorYlow(i);

    if(m_debug)
      std::cout << "Fid_2l2l: x, y = " << x2l2l[i] << " , " << y2l2l[i]
		<< " yUp, yDw = " << yEu2l2l[i] << " , " <<  yEd2l2l[i]
		<< std::endl;

  }

  Int_t nTot = obsTot->GetN();
  Double_t xTot[nTot], yTot[nTot], yEuTot[nTot], yEdTot[nTot];
  for(Int_t i=0; i<nTot; i++){
    obsTot->GetPoint(i,xTot[i],yTot[i]);
    yEuTot[i] = obsTot->GetErrorYhigh(i);
    yEdTot[i] = obsTot->GetErrorYlow(i);

    if(m_debug)
      std::cout << "FidTot: x, y = " << xTot[i] << " , " << yTot[i]
		<< " yUp, yDw = " << yEuTot[i] << " , " <<  yEdTot[i]
		<< std::endl;
    
  }

  Int_t N = xVal.size();
  std::cout<<" N " << N << std::endl;
  Double_t x[N], xu[N], xd[N], y[N], yu[N], yd[N];
  for(int i=0; i<N; i++){
    x[i]  = (xVal[i+1]-xVal[i])/2.+xVal[i];
    xu[i] = 0.*(xVal[i+1]-xVal[i])/2.;
    xd[i] = 0.*(xVal[i+1]-xVal[i])/2.;
    if(i>0 && i<5){
      y[i]  = yChan[i-1]*mul;
      yu[i] = yEuChan[i-1]*mul;
      yd[i] = yEdChan[i-1]*mul;
    }
    else if(i==9){
      y[i]  = ySum[0];
      yu[i] = yEuSum[0];
      yd[i] = yEdSum[0];
    }
    else if(i==10){
      y[i]  = yComb[0];
      yu[i] = yEuComb[0];
      yd[i] = yEdComb[0];
    }
    else if(i==7){
      y[i]  = y4l[0];
      yu[i] = yEu4l[0];
      yd[i] = yEd4l[0];
    }
    else if(i==8){
      y[i]  = y2l2l[0];
      yu[i] = yEu2l2l[0];
      yd[i] = yEd2l2l[0];
    }
    else if(i==13){
      y[i]  = yTot[0]/20000.;
      yu[i] = yEuTot[0]/20000.;
      yd[i] = yEdTot[0]/20000.;
    }
    else{
      y[i]  = 0;
      yu[i] = 0;
      yd[i] = 0;
    }
    
  }
  if(m_debug){
    for(int i=0; i<N; i++)
      std::cout << "Obs TGraph - > " << "x,y = " << x[i] << " , " << y[i]
		<< " yUp, yDw = " << yu[i] << " , " << yd[i] << std::endl;
    
  }

  TGraphAsymmErrors *tmp = new TGraphAsymmErrors(N,x,y,xd,xu,yd,yu);
  tmp->SetName( Name.c_str() );
  
  return tmp;
  
}

TGraphAsymmErrors* makeSysGraph(std::vector<TGraphAsymmErrors*> obs,
				std::vector<TGraphAsymmErrors*> obsSys,
				std::string Name,
				std::vector<double> xVal,
				bool scale){

  double mul=1.0;
  if(scale) mul=2.5;

  TGraphAsymmErrors *obsChan = obs.at(0);
  TGraphAsymmErrors *obsSum  = obs.at(1);
  TGraphAsymmErrors *obs4l   = obs.at(2);
  TGraphAsymmErrors *obs2l2l = obs.at(3);
  TGraphAsymmErrors *obsTot  = obs.at(4);
  TGraphAsymmErrors *obsComb = obs.at(5);

  TGraphAsymmErrors *obsSysChan = obsSys.at(0);
  TGraphAsymmErrors *obsSysSum  = obsSys.at(1);
  TGraphAsymmErrors *obsSys4l   = obsSys.at(2);
  TGraphAsymmErrors *obsSys2l2l = obsSys.at(3);
  TGraphAsymmErrors *obsSysTot  = obsSys.at(4);
  TGraphAsymmErrors *obsSysComb = obsSys.at(5);

  Int_t nChan = obsChan->GetN();
  Double_t xChan[nChan], yChan[nChan], yEuChan[nChan], yEdChan[nChan];
  for(Int_t i=0; i<nChan; i++){
    obsChan->GetPoint(i,xChan[i],yChan[i]);
    yEuChan[i] = sqrt( pow(obsChan->GetErrorYhigh(i),2) - pow(obsSysChan->GetErrorYhigh(i),2) );
    yEdChan[i] = sqrt( pow(obsChan->GetErrorYlow(i),2) - pow(obsSysChan->GetErrorYlow(i),2) );

    if(m_debug)
      std::cout << "FidChans: x, y = " << xChan[i] << " , " << yChan[i]
		<< " yUp, yDw = " << yEuChan[i] << " , " <<  yEdChan[i]
		<< std::endl;
  }

  Int_t nSum = obsSum->GetN();
  Double_t xSum[nSum], ySum[nSum], yEuSum[nSum], yEdSum[nSum];
  for(Int_t i=0; i<nSum; i++){
    obsSum->GetPoint(i,xSum[i],ySum[i]);
    yEuSum[i] = sqrt( pow(obsSum->GetErrorYhigh(i),2) - pow(obsSysSum->GetErrorYhigh(i),2) );
    yEdSum[i] = sqrt( pow(obsSum->GetErrorYlow(i),2) - pow(obsSysSum->GetErrorYlow(i),2) );

    if(m_debug)
      std::cout << "FidSum: x, y = " << xSum[i] << " , " << ySum[i]
		<< " yUp, yDw = " << yEuSum[i] << " , " <<  yEdSum[i]
		<< std::endl;
  }
  Int_t nComb = obsComb->GetN();
  Double_t xComb[nComb], yComb[nComb], yEuComb[nComb], yEdComb[nComb];
  for(Int_t i=0; i<nComb; i++){
    obsComb->GetPoint(i,xComb[i],yComb[i]);
    yEuComb[i] = sqrt( pow(obsComb->GetErrorYhigh(i),2) - pow(obsSysComb->GetErrorYhigh(i),2) );
    yEdComb[i] = sqrt( pow(obsComb->GetErrorYlow(i),2) - pow(obsSysComb->GetErrorYlow(i),2) );
    
    if(m_debug)
      std::cout << "FidSum: x, y = " << xSum[i] << " , " << ySum[i]
		<< " yUp, yDw = " << yEuSum[i] << " , " <<  yEdSum[i]
		<< std::endl;
  }
  

  Int_t n4l = obs4l->GetN();
  Double_t x4l[n4l], y4l[n4l], yEu4l[n4l], yEd4l[n4l];
  for(Int_t i=0; i<n4l; i++){
    obs4l->GetPoint(i,x4l[i],y4l[i]);
    yEu4l[i] = sqrt( pow(obs4l->GetErrorYhigh(i),2) - pow(obsSys4l->GetErrorYhigh(i),2) );
    yEd4l[i] = sqrt( pow(obs4l->GetErrorYlow(i),2) - pow(obsSys4l->GetErrorYlow(i),2) );

    if(m_debug)
      std::cout << "Fid_4l: x, y = " << x4l[i] << " , " << y4l[i]
		<< " yUp, yDw = " << yEu4l[i] << " , " <<  yEd4l[i]
		<< std::endl;
    
  }

  Int_t n2l2l = obs2l2l->GetN();
  Double_t x2l2l[n2l2l], y2l2l[n2l2l], yEu2l2l[n2l2l], yEd2l2l[n2l2l];
  for(Int_t i=0; i<n2l2l; i++){
    obs2l2l->GetPoint(i,x2l2l[i],y2l2l[i]);
    yEu2l2l[i] = sqrt( pow(obs2l2l->GetErrorYhigh(i),2) - pow(obsSys2l2l->GetErrorYhigh(i),2) );
    yEd2l2l[i] = sqrt( pow(obs2l2l->GetErrorYlow(i),2) - pow(obsSys2l2l->GetErrorYlow(i),2) );

    if(m_debug)
      std::cout << "Fid_2l2l: x, y = " << x2l2l[i] << " , " << y2l2l[i]
		<< " yUp, yDw = " << yEu2l2l[i] << " , " <<  yEd2l2l[i]
		<< std::endl;

  }

  Int_t nTot = obsTot->GetN();
  Double_t xTot[nTot], yTot[nTot], yEuTot[nTot], yEdTot[nTot];
  for(Int_t i=0; i<nTot; i++){
    obsTot->GetPoint(i,xTot[i],yTot[i]);
    yEuTot[i] = sqrt( pow(obsTot->GetErrorYhigh(i),2) - pow(obsSysTot->GetErrorYhigh(i),2) );
    yEdTot[i] = sqrt( pow(obsTot->GetErrorYlow(i),2) - pow(obsSysTot->GetErrorYlow(i),2) );

    if(m_debug)
      std::cout << "FidTot: x, y = " << xTot[i] << " , " << yTot[i]
		<< " yUp, yDw = " << yEuTot[i] << " , " <<  yEdTot[i]
		<< std::endl;
    
  }

  Int_t N = xVal.size();
  std::cout<<" N " << N << std::endl;
  Double_t x[N], xu[N], xd[N], y[N], yu[N], yd[N];
  for(int i=0; i<N; i++){
    x[i]  = (xVal[i+1]-xVal[i])/2.+xVal[i];
    xu[i] = 0.15;
    xd[i] = 0.15;
    if(i>0 && i<5){
      y[i]  = yChan[i-1]*mul;
      yu[i] = yEuChan[i-1]*mul;
      yd[i] = yEdChan[i-1]*mul;
    }
    else if(i==9){
      y[i]  = ySum[0];
      yu[i] = yEuSum[0];
      yd[i] = yEdSum[0];
    }
    else if(i==10){
      y[i]  = yComb[0];
      yu[i] = yEuComb[0];
      yd[i] = yEdComb[0];
    }
    else if(i==7){
      y[i]  = y4l[0];
      yu[i] = yEu4l[0];
      yd[i] = yEd4l[0];
    }
    else if(i==8){
      y[i]  = y2l2l[0];
      yu[i] = yEu2l2l[0];
      yd[i] = yEd2l2l[0];
    }
    else if(i==13){
      y[i]  = yTot[0]/20000.;
      yu[i] = yEuTot[0]/20000.;
      yd[i] = yEdTot[0]/20000.;
    }
    else{
      y[i]  = 0;
      yu[i] = 0;
      yd[i] = 0;
    }
    
  }
  if(m_debug){
    for(int i=0; i<N; i++)
      std::cout << "Obs TGraph - > " << "x,y = " << x[i] << " , " << y[i]
		<< " yUp, yDw = " << yu[i] << " , " << yd[i] << std::endl;
    
  }

  TGraphAsymmErrors *tmp = new TGraphAsymmErrors(N,x,y,xd,xu,yd,yu);
  tmp->SetName( Name.c_str() );
  
  return tmp;
  
}

TGraphAsymmErrors* makeGraphNjet(std::vector<TGraphAsymmErrors*> obs,
				 std::string Name, std::vector<double> xVal){

  
  TGraphAsymmErrors *njet    = obs.at(0);
  TGraphAsymmErrors *njetv2  = obs.at(1);
  TGraphAsymmErrors *njetv3  = obs.at(2);

  Int_t nChan = njet->GetN();
  Double_t xChan[nChan], yChan[nChan], yEuChan[nChan], yEdChan[nChan];
  for(Int_t i=0; i<nChan; i++){
    njet->GetPoint(i,xChan[i],yChan[i]);
    yEuChan[i] = njet->GetErrorYhigh(i);
    yEdChan[i] = njet->GetErrorYlow(i);

    if(m_debug)
      std::cout << "Njet: x, y = " << xChan[i] << " , " << yChan[i]
		<< " yUp, yDw = " << yEuChan[i] << " , " <<  yEdChan[i]
		<< std::endl;
  }

  Int_t nSum = njetv2->GetN();
  Double_t xSum[nSum], ySum[nSum], yEuSum[nSum], yEdSum[nSum];
  for(Int_t i=0; i<nSum; i++){
    njetv2->GetPoint(i,xSum[i],ySum[i]);
    yEuSum[i] = njetv2->GetErrorYhigh(i);
    yEdSum[i] = njetv2->GetErrorYlow(i);

    if(m_debug)
      std::cout << "Njetv2: x, y = " << xSum[i] << " , " << ySum[i]
		<< " yUp, yDw = " << yEuSum[i] << " , " <<  yEdSum[i]
		<< std::endl;
  }

  Int_t nComb = njetv3->GetN();
  Double_t xComb[nComb], yComb[nComb], yEuComb[nComb], yEdComb[nComb];
  for(Int_t i=0; i<nComb; i++){
    njetv3->GetPoint(i,xComb[i],yComb[i]);
    yEuComb[i] = njetv3->GetErrorYhigh(i);
    yEdComb[i] = njetv3->GetErrorYlow(i);
    
    if(m_debug)
      std::cout << "Njetv3: x, y = " << xSum[i] << " , " << ySum[i]
		<< " yUp, yDw = " << yEuSum[i] << " , " <<  yEdSum[i]
		<< std::endl;
  }
  
  Int_t N = xVal.size()-1;
  Double_t x[N], xu[N], xd[N], y[N], yu[N], yd[N];
  for(int i=0; i<N; i++){
    x[i]  = (xVal[i+1]-xVal[i])/2.+xVal[i];
    xu[i] = 0.*(xVal[i+1]-xVal[i])/2.;
    xd[i] = 0.*(xVal[i+1]-xVal[i])/2.;
    if(i<3){
      y[i]  = yChan[i];
      yu[i] = yEuChan[i];
      yd[i] = yEdChan[i];
    }
    else if(i==3){
      y[i]  = ySum[1];
      yu[i] = yEuSum[1];
      yd[i] = yEdSum[1];
    }
    else if(i==4){
      y[i]  = yComb[2];
      yu[i] = yEuComb[2];
      yd[i] = yEdComb[2];
    }
    else if(i==5){
      y[i]  = yChan[3];
      yu[i] = yEuChan[3];
      yd[i] = yEdChan[3];
    }
  }
  if(m_debug){
    for(int i=0; i<N; i++)
      std::cout << "Obs TGraph - > " << "x,y = " << x[i] << " , " << y[i]
		<< " yUp, yDw = " << yu[i] << " , " << yd[i] << std::endl;
    
  }

  TGraphAsymmErrors *tmp = new TGraphAsymmErrors(N,x,y,xd,xu,yd,yu);
  tmp->SetName( Name.c_str() );
  
  return tmp;
  
}

TGraphAsymmErrors* makeSysGraphNjet(std::vector<TGraphAsymmErrors*> obs,
				    std::vector<TGraphAsymmErrors*> obsSys,
				    std::string Name, std::vector<double> xVal){

  TGraphAsymmErrors *njet    = obs.at(0);
  TGraphAsymmErrors *njetv2  = obs.at(1);
  TGraphAsymmErrors *njetv3  = obs.at(2);

  TGraphAsymmErrors *Sysnjet    = obsSys.at(0);
  TGraphAsymmErrors *Sysnjetv2  = obsSys.at(1);
  TGraphAsymmErrors *Sysnjetv3  = obsSys.at(2);
  
  Int_t nChan = njet->GetN();
  Double_t xChan[nChan], yChan[nChan], yEuChan[nChan], yEdChan[nChan];
  for(Int_t i=0; i<nChan; i++){
    njet->GetPoint(i,xChan[i],yChan[i]);
    yEuChan[i] = sqrt( pow(njet->GetErrorYhigh(i),2) - pow(Sysnjet->GetErrorYhigh(i),2) );
    yEdChan[i] = sqrt( pow(njet->GetErrorYlow(i),2) - pow(Sysnjet->GetErrorYlow(i),2) );

    if(m_debug)
      std::cout << "njet: x, y = " << xChan[i] << " , " << yChan[i]
		<< " yUp, yDw = " << yEuChan[i] << " , " <<  yEdChan[i]
		<< std::endl;
  }

  Int_t nSum = njetv2->GetN();
  Double_t xSum[nSum], ySum[nSum], yEuSum[nSum], yEdSum[nSum];
  for(Int_t i=0; i<nSum; i++){
    njetv2->GetPoint(i,xSum[i],ySum[i]);
    yEuSum[i] = sqrt( pow(njetv2->GetErrorYhigh(i),2) - pow(Sysnjetv2->GetErrorYhigh(i),2) );
    yEdSum[i] = sqrt( pow(njetv2->GetErrorYlow(i),2) - pow(Sysnjetv2->GetErrorYlow(i),2) );

    if(m_debug)
      std::cout << "njetv2: x, y = " << xSum[i] << " , " << ySum[i]
		<< " yUp, yDw = " << yEuSum[i] << " , " <<  yEdSum[i]
		<< std::endl;
  }
  
  Int_t nComb = njetv3->GetN();
  Double_t xComb[nComb], yComb[nComb], yEuComb[nComb], yEdComb[nComb];
  for(Int_t i=0; i<nComb; i++){
    njetv3->GetPoint(i,xComb[i],yComb[i]);
    yEuComb[i] = sqrt( pow(njetv3->GetErrorYhigh(i),2) - pow(Sysnjetv3->GetErrorYhigh(i),2) );
    yEdComb[i] = sqrt( pow(njetv3->GetErrorYlow(i),2) - pow(Sysnjetv3->GetErrorYlow(i),2) );
    
    if(m_debug)
      std::cout << "njetv3: x, y = " << xSum[i] << " , " << ySum[i]
		<< " yUp, yDw = " << yEuSum[i] << " , " <<  yEdSum[i]
		<< std::endl;
  }

  Int_t N = xVal.size()-1;
  std::cout<<" N " << N << std::endl;
  Double_t x[N], xu[N], xd[N], y[N], yu[N], yd[N];
  for(int i=0; i<N; i++){
    x[i]  = (xVal[i+1]-xVal[i])/2.+xVal[i];
    xu[i] = 0.05;
    xd[i] = 0.05;
    if(i<3){
      y[i]  = yChan[i];
      yu[i] = yEuChan[i];
      yd[i] = yEdChan[i];
    }
    else if(i==3){
      y[i]  = ySum[1];
      yu[i] = yEuSum[1];
      yd[i] = yEdSum[1];
    }
    else if(i==4){
      y[i]  = yComb[2];
      yu[i] = yEuComb[2];
      yd[i] = yEdComb[2];
    }
    else if(i==5){
      y[i]  = yChan[3];
      yu[i] = yEuChan[3];
      yd[i] = yEdChan[3];
    }
  }
  if(m_debug){
    for(int i=0; i<N; i++)
      std::cout << "Obs TGraph - > " << "x,y = " << x[i] << " , " << y[i]
		<< " yUp, yDw = " << yu[i] << " , " << yd[i] << std::endl;
  }

  TGraphAsymmErrors *tmp = new TGraphAsymmErrors(N,x,y,xd,xu,yd,yu);
  tmp->SetName( Name.c_str() );
  
  return tmp;
  
}

void makeSys(std::vector<TH1F*> *nominalall, std::vector<TH1F*> *sysupall,
	     std::vector<TH1F*> *sysdownall, TH1F *nominal, TH1F *sysup,
	     TH1F *sysdown, bool istotal){

  if(m_debug)std::cout << "making sys" << std::endl;
  nominal->Print();

  float up =0; float down = 0 ;
  for (unsigned int prod = 0; prod < nominalall->size(); ++prod) nominal->Add(nominalall->at(prod));
  
  TH1F *tmpup   = (TH1F*) nominal->Clone("tmpup");   tmpup->Reset(); 
  TH1F *tmpdown = (TH1F*) nominal->Clone("tmpdown"); tmpdown->Reset(); 
  
  for(int i=1; i<nominal->GetNbinsX()+1; ++i){
    up=0; down=0;
    
    for (unsigned int variation = 0; variation < sysupall->size(); ++variation){
      tmpup->Reset();
      tmpdown->Reset();
      
      
      for (unsigned int prod = 0; prod < nominalall->size(); ++prod){
	
        if (variation/2==prod) {
          tmpup->Add(sysupall->at(variation));
          tmpdown->Add(sysdownall->at(variation));
        }  
        else {
          tmpup->Add(nominalall->at(prod));
          tmpdown->Add(nominalall->at(prod));
        }
      }
      
      up   += pow((nominal->GetBinContent(i) - tmpup->GetBinContent(i))/nominal->GetBinContent(i) ,2);
      down += pow((nominal->GetBinContent(i) - tmpdown->GetBinContent(i))/nominal->GetBinContent(i) ,2);
      
    }
    if (!istotal && ((std::string)nominal->GetName()=="nnlops" || (std::string)nominal->GetName()=="ref"|| (std::string)nominal->GetName()=="ref2"|| (std::string)nominal->GetName()=="ref3")){
      up   +=pow((m_YR4error.at(1)-m_YR4error.at(0))/m_YR4error.at(0),2);
      down   +=pow((m_YR4error.at(2)-m_YR4error.at(0))/m_YR4error.at(0),2);
    }
    if(m_debug) std::cout << sqrt(up) << " " << sqrt(down) << std::endl;
    sysup->SetBinContent(i, nominal->GetBinContent(i)*(1+ sqrt(up)));
    sysdown->SetBinContent(i, nominal->GetBinContent(i)*(1- sqrt(down)));
  }
  
  
}


void makehisto(std::vector<TH1F*> *nominalall,
	       std::vector<TH1F*> *sysupall,
	       std::vector<TH1F*> *sysdownall,
	       TFile *_file2, bool rest,
	       std::string var, TH1F *reference){

  if(m_debug)std::cout << "making histo" << std::endl;
  std::vector<std::string> prodmode;
  if(!rest) prodmode = {"ggHNNLOPS", "VBF","WH", "ZH", "ttH", "bbH"};
  else prodmode = {"VBF","WH", "ZH", "ttH", "bbH"};
  
  TH1F* expectedggHNNLOPS        = NULL;
  TH1F* expectedggHNNLOPSpdfup   = NULL; TH1F* expectedggHNNLOPSscaleup    =NULL;
  TH1F* expectedggHNNLOPSpdfdown = NULL; TH1F* expectedggHNNLOPSscaledown = NULL;
  TH1F* tmp = NULL;
  
  std::string name = (std::string)reference->GetName();
  
  for (unsigned int i =0 ; i < prodmode.size(); ++i){

    if(m_debug)std::cout << prodmode.at(i) << std::endl;
    
    expectedggHNNLOPS = (TH1F*)_file2->Get( (var+"_"+prodmode.at(i)).c_str() );
    tmp=(TH1F*)reference->Clone( (prodmode.at(i)).c_str() );
    tmp->Reset();
    for(int i=1; i<reference->GetNbinsX()+1; ++i)
      tmp->SetBinContent( i, expectedggHNNLOPS->GetBinContent(i)/tmp->GetBinWidth(i) );
    nominalall->push_back(tmp);
    if(m_debug) tmp->Print();
    if (prodmode.at(i) == "ggHNNLOPS") std::cout <<tmp->Integral() <<std::endl;
    
    expectedggHNNLOPSpdfup = (TH1F*)_file2->Get( (var+"_"+prodmode.at(i)+"_PdfTheoryup").c_str() );
    tmp=(TH1F*)reference->Clone( (prodmode.at(i)+"_pdfup").c_str() );
    tmp->Reset();
    for(int i=1; i<reference->GetNbinsX()+1; ++i)
      tmp->SetBinContent( i, expectedggHNNLOPSpdfup->GetBinContent(i)/tmp->GetBinWidth(i) );
    sysupall->push_back(tmp);
    if(m_debug) tmp->Print();
    
    expectedggHNNLOPSscaleup = (TH1F*)_file2->Get( (var+"_"+prodmode.at(i)+"_ScaleTheoryup").c_str() );
    tmp=(TH1F*)reference->Clone( (prodmode.at(i)+"_scaleup").c_str() );
    tmp->Reset();
    for(int i=1; i<reference->GetNbinsX()+1; ++i)
      tmp->SetBinContent( i, expectedggHNNLOPSscaleup->GetBinContent(i)/tmp->GetBinWidth(i) );
    sysupall->push_back(tmp);
    if(m_debug) tmp->Print();
    
    expectedggHNNLOPSpdfdown = (TH1F*)_file2->Get( (var+"_"+prodmode.at(i)+"_PdfTheorydown").c_str() );
    tmp=(TH1F*)reference->Clone( (prodmode.at(i)+"_pdfdown").c_str() );
    tmp->Reset();
    for(int i=1; i<reference->GetNbinsX()+1; ++i)
      tmp->SetBinContent( i, expectedggHNNLOPSpdfdown->GetBinContent(i)/tmp->GetBinWidth(i) );
    sysdownall->push_back(tmp);
    if(m_debug) tmp->Print();
    
    expectedggHNNLOPSscaledown = (TH1F*)_file2->Get( (var+"_"+prodmode.at(i)+"_ScaleTheorydown").c_str() );
    tmp=(TH1F*)reference->Clone( (prodmode.at(i)+"_scaledown").c_str() );
    tmp->Reset();
    for(int i=1; i<reference->GetNbinsX()+1; ++i)
      tmp->SetBinContent( i, expectedggHNNLOPSscaledown->GetBinContent(i)/tmp->GetBinWidth(i) );
    sysdownall->push_back(tmp);
    if(m_debug) tmp->Print();
    
  }
  
}

TGraphAsymmErrors* makeObs(TGraphAsymmErrors *obs, std::string var){

  TGraphAsymmErrors* m_obs = new TGraphAsymmErrors();
  double x, y;
  int offsetbin = 0;
  int nbins     = obs->GetN();
  float offset  = 0; 

  if(var=="pt0j")     { nbins = 4; offsetbin=0; offset=0;    }
  else if(var=="pt1j"){ nbins = 5; offsetbin=4; offset=350.; }
  else if(var=="pt2j"){ nbins = 2; offsetbin=9; offset=700;  }
   
  std::vector<double> binwidth;
  if (var=="pt")  binwidth= {10,5,5,10,15,15,20,40,80,150,650};
  if (var=="njet")  binwidth= {1,1,1,1,1};
  obs->Print(); 
  
  for(int i=0; i < nbins; ++i){
      
    obs->GetPoint( i+offsetbin, x, y );
    m_obs->SetPoint( i, x-offset, y / (m_integralobs*binwidth.at(i) ));
    m_obs->SetPointError( i, 0.0, 0.0,
			  obs->GetErrorYlow(i+offsetbin) / (m_integralobs *binwidth.at(i)),
			  obs->GetErrorYhigh(i+offsetbin) /  (m_integralobs *binwidth.at(i)) );
  }

  return m_obs;
  
}

TGraphAsymmErrors* makeObsSys(TGraphAsymmErrors *obs,
			      TGraphAsymmErrors *sys,
			      std::string var){

  TGraphAsymmErrors* m_sys = new TGraphAsymmErrors();
  double x, y;
  int offsetbin = 0;
  int nbins     = obs->GetN();
  float offset  = 0; 

  std::vector<double> binwidth;
  if (var=="pt")  binwidth= {10,5,5,10,15,15,20,40,80,150,650};
  //if (var=="pt")  binwidth= {1,1,1,1,1,1,1,1,1,1,1};
  if (var=="njet")  binwidth= {1,1,1,1,1};


  if(var=="pt0j")     { nbins = 4; offsetbin=0; offset=0;    }
  else if(var=="pt1j"){ nbins = 5; offsetbin=4; offset=350.; }
  else if(var=="pt2j"){ nbins = 2; offsetbin=9; offset=700;  }
    
  obs->Print(); 
  
  sys->Print();
  for(int i=0; i < nbins; ++i){
      
    sys->GetPoint( i+offsetbin, x, y );
    m_sys->SetPoint( i, x-offset, y / (binwidth.at(i)* m_integralobs) );  
    m_sys->SetPointError( i, GetBarSize(var).first, GetBarSize(var).first,//0.04, 0.04,
			  sqrt( pow(obs->GetErrorYlow(i+offsetbin),2) - pow(sys->GetErrorYlow(i+offsetbin)/binwidth.at(i),2) ) / m_integralobs,
			  sqrt( pow(obs->GetErrorYhigh(i+offsetbin),2) - pow(sys->GetErrorYhigh(i+offsetbin)/binwidth.at(i),2) ) / m_integralobs );
    
  
    std::cout <<   var << " bin " << i << " low " << sys->GetErrorYlow(i+offsetbin)/y << " high " << sys->GetErrorYhigh(i+offsetbin)/y <<std::endl;
  }

  sys->Print();
  return m_sys;
  
}

TGraphAsymmErrors* makeRatio(TGraphAsymmErrors *inGr,
			     TGraphAsymmErrors *obs,
			     TH1F * dummy,
			     std::string var,
			     std::string MC){
  
  TGraphAsymmErrors* m_ratio = new TGraphAsymmErrors();
  double x; double y;
  double x1; double y1;
  double offset = 0;
  if(MC=="mg")       { offset = -GetBarSpacing(var); }
  else if(MC=="hres"){ offset =  GetBarSpacing(var); }
  if(MC=="nnlops"   ) offset =  GetBarSpacing(var);

  for(Int_t ii=0; ii<inGr->GetN(); ii++){

    obs->GetPoint(ii, x, y);
    inGr->GetPoint(ii, x1, y1);

    if(var=="mjj"){

      m_ratio->SetPoint(ii, dummy->GetBinCenter(ii+1)+offset,  y1/y );
      m_ratio->SetPointError( ii, GetBarSize(m_Var).second,
			      GetBarSize(m_Var).second,
			      obs->GetErrorYlow(ii)/y1,
			      obs->GetErrorYhigh(ii)/y1 );

      if( y1/y > 1.85 ||  y1/y <0.4 )
	m_Arrows.push_back( MakeArrows(dummy->GetBinCenter(ii+1)+offset, y1/y, MC) );
    }
    else{

      m_ratio->SetPoint(ii, dummy->GetBinCenter(ii+1)+offset,  y1/y );
      m_ratio->SetPointError(ii, GetBarSize(m_Var).second,
			     GetBarSize(m_Var).second,
			     inGr->GetErrorYlow(ii)/y,
			     inGr->GetErrorYhigh(ii)/y);
      if (MC=="obs")m_ratio->SetPointError(ii, 0.5,0.5,
			     obs->GetErrorYlow(ii)/y,
			     obs->GetErrorYhigh(ii)/y);
      
      if( y1/y > 1.85 ||  y1/y <0.4 )
	m_Arrows.push_back( MakeArrows(dummy->GetBinCenter(ii+1)+offset, y1/y, MC) );
      
    }
    
  }

  return m_ratio;
  
}
