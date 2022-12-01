#ifndef CALREAD_H
#define CALREAD_H

#include "reader.h"
#include <vector>

using namespace std;

class calread: public reader<vector<vector<int>>> {
    public:
        calread(istream& stream);
        //calread(const string& filename);
        virtual ~calread();

        virtual bool on_line(const string& line);
        virtual void on_sep(const string& sep);
        virtual vector<vector<int>> finish();

    private:
        vector<int> _current;
        vector<vector<int>> _others;
};

#endif // CALREAD_H


