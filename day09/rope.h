#ifndef ROPE_H
#define ROPE_H

#include <ostream>
#include <vector>

#include "unique_vector.h"
#include "point.h"

class rope {
    public:
        rope(size_t length, point init);
        virtual ~rope();

        void move_head(long tx, long ty);

        point head() const;
        point tail() const;

        const unique_vector<point>& history() const;

        void represent(std::ostream& out, point offset, long width, long height, bool withHistory = false) const;

    private:
        bool touching(size_t i, size_t j) const;
        char knot(const point& current) const;

        unique_vector<point> _history;
        std::vector<point> _knots;
};


#endif // ROPE_H


