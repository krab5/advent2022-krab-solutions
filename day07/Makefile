CXX=g++
LD=g++
CXXFLAGS=-g -O1 -I../common
LDFLAGS=-g
TARGET=day7.exe
OBJECTS=main.o filetree.o explorer.o termread.o

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET)
	rm -f *.o



