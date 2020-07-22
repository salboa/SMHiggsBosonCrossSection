/* C++ includes */
#include "iostream"
#include "fstream"
#include "iomanip"
#include "vector"
#include "set"
/* Other includes */
#include "../Utils/PrintHelpers.h"
#include "../Utils/VarHandler.h"

void EvtListScan(int channel, std::string prod, std::string list1, std::string list2);
void WriteToFile(std::ofstream& OutF, int run, unsigned long long event, int type);

/* members */
bool m_debug;
bool m_verbose;
std::ofstream m_OutCommon;
std::ofstream m_OutList1;
std::ofstream m_OutList2;
std::ifstream m_list1;
std::ifstream m_list2;
