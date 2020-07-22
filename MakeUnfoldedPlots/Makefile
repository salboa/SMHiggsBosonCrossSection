CXX = clang++
RINT=-DWITHRINT
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CXX = g++ -std=c++11
endif

CXXFLAGS = -O -Wall -fPIC

## Libs
ROOTCXXFLAGS = $(shell root-config --cflags)
ROOTLDFLAGS  = $(shell root-config --ldflags)
ROOTLIBS     = $(shell root-config --libs)
ROOTGLIBS    = $(shell root-config --glibs)

LIBS = $(ROOTLIBS)

CXXFLAGS += $(ROOTCXXFLAGS)

#use TRint or TApplication
CXXFLAGS += $(RINT)

#MakeUnfoldefPlots
RF_OBJ = MakeUnfoldPlots.o
RF_H   = MakeUnfoldPlots.h

##Build
all: rf

#MakeUnfoldedPlots
rf:	$(RF_OBJ)
	@echo ""
	@echo "Compiling objects ($(RF_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(RF_OBJ) -o UnfoldPlots -g $(LIBS) -lm

## Clean
clean:
	@echo "Cleaning path ... "
	rm -rf *.o
	rm -rf UnfoldPlots
	rm -rf *~
