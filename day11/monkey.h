#ifndef MONKEY_H
#define MONKEY_H

#include <ostream>
#include <deque>
#include "object.h"

typedef unsigned int id_t;

class game;

class monkey {
    public:
        friend game;

        struct operation {
            enum op_type {
                Add, Mul, Pow, Nop
            };
            op_type type;
            level_t operand;

            operation(op_type t, level_t o);
            void apply(level_t& var) const;
        };

        struct test {
            enum test_type {
                Div
            };
            test_type type;
            level_t operand;

            test(test_type t, level_t o);
            bool apply(level_t var) const;
        };

        const id_t id;
        const id_t monkey_if, monkey_else;

        monkey(id_t i, const operation& o, const test& t, id_t mi, id_t me);
        virtual ~monkey();

        const std::deque<object>& items() const;
        void receive(const object& o);

        size_t get_activity() const;

        void show(std::ostream& out) const;

    private:
        void turn(game& g);
        void inspect(game& g, const object& o);


        size_t _activity;

        const operation _op;
        const test _test;
        std::deque<object> _items;

};



#endif // MONKEY_H


