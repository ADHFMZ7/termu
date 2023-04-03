#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#ifdef __linux__
#include <pty.h>
#endif

#ifdef __APPLE__
#include <util.h>
#endif


int main() {
    int status;
    int master_fd;
    pid_t pid;
    char *args[] = {"/bin/bash", NULL};
    char buf[256];

    // Fork a child process and connect it to the pseudo-terminal as secondary
    if ((pid = forkpty(&master_fd, NULL, NULL, NULL)) == -1) {
        perror("forkpty");
        exit(1);
    }

    if (pid == 0) {

        // Child process - execute the shell
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    }
    
    // Set the master_fd to non-blocking mode
    int flags = fcntl(master_fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(master_fd, F_SETFL, flags);

    int nread;
    FILE *fd = fopen("output", "ab+");
    // Send some commands to the shell and print the output
    // for (int i = 0; i < 10; i++) {
    while (1) {

        // read the output from the shell
        nread = read(master_fd, buf, sizeof(buf) - 1);
        buf[nread] = '\0';  // null-terminate the buffer
        fprintf(fd, "%s\n", buf);
        printf("OUTPUT: %s", buf);
        fflush(stdout);
        //fflush(fd);

        printf("Input: ");
        fflush(stdout);
        nread = scanf("%s\n", buf);

        if (strcmp(buf, "exit") == 0) {
            break;
        }

        // send the input to the shell
        write(master_fd, buf, nread + 1);

        // read the output from the shell
        nread = read(master_fd, buf, sizeof(buf) - 1);
        buf[nread] = '\0';  // null-terminate the buffer
        fprintf(fd, "%s\n", buf);
        fflush(fd);
        printf("second output: %s\n", buf);
        fflush(stdout);

        usleep(100000);  // sleep for 100 milliseconds
    }

    fclose(fd);

    // Wait for the child process to exit
    waitpid(pid, &status, 0);
}
