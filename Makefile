#My Code   -------------------------------

TARGET      := Sylvester
SRCDIR      := src
INCLUDEDIR  := include
OBJDIR      := obj

#Basic Config -----------------------------------------------------------------

CXX := g++
LINKER := g++

CXXFILES    := $(wildcard $(SRCDIR)/*.cpp)
HEADERS     := $(wildcard $(INCLUDEDIR)/*.h)
INCLUDE := -I$(INCLUDEDIR)
CXXFLAGS := -g -Wall -O3 -fmessage-length=0 $(INCLUDE)
LDFLAGS := 

#Rules -----------------------------------------------------------------

CXX_OBJS     := $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(CXXFILES)))

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(CXXFILES)))

$(TARGET): $(CXX_OBJS) $(HEADERS)
	$(LINKER) -o $(TARGET) $(CXX_OBJS) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE) $(OBJDIR)/*.o

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.DEFAULT_GOAL := $(TARGET)