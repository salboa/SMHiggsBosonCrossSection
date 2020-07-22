#include "map"
#include "iostream"
#include "Enum.h"
#include "XsecBins.h"

std::vector<std::string> m_diffVars;
std::map<int,std::string> m_mcTypeMap;
std::vector<double> m_values;

std::string FindZjetVarName(std::string vName){

  PRINT_VERBOSE("<FindZjetVarName()>:: retrieving Z+jets variable name ... ");

  std::string m_name = "";
  if(vName=="njet"   || vName=="njetv2" ||
     vName=="njetv3" || vName=="njetv4"  ) m_name = "njets"      ;
  else if(vName=="nbjet")                  m_name = "nbjets"     ;
  else if(vName=="pt4l")                   m_name = "pt4l_incl"  ;
  else if(vName=="ljpt")                   m_name = "jet1pt"     ;
  else if(vName=="sjpt")                   m_name = "jet2pt"     ;
  else if(vName=="etajj")                  m_name = "detajj"     ;
  else if(vName=="phijj")                  m_name = "dphijj"     ;
  else if(vName=="ct1")                    m_name = "cth1"       ;
  else if(vName=="ct2")                    m_name = "cth2"       ;
  else if(vName=="pt0j")                   m_name = "pt4l_0Jet"  ;
  else if(vName=="pt1j")                   m_name = "pt4l_1Jet"  ;
  else if(vName=="pt2j")                   m_name = "pt4l_2Jet"  ;
  else if(vName=="pt3j")                   m_name = "pt4l_ge3Jet";
  else if(vName=="pt0y")                   m_name = "pt4l_y4l0"  ;
  else if(vName=="pt1y")                   m_name = "pt4l_y4l1"  ;
  else if(vName=="pt2y")                   m_name = "pt4l_y4l2"  ;
  else if(vName=="pt3y")                   m_name = "pt4l_y4l3"  ;
  else                                     m_name = vName;
  return m_name;
  
}

void FillDiffVarVector(std::string var, bool addVars){

  PRINT_VERBOSE("<FillDiffVarVector()>:: filling differential variables vector ... ");

  if(var==""){
    m_diffVars.push_back( "m4l"    );
    m_diffVars.push_back( "pt4l"   );
    m_diffVars.push_back( "njet"   );
    m_diffVars.push_back( "njetv2" );
    m_diffVars.push_back( "njetv3" );
    m_diffVars.push_back( "njetv4" );
    m_diffVars.push_back( "nbjet"  );
    m_diffVars.push_back( "m12"    );
    m_diffVars.push_back( "m34"    );
    m_diffVars.push_back( "y4l"    );
    m_diffVars.push_back( "cts"    );
    m_diffVars.push_back( "ljpt"   );
    m_diffVars.push_back( "sjpt"   );
    m_diffVars.push_back( "mjj"    );
    m_diffVars.push_back( "etajj"  );
    m_diffVars.push_back( "phijj"  );
    m_diffVars.push_back( "m12m34" );
    m_diffVars.push_back( "ptnjet" );
    m_diffVars.push_back( "pty4l"  );
    m_diffVars.push_back( "ct1"    );
    m_diffVars.push_back( "ct2"    );
    m_diffVars.push_back( "phi"    );
    m_diffVars.push_back( "phi1"   );
    if(addVars){
      m_diffVars.push_back( "pt0j" );
      m_diffVars.push_back( "pt1j" );
      m_diffVars.push_back( "pt2j" );
      m_diffVars.push_back( "pt3j" );
      m_diffVars.push_back( "pt0y" );
      m_diffVars.push_back( "pt1y" );
      m_diffVars.push_back( "pt2y" );
      m_diffVars.push_back( "pt3y" );
    }
  }
  else{
    m_diffVars.push_back( var );
  }
  
}

void FillMcVersionsMap(){

  PRINT_VERBOSE("<FillMcVersionsMap()>:: filling mc versions map ... ");

  m_mcTypeMap[MCtype::All  ] = "mc16" ;
  m_mcTypeMap[MCtype::mc15c] = "mc15c";
  m_mcTypeMap[MCtype::mc16a] = "mc16a";
  m_mcTypeMap[MCtype::mc16d] = "mc16d";
  m_mcTypeMap[MCtype::mc16e] = "mc16e";
  
}

