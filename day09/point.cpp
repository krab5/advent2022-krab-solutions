#include "point.h"

point::point(long tx, long ty) : x(tx), y(ty) {}
point::point(const point& other) : x(other.x), y(other.y) {}
point::point() : x(0), y(0) {}

point& point::operator=(const point& other) {
    x = other.x;
    y = other.y;
    return *this;
}

point& point::translate(long tx, long ty) {
    x += tx;
    y += ty;
    return *this;
}

point& point::operator+=(const point& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

point& point::operator-=(const point& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

bool operator==(const point& lhs, const point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const point& lhs, const point& rhs) {
    return !(lhs == rhs);
}

point operator+(point lhs, const point& rhs) {
    return point(lhs.x + rhs.x, lhs.y + rhs. y);
}

point operator-(point lhs, const point& rhs) {
    return point(lhs.x - rhs.x, lhs.y - rhs. y);
}

std::ostream& operator<<(std::ostream& out, const point& p) {
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

point abs(const point& op) {
    point result(op);
    if (result.x < 0) result.x = - result.x;
    if (result.y < 0) result.y = - result.y;
    return result;
}

point unit(const point& op) {
    point result;
    if (op.x < 0) result.x = -1;
    else if (op.x > 0) result.x = 1;

    if (op.y < 0) result.y = -1;
    else if (op.y > 0) result.y = 1;

    return result;
}




