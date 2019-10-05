//Copyright (c) 2013 Kou Ouchi and Division Engineering, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <typeinfo>
#include <map>
#include <tuple>
#include <string>

namespace icicl
{

#ifdef ENABLE_ICICL

void config_throw_exception(bool _x);
void config_throw_exception(long _x);
void constructor(const std::type_info& _x);
void destructor(const std::type_info& _x);
void initialize();
void count();
int get_accum(const std::type_info& _x);
int get_total(const std::type_info& _x);
void check();

#define ICICL_CONFIG_THROW_EXCEPTION(_x) config_throw_exception( _x);
#define ICICL_CONFIG_LOG_LEVEL(_x) config_log_level( _x);
#define ICICL_CONFIG_INTERVAL(_x) config_throw_exception(_x);
#define ICICL_CONSTRUCTOR() icicl::constructor(typeid(*this))
#define ICICL_DESTRUCTOR() icicl::destructor(typeid(*this))
#define ICICL_INITIALIZE() icicl::initialize()
#define ICICL_GET_ACCUM(_x) icicl::get_accum(typeid(_x))
#define ICICL_GET_TOTAL(_x) icicl::get_total(typeid(_x))
#define ICICL_COUNT() icicl::count()
#define ICICL_CHECK() icicl::check()

#else

#define ICICL_CONSTRUCTOR() 0
#define ICICL_DESTRUCTOR() 0
#define ICICL_INITIALIZE() 0
#define ICICL_COUNT() 0
#define ICICL_CHECK() 0

#endif

} // namespace icicl
