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
#include "getPredictions.h"

using namespace std;

bool cmdline(int argc, char** argv, map<TString, TString>& opts);


int main(int argc, char *argv[])
{   

    // read in command line arguments
    map<TString, TString> opts;
    if(!cmdline(argc,argv, opts)) return 0;

    getPredictions* worker = new getPredictions(opts);
    worker->run();
    delete worker;

    return 0;

}


bool cmdline(int argc, char** argv, map<TString, TString>& opts)
{
    //opts.clear();

    opts["type"]          = "N3LOggF";
    opts["doSys"]         = "false";
    // opts["variable"]      = "all";

    for(int i = 1; i < argc; ++i)
    {
        string opt=argv[i];

        if(opt=="--help" || opt == "--options" || opt =="--h")
        {
            cout<< "Options menu \n ============================================== \n" << endl;
            cout<<"--type         : <N3LOggF,XH,MG5,HRes,N2LOggF"<< endl;

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





