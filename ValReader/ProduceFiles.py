#!/usr/bin/python
import os
import sys
import json
import getopt
import string
from GlobalVar import *

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
    #Assign None to all variables
    m_Fiducial     = None
    m_Acceptance   = None
    m_ProdModRatio = None
    m_ScaleXsec    = None
    m_125p9        = None
    m_Precision    = None
    m_Systematics  = None
    m_SigThSys     = None
    m_qqZZthSys    = None
    m_ZjetSys      = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="doAcceptance":
                m_Acceptance=True

            if key=="doFiducial":
                m_Fiducial=True

            if key=="doProdModeRatio":
                m_ProdModRatio=True

            if key=="doScaleXsec":
                m_ScaleXsec=True

            if key=="doSystematics":
                m_Systematics=True

            if key=="doSigTheorySys":
                m_SigThSys=True

            if key=="doZZTheorySys":
                m_qqZZthSys=True

            if key=="doZjetSys":
                m_ZjetSys=True

            if key=="use125p9":
                m_125p9=True

            if key=="ValPrecision":
                m_Precision=value
            
    if not m_Fiducial:
        m_Fiducial=False
    if not m_Acceptance:
        m_Acceptance=False
    if not m_ProdModRatio:
        m_ProdModRatio=False
    if not m_Systematics:
        m_Systematics=False
    if not m_SigThSys:
        m_SigThSys=False
    if not m_qqZZthSys:
        m_qqZZthSys=False
    if not m_ZjetSys:
        m_ZjetSys=False
    if not m_ScaleXsec:
        m_ScaleXsec=False
    if not m_125p9:
        m_125p9=False
    if not m_Precision:
        m_Precision=6

    if m_ScaleXsec and m_Fiducial and m_Systematics:
        print "PROBLEM:: doScaleXsec, doFiducial doSystematics cannot be used at the same time"
        print "          enable only one of the 3 options"
        sys.exit(0)

    if m_Systematics and m_SigThSys:
        print "PROBLEM:: doSystematics and doSigTheorySys cannot be used at the same time"
        print "          enable only one of the 2 options"
        print "          N.B: doSigTheorySys should be enabled only after doSystematics"
        sys.exit(0)

    if m_Systematics and m_qqZZthSys:
        print "PROBLEM:: doSystematics and doZZTheorySys cannot be used at the same time"
        print "          enable only one of the 2 options"
        print "          N.B: doZZTheorySys should be enabled only after doSystematics"
        sys.exit(0)

    if m_Systematics and m_ZjetSys:
        print "PROBLEM:: doSystematics and doZjetSys cannot be used at the same time"
        print "          enable only one of the 2 options"
        print "          N.B: doZjetSys should be enabled only after doSystematics"
        sys.exit(0)

    if m_SigThSys and m_qqZZthSys:
        print "PROBLEM:: doSigTheorySys and doZZTheorySys cannot be used at the same time"
        print "          enable only one of the 2 options"
        sys.exit(0)

    if m_SigThSys and m_ZjetSys:
        print "PROBLEM:: doSigTheorySys and doZjetSys cannot be used at the same time"
        print "          enable only one of the 2 options"
        sys.exit(0)

    if m_ZjetSys and m_qqZZthSys:
        print "PROBLEM:: doZjetSys and doZZTheorySys cannot be used at the same time"
        print "          enable only one of the 2 options"
        sys.exit(0)

    if m_Systematics:
        DeriveSystematics(m_Fiducial)
        
    elif m_SigThSys:
        UpdateSignalSystematics(m_Fiducial,m_Precision)

    elif m_qqZZthSys:
        Update_qqZZSystematics(m_Fiducial,m_Precision)
        Update_ggZZSystematics(m_Fiducial,m_Precision)

    elif m_ZjetSys:
        DeriveZjetSystematics(m_Fiducial)

    else:
        DeriveValues(m_Fiducial,m_Acceptance,m_ProdModRatio,
                     m_ScaleXsec,m_125p9,m_Precision)


