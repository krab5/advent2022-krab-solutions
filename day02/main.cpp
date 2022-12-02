#include <iostream>
#include <fstream>
#include "rps.h"

static const int values[] = { 1, 2, 3, 1, 2, 3 };

enum outcome { Lose = 0, Tie, Win };
static const int scores[] = { 0, 3, 6 };

// A X = Rock
// B Y = Paper
// C Z = Scissor
static const outcome duels[] = {
    //  A     B     C
/* X */ Tie,  Lose, Win,
/* Y */ Win,  Tie,  Lose,
/* Z */ Lose, Win,  Tie
};

static const outcome to_outcome[] = { Lose, Tie, Win };

#define DUEL(opp, me)   duels[(me % 3) * 3 + opp]

int calculate_score1(rps opponent, rps me) {
    int value_score = values[me];
    int duel_score = scores[DUEL(opponent, me)];
    return value_score + duel_score;
}

rps guess_shape(rps opponent, outcome out) {
    for (int i = 3; i < 6; i++) {
        if (DUEL(opponent, (rps) i) == out)
            return (rps) i;
    }
    return X;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }
    string arg(argv[1]);
    ifstream stream(arg.c_str());
    rpsread rr(stream);
    vector<vector<rps>> result = rr.do_parse();
    cout << "Processed " << rr.get_num_lines() << " lines." << endl;

    cout << rps_to_str(A) << " - " << rps_to_str(X) << " => " << DUEL(A, X) << endl;
    cout << rps_to_str(A) << " - " << rps_to_str(Y) << " => " << DUEL(A, Y) << endl;
    cout << rps_to_str(A) << " - " << rps_to_str(Z) << " => " << DUEL(A, Z) << endl;
    cout << rps_to_str(B) << " - " << rps_to_str(X) << " => " << DUEL(B, X) << endl;
    cout << rps_to_str(B) << " - " << rps_to_str(Y) << " => " << DUEL(B, Y) << endl;
    cout << rps_to_str(B) << " - " << rps_to_str(Z) << " => " << DUEL(B, Z) << endl;
    cout << rps_to_str(C) << " - " << rps_to_str(X) << " => " << DUEL(C, X) << endl;
    cout << rps_to_str(C) << " - " << rps_to_str(Y) << " => " << DUEL(C, Y) << endl;
    cout << rps_to_str(C) << " - " << rps_to_str(Z) << " => " << DUEL(C, Z) << endl;

    size_t i = 1;
    int sum = 0, sum2;
    for (auto it = result.begin(); it != result.end(); it++) {
        int score = calculate_score1(it->at(0), it->at(1));
        rps me = guess_shape(it->at(0), to_outcome[it->at(1) % 3]);
        int score2 = calculate_score1(it->at(0), me);
        //if (DUEL(it->at(0), me) != it->at(1) % 3)
        //cout << "Line " << i << ": " << score << endl;
        sum += score;
        sum2 += score2;
        i++;
    }

    cout << "Total score: " << sum << endl;
    cout << "Total score2: " << sum2 << endl;

    return 0;
}


