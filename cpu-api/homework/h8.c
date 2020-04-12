/* Pipe */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  int pipefd[2];
  if (pipe(pipefd) != 0) {
    fprintf(stderr, "creation of pipe failed\n");
    exit(1);
  }
   
  // Create read end process
  int rc1 = fork();
  if (rc1 < 0) {
    fprintf(stderr, "fork of the reading process failed\n");
    exit(1);
  } else if (rc1 == 0) {
    // reading process
    close(pipefd[1]); // close write desc
    char i;
    read(pipefd[0], &i, 1);
    printf("(pid: %d): Read the character %c\n", (int)getpid(), i);
    close(pipefd[0]);
  } else {
    // parent
    int rc2 = fork();
    if (rc2 < 0) {
      fprintf(stderr, "fork of the writing process failed\n");
      exit(1);
    } else if (rc2 == 0) {
      // writing process
      close(pipefd[0]); // close read desc
      char i = 'P';
      write(pipefd[1], &i, 1);
      printf("(pid: %d): Write the character %c\n", (int)getpid(), i);
      close(pipefd[1]);
    } else {
      // parent
      // Close the pipe file desc
      close (pipefd[0]);
      close (pipefd[1]);
      // Wait for children
      int wc1 = waitpid(rc1, NULL, 0);
      int wc2 = waitpid(rc2, NULL, 0);
      // Print info before exit
      printf("Parent (pid: %d) (Read: %d) (Write: %d)\n", 
             (int)getpid(), wc1, wc2);
      
    }
  }
    
  return 0;
}