int GetVariableID(std::string var){
  
  PRINT_VERBOSE("<GetVariableID()>:: retrieving enum for variable "+var+" ... ");
  
  if     ( var=="pt4l"     ) return Variable::pt4l   ;
  else if( var=="pt0j"     ) return Variable::pt0j   ;
  else if( var=="pt1j"     ) return Variable::pt1j   ;
  else if( var=="pt2j"     ) return Variable::pt2j   ;
  else if( var=="pt3j"     ) return Variable::pt3j   ;
  else if( var=="pt0y"     ) return Variable::pt0y   ;
  else if( var=="pt1y"     ) return Variable::pt1y   ;
  else if( var=="pt2y"     ) return Variable::pt2y   ;
  else if( var=="pt3y"     ) return Variable::pt3y   ;
  else if( var=="m12"      ) return Variable::m12    ;
  else if( var=="m34"      ) return Variable::m34    ;
  else if( var=="y4l"      ) return Variable::y4l    ;
  else if( var=="njet"     ) return Variable::njet   ;
  else if( var=="cts"      ) return Variable::cts    ;
  else if( var=="ljpt"     ) return Variable::ljpt   ;
  else if( var=="sjpt"     ) return Variable::sjpt   ;
  else if( var=="mjj"      ) return Variable::mjj    ;
  else if( var=="etajj"    ) return Variable::etajj  ;
  else if( var=="phijj"    ) return Variable::phijj  ;
  else if( var=="nbjet"    ) return Variable::nbjet  ;
  else if( var=="m12m34"   ) return Variable::m12m34 ;
  else if( var=="njetv2"   ) return Variable::njetv2 ;
  else if( var=="njetv3"   ) return Variable::njetv3 ;
  else if( var=="njetv4"   ) return Variable::njetv4 ;
  else if( var=="m4l"      ) return Variable::m4l    ;
  else if( var=="evt_type" ) return Variable::evtype ;
  else if( var=="ptnjet"   ) return Variable::ptnjet ;
  else if( var=="pty4l"    ) return Variable::pty4l  ;
  else if( var=="ct1"      ) return Variable::ct1    ;
  else if( var=="ct2"      ) return Variable::ct2    ;
  else if( var=="phi"      ) return Variable::phi    ;
  else if( var=="phi1"     ) return Variable::phi1   ;
  else if( var=="jet_eta"  ) return Variable::jet_eta;
  else if( var=="jet_phi"  ) return Variable::jet_phi;
  else if( var=="jet_pt"   ) return Variable::jet_pt ;
  else{
    PRINT_FATAL("                                  Variable "+var+
		" not defined -> exiting ... ");
    exit(0);
  }
  
}

std::vector<double> GetVariableRanges(int vNum){
  
  switch(vNum){
  case Variable::pt4l  : return m_PtRangeVec       ;
  case Variable::pt0j  : return m_Pt0jRangeVec     ;
  case Variable::pt1j  : return m_Pt1jRangeVec     ;
  case Variable::pt2j  : return m_Pt2jRangeVec     ;
  case Variable::pt3j  : return m_Pt3jRangeVec     ;
  case Variable::pt0y  : return m_Pt0yRangeVec     ;
  case Variable::pt1y  : return m_Pt1yRangeVec     ;
  case Variable::pt2y  : return m_Pt2yRangeVec     ;
  case Variable::pt3y  : return m_Pt3yRangeVec     ;
  case Variable::cts   : return m_CtsRangeVec      ;
  case Variable::y4l   : return m_RapRangeVec      ;
  case Variable::njet  : return m_NjetRangeVec     ;
  case Variable::njetv2: return m_NjetRangeVecv2   ;
  case Variable::njetv3: return m_NjetRangeVecv3   ;
  case Variable::njetv4: return m_NjetRangeVecv4   ;
  case Variable::nbjet : return m_NbjetRangeVec    ;
  case Variable::ljpt  : return m_LjPtRangeVec     ;
  case Variable::sjpt  : return m_SjPtRangeVec     ;
  case Variable::mjj   : return m_MjjRangeVecBis   ;
  case Variable::etajj : return m_EtajjRangeVecBis ;
  case Variable::phijj : return m_PhijjRangeVecBis ;
  case Variable::m12   : return m_M12RangeVec      ;
  case Variable::m34   : return m_M34RangeVec      ;
  case Variable::ptnjet: return m_PtNjetRangeVec   ;
  case Variable::pty4l : return m_PtRapRangeVec    ;
  case Variable::ct1   : return m_Ct1RangeVec      ;
  case Variable::ct2   : return m_Ct2RangeVec      ;
  case Variable::phi   : return m_PhiRangeVec      ;
  case Variable::phi1  : return m_Phi1RangeVec     ;
  default:
    PRINT_FATAL("                                  VariableId "+
		std::to_string(vNum)+" not defined -> exiting ... ");
    exit(0);
  }
  
}

