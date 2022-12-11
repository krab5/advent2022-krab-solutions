#include <iostream>
#include <fstream>
#include "parser.h"
#include "game.h"
#include "monkey.h"

#define SHOW_CYCLE  1000

using namespace std;

class monkey_reader: public common::reader<vector<monkey>> {
    public:
        monkey_reader(istream& stream) : common::reader<vector<monkey>>(stream) {}

        virtual void on_start() { _wrapped.on_start(); }
        virtual bool on_line(const string& line) { return _wrapped.on_line(line); }
        virtual bool on_sep(const string& sep) { return _wrapped.on_sep(sep); }
        virtual vector<monkey> finish() { return _wrapped.finish(); }

    private:
        parser _wrapped;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <filename> <num rounds> [-worried]" << endl;
        return -1;
    }

    ifstream stream(argv[1]);
    size_t maxrounds = (size_t) stol(argv[2]);
    bool worried = false;

    for (size_t i = 3; i < argc; i++) {
        if (string(argv[i]) == "-worried") {
            cout << "Worried mode enabled" << endl;
            worried = true;
        }
    }

    /*parser*/monkey_reader p(stream);
    vector<monkey> monkeys = p.do_parse();

    cout << "Got " << monkeys.size() << " monkeys:" << endl;
    game g(worried);

    for (size_t i = 0, end = monkeys.size(); i < end; i++) {
        monkeys[i].show(cout);
        g.add_monkey(&monkeys[i]);
        cout << endl;
    }

    cout << "Initial state: " << endl;
    g.show(cout);
    cout << endl;

    size_t round = 1;
    for (; round <= maxrounds; round++) {
        g.round();

        if (round == 1 || round % SHOW_CYCLE == 0) {
            cout << "After round " << round << ", the state is:" << endl;
            g.show(cout);
            cout << endl;
        }
    }

    cout << "Activity of each monkeys after " << (round - 1) << " rounds: " << endl;
    size_t maxf = 0, maxs = 0, act;
    for (monkey m : monkeys) {
        act = m.get_activity();
        cout << "Monkey " << m.id << " inspected items " << act << " times." << endl;
        if (maxf < act) {
            maxs = maxf;
            maxf = act;
        } else if (maxs < act) {
            maxs = act;
        }
    }

    cout << "2 highest activities: " << maxf << " and " << maxs << endl;
    cout << "=> monkey business: " << maxf * maxs << endl;

    return 0;
}


