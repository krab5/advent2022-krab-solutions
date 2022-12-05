#include "stackread.h"

#define MAX 9

using namespace std;

static inline char get(const string& str, size_t i) {
    size_t id = i * 4 + 1;
    if (id >= str.size())
        return ' ';
    else
        return str[id];
}

stackread::stackread(istream& stream) : common::reader<vector<stack<char>>>(stream) {}
stackread::~stackread() {}

void stackread::on_start() {
    _content.clear();
    for (size_t i = 0; i < MAX; i++)
        _content.push_back(vector<char>());
}

bool stackread::on_sep(const string& line) {
    return false;
}

bool stackread::on_line(const string& line) {
    if (!line.empty() && line[1] != '1') { // not the last line
        for (size_t i = 0; i < MAX; i++) {
            _content[i].push_back(get(line, i));
        }
    }
    return true;
}

vector<stack<char>> stackread::finish() {
    vector<stack<char>> result;
    for (auto it = _content.begin(); it != _content.end(); it++) {
        stack<char> s;
        for (auto jt = it->rbegin(); jt != it->rend(); jt++) {
            if (*jt != ' ')
                s.push(*jt);
        }
        result.push_back(s);
    }
    return result;
}


