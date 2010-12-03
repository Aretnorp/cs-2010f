PROGRAM = Puppet

LIBS = \
	-lm \
	-lGLU \
	-lglut 

#Compiler options
CXXSOURCES = Arm.cpp \
	     Head.cpp \
	     Leg.cpp \
	     Menu.cpp \
	     main.cpp \
	     Person.cpp \
	     Picking.cpp \
	     MaterialColor.cpp \
	     RotationLimits.cpp \
	     ShapeContainer.cpp \
	     Shape.cpp \
	     Square.cpp \
	     Torso.cpp
CXXOBJECTS = $(CXXSOURCES:.cpp=.o)
CXXFLAGS   = -g $(INCLUDEDIRS)
CXX        = gcc
LDFLAGS    = $(LIBDIRS) $(LIBS)

#Targets
all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

Arm.o: Arm.cpp
	$(CXX) -c -o $@ Arm.cpp  $(LDFLAGS)

Head.o: Head.cpp
	$(CXX) -c -o $@ Head.cpp $(LDFLAGS)

Leg.o: Leg.cpp
	$(CXX) -c -o $@ Leg.cpp $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c -o $@ main.cpp $(LDFLAGS)

MaterialColor.o: MaterialColor.cpp
	$(CXX) -c -o $@ MaterialColor.cpp $(LDFLAGS)

Menu.o: Menu.cpp
	$(CXX) -c -o $@ Menu.cpp $(LDFLAGS)

Person.o: Person.cpp
	$(CXX) -c -o $@ Person.cpp $(LDFLAGS)

Picking.o: Picking.cpp
	$(CXX) -c -o $@ Picking.cpp $(LDFLAGS)

RotationLimits.o: RotationLimits.cpp
	$(CXX) -c -o $@ RotationLimits.cpp $(LDFLAGS)

ShapeContainer.o: ShapeContainer.cpp
	$(CXX) -c -o $@ ShapeContainer.cpp $(LDFLAGS)

Shape.o: Shape.cpp
	$(CXX) -c -o $@ Shape.cpp $(LDFLAGS)

Square.o: Square.cpp
	$(CXX) -c -o $@ Square.cpp $(LDFLAGS)

texture.o: texture.c
	$(CXX) -c -o $@ texture.cpp $(LDFLAGS)

Torso.o: Torso.cpp
	$(CXX) -c -o $@ Torso.cpp $(LDFLAGS)

clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)
