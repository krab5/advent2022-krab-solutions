#include <iostream>
#include <vector>
#include "board.h"
#include "linereader.h"

using common::point;
using namespace std;

inline constexpr bool is_digit(const char& c) {
    return '0' <= c && c <= '9';
}

class boardread: public common::linereader<vector<point>> {
    public:
        boardread(istream& stream): common::linereader<vector<point>>(stream) {}
        virtual ~boardread() {}

        point parse_point(const string::const_iterator& begin, const string::const_iterator& end) {
            point result;
            auto it = begin;
            while (*it != ',') it++;
            result.x = stoi(string(begin, it));
            it++;
            result.y = stoi(string(it, end));
            return result;
        }

        virtual vector<point> parse_line(const string& line) {
            vector<point> instructions;
            auto it = line.cbegin(), end = line.cend(), start = it;
            while (it != end) {
                start = it;
                while (it != end && *it != ' ') it++;
                instructions.push_back(parse_point(start, it));
                while (it != end && !is_digit(*it)) it++;
            }
            return instructions;
        }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[1] << " <filename>" << endl;
        return -1;
    }

    ifstream stream(argv[1]);
    boardread br(stream);
    vector<vector<point>> insts = br.do_parse();

    // Compute min/max X and max Y
    long minx, maxx, miny = 0, maxy;
    bool set = false;
    vector<point> allpoints;
    for (vector<point> inst : insts) {
        for (point p : inst) {
            if (!set) {
                minx = p.x;
                maxx = p.x;
                maxy = p.y;
                set = true;
            } else {
                if (minx > p.x) minx = p.x;
                if (maxx < p.x) maxx = p.x;
                if (maxy < p.y) maxy = p.y;
            }
            allpoints.push_back(p);
        }
    }

    cout << "Computed window: [" << minx << "," << maxx << "]×[" << miny << "," << maxy << "]" << endl;
    point min(minx, miny), max(maxx, maxy);
    point offset = min;

    board b((size_t) (maxx - minx), (size_t) (maxy - miny), offset);
    for (vector<point> inst : insts) {
        auto it = inst.cbegin(), end = inst.cend();
        b.move_to(*it);
        it++;
        while (it != end) {
            b.line_to(*it);
            it++;
        }
    }

    point source(500,0);

    cout << "Board:" << endl;
    b.print(cout, source);

    const size_t cycle = 100;
    size_t qty = 0;
    bool stop = false;
    point n;

    while (!stop) {
        qty++;
        n = b.sand(source);
        stop = b.offlimit(n);
        if (qty % cycle == 0) {
            cout << "Step " << qty << endl;
            b.print(cout, source);
        }
    }

    b.print(cout, source);
    cout << "Quantity of sand: " << (qty - 1) << endl;
    cout << endl;


    long bottom = maxy + 2;
    for (point p : allpoints) {
        long height = bottom - p.y;
        long land_left_x = p.x - height;
        long land_right_x = p.x + height;
        if (minx > land_left_x) minx = land_left_x;
        if (maxx < land_right_x) maxx = land_right_x;
    }

    minx -= 10;
    maxx += 10;

    cout << "Computed window: [" << minx << "," << maxx << "]×[" << 0 << "," << bottom << "]" << endl;

    board b2((size_t)(maxx - minx), bottom, point(minx, 0));
    for (vector<point> inst : insts) {
        auto it = inst.cbegin(), end = inst.cend();
        b2.move_to(*it);
        it++;
        while (it != end) {
            b2.line_to(*it);
            it++;
        }
    }
    b2.move_to(point(minx, bottom));
    b2.line_to(point(maxx, bottom));
    cout << "Board with floor:" << endl;
    b2.print(cout, source);

    qty = 0;
    stop = false;

    while (!stop) {
        qty++;
        n = b2.sand(source);
        stop = (n == source);
        if (qty % cycle == 0) {
            cout << "Step " << qty << ", last sand point " << n << endl;
            //b2.print(cout, source);
        }
    }
    
    b2.print(cout, source);
    cout << "Quantity of sand: " << qty << endl;

    return 0;
}




