#ifndef AREA_H
#define AREA_H

#include "point.h"
#include "svgprinter.h"
#include <vector>

using common::point;

class straight_line {
    public:
        straight_line(long c0, long c1, long c2, bool v);
        straight_line(const straight_line& other);

        straight_line& operator=(const straight_line& other);

        bool empty() const;
        long size() const;

        long x1() const;
        long x2() const;
        long y1() const;
        long y2() const;

        bool is_vert() const;

        bool contains(const point& p) const;

        void merge_to(const straight_line& l1);

        straight_line& operator++();
        straight_line operator++(int);

        static straight_line horizontal(long y, long x1, long x2);
        static straight_line vertical(long x, long y1, long y2);
        static straight_line line(const point& p1, const point& p2);

        static bool intersecting(const straight_line& l1, const straight_line& l2);
        static straight_line merge(const straight_line& l1, const straight_line& l2);
        static straight_line intersection(const straight_line& l1, const straight_line& l2);

    private:
        long _coord0, _coord1, _coord2;
        bool _is_vert;
};

std::ostream& operator<<(std::ostream& out, const straight_line& l);

class straight_line_set {
    public:
        straight_line_set();

        void add_line(const straight_line& line);

        bool empty() const;
        bool unitary() const;

        std::vector<straight_line>::const_iterator cbegin() const;
        std::vector<straight_line>::const_iterator cend() const;

        void render(svg::printer& svgp, long y) const;

    private:
        void normalize();

        std::vector<straight_line> _content;

};

struct sensor {
    const point my_pos;
    const point beacon_pos;
    const long dist;

    sensor(const point& pos, const point& beacon);

    bool in_area(const point& other) const;
    std::vector<point> area() const;

    straight_line intersect_horizontal(long y) const;
    straight_line intersect_vertical(long x) const;
};

class area {
    public:
        using content_type = std::vector<sensor>;
        area();

        void add_sensor(const sensor& sens);
        void add_sensor(const point& pos, const point& beacon);
        
        straight_line_set intersect(long y) const;
        straight_line_set intersect(const straight_line& l) const;
        std::vector<point> beacons_on(long y) const;

        svg::printer to_svg() const;

    private:
        content_type _content;
};


#endif // AREA_H


