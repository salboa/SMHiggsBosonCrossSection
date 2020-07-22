CXX = clang++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CXX = g++
endif

CXXFLAGS = -O3 -Wall -fPIC -DNDEBUG -g

## Libs
ROOTCXXFLAGS = $(shell root-config --cflags)
ROOTLDFLAGS  = $(shell root-config --ldflags)
ROOTLIBS     = $(shell root-config --libs)
ROOTGLIBS    = $(shell root-config --glibs)

LIBS = $(ROOTLIBS)

CXXFLAGS += $(ROOTCXXFLAGS)

#MakeInput
MI_OBJ  = CreateInputs.o
MI_H    = CreateInputs.h
MI_DIC  = Dic_CreateInputs.cxx
MI_LDEF = LinkDef_CreateInputs.h
MI_LIB  = libCreateInputs.so

#EvtListScan
ES_OBJ  = EvtListScan.o

##shapeComp
#SC_OBJ  = shapeComp.o
#
##PlotSys
#PS_OBJ  = PlotsSys.o

##Build
all: dicCi Ci libCi es #libdp ss sc ps
CreateInputs:  dicCi Ci libCi
EventList: es

#MakeInput 
dicCi: $(MI_H)
	@echo ""
	@echo "Building CreateInputs dictionary ... "
	@rootcint -f $(MI_DIC) -c $(CXXFLAGSPKG) -p $(MI_H) $(MI_LDEF)

Ci:	$(MI_OBJ)
	@echo ""
	@echo "Compiling objects ($(MI_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(MI_OBJ) $(ROOTLDFLAGS) -o CreateInputs -g $(LIBS) -lm -lEG

libCi: $(MI_OBJ)
	@echo""
	@echo "Linking library ($(MI_LIB)) ... "
	@$(CXX) $(CXXFLAGS) -shared $(LIBS) $(MI_OBJ) -o $(MI_LIB)

#EvtListScan
es:	$(ES_OBJ)
	@echo ""
	@echo "Compiling objects ($(ES_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(ES_OBJ) $(ROOTLDFLAGS) -o EvtListScan -g $(LIBS) -lm -lEG

#debug mode
debug: CXXFLAGS += -DDEBUG -g
debug: all

## Clean
clean:
	@echo "Cleaning path ... "
	rm -rf *.o
	rm -rf CreateInputs
	rm -rf EvtListScan
	rm -rf *~
	rm -rf *.so
	rm -rf *.pcm
	rm -rf Dic_CreateInputs*
	rm -rf *.d

##help
help:
	@echo "CreateInputs and EventList tools                        "
	@echo "  options:                                              "
	@echo "    make              -> compiles both CreateInputs and "
	@echo "                         EventList                      "
	@echo "    make CreateInputs -> compiles CreateInputs          "
	@echo "    make EventList    -> compiles EventList             "
	@echo "    make debug        -> compiles all in debug mode     "
	@echo "    make clean        -> removes compilation files      "
