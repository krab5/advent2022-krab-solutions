#include "area.h"
#include "unique_vector.h"
#include <stdexcept>

#define ABS(x)      ((x) >= 0 ? (x) : -(x))

straight_line::straight_line(long c0, long c1, long c2, bool v) :
    _coord0(c0), _coord1(c1), _coord2(c2), _is_vert(v) {}

straight_line::straight_line(const straight_line& other) :
    _coord0(other._coord0), _coord1(other._coord1), _coord2(other._coord2), _is_vert(other._is_vert) {}

straight_line& straight_line::operator=(const straight_line& other) {
    this->_coord0 = other._coord0;
    this->_coord1 = other._coord1;
    this->_coord2 = other._coord2;
    this->_is_vert = other._is_vert;
    return *this;
}

bool straight_line::empty() const {
    return _coord2 < _coord1;
}

long straight_line::size() const {
    if (empty())
        return 0;
    else
        return (_coord2 - _coord1) + 1;
}

long straight_line::x1() const { return (_is_vert ? _coord0 : _coord1); }
long straight_line::x2() const { return (_is_vert ? _coord0 : _coord2); }
long straight_line::y1() const { return (_is_vert ? _coord1 : _coord0); }
long straight_line::y2() const { return (_is_vert ? _coord2 : _coord0); }

bool straight_line::is_vert() const { return _is_vert; }

bool straight_line::contains(const point& p) const {
    if (_is_vert) {
        return p.y == _coord0 && _coord1 <= p.x && p.x <= _coord2;
    } else {
        return p.x == _coord0 && _coord1 <= p.y && p.y <= _coord2;
    }
}

void straight_line::merge_to(const straight_line& l2) {
    if (_is_vert != l2._is_vert)
        throw std::invalid_argument("trying to merge straight lines in different directions");
    if (_coord0 != l2._coord0)
        throw std::invalid_argument("trying to merge straight lines that are not aligned");

    if (empty()) {
        *this = l2;
        return;
    }

    if (l2.empty())
        return;

    if (_coord1 > l2._coord1)
        _coord1 = l2._coord1;
    if (_coord2 < l2._coord2)
        _coord2 = l2._coord2;
}

straight_line& straight_line::operator++() {
    this->_coord0++;
    return *this;
}

straight_line straight_line::operator++(int) {
    straight_line old = *this;
    this->_coord0++;
    return old;
}

straight_line straight_line::horizontal(long y, long x1, long x2) {
    if (x1 < x2)
        return straight_line(y, x1, x2, false);
    else
        return straight_line(y, x2, x1, false);
}

straight_line straight_line::vertical(long x, long y1, long y2) {
    if (y1 < y2)
        return straight_line(x, y1, y2, true);
    else
        return straight_line(x, y2, y1, true);
}

straight_line straight_line::line(const point& p1, const point& p2) {
    if (p1.x == p2.x)
        return vertical(p1.x, p1.y, p2.y);
    else if (p1.y == p2.y)
        return horizontal(p1.y, p1.x, p2.x);
    else
        throw std::invalid_argument("straight line between non orthogonally aligned points");
}

bool straight_line::intersecting(const straight_line& l1, const straight_line& l2) {
    if (l1._is_vert == l2._is_vert) {
        return (l1._coord0 == l2._coord0)
            // x1     < l2 >     x2           x1     < l2 >     x2 
            // |-----------------|      incl. |-----------------|  
            //      |----------------|           |---------|       
            //      x1     < l1 >    x2          x1 < l1 > x2       
            && ((l2._coord1 <= l1._coord1 && l1._coord1 <= l2._coord2)
            //    x1     < l2 >     x2        x1     < l2 >     x2
            //    |-----------------|   incl. |-----------------| 
            // |----------------|                |---------|      
            // x1     < l1 >    x2              x1 < l1 > x2      
            || (l2._coord1 <= l1._coord2 && l1._coord2 <= l2._coord2)
            //    x1  < l2 >  x2                    x1     < l2 >      x2
            //    |-----------|      also incl.     |------------------|
            // |------------------|             |------------------| 
            // x1      < l1 >     x2            x1      < l1 >     x2
            || (l1._coord1 <= l2._coord1 && l2._coord1 <= l1._coord2));
    } else {
        return l2._coord1 <= l1._coord0 && l1._coord0 <= l2._coord2
            && l1._coord1 <= l2._coord0 && l2._coord0 <= l1._coord2;
    }
}

