#include <stdio.h>
#include <stdlib.h>

int compare(int a, int b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}
void main(void)
{
    printf("Comparison result: %d\n", compare(10,20));
}