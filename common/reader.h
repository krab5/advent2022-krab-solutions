#ifndef READER_H
#define READER_H

#include <iostream>
#include <istream>
#include <fstream>
#include <algorithm>

namespace common {

using namespace std;

typedef bool (*linesep)(const string&);
typedef bool (*charsep)(char);

static inline bool empty_line(const string& s) {
    return s.empty();
}

static inline bool never(const string&) {
    return false;
}

static inline bool comma(char c) {
    return c == ',';
}

static inline bool space(char c) {
    return c == ' ';
}

static inline bool findspace(unsigned char c) {
    return !isspace(c);
}

static inline void chomp(string& s) {
    s.erase(find_if(s.rbegin(), s.rend(), &findspace).base(), s.end());
}

template<typename Out, linesep LineSep = &empty_line>
class reader {
    public:
        reader(istream& stream) : _stream(stream) {}
        virtual ~reader() {}

        int get_num_lines() const { return _nlines; }
        int get_num_blocks() const { return _nblocks; }

        virtual void on_start() {}
        virtual bool on_line(const string& line) = 0;
        virtual void on_sep(const string& sep) {}
        virtual void on_interrupt() {}
        virtual void on_eof() {}

        virtual Out finish() = 0;

        Out do_parse() {
            string line;
            bool cue = true, interrupt = false, isblock = false;

            this->on_start();
            _nlines = 0;
            _nblocks = 0;

            while (cue) {
                isblock = false;
                _nlines++;
                getline(_stream, line);
                chomp(line);

                if (LineSep(line)) {
                    this->on_sep(line);
                    isblock = true;
                    _nblocks++;
                } else {
                    interrupt = !this->on_line(line);
                }

                if (_stream.eof()) {
                    cue = false;
                    _nlines--;
                    this->on_eof();
                }

                if (interrupt) {
                    cue = false;
                    this->on_interrupt();
                }
            }

            return this->finish();
        }

    private:
        istream& _stream;
        int _nlines;
        int _nblocks;
};

}

#endif // READER_H


