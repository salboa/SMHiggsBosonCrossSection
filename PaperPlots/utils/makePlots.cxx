// C++ includes
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

// ROOT includes
#include <TH1F.h>
#include <TString.h>
#include <TObjArray.h>
#include <TObjString.h>

// package includes
#include "plotMaker.h"


using namespace std;

bool cmdline(int argc, char** argv, map<TString, TString>& opts);


int main(int argc, char *argv[])
{   

    // read in command line arguments
    map<TString, TString> opts;
    if(!cmdline(argc,argv, opts)) return 0;

    plotMaker* worker = new plotMaker(opts);
    worker->run();
    
    delete worker;

    return 0;
}


bool cmdline(int argc, char** argv, map<TString, TString>& opts)
{
    //opts.clear();

    opts["variable"]          = "pt";
    opts["type"]              = "matrix";
    opts["intBins"]           = "true";
    opts["inputDir"]          = "TGraph/"; //"/Users/biancaciungu/Desktop/Moriond2019/ws_output";
    opts["outputDir"]         = "unfoldedPlots";
    opts["doExpected"]        = "false";
    opts["calcPVal"]          = "false";
    opts["plotZZ"]            = "true";

    for(int i = 1; i < argc; ++i)
    {
        string opt=argv[i];

        if(opt=="--help" || opt == "--options" || opt =="--h")
        {
            cout<< "Options menu \n ============================================== \n" << endl;
            cout<<"--variable     : The variable you want plots for, e.g. pt4l"<< endl;
            cout<<"--type         : Options: matrix,cf,comb"<< endl;
            cout<<"--inputDir     : Where the fit results are stored (with structure from differential code) "<< endl;
            cout<<"--outputDir    : Name of directory where final plots will be stored"<< endl;
            cout<<"--doExpected   : Will plot expected values from fit"<< endl;

            return false;
 
        }

        if(0!=opt.find("--")) {
            cout<<"ERROR: options start with '--'!"<<endl;
            cout<<"ERROR: options is: "<<opt<<endl;
            return false;
        }
        opt.erase(0,2);
        
        if(opts.find(opt)==opts.end()) {
            cout<<"ERROR: invalid option '"<<opt<<"'!"<<endl;
            return false;
        }

        string nxtopt=argv[i+1];
        if(0==nxtopt.find("--")||i+1>=argc) {
            cout<<"ERROR: option '"<<opt<<"' requires value!"<<endl;
            return false;
        }
        opts[opt]=nxtopt;
        i++;
    }

    return true;
}