std::vector<int> GetVarBinRange(int vNum){

  switch(vNum){
  case Variable::m4l   : return (std::vector<int>) { 1 }                          ;
  case Variable::pt4l  : return (std::vector<int>) { 1, 2, 3, 5, PtBins+1 }       ;
  case Variable::pt0j  : return (std::vector<int>) { Pt0jBins+1 }                 ;
  case Variable::pt1j  : return (std::vector<int>) { Pt1jBins+1 }                 ;
  case Variable::pt2j  : return (std::vector<int>) { Pt2jBins+1 }                 ;
  case Variable::pt3j  : return (std::vector<int>) { Pt3jBins+1 }                 ;
  case Variable::pt0y  : return (std::vector<int>) { Pt0yBins+1 }                 ;
  case Variable::pt1y  : return (std::vector<int>) { Pt1yBins+1 }                 ;
  case Variable::pt2y  : return (std::vector<int>) { Pt2yBins+1 }                 ;
  case Variable::pt3y  : return (std::vector<int>) { Pt3yBins+1 }                 ;
  case Variable::cts   : return (std::vector<int>) { 2, 4, 6, CtsBins+1 }         ;
  case Variable::y4l   : return (std::vector<int>) { 1, 2, 3, 4, 5, 7, RapBins+1 };
  case Variable::njet  : return (std::vector<int>) { 1, 2, NjetBins+1 }           ;
  case Variable::njetv2: return (std::vector<int>) { 1, NjetBinsv2+1 }            ;
  case Variable::njetv3: return (std::vector<int>) { 1, 2, NjetBinsv3+1 }         ;
  case Variable::njetv4: return (std::vector<int>) { 1, 2, NjetBinsv4+1 }         ;
  case Variable::nbjet : return (std::vector<int>) { 1, NbjetBins+1 }             ;
  case Variable::ljpt  : return (std::vector<int>) { 1, 2, 3, LjPtBins+1 }        ;
  case Variable::sjpt  : return (std::vector<int>) { 1, 2, SjPtBins+1 }           ;
  case Variable::mjj   : return (std::vector<int>) { 1, 2, MjjBins+1 }            ;
  case Variable::etajj : return (std::vector<int>) { 1, 2, EtajjBins+1 }          ;
  case Variable::phijj : return (std::vector<int>) { 1, 3, PhijjBins+1 }          ;
  case Variable::m12   : return (std::vector<int>) { 2, 3, M12Bins+1 }            ;
  case Variable::m34   : return (std::vector<int>) { 2, 4, M34Bins+1 }            ;
  case Variable::m12m34: return (std::vector<int>) { 2, 3 ,4, m12m34Bins+1 }      ;
  case Variable::ptnjet: return (std::vector<int>) { 5, 10, PtNjetBins+1 }        ;
  case Variable::pty4l : return (std::vector<int>) { 4, 7, PtRapBins+1 }          ;
  case Variable::ct1   : return (std::vector<int>) { 2, 4, 6, Ct1Bins+1 }         ;
  case Variable::ct2   : return (std::vector<int>) { 2, 4, 6, Ct2Bins+1 }         ;
  case Variable::phi   : return (std::vector<int>) { 2, 4, 6, PhiBins+1 }         ;
  case Variable::phi1  : return (std::vector<int>) { 2, 4, 6, Phi1Bins+1 }        ;
  default:
    PRINT_FATAL("                                  VariableId "+
		std::to_string(vNum)+" not defined -> exiting ... ");
    exit(0);
  }
  
}

int FindBin(int vNum, double val){

  if(vNum==Variable::m4l) return 0;
  else                   m_values = GetVariableRanges(vNum);
  
  int m_bin = -1;
  
  /* deal underflow bin for ljpt/mjj/etajj/phijj */
  if( (vNum==Variable::ljpt || vNum==Variable::sjpt  ||
       vNum==Variable::mjj  || vNum==Variable::etajj ||
       vNum==Variable::phijj ) && val==-999 ) return 0;
  if(val==-999) return -1;

  double m_val = val;
  if( vNum!=Variable::ct1 && vNum!=Variable::ct2 &&
      vNum!=Variable::phi && vNum!=Variable::phi1 )
    m_val = fabs(val);
  
  for(int i=0; i<(int)m_values.size()-1; i++){
    /* check bins */
    if( m_val>=m_values[i] && m_val<m_values[i+1] ){ m_bin = i; break; }
    
    /* deal overflow for njets/nbjet */
    if( (vNum==Variable::njet    || vNum==Variable::njetv2 ||
	 vNum==Variable::njetv3  || vNum==Variable::njetv4 ||
	 vNum==Variable::nbjet) && m_val>m_values[(int)m_values.size()-2] )
      m_bin = (int)m_values.size()-2;
  }
  if(vNum==Variable::mjj || vNum==Variable::etajj || vNum==Variable::phijj)
    m_bin = m_bin+1;

  PRINT_VERBOSE("                       bin = "+std::to_string(m_bin));

  return m_bin;
  
}

int FindBin(int vNum, double val1, double val2){

  PRINT_VERBOSE("<FindBin()> :: Finding bin for variableId "+
		std::to_string(vNum)+" ... ");
  
  int m_bin = -1;
  if(vNum==Variable::m12m34){
    if(val2<32 && val1<82)            m_bin = 0;
    if(val2>32 && val1<74)            m_bin = 1;
    if(val2>32 && val1>74)            m_bin = 2;
    if(val2<32 && val2>24 && val1>82) m_bin = 3;
    if(val2<24 && val1>82)            m_bin = 4;
  }
  else{
    double v_sht = 0.;
    if(vNum==Variable::ptnjet){
      if(val2==0)     { v_sht = 0.0   ; }
      else if(val2==1){ v_sht = 350.0 ; }
      else if(val2==2){ v_sht = 700.0 ; }
      else            { v_sht = 1050.0; }
    }
    else if(vNum==Variable::pty4l){
      if(val2<0.5)     { v_sht = 0.0   ; }
      else if(val2<1.0){ v_sht = 350.0 ; }
      else if(val2<1.5){ v_sht = 700.0 ; }
      else if(val2<2.5){ v_sht = 1050.0; }
      else             { v_sht = 9000.0; }
    }
    m_bin = FindBin(vNum,val1+v_sht);
  }
  return m_bin;
  
}

