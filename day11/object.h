#ifndef OBJECT_H
#define OBJECT_H

#include <string>

typedef long level_t;

static level_t parse_level(const std::string& in) {
    return std::stol(in);
};

struct object {
    level_t worry_level;

    object(level_t w) : worry_level(w) {}
};


#endif // OBJECT_H


