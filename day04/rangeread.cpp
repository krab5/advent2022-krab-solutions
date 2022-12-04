#include "rangeread.h"

#define PAIR_SEP    ','
#define RNG_SEP     '-'

using namespace std;
using namespace common;

rangeread::rangeread(istream& stream) : linereader(stream) {}
rangeread::~rangeread() {}


// 00: X
// 01: 1 <- begin }
// 02: 2          } substr(begin, mid - begin)
// 03: 3          }   = 1, 2, 3 (OK)
// 04: - <- mid } }
// 05: 4        }
// 06: 5        } substr(mid + 1, end - mid + 1)
// 07: 6        }   = 4, 5, 6, 7
// 08: 7        }
// 09: . <- end }

static inline range parse_range(const string& line, size_t begin, size_t end) {
    size_t mid = begin;
    while (mid < end && line[mid] != RNG_SEP)
        mid++;
    return range(
        stoi(line.substr(begin, mid - begin)),
        stoi(line.substr(mid + 1, end - mid + 1))
    );
}

pair<range,range> rangeread::parse_line(const string& line) {
    size_t mid = 0;

    while (line[mid] != PAIR_SEP)
        mid++;

    return pair<range,range>(
        parse_range(line, 0, mid),
        parse_range(line, mid + 1, line.size())
    );
}