int GetNumberOfBins(std::string var){

  PRINT_VERBOSE("<GetNumberOfBins()> :: Retrieving number of bins for variable "+var+
		" ... ");
  
  int vNum = GetVariableID(var);
  switch(vNum){
  case Variable::pt4l  : return PtBins    ;
  case Variable::pt0j  : return Pt0jBins  ;
  case Variable::pt1j  : return Pt1jBins  ;
  case Variable::pt2j  : return Pt2jBins  ;
  case Variable::pt3j  : return Pt3jBins  ;
  case Variable::pt0y  : return Pt0yBins  ;
  case Variable::pt1y  : return Pt1yBins  ;
  case Variable::pt2y  : return Pt2yBins  ;
  case Variable::pt3y  : return Pt3yBins  ;  
  case Variable::cts   : return CtsBins   ;
  case Variable::y4l   : return RapBins   ;
  case Variable::njet  : return NjetBins  ;
  case Variable::njetv2: return NjetBinsv2;
  case Variable::njetv3: return NjetBinsv3;
  case Variable::njetv4: return NjetBinsv4;
  case Variable::nbjet : return NbjetBins ;
  case Variable::ljpt  : return LjPtBins  ;
  case Variable::sjpt  : return SjPtBins  ;
  case Variable::mjj   : return MjjBins   ;
  case Variable::etajj : return EtajjBins ;
  case Variable::phijj : return PhijjBins ;
  case Variable::m4l   : return 1         ;
  case Variable::m12   : return M12Bins   ;
  case Variable::m34   : return M34Bins   ;
  case Variable::m12m34: return m12m34Bins;
  case Variable::ptnjet: return PtNjetBins;
  case Variable::pty4l : return PtRapBins ;
  case Variable::ct1   : return Ct1Bins   ;
  case Variable::ct2   : return Ct2Bins   ;
  case Variable::phi   : return PhiBins   ;
  case Variable::phi1  : return Phi1Bins  ;
  default:
    PRINT_FATAL("                                  Variable "+var+
		" not defined -> exiting ... ");
    exit(0);
  }
  
}

int GetNumberOfBins(int vNum){

  PRINT_VERBOSE("<GetNumberOfBins()> :: Retrieving number of bins for variableId "+
		std::to_string(vNum)+" ... ");

  switch(vNum){
  case Variable::pt4l  : return PtBins    ;
  case Variable::pt0j  : return Pt0jBins  ;
  case Variable::pt1j  : return Pt1jBins  ;
  case Variable::pt2j  : return Pt2jBins  ;
  case Variable::pt3j  : return Pt3jBins  ;
  case Variable::pt0y  : return Pt0yBins  ;
  case Variable::pt1y  : return Pt1yBins  ;
  case Variable::pt2y  : return Pt2yBins  ;
  case Variable::pt3y  : return Pt3yBins  ;
  case Variable::cts   : return CtsBins   ;
  case Variable::y4l   : return RapBins   ;
  case Variable::njet  : return NjetBins  ;
  case Variable::njetv2: return NjetBinsv2;
  case Variable::njetv3: return NjetBinsv3;
  case Variable::njetv4: return NjetBinsv4;
  case Variable::nbjet : return NbjetBins ;
  case Variable::ljpt  : return LjPtBins  ;
  case Variable::sjpt  : return SjPtBins  ;
  case Variable::mjj   : return MjjBins   ;
  case Variable::etajj : return EtajjBins ;
  case Variable::phijj : return PhijjBins ;
  case Variable::m4l   : return 1         ;
  case Variable::m12   : return M12Bins   ;
  case Variable::m34   : return M34Bins   ;
  case Variable::m12m34: return m12m34Bins;
  case Variable::ptnjet: return PtNjetBins;
  case Variable::pty4l : return PtRapBins ;
  case Variable::ct1   : return Ct1Bins   ;
  case Variable::ct2   : return Ct2Bins   ;
  case Variable::phi   : return PhiBins   ;
  case Variable::phi1  : return Phi1Bins  ;
  default:
    PRINT_FATAL("                                  VariableId "+std::to_string(vNum)+
		" not found -> exiting ... ");
    exit(0);
  }
  
}

