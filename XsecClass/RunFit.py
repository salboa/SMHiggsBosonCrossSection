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
    m_addSys      = None
    m_addShapeSys = None
    m_doFit       = None
    m_do2D        = None
    m_useData     = None
    m_fixSys      = None
    m_debug       = None
    m_verbose     = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="runType":
                m_runType=value

            if key=="Variable":
                m_Variable=value

            if key=="addSys":
                m_addSys=True

            if key=="addShapeSys":
                m_addShapeSys=True

            if key=="fixSys":
                m_fixSys=value

            if key=="doFit":
                m_doFit=True

            if key=="do2D":
                m_do2D=True

            if key=="useData":
                m_useData=True

            if key=="debug":
                m_debug=True

            if key=="verbose":
                m_verbose=True

    print "-------------------------------------------------"
    if not m_runType:
        print "runType not set     -> using single variable run"
        m_runType="SingleRun"
    if not m_Variable:
        if m_runType=="SingleRun" or m_runType=="Expected" or m_runType=="Observed" or m_runType=="ObsFixSys":
            print "Variable not set    -> please define it!"
            exit(0)
        else:
            m_Variable=""
    if not m_addSys:
        print "addSys not set      -> using default: 'False'"
        m_addSys=False
    if not m_addShapeSys:
        print "addShapeSys not set -> using default: 'False'"
        m_addShapeSys=False
    if not m_fixSys:
        print "fixSys not set      -> using default: 'NO'"
        m_fixSys="NO"
    if not m_doFit:
        print "doFit not set       -> using default: 'False'"
        m_doFit=False
    if not m_do2D:
        print "do2D not set        -> using default: 'False'"
        m_do2D=False
    if not m_useData:
        print "usedata not set     -> using default: 'False'"
        m_useData=False
    if not m_debug:
        m_debug=False
    if not m_verbose:
        m_verbose=False

    print "-------------------------------------------------"
    print ""
    print "  Options set: "
    print "runType     = "+m_runType
    print "Variable    = "+str(m_Variable)
    print "addSys      = "+str(m_addSys)
    print "addShapeSys = "+str(m_addShapeSys)
    print "fixSys      = "+str(m_fixSys)
    print "doFit       = "+str(m_doFit)
    print "do2D        = "+str(m_do2D)
    print "useData     = "+str(m_useData)
    print "debug       = "+str(m_debug)
    print "verbose     = "+str(m_verbose)
    print "-------------------------------------------------"

    if m_runType=="SysBands":
        CreateSysBands(m_debug,m_verbose)
        
    elif m_runType=="AllExpected":
        m_useData=False
        RunAll(m_useData,m_addSys,False,m_debug,m_verbose)
        
    elif m_runType=="AllObserved":
        m_useData=True
        RunAll(m_useData,m_addSys,False,m_debug,m_verbose)

    elif m_runType=="AllObsFixSys":
        RunAll(True,True,True,m_debug,m_verbose)
        
    elif m_runType=="Expected":
        m_useData=False
        RunSingle(m_Variable,m_useData,m_addSys,m_fixSys,m_debug,m_verbose)
        
    elif m_runType=="Observed":
        m_useData=True
        RunSingle(m_Variable,m_useData,m_addSys,m_fixSys,m_debug,m_verbose)

    elif m_runType=="ObsFixSys":
        m_useData=True
        m_addSys=True
        RunSingle(m_Variable,m_useData,m_addSys,m_fixSys,m_debug,m_verbose)
        
    elif m_runType=="SingleRun":
        RunWithOptions(m_Variable,m_useData,m_doFit,m_do2D,m_addSys,
                       m_addShapeSys,m_fixSys,m_debug,m_verbose)


def CreateSysBands(debug,verbose):

    Vars = CreateVarsVector("all",True)

    for v in Vars:
        
        cmd = "./WorkSpaceMaker --addSys --sysBands"
        
        if v.find("Fid")!=-1:
            cmd += " --FidChan"
        else:
            cmd += " --Variable "+v

        if v.find("Fid")!=-1 or v.find("njet")!=-1 or v.find("nbjet")!=-1:
            cmd += " --addShapeSys"

        if debug:
            cmd += " --debug"

        if verbose:
            cmd += " --verbose"

        print cmd
        os.system(cmd)


