#include <iostream>
#include <fstream>
#include "filetree.h"
#include "explorer.h"
#include "termread.h"

#define THRESHOLD   100000
#define MAX_SPACE   70000000
#define REQ_SPACE   30000000

using namespace std;

void build_tree(filetree::root_node* root, const vector<term_line>& lines) {
    explorer ex(root);
    for (auto line = lines.cbegin(); line != lines.cend(); line++) {
        switch (line->type) {
            case CommandLs:
                break;
            case CommandCd:
                if (line->content == "..") {
                    ex.change_dir_up();
                } else if (line->content == "/") {
                } else {
                    ex.change_dir(line->content);
                }
                break;
            case ResultFile:
                ex.add_file_child(line->content, line->extra);
                break;
            case ResultDir:
                ex.add_dir_child(line->content);
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return -1;
    }
    ifstream stream(argv[1]);
    termread tr(stream);
    vector<term_line> result = tr.do_parse();
    cout << "Parsed " << result.size() << " terminal lines" << endl;

    filetree::root_node root;
    build_tree(&root, result);

    cout << "Resulting tree:" << endl;
    root.print(cout);

    const size_t occupied = root.size();
    const size_t free = MAX_SPACE - occupied;

    cout << "=> Occupation: " << occupied << "/" << MAX_SPACE << " (free space: " << free << ")" << endl;
    cout << endl;

    size_t sum = filetree::fold<size_t>(&root,
        [](const filetree::abstract_node* node, size_t acc) {
            size_t size = node->size();
            if (node->is_directory() && size <= THRESHOLD)
                return acc + size;
            else return acc;
        }, 0);

    cout << "Total size of directories with size >= " << THRESHOLD << " = " << sum << endl;

    const size_t tofree = REQ_SPACE - free;

    const filetree::abstract_node* todel = filetree::foldP<const filetree::abstract_node*, size_t>(&root, tofree,
        [](const filetree::abstract_node* node, size_t tofree, const filetree::abstract_node* acc) {
            size_t size = node->size();
            if (node->is_directory() && size > tofree && size < acc->size())
                return node;
            else
                return acc;
        }, &root);
    cout << "Need to clear up " << tofree << " space." << endl;
    cout << "=> Can be achieved by removing " << todel->name() << " (size=" << todel->size() << ")" << endl;

    return 0;
}