std::string GetVariableName(int vNum){

  PRINT_VERBOSE("<GetVariableName()> :: Retrieving name for variableId "+
		std::to_string(vNum)+" ... ");

  switch(vNum){
  case Variable::pt4l   : return "pt"      ;
  case Variable::pt0j   : return "pt0j"    ;
  case Variable::pt1j   : return "pt1j"    ;
  case Variable::pt2j   : return "pt2j"    ;
  case Variable::pt3j   : return "pt3j"    ;
  case Variable::pt0y   : return "pt0y"    ;
  case Variable::pt1y   : return "pt1y"    ;
  case Variable::pt2y   : return "pt2y"    ;
  case Variable::pt3y   : return "pt3y"    ; 
  case Variable::m12    : return "m12"     ;
  case Variable::m34    : return "m34"     ;
  case Variable::m12m34 : return "m12m34"  ;
  case Variable::y4l    : return "y"       ;
  case Variable::njet   : return "njet"    ;
  case Variable::njetv2 : return "njetv2"  ;
  case Variable::njetv3 : return "njetv3"  ;
  case Variable::njetv4 : return "njetv4"  ;
  case Variable::nbjet  : return "nbjet"   ;
  case Variable::cts    : return "cts"     ;
  case Variable::ljpt   : return "ljpt"    ;
  case Variable::sjpt   : return "sjpt"    ;
  case Variable::mjj    : return "mjj"     ;
  case Variable::etajj  : return "etajj"   ;
  case Variable::phijj  : return "phijj"   ;
  case Variable::evtype : return "evt_type";
  case Variable::ptnjet : return "ptnjet"  ;
  case Variable::pty4l  : return "pty"     ;
  case Variable::ct1    : return "ct1"     ;
  case Variable::ct2    : return "ct2"     ;
  case Variable::phi    : return "phi"     ;
  case Variable::phi1   : return "phi1"    ;
  case Variable::jet_eta: return "jet_eta" ;
  case Variable::jet_phi: return "jet_phi" ;
  case Variable::jet_pt : return "jet_pt"  ;
  default: 
    /*case for m4l -> setting to ' ' */
    return "";
  }
  
}

std::string GetVariableName(std::string var){

  PRINT_VERBOSE("<GetVariableName()> :: Retrieving name for variable "+var+" ... ");
  
  int vNum = GetVariableID(var);
  switch(vNum){
  case Variable::pt4l   : return "pt"      ;
  case Variable::pt0j   : return "pt0j"    ;
  case Variable::pt1j   : return "pt1j"    ;
  case Variable::pt2j   : return "pt2j"    ;
  case Variable::pt3j   : return "pt3j"    ;
  case Variable::pt0y   : return "pt0y"    ;
  case Variable::pt1y   : return "pt1y"    ;
  case Variable::pt2y   : return "pt2y"    ;
  case Variable::pt3y   : return "pt3y"    ;  
  case Variable::m12    : return "m12"     ;
  case Variable::m34    : return "m34"     ;
  case Variable::y4l    : return "y"       ;
  case Variable::njet   : return "njet"    ;
  case Variable::njetv2 : return "njetv2"  ;
  case Variable::njetv3 : return "njetv3"  ;
  case Variable::njetv4 : return "njetv4"  ;
  case Variable::nbjet  : return "nbjet"   ;
  case Variable::cts    : return "cts"     ;
  case Variable::ljpt   : return "ljpt"    ;
  case Variable::sjpt   : return "sjpt"    ;
  case Variable::mjj    : return "mjj"     ;
  case Variable::etajj  : return "etajj"   ;
  case Variable::phijj  : return "phijj"   ;
  case Variable::evtype : return "evt_type";
  case Variable::m12m34 : return "m12m34"  ;
  case Variable::ptnjet : return "ptnjet"  ;
  case Variable::pty4l  : return "pty"     ;
  case Variable::ct1    : return "ct1"     ;
  case Variable::ct2    : return "ct2"     ;
  case Variable::phi    : return "phi"     ;
  case Variable::phi1   : return "phi1"    ;
  case Variable::jet_eta: return "jet_eta" ;
  case Variable::jet_phi: return "jet_phi" ;
  case Variable::jet_pt : return "jet_pt"  ;
  default: 
    PRINT_WARNING("                                  Variable "+var+
		  " not found (probably running Fiducial) -> setting to ' ' ... ");
    return "";
  }
  
}

