//
//  main.c
//  Library-C
//
//  Created by 黃佳俊 on 2022/1/5.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "basic_data.h"
#include "basic_function.h"


void show_variable_function(void);
void show_function_function(void);
int show_pointer_function(void);


int main(int argc, const char * argv[]) {
//    show_pointer_function();
    show_function_function();
    
    return 0;
}

void show_variable_function() {
    show_main_integer_size_function();
    
    printf("\n");  /* Line separator. */

    show_main_float_size_function();
    show_complex_numnber_function();
    
    printf("\n");  /* Line separator. */

    show_string_function();
}

void show_function_function() {
    // 不定函數
    assert(max(3, 7.0, 4.0, 6.0) == 7.0);
    assert(max(5, 4.0, 2.0, 1.0, 5.0, 3.0) == 5.0);
    
    // 遞迴函數
    u_long arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21};
    for (size_t i = 0; i < 9; i++)
        assert(fib(i+1) == arr[i]);
    
    // 傳值 vs 傳址
    int a = 3;
    int b = 4;
    fprintf(stderr, "a in main, before swap: %d\n", a);
    fprintf(stderr, "b in main, before swap: %d\n", b);
    swap(&a, &b);
    fprintf(stderr, "a in main, after swap: %d\n", a);
    fprintf(stderr, "b in main, after swap: %d\n", b);
    
    // 回傳指標
    char *s = my_strcat("Hello ", "World");
    printf("%s\n", s);
    free(s);
    
    // 函式指標
    assert(compute(add, 3, 4) == 7);
    assert(compute(sub, 3, 4) == -1);
}

int show_pointer_function() {
    int a = 3;
    int b = 3;

    int *p = &a;
    int *q = &a;
    int *r = &b;

    // 比對指標是否相同
    if (!(p == q)) {
        fprintf(stderr, "Wrong addresses: %p %p\n", p, q);
        goto ERROR;
    }
    if (p == r) {
        fprintf(stderr, "Wrong addresses: %p %p\n", p, r);
        goto ERROR;
    }

    // 比對實際值是否相同
    if (!(*p == *q)) {
        fprintf(stderr, "Wrong values: %d %d\n", *p, *q);
        goto ERROR;
    }
    if (!(*p == *r)) {
        fprintf(stderr, "Wrong values: %d %d\n", *p, *r);
        goto ERROR;
    }

    return 0;

ERROR:
    return 1;
}

