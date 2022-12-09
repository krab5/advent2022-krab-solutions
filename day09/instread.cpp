#include "instread.h"

using namespace std;

instread::instread(istream& stream) : common::linereader<inst>(stream) {}
instread::~instread() {}

inst instread::parse_line(const string& line) {
    return parse_inst(line);
}


