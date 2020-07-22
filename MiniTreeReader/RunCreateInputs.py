#!/usr/bin/python3
import os
import sys
import subprocess
import getopt
import string
import argparse
import time
import shlex

parser = argparse.ArgumentParser(description='Submit jobs to create all needed inputs for H (ZZ->4l) xsec measurents')
parser.add_argument("--process"        , type=str           , default=''    , help="specify the process to be processed: default is '' (auto)"  )
parser.add_argument("--nBins"          , type=int           , default=30    , help="specify number of m4l bins: default is '30'"                )
parser.add_argument("--mMin"           , type=float         , default=-1    , help="specify lowest m4l value: default is '-1'"                  )
parser.add_argument("--mMax"           , type=float         , default=-1    , help="specify highest m4l value: default is '-1'"                 )
parser.add_argument("--sysNum"         , type=int           , default=0     , help="specify sys number: default '0' (nominal). "+
                    "Options are: -1=all, 0=Nominal, 1003=Normalization_Set1, 1005=Normalization_Set1, 1009=Shape_Set1, 1011=Shape_Set1, "+
                    "1013=Shape_Set3, 1021=SigTheoryScale_Set1, 1023=SigTheoryScale_Set1, 1025=SigTheoryScale_Set1, 1029=SigTheoryPdf_Set1, "+
                    "1031=SigTheoryPdf_Set2, 1033=SigTheoryPdf_Set3, 1035=SigTheoryPdf_Set4, 1039=SigTheoryQcd_Set1, 1041=SigTheoryQcd_Set2, "+
                    "1043=SigTheoryQcd_Set3, 1047=SigTheoryShower_Set1, 1049=SigTheoryShower_Set2, 1051=SigTheoryShower_Set3, "+
                    "1053=SigHerwigShower, 1055=SigComposition, 1057=SigMassShape, 1061=qqZZTheory_Set1, 1063=qqZZTheory_Set2, 1071=Zjets"      )
parser.add_argument("--mcType"         , type=int           , default=0     , help="specify mc version: default is '0' (all). "+
                    "Options are: 0=all, 1=mc15c, 2=mc16a, 3=mc16d, 4=mc16e"                                                                    )
parser.add_argument("--doShiftUp"      , action='store_true', default=False , help="enable Higgs mass shift up: default is 'False'"             )
parser.add_argument("--doShiftDown"    , action='store_true', default=False , help="enable Higgs mass shift down: default is 'False'"           )
parser.add_argument("--isContrReg"     , action='store_true', default=False , help="enable control region mode: default is 'False'"             )
parser.add_argument("--isCouplings"    , action='store_true', default=False , help="enable coupling mode: default is 'False'"                   )
parser.add_argument("--doACRfactor"    , action='store_true', default=False , help="enable A, C and R calculation: default is 'False'"          )
parser.add_argument("--useMtxMode"     , action='store_true', default=False , help="enable matrix inversion mode: default is 'False'"           )
parser.add_argument("--splitCF"        , action='store_true', default=False , help="enable cF splitting in non fid part: default is 'False'"    )
parser.add_argument("--useRootThMtc"   , action='store_true', default=False , help="enable ROOT Truth Matching: default is 'False'"             )
parser.add_argument("--restrictJets"   , action='store_true', default=False , help="enable restrict jet kinematic: default is 'False'"          )
parser.add_argument("--checkDuplicates", action='store_true', default=False , help="enable check of duplicates events: default is 'False'"      )
parser.add_argument("--makeXsecAll"    , action='store_true', default=False , help="enable making all needed inputs: default is 'False'"        )
parser.add_argument("--makeXsecRest"   , action='store_true', default=False , help="enable making additional inputs: defaults i 'False'"        )
parser.add_argument("--mergeFiles"     , action='store_true', default=False , help="enable merging sys files: default is 'False'"               )
parser.add_argument("--maxProcesses"   , type=int           , default=4     , help="specify number of simultaneous processes: default is '4'"   )
parser.add_argument("--addProdModes"   , action='store_true', default=False , help="enable adding single prod modes: deafult is 'False'"        )
parser.add_argument("--excludeNominal" , action='store_true', default=False , help="enable excluding nominal: default is 'False'"               )
parser.add_argument("--excludeCommon"  , action='store_true', default=False , help="enable excluding common sys: default is 'False'"            )
parser.add_argument("--excludeMerging" , action='store_true', default=False , help="enable excluding roof file merging: default is 'False'"     )
parser.add_argument("--logsDir"        , type=str           , default='logs', help="specify logs store directory: default is 'logs'"            )
parser.add_argument("--unfoldType"     , type=int           , default=0     , help="specify the unfolding type: default is '0' (cF+matrix). "+
                    "Options are: 0 = cF+matrix, 1 = cF only, 2 = maxtrix only"                                                                 )
