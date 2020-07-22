#              MiniTreeReader              #


## CreateInputs + EventLoop ## 

   This class allows to produce histograms and all needed inputs to perform the
   Higgs Boson fiducial and differential cross section measurement using
   the 4-leptons decay channel.

   In the following README we will call some quantities as:
   A       = Acceptance
   cF      = correction factor
   rF      = phase space fraction
   fnonFid = non fiducial fraction
   rspmtx  = efficiency matrix
   migmtx  = migration matrix

   How to compile:
   - make sure you have a working ROOT 6 installation
   - type 'make'
   - in case you would like to enable the verbose mode, type 'make debug'

   How to run:
   - Typying './CreateInputs --help' you will have the following output:
```
CreateInputs: Run HZZ xsec inputs maker !!
  usage  :  ./CreateInputs [--help] [--Process] [--nBins]
                           [--sysNumber] [--mcType] [--stxtStage]
                           [--Min] [--Max] [--doShiftUp]
                           [--doShiftDown] [--isControlReg]
                           [--isCouplings] [--doACRfactor]
                           [--useMtxMode] [--writeEvtList]
                           [--acrDetails] [--split_cF]
                           [--useRootThMtc] [--variable]
                           [--restrictJets] [--checkDuplicates]
                           [--procXStoScale] [--valXStoScale]
                           [--debug]
                                                                 
 Optional arguments (default value): 
 --help            print this help and exit
 --Process         set physics process. Options are: 'ggH', 'VBF',
                   'WH', 'ZH', 'ttH', 'AllSig', qqZZ', 'ggZZ',
                   'Zjets', 'redBkg'
 --variable        set variable to process ( = all)
 --nBins           set Number of bins for m4l plots (30)
 --Min             set Lower m4l range (115)
 --Max             set Upper m4l range (130)
 --sysNumber       specify sys number (0)
 --mcType          set MC releases to be used (0). Options are: 
                   0 (mc16), 1 (mc15c), 2 (mc16a), 3 (mc16d)
 --stxsStage       set the STXT Stage (0). Options are: 0 (Stage0),
                   1 (Stage1), 2 (RedStage1)
 --doShiftUp       enable m4l+200 MeV shift (false)
 --doShiftDown     enable m4l-200 MeV shift (false)
 --isControlReg    enable control region mode (false)
 --isCouplings     enable couplings analysis (false)
 --doACRfactor     enable calculating A, C, r factors (false)
 --useMtxMode      enable Matrix Mode for A, C, r factors (false)
 --useRootThMtc    enable ROOT truth matching (false)
 --writeEvtList    enable writing list of selected events (false)
 --acrDetails      set printing ACR evaluation details (false)
 --split_cF        enable cF splitting into non-Fiducial (false)
 --restrictJets    restrict jets phase space (false)
 --checkDuplicates enable check for events duplicates (false)
 --procXStoScale   specify the process to which scale the XS ('')
 --valXStoScale    specify the XS scaling value (0). N.B: if set to
                   -10, the code will decrese XS value by 10%
 --debug           set debug mode (false)
```

  Outputs:
  - depending on the options set, this class will store information in dat files
    (in folder ../ValReader/Values) and/or ROOT files (in folder ../varsdistro/)
    and they will be used by WorkSpaceMaker class as inputs to perform the
    measurement
  - output ROOT files are set to have name
    XsecInputs_Nbin_ACRfactors_MCTYPE.root      -> containing histograms of
    						   A, cF, fNonFid
    XsecInputs_Nbin_MatrixARfactors_MCTYPE.root -> containing histograms of
     						   A, fNonFid, rsptmtx, migmtx
    XsecInputs_Nbin_MCTYPE.root                 -> containing histograms of
    						   processes distributions
    where
    N      = number of bins of the signal region chosen
    MCTYPE = name of the Monte Carlo version used (mc16 means merging of all
             mc16 versions)

    In case of systematic set enabled, you will find in the outname also the
    process and the systematic set names.

  Some examples:
  - Deriving A, cF, rF, fnonFid use the option --doACRfactor
  - Deriving A, rF, fnonFid, migmtx, rspmtx use the option --useMtxMode
  - Making contro region (orthogonal to signal region) process distributions
    use the option --isControlReg
  - running over a single variable (default option is to process all) use the
    option --variable VARNAME where VARNAME can be found in
    ../Utils/VarHandler.h


## GetMiniTrees.py ##

  