std::string GetVariableXaxisLabel(int vNum){

  PRINT_VERBOSE("<GetVariableXaxisLabel()> :: Retrieving X axis label for variableId "+
		std::to_string(vNum)+" ... ");

  switch(vNum){
  case Variable::pt4l   : return "#font[12]{p}_{T,4#font[12]{l}} [GeV]"                                         ;
  case Variable::pt0j   : return "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0} [GeV]"                 ;
  case Variable::pt1j   : return "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1} [GeV]"                 ;
  case Variable::pt2j   : return "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=2} [GeV]"                 ;
  case Variable::pt3j   : return "#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq3} [GeV]"              ;
  case Variable::pt0y   : return "#font[12]{p}_{T,4#font[12]{l}}^{|#font[12]{y}_{4#font[12]{l}}|<0.5} [GeV]"    ;
  case Variable::pt1y   : return "#font[12]{p}_{T,4#font[12]{l}}^{0.5<|#font[12]{y}_{4#font[12]{l}}|<1.0} [GeV]";
  case Variable::pt2y   : return "#font[12]{p}_{T,4#font[12]{l}}^{1.0<|#font[12]{y}_{4#font[12]{l}}|<1.5} [GeV]";
  case Variable::pt3y   : return "#font[12]{p}_{T,4#font[12]{l}}^{1.5<|#font[12]{y}_{4#font[12]{l}}|<2.5} [GeV]";
  case Variable::m12    : return "#font[12]{m}_{12} [GeV]"                                                      ;
  case Variable::m34    : return "#font[12]{m}_{34} [GeV]"                                                      ;
  case Variable::m12m34 : return "#font[12]{m}_{12} vs #font[12]{m}_{34}"                                       ;
  case Variable::y4l    : return "|#font[12]{y}_{4#font[12]{l}}|"                                               ;
  case Variable::njet   : return "#font[12]{N}_{jets}"                                                          ;
  case Variable::njetv2 : return "#font[12]{N}_{jets}"                                                          ;
  case Variable::njetv3 : return "#font[12]{N}_{jets}"                                                          ;
  case Variable::njetv4 : return "#font[12]{N}_{jets}"                                                          ;
  case Variable::nbjet  : return "#font[12]{N}_{b-jets}"                                                        ;
  case Variable::cts    : return "|cos#theta*|"                                                                 ;
  case Variable::ljpt   : return "#font[12]{p}_{T}^{lead. jet} [GeV]"                                           ;
  case Variable::sjpt   : return "#font[12]{p}_{T}^{sub. lead. jet} [GeV]"                                      ;
  case Variable::mjj    : return "#font[12]{m}_{jj} [GeV]"                                                      ;
  case Variable::etajj  : return "#Delta#eta_{jj}"                                                              ;
  case Variable::phijj  : return "#Delta#phi_{jj} [rad]"                                                        ;
  case Variable::ptnjet : return "#font[12]{p}_{T,4#font[12]{l}} [GeV] vs #font[12]{N}_{jets}"                  ;
  case Variable::pty4l  : return "#font[12]{p}_{T,4#font[12]{l}} [GeV] vs |#font[12]{y}_{4#font[12]{l}}|"       ;
  case Variable::ct1    : return "cos#theta_{1}"                                                                ;
  case Variable::ct2    : return "cos#theta_{2}"                                                                ;
  case Variable::phi    : return "#phi [rad]"                                                                   ;
  case Variable::phi1   : return "#phi_{1} [rad]"                                                               ;
  default: 
    return "dummy label";
  }
  
}

std::string GetVariableDistroYaxisLabel(int vNum){

  PRINT_VERBOSE("<GetVariableDistroYaxisLabel()> :: Retrieving Y axis label for variableId "+
		std::to_string(vNum)+" ... ");

  switch(vNum){
  case Variable::y4l   :
  case Variable::cts   :
  case Variable::ct1   :
  case Variable::ct2   :
  case Variable::etajj : return "Events / Bin Width";
  case Variable::phi   :
  case Variable::phi1  :
  case Variable::phijj : return "Events / #pi";
  case Variable::m12m34:
  case Variable::njet  :
  case Variable::njetv2:
  case Variable::njetv3:
  case Variable::njetv4:
  case Variable::nbjet : return "Events";
  default: 
    return "Events / GeV";
  }
  
}

