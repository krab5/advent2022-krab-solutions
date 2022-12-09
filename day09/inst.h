#ifndef INST_H
#define INST_H

#include <string>
#include "rope.h"

enum direction {
    Left, Right, Up, Down
};

direction parse_direction(char c);

struct inst {
    direction dir;
    int quantity;
};

inst parse_inst(const std::string& input);

void apply(rope& rope, const inst& i);

#endif // INST_H


