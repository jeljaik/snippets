#include "MyClass.h"

MyClass::MyClass(int initValue) {
  std::cout << "initValue is: " << initValue << std::endl;
  this->_value = initValue;
}

MyClass::~MyClass() {

}

void MyClass::setValue(int& value) {
  // Sets value only if it's between 0 and 10, not including the borders.
  if (value < 10 && value > 0) {
    this->_value = value;
    std::cout << "Good. Value between bounds." << std::endl;
  } else {
    // std::cout << "Error in: " << __FULL_METHOD_NAME__ << " - Value out of bounds" << std::endl;
    OCRA_WARNING(" - Value out of bounds");
    OCRA_ERROR(" - Value out of bounds");
  }
}

void MyClass::getValue(int& value) {
  value = this->_value;
}
