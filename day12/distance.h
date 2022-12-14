#ifndef DISTANCE_H
#define DISTANCE_H

#include <exception>
#include "matrix.h"
#include "point.h"

// Special constant for a point that is unreachable/has never been visited
#define INFINITE_DISTANCE   0xFFFFFFFF

using content_matrix = common::matrix<char,0>;
using distance_matrix = common::matrix<size_t,INFINITE_DISTANCE>;
using path_matrix = common::matrix<bool,false>;


class no_path_exception: public std::exception {
    public:
        no_path_exception() {}

        const char* what() const noexcept { return "No path found"; }
};

bool connex(const content_matrix& ct, const common::point& from, const common::point& to, char delta = 1);
distance_matrix calc_dist(const content_matrix& content, const common::point& source);

// Decreasing order
path_matrix guess_path(const content_matrix& content, const distance_matrix& dist, const common::point& source, const common::point& dest);

void show_dist(std::ostream& out, const content_matrix& content, const distance_matrix& dist);
void show_path(std::ostream& out, const content_matrix& content, const path_matrix& path, const common::point& start, const common::point& end);


#endif // DISTANCE_H



