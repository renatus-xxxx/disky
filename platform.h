#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
typedef uint16_t platform_clock_t;
//typedef unsigned int clock_t;
#define CLOCKS_PER_SEC 60
#define JIFFY          0xfc9e

platform_clock_t platform_clock(void) {
  uint8_t* ptr = (uint8_t*)0xFC9E;
  return (platform_clock_t)(ptr[0] | (ptr[1] << 8));
}

float platform_elapsed(clock_t start, clock_t end) {
  return ((end - start) & 0xFFFF) / (float)CLOCKS_PER_SEC;
}

#endif // PLATFORM_H
