#ifndef WRAPPER_H
#define WRAPPER_H

#include "Manager.h"
#include "Operator.h"

class Wrapper{
public:
  Wrapper();
  ~Wrapper();

  void useOperator();
  void useManager();  

private:
  Operator m_operator;
  Manager m_manager;
};

#endif // WRAPPER_H