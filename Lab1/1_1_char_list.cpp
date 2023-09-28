// Created by Mikhail Buyanov on 22/09/2023.

#include <iostream>

struct ListNode {
    char digit;
    ListNode* next = NULL;
};

struct ListHead {
    int size = 0;
    ListNode* node;
};

void cstring_to_char_list(char* str, ListHead* result) {
    bool in_result;
    ListNode* node;
    for (int i = 0; str[i]; i++) {
        in_result = false;
        node = result->node;
        for (int j = 0; j < result->size; j++)
            if (node->digit == str[i]) {
                in_result = true;
                break;
            }
        node = node ->next;
        if (!in_result) {
            for (node = result->node; node->next!=NULL; node = node->next);
            node->digit = str[i];
        }
    }
}

bool search(ListHead* list, char value) {
    ListNode* node;
    for (node = list->node; node->next!=NULL; node = node->next) {
        if (node->digit == value) return true;
    }
    return node->digit == value;
}

void char_list_to_cstring(ListHead* list, char* result) {
    ListNode* node = list->node;
    for (int i = 0; i < list->size; i++) {
        result[i] = node->digit;
        node = node->next;
    }
    result[list->size] = '\0';
}

int example_function_for_char_array(ListHead* a, ListHead* b, ListHead* c, ListHead* d, ListHead* result) {
    char* digits = "0123456789";
    int result_size = 0;
    ListNode* node = result->node;
    for (int i = 0; i < 10; i++) {
        if ((search(a, digits[i]) && !(search(b, digits[i]) || search(c, digits[i]))) || search(d, digits[i])) {
            node->digit = digits[i];
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