def DeriveValues(m_fid, m_acc, m_r, m_scxec, m_125p9,m_precision):

    #Configuration
    doFiducial     = m_fid
    doAcceptance   = m_acc
    doProdModRatio = m_r
    doScaleXsec    = m_scxec
    use125p9       = m_125p9
    Precision      = "%0."+str(m_precision)+"f"

    InDir         = "OrigVal/"
    OutDir        = "Values/"
    Mass          = "125_0"
    OutFilePrefix = "CF"
    SearchString  = "factor"
    ValuesName    = "correction"

    if doFiducial:
        OutDir += "Fid/"
    else:
        OutDir += "Diff/"
    
    if use125p9:
        Mass = "125_09"

    if doAcceptance:
        OutFilePrefix = "Acc"
        ValuesName    = "acceptance"
        
    if doProdModRatio:
        OutFilePrefix = "r"
        ValuesName    = "proportion"

    if doScaleXsec:
        OutFilePrefix = "scaleXsec"
        ValuesName    = "APrime"
        
    InFileName   = "Dictionary_"+ValuesName+"Factor_"+Mass+"_nominal.json"
            
    json_file    = open(InDir+InFileName)
    json_string  = json_file.read()
    json_data    = json.loads(json_string)
    AllValues    = json_data[SearchString+"s"]
    AllValuesErr = json_data[SearchString+"_errors"]

    if doFiducial:

        for v in FidVarBin:
            values  = AllValues[v[0]]
            errors  = AllValuesErr[v[0]]
            outFile = open(OutDir+OutFilePrefix+".dat", "w")
            print "Processing Variable ",v[0], "  ... "
            print ""
            FirstLine  = "Channel".ljust(5)+"AllSig".center(21)+"ggH".center(23)+"VBF".center(18)
            FirstLine += "WH".center(20)+"ZH".center(20)+"ttH".center(20)+"bbH".center(20)
            print FirstLine
            outFile.write(FirstLine+"\n")
            for b in range(0,v[1]):
                for dc in DecayChannels:
                    Line  = str(dc[0]).ljust(5)
                    Line += str(Precision % values[pm_AllSig][dc[1]][b]).rjust(10)+ str(Precision % errors[pm_AllSig][dc[1]][b]).rjust(10)
                    Line += str(Precision % values[pm_ggH][dc[1]][b]).rjust(10)   + str(Precision % errors[pm_ggH][dc[1]][b]).rjust(10)
                    Line += str(Precision % values[pm_VBF][dc[1]][b]).rjust(10)   + str(Precision % errors[pm_VBF][dc[1]][b]).rjust(10)
                    Line += str(Precision % values[pm_WH][dc[1]][b]).rjust(10)    + str(Precision % errors[pm_WH][dc[1]][b]).rjust(10)
                    Line += str(Precision % values[pm_ZH][dc[1]][b]).rjust(10)    + str(Precision % errors[pm_ZH][dc[1]][b]).rjust(10)
                    Line += str(Precision % values[pm_ttH][dc[1]][b]).rjust(10)   + str(Precision % errors[pm_ttH][dc[1]][b]).rjust(10)
                    Line += str(Precision % values[pm_bbH][dc[1]][b]).rjust(10)   + str(Precision % errors[pm_bbH][dc[1]][b]).rjust(10)
                    print Line
                    if(dc[1]==3):
                        outFile.write( Line )
                    else:
                        outFile.write( Line+"\n")
                                    
            outFile.close()
            print ""

    else:

        for v in DiffVarBin:
            values  = AllValues[v[0]]
            errors  = AllValuesErr[v[0]]

            outName = OutDir+v[2]+"/"+OutFilePrefix+"_"+v[2]+".dat"
            outFile = open(outName, "w")
            print "Processing Variable ",v[0], "  and storing in ",outName
            print ""
            FirstLine  = "bin".ljust(5)+"AllSig".center(21)+"ggH".center(23)+"VBF".center(18)
            FirstLine +="WH".center(20)+"ZH".center(20)+"ttH".center(20)+"bbH".center(20)
            print FirstLine
            outFile.write(FirstLine+"\n")
            
            for b in range(0,v[1]):
                Line  = str(b).ljust(5)
                Line += str(Precision % values[pm_AllSig][dc_incl][b]).rjust(10)+ str(Precision % errors[pm_AllSig][dc_incl][b]).rjust(10)
                Line += str(Precision % values[pm_ggH][dc_incl][b]).rjust(10)   + str(Precision % errors[pm_ggH][dc_incl][b]).rjust(10)
                Line += str(Precision % values[pm_VBF][dc_incl][b]).rjust(10)   + str(Precision % errors[pm_VBF][dc_incl][b]).rjust(10)
                Line += str(Precision % values[pm_WH][dc_incl][b]).rjust(10)    + str(Precision % errors[pm_WH][dc_incl][b]).rjust(10)
                Line += str(Precision % values[pm_ZH][dc_incl][b]).rjust(10)    + str(Precision % errors[pm_ZH][dc_incl][b]).rjust(10)
                Line += str(Precision % values[pm_ttH][dc_incl][b]).rjust(10)   + str(Precision % errors[pm_ttH][dc_incl][b]).rjust(10)
                Line += str(Precision % values[pm_bbH][dc_incl][b]).rjust(10)   + str(Precision % errors[pm_bbH][dc_incl][b]).rjust(10)
                print Line
                if b==v[1]-1:
                    outFile.write( Line)
                else:
                    outFile.write( Line+"\n")   
                
            outFile.close()
            print ""

            if v[2]=="pt0j" or v[2]=="pt1j" or v[2]=="pt2j":
                offset  = 0
                if v[2]=="pt1j":
                    offset=4
                elif v[2]=="pt2j":
                    offset=9

                outName = OutDir+"ptpt/"+OutFilePrefix+"_ptpt.dat"
                outFile = None
                if v[2]=="pt0j":
                    outFile = open(outName, "w")
                else:
                    outFile = open(outName, "a")
                        
                print "Processing Variable ",v[0], "  and storing in ",outName
                print ""
                if v[2]=="pt0j":
                    FirstLine  = "bin".ljust(5)+"AllSig".center(21)+"ggH".center(23)+"VBF".center(18)
                    FirstLine +="WH".center(20)+"ZH".center(20)+"ttH".center(20)+"bbH".center(20)
                    print FirstLine
                    outFile.write(FirstLine+"\n")

                if v[2]!="pt0j":
                        outFile.write( "\n" )

                for b in range(0,v[1]):
                    Line  = str(b+offset).ljust(5)
                    Line += str(Precision % values[pm_AllSig][dc_incl][b]).rjust(10)+ str(Precision % errors[pm_AllSig][dc_incl][b]).rjust(10)
                    Line += str(Precision % values[pm_ggH][dc_incl][b]).rjust(10)   + str(Precision % errors[pm_ggH][dc_incl][b]).rjust(10)
                    Line += str(Precision % values[pm_VBF][dc_incl][b]).rjust(10)   + str(Precision % errors[pm_VBF][dc_incl][b]).rjust(10)
                    Line += str(Precision % values[pm_WH][dc_incl][b]).rjust(10)    + str(Precision % errors[pm_WH][dc_incl][b]).rjust(10)
                    Line += str(Precision % values[pm_ZH][dc_incl][b]).rjust(10)    + str(Precision % errors[pm_ZH][dc_incl][b]).rjust(10)
                    Line += str(Precision % values[pm_ttH][dc_incl][b]).rjust(10)   + str(Precision % errors[pm_ttH][dc_incl][b]).rjust(10)
                    Line += str(Precision % values[pm_bbH][dc_incl][b]).rjust(10)   + str(Precision % errors[pm_bbH][dc_incl][b]).rjust(10)
                    print Line
                    if b==v[1]-1:
                        outFile.write( Line)
                    else:
                        outFile.write( Line+"\n")   
                
                outFile.close()
                print ""

                
