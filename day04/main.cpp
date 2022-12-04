#include <iostream>
#include "range.h"
#include "rangeread.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }
    string arg(argv[1]);
    ifstream stream(arg.c_str());
    rangeread rr(stream);
    vector<pair<range,range>> result = rr.do_parse();
    cout << "Parsed " << rr.get_num_lines() << " lines (" << result.size() << ")" << endl;

    int errors = 0, errors2 = 0;
    for (auto it = result.cbegin(); it != result.cend(); it++) {
        if (it->first.included_in(it->second) || it->second.included_in(it->first)) 
            errors++;
        if (!it->first.disjoint(it->second))
            errors2++;
    }

    cout << "Number of full inclusion: " << errors << endl;
    cout << "Number of overlap: " << errors2 << endl;

    return 0;
}


