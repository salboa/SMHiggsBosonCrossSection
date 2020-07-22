#!/usr/bin/python
import os
import sys
import subprocess
import getopt
import string

def main():
    # parse command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:], "h", ["help"])
    except getopt.error, msg:
        print msg
        print "for help use --help"
        sys.exit(2)
    # process options
    for o, a in opts:
        if o in ("-h", "--help"):
            ShowDoc()
            sys.exit(0)

    #Assign None to all variable
    m_runType     = None
    m_isConf      = None
    m_isPaper     = None
    m_isSepBkg    = None
    m_debug       = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="runType":
                m_runType=value

            if key=="isSepBkg":
                m_isSepBkg=True

            if key=="isConf":
                m_isConf=True

            if key=="isPaper":
                m_isPaper=True

            if key=="debug":
                m_debug=True

    print "-------------------------------------------------"
    if not m_runType:
        print "runType not set     -> please provide it!"
        exit(0)
    if not m_isSepBkg:
        print "isSepBkg            -> using default: False"
        m_isSepBkg=False
    if not m_isConf:
        print "isConf not set      -> using default: False"
        m_isConf=False
    if not m_isPaper:
        print "isPaper not set     -> using default: False"
        m_isPaper=False
    if not m_debug:
        m_debug=False
        
    print "-------------------------------------------------"
    print ""
    print "  Options set: "
    print "runType = "+m_runType
    print "isConf  = "+str(m_isConf)
    print "isPaper = "+str(m_isPaper)
    print "debug   = "+str(m_debug)

    print "-------------------------------------------------"

    if m_runType=="RecoPlots":
        RunRecoPlots(m_isSepBkg,m_isConf,m_isPaper,m_debug);
    else:
        Run(m_runType,m_isSepBkg,m_isConf,m_isPaper,m_debug);

    
def RunRecoPlots(isSepBkg,isConf,isPaper,debug):

    cmd = "./doPlots --doLinear --doAtlasStyle --useData --drawSyst"

    if isSepBkg:
        cmd += " --useZjets"
    else:
        cmd += " --useRedBkg"

    if isConf:
        cmd += " --isConf"

    if isPaper:
        cmd += " --isPaper"

    if debug:
        cmd += " --debug"

    os.system(cmd+" --drawM4l")
    os.system(cmd+" --drawM4l --channel 4mu")
    os.system(cmd+" --drawM4l --channel 4e")
    os.system(cmd+" --drawM4l --channel 2mu2e")
    os.system(cmd+" --drawM4l --channel 2e2mu")
    os.system(cmd+" --draw2Dmm")
    

def Run(runType,isSepBkg,isConf,isPaper,debug):

    cmd = "./doPlots --doLinear --doAtlasStyle"

    if isConf:
        cmd += " --isConf"

    if isPaper:
        cmd += " --isPaper"
        
    if runType=="RecoPlots":
        cmd += " --useData"

    if runType!="MigrMatrices" and runType!="SigOnly":
        cmd += " --drawSyst"
        if isSepBkg:
            cmd += " --useZjets"
        else:
            cmd += " --useRedBkg"
            
    elif runType=="SigOnly":
        cmd += " --SigOnly"
    elif runType=="MigrMatrices":
        cmd += " --doMatrix"

    os.system(cmd)

def ShowDoc():
    print ""
    print "Script to run doPlots code!"
    print "  Usage : ./RunDoPlots.py [Options]!"
    print "          Options:  "
    print "                   runType=RecoPlots        : needed value:     "
    print "                                              'RecoPlots',      "
    print "                                              'SigOnly',        "
    print "                                              'MigrMaytrices',  "
    print "                                              'MCOnly'          "
    print "                   isSepBkg=[True/False]    : default is False  "
    print "                   isConf=[True/False]      : default is False  "
    print "                   isPaper=[True/False]     : default is False  "
    print "                   debug=[True/False]       : default is False  "

if __name__ == "__main__":
    main()
