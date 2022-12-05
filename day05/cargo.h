#ifndef CARGO_H
#define CARGO_H

#include <ostream>
#include <vector>
#include <stack>

using namespace std;

class cargo {
    public:
        cargo();
        cargo(const vector<stack<char>>& init);
        ~cargo();

        void print(ostream& out) const;

        void move(size_t from, size_t to);
        void move(size_t quantity, size_t from, size_t to);
        void move_block(size_t quantity, size_t from, size_t to);

        vector<char> topline() const;

    private:
        vector<stack<char>> _content;

};

#endif // CARGO_H


