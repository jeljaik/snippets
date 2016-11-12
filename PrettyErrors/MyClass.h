#ifndef _MYCLASS_
#define _MYCLASS_

#include <iostream>
#include "errorsHelper.h"
// Pretty errors macro

class MyClass {
public:
  MyClass(int initValue);
  ~MyClass();

  void setValue(int& value);
  void getValue(int& value);
private:
  int _value;
};


#endif //ENF OF MYCLASS.H
