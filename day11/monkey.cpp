#include "monkey.h"
#include "game.h"
#include <cmath>

using namespace std;

monkey::operation::operation(op_type t, level_t o) : type(t), operand(o) {}

void monkey::operation::apply(level_t& var) const {
    switch (type) {
        case Add:
            var = var + operand;
            break;
        case Mul:
            var = var * operand;
            break;
        case Pow:
            var = var * var;
            break;
        default:
            break;
    }
}

monkey::test::test(test_type t, level_t o) : type(t), operand(o) {}

bool monkey::test::apply(level_t var) const {
    switch (type) {
        case Div:
            return var % operand == 0;
        default:
            return true;
    }
}

monkey::monkey(
        id_t i, const operation& o, const test& t,
        id_t mi, id_t me) :
    id(i), _op(o), _test(t), monkey_if(mi), monkey_else(me), _activity(0) {}

monkey::~monkey() {}

const deque<object>& monkey::items() const {
    return _items;
}

size_t monkey::get_activity() const {
    return _activity;
}

static inline char op_c(monkey::operation::op_type t) {
    switch (t) {
        case monkey::operation::Add:
            return '+';
        case monkey::operation::Mul:
            return '*';
        case monkey::operation::Pow:
            return '^';
        default:
            return '?';
    }
}

static inline const char* test_str(monkey::test::test_type t) {
    switch (t) {
        case monkey::test::Div:
            return "divisible by";
        default:
            return "???";
    }
}

void monkey::show(ostream& out) const {
    out << "Monkey " << id << ":" << endl;
    out << "  Items: ";
    deque<object> q(_items);
    while (!q.empty()) {
        out << q.front().worry_level;
        q.pop_front();
        if (!q.empty())
            out << ", ";
    }
    out << endl;
    out << "  Operation: new = old " << op_c(_op.type) << " " << _op.operand << endl;
    out << "  Test: " << test_str(_test.type) << " " << _test.operand << endl;
    out << "    If true: throw to monkey " << monkey_if << endl;
    out << "    If false: throw to monkey " << monkey_else << endl;
}

static inline level_t mdiv(level_t n, level_t d) {
    return n / d;
}

void monkey::turn(game& g) {
    while (!_items.empty()) {
        inspect(g, _items.front());
        _items.pop_front();
    }
}

void monkey::inspect(game& g, const object& theo) {
    object o = theo;
    _op.apply(o.worry_level);
    if (!g.is_worried)
        o.worry_level = mdiv(o.worry_level, 3);
    o.worry_level = o.worry_level % g.modulo;
    id_t next = (_test.apply(o.worry_level) ? monkey_if : monkey_else);
    g.throw_to(next, o);
    _activity++;
}

void monkey::receive(const object& o) {
    _items.push_back(o);
}


