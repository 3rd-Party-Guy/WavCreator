#include <iostream>
#include <fstream>

#include "SineOscillator.h"

const int sampleRate = 44100;
const int bitDepth = 16;

void WriteToFile(std::ofstream &file, int value, int size)
{
    file.write(reinterpret_cast<const char*>(&value), size);
}

int main(int argc, const char* argv[])
{
    SineOscillator sineOsc(340, 1, sampleRate);

    std::ofstream audioFile;
    audioFile.open("output.wav", std::ios::binary);

    // Header Chunk
    audioFile << "RIFF"; audioFile << "----";
    audioFile << "WAVE";

    // Format Chunk
    audioFile << "fmt ";
    WriteToFile(audioFile, 16, 4);          // Size
    WriteToFile(audioFile, 1, 2);           // Compression Code
    WriteToFile(audioFile, 1, 2);           // Number of Channels
    WriteToFile(audioFile, sampleRate, 4);  // Sample Rate
    WriteToFile(audioFile, sampleRate *     // Byte Rate
        bitDepth / 8, 4);
    WriteToFile(audioFile, bitDepth / 8, 2);// Block Align
    WriteToFile(audioFile, bitDepth, 2);    // Bit Depth

    // Data Chunk
    audioFile << "data";
    audioFile << "----";

    int preDataPos = audioFile.tellp();
    auto maxAmplitude = pow(2, bitDepth - 1) - 1;
    int duration = 3;

    for(int i = 0; i < sampleRate * duration; i++)
    {
        auto sample = sineOsc.Process();
        auto intSample = static_cast<int>(sample * maxAmplitude);

        WriteToFile(audioFile, intSample, 4);
    }
    int postDataPos = audioFile.tellp();

    audioFile.seekp(preDataPos - 4);
    WriteToFile(audioFile, postDataPos - preDataPos, 4);

    audioFile.seekp(4, std::ios::beg);
    WriteToFile(audioFile, postDataPos - 8, 4);

    audioFile.close();
    return 0;
}
