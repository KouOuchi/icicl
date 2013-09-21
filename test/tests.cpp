#include <boost/test/unit_test.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>

#include "icicl.h"

#include "MyClasses.h"
#include "fixtures.h"

using namespace myclass;

#ifdef USE_ICICL
using namespace icicl;
#endif

BOOST_FIXTURE_TEST_SUITE(tests, tests_fixture)


BOOST_AUTO_TEST_CASE( basic_001 )
{
  ICICL_INITIALIZE();
  {
    MyClass1 a;
    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));

    MyClass2 b;
    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass2));
    BOOST_REQUIRE_EQUAL(2, ICICL_GET_ACCUM(MyClass1));

    MyClass3<MyClass1> c;

    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass3<MyClass1>));
  }
  ICICL_CHECK();

  BOOST_REQUIRE_EQUAL(2, ICICL_GET_TOTAL(MyClass1));
  BOOST_REQUIRE_EQUAL(1, ICICL_GET_TOTAL(MyClass2));
  BOOST_REQUIRE_EQUAL(1, ICICL_GET_TOTAL(MyClass3<MyClass1>));
}

BOOST_AUTO_TEST_CASE( basic_002 )
{
  ICICL_INITIALIZE();
  {
    MyClass1* a = new MyClass1();
    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));

    MyClass2* b = new MyClass2();
    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass2));
    BOOST_REQUIRE_EQUAL(2, ICICL_GET_ACCUM(MyClass1));

    MyClass3<MyClass1>* c = new MyClass3<MyClass1>();
    BOOST_REQUIRE_EQUAL(2, ICICL_GET_ACCUM(MyClass1));
    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass3<MyClass1>));

    delete a;
    delete b;
    delete c;
  }
  ICICL_CHECK();

  BOOST_REQUIRE_EQUAL(2, ICICL_GET_TOTAL(MyClass1));
  BOOST_REQUIRE_EQUAL(1, ICICL_GET_TOTAL(MyClass2));
  BOOST_REQUIRE_EQUAL(1, ICICL_GET_TOTAL(MyClass3<MyClass1>));
}

BOOST_AUTO_TEST_CASE( basic_003 )
{
  ICICL_INITIALIZE();
  {
    boost::scoped_ptr<MyClass1> a(new MyClass1());

    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));

    boost::variant<int, MyClass1*> c(a.get());

    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));
  }
  ICICL_CHECK();

  BOOST_REQUIRE_EQUAL(1, ICICL_GET_TOTAL(MyClass1));
}

BOOST_AUTO_TEST_CASE( basic_004 )
{
  ICICL_INITIALIZE();
  {
    boost::scoped_ptr<MyClass1> a(new MyClass1());
    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));
  }
  ICICL_CHECK();

  BOOST_REQUIRE_EQUAL(1, ICICL_GET_TOTAL(MyClass1));
}

BOOST_AUTO_TEST_CASE( basic_005 )
{
  ICICL_INITIALIZE();
  {
    boost::scoped_ptr<MyClass1> a(new MyClass1());

    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));

    {
      boost::variant<int, MyClass1*> c(a.get());
    }

    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));
  }
  ICICL_CHECK();

  BOOST_REQUIRE_EQUAL(1, ICICL_GET_TOTAL(MyClass1));
}

BOOST_AUTO_TEST_CASE( basic_007 )
{
  ICICL_INITIALIZE();
  {
    MyClass3<MyClass1> a;
    a.m<MyClass2>();

    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass3<MyClass1>));
    BOOST_REQUIRE_EQUAL(0, ICICL_GET_ACCUM(MyClass1));
    BOOST_REQUIRE_EQUAL(0, ICICL_GET_ACCUM(MyClass2));  
  }
  ICICL_CHECK();

  BOOST_REQUIRE_EQUAL(1, ICICL_GET_TOTAL(MyClass3<MyClass1>));
}

BOOST_AUTO_TEST_CASE( list_001 )
{
  ICICL_INITIALIZE();
  {
    std::list<MyClass1> a;
    MyClass1 b;
    a.push_back(b);
    a.push_back(b);

    std::list<MyClass1> c(a.begin(), a.end());
    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));
  }
  BOOST_REQUIRE_EQUAL(-4, ICICL_GET_ACCUM(MyClass1)); //std::list destroy MyClass1 4 times

  // std::exception is thrown
  BOOST_REQUIRE_THROW(ICICL_CHECK(), std::exception);
}

BOOST_AUTO_TEST_CASE( leak_001 )
{
  ICICL_INITIALIZE();

  boost::shared_ptr<MyClass1> a(new MyClass1());

  BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));

  // std::exception is thrown because "a" hasn't be deleted.
  BOOST_REQUIRE_THROW(ICICL_CHECK(), std::exception);
}

BOOST_AUTO_TEST_CASE( leak_002 )
{
  ICICL_INITIALIZE();

  {
    boost::shared_ptr<MyClass1> a(new MyClass1());
    boost::variant<int, MyClass1> var1(*(a.get()));

    BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));
  }

  // std::exception is thrown. var1 should be changed to boost::variant<int, MyClass2*>
  BOOST_REQUIRE_THROW(ICICL_CHECK(), std::exception);
}

BOOST_AUTO_TEST_CASE( leak_003 )
{
  ICICL_INITIALIZE();

  new MyClass1();

  BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));

  // std::exception is thrown because "a" hasn't be deleted.
  BOOST_REQUIRE_THROW(ICICL_CHECK(), std::exception);
}

BOOST_AUTO_TEST_CASE( leak_004 )
{
  ICICL_INITIALIZE();
  ICICL_CONFIG_THROW_EXCEPTION(false);

  new MyClass1();

  BOOST_REQUIRE_EQUAL(1, ICICL_GET_ACCUM(MyClass1));

  // std::exception isn't thrown.
  ICICL_CHECK();
}

BOOST_AUTO_TEST_SUITE_END()
