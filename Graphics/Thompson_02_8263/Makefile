PROGRAM = Letter

LIBS = \
	-lm \
	-lGLU \
	-lglut \

#Compiler options
CXXSOURCES = letter.c main.c
CXXOBJECTS = $(CXXSOURCES:.c=.o)
CXXFLAGS   = -g $(INCLUDEDIRS)
CXX        = gcc
LDFLAGS    = $(LIBDIRS) $(LIBS)

#Targets
all: $(PROGRAM)

$(PROGRAM): main.o letter.o
	$(CXX) -o $@ main.o letter.o $(LDFLAGS)

main.o: main.c letter.h
	$(CXX) $(CXXFLAGS) -c -o main.o main.c

letter.o: letter.c letter.h
	$(CXX) $(CXXFLAGS) -c -o letter.o letter.c

clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)
