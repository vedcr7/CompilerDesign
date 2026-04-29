/* demo3.c - A clean program that passes semantic analysis */

int add(int a, int b) {
    return a + b;
}

int multiply(int x, int y) {
    return x * y;
}

int main(void) {
    int num1 = 5;
    int num2 = 10;
    
    int sum = add(num1, num2);
    int product = multiply(num1, num2);
    
    int result = sum + product;
    
    return result;
}
