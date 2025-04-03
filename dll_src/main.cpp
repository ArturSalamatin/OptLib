#include <iostream>
#include "Wrapper.h"

int main(){
  Wrapper* instance = new Wrapper();
  instance->useOperator();
  instance->useManager();

  delete instance;

  return 0;
}