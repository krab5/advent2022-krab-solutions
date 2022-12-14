#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include "packet.h"
#include "reader.h"

using namespace std;
using namespace common;

using element_pair = pair<element,element>;

class packetread: public reader<vector<element_pair>> {
    public:
        packetread(istream& stream) : reader<vector<element_pair>>(stream) {}

        virtual void on_start() { 
            _content.clear();
            _first_set = false;
            _content.push_back(pair<element,element>(element::mk_int(0), element::mk_int(0)));
        }
        virtual bool on_line(const string& line) {
            element e = extract(line);
            if (_first_set) {
                _content.back().second = e;
            } else {
                _content.back().first = e;
                _first_set = true;
            }
            return true;
        }
        virtual bool on_sep(const string&) {
            _first_set = false;
            _content.push_back(pair<element,element>(element::mk_int(0), element::mk_int(0)));
            return true;
        }

        virtual vector<element_pair> finish() {
            if (!_first_set)
                _content.pop_back();
            return _content;
        }

    private:
        bool _first_set;
        vector<element_pair> _content;
};

void sort_insert(vector<element>& v, const element& e) {
    bool cue = true;
    auto it = v.begin(), end = v.end();
    while (cue && it != end) {
        if (compare(*it, e) >= 0) {
            cue = false;
            v.insert(it, e);
        }
        it++;
    }
    if (cue)
        v.push_back(e);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }

    ifstream stream(argv[1]);
    packetread pr(stream);
    vector<element_pair> packets = pr.do_parse();
    cout << "Parsed " << packets.size() << " pair of packets" << endl;

    int id = 1, correct = 0;
    vector<element> result;
    for (element_pair p : packets) {
        int c = compare(p.first, p.second);
        cout << p.first << " vs " << p.second << " => " << c << endl;
        if (c < 0) {
            correct += id;
        }
        id++;
        sort_insert(result, p.first);
        sort_insert(result, p.second);
    }
    cout << "Sum of correct indices: " << correct << endl;

    element divider1 = element::mk_list(vector<element>(1, element::mk_list(vector<element>(1, element::mk_int(2)))));
    element divider2 = element::mk_list(vector<element>(1, element::mk_list(vector<element>(1, element::mk_int(6)))));

    sort_insert(result, divider1);
    sort_insert(result, divider2);

    cout << "Sorted packets:" << endl;
    size_t d1pos, d2pos;
    for (size_t i = 0, end = result.size(); i < end; i++) {
        element e = result[i];
        if (e == divider1) {
            d1pos = i + 1;
            cout << "\033[1m";
        }
        if (e == divider2) {
            d2pos = i + 1;
            cout << "\033[1m";
        }
        cout << e << "\033[0m" << endl;
    }

    cout << "Divider 1 pos = " << d1pos << ", divider 2 pos = " << d2pos << endl;
    cout << "Product: " << d1pos * d2pos << endl;

    return 0;
}


