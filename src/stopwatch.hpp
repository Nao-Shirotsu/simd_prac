#pragma once
#include <cstdint>
#include <chrono>

class StopWatch {
public:
  StopWatch() noexcept;
  void Start() noexcept;
  void Stop() noexcept;
  void Reset() noexcept;
  uint32_t GetMilliseconds() const noexcept;

private:
  std::chrono::system_clock::time_point start;
  std::chrono::milliseconds elapsedTime;
};
