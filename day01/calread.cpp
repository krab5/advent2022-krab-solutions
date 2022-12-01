#include "calread.h"

calread::calread(istream& stream) : reader(stream) {}
//calread::calread(const string& filename) : reader(filename) {}
calread::~calread() {}

bool calread::on_line(const string& line) {
    int r = stoi(line);
    _current.push_back(r);
    return true;
}

void calread::on_sep(const string&) {
    if (!_current.empty()) {
        vector<int> cp(_current);
        _others.push_back(cp);
        _current.clear();
    }
}

vector<vector<int>> calread::finish() {
    if (!_current.empty())
        _others.push_back(_current);
    return _others;
}


