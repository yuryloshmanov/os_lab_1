#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char *argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork error\n");
        exit(2);
    } else if (pid == 0) {
        FILE *f = NULL;
        if (argc > 1) {
            f = fopen(argv[1], "r");
        } else {
            char file_name[50];
            printf("Enter file name: ");
            scanf("%[^\n]%*c", file_name);
            f = fopen(file_name, "r");
        }
        if (!f) {
            fprintf(stderr, "can't open file\n");
            exit(3);
        }

        dup2(fileno(f), STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        dup2(fd[1], STDERR_FILENO);

        close(fd[0]);
        close(fd[1]);
        fclose(f);

        if (execl("child", "child", (char *) NULL) == -1) {
            fprintf(stderr, "exec error\n");
            exit(4);
        }
    } else {
        close(fd[1]);
        waitpid(pid, (int *)NULL, 0);

        float result;
        while (read(fd[0], &result, sizeof(result))) {
            printf("%f\n", result);
        }
        close(fd[0]);
    }
    return 0;
}