def RunAll(useData,addSys,fixSys,debug,verbose):

    Vars = CreateVarsVector("all",False)
    Sys  = CreateSysVector(" ")

    for v in Vars:
        
        cmd = "./WorkSpaceMaker --doFit"

        if v.find("Fid")==-1 and v.find("m12")==-1 and v.find("m34")==-1:
            cmd += " --do2D"

        if useData:
            cmd += " --WithData"

        if v.find("Fid")!=-1:
            cmd += " --"+v
        else:
            cmd += " --Variable "+v

        if addSys:
            cmd += " --addSys"
            if v.find("Fid")!=-1 or  v.find("njet")!=-1 or v.find("nbjet")!=-1:
                cmd += " --addShapeSys"

        if debug:
            cmd += " --debug"

        if verbose:
            cmd += " --verbose"

        if fixSys:

            for s in Sys:
                cmdSys = cmd+" --fixSys "+s
                print cmdSys
                os.system(cmdSys)

        else:
                
            print cmd
            os.system(cmd)

        
def RunSingle(var,useData,addSys,fixSys,debug,verbose):

    Vars = CreateVarsVector(var,False)
    Sys  = CreateSysVector(fixSys)


    for v in Vars:

        cmd = "./WorkSpaceMaker --doFit"

        if v.find("Fid")==-1 and v.find("m12")==-1 and v.find("m34")==-1:
            cmd += " --do2D"

        if useData:
            cmd += " --WithData"

        if v.find("Fid")!=-1:
            cmd += " --"+v
        else:
            cmd += " --Variable "+v

        if addSys:
            cmd += " --addSys"
            if v.find("Fid")!=-1 or v.find("njet")!=-1 or v.find("nbjet")!=-1:
                cmd += " --addShapeSys"

        if debug:
            cmd += " --debug"

        if verbose:
            cmd += " --verbose"

        if len(Sys)!=0:
            for s in Sys:
                cmdSys = cmd+" --fixSys "+s
                print cmdSys
                os.system(cmdSys)
        else:
            print cmd
            os.system(cmd)

    
def RunWithOptions(var,useData,doFit,do2D,addSys,addShapeSys,fixSys,debug,verbose):

    cmd = "./WorkSpaceMaker"

    if var.find("Fid")!=-1:
        cmd += " --"+var
    else:
        cmd += " --Variable "+var

    if useData:
        cmd += " --WithData"

    if doFit:
        cmd += " --doFit"

    if do2D:
        cmd += " --do2D"

    if addSys:
        cmd += " --addSys"

    if addShapeSys:
        cmd += " --addShapeSys"

    if fixSys!="NO":
        cmd += " --fixSys "+fixSys

    if debug:
        cmd += " --debug"

    if verbose:
        cmd += " --verbose"

    print cmd
    os.system(cmd)


def CreateVarsVector(var,sysBands):

    Vars = []
    
    if var=="all":
        Vars.append( "pt"       )
        Vars.append( "cts"      )
        Vars.append( "y"        )
        Vars.append( "m12"      )
        Vars.append( "m34",     )
        Vars.append( "njet"     )
        Vars.append( "njetv2"   )
        Vars.append( "njetv3"   )
        Vars.append( "nbjet"    )
        Vars.append( "ljpt"     )
        Vars.append( "mjj"      )
        Vars.append( "etajj"    )
        Vars.append( "phijj"    )
        Vars.append( "ptpt"     )
        Vars.append( "m12m34"   )
        Vars.append( "FidChan"  )
        if not sysBands:
            Vars.append( "Fid2l2l"  )
            Vars.append( "Fid4l"    )
            Vars.append( "FidSum"   )
            Vars.append( "FidComb"  )
            Vars.append( "FidTotal" )
    else:
        Vars.append(var)

    return Vars

def CreateSysVector(fixSys):

    Sys = []
    
    if fixSys==" ":
        Sys.append("NO")
        Sys.append("all")
        Sys.append("muon")
        Sys.append("electron")
        Sys.append("jet")
        Sys.append("ZZ")
        Sys.append("zjet")
        Sys.append("sig")
        Sys.append("lumi")
    else:
        if fixSys!="NO":
            Sys.append(fixSys)

    return Sys
        
def ShowDoc():
    print ""
    print "Script to run WorkSpaceMaker code!"
    print "  Usage : ./RunFit.py [Options]!"
    print "          Options:  "
    print "                   runType=SysBands     : default is 'SingleRun'        "
    print "                                          Choices are = 'AllExpected',  "
    print "                                          'AllObserved', 'AllObsFixSys',"
    print "                                          'SysBands', 'Expected',       "
    print "                                          'Observed', 'ObsFixSys'       "
    print "                                          'SingleRun'                   "
    print "                   Variable=pt          : default is ' '                "
    print "                   addSys=[True/False]  : default is 'False'            "
    print "                   doFit=[True/False]   : default is 'False'            "
    print "                   do2D=[True/False]    : default is 'False'            "
    print "                   useData=[True/False] : default is 'False'            "
    print "                   fixSys=all           : default is 'NO'               "
    print "                   debug=[True/False]   : default is 'False'            "
    print "                   verbose=[True/False] : default is 'False'            "

if __name__ == "__main__":
    main()
