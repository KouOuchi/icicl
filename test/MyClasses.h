#pragma once

#include "icicl.h"

#ifdef USE_ICICL
using namespace icicl;
#endif

namespace myclass
{

class MyClass1
{
public:

  MyClass1(void)
  {
    ICICL_CONSTRUCTOR();
  }

  ~MyClass1(void)
  {
    ICICL_DESTRUCTOR();
  }
};


class MyClass2 : public MyClass1
{
public:

  MyClass2(void) : MyClass1()
  {
    ICICL_CONSTRUCTOR();
  }

  ~MyClass2(void)
  {
    ICICL_DESTRUCTOR();
  }
};

template <typename T>
struct MyClass3
{
  MyClass3()
  {
    ICICL_CONSTRUCTOR();
  }

  ~MyClass3(void)
  {
    ICICL_DESTRUCTOR();
  }

  template <typename U>
  void m() { };
};

template<>
struct MyClass3<MyClass2>
{
  MyClass3()
  {
    ICICL_CONSTRUCTOR();
  }
  ~MyClass3(void)
  {
    ICICL_DESTRUCTOR();
  }

  template <typename U>
  void m() { };
};

} // namespace myclass
