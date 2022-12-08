#include "matread.h"

using namespace std;

matread::matread(istream& stream) : common::reader<matrix<char,0>, &common::never>(stream) {}
matread::~matread() {}

void matread::on_start() {
    _content.clear();
}

bool matread::on_line(const string& line) {
    if (!line.empty()) {
        if (!_content.column_set())
            _content.set_columns(line.size());
        for (auto it = line.cbegin(); it != line.cend(); it++)
            _content.push_back((*it) - '0');
    }
    return true;
}

matrix<char,0> matread::finish() {
    return _content;
}


