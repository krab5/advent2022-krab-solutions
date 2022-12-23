CXX=g++
LD=g++
CXXFLAGS=-g -O2 -I../common -std=c++17
LDFLAGS=-g
LIBS=
TARGET=day15.exe
OBJECTS=main.o svgprinter.o area.o

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET)
	rm -f *.o



