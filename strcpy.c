#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char buf[16] = "";
  char *in = argv[1], *out = buf;

  if (argc > 1) {
    strcpy(out, in);
  }
  (void)printf(buf);

  return 0;
}
