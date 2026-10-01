#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define HISTORY_SIZE 5

int main() {
  pid_t pid = fork();
  if (pid) {
    int wstatus = 0;
    if (waitpid(pid, &wstatus, 0) == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    if (WIFEXITED(wstatus))
      return WEXITSTATUS(wstatus);
    return EXIT_FAILURE;
  }
  setvbuf(stdout, NULL, _IONBF, 0);
  char *history[HISTORY_SIZE] = {NULL};
  int next = 0;
  int count = 0;
  char *line = NULL;
  size_t cap = 0;
  ssize_t len;
  printf("Enter input: ");
  while ((len = getline(&line, &cap, stdin)) != -1) {
    if (len > 0 && line[len - 1] == '\n')
      line[len - 1] = '\0';
    char *copy = strdup(line);
    if (copy == NULL) {
      perror("strdup");
      break;
    }
    free(history[next]);
    history[next] = copy;
    next = (next + 1) % HISTORY_SIZE;
    if (count < HISTORY_SIZE)
      count++;
    if (strcmp(line, "print") == 0) {
      int start = (count < HISTORY_SIZE) ? 0 : next;
      for (int i = 0; i < count; i++)
        puts(history[(start + i) % HISTORY_SIZE]);
    }
    printf("Enter input: ");
  }
  free(line);
  for (int i = 0; i < HISTORY_SIZE; i++)
    free(history[i]);
  return EXIT_SUCCESS;
}
