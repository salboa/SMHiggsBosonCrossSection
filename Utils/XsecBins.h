#include "vector"
#include "iostream"
#include <TMath.h>

double pi = TMath::Pi();
  
/******************************************/
/* Define Needed Bins and Ranges for Xsec */
/******************************************/

/* m12 and m34 */
double M12Range[]  = {50.0, 64.0, 73.0, 85.0, 106.0};
double M34Range[]  = {12.0, 20.0, 24.0, 28.0, 32.0, 40.0, 55.0, 65.0};
  
Int_t M12Bins  = ( (sizeof M12Range)  / (sizeof *M12Range)  )-1;
Int_t M34Bins  = ( (sizeof M34Range)  / (sizeof *M34Range)  )-1;

/* m12 vs m34 */
double m12m34Range[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

Int_t m12m34Bins = ( (sizeof m12m34Range) / (sizeof *m12m34Range) )-1;

/* pT, lead and sub-lead jet pT */
double PtRange[]   = { 0.0, 10.0,  20.0,   30.0,   45.0, 
		      60.0, 80.0, 120.0,  200.0,  350.0, 1000.0};
double LjPtRange[] = {29.0, 30.0,  60.0,   120.0,  350.0};//, 1000.0};
double SjPtRange[] = {29.0, 30.0,  60.0,   120.0,  350.0};//, 1000.0};

Int_t PtBins   = ( (sizeof PtRange)   / (sizeof *PtRange)   )-1;
Int_t LjPtBins = ( (sizeof LjPtRange) / (sizeof *LjPtRange) )-1;
Int_t SjPtBins = ( (sizeof SjPtRange) / (sizeof *SjPtRange) )-1;

/* pT vs njet */
double Pt0jRange[]   = {0.0,  15.0,  30.0,  120.0, 350.0};//,1000.0};
double Pt1jRange[]   = {0.0,  30.0,  60.0,   80.0,  120.0,  350.0};//, 1000.0};
double Pt2jRange[]   = {0.0, 120.0, 350.0};//, 1000.};
double Pt3jRange[]   = {0.0, 120.0, 350.0};//, 1000.};
//double PtNjetRange[] = {0.0,      15.0,   30.0,  120.0, 1000.0,       //pt0j
//			1030.0, 1060.0, 1080.0, 1120.0, 1350.0, 2000.0, //pt1j
//			2120.0, 2350.0, 3000.0,                         //pt2j
//			3120.0, 3350.0, 4000.0};                        //pt3j
double PtNjetRange[] = {0.0,      15.0,   30.0,  120.0, 350.0, //pt0j
			380.0,   410.0,   430.0, 470.0, 700.0, //pt1j
			820.0,  1050.0,                        //pt2j
			1170.0, 1400.0};                       //pt3j


Int_t Pt0jBins   = ( (sizeof Pt0jRange)   / (sizeof *Pt0jRange)   )-1;
Int_t Pt1jBins   = ( (sizeof Pt1jRange)   / (sizeof *Pt1jRange)   )-1;
Int_t Pt2jBins   = ( (sizeof Pt2jRange)   / (sizeof *Pt2jRange)   )-1;
Int_t Pt3jBins   = ( (sizeof Pt3jRange)   / (sizeof *Pt3jRange)   )-1;
Int_t PtNjetBins = ( (sizeof PtNjetRange) / (sizeof *PtNjetRange) )-1;

/* pT vs y */
double Pt0yRange[]  = {0.0, 45.0, 120.0, 350.0};//, 1000.0};
double Pt1yRange[]  = {0.0, 45.0, 120.0, 350.0};//, 1000.0};
double Pt2yRange[]  = {0.0, 45.0, 120.0, 350.0};//, 1000.0};
double Pt3yRange[]  = {0.0, 45.0, 120.0, 350.0};//, 1000.0};
//double PtRapRange[] = {0.0,      45.0,  120.0,  350.0, 1000.0,  //|y|<0.5
//		       1045.0, 1120.0, 1350.0, 2000.0,          //0.5<|y|<1
//		       2045.0, 2120.0, 2350.0, 3000.0,          //1<|y|<1.5
//		       3045.0, 3120.0, 3350.0, 4000.0};         //1.5|y|<2.5
double PtRapRange[] = {0.0,      45.0,  120.0,  350.0,  //|y|<0.5
		       395.0,   470.0,  700.0,          //0.5<|y|<1
		       745.0,   820.0, 1050.0,          //1<|y|<1.5
		       1095.0, 1170.0, 1400.0};         //1.5|y|<2.5

Int_t Pt0yBins  = ( (sizeof Pt0yRange)  / (sizeof *Pt0yRange)  )-1;
Int_t Pt1yBins  = ( (sizeof Pt1yRange)  / (sizeof *Pt1yRange)  )-1;
Int_t Pt2yBins  = ( (sizeof Pt2yRange)  / (sizeof *Pt2yRange)  )-1;
Int_t Pt3yBins  = ( (sizeof Pt3yRange)  / (sizeof *Pt3yRange)  )-1;
Int_t PtRapBins = ( (sizeof PtRapRange) / (sizeof *PtRapRange) )-1;

/* njet, nbjet, y, cts, ct1, ct2, phi and phi1 */
double NjetRange[]   = {0.0, 1.0, 2.0, 3.0, 4.0};
double NjetRangev2[] = {0.0, 1.0, 2.0};
double NjetRangev3[] = {0.0, 1.0, 2.0, 3.0};
double NjetRangev4[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
double NbjetRange[]  = {0.0, 1.0, 2.0};
double RapRange[]    = {0.0, 0.15, 0.3, 0.45, 0.6, 0.75, 0.9, 1.2, 1.6, 2.0, 2.5};
double CtsRange[]    = {0.0, 0.125, 0.250, 0.375, 0.500, 0.625, 0.750, 0.875, 1.0};
double Ct1Range[]    = {-1.0, -0.750, -0.500, -0.250, 0.0, 0.250, 0.500, 0.750, 1.0};
double Ct2Range[]    = {-1.0, -0.750, -0.500, -0.250, 0.0, 0.250, 0.500, 0.750, 1.0};
double PhiRange[]    = {-pi, -6*pi/8, -4*pi/8, -2*pi/8, 0.0, 2*pi/8, 4*pi/8, 6*pi/8, pi};
double Phi1Range[]   = {-pi, -6*pi/8, -4*pi/8, -2*pi/8, 0.0, 2*pi/8, 4*pi/8, 6*pi/8, pi};

Int_t NjetBins   = ( (sizeof NjetRange)   / (sizeof *NjetRange)   )-1;
Int_t NjetBinsv2 = ( (sizeof NjetRangev2) / (sizeof *NjetRangev2) )-1;
Int_t NjetBinsv3 = ( (sizeof NjetRangev3) / (sizeof *NjetRangev3) )-1;
Int_t NjetBinsv4 = ( (sizeof NjetRangev4) / (sizeof *NjetRangev4) )-1;
Int_t NbjetBins  = ( (sizeof NbjetRange)  / (sizeof *NbjetRange)  )-1;
Int_t RapBins    = ( (sizeof RapRange)    / (sizeof *RapRange)    )-1;
Int_t CtsBins    = ( (sizeof CtsRange)    / (sizeof *CtsRange)    )-1;
Int_t Ct1Bins    = ( (sizeof Ct1Range)    / (sizeof *Ct1Range)    )-1;
Int_t Ct2Bins    = ( (sizeof Ct2Range)    / (sizeof *Ct2Range)    )-1;
Int_t PhiBins    = ( (sizeof PhiRange)    / (sizeof *PhiRange)    )-1;
Int_t Phi1Bins   = ( (sizeof Phi1Range)   / (sizeof *Phi1Range)   )-1;

/*mjj, etajj and phijj*/
double MjjRange[]   = {0.0, 1.0, 2.0, 4.0, 7.0};
double EtajjRange[] = {0.0, 1.0, 2.0, 3.5, 10.0};
double PhijjRange[] = {0.0, 1.0, 0.5*pi+1, pi+1, 1.5*pi+1, 2*pi+1};

Int_t MjjBins    = ( (sizeof MjjRange)   / (sizeof *MjjRange)   )-1;
Int_t EtajjBins  = ( (sizeof EtajjRange) / (sizeof *EtajjRange) )-1;
Int_t PhijjBins  = ( (sizeof PhijjRange) / (sizeof *PhijjRange) )-1;


/**************************************/
/*   Define Needed bin edges vector   */
/**************************************/
std::vector<double> m_PtRangeVec      ;
std::vector<double> m_Pt0jRangeVec    ;
std::vector<double> m_Pt1jRangeVec    ;
std::vector<double> m_Pt2jRangeVec    ;
std::vector<double> m_Pt3jRangeVec    ;
std::vector<double> m_PtNjetRangeVec  ;
std::vector<double> m_Pt0yRangeVec    ;
std::vector<double> m_Pt1yRangeVec    ;
std::vector<double> m_Pt2yRangeVec    ;
std::vector<double> m_Pt3yRangeVec    ;
std::vector<double> m_PtRapRangeVec   ;
std::vector<double> m_CtsRangeVec     ;
std::vector<double> m_Ct1RangeVec     ;
std::vector<double> m_Ct2RangeVec     ;
std::vector<double> m_PhiRangeVec     ;
std::vector<double> m_Phi1RangeVec    ;
std::vector<double> m_RapRangeVec     ;
std::vector<double> m_NjetRangeVec    ;
std::vector<double> m_NjetRangeVecv2  ;
std::vector<double> m_NjetRangeVecv3  ;
std::vector<double> m_NjetRangeVecv4  ;
std::vector<double> m_NbjetRangeVec   ;
std::vector<double> m_LjPtRangeVec    ;
std::vector<double> m_SjPtRangeVec    ;
std::vector<double> m_MjjRangeVec     ;
std::vector<double> m_MjjRangeVecBis  ;
std::vector<double> m_EtajjRangeVec   ;
std::vector<double> m_EtajjRangeVecBis;
std::vector<double> m_PhijjRangeVec   ;
std::vector<double> m_PhijjRangeVecBis;
std::vector<double> m_M12RangeVec     ;
std::vector<double> m_M34RangeVec     ;

void FillVarsRanges(){

  /* 4l mass plots in pt bins */
  for(int i=0; i<PtBins+1; i++){
    m_PtRangeVec.push_back(PtRange[i]);
  }
  for(int i=0; i<Pt0jBins+1; i++){
    m_Pt0jRangeVec.push_back(Pt0jRange[i]);
  }
  for(int i=0; i<Pt1jBins+1; i++){
    m_Pt1jRangeVec.push_back(Pt1jRange[i]);
  }
  for(int i=0; i<Pt2jBins+1; i++){
    m_Pt2jRangeVec.push_back(Pt2jRange[i]);
  }
  for(int i=0; i<Pt3jBins+1; i++){
    m_Pt3jRangeVec.push_back(Pt3jRange[i]);
  }
  for(int i=0; i<PtNjetBins+1; i++){
    m_PtNjetRangeVec.push_back(PtNjetRange[i]);
  }
  for(int i=0; i<Pt0yBins+1; i++){
    m_Pt0yRangeVec.push_back(Pt0yRange[i]);
  }
  for(int i=0; i<Pt1yBins+1; i++){
    m_Pt1yRangeVec.push_back(Pt1yRange[i]);
  }
  for(int i=0; i<Pt2yBins+1; i++){
    m_Pt2yRangeVec.push_back(Pt2yRange[i]);
  }
  for(int i=0; i<Pt3yBins+1; i++){
    m_Pt3yRangeVec.push_back(Pt3yRange[i]);
  }
  for(int i=0; i<PtRapBins+1; i++){
    m_PtRapRangeVec.push_back(PtRapRange[i]);
  }
  /* 4l mass plots in cts, ct1, ct2 bins */ 
  for(int i=0; i<CtsBins+1; i++){
    m_CtsRangeVec.push_back(CtsRange[i]);
  }
  for(int i=0; i<Ct1Bins+1; i++){
    m_Ct1RangeVec.push_back(Ct1Range[i]);
  }
  for(int i=0; i<Ct2Bins+1; i++){
    m_Ct2RangeVec.push_back(Ct2Range[i]);
  }
  /* 4l mass plots in phi, phi1 and y bins */
  for(int i=0; i<PhiBins+1; i++){
    m_PhiRangeVec.push_back(PhiRange[i]);
  }
  for(int i=0; i<Phi1Bins+1; i++){
    m_Phi1RangeVec.push_back(Phi1Range[i]);
  }
  for(int i=0; i<RapBins+1; i++){
    m_RapRangeVec.push_back(RapRange[i]);
  }
  /* 4l mass plots in njet and nbjet bins */
  for(int i=0; i<NjetBins+1; i++){
    m_NjetRangeVec.push_back(NjetRange[i]);
  }
  for(int i=0; i<NjetBinsv2+1; i++){
    m_NjetRangeVecv2.push_back(NjetRangev2[i]);
  }
  for(int i=0; i<NjetBinsv3+1; i++){
    m_NjetRangeVecv3.push_back(NjetRangev3[i]);
  }
  for(int i=0; i<NjetBinsv4+1; i++){
    m_NjetRangeVecv4.push_back(NjetRangev4[i]);
  } 
  for(int i=0; i<NbjetBins+1; i++){
    m_NbjetRangeVec.push_back(NbjetRange[i]);
  }
  /* 4l mass plots in ljpt, sjpt, mjj, phijj and etajj bins */
  for(int i=0; i<LjPtBins+1; i++){
    m_LjPtRangeVec.push_back(LjPtRange[i]);
  }
  for(int i=0; i<SjPtBins+1; i++){
    m_SjPtRangeVec.push_back(SjPtRange[i]);
  }
  for(int i=0; i<MjjBins+1; i++){
    m_MjjRangeVec.push_back(MjjRange[i]);
  }
  for(int i=0; i<EtajjBins+1; i++){
    m_EtajjRangeVec.push_back(EtajjRange[i]);
  }
  for(int i=0; i<PhijjBins+1; i++){
    m_PhijjRangeVec.push_back(PhijjRange[i]);
  }
  /* 4l mass plots in m12 and m34 bins */
  for(int i=0; i<M12Bins+1; i++){
    m_M12RangeVec.push_back(M12Range[i]);
  }
  for(int i=0; i<M34Bins+1; i++){
    m_M34RangeVec.push_back(M34Range[i]);
  }

  /* filling additional mjj/etajj/phijj vectors */
  m_MjjRangeVecBis.push_back(    0.0 );
  m_MjjRangeVecBis.push_back(  120.0 );
  m_MjjRangeVecBis.push_back(  450.0 );
  m_MjjRangeVecBis.push_back( 3000.0 );

  m_EtajjRangeVecBis.push_back( 0.0 );
  m_EtajjRangeVecBis.push_back( 1.0 );
  m_EtajjRangeVecBis.push_back( 2.5 );
  m_EtajjRangeVecBis.push_back( 9.0 );

  m_PhijjRangeVecBis.push_back( 0.0    );
  m_PhijjRangeVecBis.push_back( 0.5*pi );
  m_PhijjRangeVecBis.push_back( pi     );
  m_PhijjRangeVecBis.push_back( 1.5*pi );
  m_PhijjRangeVecBis.push_back( 2*pi   );
  
}
