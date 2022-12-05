#include "instread.h"

#include <iostream>

#define MOVE_SIZE   4
#define FROM_SIZE   4
#define TO_SIZE     2

using namespace std;

instread::instread(istream& stream) : common::linereader<inst>(stream) {}
instread::~instread() {}

inst instread::parse_line(const string& line) {
    // line: move QQQ from FFF to TTT
    inst in(0, 0, 0);
    
    size_t i = MOVE_SIZE + 1;
    size_t start = i;

    while (line[i] != ' ') i++;
    in.quantity = std::stoi(line.substr(start, i - start));
    
    while (line[i] == ' ') i++;
    i += FROM_SIZE + 1;
    start = i;

    while (line[i] != ' ') i++;
    in.from = std::stoi(line.substr(start, i - start));

    while (line[i] == ' ') i++;
    i += TO_SIZE + 1;
    start = i;

    while (i < line.size() && line[i] != ' ') i++;
    in.to = std::stoi(line.substr(start, i - start));

    return in;
}


