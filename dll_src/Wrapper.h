#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef MYLIBRARY_EXPORT
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

class Operator;
class Manager;

class LIBRARY_API Wrapper{
public:
  Wrapper();
  ~Wrapper();

  void useOperator();
  void useManager();  

private:
  Operator* m_operator;
  Manager* m_manager;
};

#endif // WRAPPER_H