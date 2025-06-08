#ifndef PLATFORM_H
#define PLATFORM_H

#define PLATFORM_MSX  (0)
#define PLATFORM_X68K (0)

#if PLATFORM_MSX
typedef int clock_t;
#define CLOCKS_PER_SEC 60

clock_t platform_clock(void) {
  volatile char* ptr = (char*)0xFC9E;
  return (ptr[0]) | (ptr[1] << 8);
}

float platform_elapsed(clock_t start, clock_t end) {
  return ((end - start) & 0xFFFF) / (float)CLOCKS_PER_SEC;
}
#endif

#if PLATFORM_X68K
typedef int clock_t;
#define CLOCKS_PER_SEC 50

static inline clock_t platform_clock(void) {
  uint32_t ticks;
  asm volatile (
    "move.b #0x25, %%d1\n\t"
    "trap    #1\n\t"
    "move.l  %%d0, %0"
    : "=g"(ticks) :: "d0", "d1"
  );
  return ticks;
}

static inline double platform_elapsed(clock_t start, clock_t end) {
  return (end - start) / (double)CLOCKS_PER_SEC;
}

#endif

#if !((PLATFORM_MSX) && (PLATFORM_X68K))
#include <time.h>
static inline clock_t platform_clock(void) {
  return clock();
}

static inline double platform_elapsed(clock_t start, clock_t end) {
  return (double)(end - start) / CLOCKS_PER_SEC;
}
#endif

#endif // PLATFORM_H
