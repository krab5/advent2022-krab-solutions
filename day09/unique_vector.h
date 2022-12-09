#ifndef UNIQUE_VECTOR_H
#define UNIQUE_VECTOR_H

#include <vector>

using namespace std;

template<typename T, typename Allocator=allocator<T>>
class unique_vector: public vector<T,Allocator> {
    public:
        unique_vector() : vector<T,Allocator>() {}
        unique_vector(const unique_vector& other) : vector<T,Allocator>(other) {}
        unique_vector(const vector<T,Allocator>& other) : vector<T,Allocator>() {
            for (auto it = other.cbegin(); it != other.cend(); it++)
                this->insert(*it);
        }

        virtual ~unique_vector() {}

        bool contains(const T& value) const {
            for (auto it = this->cbegin(); it != this->cend(); it++) {
                if (*it == value)
                    return true;
            }
            return false;
        }

        void insert(const T& value) {
            if (!contains(value))
                this->push_back(value);
        }
};

#endif // UNIQUE_VECTOR_H



