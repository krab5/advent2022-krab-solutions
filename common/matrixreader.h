#ifndef MATRIXREADER_H
#define MATRIXREADER_h

#include "reader.h"
#include "matrix.h"

namespace common {

template<typename T, T Pad>
class matrixreader: public reader<const matrix<T,Pad>&, &never> {
    public:
        matrixreader(std::istream& stream) : reader<const matrix<T,Pad>&, &never>(stream) {}
        virtual ~matrixreader() {}

        virtual T parse_char(char c) = 0;

        virtual void on_start() { _content.clear(); }
        virtual bool on_line(const string& line) {
            if (!line.empty()) {
                if (!_content.column_set())
                    _content.set_columns(line.size());
                for (auto it = line.cbegin(); it != line.cend(); it++)
                    _content.push_back(this->parse_char(*it));
            }
            return true;
        }

        virtual bool on_sep(const string& sep) { return true; }
        virtual void on_interrupt() {}
        virtual void on_eof() {}

        virtual const matrix<T,Pad>& finish() {
            return _content;
        }

    private:
        matrix<T,Pad> _content;
};

};


#endif // MATRIXREADER_H


