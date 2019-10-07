icicl
=====

**I** **C**ount **I**nstances and **C**heck **L**eak. (Tiny instance counter and memory leak checker for C++). 

How To Use
------ 
+   Add icicl.cpp into your project.
+   Add Definition ``ENABLE_ICICLE'' into your project
+   Include icicl.h 
	```
    #include "icicl.h"
	'''

+   Modify your constructor and destructor ###
	```
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
	'''

+ Retrieve instance counts and check. ###
	```
	  ICICL_INITIALIZE(); // reset instance counter.

	  {
	    ...
	    MyClass1 a;
	    ...
	  }

	  ICICL_CHECK(); // test accumulate counters and log statistics.
	'''


Customize
----------------
+   `ICICL_CONFIG_THROW_EXCEPTION(true|false)` :
    When you call ICICL_CHECK():
    true : throw exception if there is a memory leak.
    false : do not throw exception if there is a memory leak.
 
+   `ICICL_GET_ACCUM(your_class)` :
    Get your accumulate count abount your_class.

+   `ICICL_GET_TOTAL(your_class)` :
    Get your total count abount your_class.
 
+   `ICICL_COUNT()` :
    Get accumulation and total about all class.


Related Information
--------
* RTTI
  http://www.cplusplus.com/reference/typeinfo/type_info/ "type_info"

License
----------
  * Copyright &copy; 2013-2019 Kou Ouchi <kou.ouchi@division-engineering.com>
