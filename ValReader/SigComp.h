/* C++ includes */
#include "iostream"
#include "fstream"
#include "vector"
#include "iterator"
#include "sstream"
#include "numeric"
#include "cstring"

void Process(std::string variable, bool Fiducial);

void eval(int bin, std::vector<double> r, int prodmode,
	  int varied, std::string sys);

void WriteToFile(int bin, int prodmode, std::string sys,
		 double Dw, double Up, bool last=false);

std::string GetProdMode(int prodmode);

std::string GetChannel(int bin);

bool m_debug;
bool m_write;
bool m_Fiducial;
std::string m_variable;
std::string m_Dir;
std::ofstream m_outF;
