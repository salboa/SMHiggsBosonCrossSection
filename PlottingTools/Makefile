CXX = clang++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CXX = g++
endif

CXXFLAGS = -O -Wall -fPIC -g

## Libs
ROOTCXXFLAGS = $(shell root-config --cflags)
ROOTLDFLAGS  = $(shell root-config --ldflags)
ROOTLIBS     = $(shell root-config --libs)
ROOTGLIBS    = $(shell root-config --glibs)

LIBS = $(ROOTLIBS)
LIBS += -lRooFit -lRooFitCore -lMinuit -lHistFactory -lRooStats

CXXFLAGS += $(ROOTCXXFLAGS)

#DrawFactors
AC_OBJ = DrawFactors.o
UN_OBJ = MakeUnfoldPlots.o


##Build
all: ac un

#Plot_ACRfactors
ac:	$(AC_OBJ)
	@echo ""
	@echo "Compiling objects ($(AC_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(AC_OBJ) $(ROOTLDFLAGS) -o DrawFactors -g $(LIBS) -lm -lEG

un:     $(UN_OBJ)
	@echo
	@echo "Compiling objects ($(UN_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(UN_OBJ) -o UnfoldPlots -g $(LIBS) -lm

#debug mode
debug: CXXFLAGS += -DDEBUG -g
debug: all

## Clean
clean:
	@echo "Cleaning path ... "
	rm -rf *.o
	rm -rf DrawFactors
	rm -rf UnfoldPlots
	rm -rf *~
	rm -rf *.so
	rm -rf *.pcm
	rm -rf *.d
