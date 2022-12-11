#ifndef PARSER_H
#define PARSER_H

#include "monkey.h"
#include "reader.h"

#include <vector>

class parser {
    public:
        parser(/*std::istream& stream*/);
        virtual ~parser();

        /*virtual*/ void on_start();
        /*virtual*/ bool on_line(const std::string& line);
        /*virtual*/ bool on_sep(const std::string& sep);

        /*virtual*/ std::vector<monkey> finish();

    private:
        struct monkey_builder;
        monkey_builder* _builder;
        std::vector<monkey> _monkeys;
};


#endif // PARSER_H



