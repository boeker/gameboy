// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_AUDIO_H
#define GAMEBOY_AUDIO_H

#include <atomic>
#include <cinttypes>
#include "apu/Gb_Apu.h"

class Stereo_Buffer;

namespace gameboy {
class Audio {
 public:
    explicit Audio();
    virtual ~Audio();
    void reset();

    void step(unsigned int lastClocks);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    long getSampleCount();
    bool getPlayFlag();
    blip_sample_t* getSampleBuffer();
    
    void endFrame();

 public:
    static const int sampleBufferSize = 8192;
    static const int sampleRate = 44100;

 private:
    bool playFlag;
    unsigned int clocks;

    Gb_Apu *apu;
    Stereo_Buffer *buffer;
    
    blip_sample_t *sampleBuffer;
    long count;
};
}

#endif
