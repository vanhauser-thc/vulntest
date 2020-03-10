#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  FILE *f;
  char line[64], *data;
  int size;

  if (argc < 3)
    return -1;

  if ((f = fopen(argv[1], "r")) == NULL)
    return -1;

  if (fgets(line, sizeof(line), f) == NULL)
    return -1;

  size = atoi(line); // untrusted

  if ((data = malloc(size)) == NULL)
    return -1;

  fread(data, 1, 1024, f); // bof
  data[1023] = 0;

  printf("Data: %s\n", data);

  fclose(f);
  return 0;
}
