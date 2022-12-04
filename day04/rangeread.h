#ifndef RANGEREAD_H
#define RANGEREAD_H

#include "range.h"
#include "linereader.h"
#include <vector>
#include <utility>

using namespace std;

class rangeread: public common::linereader<pair<range,range>> {
    public:
        rangeread(istream& stream);
        virtual ~rangeread();

        virtual pair<range,range> parse_line(const string& line);
};


#endif // RANGEREAD_H