std::string GetVariableUnfoldYaxisLabel(int vNum, bool isNorm=false){

  PRINT_VERBOSE("<GetVariableUnfoldYaxisLabel()> :: Retrieving Y axis label for variableId "+
		std::to_string(vNum)+" ... ");

  std::string prefix = ""         , suffix = "";
  if(isNorm){ prefix = "1/#sigma "; }
  
  switch(vNum){
  case Variable::y4l   :
  case Variable::cts   :
  case Variable::ct1   :
  case Variable::ct2   :
  case Variable::etajj :
  case Variable::njet  :
  case Variable::njetv2:
  case Variable::njetv3:
  case Variable::njetv4:
  case Variable::nbjet :
  case Variable::m12m34:
    if(!isNorm) suffix = " [fb]";
    break;
  case Variable::phi   :
  case Variable::phi1  :
  case Variable::phijj :
    if(isNorm) suffix = " [1/rad]";
    else       suffix = " [fb/rad]";
    break;
  default: 
    if(isNorm) suffix = " [1/GeV]";
    else       suffix = " [fb/GeV]";
  }
  
  switch(vNum){
  case Variable::pt4l   : return prefix + "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}"                                         + suffix;
  case Variable::pt0j   : return prefix + "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=0}"                 + suffix;
  case Variable::pt1j   : return prefix + "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=1}"                 + suffix;
  case Variable::pt2j   : return prefix + "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}=2}"                 + suffix;
  case Variable::pt3j   : return prefix + "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}#geq3}"              + suffix;
  case Variable::pt0y   : return prefix + "d#sigma/#font[12]{p}_{T,4#font[12]{l}}^{|#font[12]{y}_{4#font[12]{l}}|<0.5}"     + suffix;
  case Variable::pt1y   : return prefix + "d#sigma/#font[12]{p}_{T,4#font[12]{l}}^{0.5<|#font[12]{y}_{4#font[12]{l}}|<1.0}" + suffix;
  case Variable::pt2y   : return prefix + "d#sigma/#font[12]{p}_{T,4#font[12]{l}}^{1.0<|#font[12]{y}_{4#font[12]{l}}|<1.5}" + suffix;
  case Variable::pt3y   : return prefix + "d#sigma/#font[12]{p}_{T,4#font[12]{l}}^{1.5<|#font[12]{y}_{4#font[12]{l}}|<2.5}" + suffix;
  case Variable::m12    : return prefix + "d#sigma/d#font[12]{m}_{12}"                                                      + suffix;
  case Variable::m34    : return prefix + "d#sigma/d#font[12]{m}_{34}"                                                      + suffix;
  case Variable::m12m34 : return prefix + "#sigma"                                                                          + suffix;
  case Variable::y4l    : return prefix + "d#sigma/d|#font[12]{y}_{4#font[12]{l}}|"                                         + suffix;
  case Variable::njet   : return prefix + "#sigma"                                                                          + suffix;
  case Variable::njetv2 : return prefix + "#sigma"                                                                          + suffix;
  case Variable::njetv3 : return prefix + "#sigma"                                                                          + suffix;
  case Variable::njetv4 : return prefix + "#sigma"                                                                          + suffix;
  case Variable::nbjet  : return prefix + "d#sigma/d#font[12]{N}_{b-jets}"                                                  + suffix;
  case Variable::cts    : return prefix + "d#sigma/d(|cos#theta*|)"                                                         + suffix;
  case Variable::ljpt   : return prefix + "d#sigma/d#font[12]{p}_{T}^{lead. jet}"                                           + suffix;
  case Variable::sjpt   : return prefix + "d#sigma/d#font[12]{p}_{T}^{sub. lead. jet}"                                      + suffix;
  case Variable::mjj    : return prefix + "d#sigma/d#font[12]{m}_{jj}"                                                      + suffix;
  case Variable::etajj  : return prefix + "d#sigma/d(#Delta#eta_{jj})"                                                      + suffix;
  case Variable::phijj  : return prefix + "d#sigma/d(#Delta#phi_{jj})"                                                      + suffix;
  case Variable::ptnjet : return prefix + "d#sigma/d#font[12]{p}_{T,4#font[12]{l}}^{#font[12]{N}_{jets}}"                   + suffix;
  case Variable::pty4l  : return prefix + "d#sigma/#font[12]{p}_{T,4#font[12]{l}}^{|#font[12]{y}_{4#font[12]{l}}|}"         + suffix;
  case Variable::ct1    : return prefix + "d#sigma/d(cos#theta_{1})"                                                        + suffix;
  case Variable::ct2    : return prefix + "d#sigma/d(cos#theta_{2})"                                                        + suffix;
  case Variable::phi    : return prefix + "d#sigma/d(#phi)"                                                                 + suffix;
  case Variable::phi1   : return prefix + "d#sigma/d(#phi_{1})"                                                             + suffix;
  default: 
    return "dummy label";
  }
  
}

std::string GetProcessName(int p){

  PRINT_VERBOSE("<GetProcessName()> :: Retrieving name for processID = "+
		std::to_string(p)+" ... ");

  switch(p){
  case Process::Signal    : return "AllSig"    ;
  case Process::ggH       : return "ggH"       ;
  case Process::ggHbbH    : return "ggHbbH"    ;
  case Process::VBF       : return "VBF"       ;
  case Process::WH        : return "WH"        ;
  case Process::ZH        : return "ZH"        ;
  case Process::VH        : return "VH"        ;
  case Process::ttH       : return "ttH"       ;
  case Process::bbH       : return "bbH"       ;
  case Process::ggZZ      : return "ggZZ"      ;
  case Process::qqZZ      : return "qqZZ"      ;
  case Process::AllZZ     : return "AllZZ"     ;
  case Process::ZZEW      : return "ZZEW"      ;
  case Process::MultiBoson: return "MultiBoson";
  case Process::Zjets     : return "Zjets"     ;
  case Process::data      : return "data"      ;
  case Process::MG5       : return "MG5"       ;
  case Process::MG5KHvv   : return "MG5KHvv"   ;
  case Process::MG5KAgg   : return "MG5KAgg"   ;
  case Process::MG5KAvv   : return "MG5KAvv"   ;
  case Process::redBkg    : return "redBkg"    ;
  case Process::tHqb      : return "tHqb"      ;
  case Process::tWH       : return "tWH"       ;
  case Process::tH        : return "tH"        ;
  default:
    PRINT_FATAL("                                  Process "+std::to_string(p)+
		  " not defined -> exiting ... ");
    exit(0);
  }
  
}

