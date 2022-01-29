#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
int main(int argc, char **argv) {
  if (!argv[1]) {
    printf("ERROR: You must provide an integer to sieve to"
           "sieve to\n");
    return 0;
  }
  unsigned int count = atoi(argv[1]);
  printf("seiving to %d\n", count);
  bool *numbers = malloc(sizeof(unsigned int) * count);
  if (!numbers) {
    printf("ERROR: Could not allocate memmory!");
    return -1;
  }
  // initalize array of numbers to sieve
  for (int i = 0; i < count; i++) {
    numbers[i] = true;
  }
  for (int i = 2; i < count; i++) {
    if (numbers[i]) {
      unsigned int factor = i;
      for (int j = factor * 2; j < count; j += factor) {
        numbers[j] = false;
      }
    }
  }
  printf("Done calculating!\n");
  unsigned short numberLen = (int)log10(count) + 1;
  unsigned int outputLen = numberLen * count;
  char *output = malloc(outputLen);
  char *position = output;

  for (int i = 0; i < count; i++) {
    if (numbers[i]) {
      unsigned short char_count = sprintf(position, "%d\n", i);
      position += char_count;
    }
  }
  printf("Done!\n");
  printf(output);
  free(output);
  free(numbers);
  return 0;
}
