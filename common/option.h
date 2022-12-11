#ifndef OPTION_H
#define OPTION_H

#include <exception>

namespace common {

class none_access_exception: public exception {
    public:
        none_access_exception() 
            : _msg("attempting to read value of none") {}
        none_access_exception(const char* var)
            : _msg(std::string("attempting to read value of '") + var + "' which is set to none") {}

        const char* what() const noexcept {
            return _msg.c_str();
        }
    
    private:
        const std::string _msg;
};

template<typename T>
class option {
    public:
        option() : _set(false) {}
        option(const T& value) : _set(true), _value(value) {}

        bool is_set() const { return _set; }
        const T& value() const {
            if (!_set)
                throw none_access_exception();
            return _value;
        }

        const T& value(const char* name) const {
            if (!_set)
                throw none_access_exception(name);
            return _value;
        }

        void set(const T& value) {
            _set = true;
            _value = value;
        }

    private:
        T _value;
        bool _set;
};

}


#endif // OPTION_H



