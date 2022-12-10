#ifndef INSTREAD_H
#define INSTREAD_H

#include "inst.h"
#include "linereader.h"

class instread: public common::linereader<inst> {
    public:
        instread(std::istream& stream);
        virtual ~instread();

        virtual inst parse_line(const std::string& line);
};


#endif // INSTREAD_H