straight_line straight_line::merge(const straight_line& l1, const straight_line& l2) {
    straight_line l = l1;
    l.merge_to(l2);
    return l;
}

straight_line straight_line::intersection(const straight_line& l1, const straight_line& l2) {
    if (l1._is_vert == l2._is_vert && l1._coord0 == l2._coord0) {
        return straight_line(l1._coord0,
            (l1._coord1 >= l2._coord1 ? l1._coord1 : l2._coord1), // MAX
            (l1._coord2 <= l2._coord2 ? l1._coord2 : l2._coord2), // MAX
            l1._is_vert);
    } else {
        throw std::invalid_argument("cannot calculate intersection of lines in different directions");
    }
}


straight_line_set::straight_line_set() {}
void straight_line_set::add_line(const straight_line& line) {
    if (!line.empty()) {
        _content.push_back(line);
        normalize();
    }
}

bool straight_line_set::empty() const {
    return _content.empty();
}

bool straight_line_set::unitary() const {
    return _content.size() == 1;
}

void straight_line_set::normalize() {
    std::vector<straight_line>::iterator it = _content.begin();
    bool redo;

    while (it != _content.end()) {
        std::vector<straight_line>::iterator jt = it;
        redo = false;

        jt++;
        while (jt != _content.end()) {
            if (straight_line::intersecting(*it, *jt) && it->is_vert() == jt->is_vert()) {
                it->merge_to(*jt);
                _content.erase(jt);
                redo = true;
            } else {
                jt++;
            }
        }

        if (!redo)
            it++;
    }
}

std::vector<straight_line>::const_iterator straight_line_set::cbegin() const { return _content.cbegin(); }
std::vector<straight_line>::const_iterator straight_line_set::cend() const { return _content.cend(); }

