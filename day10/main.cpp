#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "instread.h"
#include "observer.h"
#include "cpu.h"

using namespace std;

class cycle_observer: public observer {
    public:
        long sum;

        cycle_observer() : sum(0) {}
        virtual ~cycle_observer() {}

        virtual void on_begin_cycle() { do_it(); }
        virtual void on_fetch() {}
        virtual void on_exec() {}

        void do_it() {
            long nc = (long) the_cpu().get_num_cycles();
            if (nc % 40 == 20) {
                long x = the_cpu().get_state().reg_x;
                cout << "Cycle " << nc << ": X=" << x << endl;
                sum += nc * x;
            }
        }
};

class crt_observer: public observer {
    public:
        crt_observer(size_t width, size_t height) : _crt_width(width), _crt_height(height) {}
        virtual ~crt_observer() {}

        string get_str() const { return _crt.str(); }

        virtual void on_begin_cycle() { do_it(); }
        virtual void on_fetch() {}
        virtual void on_exec() {}

        void do_it() {
            long posx = (long) the_cpu().get_num_cycles();
            posx = ((posx - 1) % _crt_width);
            long x = the_cpu().get_state().reg_x;
            long r = posx - x;

            if (posx == 0)
                _crt << endl;

            if (-1 <= r && r <= 1)
                _crt << '#';
            else
                _crt << '.';
        }

    private:
        ostringstream _crt;
        size_t _crt_width, _crt_height;
};

inline static bool is_being_drawn(const state& s, long x) {
    long p = x - s.reg_x;
    return -1 <= p && p <= 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }
    ifstream stream(argv[1]);
    instread ir(stream);
    vector<inst> prgrm = ir.do_parse();

    state s(1);
    cpu c(s, prgrm);

    cycle_observer* cyob = new cycle_observer();
    c.register_observer(cyob);

    crt_observer* crtob = new crt_observer(40, 6);
    c.register_observer(crtob);

    while (!c.finished()) {
        c.step();
    }

    cout << "Finished" << endl;
    cout << "Total: " << cyob->sum << endl;
    cout << "CRT:" << crtob->get_str() << endl;

    delete cyob;
    delete crtob;

    return 0;
}