parser.add_argument("--debug"          , action='store_true', default=False , help="enable debug mode"                                          )
args = parser.parse_args()

# global map
mcType = {}
mcType[0] = 'mc16'
mcType[1] = 'mc15c'
mcType[2] = 'mc16a'
mcType[3] = 'mc16d'
mcType[4] = 'mc16e'

def main():

    if args.mMin==-1 and args.mMax==-1:
        print( "Min and Max values not defined! setting them according to nBins "+str(args.nBins) )
        if args.nBins==30:
            args.mMin = 115.0
            args.mMax = 130.0
        elif args.nBins==110:
            args.mMin = 105.0
            args.mMax = 160.0

    print("-------------------------------------------------" )
    print( " Calling CreateInputs with following options:    " )   
    
    if args.makeXsecAll:
        print( "makeXsecAll  = ", args.makeXsecAll )
        print( "   ---> making all inputs for Xsec Measurements! settings:" )
        print( "        Nbins           = ", args.nBins )
        print( "        Min             = ", args.mMin )
        print( "        Max             = ", args.mMax )
        print( "        mcType          = ", args.mcType )
        print( "        restrictJets    = ", args.restrictJets )
        print( "        checkDuplicates = ", args.checkDuplicates )
        print( "        maxProcesses    = ", args.maxProcesses )
        print( "        logsDir         = ", args.logsDir )
        print( "        unfoldType      = ", args.unfoldType )
    elif args.mergeFiles:
        print( "mergeFiles  = ", args.makeXsecAll )
        print( "   ---> merging sys files for Xsec Measurements! settings:" )
        print( "        Nbins           = ", args.nBins )
        print( "        mcType          = ", args.mcType )
        print( "        unfoldType      = ", args.unfoldType )
    elif args.makeXsecRest:
        print( "makeXsecRest  = ", args.makeXsecRest )
        print( "   ---> making additional inputs for Xsec Measurements! settings:" )
        print( "        Nbins           = ", args.nBins )
        print( "        Min             = ", args.mMin )
        print( "        Max             = ", args.mMax )
        print( "        mcType          = ", args.mcType )
        print( "        restrictJets    = ", args.restrictJets )
        print( "        checkDuplicates = ", args.checkDuplicates )
        print( "        maxProcesses    = ", args.maxProcesses )
        print( "        logsDir         = ", args.logsDir )
        print( "        unfoldType      = ", args.unfoldType )
    else:
        if args.process=='':
            print( "Process         = all processes" )
        else:
            print( "Process         = ", args.process )
        print( "Nbins           = ", args.nBins )
        print( "Min             = ", args.mMin )
        print( "Max             = ", args.mMax )
        print( "sysNum          = ", args.sysNum )
        print( "mcType          = ", args.mcType )
        print( "doShiftUp       = ", args.doShiftUp )
        print( "doShiftDown     = ", args.doShiftDown )
        print( "isControlReg    = ", args.isContrReg )
        print( "isCouplings     = ", args.isCouplings )
        print( "doACRfactor     = ", args.doACRfactor )
        print( "useMtxMode      = ", args.useMtxMode )
        print( "splitCF         = ", args.splitCF )
        print( "useRootThMtc    = ", args.useRootThMtc )
        print( "restrictJets    = ", args.restrictJets )
        print( "checkDuplicates = ", args.checkDuplicates )
        print( "debug           = ", args.debug )
    print( "-------------------------------------------------" )
    print( "" )

    if args.makeXsecAll or args.makeXsecRest:
        SubmitXsecJobs()
    #    RunXsecAll()
    #elif 
    #    RunXsecRest()
    elif args.mergeFiles:
        MergeFiles()
    else:
        RunWithOptions()


