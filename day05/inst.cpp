#include "inst.h"

inst::inst(size_t q, size_t f, size_t t) : quantity(q), from(f), to(t) {}

void inst::apply(cargo& cargo) {
    cargo.move(this->quantity, this->from - 1, this->to - 1);
}


