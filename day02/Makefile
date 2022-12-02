CXX=g++
LD=g++
CXXFLAGS=-g -O1 -I../common
LDFLAGS=-g
TARGET=day2
OBJECTS=main.o rps.o 

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(TARGET)
	rm *.o



