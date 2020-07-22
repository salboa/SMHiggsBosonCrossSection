#include "CreateInputs.h"

void CreateInputs::DefineHistograms(int systNum){

  PRINT_DEBUG("<CreateInputs::DefineHistograms()>:: ",
	      "defining needed histograms ... ");

  if(m_isCouplings)      DefineCouplingsHistoSet();
  else if(m_doACRfactor) DefineACRHistoSet();
  else                   DefineXsecHistoSet(systNum);

}

void CreateInputs::DefineCouplingsHistoSet(){

  PRINT_DEBUG("<CreateInputs::DefineCouplingsHistoSet()>:: ",
	      "defining histograms for coupling analysis ... ");

  std::string HistName = "";
  
  /* BDTZZ0j */
  HistName = "hBDTZZ0j_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDTZZ0j_Bn, BDTZZ0j_Rg);
  h1d->GetXaxis()->SetTitle( "BDTZZ0j" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["BDTZZ0j"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "hBDTZZ0j_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDTZZ0j_Bn, BDTZZ0j_Rg);
    h1d->GetXaxis()->SetTitle( "BDTZZ0j" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["BDTZZ0j"][m_Ctgs.at(i).first].push_back( h1d );
  }

  /* BDT1jpT60 */
  HistName = "BDT1jpT60_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDT1jpT60_Bn, BDT1jpT60_Rg);
  h1d->GetXaxis()->SetTitle( "BDT1jpT60" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["BDT1jpT60"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "BDT1jpT60_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDT1jpT60_Bn, BDT1jpT60_Rg);
    h1d->GetXaxis()->SetTitle( "BDT1jpT60" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["BDT1jpT60"][m_Ctgs.at(i).first].push_back( h1d );
  }

  /* BDT1jpT60_120 */
  HistName = "BDT1jpT60_120_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDT1jpT60_120_Bn, BDT1jpT60_120_Rg);
  h1d->GetXaxis()->SetTitle( "BDT1jpT60_120" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["BDT1jpT60_120"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "BDT1jpT60_120_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDT1jpT60_120_Bn, BDT1jpT60_120_Rg);
    h1d->GetXaxis()->SetTitle( "BDT1jpT60_120" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["BDT1jpT60_120"][m_Ctgs.at(i).first].push_back( h1d );
  }

  /* BDT1jHpT */
  HistName = "BDT1jHpT_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDT1jHpT_Bn, BDT1jHpT_Rg);
  h1d->GetXaxis()->SetTitle( "BDT1jHpT" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["BDT1jHpT"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "BDT1jHpT_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDT1jHpT_Bn, BDT1jHpT_Rg);
    h1d->GetXaxis()->SetTitle( "BDT1jHpT" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["BDT1jHpT"][m_Ctgs.at(i).first].push_back( h1d );
  }
  
  /* BDTVHHad2j */
  HistName = "BDTVHHad2j_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDTVHHad2j_Bn, BDTVHHad2j_Rg);
  h1d->GetXaxis()->SetTitle( "BDTVHHad2j" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["BDTVHHad2j"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "BDTVHHad2j_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDTVHHad2j_Bn, BDTVHHad2j_Rg);
    h1d->GetXaxis()->SetTitle( "BDTVHHad2j" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["BDTVHHad2j"][m_Ctgs.at(i).first].push_back( h1d );
  }
  
  /* BDTVBF2j */
  HistName = "BDTVBF2j_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDTVBF2j_Bn, BDTVBF2j_Rg);
  h1d->GetXaxis()->SetTitle( "BDTVBF2j" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["BDTVBF2j"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "BDTVBF2j_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), BDTVBF2j_Bn, BDTVBF2j_Rg);
    h1d->GetXaxis()->SetTitle( "BDTVBF2j" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["BDTVBF2j"][m_Ctgs.at(i).first].push_back( h1d );
  }
  
  /* NGE200VBF */
  HistName = "NGE200VBF_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), NGE200VBF_Bn, NGE200VBF_Rg);
  h1d->GetXaxis()->SetTitle( "NGE200VBF" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["NGE200VBF"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "NGE200VBF_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), NGE200VBF_Bn, NGE200VBF_Rg);
    h1d->GetXaxis()->SetTitle( "NGE200VBF" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["NGE200VBF"][m_Ctgs.at(i).first].push_back( h1d );
  }
  
  /* NttH */ 
  HistName = "NttH_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), NttH_Bn, NttH_Rg);
  h1d->GetXaxis()->SetTitle( "NttH" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["NttH"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "NttH_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), NttH_Bn, NttH_Rg);
    h1d->GetXaxis()->SetTitle( "NttH" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["NttH"][m_Ctgs.at(i).first].push_back( h1d );
  }
  
  /* m4l */
  HistName = "hm4l_Cat_all_"+m_ProcStr;
  h1d = new TH1D( HistName.c_str(), HistName.c_str(), m_Nbins, m_Min, m_Max );
  h1d->GetXaxis()->SetTitle( "m_{4l} [GeV]" );
  h1d->GetYaxis()->SetTitle( "Events" );
  m_HmapBins["m4l"][Cats::all].push_back( h1d );
  for(uint i=0; i<m_Ctgs.size(); i++){
    HistName = "hm4l_Cat_"+m_Ctgs.at(i).second+"_"+m_ProcStr;
    h1d = new TH1D( HistName.c_str(), HistName.c_str(), m_Nbins, m_Min, m_Max );
    h1d->GetXaxis()->SetTitle( "m_{4l} [GeV]" );
    h1d->GetYaxis()->SetTitle( "Events" );
    m_HmapBins["m4l"][m_Ctgs.at(i).first].push_back( h1d );
  }

}

void CreateInputs::DefineACRHistoSet(){

  PRINT_DEBUG("<CreateInputs::DefineACRHistoSet()>:: ",
	      "defining histograms for ACR calculation ... ");

  if(m_useMatrix){
    DefineMatrixHistos("Mtx_Born",m_HmtxBornMap);
    DefineMatrixHistos("MigMtx_Born",m_HmtxMigBornMap);
    DefineMatrixHistos("Mtx_Dres",m_HmtxDresMap);
    DefineMatrixHistos("MigMtx_Dres",m_HmtxMigDresMap);
  }
  else{
    DefineACRHistos("cF_Born",m_HcFBornMap);
    DefineACRHistos("cF_Dres",m_HcFDresMap);
  }
  DefineACRHistos("fNonFid_Abs_Born",m_HfNFabsBornMap);
  DefineACRHistos("fNonFid_Abs_Dres",m_HfNFabsDresMap);
  DefineACRHistos("fNonFid_Rel_Born",m_HfNFrelBornMap);
  DefineACRHistos("fNonFid_Rel_Dres",m_HfNFrelDresMap);
  DefineACRHistos("aF_Born",m_HaFBornMap);
  DefineACRHistos("aF_Dres",m_HaFDresMap);
  DefineACRHistos("rF",m_HrFmap);
  
}

void CreateInputs::DefineACRHistos(std::string fact, std::map< std::string,std::vector<TH1D*> > & hmap ){

  PRINT_DEBUG("<CreateInputs::DefineACRHistos()>:: defining histograms for "+fact+" ...");

  std::string HistName = "";
  std::string type="";
  if(fact.find("cF")!=std::string::npos)           type = "Correction Factor";
  else if(fact.find("aF")!=std::string::npos)      type = "Acceptance";
  else if(fact.find("fNonFid")!=std::string::npos) type = "Not Fiducial Factor";
  else                                             type = "R Factor";

  for(uint v=0; v<m_diffVars.size(); v++){

    int vNum  = GetVariableID( m_diffVars[v] );
    int nbins = GetNumberOfBins( vNum );
    std::string varNick = "";
    if(vNum==Variable::m4l) varNick = "fid";
    else                    varNick = GetVariableName( vNum );
    
    for(auto& x: m_ChMap){

      int ch = x.first;
      HistName = fact+"_"+varNick+"_"+m_ChMap[ch]+"_"+m_ProcStr;
      h1d = new TH1D( HistName.c_str(), HistName.c_str(), nbins, 0, nbins );
      h1d->GetXaxis()->SetTitle( m_diffVars[v].c_str() );
      h1d->GetYaxis()->SetTitle( type.c_str() );
      hmap[m_diffVars[v]].push_back( h1d );
      
    }
    
  }
  
}

void CreateInputs::DefineMatrixHistos(std::string fact, std::map< std::string,std::vector<TH2D*> > &hmap){

  PRINT_DEBUG("<CreateInputs::DefineMatrixHistos()>:: defining histograms for "+fact+" ...");

  std::string HistName = "";
  
  for(uint v=0; v<m_diffVars.size(); v++){

    int vNum  = GetVariableID( m_diffVars[v] );
    int nbins = GetNumberOfBins(vNum);
    std::string varNick = "";
    if(vNum==Variable::m4l) varNick = "fid";
    else                    varNick = GetVariableName( vNum );
    
    for(auto& x: m_ChMap){

      int ch = x.first;
      HistName = fact+"_"+varNick+"_"+m_ChMap[ch]+"_"+m_ProcStr;
      h2d = new TH2D( HistName.c_str(), HistName.c_str(), nbins, 0, nbins, nbins, 0 , nbins);
      h2d->GetXaxis()->SetTitle( (m_diffVars[v]+"^{reco}").c_str() );
      h2d->GetYaxis()->SetTitle( (m_diffVars[v]+"^{truth}").c_str() );
      hmap[m_diffVars[v]].push_back( h2d );
      
    }
    
  }
  
}

void CreateInputs::DefineXsecHistoSet(int systNum){

  PRINT_DEBUG("<CreateInputs::DefineXsecHistoSet()>:: ",
	      "defining histograms for xsec analysis ... ");

  std::string HistName = "";
  if(m_addFineM4l){
    m_NbinsFine = 33;
    m_m4lRange[0] = m_Min;
    for(int i=0; i<31; i++){ m_m4lRange[i+1]=115.0+i*0.5; }
    m_m4lRange[32] = 135.0;
    m_m4lRange[33] = m_Max;
  }

  for(uint v=0; v<m_diffVars.size(); v++){

    int vNum  = GetVariableID( m_diffVars[v] );
    int nbins = GetNumberOfBins(vNum);
    std::string varNick = "";
    if(vNum==Variable::m4l) varNick = "m";
    else                    varNick = GetVariableName( vNum );
  
    for(auto& x: m_ChMap){

      int ch = x.first;
       HistName = "h"+varNick+"_"+m_ChMap[ch]+"_"+m_ProcStr;
       Create1DHistogram(h1d, HistName, vNum, !m_addFineM4l);
       h1d->GetXaxis()->SetTitle( (m_diffVars[v]+" ["+m_LbMap[ch]+"]").c_str() );
       h1d->GetYaxis()->SetTitle( "Events" );
       m_Hmap[m_diffVars[v]].push_back( h1d );
       if(m_addFineM4l){
	 HistName = "h"+varNick+"Fine_"+m_ChMap[ch]+"_"+m_ProcStr;
	 Create1DHistogram(h1d, HistName, vNum, m_addFineM4l);
	 h1d->GetXaxis()->SetTitle( (m_diffVars[v]+" ["+m_LbMap[ch]+"]").c_str() );
	 h1d->GetYaxis()->SetTitle( "Events" );
	 m_Hmap[m_diffVars[v]+"_Ext"].push_back( h1d );
       }

       if(vNum==Variable::m12m34 && !m_doSystematics){
	 HistName = "hm12vsm34_"+m_ChMap[ch]+"_"+m_ProcStr;
	 if(m_Process==Process::Signal)
	   h2d = new TH2D( HistName.c_str(), HistName.c_str(), 40,45.,110., 37,7.,68.);
	 else
	   h2d = new TH2D( HistName.c_str(), HistName.c_str(), 80,45.,110., 74,7.,68.);
	 h2d->GetXaxis()->SetTitle( ("m_{12}^{"+m_LbMap[ch]+"} [GeV]").c_str() );
	 h2d->GetYaxis()->SetTitle( ("m_{34}^{"+m_LbMap[ch]+"} [GeV]").c_str() );
	 m_Hmap2D["m12m34"].push_back( h2d );
       }

       if( UseMassInBins(vNum) && (!m_doSystematics || UseSysMassInBins(systNum)) ){
	 for(int i=0; i<nbins; i++){
	   HistName = "hm_"+varNick+"bin"+std::to_string(i)+"_"+m_ChMap[ch]+"_"+m_ProcStr;
	   Create1DHistogram(h1d, HistName, Variable::m4l, !m_addFineM4l);
	   h1d->GetXaxis()->SetTitle( ("m_{"+m_LbMap[ch]+"} [GeV]").c_str() );
	   h1d->GetYaxis()->SetTitle( "Events" );
	   m_HmapBins[m_diffVars[v]][i].push_back( h1d );

	   if(m_addFineM4l){
	     HistName = "hmFine_"+varNick+"bin"+std::to_string(i)+"_"+m_ChMap[ch]+"_"+m_ProcStr;
	     Create1DHistogram(h1d, HistName, Variable::m4l, m_addFineM4l);
	     h1d->GetXaxis()->SetTitle( ("m_{"+m_LbMap[ch]+"} [GeV]").c_str() );
	     h1d->GetYaxis()->SetTitle( "Events" );
	     m_HmapBinsFine[m_diffVars[v]][i].push_back(h1d);
	   }
	 }
       }
       
    }
    
  }
  
}

void CreateInputs::Create1DHistogram(TH1D* &h1d, std::string Hname, int vNum, bool isFine){

  PRINT_VERBOSE("<CreateInputs::Create1DHistogram> :: creating histogram for variable ID = "+
		std::to_string(vNum)+" ... ");
  
  switch(vNum){
  case Variable::m4l   :
    if(isFine)
      h1d = new TH1D( Hname.c_str(), Hname.c_str(), m_Nbins, m_Min, m_Max );
    else
      h1d = new TH1D( Hname.c_str(), Hname.c_str(), m_NbinsFine, m_m4lRange );
    break;
  case Variable::pt4l  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), PtBins,     PtRange);      break;
  case Variable::pt0j  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Pt0jBins,   Pt0jRange);    break;
  case Variable::pt1j  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Pt1jBins,   Pt1jRange);    break;
  case Variable::pt2j  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Pt2jBins,   Pt2jRange);    break;
  case Variable::pt3j  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Pt3jBins,   Pt3jRange);    break;
  case Variable::pt0y  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Pt0yBins,   Pt0yRange);    break;
  case Variable::pt1y  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Pt1yBins,   Pt1yRange);    break;
  case Variable::pt2y  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Pt2yBins,   Pt2yRange);    break;
  case Variable::pt3y  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Pt3yBins,   Pt3yRange);    break;
  case Variable::m12   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), M12Bins,    M12Range);     break;
  case Variable::m34   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), M34Bins,    M34Range);     break;
  case Variable::m12m34:
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), m12m34Bins, m12m34Range);  break;
  case Variable::y4l   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), RapBins,    RapRange);     break;
  case Variable::njet  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), NjetBins,   NjetRange );   break;
  case Variable::njetv2:
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), NjetBinsv2, NjetRangev2 ); break;
  case Variable::njetv3:
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), NjetBinsv3, NjetRangev3 ); break;
  case Variable::njetv4:
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), NjetBinsv4, NjetRangev4 ); break;
  case Variable::nbjet :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), NbjetBins,  NbjetRange );  break;
  case Variable::cts   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), CtsBins,    CtsRange );    break;
  case Variable::ct1   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Ct1Bins,    Ct1Range );    break;
  case Variable::ct2   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Ct2Bins,    Ct2Range );    break; 
  case Variable::phi   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), PhiBins,    PhiRange );    break;
  case Variable::phi1   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), Phi1Bins,   Phi1Range );   break; 
  case Variable::ljpt  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), LjPtBins,   LjPtRange );   break;
  case Variable::sjpt  :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), SjPtBins,   SjPtRange );   break;
  case Variable::mjj   :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), MjjBins,    MjjRange );    break;
  case Variable::etajj :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), EtajjBins,  EtajjRange );  break;
  case Variable::phijj :
    h1d = new TH1D( Hname.c_str(), Hname.c_str(), PhijjBins,  PhijjRange );  break;
  case Variable::ptnjet:
    h1d = new TH1D (Hname.c_str(), Hname.c_str(), PtNjetBins, PtNjetRange);  break;
  case Variable::pty4l:
    h1d = new TH1D (Hname.c_str(), Hname.c_str(), PtRapBins,  PtRapRange);   break;
  default: 
    PRINT_WARNING("                                  VariableId "+std::to_string(vNum)+
		  " not found ... exiting ");
    exit(0);
  }
  
}

