#ifndef LINEREADER_H
#define LINEREADER_H

#include "reader.h"
#include <vector>

using namespace std;

namespace common {

template<typename Elt>
class linereader: public reader<vector<Elt>, &never> {
    public:
        linereader(istream& stream) : reader<vector<Elt>, &never>::reader(stream) {}
        virtual ~linereader() {}

        virtual Elt parse_line(const string& line) = 0;

        virtual void on_start() { _content.clear(); }
        virtual bool on_line(const string& line) {
            if (!line.empty())
                _content.push_back(this->parse_line(line));
            return true;
        }

        virtual vector<Elt> finish() {
            return _content;
        }
    private:
        vector<Elt> _content;
};
 
}

#endif //LINEREADER_H


