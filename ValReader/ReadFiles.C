#include "ReadFiles.h"

class Options{
  
public:
  std::string inFile  ;
  std::string outFile ;
  bool debug          ;
  bool verbose        ;
  bool Fiducial       ;
  int nBins           ;
  int Bin             ;
  std::string GetDateTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%d.%m.%Y_%I.%M.%S",timeinfo);
    std::string str(buffer);
    return str;
  }
  
  void SetDefault(){
    debug    = false;
    verbose  = false;
    Fiducial = false;
    inFile   = ""   ;
    outFile  = ""   ;
    nBins    = 0    ;
    Bin      = 0    ;
  }

  bool checkOpt(char* opt, char* value){
    std::string val = value;
    if( 0==val.find("-") ){
      std::cout << "WARNING:: Option " << opt <<
	" requires value -> skipping " << std::endl;
      return false;
    }
    return true;
  }
  
};

int main( int argc, char* argv[] ) {

  assert(argc>1);
  Options opt;
  opt.SetDefault();
  bool printHelp = false;
  for(int i = 1; i < argc; ++i){
    if( !strcmp(argv[i],"--inFile")         ){
      if( opt.checkOpt(argv[i],argv[i+1]) )    opt.inFile   = argv[i+1]; }
    else if( !strcmp(argv[i],"--outFile")   ){
      if( opt.checkOpt(argv[i],argv[i+1]) )    opt.outFile  = argv[i+1]; }
    else if( !strcmp(argv[i],"--Fiducial")  ){ opt.Fiducial = true; }
    else if( !strcmp(argv[i],"--nBins" )    ){
      if( opt.checkOpt(argv[i],argv[i+1]) )    opt.nBins    = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--Bin" )      ){
      if( opt.checkOpt(argv[i],argv[i+1]) )    opt.Bin      = std::stoi(argv[i+1]); }
    else if( !strcmp(argv[i],"--debug")     ){ opt.debug    = true; }
    else if( !strcmp(argv[i],"--verbose")   ){ opt.verbose  = true; }
    else if( !strcmp(argv[i],"--help")      ){ printHelp    = true; }
  }
  if( printHelp ){
    std::cout << "ReadFiles: make systematics inputs !!" << std::endl;
    std::cout << "  Usage  :  ReadFiles [Options]"         << std::endl;
    std::cout << "             --inFile   [Specify input file: needed]"             << std::endl;
    std::cout << "             --outFile  [Specify output file: needed]"            << std::endl;
    std::cout << "             --nBins    [Specify number of bins]"                 << std::endl;
    std::cout << "             --Bin      [Specify binNumber]"                      << std::endl;
    std::cout << "             --Fiducial [Fiducial measurement: default 'false']"  << std::endl;
    std::cout << "             --debug    [Set debug mode: default is 'false']"     << std::endl;
    std::cout << "             --verbose  [Set verbose mode: default is 'false']"   << std::endl;
    std::cout << "             --help     [Print this help]"                        << std::endl;
    exit(0);
  }

  if(opt.verbose) opt.debug=true;

  if(opt.inFile==""){
    std::cout << "Input File not specified. Exiting" << std::endl;
    exit(0);
  }
  if(opt.outFile==""){
    std::cout << "Output File not specified. Exiting" << std::endl;
    exit(0);
  }
    
  if(opt.debug){
    std::cout << "Calling ReadFiles with options: " << std::endl;
    std::cout << "  inFile   = " << opt.inFile      << std::endl;
    std::cout << "  outFile  = " << opt.outFile     << std::endl;
    std::cout << "  Fiducial = " << opt.Fiducial    << std::endl;
    std::cout << "  nBins    = " << opt.nBins       << std::endl;
    std::cout << "  Bin      = " << opt.Bin         << std::endl;
  }
  Settings(opt.inFile,opt.outFile,opt.nBins,opt.Bin,
	   opt.Fiducial,opt.debug,opt.verbose);
  Process();
  return 0;
  
}

void Settings(std::string inFile, std::string outFile, int nBins,
	      int Bin, bool Fiducial, bool debug, bool verbose){

  m_Fiducial = Fiducial;
  m_debug    = debug;
  m_verbose  = verbose;
  m_FileName = inFile;
  m_OutName  = outFile;
  m_nBins    = nBins;
  m_Bin      = Bin;
  
}

void Process(){

  if(m_Fiducial){
    BlockPosition();
    ProcessFiducial();
  }
  else{
    BlockBinPosition();
    ProcessDifferential(m_Bin);
  }

}

void ProcessFiducial(){

  FillInfo("4mu");
  WriteOutput(m_OutName+"_4mu");
  FillInfo("4e");
  WriteOutput(m_OutName+"_4e");
  FillInfo("2mu2e");
  WriteOutput(m_OutName+"_2mu2e");
  FillInfo("2e2mu");
  WriteOutput(m_OutName+"_2e2mu");
  FillInfo("incl");
  WriteOutput(m_OutName+"_incl");
  
}

void ProcessDifferential(int bin){

  FillInfo("[bin"+std::to_string(bin)+"]");
  WriteOutput(m_OutName);
  
}

