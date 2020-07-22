# Patch for main ROOT source code #

## Patching Root ##

Do the following step to patch root:

  - step 1: copy RooStarMomentMorph.cxx and RooParamKeysPdf.cxx in
    path_to_root/roofit/roofit/src
```
cp Adds/RooStarMomentMorph.cxx Adds/RooParamKeysPdf.cxx path_to_root/roofit/roofit/src/.
```

  - step 2: copy RooStarMomentMorph.h and RooParamKeysPdf.h in
    path_to_root/roofit/roofit/inc/
```
cp Adds/RooStarMomentMorph.h Adds/RooParamKeysPdf.h path_to_root/roofit/roofit/inc/.
```

  - step 3: add in path_to_root/roofit/roofit/inc/LinkDef1.h the following lines
```
#pragma link C++ class RooParamKeysPdf+ ;
#pragma link C++ class RooStarMomentMorph+ ;
```

  - step 4: copy RooBSplineBases.cxx and RooBSpline.cxx in path_to_root/roofit/roostats/src
```
cp Adds/RooBSplineBases.cxx Adds/RooBSpline.cxx path_to_root/roofit/roostats/src/.
```

  - step 5:     copy RooBSplineBases.h and RooBSpline.h in path_to_root/roofit/roostats/inc/RooStats
```
cp Adds/RooBSplineBases.h Adds/RooBSpline.h path_to_root/roofit/roostats/inc/RooStats/.
```

  - step 6: add in path_to_root/roofit/roostats/inc/LinkDef.h the following lines
```
#pragma link C++ class RooStats::HistFactory::RooBSplineBases+ ;
#pragma link C++ class RooStats::HistFactory::RooBSpline+ ;
```

  - AllInOne: you can simply do all previous steps typing
```
PatchROOT.py RootPath=path/to/main/root/source/dir/
```

## Compile ##

compile ROOT from scratch. <br />
Below a reminder to compile ROOT using Cmake (after having applied the patch):
  - create an empty directory outside ROOT source directory (type 'mkdir build')
  - enter inside new directory (type 'cd build/')
  - configure all options (type 'cmake -D all=ON ../path_to_source')
  - compile (type 'cmake --build . -- -j2')

## Test new compiled ROOT ##

Try new compiled ROOT version typing
```
root -l test.C
```
located in this directory

for RCpp errors install within r install.packages("Rcpp", type="source"), install.packages("RInside", type="source")
