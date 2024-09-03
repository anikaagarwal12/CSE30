/*
 * CSE30 Spring 2024 pa1.c file
 *
 * Instructions:
 *   this program has two problems
 *   (1) using gdb find the one statement that causes the segfault
 *       and comment only it out using a line comment
 *   (2) Variable int a is getting corrupted, fix the one line causing this
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "pa1.h"

void sub(int b[])
{
    int i;
    int *j = 0;

   //*j = 0;

    /*
     * initialize the array to contain 5
     */
    for (i = 0; i < LEN; i++)
        b[i] = 5;
    
    for (i = 0; i < LEN; i++)
        printf("b[%d]: %d\n", i, b[i]);
    printf("j: %p\n", j);
}

int main(void) 
{
    int a = 1;
    int b[LEN];

    sub(b);
    printf("a: %d\n", a);
    return EXIT_SUCCESS;
}
