#ifndef TODO_H
#define TODO_H

#include <deque>

namespace common {

template<class T, class Allocator = std::allocator<T>>
class todo {
    public:
        todo() {}

        void pop() {
            _content.pop_front();
        }

        void push(const T& v) {
            for (T w : _content) {
                if (w == v)
                    return;
            }
            _content.push_back(v);
        }

        const T& peek() {
            return _content.front();
        }

        bool empty() const {
            return _content.empty();
        }

        size_t size() const {
            return _content.size();
        }

    private:
        std::deque<T,Allocator> _content;
};

}

#endif // TODO_H


