PROGRAM = main

LIBS = \
	-lcurl \

#Compiler options
CXXSOURCES = crc/crc.c main.c
CXXOBJECTS = $(CXXSOURCES:.c=.o)
CXXFLAGS   = -g $(INCLUDEDIRS)
CXX        = gcc
LDFLAGS    = $(LIBDIRS) $(LIBS)

#Targets
all: $(PROGRAM)

$(PROGRAM): main.o crc.o
	$(CXX) -o $@ main.o crc.o $(LDFLAGS)

main.o: main.c main.h
	$(CXX) $(CXXFLAGS) -c -o main.o main.c

crc.o: crc/crc.c crc/crc.h
	$(CXX) $(CXXFLAGS) -c -o crc.o crc/crc.c

clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)
