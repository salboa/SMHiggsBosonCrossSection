#!/usr/bin/python
import os
import sys
import json
import getopt
import string
from ROOT import *
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
    m_125p9     = None
    m_Precision = None
    m_Fiducial  = None
    #process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="doFiducial":
                m_Fiducial=True

            if key=="use125p9":
                m_125p9=True
                
            if key=="ValPrecision":
                m_Precision=value

    if not m_Fiducial:
        m_Fiducial=False
    if not m_125p9:
        m_125p9=False
    if not m_Precision:
        m_Precision=6

        

    DeriveValues(m_Fiducial, m_125p9, m_Precision)
    DeriveSys(m_Fiducial, m_125p9, m_Precision)

    
def DeriveValues(m_fid, m_125p9, m_precision):

    #Configuration
    use125p9       = m_125p9
    Precision      = "%0."+str(m_precision)+"f"
    doFiducial     = m_fid

    InDir         = "OrigVal/"
    OutDir        = "Values/"
    Mass          = "125_0"
    OutFilePrefix = "CF"
    SearchString  = "numerator"
    ValuesName    = "acceptance"

    if use125p9:
        Mass = "125_09"
        
    InFileName   = "Dictionary_"+ValuesName+"Factor_"+Mass+"_nominal.json"
                
    json_file    = open(InDir+InFileName)
    json_string  = json_file.read()
    json_data    = json.loads(json_string)
    AllValues    = json_data[SearchString+"s"]
    AllValuesErr = json_data[SearchString+"_errors"]

    #define out file
    outFile      = None
    if doFiducial:
        outFile = TFile("../MakeUnfoldedPlots/expected/standard.root","update")
    else:
        outFile = TFile("../MakeUnfoldedPlots/expected/standard.root","recreate")

        
    if doFiducial:

        print "Creating Expected Nominal Histograms for Fiducial \n"
        
        #xsec = [ 4.858E+01,
        #         3.782E+00,
        #         1.373E+00,
        #         8.839E-01,
        #         5.071E-01,
	#         4.880E-01,
	#         
	#         
        #print "blabla"
        #
        #theory = [+4.6	-6.7,
        #          +0.4	-0.3,
        #          +0.5	-0.7,
        #          +3.8	-3.1,
        #          +5.8	-9.2
        #          +20.2	-23.9
        #          
        #pdf = [pm 3.2,
        #       pm 2.1,
        #       pm 1.9,
        #       pm 1.6,
        #       pm 3.6

        for v in FidVarBin:
            
            values  = AllValues[v[0]]
            print "Processing Variable ",v[0]

            outFile.cd()
            Hggf = TH1F("fid_ggHNNLOPS", "fid_ggHNNLOPS", len(DecayChannels), 0., len(DecayChannels))
            Hvbf = TH1F("fid_VBF"      , "fid_VBF"      , len(DecayChannels), 0., len(DecayChannels))
            Hwh  = TH1F("fid_WH"       , "fid_WH"       , len(DecayChannels), 0., len(DecayChannels))
            Hzh  = TH1F("fid_ZH"       , "fid_ZH"       , len(DecayChannels), 0., len(DecayChannels))
            Htth = TH1F("fid_ttH"      , "fid_ttH"      , len(DecayChannels), 0., len(DecayChannels))
            Hbbh = TH1F("fid_bbH"      , "fid_bbH"      , len(DecayChannels), 0., len(DecayChannels))

            for b in range(0,v[1]):
                
                for dc in DecayChannels:

                    Hggf.SetBinContent( dc[1]+1, values[pm_ggH][dc[1]][b] )
                    Hvbf.SetBinContent( dc[1]+1, values[pm_VBF][dc[1]][b] )
                    Hwh.SetBinContent(  dc[1]+1, values[pm_WH][dc[1]][b]  )
                    Hzh.SetBinContent(  dc[1]+1, values[pm_ZH][dc[1]][b]  )
                    Htth.SetBinContent( dc[1]+1, values[pm_ttH][dc[1]][b] )
                    Hbbh.SetBinContent( dc[1]+1, values[pm_bbH][dc[1]][b] )

            print ""
            Hggf.Write()
            Hvbf.Write()
            Hwh.Write()
            Hzh.Write()
            Htth.Write()
            Hbbh.Write()
            
        outFile.Close();
        
    else:

        print "Creating Expected Nominal Histograms for Differential \n"
        
        for v in DiffVarBin:

            outFile.cd()
            Hggf = TH1F(v[2]+"_ggHNNLOPS", v[2]+"_ggHNNLOPS", v[1], 0., v[1])
            Hvbf = TH1F(v[2]+"_VBF"      , v[2]+"_VBF"      , v[1], 0., v[1])
            Hwh  = TH1F(v[2]+"_WH"       , v[2]+"_WH"       , v[1], 0., v[1])
            Hzh  = TH1F(v[2]+"_ZH"       , v[2]+"_ZH"       , v[1], 0., v[1])
            Htth = TH1F(v[2]+"_ttH"      , v[2]+"_ttH"      , v[1], 0., v[1])
            Hbbh = TH1F(v[2]+"_bbH"      , v[2]+"_bbH"      , v[1], 0., v[1])

            values  = AllValues[v[0]]
            
            print "Processing Variable ",v[0]
           
            for b in range(0,v[1]):

                Hggf.SetBinContent( b+1, values[pm_ggH][dc_incl][b] )
                Hvbf.SetBinContent( b+1, values[pm_VBF][dc_incl][b] )
                Hwh.SetBinContent(  b+1, values[pm_WH][dc_incl][b]  )
                Hzh.SetBinContent(  b+1, values[pm_ZH][dc_incl][b]  )
                Htth.SetBinContent( b+1, values[pm_ttH][dc_incl][b] )
                Hbbh.SetBinContent( b+1, values[pm_bbH][dc_incl][b] )

            print ""
            Hggf.Write()
            Hvbf.Write()
            Hwh.Write()
            Hzh.Write()
            Htth.Write()
            Hbbh.Write()

        outFile.Close()
    

