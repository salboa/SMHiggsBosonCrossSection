Analysis packages aiming to measure the fiducial and differential cross section
of the Higgs Boson using its 4-leptons decay channel.

#              Directories Structure              #

## MiniTreeReader ##

   Refer to in-folder README for more information

  - CreateInputs class  -> used to produce histograms and all needed inputs
  - EventLoop class     -> used to read minitrees and loop over trees
  - EvtListScan program -> used to compare 2 lists of events and find
                           (un)matching
  - GetMiniTrees.py     -> used to download to local cluster inputs minitrees
                           ROOT files
  - RunCreateInputs.py  -> used to submit jobs and to handle CreateInputs class
  

## RooAddOn ##

  Refer to in-folder README for more information

  - Contains addon needed by XsecClass
  - PatchROOT.py -> patches ROOT source


## XsecClass ##

  Refer to in-folder README for more information

  - WorkSpaceMaker class -> used to read run fiducial and differential
                            cross section measurements (it makes also a ROOT
			    workspace)
  - RunFit.py             -> used to submit jobs and handle WorkSpaceMaker class


## Plotting Tools ##

  Refer to in-folder README for more information

  - DrawFactors program -> used to make histograms of Acceptance, Correction
    			   Factor, Efficiency and Migration Matrices,
			   non-fiducial fractions and phase-space fraction


## Utils ##

   - contains all common features shared along classes inside the whole package


## GetValues ##

   - contains a cross-check code evaluating in another way the quantities needed
     to perform the fiducial and differential cross section measurement
     
### Fiducial measurement ###

  - run fiducial xsec on single channels
```
./WorkSpaceMaker --FidChan --doFit
```

  - run fiducial total xsec
```
./WorkSpaceMaker --FidTotal --doFit
```

  - run fiducial xsec for 4l category
```
./WorkSpaceMaker --Fid4l --doFit
```

  - run fiducial xsec for 2l2l category
```
./WorkSpaceMaker --Fid2l2l --doFit
```

  - run fiducial xsec summing all channels
```
./WorkSpaceMaker --FidSum --doFit
```

  - Previous examples are given without systematics. If you would enable them,
    just add --addSys at the end of each command
    
### Differential measurement ###

 - run differential xsec for pt (for any other variable just change 'pt' with
   the proper one)
```
./WorkSpaceMaker --Variable pt --doFit --do2D
```

  - Previous example is given without systematics. If you would enable them,
    just add --addSys at the end of thecommand