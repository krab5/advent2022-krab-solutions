#ifndef INSTREAD_H
#define INSTREAD_H

#include "inst.h"
#include "linereader.h"

using namespace std;

class instread: public common::linereader<inst> {
    public:
        instread(istream& stream);
        virtual ~instread();

        inst parse_line(const string& line);
};

#endif // INSTREAD_H


