#pragma once

#include <chrono>
#include <cstdint>

class StopWatch {
public:
  StopWatch() noexcept;
  void Start() noexcept;
  void Stop() noexcept;
  void Reset() noexcept;
  uint32_t GetMicroseconds() const noexcept;

private:
  std::chrono::system_clock::time_point start;
  std::chrono::microseconds elapsedTime;
};
