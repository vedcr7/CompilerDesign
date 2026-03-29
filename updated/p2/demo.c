/*
 * demo.c — Demonstration input for the Compiler Project
 * This file deliberately contains common C programming
 * mistakes to showcase the semantic analyser's detection.
 *
 * Problems planted:
 *   1. Unused variable (score)
 *   2. Use before initialisation (result)
 *   3. Array out-of-bounds access (arr[10] in size-5 array)
 *   4. Wrong argument count to a function call
 *   5. Division by zero
 *   6. Float assigned to int (data loss warning)
 *   7. Missing return in non-void function
 *   8. Type mismatch (string to int)
 */

int add(int x, int y)
{
    return x + y;
}

int multiply(int a, int b)
{
    return a * b;
}

int compute(int n)
{
    int result;
    int score;

    int arr[5];

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr[10] = 99;

    result = add(n, 5);

    int bad = add(1, 2, 3);

    int total = result + arr[0];

    int zero = 0;
    int danger = total / 0;

    float pi = 3.14;
    int approx = pi;

    return total;
}

void greet(int times)
{
    int i;
    for (i = 0; i < times; i++) {
        int msg = "Hello";
    }
}

int main(void)
{
    int a = 10;
    int b = 20;
    int c;

    c = add(a, b);

    if (c > 15) {
        c = multiply(a, b);
    } else {
        c = a - b;
    }

    while (a > 0) {
        a = a - 1;
    }

    int result = compute(c);

    return result;
}
