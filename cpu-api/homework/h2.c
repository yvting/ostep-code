#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  int fd = open ("./tst", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
  if (fd < 0) {
    fprintf(stderr, "failed to open file");
    exit(1);
  }
    
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child
    char * str = " Child ";
    write(fd, str, strlen(str));
    printf("Child (pid: %d)\n", (int)getpid());
    close(fd);
  } else {
    // parent
    char * str = " Parent ";
    write(fd, str, strlen(str));
    int wc = wait(NULL);
    printf("Parent (pid: %d) (wc: %d)\n", 
           (int)getpid(), wc);
    close(fd);
  }
  return 0;
}
