PROGRAM = SBA

LIBS = \
	-lm \
	-lGLU \
	-lglut 

#Compiler options
CXXSOURCES = main.cpp \
	     Menu.cpp \
	     normal.cpp \
	     Transformations.cpp
CXXOBJECTS = $(CXXSOURCES:.cpp=.o)
CXXFLAGS   = -g $(INCLUDEDIRS)
CXX        = gcc
LDFLAGS    = $(LIBDIRS) $(LIBS)

#Targets
all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c -o $@ main.cpp $(LDFLAGS)

Menu.o: Menu.cpp
	$(CXX) -c -o $@ Menu.cpp $(LDFLAGS)

normal.o: normal.cpp
	$(CXX) -c -o $@ normal.cpp $(LDFLAGS)

Transformations.o: Transformations.cpp
	$(CXX) -c -o $@ Transformations.cpp $(LDFLAGS)

clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)
