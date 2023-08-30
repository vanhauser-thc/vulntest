#include <stdio.h>

int main(int argc, char *argv[]) {
  char buf[16] = "";
  char *in = argv[1], *out = buf;

  if (argc > 1) {
    while (*in != 0) {
      *out++ = *in++;
    }
    *out = 0;
  }
  (void)printf(buf);

  return 0;
}
