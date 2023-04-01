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

    // Fork a child process and connect it to the pseudo-terminal
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
    for (int i = 0; i < 10; i++) {
        buf[0] = 'l';
        buf[1] = 's';
        buf[2] = '\n';
        buf[3] = '\0';

        // send the input to the shell
        write(master_fd, buf, strlen(buf));

        // read the output from the shell
        while ((nread = read(master_fd, buf, sizeof(buf) - 1)) > 0) {
            buf[nread] = '\0';  // null-terminate the buffer
            fprintf(fd, "%s\n", buf);
            fprintf(stdout, "%s\n", buf);
        }

        if (nread == -1 && errno != EAGAIN) {
            perror("read");
            break;
        }

        usleep(100000);  // sleep for 100 milliseconds
    }

    fclose(fd);

    // Wait for the child process to exit
    waitpid(pid, &status, 0);
}

// #include <SDL2/SDL.h>
// #include <stdlib.h>
// #include <termios.h>
// #include <sys/types.h>
// #include <sys/ioctl.h>
// #include <termios.h>
//
//
//
//
//  int main() {
//
//      if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
// 	printf("SDL initialization failed: %s\n", SDL_GetError());
// 	exit(EXIT_FAILURE);
//      };
//
//      SDL_Window *window = SDL_CreateWindow("My Window",
//          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//          640, 480, SDL_WINDOW_SHOWN);
//
//      if (!window) {
// 	printf("Window creation failed: %s\n", SDL_GetError());
// 	return 1;
//      }
//      //forkpty(int *, char *, struct termios *, struct winsize *)
//      SDL_Quit();
//
//  }
