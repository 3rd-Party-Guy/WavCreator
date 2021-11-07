#include "SineOscillator.h"

SineOscillator::~SineOscillator()
{
    //dtor
}

float SineOscillator::Process()
{
    //Asin(2pi*f/sr)

    auto sample = amplitude * sin(angle);
    angle += offset;

    return sample;
}
