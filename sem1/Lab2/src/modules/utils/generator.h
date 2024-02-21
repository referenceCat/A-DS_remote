//
// generator.h
//
// Author: Kirill Trofimov
// Email: trofkm@gmail.com
// Date: 28.09.23
//

#ifndef A_DS_REMOTE_GENERATOR_H
#define A_DS_REMOTE_GENERATOR_H

#include <ctime>
#include <random>

namespace utils {
    /// Generate random string of given size from set of numbers
    /// @param size - size of string, cannot be zero or greater then 10
    /// @return pointer to generated string
    /// @example generate_char_set(10) -> "1234567890"
    char *generate_char_set(size_t size) {
        bool mask[10];
        char *result = new char[size + 1];

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(25, 63); // define the range

        for (size_t i = 0; i < size; i++) {
            mask[i] = distr(gen) % 2;
        }
        int index = 0;
        for (size_t i = 0; i < size; i++) {
            if (mask[i]) {
                result[index++] = '0' + i;
            }
        }
        result[index] = '\0';
        return result;
    }
}// namespace utils
#endif//A_DS_REMOTE_GENERATOR_H
