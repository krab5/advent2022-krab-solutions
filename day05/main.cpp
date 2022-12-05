#include <iostream>
#include <fstream>
#include "inst.h"
#include "cargo.h"
#include "stackread.h"
#include "instread.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[1] << endl;
        return -1;
    }
    ifstream stream(argv[1]);
    stackread sr(stream);
    cargo c(sr.do_parse());
    instread ir(stream);
    vector<inst> insts = ir.do_parse();

    cout << "Parsed cargo:" << endl;
    c.print(cout);
    cout << endl;
    cout << "Parsed " << insts.size() << " instructions" << endl;

    for (auto it = insts.begin(); it != insts.end(); it++) {
        //c.move(it->quantity, it->from - 1, it->to - 1);
        c.move_block(it->quantity, it->from - 1, it->to - 1);
    }

    cout << "Cargo after transformation:" << endl;
    c.print(cout);
    cout << endl << "Top line: " << endl;
    vector<char> topline = c.topline();
    for (auto it = topline.begin(); it != topline.end(); it++)
        cout << *it;

    cout << endl;

    return 0;
}


