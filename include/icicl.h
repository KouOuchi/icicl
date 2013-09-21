//Copyright (c) 2013 Kou Ouchi and Division Engineering, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <typeinfo>
#include <boost/log/trivial.hpp>

namespace icicl
{

// Trivial severity levels from boost/log/trivial.hpp
namespace severity_level
{
enum _e
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};
}
typedef severity_level::_e severity_level_enum;

#ifdef USE_ICICL

extern void config_throw_exception(bool _x);
extern void config_log_level(severity_level_enum _x);
extern void config_throw_exception(long _x);

extern void constructor(const std::type_info& _x);
extern void destructor(const std::type_info& _x);
extern void initialize();
extern void count();
extern int get_accum(const std::type_info& _x);
extern int get_total(const std::type_info& _x);
extern void check();

#define ICICL_CONFIG_THROW_EXCEPTION(_x) config_throw_exception( _x);
#define ICICL_CONFIG_LOG_LEVEL(_x) config_log_level( _x);
#define ICICL_CONFIG_INTERVAL(_x) config_throw_exception(_x);

#define ICICL_CONSTRUCTOR() constructor(typeid(*this))
#define ICICL_DESTRUCTOR() destructor(typeid(*this))
#define ICICL_INITIALIZE() initialize()
#define ICICL_GET_ACCUM(_x) get_accum(typeid(_x))
#define ICICL_GET_TOTAL(_x) get_total(typeid(_x))
#define ICICL_COUNT() count()
#define ICICL_CHECK() check()

#else

#define ICICL_CONSTRUCTOR() 0
#define ICICL_DESTRUCTOR() 0
#define ICICL_INITIALIZE() 0
#define ICICL_COUNT() 0
#define ICICL_CHECK() 0

#endif

} // namespace icicl
