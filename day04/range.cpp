#include "range.h"

range::range(int from, int to) : from(from), to(to) {}

bool range::included_in(const range& other) const {
    return this->from >= other.from && this->to <= other.to;
}

int range::size() const {
    return this->to - this->from + 1;
}

bool range::disjoint(const range& other) const {
    return (this->to < other.from) || (other.to < this->from);
}

