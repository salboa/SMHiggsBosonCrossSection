#!/usr/bin/python
from ROOT import *
import os


Vars  = [ "pt",   "cts",   "y",    "m12", "m34",
          "njet", "nbjet", "ljpt", "mjj", "etajj", "phijj",
          "pt0j", "pt1j",  "pt2j", "m12m34" ]

Sys   = [ "all", "muon", "electron", "jet", "qqZZ", "sig" ]

Chans = ["4mu", "4e", "2mu2e", "2e2mu" ]

for s in Sys:

  for v in Vars:
    
    cmd = "./PlotsSys --variable "+v+" --sysType "+s
    os.system(cmd)

  for c in Chans:

    cmd = "./PlotsSys --variable m --sysType "+s+" --channel "+c
    os.system(cmd)
