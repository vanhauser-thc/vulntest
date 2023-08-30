#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;

  if ((fd = open("/var/log/app.log", O_RDWR | O_APPEND | O_CREAT, 0600)) < 0) {
    close(fd);
    return -1;
  }

  if (geteuid() != getuid()) {
    setegid(getgid());
    seteuid(getuid());
  }

  write(1, "Hello\n", 6);

  system("/bin/bash");

  close(fd);
  return 0;
}
