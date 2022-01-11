//
//  basic_function.h
//  Library-C
//
//  Created by 黃佳俊 on 2022/1/11.
//

#ifndef basic_function_h
#define basic_function_h

#include <stdio.h>

double max(size_t sz, double value, ...);
u_long fib(u_long n);
char * my_strcat(char a[], char b[]);

void swap(int *, int *);

/**
 * 函式指標
 * int compute(comp_fn, int, int);
 * or
 * int compute(int (*)(int, int), int, int);
 */
typedef int(*comp_fn)(int, int);
int compute(comp_fn, int, int);
int add(int a, int b);
int sub(int a, int b);

#endif /* basic_function_h */
