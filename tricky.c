#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buf[128];
  int user_len = atoi(argv[2]);
  int buf_size = sizeof(buf);

  if (user_len > buf_size) {
    printf("Attempted Overflow Detected\n");
    return -1;
  }

  memcpy(buf, argv[1], user_len);
  if (buf[0] != 0)
    return 0;
  else
    return -1;
}
