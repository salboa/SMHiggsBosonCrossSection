/* program includes */
#include "EvtListScan.h"

int main( int argc, char* argv[] ) {

  int channel       = -1;
  m_debug           = false;
  bool printHelp    = false;
  std::string prod  = "ggH";
  std::string list1 = "";
  std::string list2 = "";
  for(int i = 1; i < argc; ++i){
    bool validCmd=false;
    std::string cmd = argv[i];
    if( !strcmp(argv[i],"--channel")      ){ channel   = std::stoi(argv[i+1]); validCmd = true; }
    else if( !strcmp(argv[i],"--process") ){ prod      = argv[i+1];            validCmd = true; }
    else if( !strcmp(argv[i],"--list1")   ){ list1     = argv[i+1];            validCmd = true; }
    else if( !strcmp(argv[i],"--list2")   ){ list2     = argv[i+1];            validCmd = true; }
    else if( !strcmp(argv[i],"--debug")   ){ m_debug   = true;                 validCmd = true; }
    else if( !strcmp(argv[i],"--help")    ){ printHelp = true;               validCmd = true; }
    if( !validCmd && cmd.find("--")!=std::string::npos){
      std::cout << "\033[1;31m option " << cmd << " not valid. Type ./EvtListScan"
		<< " --help and check the available options, exit!\033[0m" << std::endl;
      exit(0);
    }
  }
  
  if(printHelp){
    std::cout << " EvtListScan: check two list of events!! "                 << std::endl;
    std::cout << "  usage:   ./EvtListScan [--help] [--channel] [--process]" << std::endl;
    std::cout << "                         [--list1] [--list2] [--debug]"    << std::endl;
    std::cout << "                         [--verbose]"                      << std::endl;
    std::cout << "                                                         " << std::endl;
    std::cout << " Optional arguments (default value): "                     << std::endl;
    std::cout << " --help         print this help and exit"                  << std::endl;
    std::cout << " --channel      choose 4l decay channel. Options are:"     << std::endl;
    std::cout << "                0=4mu, 1=4e, 2=2mu2e, 3=2e2mu (-1)"        << std::endl;
    std::cout << " --list1        specify first list of events."             << std::endl;
    std::cout << " --list2        specify second list of events."            << std::endl;
    std::cout << " --debug        set debug mode (false)"                    << std::endl;
    exit(0);
  }
  
  SetDebugLevel(m_debug);
  if(channel==-1){
    PRINT_ERROR("4l decay channel not defined: exiting ... ");
    exit(0);
  }
  if(list1==""){
    PRINT_ERROR("list1 not defined: exiting ... ");
    exit(0);
  }
  if(list2==""){
    PRINT_ERROR("list2 not defined: exiting ... ");
    exit(0);
  }
  
  if(m_debug){
    std::cout << " Calling EvtListScan with options:  " << std::endl;
    std::cout << "   channel = " << channel             << std::endl;
    std::cout << "   process = " << prod                << std::endl;
    std::cout << "   list1   = " << list1               << std::endl;
    std::cout << "   list2   = " << list2               << std::endl;
    std::cout << "   debug   = " << m_debug             << std::endl;
  }
  
  EvtListScan(channel,prod,list1,list2);
  return 0;
  
}

