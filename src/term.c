#include <SDL2/SDL.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <termios.h>


#ifdef __linux__
#include <pty.h>
#endif

#ifdef __APPLE__
#include <util.h>
#endif


// int main() {

 //    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
	// printf("SDL initialization failed: %s\n", SDL_GetError());
	// exit(EXIT_FAILURE);
 //    };
	//
 //    SDL_Window *window = SDL_CreateWindow("My Window",
 //        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
 //        640, 480, SDL_WINDOW_SHOWN);
	//
 //    if (!window) {
	// printf("Window creation failed: %s\n", SDL_GetError());
	// return 1;
 //    }
	// 
	//
 //    forkpty(int *, char *, struct termios *, struct winsize *)
	//
	//
	//
	//
	//
	//
 //    SDL_Quit();

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

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

    // Parent process - read from the pseudo-terminal and print the output
    while (1) {
        int nread = read(master_fd, buf, sizeof(buf));

        if (nread <= 0) {
            break;
        }

        FILE *fd = fopen("output", "ab+");


        fprintf(fd, "%s\n", buf);
	fclose(fd);
    }

    // Wait for the child process to exit
    waitpid(pid, &status, 0);


}
