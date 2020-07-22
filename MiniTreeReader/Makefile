CXX = clang++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CXX = g++
endif

CXXFLAGS = -O -Wall -fPIC

## Libs
ROOTCXXFLAGS = $(shell root-config --cflags)
ROOTLDFLAGS  = $(shell root-config --ldflags)
ROOTLIBS     = $(shell root-config --libs)
ROOTGLIBS    = $(shell root-config --glibs)

LIBS = $(ROOTLIBS)

CXXFLAGS += $(ROOTCXXFLAGS)

#MakeInput
MI_OBJ  = MakeInput.o
MI_H    = MakeInput.h
MI_DIC  = Dic_MakeInput.cxx
MI_LDEF = LinkDef_MakeInput.h
MI_LIB  = libMakeInput.so

#doPlots
DP_OBJ  = doPlots.o
DP_H    = doPlots.h
DP_DIC  = Dic_doPlots.cxx
DP_LDEF = LinkDef_doPlots.h
DP_LIB  = libdoPlots.so

#ShapeSysVar
SS_OBJ  = ShapeSysVar.o

#shapeComp
SC_OBJ  = shapeComp.o

#PlotSys
PS_OBJ  = PlotsSys.o

##Build
all: dicmi mi libmi dicdp dp libdp ss sc ps

#MakeInput 
dicmi: $(MI_H)
	@echo ""
	@echo "Building MakeInput dictionary ... "
	@rootcint -f $(MI_DIC) -c $(CXXFLAGSPKG) -p $(MI_H) $(MI_LDEF)

mi:	$(MI_OBJ)
	@echo ""
	@echo "Compiling objects ($(MI_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(MI_OBJ) $(ROOTLDFLAGS) -o MakeInput -g $(LIBS) -lm -lEG

#doPlots
libdp: $(DP_OBJ)
	@echo""
	@echo "Linking library ($(DP_LIB)) ... "
	@$(CXX) $(CXXFLAGS) -shared $(LIBS) $(DP_OBJ) -o $(DP_LIB)

dicdp: $(DP_H)
	@echo ""
	@echo "Building doPlots dictionary ... "
	@rootcint -f $(DP_DIC) -c $(CXXFLAGSPKG) -p $(DP_H) $(DP_LDEF)

dp:	$(DP_OBJ)
	@echo ""
	@echo "Compiling objects ($(DP_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(DP_OBJ) $(ROOTLDFLAGS) -o doPlots -g $(LIBS) -lm -lEG

libmi: $(DP_OBJ)
	@echo""
	@echo "Linking library ($(DP_LIB)) ... "
	@$(CXX) $(CXXFLAGS) -shared $(LIBS) $(DP_OBJ) -o $(DP_LIB)

#ShapeSys
ss:	$(SS_OBJ)
	@echo ""
	@echo "Compiling objects ($(SS_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(SS_OBJ) $(ROOTLDFLAGS) -o ShapeSysVar -g $(LIBS) -lm -lEG

#shapeComp
sc:	$(SC_OBJ)
	@echo ""
	@echo "Compiling objects ($(SC_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(SC_OBJ) $(ROOTLDFLAGS) -o shapeComp -g $(LIBS) -lm -lEG

ps:	$(PS_OBJ)
	@echo ""
	@echo "Compiling objects ($(PS_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(PS_OBJ) $(ROOTLDFLAGS) -o PlotsSys -g $(LIBS) -lm -lEG

## Clean
clean:
	@echo "Cleaning path ... "
	rm -rf *.o
	rm -rf MakeInput
	rm -rf ShapeSysVar
	rm -rf doPlots
	rm -rf shapeComp
	rm -rf PlotsSys
	rm -rf *~
	rm -rf *.so
	rm -rf *.pcm
	rm -rf Dic_MakeInput*
	rm -rf Dic_doPlots*
	rm -rf *.d
