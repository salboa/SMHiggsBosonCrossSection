#!/usr/bin/python3
import sys
import os
import argparse
import subprocess
import getopt
import shlex
import time
import re

parser = argparse.ArgumentParser(description='Download minitrees from CERN eos. It requires to run on lxplus cluster with Python3')
parser.add_argument( '--mcType'      , type=int           , default=-1             , help='specify mcType: default is -1=all'+
                     ' Possible options are: 0=mc16a, 1=mc16d, 2=mc16e, 3=data , 4=zjets'                                                          )
parser.add_argument( '--createDir'   , action='store_true', default=False          , help='enable creating output directories: default is False'   )
parser.add_argument( '--username'    , type=str           , default='salvucci'     , help='specify user: default is salvucci'                      )
parser.add_argument( '--maxProcesses', type=int           , default=5              , help='specify number of simultaneous processes: default is 5' )
parser.add_argument( '--logsDir'     , type=str           , default='logs'         , help='specify logs store directory: default is logs'          )
parser.add_argument( '--inputPath'   , type=str           , default=''             , help='specify input minitrees path: default is '' (eos)'      )
parser.add_argument( '--outPath'     , type=str           , default=''             , help='specify output minitrees path: default is '' (dellpc)'  )
parser.add_argument( '--destHost'    , type=str           , default='andrea-dellpc', help='specify host destination: default is dellpc'            )
parser.add_argument( '--treeVersion' , type=str           , default='Prod_v20Fix'  , help='specify trees version: default is Prod_v20Fix'          )
args = parser.parse_args()

mcType   = ['mc16a', 'mc16d', 'mc16e', 'data', 'zjets']

mainDirs = ['Nominal', 'Systematics', 'FidTheory']

sysDirs  = [
    'EG_RESOLUTION_ALL__1down'                         , 'JET_BJES_Response__1down'         , 'JET_JER_EffectiveNP_1__1down' ,
    'EG_RESOLUTION_ALL__1up'                           , 'JET_BJES_Response__1up'           , 'JET_JER_EffectiveNP_1__1up'   ,
    'EG_SCALE_AF2__1down'                              , 'JET_EffectiveNP_1__1down'         , 'JET_JER_EffectiveNP_2__1down' ,
    'EG_SCALE_AF2__1up'                                , 'JET_EffectiveNP_1__1up'           , 'JET_JER_EffectiveNP_2__1up'   ,
    'EG_SCALE_ALL__1down'                              , 'JET_EffectiveNP_2__1down'         , 'JET_JER_EffectiveNP_3__1down' ,
    'EG_SCALE_ALL__1up'                                , 'JET_EffectiveNP_2__1up'           , 'JET_JER_EffectiveNP_3__1up'   ,
    'JET_EffectiveNP_3__1down'                         , 'JET_JER_EffectiveNP_4__1down'     , 'JET_EffectiveNP_3__1up'       , 
    'JET_JER_EffectiveNP_4__1up'                       , 'JET_EffectiveNP_4__1down'         , 'JET_JER_EffectiveNP_5__1down' ,
    'JET_EffectiveNP_4__1up'                           , 'JET_JER_EffectiveNP_5__1up'       , 'JET_EffectiveNP_5__1down'     ,
    'JET_JER_EffectiveNP_6__1down'                     , 'JET_EffectiveNP_5__1up'           , 'JET_JER_EffectiveNP_6__1up'   ,
    'JET_EtaIntercalibration_Modelling__1down'         , 'JET_EffectiveNP_6__1down'         , 'MUON_SAGITTA_RESBIAS__1down'  ,
    'JET_EtaIntercalibration_Modelling__1up'           , 'JET_EffectiveNP_6__1up'           , 'MUON_SAGITTA_RESBIAS__1up'    ,
    'JET_EtaIntercalibration_NonClosure_highE__1down'  , 'JET_EffectiveNP_7__1down'         , 'MUON_SAGITTA_RHO__1down'      ,
    'JET_EtaIntercalibration_NonClosure_highE__1up'    , 'JET_EffectiveNP_7__1up'           , 'MUON_SAGITTA_RHO__1up'        ,
    'JET_EtaIntercalibration_NonClosure_negEta__1down' , 'JET_EffectiveNP_8restTerm__1down' , 'MUON_SCALE__1down'            ,                       
    'JET_EtaIntercalibration_NonClosure_negEta__1up'   , 'JET_EffectiveNP_8restTerm__1up'   , 'MUON_SCALE__1up'              ,
    'JET_EtaIntercalibration_NonClosure_posEta__1down' , 'JET_Pileup_RhoTopology__1down'    , 'MUON_ID__1down'               ,
    'JET_EtaIntercalibration_NonClosure_posEta__1up'   , 'JET_Pileup_RhoTopology__1up'      , 'MUON_ID__1up'                 ,
    'JET_EtaIntercalibration_TotalStat__1down'         , 'JET_Pileup_OffsetMu__1down'       , 'MUON_MS__1down'               ,
    'JET_EtaIntercalibration_TotalStat__1up'           , 'JET_Pileup_OffsetMu__1up'         , 'MUON_MS__1up'                 ,
    'JET_Flavor_Composition__1down'                    , 'JET_Pileup_OffsetNPV__1down'      , 'MET_SoftTrk_ResoPara'         ,
    'JET_Flavor_Composition__1up'                      , 'JET_Pileup_OffsetNPV__1up'        , 'MET_SoftTrk_ResoPerp'         ,
    'JET_Flavor_Response__1down'                       , 'JET_Pileup_PtTerm__1down'         , 'MET_SoftTrk_ScaleDown'        ,
    'JET_Flavor_Response__1up'                         , 'JET_Pileup_PtTerm__1up'           , 'MET_SoftTrk_ScaleUp'          ,
    'JET_JER_EffectiveNP_7restTerm__1down'             , 'JET_SingleParticle_HighPt__1down' , 'JET_PunchThrough_MC16__1down' ,
    'JET_JER_EffectiveNP_7restTerm__1up'               , 'JET_SingleParticle_HighPt__1up'   , 'JET_PunchThrough_MC16__1up'   ,
    'JET_JER_DataVsMC__1down'                          , 'JET_JER_DataVsMC__1up'            , 'NormSystematic'
]