def UpdateSignalSystematics(m_fid,m_precision):

    #Configuration
    doFiducial     = m_fid
    Precision      = "%0."+str(m_precision)+"f"

    InDir         = "OrigVal/"
    OutDir        = "Values/"
    
    if doFiducial:
        OutDir += "Fid/"
    else:
        OutDir += "Diff/"

    InFileName = [ ["Dictionary_correction_PdfTheory_sys.json"  , "PdfTheory"  , "ATLAS_pdf_sig_gg"        ],
                   ["Dictionary_correction_PdfTheory_sys.json"  , "PdfTheory"  , "ATLAS_pdf_sig_qq"        ],
                   ["Dictionary_correction_ScaleTheory_sys.json", "ScaleTheory", "ATLAS_scale_sig"         ],
                   ["Dictionary_correction_mass_sys.json"       , "mass"       , "ATLAS_HiggsMassVariation"] ]

    #old orig files
    #["Dictionary_correction_PdfTheory_nominal.json"  , "PdfTheory"  , "ATLAS_pdf_sig_gg"        ],
    #["Dictionary_correction_PdfTheory_nominal.json"  , "PdfTheory"  , "ATLAS_pdf_sig_qq"        ],
    #["Dictionary_correction_ScaleTheory_nominal.json", "ScaleTheory", "ATLAS_scale_sig"         ],
    #["Dictionary_correction_mass_nominal.json"       , "mass"       , "ATLAS_HiggsMassVariation"] ]
    #old sig comp files -> merged named as sys.json
    #["Dictionary_correction_production0_nominal.json", "production0", "ATLAS_SignalComposition_Var1"],
    #["Dictionary_correction_production1_nominal.json", "production1", "ATLAS_SignalComposition_Var2"],
    #["Dictionary_correction_production2_nominal.json", "production2", "ATLAS_SignalComposition_Var3"],
    #["Dictionary_correction_production3_nominal.json", "production3", "ATLAS_SignalComposition_Var4"]
    
    CorrMatrix = [ [+1, +1, +1, +1, +1, +1],
                   [+1, +1, +1, +1, +1, +1],
                   [+1, +1, +1, +1, +1, +1],
                   [+1, +1, +1, +1, +1, +1],
                   #sig comp variation
                   [-1, +1, -1, +1, +1, -1],
                   [-1, +1, -1, +1, +1, +1],
                   [-1, +1, -1, +1, +1, -1],
                   [-1, +1, -1, +1, +1, -1] ]

    Counter = 0
    
    for file in InFileName:
        
        json_file    = open(InDir+file[0])
        json_string  = json_file.read()
        json_data    = json.loads(json_string)
        AllValues    = json_data[file[1]]

        if doFiducial:
            
            for v in FidVarBin:
                
                values  = AllValues[v[0]]
                print "Processing Variable ",v[0], "  ... "
                print ""
                
                for b in range(0,v[1]):
                    
                    for dc in DecayChannels:
                        
                        for pm in SigProdMode:
                            
                            outFile = open(OutDir+"Sys/"+pm[0]+"_"+dc[0]+".dat", "a")
                            Line = "\n"
                            outFile.write( Line )
                            Line = ""
                            if file[2]=="ATLAS_SignalComposition":
                                Line += (file[2]+"_"+pm[0]).ljust(55)
                                Line += str(Precision % (1+abs(SigComp[pm[1]]))).ljust(12)
                                Line += str(Precision % (1-abs(SigComp[pm[1]]))).ljust(12)
                            elif file[2]=="ATLAS_scale_sig":
                                Line += (file[2]+"_"+pm[0]).ljust(55)
                                Line += str(Precision % (1-abs(values[pm[1]][dc[1]][b][1]))).ljust(12)
                                Line += str(Precision % (1+abs(values[pm[1]][dc[1]][b][0]))).ljust(12)
                            else:
                                Line += file[2].ljust(55)
                                if file[2]=="ATLAS_pdf_sig_gg":
                                    if pm[0]=="ggH" or pm[0]=="ttH" or pm[0]=="bbH":
                                        Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                                        Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                                    else:
                                        Line += str(Precision % (1)).ljust(12)
                                        Line += str(Precision % (1)).ljust(12)
                                elif file[2]=="ATLAS_pdf_sig_qq":
                                    if pm[0]=="VBF" or pm[0]=="WH" or pm[0]=="ZH":
                                        Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                                        Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                                    else:
                                        Line += str(Precision % (1)).ljust(12)
                                        Line += str(Precision % (1)).ljust(12)
                                else:
                                    if CorrMatrix[Counter][pm[1]]<0:
                                        Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                                        Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                                    else:
                                        Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                                        Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                                                                                                    
                            Line += str("1").rjust(12)+str("1").rjust(12)
                            print pm[0].ljust(4)+" -> "+Line

                            #next lines just for debug
                            #print "\n"
                            #print "UP    "+str(values[pm[1]][dc[1]][b][0])+"    DOWN  "+str(values[pm[1]][dc[1]][b][1])

                            outFile.write( Line )
                            outFile.close()
                        print ""

        else:

            for v in DiffVarBin:
                values  = AllValues[v[0]]
                print "Processing Variable ",v[0]
                print ""
                for b in range(0,v[1]):
                    for pm in SigProdMode:

                        offset  = 0
                        varName = v[2]
                        if v[2]=="pt0j" or v[2]=="pt1j" or v[2]=="pt2j":
                            varName = "ptpt"
                        if v[2]=="pt1j":
                            offset=4
                        elif v[2]=="pt2j":
                            offset=9
                            
                        outFile = open(OutDir+varName+"/Sys/"+pm[0]+"_bin"+str(b+offset)+".dat", "a")
                        outFile.write( "\n" )
                        Line = ""
                        if file[2]=="ATLAS_SignalComposition":
                            Line += (file[2]+"_"+pm[0]).ljust(55)
                            Line += str(Precision % (1+abs(SigComp[pm[1]]))).ljust(12)
                            Line += str(Precision % (1-abs(SigComp[pm[1]]))).ljust(12)
                        elif file[2]=="ATLAS_scale_sig":
                            Line += (file[2]+"_"+pm[0]).ljust(55)
                            Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                            Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                        else:
                            Line += file[2].ljust(55)
                            if file[2]=="ATLAS_pdf_sig_gg":
                                if pm[0]=="ggH" or pm[0]=="ttH" or pm[0]=="bbH":
                                    Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                                    Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                                else:
                                    Line += str(Precision % (1)).ljust(12)
                                    Line += str(Precision % (1)).ljust(12)
                            elif file[2]=="ATLAS_pdf_sig_qq":
                                if pm[0]=="VBF" or pm[0]=="WH" or pm[0]=="ZH":
                                    Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                                    Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                                else:
                                    Line += str(Precision % (1)).ljust(12)
                                    Line += str(Precision % (1)).ljust(12)
                            else:
                                if CorrMatrix[Counter][pm[1]]<0:
                                    Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                                    Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                                else:
                                    Line += str(Precision % (1-abs(values[pm[1]][dc_incl][b][1]))).ljust(12)
                                    Line += str(Precision % (1+abs(values[pm[1]][dc_incl][b][0]))).ljust(12)
                                
                        Line += str("1").rjust(12)+str("1").rjust(12)
                        print pm[0].ljust(4)+" -> "+Line

                        #next lines for debug
                        #print "\n"
                        #print "UP    "+str(values[pm[1]][dc_incl][b][0])+"    DOWN  "+str(values[pm[1]][dc_incl][b][1])

                        outFile.write( Line )
                        outFile.close()

                    print ""
                    
        Counter=Counter+1

    os.system("make")

    if doFiducial:
            
        cmd = " ./SigComp --Fiducial --write"
        os.system(cmd)
            
    else:

        for v in DiffSystBin:
            cmd = " ./SigComp --variable "+v[2]+" --write"
            os.system(cmd)
            
    os.system("make clean")
                    
