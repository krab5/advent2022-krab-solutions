#ifndef GAME_H
#define GAME_H

#include "monkey.h"

#include <ostream>
#include <vector>
#include <deque>
#include <map>

class game {
    public:
        friend monkey;

        game(bool worried = false);

        void add_monkey(monkey* m);

        void round();

        void show(std::ostream& o) const;

    private:
        void throw_to(id_t dest, object o);

        long modulo;
        const bool is_worried;
        std::vector<monkey*> _monkeys;
};


#endif // GAME_H


