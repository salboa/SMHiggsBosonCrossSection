#include "TSystem.h"
void loadClasses (Option_t* opt="k")
{
  //  Load classes required by ATLAS Higgs workspaces
  TString dir= TString(gSystem->DirName(__FILE__))+"/";
  gSystem->CompileMacro(dir+"RooBSplineBases.cxx",    opt);
  gSystem->CompileMacro(dir+"RooBSpline.cxx",         opt);
  gSystem->CompileMacro(dir+"RooParamKeysPdf.cxx",    opt);
  gSystem->CompileMacro(dir+"RooStarMomentMorph.cxx", opt);
}
