#pragma once

#include <time.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#ifdef CLOCK_MONOTONIC_RAW
#define SW_CLOCK CLOCK_MONOTONIC_RAW
#else
#define SW_CLOCK CLOCK_MONOTONIC
#endif

class StopWatch {
  public:
   StopWatch();
   virtual ~StopWatch();

   void start();
   void stop();
   uint32_t get_seconds();
   uint32_t get_milli();
   uint64_t get_micro();
   uint64_t get_nano();

  private:
   struct timespec _begin, _end;
   static const uint32_t ONE_BILLION;
   static const uint32_t ONE_MILLION;
   static const uint32_t ONE_THOUSAND;

   uint64_t get();
   void set(struct timespec* container);
};
