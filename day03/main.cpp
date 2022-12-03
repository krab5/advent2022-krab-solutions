#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

inline void swap(string& str, size_t i, size_t j) {
    char t = str[i];
    str[i] = str[j];
    str[j] = t;
}

size_t split(string& str, size_t begin, size_t end) {
    char p = str[end - 1];
    size_t r = begin;
    for (size_t i = begin; i < end - 1; i++) {
        if (str[i] <= p) {
            swap(str, i, r);
            r++;
        }
    }
    swap(str, r, end - 1);
    return r;
}

void sort(string& str, size_t begin, size_t end) {
    if (end - begin <= 1 || end <= begin)
        return;
    size_t r = split(str, begin, end);
    sort(str, begin, r);
    sort(str, r + 1, end);
}

char compare(const string& in) {
    string str(in);
    size_t mid = str.size() / 2;
    size_t i = 0, j = mid;
    char r = 0;

    sort(str, 0, mid);
    sort(str, mid, str.size());

    while (r == 0 && i < mid && j < str.size()) {
        if (str[i] == str[j])
            r = str[i];
        else if (str[i] < str[j])
            i++;
        else
            j++;
    }
    return r;
}

int calc_score(char c) {
    if (c <= 90) {
        return ((int) c) - 65 + 27;
    } else {
        return ((int) c) - 97 + 1;
    }
}

int processline(const string& str) {
    char c = compare(str);
    int score = calc_score(c);
    cout << str << " => " << c << " (" << score << ")" << endl;
    return score;
}

int processgroup(const vector<string>& group) {
    string a = group[0];
    string b = group[1];
    string c = group[2];
    sort(a, 0, a.size());
    sort(b, 0, b.size());
    sort(c, 0, c.size());
    size_t ia = 0, ib = 0, ic = 0;
    char r = 0;

    while (r == 0) {
        if (a[ia] < b[ib]) {
            ia++;
        } else if (a[ia] > b[ib]) {
            ib++;
        } else { // a == b
            if (c[ic] < a[ia]) {
                ic++;
            } else if (c[ic] > a[ia]) {
                ia++; ib++;
            } else {
                r = c[ic];
            }
        }
    }

    int score = calc_score(r);
    cout << "Group item: " << c << " (" << score << ")" << endl;
    return score;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }
    string arg(argv[1]);
    ifstream stream(arg.c_str());
    string line;
    int total = 0, total2 = 0;
    vector<string> group;
    while (getline(stream, line)) {
        if (!line.empty()) {
            total += processline(line);
            group.push_back(line);
            if (group.size() == 3) {
                total2 += processgroup(group);
                group.clear();
            }

        }
    }
    cout << "Total score: " << total << endl;
    cout << "Total score for groups: " << total2 << endl;

    return 0;
}

