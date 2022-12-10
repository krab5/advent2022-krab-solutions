#ifndef CPU_H
#define CPU_H

#include "inst.h"

#include <queue>

#define PIPELINE_LIMIT  1

class observer;

class cpu {
    public:
        cpu(const state& init, const std::vector<inst>& prgrm);
        ~cpu();

        void register_observer(observer* o);

        size_t get_num_cycles() const;
        const state& get_state() const;
        const inst& get_pipeline_front() const;
        size_t get_pc() const;

        void step();

        bool finished();

    private:
        bool fetch();
        void exec();
        bool pipe_in(const inst& i);

        std::vector<observer*> _observers;

        state _state;
        std::vector<inst> _instructions;
        std::queue<inst> _pipeline;
        size_t _numcycles;
        size_t _currentinst;
        size_t _pc;
};

#endif // CPU_H


