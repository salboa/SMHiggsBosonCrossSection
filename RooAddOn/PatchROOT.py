#!/usr/bin/python
import os
import sys
import getopt
import string
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--RootPath", type=str, default='', help='specify path to Root source')
args=parser.parse_args()

def main():

    print "Patching ROOT source code ... "
    if args.RootPath=='':
        print "RootPath not defined: please specify the path to ROOT source code! exiting "
        sys.exit(0)

    PatchRoot(args.RootPath)


def PatchRoot(m_path):

    isMac = True
    System = "OSX"
    OS = str( os.uname() )
    if OS.find("Linux")>0:
        isMac  = False;
        System = "Unix"

    print "Patching ROOT source for "+System
                
    PathToRootSource = m_path

    RooFitSrc   = PathToRootSource+"roofit/roofit/src/"
    RooFitInc   = PathToRootSource+"roofit/roofit/inc/"
    RooFitLink  = PathToRootSource+"roofit/roofit/inc/LinkDef1.h"

    RooStatSrc  = PathToRootSource+"roofit/roostats/src/"
    RooStatInc  = PathToRootSource+"roofit/roostats/inc/RooStats/"
    RooStatLink = PathToRootSource+"roofit/roostats/inc/LinkDef.h"

    #copying RooFit Files
    os.system("cp Adds/RooStarMomentMorph.cxx Adds/RooParamKeysPdf.cxx "+RooFitSrc+".")
    os.system("cp Adds/RooStarMomentMorph.h Adds/RooParamKeysPdf.h "+RooFitInc+".")
    
    #copying RooStat Files
    os.system("cp Adds/RooBSplineBases.cxx Adds/RooBSpline.cxx "+RooStatSrc+".")
    os.system("cp Adds/RooBSplineBases.h Adds/RooBSpline.h "+RooStatInc+".")
    
    #updating RooFit Linkdef file
    os.system("sed '7i#pragma link C++ class RooStarMomentMorph+ ;' "+RooFitLink+" > tmp_test.h")
    os.system("sed '7i#pragma link C++ class RooParamKeysPdf+ ;' tmp_test.h > test.h")
    os.system("rm -rf tmp_test.h ; mv test.h "+RooFitLink)
    
    #updating RooStat Linkdef file
    os.system("sed '28i#pragma link C++ class RooStats::HistFactory::RooBSpline+ ;' "+RooStatLink+" > tmp_test1.h")
    os.system("sed '28i#pragma link C++ class RooStats::HistFactory::RooBSplineBases+ ;' tmp_test1.h > test1.h")
    os.system("rm -rf tmp_test1.h ; mv test1.h "+RooStatLink)

    print "ROOT successfully patched!"

if __name__ == "__main__":
    main()
