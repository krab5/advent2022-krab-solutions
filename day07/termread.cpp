#include "termread.h"

using namespace std;

term_line term_line::make_command_ls() {
    term_line t;
    t.type = CommandLs;
    t.extra = 0;
    return t;
}

term_line term_line::make_command_cd(const string& ct) {
    term_line t;
    t.type = CommandCd;
    t.content = ct;
    t.extra = 0;
    return t;
}

term_line term_line::make_result_file(const string& ct, size_t size) {
    term_line t;
    t.type = ResultFile;
    t.content = ct;
    t.extra = size;
    return t;
}

term_line term_line::make_result_dir(const string& ct) {
    term_line t;
    t.type = ResultDir;
    t.content = ct;
    t.extra = 0;
    return t;
}

termread::termread(istream& stream) : linereader<term_line>(stream) {}
termread::~termread() {}

term_line termread::parse_line(const string& line) {
    if (line[0] == '$') {
        size_t start = 1, len = 0;
        while (line[start] == ' ') start++;
        while (start + len < line.size() && line[start + len] != ' ') len++;
        string cmd = line.substr(start, len);

        if (cmd == "cd") {
            start = start + len;
            while (line[start] == ' ') start++;
            return term_line::make_command_cd(line.substr(start));
        } else if (cmd == "ls") {
            return term_line::make_command_ls();
        } else {
            throw termread_exception();
        }
    } else if (line[0] == 'd') {
        size_t start = 3;
        while (line[start] == ' ') start++;
        return term_line::make_result_dir(line.substr(start));
    } else { // <numbers> <name>
        size_t lennum = 0;
        while (line[lennum] != ' ') lennum++;
        size_t ctstart = lennum;
        while (line[ctstart] == ' ') ctstart++;
        return term_line::make_result_file(line.substr(ctstart), stoi(line.substr(0, lennum)));
    }
}


