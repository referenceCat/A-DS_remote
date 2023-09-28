#include <chrono>
#include <iomanip>
#include <iostream>

#include "utils/utils.h"

void cstring_to_byte_array(char *set, bool *result) {
    for (int i = 0; i < 10; i++) {
        result[i] = false;
    }

    for (int j = 0; set[j]; j++) {
        result[set[j] - '0'] = true;
    }
}

int byte_array_to_cstring(bool *array, char *result) {
    char digits[] = "0123456789";
    int size = 0;
    for (int i = 0; i < 10; i++) {
        if (array[i]) {
            *result = digits[i];
            result++;
            size++;
        }
    }
    *result = 0;
    return size;
}

void example_function(bool *a, bool *b, bool *c, bool *d, bool *result) {
    for (int i = 0; i < 10; i++) {
        result[i] = (a[i] && !(b[i] || c[i])) || d[i];
    }
}

void business_logic(char *input_a, char *input_b, char *input_c, char *input_d, char *output_str) {
    bool a[10];
    bool b[10];
    bool c[10];
    bool d[10];

    cstring_to_byte_array(input_a, a);
    cstring_to_byte_array(input_b, b);
    cstring_to_byte_array(input_c, c);
    cstring_to_byte_array(input_d, d);

    bool result[10];

    example_function(a, b, c, d, result);

    byte_array_to_cstring(result, output_str);
}

int main() {
    char input_a[80];
    char input_b[80];
    char input_c[80];
    char input_d[80];

    std::cout << "A=";
    std::cin >> input_a;
    std::cout << "B=";
    std::cin >> input_b;
    std::cout << "C=";
    std::cin >> input_c;
    std::cout << "D=";
    std::cin >> input_d;

    char result_str[80];
    auto elapsed = utils::measure_execution_time(business_logic, input_a, input_b, input_c, input_d, result_str);
    std::cout << "E=" << result_str << "\n";
    std::cout << "Execution time: " << std::setprecision(10) << elapsed << "ms\n";
    return 0;
}
