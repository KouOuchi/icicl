icicl
=====

I Count Instances and Check Leak. (Tiny instance counter and memory leak checker for C++). Running both Linux and Windows.


How To Use
------ 
### prerequisite ###
	#include "icicl.h"

	#ifdef USE_ICICL
	using namespace icicl;
	#endif
 
### modify your constructor and destructor ###
	struct MyClass1
	{
	  MyClass1(void)
	  {
	    ICICL_CONSTRUCTOR();
	  }

	  ~MyClass1(void)
	  {
	    ICICL_DESTRUCTOR();
	  }
	};


### retrieve instance counts ###

	  ICICL_INITIALIZE(); // reset instance counter

	  {
	    MyClass1 a;
	  }

	  ICICL_CHECK(); // test accumulate counters.


Customize
----------------
+   `ICICL_CONFIG_THROW_EXCEPTION(true|false)` :
    When you call ICICL_CHECK():
    true : throw exception if there is a memory leak.
    false : do not throw exception if there is a memory leak.
 
+   `ICICL_CONFIG_LOG_LEVEL(icicl::severity_level)` :
    Set a fileter to boost::log.

+   `ICICL_GET_ACCUM(your_class)` :
    Get your accumulate count abount your_class; 

+   `ICICL_GET_TOTAL(your_class)` :
    Get your total count abount your_class; 
 
+   `ICICL_COUNT()` :
    Get accumulation and total about all class; 


How To Install
--------
### Windows
1. Setup Boost and boost-log
   I confirmed boost-1.53 and boost-log-2.0.

2. Set environment variable BOOST to boost installed path.
   e.g. BOOST=c:\Apps\bin\boost_1_53

3. Build Library 

   run premake.exe vs2010
   And then, Solution is created.


   BUILD->Configuration Manager->Active solution platform. 
   Set to "x64"

   I confirmed in VS2010 and VS2012.

4. Run Test

   In solution explorer, Right Click on icicl_test, and then, Select "Set as startup project" in context menu.

   Start debug.
 
 
### Linux

1. Setup Boost and boost-log

2. Setup environment variable

export BOOST=/usr/local/lib/boost_1_53_0
LD_LIBRARY_PATH=${BOOST}/stage/x64/lib

3. Build
	$ premake gmake
	$ make config=debug
	$ gmake/icicl_test_d 
	.-=< icicl test start >=-.
	Running 11 test cases...
	[2013-09-22 00:35:39.646030] [0x03369740] [fatal]   N7myclass8MyClass1E: accum=-4: total=1
	[2013-09-22 00:35:39.646138] [0x03369740] [fatal]   detect memory leak!
	[2013-09-22 00:35:39.646572] [0x03369740] [fatal]   N7myclass8MyClass1E: accum=1: total=1
	[2013-09-22 00:35:39.646590] [0x03369740] [fatal]   detect memory leak!
	[2013-09-22 00:35:39.646887] [0x03369740] [fatal]   N7myclass8MyClass1E: accum=-1: total=1
	[2013-09-22 00:35:39.646914] [0x03369740] [fatal]   detect memory leak!
	[2013-09-22 00:35:39.647083] [0x03369740] [fatal]   N7myclass8MyClass1E: accum=1: total=1
	[2013-09-22 00:35:39.647106] [0x03369740] [fatal]   detect memory leak!
	[2013-09-22 00:35:39.648721] [0x03369740] [fatal]   N7myclass8MyClass1E: accum=1: total=1
	[2013-09-22 00:35:39.648873] [0x03369740] [fatal]   detect memory leak!
	.-=< icicl test end >=-.

*** No errors detected

Related Information
--------
### BOOST
  [link]: http://www.boost.org/ "?"
 
### BOOST LOG
  [link]: http://www.boost.org/ "?"

### RTTI
  [link]: http://www.cplusplus.com/reference/typeinfo/type_info/ "?"

TODO
--------
1. Retrieve counts at regular intervals.

License
----------
Copyright &copy; 2013 Kou Ouchi<kou.ouchi@division-engineering.com>
Licensed under the [Boost Software License 1.0]
[BOOST]: http://www.boost.org/LICENSE_1_0.txt