void straight_line_set::render(svg::printer& svgp, long y) const {
    svg::printer::line* l = new svg::printer::line(
        point(svgp.bottom_left().x, y), point(svgp.top_right().x, y),
        svg::printer::style::stroke("#ee7700", "3px", "", 0.3)
    );
    svgp.add_element(l);

    svg::printer::style sty = svg::printer::style::stroke("#ee7700", "4px", "");

    const long tackwidth = 1;

    for (straight_line c : _content) {
        if (!c.is_vert() && c.y1() == y) {
            svg::printer::line* lc = new svg::printer::line(
                point(c.x1(), y), point(c.x2(), y),
                sty
            );
            svgp.add_element(lc);
            svg::printer::line* left = new svg::printer::line(
                point(c.x1(), y + tackwidth), point(c.x1(), y - tackwidth),
                sty
            );
            svgp.add_element(left);
            svg::printer::line* right = new svg::printer::line(
                point(c.x2(), y + tackwidth), point(c.x2(), y - tackwidth),
                sty
            );
            svgp.add_element(right);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const straight_line& l) {
    out << "[(" << l.x1() << "," << l.y1() << ")-(" << l.x2() << "," << l.y2() << ")]";
    return out;
}


sensor::sensor(const point& pos, const point& beacon)
    : my_pos(pos), beacon_pos(beacon), dist(common::manhattan(pos, beacon)) {}

bool sensor::in_area(const point& other) const {
    return manhattan(other, my_pos) <= dist;
}

std::vector<point> sensor::area() const {
    std::vector<point> result;
    for (long x = -dist; x <= dist; x++) {
        for (long y = 0; ABS(x) + y <= dist; y++) {
            result.push_back(my_pos + point(x, y));
            if (y != 0)
                result.push_back(my_pos + point(x, -y));
        }
    }
    return result;
}

/*
Principle:
.....#.....
....##B....
...#####...
..###S###..
...#####...
....###....  < y = c
.....#.....
The two points of the line are the intersection between the line (D: y = c) and the circle
of the Manhattan distance of center S and radius r = |S - B|

The distance between S and (D) is d = |S.y - y|. If d > r we know that the intersection is
empty.
Otherwise, take the vertical point at d below/above S (same result), then count left or right
a number of points s.t. d + that number = r. This entails that you find a point on (D) that is
r away from S, i.e. is on the circle.

This yields, more directly, the points: S + (±(r - d), d).
(x coord = S.x ± (r - d) )
*/
straight_line sensor::intersect_horizontal(long y) const {
    long d = ABS(my_pos.y - y); // algebraic distance between S and (D)
    long off = dist - d; // X offset (if d > dist, off < 0)
    return straight_line(y, my_pos.x - off, my_pos.x + off, false); // if d > dist, S.x - off > S.x + off and line is empty
}

straight_line sensor::intersect_vertical(long x) const {
    long d = ABS(my_pos.x - x); // algebraic distance between S and (D)
    long off = dist - d; // X offset (if d > dist, off < 0)
    return straight_line(x, my_pos.y - off, my_pos.y + off, true); // if d > dist, S.x - off > S.x + off and line is empty
}

area::area() {}

void area::add_sensor(const sensor& s) {
    _content.push_back(s);
}

void area::add_sensor(const point& pos, const point& beacon) {
    add_sensor(sensor(pos, beacon));
}

straight_line_set area::intersect(long y) const {
    straight_line_set result;
    for (sensor s : _content) {
        straight_line l = s.intersect_horizontal(y);
        result.add_line(l);
    }

    return result;
}

straight_line_set area::intersect(const straight_line& l) const {
    straight_line_set result;
    for (sensor s : _content) {
        straight_line r = (l.is_vert() ? s.intersect_vertical(l.x1()) : s.intersect_horizontal(l.y1()));
        result.add_line(straight_line::intersection(l, r));
    }

    return result;
}

std::vector<point> area::beacons_on(long y) const {
    unique_vector<point> result;
    for (sensor s : _content) {
        if (s.beacon_pos.y == y)
            result.insert(s.beacon_pos);
    }
    return result;
}

svg::printer area::to_svg() const {
    svg::printer svgp;

    // Areas
    for (sensor s : _content) {
        svg::printer::style pstyle;
        pstyle.stroke_color = "#660066";
        pstyle.stroke_width = "2px";
        pstyle.opacity = 0.6;
        pstyle.fill_color = "#8080ee";
        svg::printer::polygon* p = new svg::printer::polygon(pstyle);
        p->add_point((s.my_pos + point(s.dist, 0)));
        p->add_point((s.my_pos - point(0, s.dist)));
        p->add_point((s.my_pos - point(s.dist, 0)));
        p->add_point((s.my_pos + point(0, s.dist)));
        svgp.add_element(p);
    }

    long radius = (svgp.top_right().x - svgp.bottom_left().x) / 100;

    // Landmarks
    for (sensor s : _content) {
        svg::printer::line* l = new svg::printer::line(s.my_pos, s.beacon_pos, svg::printer::style::stroke("#00aa00", "2px", "5 7"));
        svgp.add_element(l);

        svg::printer::rect* r = new svg::printer::rect(s.beacon_pos - point(radius, radius), point(2*radius, 2*radius), svg::printer::style::fill("#00aa00"));
        svgp.add_element(r);

        svg::printer::circle* c = new svg::printer::circle(s.my_pos, radius, svg::printer::style::fill("#880066"));
        svgp.add_element(c);
    }


    float scale = 1.0;
    float width = (float) (svgp.top_right().x - svgp.bottom_left().x);

    while (width > 1000.0) {
        scale /= 10.0;
        width /= 10.0;
    }

    while (width < 100.0) {
        scale *= 10.0;
        width *= 10.0;
    }

    svgp.set_scale(scale);

    return svgp;
}



