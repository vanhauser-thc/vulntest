/*
 * @description Double Free
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

namespace CWE415_Double_Free__no_copy_const_01 {

class BadClass {
public:
  BadClass(const char *data) {
    if (data) {
      this->data = new char[strlen(data) + 1];
      strcpy(this->data, data);
    } else {
      this->data = new char[1];
      *(this->data) = '\0';
    }
  }

  ~BadClass() { delete[] data; }

  void printData() { printf("%s\n", data); }

  BadClass &operator=(const BadClass &badClassObject) {
    if (&badClassObject != this) {
      this->data = new char[strlen(badClassObject.data) + 1];
      strcpy(this->data, badClassObject.data);
    }
    return *this;
  }

private:
  char *data;
};

void bad() {
  BadClass badClassObject("One");

  /* FLAW: There is no copy constructor in the class - this will cause a double
   * free in the destructor */
  BadClass badClassObjectCopy(badClassObject);

  badClassObjectCopy.printData();
}

} // namespace CWE415_Double_Free__no_copy_const_01

/* Below is the main(). It is only used when building this testcase on
 * its own for testing or for building a binary to use in testing binary
 * analysis tools. It is not used when compiling all the testcases as one
 * application, which is how source code analysis tools are tested.
 */

using namespace CWE415_Double_Free__no_copy_const_01; /* so that we can use good
                                                         and bad easily */

int main(int argc, char *argv[]) {
  /* seed randomness */
  srand((unsigned)time(NULL));
  printf("Calling bad()...");
  bad();
  printf("Finished bad()");
  return 0;
}
