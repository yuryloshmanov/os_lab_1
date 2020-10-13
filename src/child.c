#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

const int max_count = 100;

int main() {
    while (1) {
        int numbers = 0;
        float nums[max_count];
        for (int i = 0; i < max_count; i++) {
            char c;
            char buff[50];
            for (int k = 0; k < 50; k++) {
                buff[k] = '\0';
            }
            int count = 0;
            for (int j = 0;; j++) {
                if (!read(STDIN_FILENO, &c, sizeof(c))) {
                    return 0;
                }
                if (c == '\n') {
                    break;
                }
                if (isdigit(c) || c == '.') {
                    count++;
                    buff[j] = c;
                } else {
                    break;
                }
            }
            if (count) {
                nums[i] = atof(buff);
                numbers++;
            } else {
                i--;
            }
            if (c == '\n') {
                break;
            }
        }
        float result = 0;
        for (int i = 0; i < numbers; i++) {
            result += nums[i];
        }
        write(STDOUT_FILENO, &result, sizeof(result));
    }
}
