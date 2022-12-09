#ifndef POINT_H
#define POINT_H

#include <ostream>

struct point {
    long x;
    long y;

    point(long tx, long ty);
    point(const point& other);
    point();

    point& operator=(const point& other);

    point& translate(long tx, long ty);

    point& operator+=(const point& rhs);
    point& operator-=(const point& rhs);
};

bool operator==(const point& lhs, const point& rhs);
bool operator!=(const point& lhs, const point& rhs);
point operator+(point lhs, const point& rhs);
point operator-(point lhs, const point& rhs);

std::ostream& operator<<(std::ostream& out, const point& p);

point abs(const point& op);
point unit(const point& op);

#endif // POINT_H


