#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

namespace DF_01 {

class FoobarClass {
public:
  FoobarClass(const char *data) {
    if (data) {
      this->data = new char[strlen(data) + 1];
      strcpy(this->data, data);
    } else {
      this->data = new char[1];
      *(this->data) = '\0';
    }
  }

  ~FoobarClass() { delete[] data; }

  void printData() { printf("%s\n", data); }

  FoobarClass &operator=(const FoobarClass &otherxClassObject) {
    if (&otherxClassObject != this) {
      this->data = new char[strlen(otherxClassObject.data) + 1];
      strcpy(this->data, otherxClassObject.data);
    }
    return *this;
  }

private:
  char *data;
};

void otherx() {
  FoobarClass otherxClassObject("One");

  /* FLAW: There is no copy constructor in the class - this will cause a double
   * free in the destructor */
  FoobarClass otherxClassObjectCopy(otherxClassObject);

  otherxClassObjectCopy.printData();
}

} // namespace DF_01

/* Below is the main(). It is only used when building this testcase on
 * its own for testing or for building a binary to use in testing binary
 * analysis tools. It is not used when compiling all the testcases as one
 * application, which is how source code analysis tools are tested.
 */

using namespace DF_01; /* so that we can use othery
                                                         and otherx easily */

int main(int argc, char *argv[]) {
  /* seed randomness */
  srand((unsigned)time(NULL));
  printf("Calling otherx()...");
  otherx();
  printf("Finished otherx()");
  return 0;
}
