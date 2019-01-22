#ifndef SAW_WAVE_H
#define SAW_WAVE_H

#include <kernel/Wave.hpp>

class SawWave: public Wave {
public:
private:
    const int16_t valueAt(uint8_t) const;
};

#endif /* SAW_WAVE_H */