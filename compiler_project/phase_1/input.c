int a;
int b;

a = 10;
b = 20;

if (a < b) {
    a = a + b;
} else {
    a = a - b;
}

while (a > 0) {
    a = a - 1;
}

for (a = 0; a < 5; a = a + 1) {
    b = b + a;
}

return a;