def Update_qqZZSystematics(m_fid,m_precision):

    #Configuration
    doFiducial     = m_fid
    Precision      = "%0."+str(m_precision)+"f"

    InDir         = "OrigVal/"
    OutDir        = "Values/"

    Vars = []
    
    if doFiducial:
        OutDir += "Fid/"
    else:
        OutDir += "Diff/"
        Vars = qqZZSystBin

    InFileName = [ ["qqZZ_pdf/pdf_diff_", "ATLAS_pdf_qqZZ"],
                   ["qqZZ_scale/scale_diff_", "ATLAS_scale_qqZZ"],
                   ["qqZZ_shower/qqZZ_Showering_Var_Sherpa_","ATLAS_shower_qqZZ"] ]

    for file in InFileName:

        if doFiducial:
            print "Processing Fiducial Channels ... "
            with open(InDir+file[0]+"eventtype.txt", "r") as inFile:
                for line in inFile:
                    name  = None
                    write = False
                    up    = None
                    down  = None
                    if line.find("4mu")!=-1 or line.find("4e")!=-1 or line.find("2e2mu")!=-1 or line.find("2mu2e")!=-1 or line.find("incl")!=-1:
                        chan = line.translate(None,'[]').rstrip()
                        if chan=="inclusive":
                            chan="incl"
                    else:
                        write = True
                        if file[1].find("shower")!=-1:
                            tmp =line.translate(None,'=')
                            name = tmp.split(' ')[0]
                            down = float( tmp.split(' ')[2] )
                            up   = float( tmp.split(' ')[3] )
                        else:
                            name = file[1]
                            tmp  = line.translate(None,file[1]+'=')
                            down = float( tmp.split(' ')[2] )
                            up   = float( tmp.split(' ')[3] )

                    if write:
                        outFile = open(OutDir+"/Sys/qqZZ_"+chan+".dat", "a")
                        outFile.write( "\n" )
                        Line = name.ljust(55)
                        Line += str(Precision % down).ljust(12)
                        Line += str(Precision % up).ljust(12)
                        Line += str("1").rjust(12)+str("1").rjust(12)
                        print chan.ljust(5)+" -> "+Line

                        outFile.write( Line )
                        outFile.close()

            print ""
                    
        else:

            for v in Vars:
                print "Processing Variable "+v[0]+" ... "
                with open(InDir+file[0]+v[0]+".txt", "r") as inFile:
                    for line in inFile:
                        name  = None
                        write = False
                        up    = None
                        down  = None
                        if line.find("bin")!=-1:
                            bin = int( line.translate(None,'[bin]') )
                        else:
                            write = True
                            if file[1].find("shower")!=-1:
                                tmp =line.translate(None,'=')
                                name = tmp.split(' ')[0]
                                down = float( tmp.split(' ')[2] )
                                up   = float( tmp.split(' ')[3] )
                            else:
                                name = file[1]
                                tmp  = line.translate(None,file[1]+'=')
                                down = float( tmp.split(' ')[2] )
                                up   = float( tmp.split(' ')[3] )
                            
                        if write:
                            outFile = open(OutDir+v[2]+"/Sys/qqZZ_bin"+str(bin)+".dat", "a")
                            outFile.write( "\n" )
                            Line = name.ljust(55)
                            Line += str(Precision % down).ljust(12)
                            Line += str(Precision % up).ljust(12)
                            Line += str("1").rjust(12)+str("1").rjust(12)
                            print str(bin).ljust(5)+" -> "+Line
                            
                            outFile.write( Line )
                            outFile.close()

                            
