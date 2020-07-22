#!/usr/bin/python

import os

Dir  = "/afs/cern.ch/user/z/zcyang/public/Systematics/Prod_v11/"
Diff = "Differential/"
Fid  = "Fiducial/"
File = "norm*.txt"
#File = "norm_qqZZSherpa.txt"

Vars = [ ["pt"       , "pt4l_fsr"       ],
         ["m12"      , "mZ1_fsr"        ],
         ["m34"      , "mZ2_fsr"        ],
         ["y"        , "y4l_fsr"        ],
         ["njet"     , "n_jets"         ],
         ["nbjet"    , "n_jets_btag70"  ],
         ["cts"      , "cthstr_fsr"     ],
         ["ljpt"     , "leading_jet_pt" ],
         ["mjj"      , "dijet_invmass"  ],
         ["etajj"    , "dijet_deltaeta" ],
         ["phijj"    , "dijet_deltaphi" ],
         ["m12m34"   , "mZ1_vs_mZ2"     ],
         ["ptpt"     , "pt4l_vs_njets"  ],
         ["fiducial" , ""               ] ]

for v in Vars:

    print "Downloading sys values for "+v[0]

    cmd = None
    if v[0]!="fiducial":
        cmd = "scp salvucci@lxplus.cern.ch:"+Dir+Diff+v[1]+"/"+File+" "+v[0]+"/."
    else:
        cmd = "scp salvucci@lxplus.cern.ch:"+Dir+Fid+"/"+File+" ."

    print cmd

    os.system(cmd)
