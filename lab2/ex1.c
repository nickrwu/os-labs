#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t r;
  switch (fork()) {
    case  -1:
      perror("fork");
      exit(1);
    case 0:
      write(STDOUT_FILENO, "a", 1);
      exit(0);
    default:
      write(STDOUT_FILENO, "b", 1);
      switch (r = fork()) {
        case  -1:
          perror("fork");
          exit(1);
        case 0:
          write(STDOUT_FILENO, "c", 1);
          exit(0);
        default:
          waitpid(r, NULL, 0);
              printf("\n");
          write(STDOUT_FILENO, "d", 1);
          exit(0);
    }
  }
}