std::vector<TObject*> CreateInputs::ListOfPlotsToWrite(){

  PRINT_DEBUG("<CreateInputs::ListOfPlotsToWrite()>:: ",
	      "making the list of histograms to write on file ... ");

  std::vector<TObject*> list;
  for(auto& x: m_ChMap){
    int ch = x.first;
    
    for(auto& y: m_Hmap){
      std::string name = y.first;
      list.push_back( m_Hmap[name].at(ch) );
    }
    
    for(auto& y: m_HaFBornMap){
      std::string name = y.first;
      list.push_back( m_HaFBornMap[name].at(ch) );
      list.push_back( m_HaFDresMap[name].at(ch) );
      list.push_back( m_HrFmap[name].at(ch) );
    }
    
    if(m_useMatrix){
      for(auto& y: m_HmtxBornMap) {   
        std::string name = y.first;
	list.push_back( m_HmtxBornMap[name].at(ch)    );
        list.push_back( m_HmtxDresMap[name].at(ch)    );
	list.push_back( m_HmtxMigBornMap[name].at(ch) );
	list.push_back( m_HmtxMigDresMap[name].at(ch) );
      }
    }
    else{
      for(auto& y: m_HcFBornMap){
	std::string name = y.first;
	list.push_back( m_HcFBornMap[name].at(ch) );
	list.push_back( m_HcFDresMap[name].at(ch) );
      }
    }

    for(auto& y: m_HfNFabsBornMap){
      std::string name = y.first;
      list.push_back( m_HfNFabsBornMap[name].at(ch) );
      list.push_back( m_HfNFabsDresMap[name].at(ch) );
      list.push_back( m_HfNFrelBornMap[name].at(ch) );
      list.push_back( m_HfNFrelDresMap[name].at(ch) );
    }
    
    if(!m_isCouplings){
      for(auto& z: m_HmapBins){
	std::string name = z.first;
	int bins = (int)z.second.size();
	for(int b=0; b<bins; b++){
	  list.push_back( m_HmapBins[name][b].at(ch)     );
	}
      }
      for(auto& z: m_HmapBinsFine){
	std::string name = z.first;
	int bins = (int)z.second.size();
	for(int b=0; b<bins; b++){
	  list.push_back( m_HmapBinsFine[name][b].at(ch) );
	}
      }
    }
    
    for(auto& y: m_Hmap2D){
      std::string name = y.first;
      list.push_back( m_Hmap2D[name].at(ch) );
    }

  }

  if(m_isCouplings){
    for(auto& z: m_HmapBins){
      std::string name = z.first;
      list.push_back( m_HmapBins[name][Cats::all].at(0) );
      for(uint b=0; b<m_Ctgs.size(); b++){
	list.push_back( m_HmapBins[name][m_Ctgs.at(b).first].at(0) );
      }
    }
    
  }
  return list;
  
}