void EvtListScan(int channel, std::string prod, std::string file1, std::string file2){

  std::string Dir = "../varsDistro/";

  m_list1.open( file1.c_str() );
  m_list2.open( file2.c_str() );

  std::vector<int> RunList1, RunList2, EvtTypeList1, EvtTypeList2;
  std::vector<unsigned long long> EvtList1, EvtList2;
  
  int tmpRun     = 0;
  int tmpEvtType = 0;
  unsigned long long tmpEvt = 0;
  int counter = 0;
  while(m_list1.good()){
    counter++;
    tmpRun=0;
    tmpEvt=0;
    tmpEvtType=0;
    m_list1>>tmpRun;
    m_list1>>tmpEvt;
    m_list1>>tmpEvtType;
    if(tmpEvtType!=channel) continue;
    EvtList1.push_back(tmpEvt);
    RunList1.push_back(tmpRun);
    EvtTypeList1.push_back(tmpEvtType);
  }
  PRINT("< EvtListScan() >:: Events in list "+file1+" = "+std::to_string(counter)+
	", which "+std::to_string(RunList1.size())+" are channel "+GetChannelName(channel+1));
  m_list1.close();
  
  counter = 0;
  while(m_list2.good()){
    counter++;
    tmpRun=0;
    tmpEvt=0;
    tmpEvtType=0;
    m_list2>>tmpRun;
    m_list2>>tmpEvt;
    m_list2>>tmpEvtType;
    if(tmpEvtType!=channel) continue;
    RunList2.push_back(tmpRun);
    EvtList2.push_back(tmpEvt);
    EvtTypeList2.push_back(tmpEvtType);
  }
  PRINT("< EvtListScan() >:: Events in list "+file2+" = "+std::to_string(counter)+
	", which "+std::to_string(RunList2.size())+" are channel "+GetChannelName(channel+1));
  m_list2.close();

  /* Opening Out files */
  m_OutCommon.open( (Dir+"CommonEvts_"+prod+"_"+GetChannelName(channel+1)+".dat").c_str() );
  m_OutList1.open( (Dir+"OnlyEvtsList1_"+prod+"_"+GetChannelName(channel+1)+".dat").c_str() );
  m_OutList2.open( (Dir+"OnlyEvtsList2_"+prod+"_"+GetChannelName(channel+1)+".dat").c_str() );

  ///* check douplicates */
  //std::set< std::pair<Int_t,ULong64_t> > m_EvtProcessed;
  //for(uint j=0; j<RunList2.size(); j++){
  //  int run = RunList2.at(j);
  //  unsigned long long evt = EvtList2.at(j);
  //  const std::pair<Int_t,ULong64_t> RunEvt = std::make_pair(run,evt);
  //  if( m_EvtProcessed.insert(RunEvt).second == false ){
  //    std::cout << "< DataEvtListScan() >:: Found Duplicate In List2 "
  //	<< "-> Skipping! (Run = " << run << " Event = " << evt << ")"
  //	<< std::endl;
  //    continue;
  //  }
  //}

  /* Define events counters */
  int cmEvt = 0;
  int ls1   = 0;
  int ls2   = 0;
  
  for(uint i=0; i<RunList1.size(); i++){
    if(EvtTypeList1.at(i)!=channel) continue;
    int run = RunList1.at(i);
    unsigned long long evt = EvtList1.at(i);
    int type = EvtTypeList1.at(i);
    bool evtfound=false;
    for(uint j=0; j<RunList2.size(); j++){
      if( run==RunList2.at(j) && evt==EvtList2.at(j) ){
	evtfound=true;
	WriteToFile(m_OutCommon, run, evt, type);
	cmEvt++;
      }
    }
    if(!evtfound){
      PRINT_VERBOSE("< EvtListScan() >:: Event NOT Found in List2: Run = "+std::to_string(run)+
		    " Event = "+std::to_string(evt)+" decay = "+std::to_string(type));
      WriteToFile(m_OutList1, run, evt, type);
      ls1++;
    }
  }
  m_OutCommon.close();
  m_OutList1.close();

  for(uint i=0; i<RunList2.size(); i++){
    if(EvtTypeList2.at(2)!=channel) continue;
    int run = RunList2.at(i);
    unsigned long long evt = EvtList2.at(i);
    int type = EvtTypeList2.at(i);
    bool evtfound=false;
    for(uint j=0; j<RunList1.size(); j++){
      if( run==RunList1.at(j) && evt==EvtList1.at(j) )
	evtfound=true;
    }
    if(!evtfound){
      PRINT_VERBOSE("< EvtListScan() >:: Event NOT Found in List1: Run = "+std::to_string(run)+
		    " Event = "+std::to_string(evt)+" decay = "+std::to_string(type));
      WriteToFile(m_OutList2, run, evt, type);
      ls2++;
    }
  }
  m_OutList2.close();

  double _cm1 = (double)cmEvt/(double)RunList1.size();
  double _cm2 = (double)cmEvt/(double)RunList2.size();
  double _ls1 = (double)ls1/(double)RunList1.size();
  double _ls2 = (double)ls2/(double)RunList2.size();
  PRINT("< EvtListScan() >:: Summary for channel "+GetChannelName(channel+1));
  PRINT("                    List1 = "+std::to_string(RunList1.size())+" , List2 = "+
	std::to_string(RunList2.size()));
  PRINT("                    Common = "+std::to_string(cmEvt)+" ("+
	std::to_string(_cm1)+","+std::to_string(_cm2)+"), Only List1 = "+std::to_string(ls1)+
	" ("+std::to_string(_ls1)+"), Only List2 = "+std::to_string(ls2)+" ("+
	std::to_string(_ls2)+")");

  RunList1.clear();
  RunList2.clear();
  
}

void WriteToFile(std::ofstream& OutF, int run, unsigned long long event, int type){

  OutF.width(10);
  OutF << std::right << run;
  OutF.width(14);
  OutF << std::right << event;
  OutF.width(4);
  OutF << std::right << type;
  OutF << std::endl;
  
}
