#include <stdio.h>

int main(int argc, char *argv[]) {
  char fmt[] = "%s\n";
  if (argc > 1) {
    (void)printf(fmt, argv[1]);
  }
  return 0;
}
