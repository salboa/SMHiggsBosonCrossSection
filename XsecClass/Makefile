CXX = clang++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
   CXX = g++
endif

CXXFLAGS = -O3 -Wall -fPIC -DNDEBUG
THREAD_LIB = -lpthread

## Libs
ROOTCXXFLAGS = $(shell root-config --cflags)
ROOTLDFLAGS  = $(shell root-config --ldflags)
ROOTLIBS     = $(shell root-config --libs)
ROOTGLIBS    = $(shell root-config --glibs)

#LIBS = ${THREAD_LIB} #-lcurses 
LIBS = $(ROOTLIBS)
LIBS += -lRooFit -lRooFitCore -lMinuit -lHistFactory -lRooStats

CXXFLAGS += $(ROOTCXXFLAGS)

#h4l
H4L_OBJ  = WorkSpaceMaker.o
H4L_H    = WorkSpaceMaker.h
H4L_DIC  = Dic_WorkSpaceMaker.cxx
H4L_LDEF = LinkDef_WorkSpaceMaker.h
H4L_LIB  = libWorkSpaceMaker.so

##Build
all: dich4l H4l libh4l

dich4l: $(H4L_H)
	@echo ""
	@echo "Building WorkSpaceMaker dictionary ... "
	@rootcint -f $(H4L_DIC) -c $(CXXFLAGSPKG) -p $(H4L_H) $(H4L_LDEF)

H4l:	$(H4L_OBJ)
	@echo ""
	@echo "Compiling objects ($(H4L_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(H4L_OBJ) $(ROOTLDFLAGS) -o WorkSpaceMaker -g $(LIBS) -lm -lEG

libh4l: $(H4L_OBJ)
	@echo""
	@echo "Linking library ($(H4L_LIB)) ... "
	@$(CXX) $(CXXFLAGS) -shared $(LIBS) $(H4L_OBJ) -o $(H4L_LIB)

## Clean
clean:
	@echo "Cleaning path ... "
	rm -rf *.o
	rm -rf WorkSpaceMaker
	rm -rf *~
	rm -rf *.so
	rm -rf *.pcm
	rm -rf Dic_WorkSpaceMaker*
	rm -rf *.d

##help
help:
	@echo "CreateInputs and EventList tools             "
	@echo "  options:                                   "
	@echo "    make       -> compiles WorkSpaceMaker    "
	@echo "    make clean -> removes compilation files  "
