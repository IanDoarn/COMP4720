#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char* _strdup(char* str) {
	/* I don't know what this does but I need it */
	char* other = malloc(strlen(str) + 1);
	if(other != NULL)
		strcpy(other, str);
	return other;
}

int execute(char* argv[]) {
	/* Create a child and execute a process using execvp */
	pid_t pid;
	pid = fork();

	if(pid < 0) {
		fprintf(stderr, "Fork Failed.\n");
		return 1;
	}
	// Child process
	else if(pid == 0) {
		// I shall call him Kevin
		execvp(argv[0], argv);
	}
	else {
		wait(NULL);
		// Kevin is now dead
	}
	return 0;
}

int main(void) {
	int r = 0;

	while(1) {
		char inbuffer[50];
		char* argv[100];
		int argc = 0;
		printf(">");
		fgets(inbuffer, 50, stdin);
		// printf("%d", strcmp(inbuffer, "exit"));
		if(strcmp(inbuffer, "exit") == 10) {
			return r;
		}
		else {
			// parse user input
			// printf(inbuffer);
			inbuffer[strlen(inbuffer) - 1] = '\0';

			char* str = strtok(inbuffer, " ");
			while(str != NULL) {
				argv[argc++] = _strdup(str);
				str = strtok(NULL, " ");
			}
			argv[argc] = NULL;

			// execute command
			r = execute(argv);
		}
	}
	return r;
}
