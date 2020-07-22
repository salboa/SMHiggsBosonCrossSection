#!/usr/bin/python
import os
import sys
import subprocess
import getopt
import string
import argparse
import time
import shlex

parser = argparse.ArgumentParser()
parser.add_argument("--runType"     , type=str           , default='SingleRun', help="specify run type: default is 'SingleRun'."+
                    " Options are: 'AllExpected', 'AllObserved', 'AllObsFixSys', 'SysBands', 'Expected', 'Observed', 'ObsFixSys',"+
                    " 'SingleRun','makeXsecAll'"                                                                                            )
parser.add_argument("--variable"    , type=str           , default=''   , help="specify variable'"                                          )
parser.add_argument("--addSys"      , action='store_true', default=False, help="enable systematic uncertainties: default is 'False'"        )
parser.add_argument("--addShapeSys" , action='store_true', default=False, help="enable shape systematic uncertainties: default is 'False'"  )
parser.add_argument("--mcVersion"   , type=int           , default=1    , help="specify mc Version: default is '0' (mc16)"                  )
parser.add_argument("--doFit"       , action='store_true', default=False, help="enable doing xsec fit: default is 'False'"                  )
parser.add_argument("--do2D"        , action='store_true', default=False, help="enable using m4l information: default is 'False'"           )
parser.add_argument("--useData"     , action='store_true', default=False, help="enable using data: default is 'False'"                      )
parser.add_argument("--fixSys"      , type=str           , default='NO' , help="specify which sys block to fix: default is 'NO'"            )
parser.add_argument("--useCFsplit"  , action='store_true', default=False, help="enable cF splitting with nonFid: default is 'False'"        )
parser.add_argument("--useBornLep"  , action='store_true', default=False, help="enable using Born Leptons: default is 'False'"              )
parser.add_argument("--uselxbatch"  , action='store_true', default=False, help="enable sending jobs on lxbatch: default is 'False'"         )
parser.add_argument("--queue"       , type=str           , default='8nh', help="specify lxbatch queue: default is '8nh'"                    )
parser.add_argument("--debug"       , action='store_true', default=False, help="enable debug mode"                                          )
parser.add_argument("--verbose"     , action='store_true', default=False, help="enable verbose mode"                                        )
parser.add_argument("--maxProcesses", type=int           , default=4    , help="specify number of simultaneous processes: default is '4'"   )
parser.add_argument("--logsDir"     , type=str           , default='log', help="specify logs store directory: default is 'log'"             )
args = parser.parse_args()

def main():

    if args.variable=='':
        if args.runType=='SingleRun' or args.runType=='Expected' or args.runType=='Observed' or args.runType=='ObsFixSys':
            print "runType = "+args.runType+" and variable not defined -> please choose one variable!"
            exit(0)

    if args.verbose:
        args.debug = True

    if args.runType=='SysBands':
        CreateSysBands()

    elif args.runType=='AllExpected':
        args.useData=False
        RunAll(args.useData,args.addSys,False)
        
    elif args.runType=='AllObserved':
        args.useData=True
        RunAll(args.useData,args.addSys,False)
            
    elif args.runType=='AllObsFixSys':
        RunAll(True,True,True)
        
    elif args.runType=='Expected':
        args.useData=False
        RunSingle(args.variable,args.useData,args.addSys,args.fixSys)
        
    elif args.runType=='Observed':
        args.useData=True
        RunSingle(args.variable,args.useData,args.addSys,args.fixSys)

    elif args.runType=='ObsFixSys':
        args.useData=True
        args.addSys=True
        RunSingle(args.variable,args.useData,args.addSys,args.fixSys)
        
    elif args.runType=='SingleRun':
        RunWithOptions(args.variable,args.useData,args.doFit,args.do2D,args.addSys,
                       args.addShapeSys,args.fixSys)
    elif args.runType=='makeXsecAll':
	RunXsecAll()


def WriteFile(dir,name,command):

    f = open(dir+'/'+name,'w')
    f.write('#!/bin/bash \n')
    f.write('cd '+os.getcwd()+'\n')
    f.write('setupATLAS \n')
    f.write('lsetup  "root 6.08.06-HiggsComb-x86_64-slc6-gcc49-opt" \n')
    f.write(os.getcwd()+'/'+command+' \n')
    
    
def CreateSysBands():

    Vars = CreateVarsVector("all",True)

    for v in Vars:
        
        cmd = "./WorkSpaceMaker --addSys --sysBands"
        
        if v.find("Fid")!=-1:
            cmd += " --fidChan"
        else:
            cmd += " --variable "+v

        if v.find("Fid")!=-1 or v.find("njet")!=-1 or v.find("nbjet")!=-1:
            cmd += " --addShapeSys"

        if args.debug:
            cmd += " --debug"

        if args.verbose:
            cmd += " --verbose"

        if args.useBornLep:
            cmd += " --useBornLep"

        if args.useCFsplit:
            cmd += " --doCFsplit"

        cmd += " --mcVersion "+str(args.mcVersion)
        
        print cmd
        os.system(cmd)