def Update_ggZZSystematics(m_fid,m_precision):

    #Configuration
    doFiducial     = m_fid
    Precision      = "%0."+str(m_precision)+"f"

    OutDir        = "Values/"

    Vars = []
    
    if doFiducial:
        OutDir += "Fid/"
    else:
        OutDir += "Diff/"
        Vars = qqZZSystBin

    UncSource = [ ["ATLAS_pdf_ggZZ"   , 0.60 ],
                  ["ATLAS_scale_ggZZ" , 0.08 ]  ]

    for unc in UncSource:

        if doFiducial:
            print "Processing Fiducial Channels ... "
            for chan in DecayChannels:
                outFile = open(OutDir+"/Sys/ggZZ_"+chan[0]+".dat", "a")
                outFile.write( "\n" )
                Line = unc[0].ljust(55)
                Line += str( Precision % (1-abs(unc[1])) ).ljust(12)
                Line += str( Precision % (1+abs(unc[1])) ).ljust(12)
                Line += str("1").rjust(12)+str("1").rjust(12)
                print chan[0].ljust(5)+" -> "+Line

                outFile.write( Line )
                outFile.close()

            print ""
                
        else:

            for v in Vars:
                print "Processing Variable "+v[0]+" ... "
                for bin in range(0,v[1]):
                    outFile = open(OutDir+v[2]+"/Sys/ggZZ_bin"+str(bin)+".dat", "a")
                    outFile.write( "\n" )
                    Line = unc[0].ljust(55)
                    Line += str( Precision % (1-abs(unc[1])) ).ljust(12)
                    Line += str( Precision % (1+abs(unc[1])) ).ljust(12)
                    Line += str("1").rjust(12)+str("1").rjust(12)
                    print str(bin).ljust(5)+" -> "+Line
                    
                    outFile.write( Line )
                    outFile.close()
                print ""
                        
