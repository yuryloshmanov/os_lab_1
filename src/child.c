#include <stdio.h>
#include <unistd.h>

int main() {
    float a, b;
    scanf("%f %f", &a, &b);
    float c = a + b;
    write(STDOUT_FILENO, &c, sizeof(c));
    return 0;
}