std::vector<TH1D*> CreateInputs::ListOf1DPlotsToNorm(){

  PRINT_DEBUG("<CreateInputs::ListOf1DPlotsToNorm()>:: "
	      "making the list of 1D histograms to normalize ... ");

  std::vector<TH1D*> list;
  for(uint v=0; v<m_diffVars.size(); v++){

    if(m_diffVars[v]=="m4l") continue;

    for(auto& x: m_ChMap){
      int ch = x.first;
      list.push_back( m_Hmap[m_diffVars[v]].at(ch) );
    }
    
  }
  return list;
  
}

std::vector<TH2D*> CreateInputs::ListOf2DPlotsToNorm(){

  PRINT_DEBUG("<CreateInputs::ListOf2DPlotsToNorm()>:: ",
	      "making the list of 2D histograms to normalize ... ");

  std::vector<TH2D*> list;
  for(auto& x: m_ChMap){
    int ch = x.first;

    for(auto& y: m_Hmap2D){
      std::string name = y.first;
      list.push_back( m_Hmap2D[name].at(ch) );
    }
    
  }
  return list;
  
}

void CreateInputs::DivideForBinSize(std::vector<TH1D*> &plots){
  
  PRINT_DEBUG("<CreateInputs::DivideForBinSize()>:: ",
	      "dividing 1D histograms for the bin size ... ");

  bool divBinW = false;
  std::vector<double> wid;
  wid.push_back(   1.0);
  wid.push_back( 120.0);
  wid.push_back( 330.0);
  wid.push_back(2550.0);

  for(uint k=0; k<plots.size(); k++){

    divBinW = false;
    TString name = plots[k]->GetName();
    if( name.Contains("hmjj") ){
      divBinW = true;
    }
    
    for( Int_t i=0; i<plots[k]->GetNbinsX(); i++){
      
      if(divBinW){
	plots[k]->SetBinContent( i+1, plots[k]->GetBinContent(i+1) / wid[i] );
	plots[k]->SetBinError(   i+1, plots[k]->GetBinError(i+1)   / wid[i] );
      }
      else{
	plots[k]->SetBinContent( i+1, plots[k]->GetBinContent(i+1)/
				 plots[k]->GetBinWidth(i+1) );
	plots[k]->SetBinError( i+1, plots[k]->GetBinError(i+1)/
			       plots[k]->GetBinWidth(i+1) );
      }
      
    }
    
  }
  
}