def DeriveSystematics(m_fid):

    #Configuration
    doFiducial = m_fid

    InDir      = "OrigVal/"
    OutDir     = "Values/"

    if doFiducial:
        OutDir += "Fid/"
    else:
        OutDir += "Diff/"

    os.system("make")

    for proc in Processes:

        if doFiducial:
            
            InFileName   = InDir+"norm_"
            if proc=="ggH":
                InFileName += "ggF.txt"
            else:
                InFileName += proc+".txt"

            OutName = OutDir+"Sys/"+proc
            cmd  = "./ReadFiles --inFile "+InFileName+" --outFile "+OutName
            cmd += " --Fiducial"

            os.system(cmd)
            
        else:

            for v in DiffSystBin:

                InFileName   = InDir+v[2]+"/norm_"
                if proc=="ggH":
                    InFileName += "ggF.txt"
                else:
                    InFileName += proc+".txt"

                for b in range(0,v[1]):
                    
                    OutName = OutDir+v[2]+"/Sys/"+proc+"_bin"+str(b)
                    cmd  = "./ReadFiles --inFile "+InFileName
                    cmd += " --outFile "+OutName+" --nBins "+str(v[1])
                    cmd += " --Bin "+str(b)

                    os.system(cmd)
                    
    os.system("make clean")

    