Signals = [ 
    'mc16_13TeV.345060.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_ZZ4l'              ,
    'mc16_13TeV.346228.PowhegPy8EG_NNPDF30_AZNLOCTEQ6L1_VBFH125_ZZ4lep_notau'       ,
    'mc16_13TeV.345039.PowhegPythia8EvtGen_NNPDF30_AZNLO_WpH125J_Wincl_MINLO'       ,
    'mc16_13TeV.345040.PowhegPythia8EvtGen_NNPDF30_AZNLO_WmH125J_Wincl_MINLO'       ,
    'mc16_13TeV.345038.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Zincl_MINLO'        ,
    'mc16_13TeV.345066.PowhegPythia8EvtGen_NNPDF3_AZNLO_ggZH125_ZZ4lepZinc'         ,
    'mc16_13TeV.346340.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_allhad'         ,
    'mc16_13TeV.346341.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_semilep'        ,
    'mc16_13TeV.346342.PowhegPy8EG_A14NNPDF23_NNPDF30ME_ttH125_ZZ4l_dilep'          ,
    'mc16_13TeV.344973.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_yb2_ZZ4lep_noTau'  ,
    'mc16_13TeV.344974.aMcAtNloPythia8EvtGen_A14NNPDF23LO_bbH125_ybyt_ZZ4lep_noTau' ,
    'mc16_13TeV.346511.aMcAtNloPythia8EvtGen_tWH125_ZZ4l'                           ,
    'mc16_13TeV.346414.aMcAtNloPythia8EvtGen_tHjb125_4fl_ZZ4l'
]

Signals_HW = [
    'mc16_13TeV.346446.PhH7EG_H7UE_NNLOPS_nnlo_30_ggH125_ZZ4l_noTau'   ,
    'mc16_13TeV.346447.PhH7EG_H7UE_NNPDF30_VBFH125_ZZ4lep_noTau'       ,
    'mc16_13TeV.346448.PhH7EG_H7UE_NNPDF30_ZH125J_Zincl_MINLO'         ,
    'mc16_13TeV.346449.PhH7EG_H7UE_NNPDF30_WpH125J_Wincl_MINLO'        ,
    'mc16_13TeV.346450.PhH7EG_H7UE_NNPDF30_WmH125J_Wincl_MINLO'        ,
    'mc16_13TeV.346451.PhH7EG_H7UE_NNPDF3_ggZH125_ZZ4lepZinc'          ,
    'mc16_13TeV.346452.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_allhad_noTau' ,
    'mc16_13TeV.346453.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_semilep_noTau',
    'mc16_13TeV.346454.PhH7EG_H7UE_NNPDF30ME_ttH125_ZZ4l_dilep_noTau'
]

qqZZ_Bkg = [
    'mc16_13TeV.364251.Sherpa_222_NNPDF30NNLO_llll_m4l100_300_filt100_150',
    'mc16_13TeV.364252.Sherpa_222_NNPDF30NNLO_llll_m4l300'                ,
    'mc16_13TeV.364250.Sherpa_222_NNPDF30NNLO_llll'
]

qqZZ_Bkg_PW = [
    'mc16_13TeV.342556.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_100_150'  ,
    'mc16_13TeV.343232.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_500_13000',
    'mc16_13TeV.361603.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4'
]

other_Bkg = [   
    'mc16_13TeV.345708.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_0M4l130'           ,
    'mc16_13TeV.345709.Sherpa_222_NNPDF30NNLO_ggllllNoHiggs_130M4l'            ,
    'mc16_13TeV.364364.Sherpa_222_NNPDF30NNLO_lllljj_EW6_noHiggs_AFii_'        ,
    'mc16_13TeV.364243.Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6'                    ,
    'mc16_13TeV.364245.Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6'                    ,
    'mc16_13TeV.364247.Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6'                    ,
    'mc16_13TeV.364248.Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6'                    ,
    'mc16_13TeV.345937.aMcAtNloPy8EG_MEN30NLO_A14N23LO_ttee_m4l100_150_mll_3l' ,
    'mc16_13TeV.345938.aMcAtNloPy8EG_MEN30NLO_A14N23LO_ttmm_m4l100_150_mll_3l' ,
    'mc16_13TeV.345939.aMcAtNloPy8EG_MEN30NLO_A14N23LO_ttW_m4l100_150_mll_3l'  ,
    'mc16_13TeV.410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee'           ,
    'mc16_13TeV.410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu'         ,
    'mc16_13TeV.410155.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW'
]

