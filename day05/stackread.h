#ifndef STACKREAD_H
#define STACKREAD_H

#include "reader.h"
#include <vector>
#include <stack>

using namespace std;

class stackread: public common::reader<vector<stack<char>>> {
    public:
        stackread(istream& stream);
        virtual ~stackread();

        virtual void on_start();
        virtual bool on_sep(const string& line);
        virtual bool on_line(const string& line);
        virtual vector<stack<char>> finish();

    private:
        vector<vector<char>> _content;
};


#endif // STACKREAD_H

