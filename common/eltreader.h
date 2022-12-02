#ifndef ELTREADER_H
#define ELTREADER_H

#include "reader.h"
#include <vector>


namespace common {

using namespace std;

template<typename EltType, charsep EltSep = &space>
class eltreader: public reader<vector<vector<EltType>>, &never> {
    public:
        eltreader(istream& stream) : reader<vector<vector<EltType>>, &never>::reader(stream) {}
        virtual ~eltreader() {}

        virtual EltType on_element(const string& elt) const = 0;

        virtual void on_start() {
            _content.clear();
        }

        virtual bool on_line(const string& line) {
            size_t i = 0, j;
            vector<EltType> elts;
            string elt;
            for (char c : line) {
                if (EltSep(c)) {
                    if (!elt.empty()) {
                        elts.push_back(this->on_element(elt));
                        elt.clear();
                    }
                } else {
                    elt.push_back(c);
                }
            }

            if (!elt.empty())
                elts.push_back(this->on_element(elt));
        
            if (!elts.empty())
                _content.push_back(elts);
            return true;
        }

        virtual vector<vector<EltType>> finish() {
            return _content;
        }

    private:
        vector<vector<EltType>> _content;
};

}

#endif // ELTREADER_H