void FillInfo(std::string cat){
  
  m_In.open( m_FileName.c_str() );

  m_map.clear();
  double tmpval=0;
  std::string sysId="";
  std::string trash="";
  int line=0;
  int Start=FindLowerBoundary(cat)+1;
  int End=FindUpperBoundary(cat)-1;
  while( m_In.good() ){
    if(line<Start || line>End)
      getline(m_In,trash);
    else{
      //std::cout <<"line "<<line<<std::endl;
      m_In>>sysId; m_In>>trash;
      m_In>>tmpval;
      if(tmpval<0) tmpval=0.000;
      m_map[sysId].push_back(tmpval);
      m_In>>tmpval;
      if(tmpval<0) tmpval=0.000;
      m_map[sysId].push_back(tmpval);
      m_map[sysId].push_back(1);
      m_map[sysId].push_back(1);
    }
    line++;
    
  }
  m_In.close();

  if( m_verbose ){
    for(auto& x: m_map)
      std::cout << "Systematic " << x.first << " ValDown " << x.second.at(0)
		<< " ValUp " << x.second.at(1) << " Type " << x.second.at(2)
		<< " Constr " << x.second.at(3) <<std::endl;
  }
  
}

void WriteOutput(std::string outname){

  m_Out.open( (outname+".dat").c_str() );
  m_Out.width(55); m_Out << std::left << "SysId";
  m_Out.width(12); m_Out << "DownVal";
  m_Out.width(12); m_Out << "UpVal";
  m_Out.width(12); m_Out << std::right << "SysType";
  m_Out.width(12); m_Out << "Constr"<<std::endl;
  int i=0;
  for(auto& x: m_map){
    if(i==(int)m_map.size()-1 ){
      m_Out.width(55); m_Out << std::left << x.first;
      m_Out.width(12); m_Out << x.second.at(0);
      m_Out.width(12); m_Out << x.second.at(1);
      m_Out.width(12); m_Out << std::right << x.second.at(2);
      m_Out.width(12); m_Out << x.second.at(3);
    }
    else{
      m_Out.width(55); m_Out << std::left << x.first;
      m_Out.width(12); m_Out << x.second.at(0);
      m_Out.width(12); m_Out << x.second.at(1);
      m_Out.width(12); m_Out << std::right << x.second.at(2);
      m_Out.width(12); m_Out << x.second.at(3)<<std::endl;
    }
    i++;
  }
  m_Out.close();
  
}

void BlockPosition(){

  if( m_verbose ){
    std::cout << "<BlockPosition()>:: Creating Blocks Positions" << std::endl;
  }

  m_Pos.clear();
  m_In.open( m_FileName.c_str() );
  std::string tmp="";
  int line=0;
  while( m_In.good() ){
    getline(m_In,tmp);

    if(tmp=="[4e_13TeV]"){
      m_Pos["4e"] = line;
    }
    else if(tmp=="[4mu_13TeV]"){
      m_Pos["4mu"] = line;
    }
    else if(tmp=="[2e2mu_13TeV]"){
      m_Pos["2e2mu"] = line;
    }
    else if(tmp=="[2mu2e_13TeV]"){
      m_Pos["2mu2e"] = line;
    }
    else if(tmp=="[4l_13TeV]"){
      m_Pos["incl"] = line;
    }
    line++;
      
  }
  m_In.close();

  if( m_verbose ){
    for(auto& x: m_Pos)
      std::cout << "Channel " << x.first << " line " << x.second << std::endl;
  }
  
}

void BlockBinPosition(){

  if( m_verbose ){
    std::cout << "<BlockPosition()>:: Creating Bin Blocks Positions"
	      << std::endl;
  }

  m_Pos.clear();
  m_In.open( m_FileName.c_str() );
  std::string tmp="";
  int line=0;
  while( m_In.good() ){
    getline(m_In,tmp);

    for(int i=0; i<m_nBins; i++){
      if(tmp=="[bin"+std::to_string(i)+"]"){
	m_Pos["[bin"+std::to_string(i)+"]"] = line;
      }
    }
    line++;
      
    }
    m_In.close();
    
  if( m_verbose ){
    for(auto& x: m_Pos)
      std::cout << "Bin " << x.first << " line " << x.second << std::endl;
  }
  
}

int FindLowerBoundary(std::string cat){

  if( m_verbose )
    std::cout << "<FindLowerBoundary()>:: LowerBound for category "
	      << cat << " = " << m_Pos[cat] << std::endl;
  return m_Pos[cat];
  
}

int FindUpperBoundary(std::string cat){

  /* scheme channel boundaries
     Fiducial: 
     2e2mu -> look for 2mu2e
     2mu2e -> look for 4e
     4e    -> look for 4mu
     4mu   -> look for incl
     incl  -> set it to 1000 

     Differential:
     binX -> look for binX+1
     binL -> set it to 5000  */
  int pos=-1;
  if(m_Fiducial){
    if(cat=="2e2mu")      pos = m_Pos["2mu2e"];
    else if(cat=="2mu2e") pos = m_Pos["4e"];
    else if(cat=="4e")    pos = m_Pos["4mu"];
    else if(cat=="4mu")   pos = m_Pos["incl"];
    else if(cat=="incl")  pos = 1000;
  }
  else{
    if(cat=="[bin"+std::to_string(m_nBins-1)+"]") pos=1000;
    else{
      pos = m_Pos["[bin"+std::to_string(m_Bin+1)+"]"];
    }
  }
  
  if( m_verbose )
    std::cout << "<FindUpperBoundary()>:: UpperBound for category "
	      << cat << " = " << pos << std::endl;
  
  return pos;
		    
}
