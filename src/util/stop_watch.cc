#include "stop_watch.h"

const uint32_t StopWatch::ONE_BILLION = 1000000000;
const uint32_t StopWatch::ONE_MILLION = 1000000;
const uint32_t StopWatch::ONE_THOUSAND = 1000;

StopWatch::StopWatch() {
   start();
   stop();
}
StopWatch::~StopWatch() {}

void StopWatch::start() {
   set(&_begin);
}
void StopWatch::stop() {
   set(&_end);
}
uint32_t StopWatch::get_seconds() {
   return get() / ONE_BILLION;
}
uint32_t StopWatch::get_milli() {
   return get() / ONE_MILLION;
}
uint64_t StopWatch::get_micro() {
   return get() / ONE_THOUSAND;
}
uint64_t StopWatch::get_nano() {
   return get();
}

uint64_t StopWatch::get() {
   uint64_t result = 0;

   if (_end.tv_nsec < _begin.tv_nsec) {
      result += (_end.tv_sec - _begin.tv_sec - 1) * ONE_BILLION;
      result += (_end.tv_nsec + ONE_BILLION) - _begin.tv_nsec;
   } else {
      result += (_end.tv_sec - _begin.tv_sec) * ONE_BILLION;
      result += _end.tv_nsec - _begin.tv_nsec;
   }

   return result;
}
void StopWatch::set(struct timespec* container) {
   clock_gettime(SW_CLOCK, container);
}
