#ifndef RANGE_H
#define RANGE_H

#include <ostream>

struct range {
    int from;
    int to;

    range(int from, int to);

    bool included_in(const range& other) const;
    bool disjoint(const range& other) const;
    int size() const;

};

static inline std::ostream& operator<<(std::ostream& out, const range& r) {
    out << "[" << r.from << ".." << r.to << "]";
    return out;
}

#endif //RANGE_H


