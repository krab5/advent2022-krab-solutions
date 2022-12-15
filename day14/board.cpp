#include <sstream>
#include <iomanip>
#include <iostream>
#include "board.h"

using namespace common;

board::board(size_t width, size_t height, const point& offset) :
    _content(height + 1, width + 1), _offset(offset) {}

void board::move_to(const point& p) {
    _current_point = p - _offset;
    _content.at(_current_point) = spot::Wall;
}

void board::line_to(const point& p) {
    point dest = p - _offset;
    point direction = unit(dest - _current_point);

    while (_current_point != dest) {
        _current_point += direction;
        _content.at(_current_point) = spot::Wall;
    }
}

bool board::offlimit(const common::point& p) const {
    return !_content.in_bounds(p - _offset);
}

point board::sand(const point& source) {
    point s = source - _offset, n;
    bool cue = true, offlimit = false;

    while (cue) {
        n = next(s);

        if (n == s) {
            _content.at(n) = spot::Sand;
            cue = false;
        } else if (!_content.in_bounds(n)) {
            cue = false;
            offlimit = true;
        } else {
            s = n;
        }
    }

    return n + _offset;
}

point board::next(const point& p) {
    point candidates[] = { p + point(0,1), p + point(-1,1), p + point(1,1) };
    size_t i = 0;
    while (i < 3 && _content.at(candidates[i]) != spot::Empty) i++;
    if (i < 3)
        return candidates[i];
    else
        return p;
}

struct board_pretty_printer: public common::matrix<spot,spot::Empty>::pretty_printer {
    const point source;

    board_pretty_printer(const point& s) : source(s) {}

    virtual void on_element(std::ostream& out, size_t k, size_t i, size_t j, const spot& e) {
        if (source == point((long) j, (long) i))
            out << "\033[7m";
        switch (e) {
            case spot::Wall:
                out << '#';
                break;
            case spot::Sand:
                out << 'O';
                break;
            default:
                out << '.';
        }
        if (source == point((long) j, (long) i))
            out << "\033[0m";
    }
    virtual void on_linebegin(std::ostream& out, size_t i) {
        out << std::setw(3) << i << ' ';
    }
    virtual void on_lineend(std::ostream& out, size_t i) {
        out << std::endl;
    }
};

void board::print(std::ostream& out, const point& source) {
    const size_t cycle = 10;
    size_t decade = 1000;
    while (decade > 0) {
        out << "    ";
        for (size_t i = 0; i < _content.columns(); i++) {
            if (i == 0 || i == _content.columns() - 1 || (i + _offset.x) % 10 == 0) {
                out << ((((long) i) + _offset.x) / decade) % 10;
            } else {
                out << ' ';
            }
        }
        if (decade > 1)
            out << std::endl;
        decade /= 10;
    }
    out << std::endl;
    _content.show_withp(out, new board_pretty_printer(source - _offset));
}





