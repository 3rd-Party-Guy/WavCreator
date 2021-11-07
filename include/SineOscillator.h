#ifndef SINEOSCILLATOR_H
#define SINEOSCILLATOR_H
#include <iostream>
#include <cmath>

class SineOscillator
{
    float frequency, amplitude;
    float angle = 0.0f;
    float offset = 0.0f;
    int sampleRate;

    public:
        SineOscillator(float freq, float amp, int sRate) :
            frequency(freq), amplitude(amp), sampleRate(sRate)
            {
                offset = 2 * M_PI * frequency / sampleRate;
            }
        float Process();
        virtual ~SineOscillator();

    protected:

    private:
};

#endif // SINEOSCILLATOR_H
