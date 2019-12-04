#include "stopwatch.hpp"

StopWatch::StopWatch() noexcept
  : start()
  , elapsedTime(std::chrono::milliseconds(0)) {}

void StopWatch::Start() noexcept {
  start = std::chrono::system_clock::now();
}

void StopWatch::Stop() noexcept {
  using namespace std::chrono;
  elapsedTime += duration_cast<milliseconds>(system_clock::now() - start);
}

void StopWatch::Reset() noexcept {
  using namespace std::chrono;
  elapsedTime = milliseconds(0);
}

uint32_t StopWatch::GetMilliseconds() const noexcept {
  using namespace std::chrono;
  return static_cast<uint32_t>(elapsedTime.count());
}
