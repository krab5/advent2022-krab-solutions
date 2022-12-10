#include "instread.h"

using namespace std;

instread::instread(istream& stream) : common::linereader<inst>(stream) {}
instread::~instread() {}

static inline opcode parse_opcode(const std::string str) {
    if (str == "addx")
        return ADDX;
    else
        return NOOP;
}

inst instread::parse_line(const string& line) {
    opcode op;
    long arg1 = 0;

    size_t start = 0, end = 0;
    while (line[end] != ' ') end++;
    op = parse_opcode(line.substr(start, end));
    start = end;
    while (start < line.size() && line[start] == ' ') start++;

    if (start < line.size()) {
        end = start;
        while (end < line.size() && line[end] != ' ') end++;
        arg1 = stol(line.substr(start, end));
    }

    return inst(op, arg1);
}


