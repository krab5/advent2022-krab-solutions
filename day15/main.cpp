#include <iostream>
#include <fstream>
#include "area.h"
#include "svgprinter.h"
#include "linereader.h"

using namespace std;

class configread: public common::linereader<sensor> {
    public:
        configread(istream& stream) : common::linereader<sensor>(stream) {}

        virtual sensor parse_line(const string& line) {
            point sens, beac;
            string::const_iterator start = line.cbegin(), end;
            
            while (*start != '=') start++;
            start++;
            end = start;
            while (*end != ',') end++;
            sens.x = stoi(string(start, end));

            start = end;
            while (*start != '=') start++;
            start++;
            end = start;
            while (*end != ':') end++;
            sens.y = stoi(string(start, end));

            start = end;
            while (*start != '=') start++;
            start++;
            end = start;
            while (*end != ',') end++;
            beac.x = stoi(string(start, end));

            start = end;
            while (*start != '=') start++;
            start++;
            end = start;
            while (end != line.cend()) end++;
            beac.y = stoi(string(start, end));

            return sensor(sens, beac);
        }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>              (parse only)" << endl;
        cout << "       " << argv[0] << " <filename> <y>          (1-line intersection)" << endl;
        cout << "       " << argv[0] << " <filename> <min> <max>  (search hole in area)" << endl;
        return -1;
    }

    ifstream stream(argv[1]);
    configread cr(stream);
    vector<sensor> sensors = cr.do_parse();

    area the_area;
    for (sensor s : sensors) {
        cout << "Sensor at " << s.my_pos << " linked to beacon " << s.beacon_pos << " (distance=" << s.dist << ")" << endl;
        the_area.add_sensor(s);
    }

    svg::printer print = the_area.to_svg();

    if (argc > 2 && argc <= 3) {
        long y = stol(string(argv[2]));
        cout << "Calculating intersection for y = " << y << endl;
        straight_line_set ls = the_area.intersect(y);
        ls.render(print, y);

        long sum = 0;
        for (auto it = ls.cbegin(), end = ls.cend(); it != end; it++) {
            sum += it->size();
            cout << "Line: " << *it << endl;
        }

        long beacons = the_area.beacons_on(y).size();
        cout << "Number of beacons on the line: " << beacons << endl;
        cout << "Total coverage: " << (sum - beacons) << endl;
    } else if (argc > 3) {
        long min = stol(string(argv[2])), max = stol(string(argv[3]));
        cout << "Search area: [" << min << "," << max << "]²" << endl;
        svg::printer::rect* search_area = new svg::printer::rect(point(min,min), point(max,max),
                svg::printer::style::stroke("#bb0033", "3px", "2"));
        print.add_element(search_area);

        straight_line scan = straight_line::horizontal(min, min, max);
        while (scan.y1() <= max) {
            straight_line_set r = the_area.intersect(scan);
            if (!r.unitary()) {
                cout << "Found discrepancy at line " << scan.y1() << "; intersection gives following segments: " << endl;
                vector<long> points;
                for (auto it = r.cbegin(); it != r.cend(); it++) {
                    cout << " - " << *it << endl;
                    points.push_back(it->x1());
                    points.push_back(it->x2());
                }

                long x = 0;
                for (long p1 : points) {
                    for (long p2 : points) {
                        if (p1 - p2 == 2 || p2 - p1 == 2) {
                            x = (p1 < p2 ? p1 : p2) + 1;
                        }
                    }
                }

                cout << "I guessed that the hole is located at " << point(x, scan.y1()) << endl;
                cout << "Tuning frequency: " << x * max + scan.y1() << endl;

            }
            scan++;
        }

    }

    ofstream out(string(argv[1]) + ".svg");
    print.render(out, 10, 10);

    return 0;
}


