#include "packet.h"
#include <sstream>

element::element() {}

element::element(element_type t) : type(t) {}
element::element(const element& other) :
    type(other.type), list(other.list), integer(other.integer) {}

element& element::operator=(const element& other) {
    type = other.type;
    list = other.list;
    integer = other.integer;
    return *this;
}

void element::lift() {
    type = List;
    list.clear();
    list.push_back(mk_int(integer));
}

element element::mk_list(const std::vector<element>& l) {
    element e;
    e.type = List;
    e.list = l;
    return e;
}

element element::mk_int(int i) {
    element e;
    e.type = Integer;
    e.integer = i;
    return e;
}

element extract_int(const std::string& str, std::string::const_iterator& it) {
    auto start = it;
    while ('0' <= *it && *it <= '9') { it++; }
    return element::mk_int(std::stoi(std::string(start, it)));
}

element extract_list(const std::string& str, std::string::const_iterator& it) {
    element result(List);
    bool cue = true;
    auto start = it;

    while (it < str.cend() && cue) {
        if (*it == '[') {
            it++;
            result.list.push_back(extract_list(str, it));
        } else if (*it == ']') {
            cue = false;
            it++;
        } else if ('0' <= *it && *it <= '9') {
            result.list.push_back(extract_int(str, it));
        } else {
            it++;
        }
    }

    return result;
}

element extract(const std::string& str) {
    auto beg = str.cbegin();
    if (str[0] == '[') {
        beg++;
        return extract_list(str, beg);
    } else {
        return extract_int(str, beg);
    }
}

int compare(const element& left, const element& right) {
    if (left.type == Integer && right.type == Integer) {
        if (left.integer == right.integer)
            return 0;
        else if (left.integer < right.integer)
            return -1;
        else
            return 1;
    } else if (left.type == List && right.type == List) {
        size_t i = 0;
        int r;
        while (i < left.list.size() && i < right.list.size()) {
            r = compare(left.list[i], right.list[i]);
            if (r != 0)
                return r;
            i++;
        }
        if (i < left.list.size())
            return 1;
        else if (i < right.list.size())
            return -1;
        else
            return 0;
    } else {
        element ll(left), rr(right);
        if (ll.type == Integer)
            ll.lift();
        if (rr.type == Integer)
            rr.lift();
        return compare(ll, rr);
    }
}

std::string to_str(const element& elt) {
    std::ostringstream so;
    if (elt.type == Integer) {
        so << elt.integer;
    } else {
        so << '[';
        for (size_t i = 0; i < elt.list.size(); i++) {
            so << elt.list[i];
            if (i < elt.list.size() - 1)
                so << ',';
        }
        so << ']';
    }
    return so.str();
}

bool operator==(const element& lhs, const element& rhs) {
    return compare(lhs, rhs) == 0;
}

std::ostream& operator<<(std::ostream& out, const element& elt) {
    out << to_str(elt);
    return out;
}


