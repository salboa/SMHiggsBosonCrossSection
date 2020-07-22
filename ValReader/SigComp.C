#include "SigComp.h"

int main( int argc, char* argv[] ){

  bool printHelp       = false;
  bool Fiducial        = false;
  bool debug           = false;
  bool write           = false;
  std::string variable = "";
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--Fiducial")      ){ Fiducial  = true;      }
    else if( !strcmp(argv[i],"--variable") ){ variable  = argv[i+1]; }
    else if( !strcmp(argv[i],"--write")    ){ write     = true;      }
    else if( !strcmp(argv[i],"--debug")    ){ debug     = true;      }
    else if( !strcmp(argv[i],"--help")     ){ printHelp = true;      }
  }
  if( printHelp ){
    std::cout << "SigComp: make signal composition sys!!" << std::endl;
    std::cout << "  Usage  :  SigComp [Options]"          << std::endl;
    std::cout << "             --Fiducial [Fiducial measurement: default 'false']"   << std::endl;
    std::cout << "             --variable [set differential variable: default '']"   << std::endl;
    std::cout << "             --write    [Set writing to file: default is 'false']" << std::endl;
    std::cout << "             --debug    [Set debug mode: default is 'false']"      << std::endl;
    std::cout << "             --help     [Print this help]"                         << std::endl;
    exit(0);
  }
  if(!Fiducial && variable==""){
    std::cout << "<SigComp()> :: running in differential mode "
	      << "but variable not set -> please provide it" << std::endl;
    exit(0);
  }
  if( debug ){
    std::cout << " <SigComp()> :: Running with Options: "   << std::endl;
    std::cout << "                 Fiducial = " << Fiducial << std::endl;
    std::cout << "                 variable = " << variable << std::endl;
    std::cout << "                 debug    = " << debug    << std::endl;
  }
  m_debug = debug;
  m_write = write;
  Process(variable,Fiducial);
  return 0;
  
}

void Process(std::string variable, bool Fiducial){

  m_variable = variable;
  m_Fiducial = Fiducial;

  m_Dir    = "Values/";
  if(Fiducial){ m_Dir += "Fid/";               }
  else        { m_Dir += "Diff/"+m_variable+"/"; }

  std::string FileName = m_Dir;
  if(Fiducial){ FileName += "r.dat";  }
  else        { FileName += "r_"+m_variable+".dat"; }

  if(m_debug)
    std::cout << "<SigComp()> :: opening file "<< FileName << std::endl;

  std::vector<std::vector<double>> v;
  std::ifstream in( FileName.c_str() );
  std::string record;
  std::vector<std::string> sysname = { "ATLAS_SignalComposition_ggH",
				       "ATLAS_SignalComposition_VBF",
				       "ATLAS_SignalComposition_WH" ,
				       "ATLAS_SignalComposition_ZH" ,
				       "ATLAS_SignalComposition_ttH",
				       "ATLAS_SignalComposition_bbH" };
  std::string ignore_me;

  while( in >> ignore_me, std::getline( in, record ) ){
    std::istringstream is( record );
    std::vector<double> row( ( std::istream_iterator<double>( is ) ),
			     std::istream_iterator<double>() );
    v.push_back( row );
  }

  int bin = 0;
  for( const auto &row : v ){

    if (row.size()>0){
      for (int ii=0 ; ii<6; ++ii){
	for (int jj=0 ; jj<6; ++jj){
	  eval( bin, row, jj, ii, sysname.at(ii) );
	}
      }
      bin++;
    }//for ( double x : row ) std::cout << x << ' ';
    //std::cout << std::endl;
  }
  
}    

