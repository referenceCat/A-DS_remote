// Created by Mikhail Buyanov on 22/09/2023.

#include <chrono>
#include <iomanip>
#include <iostream>

#include "utils/generator.h"
#include "utils/utils.h"

int cstring_to_char_array(char *str, char *result) {
    int result_size = 0;
    bool in_result;

    for (int i = 0; str[i]; i++) {
        in_result = false;
        for (int j = 0; j < result_size; j++)
            if (result[j] == str[i]) {
                in_result = true;
                break;
            }
        if (!in_result) {
            result[result_size] = str[i];
            result_size++;
        }
    }

    return result_size;
}

bool search(const char *array, int size, char value) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) return true;
    }
    return false;
}

void char_array_to_cstring(char *array, int size, char *result) {
    for (int i = 0; i < size; i++) {
        result[i] = array[i];
    }
    result[size] = '\0';
}

int example_function_for_char_array(char *a, int size_a, char *b, int size_b, char *c, int size_c, char *d, int size_d, char *result) {
    char *digits = "0123456789";
    int result_size = 0;
    for (int i = 0; i < 10; i++) {
        if ((search(a, size_a, digits[i]) && !(search(b, size_b, digits[i]) || search(c, size_c, digits[i]))) || search(d, size_d, digits[i])) {
            *result = digits[i];
            result++;
            result_size++;
        }
    }
    return result_size;
}


void business_logic(char *input_a, char *input_b, char *input_c, char *input_d, char *output_e) {
    char a[10];
    char b[10];
    char c[10];
    char d[10];

    int a_size;
    int b_size;
    int c_size;
    int d_size;

    a_size = cstring_to_char_array(input_a, a);
    b_size = cstring_to_char_array(input_b, b);
    c_size = cstring_to_char_array(input_c, c);
    d_size = cstring_to_char_array(input_d, d);

    char result[10];
    int result_size;


    result_size = example_function_for_char_array(a, a_size, b, b_size, c, c_size, d, d_size, result);

    char_array_to_cstring(result, result_size, output_e);
}


void run_tests(int count) {
    double average_time = 0;
    for (int i = 0; i < count; i++) {
        auto input_a = utils::generate_char_set(10);
        auto input_b = utils::generate_char_set(10);
        auto input_c = utils::generate_char_set(10);
        auto input_d = utils::generate_char_set(5);

        char result_str[80] = {0};
        auto elapsed = utils::measure_execution_time(business_logic, input_a, input_b, input_c, input_d, result_str);
        std::cout << "----------------------\n";
        std::cout << "Case " << i << ":\n";
        std::cout << "A=" << input_a << "\n";
        std::cout << "B=" << input_b << "\n";
        std::cout << "C=" << input_c << "\n";
        std::cout << "D=" << input_d << "\n";
        std::cout << "E=" << result_str << "\n";
        std::cout << "Execution time: " << std::setprecision(10) << elapsed << "ms" << std::endl;
        delete[] input_a;
        delete[] input_b;
        delete[] input_c;
        delete[] input_d;
        average_time += elapsed / count;
    }
    std::cout << "======================\n";
    std::cout << "Average time: " << std::setprecision(10) << average_time << "ms" << std::endl;
}

void user_input() {
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
}

int main() {

    std::cout << "Select mode: 1 - user input, 2 - random: ";

    int mode = 1;
    std::cin >> mode;
    switch (mode) {
        case 1:
            user_input();
            break;
        case 2:
            std::cout << "Enter number of tests: ";
            int count;
            std::cin >> count;
            std::cout << "Running tests..." << std::endl;
            run_tests(count);
            break;
    }

    return 0;
}