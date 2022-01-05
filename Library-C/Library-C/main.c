//
//  main.c
//  Library-C
//
//  Created by 黃佳俊 on 2022/1/5.
//

#include <stdio.h>
#include "basic_data.h"

void show_variable_function(void);

int main(int argc, const char * argv[]) {
    // insert code here...
    show_variable_function();
    
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
