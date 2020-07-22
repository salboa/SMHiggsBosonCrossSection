cmake_minimum_required(VERSION 3.9)
#cmake_policy(SET CMP0022 OLD)
project(H4lDiffPlots)

set(CMAKE_BUILD_TYPE Debug)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO EG Minuit RooFit RooFitCore RooStats HistFactory Core RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread MultiProc TMVA)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

# compile options
add_compile_options(-std=c++14 -fPIC -Wall -Wextra -Wno-unused-parameter -O2)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/PaperPlots)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Root/atlasstyle)

#---Create a shared library with generated dictionary
file(GLOB sources "Root/*.cxx")

add_library(projectLib SHARED ${sources})
target_link_libraries(projectLib ${ROOT_LIBRARIES})

#---Create  a main program using the library
add_executable(makePlots utils/makePlots.cxx)
target_link_libraries(makePlots projectLib)

#lsetup "gcc gcc620_x86_64_slc6"
#cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILE=gcc ../source/





