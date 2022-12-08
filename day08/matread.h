#ifndef MATREAD_H
#define MATREAD_H

#include "matrix.h"
#include "reader.h"

class matread: public common::reader<matrix<char,0>, &common::never> {
    public:
        matread(std::istream& stream);
        virtual ~matread();

        virtual void on_start();
        virtual bool on_line(const std::string& line);

        virtual matrix<char,0> finish();

    private:
        matrix<char,0> _content;
};


#endif // MATREAD_H


