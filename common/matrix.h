#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "point.h"

namespace common {

template<typename T, T Pad>
class matrix {
    public:
        using Container = std::vector<T>;

        class iterator {
            public: 
                friend class matrix;

                using iterator_category = std::forward_iterator_tag;
                using difference_type = long;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                reference operator*() { return _content[_cursor]; }
                pointer operator->() { return &(_content[_cursor]); }

                iterator& operator++() { _cursor++; return *this; }
                iterator& operator++(int) { iterator& t = *this; ++(*this); return t; }

                bool eol() const { return (_cursor + 1) % _content->columns() == 0; }

                friend bool operator==(const iterator& a, const iterator& b) { return a._cursor == b._cursor; }
                friend bool operator!=(const iterator& a, const iterator& b) { return !(a == b); }

            private:
                iterator(matrix* m, size_t pos) { _content = m; _cursor = pos; }

                size_t _cursor;
                matrix* _content;
        };

        class const_iterator {
            public: 
                friend class matrix;

                using iterator_category = std::forward_iterator_tag;
                using difference_type = long;
                using value_type = T;
                using pointer = const T*;
                using reference = const T&;

                reference operator*() const { return _content->at(_cursor); }
                pointer operator->() const { return &(_content[_cursor]); }

                const_iterator& operator++() { _cursor++; return *this; }
                const_iterator& operator++(int) { const_iterator& t = *this; ++(*this); return t; }

                bool eol() const { return (_cursor + 1) % _content->columns() == 0; }

                friend bool operator==(const const_iterator& a, const const_iterator& b) { return a._cursor == b._cursor; }
                friend bool operator!=(const const_iterator& a, const const_iterator& b) { return !(a == b); }

            private:
                const_iterator(const matrix* m, size_t pos) { _content = m; _cursor = pos; }

                size_t _cursor;
                const matrix* _content;
        };

        class line_iterator {
            public:
                friend class matrix;

                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type = long;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                reference operator*() { return _content->at(_line, (size_t) _cursor); }
                pointer operator->() { return &(_content->at(_line, (size_t) _cursor)); }

                line_iterator& operator++() { _cursor++; return *this; }
                line_iterator& operator++(int) { line_iterator& t = *this; ++(*this); return t; }

                line_iterator& operator--() { _cursor--; return *this; }
                line_iterator& operator--(int) { line_iterator& t = *this; --(*this); return t; }

                friend bool operator==(const line_iterator& a, const line_iterator& b) { return a._cursor == b._cursor; }
                friend bool operator!=(const line_iterator& a, const line_iterator& b) { return !(a == b); }

            private:
                line_iterator(matrix* m, size_t line, long pos) { _content = m; _line = line; _cursor = pos; }

                const size_t _line;
                long _cursor;
                matrix* _content;
        };

        class const_line_iterator {
            public:
                friend class matrix;

                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type = long;
                using value_type = T;
                using pointer = const T*;
                using reference = const T&;

                reference operator*() const { return _content->at(_line, (size_t) _cursor); }
                pointer operator->() const { return &(_content->at(_line, (size_t) _cursor)); }

                const_line_iterator& operator++() { _cursor++; return *this; }
                const_line_iterator& operator++(int) { const_line_iterator& t = *this; ++(*this); return t; }

                const_line_iterator& operator--() { _cursor--; return *this; }
                const_line_iterator& operator--(int) { const_line_iterator& t = *this; --(*this); return t; }

                friend bool operator==(const const_line_iterator& a, const const_line_iterator& b) { return a._cursor == b._cursor; }
                friend bool operator!=(const const_line_iterator& a, const const_line_iterator& b) { return !(a == b); }

            private:
                const_line_iterator(const matrix* m, size_t line, long pos) : _line(line) { _content = m; _cursor = pos; }

                const size_t _line;
                long _cursor;
                const matrix* _content;
        };

        class column_iterator {
            public:
                friend class matrix;

                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type = long;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                reference operator*() { return _content->at((size_t) _cursor, _column); }
                pointer operator->() { return &(_content->at((size_t) _cursor, _column)); }

