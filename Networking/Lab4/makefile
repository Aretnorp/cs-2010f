PROGRAM = lab4

LIBS = \

#Compiler options
CXXSOURCES = lab4.c
CXXOBJECTS = $(CXXSOURCES:.c=.o)
CXXFLAGS   = -g $(INCLUDEDIRS)
CXX        = gcc
LDFLAGS    = $(LIBDIRS) $(LIBS)
DOC        = doxygen

#Targets
all: $(PROGRAM)

$(PROGRAM): lab4.c
	$(CXX) -o $@ lab4.c $(LDFLAGS)

doc:
	$(DOC)

clean:
	$(RM) -rf $(CXXOBJECTS) $(PROGRAM) doc

run:
	./$(SERVERPROGRAM) 1024 . &
