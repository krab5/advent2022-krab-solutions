#include <iostream>
#include <fstream>
#include <vector>
#include "instread.h"
#include "inst.h"
#include "rope.h"

#define STARTX  0
#define STARTY  0
#define SIZE    30
#define OFFSET  -10

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }

    ifstream stream(argv[1]);
    instread ir(stream);
    vector<inst> result = ir.do_parse();

    cout << "Parsed " << result.size() << " instructions" << endl;

    point start(STARTX, STARTY);
    const point offset(OFFSET, OFFSET);
    rope r(10, start);
    cout << "Rope (starting pos " << start << "):" << endl;
    r.represent(cout, offset, SIZE, SIZE);
    cout << endl;

    for (auto it = result.begin(), end = result.end(); it != end; it++) {
        apply(r, *it);
        r.represent(cout, offset, SIZE, SIZE);
        cout << endl;
    }

    r.represent(cout, offset, SIZE, SIZE, true);
    cout << "Number of positions for tail: " << r.history().size() << endl;

    return 0;
}


