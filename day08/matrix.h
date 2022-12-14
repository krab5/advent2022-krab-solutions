#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

template<typename T, T Pad>
class matrix {
    public:
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

        matrix(size_t rows, size_t columns) : _columns(columns), _colset(true) {
            for (size_t i = 0; i < rows * columns; i++)
                _content.push_back(Pad);
        }
        matrix() : _colset(false) {}
        virtual ~matrix() {}

        size_t rows() const {
            size_t c = (_content.size() % _columns == 0 ? 0 : 1);
            return c + (_content.size() / _columns);
        }

        size_t columns() const {
            return _columns;
        }

        bool column_set() const {
            return _colset;
        }

        void set_rows(size_t rows) {
            for (size_t i = _content.size(); i < rows * _columns; i++)
                _content.push_back(Pad);
        }

        void set_columns(size_t columns) {
            _columns = columns;
            _colset = true;
        }

        const T& operator()(size_t i, size_t j) const {
            return this[id(_columns, i, j)];
        }

        T& operator()(size_t i, size_t j) {
            return at(i, j);
        }

        const T& operator[](size_t i) const {
            if (i >= _content.size())
                return Pad;
            else
                return _content[i];
        }

        T& operator[](size_t i) {
            for (size_t k = _content.size(); i <= k; i++)
                _content.push_back(Pad);
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

        void push_back(const T& elt) {
            _content.push_back(elt);
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
        vector<T> _content;
};


#endif // MATRIX_H



