#include "filetree.h"

#include <algorithm>

using namespace std;
using namespace filetree;

abstract_node::abstract_node(const string& name, bool isdir, bool isroot, abstract_node* parent) : 
    _name(name), _isdir(isdir), _isroot(isroot), _parent(parent) {}
abstract_node::~abstract_node() {}

const string& abstract_node::name() const {
    return _name;
}

bool abstract_node::is_directory() const {
    return _isdir;
}

bool abstract_node::is_root() const {
    return _isroot;
}

abstract_node* abstract_node::parent() {
    return _parent;
}


dir_node::dir_node(const string& name) : abstract_node(name, true, true, NULL) {}
dir_node::dir_node(const string& name, abstract_node* parent) : abstract_node(name, true, false, parent) {}
dir_node::~dir_node() {
    for (auto it = _children.begin(); it != _children.end(); it++) {
        delete *it;
    }
}

vector<abstract_node*> dir_node::children() const {
    return _children;
}

size_t dir_node::size() const {
    size_t sum = 0;
    for (auto it = _children.cbegin(); it != _children.cend(); it++)
        sum += (*it)->size();
    return sum;
}

abstract_node* dir_node::find_child(const string& name) {
    abstract_node* result = NULL;
    auto it = _children.begin();
    while (it != _children.end() && result == NULL) {
        if ((*it)->name() == name)
            result = *it;
        it++;
    }
    return result;
}

dir_node* dir_node::find_child_dir(const string& name) {
    abstract_node* result = NULL;
    auto it = _children.begin();
    while (it != _children.end() && result == NULL) {
        if ((*it)->is_directory() && (*it)->name() == name)
            result = *it;
        it++;
    }
    return static_cast<dir_node*>(result);
}

bool dir_node::has_child(const string& name) const {
    return find_if(_children.cbegin(), _children.cend(), [name](abstract_node* n) {
        return (n->name() == name);
    }) != _children.cend();
}

bool dir_node::has_child_file(const string& name) const {
    return find_if(_children.cbegin(), _children.cend(), [name](abstract_node* n) {
        return (!n->is_directory() && n->name() == name);
    }) != _children.cend();
}

bool dir_node::has_child_dir(const string& name) const {
    return find_if(_children.cbegin(), _children.cend(), [name](abstract_node* n) {
        return (n->is_directory() && n->name() == name);
    }) != _children.cend();
}

void dir_node::add_child(abstract_node* child) {
    _children.push_back(child);
}

dir_node* dir_node::add_child(const string& name) {
    dir_node* dn = new dir_node(name, this);
    this->add_child(dn);
    return dn;
}

file_node* dir_node::add_child(const string& name, size_t size) {
    file_node* fn = new file_node(name, size, this);
    this->add_child(fn);
    return fn;
}

void dir_node::print(ostream& stream, const string& prefix) const {
    stream << prefix << " - " << this->name() << " (dir)" << endl;
    for (auto it = _children.cbegin(); it != _children.cend(); it++)
        (*it)->print(stream, prefix + " ");
}

root_node::root_node() : dir_node("/") {}
root_node::~root_node() {}

file_node::file_node(const string& name, size_t size, abstract_node* parent) : 
    abstract_node(name, false, false, parent), _size(size) {}
file_node::~file_node() {}

size_t file_node::size() const {
    return _size;
}

void file_node::print(ostream& stream, const string& prefix) const {
    stream << prefix << " - " << this->name() << " (file, size=" << this->size() << ")" << endl;
}


