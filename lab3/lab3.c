#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  size_t BUFF_SIZE = 1024;
  FILE *stream;
  char *storedInputs[5];
  ssize_t sizeRead;
  uint8_t index = 0;

  stream = fopen("/dev/stdin", "r");
  if (!stream) {
    perror("Stream file open failed.\n");
    exit(EXIT_FAILURE);
  }

  for (uint8_t i = 0; i < 5; i++) {
    storedInputs[i] = (char *)malloc(sizeof(char) * BUFF_SIZE);
    if (!storedInputs[i]) {
      perror("Malloc failed.\n");
      exit(EXIT_FAILURE);
    }
  }
  printf("Enter input: ");
  while ((sizeRead = getline(&storedInputs[index], &BUFF_SIZE, stream)) != -1) {
    if (strncmp(storedInputs[index], "print\n", BUFF_SIZE) == 0) {
      for (uint8_t j = 0; j <= index; j++) {
        printf("%s", storedInputs[j]);
      }
      for (uint8_t k = 0; k < 5; k++) {
        storedInputs[k][0] = '\0';
      }
      index = 0;
    }
    if (index >= 4) {
      for (uint8_t i = 0; i < 4; i++) {
        memcpy(storedInputs[i], storedInputs[i + 1], BUFF_SIZE);
      }
    } else {
      index++;
    }
    printf("Enter input: ");
  }
  for (uint8_t i = 0; i < 5; i++) {
    free(storedInputs[i]);
  }
  fclose(stream);

  return 0;
}

/*
 * I feel like a more elegent way to implement this would be with a rotating
 * queue of some sort which would save on the overhead from memcpy (O(n) I
 * think?), wheras a rotating queue can just continue to loop the index between
 * 0-4 inclusive and have two index "pointers" to keep track of the index
 * tail/head and print accordingly there. But it's 6am and I was up all night
 * like a degenerate so I implemented the straightfoward "naive" version lol.
 * Was able to copy over a lot of my lab2 code in terms of getline and fopen.
 * Also, I don't think the free at the end triggers if we use ctrl-c to exit,
 * but wtv. I realized I forgot to free my pointers from lab2 lol, whoops.
 */
