#include "game.h"

using namespace std;

game::game(bool worried) : is_worried(worried), modulo(1) {}

void game::add_monkey(monkey* m) {
    id_t i = m->id;
    modulo *= m->_test.operand;
    for (size_t k = _monkeys.size(); k <= i; k++) {
        _monkeys.push_back(nullptr);
    }
    _monkeys[i] = m;
}

void game::round() {
    for (monkey* m : _monkeys) {
        m->turn(*this);
    }
}

void game::show(ostream& out) const {
    for (monkey* m : _monkeys) {
        out << "Monkey " << m->id << ": ";
        deque<object> q(m->items());
        while (!q.empty()) {
            out << q.front().worry_level;
            q.pop_front();
            if (!q.empty())
                out << ", ";
        }
        out << endl;
    }
}

void game::throw_to(id_t dest, object o) {
    _monkeys[dest]->receive(o);
}


