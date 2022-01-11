//
//  basic_function.c
//  Library-C
//
//  Created by 黃佳俊 on 2022/1/11.
//

#include "basic_function.h"
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


/**
 * 加入 const 修飾字，可以防止程式修改這個參數的值。
 * 對基本型別沒有意義，會用於指標型別。
 */
bool stack_is_empty(const stack_t *self)
{
    assert(self);
    return !(self->ss_size) ? true : false;
}

/**
 * 不定參數：
 * 1. 本身無法預先取得參數數量的資訊，要由外部傳入；另外，也要補足參數型別的資訊
 * 2. 不定參數函式需要 stdarg.h 函式庫的協助
 */
double max(size_t sz, double value, ...)
{
    // 1. va_list：宣告不定參數的變數。
    va_list args;
    
    // 2. va_start：取得第一項參數，前者為剛宣告的變數，後者為可變參數的變數名稱。
    va_start(args, value);
    
    double max = value;
    double temp;
    for (size_t i = 1; i < sz; i++) {
        // 3. va_arg：取得之後的參數，前者為剛宣告的變數，後者為載入的參數型態。
        temp = va_arg(args, double);
        
        max = max > temp ? max : temp;
    }
    
    // 4. va_end：清理宣告的不定參數變數
    va_end(args);
    
    return max;
}

/*
 * 遞迴函數
 */
u_long fib(u_long n)
{
    /* `n` starts from 1. */
    assert(n > 0);
    
    if (n == 1)
        return 0;
    
    if (n == 2)
        return 1;
    
    return fib(n - 1) + fib(n - 2);
}

/**
 * 傳值 vs 傳址
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * 回傳指標：字串連接為例
 */
char * my_strcat(char a[], char b[]) {
    char *s = calloc((strlen(a) + strlen(b) + 1), sizeof(char));
    
    strcat(s, a);
    strcat(s, b);

    return s;
}


/**
 * 函式指標
 */
int compute(comp_fn fn, int a, int b)
{
    return fn(a, b);
}
int add(int a, int b)
{
    return a + b;
}
int sub(int a, int b)
{
    return a - b;
}
