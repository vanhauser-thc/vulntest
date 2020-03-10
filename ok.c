#include <stdio.h>
int main(int argc, char *argv[]) {
  // BUG: this has no bugs
  if (argc > 1) {
    (void)printf("%s\n", argv[1]);
  }
  return 0;
}
