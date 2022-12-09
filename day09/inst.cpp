#include "inst.h"

using namespace std;

direction parse_direction(char c) {
    switch (c) {
        case 'R':
            return Right;
        case 'L':
            return Left;
        case 'U':
            return Up;
        case 'D':
            return Down;
        default:
            return Right;
    }
}

inst parse_inst(const string& input) {
    inst i;
    i.dir = parse_direction(input[0]);
    i.quantity = stoi(input.substr(2));
    return i;
}

static inline long dirx(direction d) {
    switch (d) {
        case Right:
            return +1;
        case Left:
            return -1;
        default:
            return 0;
    }
}

static inline long diry(direction d) {
    switch (d) {
        case Up:
            return +1;
        case Down:
            return -1;
        default:
            return 0;
    }
}

void apply(rope& r, const inst& i) {
    long tx = dirx(i.dir), ty = diry(i.dir);
    for (int k = 0; k < i.quantity; k++)
        r.move_head(tx, ty);
}


