#include "rps.h"

using namespace common;

rpsread::rpsread(istream& stream) : eltreader(stream) {}
rpsread::~rpsread() {}

rps rpsread::on_element(const string& str) const {
    if (str == "A")
        return A;
    else if (str == "B")
        return B;
    else if (str == "C")
        return C;
    else if (str == "X")
        return X;
    else if (str == "Y")
        return Y;
    else if (str == "Z")
        return Z;
    else
        throw rps_exception();
}