def RunAll(useData,addSys,fixSys):

    Vars = CreateVarsVector("all",False)
    Sys  = CreateSysVector(" ")

    for v in Vars:
        
        cmd = "./WorkSpaceMaker --doFit"

        if v.find("Fid")==-1 and v.find("m12")==-1 and v.find("m34")==-1:
            cmd += " --do2D"

        if useData:
            cmd += " --withData"

        if v.find("Fid")!=-1:
            cmd += " --"+v
        else:
            cmd += " --variable "+v

        if addSys:
            cmd += " --addSys"
            if v.find("Fid")!=-1 or  v.find("njet")!=-1 or v.find("nbjet")!=-1:
                cmd += " --addShapeSys"

        if args.debug:
            cmd += " --debug"

        if args.verbose:
            cmd += " --verbose"

        if args.useBornLep:
            cmd += " --useBornLep"

        if args.useCFsplit:
            cmd += " --doCFsplit"

        cmd += " --mcVersion "+str(args.mcVersion)

        if args.uselxbatch:
            if not os.path.exists("../LSFjobs"):
                os.makedirs("../LSFjobs")

        if fixSys:

            for s in Sys:
                cmdSys = cmd+" --fixSys "+s
                print cmdSys
                if args.uselxbatch:
                    name = v+s+".sh"
                    WriteFile("../LSFjobs",name,cmdSys)
                    print "Submitting job to batch "+name
                    os.system("chmod +x ../LSFjobs/*")
	            os.system("sleep 2")
		    os.system("bsub -q "+args.queue+" "+os.getcwd()+"/../LSFjobs/"+name)
                else:
                    os.system(cmdSys)

        else:
                
            print cmd
            if args.uselxbatch:
                name = v+".sh"
                WriteFile("../LSFjobs",name,cmd)
                print "Submitting job to batch "+name
                os.system("chmod +x ../LSFjobs/*")
	        os.system("sleep 2")
		os.system("bsub -q "+args.queue+" "+os.getcwd()+"/../LSFjobs/"+name)
            else:
                os.system(cmd)

        
def RunSingle(var,useData,addSys,fixSys):

    Vars = CreateVarsVector(var,False)
    Sys  = CreateSysVector(fixSys)


    for v in Vars:

        cmd = "./WorkSpaceMaker --doFit"

        if v.find("Fid")==-1 and v.find("m12")==-1 and v.find("m34")==-1:
            cmd += " --do2D"

        if useData:
            cmd += " --withData"

        if v.find("Fid")!=-1:
            cmd += " --"+v
        else:
            cmd += " --variable "+v

        if addSys:
            cmd += " --addSys"
            if v.find("Fid")!=-1 or v.find("njet")!=-1 or v.find("nbjet")!=-1:
                cmd += " --addShapeSys"

        if args.debug:
            cmd += " --debug"

        if args.verbose:
            cmd += " --verbose"

        if args.useBornLep:
            cmd += " --useBornLep"

        if args.useCFsplit:
            cmd += " --doCFsplit"

        cmd += " --mcVersion "+str(args.mcVersion)

        if args.uselxbatch:
            if not os.path.exists("../LSFjobs"):
                os.makedirs("../LSFjobs")

        if len(Sys)!=0:
            for s in Sys:
                cmdSys = cmd+" --fixSys "+s
                print cmdSys
                if args.uselxbatch:
                    name = v+s+".sh"
                    WriteFile("../LSFjobs",name,cmdSys)
                    print "Submitting job to batch "+name
                    os.system("chmod +x ../LSFjobs/*")
	            os.system("sleep 2")
		    os.system("bsub -q "+args.queue+" "+os.getcwd()+"/../LSFjobs/"+name)
                else:
                    os.system(cmdSys)
        else:
            print cmd
            if args.uselxbatch:
                name = v+".sh"
                WriteFile("../LSFjobs",name,cmd)
                print "Submitting job to batch "+name
                os.system("chmod +x ../LSFjobs/*")
	        os.system("sleep 2")
		os.system("bsub -q "+args.queue+" "+os.getcwd()+"/../LSFjobs/"+name)
            else:
                os.system(cmd)

    
def RunWithOptions(var,useData,doFit,do2D,addSys,addShapeSys,fixSys):

    cmd = "./WorkSpaceMaker"

    if var.find("Fid")!=-1:
        cmd += " --"+var
    else:
        cmd += " --variable "+var

    if useData:
        cmd += " --withData"

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

    if args.debug:
        cmd += " --debug"

    if args.verbose:
        cmd += " --verbose"

    if args.useBornLep:
        cmd += " --useBornLep"

    if args.useCFsplit:
        cmd += " --doCFsplit"

    cmd += " --mcVersion "+str(args.mcVersion)

    if args.uselxbatch:
        if not os.path.exists("../LSFjobs"):
            os.makedirs("../LSFjobs")

    print cmd
    if args.uselxbatch:
        name = var+".sh"
        WriteFile("../LSFjobs",name,cmd)
        print "Submitting job to batch "+name
        os.system("chmod +x ../LSFjobs/*")
	os.system("sleep 2")
	os.system("bsub -q "+args.queue+" "+os.getcwd()+"/../LSFjobs/"+name)
    else:
        os.system(cmd)


