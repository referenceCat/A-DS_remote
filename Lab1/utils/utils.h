//
// utils.h
//
// Author: Kirill Trofimov
// Email: trofkm@gmail.com
// Date: 28.09.23
//

#ifndef A_DS_REMOTE_UTILS_H
#define A_DS_REMOTE_UTILS_H
namespace utils {
    /// measure execution time in ms
    /// @param func function to measure
    /// @param args arguments for function
    /// @return execution time in ms
    template<typename Func, typename... Args>
    double measure_execution_time(Func &&func, Args &&...args) {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1e6;
    }
}// namespace utils
#endif//A_DS_REMOTE_UTILS_H
