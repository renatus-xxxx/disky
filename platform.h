#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef MSX
  typedef uint16_t clock_t;
  #define CLOCKS_PER_SEC 60

  static inline clock_t platform_clock(void) {
    volatile uint8_t* ptr = (uint8_t*)0xFC9E;
    return (ptr[0]) | (ptr[1] << 8);
  }

  static inline double platform_elapsed(clock_t start, clock_t end) {
    return ((end - start) & 0xFFFF) / (double)CLOCKS_PER_SEC;
  }

#elif defined(X68K)
  typedef uint32_t clock_t;
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

#else // POSIX / default
  #include <stdint.h>
  #include <time.h>
  typedef clock_t clock_t;
  // CLOCKS_PER_SEC is already defined by <time.h>

  static inline clock_t platform_clock(void) {
    return clock();
  }

  static inline double platform_elapsed(clock_t start, clock_t end) {
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    if (sec <= 0.0) sec = 1e-6;
    return sec;
  }
#endif

#endif // PLATFORM_H
