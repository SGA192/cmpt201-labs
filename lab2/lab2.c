#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  size_t n = 1024;
  FILE *stream;
  char *buffer = (char *)(malloc(sizeof(char) * n));
  char *args[20];

  if (buffer == NULL) {
    perror("Buffer allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  ssize_t sizeRead;
  char *token;
  char *savePtr;
  pid_t pid;
  int status;

  stream = fopen("/dev/stdin", "r");
  if (stream == NULL) {
    perror("fopen failed.\n");
    exit(EXIT_FAILURE);
  }

  printf("Enter programs to run.\n>");

  while ((sizeRead = getline(&buffer, &n, stream)) != -1) {
    buffer[sizeRead - 1] = '\0';
    args[0] = buffer;
    args[1] = (char *)NULL;
    unsigned int counter = 1;

    pid = fork();

    if (pid == -1) {
      perror("FORK ERROR.\n");
      exit(EXIT_FAILURE);
    }

    if (pid == 0) {
      if (execv(buffer, args) == -1) {
        perror("BAD FILE NAME.\n");
        exit(EXIT_FAILURE);
      }
    } else {
      if (waitpid(pid, &status, 0) == -1) {
        perror("Waitpid Failure.\n");
      }
      printf("Enter programs to run.\n>");
    }
  }
}

/* Was able to reuse a lot of code from lab1 for this :D.  I ended up not
 * needing to tokenize.
 * unless I'm missing something with the tokenization...\
 */
