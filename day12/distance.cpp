#include "distance.h"
#include "todo.h"
#include <iostream>
#include <iomanip>

using namespace common;
using std::vector;

bool connex(const content_matrix& content, const point& from, const point& to, char delta) {
    char v = content.at(from);
    char w = content.at(to);
    return (v >= w || w - v <= delta);
}

/* Main function of the puzzle: calculate, for each point in the grid, the minimum distance
 * from that point to the "source" point.
 * This is done by browsing through each point and finding the direct neighbor with the
 * minimum number. The distance at that point is 1 plus that minimum.
 *
 * Complexity is O(n) where n is the size of the grid (rows × columns)
 */
distance_matrix calc_dist(const content_matrix& content, const point& source) {
    distance_matrix dist(content.rows(), content.columns());
    dist.at(source) = 0;

    todo<point> tovisit; // A todo-list(/queue) for each point to visit
    tovisit.push(source);
    point p;

    while (!tovisit.empty()) {
        p = tovisit.peek();
        tovisit.pop();

        vector<point> neighbors { p + point(0,1), p + point(0,-1), p + point(1,0), p + point(-1,0) };
        for (point n : neighbors) {
            if (content.in_bounds(n)) {
                size_t valn = dist.at(n);
                size_t val = dist.at(p);
                // We look for points from which we could come (from = neighbor, to = this point)
                // and then take the minimum of distances from these points
                if (connex(content, n, p) && valn != INFINITE_DISTANCE && valn + 1 < val) {
                    dist.at(p) = valn + 1;
                }
                // We look for points that haven't been visited and that are accessible (from = this
                // point, to = neighbor)
                if (connex(content, p, n) && valn == INFINITE_DISTANCE) {
                    tovisit.push(n);
                }
            }
        }

        // If that point has not been update then it means there are no accessible neighbor...
        // We set the value to INFINITE - 1 to avoid being visited again.
        if (dist.at(p) == INFINITE_DISTANCE)
            dist.at(p) -= 1;
    }
    return dist;
}

path_matrix guess_path(const content_matrix& content, const distance_matrix& dist, const point& source, const point& dest) {
    path_matrix c(dist.rows(), dist.columns());
    point p = dest, last;
    while (p != source) {
        c.set(p, true);
        vector<point> neighs { p + point(0,1), p + point(0,-1), p + point(1,0), p + point(-1,0) };
        bool set = false;
        last = p;
        for (point n : neighs) {
            if (!set && connex(content, n, p) && dist.at(n) == dist.at(p) - 1) {
                p = n;
                set = true;
            }
        }

        if (p == last) {
            throw no_path_exception();
        }
    }

    return c;
}

void show_dist(std::ostream& out, const content_matrix& content, const distance_matrix& dist) {
    dist.show_with(out, [content](std::ostream& o, size_t k, const size_t& x) {
        if (x == INFINITE_DISTANCE)
            o << "x";
        else if (x == INFINITE_DISTANCE - 1)
            o << ".";
        else
            o << x;
        if ((k + 1) % content.columns() != 0)
            o << ",";
    });
}

void show_path(std::ostream& out, const content_matrix& content, const path_matrix& path, const point& start, const point& end) {
    size_t kstart = start.y * content.columns() + start.x;
    size_t kend = end.y * content.columns() + end.x;
    content.show_with(out, [path,kstart,kend](std::ostream& o, size_t k, const char& x) {
        if (k == kstart)
            o << "\033[90m\033[41m";
        else if (k == kend)
            o << "\033[30m\033[44m";
        else if (path.cat(k))
            o << "\033[7m";
        o << x << "\033[0m";
    });
}