def DeriveSys(m_fid, m_125p9, m_precision):
  
    #Configuration
    use125p9       = m_125p9
    Precision      = "%0."+str(m_precision)+"f"
    doFiducial     = m_fid
    
    InDir         = "OrigVal/"
    OutDir        = "Values/"
    Mass          = "125_0"
    OutFilePrefix = "CF"
    SearchString  = "numerator"
    ValuesName    = "acceptance"
    
    if use125p9:
        Mass = "125_09"
    
    InFileName = [ #["Dictionary_acceptance_PdfTheory_nominal.json"  , "PdfTheory"  ],
                   #["Dictionary_acceptance_ScaleTheory_nominal.json", "ScaleTheory"]
                   ["Dictionary_acceptance_PdfTheory_sys.json"  , "PdfTheory"  ],
                   ["Dictionary_acceptance_ScaleTheory_sys.json", "ScaleTheory"] ]
    
      
    for file in InFileName:

        json_file    = open(InDir+file[0])
        json_string  = json_file.read()
        json_data    = json.loads(json_string)
        AllValues    = json_data[file[1]]
        outFile      = TFile("../MakeUnfoldedPlots/expected/standard.root","update")

        if doFiducial:

            print "Creating "+file[1]+" Uncertainties (Up/Down) for Fiducial \n"
            
            for v in FidVarBin:
            
                print "Processing Variable ",v[0]
                values  = AllValues[v[0]]

                outFile.cd()
                Hggf_nom = outFile.Get("fid_ggHNNLOPS")
                Hvbf_nom = outFile.Get("fid_VBF")
                Hwh_nom  = outFile.Get("fid_WH")
                Hzh_nom  = outFile.Get("fid_ZH")
                Htth_nom = outFile.Get("fid_ttH")
                Hbbh_nom = outFile.Get("fid_bbH")

                Hggf_up = TH1F("fid_ggHNNLOPS_"+file[1]+"up", "fid_ggHNNLOPS_"+file[1]+"up", len(DecayChannels), 0., len(DecayChannels))
                Hvbf_up = TH1F("fid_VBF_"+file[1]+"up"      , "fid_VBF_"+file[1]+"up"      , len(DecayChannels), 0., len(DecayChannels))
                Hwh_up  = TH1F("fid_WH_"+file[1]+"up"       , "fid_WH_"+file[1]+"up"       , len(DecayChannels), 0., len(DecayChannels))
                Hzh_up  = TH1F("fid_ZH_"+file[1]+"up"       , "fid_ZH_"+file[1]+"up"       , len(DecayChannels), 0., len(DecayChannels))
                Htth_up = TH1F("fid_ttH_"+file[1]+"up"      , "fid_ttH_"+file[1]+"up"      , len(DecayChannels), 0., len(DecayChannels))
                Hbbh_up = TH1F("fid_bbH_"+file[1]+"up"      , "fid_bbH_"+file[1]+"up"      , len(DecayChannels), 0., len(DecayChannels))
            
                Hggf_down = TH1F("fid_ggHNNLOPS_"+file[1]+"down", "fid_ggHNNLOPS_"+file[1]+"down", len(DecayChannels), 0., len(DecayChannels))
                Hvbf_down = TH1F("fid_VBF_"+file[1]+"down"      , "fid_VBF_"+file[1]+"down"      , len(DecayChannels), 0., len(DecayChannels))
                Hwh_down  = TH1F("fid_WH_"+file[1]+"down"       , "fid_WH_"+file[1]+"down"       , len(DecayChannels), 0., len(DecayChannels))
                Hzh_down  = TH1F("fid_ZH_"+file[1]+"down"       , "fid_ZH_"+file[1]+"down"       , len(DecayChannels), 0., len(DecayChannels))
                Htth_down = TH1F("fid_ttH_"+file[1]+"down"      , "fid_ttH_"+file[1]+"down"      , len(DecayChannels), 0., len(DecayChannels))
                Hbbh_down = TH1F("fid_bbH_"+file[1]+"down"      , "fid_bbH_"+file[1]+"down"      , len(DecayChannels), 0., len(DecayChannels))

                for b in range(0,v[1]):
                    
                    for dc in DecayChannels:

                        Hggf_up.SetBinContent( dc[1]+1, Hggf_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_ggH][dc[1]][b][0])) )
                        Hvbf_up.SetBinContent( dc[1]+1, Hvbf_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_VBF][dc[1]][b][0])) )
                        Hwh_up.SetBinContent(  dc[1]+1, Hwh_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_WH][dc[1]][b][0]))   )
                        Hzh_up.SetBinContent(  dc[1]+1, Hzh_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_ZH][dc[1]][b][0]))   )
                        Htth_up.SetBinContent( dc[1]+1, Htth_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_ttH][dc[1]][b][0])) )
                        Hbbh_up.SetBinContent( dc[1]+1, Hbbh_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_bbH][dc[1]][b][0])) )
                        
                        Hggf_down.SetBinContent( dc[1]+1, Hggf_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_ggH][dc[1]][b][1])) )
                        Hvbf_down.SetBinContent( dc[1]+1, Hvbf_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_VBF][dc[1]][b][1])) )
                        Hwh_down.SetBinContent(  dc[1]+1, Hwh_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_WH][dc[1]][b][1]))   )
                        Hzh_down.SetBinContent(  dc[1]+1, Hzh_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_ZH][dc[1]][b][1]))   )
                        Htth_down.SetBinContent( dc[1]+1, Htth_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_ttH][dc[1]][b][1])) )
                        Hbbh_down.SetBinContent( dc[1]+1, Hbbh_nom.GetBinContent(dc[1]+1)*(1+float(values[pm_bbH][dc[1]][b][1])) )

                print ""
                Hggf_up.Write()
                Hvbf_up.Write()
                Hwh_up.Write()
                Hzh_up.Write()
                Htth_up.Write()
                Hbbh_up.Write()
                
                Hggf_down.Write()
                Hvbf_down.Write()
                Hwh_down.Write()
                Hzh_down.Write()
                Htth_down.Write()
                Hbbh_down.Write()
      
            outFile.Close()
            
        else:

            print "Creating "+file[1]+" Uncertainties (Up/Down) for Differential \n"
            
            for v in DiffVarBin:

                print "Processing Variable ",v[0]

                values  = AllValues[v[0]]

                outFile.cd()
                Hggf_nom = outFile.Get(v[2]+"_ggHNNLOPS")
                Hvbf_nom = outFile.Get(v[2]+"_VBF")
                Hwh_nom  = outFile.Get(v[2]+"_WH")
                Hzh_nom  = outFile.Get(v[2]+"_ZH")
                Htth_nom = outFile.Get(v[2]+"_ttH")
                Hbbh_nom = outFile.Get(v[2]+"_bbH")
            
                Hggf_up = TH1F(v[2]+"_ggHNNLOPS_"+file[1]+"up", v[2]+"_ggHNNLOPS_"+file[1]+"up", v[1], 0., v[1])
                Hvbf_up = TH1F(v[2]+"_VBF_"+file[1]+"up"      , v[2]+"_VBF_"+file[1]+"up"      , v[1], 0., v[1])
                Hwh_up  = TH1F(v[2]+"_WH_"+file[1]+"up"       , v[2]+"_WH_"+file[1]+"up"       , v[1], 0., v[1])
                Hzh_up  = TH1F(v[2]+"_ZH_"+file[1]+"up"       , v[2]+"_ZH_"+file[1]+"up"       , v[1], 0., v[1])
                Htth_up = TH1F(v[2]+"_ttH_"+file[1]+"up"      , v[2]+"_ttH_"+file[1]+"up"      , v[1], 0., v[1])
                Hbbh_up = TH1F(v[2]+"_bbH_"+file[1]+"up"      , v[2]+"_bbH_"+file[1]+"up"      , v[1], 0., v[1])
            
                Hggf_down = TH1F(v[2]+"_ggHNNLOPS_"+file[1]+"down", v[2]+"_ggHNNLOPS_"+file[1]+"down", v[1], 0., v[1])
                Hvbf_down = TH1F(v[2]+"_VBF_"+file[1]+"down"      , v[2]+"_VBF_"+file[1]+"down"      , v[1], 0., v[1])
                Hwh_down  = TH1F(v[2]+"_WH_"+file[1]+"down"       , v[2]+"_WH_"+file[1]+"down"       , v[1], 0., v[1])
                Hzh_down  = TH1F(v[2]+"_ZH_"+file[1]+"down"       , v[2]+"_ZH_"+file[1]+"down"       , v[1], 0., v[1])
                Htth_down = TH1F(v[2]+"_ttH_"+file[1]+"down"      , v[2]+"_ttH_"+file[1]+"down"      , v[1], 0., v[1])
                Hbbh_down = TH1F(v[2]+"_bbH_"+file[1]+"down"      , v[2]+"_bbH_"+file[1]+"down"      , v[1], 0., v[1])
                
                for b in range(0,v[1]):
                  
                    Hggf_up.SetBinContent( b+1, Hggf_nom.GetBinContent(b+1)*(1+float(values[pm_ggH][dc_incl][b][0])) )
                    Hvbf_up.SetBinContent( b+1, Hvbf_nom.GetBinContent(b+1)*(1+float(values[pm_VBF][dc_incl][b][0])) )
                    Hwh_up.SetBinContent(  b+1, Hwh_nom.GetBinContent(b+1)*(1+float(values[pm_WH][dc_incl][b][0]))   )
                    Hzh_up.SetBinContent(  b+1, Hzh_nom.GetBinContent(b+1)*(1+float(values[pm_ZH][dc_incl][b][0]))   )
                    Htth_up.SetBinContent( b+1, Htth_nom.GetBinContent(b+1)*(1+float(values[pm_ttH][dc_incl][b][0])) )
                    Hbbh_up.SetBinContent( b+1, Hbbh_nom.GetBinContent(b+1)*(1+float(values[pm_bbH][dc_incl][b][0])) )
            
                    Hggf_down.SetBinContent( b+1, Hggf_nom.GetBinContent(b+1)*(1+float(values[pm_ggH][dc_incl][b][1])) )
                    Hvbf_down.SetBinContent( b+1, Hvbf_nom.GetBinContent(b+1)*(1+float(values[pm_VBF][dc_incl][b][1])) )
                    Hwh_down.SetBinContent(  b+1, Hwh_nom.GetBinContent(b+1)*(1+float(values[pm_WH][dc_incl][b][1]))   )
                    Hzh_down.SetBinContent(  b+1, Hzh_nom.GetBinContent(b+1)*(1+float(values[pm_ZH][dc_incl][b][1]))   )
                    Htth_down.SetBinContent( b+1, Htth_nom.GetBinContent(b+1)*(1+float(values[pm_ttH][dc_incl][b][1])) )
                    Hbbh_down.SetBinContent( b+1, Hbbh_nom.GetBinContent(b+1)*(1+float(values[pm_bbH][dc_incl][b][1])) )
                    print  str(Hggf_nom.GetBinContent(b+1))+" " + str(Hggf_nom.GetBinContent(b+1)*(1+float(values[pm_ggH][dc_incl][b][0]))) + " "+str(Hggf_nom.GetBinContent(b+1)*(1+float(values[pm_ggH][dc_incl][b][1])))
                    print "vbf " + str(Hvbf_nom.GetBinContent(b+1))+" " + str(Hvbf_nom.GetBinContent(b+1)*(1+float(values[pm_VBF][dc_incl][b][0]))) + " "+str(Hvbf_nom.GetBinContent(b+1)*(1+float(values[pm_VBF][dc_incl][b][1])))

                print ""
                Hggf_up.Write()
                Hvbf_up.Write()
                Hwh_up.Write()
                Hzh_up.Write()
                Htth_up.Write()
                Hbbh_up.Write()
                
                Hggf_down.Write()
                Hvbf_down.Write()
                Hwh_down.Write()
                Hzh_down.Write()
                Htth_down.Write()
                Hbbh_down.Write()
      
            outFile.Close()

            

def ShowDoc():
    print ""
    print "Script to make Expected xsec histograms!"
    print "  Usage   : ./ProduceExpectedHistograms.py [Options]!"
    print "            Options:  "
    print "                     doFiducial=[True/False]  : default is 'False' -> doing Differential"
    print "                     ValPrecision=6           : default is '6'     -> using 6 digit (min value 5, max value 7)"
    print "                     use125p9=[True/False]    : default is 'False' -> using Mh=125 GeV"


if __name__ == "__main__":
    main()