int GetProcessNumber(std::string Process){

  PRINT_VERBOSE("<GetProcessNumber()>:: retrieving process enum ... ");

  if(Process=="ggH")             return Process::ggH       ;
  else if(Process=="VBF")        return Process::VBF       ;
  else if(Process=="WH")         return Process::WH        ;
  else if(Process=="ZH")         return Process::ZH        ;
  else if(Process=="ttH")        return Process::ttH       ;
  else if(Process=="bbH")        return Process::bbH       ;
  else if(Process=="ggHbbH")     return Process::ggHbbH    ;
  else if(Process=="VH")         return Process::VH        ;
  else if(Process=="AllSig")     return Process::Signal    ;
  else if(Process=="qqZZ")       return Process::qqZZ      ;
  else if(Process=="ggZZ")       return Process::ggZZ      ;
  else if(Process=="AllZZ")      return Process::AllZZ     ;
  else if(Process=="ZZEW")       return Process::ZZEW      ;
  else if(Process=="MultiBoson") return Process::MultiBoson;
  else if(Process=="Zjets")      return Process::Zjets     ;
  else if(Process=="data")       return Process::data      ;
  else if(Process=="MG5")        return Process::MG5       ;
  else if(Process=="MG5KHvv")    return Process::MG5KHvv   ;
  else if(Process=="MG5KAgg")    return Process::MG5KAgg   ;
  else if(Process=="MG5KAvv")    return Process::MG5KAvv   ;
  else if(Process=="redBkg")     return Process::redBkg    ;
  else if(Process=="tHqb")       return Process::tHqb      ;
  else if(Process=="tWH")        return Process::tWH       ;
  else if(Process=="tH")         return Process::tH        ;
  else{
    PRINT_FATAL("                                  Process "+Process+
		" not defined -> exiting ... ");
    exit(0);
  }
  
}

std::string GetChannelName(int ch){

  PRINT_VERBOSE("<GetChannelName()> :: Retrieving name for channelID = "+
		std::to_string(ch)+" ... ");

  switch(ch){
  case Channel::_incl : return "incl" ;
  case Channel::_4mu  : return "4mu"  ;
  case Channel::_4e   : return "4e"   ;
  case Channel::_2e2mu: return "2e2mu";
  case Channel::_2mu2e: return "2mu2e";
  case Channel::_2l2l : return "2l2l" ;
  case Channel::_4l   : return "4l"   ;
  default             : return ""     ;
  }
  
}

int GetChannelID(std::string ch){

  PRINT_VERBOSE("<GetChannelId>:: retrieving enum for channel "+ch+" ... ");
  
  if(      ch=="incl"  ) return Channel::_incl ;
  else if( ch=="4mu"   ) return Channel::_4mu  ;
  else if( ch=="4e"    ) return Channel::_4e   ;
  else if( ch=="2mu2e" ) return Channel::_2mu2e;
  else if( ch=="2e2mu" ) return Channel::_2e2mu;
  else if( ch=="2l2l"  ) return Channel::_2l2l ;
  else if( ch=="4l"    ) return Channel::_4l   ;
  else {
    PRINT_FATAL("<GetChannelID()>:: channel "+ch+" not supported and/or wrong! "+
		"exiting ... ");
    exit(0);
  }
  
}

std::string GetMCreleaseName(int mc){

  PRINT_VERBOSE("<GetMCreleaseName()> :: Retrieving name for mc release = "+
		std::to_string(mc)+" ... ");

  switch(mc){
  case MCtype::All   : return "mc16" ;
  case MCtype::mc15c : return "mc15c";
  case MCtype::mc16a : return "mc16a";
  case MCtype::mc16d : return "mc16d";
  case MCtype::mc16e : return "mc16e";
  default:
    PRINT_FATAL("                                  mc release "+std::to_string(mc)+
		" not defined -> exiting ... ");
    exit(0);
  }
  
}

bool UseMassInBins(int vNum){

  bool m_val = true;
  if( vNum==Variable::m4l ) m_val = false;
  return m_val;
  
}

std::vector<std::vector<int> > FillZZBin (int vNum) { //for now a hack for njet and pt4l

	std::vector<std::vector<int> > ZZbins;
	std::vector<int> tmp = GetVarBinRange(vNum);
	tmp.insert(tmp.begin(), 0);
	tmp[tmp.size()-1] = tmp[tmp.size()-1]-1;

	for (unsigned int i = 1; i < tmp.size(); i++) {

		//std::cout << "i = " << i << std::endl;

		std::vector<int> ZZcatbin;
		for (int j = tmp[i-1]; j < tmp[i]; j++) {
			ZZcatbin.push_back(j);
			//std::cout << "push back bin = " << j << std::endl; 
		}
		for (int j = tmp[i-1]; j < tmp[i]; j++) {
			ZZbins.push_back(ZZcatbin);
			//std::cout << "push back bin vector" << std::endl; 
		}
	}

	return ZZbins;
	
}
