#!/usr/bin/python
import os
import sys

#Decay channel
dc_4mu   = 0
dc_4e    = 1
dc_2mu2e = 2
dc_2e2mu = 3
dc_incl  = 4

DecayChannels = [ ["incl" ,dc_incl ],
                  ["4mu"  ,dc_4mu  ],
                  ["4e"   ,dc_4e   ],
                  ["2mu2e",dc_2mu2e],
                  ["2e2mu",dc_2e2mu] ]
    
#production modes
pm_ggH    = 0
pm_VBF    = 1
pm_WH     = 2
pm_ZH     = 3
pm_ttH    = 4
pm_bbH    = 5
pm_AllSig = 6


#processes
Processes   = [ "ggH", "VBF", "WH", "ZH", "ttH", "bbH", "qqZZ", "ggZZ" ]

SigProdMode = [ ["ggH" , 0],
                ["VBF" , 1],
                ["WH"  , 2],
                ["ZH"  , 3],
                ["ttH" , 4],
                ["bbH" , 5] ]

#variables and bins
DiffVarBin = [ ["pt"         , 10 , "pt"    ],
               ["pt_0jet"    ,  4 , "pt0j"  ],
               ["pt_1jet"    ,  5 , "pt1j"  ],
               ["pt_2jet"    ,  2 , "pt2j"  ],
               ["m12"        ,  6 , "m12"   ],
               ["m34"        ,  7 , "m34"   ],
               ["y"          ,  7 , "y"     ],
               ["njets"      ,  4 , "njet"  ],
               ["njets1_incl",  2 , "njetv2"],
               ["njets2_incl",  3 , "njetv3"],
               ["nbjets"     ,  2 , "nbjet" ],
               ["cthstr"     ,  8 , "cts"   ],
               ["j1pt"       ,  5 , "ljpt"  ],
               ["jj_m"       ,  2 , "mjj"   ],
               ["jj_eta"     ,  2 , "etajj" ],
               ["jj_phi"     ,  2 , "phijj" ],
               ["m12m34"     ,  5 , "m12m34"] ]

DiffSystBin = [ ["pt"         , 10 , "pt"    ],
                ["m12"        ,  6 , "m12"   ],
                ["m34"        ,  7 , "m34"   ],
                ["y"          ,  7 , "y"     ],
                ["njets"      ,  4 , "njet"  ],
                ["njetv2"     ,  2 , "njetv2"],
                ["njetv3"     ,  3 , "njetv3"],
                ["nbjet"      ,  2 , "nbjet" ],
                ["cthstr"     ,  8 , "cts"   ],
                ["j1pt"       ,  5 , "ljpt"  ],
                ["jj_m"       ,  2 , "mjj"   ],
                ["jj_eta"     ,  2 , "etajj" ],
                ["jj_phi"     ,  2 , "phijj" ],
                ["m12m34"     ,  5 , "m12m34"],
                ["ptpt"       , 11 , "ptpt"  ] ]

qqZZSystBin = [ ["pt4l"         , 10 , "pt"    ],
                ["m12"          ,  6 , "m12"   ],
                ["m34"          ,  7 , "m34"   ],
                ["y4l"          ,  7 , "y"     ],
                ["Njets"        ,  4 , "njet"  ],
                ["Njetsv2"      ,  2 , "njetv2"],
                ["Njetsv3"      ,  3 , "njetv3"],
                ["Nbjets"       ,  2 , "nbjet" ],
                ["cthstr"       ,  8 , "cts"   ],
                ["leadingjetpt" ,  5 , "ljpt"  ],
                ["mjj"          ,  2 , "mjj"   ],
                ["detajj"       ,  2 , "etajj" ],
                ["dphijj"       ,  2 , "phijj" ],
                ["m12m34"       ,  5 , "m12m34"],
                ["ptpt"         , 11 , "ptpt"  ] ]

FidVarBin = [ ["inclusive",1] ]

#Signal Composistion
SigComp = [ 0.145, 0.203, 0.433, 0.468, 3.00, 0.220, 0.00 ]
