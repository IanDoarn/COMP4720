#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	pid_t pid = fork();

	// Parent process
	if(pid > 0)
		// Sleep for 60 seconds
		sleep(60);
	// Child process
	else
		// Zombie is created as soon as child exits
		exit(0);

	return 0;
}
