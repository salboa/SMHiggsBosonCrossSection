CXX = clang++
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

#ReadFiles
RF_OBJ  = ReadFiles.o
RF_H    = ReadFiles.h

#ZjetSys
ZJ_OBJ = ZjetSys.o
ZJ_H   = ZjetSys.h

#SigComp
SG_OBJ = SigComp.o
SG_H   = SigComp.h

##Build
all: rf zj sg

#ReadFiles
rf:	$(RF_OBJ)
	@echo ""
	@echo "Compiling objects ($(RF_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(RF_OBJ) -o ReadFiles -g $(LIBS) -lm

#ZjetSys
zj:	$(ZJ_OBJ)
	@echo ""
	@echo "Compiling objects ($(ZJ_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(ZJ_OBJ) -o ZjetSys -g $(LIBS) -lm

#SigComp
sg:	$(SG_OBJ)
	@echo ""
	@echo "Compiling objects ($(SG_OBJ)) ... "
	@$(CXX) -fPIC -D_REENTRANT $(SG_OBJ) -o SigComp -g $(LIBS) -lm

## Clean
clean:
	@echo "Cleaning path ... "
	rm -rf *.o
	rm -rf ReadFiles
	rm -rf ZjetSys
	rm -rf SigComp
	rm -rf *~
