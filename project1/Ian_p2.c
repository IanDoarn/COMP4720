#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
pid_t pid;

  pid = fork();

  if (pid < 0)
  {
    fprintf(stderr, "fork failed.\n");
    return 1;
  }
  else if(pid == 0)
  {
    //
    while(pid == 0)
    {
      printf("[Parent process] PID: %d\n", getppid());
      printf("[Child process] PID: %d\n", getpid());
    }
  }
  else
  {
    wait(NULL);
    printf("Child complete.\n");
  }
  return 0;
}
