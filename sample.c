/*
 * sample.c  —  test input for Phase 1 and Phase 2
 * Covers: declarations, assignments, if/else, while, for,
 *         do-while, functions, return, arithmetic, relational,
 *         logical operators, strings, chars, floats, casts.
 */

#include <stdio.h>

/* global variable */
int counter = 0;

/* ── helper function ─────────────────────────────────────── */
int add(int a, int b)
{
    return a + b;
}

/* ── main function ───────────────────────────────────────── */
int main(void)
{
    /* variable declarations */
    int   x = 10;
    int   y = 5;
    float pi = 3.14;
    char  ch = 'A';
    int   result;

    // arithmetic
    result = add(x, y);
    result = x * 2 + y - 1;

    /* if-else */
    if (x > y) {
        result = x - y;
    } else {
        result = y - x;
    }

    /* while loop */
    while (counter < 5) {
        counter++;
    }

    /* for loop */
    int i;
    for (i = 0; i < 10; i++) {
        result += i;
    }

    /* do-while */
    do {
        x--;
    } while (x > 0);

    /* nested if */
    if (result > 0 && pi < 4.0) {
        result = (int)pi + 1;
    } else if (result == 0) {
        result = -1;
    }

    /* string literal */
    char *msg = "Hello, Compiler!";

    /* ternary operator */
    int max = (x > y) ? x : y;

    /* bitwise */
    result = x & 0xFF;
    result = result | 0x01;
    result = result << 2;

    /* compound assignment */
    result += 5;
    result *= 2;

    return result;
}
