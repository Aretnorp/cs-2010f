CLIENTPROGRAM = client
SERVERPROGRAM = server

LIBS = \
	-lXm \

#Compiler options
CXXSOURCES = server2.c client.c
CXXOBJECTS = $(CXXSOURCES:.c=.o)
CXXFLAGS   = -g $(INCLUDEDIRS)
CXX        = gcc
LDFLAGS    = $(LIBDIRS) $(LIBS)
DOC        = doxygen

#Targets
all: $(SERVERPROGRAM) $(CLIENTPROGRAM) doc

$(SERVERPROGRAM): server2.o
	$(CXX) -o $@ server2.o $(LDFLAGS)

$(CLIENTPROGRAM): client.o
	$(CXX) -o $@ client.o $(LDFLAGS)

server2.o: server2.c
	$(CXX) $(CXXFLAGS) -c -o server2.o server2.c

client.o: client.c
	$(CXX) $(CXXFLAGS) -c -o client.o client.c

doc:
	$(DOC)

clean:
	$(RM) -rf $(CXXOBJECTS) $(SERVERPROGRAM) $(CLIENTPROGRAM) doc

run:
	./$(SERVERPROGRAM) 1024 . &
