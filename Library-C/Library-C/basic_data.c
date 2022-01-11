//
//  basic_data.c
//  Library-C
//
//  Created by 黃佳俊 on 2022/1/5.
//

#include "basic_data.h"
#include <limits.h>
#include <float.h>
#include <complex.h>
#include <assert.h>
#include <string.h>

void show_main_integer_size_function(void) {
    printf("Max of signed char: %d\n", CHAR_MAX);
    printf("Min of signed char: %d\n", CHAR_MIN);

    printf("Max of signed short: %d\n", SHRT_MAX);
    printf("Min of signed short: %d\n", SHRT_MIN);

    printf("Max of signed int: %d\n", INT_MAX);
    printf("Min of signed int: %d\n", INT_MIN);

    printf("Max of signed long: %ld\n", LONG_MAX);
    printf("Min of signed long: %ld\n", LONG_MIN);

    printf("Max of signed long long: %lld\n", LLONG_MAX);
    printf("Min of signed long long: %lld\n", LLONG_MIN);

    printf("\n");  /* Line separator. */

    printf("Max of unsigned char: %u\n", UCHAR_MAX);
    printf("Max of unsigned short: %u\n", USHRT_MAX);
    printf("Max of unsigned int: %u\n", UINT_MAX);
    printf("Max of unsigned long: %lu\n", ULONG_MAX);
    printf("Max of unsigned long long: %llu\n", ULLONG_MAX);
}

void show_main_float_size_function(void) {
    printf("Max of float: %e\n", FLT_MAX);
    printf("Min pos of float: %e\n", FLT_MIN);

    printf("Max of double: %e\n", DBL_MAX);
    printf("Min pos of double: %e\n", DBL_MIN);

    printf("Max of long double: %Le\n", LDBL_MAX);
    printf("Min pos of long double: %Le\n", LDBL_MIN);

    printf("\n");  /* Line separator. */

    printf("Digit of float: %u\n", FLT_DIG);
    printf("Digit of double: %u\n", DBL_DIG);
    printf("Digit of long double: %u\n", LDBL_DIG);
}

void show_complex_numnber_function(void) {
    complex double p = 3 + 4 * I;
    
    assert(creal(p) == 3);
    assert(cimag(p) == 4);
}


void show_string_function(void) {
    char s1[] = "Hello World";
    char s2[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'};
        
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%d\n", strcmp(s1, s2));
}

void show_array_function(void) {
    int arr[] = {1, 2, 3, 4, 5};
    
    printf("array count: %lu", sizeof(arr));
}

void do_string_operation_function(void) {
    char str1[] = "Hello";
    
    // 計算字串長度
    printf("%ld", strlen(str1));
}

struct body_t {
    char name[1024];
    int year;
    float width;
    double height;
};

// 使用者可選擇使用 dl 或 i，但兩者不能共存。
union data_t {
    double dl;
    int i;
};