def GetListOfCommands():

    commandList = []
    if args.makeXsecAll:

        #Get List of Sytematics and Processes
        SysAndProcess = GetListOfSysAndProcess()
    
        #Create the list of input commands
        for sys in SysAndProcess:
            for a in sys:
                for s in sys[a]['procs']:
                    isMtx = sys[a]['isMatrix']
                    isCF  = sys[a]['isCF']
                    commandList.append(GetCommand(a,s,isMtx,isCF))
                    if a==0:
                        if args.unfoldType==0 or args.unfoldType==1:
                            commandList.append(GetCommand(a,s)+" --doACRfactor")
                        if args.unfoldType==0 or args.unfoldType==2:
                            commandList.append(GetCommand(a,s)+" --useMtxMode")
                        
    elif args.makeXsecRest:
        
        mcTypes     = []
    
        if args.mcType==-1:
            mcTypes.extend([2,3,4])
        else:
            mcTypes.extend([args.mcType])

        if args.nBins==30:
            mcTypes.extend([0])

        for mc in mcTypes:
            commandList.append( GetCommand(0,'',False,False,mc) )
            if args.unfoldType==0 or args.unfoldType==1:
                commandList.append( GetCommand(0,'',False,True,mc) )
            if args.unfoldType==0 or args.unfoldType==2:
                commandList.append( GetCommand(0,'',True,False,mc) )
    else:
        
        print("Invalid options!! Neither makeXsecAll or makeXsecRest option enabled, exiting!")
        exit(0)
    
    return commandList


def SubmitXsecJobs():

    #check if directory where logs are store exists, if it doesn't create it
    if not os.path.exists(args.logsDir):
        os.makedirs(args.logsDir)
        
    commandList = GetListOfCommands()
    processes = set()
    
    i=0
    print( 'Total number of jobs to be submitted: ', len(commandList), 'with max process: ',args.maxProcesses )

    for command in commandList:
        print('Running ', command)
        i = i + 1
        if i%args.maxProcesses == 0:
            percentDone = float(i)/len(commandList) * 100
            print('Running command #: ', i, ' percentage submitted: ' , float("{0:.1f}".format(percentDone)) )
            pass

        #get the aguments
        arguments = shlex.split(command)
        logFile = args.logsDir+'/logfile_'+str(i)+".log"
        w = open(logFile,'w')
        
        processes.add(subprocess.Popen(arguments, stdout=w, stderr=w))
        if len(processes) >= args.maxProcesses:
            os.wait()
            processes.difference_update([p for p in processes if p.poll() is not None])

    jobs = processes
    while len(jobs) > 0:
        jobs = [job for job in jobs if job.poll() is None]
        time.sleep(1)

    if args.makeXsecAll:
        #wait 10s before merging files
        time.sleep(10)
        if not args.excludeMerging:
            MergeFiles()

        
def MergeFiles():

    #Create the list of input commands
    commandList = []
    processes = set()

    if args.unfoldType==0 or args.unfoldType==1:
        commandList.append(GetMergeCommand(0,False))
    if args.unfoldType==0 or args.unfoldType==2:
        commandList.append(GetMergeCommand(0,True))
    commandList.append(GetMergeCommand(1,False))

    for command in commandList:
        print( 'Running ', command )
        print( "" )
        os.system(command)
        print( "" )

        
