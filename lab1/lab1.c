#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Enter your text: ");

  char *buff = NULL;
  size_t size = 0;

  if (getline(&buff, &size, stdin) != -1L) {
    char *input_str = buff;
    char *delim = " \t\n\r";
    char *token = NULL;
    char *saveptr = NULL;

    while ((token = strtok_r(input_str, delim, &saveptr))) {
      printf("Token: %s\n", token);
      input_str = NULL;
    }
  } else {
    printf("Getline has been failed.\n");
  }
  free(buff);
}
