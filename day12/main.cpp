#include <iostream>
#include <fstream>
#include <chrono>
#include "matrixreader.h"
#include "distance.h"

using namespace std;
using namespace common;

class matread: public common::matrixreader<char,0> {
    public:
        matread(istream& stream) : common::matrixreader<char,0>(stream) {}
        virtual ~matread() {}

        virtual char parse_char(char c) { return c; }
};

size_t doit(const content_matrix& mat, const point& start, const point& end, bool show) {
    auto tstart = chrono::high_resolution_clock::now();
    distance_matrix dist = calc_dist(mat, start);
    auto dur = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - tstart);
    if (show) {
        path_matrix path = guess_path(mat, dist, start, end);
        show_path(cout, mat, path, start, end);
        cout << "Time: " << dur.count() << "µs" << endl;
    }
    return dist.at(end);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }

    ifstream stream(argv[1]);
    matread mr(stream);
    content_matrix mat(mr.do_parse());

    point start, end;

    for (size_t i = 0; i < mat.size(); i++) {
        if (mat[i] == 'S') {
            mat[i] = 'a';
            start = point((long) mat.getj(i), (long) mat.geti(i));
        } else if (mat[i] == 'E') {
            mat[i] = 'z';
            end = point((long) mat.getj(i), (long) mat.geti(i));
        }
    }

    cout << "Heightmap:" << endl;
    cout << mat << endl;
    cout << "Start: " << start << endl;
    cout << "End: " << end << endl;

    size_t r = doit(mat, start, end, true);
    cout << "Min dist: " << r << endl;

    size_t min = INFINITE_DISTANCE;
    for (size_t i = 0; i < mat.size(); i++) {
        if (mat[i] == 'a') {
            point p((long) mat.getj(i), (long) mat.geti(i));
            size_t r = doit(mat, p, end, false);
            if (r < min)
                min = r;
        }
    }

    cout << "Min path length: " << min << endl;

    return 0;
}



