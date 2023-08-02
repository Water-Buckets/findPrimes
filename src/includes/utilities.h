#ifndef FINDPRIMES_MULTITHREAD_UTILITIES_H
#define FINDPRIMES_MULTITHREAD_UTILITIES_H
#include <chrono>
#include <iostream>
#include <string>
#include <utility>

// timer for the function executed
// note that the function must have return value
template <typename T, typename... Args>
inline auto timer(T fMethod, std::string s, Args... args) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  auto start = std::chrono::steady_clock::now();
  auto results = fMethod(std::forward<Args>(args)...);
  auto end = std::chrono::steady_clock::now();
  long long duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << s << double(duration) / 1000000000 << " seconds." << std::endl;
  return std::make_pair(results, duration);
}

#endif