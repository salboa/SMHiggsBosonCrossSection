#include "MakeInput.h"

void MakeInput::DefineHistograms(){
  
  /*********************************/
  /* Define Needed Bins and Ranges */
  /*********************************/

  /* m12 and m34 */
  double M12Range[] = {50.0, 65.0, 74.0, 82.0, 88.0, 94.0, 106.0};
  double M34Range[] = {12.0, 20.0, 24.0, 28.0, 32.0, 40.0, 55.0, 65.0};
  double M34RangeB[] = {50.0, 65.0, 74.0, 82.0, 88.0, 94.0, 106.0};
  
  Int_t M12Bins  = ( (sizeof M12Range) / (sizeof *M12Range) )-1;
  Int_t M34Bins  = ( (sizeof M34Range) / (sizeof *M34Range) )-1;
  Int_t M34BinsB = ( (sizeof M34RangeB) / (sizeof *M34RangeB) )-1;
  
  /* m12 vs m34 */
  //double Yrange[] = {12.0, 20.0, 28.0, 36.0, 50.0, 112.0};
  //double Xrange[] = {50.0, 70.0, 80.0, 85.0, 90.0,  95.0, 110.0};
  //Int_t Xbins = ( (sizeof Xrange) / (sizeof *Xrange) )-1;
  //Int_t Ybins = ( (sizeof Yrange) / (sizeof *Yrange) )-1;
  
  double m12m34range[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

  Int_t m12m34rangeBins = ( (sizeof m12m34range) / (sizeof *m12m34range) )-1;

  /* pt */
  double PtRange[]   = {0.0,  10.0, 15.0, 20.0, 30.0,  45.0, 
			60.0, 80.0, 120.0,  200.0, 350.0}; //400.0
  double Pt0jRange[] = {0.0, 15.0, 30.0, 120.0, 350.0}; //400.0
  double Pt1jRange[] = {0.0, 30.0, 60.0, 80.0, 120.0, 350.0}; //400.00
  double Pt2jRange[] = {0.0, 120.0, 350.0}; //400.0
  double PtLjRange[] = {30.0, 40.0, 55.0, 75.0, 120.0, 350.0}; //115.0, 400.0

  Int_t PtBins   = ( (sizeof PtRange)   / (sizeof *PtRange)   )-1;
  Int_t Pt0jBins = ( (sizeof Pt0jRange) / (sizeof *Pt0jRange) )-1;
  Int_t Pt1jBins = ( (sizeof Pt1jRange) / (sizeof *Pt1jRange) )-1;
  Int_t Pt2jBins = ( (sizeof Pt2jRange) / (sizeof *Pt2jRange) )-1;
  Int_t PtLjBins = ( (sizeof PtLjRange) / (sizeof *PtLjRange) )-1;

  /* double pt */
  double Pt0jPt1jRange[] = {  0.0,  15.0,  30.0, 120.0, 350.0,
			      380.0, 410.0, 430.0, 470.0, 700.0,
			      820.0, 1050.0};
  
  Int_t Pt0jPt1jBins = ( (sizeof Pt0jPt1jRange) / (sizeof *Pt0jPt1jRange) )-1;
  
  /* njet, y and costhetastar */
  double NjetRange[]   = {0.0, 1.0, 2.0, 3.0, 4.0};
  double NjetRangev2[] = {0.0, 1.0, 2.0};
  double NjetRangev3[] = {0.0, 1.0, 2.0, 3.0};
  double RapRange[]    = {0.0, 0.3, 0.6, 0.9, 1.2, 1.6, 2.0, 2.5};
  double CtsRange[]    = {0.0, 0.125, 0.250, 0.375, 0.500, 0.625, 0.750, 0.875, 1.0};
  double NbjetRange[]  = {0.0, 1.0, 2.0};

  double MjjRange[]   = {0.0, 120, 3000};
  double MjjrmRange[] = {0.0, 1.0, 4.0};
  double EtajjRange[] = {0.0, 2.0, 9.0};
  double PhijjRange[] = {0.0, TMath::Pi(), 2*TMath::Pi()};

  Int_t NjetBins   = ( (sizeof NjetRange)   / (sizeof *NjetRange)   )-1;
  Int_t NjetBinsv2 = ( (sizeof NjetRangev2) / (sizeof *NjetRangev2) )-1;
  Int_t NjetBinsv3 = ( (sizeof NjetRangev3) / (sizeof *NjetRangev3) )-1;
  Int_t RapBins    = ( (sizeof RapRange)    / (sizeof *RapRange)    )-1;
  Int_t CtsBins    = ( (sizeof CtsRange)    / (sizeof *CtsRange)    )-1;
  Int_t NbjetBins  = ( (sizeof NbjetRange)  / (sizeof *NbjetRange)  )-1;
  
  Int_t MjjBins    = ( (sizeof MjjRange)    / (sizeof *MjjRange)    )-1;
  Int_t MjjrmBins  = ( (sizeof MjjrmRange)  / (sizeof *MjjrmRange)  )-1;
  Int_t EtajjBins  = ( (sizeof EtajjRange)  / (sizeof *EtajjRange)  )-1;
  Int_t PhijjBins  = ( (sizeof PhijjRange)  / (sizeof *PhijjRange)  )-1;

  
  std::vector<std::string> Chans, Labs;
  Chans.push_back( "incl"  );  Labs.push_back( ""       ); // "4l"
  Chans.push_back( "4mu"   );  Labs.push_back( "4#mu"   );
  Chans.push_back( "4e"    );  Labs.push_back( "4e"     );
  Chans.push_back( "2mu2e" );  Labs.push_back( "2#mu2e" );
  Chans.push_back( "2e2mu" );  Labs.push_back( "2e2#mu" );
  
  /*********************************/
  /*   Define Needed Histograms    */
  /*********************************/
  
  std::string HistName = "";
  for(uint i=0; i<Chans.size(); i++){

    /* 4l lepton mass plots */
    HistName = "hm_"+Chans.at(i)+"_"+m_Process;
    hm = new TH1F( HistName.c_str(), HistName.c_str(), m_THbins, m_Min, m_Max );
    hm->GetXaxis()->SetTitle( ("m_{"+Labs.at(i)+"} [GeV]").c_str() );
    hm->GetYaxis()->SetTitle( "Events" );
    m_VecM.push_back( hm );
    
    HistName = "hm0j_"+Chans.at(i)+"_"+m_Process;
    hm0j = new TH1F( HistName.c_str(), HistName.c_str(), m_THbins, m_Min, m_Max );
    hm0j->GetXaxis()->SetTitle( ("m_{"+Labs.at(i)+"} [GeV]").c_str() );
    hm0j->GetYaxis()->SetTitle( "Events" );
    m_VecM0j.push_back( hm0j );
    
    HistName = "hm1j_"+Chans.at(i)+"_"+m_Process;
    hm1j = new TH1F( HistName.c_str(), HistName.c_str(), m_THbins, m_Min, m_Max );
    hm1j->GetXaxis()->SetTitle( ("m_{"+Labs.at(i)+"} [GeV]").c_str() );
    hm1j->GetYaxis()->SetTitle( "Events" );
    m_VecM1j.push_back( hm1j );
    
    HistName = "hm2j_"+Chans.at(i)+"_"+m_Process;
    hm2j = new TH1F( HistName.c_str(), HistName.c_str(), m_THbins, m_Min, m_Max );
    hm2j->GetXaxis()->SetTitle( ("m_{"+Labs.at(i)+"} [GeV]").c_str() );
    hm2j->GetYaxis()->SetTitle( "Events" );
    m_VecM2j.push_back( hm2j );

    HistName = "hmlowpt_"+Chans.at(i)+"_"+m_Process;
    hmLpt = new TH1F( HistName.c_str(), HistName.c_str(), m_THbins, m_Min, m_Max );
    hmLpt->GetXaxis()->SetTitle( ("m_{"+Labs.at(i)+"} [GeV]").c_str() );
    hmLpt->GetYaxis()->SetTitle( "Events" );
    m_VecMLpt.push_back( hmLpt );

    HistName = "hmhighpt_"+Chans.at(i)+"_"+m_Process;
    hmHpt = new TH1F( HistName.c_str(), HistName.c_str(), m_THbins, m_Min, m_Max );
    hmHpt->GetXaxis()->SetTitle( ("m_{"+Labs.at(i)+"} [GeV]").c_str() );
    hmHpt->GetYaxis()->SetTitle( "Events" );
    m_VecMHpt.push_back( hmHpt );
    
    /* m12 mass plots */
    HistName = "hm12_"+Chans.at(i)+"_"+m_Process;
    hm12 = new TH1F( HistName.c_str(), HistName.c_str(), M12Bins, M12Range );
    hm12->GetXaxis()->SetTitle( ("m_{12}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hm12->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecM12.push_back( hm12 );
    
    /* m34 mass plots */
    HistName = "hm34_"+Chans.at(i)+"_"+m_Process;
    hm34 = new TH1F( HistName.c_str(), HistName.c_str(), M34Bins, M34Range );
    hm34->GetXaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hm34->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecM34.push_back( hm34 );

    HistName = "hm34b_"+Chans.at(i)+"_"+m_Process;
    hm34 = new TH1F( HistName.c_str(), HistName.c_str(), M34BinsB, M34RangeB );
    hm34->GetXaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hm34->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecM34B.push_back( hm34 );

    /* pt plots */
    HistName = "hpt_"+Chans.at(i)+"_"+m_Process;
    hpt = new TH1F( HistName.c_str(), HistName.c_str(), PtBins, PtRange );
    hpt->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hpt->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecPT.push_back( hpt );
    
    HistName = "hpt0j_"+Chans.at(i)+"_"+m_Process;
    hpt0j = new TH1F( HistName.c_str(), HistName.c_str(), Pt0jBins, Pt0jRange );
    hpt0j->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hpt0j->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecPT0j.push_back( hpt0j );
    
    HistName = "hpt1j_"+Chans.at(i)+"_"+m_Process;
    hpt1j = new TH1F( HistName.c_str(), HistName.c_str(), Pt1jBins, Pt1jRange );
    hpt1j->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hpt1j->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecPT1j.push_back( hpt1j );
    
    HistName = "hpt2j_"+Chans.at(i)+"_"+m_Process;
    hpt2j = new TH1F( HistName.c_str(), HistName.c_str(), Pt2jBins, Pt2jRange );
    hpt2j->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hpt2j->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecPT2j.push_back( hpt2j );

    /* njet plots */
    HistName = "hnjet_"+Chans.at(i)+"_"+m_Process;
    hnjet = new TH1F( HistName.c_str(), HistName.c_str(), NjetBins, NjetRange );
    hnjet->GetXaxis()->SetTitle( ("N_{jets}^{"+Labs.at(i)+"}").c_str() );
    hnjet->GetYaxis()->SetTitle( "Events" );
    hnjet->GetXaxis()->SetBinLabel(1,"0");
    hnjet->GetXaxis()->SetBinLabel(2,"1");
    hnjet->GetXaxis()->SetBinLabel(3,"2");
    hnjet->GetXaxis()->SetBinLabel(4,"#geq3");
    hnjet->GetXaxis()->SetLabelSize(0.15);
    m_VecNjet.push_back( hnjet );

    HistName = "hnjetv2_"+Chans.at(i)+"_"+m_Process;
    hnjet = new TH1F( HistName.c_str(), HistName.c_str(), NjetBinsv2, NjetRangev2 );
    hnjet->GetXaxis()->SetTitle( ("N_{jets}^{"+Labs.at(i)+"}").c_str() );
    hnjet->GetYaxis()->SetTitle( "Events" );
    hnjet->GetXaxis()->SetBinLabel(1,"0");
    hnjet->GetXaxis()->SetBinLabel(2,"#geq1");
    hnjet->GetXaxis()->SetLabelSize(0.15);
    m_VecNjetv2.push_back( hnjet );

    HistName = "hnjetv3_"+Chans.at(i)+"_"+m_Process;
    hnjet = new TH1F( HistName.c_str(), HistName.c_str(), NjetBinsv3, NjetRangev3 );
    hnjet->GetXaxis()->SetTitle( ("N_{jets}^{"+Labs.at(i)+"}").c_str() );
    hnjet->GetYaxis()->SetTitle( "Events" );
    hnjet->GetXaxis()->SetBinLabel(1,"0");
    hnjet->GetXaxis()->SetBinLabel(2,"1");
    hnjet->GetXaxis()->SetBinLabel(3,"#geq2");
    hnjet->GetXaxis()->SetLabelSize(0.15);
    m_VecNjetv3.push_back( hnjet );

    /* nbjet plots */
    HistName = "hnbjet_"+Chans.at(i)+"_"+m_Process;
    hnbjet = new TH1F( HistName.c_str(), HistName.c_str(), NbjetBins, NbjetRange );
    hnbjet->GetXaxis()->SetTitle( ("N_{b-jet}^{"+Labs.at(i)+"}").c_str() );
    hnbjet->GetYaxis()->SetTitle( "Events" );
    hnbjet->GetXaxis()->SetBinLabel(1, "0");
    hnbjet->GetXaxis()->SetBinLabel(2, "#geq1");
    m_VecNbjet.push_back( hnbjet );
    
    /* y plots */
    HistName = "hy_"+Chans.at(i)+"_"+m_Process;
    hy = new TH1F( HistName.c_str(), HistName.c_str(), RapBins, RapRange );
    hy->GetXaxis()->SetTitle( ("y^{"+Labs.at(i)+"}").c_str() );
    hy->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecY.push_back( hy );
    
    HistName = "hy0j_"+Chans.at(i)+"_"+m_Process;
    hy0j = new TH1F( HistName.c_str(), HistName.c_str(), RapBins, RapRange );
    hy0j->GetXaxis()->SetTitle( ("y^{"+Labs.at(i)+"}").c_str() );
    hy0j->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecY0j.push_back( hy0j );
    
    HistName = "hy1j_"+Chans.at(i)+"_"+m_Process;
    hy1j = new TH1F( HistName.c_str(), HistName.c_str(), RapBins, RapRange );
    hy1j->GetXaxis()->SetTitle( ("y^{"+Labs.at(i)+"}").c_str() );
    hy1j->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecY1j.push_back( hy1j );

    HistName = "hylowpt_"+Chans.at(i)+"_"+m_Process;
    hyLpt = new TH1F( HistName.c_str(), HistName.c_str(), RapBins, RapRange );
    hyLpt->GetXaxis()->SetTitle( ("y^{"+Labs.at(i)+"}").c_str() );
    hyLpt->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecYLpt.push_back( hyLpt );

    HistName = "hyhighpt_"+Chans.at(i)+"_"+m_Process;
    hyHpt = new TH1F( HistName.c_str(), HistName.c_str(), RapBins, RapRange );
    hyHpt->GetXaxis()->SetTitle( ("y^{"+Labs.at(i)+"}").c_str() );
    hyHpt->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecYHpt.push_back( hyHpt );
    
    /* costhetastar plots */
    HistName = "hcts_"+Chans.at(i)+"_"+m_Process;
    hcts = new TH1F( HistName.c_str(), HistName.c_str(), CtsBins, CtsRange );
    hcts->GetXaxis()->SetTitle( ("cos#theta^{*}_{"+Labs.at(i)+"}").c_str() );
    hcts->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecCts.push_back( hcts );
    
    HistName = "hcts0j_"+Chans.at(i)+"_"+m_Process;
    hcts0j = new TH1F( HistName.c_str(), HistName.c_str(), CtsBins, CtsRange );
    hcts0j->GetXaxis()->SetTitle( ("cos#theta^{*}_{"+Labs.at(i)+"}").c_str() );
    hcts0j->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecCts0j.push_back( hcts0j );

    
    HistName = "hcts1j_"+Chans.at(i)+"_"+m_Process;
    hcts1j = new TH1F( HistName.c_str(), HistName.c_str(), CtsBins, CtsRange );
    hcts1j->GetXaxis()->SetTitle( ("cos#theta^{*}_{"+Labs.at(i)+"}").c_str() );
    hcts1j->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecCts1j.push_back( hcts1j );

    HistName = "hctslowpt_"+Chans.at(i)+"_"+m_Process;
    hctsLpt = new TH1F( HistName.c_str(), HistName.c_str(), CtsBins, CtsRange );
    hctsLpt->GetXaxis()->SetTitle( ("cos#theta^{*}_{"+Labs.at(i)+"}").c_str() );
    hctsLpt->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecCtsLpt.push_back( hctsLpt );

    HistName = "hctshighpt_"+Chans.at(i)+"_"+m_Process;
    hctsHpt = new TH1F( HistName.c_str(), HistName.c_str(), CtsBins, CtsRange );
    hctsHpt->GetXaxis()->SetTitle( ("cos#theta^{*}_{"+Labs.at(i)+"}").c_str() );
    hctsHpt->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecCtsHpt.push_back( hctsHpt );


    /* lead. jet pt plots */
    HistName = "hljpt_"+Chans.at(i)+"_"+m_Process;
    hljpt = new TH1F( HistName.c_str(), HistName.c_str(), PtLjBins, PtLjRange );
    hljpt->GetXaxis()->SetTitle( "p_{T}^{lead. jet} [GeV]" );
    hljpt->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecJetPt.push_back( hljpt );
    
    /* inv mass jet-jet */
    HistName = "hmjj_"+Chans.at(i)+"_"+m_Process;
    hmjj = new TH1F( HistName.c_str(), HistName.c_str(), MjjBins, MjjRange );
    hmjj->GetXaxis()->SetTitle( "m_{jj} [GeV]" );
    hmjj->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecMJJ.push_back( hmjj );

    HistName = "hmjjrm_"+Chans.at(i)+"_"+m_Process;
    hmjjrm = new TH1F( HistName.c_str(), HistName.c_str(), MjjrmBins, MjjrmRange );
    hmjjrm->GetXaxis()->SetTitle( "m_{jj} [GeV]" );
    hmjjrm->GetYaxis()->SetTitle( "Events " );
    m_VecMJJrm.push_back( hmjjrm );
        
    /* delta eta jet-jet */
    HistName = "hetajj_"+Chans.at(i)+"_"+m_Process;
    hetajj = new TH1F( HistName.c_str(), HistName.c_str(), EtajjBins, EtajjRange );
    hetajj->GetXaxis()->SetTitle( "#Delta#eta_{jj}" );
    hetajj->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecETAJJ.push_back( hetajj );
    
    
    /* delta phi jet-jet */
    HistName = "hphijj_"+Chans.at(i)+"_"+m_Process;
    hphijj = new TH1F( HistName.c_str(), HistName.c_str(), PhijjBins, PhijjRange );
    hphijj->GetXaxis()->SetTitle( "#Delta#phi_{jj}" );
    hphijj->GetYaxis()->SetTitle( "Events / #pi" );
    m_VecPHIJJ.push_back( hphijj );
    

    /* double pt */
    HistName = "hptpt_"+Chans.at(i)+"_"+m_Process;
    hptpt = new TH1F( HistName.c_str(), HistName.c_str(), Pt0jPt1jBins, Pt0jPt1jRange );
    hptpt->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hptpt->GetYaxis()->SetTitle( "Events / Bin Width" );
    m_VecPTPT.push_back( hptpt );

    /* m12 vs m34 plots */
    HistName = "hm12vsm34_"+Chans.at(i)+"_"+m_Process;
    if(m_Process=="AllSig")
      hm12vsm34 = new TH2F( HistName.c_str(), HistName.c_str(), 40,45.,110., 37,7.,68.);//Xbins,Xrange,Ybins,Yrange );
    else
      hm12vsm34 = new TH2F( HistName.c_str(), HistName.c_str(), 80,45.,110., 74,7.,68.);//Xbins,Xrange,Ybins,Yrange );
    hm12vsm34->GetXaxis()->SetTitle( ("m_{12}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hm12vsm34->GetYaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecM12M34.push_back( hm12vsm34 );

    
    HistName = "hm12m34_"+Chans.at(i)+"_"+m_Process;
    hm12vsm34rm = new TH1F( HistName.c_str(), HistName.c_str(), m12m34rangeBins,m12m34range );
    hm12vsm34rm->GetXaxis()->SetTitle( "m_{12} vs m_{34} bins" );
    hm12vsm34rm->GetXaxis()->SetBinLabel(1,"bin 0");
    hm12vsm34rm->GetXaxis()->SetBinLabel(2,"bin 1");
    hm12vsm34rm->GetXaxis()->SetBinLabel(3,"bin 2");
    hm12vsm34rm->GetXaxis()->SetBinLabel(4,"bin 3");
    hm12vsm34rm->GetXaxis()->SetBinLabel(5,"bin 4");
    hm12vsm34rm->GetXaxis()->SetLabelSize(0.15);
    hm12vsm34rm->GetYaxis()->SetTitle( "Events" );
    m_VecM12M34rm.push_back( hm12vsm34rm );
    
    
    /* response matrices */
    HistName = "hptmtx_"+Chans.at(i)+"_"+m_Process;
    hptmtx = new TH2F( HistName.c_str(), HistName.c_str(), PtBins, PtRange, PtBins, PtRange );
    hptmtx->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hptmtx->GetYaxis()->SetTitle( ("p_{T, born}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecPTmtx.push_back( hptmtx );
    
    HistName = "hpt0jmtx_"+Chans.at(i)+"_"+m_Process;
    hpt0jmtx = new TH2F( HistName.c_str(), HistName.c_str(), Pt0jBins, Pt0jRange, Pt0jBins, Pt0jRange );
    hpt0jmtx->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hpt0jmtx->GetYaxis()->SetTitle( ("p_{T, born}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecPT0jmtx.push_back( hpt0jmtx );
    
    HistName = "hpt1jmtx_"+Chans.at(i)+"_"+m_Process;
    hpt1jmtx = new TH2F( HistName.c_str(), HistName.c_str(), Pt1jBins, Pt1jRange, Pt1jBins, Pt1jRange );
    hpt1jmtx->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hpt1jmtx->GetYaxis()->SetTitle( ("p_{T, born}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecPT1jmtx.push_back( hpt1jmtx );
     
    HistName = "hpt2jmtx_"+Chans.at(i)+"_"+m_Process;
    hpt2jmtx = new TH2F( HistName.c_str(), HistName.c_str(), Pt2jBins, Pt2jRange, Pt2jBins, Pt2jRange );
    hpt2jmtx->GetXaxis()->SetTitle( ("p_{T}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hpt2jmtx->GetYaxis()->SetTitle( ("p_{T, born}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecPT2jmtx.push_back( hpt2jmtx );
    
    HistName = "hm12mtx_"+Chans.at(i)+"_"+m_Process;
    hm12mtx = new TH2F( HistName.c_str(), HistName.c_str(), M12Bins, M12Range, M12Bins, M12Range );
    hm12mtx->GetXaxis()->SetTitle( ("m_{12}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hm12mtx->GetYaxis()->SetTitle( ("m_{12, born}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecM12mtx.push_back( hm12mtx );
    
    HistName = "hm34mtx_"+Chans.at(i)+"_"+m_Process;
    hm34mtx = new TH2F( HistName.c_str(), HistName.c_str(), M34Bins, M34Range, M34Bins, M34Range );
    hm34mtx->GetXaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hm34mtx->GetYaxis()->SetTitle( ("m_{34, born}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecM34mtx.push_back( hm34mtx );

    HistName = "hymtx_"+Chans.at(i)+"_"+m_Process;
    hymtx = new TH2F( HistName.c_str(), HistName.c_str(), RapBins, RapRange, RapBins, RapRange );
    hymtx->GetXaxis()->SetTitle( ("y^{"+Labs.at(i)+"}").c_str() );
    hymtx->GetYaxis()->SetTitle( ("y_{born}^{"+Labs.at(i)+"}").c_str() );
    m_VecYmtx.push_back( hymtx );

    HistName = "hctsmtx_"+Chans.at(i)+"_"+m_Process;
    hctsmtx = new TH2F( HistName.c_str(), HistName.c_str(), CtsBins, CtsRange, CtsBins, CtsRange );
    hctsmtx->GetXaxis()->SetTitle( ("cos#theta^{*}^{"+Labs.at(i)+"}").c_str() );
    hctsmtx->GetYaxis()->SetTitle( ("cos#theta^{*}_{born}^{"+Labs.at(i)+"}").c_str() );
    m_VecCTSmtx.push_back( hctsmtx );
    
    HistName = "hnjetmtx_"+Chans.at(i)+"_"+m_Process;
    hnjetmtx = new TH2F( HistName.c_str(), HistName.c_str(), NjetBins, NjetRange, NjetBins, NjetRange );
    hnjetmtx->GetXaxis()->SetTitle( ("N_{jets}^{"+Labs.at(i)+"}").c_str() );
    hnjetmtx->GetYaxis()->SetTitle( ("N_{jets}_{born}^{"+Labs.at(i)+"}").c_str() );
    m_VecNJETmtx.push_back( hnjetmtx );

    HistName = "hnjetv2mtx_"+Chans.at(i)+"_"+m_Process;
    hnjetmtx = new TH2F( HistName.c_str(), HistName.c_str(), NjetBinsv2, NjetRangev2, NjetBinsv2, NjetRangev2 );
    hnjetmtx->GetXaxis()->SetTitle( ("N_{jets}^{"+Labs.at(i)+"}").c_str() );
    hnjetmtx->GetYaxis()->SetTitle( ("N_{jets}_{born}^{"+Labs.at(i)+"}").c_str() );
    m_VecNJETmtxv2.push_back( hnjetmtx );

    HistName = "hnjetv3mtx_"+Chans.at(i)+"_"+m_Process;
    hnjetmtx = new TH2F( HistName.c_str(), HistName.c_str(), NjetBinsv3, NjetRangev3, NjetBinsv3, NjetRangev3 );
    hnjetmtx->GetXaxis()->SetTitle( ("N_{jets}^{"+Labs.at(i)+"}").c_str() );
    hnjetmtx->GetYaxis()->SetTitle( ("N_{jets}_{born}^{"+Labs.at(i)+"}").c_str() );
    m_VecNJETmtxv3.push_back( hnjetmtx );

    HistName = "hnbjetmtx_"+Chans.at(i)+"_"+m_Process;
    hnbjetmtx = new TH2F( HistName.c_str(), HistName.c_str(), NbjetBins, NbjetRange, NbjetBins, NbjetRange );
    hnbjetmtx->GetXaxis()->SetTitle( ("N_{b-jets}^{"+Labs.at(i)+"}").c_str() );
    hnbjetmtx->GetYaxis()->SetTitle( ("N_{b-jets}_{born}^{"+Labs.at(i)+"}").c_str() );
    m_VecNBJETmtx.push_back( hnbjetmtx );
  
    HistName = "hljetmtx_"+Chans.at(i)+"_"+m_Process;
    hljetmtx = new TH2F( HistName.c_str(), HistName.c_str(), PtLjBins, PtLjRange, PtLjBins, PtLjRange );
    hljetmtx->GetXaxis()->SetTitle( ("p_{T_{jet}}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hljetmtx->GetYaxis()->SetTitle( ("p_{T_{jet}}_{born}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecLJETmtx.push_back( hljetmtx );

    HistName = "hmjjmtx_"+Chans.at(i)+"_"+m_Process;
    hmjjmtx  = new TH2F( HistName.c_str(), HistName.c_str(), MjjBins, MjjRange, MjjBins, MjjRange );
    hmjjmtx->GetXaxis()->SetTitle( ("m_{jj}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hmjjmtx->GetYaxis()->SetTitle( ("m_{jj}_{born}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_VecMJJmtx.push_back( hmjjmtx );

    HistName = "hetajjmtx_"+Chans.at(i)+"_"+m_Process;
    hetajjmtx  = new TH2F( HistName.c_str(), HistName.c_str(), EtajjBins, EtajjRange, EtajjBins, EtajjRange );
    hetajjmtx->GetXaxis()->SetTitle( ("#eta_{jj}^{"+Labs.at(i)+"}").c_str() );
    hetajjmtx->GetYaxis()->SetTitle( ("#eta_{jj}_{born}^{"+Labs.at(i)+"}").c_str() );
    m_VecETAJJmtx.push_back( hetajjmtx );

    HistName = "hphijjmtx_"+Chans.at(i)+"_"+m_Process;
    hphijjmtx  = new TH2F( HistName.c_str(), HistName.c_str(), PhijjBins, PhijjRange, PhijjBins, PhijjRange );
    hphijjmtx->GetXaxis()->SetTitle( ("#phi_{jj}^{"+Labs.at(i)+"}").c_str() );
    hphijjmtx->GetYaxis()->SetTitle( ("#phi_{jj}_{born}^{"+Labs.at(i)+"}").c_str() );
    m_VecPHIJJmtx.push_back( hphijjmtx );
    
    HistName = "hm12vsm34rmmtx_"+Chans.at(i)+"_"+m_Process;
    hm12vsm34rmmtx = new TH2F( HistName.c_str(), HistName.c_str(), m12m34rangeBins, m12m34range, m12m34rangeBins, m12m34range );
    hm12vsm34rmmtx->GetXaxis()->SetTitle( ("bin_{m12m34, reco}^{"+Labs.at(i)+"}").c_str() );
    hm12vsm34rmmtx->GetYaxis()->SetTitle( ("bin_{m12m34, born}^{"+Labs.at(i)+"}").c_str() );
    m_Vechm12vsm34rmmtx.push_back( hm12vsm34rmmtx );
    
    HistName = "hbin1Z1Z2mtx_"+Chans.at(i)+"_"+m_Process;
    hbin1Z1Z2mtx = new TH2F( HistName.c_str(), HistName.c_str(), 65, 45, 110, 61, 9, 70 );
    hbin1Z1Z2mtx->GetXaxis()->SetTitle( ("m_{12}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hbin1Z1Z2mtx->GetYaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_Vechbin1Z1Z2mtx.push_back( hbin1Z1Z2mtx );
    
    HistName = "hbin2Z1Z2mtx_"+Chans.at(i)+"_"+m_Process;
    hbin2Z1Z2mtx = new TH2F( HistName.c_str(), HistName.c_str(), 65, 45, 110, 61, 9, 70 );
    hbin2Z1Z2mtx->GetXaxis()->SetTitle( ("m_{12}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hbin2Z1Z2mtx->GetYaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_Vechbin2Z1Z2mtx.push_back( hbin2Z1Z2mtx );
    
    HistName = "hbin3Z1Z2mtx_"+Chans.at(i)+"_"+m_Process;
    hbin3Z1Z2mtx = new TH2F( HistName.c_str(), HistName.c_str(), 65, 45, 110, 61, 9, 70 );
    hbin3Z1Z2mtx->GetXaxis()->SetTitle( ("m_{12}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hbin3Z1Z2mtx->GetYaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_Vechbin3Z1Z2mtx.push_back( hbin3Z1Z2mtx );
    
    HistName = "hbin4Z1Z2mtx_"+Chans.at(i)+"_"+m_Process;
    hbin4Z1Z2mtx = new TH2F( HistName.c_str(), HistName.c_str(), 65, 45, 110, 61, 9, 70 );
    hbin4Z1Z2mtx->GetXaxis()->SetTitle( ("m_{12}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hbin4Z1Z2mtx->GetYaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_Vechbin4Z1Z2mtx.push_back( hbin4Z1Z2mtx );
    
    HistName = "hbin5Z1Z2mtx_"+Chans.at(i)+"_"+m_Process;
    hbin5Z1Z2mtx = new TH2F( HistName.c_str(), HistName.c_str(), 65, 45, 110, 61, 9, 70 );
    hbin5Z1Z2mtx->GetXaxis()->SetTitle( ("m_{12}^{"+Labs.at(i)+"} [GeV]").c_str() );
    hbin5Z1Z2mtx->GetYaxis()->SetTitle( ("m_{34}^{"+Labs.at(i)+"} [GeV]").c_str() );
    m_Vechbin5Z1Z2mtx.push_back( hbin5Z1Z2mtx );

  }

  /* 4l mass plots in pt bins */
  for(int i=0; i<PtBins+1; i++){
    PtRangeVec.push_back(PtRange[i]);
    if(i>0){
      HistName = "hm_ptbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_ptbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_ptbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm_ptbin->GetYaxis()->SetTitle( "Events" );
      m_pTBins.push_back(hm_ptbin);
    }
  }
  for(int i=0; i<Pt0jBins+1; i++){
    Pt0jRangeVec.push_back(Pt0jRange[i]);
    if(i>0){
      HistName = "hm_pt0jbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm0j_ptbin  = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm0j_ptbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm0j_ptbin->GetYaxis()->SetTitle( "Events" );
      m_pT0jBins.push_back(hm0j_ptbin);
    }
  }
  for(int i=0; i<Pt1jBins+1; i++){
    Pt1jRangeVec.push_back(Pt1jRange[i]);
    if(i>0){
      HistName = "hm_pt1jbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm1j_ptbin  = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm1j_ptbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm1j_ptbin->GetYaxis()->SetTitle( "Events" );
      m_pT1jBins.push_back(hm1j_ptbin);
    }
  }
  for(int i=0; i<Pt2jBins+1; i++){
    Pt2jRangeVec.push_back(Pt2jRange[i]);
    if(i>0){
      HistName = "hm_pt2jbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm2j_ptbin  = new TH1F( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm2j_ptbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm2j_ptbin->GetYaxis()->SetTitle( "Events" );
      m_pT2jBins.push_back(hm2j_ptbin);
    }
  }
  for(int i=0; i<Pt0jPt1jBins+1; i++){
    if(i>0){
      HistName = "hm_ptptbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_ptptbin = new TH1F( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_ptptbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm_ptptbin->GetYaxis()->SetTitle( "Events" );
      m_pTpTBins.push_back(hm_ptptbin);
    }
  }

  /* 4l mass plots in cts bins */
  for(int i=0; i<CtsBins+1; i++){
    CtsRangeVec.push_back(CtsRange[i]);
    if(i>0){
      HistName = "hm_ctsbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_ctsbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_ctsbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"}").c_str() );
      hm_ctsbin->GetYaxis()->SetTitle( "Events" );
      m_ctsBins.push_back(hm_ctsbin);
    }
  }
  
  /* 4l mass plots in y bins */
  for(int i=0; i<RapBins+1; i++){
    RapRangeVec.push_back(RapRange[i]);
    if(i>0){
      HistName = "hm_ybin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_ybin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_ybin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"}").c_str() );
      hm_ybin->GetYaxis()->SetTitle( "Events" );
      m_yBins.push_back(hm_ybin);
    }
  }
  
  /* 4l mass plots in m12 bins */
  for(int i=0; i<M12Bins+1; i++){
    M12RangeVec.push_back(M12Range[i]);
    if(i>0){
      HistName = "hm_m12bin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_m12bin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_m12bin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm_m12bin->GetYaxis()->SetTitle( "Events" );
      m_m12Bins.push_back(hm_m12bin);
    }
  }
  
  /* 4l mass plots in m34 bins */
  for(int i=0; i<M34Bins+1; i++){
    M34RangeVec.push_back(M34Range[i]);
    if(i>0){
      HistName = "hm_m34bin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_m34bin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_m34bin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm_m34bin->GetYaxis()->SetTitle( "Events" );
      m_m34Bins.push_back(hm_m34bin);
    }
  }
  
  /* 4l mass plots in njet bins */
  for(int i=0; i<NjetBins+1; i++){
    NjetRangeVec.push_back(NjetRange[i]);
    if(i>0){
      HistName = "hm_njetbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_njetbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_njetbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"}").c_str() );
      hm_njetbin->GetYaxis()->SetTitle( "Events" );
      m_njetBins.push_back(hm_njetbin);
    }
  }
  for(int i=0; i<NjetBinsv2+1; i++){
    NjetRangeVecv2.push_back(NjetRangev2[i]);
    if(i>0){
      HistName = "hm_njetv2bin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_njetbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_njetbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"}").c_str() );
      hm_njetbin->GetYaxis()->SetTitle( "Events" );
      m_njetBinsv2.push_back(hm_njetbin);
    }
  }
  for(int i=0; i<NjetBinsv3+1; i++){
    NjetRangeVecv3.push_back(NjetRangev3[i]);
    if(i>0){
      HistName = "hm_njetv3bin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_njetbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_njetbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"}").c_str() );
      hm_njetbin->GetYaxis()->SetTitle( "Events" );
      m_njetBinsv3.push_back(hm_njetbin);
    }
  }
  
  /* 4l mass plots in nbjet bins */
  for(int i=0; i<NbjetBins+1; i++){
    NbjetRangeVec.push_back(NbjetRange[i]);
    if(i>0){
      HistName = "hm_nbjetbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_nbjetbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_nbjetbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"}").c_str() );
      hm_nbjetbin->GetYaxis()->SetTitle( "Events" );
      m_nbjetBins.push_back(hm_nbjetbin);
    }
  }
  
  /* 4l mass plots in ljpt bins */
  for(int i=0; i<PtLjBins+1; i++){
    LjPtRangeVec.push_back(PtLjRange[i]);
    if(i>0){
      HistName = "hm_ljptbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_ljptbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_ljptbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm_ljptbin->GetYaxis()->SetTitle( "Events" );
      m_ljptBins.push_back(hm_ljptbin);
    }
  }
  
  /* 4l mass plots in mjj bins */
  for(int i=0; i<MjjBins+1; i++){
    MjjRangeVec.push_back(MjjRange[i]);
    if(i>0){
      HistName = "hm_mjjbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_mjjbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_mjjbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"} [GeV]").c_str() );
      hm_mjjbin->GetYaxis()->SetTitle( "Events" );
      m_mjjBins.push_back(hm_mjjbin);
    }
  }

  /* 4l mass plots in detajj bins */
  for(int i=0; i<EtajjBins+1; i++){
    EtajjRangeVec.push_back(EtajjRange[i]);
    if(i>0){
      HistName = "hm_etajjbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_etajjbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_etajjbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"}").c_str() );
      hm_etajjbin->GetYaxis()->SetTitle( "Events" );
      m_etajjBins.push_back(hm_etajjbin);
    }
  }

  /* 4l mass plots in dphijj bins */
  for(int i=0; i<PhijjBins+1; i++){
    PhijjRangeVec.push_back(PhijjRange[i]);
    if(i>0){
      HistName = "hm_phijjbin"+std::to_string(i-1)+"_"+Chans.at(0)+"_"+m_Process;
      hm_phijjbin = new TH1F ( HistName.c_str() , HistName.c_str() , m_Nbins, m_Min, m_Max );
      hm_phijjbin->GetXaxis()->SetTitle( ("m_{"+Labs.at(0)+"}").c_str() );
      hm_phijjbin->GetYaxis()->SetTitle( "Events" );
      m_phijjBins.push_back(hm_phijjbin);
    }
  }

}

std::vector<TObject*> MakeInput::ListOfPlotsToWrite(){

  std::vector<TObject*> list;
  for(uint i=0; i<m_VecM.size(); i++){
    list.push_back( m_VecM.at(i)              );
    //list.push_back( m_VecM0j.at(i)            );
    //list.push_back( m_VecM1j.at(i)            );
    //list.push_back( m_VecM2j.at(i)            );
    //list.push_back( m_VecMLpt.at(i)           );
    //list.push_back( m_VecMHpt.at(i)           );
    list.push_back( m_VecPT.at(i)             );
    list.push_back( m_VecPT0j.at(i)           );
    list.push_back( m_VecPT1j.at(i)           );
    list.push_back( m_VecPT2j.at(i)           );
    list.push_back( m_VecPTPT.at(i)           );
    list.push_back( m_VecM12.at(i)            );
    list.push_back( m_VecM34.at(i)            );
    list.push_back( m_VecM34B.at(i)           );
    list.push_back( m_VecNjet.at(i)           );
    list.push_back( m_VecNjetv2.at(i)         );
    list.push_back( m_VecNjetv3.at(i)         );
    list.push_back( m_VecNbjet.at(i)          );
    list.push_back( m_VecY.at(i)              );
    //list.push_back( m_VecY0j.at(i)            );
    //list.push_back( m_VecY1j.at(i)            );
    //list.push_back( m_VecYLpt.at(i)           );
    //list.push_back( m_VecYHpt.at(i)           );
    list.push_back( m_VecCts.at(i)            );
    //list.push_back( m_VecCts0j.at(i)          );
    //list.push_back( m_VecCts1j.at(i)          );
    //list.push_back( m_VecCtsLpt.at(i)         );
    //list.push_back( m_VecCtsHpt.at(i)         );
    list.push_back( m_VecJetPt.at(i)          );
    list.push_back( m_VecMJJ.at(i)            );
    list.push_back( m_VecMJJrm.at(i)          );
    list.push_back( m_VecETAJJ.at(i)          );
    list.push_back( m_VecPHIJJ.at(i)          );
    list.push_back( m_VecM12M34.at(i)         );
    list.push_back( m_VecM12M34rm.at(i)       );
    if(m_doMtx){
      list.push_back( m_VecPTmtx.at(i)          );
      list.push_back( m_VecPT0jmtx.at(i)        );
      list.push_back( m_VecPT1jmtx.at(i)        );
      list.push_back( m_VecPT2jmtx.at(i)        );
      list.push_back( m_VecM12mtx.at(i)         );
      list.push_back( m_VecM34mtx.at(i)         );
      list.push_back( m_VecYmtx.at(i)           );
      list.push_back( m_VecCTSmtx.at(i)         );
      list.push_back( m_VecNJETmtx.at(i)        );
      list.push_back( m_VecNJETmtxv2.at(i)      );
      list.push_back( m_VecNJETmtxv3.at(i)      );
      list.push_back( m_VecNBJETmtx.at(i)       );
      list.push_back( m_VecLJETmtx.at(i)        );
      list.push_back( m_VecMJJmtx.at(i)         );
      list.push_back( m_VecETAJJmtx.at(i)       );
      list.push_back( m_VecPHIJJmtx.at(i)       );
      list.push_back( m_Vechm12vsm34rmmtx.at(i) );
      list.push_back( m_Vechbin1Z1Z2mtx.at(i)   );
      list.push_back( m_Vechbin2Z1Z2mtx.at(i)   );
      list.push_back( m_Vechbin3Z1Z2mtx.at(i)   );
      list.push_back( m_Vechbin4Z1Z2mtx.at(i)   );
      list.push_back( m_Vechbin5Z1Z2mtx.at(i)   );
    }
    
  }
  for(uint i=0; i<m_pTBins.size(); i++){
    list.push_back( m_pTBins.at(i) );
  }
  for(uint i=0; i<m_pT0jBins.size(); i++){
    list.push_back( m_pT0jBins.at(i) );
  }
  for(uint i=0; i<m_pT1jBins.size(); i++){
    list.push_back( m_pT1jBins.at(i) );
  }
  for(uint i=0; i<m_pT2jBins.size(); i++){
    list.push_back( m_pT2jBins.at(i) );
  }
  for(uint i=0; i<m_ctsBins.size(); i++){
    list.push_back( m_ctsBins.at(i) );
  }
  for(uint i=0; i<m_yBins.size(); i++){
    list.push_back( m_yBins.at(i) );
  }
  for(uint i=0; i<m_m12Bins.size(); i++){
    list.push_back( m_m12Bins.at(i) );
  }
  for(uint i=0; i<m_m34Bins.size(); i++){
    list.push_back( m_m34Bins.at(i) );
  }
  for(uint i=0; i<m_njetBins.size(); i++){
    list.push_back( m_njetBins.at(i) );
  }
  for(uint i=0; i<m_njetBinsv2.size(); i++){
    list.push_back( m_njetBinsv2.at(i) );
  }
  for(uint i=0; i<m_njetBinsv3.size(); i++){
    list.push_back( m_njetBinsv3.at(i) );
  }
  for(uint i=0; i<m_nbjetBins.size(); i++){
    list.push_back( m_nbjetBins.at(i) );
  }
  for(uint i=0; i<m_ljptBins.size(); i++){
    list.push_back( m_ljptBins.at(i) );
  }
  for(uint i=0; i<m_mjjBins.size(); i++){
    list.push_back( m_mjjBins.at(i) );
  }
  for(uint i=0; i<m_etajjBins.size(); i++){
    list.push_back( m_etajjBins.at(i) );
  }
  for(uint i=0; i<m_phijjBins.size(); i++){
    list.push_back( m_phijjBins.at(i) );
  }
  for(uint i=0; i<m_pTpTBins.size(); i++){
    list.push_back( m_pTpTBins.at(i) );
  }
  return list;
  
}

std::vector<TH1F*> MakeInput::ListOfPlotsToNormalize(){

  std::vector<TH1F*> list;
  for(uint i=0; i<m_VecM.size(); i++){
    list.push_back( m_VecM.at(i)              );
    list.push_back( m_VecM0j.at(i)            );
    list.push_back( m_VecM1j.at(i)            );
    list.push_back( m_VecM2j.at(i)            );
    list.push_back( m_VecPT.at(i)             );
    list.push_back( m_VecPT0j.at(i)           );
    list.push_back( m_VecPT1j.at(i)           );
    list.push_back( m_VecPT2j.at(i)           );
    list.push_back( m_VecPTPT.at(i)           );
    list.push_back( m_VecM12.at(i)            );
    list.push_back( m_VecM34.at(i)            );
    list.push_back( m_VecM34B.at(i)           );
    list.push_back( m_VecNjet.at(i)           );
    list.push_back( m_VecNjetv2.at(i)         );
    list.push_back( m_VecNjetv3.at(i)         );
    list.push_back( m_VecNbjet.at(i)          );
    list.push_back( m_VecY.at(i)              );
    list.push_back( m_VecY0j.at(i)            );
    list.push_back( m_VecY1j.at(i)            );
    list.push_back( m_VecCts.at(i)            );
    list.push_back( m_VecCts0j.at(i)          );
    list.push_back( m_VecCts1j.at(i)          );
    list.push_back( m_VecJetPt.at(i)          );
    list.push_back( m_VecMJJ.at(i)            );
    list.push_back( m_VecETAJJ.at(i)          );
    list.push_back( m_VecPHIJJ.at(i)          );
    list.push_back( m_VecM12M34rm.at(i)       );
  }
  
  return list;
  
}

std::vector<TH1F*> MakeInput::ListOf1DPlotsToNorm(){

  std::vector<TH1F*> list;
  for(uint i=0; i<m_VecM12.size(); i++){
    SetAxisTitleOffset( m_VecM12.at(i)       );
    SetAxisTitleOffset( m_VecM34.at(i)       );
    SetAxisTitleOffset( m_VecM34B.at(i)      );
    SetAxisTitleOffset( m_VecPT.at(i)        );
    SetAxisTitleOffset( m_VecPT0j.at(i)      );
    SetAxisTitleOffset( m_VecPT1j.at(i)      );
    SetAxisTitleOffset( m_VecPT2j.at(i)      );
    SetAxisTitleOffset( m_VecPTPT.at(i)      );
    SetAxisTitleOffset( m_VecNjet.at(i)      );
    SetAxisTitleOffset( m_VecNjetv2.at(i)    );
    SetAxisTitleOffset( m_VecNjetv3.at(i)    );
    SetAxisTitleOffset( m_VecNbjet.at(i)     );
    SetAxisTitleOffset( m_VecY.at(i)         );
    SetAxisTitleOffset( m_VecY0j.at(i)       );
    SetAxisTitleOffset( m_VecY1j.at(i)       );
    SetAxisTitleOffset( m_VecYLpt.at(i)      );
    SetAxisTitleOffset( m_VecYHpt.at(i)      );
    SetAxisTitleOffset( m_VecCts.at(i)       );
    SetAxisTitleOffset( m_VecCts0j.at(i)     );
    SetAxisTitleOffset( m_VecCts1j.at(i)     );
    SetAxisTitleOffset( m_VecCtsLpt.at(i)    );
    SetAxisTitleOffset( m_VecCtsHpt.at(i)    );
    SetAxisTitleOffset( m_VecJetPt.at(i)     );
    SetAxisTitleOffset( m_VecMJJ.at(i)       );
    SetAxisTitleOffset( m_VecMJJrm.at(i)     );
    SetAxisTitleOffset( m_VecETAJJ.at(i)     );
    SetAxisTitleOffset( m_VecPHIJJ.at(i)     );
    
    list.push_back( m_VecM12.at(i)       );
    list.push_back( m_VecM34.at(i)       );
    list.push_back( m_VecM34B.at(i)      );
    list.push_back( m_VecPT.at(i)        );
    list.push_back( m_VecPT0j.at(i)      );
    list.push_back( m_VecPT1j.at(i)      );
    list.push_back( m_VecPT2j.at(i)      );
    list.push_back( m_VecPTPT.at(i)      );
    //list.push_back( m_VecNjet.at(i)      );
    //list.push_back( m_VecNbjet.at(i)     );
    list.push_back( m_VecY.at(i)         );
    list.push_back( m_VecY0j.at(i)       );
    list.push_back( m_VecY1j.at(i)       );
    list.push_back( m_VecYLpt.at(i)      );
    list.push_back( m_VecYHpt.at(i)      );
    list.push_back( m_VecCts.at(i)       );
    list.push_back( m_VecCts0j.at(i)     );
    list.push_back( m_VecCts1j.at(i)     );
    list.push_back( m_VecCtsLpt.at(i)    );
    list.push_back( m_VecCtsHpt.at(i)    );
    list.push_back( m_VecJetPt.at(i)     );
    list.push_back( m_VecMJJ.at(i)       );
    list.push_back( m_VecMJJrm.at(i)     );
    list.push_back( m_VecETAJJ.at(i)     );
    list.push_back( m_VecPHIJJ.at(i)     );
  }
  return list;
  
}

std::vector<TH2F*> MakeInput::ListOf2DPlotsToNorm(){

  std::vector<TH2F*> list;
  for(uint i=0; i<m_VecM12M34.size(); i++){
    SetAxisTitleOffset( m_VecM12M34.at(i)   );
    //list.push_back( m_VecM12M34.at(i)   );
    if(m_doMtx){
      SetAxisTitleOffset( m_VecPTmtx.at(i)     );
      SetAxisTitleOffset( m_VecPT0jmtx.at(i)   );
      SetAxisTitleOffset( m_VecPT1jmtx.at(i)   );
      SetAxisTitleOffset( m_VecPT2jmtx.at(i)   );
      SetAxisTitleOffset( m_VecM12mtx.at(i)    );
      SetAxisTitleOffset( m_VecM34mtx.at(i)    );
      SetAxisTitleOffset( m_VecYmtx.at(i)      );
      SetAxisTitleOffset( m_VecCTSmtx.at(i)    );
      SetAxisTitleOffset( m_VecNJETmtx.at(i)   );
      SetAxisTitleOffset( m_VecNJETmtxv2.at(i) );
      SetAxisTitleOffset( m_VecNJETmtxv3.at(i) );
      SetAxisTitleOffset( m_VecNBJETmtx.at(i)  );
      SetAxisTitleOffset( m_VecLJETmtx.at(i)   );
      SetAxisTitleOffset( m_VecMJJmtx.at(i)    );
      SetAxisTitleOffset( m_VecETAJJmtx.at(i)  );
      SetAxisTitleOffset( m_VecPHIJJmtx.at(i)  );
      list.push_back( m_VecPTmtx.at(i)     );
      list.push_back( m_VecPT0jmtx.at(i)   );
      list.push_back( m_VecPT1jmtx.at(i)   );
      list.push_back( m_VecPT2jmtx.at(i)   );
      list.push_back( m_VecM12mtx.at(i)    );
      list.push_back( m_VecM34mtx.at(i)    );
      list.push_back( m_VecYmtx.at(i)      );
      list.push_back( m_VecCTSmtx.at(i)    );
      list.push_back( m_VecNJETmtx.at(i)   );
      list.push_back( m_VecNJETmtxv2.at(i) );
      list.push_back( m_VecNJETmtxv3.at(i) );
      list.push_back( m_VecNBJETmtx.at(i)  );
      list.push_back( m_VecLJETmtx.at(i)   );
      list.push_back( m_VecMJJmtx.at(i)    );
      list.push_back( m_VecETAJJmtx.at(i)  );
      list.push_back( m_VecPHIJJmtx.at(i)  );
    }
  }
  return list;
  
}

void MakeInput::DivideForBinSize(std::vector<TH1F*> &plots){

  bool divBinW = false;
  std::vector<double> wid;
  wid.push_back(120.);
  wid.push_back(2880.);

  for(uint k=0; k<plots.size(); k++){

    divBinW = false;
    TString name = plots.at(k)->GetName();
    if( name.Contains("hmjjrm_") ){
      divBinW = true;
    }

    for( Int_t i=0; i<plots.at(k)->GetNbinsX(); i++){

      if(divBinW){
	plots.at(k)->SetBinContent( i+1, plots.at(k)->GetBinContent(i+1)/wid.at(i) );
	plots.at(k)->SetBinError(i+1, plots.at(k)->GetBinError(i+1)/wid.at(i) );
      }
      else{
	plots.at(k)->SetBinContent( i+1, plots.at(k)->GetBinContent(i+1)/
				    plots.at(k)->GetBinWidth(i+1) );
	plots.at(k)->SetBinError(i+1, plots.at(k)->GetBinError(i+1)/
				 plots.at(k)->GetBinWidth(i+1));
      }
      
    }
    
  }
  
}

void MakeInput::DivideForBinSize(std::vector<TH2F*> &plots){

  double binW = 1.0;
  for(uint k=0; k<plots.size(); k++){
    
    for( Int_t i=0; i<plots.at(k)->GetNbinsX(); i++){
      for( Int_t j=0; j<plots.at(k)->GetNbinsY(); j++){
	
	binW = plots.at(k)->GetXaxis()->GetBinWidth(i+1)*plots.at(k)->GetYaxis()->GetBinWidth(j+1);
	plots.at(k)->SetBinContent( i+1, j+1,
				    plots.at(k)->GetBinContent(i+1,j+1)/binW );
	plots.at(k)->SetBinError( i+1, j+1,
				  plots.at(k)->GetBinError(i+1,j+1)/binW );
      }
    }
    
  }
  
}

void MakeInput::SetAxisTitleOffset(TH1F* h){
  
  h->GetXaxis()->SetTitleOffset(1.30);
  h->GetYaxis()->SetTitleOffset(1.55);
  
}

void MakeInput::SetAxisTitleOffset(TH2F* h){
  
  h->GetXaxis()->SetTitleOffset(1.30);
  h->GetYaxis()->SetTitleOffset(1.55);
  
}

void MakeInput::MergeAndNormalizePlots(std::vector<TH1F*> &vec, double yield){
  
  bool divBinW = false;
  std::vector<double> wid;
  wid.push_back(120.);
  wid.push_back(2880.);

  //TString name =  vec[0]->GetName();
  //if( name.Contains("hmjjrm_") ){
  //  std::cout << "Processing " << name.Data() << std::endl;
  //  divBinW = false;
  //}
  
  for(int i=0; i<vec[0]->GetNbinsX(); i++){
    double content = vec[1]->GetBinContent(i+1)+vec[2]->GetBinContent(i+1)+
      vec[3]->GetBinContent(i+1)+vec[4]->GetBinContent(i+1);
    if(divBinW)
      vec[0]->SetBinContent( i+1, content/wid.at(i) );
    else
      vec[0]->SetBinContent( i+1, content );
  }
  vec[0]->Scale( yield/vec[0]->Integral() );
  
}

void MakeInput::FillZjetsPlots(std::vector<TH1F*> &vec, std::string var){


  if(var=="njetv2"){
    vec[1]->SetBinContent( 1, m_llmumu->GetBinContent(1) );
    vec[2]->SetBinContent( 1, m_llee->GetBinContent(1)   );
    vec[3]->SetBinContent( 1, m_llee->GetBinContent(1)   );
    vec[4]->SetBinContent( 1, m_llmumu->GetBinContent(1) );

    vec[1]->SetBinContent( 2, (m_llmumu->GetBinContent(2)+
			       m_llmumu->GetBinContent(3)+
			       m_llmumu->GetBinContent(4)) );
    
    vec[2]->SetBinContent( 2, (m_llee->GetBinContent(2)+
			       m_llee->GetBinContent(3)+
			       m_llee->GetBinContent(4)) );
    
    vec[3]->SetBinContent( 2, (m_llee->GetBinContent(2)+
			       m_llee->GetBinContent(3)+
			       m_llee->GetBinContent(4)) );
    
    vec[4]->SetBinContent( 2, (m_llmumu->GetBinContent(2)+
			       m_llmumu->GetBinContent(3)+
			       m_llmumu->GetBinContent(4)) );
  }
  else if(var=="njetv3"){
    vec[1]->SetBinContent( 1, m_llmumu->GetBinContent(1) );
    vec[2]->SetBinContent( 1, m_llee->GetBinContent(1)   );
    vec[3]->SetBinContent( 1, m_llee->GetBinContent(1)   );
    vec[4]->SetBinContent( 1, m_llmumu->GetBinContent(1) );

    vec[1]->SetBinContent( 2, m_llmumu->GetBinContent(2) );
    vec[2]->SetBinContent( 2, m_llee->GetBinContent(2)   );
    vec[3]->SetBinContent( 2, m_llee->GetBinContent(2)   );
    vec[4]->SetBinContent( 2, m_llmumu->GetBinContent(2) );

    vec[1]->SetBinContent( 3, (m_llmumu->GetBinContent(3)+
			       m_llmumu->GetBinContent(4)) );
    vec[2]->SetBinContent( 3, (m_llee->GetBinContent(3)+
			       m_llee->GetBinContent(4)) );
    vec[3]->SetBinContent( 3, (m_llee->GetBinContent(3)+
			       m_llee->GetBinContent(4)) );
    vec[4]->SetBinContent( 3, (m_llmumu->GetBinContent(3)+
			       m_llmumu->GetBinContent(4)) );
    
  }
  else{
    for(int b=0; b<m_llmumu->GetNbinsX(); b++){
      vec[1]->SetBinContent( b+1, m_llmumu->GetBinContent(b+1) );
      vec[2]->SetBinContent( b+1, m_llee->GetBinContent(b+1)   );
      vec[3]->SetBinContent( b+1, m_llee->GetBinContent(b+1)   );
      vec[4]->SetBinContent( b+1, m_llmumu->GetBinContent(b+1) );
    }
  }
  
  m_llmumu->Delete();
  m_llee->Delete();
  
}

void MakeInput::NormalizePlots(Float_t qqZZint, Float_t ggZZint){

  double Factor = 1.;
  TString hName;
  std::vector<TH1F*> Plots = ListOfPlotsToNormalize();
  for(uint p=0; p<Plots.size(); p++){
    hName = Plots.at(p)->GetName();
    if( hName.Contains("0j") )      Factor = 0.946;
    else if( hName.Contains("1j") || hName.Contains("ljpt") ) Factor = 0.956;
    else if( hName.Contains("2j") || hName.Contains("jj") ) Factor = 1.252;
    else Factor = 1.;
    
    std::cout << " Name " << hName << "   Factor = " << Factor << std::endl;
    Plots.at(p)->Scale( (qqZZint*Factor+ggZZint)/Plots.at(p)->Integral() );
  }
      
}
