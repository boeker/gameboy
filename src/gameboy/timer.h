#ifndef GAMEBOY_TIMER_H
#define GAMEBOY_TIMER_H

namespace gameboy {
class Memory;
}

namespace gameboy {
class Timer {
 public:
    explicit Timer(Memory *memory);
    virtual ~Timer();
    void reset();

    void step(unsigned int lastClocks);

 private:
    void stepCounter();

 private:
    Memory *memory;

    unsigned int clocks;
    unsigned int main; // 1/4 of m-clock (which is 1/4 of the base clock)
                       // 262,144Hz
    unsigned int dividerHelper; // 0xFF04 - Divider - 16384Hz (1/16 main)
};
}

#endif