def RunWithOptions():
    
    #Process Definition:
    Samples = GetListOfSamples(args.process)
    print( "Processing Samples = ", Samples )
    
    os.getenv('DYLD_LIBRARY_PATH')

    for sample in Samples:

        cmd  = "./CreateInputs --Process "+sample+" --nBins "+str(args.nBins)
        cmd += " --Min "+str(args.mMin)+" --Max "+str(args.mMax)
        cmd += " --sysNumber "+str(args.sysNum)
        cmd += " --mcType "+str(args.mcType)
        if args.debug:
            cmd += " --debug"
        if args.doShiftUp:
            cmd += " --doShiftUp"
        if args.doShiftDown:
            cmd += " --doShiftDown"
        if args.isCouplings:
            cmd += " --isCouplings"
        if args.isContrReg:
            cmd += " --isControlReg"
        if args.doACRfactor:
            cmd += " --doACRfactor"
        if args.useMtxMode:
            cmd += " --useMtxMode"
        if args.splitCF:
            cmd += " --split_cF"
        if args.useRootThMtc:
            cmd += " --useRootThMtc"
        if args.restrictJets:
            cmd += " --restrictJets"
        if args.checkDuplicates:
            cmd += " --checkDuplicates"

        os.system(cmd)

        
def GetListOfSamples(process):

    samples = []
    if process!='':
        samples.append(process)
        return samples
    
    samples.append( "ggH"    )
    samples.append( "VBF"    )
    samples.append( "WH"     )
    samples.append( "ZH"     )
    samples.append( "ttH"    )
    samples.append( "bbH"    )
    samples.append( "ggHbbH" )
    samples.append( "VH"     )
    samples.append( "AllSig" )

    if not (args.doShiftUp or args.doShiftDown or args.doACRfactor or args.useMtxMode):

        samples.append( "qqZZ" ) 
        samples.append( "ggZZ" )
                
        if args.sysNum==0:
            samples.append( "AllZZ"     )
            samples.append( "ZZEW"      )
            samples.append( "Zjets"     )
            samples.append( "MultiBoson")
            samples.append( "data"      )
            samples.append( "redBkg"    )
            
            #"MG5","MG5KHvv", "MG5KAvv", "MG5KAgg",
       
    return samples


def GetListOfSysAndProcess():

    sysVec = []

    if not args.excludeNominal:
        sysVec.append( GetListOfJobsNominal() )

    if args.unfoldType==0:
        sysVec.append( GetListOfJobsForMatrix() )
        sysVec.append( GetListOfJobsForCorrFact() )
    elif args.unfoldType==1:
        sysVec.append( GetListOfJobsForCorrFact() )
    elif args.unfoldType==2:
        sysVec.append( GetListOfJobsForMatrix() )

    if not args.excludeCommon:
        sysVec.append( GetListOfCommonJobs() )

    return sysVec


def GetListOfJobsNominal():

    sysVec = {}
    sysVec[0] = {'procs': [''], 'isMatrix': False, 'isCF': False}
    
    return sysVec


def GetListOfJobsForMatrix():

    sysVec = {}
    #sysVec[1003] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1005] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1009] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1011] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1013] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1021] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1023] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1025] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1029] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1031] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1033] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1035] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1039] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1041] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    sysVec[1043] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1047] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1049] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1051] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1053] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}
    #sysVec[1055] = {'procs': ['AllSig'], 'isMatrix': True , 'isCF': False}

    return sysVec


def GetListOfJobsForCorrFact():

    sysVec = {}
    #sysVec[1003] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': False}
    #sysVec[1005] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': False}
    #sysVec[1009] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': False}
    #sysVec[1011] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': False}
    #sysVec[1013] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': False}
    #sysVec[1021] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1023] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1025] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1029] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1031] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1033] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1035] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1039] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1041] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    sysVec[1043] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1047] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1049] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1051] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1053] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }
    #sysVec[1055] = {'procs': ['AllSig'], 'isMatrix': False, 'isCF': True }

    if args.addProdModes:
        sysVec[1003]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1005]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1009]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1011]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1013]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1021]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1023]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1025]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1029]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1031]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1033]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1035]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1039]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1041]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1043]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1047]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1049]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1051]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        sysVec[1053]['procs'].extend(['ggHbbH', 'VBF', 'VH', 'ttH'])
        
    return sysVec


