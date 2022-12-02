#ifndef RPS_H // Rock, Paper, Scissors
#define RPS_H

#include <exception>
#include "eltreader.h"

using namespace std;

enum rps { A = 0, B, C, X, Y, Z };

static inline const char* __rps2str[] = { "Rock", "Paper", "Scissors", "Rock", "Paper", "Scissors" } ;

static inline const char* rps_to_str(rps x) {
    return __rps2str[x];
}

class rps_exception: public exception {
    public:
        rps_exception() {}
        virtual const char* what() const noexcept {
            return "Unrecognized character";
        }
};

class rpsread: public common::eltreader<rps> {
    public:
        rpsread(istream& stream);
        virtual ~rpsread();

        virtual rps on_element(const string& str) const;
};

#endif // RPS_H


