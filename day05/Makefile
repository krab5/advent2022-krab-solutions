CXX=g++
LD=g++
CXXFLAGS=-g -O1 -I../common
LDFLAGS=-g
TARGET=day5.exe
OBJECTS=main.o inst.o cargo.o instread.o stackread.o

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(TARGET)
	rm *.o



