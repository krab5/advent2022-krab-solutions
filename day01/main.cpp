#include <iostream>
#include <fstream>
#include "calread.h"

using namespace std;

int sum_max(const vector<vector<int>>& input) {
    int max = -1, sum;
    for (auto it = input.cbegin(); it != input.cend(); it++) {
        sum = 0;
        for (auto jt = it->cbegin(); jt != it->cend(); jt++) {
            sum += *jt;
        }
        if (sum > max) max = sum;
    }
    return max;
}

void sum_max3(const vector<vector<int>>& input, int& top1, int& top2, int& top3) {
    int max1 = -1, max2 = -1, max3 = -1, sum;
    for (auto it = input.cbegin(); it != input.cend(); it++) {
        sum = 0;
        for (auto jt = it->cbegin(); jt != it->cend(); jt++) {
            sum += *jt;
        }

        if (sum > max1) {
            max3 = max2;
            max2 = max1;
            max1 = sum;
        } else if (sum > max2) {
            max3 = max2;
            max2 = sum;
        } else if (sum > max3) {
            max3 = sum;
        }
    }
    top1 = max1;
    top2 = max2;
    top3 = max3;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }
    string arg(argv[1]);
    ifstream stream(arg.c_str());
    calread cr(stream);
    vector<vector<int>> result = cr.do_parse();
    cout << "Processed " << cr.get_num_lines() << " lines resulting in " << cr.get_num_blocks() << " blocks." << endl;
    cout << "Maximum of sums: " << sum_max(result) << endl;

    int t1,t2,t3;
    sum_max3(result, t1, t2, t3);
    cout << "Top 3 sums is " << t1 << ", " << t2 << " and " << t3 << " (sum = " << (t1 + t2 + t3) << ")" << endl;

    return 0;
}




