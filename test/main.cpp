#define BOOST_TEST_MODULE main

#include <boost/test/included/unit_test.hpp>
#include <iostream>

struct TestMain
{
  TestMain()
  {
    std::cout << ".-=< icicl test start >=-." << std::endl;
  }
  ~TestMain()
  {
    std::cout << ".-=< icicl test end >=-." << std::endl;
#if defined(WIN32) || defined(WIN64) || defined(WINDOWS)
    ::system("pause");
#endif
  }
};

BOOST_GLOBAL_FIXTURE( TestMain );
