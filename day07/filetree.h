#ifndef FILETREE_H
#define FILETREE_H

#include <ostream>
#include <string>
#include <vector>

using namespace std;

namespace filetree {

class abstract_node {
    public:
        abstract_node(const string& name, bool isdir, bool isroot, abstract_node* parent);
        virtual ~abstract_node();

        virtual const string& name() const;
        virtual size_t size() const = 0;
        virtual bool is_directory() const;
        virtual bool is_root() const;
        virtual abstract_node* parent();

        virtual void print(ostream& stream, const string& prefix = "") const = 0;

    protected:
        abstract_node* _parent;

    private:
        string _name;
        bool _isdir;
        bool _isroot;
};

class file_node;

class dir_node: public abstract_node {
    public:
        dir_node(const string& name, abstract_node* parent);
        virtual ~dir_node();

        virtual size_t size() const;
        virtual vector<abstract_node*> children() const;

        abstract_node* find_child(const string& name);
        dir_node* find_child_dir(const string& name);

        bool has_child(const string& name) const;
        bool has_child_file(const string& name) const;
        bool has_child_dir(const string& name) const;

        dir_node* add_child(const string& name);
        file_node* add_child(const string& name, size_t size);

        virtual void print(ostream& stream, const string& prefix = "") const;

    protected:
        dir_node(const string& name);
        void add_child(abstract_node* child);

    private:
        vector<abstract_node*> _children;
};

class root_node: public dir_node {
    public:
        root_node();
        virtual ~root_node();
};

class file_node: public abstract_node {
    public:
        file_node(const string& name, size_t size, abstract_node* parent);
        virtual ~file_node();

        virtual size_t size() const;

        virtual void print(ostream& stream, const string& prefix = "") const;

    private:
        size_t _size;
};

// prefix browsing
template<typename T>
static T fold(const abstract_node* node, T (*combine)(const abstract_node*, T), T zero) {
    T acc = combine(node, zero);

    if (node->is_directory()) {
        vector<abstract_node*> children = (static_cast<const dir_node*>(node))->children();
        for (auto it = children.cbegin(); it != children.cend(); it++) {
            acc = fold(*it, combine, acc);
        }
    }

    return acc;
}

template<typename T, typename P>
static T foldP(const abstract_node* node, P param, T (*combine)(const abstract_node*, P, T), T zero) {
    T acc = combine(node, param, zero);

    if (node->is_directory()) {
        vector<abstract_node*> children = (static_cast<const dir_node*>(node))->children();
        for (auto it = children.cbegin(); it != children.cend(); it++) {
            acc = foldP(*it, param, combine, acc);
        }
    }

    return acc;
}

}


#endif // FILETREE_H