void CreateInputs::DivideForBinSize(std::vector<TH2D*> &plots){

  PRINT_DEBUG("<CreateInputs::DivideForBinSize()>:: ",
	      "dividing 2D histograms for the bin size ... ");

  double binW = 1.0;
  for(uint k=0; k<plots.size(); k++){
    
    for( Int_t i=0; i<plots[k]->GetNbinsX(); i++){

      for( Int_t j=0; j<plots[k]->GetNbinsY(); j++){
	
	binW = plots[k]->GetXaxis()->GetBinWidth(i+1)*plots[k]->GetYaxis()->GetBinWidth(j+1);
	plots[k]->SetBinContent( i+1, j+1, plots[k]->GetBinContent(i+1,j+1)/binW );
	plots[k]->SetBinError( i+1, j+1, plots[k]->GetBinError(i+1,j+1)/binW );
	
      }
      
    }
    
  }
  
}

void CreateInputs::MergeAndNormalizeZjetsPlots(std::string var, bool normalize){

  PRINT_DEBUG("<CreateInputs::MergeAndNormalizeZjetsPlots()>:: merging and normalising Z+jets histograms for var "+
	      var+" ... ");
  
  for(int i=0; i<m_Hmap[var].at(Channel::_incl)->GetNbinsX(); i++){

    double cIncl = ( m_Hmap[var].at(Channel::_4mu)  ->GetBinContent(i+1)+
		     m_Hmap[var].at(Channel::_4e)   ->GetBinContent(i+1)+
		     m_Hmap[var].at(Channel::_2mu2e)->GetBinContent(i+1)+
		     m_Hmap[var].at(Channel::_2e2mu)->GetBinContent(i+1) );
    double c4l   = ( m_Hmap[var].at(Channel::_4mu)  ->GetBinContent(i+1)+
		     m_Hmap[var].at(Channel::_4e)   ->GetBinContent(i+1) );
    double c2l2l = ( m_Hmap[var].at(Channel::_2mu2e)->GetBinContent(i+1)+
		     m_Hmap[var].at(Channel::_2e2mu)->GetBinContent(i+1) );

    m_Hmap[var].at(Channel::_incl)->SetBinContent( i+1, cIncl );
    m_Hmap[var].at(Channel::_4l)  ->SetBinContent( i+1, c4l   );
    m_Hmap[var].at(Channel::_2l2l)->SetBinContent( i+1, c2l2l );
    
  }
  if(normalize){
    m_Hmap[var].at(Channel::_incl)->Scale( m_zjetYields.at(Channel::_incl) /
  					   m_Hmap[var].at(Channel::_incl)->Integral() );
    m_Hmap[var].at(Channel::_4l)  ->Scale( m_zjetYields.at(Channel::_4l)   /
  					   m_Hmap[var].at(Channel::_4l)->Integral() );
    m_Hmap[var].at(Channel::_2l2l)->Scale( m_zjetYields.at(Channel::_2l2l) /
  					   m_Hmap[var].at(Channel::_2l2l)->Integral() );
  }
  
  PRINT_DEBUG("                                                Integral for channel incl  : "+
	      std::to_string( m_Hmap[var].at(Channel::_incl)->Integral()  ) );
  PRINT_DEBUG("                                                Integral for channel 4mu   : "+
	      std::to_string( m_Hmap[var].at(Channel::_4mu)->Integral()   ) );
  PRINT_DEBUG("                                                Integral for channel 4e    : "+
	      std::to_string( m_Hmap[var].at(Channel::_4e)->Integral()    ) );
  PRINT_DEBUG("                                                Integral for channel 2mu2e : "+
	      std::to_string( m_Hmap[var].at(Channel::_2mu2e)->Integral() ) );
  PRINT_DEBUG("                                                Integral for channel 2e2mu : "+
	      std::to_string( m_Hmap[var].at(Channel::_2e2mu)->Integral() ) );
  PRINT_DEBUG("                                                Integral for channel 4l    : "+
	      std::to_string( m_Hmap[var].at(Channel::_4l)->Integral()    ) );
  PRINT_DEBUG("                                                Integral for channel 2l2l  : "+
	      std::to_string( m_Hmap[var].at(Channel::_2l2l)->Integral()  ) );
  
}