void eval(int bin, std::vector<double> r, int prodmode,
	  int varied, std::string sys){
  
  std::vector<double> valuesup;
  std::vector<double> valuesdown;
  std::vector<double> SigComp = { 0.145, 0.203, 0.433, 0.468, 3.00, 0.220 };
  std::vector<double> select  = { 0, 0, 0, 0, 0, 0 };
  select.at(varied)=1;
  
  valuesup.push_back( r.at(2)  * (1 + select.at(0)*SigComp.at(0)) );
  valuesup.push_back( r.at(4)  * (1 + select.at(1)*SigComp.at(1)) );
  valuesup.push_back( r.at(5)  * (1 + select.at(2)*SigComp.at(2)) );
  valuesup.push_back( r.at(8)  * (1 + select.at(3)*SigComp.at(3)) );
  valuesup.push_back( r.at(10) * (1 + select.at(4)*SigComp.at(4)) );
  valuesup.push_back( r.at(12) * (1 + select.at(5)*SigComp.at(5)) );
  
  
  valuesdown.push_back( r.at(2)  * (1 - select.at(0)*SigComp.at(0)) );
  valuesdown.push_back( r.at(4)  * (1 - select.at(1)*SigComp.at(1)) );
  valuesdown.push_back( r.at(6)  * (1 - select.at(2)*SigComp.at(2)) );
  valuesdown.push_back( r.at(8)  * (1 - select.at(3)*SigComp.at(3)) );
  valuesdown.push_back( r.at(10) * (1 - select.at(4)*SigComp.at(4)*0.) ); /// force the negative error of tth to be 0
  valuesdown.push_back( r.at(12) * (1 - select.at(5)*SigComp.at(5)) );
  
//std::cout << sys << " "
//	    << (valuesdown.at(prodmode)/std::accumulate(valuesdown.begin(),valuesdown.end(),0.))/r.at(2+prodmode*2)
//	    << "  "
//	    << (valuesup.at(prodmode)/std::accumulate(valuesup.begin(),valuesup.end(),0.))/r.at(2+prodmode*2) << std::endl;;

  double Dw = (valuesdown.at(prodmode)/std::accumulate(valuesdown.begin(),valuesdown.end(),0.))/r.at(2+prodmode*2);
  double Up = (valuesup.at(prodmode)/std::accumulate(valuesup.begin(),valuesup.end(),0.))/r.at(2+prodmode*2);

  std::cout << sys << " " << Dw << "  " << Up << std::endl;

  if(m_write)
    WriteToFile(bin,prodmode,sys,Dw,Up);
  
}

void WriteToFile(int bin, int prodmode, std::string sys,
		 double Dw, double Up, bool last){

  std::string binName = "";
  if(m_Fiducial){ binName = GetChannel(bin);           }
  else{           binName = "bin"+std::to_string(bin); }

  std::string ProdMode = GetProdMode(prodmode);
  std::string outFile  = m_Dir+"Sys/"+ProdMode+"_"+binName+".dat";
  if(m_debug)
    std::cout << "<SigComp()> :: update file " << outFile << std::endl;
  
  m_outF.open( outFile.c_str(), std::ios_base::app);
  if(sys.find("ggH")!=std::string::npos) m_outF<<std::endl;

  if(last){
    m_outF.width(55); m_outF << std::left << sys;
    m_outF.width(12); m_outF << Dw;
    m_outF.width(12); m_outF << Up;
    m_outF.width(12); m_outF << std::right << 1;
    m_outF.width(12); m_outF << std::right << 1;
  }
  else{
    m_outF.width(55); m_outF << std::left << sys;
    m_outF.width(12); m_outF << Dw;
    m_outF.width(12); m_outF << Up;
    m_outF.width(12); m_outF << std::right << 1;
    m_outF.width(12); m_outF << std::right << 1 << std::endl;
  }

  m_outF.close();
  
}

std::string GetProdMode(int prodmode){

  std::string pd = "";
  if(prodmode==0)     { pd="ggH"; }
  else if(prodmode==1){ pd="VBF"; }
  else if(prodmode==2){ pd="WH";  }
  else if(prodmode==3){ pd="ZH";  }
  else if(prodmode==4){ pd="ttH"; }
  else if(prodmode==5){ pd="bbH"; }

  return pd;
  
}

std::string GetChannel(int bin){

  std::string ch = "";
  if(bin==0)     { ch="incl";  }
  else if(bin==1){ ch="4mu";   }
  else if(bin==2){ ch="4e";    }
  else if(bin==3){ ch="2mu2e"; }
  else if(bin==4){ ch="2e2mu"; }

  return ch;
  
}
