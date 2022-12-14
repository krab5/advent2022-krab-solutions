#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>
#include <ostream>

enum element_type { List, Integer };

struct element {
    element_type type;
    std::vector<element> list;
    int integer;

    element(element_type t);
    element(const element& other);

    element& operator=(const element& other);

    void lift();

    static element mk_list(const std::vector<element>& l);
    static element mk_int(int i);

private:
    element();
};

element extract(const std::string& str);
int compare(const element& left, const element& right);

bool operator==(const element& lhs, const element& rhs);

std::ostream& operator<<(std::ostream& out, const element& elt);

#endif // PACKET_H