def GetListOfCommonJobs():

    sysVec = {}
    sysVec[1003] = {'procs': ['qqZZ','ggZZ']          , 'isMatrix': False, 'isCF': False}
    sysVec[1005] = {'procs': ['qqZZ','ggZZ']          , 'isMatrix': False, 'isCF': False}
    sysVec[1009] = {'procs': ['qqZZ','ggZZ']          , 'isMatrix': False, 'isCF': False}
    sysVec[1011] = {'procs': ['qqZZ','ggZZ']          , 'isMatrix': False, 'isCF': False}
    sysVec[1013] = {'procs': ['qqZZ','ggZZ']          , 'isMatrix': False, 'isCF': False}
    sysVec[1057] = {'procs': ['AllSig']               , 'isMatrix': False, 'isCF': False}
    sysVec[1061] = {'procs': ['qqZZ']                 , 'isMatrix': False, 'isCF': False}
    sysVec[1063] = {'procs': ['qqZZ']                 , 'isMatrix': False, 'isCF': False}
    sysVec[1071] = {'procs': ['Zjets', 'MultiBoson',
                              'redBkg']               , 'isMatrix': False, 'isCF': False}

    return sysVec


def GetCommand(sysNum, proc, isMatrix=False, isCF=False, mcType=args.mcType):

    cmd  = "python RunCreateInputs.py --mcType "+str(mcType)
    cmd += " --nBins "+str(args.nBins)+" --mMin "+str(args.mMin)
    cmd += " --mMax "+str(args.mMax)+" --sysNum "+str(sysNum)
    if args.restrictJets:
        cmd += " --restrictJets"
    if args.checkDuplicates:
        cmd += " --checkDuplicates"
    if proc!='':
        cmd += " --process "+str(proc)
    if isMatrix:
        cmd += " --useMtxMode"
    if isCF:
        cmd += " --doACRfactor"
    if args.debug:
        cmd += " --debug"

    return cmd


def GetMergeCommand(type,isMatrix):

    #type -> 0=matrix/AC sys, 1=other sys
    target = {0: '', 1: ''}
    inputs = {0: [], 1: []}
    name = 'ACR'
    proc = '*'
    dir = "../varsDistro/"
    if isMatrix:
        name = 'MatrixAR'
        proc = 'AllSig'
        
    target[0] = 'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_Systematics.root'
    target[1] = 'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_Systematics.root'

    if isMatrix:
        inputs[0].extend(['XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_NormPart1Systematics_'+proc+'.root',
                          'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_NormPart2Systematics_'+proc+'.root',
                          'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_ShapePart1Systematics_'+proc+'.root',
                          'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_ShapePart2Systematics_'+proc+'.root',
                          'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_ShapePart3Systematics_'+proc+'.root'])

    inputs[0].extend(['XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThPdfPart1Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThPdfPart2Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThPdfPart3Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThPdfPart4Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThQcdPart1Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThQcdPart2Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThQcdPart3Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThScalePart1Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThScalePart2Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigThScalePart3Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigShowerPart1Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigShowerPart2Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigShowerPart3Systematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigShowerHerwigSystematics_'+proc+'.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+name+'factors_'+mcType[args.mcType]+'_SigCompositionSystematics_'+proc+'.root'])
        
    inputs[1].extend(['XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_NormPart1Systematics_*.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_NormPart2Systematics_*.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_ShapePart1Systematics_*.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_ShapePart2Systematics_*.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_ShapePart3Systematics_*.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_ZjetsSystematiscs_*.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_ZZTheoryPart1Systematics_*.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_ZZTheoryPart2Systematics_*.root',
                      'XsecInputs_'+str(args.nBins)+'bin_'+mcType[args.mcType]+'_SigMassShapeSystematics_*.root'])

    cmd = 'hadd -f '+dir+target[type]
    for file in inputs[type]:
        cmd += ' '+dir+file

    return cmd


if __name__ == "__main__":
    main()
