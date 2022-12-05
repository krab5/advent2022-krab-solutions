#ifndef INST_H
#define INST_H

#include "cargo.h"
#include <string>
#include <ostream>

struct inst {
    size_t quantity;
    size_t from;
    size_t to;

    inst(size_t quantity, size_t from, size_t to);

    void apply(cargo& cargo);
};

static inline std::ostream& operator<<(std::ostream& out, const inst& i) {
    out << "move " << i.quantity << " from " << i.from << " to " << i.to;
    return out;
}

#endif // INST_H