def CreateVarsVector(var,sysBands):

    Vars = []
    
    if var=="all":
        Vars.append( "pt"       )
        Vars.append( "cts"      )
#        Vars.append( "ct1"      )
#        Vars.append( "ct2"      )
        Vars.append( "y"        )
        Vars.append( "m12"      )
        Vars.append( "m34",     )
        #Vars.append( "phi1"     )
        #Vars.append( "phi2"     )
        Vars.append( "njet"     )
        #Vars.append( "njetv2"   )
        #Vars.append( "njetv3"   )
        Vars.append( "nbjet"    )
        Vars.append( "ljpt"     )
        Vars.append( "mjj"      )
        Vars.append( "etajj"    )
        Vars.append( "phijj"    )
        Vars.append( "ptnjet"   )
        #Vars.append( "pty"      )
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


########################################################################################

def CreatediffVarsVector():

    Vars = []

    Vars.append( "pt"       )
    Vars.append( "cts"      )
#    Vars.append( "ct1"      )
#    Vars.append( "ct2"      )
    Vars.append( "y"        )
    Vars.append( "m12"      )
    Vars.append( "m34"      )
    #Vars.append( "phi1"     )
    #Vars.append( "phi2"     )
    Vars.append( "njet"     )
    #Vars.append( "njetv2"   )
    #Vars.append( "njetv3"   )
    Vars.append( "nbjet"    )
    Vars.append( "ljpt"     )
    Vars.append( "mjj"      )
    Vars.append( "etajj"    )
    Vars.append( "phijj"    )
    Vars.append( "ptnjet"   )
    #Vars.append( "pty"      )
    Vars.append( "m12m34"   )
    #Vars.append( "FidChan"  )

    return Vars

def CreatediffChVector(v):

    Ch = []
    
    Ch.append( "incl"      )
    #Ch.append( "4mu"      )
    #Ch.append( "4e"       )
    #Ch.append( "2mu2e"    )
    #Ch.append( "2e2mu "    )
    if v == "m12" or v =="m34" or v=="m12m34":
      Ch.append( "2l2l"     )
      Ch.append( "4l"       )
   
    return Ch

def CreatedfloatqqZZVector():

    v = []
    
    v.append( ""                 )
    v.append( "--floatqqZZ "      )

    return v

def CreateMatrixVector():

    v = []
    
    v.append( "--prodMode MergProd"               )
    v.append( "--doMatrix --prodMode AllSig"      )

    return v

def CreateLepTypeVector():

    v = []
    
    v.append( ""                 )
    v.append( "--useBornLep "      )

    return v

def CreateSysVector():

    v = []
    
    v.append( ""                 )
    v.append( "--addSys "      )

    return v


def GetCommand(v, c, qq, u, l, s):

    cmd  = "./WorkSpaceMaker "
    cmd += "--variable "+v+" "
    cmd += "--channel " +c+" "
    cmd += qq+" "
    cmd += u+" "
    cmd += l+" "
    cmd += " --doFit"+" "
    cmd += " --do2D"+" "
    cmd += " --bkgOption ZZ"+" "
    cmd += s+" "

    return cmd
    

def RunXsecAll():

    #check if directory where logs are store exists, if it doesn't create it
    createlogDir = False
    if not os.path.exists(args.logsDir):
        os.makedirs(args.logsDir)
        logsDir = True
    os.system(str("rm "+args.logsDir+"/*"))
    var = CreatediffVarsVector();
    qqZZ= CreatedfloatqqZZVector();
    unf = CreateMatrixVector();
    lep = CreateLepTypeVector();
    sys = CreateSysVector();

    #Create the list of input commands
    commandList = []
    processes = set()
    for v in var:
       ch  = CreatediffChVector(v);
       for c in ch:
          for qq in qqZZ:
             for u in unf:
		for l in lep:
		   for s in sys:
   		      commandList.append(GetCommand(v,c,qq,u,l,s))

    i=0
    for command in commandList:
        print 'Running ', command
        i = i + 1
        if(i%args.maxProcesses == 0):
            precentDone = float(i)/len(commandList) * 100
            print 'Running command #: ', i, ' percentage submitted: ' , float("{0:.1f}".format(precentDone))
            pass

        #get the aguments
        arguments = shlex.split(command)
        logFile = args.logsDir+'/logfile_'+str(i)+".dat"
        w = open(logFile,'w')
        
        processes.add(subprocess.Popen(arguments, stdout=w, stderr=w))
        if len(processes) >= args.maxProcesses:
            os.wait()
            processes.difference_update([p for p in processes if p.poll() is not None])


        
if __name__ == "__main__":
    main()
