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
    m_MCtype      = None
    m_Nbins       = None
    m_Min         = None
    m_Max         = None
    m_DoNormSyst  = None
    m_DoShapeSyst = None
    m_doMtx       = None
    m_doShiftUp   = None
    m_doShiftDown = None
    m_usePowhegZZ = None
    m_LowMass     = None
    m_HighMass    = None
    m_debug       = None
    m_verbose     = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="MCtype":
                m_MCtype=value

            if key=="Nbins":
                m_Nbins=value

            if key=="Min":
                m_Min=value

            if key=="Max":
                m_Max=value

            if key=="doMatrix":
                m_doMtx=True

            if (key=="doShiftUp"):
                m_doShiftUp=True

            if (key=="doShiftDown"):
                m_doShiftDown=True

            if key=="DoNormSyst":
                m_DoNormSyst=True

            if key=="DoShapeSyst":
                m_DoShapeSyst=True

            if key=="usePowhegZZ":
                m_usePowhegZZ=True

            if key=="isLowMass":
                m_LowMass=True

            if key=="isHighMass":
                m_HighMass=True

            if key=="debug":
                m_debug=True

            if key=="verbose":
                m_verbose=True

    print "-------------------------------------------------"
    if not m_MCtype:
        print "MCtype not set      -> using default: mc15c"
        m_MCtype="mc15c"
    if not m_Nbins:
        print "Nbins not set       -> using default: 15"
        m_Nbins=15
    if not m_Min:
        print "Min value not set   -> using default: 115"
        m_Min=115
    if not m_Max:
        print "Max value not set   -> using default: 130"
        m_Max=130
    if not m_doMtx:
        print "doMatrix not set    -> using default: False"
        m_doMtx=False
    if not m_doShiftUp:
        print "doShiftUp not set   -> using default: False"
        m_doShiftUp=False
    if not m_doShiftDown:
        print "doShiftDown not set -> using default: False"
        m_doShiftDown=False
    if not m_DoNormSyst:
        print "DoNormSyst not set  -> using default: False"
        m_DoNormSyst=False
    if not m_DoShapeSyst:
        print "DoShapeSyst not set -> using default: False"
        m_DoShapeSyst=False
    if not m_usePowhegZZ:
        print "usePowhegZZ not set -> using default: False"
        m_usePowhegZZ=False
    if not m_LowMass:
        print "isLowMass not set   -> using default: False"
        m_LowMass=False
    if not m_HighMass:
        print "isHighMass not set  -> using default: False"
        m_HighMass=False
    if not m_debug:
        m_debug=False
    if not m_verbose:
        m_verbose=False

    if m_LowMass:
        m_Min = 80
        m_Max = 110

    if m_HighMass:
        m_Min = 150
        m_Max = 360
        
    print "-------------------------------------------------"
    print ""
    print "  Options set: "
    print "MCtype      = "+m_MCtype
    print "Nbins       = "+str(m_Nbins)
    print "Min         = "+str(m_Min)
    print "Max         = "+str(m_Max)
    print "doMatrix    = "+str(m_doMtx)
    print "doShiftUp   = "+str(m_doShiftUp)
    print "doShiftDown = "+str(m_doShiftDown)
    print "DoNormSyst  = "+str(m_DoNormSyst)
    print "DoShapeSyst = "+str(m_DoShapeSyst)
    print "usePowhegZZ = "+str(m_usePowhegZZ)
    print "isLowMass   = "+str(m_LowMass)
    print "isHighMass  = "+str(m_HighMass)
    print "debug       = "+str(m_debug)
    print "verbose     = "+str(m_verbose)
    print "-------------------------------------------------"


    RunMakeInput(m_MCtype,m_Nbins,m_Min,m_Max,m_doMtx,m_doShiftUp,m_doShiftDown,
                 m_DoNormSyst,m_DoShapeSyst,m_usePowhegZZ,m_debug,m_verbose)


def RunMakeInput(MCtype,
                 Nbins,
                 Min,
                 Max,
                 Mtx,
                 ShiftUp,
                 ShiftDown,
                 DoNormSyst,
                 DoShapeSyst,
                 powhegZZ,
                 debug,
                 verbose):

    print ""
    #Process Definition:
    Samples = ["ggH", "ggH_Powheg", "VBF", "WH", "ZH", "ttH", "bbH", "AllSig"]

    if not (ShiftUp or ShiftDown):

        Other = ["qqZZ", "ggZZ", "AllZZ", "ZZEW", "MG5",
                 "MG5KHvv", "MG5KAvv", "MG5KAgg",
                 "MultiBoson", "Zjets","data","redBkg"]

        Samples.extend(Other)

    print "Processing Samples = ",Samples
    
    #Systematics Setting
    Begin      = -1
    SystNumber = 0
    if DoNormSyst:
        SystNumber=93
    if DoShapeSyst:
        Begin      = 93
        SystNumber = 146

    os.getenv('DYLD_LIBRARY_PATH')

    for i in range(Begin+1,SystNumber+1):

        print "Running MakeInput for Systematic "+str(i)
        
        for sample in Samples:

            cmd  = "./MakeInput --Process "+sample+" --MCtype "+MCtype
            cmd += " --SysType "+str(i)+" --Nbins "+str(Nbins)
            cmd += " --Min "+str(Min)+" --Max "+str(Max)
            if debug:
                cmd += " --debug"
            if verbose:
                cmd += " --verbose"
            if Mtx:
                cmd += " --doMatrix"
            if ShiftUp:
                cmd += " --doShiftUp"
            if ShiftDown:
                cmd += " --doShiftDown"

            if powhegZZ:
                cmd += " --usePowhegZZ"
            os.system(cmd)

def ShowDoc():
    print ""
    print "Script to run MakeInput code!"
    print "  Usage : ./RunMakeInput.py [Options]!"
    print "          Options:  "
    print "                   MCtype=mc15c             : default is 'mc15c'"
    print "                   Nbins=15                 : default is 15     "
    print "                   Min=115                  : default is 115    "
    print "                   Max=130                  : default is 130    "
    print "                   doMatrix=[True/False]    : default is False  "
    print "                   doShiftUp=[True/False]   : default is False  "
    print "                   doShiftDown=[True/False] : default is False  "
    print "                   DoNormSyst=[True/False]  : default is False  "
    print "                   DoShapeSyst=[True/False] : default is False  "
    print "                   usePowhegZZ=[True/False] : default is False  "
    print "                   isLowMass=[True/False]   : default is False  "
    print "                   isHighMass=[True/False]  : default is False  "
    print "                   debug=[True/False]       : default is False  "
    print "                   verbose=[True/False]     : default is False  "

if __name__ == "__main__":
    main()
