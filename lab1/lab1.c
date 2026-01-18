#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  size_t n = 1024;
  FILE *stream;
  char *strBuffer = (char *)malloc(sizeof(char) * n);
  if (strBuffer == NULL) {
    perror("String buffer allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  ssize_t sizeRead;
  char *token;
  char *saveptr;

  /*  if (argc != 2) {
      fprintf(stderr, "Insufficient arguements (missing STDIN ?)\n");
      exit(EXIT_FAILURE);
    }
  */
  stream = fopen("/dev/stdin", "r");
  if (stream == NULL) {
    perror("fopen\n");
    exit(EXIT_FAILURE);
  }

  printf("Please enter some text: ");

  while ((sizeRead = getline(&strBuffer, &n, stream)) != -1) {
    token = strtok_r(strBuffer, " ", &saveptr);
    printf("Tokens:\n");
    while (token != NULL) {
      printf("\t%s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
    printf("Please enter some text: ");
  }

  free(strBuffer);
  fclose(stream);

  exit(EXIT_SUCCESS);
}

/* A lot of this code (primarily the getline part) was taken from the man page
 * examples for man getline(3), although I had to alter the absolute path for
 * fopen since the man page example was taking raw command line arguments,
 * wheras this program reads input at runtime.
 */
