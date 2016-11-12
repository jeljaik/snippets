#include "MyClass.h"

int main(int argc, char *argv[]) {

  MyClass myClassObject(1);
  int val = 5;
  myClassObject.setValue(val);
  int val2 = -1;
  myClassObject.setValue(val2);

  return 0;
}
