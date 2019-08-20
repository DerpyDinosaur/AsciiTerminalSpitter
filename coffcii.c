#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <time.h>

#define RED 	"\x1b[31m"
#define GREEN 	"\x1b[32m"
#define RESET 	"\x1b[0m"

#define clearScreen() printf("\033[H\033[J")

void signalHandler(int sig){
	// Re-enable cursor
	printf("\e[?25h");
	exit(0);
}

int main(int argc, char const *argv[]){
	// Signal handler
	signal(SIGINT, signalHandler);

	// Get width of terminal
	struct winsize w;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1) {
    	fprintf(stderr, "Cannot find STDIN info: %s\n", strerror(errno));
    	exit(1);
	}
	int width = w.ws_col;

	bool rainbowBlast = false;
	char line[100];

	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 200000000L;

	// Blocked Unbuffered
	setvbuf(stdout, NULL, _IOFBF, 0);

	// Blank screen ready for printing
	clearScreen();

	// Remove cursor
	printf("\033[?25l");

	// Check argument if true
	if (argc > 1){
		if (strcmp(argv[1], "true") == 0){
			rainbowBlast = true;
		}
	}

	while(true){
		FILE * fp = fopen("ascii.txt", "r");
		// If file cant be read replace title and continue
		if (fp == NULL){
			puts(RED"\t\t*Insert ascii title here*"RESET);
			puts(RED"\tSomething went wrong with the ascii file"RESET);
		}else{
			while(!feof(fp)){
				fgets(line, sizeof(line), fp);
				fflush(stdin);
				int center = (width + strlen(line)) / 2;
				printf("%*s", center, line);
			}
			fclose(fp);
		}
		printf("\033[H");

		// If rainbowBlast == false then sleep
		if (!rainbowBlast){
			if (nanosleep(&tim, &tim2) > 0){
				printf("Nanosleep failed!");
				return -1;
			}
		}
	}
	return 0;
}