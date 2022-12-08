#include <iostream>
#include <sstream>
#include "matread.h"
#include "matrix.h"

using namespace std;

void print(ostream& out, const matrix<char,0>& mat) {
    for (auto it = mat.cbegin(); it != mat.cend(); it++) {
        cout << (int)(*it);
        if (it.eol()) cout << endl;
    }
}

bool visible_from_north(const matrix<char,0>& mat, size_t i, size_t j, int& score) {
    score = 0;
    if (i == 0)
        return true;

    size_t ii = i - 1;
    char tree = mat.at(i,j);
    bool visible = true;

    while (visible && ii > 0) {
        visible = visible && tree > mat.at(ii,j);
        ii--;
        score++;
    }

    if (visible && tree > mat.at(ii,j)) {
        score++;
        return true;
    } else {
        return false;
    }
}

bool visible_from_south(const matrix<char,0>& mat, size_t i, size_t j, int& score) {
    score = 0;
    size_t ii = i + 1;
    char tree = mat.at(i,j);
    bool visible = true;

    while (visible && ii < mat.rows()) {
        visible = visible && tree > mat.at(ii,j);
        ii++;
        score++;
    }

    return visible;
}

bool visible_from_east(const matrix<char,0>& mat, size_t i, size_t j, int& score) {
    score = 0;

    if (j == 0)
        return true;

    size_t jj = j - 1;
    char tree = mat.at(i,j);
    bool visible = true;

    while (visible && jj > 0) {
        visible = visible && tree > mat.at(i,jj);
        jj--;
        score++;
    }

    if (visible && tree > mat.at(i,jj)) {
        score++;
        return true;
    } else {
        return false;
    }
}

bool visible_from_west(const matrix<char,0>& mat, size_t i, size_t j, int& score) {
    score = 0;
    size_t jj = j + 1;
    char tree = mat.at(i,j);
    bool visible = true;

    while (visible && jj < mat.columns()) {
        visible = visible && tree > mat.at(i,jj);
        jj++;
        score++;
    }

    return visible;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }
    ifstream stream(argv[1]);
    matread mr(stream);
    matrix<char,0> result = mr.do_parse();

    cout << "Parsed matrix (" << result.rows() << "×" << result.columns() << "): " << endl;
    print(cout, result);

    int numvis = 0, max = 0;
    size_t maxi = 0, maxj = 0;

    for (size_t i = 0; i < result.rows(); i++) {
        for (size_t j = 0; j < result.columns(); j++) {
            bool visible = false;
            int scoren, scores, scorew, scoree;
            ostringstream out;
            cout << "(" << i << "," << j << ") [" << ((int) result(i,j)) << "]";
            out << " visible from ";
            if (visible_from_north(result, i, j, scoren)) {
                out << "north";
                visible = true;
            }
            if (visible_from_south(result, i, j, scores)) {
                out << (visible ? ", " : "") << "south";
                visible = true;
            }
            if (visible_from_east(result, i, j, scoree)) {
                out << (visible ? ", " : "") << "east";
                visible = true;
            }
            if (visible_from_west(result, i, j, scorew)) {
                out << (visible ? ", " : "") << "west";
                visible = true;
            }

            if (visible) {
                numvis++;
                cout << out.str();
            }

            int score = scoren * scores * scorew * scoree;
            cout << " has score " << score << "(N,S,W,E = " << scoren << "," << scores << "," << scorew << "," << scoree << ")" << endl;

            if (score > max) {
                max = score;
                maxi = i;
                maxj = j;
            }
        }
    }

    cout << "Total: " << numvis << " visible trees." << endl;
    cout << "Best scenic score: " << max << " (reached for (" << maxi << "," << maxj << "))" << endl;

    return 0;
}



