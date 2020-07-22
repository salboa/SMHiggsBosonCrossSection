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
    m_Variable    = None
    m_doFiducial  = None
    m_Draw        = None
    m_Normalized  = None
    m_doN3LO      = None
    m_isConf      = None
    m_isPaper     = None
    m_debug       = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="runType":
                m_runType=value

            if key=="Variable":
                m_Variable=value

            if key=="doFiducial":
                m_doFiducial=True

            if key=="Draw":
                m_Draw=True

            if key=="Normalized":
                m_Normalized=True
            
            if key=="doN3LO":
              m_doN3LO=True

            if key=="isConf":
                m_isConf=True

            if key=="isPaper":
                m_isPaper=True

            if key=="debug":
                m_debug=True

    print "-------------------------------------------------"
    if not m_runType:
        print "runType not set     -> using single variable run"
        m_runType="SingleRun"
    if not m_Variable:
        if m_runType=="SingleRun" and not m_doFiducial:
            print "Variable not set    -> please define it!"
            exit(0)
        else:
            m_Variable=""
    if not m_doFiducial:
        print "doFicucial not set  -> using default: 'False'"
        m_doFiducial=False
    if not m_Draw:
        print "Draw not set        -> using default: 'False'"
        m_addShapeSys=False
    if not m_Normalized:
        print "Normalized not set  -> using default: 'False'"
        m_Normalized=False
    if not m_doN3LO:
        print "N3LO not set        -> using default: 'False'"
        m_doN3LO=False
    if not m_isConf:
        print "isConf not set      -> using default: 'False'"
        m_isConf=False
    if not m_isPaper:
        print "isPaper not set    -> using default: 'False'"
        m_isPaper=False
    if not m_debug:
        m_debug=False

    print "-------------------------------------------------"
    print ""
    print "  Options set: "
    print "runType     = "+m_runType
    print "Variable    = "+str(m_Variable)
    print "doFiducial  = "+str(m_doFiducial)
    print "Draw        = "+str(m_Draw)
    print "Normalized  = "+str(m_Normalized)
    print "doN3LO      = "+str(m_doN3LO)
    print "isConf      = "+str(m_isConf)
    print "isPaper     = "+str(m_isPaper)
    print "debug       = "+str(m_debug)
    print "-------------------------------------------------"

    if m_runType=="All":
        RunAll(m_debug,m_isConf,m_isPaper)
        
    elif m_runType=="Standard":
        m_Normalized = False
        m_doN3LO     = False
        Run(m_Normalized,m_doN3LO,m_debug,m_isConf,m_isPaper)
        
    elif m_runType=="Normalized":
        m_Normalized = True
        m_doN3LO     = False
        Run(m_Normalized,m_doN3LO,m_debug,m_isConf,m_isPaper)

    elif m_runType=="N3LO":
        m_Normalized = False
        m_doN3LO     = True
        Run(m_Normalized,m_doN3LO,m_debug,m_isConf,m_isPaper)

    elif m_runType=="NormN3LO":
        m_Normalized = True
        m_doN3LO     = True
        Run(m_Normalized,m_doN3LO,m_debug,m_isConf,m_isPaper)
        
    elif m_runType=="SingleRun":
        RunWithOptions(m_Variable,m_doFiducial,m_Draw,m_Normalized,m_debug,
                       m_isConf,m_isPaper)


def RunAll(debug,isConf,isPaper):

    # Making Standard Plots
    #Run(False,False,debug,isConf,isPaper)

    # Making Normalized Plots
    #Run(True,False,debug,isConf,isPaper)
    

    # Making N3LO Plots
    Run(False,True,debug,isConf,isPaper)
    
    # Making Normalized N3LO Plots
    #Run(True,True,debug,isConf,isPaper)


def Run(normalized,n3lo,debug,isConf,isPaper):

    Vars = ["pt","njet","Fiducial"]
             
    for v in Vars:
        
        cmd = "./UnfoldPlots "

        if v.find("Fiducial")!=-1:
            cmd += " --doFiducial"
        else:
            cmd += " --Variable "+v
            
        if normalized and v!="Fiducial":
            cmd += " --Normalized"
        
        if n3lo and v!="Fiducial":
            cmd += " --doN3LO"
            
        if debug:
            cmd += " --debug"

        if isConf:
            cmd += " --isConf"

        if isPaper:
            cmd += " --isPaper"

        print cmd
        os.system(cmd)

        
def RunWithOptions(var,doFiducial,draw,normalized,debug,isConf,isPaper):

    cmd = "./UnfoldPlots"

    if doFiducial:
        cmd += " --doFiducial"
    else:
        cmd += " --Variable "+var

    if draw:
        cmd += " --Draw"

    if normalized:
        cmd += " --Normalized"

    if debug:
        cmd += " --debug"

    if isConf:
        cmd += " --isConf"

    if isPaper:
        cmd += " --isPaper"

    print cmd
    os.system(cmd)
    
    
def ShowDoc():
    print ""
    print "Script to run RunMakeUnfold code!"
    print "  Usage : ./RunMakeUnfold.py [Options]!"
    print "          Options:  "
    print "                   runType=All             : default is 'SingleRun'    "
    print "                                             Choices are = 'All',      "
    print "                                             'Standard', 'Normalized', "
    print "                                             'N3LO', 'NormN3LO'        "
    print "                                             'SingleRun'               "
    print "                   Variable=pt             : default is ' '            "
    print "                   doFiducial=[True/False] : default is 'False'        "
    print "                   Draw=[True/False]       : default is 'False'        "
    print "                   Normalized=[True/False] : default is 'False'        "
    print "                   doN3LO=[True/False]     : default is 'False'        "
    print "                   isConf=[True/False]     : default is 'False'        "
    print "                   isPaper=[True/False]    : default is 'False'        "
    print "                   debug=[True/False]      : default is 'False'        "

if __name__ == "__main__":
    main()
