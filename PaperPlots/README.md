**Table of contents:**
1. [Compile](#setup)
1. [Plotting](#plotting)

----

## 1. Setting up <a name="setup"></a>
```
cd build;
cmake ../source
make
```

## 2. Plotting <a name="plotting"></a>
You will need a folder called run/TGraphs with the tgraphs from the WScanner post process.
You will also need a folder called run/workspaces with the workspaces for data (for pVal calculation).
From run:
```
../build; make; cd ../run; ../build/makePlots --variable <fid/njets/pt> --type <cf/matrix> --calcPVal <true/false>
```
To get the pValues you only need too run --calcPVal true once (for each variable, unfolding type). It will be caches in a textFile that will be read in if you run with --calcPVal false (the default). Cached pVals will be overwrote by re-running calcPVal