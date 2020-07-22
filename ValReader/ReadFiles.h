/* C++ includes */
#include "iostream"
#include "fstream"
#include "set"
#include "map"
#include "vector"
#include "cassert"
#include "ctime"
#include "stdio.h"
#include "string.h"

/* Methods */
void Settings(std::string inFile, std::string outFile, int nBins,
	      int Bin, bool Fiducial, bool debug, bool verbose);
void Process();
void ProcessFiducial();
void ProcessDifferential(int bin);
void FillInfo(std::string cat);
void WriteOutput(std::string outname);
void BlockPosition();
void BlockBinPosition();
int FindLowerBoundary(std::string ch);
int FindUpperBoundary(std::string ch);

/* Internal Variables */
std::map<std::string,std::vector<double> > m_map;
std::ifstream m_In;
std::ofstream m_Out;
std::string m_FileName;
std::string m_OutName;
int m_nBins;
int m_Bin;
bool m_Fiducial, m_debug, m_verbose;
std::map<std::string,int> m_Pos;
