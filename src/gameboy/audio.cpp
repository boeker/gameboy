// Copyright (c) 2014 Jan Böker
// MIT License

#include "audio.h"

#include <QDebug>
#include "apu/Multi_Buffer.h"

namespace gameboy {
Audio::Audio() {
    count = -1;
    sampleBuffer = new blip_sample_t[sampleBufferSize];
    apu = new Gb_Apu();
    buffer = new Stereo_Buffer();

    buffer->set_sample_rate(sampleRate);
    buffer->clock_rate(4194304);

    apu->set_output(buffer->center(), buffer->left(), buffer->right());

    reset();
}

Audio::~Audio() {
    delete buffer;
    delete apu;
    delete[] sampleBuffer;
}

void Audio::reset() {
    playFlag = false;
    clocks = 0;

    apu->reset(Gb_Apu::mode_dmg);
    buffer->clear();
}

void Audio::step(unsigned int lastClocks) {
    clocks += lastClocks;
}

uint8_t Audio::read(uint16_t address) {
    return apu->read_register(clocks, address);
}

void Audio::write(uint16_t address, uint8_t value) {
    apu->write_register(clocks, address, value);
}

long Audio::getSampleCount() {
    return count;
}

bool Audio::getPlayFlag() {
    return playFlag;
}

blip_sample_t* Audio::getSampleBuffer() {
    return sampleBuffer;
}

void Audio::endFrame() {
    apu->end_frame(clocks*4);
    buffer->end_frame(clocks*4);
    clocks = 0;

    if (buffer->samples_avail() >= sampleBufferSize) {
        count = buffer->read_samples(sampleBuffer, sampleBufferSize);
        playFlag = true;
    } else {
        playFlag = false;
    }
}
}
