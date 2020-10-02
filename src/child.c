#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int main() {
    while (1) {
        float nums[3];
        for (int i = 0; i < 3; i++) {
            char c;
            char buff[50];
            for (int k = 0; k < 50; k++) {
                buff[i] = '\0';
            }
            int count = 0;
            for (int j = 0;; j++) {
                if (!read(STDIN_FILENO, &c, sizeof(c))) {
                    return 0;
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
            } else {
                i--;
            }
        }
        float result = nums[0] + nums[1] + nums[2];
        write(STDOUT_FILENO, &result, sizeof(result));
    }
}