void CreateInputs::FillZjetsPlots(std::string var){

  PRINT_VERBOSE("<CreateInputs::FillZjetPlots()>:: filling Z+jets histograms for var "+
		var+" ... ");

  if(var=="m4l"){
    Int_t Bin_mMin = m_llmumu->FindBin(m_Min);

    if(m_Min!=115 && m_Max!=130){
      
      Int_t Bin_m115 = m_llmumu->FindBin(115);
      Int_t Bin_m130 = m_llmumu->FindBin(130);
      Int_t Bin_m135 = m_llmumu->FindBin(135);
      Int_t Bin_mMax = m_llmumu->FindBin(m_Max);
      /* left sideband */
      double llmmCont = 0, lleeCont = 0;
      for(int i=0; i<(Bin_m115-Bin_mMin); i++){
	llmmCont += m_llmumu->GetBinContent(i+Bin_mMin);
	lleeCont += m_llee->GetBinContent(i+Bin_mMin);
      }
      m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 1,llmmCont );
      m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 1,lleeCont );
      m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 1,lleeCont );
      m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 1,llmmCont );

      /* signal region */
      for(int i=0; i<Bin_m130-Bin_m115; i++){
	m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( i+2,m_llmumu->GetBinContent(i+Bin_m115) );
	m_Hmap[var].at(Channel::_4e)   ->SetBinContent( i+2,m_llee->GetBinContent(i+Bin_m115)   );
	m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( i+2,m_llee->GetBinContent(i+Bin_m115)   );
	m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( i+2,m_llmumu->GetBinContent(i+Bin_m115) );
      }

      /* right sideband */
      llmmCont = 0, lleeCont = 0;
      for(int i=0; i<Bin_m135-Bin_m130; i++){
	llmmCont += m_llmumu->GetBinContent(i+Bin_m130);
	lleeCont += m_llee->GetBinContent(i+Bin_m130);
      }
      m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 32,llmmCont );
      m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 32,lleeCont );
      m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 32,lleeCont );
      m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 32,llmmCont );

      llmmCont = 0, lleeCont = 0;
      for(int i=0; i<Bin_mMax-Bin_m135; i++){
	llmmCont += m_llmumu->GetBinContent(i+Bin_m135);
	lleeCont += m_llee->GetBinContent(i+Bin_m135);
      }
      m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 33,llmmCont );
      m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 33,lleeCont );
      m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 33,lleeCont );
      m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 33,llmmCont );
      
    }
    else{
      FillZjetsFineM4l(Bin_mMin,var);
    }
  }
  else if(var=="m4l_Ext"){
    m_llmumu = (TH1D*)m_In->Get( ("h_"+FindZjetVarName("m4l")+
				  "_2l2mu"+m_zjetNameSuffix).c_str() );
    
    m_llee   = (TH1D*)m_In->Get( ("h_"+FindZjetVarName("m4l")+
				  "_2l2e"+m_zjetNameSuffix).c_str() );
    
    Int_t Bin_mMin = m_llmumu->FindBin(m_Min);
    FillZjetsFineM4l(Bin_mMin,var);
  }
  else if(var=="njetv2"){
    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 1, m_llmumu->GetBinContent(1) );
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 1, m_llee->GetBinContent(1)   );
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 1, m_llee->GetBinContent(1)   );
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 1, m_llmumu->GetBinContent(1) );

    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 2, (m_llmumu->GetBinContent(2)+
							m_llmumu->GetBinContent(3)+
							m_llmumu->GetBinContent(4)+
							m_llmumu->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 2, (m_llee->GetBinContent(2)+
							m_llee->GetBinContent(3)+
							m_llee->GetBinContent(4)+
							m_llee->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 2, (m_llee->GetBinContent(2)+
							m_llee->GetBinContent(3)+
							m_llee->GetBinContent(4)+
							m_llee->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 2, (m_llmumu->GetBinContent(2)+
							m_llmumu->GetBinContent(3)+
							m_llmumu->GetBinContent(4)+
							m_llmumu->GetBinContent(5)) );
  }
  else if(var=="njetv3"){
    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 1, m_llmumu->GetBinContent(1) );
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 1, m_llee->GetBinContent(1)   );
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 1, m_llee->GetBinContent(1)   );
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 1, m_llmumu->GetBinContent(1) );

    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 2, m_llmumu->GetBinContent(2) );
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 2, m_llee->GetBinContent(2)   );
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 2, m_llee->GetBinContent(2)   );
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 2, m_llmumu->GetBinContent(2) );

    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 3, (m_llmumu->GetBinContent(3)+
							m_llmumu->GetBinContent(4)+
							m_llmumu->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 3, (m_llee->GetBinContent(3)+
							m_llee->GetBinContent(4)+
							m_llee->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 3, (m_llee->GetBinContent(3)+
							m_llee->GetBinContent(4)+
							m_llee->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 3, (m_llmumu->GetBinContent(3)+
							m_llmumu->GetBinContent(4)+
							m_llmumu->GetBinContent(5)) );
    
  }
  else if(var=="njet"){ //was njetv4
    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 1, m_llmumu->GetBinContent(1) );
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 1, m_llee->GetBinContent(1)   );
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 1, m_llee->GetBinContent(1)   );
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 1, m_llmumu->GetBinContent(1) );

    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 2, m_llmumu->GetBinContent(2) );
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 2, m_llee->GetBinContent(2)   );
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 2, m_llee->GetBinContent(2)   );
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 2, m_llmumu->GetBinContent(2) );

    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 3, m_llmumu->GetBinContent(3) );
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 3, m_llee->GetBinContent(3)   );
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 3, m_llee->GetBinContent(3)   );
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 3, m_llmumu->GetBinContent(3) );
    
    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( 4, (m_llmumu->GetBinContent(4)+
							m_llmumu->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( 4, (m_llee->GetBinContent(4)+
							m_llee->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( 4, (m_llee->GetBinContent(4)+
							m_llee->GetBinContent(5)) );
    
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( 4, (m_llmumu->GetBinContent(4)+
							m_llmumu->GetBinContent(5)) );
  }
  else{
    for(int b=0; b<m_llmumu->GetNbinsX(); b++){
      m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( b+1, m_llmumu->GetBinContent(b+1) );
      m_Hmap[var].at(Channel::_4e)   ->SetBinContent( b+1, m_llee->GetBinContent(b+1)   );
      m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( b+1, m_llee->GetBinContent(b+1)   );
      m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( b+1, m_llmumu->GetBinContent(b+1) );
    }
  }
  
  m_Hmap[var].at(Channel::_4mu)  ->Scale( m_zjetYields.at(Channel::_4mu)   /
  					  m_Hmap[var].at(Channel::_4mu)->Integral()   );
  m_Hmap[var].at(Channel::_4e)   ->Scale( m_zjetYields.at(Channel::_4e)    /
  					  m_Hmap[var].at(Channel::_4e)->Integral()    );
  m_Hmap[var].at(Channel::_2mu2e)->Scale( m_zjetYields.at(Channel::_2mu2e) /
  					  m_Hmap[var].at(Channel::_2mu2e)->Integral() );
  m_Hmap[var].at(Channel::_2e2mu)->Scale( m_zjetYields.at(Channel::_2e2mu) /
  					  m_Hmap[var].at(Channel::_2e2mu)->Integral() );

  m_llmumu->Delete();
  m_llee->Delete();
  
}

void CreateInputs::FillZjetsFineM4l(int InBin, std::string var){

  PRINT_VERBOSE("<CreateInputs::FillZjetsFineM4l()>:: filling fine Zjets m4l histogram ...");

  for(int i=0; i<m_Nbins; i++){
    m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( i+1,m_llmumu->GetBinContent(i+InBin) );
    m_Hmap[var].at(Channel::_4e)   ->SetBinContent( i+1,m_llee->GetBinContent(i+InBin)   );
    m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( i+1,m_llee->GetBinContent(i+InBin)   );
    m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( i+1,m_llmumu->GetBinContent(i+InBin) );
  }
  
}

void CreateInputs::Handle2DZjetsPlotsInfo(){

  PRINT_VERBOSE("<CreateInputs::HandleZjetPlotsInfo()>:: handling 2D vars Z+jets information");

  m_zjetNames[Variable::ptnjet].push_back( std::make_pair("pt0j",FindZjetVarName("pt0j")) );
  m_zjetNames[Variable::ptnjet].push_back( std::make_pair("pt1j",FindZjetVarName("pt1j")) );
  m_zjetNames[Variable::ptnjet].push_back( std::make_pair("pt2j",FindZjetVarName("pt2j")) );
  m_zjetNames[Variable::ptnjet].push_back( std::make_pair("pt3j",FindZjetVarName("pt3j")) );

  m_zjetNames[Variable::pty4l].push_back( std::make_pair("pt0y",FindZjetVarName("pt0y")) );
  m_zjetNames[Variable::pty4l].push_back( std::make_pair("pt1y",FindZjetVarName("pt1y")) );
  m_zjetNames[Variable::pty4l].push_back( std::make_pair("pt2y",FindZjetVarName("pt2y")) );
  m_zjetNames[Variable::pty4l].push_back( std::make_pair("pt3y",FindZjetVarName("pt3y")) );

  /* m4l stat/sys uncertainties */
  if(m_Min==105.0 && m_Max==160){
    m_zjetStat.push_back( 1.52 / 100. );  m_zjetSys.push_back(  7.19 / 100. ); //4mu
    m_zjetStat.push_back( 8.43 / 100. );  m_zjetSys.push_back( 13.0  / 100. ); //4e
    m_zjetStat.push_back( 5.97 / 100. );  m_zjetSys.push_back( 14.8  / 100. ); //2mu2e
    m_zjetStat.push_back( 1.52 / 100. );  m_zjetSys.push_back(  7.19 / 100. ); //2e2mu
  }
  else{
    m_zjetStat.push_back( 1.52 / 100. );  m_zjetSys.push_back(  7.19 / 100. ); //4mu
    m_zjetStat.push_back( 8.43 / 100. );  m_zjetSys.push_back( 13.0  / 100. ); //4e
    m_zjetStat.push_back( 5.97 / 100. );  m_zjetSys.push_back( 14.8  / 100. ); //2mu2e
    m_zjetStat.push_back( 1.52 / 100. );  m_zjetSys.push_back(  7.19 / 100. ); //2e2mu
  }
  
}

int CreateInputs::Get2DZjetsVarShift(int vNum, int pos){

  PRINT_VERBOSE("<CreateInputs::Get2DZjetVarShift()>:: getting 2D vars Z+jets shift");

  int m_shift = 0;
  if(m_zjetNames[vNum].at(pos).first=="pt1j" || m_zjetNames[vNum].at(pos).first=="pt1y"){
    m_shift = GetNumberOfBins(m_zjetNames[vNum].at(pos-1).first);
  }
  else if(m_zjetNames[vNum].at(pos).first=="pt2j" || m_zjetNames[vNum].at(pos).first=="pt2y"){
    m_shift = ( GetNumberOfBins(m_zjetNames[vNum].at(pos-2).first)+
		GetNumberOfBins(m_zjetNames[vNum].at(pos-1).first)  );
  }
  else if(m_zjetNames[vNum].at(pos).first=="pt3j" || m_zjetNames[vNum].at(pos).first=="pt3y"){
    m_shift = ( GetNumberOfBins(m_zjetNames[vNum].at(pos-3).first)+
		GetNumberOfBins(m_zjetNames[vNum].at(pos-2).first)+
		GetNumberOfBins(m_zjetNames[vNum].at(pos-1).first)   );
  }
  return m_shift;
  
}

void CreateInputs::Fill2DZjetsPlots(std::string var){

  PRINT_VERBOSE("<CreateInputs::Fill2DZjetPlots()>:: filling Z+jets histograms for var "+
		var+" ... ");

  int vNum = GetVariableID(var);
  for(uint n=0; n<m_zjetNames[vNum].size(); n++){

    m_llmumu = (TH1D*)m_In->Get( ("h_"+m_zjetNames[vNum].at(n).second+
				  "_2l2mu"+m_zjetNameSuffix).c_str() );
    
    m_llee   = (TH1D*)m_In->Get( ("h_"+m_zjetNames[vNum].at(n).second+
				  "_2l2e"+m_zjetNameSuffix).c_str()  );

    int init = Get2DZjetsVarShift(vNum,n);
    PRINT_VERBOSE( "                                        "+
		   m_zjetNames[vNum][n].second+" "+
		   std::to_string(m_llmumu->Integral())+" "+
		   std::to_string(m_llee->Integral()) );
		   
    for(int i=0; i<GetNumberOfBins(m_zjetNames[vNum].at(n).first); i++){
      m_Hmap[var].at(Channel::_4mu)  ->SetBinContent( init+i+1, m_llmumu->GetBinContent(i+1) );
      m_Hmap[var].at(Channel::_4e)   ->SetBinContent( init+i+1, m_llee->GetBinContent(i+1)   );
      m_Hmap[var].at(Channel::_2mu2e)->SetBinContent( init+i+1, m_llee->GetBinContent(i+1)   );
      m_Hmap[var].at(Channel::_2e2mu)->SetBinContent( init+i+1, m_llmumu->GetBinContent(i+1) );
    }
    
    m_llmumu->Delete();
    m_llee->Delete();
  }
  m_Hmap[var].at(Channel::_4mu)  ->Scale( m_zjetYields.at(Channel::_4mu)   /
					  m_Hmap[var].at(Channel::_4mu)->Integral()   );
  m_Hmap[var].at(Channel::_4e)   ->Scale( m_zjetYields.at(Channel::_4e)    /
					  m_Hmap[var].at(Channel::_4e)->Integral()    );
  m_Hmap[var].at(Channel::_2mu2e)->Scale( m_zjetYields.at(Channel::_2mu2e) /
					  m_Hmap[var].at(Channel::_2mu2e)->Integral() );
  m_Hmap[var].at(Channel::_2e2mu)->Scale( m_zjetYields.at(Channel::_2e2mu) /
					  m_Hmap[var].at(Channel::_2e2mu)->Integral() );
  
}

void CreateInputs::Normalize2DZjetsPlots(int vNum, std::string var){
  
  PRINT_VERBOSE("<CreateInputs::Normalize2DZjetPlots()>:: normalizing Z+jets histograms for var "+
		var+" ... ");

  int init  = 0;
  std::string _var = "";
  switch(vNum){
  case Variable::pt1j: init = Get2DZjetsVarShift(Variable::ptnjet,1); _var = "ptnjet"; break;
  case Variable::pt2j: init = Get2DZjetsVarShift(Variable::ptnjet,2); _var = "ptnjet"; break;
  case Variable::pt3j: init = Get2DZjetsVarShift(Variable::ptnjet,3); _var = "ptnjet"; break;
  case Variable::pt1y: init = Get2DZjetsVarShift(Variable::pty4l,1) ; _var = "pty4l" ; break;
  case Variable::pt2y: init = Get2DZjetsVarShift(Variable::pty4l,2) ; _var = "pty4l" ; break;
  case Variable::pt3y: init = Get2DZjetsVarShift(Variable::pty4l,3) ; _var = "pty4l" ; break;
  default:
    init = 0;
    if(vNum==Variable::pt0j) _var = "ptnjet";
    if(vNum==Variable::pt0y) _var = "pty4l" ;
  }
  std::vector<double> content{0,0,0,0,0,0,0};
  for(int i=0; i<GetNumberOfBins(vNum); i++){
    for(auto& x: m_ChMap){
      content[x.first] += m_Hmap[_var].at(x.first)->GetBinContent(init+i+1);
    }
  }
  for(auto& x: m_ChMap){
    m_Hmap[var].at(x.first)->Scale( content.at(x.first) /
				    m_Hmap[var].at(x.first)->Integral() );
  }
  
}
