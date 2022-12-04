CXX=g++
LD=g++
CXXFLAGS=-g -O1 -I../common
LDFLAGS=-g
TARGET=day4.exe
OBJECTS=main.o range.o rangeread.o

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(TARGET)
	rm *.o



