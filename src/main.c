#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(const int argc, const char *argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        char message[] = "pipe error\n";
        write(STDERR_FILENO, &message, sizeof(message) - 1);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        char message[] = "fork error\n";
        write(STDERR_FILENO, &message, sizeof(message) - 1);
        return 2;
    } else if (pid == 0) {
        int file;
        if (argc > 1) {
            file = open(argv[1], O_RDONLY);
        } else {
            char buff[] = "Enter file name: ";
            char file_name[50];

            write(STDOUT_FILENO, &buff, sizeof(buff) - 1);
            read(STDIN_FILENO, &file_name, sizeof(file_name));
            int i;
            for (i = 0; i < 50; i++) {
                if (file_name[i] == '\n' || file_name[i] == '\0') {
                    break;
                }
            }
            char ff[i + 1];
            for (int j = 0; j < i; j++) {
                ff[j] = file_name[j];
            }
            ff[i] = '\0';
            file = open(ff, O_RDONLY);
        }

        if (file == -1) {
            char message[] = "can't open file\n";
            write(STDERR_FILENO, &message, sizeof(message) - 1);
            return 3;
        }

        dup2(file, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        dup2(fd[1], STDERR_FILENO);

        close(fd[0]);
        close(fd[1]);
        close(file);

        if (execl("child", "child", (char *) NULL) == -1) {
            char message[] = "exec error\n";
            write(STDERR_FILENO, &message, sizeof(message) - 1);
            return 4;
        }
    } else {
        close(fd[1]);
        waitpid(pid, (int *)NULL, 0);

        float result;
        while (read(fd[0], &result, sizeof(result))) {
            char buff[50];
            gcvt(result, 7, buff);
            int i;
            for (i = 0; i < 50; i++) {
                if (buff[i] == '\0') {
                    break;
                }
            }
            buff[i] = '\n';
            write(STDOUT_FILENO, &buff, i + 1);
        }
        close(fd[0]);
    }
    return 0;
}
