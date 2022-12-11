#include "parser.h"
#include "object.h"
#include <deque>

#include "option.h"

#define substring(line, start, end) line.substr(start, end - start)

using namespace std;
using namespace common;

struct parser::monkey_builder {
    option<id_t> id;
    option<id_t> mon_if;
    option<id_t> mon_else;
    option<monkey::operation::op_type> opt;
    option<level_t> opop;
    option<monkey::test::test_type> tt;
    option<level_t> top;
    deque<object> start;

    monkey build() {
        monkey m(
            id.value("id"),
            monkey::operation(opt.value("op_type"), opop.value("op_operand")),
            monkey::test(tt.value("test_type"), top.value("test_operand")),
            mon_if.value("monkey_if"), mon_else.value("monkey_else"));
        for (object o : start)
            m.receive(o);
        return m;
    }
};

//parser::parser(istream& stream) : common::reader<vector<monkey>>(stream) {}
parser::parser() {}
parser::~parser() {
    if (_builder != nullptr) {
        delete _builder;
    }
}

void parser::on_start() {
    _monkeys.clear();
    _builder = new monkey_builder();
}

inline static bool next_char(const string& line, char c, size_t& x) {
    size_t s = line.size();
    while (x < s && line[x] != c) x++;
    return (x >= s);
}

inline static bool next_non_char(const string& line, char c, size_t& x) {
    size_t s = line.size();
    while (x < s && line[x] == c) x++;
    return (x >= s);
}

inline static bool next_space(const string& line, size_t& x) {
    return next_char(line, ' ', x);
}

inline static bool next_non_space(const string& line, size_t& x) {
    return next_non_char(line, ' ', x);
}

inline static monkey::operation::op_type get_opc(char c) {
    switch (c) {
        case '+':
            return monkey::operation::Add;
        case '*':
            return monkey::operation::Mul;
        default:
            return monkey::operation::Nop;
    }
}

bool parser::on_line(const std::string& line) {
    size_t start = 0, end;
    next_non_space(line, start);
    end = start;
    next_space(line, end);

    if (substring(line, start, end) == "Monkey") {
        start = end;
        next_non_space(line, start);
        end = start;
        next_char(line, ':', end);
        _builder->id.set((id_t) stoi(substring(line, start, end)));
    } else {
        end--;
        next_char(line, ':', end);
        string cmd = substring(line, start, end);
        start = end + 1;
        next_non_space(line, start);
        string op = substring(line, start, string::npos);

        if (cmd == "Starting items") {
            start = 0; end = 0;
            while (end < op.size()) {
                end = start;
                next_char(op, ',', end);
                _builder->start.push_back(object(parse_level(substring(op, start, end))));
                start = end + 1;
                next_non_space(line, start);
            }
        } else if (cmd == "Operation") {
            start = 10; // size of "new = old "
            char o = op[start];
            start += 2;
            monkey::operation::op_type ot = get_opc(o);
            string ov = substring(op, start, string::npos);

            if (ot == monkey::operation::Mul && ov == "old") {
                _builder->opt.set(monkey::operation::Pow);
                _builder->opop.set(2);
            } else {
                _builder->opt.set(get_opc(o));
                _builder->opop.set(parse_level(ov));
            }
        } else if (cmd == "Test") {
            start = 0; end = start;
            next_space(op, end);
            if (substring(op, start, end) == "divisible") {
                start = end + 3; // size of "by "
                _builder->tt.set(monkey::test::Div);
                _builder->top.set(stol(substring(op, start, string::npos)));
            }
        } else if (cmd == "If true" || cmd == "If false") {
            option<id_t>* o = (cmd == "If true" ? &_builder->mon_if : &_builder->mon_else);
            start = 16; // size of "throw to monkey "
            o->set(stol(substring(op, start, string::npos)));
        }
    }

    return true;
}

bool parser::on_sep(const std::string& sep) {
    if (_builder->id.is_set()) {
        _monkeys.push_back(_builder->build());
        delete _builder;
        _builder = new monkey_builder();
    }
    return true;
}

vector<monkey> parser::finish() {
    on_sep("");
    delete _builder;
    _builder = nullptr;
    return _monkeys;
}



