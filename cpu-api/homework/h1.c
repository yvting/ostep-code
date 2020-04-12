#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child
    x = x - 1;
    printf("Child (pid: %d): variable x is %d\n", (int)getpid(), x);
  } else {
    // parent
    x = x + 1;
    int wc = wait(NULL);
    printf("Parent (pid: %d) (wc: %d): variable x is %d\n", 
           (int)getpid(), wc, x);
  }
  return 0;
}
