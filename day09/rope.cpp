#include "rope.h"

using namespace std;

rope::rope(size_t length, point init) {
    for (size_t i = 0; i < length; i++)
        _knots.push_back(point(init));
    _history.insert(init);
}

rope::~rope() {
}

void rope::move_head(long tx, long ty) {
    _knots[0].translate(tx, ty);
    for (size_t i = 1; i < _knots.size(); i++) {
        if (!touching(i - 1, i)) {
            point diff = _knots[i - 1] - _knots[i];
            // First case: 1 square Manhattan distance (= same row/same col)
            if ((diff.x == 0 && diff.y * diff.y == 1) ||
                (diff.y == 0 && diff.x * diff.x == 1)) {
                _knots[i] += diff;
            } 
            // Second case: L shape
            else { // if (abs(diff.x) == 2 && abs(diff.y) == 1 || abs(diff.x) == 1 && abs(diff.y) == 2)
                _knots[i] += unit(diff);
            }

        }
    }
    _history.insert(_knots.back());
}

point rope::head() const { return _knots.front(); }
point rope::tail() const { return _knots.back(); }

const unique_vector<point>& rope::history() const { return _history; }

void rope::represent(ostream& out, point offset, long width, long height, bool withHistory) const {
    for (long i = height - 1; i >= 0; i--) { // line
        for (long j = 0; j < width; j++) {   // column
            point current(j + offset.x, i + offset.y);
            char c = knot(current);
            if (c == 0) {
                if (withHistory && _history.contains(current))
                    out << '#';
                else 
                    out << '.';
            } else {
                out << c;
            }
        }
        out << endl;
    }
}

bool rope::touching(size_t i, size_t j) const {
    point diff = abs(_knots[i] - _knots[j]);
    return diff.x <= 1 && diff.y <= 1;
}

char rope::knot(const point& current) const {
    size_t i = 0;
    while (i < _knots.size() && _knots[i] != current) {
        i++;
    }

    if (i == 0)
        return 'H';
    else if (i == _knots.size() - 1)
        return 'T';
    else if (i >= _knots.size())
        return 0;
    else
        return ((char) i) + '0';
}


