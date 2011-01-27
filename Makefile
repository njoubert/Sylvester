
SRCDIR      := src
INCLUDEDIR  := include

CXX := g++
LINKER := g++

# All CXX files grouped by sub-namespace
JSON_CXXFILES      := $(wildcard $(SRCDIR)/json/*.cpp)
SERVER_CXXFILES    := $(wildcard $(SRCDIR)/Sylvester/Server/*.cpp)
CXXFILES           := $(JSON_CXXFILES) $(SERVER_CXXFILES)

# All Header files grouped by sub-namespace
JSON_HEADERS       := $(wildcard $(INCLUDEDIR)/json/*.h)
SERVER_HEADERS     := $(wildcard $(INCLUDEDIR)/Sylvester/Server/*.h)
HEADERS            := $(JSON_HEADERS) $(SERVER_HEADERS)

CFLAGS      := -W -Wall -I -pthread -g
INCLUDE := -I$(INCLUDEDIR)/ -Ilib/
CXXFLAGS := -g -Wall -O3 -fmessage-length=0 $(INCLUDE)
LDFLAGS := 
LIBS := lib/mongoose.o

#Rules -----------------------------------------------------------------

JSON_CXXOBJS     := $(JSON_CXXFILES:.cpp=.o)
SERVER_CXXOBJS     := $(SERVER_CXXFILES:.cpp=.o)

%.o : %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

server: $(SERVER_CXXOBJS) $(JSON_CXXOBJS) $(SERVER_HEADERS) $(JSON_HEADERS) $(LIBS)
	$(LINKER) -o server $(SERVER_CXXOBJS) $(JSON_CXXOBJS) $(LDFLAGS) $(LIBS)

lint:
	$(foreach myfile,$(SERVER_HEADERS),python cpplint.py --filter=-whitespace $(myfile);)
	$(foreach myfile,$(SERVER_CXXFILES),python cpplint.py --filter=-whitespace $(myfile);)

clean:
	rm -f server $(JSON_CXXOBJS) $(SERVER_CXXOBJS)

.DEFAULT_GOAL := server

#Libraries -----------------------------------------------------------------

lib/mongoose.o: 
	$(CC) $(CFLAGS) -c lib/mongoose/mongoose.c -o lib/mongoose.o
