#My Code   -------------------------------

TARGET      := Sylvester
SRCDIR      := src
INCLUDEDIR  := include
OBJDIR      := obj

#Basic Config -----------------------------------------------------------------

CXX := g++
LINKER := g++

CXXFILES    := $(wildcard $(SRCDIR)/*.cpp)
CFLAGS      := -W -Wall -I -pthread -g
HEADERS     := $(wildcard $(INCLUDEDIR)/*.h)
INCLUDE := -I$(INCLUDEDIR)/ -Ilib/
CXXFLAGS := -g -Wall -O3 -fmessage-length=0 $(INCLUDE)
LDFLAGS := 
LIBS :=
#Rules -----------------------------------------------------------------

lib/mongoose.o: 
	$(CC) $(CFLAGS) -c lib/mongoose/mongoose.c -o lib/mongoose.o

LIBS += lib/mongoose.o
#Mongoose --------------------------------------------------------------

CXX_OBJS     := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(CXXFILES)))

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)


$(TARGET): $(CXX_OBJS) $(HEADERS) $(LIBS)
	$(LINKER) -o $(TARGET) $(CXX_OBJS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(EXECUTABLE) $(OBJDIR)/*.o

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.DEFAULT_GOAL := $(TARGET)