                column_iterator& operator++() { _cursor++; return *this; }
                column_iterator& operator++(int) { column_iterator& t = *this; ++(*this); return t; }

                column_iterator& operator--() { _cursor--; return *this; }
                column_iterator& operator--(int) { column_iterator& t = *this; --(*this); return t; }

                friend bool operator==(const column_iterator& a, const column_iterator& b) { return a._cursor == b._cursor; }
                friend bool operator!=(const column_iterator& a, const column_iterator& b) { return !(a == b); }

            private:
                column_iterator(matrix* m, size_t column, long pos) { _content = m; _column = column; _cursor = pos; }

                const size_t _column;
                long _cursor;
                matrix* _content;
        };

        class const_column_iterator {
            public:
                friend class matrix;

                using iterator_category = std::bidirectional_iterator_tag;
                using difference_type = long;
                using value_type = T;
                using pointer = const T*;
                using reference = const T&;

                reference operator*() const { return _content->at((size_t) _cursor, _column); }
                pointer operator->() const { return &(_content->at((size_t) _cursor, _column)); }

                const_column_iterator& operator++() { _cursor++; return *this; }
                const_column_iterator& operator++(int) { const_column_iterator& t = *this; ++(*this); return t; }

                const_column_iterator& operator--() { _cursor--; return *this; }
                const_column_iterator& operator--(int) { const_column_iterator& t = *this; --(*this); return t; }

                friend bool operator==(const const_column_iterator& a, const const_column_iterator& b) { return a._cursor == b._cursor; }
                friend bool operator!=(const const_column_iterator& a, const const_column_iterator& b) { return !(a == b); }

            private:
                const_column_iterator(const matrix* m, size_t column, long pos) { _content = m; _column = column; _cursor = pos; }

                const size_t _column;
                long _cursor;
                const matrix* _content;
        };

        const T PadC = Pad;

        matrix(size_t rows, size_t columns) : _columns(columns), _colset(true) {
            for (size_t i = 0; i < rows * columns; i++)
                _content.push_back(Pad);
        }
        matrix(const matrix<T,Pad>& other) : _columns(other._columns), _colset(true), _content(other._content) {}
        matrix() : _colset(false) {}
        virtual ~matrix() {}

        matrix& operator=(const matrix& other) {
            this->copy_from(other);
            return *this;
        }

        size_t rows() const {
            size_t c = (_content.size() % _columns == 0 ? 0 : 1);
            return c + (_content.size() / _columns);
        }

        size_t columns() const {
            return _columns;
        }

        size_t size() const {
            return _content.size();
        }

        bool column_set() const {
            return _colset;
        }

        size_t geti(size_t id) const {
            return id / _columns;
        }

        size_t getj(size_t id) const {
            return id % _columns;
        }

        void set_rows(size_t rows) {
            for (size_t i = _content.size(); i < rows * _columns; i++)
                _content.push_back(Pad);
        }

        void set_columns(size_t columns) {
            _columns = columns;
            _colset = true;
        }

        bool in_bounds(const point& p) const {
            return p.x >= 0 && p.y >= 0 && p.x < _columns && p.y < rows();
        }

        const T& operator()(size_t i, size_t j) const {
            return this[id(_columns, i, j)];
        }

        T& operator()(size_t i, size_t j) {
            return at(i, j);
        }

        const T& operator[](size_t i) const {
            if (i >= _content.size())
                return PadC;
            else
                return _content[i];
        }

        T& operator[](size_t i) {
            for (size_t k = _content.size(); k <= i; k++)
                _content.push_back(Pad);
            return _content[i];
        }

        T cat(size_t i) const {
            return _content[i];
        }

        const T& at(size_t i) const {
            return _content[i];
        }

        const T& at(size_t i, size_t j) const {
            return _content[id(_columns, i, j)];
        }

        T& at(size_t i, size_t j) {
            return _content[id(_columns, i, j)];
        }

        const T& at(const point& p) const {
            return _content[id(_columns, (size_t) p.y, (size_t) p.x)];
        }

