#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef __linux__
#include "Arduino.h"
#else
#include <cstdint>
#endif

namespace constants
{
    const uint8_t NumAnalogInput = 10;
    const uint8_t NumStepper = 5;
    const uint8_t NumPwm = 5;
    const uint8_t NumTrigger = 2;
    const uint8_t NumDigitalOutput = 2;

#ifndef __linux__
    // Communications timeouts
    extern const uint16_t DevToHostTimeout;
    extern const uint16_t HostToDevTimeout;

    // Timing parameters 
    extern const uint8_t  TimerPriority;
    extern const uint32_t TimerPeriod_us;

    // Analog input parameters
    extern const uint8_t AnalogReadNumBits;
    extern const uint8_t AnalogReadNumAvg;
    extern const uint8_t AnalogRefType;
    extern const uint8_t AnalogInputPinArray[NumAnalogInput]; 
#endif 

} // namespace
#endif

