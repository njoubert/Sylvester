#My Code   -------------------------------

TARGET      := Sylvester
SRCDIR      := src
INCLUDEDIR  := include

#Basic Config -----------------------------------------------------------------

CXX := g++
LINKER := g++

CXXFILES    := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/json/*.cpp)
HEADERS     := $(wildcard $(INCLUDEDIR)/*.h) $(wildcard $(INCLUDEDIR)/json/*.h)
CFLAGS      := -W -Wall -I -pthread -g

INCLUDE := -I$(INCLUDEDIR)/ -Ilib/
CXXFLAGS := -g -Wall -O3 -fmessage-length=0 $(INCLUDE)
LDFLAGS := 
LIBS :=
#Rules -----------------------------------------------------------------

lib/mongoose.o: 
	$(CC) $(CFLAGS) -c lib/mongoose/mongoose.c -o lib/mongoose.o

LIBS += lib/mongoose.o
#Mongoose --------------------------------------------------------------

CXX_OBJS     := $(CXXFILES:.cpp=.o)

%.o : %.cpp $(HEADERS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)


$(TARGET): $(CXX_OBJS) $(HEADERS) $(LIBS)
	$(LINKER) -o $(TARGET) $(CXX_OBJS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(EXECUTABLE) $(CXX_OBJS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.DEFAULT_GOAL := $(TARGET)