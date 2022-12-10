#ifndef OBSERVER_H
#define OBSERVER_H

#include "cpu.h"
#include "inst.h"

class observer {
    public:
        virtual ~observer() {}

        /** Event triggered at the beginning of a new CPU cycle.
         */
        virtual void on_begin_cycle() = 0;
        /** Event triggered right after fetching the insutrction.
         */
        virtual void on_fetch() = 0;
        /** Event triggered right after execution is finished.
         */
        virtual void on_exec() = 0;

        //virtual void on_end_cycle() = 0;
        
        friend cpu;
    
    protected:
        const cpu& the_cpu() { return *_cpu; }

    private:
        void set_cpu(cpu* cpu) { _cpu = cpu; }
        cpu* _cpu;
};


#endif // OBSERVER_H


