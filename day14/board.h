#ifndef BOARD_H
#define BOARD_H

#include <ostream>
#include "point.h"
#include "matrix.h"

enum class spot : char {
    Empty = 0, Wall = 1, Sand = 2
};

using board_content = common::matrix<spot,spot::Empty>;

class board {
    public:
        board(size_t width, size_t height, const common::point& offset);

        void move_to(const common::point& p);
        void line_to(const common::point& p);

        bool offlimit(const common::point& p) const;

        common::point sand(const common::point& source);

        void print(std::ostream& out, const common::point& source);

    private:
        common::point next(const common::point& p);
        const common::point _offset;
        common::point _current_point;
        board_content _content;
};


#endif // BOARD_H


