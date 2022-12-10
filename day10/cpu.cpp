#include <iostream>
#include <iomanip>
#include "observer.h"
#include "cpu.h"

using namespace std;

cpu::cpu(const state& init, const std::vector<inst>& prgrm) : 
    _state(init), _instructions(prgrm),
    _numcycles(0), _currentinst(0), _pc(0) {}
cpu::~cpu() {}

void cpu::register_observer(observer* o) {
    o->set_cpu(this);
    _observers.push_back(o);
}

size_t cpu::get_num_cycles() const {
    return _numcycles;
}

const state& cpu::get_state() const {
    return _state;
}

const inst& cpu::get_pipeline_front() const {
    return _pipeline.front();
}

size_t cpu::get_pc() const {
    return _pc;
}

void cpu::step() {
    _numcycles++;
    for (observer* o : _observers) o->on_begin_cycle();

    fetch();
    for (observer* o : _observers) o->on_fetch();

    exec();
    for (observer* o : _observers) o->on_exec();
}

bool cpu::finished() {
    return (_pc >= _instructions.size() && _pipeline.empty());
}

bool cpu::fetch() {
    bool changed = pipe_in(_instructions[_pc]);
    if (changed)
        _pc++;
    return changed;
}

void cpu::exec() {
    if (!_pipeline.empty())
        _currentinst++;

    if (_currentinst >= _pipeline.front().num_cycles()) {
        _pipeline.front().apply(_state);
        _pipeline.pop();
        _currentinst = 0;
    }
}

bool cpu::pipe_in(const inst& i) {
    if (_pipeline.size() >= PIPELINE_LIMIT)
        return false;
    _pipeline.push(i);
    return true;
}