        T& at(const point& p) {
            return _content[id(_columns, (size_t) p.y, (size_t) p.x)];
        }

        void set(const point& p, const T& x) {
            _content[id(_columns, (size_t) p.y, (size_t) p.x)] = x;
        }

        void push_back(const T& elt) {
            _content.push_back(elt);
        }

        void copy_from(const matrix& m) {
            this->clear();
            this->_content.assign(m._content.cbegin(), m._content.cend());
//            std::copy(m._content.cbegin(), m._content.cend(), std::back_inserter(this->_content));
            _columns = m._columns;
            _colset = true;
        }

        void show_with(std::ostream& out, void (*showOne)(std::ostream&,size_t,const T&)) const {
            if (column_set()) {
                size_t nc = columns();
                for (size_t i = 0, end = size(); i < end; i++) {
                    showOne(out, i, at(i));
                    if ((i + 1) % nc == 0)
                        out << std::endl;
                }
            } else {
                out << "<<?>>" << std::endl;
            }
        }

        template<typename F>
        void show_with(std::ostream& out, F&& showOne) const {
            if (column_set()) {
                size_t nc = columns();
                for (size_t i = 0, end = size(); i < end; i++) {
                    std::forward<F>(showOne)(out, i, at(i));
                    if ((i + 1) % nc == 0)
                        out << std::endl;
                }
            } else {
                out << "<<?>>" << std::endl;
            }
        }

        struct pretty_printer {
            virtual void on_unset(std::ostream& out) { out << "<<?>>"; }
            virtual void on_element(std::ostream& out, size_t k, size_t i, size_t j, const T& e) = 0;
            virtual void on_linebegin(std::ostream& out, size_t i) = 0;
            virtual void on_lineend(std::ostream& out, size_t i) = 0;
        };

        void show_withp(std::ostream& out, pretty_printer* p) {
            if (column_set()) {
                size_t nc = columns();
                for (size_t i = 0, endi = rows(); i < endi; i++) {
                    p->on_linebegin(out, i);
                    for (size_t j = 0, endj = columns(); j < endj; j++) {
                        size_t k = i * nc + j;
                        p->on_element(out, k, i, j, at(k));
                    }
                    p->on_lineend(out, i);
                }
            } else {
                p->on_unset(out);
            }
        }

        void clear() {
            _content.clear();
            _columns = 0;
            _colset = false;
        }

        iterator& begin() {
            return *(new iterator(this, 0));
        }

        iterator& end() {
            return *(new iterator(this, rows() * columns()));
        }

        const_iterator& cbegin() const {
            return *(new const_iterator(this, 0));
        }

        const_iterator& cend() const {
            return *(new const_iterator(this, rows() * columns()));
        }

        line_iterator& line_begin(size_t line) {
            return *(new line_iterator(this, line, 0));
        }

        line_iterator& line_end(size_t line) {
            return *(new line_iterator(this, line, columns()));
        }

        const_line_iterator& line_cbegin(size_t line) const {
            return *(new const_line_iterator(this, line, 0));
        }

        const_line_iterator& line_cend(size_t line) const {
            return *(new const_line_iterator(this, line, columns()));
        }

        column_iterator& column_begin(size_t column) {
            return *(new column_iterator(this, column, 0));
        }

        column_iterator& column_end(size_t column) {
            return *(new column_iterator(this, column, rows()));
        }

        const_column_iterator& column_cbegin(size_t column) const {
            return *(new const_column_iterator(this, column, 0));
        }

        const_column_iterator& column_cend(size_t column) const {
            return *(new const_column_iterator(this, column, rows()));
        }

    private:
        static inline constexpr size_t id(size_t col, size_t i, size_t j) {
            return i * col + j;
        }

        bool _colset;
        size_t _columns;
        Container _content;
};

template<typename T, T Pad>
std::ostream& operator<<(std::ostream& out, const matrix<T,Pad>& m) {
    m.show_with(out, [](std::ostream& o, size_t, const T& e) { o << e; });
    return out;
}


}

#endif // MATRIX_H



