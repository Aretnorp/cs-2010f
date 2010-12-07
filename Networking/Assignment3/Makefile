CLIENTPROGRAM = sfl
SERVERPROGRAM = sfl_proc

LIBS = -lrpcsvc

#Compiler options
CXXSOURCES = sfl.c sfl_proc.c
CXXOBJECTS = $(CXXSOURCES:.c=.o)
CXXFLAGS   = -g $(INCLUDEDIRS)
CXX        = gcc
LDFLAGS    = $(LIBDIRS) $(LIBS)
DOC        = echo 'hi'

#Targets
all: $(SERVERPROGRAM) $(CLIENTPROGRAM) doc

$(CLIENTPROGRAM): sfl.o sfl_clnt.o sfl_xdr.o
	$(CXX) -o $@ sfl.o sfl_clnt.o sfl_xdr.o $(LDFLAGS)

$(SERVERPROGRAM): sfl_proc.o sfl_svc.o sfl_xdr.o
	$(CXX) -o $@ sfl_proc.o sfl_svc.o sfl_xdr.o $(LDFLAGS)

sfl.o: sfl.c sfl.h
	$(CXX) $(CXXFLAGS) -c -o $@ sfl.c

sfl_proc.o: sfl_proc.c sfl.h
	$(CXX) $(CXXFLAGS) -c -o $@ sfl_proc.c

sfl_xdr.o: sfl.h
	$(CXX) $(CXXFLAGS) -c -o $@ sfl_xdr.c

sfl_svc.o: sfl.h
	$(CXX) $(CXXFLAGS) -c -o $@ sfl_svc.c

sfl_clnt.o: sfl.h
	$(CXX) $(CXXFLAGS) -c -o $@ sfl_clnt.c

sfl.h: sfl.x
	rpcgen -C -a sfl.x

doc:
	$(DOC)

clean:
	$(RM) -rf $(CXXOBJECTS) $(SERVERPROGRAM) $(CLIENTPROGRAM) sfl_clnt.c sfl.h sfl_xdr.c sfl_svc.c sfl_svc.o sfl_clnt.o sfl_xdr.o sfl_server.c sfl_client.c Makefile.sfl doc
