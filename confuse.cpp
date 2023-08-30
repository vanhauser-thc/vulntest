#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Base {};

class Exec : public Base {
public:
  virtual void exec(const char *prg) { system(prg); }
};

class Greeter : public Base {
public:
  virtual void sayHi(const char *str) { std::cout << str << std::endl; }
};

int main(int argc, char *argv[]) {
  Base *b1 = new Greeter();
  Base *b2 = new Exec();
  Greeter *g;
  if (argc != 3) {
    printf("Syntax: %s 1|2 greeting\n", argv[0]);
    exit(-1);
  }
  if (argv[1][0] == '1')
    g = static_cast<Greeter *>(b1);
  else if (argv[1][0] == '2')
    g = static_cast<Greeter *>(b2);
  else {
    printf("wrong mode\n");
    exit(-1);
  }
  g->sayHi(argv[2]);
  return 0;
}