Data = [ "data1516_13TeV", "data17_13TeV", "data18_13TeV" ]

Zjets = [ "allShapes", "rehbrtest.log" ]


def main():
    InPrefix  = args.inputPath
    OutPrefix = args.outPath
    if args.inputPath=='':
        InPrefix = '/eos/atlas/atlascerngroupdisk/phys-higgs/HSG2/H4l/2018/MiniTrees/'
    if args.outPath=='':
        OutPrefix = '/mnt/DataHD/minitree/'

    InPrefix  += args.treeVersion+'/'
    OutPrefix += args.treeVersion+'/'
    hostDest  = args.username+'@'+args.destHost+':'
    commands = []
    for mc in getListOfMCtypes():
        if args.createDir:
            createDirectories( OutPrefix+mc )
        else:
            commands.extend( getListOfCommands( InPrefix+mc,OutPrefix+mc,hostDest ) )
    
    #check if directory where logs are store exists, if it doesn't create it
    if not args.createDir:
        if not os.path.exists(args.logsDir):
            os.makedirs(args.logsDir)

    i=0
    processes = set()

    for cmd in commands:
        left = '/mc16'
        if cmd.find('data')!=-1:
            left = '/data1'
        if cmd.find('background')!=-1:
            left = '/all'
        print( 'Copying files under ', re.search(InPrefix+'(.+?)'+left,cmd).group(1) )
        i = i + 1
        if(i%args.maxProcesses == 0):
            precentDone = float(i)/len(commands) * 100
            print( 'Running command #: ', i, ' percentage submitted: ' , float("{0:.1f}".format(precentDone)) )
            pass

        arguments = shlex.split(cmd)
        logPostFix = (re.search(InPrefix+'(.+?)'+left,cmd).group(1)).replace('/','_')
        logFile = args.logsDir+'/logfile_'+logPostFix+".log"
        w = open(logFile,'w')
        
        processes.add( subprocess.Popen(arguments,stdout=w, stderr=w) )
        if len(processes) >= args.maxProcesses:
            os.wait()
            processes.difference_update([p for p in processes if p.poll() is not None])

    jobs = processes
    while len(jobs) > 0:
        jobs = [job for job in jobs if job.poll() is None]
        time.sleep(1)
        
            
def createDirectories( prefix ):

    dirList = getListOfDirectories( prefix )
    prefix = prefix.replace('/zjets','')
    for dir in dirList:
        if not os.path.isdir(prefix+'/'+dir):
            os.makedirs(prefix+'/'+dir)

            
def getListOfCommands( inPrefix,outPrefix,hostDest ):

    m_list = []
    dirList = getListOfDirectories(inPrefix)
    inPrefix = inPrefix.replace('/zjets','')
    outPrefix = outPrefix.replace('/zjets','')
    for dir in dirList:
        list = (inPrefix+'/'+dir).join( s+".root " for s in getListOfSamples(dir,inPrefix) )
        if list.find('.log.root')!=-1:
            list = list.replace('.log.root','.log')
        m_list.append( 'scp '+inPrefix+'/'+dir+list+' '+hostDest+outPrefix+'/'+dir+'.' )
        
    return m_list


def getListOfDirectories(prefix):

    m_list = []
    if prefix.find('/data')!=-1:
        m_list.append('Nominal/')
    elif prefix.find('/zjets')!=-1:
        m_list.append('backgroundResults/')
    else:
        for d in mainDirs:
            if d=='Systematics':
                if(args.createDir):
                    m_list.append(d+'/')
                for s in sysDirs:
                    m_list.append('Systematics/'+s+'/')
            else:
                m_list.append(d+'/')

    return m_list


def getListOfMCtypes():

    m_list = []
    if args.mcType==-1:
        m_list.extend(mcType)
    else:
        m_list.append(mcType[args.mcType])

    return m_list


def getListOfSamples(dir,prefix):

    m_list = []
    if prefix.find('data')!=-1:
        m_list.extend(Data)
    elif dir.find('background')!=-1:
        m_list.extend(Zjets)
    else:
        m_list.extend(Signals)
        if dir.find('Nominal')!=-1 or dir.find('FidTheory')!=-1:
            if prefix.find('mc16e')!=-1:
                m_list.extend(Signals_HW)
        if dir.find('FidTheory')==-1:
            m_list.extend(qqZZ_Bkg)
            m_list.extend(other_Bkg)
            if dir.find('Nominal')!=-1:
                m_list.extend(qqZZ_Bkg_PW)

    return m_list
    

if __name__ == "__main__":
    main()
