#include <stdio.h>
#include <unistd.h>

int main() {
    float a, b, c;
    while (scanf("%f %f %f", &a, &b, &c) != -1) {
        float result = a + b + c;
        write(STDOUT_FILENO, &result, sizeof(result));
    }
    return 0;
}
