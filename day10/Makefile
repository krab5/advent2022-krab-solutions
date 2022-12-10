CXX=g++
LD=g++
CXXFLAGS=-g -O0 -I../common
LDFLAGS=-g
TARGET=day10.exe
OBJECTS=main.o cpu.o instread.o

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET)
	rm -f *.o



