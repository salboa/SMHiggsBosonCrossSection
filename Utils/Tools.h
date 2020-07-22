#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <sys/stat.h>
#include <TChainElement.h>
#include <TChain.h>

void CheckOutDir(std::string outDir){

  std::string delim = "/";
  std::vector<std::string> m_dirs;
  size_t pos = 0;
  while( (pos = outDir.find(delim)) != std::string::npos ){
    m_dirs.push_back( outDir.substr(0, pos) );
    outDir.erase(0, pos + delim.length());
  }

  std::string m_tmpOutDir = "";
  for(uint i=0; i<m_dirs.size(); i++){
    struct stat st;
    m_tmpOutDir+=m_dirs.at(i)+"/";
    if(stat(m_tmpOutDir.c_str(),&st) == 0){
      PRINT_DEBUG("<CheckOutDir()> :: \033[1;32m Out Directory "+m_tmpOutDir+
		  " already present!\033[0m");
    }
    else{
      PRINT_DEBUG("<CheckOutDir()> :: \033[1;34m Creating Directory "+m_tmpOutDir+
		  " ... \033[0m");
      int outD = system( ("mkdir "+m_tmpOutDir).c_str() );
      if(outD!=0)
	PRINT_FATAL("<CheckOutDir()>:: \033[1;31m Directory "+m_tmpOutDir+
		    " could not be created!\033[0m");
    }
  }
  m_dirs.clear();
  
}

void PrintChainContent(std::string type, TChain *chain){

  PRINT_DEBUG("<PrintChainContent()>:: "+type+" chain contains files:");
  TObjArray * fileElements = chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl=0;
  while (( chEl=(TChainElement*)next() )) {
    TFile f(chEl->GetTitle());
    PRINT_DEBUG("                      "+(std::string)f.GetName());
  }
  
}

std::string ConvertToStringWithPrecision(double value, int n){
  
  std::ostringstream out;
  out << std::setprecision(n) << value;
  return out.str();
  
}

double GetDefaultIntLumi(){

  return 138.96;
  
}
