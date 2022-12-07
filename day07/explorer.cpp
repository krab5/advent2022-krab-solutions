#include "explorer.h"

using namespace std;
using namespace filetree;

explorer::explorer_exception::explorer_exception(const string& msg) : _msg(msg) {}
const char* explorer::explorer_exception::what() const noexcept {
    return _msg.c_str();
}

explorer::explorer(dir_node* node) : _cursor(node) {}
explorer::~explorer() {}

void explorer::change_dir_up() {
    _cursor = static_cast<dir_node*>(_cursor->parent());
}

void explorer::change_dir(const string& name) {
    dir_node* child = _cursor->find_child_dir(name);

    if (child == NULL)
        throw explorer_exception(name + ": no such directory");

    _cursor = child;
}

void explorer::add_dir_child(const string& name) {
    if (!_cursor->has_child_dir(name))
        _cursor->add_child(name);
}

void explorer::add_file_child(const string& name, size_t size) {
    if (!_cursor->has_child_file(name))
        _cursor->add_child(name, size);
}



