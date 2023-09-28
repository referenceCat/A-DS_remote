// Created by Mikhail Buyanov on 22/09/2023.

#include <iostream>

int cstring_to_char_array(char* str, char* result) {
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

void char_array_to_cstring(char* array, int size, char* result) {
    for (int i = 0; i < size; i++) {
        result[i] = array[i];
    }
    result[size] = '\0';
}

int example_function_for_char_array(char* a, int size_a, char* b, int size_b, char* c, int size_c, char* d, int size_d, char* result) {
    char* digits = "0123456789";
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

int main() {
    char input_a[80];
    char input_b[80];
    char input_c[80];
    char input_d[80];

    std::cout<<"A=";
    std::cin>>input_a;
    std::cout<<"B=";
    std::cin>>input_b;
    std::cout<<"C=";
    std::cin>>input_c;
    std::cout<<"D=";
    std::cin>>input_d;

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



    char result_str[11];
    char_array_to_cstring(result, result_size, result_str);
    std::cout<<"E="<<result_str<<"\n";
    return 0;
}