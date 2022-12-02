#ifndef CALREAD_H
#define CALREAD_H

#include "reader.h"
#include <vector>

class calread: public common::reader<std::vector<std::vector<int>>> {
    public:
        calread(std::istream& stream);
        //calread(const string& filename);
        virtual ~calread();

        virtual void on_start();
        virtual bool on_line(const std::string& line);
        virtual void on_sep(const std::string& sep);
        virtual std::vector<std::vector<int>> finish();

    private:
        std::vector<int> _current;
        std::vector<std::vector<int>> _others;
};

#endif // CALREAD_H


