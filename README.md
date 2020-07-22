#              Directories Structure              #

## LatexTemplate ##

  - standard template for slides making

## MakeUnfoldedPlots ##

  - MakeUnfoldPlots.C -> script used to make unfolded plots
  - RunMakeUnfold.py  -> python script handling MakeUnfoldPlots.C

## MiniTreeReader ##

  - MakeInput.C     -> script used to read HZZ minitrees
  - RunMakeInput.py -> python script handling MakeInput.C
  - doPlots.C       -> distributions maker
  - PrintYields.C   -> prints signal, bkg and data yields
  - ShapeSysVar     -> arrange shape systematic histograms

## RooAddOn ##

  - Contains addon needed by XsecClass
  - PatchROOT.py -> patches ROOT source
  - refer to its specific README to apply patch and compile ROOT

## ValReader ##

  - ReadFiles.C     -> script to translate systematic values files from
    		       standard input to WorkSpaceMaker like input
  - ProduceFiles.py -> Make input data files for WorkSpaceMaker class, handling
    		       ReadFiles.C for systematic values

## XsecClass ##

  - for fiducial and differential xsec studies
  - just type 'make' to compile it
  - to have a look to all possible options of the clase, type
    './WorkSpaceMaker --help'; below the output
```
WorkSpaceMaker: Make WorkSpace for HZZ4l xsec measurement!!
  Usage  :  WorkSpaceMaker [Options]
             --Variable [Define variable to be used -> possible choices:
                         'pt', 'pt0j', 'pt1j', 'pt2j', 'm12', 'm34', 'y'
                         'njet', 'cts', 'ljpt']
             --Channel  [Define channel to be used -> possible choices:
                         'incl', '4mu', '4e', '2mu2e', '2e2mu']
             --FileName [Set ROOT filename to be used: default is ' ']
             --DataPath [Specify path to CF, A, xsec, r files: 
                         default is '']
             --FidChan [Enable Fiducial single channel xsec measurement:
                         default is 'false']
             --FidTotal [Enable Fiducial total xsec measurement:
                         default is 'false']
             --Fid4l [Enable Fiducial total xsec measurement for 4l case
                      (4e+4mu): default is 'false']
             --Fid2l2l [Enable Fiducial total xsec measurement for 2l2l
                        case (2e2mu+2mu2e): default is 'false']
             --FidSum [Enable Fiducial xsec measurement summing all
                       channels (4e+4mu+2e2mu+2mu2e): default is 'false']
             --do2D     [Enable 2D: default is 'false'
             --addSys   [Use Systematics: default is 'false']
             --debug    [Set debug mode: default is 'false']
             --verbose  [Set verbose mode: default is 'false']
             --lumi     [Set luminosity: default is '35' 1/fb]
             --doFit    [Enable fit at the end of ws creation]
             --parallel [Enable fit in parallel mode preliminary]
             --help     [Print this help]
  
          -------------------   REMARKS -----------------
             --Variable option is needed when none of fiducial
                        measurement flag is enabled.
             --Channel option is needed when none of fiducial
                        measurement flag is enabled, but for now 'incl'
                        is used as default
```

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