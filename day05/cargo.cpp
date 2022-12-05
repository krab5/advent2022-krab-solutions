#include "cargo.h"

using namespace std;

cargo::cargo() {}
cargo::cargo(const vector<stack<char>>& init) {
    for (auto it = init.cbegin(); it != init.cend(); it++) {
        _content.push_back(stack<char>(*it));
    }
}

cargo::~cargo() {}

void cargo::print(ostream& out) const {
    size_t maxheight = 0;
    for (auto it = _content.cbegin(); it != _content.cend(); it++) {
        if (it->size() > maxheight)
            maxheight = it->size();
    }

    size_t width = _content.size();
    char* matrix = new char[maxheight * width];

    for (size_t j = 0; j < width; j++) {
        stack<char> s(_content[j]);
        size_t i = 0;
        while (i < maxheight - s.size()) {
            matrix[j + width * i] = 0;
            i++;
        }

        while (!s.empty()) {
            matrix[j + width * i] = s.top();
            s.pop();
            i++;
        }
    }

    for (size_t i = 0; i < maxheight; i++) {
        for (size_t j = 0; j < width; j++) {
            if (matrix[i * width + j] == 0)
                out << "    ";
            else
                out << "[" << matrix[i * width + j] << "] ";
        }
        out << endl;
    }

    for (size_t j = 0; j < width; j++) {
        out << " " << j << "  ";
    }
    out << endl;
}

void cargo::move(size_t from, size_t to) {
    char c = _content[from].top();
    _content[from].pop();
    _content[to].push(c);
}

void cargo::move(size_t quantity, size_t from, size_t to) {
    for (int i = 0; i < quantity; i++)
        this->move(from, to);
}

void cargo::move_block(size_t quantity, size_t from, size_t to) {
    stack<char> block;
    for (int i = 0; i < quantity; i++) {
        block.push(_content[from].top());
        _content[from].pop();
    }
    while (!block.empty()) {
        _content[to].push(block.top());
        block.pop();
    }
}

vector<char> cargo::topline() const {
    vector<char> result;
    for (auto it = _content.cbegin(); it != _content.cend(); it++)
        result.push_back(it->top());
    return result;
}


