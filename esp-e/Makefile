# This is the Makefile of spec, by liigo
COMPIlER = gcc
COMPLIE_FLAGS = -w -fPIC -c -D __OS_LINUX_VER -D __GCC_ -D _NO_MFC -D NDEBUG
#-D _DEBUG

LINK_FLAGS = -shared -O2
#-O3: -O[number] Set optimisation level to [number]
#-rdynamic -ldl -lpthread -lm -s

LIBS = -L.
INCLUDE_PATH = -I elib_h
ELIB_H = /elib_h

###
all: clean got-so-and-delete-temp-file

###############################################################################
# Output esp_fne.so file
#
# $@: rule itself; $?: rule's dependence
#

esp.so: esp_fne.o fnshare.o cmem.o
	$(COMPIlER) -o$@ $? $(LIBS) $(LINK_FLAGS)


clean:
	-rm espmod.so
	-rm *.o

got-so-and-delete-temp-file: esp.so
	-rm *.o

esp_fne.o: fnshare.o
	$(COMPIlER) $(COMPLIE_FLAGS) -o$@ esp_fne.cpp $(INCLUDE_PATH)

fnshare.o: cmem.o
	$(COMPIlER) $(COMPLIE_FLAGS) -o$@ .${ELIB_H}/fnshare.c $(INCLUDE_PATH)

cmem.o:
	$(COMPIlER) $(COMPLIE_FLAGS) -o$@ .${ELIB_H}/cmem.c $(INCLUDE_PATH)

