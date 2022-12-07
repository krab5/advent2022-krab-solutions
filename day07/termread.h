#ifndef TERMREAD_H
#define TERMREAD_H

#include <exception>
#include "linereader.h"

using namespace std;

enum term_line_type {
    CommandLs, CommandCd, ResultDir, ResultFile
};

struct term_line {
    term_line_type type;
    string content;
    size_t extra;

    static term_line make_command_ls();
    static term_line make_command_cd(const string& ct);
    static term_line make_result_file(const string& ct, size_t size);
    static term_line make_result_dir(const string& ct);
};

class termread: public common::linereader<term_line> {
    public:
        class termread_exception: public exception {
            public:
                termread_exception() {}
                const char* what() const noexcept { return "cannot parse line"; }
        };
        termread(istream& stream);
        virtual ~termread();

        virtual term_line parse_line(const string& line);

};


#endif // TERMREAD_H


