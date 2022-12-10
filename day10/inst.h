#ifndef INST_H
#define INST_H

#include <ostream>

struct state {
    long reg_x;

    state(long x) : reg_x(x) {}
    state() : reg_x(0) {}
    state(const state& other) : reg_x(other.reg_x) {}
};

enum opcode {
    NOOP, ADDX
};

struct inst {
    const opcode op;
    const long arg1;
    const long arg2;

    inst(opcode o) : op(o), arg1(0), arg2(0) {}
    inst(opcode o, long a1) : op(o), arg1(a1), arg2(0) {}
    inst(opcode o, long a1, long a2) : op(o), arg1(a1), arg2(a2) {}

    size_t num_cycles() const {
        switch (op) {
            case NOOP:
                return 1;
            case ADDX:
                return 2;
            default:
                return 0;
        }
    }

    void apply(state& state) const {
        switch (op) {
            case ADDX:
                state.reg_x += arg1;
                break;
            default:
                break;
        }
    }
};

static std::ostream& operator<<(std::ostream& out, const inst& i) {
    std::string o;
    size_t narg = 0;
    switch (i.op) {
        case ADDX:
            o = "addx";
            narg = 1;
            break;
        case NOOP:
            o = "noop";
            break;
        default:
            o = "???";
            break;
    }

    out << o;
    if (narg > 0)
        out << " " << i.arg1;
    if (narg > 1)
        out << " " << i.arg2;
    return out;
}

#endif // INST_H


