#include <iostream>
#include <fstream>

#define MAX(x, y)           (x > y ? x : y)
#define START_PACKET_SIZE   4
#define MSG_PACKET_SIZE     14

using namespace std;

// Case:
// xxxOOxxxx
//     ^     => cursor inc such that first O out of window

size_t packet_start(const string& str, size_t packet_size) {
    size_t i = 0, j = 0, next = packet_size; // next == next character from which string may be checked
    char current;
    bool cue = true;

    while (cue && i < str.size()) {
        current = str[i];
        j = 1;
        while (j < i & j < packet_size && str[i - j] != current) {
            j++;
        }

        if (j >= packet_size) {
            if (i >= next)
                cue = false;
        } else {
            if (j < i)
                next = MAX(next, i + packet_size - j);
        }
        i++;
    }

    if (i >= str.size())
        return 0;
    return i;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[1] << " <filename>" << endl;
        return -1;
    }
    ifstream stream(argv[1]);
    string line;

    while (getline(stream,line)) {
        if (!line.empty()) {
            cout << line << endl;
            size_t ps = packet_start(line, START_PACKET_SIZE);
            size_t ms = packet_start(line, MSG_PACKET_SIZE);
            cout << "Packet start: " << ps << " [..." << line.substr(ps, START_PACKET_SIZE) << "...]" << endl;
            cout << "Message start: " << ms << " [..." << line.substr(ms, MSG_PACKET_SIZE) << "...]" << endl;
            cout << endl;
        }
    }

    return 0;
}