def DeriveZjetSystematics(m_fid):

    #Configuration
    doFiducial     = m_fid

    os.system("make")

    cmd = "./ZjetSys"
    if doFiducial:
        cmd += " --Fiducial"
        
    os.system(cmd)
    os.system("make clean")

    
def ShowDoc():
    print ""
    print "Script to make Acceptance and Correction Factors input files!"
    print "  Usage   : ./ProduceFiles.py [Options]!"
    print "            Options:  "
    print "                     doFiducial=[True/False]      : default is 'False' -> doing Differential"
    print "                     doAcceptance=[True/False]    : default is 'False' -> doing Correction Factors"
    print "                     doProdModeRatio=[True/False] : default is 'False' -> doing Correction Factors"
    print "                     doScaleXsec=[True/False]     : default is 'False' -> doing Correction Factors"
    print "                     doSystematics=[True/False]   : default is 'False' -> doing Correction Factors"
    print "                     doSigTheorySys=[True/False]  : default is 'False' -> doing Correction Factors"
    print "                     doZZTheorySys=[True/False]   : default is 'False' -> doing Correction Factors"
    print "                     doZjetSys=[True/False]       : default is 'False' -> doing Correction Factors"
    
    print "                     ValPrecision=6               : default is '6'     -> using 6 digit (min value 5, max value 7)"
    print "                     use125p9=[True/False]        : default is 'False' -> using Mh=125 GeV"


if __name__ == "__main__":
    main()
