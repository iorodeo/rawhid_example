#include "constants.h"

#ifndef  __linux__
namespace constants
{

    // Communications timeouts
    const uint16_t DevToHostTimeout = 50;
    const uint16_t HostToDevTimeout = 50;

    // Timing parameters 
    const uint8_t  TimerPriority = 1;
    const uint32_t TimerPeriod_us = 5000ul;

    // Analog input parameters
    const uint8_t AnalogReadNumBits = 16;
    const uint8_t AnalogReadNumAvg = 32;
    const uint8_t AnalogRefType = INTERNAL;
    const uint8_t AnalogInputPinArray[NumAnalogInput] = {A0,A1,A2,A3,A4,A5,A10,A11,A12,A13};

};
#endif
