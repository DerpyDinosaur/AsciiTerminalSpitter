#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define RED 	"\x1b[31m"
#define GREEN 	"\x1b[32m"
#define RESET 	"\x1b[0m"

#define clearScreen() printf("\033[H\033[J")

int main(int argc, char const *argv[]){
	
	// BUG: CENTER WONT WORK
	// struct winsize w;
	// ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	// int width = w.ws_col;
	int tabCount = 0;
	bool rainbowBlast = false;
	char line[100];


	// Blocked Unbuffered
	setvbuf(stdout, NULL, _IOFBF, 0);

	// Blank screen ready for printing
	printf("\033[H\033[J");
	// Remove cursor
	printf("\033[?25l");

	if(argc > 0){
		tabCount = atoi(argv[1]);
	}

	if (argv[2] != 0){
		if (strcmp(argv[2], "true") == 0){
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
				// BUG: CENTER WONT WORK
				// int center = (width + strlen(line)) / 2;
				// printf("%*s", center, line);

				fgets(line, sizeof(line), fp);
				fflush(stdout);
				for (int i = 0; i < tabCount; ++i){
					printf("\t");
				}
				printf("%s", line);
			}
			fclose(fp);
		}
		printf("\033[H");
		if (!rainbowBlast){
			sleep(1);
		}
	}
	return 0;
}