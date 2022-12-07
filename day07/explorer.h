#ifndef EXPLORER_H
#define EXPLORER_H

#include "filetree.h"

using namespace std;

class explorer {
    public:
        class explorer_exception: public exception {
            public:
                explorer_exception(const string& msg);
                virtual const char* what() const noexcept;

            private:
                string _msg;
        };

        explorer(filetree::dir_node* node);
        virtual ~explorer();

        void change_dir_up();
        void change_dir(const string& name);
        void add_dir_child(const string& name);
        void add_file_child(const string& name, size_t size);

    private:
        filetree::dir_node* _cursor;
};


#endif //EXPLORER_H


