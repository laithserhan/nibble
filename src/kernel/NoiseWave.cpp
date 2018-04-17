#include <kernel/NoiseWave.hpp>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <iostream>
using namespace std;

NoiseWave::NoiseWave():
    Wave() {
	amplitude = 1;
}

int16_t* NoiseWave::fill(const unsigned int sampleCount) {
	for (unsigned int i=0;i<sampleCount;i++) {
		samples[i] = 0;
	}

	unsigned int hz = int(1.0/period*44100);
	unsigned int err = 0;
	unsigned int val = 0;

	for (unsigned int i=0;i<sampleCount;i++) {
		err += hz;
		if (err > 44100){
			err -= 44100;
			val = rand();
		}
		samples[i] = val;
	}

	return samples;
}
