# FFTPitchShift

## VST3 Plugin
This is a VST3 plugin. You can include FFTPitchShift.vst3 file into your VST3 folder and use in your DAW that supports VST3.
This folder provides Mac build environment but you can also copy the source code and build it in your desirable environments.

## How to use it
This plugin does not have GUI. However, it provides parameter that can be detected, adjusted and automated your DAW. Pitch parameter goes from 0 to 1 where 0 means no pitch shifting and 1 means twice the frequency. The value moves exponentially as it represents change in midi pitch value. 

## Sources
- FFT C++ algorithm : [https://rosettacode.org/wiki/Fast_Fourier_transform#C++](https://rosettacode.org/wiki/Fast_Fourier_transform#C++)
- Process Phase Vocoder : [Youtube Link](https://youtu.be/2p_-jbl6Dyc?si=1MZkuIqaFgCLCBnz&t=1742)
