#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;

  if ((fd = open("/var/log/app.log", O_RDWR | O_APPEND | O_CREAT, 0600)) < 0) {
    close(fd); // pointless on purpose
    return -1;
  }

  if (geteuid() != getuid())
    seteuid(getuid());

  write(1, "Hello", 6);

  system("/bin/bash"); // fd leak here

  close(fd);
  return 0;
}
